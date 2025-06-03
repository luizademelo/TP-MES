Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

// Platform-specific header for portability
#include <grpc/support/port_platform.h>

// Only compile this code for POSIX-compatible CPU platforms
#if defined(GPR_CPU_POSIX)

// System and library includes
#include <errno.h>
#include <grpc/support/cpu.h>
#include <grpc/support/sync.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

// Project-specific includes
#include "absl/log/log.h"
#include "src/core/util/crash.h"
#include "src/core/util/useful.h"

// Global variable to store the number of CPU cores
static long ncpus = 0;

// Thread-specific storage key for thread IDs
static pthread_key_t thread_id_key;

// Initializes the ncpus variable with the number of available CPU cores
static void init_ncpus() {
  // Get the number of configured processors
  ncpus = sysconf(_SC_NPROCESSORS_CONF);
  
  // Validate the number of CPUs (must be between 1 and INT32_MAX)
  if (ncpus < 1 || ncpus > INT32_MAX) {
    LOG(ERROR) << "Cannot determine number of CPUs: assuming 1";
    ncpus = 1;
  }
}

// Returns the number of CPU cores available on the system
unsigned gpr_cpu_num_cores(void) {
  // Ensure init_ncpus is called exactly once in a thread-safe manner
  static gpr_once once = GPR_ONCE_INIT;
  gpr_once_init(&once, init_ncpus);
  
  // Return the cached number of CPUs
  return (unsigned)ncpus;
}

// Cleanup function for thread-specific data
static void delete_thread_id(void* value) {
  if (value) {
    free(value);
  }
}

// Initializes the thread-specific storage key
static void init_thread_id_key(void) {
  // Create a key with associated cleanup function
  pthread_key_create(&thread_id_key, delete_thread_id);
}

// Returns a "current CPU" identifier for the calling thread
unsigned gpr_cpu_current_cpu(void) {
  // NOTE: there's no way I know to return the actual cpu index portably...

  // Ensure the thread ID key is initialized exactly once
  static gpr_once once = GPR_ONCE_INIT;
  gpr_once_init(&once, init_thread_id_key);

  // Get thread-specific data (thread ID)
  unsigned int* thread_id =
      static_cast<unsigned int*>(pthread_getspecific(thread_id_key));
      
  // If no thread ID exists for this thread, create one
  if (thread_id == nullptr) {
    thread_id = static_cast<unsigned int*>(malloc(sizeof(unsigned int)));
    pthread_setspecific(thread_id_key, thread_id);
  }

  // Return a hash of the thread pointer, bounded by the number of CPU cores
  return (unsigned)grpc_core::HashPointer(thread_id, gpr_cpu_num_cores());
}

#endif  // GPR_CPU_POSIX
```

Key improvements in the comments:
1. Added file-level comment about the copyright
2. Explained the purpose of each include group
3. Documented all global variables
4. Added detailed function-level comments explaining purpose and behavior
5. Clarified the thread-safety mechanisms (gpr_once usage)
6. Explained the fallback behavior when CPU count can't be determined
7. Documented the NOTE about platform limitations
8. Added clear section comments for logical groupings
9. Explained the thread-specific storage mechanism
10. Added closing endif comment for better readability

The comments now provide a comprehensive understanding of the code's functionality while maintaining readability.