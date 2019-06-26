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

#include <inttypes.h> /* stdlib includes */
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "FreeRTOS.h" /* freeRtos includes */
#include "queue.h"
#include "semphr.h"
#include "task.h"
#include "timers.h"

#include "sopc_enums.h" /* s2opc includes */

#include "p_synchronisation.h" /* synchronisation include */
#include "p_utils.h"           /* private list include */

/*****Private condition variable api*****/

// Clear condition variable: release all thread waiting on it
SOPC_ReturnStatus P_SYNCHRO_ClearConditionVariable(Condition* pConditionVariable)
{
    SOPC_ReturnStatus result = SOPC_STATUS_OK;
    uint16_t wCurrentSlotId = UINT16_MAX;
    TaskHandle_t handle = NULL;
    uint32_t wClearSignal = 0;

    if (pConditionVariable != NULL)
    {
        if ((E_COND_VAR_STATUS_INITIALIZED == pConditionVariable->status) // Workspace initialized
            && (NULL != pConditionVariable->handleLockCounter))           // Critical section token exist
        {
            xSemaphoreTake(pConditionVariable->handleLockCounter, portMAX_DELAY); // Critical section
            {
                pConditionVariable->status = E_COND_VAR_STATUS_NOT_INITIALIZED; // Mark as not initialized

                // Indicate for each registered task that clearing signal is pending
                wCurrentSlotId = UINT16_MAX;
                do
                {
                    handle = (TaskHandle_t) P_UTILS_LIST_ParseValueElt(&pConditionVariable->taskList, //
                                                                       NULL,                          //
                                                                       &wClearSignal,                 //
                                                                       NULL,                          //
                                                                       &wCurrentSlotId);              //
                    if (handle != NULL)
                    {
                        xTaskGenericNotify(handle, wClearSignal, eSetBits, NULL);
                    }
                } while (wCurrentSlotId != UINT16_MAX);

                // Task list destruction
                P_UTILS_LIST_DeInit(&pConditionVariable->taskList);
            }

            vQueueDelete(pConditionVariable->handleLockCounter); // End of critical section. Destroy it on clear
            pConditionVariable->handleLockCounter = NULL;
            DEBUG_decrementCpt();
            memset(pConditionVariable, 0, sizeof(Condition)); // Raz on leave memory
        }
        else
        {
            result = SOPC_STATUS_INVALID_STATE;
        }
    }
    else
    {
        result = SOPC_STATUS_INVALID_PARAMETERS;
    }
    return result;
}

// Initialize condition variable
SOPC_ReturnStatus P_SYNCHRO_InitConditionVariable(Condition* pConditionVariable, // Condition variable handle
                                                  uint16_t wMaxWaiters)          // max parallel waiting tasks
{
    SOPC_ReturnStatus result = SOPC_STATUS_OK;
    QueueHandle_t pMutex = NULL;

    if ((MAX_WAITERS < wMaxWaiters) || (NULL == pConditionVariable))
    {
        result = SOPC_STATUS_INVALID_PARAMETERS;
    }
    else
    {
        if (E_COND_VAR_STATUS_NOT_INITIALIZED == pConditionVariable->status) // Check if workspace already exists
        {
            // Raz allocated workspaace
            memset(pConditionVariable, 0, sizeof(Condition));
            pMutex = xQueueCreateMutex(queueQUEUE_TYPE_MUTEX);
            if (pMutex != NULL)
            {
                DEBUG_incrementCpt();
                // Allocate list of waiters
                P_UTILS_LIST_Init(&pConditionVariable->taskList, wMaxWaiters);
                if (pConditionVariable->taskList.list == NULL)
                {
                    vQueueDelete(pMutex);
                    pMutex = NULL;

                    // Raz leaved memory
                    memset(pConditionVariable, 0, sizeof(Condition));
                    DEBUG_decrementCpt();
                    result = SOPC_STATUS_OUT_OF_MEMORY;
                }
                else
                {
                    pConditionVariable->handleLockCounter = pMutex;
                    pConditionVariable->status = E_COND_VAR_STATUS_INITIALIZED;
                    result = SOPC_STATUS_OK;
                }
            }
            else
            {
                /* Raz leaved memory*/
                memset(pConditionVariable, 0, sizeof(Condition));
                result = SOPC_STATUS_OUT_OF_MEMORY;
            }
        }
        else
        {
            result = SOPC_STATUS_INVALID_STATE;
        }
    }
    return result;
}

