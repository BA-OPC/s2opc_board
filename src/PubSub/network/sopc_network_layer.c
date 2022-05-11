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

#include <assert.h>

#include "sopc_encoder.h"
#include "sopc_mem_alloc.h"
#include "sopc_network_layer.h"
#include "sopc_pubsub_constants.h"

static uint32_t network_Error_Code = SOPC_UADP_NetworkMessage_Error_Code_None;

/**
 * For next versions:
 *  - Replace constants by variables from configuration,
 *  - Add code to manage disabled part of the Network Message
 *  - Re- allocate memory of the returned buffer if needed
 *  - Manage other type of publisher id type. Only uint32_t is managed
 */

/* Convert a PublisherId from dataset module to one of Configuration module */
static SOPC_Conf_PublisherId Network_Layer_Convert_PublisherId(SOPC_Dataset_LL_PublisherId* src);

/*
 * Check if security mode as enum is equals to security mode as boolean
 */
static bool Network_Check_ReceivedSecurityMode(SOPC_SecurityMode_Type mode, bool ssigned, bool encrypted);

/**
 * Constants definition for Hard-Coded value.
 * It defines the part of the Network Message which are not managed.
 * Warning: these constant cannot be changed without added new code
 */

const bool DATASET_LL_VERSION_FLAGS_ENABLED = true;
const bool DATASET_LL_FLAGS1_ENABLED = true;
const bool DATASET_LL_PUBLISHER_ID_ENABLED = true;
const bool DATASET_LL_GROUP_FLAGS_ENABLED = true;
const bool DATASET_LL_GROUP_HEADER_ENABLED = true;
const bool DATASET_LL_PAYLOAD_HEADER_ENABLED = true;
const bool DATASET_LL_DATASET_CLASSID_ENABLED = false;
const bool DATASET_LL_TIMESTAMP_ENABLED = false;
const bool DATASET_LL_PICOSECONDS_ENABLED = false;
const bool DATASET_LL_EXTENDED_FLAGS2_ENABLED = false;

const bool DATASET_LL_WRITER_GROUP_ID_ENABLED = true;
const bool DATASET_LL_WRITER_GROUP_VERSION_ENABLED = true;
const bool DATASET_LL_NETWORK_MESSAGE_NUMBER_ENABLED = false;
const bool DATASET_LL_SEQUENCE_NUMBER_ENABLED = false;

const uint8_t DATASET_LL_DSM_ENCODING_TYPE = 0; // Must include 1 shift bit.
const bool DATASET_LL_DSM_IS_VALID = true;
const bool DATASET_LL_DSM_SEQ_NUMBER_ENABLED = false;
const bool DATASET_LL_DSM_STATUS_ENABLED = false;
const bool DATASET_LL_DSM_MAJOR_VERSION_ENABLED = false;
const bool DATASET_LL_DSM_MINOR_VERSION_ENABLED = false;
// DataSet Flags 2 is not managed => UADP DataSetMessage type is Data Key Frame
const bool DATASET_LL_DSM_FLAGS2_ENABLED = false;

// Security Header Flag
const bool DATASET_LL_SECURITY_SIGNED_ENABLED = true;
const bool DATASET_LL_SECURITY_ENCRYPTED_ENABLED = true;
const bool DATASET_LL_SECURITY_FOOTER_ENABLED = false;
const bool DATASET_LL_SECURITY_KEY_RESET_ENABLED = false;

// END Constantes definition for Hard-Coded value

/**
 * Mask to set value at bit position
 */
const uint8_t C_NETWORK_MESSAGE_BIT_0 = 1;
const uint8_t C_NETWORK_MESSAGE_BIT_1 = 2;
const uint8_t C_NETWORK_MESSAGE_BIT_2 = 4;
const uint8_t C_NETWORK_MESSAGE_BIT_3 = 8;
const uint8_t C_NETWORK_MESSAGE_BIT_4 = 16;
const uint8_t C_NETWORK_MESSAGE_BIT_5 = 32;
const uint8_t C_NETWORK_MESSAGE_BIT_6 = 64;
const uint8_t C_NETWORK_MESSAGE_BIT_7 = 128;

const uint8_t C_NETWORK_MESSAGE_COMP_BIT_0 = 255 - 1;
const uint8_t C_NETWORK_MESSAGE_COMP_BIT_1 = 255 - 2;
const uint8_t C_NETWORK_MESSAGE_COMP_BIT_2 = 255 - 4;
const uint8_t C_NETWORK_MESSAGE_COMP_BIT_3 = 255 - 8;
const uint8_t C_NETWORK_MESSAGE_COMP_BIT_4 = 255 - 16;
const uint8_t C_NETWORK_MESSAGE_COMP_BIT_5 = 255 - 32;
const uint8_t C_NETWORK_MESSAGE_COMP_BIT_6 = 255 - 64;
const uint8_t C_NETWORK_MESSAGE_COMP_BIT_7 = 255 - 128;

/**
 * Set the value of a bit
 * byte is the variable to set. Type is uint8_t*
 * bit is the position of the bit to set. Type is uint8_t
 * b is the new value of the given bit. Type is bool
 */
#define Network_Message_Set_Bool_Bit(byte, bit, b)     \
    {                                                  \
        if (b)                                         \
        {                                              \
            *byte |= C_NETWORK_MESSAGE_BIT_##bit;      \
        }                                              \
        else                                           \
        {                                              \
            *byte &= C_NETWORK_MESSAGE_COMP_BIT_##bit; \
        }                                              \
    }

/**
 * Get the value of a bit
 * byte is the variable to read. Type is SOPC_Byte
 * bit is the position of the bit. Type is SOPC_Byte
 */
#define Network_Message_Get_Bool_Bit(byte, bit) ((byte & (C_NETWORK_MESSAGE_BIT_##bit)) ? true : false)

static inline SOPC_ReturnStatus valid_bool_to_status(const bool b)
{
    return (b ? SOPC_STATUS_OK : SOPC_STATUS_NOK);
}

static inline void check_status_and_set_default(const SOPC_ReturnStatus status,
                                                const SOPC_UADP_NetworkMessage_Error_Code code)
{
    if (SOPC_STATUS_OK != status)
    {
        network_Error_Code = code;
    }
}

static inline void set_status_default(SOPC_ReturnStatus* const status, const SOPC_UADP_NetworkMessage_Error_Code code)
{
    *status = SOPC_STATUS_NOK;
    network_Error_Code = code;
}

/**
 * Private
 * Network Message are initialised. DataMessage Array of the Network Message is not allocated.
 * Configuration fields are initialised to false.
 */
static SOPC_UADP_NetworkMessage* SOPC_Network_Message_Create(void);

/**
 * Private
 * precondition: dsm is not null neither its dataset fields
 */
static SOPC_ReturnStatus Network_DataSetFields_To_UADP(SOPC_Buffer* buffer, SOPC_Dataset_LL_DataSetMessage* dsm);

/**
 * Private
 * Read Length and Data in buffer and fill DataSetFields array of given DataSetMessage
 */
static SOPC_ReturnStatus UADP_To_DataSetFields(SOPC_Buffer* buffer, SOPC_Dataset_LL_DataSetMessage* dsm);

/**
 * Private
 * Write a publisher id.
 */
static SOPC_ReturnStatus Network_Layer_PublisherId_Write(SOPC_Buffer* buffer, SOPC_Dataset_LL_PublisherId* pub_id);

