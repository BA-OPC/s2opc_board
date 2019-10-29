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

 File Name            : call_method_mgr.c

 Date                 : 28/10/2019 13:09:20

 C Translator Version : tradc Java V1.0 (14/03/2012)

******************************************************************************/

/*------------------------
   Exported Declarations
  ------------------------*/
#include "call_method_mgr.h"

/*------------------------
   INITIALISATION Clause
  ------------------------*/
void call_method_mgr__INITIALISATION(void) {
}

/*--------------------
   OPERATIONS Clause
  --------------------*/
void call_method_mgr__treat_method_call_request(
   const constants__t_session_i call_method_mgr__p_session,
   const constants__t_msg_i call_method_mgr__p_req_msg,
   const constants__t_msg_i call_method_mgr__p_resp_msg,
   constants_statuscodes_bs__t_StatusCode_i * const call_method_mgr__StatusCode_service) {
   {
      constants__t_endpoint_config_idx_i call_method_mgr__l_endpoint_config_idx;
      t_bool call_method_mgr__l_continue;
      t_entier4 call_method_mgr__l_nb;
      constants_statuscodes_bs__t_StatusCode_i call_method_mgr__l_status_op;
      constants__t_CallMethod_i call_method_mgr__l_callMethod;
      
      call_method_mgr__session_get_endpoint_config(call_method_mgr__p_session,
         &call_method_mgr__l_endpoint_config_idx);
      if (call_method_mgr__l_endpoint_config_idx != constants__c_endpoint_config_idx_indet) {
         msg_call_method_bs__read_call_method_request(call_method_mgr__p_req_msg,
            call_method_mgr__StatusCode_service,
            &call_method_mgr__l_nb);
         if (*call_method_mgr__StatusCode_service == constants_statuscodes_bs__e_sc_ok) {
            call_method_it__init_iter_callMethods(call_method_mgr__p_req_msg,
               &call_method_mgr__l_continue);
            if (call_method_mgr__l_continue == false) {
               *call_method_mgr__StatusCode_service = constants_statuscodes_bs__e_sc_bad_nothing_to_do;
            }
            else if (call_method_mgr__l_nb > constants__k_n_genericOperationPerReq_max) {
               *call_method_mgr__StatusCode_service = constants_statuscodes_bs__e_sc_bad_too_many_ops;
            }
            else {
               msg_call_method_bs__alloc_CallMethod_Result(call_method_mgr__p_resp_msg,
                  call_method_mgr__l_nb,
                  call_method_mgr__StatusCode_service);
               call_method_mgr__l_continue = (*call_method_mgr__StatusCode_service == constants_statuscodes_bs__e_sc_ok);
               while (call_method_mgr__l_continue == true) {
                  call_method_it__continue_iter_callMethod(&call_method_mgr__l_continue,
                     &call_method_mgr__l_callMethod);
                  call_method_mgr__treat_one_method_call(call_method_mgr__p_session,
                     call_method_mgr__p_req_msg,
                     call_method_mgr__p_resp_msg,
                     call_method_mgr__l_callMethod,
                     call_method_mgr__l_endpoint_config_idx,
                     &call_method_mgr__l_status_op);
                  if (call_method_mgr__l_status_op == constants_statuscodes_bs__e_sc_bad_out_of_memory) {
                     call_method_mgr__l_continue = false;
                     *call_method_mgr__StatusCode_service = constants_statuscodes_bs__e_sc_bad_out_of_memory;
                  }
               }
            }
         }
      }
      else {
         *call_method_mgr__StatusCode_service = constants_statuscodes_bs__e_sc_bad_session_id_invalid;
      }
   }
}

