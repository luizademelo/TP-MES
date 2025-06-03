Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

#ifndef GRPCPP_IMPL_SERVICE_TYPE_H
#define GRPCPP_IMPL_SERVICE_TYPE_H

#include <grpcpp/impl/rpc_service_method.h>
#include <grpcpp/impl/serialization_traits.h>
#include <grpcpp/server_interface.h>
#include <grpcpp/support/config.h>
#include <grpcpp/support/status.h>

#include "absl/log/absl_check.h"

namespace grpc {

class CompletionQueue;
class ServerContext;
class ServerInterface;

namespace internal {
// Interface for server-side asynchronous streaming operations
class ServerAsyncStreamingInterface {
 public:
  virtual ~ServerAsyncStreamingInterface() {}

  // Sends initial metadata to the client
  virtual void SendInitialMetadata(void* tag) = 0;

 private:
  friend class grpc::ServerInterface;
  // Binds a call to this streaming interface
  virtual void BindCall(Call* call) = 0;
};
}

// Base class for gRPC services that provides common functionality
// for both synchronous and asynchronous method handling
class Service {
 public:
  Service() : server_(nullptr) {}
  virtual ~Service() {}

  // Checks if the service has any asynchronous methods
  bool has_async_methods() const {
    for (const auto& method : methods_) {
      if (method && method->handler() == nullptr) {
        return true;
      }
    }
    return false;
  }

  // Checks if the service has any synchronous methods
  bool has_synchronous_methods() const {
    for (const auto& method : methods_) {
      if (method &&
          method->api_type() == internal::RpcServiceMethod::ApiType::SYNC) {
        return true;
      }
    }
    return false;
  }

  // Checks if the service has any callback methods
  bool has_callback_methods() const {
    for (const auto& method : methods_) {
      if (method && (method->api_type() ==
                         internal::RpcServiceMethod::ApiType::CALL_BACK ||
                     method->api_type() ==
                         internal::RpcServiceMethod::ApiType::RAW_CALL_BACK)) {
        return true;
      }
    }
    return false;
  }

  // Checks if the service has any generic methods (methods that can handle any RPC)
  bool has_generic_methods() const {
    for (const auto& method : methods_) {
      if (method == nullptr) {
        return true;
      }
    }
    return false;
  }

 protected:
  // Requests an asynchronous unary call
  template <class Message>
  void RequestAsyncUnary(int index, grpc::ServerContext* context,
                         Message* request,
                         internal::ServerAsyncStreamingInterface* stream,
                         grpc::CompletionQueue* call_cq,
                         grpc::ServerCompletionQueue* notification_cq,
                         void* tag) {
    size_t idx = static_cast<size_t>(index);
    server_->RequestAsyncCall(methods_[idx].get(), context, stream, call_cq,
                              notification_cq, tag, request);
  }

  // Requests an asynchronous client streaming call
  void RequestAsyncClientStreaming(
      int index, grpc::ServerContext* context,
      internal::ServerAsyncStreamingInterface* stream,
      grpc::CompletionQueue* call_cq,
      grpc::ServerCompletionQueue* notification_cq, void* tag) {
    size_t idx = static_cast<size_t>(index);
    server_->RequestAsyncCall(methods_[idx].get(), context, stream, call_cq,
                              notification_cq, tag);
  }

  // Requests an asynchronous server streaming call
  template <class Message>
  void RequestAsyncServerStreaming(
      int index, grpc::ServerContext* context, Message* request,
      internal::ServerAsyncStreamingInterface* stream,
      grpc::CompletionQueue* call_cq,
      grpc::ServerCompletionQueue* notification_cq, void* tag) {
    size_t idx = static_cast<size_t>(index);
    server_->RequestAsyncCall(methods_[idx].get(), context, stream, call_cq,
                              notification_cq, tag, request);
  }

  // Requests an asynchronous bidirectional streaming call
  void RequestAsyncBidiStreaming(
      int index, grpc::ServerContext* context,
      internal::ServerAsyncStreamingInterface* stream,
      grpc::CompletionQueue* call_cq,
      grpc::ServerCompletionQueue* notification_cq, void* tag) {
    size_t idx = static_cast<size_t>(index);
    server_->RequestAsyncCall(methods_[idx].get(), context, stream, call_cq,
                              notification_cq, tag);
  }

  // Adds a new method to the service
  void AddMethod(internal::RpcServiceMethod* method) {
    methods_.emplace_back(method);
  }

  // Marks a method as asynchronous
  void MarkMethodAsync(int index) {
    size_t idx = static_cast<size_t>(index);
    ABSL_CHECK_NE(methods_[idx].get(), nullptr)
        << "Cannot mark the method as 'async' because it has already been "
           "marked as 'generic'.";
    methods_[idx]->SetServerApiType(internal::RpcServiceMethod::ApiType::ASYNC);
  }

  // Marks a method as raw (low-level API)
  void MarkMethodRaw(int index) {
    size_t idx = static_cast<size_t>(index);
    ABSL_CHECK_NE(methods_[idx].get(), nullptr)
        << "Cannot mark the method as 'raw' because it has already "
           "been marked as 'generic'.";
    methods_[idx]->SetServerApiType(internal::RpcServiceMethod::ApiType::RAW);
  }

  // Marks a method as generic (can handle any RPC)
  void MarkMethodGeneric(int index) {
    size_t idx = static_cast<size_t>(index);
    ABSL_CHECK_NE(methods_[idx]->handler(), nullptr)
        << "Cannot mark the method as 'generic' because it has already been "
           "marked as 'async' or 'raw'.";
    methods_[idx].reset();
  }

  // Marks a method as streamed and sets its handler
  void MarkMethodStreamed(int index, internal::MethodHandler* streamed_method) {
    size_t idx = static_cast<size_t>(index);
    ABSL_CHECK(methods_[idx] && methods_[idx]->handler())
        << "Cannot mark an async or generic method Streamed";
    methods_[idx]->SetHandler(streamed_method);
    methods_[idx]->SetMethodType(internal::RpcMethod::BIDI_STREAMING);
  }

  // Marks a method as callback-based and sets its handler
  void MarkMethodCallback(int index, internal::MethodHandler* handler) {
    size_t idx = static_cast<size_t>(index);
    ABSL_CHECK_NE(methods_[idx].get(), nullptr)
        << "Cannot mark the method as 'callback' because it has already been "
           "marked as 'generic'.";
    methods_[idx]->SetHandler(handler);
    methods_[idx]->SetServerApiType(
        internal::RpcServiceMethod::ApiType::CALL_BACK);
  }

  // Marks a method as raw callback-based and sets its handler
  void MarkMethodRawCallback(int index, internal::MethodHandler* handler) {
    size_t idx = static_cast<size_t>(index);
    ABSL_CHECK_NE(methods_[idx].get(), nullptr)
        << "Cannot mark the method as 'raw callback' because it has already "
           "been marked as 'generic'.";
    methods_[idx]->SetHandler(handler);
    methods_[idx]->SetServerApiType(
        internal::RpcServiceMethod::ApiType::RAW_CALL_BACK);
  }

  // Gets the handler for a method at the given index
  internal::MethodHandler* GetHandler(int index) {
    size_t idx = static_cast<size_t>(index);
    return methods_[idx]->handler();
  }

 private:
  friend class Server;
  friend class ServerInterface;
  ServerInterface* server_;  // Pointer to the server interface
  std::vector<std::unique_ptr<internal::RpcServiceMethod>> methods_;  // Collection of service methods
};

}

#endif
```