// Destruction of condition variable if created via CreateConditionVariable.
void P_SYNCHRO_DestroyConditionVariable(Condition** ppConditionVariable)
{
    if ((ppConditionVariable != NULL) && ((*ppConditionVariable) != NULL))
    {
        P_SYNCHRO_ClearConditionVariable(*ppConditionVariable);
        memset(*ppConditionVariable, 0, sizeof(Condition));
        vPortFree(*ppConditionVariable);
        *ppConditionVariable = NULL;
        DEBUG_decrementCpt();
    }
}

// Creation workspace.
Condition* P_SYNCHRO_CreateConditionVariable(uint16_t wMaxRDV)
{
    Condition* pConditionVariable = NULL;
    pConditionVariable = (Condition*) pvPortMalloc(sizeof(Condition));
    if (pConditionVariable != NULL)
    {
        DEBUG_incrementCpt();
        // Raz handle
        memset(pConditionVariable, 0, sizeof(Condition));
        if (P_SYNCHRO_InitConditionVariable(pConditionVariable, wMaxRDV) != SOPC_STATUS_OK)
        {
            P_SYNCHRO_ClearConditionVariable(pConditionVariable);
            // Raz handle
            memset(pConditionVariable, 0, sizeof(Condition));
            vPortFree(pConditionVariable);
            pConditionVariable = NULL;
            DEBUG_decrementCpt();
        }
    }
    return pConditionVariable;
}

SOPC_ReturnStatus P_SYNCHRO_SignalConditionVariable(Condition* pConditionVariable) // Signal to one
{
    SOPC_ReturnStatus result = SOPC_STATUS_INVALID_STATE;
    uint16_t wCurrentSlotId = USHRT_MAX;
    TaskHandle_t handle = NULL;
    uint32_t signal = 0;

    if (pConditionVariable != NULL)
    {
        if ((E_COND_VAR_STATUS_INITIALIZED == pConditionVariable->status) //
            && (NULL != pConditionVariable->handleLockCounter))           //
        {
            xQueueSemaphoreTake(pConditionVariable->handleLockCounter, portMAX_DELAY); // Critical section
            {
                wCurrentSlotId = USHRT_MAX;

                handle = (TaskHandle_t) P_UTILS_LIST_ParseValueElt(&pConditionVariable->taskList, // List of task
                                                                   &signal,                       // Signal to send
                                                                   NULL,                          //
                                                                   NULL,                          //
                                                                   &wCurrentSlotId);              // Slot id
                if (handle != NULL)
                {
                    xTaskGenericNotify(handle, signal, eSetBits, NULL);
                    result = SOPC_STATUS_OK;
                }
            }
            xSemaphoreGive(pConditionVariable->handleLockCounter); // End critical section
        }
        else
        {
            result = SOPC_STATUS_INVALID_STATE;
        }
    }
    else
    {
        result = SOPC_STATUS_INVALID_PARAMETERS;
    }
    return result;
}

// Broadcast signal to all waiting task on signal passed in parameters
SOPC_ReturnStatus P_SYNCHRO_SignalAllConditionVariable(Condition* pConditionVariable) // Signal to broadcaset
{
    SOPC_ReturnStatus result = SOPC_STATUS_INVALID_STATE;
    uint16_t wCurrentSlotId = UINT16_MAX;
    TaskHandle_t handle = NULL;
    uint32_t signal = 0;

    if (NULL != pConditionVariable)
    {
        if ((E_COND_VAR_STATUS_INITIALIZED == pConditionVariable->status) &&
            (NULL != pConditionVariable->handleLockCounter))
        {
            xQueueSemaphoreTake(pConditionVariable->handleLockCounter, portMAX_DELAY); // Critical section
            {
                wCurrentSlotId = UINT16_MAX;
                do
                {
                    handle = (TaskHandle_t) P_UTILS_LIST_ParseValueElt(
                        &pConditionVariable->taskList, // Task of list to notify
                        &signal,                       // signal to send
                        NULL,                          //
                        NULL,                          //
                        &wCurrentSlotId);              // Slot id
                    if (handle != NULL)
                    {
                        xTaskGenericNotify(handle, signal, eSetBits, NULL);
                        result = SOPC_STATUS_OK;
                    }
                } while (wCurrentSlotId != UINT16_MAX);
            }
            xSemaphoreGive(pConditionVariable->handleLockCounter); // End critical section
        }
        else
        {
            result = SOPC_STATUS_INVALID_STATE;
        }
    }
    else
    {
        result = SOPC_STATUS_INVALID_PARAMETERS;
    }
    return result;
}

