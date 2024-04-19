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

#include <stdbool.h>
#include <string.h>

#include "sopc_assert.h"
#include "samples_platform_dep.h"

// DO NOT EDIT THIS FILE HAS BEEN GENERATED BY generate-s2opc_pubsub-static-config.py



static SOPC_WriterGroup* SOPC_PubSubConfig_SetPubMessageAt(SOPC_PubSubConnection* connection,
                                                           uint16_t index,
                                                           uint16_t groupId,
                                                           uint32_t groupVersion,
                                                           double interval,
                                                           int32_t offsetUs,
                                                           SOPC_SecurityMode_Type securityMode,
                                                           const char* mqttTopic,
                                                           const SOPC_Pubsub_MessageEncodingType encoding,
                                                           const bool isFixedBufferSize)
{
    SOPC_WriterGroup* group = SOPC_PubSubConnection_Get_WriterGroup_At(connection, index);
    SOPC_WriterGroup_Set_Id(group, groupId);
    SOPC_WriterGroup_Set_Version(group, groupVersion);
    SOPC_WriterGroup_Set_PublishingInterval(group, interval);
    SOPC_WriterGroup_Set_SecurityMode(group, securityMode);
    SOPC_WriterGroup_Set_MqttTopic(group, mqttTopic);
    SOPC_WriterGroup_Set_Encoding(group, encoding);
    const SOPC_WriterGroup_Options writerGroupOptions = {.useFixedSizeBuffer = isFixedBufferSize};
    SOPC_WriterGroup_Set_Options(group, &writerGroupOptions);
    if (offsetUs >=0)
    {
        SOPC_WriterGroup_Set_PublishingOffset(group, offsetUs / 1000);
    }

    return group;
}



static SOPC_PublishedDataSet* SOPC_PubSubConfig_InitDataSet(SOPC_PubSubConfiguration* config,
                                                            uint16_t dataSetIndex,
                                                            SOPC_DataSetWriter* writer,
                                                            bool isAcyclic,
                                                            uint16_t dataSetId,
                                                            bool useSeqNum,
                                                            uint16_t nbVar)
{
    SOPC_PublishedDataSet* dataset = SOPC_PubSubConfiguration_Get_PublishedDataSet_At(config, dataSetIndex);
    if(isAcyclic)
    {
        SOPC_PublishedDataSet_Init(dataset, SOPC_PublishedDataSetCustomSourceDataType, nbVar);
    }
    else
    {
        SOPC_PublishedDataSet_Init(dataset, SOPC_PublishedDataItemsDataType, nbVar);
    }
    SOPC_DataSetWriter_Set_DataSet(writer, dataset);
    SOPC_DataSetWriter_Set_Id(writer, dataSetId);
    const SOPC_DataSetWriter_Options dsmOptions = {.noUseSeqNum = !useSeqNum};
    SOPC_DataSetWriter_Set_Options(writer, &dsmOptions);

    return dataset;
}


static void SOPC_PubSubConfig_SetPubVariableAt(SOPC_PublishedDataSet* dataset,
                                               uint16_t index,
                                               const char* strNodeId,
                                               SOPC_BuiltinId builtinType,
                                               int32_t valueRank,
                                               uint32_t* arrayDimensions)
{
    SOPC_FieldMetaData* fieldmetadata = SOPC_PublishedDataSet_Get_FieldMetaData_At(dataset, index);
    SOPC_PubSub_ArrayDimension arrayDimension = {.valueRank = valueRank, .arrayDimensions = arrayDimensions};
    SOPC_FiledMetaDeta_SetCopy_ArrayDimension(fieldmetadata, &arrayDimension);
    SOPC_FieldMetaData_Set_BuiltinType(fieldmetadata, builtinType);
    SOPC_PublishedVariable* publishedVar = SOPC_FieldMetaData_Get_PublishedVariable(fieldmetadata);
    SOPC_ASSERT(NULL != publishedVar);
    SOPC_NodeId* nodeId = SOPC_NodeId_FromCString(strNodeId, (int32_t) strlen(strNodeId));
    SOPC_ASSERT(NULL != nodeId);
    SOPC_PublishedVariable_Set_NodeId(publishedVar, nodeId);
    SOPC_PublishedVariable_Set_AttributeId(publishedVar,
                                           13); // Value => AttributeId=13
}


