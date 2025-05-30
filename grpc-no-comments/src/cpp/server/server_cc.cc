
// Copyright 2015 gRPC authors.

#include <grpc/byte_buffer.h>
#include <grpc/grpc.h>
#include <grpc/impl/channel_arg_names.h>
#include <grpc/slice.h>
#include <grpc/support/sync.h>
#include <grpc/support/time.h>
#include <grpcpp/channel.h>
#include <grpcpp/completion_queue.h>
#include <grpcpp/generic/async_generic_service.h>
#include <grpcpp/health_check_service_interface.h>
#include <grpcpp/impl/call.h>
#include <grpcpp/impl/call_op_set.h>
#include <grpcpp/impl/call_op_set_interface.h>
#include <grpcpp/impl/completion_queue_tag.h>
#include <grpcpp/impl/interceptor_common.h>
#include <grpcpp/impl/metadata_map.h>
#include <grpcpp/impl/rpc_method.h>
#include <grpcpp/impl/rpc_service_method.h>
#include <grpcpp/impl/server_callback_handlers.h>
#include <grpcpp/impl/server_initializer.h>
#include <grpcpp/impl/service_type.h>
#include <grpcpp/impl/sync.h>
#include <grpcpp/security/server_credentials.h>
#include <grpcpp/server.h>
#include <grpcpp/server_context.h>
#include <grpcpp/server_interface.h>
#include <grpcpp/support/byte_buffer.h>
#include <grpcpp/support/channel_arguments.h>
#include <grpcpp/support/client_interceptor.h>
#include <grpcpp/support/interceptor.h>
#include <grpcpp/support/method_handler.h>
#include <grpcpp/support/server_interceptor.h>
#include <grpcpp/support/slice.h>
#include <grpcpp/support/status.h>
#include <limits.h>
#include <string.h>

#include <algorithm>
#include <atomic>
#include <cstdlib>
#include <memory>
#include <new>
#include <sstream>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/status/status.h"
#include "src/core/ext/transport/inproc/inproc_transport.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/iomgr/iomgr.h"
#include "src/core/lib/resource_quota/api.h"
#include "src/core/lib/surface/completion_queue.h"
#include "src/core/server/server.h"
#include "src/core/util/manual_constructor.h"
#include "src/cpp/client/create_channel_internal.h"
#include "src/cpp/server/external_connection_acceptor_impl.h"
#include "src/cpp/server/health/default_health_check_service.h"
#include "src/cpp/thread_manager/thread_manager.h"

namespace grpc {
namespace {

#define DEFAULT_MAX_SYNC_SERVER_THREADS INT_MAX

const char* kServerThreadpoolExhausted = "Server Threadpool Exhausted";

const char* kUnknownRpcMethod = "";

class DefaultGlobalCallbacks final : public Server::GlobalCallbacks {
 public:
  ~DefaultGlobalCallbacks() override {}
  void PreSynchronousRequest(ServerContext* ) override {}
  void PostSynchronousRequest(ServerContext* ) override {}
};

std::shared_ptr<Server::GlobalCallbacks> g_callbacks = nullptr;
Server::GlobalCallbacks* g_raw_callbacks = nullptr;
gpr_once g_once_init_callbacks = GPR_ONCE_INIT;

void InitGlobalCallbacks() {
  if (grpc_core::IsServerGlobalCallbacksOwnershipEnabled()) {
    if (!g_raw_callbacks) {
      g_raw_callbacks = new DefaultGlobalCallbacks;
    }
  } else {
    if (!g_callbacks) {
      g_callbacks = std::make_shared<DefaultGlobalCallbacks>();
    }
  }
}

class ShutdownTag : public internal::CompletionQueueTag {
 public:
  bool FinalizeResult(void** , bool* ) override {
    return false;
  }
};

class PhonyTag : public internal::CompletionQueueTag {
 public:
  bool FinalizeResult(void** , bool* ) override {
    return true;
  }
};

class UnimplementedAsyncRequestContext {
 protected:
  UnimplementedAsyncRequestContext() : generic_stream_(&server_context_) {}

