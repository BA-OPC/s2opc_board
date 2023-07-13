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

#ifdef __MINGW32__
#include <winsock2.h>
#endif

#include <windows.h>

typedef CRITICAL_SECTION Mutex;

typedef CONDITION_VARIABLE Condition;

typedef void* SOPCThreadStartFct(void*);

typedef struct SOPC_Thread
{
    HANDLE thread;
    SOPCThreadStartFct* startFct;
    void* args;
} SOPC_Thread;

#endif /* SOPC_P_THREADS_H_ */
