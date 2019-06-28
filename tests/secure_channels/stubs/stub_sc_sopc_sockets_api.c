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

#include "stub_sc_sopc_sockets_api.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "event_helpers.h"
#include "hexlify.h"
#include "sopc_buffer.h"

SOPC_AsyncQueue* socketsInputEvents = NULL;
SOPC_EventHandler* socketsEventHandler = NULL;

void SOPC_Sockets_EnqueueEvent(SOPC_Sockets_InputEvent scEvent, uint32_t id, void* params, uintptr_t auxParam)
{
    SOPC_ReturnStatus status = SOPC_STATUS_OK;
    SOPC_Event* scParams = SOPC_Calloc(1, sizeof(SOPC_Event));
    assert(scParams != NULL && socketsInputEvents != NULL);
    scParams->event = (int32_t) scEvent;
    scParams->eltId = id;
    scParams->params = params;
    scParams->auxParam = auxParam;

    status = SOPC_AsyncQueue_BlockingEnqueue(socketsInputEvents, (void*) scParams);

    (void) status; // avoid unused parameter compiler warning: status is not used if asserts are not compiled in
    assert(status == SOPC_STATUS_OK);
}

void SOPC_Sockets_Initialize()
{
    SOPC_ReturnStatus status = SOPC_AsyncQueue_Init(&socketsInputEvents, "StubsSC_SocketsEventQueue");
    assert(status == SOPC_STATUS_OK);
}

void SOPC_Sockets_Clear()
{
    SOPC_AsyncQueue_Free(&socketsInputEvents);
}

void SOPC_Sockets_SetEventHandler(SOPC_EventHandler* handler)
{
    socketsEventHandler = handler;
}

SOPC_Event* Check_Socket_Event_Received(SOPC_Sockets_InputEvent event, uint32_t eltId, uintptr_t auxParam)
{
    SOPC_Event* socketEvent = NULL;
    WaitEvent(socketsInputEvents, (void**) &socketEvent);

    if (CheckEvent("Sockets", socketEvent, (int32_t) event, eltId, auxParam))
    {
        return socketEvent;
    }
    else
    {
        free(socketEvent);
        return NULL;
    }
}

static SOPC_ReturnStatus check_expected_sent_message_helper(const char* hexExpMsg,
                                                            const SOPC_Buffer* buffer,
                                                            bool ignoreBytes,
                                                            uint16_t start,
                                                            uint16_t length)
{
    char hexOutput[5000];
    int res = 0;

    if (ignoreBytes != false)
    {
        assert((uint32_t)(start + length) <= buffer->length);
        // Set bytes to 0
        memset(buffer->data + start, 0, (size_t) length);
    }

    res = hexlify(buffer->data, hexOutput, buffer->length);

    if ((uint32_t) res != buffer->length || strlen(hexExpMsg) != 2 * buffer->length)
    {
        printf("SC_Rcv_Buffer: ERROR invalid message length\n");
        return SOPC_STATUS_NOK;
    }

    res = memcmp(hexOutput, hexExpMsg, strlen(hexExpMsg));
    if (res != 0)
    {
        printf("SC_Rcv_Buffer: ERROR invalid message content\n");
        printf("expected \n%s\n", hexExpMsg);
        printf("provided \n%s\n", hexOutput);
        return SOPC_STATUS_NOK;
    }

    return SOPC_STATUS_OK;
}

SOPC_ReturnStatus Check_Expected_Sent_Message(uint32_t socketIdx,
                                              const char* hexExpMsg,
                                              bool ignoreBytes,
                                              uint16_t start,
                                              uint16_t length)
{
    // Retrieve socket event to write message
    SOPC_Event* socketEvent = Check_Socket_Event_Received(SOCKET_WRITE, socketIdx, 0);

    if (socketEvent == NULL)
    {
        return SOPC_STATUS_NOK;
    }

    SOPC_Buffer* buffer = (SOPC_Buffer*) socketEvent->params;

    SOPC_ReturnStatus status;

    if (buffer == NULL)
    {
        status = SOPC_STATUS_NOK;
    }
    else
    {
        status = check_expected_sent_message_helper(hexExpMsg, buffer, ignoreBytes, start, length);
    }

    SOPC_Buffer_Delete(buffer);
    free(socketEvent);
    return status;
}

SOPC_ReturnStatus Simulate_Received_Message(uint32_t scIdx, char* hexInputMsg)
{
    assert(strlen(hexInputMsg) <= UINT32_MAX);

    SOPC_ReturnStatus status = SOPC_STATUS_OK;
    SOPC_Buffer* buffer = SOPC_Buffer_Create((uint32_t) strlen(hexInputMsg) / 2);

    int res = 0;

    if (buffer != NULL)
    {
        status = SOPC_Buffer_SetDataLength(buffer, (uint32_t) strlen(hexInputMsg) / 2);

        if (SOPC_STATUS_OK == status)
        {
            res = unhexlify(hexInputMsg, buffer->data, buffer->length);

            if ((uint32_t) res != buffer->length)
            {
                printf("SC_Rcv_Buffer: ERROR: unhexlify received message error\n");
                status = SOPC_STATUS_NOK;
            }
        }
        if (SOPC_STATUS_OK == status)
        {
            SOPC_EventHandler_Post(socketsEventHandler, SOCKET_RCV_BYTES, scIdx, (void*) buffer, 0);
        }
    }
    else
    {
        status = SOPC_STATUS_NOK;
    }

    if (SOPC_STATUS_OK != status)
    {
        SOPC_Buffer_Delete(buffer);
    }
    return status;
}
