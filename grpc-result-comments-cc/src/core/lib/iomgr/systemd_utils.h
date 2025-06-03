Here's the commented version of the code snippet:

```c++
// Copyright 2022 gRPC authors.

// Header guard to prevent multiple inclusions of this header file
#ifndef GRPC_SRC_CORE_LIB_IOMGR_SYSTEMD_UTILS_H
#define GRPC_SRC_CORE_LIB_IOMGR_SYSTEMD_UTILS_H

// Platform-specific support macros and includes
#include <grpc/support/port_platform.h>

// Include for POSIX TCP server utilities
#include "src/core/lib/iomgr/tcp_server_utils_posix.h"

/// Sets matching file descriptors from systemd for the given TCP server.
///
/// This function is used when running under systemd to inherit pre-allocated
/// socket file descriptors that match the requested address and port.
///
/// @param s The TCP server instance to configure
/// @param addr The resolved address to match against systemd's provided sockets
/// @param requested_port The port number to match against systemd's provided sockets
void set_matching_sd_fds(grpc_tcp_server* s, const grpc_resolved_address* addr,
                         int requested_port);

#endif  // GRPC_SRC_CORE_LIB_IOMGR_SYSTEMD_UTILS_H
```

The comments added include:
1. Explanation of the header guard purpose
2. Note about platform support includes
3. Documentation of the included header
4. Detailed function documentation including:
   - Purpose of the function
   - Behavior explanation
   - Parameter descriptions
5. Commented closing of the header guard for clarity

The comments follow standard C++ documentation practices and provide clear explanations for maintenance purposes.