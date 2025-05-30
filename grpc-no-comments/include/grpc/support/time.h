
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

typedef enum {

  GPR_CLOCK_MONOTONIC = 0,

  GPR_CLOCK_REALTIME,

  GPR_CLOCK_PRECISE,

  GPR_TIMESPAN
} gpr_clock_type;

typedef struct gpr_timespec {
  int64_t tv_sec;
  int32_t tv_nsec;

  gpr_clock_type clock_type;
} gpr_timespec;

GPRAPI gpr_timespec gpr_time_0(gpr_clock_type type);

GPRAPI gpr_timespec gpr_inf_future(gpr_clock_type type);

GPRAPI gpr_timespec gpr_inf_past(gpr_clock_type type);

#define GPR_MS_PER_SEC 1000
#define GPR_US_PER_SEC 1000000
#define GPR_NS_PER_SEC 1000000000
#define GPR_NS_PER_MS 1000000
#define GPR_NS_PER_US 1000
#define GPR_US_PER_MS 1000

GPRAPI void gpr_time_init(void);

GPRAPI gpr_timespec gpr_now(gpr_clock_type clock);

GPRAPI gpr_timespec gpr_convert_clock_type(gpr_timespec t,
                                           gpr_clock_type clock_type);

GPRAPI int gpr_time_cmp(gpr_timespec a, gpr_timespec b);

GPRAPI gpr_timespec gpr_time_max(gpr_timespec a, gpr_timespec b);
GPRAPI gpr_timespec gpr_time_min(gpr_timespec a, gpr_timespec b);

GPRAPI gpr_timespec gpr_time_add(gpr_timespec a, gpr_timespec b);
GPRAPI gpr_timespec gpr_time_sub(gpr_timespec a, gpr_timespec b);

GPRAPI gpr_timespec gpr_time_from_micros(int64_t us, gpr_clock_type clock_type);
GPRAPI gpr_timespec gpr_time_from_nanos(int64_t ns, gpr_clock_type clock_type);
GPRAPI gpr_timespec gpr_time_from_millis(int64_t ms, gpr_clock_type clock_type);
GPRAPI gpr_timespec gpr_time_from_seconds(int64_t s, gpr_clock_type clock_type);
GPRAPI gpr_timespec gpr_time_from_minutes(int64_t m, gpr_clock_type clock_type);
GPRAPI gpr_timespec gpr_time_from_hours(int64_t h, gpr_clock_type clock_type);

GPRAPI int32_t gpr_time_to_millis(gpr_timespec timespec);

GPRAPI int gpr_time_similar(gpr_timespec a, gpr_timespec b,
                            gpr_timespec threshold);

GPRAPI void gpr_sleep_until(gpr_timespec until);

GPRAPI double gpr_timespec_to_micros(gpr_timespec t);

#ifdef __cplusplus
}
#endif

#endif
