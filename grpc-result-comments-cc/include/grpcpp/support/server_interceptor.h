Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

#ifndef GRPCPP_SUPPORT_SERVER_INTERCEPTOR_H
#define GRPCPP_SUPPORT_SERVER_INTERCEPTOR_H

#include <grpcpp/impl/rpc_method.h>
#include <grpcpp/support/interceptor.h>
#include <grpcpp/support/string_ref.h>

#include <atomic>
#include <vector>

#include "absl/log/absl_check.h"

namespace grpc {
class ServerContextBase;
namespace internal {
class InterceptorBatchMethodsImpl;
}

namespace experimental {

class ServerRpcInfo;

// Abstract factory interface for creating server interceptors
class ServerInterceptorFactoryInterface {
 public:
  virtual ~ServerInterceptorFactoryInterface() {}

  // Creates a new server interceptor instance
  // @param info: ServerRpcInfo object containing RPC call information
  // @return: Pointer to newly created interceptor instance
  virtual Interceptor* CreateServerInterceptor(ServerRpcInfo* info) = 0;
};

// Contains information about an RPC being processed by the server
// and manages server-side interceptors for the RPC
class ServerRpcInfo {
 public:
  // Enumeration of RPC types
  enum class Type { 
    UNARY,             // Unary RPC (single request, single response)
    CLIENT_STREAMING,  // Client streaming RPC
    SERVER_STREAMING,  // Server streaming RPC
    BIDI_STREAMING    // Bidirectional streaming RPC
  };

  ~ServerRpcInfo() {}

  // Delete copy and move constructors/assignment operators
  ServerRpcInfo(const ServerRpcInfo&) = delete;
  ServerRpcInfo& operator=(const ServerRpcInfo&) = delete;
  ServerRpcInfo(ServerRpcInfo&&) = delete;
  ServerRpcInfo& operator=(ServerRpcInfo&&) = delete;

  // Gets the method name for this RPC
  // @return: Method name string
  const char* method() const { return method_; }

  // Gets the type of this RPC
  // @return: Type enum value
  Type type() const { return type_; }

  // Gets the server context associated with this RPC
  // @return: Pointer to ServerContextBase
  ServerContextBase* server_context() { return ctx_; }

 private:
  // Static assertions to ensure enum values match between Type and RpcMethod
  static_assert(Type::UNARY ==
                    static_cast<Type>(internal::RpcMethod::NORMAL_RPC),
                "violated expectation about Type enum");
  static_assert(Type::CLIENT_STREAMING ==
                    static_cast<Type>(internal::RpcMethod::CLIENT_STREAMING),
                "violated expectation about Type enum");
  static_assert(Type::SERVER_STREAMING ==
                    static_cast<Type>(internal::RpcMethod::SERVER_STREAMING),
                "violated expectation about Type enum");
  static_assert(Type::BIDI_STREAMING ==
                    static_cast<Type>(internal::RpcMethod::BIDI_STREAMING),
                "violated expectation about Type enum");

  // Private constructor - can only be created by friends
  // @param ctx: Server context
  // @param method: Method name
  // @param type: RPC type
  ServerRpcInfo(ServerContextBase* ctx, const char* method,
                internal::RpcMethod::RpcType type)
      : ctx_(ctx), method_(method), type_(static_cast<Type>(type)) {}

  // Executes the interceptor at the specified position
  // @param interceptor_methods: Batch methods for interceptor to process
  // @param pos: Position of interceptor in interceptors_ vector
  void RunInterceptor(
      experimental::InterceptorBatchMethods* interceptor_methods, size_t pos) {
    ABSL_CHECK_LT(pos, interceptors_.size());
    interceptors_[pos]->Intercept(interceptor_methods);
  }

  // Registers interceptors from factory creators
  // @param creators: Vector of interceptor factory interfaces
  void RegisterInterceptors(
      const std::vector<
          std::unique_ptr<experimental::ServerInterceptorFactoryInterface>>&
          creators) {
    for (const auto& creator : creators) {
      auto* interceptor = creator->CreateServerInterceptor(this);
      if (interceptor != nullptr) {
        interceptors_.push_back(
            std::unique_ptr<experimental::Interceptor>(interceptor));
      }
    }
  }

  // Increases reference count
  void Ref() { ref_.fetch_add(1, std::memory_order_relaxed); }
  
  // Decreases reference count and deletes object if count reaches zero
  void Unref() {
    if (GPR_UNLIKELY(ref_.fetch_sub(1, std::memory_order_acq_rel) == 1)) {
      delete this;
    }
  }

  // Member variables
  ServerContextBase* ctx_ = nullptr;  // Server context for this RPC
  const char* method_ = nullptr;      // Method name for this RPC
  const Type type_;                   // Type of this RPC
  std::atomic<intptr_t> ref_{1};      // Reference counter for this object
  std::vector<std::unique_ptr<experimental::Interceptor>> interceptors_;  // Registered interceptors

  // Friends that can access private members
  friend class internal::InterceptorBatchMethodsImpl;
  friend class grpc::ServerContextBase;
};

}  // namespace experimental
}  // namespace grpc

#endif
```

The comments explain:
1. The purpose of each class and its main responsibilities
2. The meaning of enum values
3. The functionality of each method
4. Important implementation details
5. The role of private members
6. Ownership and lifetime management (reference counting)
7. Relationships between classes (friends)
8. Static assertions that validate enum mappings

The comments are concise but provide enough information for a developer to understand the code's purpose and behavior without having to analyze the implementation details.