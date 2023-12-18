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

#ifndef SOPC_P_THREADS_H_
#define SOPC_P_THREADS_H_

#include "p_sopc_synchronisation.h"

/*****Private thread api*****/

typedef struct T_THREAD_WKS tThreadWks; // Thread workspace
typedef tThreadWks* SOPC_Thread;        // Handle workspace

typedef void tPtrFct(void*);

SOPC_ReturnStatus P_THREAD_Init(SOPC_Thread* ptrWks, // Handle workspace
                                tPtrFct* fct,        // Callback
                                void* args,          // Args to pass to thread callback
                                int priority,
                                const char* taskName); // Callback debug joined, called before signal thread well ended

SOPC_ReturnStatus P_THREAD_Join(SOPC_Thread* p);

void P_THREAD_Sleep(uint32_t milliseconds);

#endif /* SOPC_P_THREADS_H_ */
