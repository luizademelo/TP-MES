Here's the commented version of the code:

```c++
// Copyright 2016 gRPC authors.

#ifndef GRPCPP_IMPL_RPC_SERVICE_METHOD_H
#define GRPCPP_IMPL_RPC_SERVICE_METHOD_H

#include <grpcpp/impl/rpc_method.h>
#include <grpcpp/support/byte_buffer.h>
#include <grpcpp/support/config.h>
#include <grpcpp/support/status.h>

#include <climits>
#include <functional>
#include <map>
#include <memory>
#include <vector>

#include "absl/log/absl_check.h"
#include "absl/log/absl_log.h"

namespace grpc {
class ServerContextBase;
namespace internal {

// Base class for handling RPC methods. Provides interface for running handlers
// and deserializing requests.
class MethodHandler {
 public:
  virtual ~MethodHandler() {}
  
  // Container for parameters passed to method handlers
  struct HandlerParameter {
    // Constructs a HandlerParameter with all necessary context for method handling
    HandlerParameter(Call* c, grpc::ServerContextBase* context, void* req,
                     Status req_status, void* handler_data,
                     std::function<void()> requester)
        : call(c),
          server_context(context),
          request(req),
          status(req_status),
          internal_data(handler_data),
          call_requester(std::move(requester)) {}
    ~HandlerParameter() {}
    
    Call* const call;                      // The RPC call object
    grpc::ServerContextBase* const server_context;  // Server context for the call
    void* const request;                   // Deserialized request message
    const Status status;                   // Status of the request
    void* const internal_data;             // Internal handler-specific data
    const std::function<void()> call_requester;  // Function to request next call
  };
  
  // Main method to execute the handler logic
  virtual void RunHandler(const HandlerParameter& param) = 0;

  // Deserializes the request buffer. Default implementation expects null buffer.
  virtual void* Deserialize(grpc_call* , grpc_byte_buffer* req,
                            Status* , void** ) {
    ABSL_CHECK_EQ(req, nullptr);
    return nullptr;
  }
};

// Represents an RPC service method, containing method information and handler
class RpcServiceMethod : public RpcMethod {
 public:
  // Constructs an RPC service method with name, type, and handler
  RpcServiceMethod(const char* name, RpcMethod::RpcType type,
                   MethodHandler* handler)
      : RpcMethod(name, type),
        server_tag_(nullptr),
        api_type_(ApiType::SYNC),
        handler_(handler) {}

  // Enumeration of different API types supported by gRPC
  enum class ApiType {
    SYNC,        // Synchronous API
    ASYNC,       // Asynchronous API
    RAW,         // Raw API (no protobuf serialization)
    CALL_BACK,    // Callback-based API
    RAW_CALL_BACK // Raw callback-based API
  };

  // Sets the server tag used for identifying this method
  void set_server_tag(void* tag) { server_tag_ = tag; }
  // Gets the server tag
  void* server_tag() const { return server_tag_; }

  // Gets the method handler
  MethodHandler* handler() const { return handler_.get(); }
  // Gets the API type
  ApiType api_type() const { return api_type_; }
  // Sets a new method handler
  void SetHandler(MethodHandler* handler) { handler_.reset(handler); }
  
  // Sets the API type for this method, with validation and logging
  void SetServerApiType(RpcServiceMethod::ApiType type) {
    if ((api_type_ == ApiType::SYNC) &&
        (type == ApiType::ASYNC || type == ApiType::RAW)) {
      // For SYNC->ASYNC or SYNC->RAW transitions, reset the handler
      handler_.reset();
    } else if (api_type_ != ApiType::SYNC) {
      // Log warning when changing API type from non-SYNC to something else
      ABSL_LOG(INFO)
          << "You are marking method " << name() << " as '"
          << TypeToString(api_type_)
          << "', even though it was previously marked '" << TypeToString(type)
          << "'. This behavior will overwrite the original behavior. If "
             "you expected this then ignore this message.";
    }
    api_type_ = type;
  }

 private:
  void* server_tag_;                     // Tag used for server registration
  ApiType api_type_;                     // Type of API this method uses
  std::unique_ptr<MethodHandler> handler_; // Handler for this method

  // Converts ApiType enum to string representation for logging
  const char* TypeToString(RpcServiceMethod::ApiType type) {
    switch (type) {
      case ApiType::SYNC:
        return "sync";
      case ApiType::ASYNC:
        return "async";
      case ApiType::RAW:
        return "raw";
      case ApiType::CALL_BACK:
        return "callback";
      case ApiType::RAW_CALL_BACK:
        return "raw_callback";
      default:
        GPR_UNREACHABLE_CODE(return "unknown");
    }
  }
};
}

}

#endif
```

The comments added explain:
1. The overall purpose of each class and its components
2. The meaning of important data structures like HandlerParameter
3. The purpose and behavior of each method
4. The different API types supported
5. The logic behind the SetServerApiType method's validation
6. The ownership and lifecycle of important members like the handler_
7. The purpose of utility methods like TypeToString

The comments are designed to help future developers understand:
- What the code does
- Why certain design decisions were made
- How to properly use and extend the classes
- Important implementation details and constraints