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

#include <stdio.h>
#include <string.h>

#include "libs2opc_client_config.h"
#include "libs2opc_client_internal.h"
#include "libs2opc_common_config.h"
#include "libs2opc_common_internal.h"
// TODO: remove, only to set logger in state machine
#include "toolkit_helpers.h"

#include "sopc_assert.h"
#include "sopc_atomic.h"
#include "sopc_key_manager.h"
#include "sopc_logger.h"
#include "sopc_mem_alloc.h"
#include "sopc_pki_stack.h"
#include "sopc_toolkit_async_api.h"
#include "sopc_toolkit_config.h"

const SOPC_ClientHelper_Config sopc_client_helper_config_default = {
    .initialized = false,
    .secureConnections = {NULL},
    .configuredReverseEndpointsToCfgIdx = {0},
    .openedReverseEndpointsFromCfgIdx = {false},
    .asyncRespCb = NULL,

    .getClientKeyPasswordCb = NULL,
    .getUserKeyPasswordCb = NULL,

    .getUserNamePasswordCb = NULL,
};

SOPC_ClientHelper_Config sopc_client_helper_config = {
    .initialized = false, // ensures it will indicated not initialized before first init
};

bool SOPC_ClientInternal_IsInitialized(void)
{
    return SOPC_Atomic_Int_Get(&sopc_client_helper_config.initialized);
}

static void SOPC_ClientHelper_Logger(const SOPC_Log_Level log_level, const char* text)
{
    switch (log_level)
    {
    case SOPC_LOG_LEVEL_ERROR:
        SOPC_Logger_TraceError(SOPC_LOG_MODULE_CLIENTSERVER, "%s", text);
        break;
    case SOPC_LOG_LEVEL_WARNING:
        SOPC_Logger_TraceWarning(SOPC_LOG_MODULE_CLIENTSERVER, "%s", text);
        break;
    case SOPC_LOG_LEVEL_INFO:
        SOPC_Logger_TraceInfo(SOPC_LOG_MODULE_CLIENTSERVER, "%s", text);
        break;
    case SOPC_LOG_LEVEL_DEBUG:
        SOPC_Logger_TraceDebug(SOPC_LOG_MODULE_CLIENTSERVER, "%s", text);
        break;
    default:
        SOPC_ASSERT(false);
    }
}

SOPC_ReturnStatus SOPC_HelperConfigClient_Initialize(void)
{
    if (!SOPC_CommonHelper_GetInitialized() || SOPC_ClientInternal_IsInitialized())
    {
        // Common wrapper not initialized or client wrapper already initialized
        return SOPC_STATUS_INVALID_STATE;
    }

    // SOPC_CommonHelper_SetClientComEvent done by SOPC_ClientCommon_Initialize

    SOPC_S2OPC_Config* pConfig = SOPC_CommonHelper_GetConfiguration();
    SOPC_ASSERT(NULL != pConfig);
    sopc_client_helper_config = sopc_client_helper_config_default;

    // We only do copies in helper config
    pConfig->clientConfig.freeCstringsFlag = true;

    // Client state initialization
    SOPC_ReturnStatus mutStatus = Mutex_Initialization(&sopc_client_helper_config.configMutex);
    SOPC_ASSERT(SOPC_STATUS_OK == mutStatus);

    mutStatus = Condition_Init(&sopc_client_helper_config.reverseEPsClosedCond);
    SOPC_ASSERT(SOPC_STATUS_OK == mutStatus);

    SOPC_ReturnStatus status = SOPC_CommonHelper_SetClientComEvent(SOPC_ClientInternal_ToolkitEventCallback);
    SOPC_Atomic_Int_Set(&sopc_client_helper_config.initialized, (int32_t) true);

    // TODO: to be deleted and state machine shall use library logger
    Helpers_SetLogger(SOPC_ClientHelper_Logger);

    if (SOPC_STATUS_OK != status)
    {
        SOPC_HelperConfigClient_Clear();
    }
    return status;
}

