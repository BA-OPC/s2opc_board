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

#include "libs2opc_common_config.h"

#include <assert.h>
#include <stdio.h>

#include "libs2opc_common_internal.h"
#include "sopc_atomic.h"
#include "sopc_logger.h"
#include "sopc_mem_alloc.h"
#include "sopc_mutexes.h"
#include "sopc_toolkit_config.h"

/* Internal configuration structure and functions */
static void SOPC_Helper_ComEventCb(SOPC_App_Com_Event event, uint32_t IdOrStatus, void* param, uintptr_t helperContext);

SOPC_Helper_Config sopc_helper_config = {
    .initialized = (int32_t) false,
};

void SOPC_Helper_ComEventCb(SOPC_App_Com_Event event, uint32_t IdOrStatus, void* param, uintptr_t helperContext)
{
    Mutex_Lock(&sopc_helper_config.callbacksMutex);
    switch (event)
    {
    /* Client events */
    case SE_SESSION_ACTIVATION_FAILURE:
    case SE_ACTIVATED_SESSION:
    case SE_SESSION_REACTIVATING:
    case SE_RCV_SESSION_RESPONSE:
    case SE_CLOSED_SESSION:
    case SE_RCV_DISCOVERY_RESPONSE:
    case SE_SND_REQUEST_FAILED:
        if (NULL != sopc_helper_config.clientComEventCb)
        {
            sopc_helper_config.clientComEventCb(event, IdOrStatus, param, helperContext);
        }
        else
        {
            SOPC_Logger_TraceError(SOPC_LOG_MODULE_CLIENTSERVER,
                                   "Error: common wrapper not configured to manage client event %d\n", event);
        }
        break;
    /* Server events */
    case SE_CLOSED_ENDPOINT:
    case SE_LOCAL_SERVICE_RESPONSE:
        if (NULL != sopc_helper_config.serverComEventCb)
        {
            sopc_helper_config.serverComEventCb(event, IdOrStatus, param, helperContext);
        }
        else
        {
            SOPC_Logger_TraceError(SOPC_LOG_MODULE_CLIENTSERVER,
                                   "Error: common wrapper not configured to manage server event %d\n", event);
        }
        break;
    default:
        assert(false && "Unexpected event");
    }
    Mutex_Unlock(&sopc_helper_config.callbacksMutex);
}

SOPC_ReturnStatus SOPC_CommonHelper_Initialize(SOPC_Log_Configuration* optLogConfig)
{
    if (SOPC_Atomic_Int_Get(&sopc_helper_config.initialized))
    {
        return SOPC_STATUS_INVALID_STATE;
    }
    SOPC_ReturnStatus status = SOPC_STATUS_OK;
    if (NULL != optLogConfig)
    {
        status = SOPC_Common_Initialize(*optLogConfig);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Toolkit_Initialize(SOPC_Helper_ComEventCb);
    }

    sopc_helper_config.initialized = (int32_t) false;

    SOPC_S2OPC_Config_Initialize(&sopc_helper_config.config);

    if (SOPC_STATUS_OK != status)
    {
        SOPC_Toolkit_Clear();
    }
    else
    {
        Mutex_Initialization(&sopc_helper_config.callbacksMutex);
        SOPC_Atomic_Int_Set(&sopc_helper_config.initialized, (int32_t) true);
    }

    return status;
}

void SOPC_CommonHelper_Clear(void)
{
    if (!SOPC_Atomic_Int_Get(&sopc_helper_config.initialized))
    {
        return;
    }
    SOPC_Atomic_Int_Set(&sopc_helper_config.initialized, (int32_t) false);

    Mutex_Lock(&sopc_helper_config.callbacksMutex);
    sopc_helper_config.clientComEventCb = NULL;
    sopc_helper_config.serverComEventCb = NULL;
    Mutex_Unlock(&sopc_helper_config.callbacksMutex);
    Mutex_Clear(&sopc_helper_config.callbacksMutex);
    SOPC_S2OPC_Config_Clear(&sopc_helper_config.config);

    SOPC_Toolkit_Clear();
}

SOPC_Toolkit_Build_Info SOPC_CommonHelper_GetBuildInfo(void)
{
    return SOPC_ToolkitConfig_GetBuildInfo();
}

SOPC_ReturnStatus SOPC_CommonHelper_SetClientComEvent(SOPC_ComEvent_Fct* clientComEvtCb)
{
    if (!SOPC_Atomic_Int_Get(&sopc_helper_config.initialized))
    {
        return SOPC_STATUS_INVALID_STATE;
    }
    Mutex_Lock(&sopc_helper_config.callbacksMutex);
    sopc_helper_config.clientComEventCb = clientComEvtCb;
    Mutex_Unlock(&sopc_helper_config.callbacksMutex);

    return SOPC_STATUS_OK;
}

SOPC_ReturnStatus SOPC_CommonHelper_SetServerComEvent(SOPC_ComEvent_Fct* serverComEvtCb)
{
    if (!SOPC_Atomic_Int_Get(&sopc_helper_config.initialized))
    {
        return SOPC_STATUS_INVALID_STATE;
    }

    Mutex_Lock(&sopc_helper_config.callbacksMutex);
    sopc_helper_config.serverComEventCb = serverComEvtCb;
    Mutex_Unlock(&sopc_helper_config.callbacksMutex);

    return SOPC_STATUS_OK;
}
