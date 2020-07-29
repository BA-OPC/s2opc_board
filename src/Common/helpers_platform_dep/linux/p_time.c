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

#include <assert.h>
#include <stdint.h>
#include <time.h>

#include "sopc_time.h"

#include "sopc_enums.h"

/*
 * It represents the number of seconds between the OPC-UA (Windows) which starts on 1601/01/01 (supposedly 00:00:00
 * UTC), and Linux times starts on epoch, 1970/01/01 00:00:00 UTC.
 * */
static const uint64_t SOPC_SECOND_TO_NANOSECONDS = 1000000000;   // 10^9
static const uint64_t SOPC_MILLISECOND_TO_NANOSECONDS = 1000000; // 10^6

int64_t SOPC_Time_GetCurrentTimeUTC(void)
{
    struct timespec currentTime;
    int64_t dt = 0;

    /*
     * Extract from clock_gettime documentation:
     * All implementations support the system-wide real-time clock, which is identified by CLOCK_REALTIME.  Its time
     * represents seconds and nanoseconds since the Epoch.  When its time is changed, timers for a relative interval are
     * unaffected, but timers for an absolute point in time are affected.
     * */
    if (clock_gettime(CLOCK_REALTIME, &currentTime) != 0)
    {
        return 0;
    }

    int64_t ns100 = currentTime.tv_nsec / 100;

    if ((SOPC_Time_FromTimeT(currentTime.tv_sec, &dt) != SOPC_STATUS_OK) || (INT64_MAX - ns100 < dt))
    {
        // Time overflow...
        return INT64_MAX;
    }

    dt += ns100;

    return dt;
}

SOPC_TimeReference SOPC_TimeReference_GetCurrent(void)
{
    /* Extract of clock_gettime documentation:
     *
     *   CLOCK_REALTIME
     *          System-wide  clock  that measures real (i.e., wall-clock) time.  Setting this clock requires appropriate
     * privileges.  This clock is affected by discontinuous jumps in the system time (e.g., if the system administrator
     * manually changes the clock), and by the incremental adjustments performed by adjtime(3) and NTP.
     *
     *   CLOCK_MONOTONIC
     *          Clock that cannot be set and represents monotonic time since some unspecified starting point.  This
     * clock is not affected by discontinuous jumps in the system time (e.g., if the  system administrator manually
     * changes the clock), but is affected by the incremental adjustments performed by adjtime(3) and NTP.
     *
     *   CLOCK_MONOTONIC_RAW (since Linux 2.6.28; Linux-specific)
     *          Similar to CLOCK_MONOTONIC, but provides access to a raw hardware-based time that is not subject to NTP
     * adjustments or the incremental adjustments performed by adjtime(3).
     */

    int gettimeResult;
    struct timespec currentTime;
    SOPC_TimeReference result = 0;
    uint64_t nanosecs = 0;

    gettimeResult = clock_gettime(CLOCK_MONOTONIC, &currentTime);
    if (gettimeResult != 0)
    {
        /* If the system does not support monotonic clock,
         * it is necessary to set SOPC_MONOTONIC_CLOCK to false.
         * In this latter case the real time is used which is not monotonic
         * and there is no guarantee on elapsed duration computation.
         * */
        assert(false == SOPC_MONOTONIC_CLOCK);
        gettimeResult = clock_gettime(CLOCK_REALTIME, &currentTime);
    }
    // At least realtime clock shall always be available
    assert(0 == gettimeResult);

    if (currentTime.tv_sec > 0 && UINT64_MAX / 1000 > (uint64_t) currentTime.tv_sec)
    {
        result = (uint64_t) currentTime.tv_sec * 1000; // Add seconds to results

        if (currentTime.tv_nsec > 0 && (uint64_t) currentTime.tv_nsec < SOPC_SECOND_TO_NANOSECONDS)
        {
            nanosecs = (uint64_t) currentTime.tv_nsec;
        }
        else
        {
            nanosecs = SOPC_SECOND_TO_NANOSECONDS - 1; // Use maximum nanoseconds representable (< 1 second)
        }
        // Since nanosecs < 1 second no overflow possible
        result = result + nanosecs / SOPC_MILLISECOND_TO_NANOSECONDS; // Add milliseconds to result
    }
    else
    {
        result = UINT64_MAX; // Use maximum representable value
    }

    return result;
}

SOPC_ReturnStatus SOPC_Time_Breakdown_Local(time_t t, struct tm* tm)
{
    return (localtime_r(&t, tm) == NULL) ? SOPC_STATUS_NOK : SOPC_STATUS_OK;
}

SOPC_ReturnStatus SOPC_Time_Breakdown_UTC(time_t t, struct tm* tm)
{
    return (gmtime_r(&t, tm) == NULL) ? SOPC_STATUS_NOK : SOPC_STATUS_OK;
}
