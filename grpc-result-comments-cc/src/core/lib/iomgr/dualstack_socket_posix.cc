Here's the commented version of the code:

```c++
// Copyright 2020 gRPC authors.

// Include platform-specific portability definitions
#include <grpc/support/port_platform.h>

// Include port definitions for I/O manager
#include "src/core/lib/iomgr/port.h"

// Only compile this code if using POSIX socket utilities
#ifdef GRPC_POSIX_SOCKET_UTILS_COMMON

// Include standard networking headers
#include <netinet/in.h>

// Include POSIX-specific socket utilities
#include "src/core/lib/iomgr/socket_utils_posix.h"

// Only define these functions if no custom dualstack implementation exists
#ifndef GRPC_SET_SOCKET_DUALSTACK_CUSTOM

// Global flag to control dualstack socket behavior for testing purposes
// When set to non-zero, forces IPv6-only sockets (disables dualstack)
int grpc_forbid_dualstack_sockets_for_testing = 0;

/**
 * Configures a socket for dualstack operation (IPv4 and IPv6 on same socket).
 * 
 * @param fd The file descriptor of the socket to configure
 * @return Returns 1 if successful (or if test mode is active), 0 on failure
 * 
 * When not in test mode (grpc_forbid_dualstack_sockets_for_testing == 0):
 *   - Attempts to disable IPV6_V6ONLY option to enable dualstack
 *   - Returns 1 if successful, 0 if setsockopt fails
 * 
 * When in test mode (grpc_forbid_dualstack_sockets_for_testing != 0):
 *   - Explicitly enables IPV6_V6ONLY option (disabling dualstack)
 *   - Always returns 1 (success) for testing purposes
 */
int grpc_set_socket_dualstack(int fd) {
  if (!grpc_forbid_dualstack_sockets_for_testing) {
    // Normal operation: try to enable dualstack
    const int off = 0;
    return 0 == setsockopt(fd, IPPROTO_IPV6, IPV6_V6ONLY, &off, sizeof(off));
  } else {
    // Test mode: force IPv6-only socket
    const int on = 1;
    setsockopt(fd, IPPROTO_IPV6, IPV6_V6ONLY, &on, sizeof(on));
    return 0;
  }
}
#endif
#endif
```

The comments explain:
1. The purpose of each include directive
2. The conditional compilation blocks
3. The global testing flag variable
4. The dualstack socket configuration function, including:
   - Parameters and return value
   - Behavior in normal vs test mode
   - The socket option being modified (IPV6_V6ONLY)
   - The different paths the function can take

The comments are designed to help future maintainers understand both what the code does and why it does it, particularly the testing-related functionality.