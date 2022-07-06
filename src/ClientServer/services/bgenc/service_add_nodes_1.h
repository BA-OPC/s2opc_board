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

/******************************************************************************

 File Name            : service_add_nodes_1.h

 Date                 : 05/08/2022 09:03:06

 C Translator Version : tradc Java V1.2 (06/02/2022)

******************************************************************************/

#ifndef _service_add_nodes_1_h
#define _service_add_nodes_1_h

/*--------------------------
   Added by the Translator
  --------------------------*/
#include "b2c.h"

/*-----------------
   IMPORTS Clause
  -----------------*/
#include "service_write.h"

/*--------------
   SEES Clause
  --------------*/
#include "constants.h"
#include "constants_statuscodes_bs.h"
#include "message_in_bs.h"
#include "message_out_bs.h"
#include "msg_node_management_add_nodes.h"

/*------------------------
   INITIALISATION Clause
  ------------------------*/
extern void service_add_nodes_1__INITIALISATION(void);

/*-------------------------------
   PROMOTES and EXTENDS Clauses
  -------------------------------*/
#define service_add_nodes_1__check_nodeId_isValid service_write__check_nodeId_isValid
#define service_add_nodes_1__check_object_has_method service_write__check_object_has_method
#define service_add_nodes_1__get_BrowseName service_write__get_BrowseName
#define service_add_nodes_1__get_DisplayName service_write__get_DisplayName
#define service_add_nodes_1__get_Executable service_write__get_Executable
#define service_add_nodes_1__get_InputArguments service_write__get_InputArguments
#define service_add_nodes_1__get_NodeClass service_write__get_NodeClass
#define service_add_nodes_1__get_Node_RefIndexEnd service_write__get_Node_RefIndexEnd
#define service_add_nodes_1__get_RefIndex_Reference service_write__get_RefIndex_Reference
#define service_add_nodes_1__get_Reference_IsForward service_write__get_Reference_IsForward
#define service_add_nodes_1__get_Reference_ReferenceType service_write__get_Reference_ReferenceType
#define service_add_nodes_1__get_Reference_TargetNode service_write__get_Reference_TargetNode
#define service_add_nodes_1__get_TypeDefinition service_write__get_TypeDefinition
#define service_add_nodes_1__get_Value_StatusCode service_write__get_Value_StatusCode
#define service_add_nodes_1__get_conv_Variant_Type service_write__get_conv_Variant_Type
#define service_add_nodes_1__get_conv_Variant_ValueRank service_write__get_conv_Variant_ValueRank
#define service_add_nodes_1__get_user_authorization service_write__get_user_authorization
#define service_add_nodes_1__is_AddressSpace_constant service_write__is_AddressSpace_constant
#define service_add_nodes_1__is_IndexRangeDefined service_write__is_IndexRangeDefined
#define service_add_nodes_1__is_NodeId_equal service_write__is_NodeId_equal
#define service_add_nodes_1__is_local_service_treatment service_write__is_local_service_treatment
#define service_add_nodes_1__is_mandatory_attribute service_write__is_mandatory_attribute
#define service_add_nodes_1__is_transitive_subtype service_write__is_transitive_subtype
#define service_add_nodes_1__is_valid_ReferenceTypeId service_write__is_valid_ReferenceTypeId
#define service_add_nodes_1__read_AddressSpace_clear_value service_write__read_AddressSpace_clear_value
#define service_add_nodes_1__read_AddressSpace_free_variant service_write__read_AddressSpace_free_variant
#define service_add_nodes_1__read_Node_Attribute service_write__read_Node_Attribute
#define service_add_nodes_1__read_variable_compat_type service_write__read_variable_compat_type
#define service_add_nodes_1__readall_AddressSpace_Node service_write__readall_AddressSpace_Node
#define service_add_nodes_1__set_local_service_treatment service_write__set_local_service_treatment
#define service_add_nodes_1__treat_write_request service_write__treat_write_request

/*--------------------------
   LOCAL_OPERATIONS Clause
  --------------------------*/
extern void service_add_nodes_1__check_add_nodes_item_params(
   const constants__t_ExpandedNodeId_i service_add_nodes_1__p_parentNid,
   const constants__t_NodeId_i service_add_nodes_1__p_refTypeId,
   const constants__t_ExpandedNodeId_i service_add_nodes_1__p_reqNodeId,
   const constants__t_NodeClass_i service_add_nodes_1__p_nodeClass,
   const constants__t_ExpandedNodeId_i service_add_nodes_1__p_typeDefId,
   constants_statuscodes_bs__t_StatusCode_i * const service_add_nodes_1__sc_operation,
   constants__t_NodeId_i * const service_add_nodes_1__new_nid);

/*--------------------
   OPERATIONS Clause
  --------------------*/
extern void service_add_nodes_1__treat_add_nodes_item(
   const constants__t_ExpandedNodeId_i service_add_nodes_1__p_parentExpNid,
   const constants__t_NodeId_i service_add_nodes_1__p_refTypeId,
   const constants__t_ExpandedNodeId_i service_add_nodes_1__p_reqExpNodeId,
   const constants__t_QualifiedName_i service_add_nodes_1__p_browseName,
   const constants__t_NodeClass_i service_add_nodes_1__p_nodeClass,
   const constants__t_NodeAttributes_i service_add_nodes_1__p_nodeAttributes,
   const constants__t_ExpandedNodeId_i service_add_nodes_1__p_typeDefId,
   constants_statuscodes_bs__t_StatusCode_i * const service_add_nodes_1__sc_operation,
   constants__t_NodeId_i * const service_add_nodes_1__new_nodeId);

#endif
