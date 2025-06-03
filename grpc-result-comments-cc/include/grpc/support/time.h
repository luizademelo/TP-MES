Here's the commented version of the code:

```c++
/*
 *
 * Copyright 2015 gRPC authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef GRPC_SUPPORT_TIME_H
#define GRPC_SUPPORT_TIME_H

#include <grpc/support/port_platform.h>
#include <stddef.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Enum representing different types of clocks/time sources */
typedef enum {
  /* Monotonic clock that cannot be set and represents monotonic time since some unspecified starting point */
  GPR_CLOCK_MONOTONIC = 0,
  
  /* System real-time clock which may be set */
  GPR_CLOCK_REALTIME,
  
  /* Most precise clock available on the system */
  GPR_CLOCK_PRECISE,
  
  /* Represents a time interval (not an absolute time) */
  GPR_TIMESPAN
} gpr_clock_type;

/* Structure representing time with nanosecond precision */
typedef struct gpr_timespec {
  int64_t tv_sec;        /* Seconds component of the time */
  int32_t tv_nsec;       /* Nanoseconds component of the time (0-999,999,999) */
  gpr_clock_type clock_type; /* Type of clock this timespec represents */
} gpr_timespec;

/* Returns a zero/initialized timespec for the given clock type */
GPRAPI gpr_timespec gpr_time_0(gpr_clock_type type);

/* Returns a timespec representing infinite future for the given clock type */
GPRAPI gpr_timespec gpr_inf_future(gpr_clock_type type);

/* Returns a timespec representing infinite past for the given clock type */
GPRAPI gpr_timespec gpr_inf_past(gpr_clock_type type);

/* Time conversion constants */
#define GPR_MS_PER_SEC 1000        /* Milliseconds per second */
#define GPR_US_PER_SEC 1000000     /* Microseconds per second */
#define GPR_NS_PER_SEC 1000000000  /* Nanoseconds per second */
#define GPR_NS_PER_MS 1000000      /* Nanoseconds per millisecond */
#define GPR_NS_PER_US 1000         /* Nanoseconds per microsecond */
#define GPR_US_PER_MS 1000         /* Microseconds per millisecond */

/* Initialize the time system (if needed) */
GPRAPI void gpr_time_init(void);

/* Get the current time from the specified clock source */
GPRAPI gpr_timespec gpr_now(gpr_clock_type clock);

/* Convert a timespec from one clock type to another */
GPRAPI gpr_timespec gpr_convert_clock_type(gpr_timespec t,
                                           gpr_clock_type clock_type);

/* Compare two timespecs: returns -1 if a < b, 0 if a == b, 1 if a > b */
GPRAPI int gpr_time_cmp(gpr_timespec a, gpr_timespec b);

/* Returns the later of two timespecs */
GPRAPI gpr_timespec gpr_time_max(gpr_timespec a, gpr_timespec b);
/* Returns the earlier of two timespecs */
GPRAPI gpr_timespec gpr_time_min(gpr_timespec a, gpr_timespec b);

/* Add two timespecs (b is treated as timespan) */
GPRAPI gpr_timespec gpr_time_add(gpr_timespec a, gpr_timespec b);
/* Subtract two timespecs (b is treated as timespan) */
GPRAPI gpr_timespec gpr_time_sub(gpr_timespec a, gpr_timespec b);

/* Create timespec from various time units */
GPRAPI gpr_timespec gpr_time_from_micros(int64_t us, gpr_clock_type clock_type);
GPRAPI gpr_timespec gpr_time_from_nanos(int64_t ns, gpr_clock_type clock_type);
GPRAPI gpr_timespec gpr_time_from_millis(int64_t ms, gpr_clock_type clock_type);
GPRAPI gpr_timespec gpr_time_from_seconds(int64_t s, gpr_clock_type clock_type);
GPRAPI gpr_timespec gpr_time_from_minutes(int64_t m, gpr_clock_type clock_type);
GPRAPI gpr_timespec gpr_time_from_hours(int64_t h, gpr_clock_type clock_type);

/* Convert timespec to milliseconds */
GPRAPI int32_t gpr_time_to_millis(gpr_timespec timespec);

/* Check if two timespecs are within threshold of each other */
GPRAPI int gpr_time_similar(gpr_timespec a, gpr_timespec b,
                            gpr_timespec threshold);

/* Sleep until the specified time */
GPRAPI void gpr_sleep_until(gpr_timespec until);

/* Convert timespec to microseconds as floating point */
GPRAPI double gpr_timespec_to_micros(gpr_timespec t);

#ifdef __cplusplus
}
#endif

#endif
```