static bool SOPC_Internal_AllReverseEPsClosed(SOPC_S2OPC_Config* pConfig)
{
    for (uint16_t i = 0; i < pConfig->clientConfig.nbReverseEndpointURLs; i++)
    {
        uint32_t cfgIdx = sopc_client_helper_config.configuredReverseEndpointsToCfgIdx[i];
        if (sopc_client_helper_config
                .openedReverseEndpointsFromCfgIdx[SOPC_ClientInternal_GetReverseEPcfgIdxNoOffset(cfgIdx)])
        {
            return false;
        }
    }
    return true;
}

void SOPC_HelperConfigClient_Clear(void)
{
    if (!SOPC_ClientInternal_IsInitialized())
    {
        // Client wrapper not initialized
        return;
    }

    SOPC_S2OPC_Config* pConfig = NULL;

    SOPC_ReturnStatus mutStatus = Mutex_Lock(&sopc_client_helper_config.configMutex);
    SOPC_ASSERT(SOPC_STATUS_OK == mutStatus);

    pConfig = SOPC_CommonHelper_GetConfiguration();

    // Close connections/sessions if not already done
    SOPC_ClientConnection* secureConnection = NULL;
    for (size_t i = 0; i < pConfig->clientConfig.nbSecureConnections; i++)
    {
        secureConnection = sopc_client_helper_config.secureConnections[i];
        if (NULL != secureConnection)
        {
            // TODO: replace by a DisconnectAll operation ?
            mutStatus = Mutex_Unlock(&sopc_client_helper_config.configMutex);
            SOPC_ASSERT(SOPC_STATUS_OK == mutStatus);
            SOPC_ClientHelper_Disconnect(&secureConnection);
            mutStatus = Mutex_Lock(&sopc_client_helper_config.configMutex);
            SOPC_ASSERT(SOPC_STATUS_OK == mutStatus);
        }
    }

    // Close all reverse endpoints
    SOPC_ReverseEndpointConfigIdx rEPcfgIdx = 0;
    uint32_t rEPcfgIdxNoOffset = 0;
    for (uint16_t i = 0; i < pConfig->clientConfig.nbReverseEndpointURLs; i++)
    {
        rEPcfgIdx = sopc_client_helper_config.configuredReverseEndpointsToCfgIdx[i];
        rEPcfgIdxNoOffset = SOPC_ClientInternal_GetReverseEPcfgIdxNoOffset(rEPcfgIdx);
        if (0 != rEPcfgIdx && sopc_client_helper_config.openedReverseEndpointsFromCfgIdx[rEPcfgIdxNoOffset])
        {
            SOPC_ToolkitClient_AsyncCloseReverseEndpoint(
                sopc_client_helper_config.configuredReverseEndpointsToCfgIdx[i]);
        }
    }

    // Wait for all reverse endpoints to be closed
    if (pConfig->clientConfig.nbReverseEndpointURLs > 0)
    {
        while (!SOPC_Internal_AllReverseEPsClosed(pConfig))
        {
            mutStatus = Mutex_UnlockAndWaitCond(&sopc_client_helper_config.reverseEPsClosedCond,
                                                &sopc_client_helper_config.configMutex);
            SOPC_ASSERT(SOPC_STATUS_OK == mutStatus);
        }
    }

    mutStatus = Mutex_Unlock(&sopc_client_helper_config.configMutex);
    SOPC_ASSERT(SOPC_STATUS_OK == mutStatus);

    // Inhibition of client events (avoid possible lock attempt on config mutex by callbacks)
    SOPC_ReturnStatus status = SOPC_CommonHelper_SetClientComEvent(NULL);
    SOPC_ASSERT(SOPC_STATUS_OK == status);

    // Close open connections
    SOPC_ToolkitClient_ClearAllSCs();

    mutStatus = Mutex_Lock(&sopc_client_helper_config.configMutex);
    SOPC_ASSERT(SOPC_STATUS_OK == mutStatus);

    SOPC_ClientConfig_Clear(&pConfig->clientConfig);

    mutStatus = Mutex_Unlock(&sopc_client_helper_config.configMutex);
    SOPC_ASSERT(SOPC_STATUS_OK == mutStatus);
    mutStatus = Condition_Clear(&sopc_client_helper_config.reverseEPsClosedCond);
    SOPC_ASSERT(SOPC_STATUS_OK == mutStatus);
    mutStatus = Mutex_Clear(&sopc_client_helper_config.configMutex);
    SOPC_ASSERT(SOPC_STATUS_OK == mutStatus);
    SOPC_Atomic_Int_Set(&sopc_client_helper_config.initialized, (int32_t) false);

    return;
}

