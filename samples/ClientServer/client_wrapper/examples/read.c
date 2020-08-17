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
 * \brief A read example using the high-level client API
 *
 * Requires the toolkit_test_server to be running.
 * Connect to the server and reads a UInt64 value in a predefined node.
 * Then disconnect and closes the toolkit.
 *
 */

#include <assert.h>
#include <inttypes.h>
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
    SOPC_ClientHelper_Initialize("./s2opc_wrapper_read_logs/", SOPC_LOG_LEVEL_DEBUG, disconnect_callback);

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
    char* node_id = "ns=1;i=1012";

    /* connect to the endpoint */
    int32_t configurationId = SOPC_ClientHelper_CreateConfiguration(endpoint_url, &security);
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
        SOPC_ClientHelper_ReadValue readValue;

        /* initalize read value structure */
        readValue.nodeId = node_id;
        readValue.attributeId = 13; // value
        readValue.indexRange = NULL;

        SOPC_DataValue* readDataValue = NULL;

        /* read the node id value */
        res = SOPC_ClientHelper_Read(connectionId, &readValue, 1, &readDataValue);

        if (0 == res)
        {
            if (NULL == readDataValue)
            {
                printf("NULL\n");
            }
            else
            {
                SOPC_Variant variant = readDataValue->Value;
                if (SOPC_UInt64_Id == variant.BuiltInTypeId)
                {
                    printf("NodeId:\"%s\" - Value: %" PRIu64 "\n", node_id, variant.Value.Uint64);
                }
            }
            free(readDataValue);
        }
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