  GenericServerContext server_context_;
  GenericServerAsyncReaderWriter generic_stream_;
};

}

ServerInterface::BaseAsyncRequest::BaseAsyncRequest(
    ServerInterface* server, ServerContext* context,
    internal::ServerAsyncStreamingInterface* stream, CompletionQueue* call_cq,
    ServerCompletionQueue* notification_cq, void* tag, bool delete_on_finalize)
    : server_(server),
      context_(context),
      stream_(stream),
      call_cq_(call_cq),
      notification_cq_(notification_cq),
      tag_(tag),
      delete_on_finalize_(delete_on_finalize),
      call_(nullptr),
      done_intercepting_(false) {

  interceptor_methods_.SetCall(&call_wrapper_);
  interceptor_methods_.SetReverse();
  call_cq_->RegisterAvalanching();
  call_metric_recording_enabled_ = server_->call_metric_recording_enabled();
  server_metric_recorder_ = server_->server_metric_recorder();
}

ServerInterface::BaseAsyncRequest::~BaseAsyncRequest() {
  call_cq_->CompleteAvalanching();
}

bool ServerInterface::BaseAsyncRequest::FinalizeResult(void** tag,
                                                       bool* status) {
  if (done_intercepting_) {
    *tag = tag_;
    if (delete_on_finalize_) {
      delete this;
    }
    return true;
  }
  context_->set_call(call_, call_metric_recording_enabled_,
                     server_metric_recorder_);
  context_->cq_ = call_cq_;
  if (call_wrapper_.call() == nullptr) {

    call_wrapper_ = internal::Call(
        call_, server_, call_cq_, server_->max_receive_message_size(), nullptr);
  }

  stream_->BindCall(&call_wrapper_);

  if (*status && call_ && call_wrapper_.server_rpc_info()) {
    done_intercepting_ = true;

    interceptor_methods_.AddInterceptionHookPoint(
        experimental::InterceptionHookPoints::POST_RECV_INITIAL_METADATA);
    interceptor_methods_.SetRecvInitialMetadata(&context_->client_metadata_);
    if (interceptor_methods_.RunInterceptors(
            [this]() { ContinueFinalizeResultAfterInterception(); })) {

    } else {

      return false;
    }
  }
  if (*status && call_) {
    context_->BeginCompletionOp(&call_wrapper_, nullptr, nullptr);
  }
  *tag = tag_;
  if (delete_on_finalize_) {
    delete this;
  }
  return true;
}

void ServerInterface::BaseAsyncRequest::
    ContinueFinalizeResultAfterInterception() {
  context_->BeginCompletionOp(&call_wrapper_, nullptr, nullptr);

  grpc_core::ExecCtx exec_ctx;
  grpc_cq_begin_op(notification_cq_->cq(), this);
  grpc_cq_end_op(
      notification_cq_->cq(), this, absl::OkStatus(),
      [](void* , grpc_cq_completion* completion) { delete completion; },
      nullptr, new grpc_cq_completion());
}

ServerInterface::RegisteredAsyncRequest::RegisteredAsyncRequest(
    ServerInterface* server, ServerContext* context,
    internal::ServerAsyncStreamingInterface* stream, CompletionQueue* call_cq,
    ServerCompletionQueue* notification_cq, void* tag, const char* name,
    internal::RpcMethod::RpcType type)
    : BaseAsyncRequest(server, context, stream, call_cq, notification_cq, tag,
                       true),
      name_(name),
      type_(type) {}

void ServerInterface::RegisteredAsyncRequest::IssueRequest(
    void* registered_method, grpc_byte_buffer** payload,
    ServerCompletionQueue* notification_cq) {

  CHECK(grpc_server_request_registered_call(
            server_->server(), registered_method, &call_, &context_->deadline_,
            context_->client_metadata_.arr(), payload, call_cq_->cq(),
            notification_cq->cq(), this) == GRPC_CALL_OK);
}

ServerInterface::GenericAsyncRequest::GenericAsyncRequest(
    ServerInterface* server, GenericServerContext* context,
    internal::ServerAsyncStreamingInterface* stream, CompletionQueue* call_cq,
    ServerCompletionQueue* notification_cq, void* tag, bool delete_on_finalize,
    bool issue_request)
    : BaseAsyncRequest(server, context, stream, call_cq, notification_cq, tag,
                       delete_on_finalize) {
  grpc_call_details_init(&call_details_);
  CHECK(notification_cq);
  CHECK(call_cq);
  if (issue_request) {
    IssueRequest();
  }
}

bool ServerInterface::GenericAsyncRequest::FinalizeResult(void** tag,
                                                          bool* status) {

  if (done_intercepting_) {
    return BaseAsyncRequest::FinalizeResult(tag, status);
  }

  if (*status) {
    static_cast<GenericServerContext*>(context_)->method_ =
        StringFromCopiedSlice(call_details_.method);
    static_cast<GenericServerContext*>(context_)->host_ =
        StringFromCopiedSlice(call_details_.host);
    context_->deadline_ = call_details_.deadline;
  }
  grpc_slice_unref(call_details_.method);
  grpc_slice_unref(call_details_.host);
  call_wrapper_ = internal::Call(
      call_, server_, call_cq_, server_->max_receive_message_size(),
      context_->set_server_rpc_info(
          static_cast<GenericServerContext*>(context_)->method_.c_str(),
          internal::RpcMethod::BIDI_STREAMING,
          *server_->interceptor_creators()));
  return BaseAsyncRequest::FinalizeResult(tag, status);
}

void ServerInterface::GenericAsyncRequest::IssueRequest() {

  CHECK(grpc_server_request_call(server_->server(), &call_, &call_details_,
                                 context_->client_metadata_.arr(),
                                 call_cq_->cq(), notification_cq_->cq(),
                                 this) == GRPC_CALL_OK);
}

namespace {
class ShutdownCallback : public grpc_completion_queue_functor {
 public:
  ShutdownCallback() {
    functor_run = &ShutdownCallback::Run;

    inlineable = true;
  }

  void TakeCQ(CompletionQueue* cq) { cq_ = cq; }

  static void Run(grpc_completion_queue_functor* cb, int) {
    auto* callback = static_cast<ShutdownCallback*>(cb);
    delete callback->cq_;
    delete callback;
  }

 private:
  CompletionQueue* cq_ = nullptr;
};
}

class Server::UnimplementedAsyncRequest final
    : private grpc::UnimplementedAsyncRequestContext,
      public GenericAsyncRequest {
 public:
  UnimplementedAsyncRequest(ServerInterface* server,
                            grpc::ServerCompletionQueue* cq)
      : GenericAsyncRequest(server, &server_context_, &generic_stream_, cq, cq,
                            nullptr, false,
                            false) {

    IssueRequest();
  }

  bool FinalizeResult(void** tag, bool* status) override;

  grpc::ServerContext* context() { return &server_context_; }
  grpc::GenericServerAsyncReaderWriter* stream() { return &generic_stream_; }
};

class Server::UnimplementedAsyncResponse final
    : public grpc::internal::CallOpSet<
          grpc::internal::CallOpSendInitialMetadata,
          grpc::internal::CallOpServerSendStatus> {
 public:
  explicit UnimplementedAsyncResponse(UnimplementedAsyncRequest* request);
  ~UnimplementedAsyncResponse() override { delete request_; }

  bool FinalizeResult(void** tag, bool* status) override {
    if (grpc::internal::CallOpSet<
            grpc::internal::CallOpSendInitialMetadata,
            grpc::internal::CallOpServerSendStatus>::FinalizeResult(tag,
                                                                    status)) {
      delete this;
    } else {

    }
    return false;
  }

 private:
  UnimplementedAsyncRequest* const request_;
};

class Server::SyncRequest final : public grpc::internal::CompletionQueueTag {
 public:
  SyncRequest(Server* server, grpc::internal::RpcServiceMethod* method,
              grpc_core::Server::RegisteredCallAllocation* data)
      : SyncRequest(server, method) {
    CommonSetup(data);
    data->deadline = &deadline_;
    data->optional_payload = has_request_payload_ ? &request_payload_ : nullptr;
  }

