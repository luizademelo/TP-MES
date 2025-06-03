Here's the commented version of the code:

```c++
// Copyright 2017 gRPC authors.

// Platform-specific header for portability
#include <grpc/support/port_platform.h>

// Headers for hostname functionality
#include "src/core/lib/iomgr/port.h"
#include "src/core/util/gethostname.h"

// Implementation for POSIX-compliant systems that define HOST_NAME_MAX
#ifdef GRPC_POSIX_HOST_NAME_MAX

// Required headers for memory allocation and system calls
#include <grpc/support/alloc.h>
#include <limits.h>
#include <unistd.h>

/**
 * Gets the hostname of the current machine.
 * 
 * @return On success, returns a dynamically allocated string containing 
 *         the hostname. The caller is responsible for freeing this memory.
 *         On failure (if gethostname system call fails), returns nullptr.
 * 
 * @note This implementation is specifically for POSIX systems that define
 *       HOST_NAME_MAX. The function allocates a buffer of HOST_NAME_MAX size,
 *       attempts to get the hostname, and returns the result.
 */
char* grpc_gethostname() {
  // Allocate buffer for hostname with maximum possible size
  char* hostname = static_cast<char*>(gpr_malloc(HOST_NAME_MAX));
  
  // Attempt to get hostname using system call
  if (gethostname(hostname, HOST_NAME_MAX) != 0) {
    // Clean up allocated memory and return nullptr on failure
    gpr_free(hostname);
    return nullptr;
  }
  
  // Return the successfully obtained hostname
  return hostname;
}

#endif  // GRPC_POSIX_HOST_NAME_MAX
```

The comments provide:
1. File-level information about the copyright and purpose
2. Explanation of header inclusions
3. Clear documentation of the conditional compilation block
4. Detailed function documentation including:
   - Purpose of the function
   - Return value semantics
   - Memory ownership information
   - Implementation notes
5. Inline comments explaining key operations
6. Clear indication of the conditional compilation block's end

The comments are designed to help maintainers understand:
- The context in which this code operates
- The memory management responsibilities
- The system dependencies
- The error handling behavior
- The platform-specific nature of the implementation