/**
 * Private
 * Read a publisher id in the given buffer.
 * The size of byte to read depends of pub_id_type.
 * The readed data is set in the given NetworkMessage
 */
static SOPC_ReturnStatus Network_Layer_PublisherId_Read(SOPC_Buffer* buffer,
                                                        SOPC_Byte pub_id_type,
                                                        SOPC_Dataset_LL_NetworkMessage* nm);

/**
 * Private
 * Return true if ExtendedFlags1 block should be enabled.
 */
static bool Network_Layer_Is_Flags1_Enabled(SOPC_Dataset_LL_NetworkMessage* nm, bool security);

/**
 * Private
 * Check if the received NetworkMessage is newer than the last processed.
 * To do this, compare the sequence number of the NetworkMessage which should be strictly monotonically increasing.
 * This function manages sequence numbers roll over (change from 4294967295 to 0).
 * See OPCUA Spec Part 14 - Table 75
 *
 * received is the sequence number in the current message
 * processed is the last processed sequence number
 */
static bool Network_Layer_Is_Sequence_Number_Newer(uint32_t received, uint32_t processed);

static SOPC_UADP_NetworkMessage* SOPC_Network_Message_Create(void)
{
    SOPC_UADP_NetworkMessage* result = SOPC_Calloc(1, sizeof(SOPC_UADP_NetworkMessage));
    result->nm = SOPC_Dataset_LL_NetworkMessage_CreateEmpty();
    return result;
}

static SOPC_ReturnStatus Network_DataSetFields_To_UADP(SOPC_Buffer* buffer, SOPC_Dataset_LL_DataSetMessage* dsm)
{
    uint16_t length = SOPC_Dataset_LL_DataSetMsg_Nb_DataSetField(dsm);

    SOPC_ReturnStatus status = SOPC_UInt16_Write(&length, buffer, 0);
    for (uint16_t i = 0; i < length && SOPC_STATUS_OK == status; i++)
    {
        const SOPC_Variant* variant = SOPC_Dataset_LL_DataSetMsg_Get_Variant_At(dsm, i);
        status = SOPC_Variant_Write(variant, buffer, 0);
    }
    return status;
}

static SOPC_ReturnStatus UADP_To_DataSetFields(SOPC_Buffer* buffer, SOPC_Dataset_LL_DataSetMessage* dsm)
{
    uint16_t length = 0;
    SOPC_ReturnStatus status;
    bool allocStatus;

    status = SOPC_UInt16_Read(&length, buffer, 0);
    if (SOPC_STATUS_OK != status)
    {
        return status;
    }

    allocStatus = SOPC_Dataset_LL_DataSetMsg_Allocate_DataSetField_Array(dsm, length);
    if (!allocStatus)
    {
        return SOPC_STATUS_OUT_OF_MEMORY;
    }

    for (uint16_t i = 0; i < length && SOPC_STATUS_OK == status; i++)
    {
        SOPC_Variant* variant = SOPC_Variant_Create();
        if (NULL == variant)
        {
            status = SOPC_STATUS_OUT_OF_MEMORY;
        }
        else
        {
            bool res = SOPC_Dataset_LL_DataSetMsg_Set_DataSetField_Variant_At(dsm, variant, i);
            assert(res); // valid index
            status = SOPC_Variant_Read(variant, buffer, 0);
        }
    }

    if (SOPC_STATUS_OK != status)
    {
        SOPC_Dataset_LL_DataSetMsg_Delete_DataSetField_Array(dsm);
    }

    return status;
}

static SOPC_ReturnStatus Network_Layer_PublisherId_Write(SOPC_Buffer* buffer, SOPC_Dataset_LL_PublisherId* pub_id)
{
    assert(NULL != buffer && NULL != pub_id);
    // String Publisher Id is not managed
    assert(DataSet_LL_PubId_String_Id != pub_id->type);
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    switch (pub_id->type)
    {
    case DataSet_LL_PubId_Byte_Id:
        status = SOPC_Byte_Write(&(pub_id->data.byte), buffer, 0);
        break;
    case DataSet_LL_PubId_UInt16_Id:
        status = SOPC_UInt16_Write(&(pub_id->data.uint16), buffer, 0);
        break;
    case DataSet_LL_PubId_UInt32_Id:
        status = SOPC_UInt32_Write(&(pub_id->data.uint32), buffer, 0);
        break;
    case DataSet_LL_PubId_UInt64_Id:
        status = SOPC_UInt64_Write(&(pub_id->data.uint64), buffer, 0);
        break;
    case DataSet_LL_PubId_String_Id:
    default:
        status = SOPC_STATUS_INVALID_PARAMETERS;
    }
    return status;
}

static SOPC_ReturnStatus Network_Layer_PublisherId_Read(SOPC_Buffer* buffer,
                                                        SOPC_Byte pub_id_type,
                                                        SOPC_Dataset_LL_NetworkMessage* nm)
{
    assert(NULL != buffer && NULL != nm);
    // String Publisher Id is not managed
    assert(DataSet_LL_PubId_String_Id != pub_id_type);
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    switch (pub_id_type)
    {
    case DataSet_LL_PubId_Byte_Id:
    {
        SOPC_Byte id;
        status = SOPC_Byte_Read(&id, buffer, 0);
        SOPC_Dataset_LL_NetworkMessage_Set_PublisherId_Byte(nm, id);
        break;
    }
    case DataSet_LL_PubId_UInt16_Id:
    {
        uint16_t id;
        status = SOPC_UInt16_Read(&id, buffer, 0);
        SOPC_Dataset_LL_NetworkMessage_Set_PublisherId_UInt16(nm, id);
        break;
    }
    case DataSet_LL_PubId_UInt32_Id:
    {
        uint32_t id;
        status = SOPC_UInt32_Read(&id, buffer, 0);
        SOPC_Dataset_LL_NetworkMessage_Set_PublisherId_UInt32(nm, id);
        break;
    }
    case DataSet_LL_PubId_UInt64_Id:
    {
        uint64_t id;
        status = SOPC_UInt64_Read(&id, buffer, 0);
        SOPC_Dataset_LL_NetworkMessage_Set_PublisherId_UInt64(nm, id);
        break;
    }
    case DataSet_LL_PubId_String_Id:
    default:
        status = SOPC_STATUS_INVALID_PARAMETERS;
    }
    return status;
}

static bool Network_Layer_Is_Flags1_Enabled(SOPC_Dataset_LL_NetworkMessage* nm, bool security)
{
    SOPC_Dataset_LL_PublisherId* pub_id = SOPC_Dataset_LL_NetworkMessage_Get_PublisherId(nm);
    return (DataSet_LL_PubId_Byte_Id != pub_id->type || DATASET_LL_DATASET_CLASSID_ENABLED || security ||
            DATASET_LL_TIMESTAMP_ENABLED || DATASET_LL_PICOSECONDS_ENABLED);
}

static bool Network_Layer_Is_Sequence_Number_Newer(uint32_t received, uint32_t processed)
{
    // See Spec OPC UA Part 14 - Table 75
    // NetworkMessages the following formula shall be used:
    // (4294967295 + received sequence number – last processed sequence number) modulo 4294967296.
    // Results below 1073741824 indicate that the received NetworkMessages is newer than
    // the last processed NetworkMessages...
    // Results above 3221225472 indicate that the received message is older (or same) than
    // the last processed NetworkMessages...
    // Other results are invalid...
    uint64_t max_uint32 = UINT32_MAX;
    uint64_t diff = max_uint32 + received - processed;
    uint64_t res = diff % (max_uint32 + 1);
    if (1073741824 > res)
    {
        return true;
    }
    else
    {
        return false;
    }
}

