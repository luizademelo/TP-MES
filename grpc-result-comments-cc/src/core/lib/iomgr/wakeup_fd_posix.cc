Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

// Platform-specific header for portability
#include <grpc/support/port_platform.h>

// Include port-specific definitions
#include "src/core/lib/iomgr/port.h"

// Only compile this code if using POSIX wakeup file descriptors
#ifdef GRPC_POSIX_WAKEUP_FD

#include <stddef.h>  // For NULL definition

// Include implementations for different wakeup fd types
#include "src/core/lib/iomgr/wakeup_fd_pipe.h"
#include "src/core/lib/iomgr/wakeup_fd_posix.h"

// Global variable storing the virtual function table for wakeup fd operations
static const grpc_wakeup_fd_vtable* wakeup_fd_vtable = nullptr;

// Configuration flags for wakeup fd types:
int grpc_allow_specialized_wakeup_fd = 1;  // Allow specialized implementations
int grpc_allow_pipe_wakeup_fd = 1;         // Allow pipe-based implementations

// Flag indicating if a real wakeup fd implementation is available
static int has_real_wakeup_fd = 1;

// One-time initialization control for wakeup fd system
static gpr_once once_init_wakeup_fd = GPR_ONCE_INIT;

// Initialize the global wakeup fd system, choosing the best available implementation
void grpc_wakeup_fd_global_init(void) {
  gpr_once_init(&once_init_wakeup_fd, []() {
    // First try specialized implementation if allowed and available
    if (grpc_allow_specialized_wakeup_fd &&
        grpc_specialized_wakeup_fd_vtable.check_availability()) {
      wakeup_fd_vtable = &grpc_specialized_wakeup_fd_vtable;
    } 
    // Fall back to pipe implementation if allowed and available
    else if (grpc_allow_pipe_wakeup_fd &&
             grpc_pipe_wakeup_fd_vtable.check_availability()) {
      wakeup_fd_vtable = &grpc_pipe_wakeup_fd_vtable;
    } 
    // No available implementation
    else {
      has_real_wakeup_fd = 0;
    }
  });
}

// Cleanup function for wakeup fd system (currently no-op)
void grpc_wakeup_fd_global_destroy(void) {}

// Check if a real wakeup fd implementation is available
int grpc_has_wakeup_fd(void) { return has_real_wakeup_fd; }

// Initialize a wakeup file descriptor
grpc_error_handle grpc_wakeup_fd_init(grpc_wakeup_fd* fd_info) {
  return wakeup_fd_vtable->init(fd_info);
}

// Consume a wakeup event from the file descriptor
grpc_error_handle grpc_wakeup_fd_consume_wakeup(grpc_wakeup_fd* fd_info) {
  return wakeup_fd_vtable->consume(fd_info);
}

// Trigger a wakeup event on the file descriptor
grpc_error_handle grpc_wakeup_fd_wakeup(grpc_wakeup_fd* fd_info) {
  return wakeup_fd_vtable->wakeup(fd_info);
}

// Clean up and destroy a wakeup file descriptor
void grpc_wakeup_fd_destroy(grpc_wakeup_fd* fd_info) {
  wakeup_fd_vtable->destroy(fd_info);
}

#endif  // GRPC_POSIX_WAKEUP_FD
```

Key aspects covered in the comments:
1. File descriptor initialization and cleanup
2. Implementation selection logic
3. Wakeup event handling
4. Platform-specific considerations
5. Configuration options
6. Error handling approach
7. One-time initialization pattern

The comments explain both the high-level architecture and the specific implementation details while maintaining readability.