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

#ifndef TEST_FILE_TRANSFER_METHOD_H_
#define TEST_FILE_TRANSFER_METHOD_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libs2opc_client_cmds.h"
#include "sopc_builtintypes.h"

/* Set this macro to "1" to enable debug: display directly pieces of informations
 *  on the console.
 */
#define TEST_DEBUG_FT 0

/**
 * \brief Get the current internal TestCase number.
 * \return The current TestCase number.
 */
int32_t SOPC_TEST_FileTransfer_GetTestCaseNumber(void);

/**
 * \brief Set the current internal TestCase number.
 * \param number The number to set.
 */
void SOPC_TEST_FileTransfer_SetTestCaseNumber(int32_t number);

/**
 * \brief Open a file with a specific mode and return a file handle.
 * \param connectionId connectionId of the client.
 * \param sameTestCase true if it is the same test case, otherwise false.
 * \param pCallRequest Pointer to the CallRequest, it contains the input parameters of the method call
 * \param pCallResult Pointer to the CallResult, it contains the result of the method call
 * \param met_openId Node ID of the open method
 * \param mode The selected mode of the file:
 *        - bit 0 : The file is opened for reading. If this bit is not set the Read Method cannot be executed.
 *
 *        - bit 1 : The file is opened for writing. If this bit is not set the Write Method cannot be executed.
 *
 *        - bit 2 : This bit can only be set if the file is opened for writing (Write bit is set).
 *              The existing content of the file is erased and an empty file is provided.
 *
 *        - bit 3 : When the Append bit is set the file is opened at end of the file, otherwise at begin of the file.
 *              The SetPosition Method can be used to change the position.
 *
 * \return uint32_t fileHandle. The fileHandle is generated by the server and is unique for the Session
 *         fileHanlde is equal to 0 if an error occurs.
 */
uint32_t SOPC_TEST_FileTransfer_OpenMethod(int32_t connectionId,
                                           bool sameTestCase,
                                           SOPC_ClientHelper_CallMethodRequest* pCallRequest,
                                           SOPC_ClientHelper_CallMethodResult* pCallResults,
                                           char* met_openId,
                                           SOPC_Byte mode);

/**
 * \brief Close a file thanks to fileHandle. Then the fileHanlde becomes invalid.
 * \param connectionId connectionId of the client.
 * \param sameTestCase true if it is the same test case, otherwise false.
 * \param pCallRequest Pointer to the CallRequest, it contains the input parameters of the method call
 * \param pCallResult Pointer to the CallResult, it contains the result of the method call
 * \param met_closeId Node ID of the close method
 * \param fileHandle fileHandle given by the open method
 * \return SOPC_GoodGenericStatus otherwise other value
 */
SOPC_StatusCode SOPC_TEST_FileTransfer_CloseMethod(int32_t connectionId,
                                                   bool sameTestCase,
                                                   SOPC_ClientHelper_CallMethodRequest* pCallRequest,
                                                   SOPC_ClientHelper_CallMethodResult* pCallResults,
                                                   char* met_closeId,
                                                   uint32_t fileHandle);

/**
 * \brief Write bytes from the current position in the file. Moves the cursor from X number of bytes.
 * \param connectionId connectionId of the client.
 * \param sameTestCase true if it is the same test case, otherwise false.
 * \param pCallRequest Pointer to the CallRequest, it contains the input parameters of the method call
 * \param pCallResult Pointer to the CallResult, it contains the result of the method call
 * \param met_writeId Node ID of the write method
 * \param fileHandle fileHandle given by the open method
 * \param dataToWrite String Data to be written in the file in byte size.
 * \return SOPC_GoodGenericStatus otherwise other value
 */
SOPC_StatusCode SOPC_TEST_FileTransfer_WriteMethod(int32_t connectionId,
                                                   bool sameTestCase,
                                                   SOPC_ClientHelper_CallMethodRequest* pCallRequest,
                                                   SOPC_ClientHelper_CallMethodResult* pCallResults,
                                                   char* met_writeId,
                                                   uint32_t fileHandle,
                                                   SOPC_ByteString* dataToWrite);

/**
 * \brief Read bytes from the current position in the file.
 * \param connectionId connectionId of the client.
 * \param sameTestCase true if it is the same test case, otherwise false.
 * \param pCallRequest Pointer to the CallRequest, it contains the input parameters of the method call.
 * \param pCallResult Pointer to the CallResult, it contains the result of the method call.
 * \param met_readId Node ID of the read method.
 * \param fileHandle fileHandle given by the open method.
 * \param length number of bytes to read in byte size.
 * \return SOPC_GoodGenericStatus otherwise other value
 */
SOPC_StatusCode SOPC_TEST_FileTransfer_ReadMethod(int32_t connectionId,
                                                  bool sameTestCase,
                                                  SOPC_ClientHelper_CallMethodRequest* pCallRequest,
                                                  SOPC_ClientHelper_CallMethodResult* pCallResults,
                                                  char* met_readId,
                                                  uint32_t fileHandle,
                                                  int32_t length);

/**
 * \brief Set the current position to a specific position in the file.
 * \param connectionId connectionId of the client.
 * \param sameTestCase true if it is the same test case, otherwise false.
 * \param pCallRequest Pointer to the CallRequest, it contains the input parameters of the method call.
 * \param pCallResult Pointer to the CallResult, it contains the result of the method call.
 * \param met_setposId Node ID of the set position method.
 * \param fileHandle fileHandle given by the open method.
 * \param position Position to set in the file.
 * \return SOPC_GoodGenericStatus otherwise other value
 */
SOPC_StatusCode SOPC_TEST_FileTransfer_SetPositionMethod(int32_t connectionId,
                                                         bool sameTestCase,
                                                         SOPC_ClientHelper_CallMethodRequest* pCallRequest,
                                                         SOPC_ClientHelper_CallMethodResult* pCallResults,
                                                         char* met_setposdId,
                                                         uint32_t fileHandle,
                                                         uint64_t position);

/**
 * \brief Get the current position of the cursor in the file.
 * \param connectionId connectionId of the client.
 * \param sameTestCase true if it is the same test case, otherwise false.
 * \param pCallRequest Pointer to the CallRequest, it contains the input parameters of the method call.
 * \param pCallResult Pointer to the CallResult, it contains the result of the method call.
 * \param met_getposId Node ID of the get position method.
 * \param fileHandle fileHandle given by the open method.
 * \return uint64_t getposition: the current position of the cursor in the file.
 */
uint64_t SOPC_TEST_FileTransfer_GetPositionMethod(int32_t connectionId,
                                                  bool sameTestCase,
                                                  SOPC_ClientHelper_CallMethodRequest* pCallRequest,
                                                  SOPC_ClientHelper_CallMethodResult* pCallResults,
                                                  char* met_getposId,
                                                  uint32_t fileHandle);

#endif
