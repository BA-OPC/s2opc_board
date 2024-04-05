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

/***
 * @brief
 *  This demo application configures a OPCUA server and a PubSub
 *  - The server endpoint is provided by CONFIG_SOPC_ENDPOINT_ADDRESS
 *  - The PubSub configuration is staticly defined (see pubsub_config_static.h)
 *  - The server provides nodes to control the PubSub:
 *    - Start
 *    - Stop
 *    - Change publish period
 *    - Expose content of Subscriber-received DataSets (Read-Only)
 *      - These data are refreshed periodically based on CONFIG_SOPC_SUBSCRIBER_SYNCH_TIME_MS
 *      - If 0, then the data are synchronized to the AddressSpace synchronously
 *      (may be used with caution, in particular if PubSub periods are small)
 *    - Expose content of Publisher-emitted DataSets (Read-Write)
 *  - Notes: The content of the DSM CANNOT BE MODIFIED in this demo
 */
// System includes
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libs2opc_common_config.h"
#include "libs2opc_request_builder.h"
#include "libs2opc_server.h"

// S2OPC includes
#include "samples_platform_dep.h"
#include "sopc_assert.h"
#include "sopc_atomic.h"
#include "sopc_encodeable.h"
#include "sopc_logger.h"
#include "sopc_macros.h"
#include "sopc_mem_alloc.h"
#include "sopc_pub_scheduler.h"
#include "sopc_pubsub_local_sks.h"

// project includes
#include "cache.h"
#include "pubsub_config_static.h"
#include "static_security_data.h"
#include "test_config.h"

#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/adc.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/util.h>

/***************************************************/
/**               MISC FUNCTIONS                   */
/***************************************************/
static void log_UserCallback(const char* context, const char* text);

/***************************************************/
/**               SERVER CONFIGURATION             */
/***************************************************/
#define ASYNCH_CONTEXT_PARAM 0x12345678u
#define ASYNCH_CONTEXT_CACHE_SYNC 0x12345679u
#define APPLICATION_URI "urn:S2OPC:localhost"
#define PRODUCT_URI "urn:S2OPC:localhost"
#define SERVER_DESCRIPTION "S2OPC Publisher demo"
#define LOCALE_ID "en-US"

/***************************************************/
/**               SERVER VARIABLES CONTENT         */
/***************************************************/
static int32_t gStopped = true;

static int32_t value_PubSubStartStop = 0;

static bool Server_LocalWriteSingleNode(const SOPC_NodeId* pNid, SOPC_DataValue* pDv);
static SOPC_DataValue* Server_LocalReadSingleNode(const SOPC_NodeId* pNid);

#define NID_MEASURED_FORCE "ns=1;s=Force"
#define NID_TANK_LEVEL "ns=1;s=TankLevel"
#define NID_RAW_VOLTAGE "ns=1;s=RawVoltage"
static int write_double_value(double value, char* node_id);
static int write_bool_value(bool value, char* node_id);

static int write_underflow_warning(double tank_level);
static int write_overflow_warning(double tank_level);
static int read_tara(double* tara);
static int read_slope(double* slope);
static int update_publisher(void);

/***************************************************/
/**               PUBSUB VARIABLES CONTENT         */
/***************************************************/
static SOPC_PubSubConfiguration* pPubSubConfig = NULL;
static SOPC_PubSourceVariableConfig* pSourceConfig = NULL;
static bool gPubStarted = false;
// Date of last reception on Sub
static SOPC_RealTime* gLastReceptionDateMs = NULL;

/***************************************************/
/**               HELPER LOG MACROS                */
/***************************************************/
#define LOG_DEBUG(...) SOPC_Logger_TraceDebug(SOPC_LOG_MODULE_CLIENTSERVER, __VA_ARGS__)
#define LOG_INFO(...) SOPC_Logger_TraceInfo(SOPC_LOG_MODULE_CLIENTSERVER, __VA_ARGS__)
#define LOG_WARNING(...) SOPC_Logger_TraceWarning(SOPC_LOG_MODULE_CLIENTSERVER, __VA_ARGS__)
#define LOG_ERROR(...) SOPC_Logger_TraceError(SOPC_LOG_MODULE_CLIENTSERVER, __VA_ARGS__)
#define PRINT printf
#define YES_NO(x) ((x) ? "YES" : "NO")

