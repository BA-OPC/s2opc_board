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

 File Name            : service_add_nodes_1.c

 Date                 : 05/08/2022 09:03:06

 C Translator Version : tradc Java V1.2 (06/02/2022)

******************************************************************************/

/*------------------------
   Exported Declarations
  ------------------------*/
#include "service_add_nodes_1.h"

/*------------------------
   INITIALISATION Clause
  ------------------------*/
void service_add_nodes_1__INITIALISATION(void) {
}

/*--------------------
   OPERATIONS Clause
  --------------------*/
void service_add_nodes_1__check_add_nodes_item_params(
   const constants__t_ExpandedNodeId_i service_add_nodes_1__p_parentNid,
   const constants__t_NodeId_i service_add_nodes_1__p_refTypeId,
   const constants__t_ExpandedNodeId_i service_add_nodes_1__p_reqNodeId,
   const constants__t_NodeClass_i service_add_nodes_1__p_nodeClass,
   const constants__t_ExpandedNodeId_i service_add_nodes_1__p_typeDefId,
   constants_statuscodes_bs__t_StatusCode_i * const service_add_nodes_1__sc_operation,
   constants__t_NodeId_i * const service_add_nodes_1__new_nid) {
   {
      t_bool service_add_nodes_1__l_bres;
      t_bool service_add_nodes_1__l_local_server_exp_node_id;
      constants__t_NodeId_i service_add_nodes_1__l_node_id;
      t_bool service_add_nodes_1__l_node_exists;
      constants__t_Node_i service_add_nodes_1__l_node;
      constants__t_NodeClass_i service_add_nodes_1__l_node_class;
      
      *service_add_nodes_1__new_nid = constants__c_NodeId_indet;
      service_add_nodes_1__l_bres = false;
      *service_add_nodes_1__sc_operation = constants_statuscodes_bs__e_sc_bad_unexpected_error;
      constants__getall_conv_ExpandedNodeId_NodeId(service_add_nodes_1__p_parentNid,
         &service_add_nodes_1__l_local_server_exp_node_id,
         &service_add_nodes_1__l_node_id);
      if (service_add_nodes_1__l_local_server_exp_node_id == true) {
         service_write__readall_AddressSpace_Node(service_add_nodes_1__l_node_id,
            &service_add_nodes_1__l_node_exists,
            &service_add_nodes_1__l_node);
         if (service_add_nodes_1__l_node_exists == true) {
            service_add_nodes_1__l_bres = true;
         }
         else {
            *service_add_nodes_1__sc_operation = constants_statuscodes_bs__e_sc_bad_parent_node_id_invalid;
         }
      }
      else {
         *service_add_nodes_1__sc_operation = constants_statuscodes_bs__e_sc_bad_parent_node_id_invalid;
      }
      if (service_add_nodes_1__l_bres == true) {
         service_write__is_valid_ReferenceTypeId(service_add_nodes_1__p_refTypeId,
            &service_add_nodes_1__l_bres);
         if (service_add_nodes_1__l_bres == false) {
            *service_add_nodes_1__sc_operation = constants_statuscodes_bs__e_sc_bad_reference_type_id_invalid;
         }
      }
      if (service_add_nodes_1__l_bres == true) {
         service_write__is_transitive_subtype(service_add_nodes_1__p_refTypeId,
            constants__c_HierarchicalReferences_Type_NodeId,
            &service_add_nodes_1__l_bres);
         if (service_add_nodes_1__l_bres == false) {
            *service_add_nodes_1__sc_operation = constants_statuscodes_bs__e_sc_bad_reference_type_id_invalid;
         }
      }
      if (service_add_nodes_1__l_bres == true) {
         if (service_add_nodes_1__p_reqNodeId != constants__c_ExpandedNodeId_indet) {
            constants__getall_conv_ExpandedNodeId_NodeId(service_add_nodes_1__p_reqNodeId,
               &service_add_nodes_1__l_local_server_exp_node_id,
               &service_add_nodes_1__l_node_id);
            if (service_add_nodes_1__l_local_server_exp_node_id == true) {
               service_write__readall_AddressSpace_Node(service_add_nodes_1__l_node_id,
                  &service_add_nodes_1__l_node_exists,
                  &service_add_nodes_1__l_node);
               if (service_add_nodes_1__l_node_exists == false) {
                  *service_add_nodes_1__new_nid = service_add_nodes_1__l_node_id;
               }
               else {
                  service_add_nodes_1__l_bres = false;
                  *service_add_nodes_1__sc_operation = constants_statuscodes_bs__e_sc_bad_node_id_exists;
               }
            }
            else {
               service_add_nodes_1__l_bres = false;
               *service_add_nodes_1__sc_operation = constants_statuscodes_bs__e_sc_bad_node_id_rejected;
            }
         }
         else {
            service_add_nodes_1__l_bres = false;
            *service_add_nodes_1__sc_operation = constants_statuscodes_bs__e_sc_bad_node_id_rejected;
         }
      }
      if ((service_add_nodes_1__l_bres == true) &&
         (service_add_nodes_1__p_typeDefId != constants__c_ExpandedNodeId_indet)) {
         constants__getall_conv_ExpandedNodeId_NodeId(service_add_nodes_1__p_typeDefId,
            &service_add_nodes_1__l_local_server_exp_node_id,
            &service_add_nodes_1__l_node_id);
         if (service_add_nodes_1__l_local_server_exp_node_id == true) {
            service_write__readall_AddressSpace_Node(service_add_nodes_1__l_node_id,
               &service_add_nodes_1__l_node_exists,
               &service_add_nodes_1__l_node);
            if (service_add_nodes_1__l_node_exists == true) {
               service_write__get_NodeClass(service_add_nodes_1__l_node,
                  &service_add_nodes_1__l_node_class);
               if ((service_add_nodes_1__l_node_class == constants__e_ncl_VariableType) &&
                  (service_add_nodes_1__p_nodeClass == constants__e_ncl_Variable)) {
                  ;
               }
               else if ((service_add_nodes_1__l_node_class == constants__e_ncl_ObjectType) &&
                  (service_add_nodes_1__p_nodeClass == constants__e_ncl_Object)) {
                  ;
               }
               else {
                  service_add_nodes_1__l_bres = false;
                  *service_add_nodes_1__sc_operation = constants_statuscodes_bs__e_sc_bad_type_definition_invalid;
               }
            }
            else {
               service_add_nodes_1__l_bres = false;
               *service_add_nodes_1__sc_operation = constants_statuscodes_bs__e_sc_bad_type_definition_invalid;
            }
         }
      }
      if (service_add_nodes_1__l_bres == true) {
         *service_add_nodes_1__sc_operation = constants_statuscodes_bs__e_sc_ok;
      }
   }
}

