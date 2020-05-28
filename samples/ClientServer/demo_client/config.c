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

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "sopc_mem_alloc.h"
#include "sopc_pki_stack.h"

#include "config.h"

char* ENDPOINT_URL = "opc.tcp://localhost:4841";
uint32_t SC_LIFETIME = 60000;

char* PATH_CLIENT_PUBL = "./client_public/client_4k_cert.der";
char* PATH_CLIENT_PRIV = "./client_private/client_4k_key.pem";
char* PATH_SERVER_PUBL = "./server_public/server_4k_cert.der";
char* PATH_CACERT_PUBL = "./trusted/cacert.der";
char* PATH_CACRL = "./revoked/cacrl.der";

char* USER_POLICY_ID = "user";
char* USER_NAME = NULL;
char* USER_PWD = NULL;

struct argparse_option CONN_OPTIONS[11] = {
    OPT_GROUP("Connection options"),
    OPT_STRING('e',
               "endpointURL",
               &ENDPOINT_URL,
               "(default: opc.tcp://localhost:4841) endpoint URL in format: opc.tcp://<ip>:<port>[/<name>]",
               NULL,
               0,
               0),

    OPT_INTEGER(0,
                "scLifetime",
                &SC_LIFETIME,
                "(default: 60000 ms) secure channel lifetime (symmetric key renewal)",
                NULL,
                0,
                0),
    OPT_STRING(0,
               "client_cert",
               &PATH_CLIENT_PUBL,
               "(default: ./client_public/client_4k_cert.der) path to the client certificate to use (public key)",
               NULL,
               0,
               0),
    OPT_STRING(0,
               "client_key",
               &PATH_CLIENT_PRIV,
               "(default: ./client_private/client_4k_key.pem) path to the client private key to use",
               NULL,
               0,
               0),
    OPT_STRING(0,
               "server_cert",
               &PATH_SERVER_PUBL,
               "(default: ./server_public/server_4k_cert.der) path to the server certificate to use",
               NULL,
               0,
               0),
    OPT_STRING(0,
               "ca",
               &PATH_CACERT_PUBL,
               "(default: ./trusted/cacert.der) path to the certificate authority (CA)",
               NULL,
               0,
               0),
    OPT_STRING(0,
               "crl",
               &PATH_CACRL,
               "(default: ./revoked/cacrl.der) path to the certificate authority revocation list (CRL)",
               NULL,
               0,
               0),
    OPT_STRING(0,
               "user_policy_id",
               &USER_POLICY_ID,
               "(default: 'user') user policy id used to establish session",
               NULL,
               0,
               0),
    OPT_STRING('u',
               "username",
               &USER_NAME,
               "(if not set anonymous mode is active) the username of the user used to establish session",
               NULL,
               0,
               0),
    OPT_STRING('p',
               "password",
               &USER_PWD,
               "(if not set anonymous mode is active) the username of the user used to establish session",
               NULL,
               0,
               0)};

/* Only supports one set of certificates at a time. They are all shared by the configs. */
int nCfgCreated = 0; /* Number of created configs with certificates, to remember when to release certificates */
SOPC_SerializedCertificate* pCrtCli = NULL;
SOPC_SerializedCertificate* pCrtSrv = NULL;
SOPC_SerializedAsymmetricKey* pKeyCli = NULL;
SOPC_PKIProvider* pPki = NULL;

SOPC_ReturnStatus Config_LoadCertificates(void);

