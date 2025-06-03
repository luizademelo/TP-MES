Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

#ifndef GRPCPP_SERVER_INTERFACE_H
#define GRPCPP_SERVER_INTERFACE_H

// Include necessary gRPC headers
#include <grpc/grpc.h>
#include <grpc/impl/grpc_types.h>
#include <grpc/support/port_platform.h>
#include <grpc/support/time.h>
#include <grpcpp/impl/call.h>
#include <grpcpp/impl/call_hook.h>
#include <grpcpp/impl/codegen/interceptor_common.h>
#include <grpcpp/impl/completion_queue_tag.h>
#include <grpcpp/impl/rpc_service_method.h>
#include <grpcpp/server_context.h>
#include <grpcpp/support/byte_buffer.h>

// Include ABSL checking utilities
#include "absl/log/absl_check.h"

namespace grpc {

// Forward declarations
class AsyncGenericService;
class Channel;
class CompletionQueue;
class GenericServerContext;
class ServerCompletionQueue;
class ServerCredentials;
class Service;

namespace internal {
class ServerAsyncStreamingInterface;
}

class CallbackGenericService;

namespace experimental {
class ServerInterceptorFactoryInterface;
class ServerMetricRecorder;
}

// ServerInterface is the base class for gRPC server implementations.
// It provides core server functionality and serves as an interface for different server types.
class ServerInterface : public internal::CallHook {
 public:
  ~ServerInterface() override {}

  // Shutdown the server with a specific deadline
  template <class T>
  void Shutdown(const T& deadline) {
    ShutdownInternal(TimePoint<T>(deadline).raw_time());
  }

  // Shutdown the server immediately
  void Shutdown() { ShutdownInternal(gpr_inf_future(GPR_CLOCK_MONOTONIC)); }

  // Wait for the server to shutdown completely
  virtual void Wait() = 0;

 protected:
  friend class grpc::Service;

  // Register a service with the server
  virtual bool RegisterService(const std::string* host, Service* service) = 0;

  // Register an asynchronous generic service
  virtual void RegisterAsyncGenericService(AsyncGenericService* service) = 0;

  // Register a callback generic service (default empty implementation)
  virtual void RegisterCallbackGenericService(CallbackGenericService*) {}

  // Add a listening port to the server
  virtual int AddListeningPort(const std::string& addr,
                               ServerCredentials* creds) = 0;

  // Start the server with the given completion queues
  virtual void Start(grpc::ServerCompletionQueue** cqs, size_t num_cqs) = 0;

  // Internal shutdown implementation with a deadline
  virtual void ShutdownInternal(gpr_timespec deadline) = 0;

  // Get the maximum receive message size
  virtual int max_receive_message_size() const = 0;

  // Get the underlying gRPC server object
  virtual grpc_server* server() = 0;

  // Perform operations on a call
  void PerformOpsOnCall(internal::CallOpSetInterface* ops,
                        internal::Call* call) override = 0;

  // Base class for asynchronous request handling
  class BaseAsyncRequest : public internal::CompletionQueueTag {
   public:
    BaseAsyncRequest(ServerInterface* server, grpc::ServerContext* context,
                     internal::ServerAsyncStreamingInterface* stream,
                     grpc::CompletionQueue* call_cq,
                     grpc::ServerCompletionQueue* notification_cq, void* tag,
                     bool delete_on_finalize);
    ~BaseAsyncRequest() override;

    // Finalize the result of the asynchronous operation
    bool FinalizeResult(void** tag, bool* status) override;

   private:
    // Continue finalization after interception
    void ContinueFinalizeResultAfterInterception();

   protected:
    ServerInterface* const server_;  // The server instance
    grpc::ServerContext* const context_;  // Server context for the call
    internal::ServerAsyncStreamingInterface* const stream_;  // Streaming interface
    grpc::CompletionQueue* const call_cq_;  // Completion queue for calls
    grpc::ServerCompletionQueue* const notification_cq_;  // Notification queue
    void* const tag_;  // Tag associated with the request
    const bool delete_on_finalize_;  // Whether to delete on finalization
    grpc_call* call_;  // The underlying gRPC call
    internal::Call call_wrapper_;  // Wrapper for the call
    internal::InterceptorBatchMethodsImpl interceptor_methods_;  // Interceptor methods
    bool done_intercepting_;  // Flag for interception completion
    bool call_metric_recording_enabled_;  // Flag for metric recording
    experimental::ServerMetricRecorder* server_metric_recorder_;  // Metric recorder
  };

  // Class for handling registered asynchronous requests
  class RegisteredAsyncRequest : public BaseAsyncRequest {
   public:
    RegisteredAsyncRequest(ServerInterface* server,
                           grpc::ServerContext* context,
                           internal::ServerAsyncStreamingInterface* stream,
                           grpc::CompletionQueue* call_cq,
                           grpc::ServerCompletionQueue* notification_cq,
                           void* tag, const char* name,
                           internal::RpcMethod::RpcType type);

    // Finalize the result with additional RPC method information
    bool FinalizeResult(void** tag, bool* status) override {
      if (done_intercepting_) {
        return BaseAsyncRequest::FinalizeResult(tag, status);
      }
      call_wrapper_ = grpc::internal::Call(
          call_, server_, call_cq_, server_->max_receive_message_size(),
          context_->set_server_rpc_info(name_, type_,
                                        *server_->interceptor_creators()));
      return BaseAsyncRequest::FinalizeResult(tag, status);
    }

   protected:
    // Issue the actual request to the server
    void IssueRequest(void* registered_method, grpc_byte_buffer** payload,
                      grpc::ServerCompletionQueue* notification_cq);
    const char* name_;  // Name of the RPC method
    const internal::RpcMethod::RpcType type_;  // Type of the RPC method
  };