/***************************************************/
/**               Stuff from ADC-example           */
/***************************************************/
#if !DT_NODE_EXISTS(DT_PATH(zephyr_user)) || !DT_NODE_HAS_PROP(DT_PATH(zephyr_user), io_channels)
#error "No suitable devicetree overlay specified"
#endif

#define DT_SPEC_AND_COMMA(node_id, prop, idx) ADC_DT_SPEC_GET_BY_IDX(node_id, idx),

/* Data of ADC io-channels specified in devicetree. */
static const struct adc_dt_spec adc_channels[] = {
    DT_FOREACH_PROP_ELEM(DT_PATH(zephyr_user), io_channels, DT_SPEC_AND_COMMA)};

/***************************************************/
static void log_UserCallback(const char* context, const char* text)
{
    SOPC_UNUSED_ARG(context);
    PRINT("%s\n", text);
}

/***************************************************/
static void cacheSync_WriteToCache(const SOPC_NodeId* pNid, const SOPC_DataValue* pDv)
{
    Cache_Lock();
    SOPC_DataValue* pDvCache = Cache_Get(pNid);

    // Only write values of cache that are already defined
    if (pDvCache != NULL)
    {
        // Replace content of Cache
        SOPC_DataValue_Clear(pDvCache);
        SOPC_DataValue_Copy(pDvCache, pDv);
    }
    Cache_Unlock();
}

/***************************************************/

/***************************************************/
/***
 * Request the server to update a node value (local request)
 * @param pNid The nodeId to modify
 * @param pDv The DataValue to write
 * @post \a localServiceAsyncRespCallback will be called with operation result
 */
static bool Server_LocalWriteSingleNode(const SOPC_NodeId* pNid, SOPC_DataValue* pDv)
{
    OpcUa_WriteRequest* request = SOPC_WriteRequest_Create(1);
    SOPC_ASSERT(NULL != request);

    SOPC_ReturnStatus status;
    status = SOPC_WriteRequest_SetWriteValue(request, 0, pNid, SOPC_AttributeId_Value, NULL, pDv);
    if (status != SOPC_STATUS_OK)
    {
        LOG_WARNING("SetWriteValue failed with code  %d", status);
        SOPC_Free(request);
    }
    else
    {
        // Synchronize cache for PubSub
        cacheSync_WriteToCache(pNid, pDv);

        // param is not used here because this is a static context. In a more complex application,
        // param can be set to any context pointer that way be required by the application
        // We use a simple marker to show data transmission from here to localServiceAsyncRespCallback
        status = SOPC_ServerHelper_LocalServiceAsync(request, ASYNCH_CONTEXT_PARAM);
        if (status != SOPC_STATUS_OK)
        {
            LOG_WARNING("LocalServiceAsync failed with code  (%d)", status);
            SOPC_Free(request);
        }
    }

    return status == SOPC_STATUS_OK;
}

/***************************************************/
/***
 * Send a read request to the server and wait for the response
 * @param pNid The nodeId to read
 * @return a new allocated DataValue containing the result (or NULL in case of failure).
 *      Shall be freed by caller after use.
 */
static SOPC_DataValue* Server_LocalReadSingleNode(const SOPC_NodeId* pNid)
{
    OpcUa_ReadRequest* request = SOPC_ReadRequest_Create(1, OpcUa_TimestampsToReturn_Neither);
    OpcUa_ReadResponse* response = NULL;
    SOPC_ASSERT(NULL != request);

    SOPC_ReturnStatus status;
    status = SOPC_ReadRequest_SetReadValue(request, 0, pNid, SOPC_AttributeId_Value, NULL);
    if (status != SOPC_STATUS_OK)
    {
        LOG_WARNING("Read Value failed with code  %d", status);
        SOPC_Free(request);
        return NULL;
    }

    // TODO: this obviously doesn't work, as there is no server running
    //       maybe connect to a different server, which is running the config,
    //       or pull in a minimal server config
    //       or use the "cache" to store the required node ids (initialization tbd.)
    //
    // status = SOPC_ClientCommon_Connect(const SOPC_LibSub_ConfigurationId cfgId, SOPC_LibSub_ConnectionId* pCliId);

    status = SOPC_ServerHelper_LocalServiceSync(request, (void**) &response);
    if (status != SOPC_STATUS_OK)
    {
        LOG_WARNING("Read Value failed with code  %d", status);
        SOPC_ASSERT(NULL == response);
        SOPC_Free(request);
        return NULL;
    }

    SOPC_DataValue* result = NULL;
    if (response != NULL && response->NoOfResults == 1)
    {
        // Allocate the result only if the response contains exactly the expected content
        result = SOPC_Malloc(sizeof(*result));
        SOPC_ASSERT(NULL != result);
        SOPC_DataValue_Copy(result, &response->Results[0]);
    }
    OpcUa_ReadResponse_Clear(response);
    SOPC_Free(response);
    return result;
}