  SyncRequest(Server* server, grpc::internal::RpcServiceMethod* method,
              grpc_core::Server::BatchCallAllocation* data)
      : SyncRequest(server, method) {
    CommonSetup(data);
    call_details_ = new grpc_call_details;
    grpc_call_details_init(call_details_);
    data->details = call_details_;
  }

  ~SyncRequest() override {

    if (has_request_payload_ && request_payload_) {
      grpc_byte_buffer_destroy(request_payload_);
    }
    if (call_details_ != nullptr) {
      grpc_call_details_destroy(call_details_);
      delete call_details_;
    }
    grpc_metadata_array_destroy(&request_metadata_);
    server_->UnrefWithPossibleNotify();
  }

  bool FinalizeResult(void** , bool* status) override {
    if (!*status) {
      delete this;
      return false;
    }
    if (call_details_) {
      deadline_ = call_details_->deadline;
    }
    return true;
  }

  void Run(const std::shared_ptr<GlobalCallbacks>& global_callbacks,
           bool resources) {
    ctx_.Init(deadline_, &request_metadata_);
    wrapped_call_.Init(
        call_, server_, &cq_, server_->max_receive_message_size(),
        ctx_->ctx.set_server_rpc_info(method_->name(), method_->method_type(),
                                      server_->interceptor_creators_));
    ctx_->ctx.set_call(call_, server_->call_metric_recording_enabled(),
                       server_->server_metric_recorder());
    ctx_->ctx.cq_ = &cq_;
    request_metadata_.count = 0;

    if (!grpc_core::IsServerGlobalCallbacksOwnershipEnabled()) {
      global_callbacks_ = global_callbacks;
    }
    resources_ = resources;

    interceptor_methods_.SetCall(&*wrapped_call_);
    interceptor_methods_.SetReverse();

    interceptor_methods_.AddInterceptionHookPoint(
        grpc::experimental::InterceptionHookPoints::POST_RECV_INITIAL_METADATA);
    interceptor_methods_.SetRecvInitialMetadata(&ctx_->ctx.client_metadata_);

    if (has_request_payload_) {

      auto* handler = resources_ ? method_->handler()
                                 : server_->resource_exhausted_handler_.get();
      deserialized_request_ = handler->Deserialize(call_, request_payload_,
                                                   &request_status_, nullptr);
      if (!request_status_.ok()) {
        VLOG(2) << "Failed to deserialize message.";
      }
      request_payload_ = nullptr;
      interceptor_methods_.AddInterceptionHookPoint(
          grpc::experimental::InterceptionHookPoints::POST_RECV_MESSAGE);
      interceptor_methods_.SetRecvMessage(deserialized_request_, nullptr);
    }

    if (interceptor_methods_.RunInterceptors(
            [this]() { ContinueRunAfterInterception(); })) {
      ContinueRunAfterInterception();
    } else {

    }
  }

  void ContinueRunAfterInterception() {
    ctx_->ctx.BeginCompletionOp(&*wrapped_call_, nullptr, nullptr);
    if (grpc_core::IsServerGlobalCallbacksOwnershipEnabled()) {
      g_raw_callbacks->PreSynchronousRequest(&ctx_->ctx);
    } else {
      global_callbacks_->PreSynchronousRequest(&ctx_->ctx);
    }
    auto* handler = resources_ ? method_->handler()
                               : server_->resource_exhausted_handler_.get();
    handler->RunHandler(grpc::internal::MethodHandler::HandlerParameter(
        &*wrapped_call_, &ctx_->ctx, deserialized_request_, request_status_,
        nullptr, nullptr));
    if (grpc_core::IsServerGlobalCallbacksOwnershipEnabled()) {
      g_raw_callbacks->PostSynchronousRequest(&ctx_->ctx);
    } else {
      global_callbacks_->PostSynchronousRequest(&ctx_->ctx);
    }

    cq_.Shutdown();

    grpc::internal::CompletionQueueTag* op_tag = ctx_->ctx.GetCompletionOpTag();
    cq_.TryPluck(op_tag, gpr_inf_future(GPR_CLOCK_REALTIME));

    grpc::PhonyTag ignored_tag;
    CHECK(cq_.Pluck(&ignored_tag) == false);

    wrapped_call_.Destroy();
    ctx_.Destroy();

    delete this;
  }

  void Cleanup() {
    cq_.Shutdown();
    grpc_call_unref(call_);
    delete this;
  }

 private:
  SyncRequest(Server* server, grpc::internal::RpcServiceMethod* method)
      : server_(server),
        method_(method),
        has_request_payload_(method->method_type() ==
                                 grpc::internal::RpcMethod::NORMAL_RPC ||
                             method->method_type() ==
                                 grpc::internal::RpcMethod::SERVER_STREAMING),
        cq_(grpc_completion_queue_create_for_pluck(nullptr)) {}

  template <class CallAllocation>
  void CommonSetup(CallAllocation* data) {
    server_->Ref();
    grpc_metadata_array_init(&request_metadata_);
    data->tag = static_cast<void*>(this);
    data->call = &call_;
    data->initial_metadata = &request_metadata_;
    data->cq = cq_.cq();
  }