SOPC_Buffer* SOPC_UADP_NetworkMessage_Encode(SOPC_Dataset_LL_NetworkMessage* nm, SOPC_PubSub_SecurityType* security)
{
    SOPC_ReturnStatus status = SOPC_STATUS_OK;
    SOPC_Buffer* buffer = SOPC_Buffer_Create(SOPC_PUBSUB_BUFFER_SIZE);
    SOPC_Buffer* buffer_payload = NULL;
    uint32_t* dsmSizeBufferPos = NULL;
    uint8_t byte = 0;
    bool flags1_enabled;
    // security flags is enabled
    bool securityEnabled = (NULL != security);
    bool signedEnabled = false;
    bool encryptedEnabled = false;
    const uint8_t dsm_count = SOPC_Dataset_LL_NetworkMessage_Nb_DataSetMsg(nm);

    if (NULL != security)
    {
        signedEnabled =
            (SOPC_SecurityMode_Sign == security->mode || SOPC_SecurityMode_SignAndEncrypt == security->mode);
        encryptedEnabled = (SOPC_SecurityMode_SignAndEncrypt == security->mode);
    }

    // UADP version bit 0-3
    byte = SOPC_Dataset_LL_NetworkMessage_Get_Version(nm);
    // UADP flags bit 4-7
    //  - PublisherId enabled
    Network_Message_Set_Bool_Bit(&byte, 4, DATASET_LL_PUBLISHER_ID_ENABLED);
    //  - GroupHeader enabled
    Network_Message_Set_Bool_Bit(&byte, 5, DATASET_LL_GROUP_HEADER_ENABLED);
    //  - PayloadHeader enabled
    Network_Message_Set_Bool_Bit(&byte, 6, DATASET_LL_PAYLOAD_HEADER_ENABLED);
    //  - ExtendedFlags1 enabled
    flags1_enabled = Network_Layer_Is_Flags1_Enabled(nm, securityEnabled);
    Network_Message_Set_Bool_Bit(&byte, 7, flags1_enabled);
    status = SOPC_Buffer_Write(buffer, &byte, 1);
    check_status_and_set_default(status, SOPC_UADP_NetworkMessage_Error_Write_Buffer_Failed);

    if (flags1_enabled && SOPC_STATUS_OK == status)
    {
        // Bit range 0-2: PublisherId Type
        byte = (uint8_t) SOPC_Dataset_LL_NetworkMessage_Get_PublisherId(nm)->type;
        Network_Message_Set_Bool_Bit(&byte, 3, DATASET_LL_DATASET_CLASSID_ENABLED);
        Network_Message_Set_Bool_Bit(&byte, 4, securityEnabled);
        Network_Message_Set_Bool_Bit(&byte, 5, DATASET_LL_TIMESTAMP_ENABLED);
        Network_Message_Set_Bool_Bit(&byte, 6, DATASET_LL_PICOSECONDS_ENABLED);
        Network_Message_Set_Bool_Bit(&byte, 7, DATASET_LL_EXTENDED_FLAGS2_ENABLED);

        status = SOPC_Buffer_Write(buffer, &byte, 1);
        check_status_and_set_default(status, SOPC_UADP_NetworkMessage_Error_Write_Buffer_Failed);
    }

    if (DATASET_LL_PUBLISHER_ID_ENABLED && SOPC_STATUS_OK == status)
    {
        status = Network_Layer_PublisherId_Write(buffer, SOPC_Dataset_LL_NetworkMessage_Get_PublisherId(nm));
        check_status_and_set_default(status, SOPC_UADP_NetworkMessage_Error_Write_PubId_Failed);
    }

    if (DATASET_LL_DATASET_CLASSID_ENABLED && SOPC_STATUS_OK == status)
    {
        // Note :  DATASET_LL_DATASET_CLASSID_ENABLED is disabled in this version.
        // Otherwise, DataSetClassId should be encoded here
        assert(false);
    }

    // GroupHeader
    if (SOPC_STATUS_OK == status)
    {
        //  - set reserved bits to 0
        byte = 0;
        //  - WriterGroupId enabled
        Network_Message_Set_Bool_Bit(&byte, 0, DATASET_LL_WRITER_GROUP_ID_ENABLED);
        //  - WriterGroupVersion enabled
        Network_Message_Set_Bool_Bit(&byte, 1, DATASET_LL_WRITER_GROUP_VERSION_ENABLED);
        //  - NetworkMessageNumber enabled
        Network_Message_Set_Bool_Bit(&byte, 2, DATASET_LL_NETWORK_MESSAGE_NUMBER_ENABLED);
        //  - SequenceNumber enabled
        Network_Message_Set_Bool_Bit(&byte, 3, DATASET_LL_SEQUENCE_NUMBER_ENABLED);
        status = SOPC_Buffer_Write(buffer, &byte, 1);
        check_status_and_set_default(status, SOPC_UADP_NetworkMessage_Error_Write_Buffer_Failed);
    }

    if (DATASET_LL_WRITER_GROUP_ID_ENABLED && SOPC_STATUS_OK == status)
    {
        uint16_t byte_2 = SOPC_Dataset_LL_NetworkMessage_Get_GroupId(nm);
        status = SOPC_UInt16_Write(&byte_2, buffer, 0);
        check_status_and_set_default(status, SOPC_UADP_NetworkMessage_Error_Write_GroupId_Failed);
    }

    if (DATASET_LL_WRITER_GROUP_VERSION_ENABLED && SOPC_STATUS_OK == status)
    {
        uint32_t version = SOPC_Dataset_LL_NetworkMessage_Get_GroupVersion(nm);
        status = SOPC_UInt32_Write(&version, buffer, 0);
        check_status_and_set_default(status, SOPC_UADP_NetworkMessage_Error_Write_GroupVersion_Failed);
    }

    // payload header
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Buffer_Write(buffer, (const uint8_t*) &dsm_count, 1);
        check_status_and_set_default(status, SOPC_UADP_NetworkMessage_Error_Write_Buffer_Failed);

        for (int i = 0; i < dsm_count && SOPC_STATUS_OK == status; i++)
        {
            SOPC_Dataset_LL_DataSetMessage* dsm = SOPC_Dataset_LL_NetworkMessage_Get_DataSetMsg_At(nm, i);
            // - writer id
            uint16_t byte_2 = SOPC_Dataset_LL_DataSetMsg_Get_WriterId(dsm);
            status = SOPC_UInt16_Write(&byte_2, buffer, 0);
            check_status_and_set_default(status, SOPC_UADP_NetworkMessage_Error_Write_WriterId_Failed);
        }
    }

    // security header
    if (securityEnabled && SOPC_STATUS_OK == status)
    {
        byte = 0;
        // - NetworkMessage Signed
        Network_Message_Set_Bool_Bit(&byte, 0, signedEnabled);
        // - NetworkMessage Encrypted
        Network_Message_Set_Bool_Bit(&byte, 1, encryptedEnabled);
        // - Security Footer enabled
        Network_Message_Set_Bool_Bit(&byte, 2, DATASET_LL_SECURITY_FOOTER_ENABLED);
        // - Force key reset
        Network_Message_Set_Bool_Bit(&byte, 3, DATASET_LL_SECURITY_KEY_RESET_ENABLED);
        status = SOPC_Buffer_Write(buffer, &byte, 1);
        check_status_and_set_default(status, SOPC_UADP_NetworkMessage_Error_Write_Buffer_Failed);
        if (SOPC_STATUS_OK == status)
        {
            status = SOPC_UInt32_Write(&security->groupKeys->tokenId, buffer, 0);
            check_status_and_set_default(status, SOPC_UADP_NetworkMessage_Error_Write_TokenId_Failed);
        }

        if (SOPC_STATUS_OK == status)
        {
            uint32_t nonceRandomLength;
            status = SOPC_CryptoProvider_PubSubGetLength_MessageRandom(security->provider, &nonceRandomLength);
            check_status_and_set_default(status, SOPC_UADP_NetworkMessage_Error_Write_SecuHdr_Failed);

            assert(4 == nonceRandomLength &&            // Size is fixed to 4 bytes. See OPCUA Spec Part 14 - Table 75
                   nonceRandomLength + 4 <= UINT8_MAX); // check before cast to uint8

            // Random bytes + SequenceNumber 32 bits
            if (SOPC_STATUS_OK == status)
            {
                uint8_t nonceLength = (uint8_t)(nonceRandomLength + 4);
                status = SOPC_Byte_Write(&nonceLength, buffer, 0);
                check_status_and_set_default(status, SOPC_UADP_NetworkMessage_Error_Write_Buffer_Failed);
            }
            if (SOPC_STATUS_OK == status)
            {
                status = SOPC_Buffer_Write(buffer, security->msgNonceRandom, nonceRandomLength);
                check_status_and_set_default(status, SOPC_UADP_NetworkMessage_Error_Write_SecuHdr_Failed);
            }
        }

        if (SOPC_STATUS_OK == status)
        {
            status = SOPC_UInt32_Write(&security->sequenceNumber, buffer, 0);
            check_status_and_set_default(status, SOPC_UADP_NetworkMessage_Error_Write_SecuHdr_Failed);
        }

        if (DATASET_LL_SECURITY_FOOTER_ENABLED && SOPC_STATUS_OK == status)
        {
            // Security Footer is not used with AES-CTR
            set_status_default(&status, SOPC_UADP_NetworkMessage_Error_Write_SecuFooter_Failed);
        }
    }

    // payload: write Payload in an intermediate buffer.
    // and encrypt if security is enabled

    if (SOPC_STATUS_OK == status)
    {
        buffer_payload = SOPC_Buffer_Create(SOPC_PUBSUB_BUFFER_SIZE);
        if (NULL == buffer_payload)
        {
            set_status_default(&status, SOPC_UADP_NetworkMessage_Error_Write_Alloc_Failed);
        }
    }

    if (DATASET_LL_PAYLOAD_HEADER_ENABLED && dsm_count > 1 && SOPC_STATUS_OK == status)
    {
        dsmSizeBufferPos = SOPC_Calloc(dsm_count, sizeof(*dsmSizeBufferPos));
        if (NULL == dsmSizeBufferPos)
        {
            set_status_default(&status, SOPC_UADP_NetworkMessage_Error_Write_Alloc_Failed);
        }

        const uint16_t zero = 0;

        // DataSet Message size(2 bytes)
        // Sizes are unknown yet. Write Zeros, and store current position to write it later
        for (int i = 0; SOPC_STATUS_OK == status && i < dsm_count; i++)
        {
            status = SOPC_Buffer_GetPosition(buffer_payload, &dsmSizeBufferPos[i]);
            check_status_and_set_default(status, SOPC_UADP_NetworkMessage_Error_Write_DsmPreSize_Failed);

            if (SOPC_STATUS_OK == status)
            {
                status = SOPC_UInt16_Write(&zero, buffer_payload, 0);
                check_status_and_set_default(status, SOPC_UADP_NetworkMessage_Error_Write_DsmPreSize_Failed);
            }
        }
    }

    for (int i = 0; i < dsm_count && SOPC_STATUS_OK == status; i++)
    {
        // dsmStartBufferPos is set with buffer position before DSM content
        uint32_t dsmStartBufferPos;
        status = SOPC_Buffer_GetPosition(buffer_payload, &dsmStartBufferPos);
        assert(SOPC_STATUS_OK == status);

        SOPC_Dataset_LL_DataSetMessage* dsm = SOPC_Dataset_LL_NetworkMessage_Get_DataSetMsg_At(nm, i);
        assert(NULL != dsm);

        // DataSetMessage (1 byte)

        // - DataSet Flags 1
        //   - FieldEncoding is variant
        byte = DATASET_LL_DSM_ENCODING_TYPE;
        //   - DataSetMessage isValid = true
        Network_Message_Set_Bool_Bit(&byte, 0, DATASET_LL_DSM_IS_VALID);
        //   - sequence number is disabled
        Network_Message_Set_Bool_Bit(&byte, 3, DATASET_LL_DSM_SEQ_NUMBER_ENABLED);
        //   - status is disabled
        Network_Message_Set_Bool_Bit(&byte, 4, DATASET_LL_DSM_STATUS_ENABLED);
        //   - major version is disabled
        Network_Message_Set_Bool_Bit(&byte, 5, DATASET_LL_DSM_MAJOR_VERSION_ENABLED);
        //   - minor version is disabled
        Network_Message_Set_Bool_Bit(&byte, 6, DATASET_LL_DSM_MINOR_VERSION_ENABLED);
        //   - extended flags 2 is disabled
        Network_Message_Set_Bool_Bit(&byte, 7, DATASET_LL_DSM_FLAGS2_ENABLED);
        status = SOPC_Buffer_Write(buffer_payload, (uint8_t*) &byte, 1);
        check_status_and_set_default(status, SOPC_UADP_NetworkMessage_Error_Write_Buffer_Failed);

        if (SOPC_STATUS_OK == status)
        {
            status = Network_DataSetFields_To_UADP(buffer_payload, dsm);
            check_status_and_set_default(status, SOPC_UADP_NetworkMessage_Error_Write_DsmField_Failed);
        }

        if (NULL != dsmSizeBufferPos && SOPC_STATUS_OK == status)
        {
            // Write the DSM size at the payload start
            uint32_t dsmEndBufferPos;
            status = SOPC_Buffer_GetPosition(buffer_payload, &dsmEndBufferPos);
            assert(SOPC_STATUS_OK == status);

            const uint16_t dsmSize = (uint16_t)(dsmEndBufferPos - dsmStartBufferPos);
            bool writeOk = true;
            writeOk &= (SOPC_STATUS_OK == SOPC_Buffer_SetPosition(buffer_payload, dsmSizeBufferPos[i]));
            writeOk &= (SOPC_STATUS_OK == SOPC_UInt16_Write(&dsmSize, buffer_payload, 0));
            writeOk &= (SOPC_STATUS_OK == SOPC_Buffer_SetPosition(buffer_payload, dsmEndBufferPos));

            if (!writeOk)
            {
                set_status_default(&status, SOPC_UADP_NetworkMessage_Error_Write_DsmSize_Failed);
            }
        }
    }
    if (NULL != dsmSizeBufferPos)
    {
        SOPC_Free(dsmSizeBufferPos);
        dsmSizeBufferPos = NULL;
    }

    // Encrypt the Payload if encrypt is enabled
    if (encryptedEnabled && SOPC_STATUS_OK == status)
    {
        SOPC_Buffer* payload_encrypted = SOPC_PubSub_Security_Encrypt(security, buffer_payload);
        if (NULL == payload_encrypted)
        {
            set_status_default(&status, SOPC_UADP_NetworkMessage_Error_Write_EncryptPaylod_Failed);
        }
        else
        {
            // replace payload by the encrypted buffer
            SOPC_Buffer_Delete(buffer_payload);
            buffer_payload = payload_encrypted;
        }
    }

    // Write the Payload in the NetworkMessage Buffer
    if (SOPC_STATUS_OK == status)
    {
        SOPC_Buffer_SetPosition(buffer_payload, 0);
        int64_t nbread = SOPC_Buffer_ReadFrom(buffer, buffer_payload, buffer_payload->length);
        status = SOPC_Buffer_SetPosition(buffer, buffer->length);

        if (buffer_payload->length != nbread || SOPC_STATUS_OK != status)
        {
            set_status_default(&status, SOPC_UADP_NetworkMessage_Error_Write_PayloadFlush_Failed);
        }
    }

    if (NULL != buffer_payload)
    {
        SOPC_Buffer_Delete(buffer_payload);
    }
    /* end payload */

    // Signature
    if (signedEnabled && SOPC_STATUS_OK == status)
    {
        status = SOPC_PubSub_Security_Sign(security, buffer);
        check_status_and_set_default(status, SOPC_UADP_NetworkMessage_Error_Write_Sign_Failed);
    }

    if (NULL != buffer)
    {
        SOPC_Buffer_SetPosition(buffer, 0);
    }

    if (SOPC_STATUS_OK != status)
    {
        SOPC_Buffer_Delete(buffer);
        buffer = NULL;
    }

    return buffer;
}

