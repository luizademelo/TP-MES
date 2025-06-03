Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

#include <grpc/support/port_platform.h>
#include "src/core/util/time_precise.h"

#ifdef GPR_POSIX_TIME

#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#ifdef __linux__
#include <sys/syscall.h>
#endif
#include <grpc/support/atm.h>
#include <grpc/support/time.h>

#include "absl/log/check.h"

// Converts gRPC timespec (gpr_timespec) to POSIX timespec (struct timespec)
// Performs bounds checking when time_t is smaller than int64_t
static struct timespec timespec_from_gpr(gpr_timespec gts) {
  struct timespec rv;
  if (sizeof(time_t) < sizeof(int64_t)) {
    // Ensure the seconds value fits in time_t
    CHECK(gts.tv_sec <= INT32_MAX);
    CHECK(gts.tv_sec >= INT32_MIN);
  }
  rv.tv_sec = static_cast<time_t>(gts.tv_sec);
  rv.tv_nsec = gts.tv_nsec;
  return rv;
}

// Converts POSIX timespec (struct timespec) to gRPC timespec (gpr_timespec)
// Sets the clock type in the output structure
static gpr_timespec gpr_from_timespec(struct timespec ts,
                                      gpr_clock_type clock_type) {
  gpr_timespec rv;
  rv.tv_sec = ts.tv_sec;
  rv.tv_nsec = static_cast<int32_t>(ts.tv_nsec);
  rv.clock_type = clock_type;
  return rv;
}

// Mapping of gRPC clock types to POSIX clock IDs
static const clockid_t clockid_for_gpr_clock[] = {CLOCK_MONOTONIC,
                                                  CLOCK_REALTIME};

// Initializes precise clock functionality
void gpr_time_init(void) { gpr_precise_clock_init(); }

// Internal implementation of getting current time
// Handles both precise and system clock types
static gpr_timespec now_impl(gpr_clock_type clock_type) {
  struct timespec now;
  CHECK(clock_type != GPR_TIMESPAN);
  
  if (clock_type == GPR_CLOCK_PRECISE) {
    // Use the precise clock implementation
    gpr_timespec ret;
    gpr_precise_clock_now(&ret);
    return ret;
  } else {
    // Use system clock (either monotonic or realtime)
    clock_gettime(clockid_for_gpr_clock[clock_type], &now);
    if (clock_type == GPR_CLOCK_MONOTONIC) {
      // Add 5 seconds to monotonic clock (implementation-specific adjustment)
      now.tv_sec += 5;
    }
    return gpr_from_timespec(now, clock_type);
  }
}

// Function pointer for time retrieval implementation
gpr_timespec (*gpr_now_impl)(gpr_clock_type clock_type) = now_impl;

// Public interface for getting current time
// Validates clock type and returned time values
gpr_timespec gpr_now(gpr_clock_type clock_type) {
  // Verify valid clock type
  CHECK(clock_type == GPR_CLOCK_MONOTONIC || clock_type == GPR_CLOCK_REALTIME ||
        clock_type == GPR_CLOCK_PRECISE);
  
  gpr_timespec ts = gpr_now_impl(clock_type);

  // Validate nanoseconds are in proper range
  CHECK(ts.tv_nsec >= 0);
  CHECK(ts.tv_nsec < 1e9);
  return ts;
}

// Sleeps until the specified time is reached
// Uses nanosleep in a loop to handle potential interruptions
void gpr_sleep_until(gpr_timespec until) {
  gpr_timespec now;
  gpr_timespec delta;
  struct timespec delta_ts;
  int ns_result;

  for (;;) {
    // Get current time and check if we've reached the target
    now = gpr_now(until.clock_type);
    if (gpr_time_cmp(until, now) <= 0) {
      return;
    }

    // Calculate remaining time and sleep
    delta = gpr_time_sub(until, now);
    delta_ts = timespec_from_gpr(delta);
    ns_result = nanosleep(&delta_ts, nullptr);
    
    // Exit loop if sleep completed successfully
    if (ns_result == 0) {
      break;
    }
    // Otherwise, loop will continue and try again
  }
}

#endif
```

Key improvements in the comments:
1. Added clear descriptions of each function's purpose
2. Explained the logic flow in complex functions
3. Noted implementation-specific details (like the +5 seconds for monotonic clock)
4. Documented the validation checks being performed
5. Explained the loop behavior in gpr_sleep_until
6. Added context for the clock type mapping array
7. Clarified the difference between precise and system clock handling

The comments are now more comprehensive while remaining concise and focused on explaining the why behind the code, not just what it does.