void call_method_mgr__treat_one_method_call(
   const constants__t_session_i call_method_mgr__p_session,
   const constants__t_msg_i call_method_mgr__p_req_msg,
   const constants__t_msg_i call_method_mgr__p_res_msg,
   const constants__t_CallMethod_i call_method_mgr__p_callMethod,
   const constants__t_endpoint_config_idx_i call_method_mgr__p_endpoint_config_idx,
   constants_statuscodes_bs__t_StatusCode_i * const call_method_mgr__StatusCode) {
   call_method_mgr__check_method_call_inputs(call_method_mgr__p_session,
      call_method_mgr__p_req_msg,
      call_method_mgr__p_callMethod,
      call_method_mgr__StatusCode);
   if (*call_method_mgr__StatusCode == constants_statuscodes_bs__e_sc_ok) {
      call_method_bs__exec_callMethod(call_method_mgr__p_req_msg,
         call_method_mgr__p_callMethod,
         call_method_mgr__p_endpoint_config_idx,
         call_method_mgr__StatusCode);
      if (*call_method_mgr__StatusCode == constants_statuscodes_bs__e_sc_ok) {
         call_method_mgr__check_exec_result(call_method_mgr__p_req_msg,
            call_method_mgr__p_callMethod,
            call_method_mgr__StatusCode);
         if (*call_method_mgr__StatusCode == constants_statuscodes_bs__e_sc_ok) {
            call_method_mgr__copy_exec_result(call_method_mgr__p_res_msg,
               call_method_mgr__p_callMethod,
               call_method_mgr__StatusCode);
         }
      }
      call_method_bs__free_exec_result();
   }
   msg_call_method_bs__write_CallMethod_Res_Status(call_method_mgr__p_res_msg,
      call_method_mgr__p_callMethod,
      *call_method_mgr__StatusCode);
}

void call_method_mgr__check_method_call_inputs(
   const constants__t_session_i call_method_mgr__p_session,
   const constants__t_msg_i call_method_mgr__p_req_msg,
   const constants__t_CallMethod_i call_method_mgr__p_callMethod,
   constants_statuscodes_bs__t_StatusCode_i * const call_method_mgr__StatusCode) {
   {
      constants__t_Node_i call_method_mgr__l_object;
      constants__t_NodeId_i call_method_mgr__l_objectid;
      constants__t_Node_i call_method_mgr__l_method;
      constants__t_NodeId_i call_method_mgr__l_methodid;
      constants__t_user_i call_method_mgr__l_user;
      t_bool call_method_mgr__l_valid_executable;
      t_bool call_method_mgr__l_valid_user_executable;
      
      msg_call_method_bs__read_CallMethod_Objectid(call_method_mgr__p_req_msg,
         call_method_mgr__p_callMethod,
         &call_method_mgr__l_objectid);
      call_method_mgr__check_nodeId(call_method_mgr__l_objectid,
         call_method_mgr__StatusCode,
         &call_method_mgr__l_object);
      if (*call_method_mgr__StatusCode == constants_statuscodes_bs__e_sc_ok) {
         msg_call_method_bs__read_CallMethod_MethodId(call_method_mgr__p_req_msg,
            call_method_mgr__p_callMethod,
            &call_method_mgr__l_methodid);
         call_method_mgr__check_nodeId(call_method_mgr__l_methodid,
            call_method_mgr__StatusCode,
            &call_method_mgr__l_method);
         if (*call_method_mgr__StatusCode == constants_statuscodes_bs__e_sc_ok) {
            session_mgr__get_session_user_server(call_method_mgr__p_session,
               &call_method_mgr__l_user);
            address_space__get_Executable(call_method_mgr__l_method,
               &call_method_mgr__l_valid_executable);
            address_space__get_user_authorization(constants__e_operation_type_executable,
               call_method_mgr__l_methodid,
               constants__e_aid_UserExecutable,
               call_method_mgr__l_user,
               &call_method_mgr__l_valid_user_executable);
            if ((call_method_mgr__l_valid_executable == true) &&
               (call_method_mgr__l_valid_user_executable == true)) {
               *call_method_mgr__StatusCode = constants_statuscodes_bs__e_sc_bad_user_access_denied;
            }
            else {
               *call_method_mgr__StatusCode = constants_statuscodes_bs__e_sc_ok;
            }
         }
         else {
            *call_method_mgr__StatusCode = constants_statuscodes_bs__e_sc_bad_method_invalid;
         }
      }
   }
}

void call_method_mgr__check_exec_result(
   const constants__t_msg_i call_method_mgr__p_req_msg,
   const constants__t_CallMethod_i call_method_mgr__p_callMethod,
   constants_statuscodes_bs__t_StatusCode_i * const call_method_mgr__StatusCode) {
   if ((call_method_mgr__p_req_msg != constants__c_msg_indet) &&
      (call_method_mgr__p_callMethod != constants__c_CallMethod_indet)) {
      *call_method_mgr__StatusCode = constants_statuscodes_bs__e_sc_ok;
   }
   else {
      *call_method_mgr__StatusCode = constants_statuscodes_bs__e_sc_bad_method_invalid;
   }
}

