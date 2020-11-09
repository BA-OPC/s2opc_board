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

// WARNING: this source file is only included if the XML library (Expat) is available

#include <stdio.h>

#include "libs2opc_server_config.h"
#include "libs2opc_server_internal.h"

#include "sopc_logger.h"
#include "sopc_mem_alloc.h"
#include "sopc_pki_stack.h"
#include "sopc_toolkit_config.h"

#include "xml_expat/sopc_config_loader.h"
#include "xml_expat/sopc_uanodeset_loader.h"
#include "xml_expat/sopc_users_loader.h"

static FILE* SOPC_HelperInternal_OpenFileFromPath(const char* filename)
{
    FILE* fd = fopen(filename, "r");

    if (fd == NULL)
    {
        SOPC_Logger_TraceError(SOPC_LOG_MODULE_CLIENTSERVER,
                               "Configuration file %s cannot be opened. Please check path.\n", filename);
    }

    return fd;
}

static bool SOPC_HelperInternal_CreatePKIfromPaths(void)
{
    SOPC_Server_Config* serverConfig = &sopc_helper_config.config.serverConfig;
    /* Create the PKI (Public Key Infrastructure) provider */
    SOPC_ReturnStatus status = SOPC_PKIProviderStack_CreateFromPaths(
        serverConfig->trustedRootIssuersList, serverConfig->trustedIntermediateIssuersList,
        serverConfig->untrustedRootIssuersList, serverConfig->untrustedIntermediateIssuersList,
        serverConfig->issuedCertificatesList, serverConfig->certificateRevocationPathList, &serverConfig->pki);
    if (SOPC_STATUS_OK != status)
    {
        SOPC_Logger_TraceError(
            SOPC_LOG_MODULE_CLIENTSERVER,
            "Failed to instantiate PKI provider from the list of certificate paths. Please check configuration file "
            "contains only valid file paths to X509 certificate at DER format.");
        return false;
    }
    return true;
}

static bool SOPC_HelperInternal_LoadCertsFromPaths(void)
{
    SOPC_Server_Config* serverConfig = &sopc_helper_config.config.serverConfig;
    SOPC_ReturnStatus status = SOPC_KeyManager_SerializedCertificate_CreateFromFile(serverConfig->serverCertPath,
                                                                                    &serverConfig->serverCertificate);
    bool res = true;
    if (SOPC_STATUS_OK != status)
    {
        SOPC_Logger_TraceError(
            SOPC_LOG_MODULE_CLIENTSERVER,
            "Failed to load server certificate file %s. Please check it is a X509 certificate at DER format.",
            serverConfig->serverCertPath);
        res = false;
    }
    status =
        SOPC_KeyManager_SerializedAsymmetricKey_CreateFromFile(serverConfig->serverKeyPath, &serverConfig->serverKey);
    if (SOPC_STATUS_OK != status)
    {
        SOPC_Logger_TraceError(
            SOPC_LOG_MODULE_CLIENTSERVER,
            "Failed to load server private key file %s. Please check it is a private key at DER or PEM format.",
            serverConfig->serverKeyPath);
        res = false;
    }
    return res;
}

static bool SOPC_HelperInternal_LoadServerConfigFromFile(const char* filename)
{
    FILE* fd = SOPC_HelperInternal_OpenFileFromPath(filename);
    if (NULL == fd)
    {
        return false;
    }
    bool res = SOPC_Config_Parse(fd, &sopc_helper_config.config);
    fclose(fd);

    if (!res)
    {
        SOPC_Logger_TraceError(SOPC_LOG_MODULE_CLIENTSERVER,
                               "Error parsing configuration file %s. Please check logged errors.\n", filename);
        return false;
    }

    res = SOPC_HelperInternal_CreatePKIfromPaths();

    res &= SOPC_HelperInternal_LoadCertsFromPaths();

    return res;
}

