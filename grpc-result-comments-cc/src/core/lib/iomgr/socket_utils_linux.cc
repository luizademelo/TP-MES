Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

// Platform-specific header for portability
#include <grpc/support/port_platform.h>

// Header for port-specific I/O manager functionality
#include "src/core/lib/iomgr/port.h"

// Only compile this code on Linux systems with socket utilities support
#ifdef GRPC_LINUX_SOCKETUTILS

// System headers for socket operations
#include <sys/socket.h>
#include <sys/types.h>

// gRPC headers for socket address handling and POSIX socket utilities
#include "src/core/lib/iomgr/sockaddr.h"
#include "src/core/lib/iomgr/socket_utils_posix.h"
#include "src/core/util/crash.h"

/**
 * Creates a new socket for a connection and sets socket options.
 * This is a Linux-specific implementation using accept4() system call.
 *
 * @param sockfd The listening socket file descriptor
 * @param resolved_addr Pointer to store the connected peer's address
 * @param nonblock If non-zero, sets the socket to non-blocking mode
 * @param cloexec If non-zero, sets the close-on-exec flag
 * @return The new socket file descriptor on success, or -1 on error
 *
 * The function combines the accept() operation with setting socket options:
 * - SOCK_NONBLOCK: Sets non-blocking mode if requested
 * - SOCK_CLOEXEC: Sets close-on-exec flag if requested
 * This atomic operation avoids race conditions that could occur if these
 * operations were performed separately.
 */
int grpc_accept4(int sockfd, grpc_resolved_address* resolved_addr, int nonblock,
                 int cloexec) {
  // Initialize flags for socket options
  int flags = 0;
  // Set non-blocking flag if requested
  flags |= nonblock ? SOCK_NONBLOCK : 0;
  // Set close-on-exec flag if requested
  flags |= cloexec ? SOCK_CLOEXEC : 0;
  
  // Perform the accept operation with the specified flags
  return accept4(sockfd, reinterpret_cast<grpc_sockaddr*>(resolved_addr->addr),
                 &resolved_addr->len, flags);
}

#endif  // GRPC_LINUX_SOCKETUTILS
```