void call_method_mgr__copy_exec_result(
   const constants__t_msg_i call_method_mgr__p_res_msg,
   const constants__t_CallMethod_i call_method_mgr__p_callMethod,
   constants_statuscodes_bs__t_StatusCode_i * const call_method_mgr__StatusCode) {
   {
      t_bool call_method_mgr__l_continue;
      t_entier4 call_method_mgr__l_nb;
      constants__t_Variant_i call_method_mgr__l_value;
      t_entier4 call_method_mgr__l_index;
      
      call_method_bs__read_nb_exec_result(&call_method_mgr__l_nb);
      call_method_result_it__init_iter_callMethodResultIdx(call_method_mgr__l_nb,
         &call_method_mgr__l_continue);
      if (call_method_mgr__l_continue == false) {
         *call_method_mgr__StatusCode = constants_statuscodes_bs__e_sc_ok;
      }
      else {
         msg_call_method_bs__alloc_CallMethod_Res_OutputArgument(call_method_mgr__p_res_msg,
            call_method_mgr__p_callMethod,
            call_method_mgr__l_nb,
            call_method_mgr__StatusCode);
         call_method_mgr__l_continue = (*call_method_mgr__StatusCode == constants_statuscodes_bs__e_sc_ok);
         while (call_method_mgr__l_continue == true) {
            call_method_result_it__continue_iter_callMethodResultIdx(&call_method_mgr__l_continue,
               &call_method_mgr__l_index);
            call_method_bs__read_exec_result(call_method_mgr__l_index,
               &call_method_mgr__l_value);
            msg_call_method_bs__write_CallMethod_Res_OutputArgument(call_method_mgr__p_res_msg,
               call_method_mgr__p_callMethod,
               call_method_mgr__l_index,
               call_method_mgr__l_value,
               call_method_mgr__StatusCode);
            call_method_mgr__l_continue = ((call_method_mgr__l_continue == true) &&
               (*call_method_mgr__StatusCode == constants_statuscodes_bs__e_sc_ok));
         }
         if (*call_method_mgr__StatusCode == constants_statuscodes_bs__e_sc_bad_out_of_memory) {
            msg_call_method_bs__free_CallMethod_Res_OutputArgument(call_method_mgr__p_res_msg,
               call_method_mgr__p_callMethod);
         }
      }
   }
}

void call_method_mgr__check_nodeId(
   const constants__t_NodeId_i call_method_mgr__nodeid,
   constants_statuscodes_bs__t_StatusCode_i * const call_method_mgr__statusCode,
   constants__t_Node_i * const call_method_mgr__node) {
   {
      t_bool call_method_mgr__l_isvalid;
      
      *call_method_mgr__statusCode = constants_statuscodes_bs__e_sc_ok;
      *call_method_mgr__node = constants__c_Node_indet;
      if (call_method_mgr__nodeid == constants__c_NodeId_indet) {
         *call_method_mgr__statusCode = constants_statuscodes_bs__e_sc_bad_node_id_invalid;
      }
      else {
         address_space__readall_AddressSpace_Node(call_method_mgr__nodeid,
            &call_method_mgr__l_isvalid,
            call_method_mgr__node);
         if (call_method_mgr__l_isvalid == false) {
            *call_method_mgr__statusCode = constants_statuscodes_bs__e_sc_bad_node_id_unknown;
         }
      }
   }
}

void call_method_mgr__session_get_endpoint_config(
   const constants__t_session_i call_method_mgr__p_session,
   constants__t_endpoint_config_idx_i * const call_method_mgr__endpoint_config_idx) {
   {
      constants__t_channel_i call_method_mgr__l_channel;
      t_bool call_method_mgr__l_continue;
      
      *call_method_mgr__endpoint_config_idx = constants__c_endpoint_config_idx_indet;
      session_mgr__getall_valid_session_channel(call_method_mgr__p_session,
         &call_method_mgr__l_continue,
         &call_method_mgr__l_channel);
      if (call_method_mgr__l_continue == true) {
         channel_mgr__server_get_endpoint_config(call_method_mgr__l_channel,
            call_method_mgr__endpoint_config_idx);
      }
   }
}
