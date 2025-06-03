Here's the commented version of the code:

```c++
// Copyright 2023 gRPC authors.

// Header guard to prevent multiple inclusions of this header file
#ifndef GRPC_SRC_CORE_LIB_IOMGR_VSOCK_H
#define GRPC_SRC_CORE_LIB_IOMGR_VSOCK_H

// Include necessary platform-specific support headers
#include <grpc/support/port_platform.h>
#include <grpc/support/string_util.h>

// Standard library includes
#include <string>

// Third-party includes
#include "absl/strings/string_view.h"
// Internal gRPC includes
#include "src/core/lib/iomgr/port.h"
#include "src/core/lib/iomgr/resolve_address.h"

/// @brief Resolves a VSOCK address string into a list of resolved addresses
/// @param name The VSOCK address string to resolve (e.g., "vsock:<cid>:<port>")
/// @return Returns either:
///         - A vector of resolved addresses on success
///         - An error status if resolution fails
absl::StatusOr<std::vector<grpc_resolved_address>> grpc_resolve_vsock_address(
    absl::string_view name);

/// @brief Checks if the given resolved address is a VSOCK address
/// @param resolved_addr Pointer to the resolved address to check
/// @return Returns non-zero (true) if the address is a VSOCK address,
///         zero (false) otherwise
int grpc_is_vsock(const grpc_resolved_address* resolved_addr);

// End of header guard
#endif
```

The comments added explain:
1. The purpose of the header guard
2. The included headers and their categories (platform support, standard library, third-party, internal)
3. Detailed documentation for each function including:
   - Purpose of the function
   - Parameter descriptions
   - Return value explanations
4. The end of the header guard

The comments follow a consistent style and provide clear, concise explanations of the code's functionality while maintaining professional documentation standards.