/**
 * /brief Encode the payload of a datasetmessage
 * /param dsm The DataSetMessage to decode
 * /param buffer_payload The Payload
 * /param dsmSize The expected size (bytes) of the decoded payload from the DataSetMessage.
 *  Set to 0 if unknown
 * /return SOPC_STATUS_OK in case of success:
 *    - dsmSize matches actual decoded size, or dsmSize = 0
 *    - decoding stream is consistent (and payload large enough).
 *    Otherwise, network_Error_Code is set to a specific error code and an error code is returned.
 */
static SOPC_ReturnStatus decode_dataSetMessage(SOPC_Dataset_LL_DataSetMessage* dsm,
                                               SOPC_Buffer* buffer_payload,
                                               uint16_t dsmSize)
{
    assert(NULL != buffer_payload);
    assert(NULL != dsm);
    // Note :  dsmSizes may be NULL

    SOPC_ReturnStatus status = SOPC_STATUS_OK;
    SOPC_Byte data;
    SOPC_Boolean seq_nb_enabled = false;
    SOPC_Boolean status_enabled = false;
    SOPC_Boolean maj_version_enabled = false;
    SOPC_Boolean min_version_enabled = false;
    SOPC_Boolean dsm_flags2 = false;
    SOPC_Boolean timestamp_enabled = false;
    SOPC_Boolean picoseconds_enabled = false;

    uint32_t dsmStartBufferPos;
    status = SOPC_Buffer_GetPosition(buffer_payload, &dsmStartBufferPos);
    assert(SOPC_STATUS_OK == status);
    /* DataSetMessages Header */

    /** DataSetFlags1 **/
    if (DATASET_LL_FLAGS1_ENABLED)
    {
        status = SOPC_Byte_Read(&data, buffer_payload, 0);
        check_status_and_set_default(status, SOPC_UADP_NetworkMessage_Error_Read_Byte_Failed);

        if (SOPC_STATUS_OK == status)
        {
            status = valid_bool_to_status(Network_Message_Get_Bool_Bit(data, 0));
            check_status_and_set_default(status, SOPC_UADP_NetworkMessage_Error_Read_InvalidBit);
        }

        if (SOPC_STATUS_OK == status)
        {
            uint8_t field_encoding = data & (uint8_t)(C_NETWORK_MESSAGE_BIT_1 + C_NETWORK_MESSAGE_BIT_2);
            if (DATASET_LL_DSM_ENCODING_TYPE != field_encoding)
            {
                // not managed yet
                set_status_default(&status, SOPC_UADP_NetworkMessage_Error_Unsupported_EncodingType);
            }
            else
            {
                seq_nb_enabled = Network_Message_Get_Bool_Bit(data, 3);
                status_enabled = Network_Message_Get_Bool_Bit(data, 4);
                maj_version_enabled = Network_Message_Get_Bool_Bit(data, 5);
                min_version_enabled = Network_Message_Get_Bool_Bit(data, 6);
                dsm_flags2 = Network_Message_Get_Bool_Bit(data, 7);
                timestamp_enabled = false;
                picoseconds_enabled = false;
            }
        }
    }

    /** DataSetFlags2 **/
    if (dsm_flags2 && SOPC_STATUS_OK == status)
    {
        // Bit range 0-3: UADP DataSetMessage type
        // Bit 4: Timestamp enabled
        // Bit 5: PicoSeconds enabled
        status = SOPC_Byte_Read(&data, buffer_payload, 0);
        check_status_and_set_default(status, SOPC_UADP_NetworkMessage_Error_Read_Byte_Failed);

        if (SOPC_STATUS_OK == status)
        {
            uint8_t dataSmessage_type = data & (uint8_t)(C_NETWORK_MESSAGE_BIT_4 - 1);
            if (0 != dataSmessage_type)
            {
                set_status_default(&status, SOPC_UADP_NetworkMessage_Error_Unsupported_DsmType);
            }
            else
            {
                timestamp_enabled = Network_Message_Get_Bool_Bit(data, 4);
                picoseconds_enabled = Network_Message_Get_Bool_Bit(data, 5);
            }
        }
    }

    /** DataSetMessage SequenceNumber **/
    if (seq_nb_enabled && SOPC_STATUS_OK == status)
    {
        // not managed yet
        uint16_t notUsed;
        status = SOPC_UInt16_Read(&notUsed, buffer_payload, 0);
        check_status_and_set_default(status, SOPC_UADP_NetworkMessage_Error_Unsupported_DsmSeqNum);
    }

    /** Timestamp **/
    if (timestamp_enabled && SOPC_STATUS_OK == status)
    {
        // not managed yet
        uint64_t timestamp;
        status = SOPC_UInt64_Read(&timestamp, buffer_payload, 0);
        check_status_and_set_default(status, SOPC_UADP_NetworkMessage_Error_Unsupported_DsmTimeStamp);
    }

    /** PicoSeconds **/
    if (picoseconds_enabled && SOPC_STATUS_OK == status)
    {
        // not managed yet
        uint16_t notUsed;
        status = SOPC_UInt16_Read(&notUsed, buffer_payload, 0);
        check_status_and_set_default(status, SOPC_UADP_NetworkMessage_Error_Unsupported_DsmPicoseconds);
    }

    /** Status **/
    if (status_enabled && SOPC_STATUS_OK == status)
    {
        // not managed yet
        uint16_t notUsed;
        status = SOPC_UInt16_Read(&notUsed, buffer_payload, 0);
        check_status_and_set_default(status, SOPC_UADP_NetworkMessage_Error_Read_Short_Failed);
    }

    /** ConfigurationVersion MajorVersion **/
    if (maj_version_enabled && SOPC_STATUS_OK == status)
    {
        // not managed yet
        uint32_t not_used;
        status = SOPC_UInt32_Read(&not_used, buffer_payload, 0);
        check_status_and_set_default(status, SOPC_UADP_NetworkMessage_Error_Read_Int_Failed);
    }

    /** ConfigurationVersion MinorVersion **/
    if (min_version_enabled && SOPC_STATUS_OK == status)
    {
        // not managed yet
        uint32_t not_used;
        status = SOPC_UInt32_Read(&not_used, buffer_payload, 0);
        check_status_and_set_default(status, SOPC_UADP_NetworkMessage_Error_Read_Int_Failed);
    }

    if (SOPC_STATUS_OK == status)
    {
        /* Data Key Frame DataSetMessage Data */
        status = UADP_To_DataSetFields(buffer_payload, dsm);
        check_status_and_set_default(status, SOPC_UADP_NetworkMessage_Error_Read_DsmFields_Failed);
    }

    if (0 != dsmSize && SOPC_STATUS_OK == status)
    {
        uint32_t dsmEndBufferPos;
        status = SOPC_Buffer_GetPosition(buffer_payload, &dsmEndBufferPos);
        assert(SOPC_STATUS_OK == status);

        const uint16_t dsmBufferSize = (uint16_t)(dsmEndBufferPos - dsmStartBufferPos);

        if (dsmBufferSize != dsmSize)
        {
            // Mismatching DSM buffer size.
            set_status_default(&status, SOPC_UADP_NetworkMessage_Error_Read_DsmSizeCheck_Failed);
        }
    }

    return status;
}

