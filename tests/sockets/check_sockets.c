/*
 * Licensed to Systerel under one or more contributor license
 * agreements. See the NOTICE file distributed with this work
 * for additional information regarding copyright ownership.
 * Systerel licenses this file to you under the Apache
 * License, Version 2.0 (the "License"); you may not use this
 * file except in compliance with the License. You may obtain
 * a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

/** \file
 *
 * \brief Entry point for tools tests. Tests use libcheck.
 *
 * If you want to debug the exe, you should define env var CK_FORK=no
 * http://check.sourceforge.net/doc/check_html/check_4.html#No-Fork-Mode
 */

#include <check.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "sopc_buffer.h"

#include "sopc_async_queue.h"
#include "sopc_event_timer_manager.h"
#include "sopc_sockets_api.h"

const char* uri = "opc.tcp://localhost:4841/myEndPoint";
const uint32_t endpointDescConfigId = 10;
const uint32_t serverSecureChannelConnectionId = 100;
const uint32_t clientSecureChannelConnectionId = 200;

static SOPC_AsyncQueue* socketEvents = NULL;

static void onSocketEvent(SOPC_EventHandler* handler, int32_t event, uint32_t id, void* params, uintptr_t auxParam)
{
    (void) handler;

    SOPC_Event* ev = calloc(1, sizeof(SOPC_Event));
    ck_assert_ptr_nonnull(ev);

    ev->event = event;
    ev->eltId = id;
    ev->params = params;
    ev->auxParam = auxParam;

    ck_assert_int_eq(SOPC_STATUS_OK, SOPC_AsyncQueue_BlockingEnqueue(socketEvents, ev));
}

static SOPC_Event* expect_event(int32_t event, uint32_t id)
{
    SOPC_Event* ev = NULL;
    ck_assert_int_eq(SOPC_STATUS_OK, SOPC_AsyncQueue_BlockingDequeue(socketEvents, (void**) &ev));
    ck_assert_int_eq(event, ev->event);
    ck_assert_uint_eq(id, ev->eltId);
    return ev;
}