/***************************************************/
static void clearPubSub(void)
{
    SOPC_PubScheduler_Stop();
    Cache_Clear();
}

/*****************************************************
 * @brief Creates and setup the PubSub, using KConfig parameters
 */
static void setupPubSub(void)
{
    // CONFIGURE PUBSUB
    pPubSubConfig = SOPC_PubSubConfig_GetStatic();
    SOPC_ASSERT(NULL != pPubSubConfig && "SOPC_PubSubConfig_GetStatic failed");

    /* Pub target configuration */
    pSourceConfig = SOPC_PubSourceVariableConfig_Create(&Cache_GetSourceVariables);
    SOPC_ASSERT(NULL != pSourceConfig && "SOPC_PubSourceVariableConfig_Create failed");

    // Configure SKS for PubSub
    SOPC_KeyBunch_init_static(pubSub_keySign, sizeof(pubSub_keySign), pubSub_keyEncrypt, sizeof(pubSub_keyEncrypt),
                              pubSub_keyNonce, sizeof(pubSub_keyNonce));

    Cache_Initialize(pPubSubConfig);
}

/***************************************************/
void SOPC_Platform_Main(void)
{
    SOPC_ReturnStatus status;
    PRINT("Build date : " __DATE__ " " __TIME__ "\n");

    int32_t val_mv;

    double tank_level = 0;
    double measured_force = 0;
    double tara = 0;
    double adc = 0;
    double slope = 0;

    int err;
    int16_t buf;
    struct adc_sequence sequence = {
        .buffer = &buf,
        /* buffer size in bytes, not number of samples */
        .buffer_size = sizeof(buf),
    };

    /* Configure channels individually prior to sampling. */
    for (size_t i = 0U; i < ARRAY_SIZE(adc_channels); i++)
    {
        if (!device_is_ready(adc_channels[i].dev))
        {
            printf("ADC controller device not ready\n");
            return;
        }

        err = adc_channel_setup_dt(&adc_channels[i]);
        if (err < 0)
        {
            printf("Could not setup channel #%d (%d)\n", i, err);
            return;
        }
    }

    /* Setup platform-dependant features (network, ...)*/
    SOPC_Platform_Setup();

    /* Configure the server logger (user logger) */
    SOPC_Log_Configuration logConfig;
    logConfig.logSystem = SOPC_LOG_SYSTEM_USER;
    logConfig.logLevel = SOPC_LOG_LEVEL_WARNING;
    logConfig.logSysConfig.userSystemLogConfig.doLog = &log_UserCallback;
    status = SOPC_CommonHelper_Initialize(&logConfig);
    SOPC_ASSERT(status == SOPC_STATUS_OK && "SOPC_CommonHelper_Initialize failed");

    gLastReceptionDateMs = SOPC_RealTime_Create(NULL);

    SOPC_NodeId nid_slope;
    SOPC_NodeId nid_tara;

    setupPubSub();
    {
        SOPC_DataValue slope;
        SOPC_DataValue_Initialize(&slope);
        slope.Value.Value.Uint32 = 38;
        slope.Value.BuiltInTypeId = SOPC_UInt32_Id;
        slope.Value.ArrayType = SOPC_VariantArrayType_SingleValue;
        SOPC_NodeId_InitializeFromCString(&nid_slope, "ns=1;s=Slope", 12);
        Cache_Set(&nid_slope, &slope);
    }

    {
        SOPC_DataValue tara;
        SOPC_DataValue_Initialize(&tara);
        tara.Value.Value.Uint32 = 55;
        tara.Value.BuiltInTypeId = SOPC_UInt32_Id;
        tara.Value.ArrayType = SOPC_VariantArrayType_SingleValue;
        SOPC_NodeId_InitializeFromCString(&nid_tara, "ns=1;s=Tara", 11);
        Cache_Set(&nid_tara, &tara);
    }

    //////////////////////////////////
    SOPC_Atomic_Int_Set(&gStopped, 0);

    // Check for server status after some time. (Start is asynchronous)
    SOPC_Sleep(100);
    SOPC_ASSERT(SOPC_Atomic_Int_Get(&gStopped) == 0 && "Failed to start.");

    // start publisher
    bool bResult;
    bResult = SOPC_PubScheduler_Start(pPubSubConfig, pSourceConfig, CONFIG_SOPC_PUBLISHER_PRIORITY);
    if (!bResult)
    {
        PRINT("\r\nFailed to start Publisher!\r\n");
    }
    else
    {
        gPubStarted = true;
        PRINT("\r\nPublisher started\r\n");
    }

    // uint64_t mock_value = 0x1122334455667788;

    // Wait for termination
    while (SOPC_Atomic_Int_Get(&gStopped) == 0)
    {
        SOPC_Sleep(50 * 20);

        read_tara(&tara);

        /* Read the ADC, and convert it into liters*/
        // printf("ADC reading:- %s, channel %d: ", adc_channels[0].dev->name, adc_channels[0].channel_id);
        (void) adc_sequence_init_dt(&adc_channels[0], &sequence);
        err = adc_read(adc_channels[0].dev, &sequence);
        // printf("%" PRId16, buf);
        val_mv = buf;
        err = adc_raw_to_millivolts_dt(&adc_channels[0], &val_mv);
        // printf(" = %" PRId32 " mV\n", val_mv);
        adc = (double) val_mv / 1000;
        write_double_value(adc, NID_RAW_VOLTAGE);
        read_slope(&slope);
        measured_force = (adc * slope); // 1.5kg => 15N => 2.4V  --> divide vy 0.16
        write_double_value(measured_force, NID_MEASURED_FORCE);
        tank_level = measured_force / 10 - tara;

        // uint64_t tmp = (mock_value&0xff) << 56;
        // mock_value = tmp | (mock_value >> 8);
        // tank_level = *((double*)(void*)&mock_value);

        // write_double_value(adc, NID_TANK_LEVEL);
        write_double_value(tank_level, NID_TANK_LEVEL);
        write_overflow_warning(tank_level);
        write_underflow_warning(tank_level);

        update_publisher();
    }

    SOPC_Atomic_Int_Set(&gStopped, 1);

    clearPubSub();

    LOG_DEBUG("SOPC_CommonHelper_Clear");
    SOPC_CommonHelper_Clear();

    SOPC_RealTime_Delete(&gLastReceptionDateMs);

    LOG_INFO("# Info: Server closed.\n");

    SOPC_Platform_Shutdown(true);
}

