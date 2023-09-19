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

/**
 * \file sopc_sockets_api.h
 *
 * \brief Event oriented API of the Services layer.
 *
 *   This module is in charge of the event dispatcher thread management.
 */

#ifndef SOPC_SERVICES_API_H_
#define SOPC_SERVICES_API_H_

#include <stdint.h>

#include "sopc_event_handler.h"

/**
 * Services events input events from application, services layer it-self or timer manager
 */
typedef enum SOPC_Services_Event
{
    /* Services to services events */
    SE_TO_SE_SC_ALL_DISCONNECTED =
        0x600,                          /**< Special event sent by B code to indicate all SC are closed.<BR>
                                           It might concerns only SC established as client or both client/server.<BR>
                                           params = true if for SCs as client only, false if both client and server SCs.
                                         */
    SE_TO_SE_ACTIVATE_ORPHANED_SESSION, /**< Client side only:<BR>
                                           id = session id<BR>
                                           auxParam = (uint32_t) secure channel config index
                                        */
    SE_TO_SE_CREATE_SESSION,            /**< Client side only:<BR>
                                           id = session id<BR>
                                           auxParam = (uint32_t) secure channel config index
                                        */
    SE_TO_SE_ACTIVATE_SESSION,          /**< Client side only:<BR>
                                         * id = session id<BR>
                                         * params = (user token structure)
                                         */

    SE_TO_SE_SERVER_DATA_CHANGED, /**< Server side only:<BR>
                                    params = (OpcUa_WriteValue*) old data value<BR>
                                    auxParam = (OpcUa_WriteValue*) new data value
                                  */

    SE_TO_SE_SERVER_NODE_CHANGED, /**< Server side only:<BR>
                                     params = (bool) true if node added, false if node deleted<BR>
                                     auxParam = (SOPC_NodeId*) NodeId of the node added/deleted
                                   */

    SE_TO_SE_SERVER_INACTIVATED_SESSION_PRIO, /**< Server side only:<BR>
                                                 id = session id<BR>
                                                 auxParam = (int32_t) session state
                                               */
    SE_TO_SE_SERVER_SEND_ASYNC_PUB_RESP_PRIO, /**< Server side only:<BR>
                                                 id = session id<BR>
                                                 params = (SOPC_Internal_AsyncSendMsgData*)<BR>
                                                 auxParams = (constants_statuscodes_bs__t_StatusCode_i) service result
                                                 code
                                               */

    /* Timer to services events */
    TIMER_SE_EVAL_SESSION_TIMEOUT,  /**< Server side only: id = session id */
    TIMER_SE_PUBLISH_CYCLE_TIMEOUT, /**< Server side only: id = subscription id */

    /* App to Services events : server side */
    APP_TO_SE_OPEN_ENDPOINT,         /**< id = endpoint description config index
                                      */
    APP_TO_SE_CLOSE_ENDPOINT,        /**< id = endpoint description config index
                                      */
    APP_TO_SE_LOCAL_SERVICE_REQUEST, /**< id = endpoint description config index<BR>
                                        params = (OpcUa_<MessageStruct>*) OPC UA message payload structure (header
                                         ignored)<BR>
                                        auxParam = user application session context
                                      */
    /* App to Services events : client side */
    APP_TO_SE_OPEN_REVERSE_ENDPOINT,  /**< id = reverse endpoint description config index */
    APP_TO_SE_CLOSE_REVERSE_ENDPOINT, /**< id = reverse endpoint description config index */
    APP_TO_SE_ACTIVATE_SESSION,       /**< Connect SC + Create Session + Activate session <BR>
                                         id = secure channel config index<BR>
                                         params = reverse endpoint connection index or 0 if not a reverse connection<BR>
                                         auxParam = (SOPC_Internal_SessionAppContext*)
                                       */
    APP_TO_SE_SEND_SESSION_REQUEST,   /**< id = session id<BR>
                                         params = (OpcUa_<MessageStruct>*) OPC UA message payload structure (header
                                         ignored)<BR>
                                         auxParam = user application request context
                                      */
    APP_TO_SE_SEND_DISCOVERY_REQUEST, /**< id = secure channel config index<BR>
                                         params = reverse endpoint connection index or 0 if not a reverse connection<BR>
                                         auxParam = (SOPC_Internal_DiscoveryContext*)
                                       */
    APP_TO_SE_CLOSE_SESSION,          /**< id = session id */
    APP_TO_SE_CLOSE_ALL_CONNECTIONS,  /**< Request to close all established SC connections<BR>
                                         It might be used to close only SC established as client or both client/server.
                                         Automatically called by ::SOPC_Toolkit_Clear for both client and server.<BR>
                                         params = true if for SCs as client only, false if both client and server SCs.
                                       */
    APP_TO_SE_REEVALUATE_SCS,         /**< Re-evaluate the secure channels due to application certificate/key update
                                           (force SC re-establishment)
                                           or PKI application trust list update (peer certificate re-validation necessary).<BR>
        
                                           params = (bool) flag indicating if it concerns server (true) or client (false)
                                           application secure channels.<BR>
                                           auxParam = (bool) flag indicating if it concerns application certificate/key update
                                           (true), otherwise the PKI trust list update (false).
                                      */

} SOPC_Services_Event;

/* API to enqueue an event for services */
void SOPC_Services_EnqueueEvent(SOPC_Services_Event seEvent, uint32_t id, uintptr_t params, uintptr_t auxParam);

/**
 *  \brief Initializes the services and application event dispatcher threads
 */
void SOPC_Services_Initialize(SOPC_SetListenerFunc* setSecureChannelsListener);

/**
 *  \brief Close all SecureChannels (established as client or both) in a synchronous way.
 *
 *  \param clientOnly  If flag is set, only the Secure Channels established as a client are closed.
 *                     Otherwise both Secure Channels established as a server and as client are closed.
 *
 *  \warning   It is a pre-requisite to call SOPC_Services_CloseAllSCs(false) prior to ::SOPC_Services_Clear
 */
void SOPC_Services_CloseAllSCs(bool clientOnly);

/**
 *  \brief Stop and clear the services and application event dispatcher threads
 */
void SOPC_Services_Clear(void);

// Internal use only (timers)
SOPC_EventHandler* SOPC_Services_GetEventHandler(void);

#endif /* SOPC_SERVICES_API_H_ */
