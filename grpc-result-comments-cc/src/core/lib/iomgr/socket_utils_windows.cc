Here's the commented version of the code:

```c++
// Copyright 2016 gRPC authors.

// Platform-specific includes and definitions
#include <grpc/support/port_platform.h>

// Include port-specific definitions
#include "src/core/lib/iomgr/port.h"

// Windows-specific socket utilities implementation
#ifdef GRPC_WINDOWS_SOCKETUTILS

// Include necessary headers for socket address manipulation and utilities
#include "src/core/lib/iomgr/sockaddr.h"
#include "src/core/lib/iomgr/socket_utils.h"
#include "src/core/util/crash.h"

// Converts a u_short from host byte order to network byte order
// Parameters:
//   hostshort - 16-bit value in host byte order
// Returns: 16-bit value in network byte order
uint16_t grpc_htons(uint16_t hostshort) { return htons(hostshort); }

// Converts a u_short from network byte order to host byte order
// Parameters:
//   netshort - 16-bit value in network byte order
// Returns: 16-bit value in host byte order
uint16_t grpc_ntohs(uint16_t netshort) { return ntohs(netshort); }

// Converts a u_long from host byte order to network byte order
// Parameters:
//   hostlong - 32-bit value in host byte order
// Returns: 32-bit value in network byte order
uint32_t grpc_htonl(uint32_t hostlong) { return htonl(hostlong); }

// Converts a u_long from network byte order to host byte order
// Parameters:
//   netlong - 32-bit value in network byte order
// Returns: 32-bit value in host byte order
uint32_t grpc_ntohl(uint32_t netlong) { return ntohl(netlong); }

// Converts an Internet address from text to binary form
// Parameters:
//   af - address family (AF_INET or AF_INET6)
//   src - pointer to the null-terminated string to convert
//   dst - pointer to buffer for converted address
// Returns: 1 on success, 0 if src is invalid, -1 if af is invalid
int grpc_inet_pton(int af, const char* src, void* dst) {
  return inet_pton(af, src, dst);
}

// Converts an Internet address from binary to text form
// Parameters:
//   af - address family (AF_INET or AF_INET6)
//   src - pointer to network address structure
//   dst - pointer to buffer for converted string
//   size - size of destination buffer
// Returns: pointer to destination string on success, NULL on error
const char* grpc_inet_ntop(int af, const void* src, char* dst, size_t size) {
  // Note: InetNtopA is the Windows-specific version of inet_ntop
  return InetNtopA(af, (void*)src, dst, size);
}

#endif  // GRPC_WINDOWS_SOCKETUTILS
```

The comments explain:
1. The purpose of each include directive
2. The conditional compilation for Windows-specific implementations
3. Each function's purpose, parameters, and return values
4. The byte order conversion functions (htons, ntohs, htonl, ntohl)
5. The address conversion functions (inet_pton and inet_ntop equivalents)
6. Platform-specific notes about Windows implementations

The comments are concise yet informative, helping future maintainers understand the code's purpose and functionality without being overly verbose.