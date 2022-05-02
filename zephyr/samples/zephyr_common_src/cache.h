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
 * \brief Provides a cache for data values.
 *
 * This cached is based on a SOPC_Dict whose keys are SOPC_NodeId and values are SOPC_DataVariant.
 * Functions Cache_GetSourceVariables and Cache_SetTargetVariables are callback that interface PubSub with the cache.
 *
 * For now, this cache uses a single Mutex to assert that only one thread writes or read.
 * This could be enhanced with the use of a read/write double buffer for instance.
 */

#ifndef CACHE_H_
#define CACHE_H_

#include <stdbool.h>

#include "sopc_builtintypes.h"
#include "sopc_pub_source_variable.h"
#include "sopc_pubsub_conf.h"
#include "sopc_sub_target_variable.h"

/** Initializes the cache from the configuration using default zero-values (or null strings) */
bool Cache_Initialize(SOPC_PubSubConfiguration* config);

/**
 * \brief Get a value in the cache
 *
 * \warning The returned pointer is a direct access to the cached value and should not be freed
 *
 * \return A pointer to the value in cache, or NULL if not found
 */
SOPC_DataValue* Cache_Get(const SOPC_NodeId* nid);

/**
 * \brief Set a value in the cache
 *
 * \warning The ownership of given \p dv is taken by the cache, so you should not reuse or free it
 */
bool Cache_Set(SOPC_NodeId* nid, SOPC_DataValue* dv);

/** The SOPC_GetSourceVariables_Func-compatible implementation that copies the values from the cache */
SOPC_DataValue* Cache_GetSourceVariables(OpcUa_ReadValueId* nodesToRead, int32_t nbValues);

/** The SOPC_SetTargetVariables_Func-compatible implementation that copies the values to the cache */
bool Cache_SetTargetVariables(OpcUa_WriteValue* nodesToWrite, int32_t nbValues);

/** Prints on console a human-readable representation of a nid and a Datavalue

 * @param pNid The NodeId to display
 * @param dv The DataValue to display
 */
void Cache_Dump_VarValue(const SOPC_NodeId* nid, const SOPC_DataValue* dv);

/** Prints on console a human-readable representation of the whole cache
 * Note:  this call locks the cache during all operation, which will prevent
 * other tasks to respond in time.
 * This is only a debug function
 */
void Cache_Dump(void);

/** The Cache shall be locked before accessing data (and its content, to prevent it from being freed) */
void Cache_Lock(void);
/** Unlock the cache previously locked by ::Cache_Lock */
void Cache_Unlock(void);
/** Deletes the cache */
void Cache_Clear(void);

/** Prototype for "listener" event callback. See ::Cache_SetSourceVarListener */
typedef void(Cache_SourceVarListener)(SOPC_DataValue* pDv);

/** Associates a "listener" to a given nodeId. each time the nodeId is modified
 * in the Cache, the "listener" is called.
 * @restriction In current implementation, only one listener is possible.
 * @param nid The NodeId to monitor. This nid must be allocated before call, and ownership
 *      s taken by current module (nid must be neither deallocated nor reused after call)
 * @param listener The event to call
 */
void Cache_SetSourceVarListener(SOPC_NodeId* nid, Cache_SourceVarListener* listener);

#endif /* CACHE_H_ */