  Server* const server_;
  grpc::internal::RpcServiceMethod* const method_;
  const bool has_request_payload_;
  grpc_call* call_;
  grpc_call_details* call_details_ = nullptr;
  gpr_timespec deadline_;
  grpc_metadata_array request_metadata_;
  grpc_byte_buffer* request_payload_ = nullptr;
  grpc::CompletionQueue cq_;
  grpc::Status request_status_;
  std::shared_ptr<GlobalCallbacks> global_callbacks_;
  bool resources_;
  void* deserialized_request_ = nullptr;
  grpc::internal::InterceptorBatchMethodsImpl interceptor_methods_;

  struct ServerContextWrapper {
    ServerContext ctx;

    ServerContextWrapper(gpr_timespec deadline, grpc_metadata_array* arr)
        : ctx(deadline, arr) {}
  };

  grpc_core::ManualConstructor<ServerContextWrapper> ctx_;
  grpc_core::ManualConstructor<internal::Call> wrapped_call_;
};

template <class ServerContextType>
class Server::CallbackRequest final
    : public grpc::internal::CompletionQueueTag {
 public:
  static_assert(
      std::is_base_of<grpc::CallbackServerContext, ServerContextType>::value,
      "ServerContextType must be derived from CallbackServerContext");

  CallbackRequest(Server* server, grpc::internal::RpcServiceMethod* method,
                  grpc::CompletionQueue* cq,
                  grpc_core::Server::RegisteredCallAllocation* data)
      : server_(server),
        method_(method),
        has_request_payload_(method->method_type() ==
                                 grpc::internal::RpcMethod::NORMAL_RPC ||
                             method->method_type() ==
                                 grpc::internal::RpcMethod::SERVER_STREAMING),
        cq_(cq),
        tag_(this),
        ctx_(server_->context_allocator() != nullptr
                 ? server_->context_allocator()->NewCallbackServerContext()
                 : nullptr) {
    CommonSetup(server, data);
    data->deadline = &deadline_;
    data->optional_payload = has_request_payload_ ? &request_payload_ : nullptr;
  }

  CallbackRequest(Server* server, grpc::CompletionQueue* cq,
                  grpc_core::Server::BatchCallAllocation* data)
      : server_(server),
        method_(nullptr),
        has_request_payload_(false),
        call_details_(new grpc_call_details),
        cq_(cq),
        tag_(this),
        ctx_(server_->context_allocator() != nullptr
                 ? server_->context_allocator()
                       ->NewGenericCallbackServerContext()
                 : nullptr) {
    CommonSetup(server, data);
    grpc_call_details_init(call_details_);
    data->details = call_details_;
  }

  ~CallbackRequest() override {
    delete call_details_;
    grpc_metadata_array_destroy(&request_metadata_);
    if (has_request_payload_ && request_payload_) {
      grpc_byte_buffer_destroy(request_payload_);
    }
    if (ctx_alloc_by_default_ || server_->context_allocator() == nullptr) {
      default_ctx_.Destroy();
    }
    server_->UnrefWithPossibleNotify();
  }

  bool FinalizeResult(void** tag, bool* status) override;

 private:

  const char* method_name() const;

  class CallbackCallTag : public grpc_completion_queue_functor {
   public:
    explicit CallbackCallTag(Server::CallbackRequest<ServerContextType>* req)
        : req_(req) {
      functor_run = &CallbackCallTag::StaticRun;

      inlineable = true;
    }

    void force_run(bool ok) { Run(ok); }

   private:
    Server::CallbackRequest<ServerContextType>* req_;
    grpc::internal::Call* call_;

    static void StaticRun(grpc_completion_queue_functor* cb, int ok) {
      static_cast<CallbackCallTag*>(cb)->Run(static_cast<bool>(ok));
    }
    void Run(bool ok) {
      void* ignored = req_;
      bool new_ok = ok;
      CHECK(!req_->FinalizeResult(&ignored, &new_ok));
      CHECK(ignored == req_);

      if (!ok) {

        delete req_;
        return;
      }

      req_->ctx_->set_call(req_->call_,
                           req_->server_->call_metric_recording_enabled(),
                           req_->server_->server_metric_recorder());
      req_->ctx_->cq_ = req_->cq_;
      req_->ctx_->BindDeadlineAndMetadata(req_->deadline_,
                                          &req_->request_metadata_);
      req_->request_metadata_.count = 0;

      call_ =
          new (grpc_call_arena_alloc(req_->call_, sizeof(grpc::internal::Call)))
              grpc::internal::Call(
                  req_->call_, req_->server_, req_->cq_,
                  req_->server_->max_receive_message_size(),
                  req_->ctx_->set_server_rpc_info(
                      req_->method_name(),
                      (req_->method_ != nullptr)
                          ? req_->method_->method_type()
                          : grpc::internal::RpcMethod::BIDI_STREAMING,
                      req_->server_->interceptor_creators_));

      req_->interceptor_methods_.SetCall(call_);
      req_->interceptor_methods_.SetReverse();

      req_->interceptor_methods_.AddInterceptionHookPoint(
          grpc::experimental::InterceptionHookPoints::
              POST_RECV_INITIAL_METADATA);
      req_->interceptor_methods_.SetRecvInitialMetadata(
          &req_->ctx_->client_metadata_);

      if (req_->has_request_payload_) {

        req_->request_ = req_->method_->handler()->Deserialize(
            req_->call_, req_->request_payload_, &req_->request_status_,
            &req_->handler_data_);
        if (!(req_->request_status_.ok())) {
          VLOG(2) << "Failed to deserialize message.";
        }
        req_->request_payload_ = nullptr;
        req_->interceptor_methods_.AddInterceptionHookPoint(
            grpc::experimental::InterceptionHookPoints::POST_RECV_MESSAGE);
        req_->interceptor_methods_.SetRecvMessage(req_->request_, nullptr);
      }

      if (req_->interceptor_methods_.RunInterceptors(
              [this] { ContinueRunAfterInterception(); })) {
        ContinueRunAfterInterception();
      } else {

      }
    }
    void ContinueRunAfterInterception() {
      auto* handler = (req_->method_ != nullptr)
                          ? req_->method_->handler()
                          : req_->server_->generic_handler_.get();
      handler->RunHandler(grpc::internal::MethodHandler::HandlerParameter(
          call_, req_->ctx_, req_->request_, req_->request_status_,
          req_->handler_data_, [this] { delete req_; }));
    }
  };

  template <class CallAllocation>
  void CommonSetup(Server* server, CallAllocation* data) {
    server->Ref();
    grpc_metadata_array_init(&request_metadata_);
    data->tag = static_cast<void*>(&tag_);
    data->call = &call_;
    data->initial_metadata = &request_metadata_;
    if (ctx_ == nullptr) {
      default_ctx_.Init();
      ctx_ = &*default_ctx_;
      ctx_alloc_by_default_ = true;
    }
    ctx_->set_context_allocator(server->context_allocator());
    data->cq = cq_->cq();
  }

  Server* const server_;
  grpc::internal::RpcServiceMethod* const method_;
  const bool has_request_payload_;
  grpc_byte_buffer* request_payload_ = nullptr;
  void* request_ = nullptr;
  void* handler_data_ = nullptr;
  grpc::Status request_status_;
  grpc_call_details* const call_details_ = nullptr;
  grpc_call* call_;
  gpr_timespec deadline_;
  grpc_metadata_array request_metadata_;
  grpc::CompletionQueue* const cq_;
  bool ctx_alloc_by_default_ = false;
  CallbackCallTag tag_;
  ServerContextType* ctx_ = nullptr;
  grpc_core::ManualConstructor<ServerContextType> default_ctx_;
  grpc::internal::InterceptorBatchMethodsImpl interceptor_methods_;
};

template <>
bool Server::CallbackRequest<grpc::CallbackServerContext>::FinalizeResult(
    void** , bool* ) {
  return false;
}

template <>
bool Server::CallbackRequest<
    grpc::GenericCallbackServerContext>::FinalizeResult(void** ,
                                                        bool* status) {
  if (*status) {
    deadline_ = call_details_->deadline;

    ctx_->method_ = grpc::StringFromCopiedSlice(call_details_->method);
    ctx_->host_ = grpc::StringFromCopiedSlice(call_details_->host);
  }
  grpc_slice_unref(call_details_->method);
  grpc_slice_unref(call_details_->host);
  return false;
}

template <>
const char* Server::CallbackRequest<grpc::CallbackServerContext>::method_name()
    const {
  return method_->name();
}

template <>
const char* Server::CallbackRequest<
    grpc::GenericCallbackServerContext>::method_name() const {
  return ctx_->method().c_str();
}

class Server::SyncRequestThreadManager : public grpc::ThreadManager {
 public:
  SyncRequestThreadManager(Server* server, grpc::CompletionQueue* server_cq,
                           std::shared_ptr<GlobalCallbacks> global_callbacks,
                           grpc_resource_quota* rq, int min_pollers,
                           int max_pollers, int cq_timeout_msec)
      : ThreadManager("SyncServer", rq, min_pollers, max_pollers),
        server_(server),
        server_cq_(server_cq),
        cq_timeout_msec_(cq_timeout_msec),
        global_callbacks_(std::move(global_callbacks)) {}

