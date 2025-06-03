Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

// Header guard to prevent multiple inclusions
#ifndef GRPC_SRC_CORE_LIB_IOMGR_TCP_WINDOWS_H
#define GRPC_SRC_CORE_LIB_IOMGR_TCP_WINDOWS_H

// Include platform-specific portability headers
#include <grpc/support/port_platform.h>

// Include the port configuration for I/O manager
#include "src/core/lib/iomgr/port.h"

// Only include these declarations if compiling for Windows Sockets
#ifdef GRPC_WINSOCK_SOCKET

// Include necessary I/O manager interfaces
#include "src/core/lib/iomgr/endpoint.h"
#include "src/core/lib/iomgr/socket_windows.h"

// Creates a TCP endpoint from a Windows socket
// Parameters:
//   socket - The Windows socket to create endpoint from
//   peer_string - String identifying the peer (typically IP:port)
// Returns:
//   A newly created grpc_endpoint object
grpc_endpoint* grpc_tcp_create(grpc_winsocket* socket,
                               absl::string_view peer_string);

// Prepares a socket for use with gRPC
// Parameters:
//   sock - The socket to prepare
// Returns:
//   grpc_error_handle indicating success or failure
grpc_error_handle grpc_tcp_prepare_socket(SOCKET sock);

// Sets a socket to non-blocking mode
// Parameters:
//   sock - The socket to configure
// Returns:
//   grpc_error_handle indicating success or failure
grpc_error_handle grpc_tcp_set_non_block(SOCKET sock);

#endif  // GRPC_WINSOCK_SOCKET

#endif  // GRPC_SRC_CORE_LIB_IOMGR_TCP_WINDOWS_H
```

The comments provide:
1. Explanation of header guards and includes
2. Context about the conditional compilation for Windows Sockets
3. Documentation for each function including:
   - Purpose of the function
   - Parameters with their types and meanings
   - Return value information
4. Clear indication of conditional compilation boundaries
5. Consistent formatting and style throughout

The comments are designed to help maintainers understand:
- When and why this header is used
- What each function does
- The expected inputs and outputs
- The platform-specific nature of the implementation