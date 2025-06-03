Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

// Include necessary gRPC headers for server security functionality
#include <grpc/grpc.h>
#include <grpc/grpc_security.h>
#include <grpcpp/security/auth_metadata_processor.h>
#include <grpcpp/security/server_credentials.h>

#include <memory>  // For std::shared_ptr and std::make_shared

namespace grpc {
namespace {
// Implementation of insecure server credentials for gRPC.
// This class provides credentials that don't provide any security (no encryption or authentication).
// Should only be used for testing or in secure internal networks.
class InsecureServerCredentialsImpl final : public ServerCredentials {
 public:
  // Constructor creates insecure server credentials using the gRPC C-core API
  InsecureServerCredentialsImpl()
      : ServerCredentials(grpc_insecure_server_credentials_create()) {}
};
}  // anonymous namespace

// Factory function to create and return insecure server credentials
// Returns: std::shared_ptr<ServerCredentials> - a shared pointer to the created credentials
std::shared_ptr<ServerCredentials> InsecureServerCredentials() {
  // Create and return an instance of InsecureServerCredentialsImpl wrapped in a shared_ptr
  return std::make_shared<InsecureServerCredentialsImpl>();
}

}  // namespace grpc
```

The comments explain:
1. The purpose of the include files
2. The role of the InsecureServerCredentialsImpl class
3. The security implications of using these credentials
4. The constructor's functionality
5. The purpose of the factory function
6. The return type and ownership semantics

The comments are kept concise while providing all the essential information a maintainer would need to understand and work with this code.