static SOPC_ReturnStatus SOPC_HelperConfigClient_MayFinalize_ClientConfigFromPaths(SOPC_Client_Config* cConfig)
{
    SOPC_ASSERT(NULL != cConfig);

    SOPC_ReturnStatus status = SOPC_STATUS_NOK;
    if (cConfig->isConfigFromPathsNeeded)
    {
        SOPC_Client_ConfigFromPaths* configFromPaths = cConfig->configFromPaths;
        SOPC_ASSERT(NULL != configFromPaths);

        SOPC_PKIProvider* pki = NULL;
        SOPC_SerializedCertificate* cliCert = NULL;
        SOPC_SerializedAsymmetricKey* cliKey = NULL;

        if (NULL == cConfig->clientPKI && NULL != configFromPaths->trustedRootIssuersList)
        {
            // Configure certificates / PKI / key from paths
            status = SOPC_PKIProviderStack_CreateFromPaths(
                configFromPaths->trustedRootIssuersList, configFromPaths->trustedIntermediateIssuersList,
                configFromPaths->untrustedRootIssuersList, configFromPaths->untrustedIntermediateIssuersList,
                configFromPaths->issuedCertificatesList, configFromPaths->certificateRevocationPathList, &pki);
            if (SOPC_STATUS_OK != status)
            {
                SOPC_Logger_TraceError(SOPC_LOG_MODULE_CLIENTSERVER, "Failed to create client config PKI from paths.");
            }
        }
        else
        {
            if (NULL != configFromPaths->trustedRootIssuersList)
            {
                SOPC_Logger_TraceWarning(SOPC_LOG_MODULE_CLIENTSERVER,
                                         "Client config PKI from paths ignored since a PKI is already instantiated.");
            }
            status = SOPC_STATUS_OK;
        }

        if (SOPC_STATUS_OK == status)
        {
            if (NULL == cConfig->clientCertificate && NULL != configFromPaths->clientCertPath)
            {
                status =
                    SOPC_KeyManager_SerializedCertificate_CreateFromFile(configFromPaths->clientCertPath, &cliCert);
                if (SOPC_STATUS_OK != status)
                {
                    SOPC_Logger_TraceError(SOPC_LOG_MODULE_CLIENTSERVER,
                                           "Failed to load client certificate from path.");
                }
            }
            else if (NULL != configFromPaths->clientCertPath)
            {
                SOPC_Logger_TraceWarning(
                    SOPC_LOG_MODULE_CLIENTSERVER,
                    "Client certificate config from path ignored since a certificate is already instantiated.");
            }
        }
        if (SOPC_STATUS_OK == status)
        {
            if (NULL == cConfig->clientKey && NULL != configFromPaths->clientKeyPath)
            {
                char* password = NULL;
                size_t lenPassword = 0;
                bool clientKeyEncrypted = SOPC_ClientInternal_IsEncryptedClientKey();
                if (clientKeyEncrypted)
                {
                    bool res = SOPC_ClientInternal_GetClientKeyPassword(&password);
                    if (!res)
                    {
                        SOPC_Logger_TraceError(
                            SOPC_LOG_MODULE_CLIENTSERVER,
                            "Failed to retrieve the password of the client's private key from callback.");
                        status = SOPC_STATUS_NOK;
                    }
                }

                if (SOPC_STATUS_OK == status && NULL != password)
                {
                    lenPassword = strlen(password);
                    if (UINT32_MAX < lenPassword)
                    {
                        status = SOPC_STATUS_NOK;
                    }
                }

                if (SOPC_STATUS_OK == status)
                {
                    status = SOPC_KeyManager_SerializedAsymmetricKey_CreateFromFile_WithPwd(
                        configFromPaths->clientKeyPath, &cliKey, password, (uint32_t) lenPassword);
                    if (SOPC_STATUS_OK != status)
                    {
                        SOPC_Logger_TraceError(
                            SOPC_LOG_MODULE_CLIENTSERVER,
                            "Failed to load client private key from path. Please check the password if the key "
                            "is encrypted and check the key format (PEM)");
                    }
                }

                if (NULL != password)
                {
                    SOPC_Free(password);
                }
            }
            else if (NULL != configFromPaths->clientKeyPath)
            {
                SOPC_Logger_TraceWarning(SOPC_LOG_MODULE_CLIENTSERVER,
                                         "Client key config from path ignored since a key is already instantiated.");
            }
        }

        if (SOPC_STATUS_OK == status)
        {
            cConfig->clientPKI = (NULL != pki ? pki : cConfig->clientPKI);
            cConfig->clientCertificate = (NULL != cliCert ? cliCert : cConfig->clientCertificate);
            cConfig->clientKey = (NULL != cliKey ? cliKey : cConfig->clientKey);
            cConfig->isConfigFromPathsNeeded = false;
        }
        else
        {
            SOPC_PKIProvider_Free(&pki);
            SOPC_KeyManager_SerializedCertificate_Delete(cliCert);
            SOPC_KeyManager_SerializedAsymmetricKey_Delete(cliKey);
        }
    }
    else
    {
        status = SOPC_STATUS_OK;
    }
    if (NULL == cConfig->clientPKI)
    {
        SOPC_Logger_TraceWarning(SOPC_LOG_MODULE_CLIENTSERVER, "No client PKI configured");
    }
    if (NULL == cConfig->clientCertificate || NULL == cConfig->clientKey)
    {
        SOPC_Logger_TraceWarning(SOPC_LOG_MODULE_CLIENTSERVER, "No client certificate/key configured");
    }
    return status;
}

