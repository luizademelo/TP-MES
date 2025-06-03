Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

// Header guard to prevent multiple inclusions of this header file
#ifndef GRPC_SRC_CORE_LIB_IOMGR_SOCKET_UTILS_H
#define GRPC_SRC_CORE_LIB_IOMGR_SOCKET_UTILS_H

// Include platform-specific support macros and standard size definitions
#include <grpc/support/port_platform.h>
#include <stddef.h>

// Converts a 16-bit value from host byte order to network byte order
// (typically big-endian)
// @param hostshort: 16-bit value in host byte order
// @return: 16-bit value in network byte order
uint16_t grpc_htons(uint16_t hostshort);

// Converts a 16-bit value from network byte order to host byte order
// @param netshort: 16-bit value in network byte order
// @return: 16-bit value in host byte order
uint16_t grpc_ntohs(uint16_t netshort);

// Converts a 32-bit value from host byte order to network byte order
// (typically big-endian)
// @param hostlong: 32-bit value in host byte order
// @return: 32-bit value in network byte order
uint32_t grpc_htonl(uint32_t hostlong);

// Converts a 32-bit value from network byte order to host byte order
// @param netlong: 32-bit value in network byte order
// @return: 32-bit value in host byte order
uint32_t grpc_ntohl(uint32_t netlong);

// Converts an address from text (human-readable) form to binary form
// @param af: Address family (AF_INET or AF_INET6)
// @param src: Pointer to the text string to convert
// @param dst: Pointer to buffer for the binary result
// @return: 1 on success, 0 if src doesn't contain valid address, -1 on error
int grpc_inet_pton(int af, const char* src, void* dst);

// Converts an address from binary form to text (human-readable) form
// @param af: Address family (AF_INET or AF_INET6)
// @param src: Pointer to binary address to convert
// @param dst: Pointer to buffer for the text result
// @param size: Size of the destination buffer
// @return: Pointer to dst on success, NULL on error
const char* grpc_inet_ntop(int af, const void* src, char* dst, size_t size);

#endif  // GRPC_SRC_CORE_LIB_IOMGR_SOCKET_UTILS_H
```

The comments provide:
1. Explanation of the header guard purpose
2. Description of included headers
3. Detailed documentation for each function including:
   - Purpose of the function
   - Parameters with their meanings
   - Return values and their interpretations
4. Consistent formatting for readability
5. Closing comment for the header guard

The comments follow standard documentation practices for C/C++ code and provide all the necessary information for developers to understand and use these socket utility functions.