  WorkStatus PollForWork(void** tag, bool* ok) override {
    *tag = nullptr;

    gpr_timespec deadline =
        gpr_time_add(gpr_now(GPR_CLOCK_MONOTONIC),
                     gpr_time_from_millis(cq_timeout_msec_, GPR_TIMESPAN));

    switch (server_cq_->AsyncNext(tag, ok, deadline)) {
      case grpc::CompletionQueue::TIMEOUT:
        return TIMEOUT;
      case grpc::CompletionQueue::SHUTDOWN:
        return SHUTDOWN;
      case grpc::CompletionQueue::GOT_EVENT:
        return WORK_FOUND;
    }

    GPR_UNREACHABLE_CODE(return TIMEOUT);
  }

  void DoWork(void* tag, bool ok, bool resources) override {
    (void)ok;
    SyncRequest* sync_req = static_cast<SyncRequest*>(tag);

    DCHECK_NE(sync_req, nullptr);
    DCHECK(ok);

    sync_req->Run(global_callbacks_, resources);
  }

  void AddSyncMethod(grpc::internal::RpcServiceMethod* method, void* tag) {
    grpc_core::Server::FromC(server_->server())
        ->SetRegisteredMethodAllocator(server_cq_->cq(), tag, [this, method] {
          grpc_core::Server::RegisteredCallAllocation result;
          new SyncRequest(server_, method, &result);
          return result;
        });
    has_sync_method_ = true;
  }

  void AddUnknownSyncMethod() {
    if (has_sync_method_) {
      unknown_method_ = std::make_unique<grpc::internal::RpcServiceMethod>(
          "unknown", grpc::internal::RpcMethod::BIDI_STREAMING,
          new grpc::internal::UnknownMethodHandler(kUnknownRpcMethod));
      grpc_core::Server::FromC(server_->server())
          ->SetBatchMethodAllocator(server_cq_->cq(), [this] {
            grpc_core::Server::BatchCallAllocation result;
            new SyncRequest(server_, unknown_method_.get(), &result);
            return result;
          });
    }
  }

  void Shutdown() override {
    ThreadManager::Shutdown();
    server_cq_->Shutdown();
  }

  void Wait() override {
    ThreadManager::Wait();

    void* tag;
    bool ok;
    while (server_cq_->Next(&tag, &ok)) {

      static_cast<SyncRequest*>(tag)->Cleanup();
    }
  }

  void Start() {
    if (has_sync_method_) {
      Initialize();
    }
  }

