Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

// Include necessary gRPC headers for core functionality and security features
#include <grpc/grpc.h>
#include <grpc/grpc_security.h>
#include <grpcpp/security/auth_context.h>

#include <memory>  // For std::shared_ptr

// Include internal gRPC headers for auth context and reference counting
#include "src/core/transport/auth_context.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/cpp/common/secure_auth_context.h"

namespace grpc {

/// @brief Creates a shared AuthContext from a gRPC call object
/// @param call Pointer to the gRPC call object. If null, returns empty context
/// @return std::shared_ptr<const AuthContext> Shared pointer to auth context
/// 
/// This function:
/// 1. Checks for null call pointer and returns empty context if null
/// 2. Retrieves the auth context from the call using grpc_call_auth_context
/// 3. Wraps the auth context in a RefCountedPtr for safe memory management
/// 4. Creates and returns a SecureAuthContext that wraps the raw auth context
std::shared_ptr<const AuthContext> CreateAuthContext(grpc_call* call) {
  // Handle null call case by returning empty shared_ptr
  if (call == nullptr) {
    return std::shared_ptr<const AuthContext>();
  }
  
  // Get auth context from call and manage it with RefCountedPtr
  grpc_core::RefCountedPtr<grpc_auth_context> ctx(grpc_call_auth_context(call));
  
  // Create and return SecureAuthContext that wraps the raw auth context
  return std::make_shared<SecureAuthContext>(ctx.get());
}

}  // namespace grpc
```

The comments explain:
1. The purpose and functionality of the CreateAuthContext function
2. The parameter and return value
3. The null check safety mechanism
4. The memory management approach using RefCountedPtr
5. The final wrapping in SecureAuthContext
6. The overall flow of the function

I've used both line comments for specific implementation details and block comments for the function documentation, following common C++ documentation practices.