static bool SOPC_HelperInternal_LoadAddressSpaceConfigFromFile(const char* filename)
{
    FILE* fd = SOPC_HelperInternal_OpenFileFromPath(filename);
    if (NULL == fd)
    {
        return false;
    }
    SOPC_AddressSpace* space = SOPC_UANodeSet_Parse(fd);
    fclose(fd);

    if (space == NULL)
    {
        SOPC_Logger_TraceError(SOPC_LOG_MODULE_CLIENTSERVER,
                               "Error parsing configuration file %s. Please check logged errors.\n", filename);
        return false;
    }

    SOPC_ReturnStatus status = SOPC_ToolkitServer_SetAddressSpaceConfig(space);
    if (SOPC_STATUS_OK != status)
    {
        SOPC_Logger_TraceError(SOPC_LOG_MODULE_CLIENTSERVER,
                               "Error loading address space configuration parsed from %s. Error: %d\n", filename,
                               status);
        SOPC_AddressSpace_Delete(space);
        return false;
    }
    // Keep address space instance reference for deallocation
    sopc_helper_config.server.addressSpace = space;

    return true;
}

static bool SOPC_HelperInternal_LoadUsersConfigFromFile(const char* filename)
{
    FILE* fd = SOPC_HelperInternal_OpenFileFromPath(filename);
    if (NULL == fd)
    {
        return false;
    }
    bool res = SOPC_UsersConfig_Parse(fd, &sopc_helper_config.server.authenticationManager,
                                      &sopc_helper_config.server.authorizationManager);
    fclose(fd);

    if (!res)
    {
        SOPC_Logger_TraceError(SOPC_LOG_MODULE_CLIENTSERVER,
                               "Error parsing configuration file %s. Please check logged errors.\n", filename);
    }

    return res;
}

SOPC_ReturnStatus SOPC_HelperConfigServer_ConfigureFromXML(const char* serverConfigPath,
                                                           const char* addressSpaceConfigPath,
                                                           const char* userConfigPath,
                                                           SOPC_ConfigServerXML_Custom* customConfig)
{
    // Avoid compiler warning on unused parameter, reserved for future use
    (void) customConfig;

    if (!SOPC_HelperConfig_IsInitAndUnlock())
    {
        return SOPC_STATUS_INVALID_STATE;
    }
    if (NULL == serverConfigPath && NULL == addressSpaceConfigPath && NULL == userConfigPath)
    {
        return SOPC_STATUS_INVALID_PARAMETERS;
    }

    bool res = true;
    /* Server XML config */
    if (NULL != serverConfigPath)
    {
        res &= SOPC_HelperInternal_LoadServerConfigFromFile(serverConfigPath);
        // "Transfer" endpoints from low level S2OPC server config to high level one
        // Note: in the future we should modify low level representation instead
        for (uint8_t i = 0; i < sopc_helper_config.config.serverConfig.nbEndpoints; i++)
        {
            SOPC_Endpoint_Config* ep = &sopc_helper_config.config.serverConfig.endpoints[i];
            sopc_helper_config.server.endpoints[i] = SOPC_Calloc(1, sizeof(SOPC_Endpoint_Config));
            if (NULL != sopc_helper_config.server.endpoints[i])
            {
                *sopc_helper_config.server.endpoints[i] = *ep;
                sopc_helper_config.server.nbEndpoints++;
            }
            else
            {
                // Clear in case of failure to clear low level config
                SOPC_HelperInternal_ClearEndpoint(ep);
                res = false;
            }
        }
        SOPC_Free(sopc_helper_config.config.serverConfig.endpoints);
        sopc_helper_config.config.serverConfig.endpoints = NULL;
        sopc_helper_config.config.serverConfig.nbEndpoints = 0;
    }
    /* AddressSpace XML config */
    if (NULL != addressSpaceConfigPath)
    {
        res &= SOPC_HelperInternal_LoadAddressSpaceConfigFromFile(addressSpaceConfigPath);
    }
    /* Users XML config */
    if (NULL != userConfigPath)
    {
        res &= SOPC_HelperInternal_LoadUsersConfigFromFile(userConfigPath);
    }

    if (!res)
    {
        return SOPC_STATUS_INVALID_PARAMETERS;
    }

    return SOPC_STATUS_OK;
}