START_TEST(test_sockets)
{
    uint32_t serverSocketIdx = 0;
    uint32_t clientSocketIdx = 0;

    SOPC_Buffer* sendBuffer = SOPC_Buffer_Create(1000);
    SOPC_Buffer* receivedBuffer = NULL;
    SOPC_Buffer* accBuffer = SOPC_Buffer_Create(1000);
    uint32_t idx = 0;
    uint8_t byte = 0;
    uint32_t receivedBytes = 0;
    uint8_t attempts = 0;

    SOPC_EventTimer_Initialize();
    SOPC_Sockets_Initialize();

    ck_assert_int_eq(SOPC_STATUS_OK, SOPC_AsyncQueue_Init(&socketEvents, ""));

    SOPC_Looper* looper = SOPC_Looper_Create();
    ck_assert_ptr_nonnull(looper);

    SOPC_EventHandler* event_handler = SOPC_EventHandler_Create(looper, onSocketEvent);
    ck_assert_ptr_nonnull(event_handler);

    SOPC_Sockets_SetEventHandler(event_handler);

    /* SERVER SIDE: listener creation */

    // const URI is not modified but generic API cannot guarantee it
    SOPC_GCC_DIAGNOSTIC_IGNORE_CAST_CONST
    SOPC_Sockets_EnqueueEvent(SOCKET_CREATE_SERVER, endpointDescConfigId, (void*) uri, (uint32_t) true);
    SOPC_GCC_DIAGNOSTIC_RESTORE

    free(expect_event(SOCKET_LISTENER_OPENED, endpointDescConfigId));

    /* CLIENT SIDE: connection establishment */
    // Create client connection
    // const URI is not modified but generic API cannot guarantee it
    SOPC_GCC_DIAGNOSTIC_IGNORE_CAST_CONST
    SOPC_Sockets_EnqueueEvent(SOCKET_CREATE_CLIENT, clientSecureChannelConnectionId, (void*) uri, 0);
    SOPC_GCC_DIAGNOSTIC_RESTORE

    /* SERVER SIDE: accepted connection (socket level only) */
    {
        SOPC_Event* ev = expect_event(SOCKET_LISTENER_CONNECTION, endpointDescConfigId);
        serverSocketIdx = (uint32_t) ev->auxParam;
        free(ev);
    }

    /* CLIENT SIDE: accepted socket connection */
    {
        SOPC_Event* ev = expect_event(SOCKET_CONNECTION, clientSecureChannelConnectionId);
        clientSocketIdx = (uint32_t) ev->auxParam;
        free(ev);
    }

    /* SERVER SIDE: finish accepting connection (secure channel level) */
    // Note: a new secure channel (with associated connection index) has been created and
    //       must be recorded by the socket as the connection Id
    SOPC_Sockets_EnqueueEvent(SOCKET_ACCEPTED_CONNECTION, serverSocketIdx, NULL, serverSecureChannelConnectionId);

    /* CLIENT SIDE: send a msg buffer through connection */
    for (idx = 0; idx < 1000; idx++)
    {
        byte = (uint8_t)(idx % 256);
        SOPC_Buffer_Write(sendBuffer, &byte, 1);
    }
    SOPC_Sockets_EnqueueEvent(SOCKET_WRITE, clientSocketIdx, (void*) sendBuffer, 0);
    sendBuffer = NULL; // deallocated by Socket event manager

    /* SERVER SIDE: receive a msg buffer through connection */
    // Accumulate received bytes in a unique buffer
    receivedBytes = 0;
    // Let 5 attempts to retrieve all the bytes
    attempts = 0;
    while (receivedBytes < 1000 && attempts < 5)
    {
        SOPC_Event* ev = expect_event(SOCKET_RCV_BYTES, serverSecureChannelConnectionId);
        receivedBuffer = (SOPC_Buffer*) ev->params;
        free(ev);

        ck_assert(receivedBuffer->length <= 1000);
        receivedBytes = receivedBytes + receivedBuffer->length;
        SOPC_Buffer_Write(accBuffer, receivedBuffer->data, receivedBuffer->length);
        SOPC_Buffer_Delete(receivedBuffer);

        attempts++;
    }

    ck_assert(receivedBytes == 1000 && accBuffer->length == 1000);
    receivedBuffer = NULL;
    SOPC_Buffer_SetPosition(accBuffer, 0);

    // Check acc buffer content
    for (idx = 0; idx < 1000; idx++)
    {
        SOPC_Buffer_Read(&byte, accBuffer, 1);
        ck_assert(byte == (idx % 256));
    }

    /* SERVER SIDE: send a msg buffer through connection */
    sendBuffer = SOPC_Buffer_Create(1000);
    SOPC_Buffer_Reset(accBuffer);

    for (idx = 0; idx < 1000; idx++)
    {
        byte = (uint8_t)(idx % 256);
        SOPC_Buffer_Write(sendBuffer, &byte, 1);
    }
    SOPC_Sockets_EnqueueEvent(SOCKET_WRITE, serverSocketIdx, (void*) sendBuffer, 0);
    sendBuffer = NULL; // deallocated by Socket event manager

    /* CLIENT SIDE: receive a msg buffer through connection */
    // Accumulate received bytes in a unique buffer
    receivedBytes = 0;
    // Let 5 attempts to retrieve all the bytes
    attempts = 0;
    while (receivedBytes < 1000 && attempts < 5)
    {
        SOPC_Event* ev = expect_event(SOCKET_RCV_BYTES, clientSecureChannelConnectionId);
        receivedBuffer = (SOPC_Buffer*) ev->params;
        free(ev);

        ck_assert(receivedBuffer->length <= 1000);
        receivedBytes = receivedBytes + receivedBuffer->length;
        SOPC_Buffer_Write(accBuffer, receivedBuffer->data, receivedBuffer->length);
        SOPC_Buffer_Delete(receivedBuffer);

        attempts++;
    }

    ck_assert(receivedBytes == 1000 && accBuffer->length == 1000);
    receivedBuffer = NULL;
    SOPC_Buffer_SetPosition(accBuffer, 0);

    // Check acc buffer content
    for (idx = 0; idx < 1000; idx++)
    {
        SOPC_Buffer_Read(&byte, accBuffer, 1);
        ck_assert(byte == (idx % 256));
    }

    SOPC_Buffer_Delete(accBuffer);

    /* CLIENT SIDE: send a msg buffer through connection with a length greater than maximum message size
     * => the socket layer shall provide it in several buffers  */
    sendBuffer = SOPC_Buffer_Create(2 * SOPC_MAX_MESSAGE_LENGTH);
    accBuffer = SOPC_Buffer_Create(2 * SOPC_MAX_MESSAGE_LENGTH);

    for (idx = 0; idx < 2 * SOPC_MAX_MESSAGE_LENGTH; idx++)
    {
        byte = (uint8_t)(idx % 256);
        SOPC_Buffer_Write(sendBuffer, &byte, 1);
    }
    SOPC_Sockets_EnqueueEvent(SOCKET_WRITE, clientSocketIdx, (void*) sendBuffer, 0);
    sendBuffer = NULL; // deallocated by Socket event manager

    /* SERVER SIDE: receive a msg buffer through connection */
    // Accumulate received bytes in a unique buffer
    receivedBytes = 0;
    // Let 10 attempts to retrieve all the bytes
    attempts = 0;
    while (receivedBytes < 2 * SOPC_MAX_MESSAGE_LENGTH && attempts < 10)
    {
        SOPC_Event* ev = expect_event(SOCKET_RCV_BYTES, serverSecureChannelConnectionId);
        receivedBuffer = (SOPC_Buffer*) ev->params;
        free(ev);

        ck_assert(receivedBuffer->length <= 2 * SOPC_MAX_MESSAGE_LENGTH);
        receivedBytes = receivedBytes + receivedBuffer->length;
        SOPC_Buffer_Write(accBuffer, receivedBuffer->data, receivedBuffer->length);
        SOPC_Buffer_Delete(receivedBuffer);

        attempts++;
    }

    ck_assert(receivedBytes == 2 * SOPC_MAX_MESSAGE_LENGTH && accBuffer->length == 2 * SOPC_MAX_MESSAGE_LENGTH);
    ck_assert(attempts > 1);
    receivedBuffer = NULL;
    SOPC_Buffer_SetPosition(accBuffer, 0);

    // Check acc buffer content
    for (idx = 0; idx < 2 * SOPC_MAX_MESSAGE_LENGTH; idx++)
    {
        SOPC_Buffer_Read(&byte, accBuffer, 1);
        ck_assert(byte == (idx % 256));
    }

    SOPC_Buffer_Delete(accBuffer);

    /* CLIENT SIDE: receive a msg buffer through connection */
    SOPC_Sockets_EnqueueEvent(SOCKET_CLOSE, clientSocketIdx, NULL, 0);

    /* SERVER SIDE: accepted connection (socket level only) */
    {
        SOPC_Event* ev = expect_event(SOCKET_FAILURE, serverSecureChannelConnectionId);
        ck_assert_uint_eq(serverSocketIdx, ev->auxParam);
        free(ev);
    }

    SOPC_Sockets_Clear();
    SOPC_EventTimer_Clear();
}
END_TEST

Suite* tests_make_suite_sockets(void)
{
    Suite* s;
    TCase* tc_sockets;

    s = suite_create("Sockets");
    tc_sockets = tcase_create("Sockets");
    tcase_add_test(tc_sockets, test_sockets);
    suite_add_tcase(s, tc_sockets);

    return s;
}

int main(void)
{
    int number_failed;
    SRunner* sr;

    sr = srunner_create(tests_make_suite_sockets());

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