SOPC_PubSubConfiguration* SOPC_PubSubConfig_GetStatic(void)
{
    bool alloc = true;
    SOPC_PubSubConfiguration* config = SOPC_PubSubConfiguration_Create();
    
    SOPC_PubSubConnection* connection = NULL;

    /* 1 publisher connection */
    alloc = SOPC_PubSubConfiguration_Allocate_PubConnection_Array(config, 1);
    
    /* 2 Published Datasets */
    alloc = SOPC_PubSubConfiguration_Allocate_PublishedDataSet_Array(config, 2);
    
    /** Publisher connection 0 **/
    
    if (alloc)
    {
        // Set address
        connection = SOPC_PubSubConfiguration_Get_PubConnection_At(config, 0);
        SOPC_ASSERT(NULL != connection);
        alloc = SOPC_PubSubConnection_Set_Address(connection, "opc.udp://232.1.2.100:4840");
    }
    
        if (alloc)
        {
            // Set publisher id
            SOPC_PubSubConnection_Set_PublisherId_UInteger(connection, 42);
        }
        
    // Set acyclic publisher mode
    SOPC_PubSubConnection_Set_AcyclicPublisher(connection, 0);
    
    if (alloc)
    {

        const char* itf_name = "";
        if (itf_name[0] == '\0')
        {
            // Force default interface if not specifi/ed
            itf_name = SOPC_Platform_Get_Default_Net_Itf();
        }
        if (itf_name[0] != '\0')
        {
            alloc = SOPC_PubSubConnection_Set_InterfaceName(connection, itf_name);
        }
    }

            
    if (alloc)
    {
        // Allocate 2 writer groups (messages)
        alloc = SOPC_PubSubConnection_Allocate_WriterGroup_Array(connection, 2);
    }

    
    SOPC_WriterGroup* writerGroup = NULL;
    /*** Pub Message 14 ***/
    
    if (alloc)
    {
        // GroupId = 14
        // GroupVersion = 1
        // Interval = 100.000000 ms
        // Offest = -1 us
        // mqttTopic = NULL
        // encoding = SOPC_MessageEncodeUADP
        writerGroup = SOPC_PubSubConfig_SetPubMessageAt(connection, 0, 14, 1, 100.000000, -1, SOPC_SecurityMode_None, NULL, SOPC_MessageEncodeUADP, 0);
        alloc = NULL != writerGroup;
    }
    
    if (alloc)
    {
       // 1 data sets for message 14
       alloc = SOPC_WriterGroup_Allocate_DataSetWriter_Array(writerGroup, 1);
    }

    
    /*** DataSetMessage No 1 of message 14 ***/
    
    SOPC_DataSetWriter* writer = NULL;
    SOPC_PublishedDataSet* dataset = NULL;
    if (alloc)
    {
        writer = SOPC_WriterGroup_Get_DataSetWriter_At(writerGroup, 0);
        SOPC_ASSERT(NULL != writer);
        // WriterId = 1
        dataset = SOPC_PubSubConfig_InitDataSet(config, 0, writer, 0, 1, 1, 3);
        alloc = NULL != dataset;
    }
    if (alloc)
    {
        SOPC_PubSubConfig_SetPubVariableAt(dataset, 0, "ns=2;s=RawSingleSample_X", SOPC_Int32_Id, -1, NULL); // X
        SOPC_PubSubConfig_SetPubVariableAt(dataset, 1, "ns=2;s=RawSingleSample_Y", SOPC_Int32_Id, -1, NULL); // Y
        SOPC_PubSubConfig_SetPubVariableAt(dataset, 2, "ns=2;s=RawSingleSample_Z", SOPC_Int32_Id, -1, NULL); // Z
    }
    
    /*** Pub Message 15 ***/
    
    if (alloc)
    {
        // GroupId = 15
        // GroupVersion = 1
        // Interval = 1000.000000 ms
        // Offest = -1 us
        // mqttTopic = NULL
        // encoding = SOPC_MessageEncodeUADP
        writerGroup = SOPC_PubSubConfig_SetPubMessageAt(connection, 1, 15, 1, 1000.000000, -1, SOPC_SecurityMode_None, NULL, SOPC_MessageEncodeUADP, 0);
        alloc = NULL != writerGroup;
    }
    
    if (alloc)
    {
       // 1 data sets for message 15
       alloc = SOPC_WriterGroup_Allocate_DataSetWriter_Array(writerGroup, 1);
    }

    
    /*** DataSetMessage No 1 of message 15 ***/
    
    if (alloc)
    {
        writer = SOPC_WriterGroup_Get_DataSetWriter_At(writerGroup, 0);
        SOPC_ASSERT(NULL != writer);
        // WriterId = 1
        dataset = SOPC_PubSubConfig_InitDataSet(config, 1, writer, 0, 1, 1, 4);
        alloc = NULL != dataset;
    }
    if (alloc)
    {
        uint32_t arrayDimensions_0[1] = {10};
        SOPC_PubSubConfig_SetPubVariableAt(dataset, 0, "ns=2;s=RawBatch10_X_Array", SOPC_Int32_Id, 1, arrayDimensions_0); // X-Array
        uint32_t arrayDimensions_1[1] = {10};
        SOPC_PubSubConfig_SetPubVariableAt(dataset, 1, "ns=2;s=RawBatch10_Y_Array", SOPC_Int32_Id, 1, arrayDimensions_1); // Y-Array
        uint32_t arrayDimensions_2[1] = {10};
        SOPC_PubSubConfig_SetPubVariableAt(dataset, 2, "ns=2;s=RawBatch10_Z_Array", SOPC_Int32_Id, 1, arrayDimensions_2); // Z-Array
        SOPC_PubSubConfig_SetPubVariableAt(dataset, 3, "ns=2;s=RawBatch10_Time", SOPC_DateTime_Id, -1, NULL); // TimeFirstSample
    }
    

    if (!alloc)
    {
        SOPC_PubSubConfiguration_Delete(config);
        return NULL;
    }

    return config;
}
    