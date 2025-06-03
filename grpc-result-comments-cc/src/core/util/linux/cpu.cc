Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

// Ensure GNU extensions are available (for features like sched_getcpu)
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <grpc/support/port_platform.h>

// Only compile this code for Linux platforms
#ifdef GPR_CPU_LINUX

#include <errno.h>
#include <grpc/support/cpu.h>
#include <grpc/support/sync.h>
#include <sched.h>
#include <string.h>
#include <unistd.h>

#include "absl/log/log.h"
#include "src/core/util/crash.h"
#include "src/core/util/strerror.h"

// Global variable to cache the number of CPUs
static int ncpus = 0;

// Initializes the number of CPUs in the system
static void init_num_cpus() {
#ifndef GPR_MUSL_LIBC_COMPAT
  // Check if we can get the current CPU (not available in MUSL libc)
  if (sched_getcpu() < 0) {
    LOG(ERROR) << "Error determining current CPU: "
               << grpc_core::StrError(errno) << "\n";
    ncpus = 1;
    return;
  }
#endif

  // Get the number of configured processors from system configuration
  ncpus = static_cast<int>(sysconf(_SC_NPROCESSORS_CONF));
  if (ncpus < 1) {
    LOG(ERROR) << "Cannot determine number of CPUs: assuming 1";
    ncpus = 1;
  }
}

// Returns the number of CPU cores in the system
// Uses thread-safe initialization to determine the count only once
unsigned gpr_cpu_num_cores(void) {
  static gpr_once once = GPR_ONCE_INIT;
  gpr_once_init(&once, init_num_cpus);
  return static_cast<unsigned>(ncpus);
}

// Returns the current CPU core this thread is running on
unsigned gpr_cpu_current_cpu(void) {
#ifdef GPR_MUSL_LIBC_COMPAT
  // MUSL libc compatibility - return 0 as sched_getcpu() isn't available
  return 0;
#else
  // If there's only one core, we're always on core 0
  if (gpr_cpu_num_cores() == 1) {
    return 0;
  }
  
  // Get current CPU core
  int cpu = sched_getcpu();
  if (cpu < 0) {
    LOG(ERROR) << "Error determining current CPU: "
               << grpc_core::StrError(errno) << "\n";
    return 0;
  }
  
  // Handle case where CPU number exceeds our cached count (hot-plugged CPUs)
  if (static_cast<unsigned>(cpu) >= gpr_cpu_num_cores()) {
    VLOG(2) << "Cannot handle hot-plugged CPUs";
    return 0;
  }
  
  return static_cast<unsigned>(cpu);
#endif
}

#endif  // GPR_CPU_LINUX
```

Key aspects covered in the comments:
1. Purpose of the GNU_SOURCE definition
2. Platform-specific compilation guard
3. Explanation of the global ncpus variable
4. Detailed documentation of the CPU detection logic
5. Thread-safe initialization pattern in gpr_cpu_num_cores()
6. Special handling for MUSL libc compatibility
7. Error handling and edge cases in CPU detection
8. Hot-plugged CPU scenario handling

The comments maintain a balance between explaining the what (functionality) and the why (design decisions) while being concise and directly relevant to the code.