void service_add_nodes_1__treat_add_nodes_item(
   const constants__t_ExpandedNodeId_i service_add_nodes_1__p_parentExpNid,
   const constants__t_NodeId_i service_add_nodes_1__p_refTypeId,
   const constants__t_ExpandedNodeId_i service_add_nodes_1__p_reqExpNodeId,
   const constants__t_QualifiedName_i service_add_nodes_1__p_browseName,
   const constants__t_NodeClass_i service_add_nodes_1__p_nodeClass,
   const constants__t_NodeAttributes_i service_add_nodes_1__p_nodeAttributes,
   const constants__t_ExpandedNodeId_i service_add_nodes_1__p_typeDefId,
   constants_statuscodes_bs__t_StatusCode_i * const service_add_nodes_1__sc_operation,
   constants__t_NodeId_i * const service_add_nodes_1__new_nodeId) {
   {
      constants_statuscodes_bs__t_StatusCode_i service_add_nodes_1__l_sc;
      constants__t_NodeId_i service_add_nodes_1__l_new_nid;
      
      service_add_nodes_1__check_add_nodes_item_params(service_add_nodes_1__p_parentExpNid,
         service_add_nodes_1__p_refTypeId,
         service_add_nodes_1__p_reqExpNodeId,
         service_add_nodes_1__p_nodeClass,
         service_add_nodes_1__p_typeDefId,
         &service_add_nodes_1__l_sc,
         &service_add_nodes_1__l_new_nid);
      if (service_add_nodes_1__l_sc == constants_statuscodes_bs__e_sc_ok) {
         ;
      }
      if (service_add_nodes_1__l_sc == constants_statuscodes_bs__e_sc_ok) {
         service_write__addNode_AddressSpace(service_add_nodes_1__p_parentExpNid,
            service_add_nodes_1__p_refTypeId,
            service_add_nodes_1__l_new_nid,
            service_add_nodes_1__p_browseName,
            service_add_nodes_1__p_nodeClass,
            service_add_nodes_1__p_nodeAttributes,
            service_add_nodes_1__p_typeDefId,
            &service_add_nodes_1__l_sc);
      }
      *service_add_nodes_1__sc_operation = service_add_nodes_1__l_sc;
      if (*service_add_nodes_1__sc_operation == constants_statuscodes_bs__e_sc_ok) {
         *service_add_nodes_1__new_nodeId = service_add_nodes_1__l_new_nid;
      }
      else {
         *service_add_nodes_1__new_nodeId = constants__c_NodeId_indet;
      }
   }
}