SOPC_UADP_NetworkMessage* SOPC_UADP_NetworkMessage_Decode(SOPC_Buffer* buffer,
                                                          SOPC_UADP_GetSecurity_Func getSecurity_Func)
{
    SOPC_ReturnStatus status;
    SOPC_UADP_NetworkMessage* uadp_nm = SOPC_Network_Message_Create();
    SOPC_Dataset_LL_NetworkMessage* nm = uadp_nm->nm;
    SOPC_UADP_Configuration* conf = &uadp_nm->conf;
    SOPC_Boolean flags1_enabled = false;
    SOPC_Boolean flags2_enabled = false;
    // Publisher Id Type. Read in Extended flags1 or Byte if no flags1
    SOPC_Byte pub_id_type = DataSet_LL_PubId_Byte_Id;
    // number of DataSetMessage. Should be one
    SOPC_Byte msg_count = 0;
    SOPC_PubSub_SecurityType* security = NULL;
    SOPC_Buffer* buffer_payload = NULL;
    uint32_t payload_position = buffer->position;

    uint8_t securitySignedEnabled = false;
    uint8_t securityEncryptedEnabled = false;
    uint8_t securityFooterEnabled = false;
    uint8_t securityResetEnabled = false;
    uint16_t group_id = 0; // default value means not used

    // Version and Flags
    //  Bit range 0-3: Version of the UADP NetworkMessage
    //  Bit 4: PublisherId enabled
    //  Bit 5: GroupHeader enabled
    //  Bit 6: PayloadHeader enabled
    //  Bit 7: ExtendedFlags1 enabled
    if (DATASET_LL_VERSION_FLAGS_ENABLED)
    {
        SOPC_Byte data;
        SOPC_Byte version;
        status = SOPC_Byte_Read(&data, buffer, 0);
        check_status_and_set_default(status, SOPC_UADP_NetworkMessage_Error_Read_Byte_Failed);

        if (SOPC_STATUS_OK == status)
        {
            version = data & (uint8_t)(C_NETWORK_MESSAGE_BIT_4 - 1);
            SOPC_Dataset_LL_NetworkMessage_SetVersion(nm, version);
            conf->PublisherIdFlag = Network_Message_Get_Bool_Bit(data, 4);
            conf->GroupHeaderFlag = Network_Message_Get_Bool_Bit(data, 5);
            conf->PayloadHeaderFlag = Network_Message_Get_Bool_Bit(data, 6);
            flags1_enabled = Network_Message_Get_Bool_Bit(data, 7);
        }
    }

    // Bit range 0-2: PublisherId Type
    // Bit 3: DataSetClassId enabled
    // Bit 4: Security enabled
    // Bit 5: Timestamp enabled
    // Bit 6: PicoSeconds enabled
    // Bit 7: ExtendedFlags2 enabled
    if (flags1_enabled && SOPC_STATUS_OK == status)
    {
        SOPC_Byte data;
        status = SOPC_Byte_Read(&data, buffer, 0);
        check_status_and_set_default(status, SOPC_UADP_NetworkMessage_Error_Read_Byte_Failed);

        if (SOPC_STATUS_OK == status)
        {
            pub_id_type = data & (uint8_t)(C_NETWORK_MESSAGE_BIT_3 - 1);
            // other flags are not managed
            conf->DataSetClassIdFlag = Network_Message_Get_Bool_Bit(data, 3);
            conf->SecurityFlag = Network_Message_Get_Bool_Bit(data, 4);
            conf->TimestampFlag = Network_Message_Get_Bool_Bit(data, 5);
            conf->PicoSecondsFlag = Network_Message_Get_Bool_Bit(data, 6);
            flags2_enabled = Network_Message_Get_Bool_Bit(data, 7);
            if (conf->DataSetClassIdFlag || conf->TimestampFlag || conf->PicoSecondsFlag || flags2_enabled)
            {
                // not managed yet
                set_status_default(&status, SOPC_UADP_NetworkMessage_Error_Unsupported_Flags1);
            }
        }
    }
    else
    {
        conf->DataSetClassIdFlag = false;
        conf->SecurityFlag = false;
        conf->TimestampFlag = false;
        conf->PicoSecondsFlag = false;
        flags2_enabled = false;
    }
    // starting here, we assume that flags2_enabled is false
    // and do not manage the following bits for now:
    // Bit 0: Chunk message
    // Bit 1: PromotedFields enabled
    // Bit range 2-4: UADP NetworkMessage type
    // Others: not used
    conf->PromotedFieldsFlag = false;

    if (conf->PublisherIdFlag && SOPC_STATUS_OK == status)
    {
        status = Network_Layer_PublisherId_Read(buffer, pub_id_type, nm);
        check_status_and_set_default(status, SOPC_UADP_NetworkMessage_Error_Unsupported_PubIdType);
    }

    if (conf->DataSetClassIdFlag && SOPC_STATUS_OK == status)
    {
        // not managed yet
        set_status_default(&status, SOPC_UADP_NetworkMessage_Error_Unsupported_ClassId);
    }

    // Group Header
    if (conf->GroupHeaderFlag && SOPC_STATUS_OK == status)
    {
        // Bit 0: WriterGroupId enabled
        // Bit 1: GroupVersion enabled
        // Bit 2: NetworkMessageNumber enabled
        // Bit 3: SequenceNumber enabled
        // Others: not used
        {
            SOPC_Byte data;
            status = SOPC_Byte_Read(&data, buffer, 0);
            check_status_and_set_default(status, SOPC_UADP_NetworkMessage_Error_Read_Byte_Failed);

            if (SOPC_STATUS_OK == status)
            {
                conf->GroupIdFlag = Network_Message_Get_Bool_Bit(data, 0);
                conf->GroupVersionFlag = Network_Message_Get_Bool_Bit(data, 1);
                conf->NetworkMessageNumberFlag = Network_Message_Get_Bool_Bit(data, 2);
                conf->SequenceNumberFlag = Network_Message_Get_Bool_Bit(data, 3);
            }
        }

        if (conf->GroupIdFlag && SOPC_STATUS_OK == status)
        {
            status = SOPC_UInt16_Read(&group_id, buffer, 0);
            check_status_and_set_default(status, SOPC_UADP_NetworkMessage_Error_Read_Short_Failed);

            if (SOPC_STATUS_OK == status)
            {
                SOPC_Dataset_LL_NetworkMessage_Set_GroupId(nm, group_id);
            }
        }

        if (conf->GroupVersionFlag && SOPC_STATUS_OK == status)
        {
            uint32_t group_version;
            status = SOPC_UInt32_Read(&group_version, buffer, 0);
            check_status_and_set_default(status, SOPC_UADP_NetworkMessage_Error_Read_Int_Failed);

            if (SOPC_STATUS_OK == status)
            {
                SOPC_Dataset_LL_NetworkMessage_Set_GroupVersion(nm, group_version);
            }
        }

        if (conf->NetworkMessageNumberFlag && SOPC_STATUS_OK == status)
        {
            // not managed yet
            set_status_default(&status, SOPC_UADP_NetworkMessage_Error_Unsupported_MessageNum);
        }

        if (conf->SequenceNumberFlag && SOPC_STATUS_OK == status)
        {
            // not managed yet
            set_status_default(&status, SOPC_UADP_NetworkMessage_Error_Unsupported_SeqNum);
        }
    }

    // Payload Header
    // Only DataSetMessage is managed
    if (conf->PayloadHeaderFlag && SOPC_STATUS_OK == status)
    {
        status = SOPC_Byte_Read(&msg_count, buffer, 0);
        check_status_and_set_default(status, SOPC_UADP_NetworkMessage_Error_Read_Byte_Failed);
    }
    else if (SOPC_STATUS_OK == status)
    {
        msg_count = 1;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = valid_bool_to_status(SOPC_Dataset_LL_NetworkMessage_Allocate_DataSetMsg_Array(nm, msg_count));
        check_status_and_set_default(status, SOPC_UADP_NetworkMessage_Error_Read_Alloc_Failed);
    }

    for (int i = 0; i < msg_count && SOPC_STATUS_OK == status; i++)
    {
        SOPC_Dataset_LL_DataSetMessage* dsm = SOPC_Dataset_LL_NetworkMessage_Get_DataSetMsg_At(nm, i);
        uint16_t writer_id;
        status = SOPC_UInt16_Read(&writer_id, buffer, 0);
        check_status_and_set_default(status, SOPC_UADP_NetworkMessage_Error_Read_Short_Failed);

        if (SOPC_STATUS_OK == status)
        {
            SOPC_Dataset_LL_DataSetMsg_Set_WriterId(dsm, writer_id);
        }
    }

    // Timestamp
    if (conf->TimestampFlag && SOPC_STATUS_OK == status)
    {
        // not managed yet
        set_status_default(&status, SOPC_UADP_NetworkMessage_Error_Unsupported_Timestamp);
    }

    // Picoseconds
    if (conf->PicoSecondsFlag && SOPC_STATUS_OK == status)
    {
        // not managed yet
        set_status_default(&status, SOPC_UADP_NetworkMessage_Error_Unsupported_Picosceonds);
    }

    // Promoted fields
    if (conf->PromotedFieldsFlag && SOPC_STATUS_OK == status)
    {
        // not managed yet
        set_status_default(&status, SOPC_UADP_NetworkMessage_Error_Unsupported_PromotedFields);
    }

    // Security Header
    if (conf->SecurityFlag && SOPC_STATUS_OK == status)
    {
        uint8_t data;
        uint32_t securityTokenId;
        uint8_t securityNonceLength;
        uint8_t securityMessageNonce[4];
        uint32_t sequenceNumber;

        if (NULL == getSecurity_Func || 0 == group_id || !conf->PublisherIdFlag)
        {
            // Security information cannot be retrieved. The message is not processed
            set_status_default(&status, SOPC_UADP_NetworkMessage_Error_Read_Security_Failed);
        }
        else
        {
            status = SOPC_Byte_Read(&data, buffer, 0);
            check_status_and_set_default(status, SOPC_UADP_NetworkMessage_Error_Read_Byte_Failed);
        }

        if (SOPC_STATUS_OK == status)
        {
            securitySignedEnabled = Network_Message_Get_Bool_Bit(data, 0);
            securityEncryptedEnabled = Network_Message_Get_Bool_Bit(data, 1);
            securityFooterEnabled = Network_Message_Get_Bool_Bit(data, 2);
            securityResetEnabled = Network_Message_Get_Bool_Bit(data, 3);
        }

        if ((securityFooterEnabled || securityResetEnabled) && SOPC_STATUS_OK == status)
        {
            // security footer not used and reset not managed.
            set_status_default(&status, SOPC_UADP_NetworkMessage_Error_Unsupported_SecurityFooterReset);
        }

        if (SOPC_STATUS_OK == status)
        {
            status = SOPC_UInt32_Read(&securityTokenId, buffer, 0);
            check_status_and_set_default(status, SOPC_UADP_NetworkMessage_Error_Read_Int_Failed);
        }

        if (SOPC_STATUS_OK == status)
        {
            /* TODO: maybe this message is encrypted but we are not in the right group to decrypt it */
            security = getSecurity_Func(
                securityTokenId, Network_Layer_Convert_PublisherId(SOPC_Dataset_LL_NetworkMessage_Get_PublisherId(nm)),
                group_id);
            // Checked the security configuration of subscriber
            if (NULL == security ||
                !Network_Check_ReceivedSecurityMode(security->mode, securitySignedEnabled, securityEncryptedEnabled))
            {
                set_status_default(&status, SOPC_UADP_NetworkMessage_Error_Read_SecurityConf_Failed);
            }
        }

        if (SOPC_STATUS_OK == status)
        {
            assert(securityTokenId == security->groupKeys->tokenId);

            // Check signature before decoding
            if (securitySignedEnabled && !SOPC_PubSub_Security_Verify(security, buffer, payload_position))
            {
                set_status_default(&status, SOPC_UADP_NetworkMessage_Error_Read_SecuritySign_Failed);
            }
        }

        if (SOPC_STATUS_OK == status)
        {
            status = SOPC_Byte_Read(&securityNonceLength, buffer, 0);
            check_status_and_set_default(status, SOPC_UADP_NetworkMessage_Error_Read_Byte_Failed);
        }

        if (SOPC_STATUS_OK == status)
        {
            if (securityNonceLength != 8)
            {
                // See Spec OPC UA Part 14 - Table 76
                set_status_default(&status, SOPC_UADP_NetworkMessage_Error_Read_SecurityNonce_Failed);
            }
        }

        if (SOPC_STATUS_OK == status)
        {
            status = SOPC_Buffer_Read(securityMessageNonce, buffer, 4);
            check_status_and_set_default(status, SOPC_UADP_NetworkMessage_Error_Read_Byte_Failed);
        }

        if (SOPC_STATUS_OK == status)
        {
            // Get sequence number and check it is greater than last one received for the same (TokenId, PublisherId)
            status = SOPC_UInt32_Read(&sequenceNumber, buffer, 0);
            check_status_and_set_default(status, SOPC_UADP_NetworkMessage_Error_Read_SeqNum_Failed);
        }

        if (SOPC_STATUS_OK == status &&
            !Network_Layer_Is_Sequence_Number_Newer(sequenceNumber, security->sequenceNumber))
        {
            set_status_default(&status, SOPC_UADP_NetworkMessage_Error_Read_SeqNum_Failed);
        }

        if (SOPC_STATUS_OK == status)
        {
            security->sequenceNumber = sequenceNumber;
        }

        // Note: security footer not used for now
        // if (securityFooterEnabled)
        //{
        //    uint16_t securityFooterSize = 0;
        //    status = SOPC_UInt16_Read(&securityFooterSize, buffer, 0);
        //}

        // decrypt Payload
        if (securityEncryptedEnabled && SOPC_STATUS_OK == status)
        {
            uint32_t sizeSignature;
            status = SOPC_PubSub_Security_GetSignSize(security, securitySignedEnabled, &sizeSignature);
            check_status_and_set_default(status, SOPC_UADP_NetworkMessage_Error_Read_SecuritySignSize_Failed);

            if (SOPC_STATUS_OK == status)
            {
                // New data are Payload and signature.
                uint32_t sizePayload = SOPC_Buffer_Remaining(buffer) - sizeSignature;

                // This data shall be forget after calling Decrypt function
                security->msgNonceRandom = securityMessageNonce;
                // This function decrypt "sizePayload" bytes of the buffer from current position
                // Crypted data are replace by clear data in the buffer
                buffer_payload = SOPC_PubSub_Security_Decrypt(security, buffer, sizePayload);
                security->msgNonceRandom = NULL;
                if (NULL == buffer_payload)
                {
                    set_status_default(&status, SOPC_UADP_NetworkMessage_Error_Read_SecurityDecrypt_Failed);
                }
            }
        }
    }
    else
    {
        // check that subscriber expects security mode is none
        if (NULL != getSecurity_Func && SOPC_STATUS_OK == status) // if NULL, security mode is None
        {
            security = getSecurity_Func(
                SOPC_PUBSUB_SKS_DEFAULT_TOKENID,
                Network_Layer_Convert_PublisherId(SOPC_Dataset_LL_NetworkMessage_Get_PublisherId(nm)), group_id);
            // if security is NULL, there is no reader configured with security sign or encrypt/sign
            if (NULL != security && !Network_Check_ReceivedSecurityMode(security->mode, false, false))
            {
                set_status_default(&status, SOPC_UADP_NetworkMessage_Error_Read_SecurityNone_Failed);
            }
        }
    }

    // Payload
    if (NULL == buffer_payload && SOPC_STATUS_OK == status)
    {
        buffer_payload = buffer;
    }

    // Store DMS size to check it later
    uint16_t* dsmSizes = NULL;

    // No size if there is only one DataSetMessage
    if (msg_count > 1 && conf->PayloadHeaderFlag && SOPC_STATUS_OK == status)
    {
        dsmSizes = SOPC_Calloc(msg_count, sizeof(uint16_t));
        if (NULL == dsmSizes)
        {
            status = SOPC_STATUS_OUT_OF_MEMORY;
        }

        for (int i = 0; i < msg_count && SOPC_STATUS_OK == status; i++)
        {
            status = SOPC_UInt16_Read(&dsmSizes[i], buffer_payload, 0);
        }
        check_status_and_set_default(status, SOPC_UADP_NetworkMessage_Error_Read_DsmSize_Failed);
    }

    // Decode DataSetMessages

    // Bit 0: DataSetMessage is valid.
    // Bit range 1-2: Field Encoding
    // Bit 3: DataSetMessageSequenceNumber enabled
    // Bit 4: Status enabled
    // Bit 5: ConfigurationVersionMajorVersion enabled
    // Bit 6: ConfigurationVersionMinorVersion enable
    // Bit 7: DataSetFlags2 enabled
    for (int i = 0; i < msg_count && SOPC_STATUS_OK == status; i++)
    {
        SOPC_Dataset_LL_DataSetMessage* dsm = SOPC_Dataset_LL_NetworkMessage_Get_DataSetMsg_At(nm, i);

        const uint16_t size = (NULL == dsmSizes ? 0 : dsmSizes[i]);
        status = decode_dataSetMessage(dsm, buffer_payload, size);
    }

    if (NULL != dsmSizes)
    {
        SOPC_Free(dsmSizes);
    }

    if (SOPC_STATUS_OK != status)
    {
        assert(SOPC_UADP_NetworkMessage_Error_Code_None != network_Error_Code);
        SOPC_Dataset_LL_NetworkMessage_Delete(uadp_nm->nm);
        SOPC_Free(uadp_nm);
        uadp_nm = NULL;
    }

    // delete the Payload if it has been decrypted
    if (NULL != buffer_payload && buffer != buffer_payload)
    {
        SOPC_Buffer_Delete(buffer_payload);
    }

    return uadp_nm;
}

