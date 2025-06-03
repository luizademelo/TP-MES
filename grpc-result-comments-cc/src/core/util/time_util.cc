Here's the commented version of the code:

```c++
// Copyright 2021 the gRPC authors.

#include "src/core/util/time_util.h"

#include <grpc/support/port_platform.h>
#include <grpc/support/time.h>
#include <stdint.h>
#include <time.h>

#include "absl/log/check.h"

namespace grpc_core {

// Converts an absl::Duration to a gpr_timespec
// Handles infinite durations and converts finite durations to seconds + nanoseconds
gpr_timespec ToGprTimeSpec(absl::Duration duration) {
  // Handle infinite future case
  if (duration == absl::InfiniteDuration()) {
    return gpr_inf_future(GPR_TIMESPAN);
  } 
  // Handle infinite past case
  else if (duration == -absl::InfiniteDuration()) {
    return gpr_inf_past(GPR_TIMESPAN);
  } 
  // Convert finite duration
  else {
    // Split duration into seconds and remaining nanoseconds
    int64_t s = absl::IDivDuration(duration, absl::Seconds(1), &duration);
    int64_t n = absl::IDivDuration(duration, absl::Nanoseconds(1), &duration);
    // Combine seconds and nanoseconds into gpr_timespec
    return gpr_time_add(gpr_time_from_seconds(s, GPR_TIMESPAN),
                        gpr_time_from_nanos(n, GPR_TIMESPAN));
  }
}

// Converts an absl::Time to a gpr_timespec
// Handles infinite time values and converts finite times to timespec format
gpr_timespec ToGprTimeSpec(absl::Time time) {
  // Handle infinite future case
  if (time == absl::InfiniteFuture()) {
    return gpr_inf_future(GPR_CLOCK_REALTIME);
  } 
  // Handle infinite past case
  else if (time == absl::InfinitePast()) {
    return gpr_inf_past(GPR_CLOCK_REALTIME);
  } 
  // Convert finite time
  else {
    // Convert to timespec format
    timespec ts = absl::ToTimespec(time);
    gpr_timespec out;
    // Copy seconds and nanoseconds components
    out.tv_sec = static_cast<decltype(out.tv_sec)>(ts.tv_sec);
    out.tv_nsec = static_cast<decltype(out.tv_nsec)>(ts.tv_nsec);
    // Set clock type to realtime
    out.clock_type = GPR_CLOCK_REALTIME;
    return out;
  }
}

// Converts a gpr_timespec to an absl::Duration
// Requires the input to be a timespan (not a specific clock type)
absl::Duration ToAbslDuration(gpr_timespec ts) {
  // Verify input is a timespan
  CHECK(ts.clock_type == GPR_TIMESPAN);
  // Handle infinite future case
  if (gpr_time_cmp(ts, gpr_inf_future(GPR_TIMESPAN)) == 0) {
    return absl::InfiniteDuration();
  } 
  // Handle infinite past case
  else if (gpr_time_cmp(ts, gpr_inf_past(GPR_TIMESPAN)) == 0) {
    return -absl::InfiniteDuration();
  } 
  // Convert finite duration
  else {
    // Combine seconds and nanoseconds into absl::Duration
    return absl::Seconds(ts.tv_sec) + absl::Nanoseconds(ts.tv_nsec);
  }
}

// Converts a gpr_timespec to an absl::Time
// Requires the input to not be a timespan (must be a clock type)
absl::Time ToAbslTime(gpr_timespec ts) {
  // Verify input is not a timespan
  CHECK(ts.clock_type != GPR_TIMESPAN);
  // Convert to realtime clock type for consistency
  gpr_timespec rts = gpr_convert_clock_type(ts, GPR_CLOCK_REALTIME);
  // Handle infinite future case
  if (gpr_time_cmp(rts, gpr_inf_future(GPR_CLOCK_REALTIME)) == 0) {
    return absl::InfiniteFuture();
  } 
  // Handle infinite past case
  else if (gpr_time_cmp(rts, gpr_inf_past(GPR_CLOCK_REALTIME)) == 0) {
    return absl::InfinitePast();
  } 
  // Convert finite time
  else {
    // Calculate time relative to Unix epoch
    return absl::UnixEpoch() + absl::Seconds(rts.tv_sec) +
           absl::Nanoseconds(rts.tv_nsec);
  }
}

}  // namespace grpc_core
```