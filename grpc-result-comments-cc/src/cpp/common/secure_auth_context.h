Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CPP_COMMON_SECURE_AUTH_CONTEXT_H
#define GRPC_SRC_CPP_COMMON_SECURE_AUTH_CONTEXT_H

// Include necessary headers for security and authentication functionality
#include <grpc/grpc_security.h>
#include <grpcpp/security/auth_context.h>
#include <grpcpp/support/string_ref.h>

// Standard C++ headers
#include <string>
#include <vector>

// Internal gRPC headers
#include "src/core/transport/auth_context.h"
#include "src/core/util/ref_counted_ptr.h"

namespace grpc {

// SecureAuthContext is a concrete implementation of AuthContext that provides
// secure authentication context functionality. It wraps a grpc_auth_context
// and provides methods to inspect and modify authentication properties.
class SecureAuthContext final : public AuthContext {
 public:
  // Constructor takes ownership of the provided grpc_auth_context.
  // If ctx is null, creates an empty context.
  explicit SecureAuthContext(grpc_auth_context* ctx)
      : ctx_(ctx != nullptr ? ctx->Ref() : nullptr) {}

  // Default destructor
  ~SecureAuthContext() override = default;

  // Returns true if the peer was authenticated, false otherwise.
  bool IsPeerAuthenticated() const override;

  // Returns the peer's identity as a vector of string references.
  std::vector<grpc::string_ref> GetPeerIdentity() const override;

  // Returns the name of the property that contains the peer's identity.
  std::string GetPeerIdentityPropertyName() const override;

  // Finds all property values associated with the given name.
  std::vector<grpc::string_ref> FindPropertyValues(
      const std::string& name) const override;

  // Returns an iterator to the beginning of the authentication properties.
  AuthPropertyIterator begin() const override;

  // Returns an iterator to the end of the authentication properties.
  AuthPropertyIterator end() const override;

  // Adds a new property with the given key-value pair to the context.
  void AddProperty(const std::string& key,
                   const grpc::string_ref& value) override;

  // Sets the property name that will be used to identify the peer.
  // Returns true if successful, false otherwise.
  bool SetPeerIdentityPropertyName(const std::string& name) override;

 private:
  // The underlying reference-counted authentication context.
  grpc_core::RefCountedPtr<grpc_auth_context> ctx_;
};

}  // namespace grpc

#endif  // GRPC_SRC_CPP_COMMON_SECURE_AUTH_CONTEXT_H
```

The comments explain:
1. The purpose of each include directive
2. The overall class purpose and inheritance
3. Each public method's functionality and return values
4. The private member variable's role
5. The constructor's behavior with null input
6. The default destructor
7. The namespace and header guard

The comments are concise yet informative, providing enough context for future maintainers to understand the code's purpose and functionality without being overly verbose.