/***************************************************/
static int write_double_value(double value, char* node_id)
{
    SOPC_NodeId nid;
    SOPC_ReturnStatus status = SOPC_NodeId_InitializeFromCString(&nid, node_id, (int32_t) strlen(node_id));
    SOPC_ASSERT(SOPC_STATUS_OK == status);
    SOPC_DataValue dv;
    SOPC_DataValue_Initialize(&dv);

    dv.Value.ArrayType = SOPC_VariantArrayType_SingleValue;
    dv.Value.DoNotClear = false;
    dv.Value.BuiltInTypeId = SOPC_Double_Id;
    dv.Value.Value.Doublev = value;

    Server_LocalWriteSingleNode(&nid, &dv);

    SOPC_NodeId_Clear(&nid);
    SOPC_DataValue_Clear(&dv);
    return 0;
}

static int write_bool_value(bool value, char* node_id)
{
    SOPC_NodeId nid_write;
    SOPC_ReturnStatus status = SOPC_NodeId_InitializeFromCString(&nid_write, node_id, (int32_t) strlen(node_id));
    SOPC_ASSERT(SOPC_STATUS_OK == status);
    SOPC_DataValue dv_write;
    SOPC_DataValue_Initialize(&dv_write);

    dv_write.Value.ArrayType = SOPC_VariantArrayType_SingleValue;
    dv_write.Value.DoNotClear = false;
    dv_write.Value.BuiltInTypeId = SOPC_Boolean_Id;
    dv_write.Value.Value.Boolean = value;

    Server_LocalWriteSingleNode(&nid_write, &dv_write);
    SOPC_NodeId_Clear(&nid_write);
    SOPC_DataValue_Clear(&dv_write);

    return 0;
}

