Here's the commented version of the code:

```c++
// Copyright 2021 gRPC authors.

// Include necessary headers for gRPC security, status codes, memory management,
// and authorization policy functionality
#include <grpc/grpc_security.h>
#include <grpc/status.h>
#include <grpc/support/alloc.h>
#include <grpcpp/security/authorization_policy_provider.h>
#include <grpcpp/support/status.h>

#include <memory>
#include <string>

namespace grpc {
namespace experimental {

// Creates a static data authorization policy provider from the given policy string
// Parameters:
//   authz_policy: The authorization policy string to be used
//   status: Output parameter for operation status
// Returns:
//   Shared pointer to the created provider, or nullptr if creation failed
std::shared_ptr<StaticDataAuthorizationPolicyProvider>
StaticDataAuthorizationPolicyProvider::Create(const std::string& authz_policy,
                                              grpc::Status* status) {
  grpc_status_code code = GRPC_STATUS_OK;
  const char* error_details;
  // Create C-core authorization policy provider from static data
  grpc_authorization_policy_provider* provider =
      grpc_authorization_policy_provider_static_data_create(
          authz_policy.c_str(), &code, &error_details);
  
  // Handle creation failure
  if (code != GRPC_STATUS_OK) {
    *status = grpc::Status(static_cast<grpc::StatusCode>(code), error_details);
    gpr_free(const_cast<char*>(error_details));  // Free error details string
    return nullptr;
  }
  
  // Return success status and the created provider
  *status = grpc::Status();
  return std::make_shared<StaticDataAuthorizationPolicyProvider>(provider);
}

// Destructor for StaticDataAuthorizationPolicyProvider
// Releases the underlying C-core provider resources
StaticDataAuthorizationPolicyProvider::
    ~StaticDataAuthorizationPolicyProvider() {
  grpc_authorization_policy_provider_release(c_provider_);
}

// Creates a file watcher authorization policy provider
// Parameters:
//   authz_policy_path: Path to the authorization policy file
//   refresh_interval_sec: How often to check for file updates (in seconds)
//   status: Output parameter for operation status
// Returns:
//   Shared pointer to the created provider, or nullptr if creation failed
std::shared_ptr<FileWatcherAuthorizationPolicyProvider>
FileWatcherAuthorizationPolicyProvider::Create(
    const std::string& authz_policy_path, unsigned int refresh_interval_sec,
    grpc::Status* status) {
  grpc_status_code code = GRPC_STATUS_OK;
  const char* error_details;
  // Create C-core file watcher authorization policy provider
  grpc_authorization_policy_provider* provider =
      grpc_authorization_policy_provider_file_watcher_create(
          authz_policy_path.c_str(), refresh_interval_sec, &code,
          &error_details);
  
  // Handle creation failure
  if (code != GRPC_STATUS_OK) {
    *status = grpc::Status(static_cast<grpc::StatusCode>(code), error_details);
    gpr_free(const_cast<char*>(error_details));  // Free error details string
    return nullptr;
  }
  
  // Return the created provider
  return std::make_shared<FileWatcherAuthorizationPolicyProvider>(provider);
}

// Destructor for FileWatcherAuthorizationPolicyProvider
// Releases the underlying C-core provider resources
FileWatcherAuthorizationPolicyProvider::
    ~FileWatcherAuthorizationPolicyProvider() {
  grpc_authorization_policy_provider_release(c_provider_);
}

}  // namespace experimental
}  // namespace grpc
```

Key improvements made:
1. Added detailed function descriptions explaining purpose, parameters, and return values
2. Added comments for important code blocks and logic flows
3. Explained error handling cases
4. Documented resource management (memory freeing)
5. Added namespace closing comments
6. Explained the purpose of included headers
7. Added comments for both creation methods and destructors
8. Explained the relationship with C-core functionality

The comments are concise yet informative, helping future developers understand both the what and why of the code's implementation.