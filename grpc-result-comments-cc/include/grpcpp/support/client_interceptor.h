Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

#ifndef GRPCPP_SUPPORT_CLIENT_INTERCEPTOR_H
#define GRPCPP_SUPPORT_CLIENT_INTERCEPTOR_H

#include <grpcpp/impl/rpc_method.h>
#include <grpcpp/support/interceptor.h>
#include <grpcpp/support/string_ref.h>

#include <memory>
#include <vector>

#include "absl/log/absl_check.h"

namespace grpc {

class Channel;
class ClientContext;

namespace internal {
class InterceptorBatchMethodsImpl;
}

namespace experimental {
class ClientRpcInfo;

// Abstract factory interface for creating client interceptors
class ClientInterceptorFactoryInterface {
 public:
  virtual ~ClientInterceptorFactoryInterface() {}

  // Pure virtual method to create a client interceptor
  // @param info: Contains RPC call information needed for interceptor creation
  // @return: Pointer to the created interceptor
  virtual Interceptor* CreateClientInterceptor(ClientRpcInfo* info) = 0;
};
}

namespace internal {
// Global factory for client interceptors
extern experimental::ClientInterceptorFactoryInterface*
    g_global_client_interceptor_factory;

// Global factory for client stats interceptors
extern experimental::ClientInterceptorFactoryInterface*
    g_global_client_stats_interceptor_factory;
}

namespace experimental {
// Class containing information about a client RPC call that interceptors can use
class ClientRpcInfo {
 public:
  // Enumeration of RPC call types
  enum class Type {
    UNARY,              // Unary RPC (single request, single response)
    CLIENT_STREAMING,   // Client streaming RPC
    SERVER_STREAMING,   // Server streaming RPC
    BIDI_STREAMING,     // Bidirectional streaming RPC
    UNKNOWN             // Unknown type (default)
  };

  ~ClientRpcInfo() {}

  // Delete copy constructor
  ClientRpcInfo(const ClientRpcInfo&) = delete;
  // Default move constructor
  ClientRpcInfo(ClientRpcInfo&&) = default;

  // Getter for RPC method name
  const char* method() const { return method_; }

  // Getter for stats suffix
  const char* suffix_for_stats() const { return suffix_for_stats_; }

  // Getter for channel interface
  ChannelInterface* channel() { return channel_; }

  // Getter for client context
  grpc::ClientContext* client_context() { return ctx_; }

  // Getter for RPC type
  Type type() const { return type_; }

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

  // Private default constructor
  ClientRpcInfo() = default;

  // Constructor with parameters for RPC info initialization
  ClientRpcInfo(grpc::ClientContext* ctx, internal::RpcMethod::RpcType type,
                const char* method, const char* suffix_for_stats,
                grpc::ChannelInterface* channel)
      : ctx_(ctx),
        type_(static_cast<Type>(type)),
        method_(method),
        suffix_for_stats_(suffix_for_stats),
        channel_(channel) {}

  // Default move assignment operator
  ClientRpcInfo& operator=(ClientRpcInfo&&) = default;

  // Runs a specific interceptor at the given position
  void RunInterceptor(
      experimental::InterceptorBatchMethods* interceptor_methods, size_t pos) {
    ABSL_CHECK_LT(pos, interceptors_.size());
    interceptors_[pos]->Intercept(interceptor_methods);
  }

  // Registers interceptors from factories, including global ones
  void RegisterInterceptors(
      const std::vector<std::unique_ptr<
          experimental::ClientInterceptorFactoryInterface>>& creators,
      size_t interceptor_pos) {
    // Calculate total number of interceptors (local + global)
    size_t num_interceptors =
        creators.size() +
        (internal::g_global_client_stats_interceptor_factory != nullptr) +
        (internal::g_global_client_interceptor_factory != nullptr);
    
    // Early return if position is beyond total interceptors
    if (interceptor_pos > num_interceptors) {
      return;
    }

    // Add global stats interceptor if exists
    if (internal::g_global_client_stats_interceptor_factory != nullptr) {
      interceptors_.push_back(std::unique_ptr<experimental::Interceptor>(
          internal::g_global_client_stats_interceptor_factory
              ->CreateClientInterceptor(this)));
      --interceptor_pos;
    }

    // Add interceptors from the provided factories starting from interceptor_pos
    for (auto it = creators.begin() + interceptor_pos; it != creators.end();
         ++it) {
      auto* interceptor = (*it)->CreateClientInterceptor(this);
      if (interceptor != nullptr) {
        interceptors_.push_back(
            std::unique_ptr<experimental::Interceptor>(interceptor));
      }
    }

    // Add global interceptor if exists (added last)
    if (internal::g_global_client_interceptor_factory != nullptr) {
      interceptors_.push_back(std::unique_ptr<experimental::Interceptor>(
          internal::g_global_client_interceptor_factory
              ->CreateClientInterceptor(this)));
    }
  }

  // Member variables
  grpc::ClientContext* ctx_ = nullptr;               // Client context for the RPC
  Type type_{Type::UNKNOWN};                         // Type of RPC
  const char* method_ = nullptr;                     // RPC method name
  const char* suffix_for_stats_ = nullptr;           // Suffix for stats
  grpc::ChannelInterface* channel_ = nullptr;        // Channel for the RPC
  std::vector<std::unique_ptr<experimental::Interceptor>> interceptors_; // List of interceptors
  bool hijacked_ = false;                            // Whether RPC is hijacked
  size_t hijacked_interceptor_ = 0;                  // Position of hijacking interceptor

  // Friend classes that need access to private members
  friend class internal::InterceptorBatchMethodsImpl;
  friend class grpc::ClientContext;
};

// Function to register a global client interceptor factory
void RegisterGlobalClientInterceptorFactory(
    ClientInterceptorFactoryInterface* factory);

// Function to reset global client interceptor factory (for testing only)
void TestOnlyResetGlobalClientInterceptorFactory();

}
}

#endif
```

The comments explain:
1. The purpose of each class and its main responsibilities
2. The meaning of enum values and important methods
3. The logic behind interceptor registration and execution
4. The relationships between different components
5. Important implementation details
6. The purpose of private members and friend classes

The comments are designed to help future developers understand:
- How to use the interceptor system
- The flow of interceptor creation and execution
- The different types of RPC calls supported
- Where to look for specific functionality