Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

// Include necessary headers for time handling in gRPC
#include <grpc/support/time.h>
#include <grpcpp/support/time.h>

// C++ standard library headers for chrono and integer types
#include <chrono>
#include <cstdint>

// Import commonly used chrono components to reduce verbosity
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;
using std::chrono::nanoseconds;
using std::chrono::seconds;
using std::chrono::system_clock;

namespace grpc {

// Converts a system_clock time_point to a gpr_timespec structure
// Handles special cases like maximum time point and out-of-range values
void Timepoint2Timespec(const system_clock::time_point& from,
                        gpr_timespec* to) {
  // Get duration since epoch
  system_clock::duration deadline = from.time_since_epoch();
  // Convert to seconds for comparison
  seconds secs = duration_cast<seconds>(deadline);
  
  // Handle special cases:
  // 1. Maximum time point
  // 2. Future time beyond gRPC's representation
  // 3. Negative time (before epoch)
  if (from == system_clock::time_point::max() ||
      secs.count() >= gpr_inf_future(GPR_CLOCK_REALTIME).tv_sec ||
      secs.count() < 0) {
    *to = gpr_inf_future(GPR_CLOCK_REALTIME);
    return;
  }
  
  // Calculate remaining nanoseconds after whole seconds
  nanoseconds nsecs = duration_cast<nanoseconds>(deadline - secs);
  // Populate the output timespec structure
  to->tv_sec = static_cast<int64_t>(secs.count());
  to->tv_nsec = static_cast<int32_t>(nsecs.count());
  to->clock_type = GPR_CLOCK_REALTIME;
}

// Similar to Timepoint2Timespec but uses high_resolution_clock as input
// Converts a high_resolution_clock time_point to a gpr_timespec structure
void TimepointHR2Timespec(const high_resolution_clock::time_point& from,
                          gpr_timespec* to) {
  // Get duration since epoch
  high_resolution_clock::duration deadline = from.time_since_epoch();
  // Convert to seconds for comparison
  seconds secs = duration_cast<seconds>(deadline);
  
  // Handle special cases (same as Timepoint2Timespec)
  if (from == high_resolution_clock::time_point::max() ||
      secs.count() >= gpr_inf_future(GPR_CLOCK_REALTIME).tv_sec ||
      secs.count() < 0) {
    *to = gpr_inf_future(GPR_CLOCK_REALTIME);
    return;
  }
  
  // Calculate remaining nanoseconds after whole seconds
  nanoseconds nsecs = duration_cast<nanoseconds>(deadline - secs);
  // Populate the output timespec structure
  to->tv_sec = static_cast<int64_t>(secs.count());
  to->tv_nsec = static_cast<int32_t>(nsecs.count());
  to->clock_type = GPR_CLOCK_REALTIME;
}

// Converts a gpr_timespec to a system_clock time_point
system_clock::time_point Timespec2Timepoint(gpr_timespec t) {
  // Handle infinite future case
  if (gpr_time_cmp(t, gpr_inf_future(t.clock_type)) == 0) {
    return system_clock::time_point::max();
  }
  
  // Convert to REALTIME clock if necessary
  t = gpr_convert_clock_type(t, GPR_CLOCK_REALTIME);
  
  // Construct time_point by adding seconds and nanoseconds components
  system_clock::time_point tp;
  tp += duration_cast<system_clock::time_point::duration>(seconds(t.tv_sec));
  tp +=
      duration_cast<system_clock::time_point::duration>(nanoseconds(t.tv_nsec));
  return tp;
}

}  // namespace grpc
```

The comments explain:
1. The purpose of each function
2. The handling of special cases (like max time and infinite future)
3. The conversion logic between different time representations
4. The breakdown of time components (seconds and nanoseconds)
5. The clock type handling
6. The flow of each function

The comments are designed to help future maintainers understand:
- Why certain conversions are needed
- How edge cases are handled
- The relationship between C++ chrono types and gRPC's time representations
- The structure of the conversion process