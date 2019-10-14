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

 File Name            : translate_browse_path_result_it.c

 Date                 : 21/11/2019 15:45:17

 C Translator Version : tradc Java V1.0 (14/03/2012)

******************************************************************************/

/*------------------------
   Exported Declarations
  ------------------------*/
#include "translate_browse_path_result_it.h"

/*----------------------------
   CONCRETE_VARIABLES Clause
  ----------------------------*/
t_entier4 translate_browse_path_result_it__currentBrowseResultIdx_i;
t_entier4 translate_browse_path_result_it__nb_browseResult_max_refs_i;

/*------------------------
   INITIALISATION Clause
  ------------------------*/
void translate_browse_path_result_it__INITIALISATION(void) {
   translate_browse_path_result_it__currentBrowseResultIdx_i = 0;
   translate_browse_path_result_it__nb_browseResult_max_refs_i = 0;
}

/*--------------------
   OPERATIONS Clause
  --------------------*/
void translate_browse_path_result_it__init_iter_browseResult(
   const t_entier4 translate_browse_path_result_it__p_nb_browseResult_max_refs,
   t_bool * const translate_browse_path_result_it__p_continue) {
   translate_browse_path_result_it__nb_browseResult_max_refs_i = translate_browse_path_result_it__p_nb_browseResult_max_refs;
   translate_browse_path_result_it__currentBrowseResultIdx_i = 0;
   *translate_browse_path_result_it__p_continue = (0 < translate_browse_path_result_it__p_nb_browseResult_max_refs);
}

void translate_browse_path_result_it__continue_iter_browseResult(
   t_bool * const translate_browse_path_result_it__p_continue,
   t_entier4 * const translate_browse_path_result_it__p_browseResultIdx) {
   translate_browse_path_result_it__currentBrowseResultIdx_i = translate_browse_path_result_it__currentBrowseResultIdx_i +
      1;
   *translate_browse_path_result_it__p_browseResultIdx = translate_browse_path_result_it__currentBrowseResultIdx_i;
   *translate_browse_path_result_it__p_continue = (translate_browse_path_result_it__currentBrowseResultIdx_i < translate_browse_path_result_it__nb_browseResult_max_refs_i);
}