void SOPC_UADP_NetworkMessage_Delete(SOPC_UADP_NetworkMessage* uadp_nm)
{
    if (NULL != uadp_nm)
    {
        SOPC_Dataset_LL_NetworkMessage_Delete(uadp_nm->nm);
        SOPC_Free(uadp_nm);
    }
}

SOPC_UADP_NetworkMessage_Error_Code SOPC_UADP_NetworkMessage_Get_Last_Error(void)
{
    const SOPC_UADP_NetworkMessage_Error_Code result = network_Error_Code;
    network_Error_Code = SOPC_UADP_NetworkMessage_Error_Code_None;
    return result;
}

static SOPC_Conf_PublisherId Network_Layer_Convert_PublisherId(SOPC_Dataset_LL_PublisherId* src)
{
    SOPC_Conf_PublisherId result;
    switch (src->type)
    {
    case DataSet_LL_PubId_Byte_Id:
    {
        result.type = SOPC_UInteger_PublisherId;
        result.data.uint = src->data.byte;
        break;
    }
    case DataSet_LL_PubId_UInt16_Id:
    {
        result.type = SOPC_UInteger_PublisherId;
        result.data.uint = src->data.uint16;
        break;
    }
    case DataSet_LL_PubId_UInt32_Id:
    {
        result.type = SOPC_UInteger_PublisherId;
        result.data.uint = src->data.uint32;
        break;
    }
    case DataSet_LL_PubId_UInt64_Id:
    {
        result.type = SOPC_UInteger_PublisherId;
        result.data.uint = src->data.uint64;
        break;
    }
    case DataSet_LL_PubId_String_Id:
    {
        result.type = SOPC_String_PublisherId;
        result.data.string = src->data.string;
        break;
    }
    default:
        result.type = SOPC_Null_PublisherId;
    }
    return result;
}

static bool Network_Check_ReceivedSecurityMode(SOPC_SecurityMode_Type mode, bool ssigned, bool encrypted)
{
    switch (mode)
    {
    case SOPC_SecurityMode_Invalid:
        return false;
    case SOPC_SecurityMode_None:
        return !ssigned && !encrypted;
    case SOPC_SecurityMode_Sign:
        return ssigned && !encrypted;
    case SOPC_SecurityMode_SignAndEncrypt:
        return ssigned && encrypted;
    default:
        return false;
    }
}
