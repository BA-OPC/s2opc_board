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
 * \privatesection
 *
 * \brief Internal module used to manage the wrapper for client config. It should not be used outside of the client
 * wraper implementation.
 *
 */

#ifndef LIBS2OPC_CLIENT_INTERNAL_H_
#define LIBS2OPC_CLIENT_INTERNAL_H_

#include <stdbool.h>

#include "libs2opc_new_client.h"

#include "sopc_mutexes.h"
#include "sopc_user_app_itf.h"

// The client helper dedicated configuration in addition to configuration ::SOPC_S2OPC_Config
typedef struct SOPC_ClientHelper_Config
{
    // Flag atomically set when the structure is initialized during call to SOPC_HelperConfigClient_Initialize
    // and singleton config is initialized
    int32_t initialized;
    Mutex configMutex;

    SOPC_ClientConnection* secureConnections[SOPC_MAX_CLIENT_SECURE_CONNECTIONS_CONFIG];
    int32_t openedReverseEndpointsIdx[SOPC_MAX_CLIENT_SECURE_CONNECTIONS_CONFIG];

    SOPC_ServiceAsyncResp_Fct* asyncRespCb;

    SOPC_GetPassword_Fct* getClientKeyPasswordCb;

    SOPC_GetClientUserPassword_Fct* getUserKeyPasswordCb;
    SOPC_GetClientUserPassword_Fct* getUserNamePasswordCb;
} SOPC_ClientHelper_Config;

// The singleton configuration structure
extern SOPC_ClientHelper_Config sopc_client_helper_config;

// Returns true if the client is initialize, false otherwise
bool SOPC_ClientInternal_IsInitialized(void);

void SOPC_ClientInternal_ToolkitEventCallback(SOPC_App_Com_Event event,
                                              uint32_t IdOrStatus,
                                              void* param,
                                              uintptr_t appContext);

// Finalize the SecureChannel configuration by parsing the necessary files
SOPC_ReturnStatus SOPC_HelperConfigClient_Finalize_SecureConnectionConfig(const SOPC_Client_Config* cConfig,
                                                                          SOPC_SecureConnection_Config* secConnConfig);

/**
 * \brief Function to call the callback to retrieve password for decryption of the Client private key.
 *
 * \param[out] outPassword   the newly allocated password.
 *
 * \return                   true in case of success, otherwise false.
 *
 */
bool SOPC_ClientInternal_GetClientKeyPassword(char** outPassword);

/**
 * \brief Function to know if the callback has been defined ::SOPC_HelperConfigClient_SetClientKeyPasswordCallback (i.e.
 * the client's key is encrypted).
 *
 */
bool SOPC_ClientInternal_IsEncryptedClientKey(void);

/**
 * \brief Function to call the callback to retrieve password for decryption of the user private key associated to given
 *        cert Sha1.
 *
 * \param[out] outPassword   the newly allocated password.
 *
 * \return                   true in case of success, otherwise false.
 *
 */
bool SOPC_ClientInternal_GetUserKeyPassword(const char* cert1Sha1, char** outPassword);

/**
 * \brief Function to call the callback to retrieve password associated to given username
 *
 * \param[out] outPassword   the newly allocated password.
 *
 * \return                   true in case of success, otherwise false.
 *
 */
bool SOPC_ClientInternal_GetUserNamePassword(const char* username, char** outPassword);

#endif /* LIBS2OPC_CLIENT_INTERNAL_H_ */
