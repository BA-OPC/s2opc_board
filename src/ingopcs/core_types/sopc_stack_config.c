/*
 *  Copyright (C) 2016 Systerel and others.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "sopc_stack_config.h"

#include <stdlib.h>
#include <string.h>
#include "p_sockets.h"
#include "sopc_types.h"

typedef struct SOPC_StackConfiguration {
    SOPC_NamespaceTable*  nsTable;
    SOPC_EncodeableType** encTypesTable;
    uint32_t              nbEncTypesTable;
} SOPC_StackConfiguration;

SOPC_StackConfiguration g_stackConfiguration;
uint8_t g_lockedConfig = FALSE;

static uint8_t initDone = FALSE;

SOPC_StatusCode StackConfiguration_Initialize(){
    SOPC_StatusCode status = STATUS_OK;
    if(initDone == FALSE){
        StackConfiguration_Clear();
        initDone = 1;
    }
    Namespace_Initialize(g_stackConfiguration.nsTable);
    status = Socket_Network_Initialize();
    InitPlatformDependencies();
    return status;
}

void StackConfiguration_Locked(){
    g_lockedConfig = 1;
}

void StackConfiguration_Unlocked(){
    g_lockedConfig = FALSE;
}

void StackConfiguration_Clear(){
    if(g_stackConfiguration.encTypesTable != NULL){
        free(g_stackConfiguration.encTypesTable);
    }
    g_stackConfiguration.nsTable = NULL;
    g_stackConfiguration.encTypesTable = NULL;
    g_stackConfiguration.nbEncTypesTable = 0;
    Socket_Network_Clear();
    StackConfiguration_Unlocked();
    initDone = FALSE;
}

SOPC_StatusCode StackConfiguration_SetNamespaceUris(SOPC_NamespaceTable* nsTable){
    SOPC_StatusCode status = STATUS_INVALID_STATE;
    if(initDone != FALSE && g_lockedConfig == FALSE){
        if(nsTable == NULL){
            status = STATUS_INVALID_PARAMETERS;
        }else{
            g_stackConfiguration.nsTable = nsTable;
        }
    }
    return status;
}

static uint32_t GetKnownEncodeableTypesLength(){
    uint32_t result = 0;
    for(result = 0; SOPC_KnownEncodeableTypes[result] != NULL; result++);
    return result + 1;
}

SOPC_StatusCode StackConfiguration_AddTypes(SOPC_EncodeableType** encTypesTable,
                                            uint32_t              nbTypes){
    SOPC_StatusCode status = STATUS_INVALID_PARAMETERS;
    uint32_t idx = 0;
    uint32_t nbKnownTypes = 0;
    SOPC_EncodeableType** additionalTypes = NULL;

    if(initDone == FALSE  || g_lockedConfig != FALSE){
        return STATUS_INVALID_STATE;
    }

    if(encTypesTable != NULL && nbTypes > 0 ){
        status = STATUS_OK;
        if(g_stackConfiguration.encTypesTable == NULL){
            // known types to be added
            nbKnownTypes = GetKnownEncodeableTypesLength();
            // +1 for null value termination
            g_stackConfiguration.encTypesTable = malloc(sizeof(SOPC_EncodeableType*) * (nbKnownTypes + nbTypes + 1));
            if(g_stackConfiguration.encTypesTable == NULL ||
               g_stackConfiguration.encTypesTable != memcpy(g_stackConfiguration.encTypesTable,
                                                            SOPC_KnownEncodeableTypes,
                                                            nbKnownTypes * sizeof(SOPC_EncodeableType*)))
            {
                g_stackConfiguration.encTypesTable = NULL;
            }else{
                additionalTypes = g_stackConfiguration.encTypesTable;
                g_stackConfiguration.nbEncTypesTable = nbKnownTypes;
            }
        }else{
            // +1 for null value termination
            additionalTypes = realloc(g_stackConfiguration.encTypesTable,
                                      sizeof(SOPC_EncodeableType*) * g_stackConfiguration.nbEncTypesTable + nbTypes + 1);
        }

        if(additionalTypes != NULL){
            g_stackConfiguration.encTypesTable = additionalTypes;

            for(idx = 0; idx < nbTypes; idx++){
                g_stackConfiguration.encTypesTable[g_stackConfiguration.nbEncTypesTable + idx] = encTypesTable[idx];
            }
            g_stackConfiguration.nbEncTypesTable += nbTypes;
            // NULL terminated table

        }else{
            status = STATUS_NOK;
        }
    }
    return status;
}

SOPC_EncodeableType** StackConfiguration_GetEncodeableTypes()
{
    if (g_stackConfiguration.encTypesTable != NULL && g_stackConfiguration.nbEncTypesTable > 0){
        // Additional types are present: contains known types + additional
        return g_stackConfiguration.encTypesTable;
    }else{
        // No additional types: return static known types
        return SOPC_KnownEncodeableTypes;
    }
}

SOPC_NamespaceTable* StackConfiguration_GetNamespaces()
{
    return g_stackConfiguration.nsTable;
}