// Used by P_SYNCHRO_UnlockAndWaitForConditionVariable
static inline SOPC_ReturnStatus _P_SYNCHRO_WaitSignal(uint32_t* pNotificationValue, // Notif received
                                                      uint32_t uwSignal,            // Signal waited
                                                      uint32_t uwClearSignal,       // Clear signal
                                                      TickType_t xTimeToWait)       // TimeOut
{
    SOPC_ReturnStatus result = SOPC_STATUS_OK;
    uint32_t notificationValue = 0;
    uint8_t bQuit = 0;
    TimeOut_t xTimeOut = {0, 0};

    if (NULL == pNotificationValue)
    {
        result = SOPC_STATUS_NOK;
    }
    else
    {
        while (0 == bQuit)
        {
            vTaskSetTimeOutState(&xTimeOut); // RAZ timeout
            // Wait for specified signal bit 0 -> 30. Bit 31 = CLEARING_SIGNAL
            if (pdPASS != xTaskNotifyWait(0,                        //
                                          uwSignal | uwClearSignal, //
                                          &notificationValue,       //
                                          xTimeToWait))             //
            {
                result = SOPC_STATUS_TIMEOUT;
                // TimeOut
                bQuit = 1;
            }
            else
            {
                // If others notifications, forward it in order to generate a task event
                if (0 != (notificationValue & (~(uwSignal | uwClearSignal))))
                {
                    xTaskGenericNotify(xTaskGetCurrentTaskHandle(),                       //
                                       notificationValue & (~(uwSignal | uwClearSignal)), //
                                       eSetBits,                                          //
                                       NULL);                                             //
                }
                // Verify if notification arrived
                if (uwClearSignal == (notificationValue & uwClearSignal))
                {
                    // Clearing on going
                    result = SOPC_STATUS_INVALID_STATE;
                    bQuit = 1;
                }
                else if (uwSignal != (notificationValue & uwSignal))
                {
                    // Update timeout status
                    if (pdTRUE == xTaskCheckForTimeOut(&xTimeOut, &xTimeToWait))
                    {
                        // Timeout occurred
                        result = SOPC_STATUS_TIMEOUT;
                        bQuit = 1;
                    }
                }
                else
                {
                    // Waited signal received. Quit waiting loop with E_COND_VAR_RESULT_OK
                    bQuit = 1;
                }
            }
        }

        *pNotificationValue = notificationValue;
    }

    return result;
}