  // Class for handling requests without payload
  class NoPayloadAsyncRequest final : public RegisteredAsyncRequest {
   public:
    NoPayloadAsyncRequest(internal::RpcServiceMethod* registered_method,
                          ServerInterface* server, grpc::ServerContext* context,
                          internal::ServerAsyncStreamingInterface* stream,
                          grpc::CompletionQueue* call_cq,
                          grpc::ServerCompletionQueue* notification_cq,
                          void* tag)
        : RegisteredAsyncRequest(
              server, context, stream, call_cq, notification_cq, tag,
              registered_method->name(), registered_method->method_type()) {
      IssueRequest(registered_method->server_tag(), nullptr, notification_cq);
    }
  };

  // Template class for handling requests with payload
  template <class Message>
  class PayloadAsyncRequest final : public RegisteredAsyncRequest {
   public:
    PayloadAsyncRequest(internal::RpcServiceMethod* registered_method,
                        ServerInterface* server, grpc::ServerContext* context,
                        internal::ServerAsyncStreamingInterface* stream,
                        grpc::CompletionQueue* call_cq,
                        grpc::ServerCompletionQueue* notification_cq, void* tag,
                        Message* request)
        : RegisteredAsyncRequest(
              server, context, stream, call_cq, notification_cq, tag,
              registered_method->name(), registered_method->method_type()),
          registered_method_(registered_method),
          request_(request) {
      IssueRequest(registered_method->server_tag(), payload_.bbuf_ptr(),
                   notification_cq);
    }

    ~PayloadAsyncRequest() override {
      payload_.Release();
    }

    // Finalize the result with payload handling
    bool FinalizeResult(void** tag, bool* status) override {
      if (done_intercepting_) {
        return RegisteredAsyncRequest::FinalizeResult(tag, status);
      }
      if (*status) {
        // Validate and deserialize the payload
        if (!payload_.Valid() || !SerializationTraits<Message>::Deserialize(
                                      payload_.bbuf_ptr(), request_)
                                      .ok()) {
          // Handle parsing failure
          grpc_call_cancel_with_status(call_, GRPC_STATUS_INTERNAL,
                                       "Unable to parse request", nullptr);
          grpc_call_unref(call_);
          new PayloadAsyncRequest(registered_method_, server_, context_,
                                  stream_, call_cq_, notification_cq_, tag_,
                                  request_);
          delete this;
          return false;
        }
      }

      // Add post-receive message interception point
      interceptor_methods_.AddInterceptionHookPoint(
          experimental::InterceptionHookPoints::POST_RECV_MESSAGE);
      interceptor_methods_.SetRecvMessage(request_, nullptr);
      return RegisteredAsyncRequest::FinalizeResult(tag, status);
    }

   private:
    internal::RpcServiceMethod* const registered_method_;  // The RPC method
    Message* const request_;  // The request message
    ByteBuffer payload_;  // The payload buffer
  };

  // Class for handling generic asynchronous requests
  class GenericAsyncRequest : public BaseAsyncRequest {
   public:
    GenericAsyncRequest(ServerInterface* server, GenericServerContext* context,
                        internal::ServerAsyncStreamingInterface* stream,
                        grpc::CompletionQueue* call_cq,
                        grpc::ServerCompletionQueue* notification_cq, void* tag,
                        bool delete_on_finalize, bool issue_request = true);

    bool FinalizeResult(void** tag, bool* status) override;

   protected:
    void IssueRequest();

   private:
    grpc_call_details call_details_;  // Details of the call
  };

  // Request an asynchronous call with a message payload
  template <class Message>
  void RequestAsyncCall(internal::RpcServiceMethod* method,
                        grpc::ServerContext* context,
                        internal::ServerAsyncStreamingInterface* stream,
                        grpc::CompletionQueue* call_cq,
                        grpc::ServerCompletionQueue* notification_cq, void* tag,
                        Message* message) {
    ABSL_CHECK(method);
    new PayloadAsyncRequest<Message>(method, this, context, stream, call_cq,
                                     notification_cq, tag, message);
  }

  // Request an asynchronous call without a message payload
  void RequestAsyncCall(internal::RpcServiceMethod* method,
                        grpc::ServerContext* context,
                        internal::ServerAsyncStreamingInterface* stream,
                        grpc::CompletionQueue* call_cq,
                        grpc::ServerCompletionQueue* notification_cq,
                        void* tag) {
    ABSL_CHECK(method);
    new NoPayloadAsyncRequest(method, this, context, stream, call_cq,
                              notification_cq, tag);
  }

  // Request a generic asynchronous call
  void RequestAsyncGenericCall(GenericServerContext* context,
                               internal::ServerAsyncStreamingInterface* stream,
                               grpc::CompletionQueue* call_cq,
                               grpc::ServerCompletionQueue* notification_cq,
                               void* tag) {
    new GenericAsyncRequest(this, context, stream, call_cq, notification_cq,
                            tag, true);
  }

 private:
  // Get the interceptor creators (default returns nullptr)
  virtual std::vector<
      std::unique_ptr<experimental::ServerInterceptorFactoryInterface>>*
  interceptor_creators() {
    return nullptr;
  }

  // Check if call metric recording is enabled
  virtual bool call_metric_recording_enabled() const = 0;

  // Get the server metric recorder
  virtual experimental::ServerMetricRecorder* server_metric_recorder()
      const = 0;

  // Get the callback completion queue (default returns nullptr)
  virtual grpc::CompletionQueue* CallbackCQ() { return nullptr; }
};

}  // namespace grpc

#endif  // GRPCPP_SERVER_INTERFACE_H
```