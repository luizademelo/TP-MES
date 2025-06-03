Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

// Platform-specific configuration header
#include <grpc/support/port_platform.h>

// Include port definitions for I/O manager
#include "src/core/lib/iomgr/port.h"

// Only compile this code if using POSIX socket utilities
#ifdef GRPC_POSIX_SOCKET_UTILS_COMMON

// Socket utility functions
#include "src/core/lib/iomgr/socket_utils.h"

// System headers for socket operations
#include <sys/types.h>
// Platform-specific TCP header inclusion
#ifdef GRPC_LINUX_TCP_H
#include <linux/tcp.h>  // Linux-specific TCP definitions
#else
#include <netinet/tcp.h>  // Standard TCP definitions
#endif
// GRPC support libraries
#include <grpc/support/alloc.h>
#include <grpc/support/sync.h>
// Standard C headers
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include <string>

// Abseil logging utilities
#include "absl/log/check.h"
// GRPC address utilities
#include "src/core/lib/iomgr/sockaddr.h"
#include "src/core/util/crash.h"

// Convert 16-bit host byte order to network byte order
// Wrapper around standard htons() function
uint16_t grpc_htons(uint16_t hostshort) { return htons(hostshort); }

// Convert 16-bit network byte order to host byte order
// Wrapper around standard ntohs() function
uint16_t grpc_ntohs(uint16_t netshort) { return ntohs(netshort); }

// Convert 32-bit host byte order to network byte order
// Wrapper around standard htonl() function
uint32_t grpc_htonl(uint32_t hostlong) { return htonl(hostlong); }

// Convert 32-bit network byte order to host byte order
// Wrapper around standard ntohl() function
uint32_t grpc_ntohl(uint32_t netlong) { return ntohl(netlong); }

// Convert IP address from text to binary form
// Wrapper around standard inet_pton() function
// Parameters:
//   af - address family (AF_INET or AF_INET6)
//   src - source IP address string
//   dst - destination buffer for binary form
// Returns: 1 on success, 0 for invalid input, -1 for error
int grpc_inet_pton(int af, const char* src, void* dst) {
  return inet_pton(af, src, dst);
}

// Convert IP address from binary to text form
// Wrapper around standard inet_ntop() function with size validation
// Parameters:
//   af - address family (AF_INET or AF_INET6)
//   src - source binary IP address
//   dst - destination buffer for text form
//   size - size of destination buffer
// Returns: pointer to dst on success, NULL on error
const char* grpc_inet_ntop(int af, const void* src, char* dst, size_t size) {
  CHECK(size <= (socklen_t)-1);  // Ensure size is valid for socklen_t
  return inet_ntop(af, src, dst, static_cast<socklen_t>(size));
}

#endif  // GRPC_POSIX_SOCKET_UTILS_COMMON
```

The comments I've added:
1. Explain the purpose of each include file
2. Document the conditional compilation block
3. Provide detailed descriptions of each utility function including:
   - Their purpose
   - Parameters
   - Return values
   - Relationship to standard functions
4. Note the platform-specific considerations
5. Explain the safety check in grpc_inet_ntop

The comments maintain a consistent style and provide enough information for future maintainers to understand the code's purpose and behavior without being overly verbose.