// Unlock recursive mutex in parameters before wait a signal.
// Mutex in parameter is optional. In this case, simple wait signal.
// On timeout, task is removed from task to notify.
SOPC_ReturnStatus P_SYNCHRO_UnlockAndWaitForConditionVariable(
    Condition* pConditionVariable, // Condition variable workspace
    QueueHandle_t* pMutex,         // Recursive mutex
    uint32_t uwSignal,             // Signal to wait
    uint32_t uwClearSignal,        // Clear signal
    uint32_t uwTimeOutMs)          // TimeOut
{
    SOPC_ReturnStatus result = SOPC_STATUS_INVALID_PARAMETERS;
    SOPC_ReturnStatus status = SOPC_STATUS_NOK;
    TickType_t xTimeToWait = 0;
    TaskHandle_t handleTask = 0;
    uint32_t notificationValue = 0;

    if (pConditionVariable != NULL)
    {
        if (uwTimeOutMs >= (portMAX_DELAY / (configTICK_RATE_HZ * ((uint32_t) 1000))))
        {
            xTimeToWait = portMAX_DELAY;
        }
        else
        {
            xTimeToWait = pdMS_TO_TICKS(uwTimeOutMs);
        }

        if (                                                              // Check workspace exists
            (E_COND_VAR_STATUS_INITIALIZED == pConditionVariable->status) // Check workspace initialization
            && (NULL != pConditionVariable->handleLockCounter))           // Check sem existence
        {
            // Critical section
            xQueueSemaphoreTake(pConditionVariable->handleLockCounter, portMAX_DELAY);
            {
                handleTask = xTaskGetCurrentTaskHandle();

                status = P_UTILS_LIST_AddElt(&pConditionVariable->taskList, // Task waiting
                                             handleTask,                    // Current task
                                             NULL,                          // No context
                                             uwSignal,                      // Signal
                                             uwClearSignal);                // Clear signal

                if (SOPC_STATUS_OK != status)
                {
                    result = SOPC_STATUS_INVALID_STATE;
                }
                else
                {
                    result = SOPC_STATUS_OK;
                }
            }
            xSemaphoreGive(pConditionVariable->handleLockCounter);
        }
        else
        {
            notificationValue = uwClearSignal;
            result = SOPC_STATUS_INVALID_STATE;
        }

        // Give mutex from parameters
        if ((NULL != pMutex)&& (NULL != (*pMutex)))
        {
            xQueueGiveMutexRecursive(*pMutex);
        }

        if (SOPC_STATUS_OK == result)
        {
            // Wait signal or timeout
            // If signal or timeout, in both case, unstack signal
            // (we signal to the waiting task that nb of waiting task is decremented)

            result = _P_SYNCHRO_WaitSignal(&notificationValue, // Notif
                                           uwSignal,           // Signal waited
                                           uwClearSignal,      // Clear signal
                                           xTimeToWait);       // Tick timeout

            // Critical section

            if ((uwClearSignal != (notificationValue & uwClearSignal))           // Not a clear signal
                && (E_COND_VAR_STATUS_INITIALIZED == pConditionVariable->status) // Workspace initilized
                && (NULL != pConditionVariable->handleLockCounter))              // Lock exists
            {
                xQueueSemaphoreTake(pConditionVariable->handleLockCounter, portMAX_DELAY); // Critical section
                {
                    P_UTILS_LIST_RemoveElt(&pConditionVariable->taskList, //
                                           handleTask,                    //
                                           uwSignal,                      //
                                           uwClearSignal,                 //
                                           NULL);                         //
                }
                xSemaphoreGive(pConditionVariable->handleLockCounter);

                result = SOPC_STATUS_OK;
            }
            else
            {
                result = SOPC_STATUS_INVALID_STATE;
            }
        }

        // Take mutex in parameter if exists
        if ((NULL != pMutex)&& (NULL != (*pMutex)))
        {
            xQueueTakeMutexRecursive(*pMutex, portMAX_DELAY);
        }
    }
    else
    {
        result = SOPC_STATUS_INVALID_PARAMETERS;
    }

    return result;
}

/*****Public s2opc condition variable and mutex api*****/

SOPC_ReturnStatus Condition_Init(Condition* cond)
{
    SOPC_ReturnStatus resSOPC = SOPC_STATUS_OK;
    Condition* ptr = (Condition*) cond;

    if (ptr != NULL)
    {
        resSOPC = P_SYNCHRO_InitConditionVariable(ptr, MAX_P_UTILS_LIST);
    }
    else
    {
        resSOPC = SOPC_STATUS_INVALID_PARAMETERS;
    }
    return resSOPC;
}

/*Destroy a condition variable.*/
SOPC_ReturnStatus Condition_Clear(Condition* cond)
{
    SOPC_ReturnStatus resSOPC = SOPC_STATUS_OK;
    Condition* ptrCond = (Condition*) cond;
    if (ptrCond != NULL)
    {
        resSOPC = P_SYNCHRO_ClearConditionVariable(ptrCond);
    }
    else
    {
        resSOPC = SOPC_STATUS_INVALID_PARAMETERS;
    }
    return resSOPC;
}

SOPC_ReturnStatus Condition_SignalAll(Condition* cond)
{
    SOPC_ReturnStatus resSOPC = SOPC_STATUS_OK;
    Condition* ptrCond = (Condition*) cond;
    if (ptrCond != NULL)
    {
        resSOPC = P_SYNCHRO_SignalAllConditionVariable(ptrCond);
    }
    else
    {
        resSOPC = SOPC_STATUS_INVALID_PARAMETERS;
    }
    return resSOPC;
}

