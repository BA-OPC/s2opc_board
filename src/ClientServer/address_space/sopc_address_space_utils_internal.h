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

#ifndef SOPC_ADDRESS_SPACE_UTILS_INTERNAL_H_
#define SOPC_ADDRESS_SPACE_UTILS_INTERNAL_H_

#include <stdbool.h>

#include "sopc_address_space.h"
#include "sopc_builtintypes.h"
#include "sopc_common_constants.h"
#include "sopc_types.h"

#define RECURSION_LIMIT SOPC_DEFAULT_MAX_STRUCT_NESTED_LEVEL

bool SOPC_AddressSpaceUtil_IsTypeDefinition(const OpcUa_ReferenceNode* ref);
bool SOPC_AddressSpaceUtil_IsComponent(const OpcUa_ReferenceNode* ref);
bool SOPC_AddressSpaceUtil_IsProperty(const OpcUa_ReferenceNode* ref);
bool SOPC_AddressSpaceUtil_IsReversedHasChild(const OpcUa_ReferenceNode* ref);

SOPC_ExpandedNodeId* SOPC_AddressSpaceUtil_GetTypeDefinition(SOPC_AddressSpace* addSpace, SOPC_AddressSpace_Node* node);

const SOPC_NodeId* SOPC_AddressSpaceUtil_GetDirectParentType(SOPC_AddressSpace* addSpace,
                                                             const SOPC_NodeId* childNodeId);

bool SOPC_AddressSpaceUtil_RecursiveIsTransitiveSubtype(SOPC_AddressSpace* addSpace,
                                                        int recursionLimit,
                                                        const SOPC_NodeId* originSubtype,
                                                        const SOPC_NodeId* currentTypeOrSubtype,
                                                        const SOPC_NodeId* expectedParentType);

bool SOPC_AddressSpaceUtil_IsValidReferenceTypeId(SOPC_AddressSpace* addSpace, const SOPC_NodeId* nodeId);

/**
 * \brief Returns the DataType NodeId for the given encoding NodeId (DefaultBinary variable node)
 *        or NULL in case of failure. The variable S2OPC_DYNAMIC_TYPE_RESOLUTION definition shall be set to true.
 *
 * \param addSpace        The address space in which the encoding node is expected to be found.
 * \param encodingNodeId  The NodeId of a "Default Binary" encoding object expected to have an HasEncoding
 *                        backward reference to the searched DataType node.
 *                        If this nodeId directly matches a DataType node, it is returned.
 *
 * \return The DataType NodeId or NULL in case of failure.
 */
const SOPC_NodeId* SOPC_AddressSpaceUtil_GetEncodingDataType(SOPC_AddressSpace* addSpace,
                                                             const SOPC_NodeId* encodingNodeId);

#endif /* SOPC_ADDRESS_SPACE_UTILS_INTERNAL_H_ */