SOPC_ReturnStatus SOPC_HelperConfigClient_Finalize_SecureConnectionConfig(SOPC_Client_Config* cConfig,
                                                                          SOPC_SecureConnection_Config* secConnConfig)
{
    SOPC_ASSERT(NULL != cConfig);
    SOPC_ASSERT(NULL != secConnConfig);
    SOPC_ASSERT(secConnConfig == cConfig->secureConnections[secConnConfig->secureConnectionIdx]);
    SOPC_SecureChannel_Config* scConfig = (SOPC_SecureChannel_Config*) &secConnConfig->scConfig;
    SOPC_ASSERT(NULL != scConfig);
    SOPC_ASSERT(scConfig->clientConfigPtr == cConfig);

    if (secConnConfig->finalized)
    {
        // Configuration already done
        return SOPC_STATUS_INVALID_STATE;
    }

    SOPC_ReturnStatus status = SOPC_HelperConfigClient_MayFinalize_ClientConfigFromPaths(cConfig);
    if (SOPC_STATUS_OK == status && secConnConfig->isServerCertFromPathNeeded)
    {
        SOPC_SerializedCertificate* srvCert = NULL;
        if (NULL != secConnConfig->serverCertPath)
        {
            status = SOPC_KeyManager_SerializedCertificate_CreateFromFile(secConnConfig->serverCertPath, &srvCert);
            if (SOPC_STATUS_OK == status)
            {
                scConfig->peerAppCert = srvCert;
            }
            else
            {
                SOPC_Logger_TraceError(SOPC_LOG_MODULE_CLIENTSERVER,
                                       "Connection[%" PRIu16 "]: Failed to load server certificate.",
                                       secConnConfig->secureConnectionIdx);
            }
        }
        else
        {
            status = SOPC_STATUS_INVALID_PARAMETERS;
        }
    }

    OpcUa_UserTokenType sessionTokenType = secConnConfig->sessionConfig.userTokenType;

    if (SOPC_STATUS_OK == status && OpcUa_UserTokenType_UserName == sessionTokenType &&
        NULL == secConnConfig->sessionConfig.userToken.userName.userPwd)
    {
        bool res = SOPC_ClientInternal_GetUserNamePassword(secConnConfig->sessionConfig.userToken.userName.userName,
                                                           &secConnConfig->sessionConfig.userToken.userName.userPwd);
        if (!res)
        {
            status = SOPC_STATUS_INVALID_PARAMETERS;
        }
    }

    return status;
}