// Must be called between lock and unlock of Mutex used to wait on condition
SOPC_ReturnStatus Mutex_UnlockAndTimedWaitCond(Condition* cond, Mutex* mut, uint32_t milliSecs)
{
    SOPC_ReturnStatus resSOPC = SOPC_STATUS_INVALID_PARAMETERS;
    Condition* ptrCond = (Condition*) cond;
    QueueHandle_t* pFreeRtosMutex = mut;

    if (ptrCond != NULL)
    {
        if (mut != NULL)
        {
            pFreeRtosMutex = ((QueueHandle_t*) mut);
        }

        resSOPC = P_SYNCHRO_UnlockAndWaitForConditionVariable(ptrCond,             //
                                                              pFreeRtosMutex,      //
                                                              APP_DEFAULT_SIGNAL,  //
                                                              APP_CLEARING_SIGNAL, //
                                                              milliSecs);          //
    }
    else
    {
        resSOPC = SOPC_STATUS_INVALID_PARAMETERS;
    }

    return resSOPC;
}

// Must be called between lock and unlock of Mutex used to wait on condition
SOPC_ReturnStatus Mutex_UnlockAndWaitCond(Condition* cond, Mutex* mut)
{
    SOPC_ReturnStatus resSOPC = SOPC_STATUS_INVALID_PARAMETERS;

    resSOPC = Mutex_UnlockAndTimedWaitCond(cond, mut, UINT32_MAX);

    return resSOPC;
}

/*Create recursive mutex*/
SOPC_ReturnStatus Mutex_Initialization(Mutex* mut)
{
    SOPC_ReturnStatus result = SOPC_STATUS_OK;
    QueueHandle_t freeRtosMutex = NULL;

    if (mut == NULL)
    {
        result = SOPC_STATUS_INVALID_PARAMETERS;
    }
    else
    {
        freeRtosMutex = xSemaphoreCreateRecursiveMutex();
        if (freeRtosMutex == NULL)
        {
            result = SOPC_STATUS_OUT_OF_MEMORY;
            *mut = NULL;
        }
        else
        {
            result = SOPC_STATUS_OK;
            *mut = (Mutex) freeRtosMutex;
        }
    }
    return result;
}

/*Destroy recursive mutex*/
SOPC_ReturnStatus Mutex_Clear(Mutex* mut)
{
    QueueHandle_t handleRecursiveMutex = NULL;
    SOPC_ReturnStatus result = SOPC_STATUS_OK;

    if (mut == NULL)
    {
        result = SOPC_STATUS_INVALID_PARAMETERS;
    }
    else
    {
        handleRecursiveMutex = *((QueueHandle_t*) (mut));
        if (handleRecursiveMutex == NULL)
        {
            result = SOPC_STATUS_INVALID_PARAMETERS;
        }
        else
        {
            vSemaphoreDelete(handleRecursiveMutex);
            result = SOPC_STATUS_OK;
        }
    }
    return result;
}

// Lock recursive mutex
SOPC_ReturnStatus Mutex_Lock(Mutex* mut)
{
    SOPC_ReturnStatus result = SOPC_STATUS_OK;
    QueueHandle_t freeRtosMutex = NULL;
    if (mut == NULL)
    {
        result = SOPC_STATUS_INVALID_PARAMETERS;
    }
    else
    {
        freeRtosMutex = *((QueueHandle_t*) (mut));
        if (freeRtosMutex == NULL)
        {
            result = SOPC_STATUS_INVALID_PARAMETERS;
        }
        else
        {
            if (xQueueTakeMutexRecursive(freeRtosMutex, portMAX_DELAY) == pdPASS)
            {
                result = SOPC_STATUS_OK;
            }
            else
            {
                result = SOPC_STATUS_NOK;
            }
        }
    }
    return result;
}

// Unlock recursive mutex
SOPC_ReturnStatus Mutex_Unlock(Mutex* mut)
{
    QueueHandle_t freeRtosMutex = NULL;
    SOPC_ReturnStatus result = SOPC_STATUS_OK;
    if (mut == NULL)
    {
        result = SOPC_STATUS_INVALID_PARAMETERS;
    }
    else
    {
        freeRtosMutex = *((QueueHandle_t*) (mut));
        if (freeRtosMutex == NULL)
        {
            result = SOPC_STATUS_INVALID_PARAMETERS;
        }
        else
        {
            if (xQueueGiveMutexRecursive(freeRtosMutex) == pdPASS)
            {
                result = SOPC_STATUS_OK;
            }
            else
            {
                result = SOPC_STATUS_NOK;
            }
        }
    }
    return result;
}