SOPC_SecureChannel_Config* Config_NewSCConfig(const char* reqSecuPolicyUri, OpcUa_MessageSecurityMode msgSecurityMode)
{
    SOPC_ReturnStatus status = SOPC_STATUS_OK;
    SOPC_SecureChannel_Config* pscConfig = NULL;
    bool bInconsistentPolicyMode = false;

    /* Check that SecuPolicy None <=> SecuMode None */
    bInconsistentPolicyMode =
        strncmp(reqSecuPolicyUri, SOPC_SecurityPolicy_None_URI, strlen(SOPC_SecurityPolicy_None_URI) + 1) == 0;
    bInconsistentPolicyMode ^= OpcUa_MessageSecurityMode_None == msgSecurityMode;
    if (bInconsistentPolicyMode)
    {
        printf(
            "# Error: inconsistent security mode, message security mode may be None if and only if security policy is "
            "None.\n");
        status = SOPC_STATUS_NOK;
    }

    /* Try to load the certificates before the creation of the config */
    if (SOPC_STATUS_OK == status && OpcUa_MessageSecurityMode_None != msgSecurityMode)
    {
        status = Config_LoadCertificates();
    }

    /* Create the configuration */
    if (SOPC_STATUS_OK == status)
    {
        pscConfig = SOPC_Malloc(sizeof(SOPC_SecureChannel_Config));

        if (NULL != pscConfig)
        {
            pscConfig->isClientSc = true;
            pscConfig->url = ENDPOINT_URL;
            pscConfig->crt_cli = NULL;
            pscConfig->key_priv_cli = NULL;
            pscConfig->crt_srv = NULL;
            pscConfig->pki = pPki;
            pscConfig->requestedLifetime = SC_LIFETIME;
            pscConfig->reqSecuPolicyUri = reqSecuPolicyUri;
            pscConfig->msgSecurityMode = msgSecurityMode;

            if (OpcUa_MessageSecurityMode_None != msgSecurityMode)
            {
                pscConfig->crt_cli = pCrtCli;
                pscConfig->crt_srv = pCrtSrv;
                pscConfig->key_priv_cli = pKeyCli;
            }
        }
    }

    return pscConfig;
}

void Config_DeleteSCConfig(SOPC_SecureChannel_Config** ppscConfig)
{
    if (NULL == ppscConfig || NULL == *ppscConfig)
        return;

    if (NULL != (*ppscConfig)->crt_cli)
    {
        nCfgCreated -= 1;
    }

    SOPC_Free(*ppscConfig);
    *ppscConfig = NULL;

    /* Garbage collect, if needed */
    if (0 == nCfgCreated)
    {
        SOPC_KeyManager_SerializedCertificate_Delete(pCrtCli);
        SOPC_KeyManager_SerializedCertificate_Delete(pCrtSrv);
        SOPC_KeyManager_SerializedAsymmetricKey_Delete(pKeyCli);
        SOPC_PKIProvider_Free(&pPki);
        pCrtCli = NULL;
        pCrtSrv = NULL;
        pKeyCli = NULL;
        pPki = NULL;
    }
}

SOPC_ReturnStatus Config_LoadCertificates(void)
{
    SOPC_ReturnStatus status = SOPC_STATUS_OK;

    if (0 == nCfgCreated)
    {
        status = SOPC_KeyManager_SerializedCertificate_CreateFromFile(PATH_CLIENT_PUBL, &pCrtCli);
        if (SOPC_STATUS_OK != status)
        {
            printf("# Error: Failed to load client certificate\n");
        }

        if (SOPC_STATUS_OK == status)
        {
            status = SOPC_KeyManager_SerializedCertificate_CreateFromFile(PATH_SERVER_PUBL, &pCrtSrv);
            if (SOPC_STATUS_OK != status)
            {
                printf("# Error: Failed to load server certificate\n");
            }
        }

        if (SOPC_STATUS_OK == status)
        {
            status = SOPC_KeyManager_SerializedAsymmetricKey_CreateFromFile(PATH_CLIENT_PRIV, &pKeyCli);
            if (SOPC_STATUS_OK != status)
            {
                printf("# Error: Failed to load client private key\n");
            }
        }

        if (SOPC_STATUS_OK == status)
        {
            char* lPathsTrustedRoots[] = {PATH_CACERT_PUBL, NULL};
            char* lPathsTrustedLinks[] = {NULL};
            char* lPathsUntrustedRoots[] = {NULL};
            char* lPathsUntrustedLinks[] = {NULL};
            char* lPathsIssuedCerts[] = {NULL};
            char* lPathsCRL[] = {PATH_CACRL, NULL};
            status = SOPC_PKIProviderStack_CreateFromPaths(lPathsTrustedRoots, lPathsTrustedLinks, lPathsUntrustedRoots,
                                                           lPathsUntrustedLinks, lPathsIssuedCerts, lPathsCRL, &pPki);
            if (SOPC_STATUS_OK != status)
            {
                printf("# Error: Failed to create PKI\n");
            }
        }
    }

    nCfgCreated += 1; /* If it failed once, do not try again */

    return status;
}
