
// Copyright 2015 gRPC authors.

#ifndef GRPCPP_SERVER_INTERFACE_H
#define GRPCPP_SERVER_INTERFACE_H

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

#include "absl/log/absl_check.h"

namespace grpc {

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

class ServerInterface : public internal::CallHook {
 public:
  ~ServerInterface() override {}

  template <class T>
  void Shutdown(const T& deadline) {
    ShutdownInternal(TimePoint<T>(deadline).raw_time());
  }

  void Shutdown() { ShutdownInternal(gpr_inf_future(GPR_CLOCK_MONOTONIC)); }

  virtual void Wait() = 0;

 protected:
  friend class grpc::Service;

  virtual bool RegisterService(const std::string* host, Service* service) = 0;

  virtual void RegisterAsyncGenericService(AsyncGenericService* service) = 0;

  virtual void RegisterCallbackGenericService(CallbackGenericService*
                                              ) {}

  virtual int AddListeningPort(const std::string& addr,
                               ServerCredentials* creds) = 0;

  virtual void Start(grpc::ServerCompletionQueue** cqs, size_t num_cqs) = 0;

  virtual void ShutdownInternal(gpr_timespec deadline) = 0;

  virtual int max_receive_message_size() const = 0;

  virtual grpc_server* server() = 0;

  void PerformOpsOnCall(internal::CallOpSetInterface* ops,
                        internal::Call* call) override = 0;

  class BaseAsyncRequest : public internal::CompletionQueueTag {
   public:
    BaseAsyncRequest(ServerInterface* server, grpc::ServerContext* context,
                     internal::ServerAsyncStreamingInterface* stream,
                     grpc::CompletionQueue* call_cq,
                     grpc::ServerCompletionQueue* notification_cq, void* tag,
                     bool delete_on_finalize);
    ~BaseAsyncRequest() override;

    bool FinalizeResult(void** tag, bool* status) override;

   private:
    void ContinueFinalizeResultAfterInterception();

   protected:
    ServerInterface* const server_;
    grpc::ServerContext* const context_;
    internal::ServerAsyncStreamingInterface* const stream_;
    grpc::CompletionQueue* const call_cq_;
    grpc::ServerCompletionQueue* const notification_cq_;
    void* const tag_;
    const bool delete_on_finalize_;
    grpc_call* call_;
    internal::Call call_wrapper_;
    internal::InterceptorBatchMethodsImpl interceptor_methods_;
    bool done_intercepting_;
    bool call_metric_recording_enabled_;
    experimental::ServerMetricRecorder* server_metric_recorder_;
  };

  class RegisteredAsyncRequest : public BaseAsyncRequest {
   public:
    RegisteredAsyncRequest(ServerInterface* server,
                           grpc::ServerContext* context,
                           internal::ServerAsyncStreamingInterface* stream,
                           grpc::CompletionQueue* call_cq,
                           grpc::ServerCompletionQueue* notification_cq,
                           void* tag, const char* name,
                           internal::RpcMethod::RpcType type);

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
    void IssueRequest(void* registered_method, grpc_byte_buffer** payload,
                      grpc::ServerCompletionQueue* notification_cq);
    const char* name_;
    const internal::RpcMethod::RpcType type_;
  };

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

    bool FinalizeResult(void** tag, bool* status) override {

      if (done_intercepting_) {
        return RegisteredAsyncRequest::FinalizeResult(tag, status);
      }
      if (*status) {
        if (!payload_.Valid() || !SerializationTraits<Message>::Deserialize(
                                      payload_.bbuf_ptr(), request_)
                                      .ok()) {

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

      interceptor_methods_.AddInterceptionHookPoint(
          experimental::InterceptionHookPoints::POST_RECV_MESSAGE);
      interceptor_methods_.SetRecvMessage(request_, nullptr);
      return RegisteredAsyncRequest::FinalizeResult(tag, status);
    }

   private:
    internal::RpcServiceMethod* const registered_method_;
    Message* const request_;
    ByteBuffer payload_;
  };

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
    grpc_call_details call_details_;
  };

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

  void RequestAsyncGenericCall(GenericServerContext* context,
                               internal::ServerAsyncStreamingInterface* stream,
                               grpc::CompletionQueue* call_cq,
                               grpc::ServerCompletionQueue* notification_cq,
                               void* tag) {
    new GenericAsyncRequest(this, context, stream, call_cq, notification_cq,
                            tag, true);
  }

 private:

  virtual std::vector<
      std::unique_ptr<experimental::ServerInterceptorFactoryInterface>>*
  interceptor_creators() {
    return nullptr;
  }

  virtual bool call_metric_recording_enabled() const = 0;

  virtual experimental::ServerMetricRecorder* server_metric_recorder()
      const = 0;

  virtual grpc::CompletionQueue* CallbackCQ() { return nullptr; }
};

}

#endif