static SOPC_ReturnStatus read_double_value(double* result, char* node_id)
{
    SOPC_NodeId nid_read;
    SOPC_ReturnStatus status = SOPC_NodeId_InitializeFromCString(&nid_read, node_id, (int32_t) strlen(node_id));
    SOPC_ASSERT(SOPC_STATUS_OK == status);
    Cache_Lock();
    SOPC_DataValue* dv_read = Cache_Get(&nid_read);
    Cache_Unlock();
    // Server_LocalReadSingleNode(&nid_read);

    if (NULL == dv_read)
    {
        PRINT("Failed to read node '%s'\n", node_id);
        SOPC_NodeId_Clear(&nid_read);
        return SOPC_STATUS_NOK;
    }

    *result = dv_read->Value.Value.Doublev;

    SOPC_NodeId_Clear(&nid_read);
    return SOPC_STATUS_OK;
}

SOPC_ReturnStatus read_uint32_value(uint32_t* result, char* node_id)
{
    SOPC_NodeId nid_read;
    SOPC_ReturnStatus status = SOPC_NodeId_InitializeFromCString(&nid_read, node_id, (int32_t) strlen(node_id));
    SOPC_ASSERT(SOPC_STATUS_OK == status);
    Cache_Lock();
    SOPC_DataValue* dv_read = Cache_Get(&nid_read);
    Cache_Unlock();
    // Server_LocalReadSingleNode(&nid_read);

    if (NULL == dv_read)
    {
        PRINT("Failed to read node '%s'\n", node_id);
        SOPC_NodeId_Clear(&nid_read);
        return SOPC_STATUS_NOK;
    }

    *result = dv_read->Value.Value.Uint32;

    SOPC_NodeId_Clear(&nid_read);
    return SOPC_STATUS_OK;
}

static int write_overflow_warning(double tank_level)
{
    double limit;
    SOPC_ReturnStatus status = read_double_value(&limit, "ns=1;s=HiLimitTankLevel");
    if (status == SOPC_STATUS_NOK)
    {
        return 1;
    }

    write_bool_value(tank_level > limit, "ns=1;s=LevelAboveHigh");

    return 0;
}

static int write_underflow_warning(double tank_level)
{
    double limit;
    SOPC_ReturnStatus status = read_double_value(&limit, "ns=1;s=LoLimitTankLevel");
    if (status == SOPC_STATUS_NOK)
    {
        return 1;
    }

    write_bool_value(tank_level < limit, "ns=1;s=LevelUnderLow");

    return 0;
}

static int read_tara(double* tara)
{
    SOPC_ReturnStatus val = read_double_value(tara, "ns=1;s=Tara");
    if (val == SOPC_STATUS_NOK)
    {
        return 1;
    }

    return 0;
}

static int read_slope(double* slope)
{
    SOPC_ReturnStatus val = read_double_value(slope, "ns=1;s=Slope");
    if (val == SOPC_STATUS_NOK)
    {
        return 1;
    }
    return 0;
}

static int update_publisher(void)
{
    char nID_char_PubSubStartStop[23] = "ns=1;s=PubSubStartStop";

    SOPC_NodeId nid_read;
    SOPC_ReturnStatus status = SOPC_NodeId_InitializeFromCString(&nid_read, nID_char_PubSubStartStop,
                                                                 (int32_t) strlen(nID_char_PubSubStartStop));
    SOPC_ASSERT(SOPC_STATUS_OK == status);
    SOPC_DataValue* dv_read = Server_LocalReadSingleNode(&nid_read);
    if (NULL == dv_read)
    {
        PRINT("Failed to read node '%s'\n", nID_char_PubSubStartStop);
        SOPC_NodeId_Clear(&nid_read);
        return 1;
    }

    /* only execute on change! The functions start and stop threads...*/
    if (value_PubSubStartStop != dv_read->Value.Value.Byte)
    {
        if (1 == dv_read->Value.Value.Byte)
        {
            // start publisher (will fail if already started)
            bool bResult;
            bResult = SOPC_PubScheduler_Start(pPubSubConfig, pSourceConfig, CONFIG_SOPC_PUBLISHER_PRIORITY);
            if (!bResult)
            {
                PRINT("\r\nFailed to start Publisher!\r\n");
                return 1;
            }
            else
            {
                gPubStarted = true;
                PRINT("\r\nPublisher started\r\n");
                return 0;
            }
        }
        if (0 == dv_read->Value.Value.Byte)
        {
            SOPC_PubScheduler_Stop();
            gPubStarted = false;
            return 0;
        }
    }

    value_PubSubStartStop = dv_read->Value.Value.Byte;

    SOPC_NodeId_Clear(&nid_read);
    SOPC_DataValue_Clear(dv_read);
    SOPC_Free(dv_read);
    return 0;
}
