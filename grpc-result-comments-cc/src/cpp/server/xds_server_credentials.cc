Here's the commented version of the code:

```c++
// Copyright 2020 gRPC authors.

// Include necessary gRPC and Abseil headers
#include <grpc/grpc.h>
#include <grpc/grpc_security.h>
#include <grpcpp/security/server_credentials.h>

#include <memory>

#include "absl/log/check.h"

namespace grpc {

// Creates and returns XDS server credentials using provided fallback credentials
// Args:
//   fallback_credentials: Shared pointer to the credentials to use as fallback
//                        when XDS credentials are not available
// Returns:
//   Shared pointer to the newly created XDS server credentials
// Note:
//   - Performs null checks on input credentials
//   - Wraps the gRPC core function grpc_xds_server_credentials_create
std::shared_ptr<ServerCredentials> XdsServerCredentials(
    const std::shared_ptr<ServerCredentials>& fallback_credentials) {
  // Ensure fallback credentials are not null
  CHECK_NE(fallback_credentials, nullptr);
  // Ensure the underlying C credentials object exists
  CHECK_NE(fallback_credentials->c_creds_, nullptr);
  
  // Create and return new ServerCredentials instance with XDS credentials
  return std::shared_ptr<ServerCredentials>(new ServerCredentials(
      grpc_xds_server_credentials_create(fallback_credentials->c_creds_)));
}

namespace experimental {

// Experimental version of XdsServerCredentials that forwards to the stable version
// Args:
//   fallback_credentials: Shared pointer to the credentials to use as fallback
// Returns:
//   Shared pointer to the newly created XDS server credentials
// Note:
//   - This exists to maintain experimental API compatibility
//   - Simply forwards to the stable grpc::XdsServerCredentials implementation
std::shared_ptr<ServerCredentials> XdsServerCredentials(
    const std::shared_ptr<ServerCredentials>& fallback_credentials) {
  return grpc::XdsServerCredentials(fallback_credentials);
}

}  // namespace experimental
}  // namespace grpc
```

The comments explain:
1. The purpose and behavior of each function
2. The parameters and return values
3. Important implementation details (null checks)
4. The relationship between the stable and experimental versions
5. The use of underlying gRPC core functionality
6. Namespace boundaries

The comments are designed to help future maintainers understand:
- What the code does
- Why certain checks exist
- How the different versions relate to each other
- Where to look for underlying implementations