 private:
  Server* server_;
  grpc::CompletionQueue* server_cq_;
  int cq_timeout_msec_;
  bool has_sync_method_ = false;
  std::unique_ptr<grpc::internal::RpcServiceMethod> unknown_method_;
  std::shared_ptr<Server::GlobalCallbacks> global_callbacks_;
};

Server::Server(
    grpc::ChannelArguments* args,
    std::shared_ptr<std::vector<std::unique_ptr<grpc::ServerCompletionQueue>>>
        sync_server_cqs,
    int min_pollers, int max_pollers, int sync_cq_timeout_msec,
    std::vector<std::shared_ptr<grpc::internal::ExternalConnectionAcceptorImpl>>
        acceptors,
    grpc_server_config_fetcher* server_config_fetcher,
    grpc_resource_quota* server_rq,
    std::vector<
        std::unique_ptr<grpc::experimental::ServerInterceptorFactoryInterface>>
        interceptor_creators,
    experimental::ServerMetricRecorder* server_metric_recorder)
    : acceptors_(std::move(acceptors)),
      interceptor_creators_(std::move(interceptor_creators)),
      max_receive_message_size_(INT_MIN),
      sync_server_cqs_(std::move(sync_server_cqs)),
      started_(false),
      shutdown_(false),
      shutdown_notified_(false),
      server_(nullptr),
      server_initializer_(new ServerInitializer(this)),
      health_check_service_disabled_(false),
      server_metric_recorder_(server_metric_recorder) {
  gpr_once_init(&grpc::g_once_init_callbacks, grpc::InitGlobalCallbacks);
  if (grpc_core::IsServerGlobalCallbacksOwnershipEnabled()) {
    g_raw_callbacks->UpdateArguments(args);
  } else {
    global_callbacks_ = grpc::g_callbacks;
    global_callbacks_->UpdateArguments(args);
  }

  if (sync_server_cqs_ != nullptr) {
    bool default_rq_created = false;
    if (server_rq == nullptr) {
      server_rq = grpc_resource_quota_create("SyncServer-default-rq");
      grpc_resource_quota_set_max_threads(server_rq,
                                          DEFAULT_MAX_SYNC_SERVER_THREADS);
      default_rq_created = true;
    }

    for (const auto& it : *sync_server_cqs_) {
      sync_req_mgrs_.emplace_back(new SyncRequestThreadManager(
          this, it.get(), global_callbacks_, server_rq, min_pollers,
          max_pollers, sync_cq_timeout_msec));
    }

    if (default_rq_created) {
      grpc_resource_quota_unref(server_rq);
    }
  }

  for (auto& acceptor : acceptors_) {
    acceptor->SetToChannelArgs(args);
  }

  grpc_channel_args channel_args;
  args->SetChannelArgs(&channel_args);

  for (size_t i = 0; i < channel_args.num_args; i++) {
    if (0 == strcmp(channel_args.args[i].key,
                    grpc::kHealthCheckServiceInterfaceArg)) {
      if (channel_args.args[i].value.pointer.p == nullptr) {
        health_check_service_disabled_ = true;
      } else {
        health_check_service_.reset(
            static_cast<grpc::HealthCheckServiceInterface*>(
                channel_args.args[i].value.pointer.p));
      }
    }
    if (0 ==
        strcmp(channel_args.args[i].key, GRPC_ARG_MAX_RECEIVE_MESSAGE_LENGTH)) {
      max_receive_message_size_ = channel_args.args[i].value.integer;
    }
    if (0 == strcmp(channel_args.args[i].key,
                    GRPC_ARG_SERVER_CALL_METRIC_RECORDING)) {
      call_metric_recording_enabled_ = channel_args.args[i].value.integer;
    }
  }
  server_ = grpc_server_create(&channel_args, nullptr);
  grpc_server_set_config_fetcher(server_, server_config_fetcher);
}

Server::~Server() {
  {
    grpc::internal::ReleasableMutexLock lock(&mu_);
    if (started_ && !shutdown_) {
      lock.Release();
      Shutdown();
    } else if (!started_) {

      for (const auto& value : sync_req_mgrs_) {
        value->Shutdown();
      }
      CompletionQueue* callback_cq =
          callback_cq_.load(std::memory_order_relaxed);
      if (callback_cq != nullptr) {
        if (grpc_iomgr_run_in_background()) {

          callback_cq->Shutdown();
        } else {
          CompletionQueue::ReleaseCallbackAlternativeCQ(callback_cq);
        }
        callback_cq_.store(nullptr, std::memory_order_release);
      }
    }
  }

  health_check_service_.reset();
  grpc_server_destroy(server_);
}

void Server::SetGlobalCallbacks(GlobalCallbacks* callbacks) {
  if (grpc_core::IsServerGlobalCallbacksOwnershipEnabled()) {
    CHECK(!g_raw_callbacks);
    CHECK(callbacks);
    g_raw_callbacks = callbacks;
  } else {
    CHECK(!g_callbacks);
    CHECK(callbacks);
    g_callbacks.reset(callbacks);
  }
}

grpc_server* Server::c_server() { return server_; }

std::shared_ptr<grpc::Channel> Server::InProcessChannel(
    const grpc::ChannelArguments& args) {
  grpc_channel_args channel_args = args.c_channel_args();
  return grpc::CreateChannelInternal(
      "inproc", grpc_inproc_channel_create(server_, &channel_args, nullptr),
      std::vector<std::unique_ptr<
          grpc::experimental::ClientInterceptorFactoryInterface>>());
}

std::shared_ptr<grpc::Channel>
Server::experimental_type::InProcessChannelWithInterceptors(
    const grpc::ChannelArguments& args,
    std::vector<
        std::unique_ptr<grpc::experimental::ClientInterceptorFactoryInterface>>
        interceptor_creators) {
  grpc_channel_args channel_args = args.c_channel_args();
  return grpc::CreateChannelInternal(
      "inproc",
      grpc_inproc_channel_create(server_->server_, &channel_args, nullptr),
      std::move(interceptor_creators));
}

static grpc_server_register_method_payload_handling PayloadHandlingForMethod(
    grpc::internal::RpcServiceMethod* method) {
  switch (method->method_type()) {
    case grpc::internal::RpcMethod::NORMAL_RPC:
    case grpc::internal::RpcMethod::SERVER_STREAMING:
      return GRPC_SRM_PAYLOAD_READ_INITIAL_BYTE_BUFFER;
    case grpc::internal::RpcMethod::CLIENT_STREAMING:
    case grpc::internal::RpcMethod::BIDI_STREAMING:
      return GRPC_SRM_PAYLOAD_NONE;
  }
  GPR_UNREACHABLE_CODE(return GRPC_SRM_PAYLOAD_NONE;);
}

bool Server::RegisterService(const std::string* addr, grpc::Service* service) {
  bool has_async_methods = service->has_async_methods();
  if (has_async_methods) {
    CHECK_EQ(service->server_, nullptr)
        << "Can only register an asynchronous service against one server.";
    service->server_ = this;
  }

  const char* method_name = nullptr;

  for (const auto& method : service->methods_) {
    if (method == nullptr) {
      continue;
    }

    void* method_registration_tag = grpc_server_register_method(
        server_, method->name(), addr ? addr->c_str() : nullptr,
        PayloadHandlingForMethod(method.get()), 0);
    if (method_registration_tag == nullptr) {
      VLOG(2) << "Attempt to register " << method->name() << " multiple times";
      return false;
    }

    if (method->handler() == nullptr) {
      method->set_server_tag(method_registration_tag);
    } else if (method->api_type() ==
               grpc::internal::RpcServiceMethod::ApiType::SYNC) {
      for (const auto& value : sync_req_mgrs_) {
        value->AddSyncMethod(method.get(), method_registration_tag);
      }
    } else {
      has_callback_methods_ = true;
      grpc::internal::RpcServiceMethod* method_value = method.get();
      grpc::CompletionQueue* cq = CallbackCQ();
      grpc_server_register_completion_queue(server_, cq->cq(), nullptr);
      grpc_core::Server::FromC(server_)->SetRegisteredMethodAllocator(
          cq->cq(), method_registration_tag, [this, cq, method_value] {
            grpc_core::Server::RegisteredCallAllocation result;
            new CallbackRequest<grpc::CallbackServerContext>(this, method_value,
                                                             cq, &result);
            return result;
          });
    }

    method_name = method->name();
  }

  if (method_name != nullptr) {
    std::stringstream ss(method_name);
    std::string service_name;
    if (std::getline(ss, service_name, '/') &&
        std::getline(ss, service_name, '/')) {
      services_.push_back(service_name);
    }
  }
  return true;
}

void Server::RegisterAsyncGenericService(grpc::AsyncGenericService* service) {
  CHECK_EQ(service->server_, nullptr)
      << "Can only register an async generic service against one server.";
  service->server_ = this;
  has_async_generic_service_ = true;
}

void Server::RegisterCallbackGenericService(
    grpc::CallbackGenericService* service) {
  CHECK_EQ(service->server_, nullptr)
      << "Can only register a callback generic service against one server.";
  service->server_ = this;
  has_callback_generic_service_ = true;
  generic_handler_.reset(service->Handler());

  grpc::CompletionQueue* cq = CallbackCQ();
  grpc_core::Server::FromC(server_)->SetBatchMethodAllocator(cq->cq(), [this,
                                                                        cq] {
    grpc_core::Server::BatchCallAllocation result;
    new CallbackRequest<grpc::GenericCallbackServerContext>(this, cq, &result);
    return result;
  });
}

int Server::AddListeningPort(const std::string& addr,
                             grpc::ServerCredentials* creds) {
  CHECK(!started_);
  int port = creds->AddPortToServer(addr, server_);
  if (grpc_core::IsServerGlobalCallbacksOwnershipEnabled()) {
    g_raw_callbacks->AddPort(this, addr, creds, port);
  } else {
    global_callbacks_->AddPort(this, addr, creds, port);
  }
  return port;
}

void Server::Ref() {
  shutdown_refs_outstanding_.fetch_add(1, std::memory_order_relaxed);
}

void Server::UnrefWithPossibleNotify() {
  if (GPR_UNLIKELY(shutdown_refs_outstanding_.fetch_sub(
                       1, std::memory_order_acq_rel) == 1)) {

    grpc::internal::MutexLock lock(&mu_);
    CHECK(shutdown_);
    shutdown_done_ = true;
    shutdown_done_cv_.Signal();
  }
}

void Server::UnrefAndWaitLocked() {
  if (GPR_UNLIKELY(shutdown_refs_outstanding_.fetch_sub(
                       1, std::memory_order_acq_rel) == 1)) {
    shutdown_done_ = true;
    return;
  }
  while (!shutdown_done_) {
    shutdown_done_cv_.Wait(&mu_);
  }
}

void Server::Start(grpc::ServerCompletionQueue** cqs, size_t num_cqs) {
  CHECK(!started_);
  if (grpc_core::IsServerGlobalCallbacksOwnershipEnabled()) {
    g_raw_callbacks->PreServerStart(this);
  } else {
    g_callbacks->PreServerStart(this);
  }
  started_ = true;

  if (health_check_service_ == nullptr && !health_check_service_disabled_ &&
      grpc::DefaultHealthCheckServiceEnabled()) {
    auto default_hc_service = std::make_unique<DefaultHealthCheckService>();
    auto* hc_service_impl = default_hc_service->GetHealthCheckService();
    health_check_service_ = std::move(default_hc_service);
    RegisterService(nullptr, hc_service_impl);
  }

  for (auto& acceptor : acceptors_) {
    acceptor->GetCredentials()->AddPortToServer(acceptor->name(), server_);
  }

#ifndef NDEBUG
  for (size_t i = 0; i < num_cqs; i++) {
    cq_list_.push_back(cqs[i]);
  }
#endif

  bool unknown_rpc_needed =
      !has_async_generic_service_ && !has_callback_generic_service_;
  if (unknown_rpc_needed && has_callback_methods_) {
    unimplemented_service_ = std::make_unique<grpc::CallbackGenericService>();
    RegisterCallbackGenericService(unimplemented_service_.get());
    unknown_rpc_needed = false;
  }
  if (unknown_rpc_needed && !sync_req_mgrs_.empty()) {
    sync_req_mgrs_[0]->AddUnknownSyncMethod();
    unknown_rpc_needed = false;
  }

  grpc_server_start(server_);

  if (unknown_rpc_needed) {
    for (size_t i = 0; i < num_cqs; i++) {
      if (cqs[i]->IsFrequentlyPolled()) {
        new UnimplementedAsyncRequest(this, cqs[i]);
      }
    }
    unknown_rpc_needed = false;
  }

  if (sync_server_cqs_ != nullptr && !sync_server_cqs_->empty()) {
    resource_exhausted_handler_ =
        std::make_unique<grpc::internal::ResourceExhaustedHandler>(
            kServerThreadpoolExhausted);
  }

  for (const auto& value : sync_req_mgrs_) {
    value->Start();
  }

  for (auto& acceptor : acceptors_) {
    acceptor->Start();
  }
}

void Server::ShutdownInternal(gpr_timespec deadline) {
  grpc::internal::MutexLock lock(&mu_);
  if (shutdown_) {
    return;
  }

  shutdown_ = true;

  for (auto& acceptor : acceptors_) {
    acceptor->Shutdown();
  }

  grpc::CompletionQueue shutdown_cq;
  grpc::ShutdownTag shutdown_tag;
  grpc_server_shutdown_and_notify(server_, shutdown_cq.cq(), &shutdown_tag);

  shutdown_cq.Shutdown();

  void* tag;
  bool ok;
  grpc::CompletionQueue::NextStatus status =
      shutdown_cq.AsyncNext(&tag, &ok, deadline);

  if (status == grpc::CompletionQueue::NextStatus::TIMEOUT) {
    grpc_server_cancel_all_calls(server_);
    status =
        shutdown_cq.AsyncNext(&tag, &ok, gpr_inf_future(GPR_CLOCK_MONOTONIC));
  }

  UnrefAndWaitLocked();

  for (const auto& value : sync_req_mgrs_) {
    value->Shutdown();
  }

  for (const auto& value : sync_req_mgrs_) {
    value->Wait();
  }

  CompletionQueue* callback_cq = callback_cq_.load(std::memory_order_relaxed);
  if (callback_cq != nullptr) {
    if (grpc_iomgr_run_in_background()) {

      callback_cq->Shutdown();
    } else {
      CompletionQueue::ReleaseCallbackAlternativeCQ(callback_cq);
    }
    callback_cq_.store(nullptr, std::memory_order_release);
  }

  while (shutdown_cq.Next(&tag, &ok)) {

  }

  shutdown_notified_ = true;
  shutdown_cv_.SignalAll();

#ifndef NDEBUG

  for (auto* cq : cq_list_) {
    cq->UnregisterServer(this);
  }
  cq_list_.clear();
#endif
}

void Server::Wait() {
  grpc::internal::MutexLock lock(&mu_);
  while (started_ && !shutdown_notified_) {
    shutdown_cv_.Wait(&mu_);
  }
}

void Server::PerformOpsOnCall(grpc::internal::CallOpSetInterface* ops,
                              grpc::internal::Call* call) {
  ops->FillOps(call);
}

bool Server::UnimplementedAsyncRequest::FinalizeResult(void** tag,
                                                       bool* status) {
  if (GenericAsyncRequest::FinalizeResult(tag, status)) {

    if (*status) {

      new UnimplementedAsyncRequest(server_, notification_cq_);
      new UnimplementedAsyncResponse(this);
    } else {
      delete this;
    }
  } else {

  }
  return false;
}

Server::UnimplementedAsyncResponse::UnimplementedAsyncResponse(
    UnimplementedAsyncRequest* request)
    : request_(request) {
  grpc::Status status(grpc::StatusCode::UNIMPLEMENTED, kUnknownRpcMethod);
  grpc::internal::UnknownMethodHandler::FillOps(request_->context(),
                                                kUnknownRpcMethod, this);
  request_->stream()->call_.PerformOps(this);
}

grpc::ServerInitializer* Server::initializer() {
  return server_initializer_.get();
}

grpc::CompletionQueue* Server::CallbackCQ() {

  CompletionQueue* callback_cq = callback_cq_.load(std::memory_order_acquire);
  if (callback_cq != nullptr) {
    return callback_cq;
  }

  grpc::internal::MutexLock l(&mu_);
  callback_cq = callback_cq_.load(std::memory_order_relaxed);
  if (callback_cq != nullptr) {
    return callback_cq;
  }
  if (grpc_iomgr_run_in_background()) {

    auto* shutdown_callback = new grpc::ShutdownCallback;
    callback_cq = new grpc::CompletionQueue(grpc_completion_queue_attributes{
        GRPC_CQ_CURRENT_VERSION, GRPC_CQ_CALLBACK, GRPC_CQ_DEFAULT_POLLING,
        shutdown_callback});

    shutdown_callback->TakeCQ(callback_cq);
  } else {

    callback_cq = CompletionQueue::CallbackAlternativeCQ();
  }

  callback_cq_.store(callback_cq, std::memory_order_release);
  return callback_cq;
}

}
