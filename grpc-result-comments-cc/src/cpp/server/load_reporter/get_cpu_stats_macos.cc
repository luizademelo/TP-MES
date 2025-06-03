Here's the commented version of the code:

```c++
// Copyright 2018 gRPC authors.

// Platform-specific header for portability
#include <grpc/support/port_platform.h>

// Only compile this code for Apple platforms
#ifdef GPR_APPLE

// Include necessary Apple-specific headers for CPU statistics
#include <mach/mach.h>
// Include the header for CPU stats functionality
#include "src/cpp/server/load_reporter/get_cpu_stats.h"

namespace grpc {
namespace load_reporter {

// Returns a pair of CPU usage statistics: (busy_ticks, total_ticks)
// This implementation is specific to Apple platforms (macOS/iOS)
std::pair<uint64_t, uint64_t> GetCpuStatsImpl() {
  // Initialize counters for busy and total CPU ticks
  uint64_t busy = 0, total = 0;
  // Structure to hold CPU load information
  host_cpu_load_info_data_t cpuinfo;
  // Number of elements in the cpuinfo structure
  mach_msg_type_number_t count = HOST_CPU_LOAD_INFO_COUNT;
  
  // Retrieve CPU statistics from the Mach kernel
  if (host_statistics(mach_host_self(), HOST_CPU_LOAD_INFO,
                      (host_info_t)&cpuinfo, &count) == KERN_SUCCESS) {
    // Calculate total ticks by summing all CPU states
    for (int i = 0; i < CPU_STATE_MAX; i++) {
      total += cpuinfo.cpu_ticks[i];
    }
    // Calculate busy ticks as total minus idle ticks
    busy = total - cpuinfo.cpu_ticks[CPU_STATE_IDLE];
  }
  // Return the pair of (busy_ticks, total_ticks)
  return std::pair(busy, total);
}

}  // namespace load_reporter
}  // namespace grpc

#endif  // GPR_APPLE
```

Key improvements in the comments:
1. Added explanation of the function's purpose and return value
2. Documented platform-specific nature of the implementation
3. Explained the significance of each variable
4. Clarified the Mach kernel API usage
5. Added comments for the calculation logic
6. Added namespace closing comments
7. Improved the preprocessor directive comment
8. Explained the busy ticks calculation

The comments now provide a clear understanding of what the code does, how it works, and its platform-specific nature, which will be helpful for future maintenance.