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

#include "pubsub_config_static.h"

#include <assert.h>
#include <stdbool.h>
#include <string.h>

#include "samples_platform_dep.h"
#include "test_config.h"

// These nodeIds must exist in AddressSpace!
#define PUB_VAR_DOUBLE_TANK_LEVEL 	"ns=1;s=TankLevel"
#define PUB_VAR_BOOL_HI_WARN 		"ns=1;s=LevelAboveHigh"
#define PUB_VAR_BOOL_LO_WARN 		"ns=1;s=LevelUnderLow"
#define NB_PUB_VARS 3


#define PUBLISHER_ID 42
#define MESSAGE_ID 20
#define MESSAGE_VERSION 1

static SOPC_DataSetWriter* SOPC_PubSubConfig_SetPubMessageAt(SOPC_PubSubConnection* connection,
                                                             uint16_t index,
                                                             uint16_t messageId,
                                                             uint32_t version,
                                                             uint64_t interval,
                                                             SOPC_SecurityMode_Type securityMode)

{
    SOPC_WriterGroup* group = SOPC_PubSubConnection_Get_WriterGroup_At(connection, index);
    SOPC_WriterGroup_Set_Id(group, messageId);
    SOPC_WriterGroup_Set_Version(group, version);
    SOPC_WriterGroup_Set_PublishingInterval(group, (double) interval);
    SOPC_WriterGroup_Set_SecurityMode(group, securityMode);

    // Create one DataSet Writer
    SOPC_WriterGroup_Allocate_DataSetWriter_Array(group, 1);
    SOPC_DataSetWriter* writer = SOPC_WriterGroup_Get_DataSetWriter_At(group, 0);
    SOPC_DataSetWriter_Set_Id(writer, messageId);
    return writer;
}

static SOPC_PublishedDataSet* SOPC_PubSubConfig_InitDataSet(SOPC_PubSubConfiguration* config,
                                                            uint16_t dataSetIndex,
                                                            SOPC_DataSetWriter* writer,
                                                            uint16_t nbVar)
{
    SOPC_PublishedDataSet* dataset = SOPC_PubSubConfiguration_Get_PublishedDataSet_At(config, dataSetIndex);
    SOPC_PublishedDataSet_Init(dataset, SOPC_PublishedDataItemsDataType, nbVar);
    SOPC_DataSetWriter_Set_DataSet(writer, dataset);

    return dataset;
}

static void SOPC_PubSubConfig_SetPubVariableAt(SOPC_PublishedDataSet* dataset,
                                               uint16_t index,
                                               char* strNodeId,
                                               SOPC_BuiltinId builtinType)
{
    SOPC_FieldMetaData* fieldmetadata = SOPC_PublishedDataSet_Get_FieldMetaData_At(dataset, index);
    SOPC_FieldMetaData_Set_ValueRank(fieldmetadata, -1);
    SOPC_FieldMetaData_Set_BuiltinType(fieldmetadata, builtinType);
    SOPC_PublishedVariable* publishedVar = SOPC_FieldMetaData_Get_PublishedVariable(fieldmetadata);
    assert(NULL != publishedVar);
    SOPC_NodeId* nodeId = SOPC_NodeId_FromCString(strNodeId, (int32_t) strlen(strNodeId));
    assert(NULL != nodeId);
    SOPC_PublishedVariable_Set_NodeId(publishedVar, nodeId);
    SOPC_PublishedVariable_Set_AttributeId(publishedVar,
                                           13); // Value => AttributeId=13
}

SOPC_PubSubConfiguration* SOPC_PubSubConfig_GetStatic(void)
{
    bool alloc = true;
    SOPC_PubSubConfiguration* config = SOPC_PubSubConfiguration_Create();
    SOPC_PubSubConnection* connection;

    /* 1 connection pub */
    alloc = SOPC_PubSubConfiguration_Allocate_PubConnection_Array(config, 1);

    /** connection pub 0 **/

    if (alloc) {
        // Set publisher id and address
        connection = SOPC_PubSubConfiguration_Get_PubConnection_At(config, 0);
        SOPC_PubSubConnection_Set_PublisherId_UInteger(connection, PUBLISHER_ID);
        alloc = SOPC_PubSubConnection_Set_Address(connection, CONFIG_SOPC_PUBLISHER_ADDRESS);
    }

    if (alloc) {
        const char* itf_name = CONFIG_SOPC_PUBLISHER_ITF_NAME;
        if (CONFIG_SOPC_PUBLISHER_ITF_NAME[0] == '\0') {
            // Force default interface if not specified
            itf_name = SOPC_Platform_Get_Default_Net_Itf();
        }
        if (itf_name[0] != '\0') {
            alloc = SOPC_PubSubConnection_Set_InterfaceName(connection, itf_name);
        }
    }

    if (alloc) {
        // 2 pub messages
        alloc = SOPC_PubSubConnection_Allocate_WriterGroup_Array(connection, 1);
    }

    if (alloc) {
        // 2 published data sets
        alloc = SOPC_PubSubConfiguration_Allocate_PublishedDataSet_Array(config, 1);
    }

    /*** Pub Message ***/

    SOPC_DataSetWriter* writer = NULL;
    if (alloc)
    {
        writer = SOPC_PubSubConfig_SetPubMessageAt(
            connection, 0, MESSAGE_ID, MESSAGE_VERSION, CONFIG_SOPC_PUBLISHER_PERIOD_US / 1000, SOPC_SecurityMode_None
            // SOPC_SecurityMode_SignAndEncrypt
        );
        alloc = NULL != writer;
    }

    SOPC_PublishedDataSet* dataset = NULL;
    if (alloc)
    {
        dataset = SOPC_PubSubConfig_InitDataSet(config, 0, writer, NB_PUB_VARS);
        alloc = NULL != dataset;
    }
    if (alloc)
    {
        SOPC_PubSubConfig_SetPubVariableAt(dataset, 0, PUB_VAR_DOUBLE_TANK_LEVEL, SOPC_Double_Id);
        SOPC_PubSubConfig_SetPubVariableAt(dataset, 1, PUB_VAR_BOOL_HI_WARN, SOPC_Boolean_Id);
        SOPC_PubSubConfig_SetPubVariableAt(dataset, 2, PUB_VAR_BOOL_LO_WARN, SOPC_Boolean_Id);
    }

    return config;
}
