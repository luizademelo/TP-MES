Here's the commented version of the code:

```c++
// Copyright 2021 gRPC authors.

#ifndef GRPCPP_SECURITY_AUTHORIZATION_POLICY_PROVIDER_H
#define GRPCPP_SECURITY_AUTHORIZATION_POLICY_PROVIDER_H

#include <grpc/grpc_security.h>
#include <grpc/status.h>
#include <grpcpp/support/status.h>

#include <memory>

namespace grpc {
namespace experimental {

// Abstract base class for authorization policy providers.
// Defines the interface that all concrete authorization policy providers must implement.
class AuthorizationPolicyProviderInterface {
 public:
  virtual ~AuthorizationPolicyProviderInterface() = default;
  
  // Returns the underlying C-style authorization policy provider.
  // This is used for interoperability with the core gRPC C API.
  virtual grpc_authorization_policy_provider* c_provider() = 0;
};

// Concrete implementation of AuthorizationPolicyProviderInterface that provides
// static authorization policy data (policy doesn't change after initialization).
class StaticDataAuthorizationPolicyProvider
    : public AuthorizationPolicyProviderInterface {
 public:
  // Factory method to create a StaticDataAuthorizationPolicyProvider instance.
  // @param authz_policy The authorization policy string to use
  // @param status Output parameter for creation status
  // @return Shared pointer to the created provider
  static std::shared_ptr<StaticDataAuthorizationPolicyProvider> Create(
      const std::string& authz_policy, grpc::Status* status);

  // Constructor that takes an existing C provider.
  // @param provider The C-style authorization policy provider to wrap
  explicit StaticDataAuthorizationPolicyProvider(
      grpc_authorization_policy_provider* provider)
      : c_provider_(provider) {}

  ~StaticDataAuthorizationPolicyProvider() override;

  // Returns the underlying C-style authorization policy provider.
  grpc_authorization_policy_provider* c_provider() override {
    return c_provider_;
  }

 private:
  // The underlying C-style authorization policy provider.
  grpc_authorization_policy_provider* c_provider_ = nullptr;
};

// Concrete implementation of AuthorizationPolicyProviderInterface that watches
// a file for changes to the authorization policy and automatically refreshes.
class FileWatcherAuthorizationPolicyProvider
    : public AuthorizationPolicyProviderInterface {
 public:
  // Factory method to create a FileWatcherAuthorizationPolicyProvider instance.
  // @param authz_policy_path Path to the file containing authorization policy
  // @param refresh_interval_sec How often to check for file changes (in seconds)
  // @param status Output parameter for creation status
  // @return Shared pointer to the created provider
  static std::shared_ptr<FileWatcherAuthorizationPolicyProvider> Create(
      const std::string& authz_policy_path, unsigned int refresh_interval_sec,
      grpc::Status* status);

  // Constructor that takes an existing C provider.
  // @param provider The C-style authorization policy provider to wrap
  explicit FileWatcherAuthorizationPolicyProvider(
      grpc_authorization_policy_provider* provider)
      : c_provider_(provider) {}

  ~FileWatcherAuthorizationPolicyProvider() override;

  // Returns the underlying C-style authorization policy provider.
  grpc_authorization_policy_provider* c_provider() override {
    return c_provider_;
  }

 private:
  // The underlying C-style authorization policy provider.
  grpc_authorization_policy_provider* c_provider_ = nullptr;
};

}  // namespace experimental
}  // namespace grpc

#endif  // GRPCPP_SECURITY_AUTHORIZATION_POLICY_PROVIDER_H
```

Key improvements made:
1. Added detailed class-level comments explaining the purpose of each class
2. Added detailed method comments explaining parameters and return values
3. Added comments for member variables
4. Added namespace closing comments
5. Added clear explanation of the interface and its implementations
6. Explained the purpose of the C-style provider accessor
7. Clarified the difference between static and file-watcher implementations
8. Added proper header guard closing comment

The comments now provide comprehensive documentation for developers who need to understand, use, or maintain this authorization policy provider functionality.