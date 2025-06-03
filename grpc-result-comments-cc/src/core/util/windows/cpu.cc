Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

// Platform-specific header inclusion
#include <grpc/support/port_platform.h>

// Windows-specific implementations
#ifdef GPR_WINDOWS
#include <grpc/support/cpu.h>

#include "src/core/util/crash.h"

/**
 * @brief Gets the number of logical CPU cores available on the system
 * 
 * This function uses Windows API to retrieve system information and
 * returns the count of processors available.
 * 
 * @return unsigned - Number of logical processors in the system
 */
unsigned gpr_cpu_num_cores(void) {
  SYSTEM_INFO si;
  GetSystemInfo(&si);  // Retrieves system information including processor count
  return si.dwNumberOfProcessors;  // Returns the number of processors
}

/**
 * @brief Gets the current processor number the calling thread is running on
 * 
 * This function uses Windows API to determine which processor the current
 * thread is executing on. Note: This may not be accurate on systems with
 * more than 64 logical processors.
 * 
 * @return unsigned - Current processor number (0-indexed)
 */
unsigned gpr_cpu_current_cpu(void) { 
  return GetCurrentProcessorNumber();  // Returns current processor number
}

#endif  // GPR_WINDOWS
```

The comments provide:
1. File-level copyright notice
2. Explanation of platform-specific implementation
3. Detailed function documentation for both:
   - Purpose of each function
   - Brief implementation details
   - Return value information
4. Note about potential limitations (for gpr_cpu_current_cpu)
5. Clear indication of platform-specific code block boundaries

The comments follow a consistent style and provide useful information for maintenance while not being overly verbose.