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
 * \brief A browse example using the high-level client API
 *
 * Requires the toolkit_test_server to be running.
 * Connect to the server and browse the "/Root/Objects" node.
 * Then disconnect and closes the toolkit.
 *
 */

#include <assert.h>
#include <stdio.h>

#include "libs2opc_client_cmds.h"

static void disconnect_callback(const uint32_t c_id)
{
    printf("===> connection #%d has been terminated!\n", c_id);
}

int main(int argc, char* const argv[])
{
    (void) (argc);
    (void) (argv);

    int res = 0;

    /* Initialize the toolkit */
    SOPC_ClientHelper_Initialize("./s2opc_wrapper_browse_logs/", SOPC_TOOLKIT_LOG_LEVEL_DEBUG, disconnect_callback);

    SOPC_ClientHelper_Security security = {
        .security_policy = SOPC_SecurityPolicy_None_URI,
        .security_mode = OpcUa_MessageSecurityMode_None,
        .path_cert_auth = "./trusted/cacert.der",
        .path_crl = "./revoked/cacrl.der",
        .path_cert_srv = "./server_public/server_2k_cert.der",
        .path_cert_cli = "./client_public/client_2k_cert.der",
        .path_key_cli = "./client_private/client_2k_key.pem",
        .policyId = "anonymous",
        .username = NULL,
        .password = NULL,
    };

    const char* endpoint_url = "opc.tcp://localhost:4841";

    /* connect to the endpoint */
    int32_t configurationId = SOPC_ClientHelper_CreateConfiguration(endpoint_url, security);
    if (configurationId <= 0)
    {
        res = -1;
    }

    int32_t connectionId = 0;
    if (0 == res)
    {
        connectionId = SOPC_ClientHelper_CreateConnection(configurationId);

        if (connectionId <= 0)
        {
            /* connectionId is invalid */
            res = -1;
        }
    }

    if (0 == res)
    {
        SOPC_ClientHelper_BrowseRequest browseRequest;
        SOPC_ClientHelper_BrowseResult browseResult;

        browseRequest.nodeId = "ns=0;i=85"; // Root/Objects/
        browseRequest.direction = 0;        // forward
        browseRequest.referenceTypeId = ""; // all reference types
        browseRequest.includeSubtypes = true;

        /* Browse specified node */
        res = SOPC_ClientHelper_Browse(connectionId, &browseRequest, 1, &browseResult);

        printf("status: %d, nbOfResults: %d\n", browseResult.statusCode, browseResult.nbOfReferences);
        for (int32_t i = 0; i < browseResult.nbOfReferences; i++)
        {
            printf("Item #%d\n", i);
            printf("- nodeId: %s\n", browseResult.references[i].nodeId);
            printf("- displayName: %s\n", browseResult.references[i].displayName);

            free(browseResult.references[i].nodeId);
            free(browseResult.references[i].displayName);
            free(browseResult.references[i].browseName);
            free(browseResult.references[i].referenceTypeId);
        }
        free(browseResult.references);
    }

    if (connectionId > 0)
    {
        int32_t discoRes = SOPC_ClientHelper_Disconnect(connectionId);
        res = res != 0 ? res : discoRes;
    }

    /* Close the toolkit */
    SOPC_ClientHelper_Finalize();

    return res;
}
