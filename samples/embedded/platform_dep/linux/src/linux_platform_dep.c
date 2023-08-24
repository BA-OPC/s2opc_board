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

/** \file samples_platform_dep.c
 *
 * \brief Provides the implementation for LINUX of OS-dependant features required for samples
 */

#include "samples_platform_dep.h"

#include <stdio.h>

#include "sopc_assert.h"
#include "sopc_macros.h"

/***************************************************/
void SOPC_Platform_Setup(void)
{
    // Nothing to be done
}

/***************************************************/
void SOPC_Platform_Shutdown(const bool reboot)
{
    SOPC_UNUSED_ARG(reboot);
    // Nothing to be done. Do not apply reboot on linux
}

/***************************************************/
char* SOPC_Shell_ReadLine(void)
{
    char* line = NULL;
    size_t len = 0;
    ssize_t result = getline(&line, &len, stdin);

    // Remove EOL chars
    while (-1 != result && NULL != line && len > 0 && line[len - 1] < ' ')
    {
        len--;
        line[len] = 0;
    }
    return line;
}

/***************************************************/
const char* SOPC_Platform_Get_Default_Net_Itf(void)
{
    return "";
}

/***************************************************/
void SOPC_Platform_Target_Debug(const char* param)
{
    SOPC_UNUSED_ARG(param);
    // Nothing required
}

/***************************************************/
int main(int argc, char* const argv[])
{
    SOPC_UNUSED_ARG(argc);
    SOPC_UNUSED_ARG(argv);
    SOPC_Platform_Main();
}
