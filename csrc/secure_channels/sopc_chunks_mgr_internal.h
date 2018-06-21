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

#ifndef SOPC_CHUNKS_MGR_INTERNAL_H_
#define SOPC_CHUNKS_MGR_INTERNAL_H_

#include "sopc_secure_channels_internal_ctx.h"

bool SC_Chunks_DecodeReceivedBuffer(SOPC_SecureConnection_ChunkMgrCtx* ctx,
                                    SOPC_Buffer* receivedBuffer,
                                    SOPC_StatusCode* error);

bool SC_Chunks_TreatTcpPayload(SOPC_SecureConnection* scConnection, uint32_t* requestId, SOPC_StatusCode* errorStatus);

#endif // SOPC_CHUNKS_MGR_INTERNAL_H_
