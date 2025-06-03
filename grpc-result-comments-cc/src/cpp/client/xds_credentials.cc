Here's the commented version of the code:

```c++
// Copyright 2020 gRPC authors.

// Include necessary gRPC headers for core functionality and security features
#include <grpc/grpc.h>
#include <grpc/grpc_security.h>
#include <grpcpp/security/credentials.h>

#include <memory>

// Include ABSL's CHECK macros for runtime verification
#include "absl/log/check.h"

namespace grpc {

// Implementation of XDS (Cross-Data-center Service) Channel Credentials
// This class wraps gRPC's C-core XDS credentials with C++ interface
class XdsChannelCredentialsImpl final : public ChannelCredentials {
 public:
  // Constructor that takes fallback credentials to use when XDS credentials
  // cannot be used. The fallback credentials must be valid (non-null).
  explicit XdsChannelCredentialsImpl(
      const std::shared_ptr<ChannelCredentials>& fallback_creds)
      : ChannelCredentials(
            grpc_xds_credentials_create(fallback_creds->c_creds_)) {
    // Verify that the fallback credentials' underlying C credentials are valid
    CHECK_NE(fallback_creds->c_creds_, nullptr);
  }
};

// Factory function to create XDS credentials with the given fallback credentials
// Args:
//   fallback_creds: Credentials to use when XDS credentials are not available
// Returns:
//   Shared pointer to the newly created XdsChannelCredentialsImpl instance
std::shared_ptr<ChannelCredentials> XdsCredentials(
    const std::shared_ptr<ChannelCredentials>& fallback_creds) {
  // Ensure the provided fallback credentials are not null
  CHECK_NE(fallback_creds, nullptr);
  return std::make_shared<XdsChannelCredentialsImpl>(fallback_creds);
}

namespace experimental {

// Experimental version of the XDS credentials factory function
// This forwards to the stable version in the grpc namespace
// Args:
//   fallback_creds: Credentials to use when XDS credentials are not available
// Returns:
//   Shared pointer to the newly created XdsChannelCredentialsImpl instance
std::shared_ptr<ChannelCredentials> XdsCredentials(
    const std::shared_ptr<ChannelCredentials>& fallback_creds) {
  return grpc::XdsCredentials(fallback_creds);
}

}  // namespace experimental
}  // namespace grpc
```

The comments added explain:
1. The purpose of each include directive
2. The overall purpose of the XdsChannelCredentialsImpl class
3. The constructor's behavior and requirements
4. The runtime checks being performed
5. The purpose and behavior of both XdsCredentials factory functions
6. The relationship between the experimental and stable versions
7. Parameter requirements and return values

The comments are kept concise while providing all the essential information a maintainer would need to understand and work with this code.