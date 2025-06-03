Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

// Include necessary headers for CPU support and platform-specific functionality
#include <grpc/support/cpu.h>
#include <grpc/support/port_platform.h>

// This implementation is specific to iOS (IPHONE) platforms
#ifdef GPR_CPU_IPHONE

#include <sys/sysctl.h>  // Required for sysctlbyname() function

/**
 * @brief Returns the number of CPU cores available on the iOS device.
 * 
 * This function uses the iOS system call 'sysctlbyname' to query the number
 * of CPU cores (via "hw.ncpu" parameter). The result is cached in 'ncpu'.
 * 
 * @return unsigned The number of CPU cores available on the device.
 */
unsigned gpr_cpu_num_cores(void) {
  size_t len;
  unsigned int ncpu;
  len = sizeof(ncpu);
  // Query the system for number of CPU cores
  sysctlbyname("hw.ncpu", &ncpu, &len, NULL, 0);

  return ncpu;
}

/**
 * @brief Returns the current CPU index (core number) the code is running on.
 * 
 * Note: On iOS, this implementation always returns 0 as there isn't a direct
 * way to query the current CPU core on iOS. This is a placeholder implementation.
 * 
 * @return unsigned Always returns 0 (placeholder implementation)
 */
unsigned gpr_cpu_current_cpu(void) { return 0; }

#endif  // GPR_CPU_IPHONE
```

Key improvements made:
1. Added descriptive header comments explaining the purpose of each function
2. Added documentation for return values
3. Explained the platform-specific nature of the implementation
4. Noted the placeholder nature of `gpr_cpu_current_cpu()`
5. Added comments explaining the system call usage
6. Maintained the original copyright notice
7. Kept all original functionality while making it more understandable