SOPC_SecureConnection_Config* SOPC_HelperConfigClient_GetConfigFromId(const char* userDefinedId)
{
    if (!SOPC_ClientInternal_IsInitialized())
    {
        // Client wrapper not initialized
        return NULL;
    }
    SOPC_S2OPC_Config* pConfig = SOPC_CommonHelper_GetConfiguration();
    SOPC_SecureConnection_Config* res = NULL;
    for (uint16_t i = 0; NULL == res && i < pConfig->clientConfig.nbSecureConnections; i++)
    {
        SOPC_SecureConnection_Config* tmp = pConfig->clientConfig.secureConnections[i];
        if (NULL != tmp->userDefinedId && 0 == strcmp(tmp->userDefinedId, userDefinedId))
        {
            res = tmp;
        }
    }
    return res;
}

SOPC_ReturnStatus SOPC_HelperConfigClient_SetServiceAsyncResponse(SOPC_ServiceAsyncResp_Fct* asyncRespCb)
{
    if (NULL == asyncRespCb)
    {
        return SOPC_STATUS_INVALID_PARAMETERS;
    }
    if (!SOPC_ClientInternal_IsInitialized())
    {
        // Client wrapper not initialized
        return SOPC_STATUS_INVALID_STATE;
    }
    SOPC_ReturnStatus status = SOPC_STATUS_OK;
    SOPC_ReturnStatus mutStatus = Mutex_Lock(&sopc_client_helper_config.configMutex);
    SOPC_ASSERT(SOPC_STATUS_OK == mutStatus);

    if (NULL == sopc_client_helper_config.asyncRespCb)
    {
        sopc_client_helper_config.asyncRespCb = asyncRespCb;
    }
    else
    {
        status = SOPC_STATUS_INVALID_STATE;
    }

    mutStatus = Mutex_Unlock(&sopc_client_helper_config.configMutex);
    SOPC_ASSERT(SOPC_STATUS_OK == mutStatus);

    return status;
}

static SOPC_ReturnStatus SetPasswordCallback(SOPC_GetPassword_Fct** destCb, SOPC_GetPassword_Fct* getKeyPassword)
{
    SOPC_ASSERT(NULL != destCb);
    // TODO: uncomment when only new API available
    /*
    if (!SOPC_ClientInternal_IsInitialized())
    {
        // Client wrapper not initialized
        return SOPC_STATUS_INVALID_STATE;
    }
    */
    if (NULL == getKeyPassword)
    {
        return SOPC_STATUS_INVALID_PARAMETERS;
    }
    *destCb = getKeyPassword;
    return SOPC_STATUS_OK;
}

static SOPC_ReturnStatus SetUserPasswordCallback(SOPC_GetClientUserPassword_Fct** destCb,
                                                 SOPC_GetClientUserPassword_Fct* getUserPassword)
{
    SOPC_ASSERT(NULL != destCb);
    // TODO: uncomment when only new API available
    /*
    if (!SOPC_ClientInternal_IsInitialized())
    {
        // Client wrapper not initialized
        return SOPC_STATUS_INVALID_STATE;
    }
    */
    if (NULL == getUserPassword)
    {
        return SOPC_STATUS_INVALID_PARAMETERS;
    }
    *destCb = getUserPassword;
    return SOPC_STATUS_OK;
}

SOPC_ReturnStatus SOPC_HelperConfigClient_SetClientKeyPasswordCallback(SOPC_GetPassword_Fct* getClientKeyPassword)
{
    return SetPasswordCallback(&sopc_client_helper_config.getClientKeyPasswordCb, getClientKeyPassword);
}

SOPC_ReturnStatus SOPC_HelperConfigClient_SetUsernamePasswordCallback(
    SOPC_GetClientUserPassword_Fct* getClientUsernamePassword)
{
    return SetUserPasswordCallback(&sopc_client_helper_config.getUserNamePasswordCb, getClientUsernamePassword);
}

SOPC_ReturnStatus SOPC_HelperConfigClient_SetX509userPasswordCallback(
    SOPC_GetClientUserPassword_Fct* getClientX509userKeyPassword)
{
    return SetUserPasswordCallback(&sopc_client_helper_config.getUserKeyPasswordCb, getClientX509userKeyPassword);
}

static bool SOPC_ClientInternal_GetPassword(SOPC_GetPassword_Fct* passwordCb, const char* cbName, char** outPassword)
{
    // TODO: uncomment when only new API available
    /*
    if (!SOPC_ClientInternal_IsInitialized())
    {
        // Client wrapper not initialized
        return SOPC_STATUS_INVALID_STATE;
    }
    */
    if (NULL == outPassword)
    {
        return false;
    }
    if (NULL == passwordCb)
    {
        SOPC_Logger_TraceError(SOPC_LOG_MODULE_CLIENTSERVER, "The following callback isn't configured: %s", cbName);
        return false;
    }
    return passwordCb(outPassword);
}

static bool SOPC_ClientInternal_GetUserPassword(SOPC_GetClientUserPassword_Fct* userPasswordCb,
                                                const char* cbName,
                                                const char* userId,
                                                char** outPassword)
{
    // TODO: uncomment when only new API available
    /*
    if (!SOPC_ClientInternal_IsInitialized())
    {
        // Client wrapper not initialized
        return SOPC_STATUS_INVALID_STATE;
    }
    */
    if (NULL == outPassword)
    {
        return false;
    }
    if (NULL == userPasswordCb)
    {
        SOPC_Logger_TraceError(SOPC_LOG_MODULE_CLIENTSERVER, "The following callback isn't configured: %s", cbName);
        return false;
    }
    return userPasswordCb(userId, outPassword);
}

// Get password to decrypt user private key from internal callback
bool SOPC_ClientInternal_GetClientKeyPassword(char** outPassword)
{
    return SOPC_ClientInternal_GetPassword(sopc_client_helper_config.getClientKeyPasswordCb,
                                           "ClientKeyPasswordCallback", outPassword);
}

// Get password to decrypt user private key from internal callback
bool SOPC_ClientInternal_GetUserKeyPassword(const char* certSha1, char** outPassword)
{
    return SOPC_ClientInternal_GetUserPassword(sopc_client_helper_config.getUserKeyPasswordCb,
                                               "UserKeyPasswordCallback", certSha1, outPassword);
}

// Get password associated to username from internal callback
bool SOPC_ClientInternal_GetUserNamePassword(const char* username, char** outPassword)
{
    return SOPC_ClientInternal_GetUserPassword(sopc_client_helper_config.getUserNamePasswordCb,
                                               "UserNamePasswordCallback", username, outPassword);
}

bool SOPC_ClientInternal_IsEncryptedClientKey(void)
{
    return NULL != sopc_client_helper_config.getClientKeyPasswordCb;
}

uint32_t SOPC_ClientInternal_GetReverseEPcfgIdxNoOffset(SOPC_ReverseEndpointConfigIdx rEPcfgIdx)
{
    if (rEPcfgIdx > SOPC_MAX_ENDPOINT_DESCRIPTION_CONFIGURATIONS &&
        rEPcfgIdx <= 2 * SOPC_MAX_ENDPOINT_DESCRIPTION_CONFIGURATIONS)
    {
        return (rEPcfgIdx - SOPC_MAX_ENDPOINT_DESCRIPTION_CONFIGURATIONS);
    }
    return 0;
}
