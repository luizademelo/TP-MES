
// Copyright 2015 gRPC authors.

#ifndef GRPCPP_SERVER_CONTEXT_H
#define GRPCPP_SERVER_CONTEXT_H

#include <grpc/grpc.h>
#include <grpc/impl/call.h>
#include <grpc/impl/compression_types.h>
#include <grpc/support/port_platform.h>
#include <grpcpp/impl/call.h>
#include <grpcpp/impl/call_op_set.h>
#include <grpcpp/impl/codegen/create_auth_context.h>
#include <grpcpp/impl/codegen/metadata_map.h>
#include <grpcpp/impl/completion_queue_tag.h>
#include <grpcpp/impl/metadata_map.h>
#include <grpcpp/impl/rpc_service_method.h>
#include <grpcpp/security/auth_context.h>
#include <grpcpp/support/callback_common.h>
#include <grpcpp/support/config.h>
#include <grpcpp/support/message_allocator.h>
#include <grpcpp/support/server_callback.h>
#include <grpcpp/support/server_interceptor.h>
#include <grpcpp/support/status.h>
#include <grpcpp/support/string_ref.h>
#include <grpcpp/support/time.h>

#include <atomic>
#include <cassert>
#include <map>
#include <memory>
#include <type_traits>
#include <vector>

struct grpc_metadata;
struct grpc_call;
struct census_context;

namespace grpc {
template <class W, class R>
class ServerAsyncReader;
template <class W>
class ServerAsyncWriter;
template <class W>
class ServerAsyncResponseWriter;
template <class W, class R>
class ServerAsyncReaderWriter;
template <class R>
class ServerReader;
template <class W>
class ServerWriter;

namespace internal {
template <class ServiceType, class RequestType, class ResponseType>
class BidiStreamingHandler;
template <class RequestType, class ResponseType>
class CallbackUnaryHandler;
template <class RequestType, class ResponseType>
class CallbackClientStreamingHandler;
template <class RequestType, class ResponseType>
class CallbackServerStreamingHandler;
template <class RequestType, class ResponseType>
class CallbackBidiHandler;
template <class ServiceType, class RequestType, class ResponseType>
class ClientStreamingHandler;
template <class ResponseType>
void UnaryRunHandlerHelper(const MethodHandler::HandlerParameter&,
                           ResponseType*, Status&);
template <class ServiceType, class RequestType, class ResponseType,
          class BaseRequestType, class BaseResponseType>
class RpcMethodHandler;
template <class Base>
class FinishOnlyReactor;
template <class W, class R>
class ServerReaderWriterBody;
template <class ServiceType, class RequestType, class ResponseType>
class ServerStreamingHandler;
class ServerReactor;
template <class Streamer, bool WriteNeeded>
class TemplatedBidiStreamingHandler;
template <grpc::StatusCode code>
class ErrorMethodHandler;
}

class ClientContext;
class CompletionQueue;
class GenericServerContext;
class Server;
class ServerInterface;
class ContextAllocator;
class GenericCallbackServerContext;

namespace internal {
class Call;
}

namespace testing {
class InteropServerContextInspector;
class ServerContextTestSpouse;
class DefaultReactorTestPeer;
}

namespace experimental {
class CallMetricRecorder;
class ServerMetricRecorder;
}

class ServerContextBase {
 public:
  virtual ~ServerContextBase();

  std::chrono::system_clock::time_point deadline() const {
    return grpc::Timespec2Timepoint(deadline_);
  }

  gpr_timespec raw_deadline() const { return deadline_; }

  void AddInitialMetadata(const std::string& key, const std::string& value);

  void AddTrailingMetadata(const std::string& key, const std::string& value);

  bool IsCancelled() const;

  void TryCancel() const;

  const std::multimap<grpc::string_ref, grpc::string_ref>& client_metadata()
      const {
    return *client_metadata_.map();
  }

  grpc_compression_level compression_level() const {
    return compression_level_;
  }

  void set_compression_level(grpc_compression_level level) {
    compression_level_set_ = true;
    compression_level_ = level;
  }

  bool compression_level_set() const { return compression_level_set_; }

  grpc_compression_algorithm compression_algorithm() const {
    return compression_algorithm_;
  }

  void set_compression_algorithm(grpc_compression_algorithm algorithm);

  void SetLoadReportingCosts(const std::vector<std::string>& cost_data);

  std::shared_ptr<const grpc::AuthContext> auth_context() const {
    if (auth_context_ == nullptr) {
      auth_context_ = grpc::CreateAuthContext(call_.call);
    }
    return auth_context_;
  }

  std::string peer() const;

  const struct census_context* census_context() const;

  grpc_call* c_call() { return call_.call; }

  experimental::CallMetricRecorder* ExperimentalGetCallMetricRecorder() {
    return call_metric_recorder_;
  }

  grpc::string_ref ExperimentalGetAuthority() const;

 protected:

  /// Note: the tag will only be returned if call starts.

  void AsyncNotifyWhenDone(void* tag) {
    has_notify_when_done_tag_ = true;
    async_notify_when_done_tag_ = tag;
  }

  /// NOTE: This is an API for advanced users who need custom allocators.

  RpcAllocatorState* GetRpcAllocatorState() { return message_allocator_state_; }

  grpc::ServerUnaryReactor* DefaultReactor() {

    if (test_unary_ != nullptr) {
      return reinterpret_cast<Reactor*>(&default_reactor_);
    }
    new (&default_reactor_) Reactor;
#ifndef NDEBUG
    bool old = false;
    assert(default_reactor_used_.compare_exchange_strong(
        old, true, std::memory_order_relaxed));
#else
    default_reactor_used_.store(true, std::memory_order_relaxed);
#endif
    return reinterpret_cast<Reactor*>(&default_reactor_);
  }

  ServerContextBase();
  ServerContextBase(gpr_timespec deadline, grpc_metadata_array* arr);

  void set_context_allocator(ContextAllocator* context_allocator) {
    context_allocator_ = context_allocator;
  }

  ContextAllocator* context_allocator() const { return context_allocator_; }

 private:
  friend class grpc::testing::InteropServerContextInspector;
  friend class grpc::testing::ServerContextTestSpouse;
  friend class grpc::testing::DefaultReactorTestPeer;
  friend class grpc::ServerInterface;
  friend class grpc::Server;
  template <class W, class R>
  friend class grpc::ServerAsyncReader;
  template <class W>
  friend class grpc::ServerAsyncWriter;
  template <class W>
  friend class grpc::ServerAsyncResponseWriter;
  template <class W, class R>
  friend class grpc::ServerAsyncReaderWriter;
  template <class R>
  friend class grpc::ServerReader;
  template <class W>
  friend class grpc::ServerWriter;
  template <class W, class R>
  friend class grpc::internal::ServerReaderWriterBody;
  template <class ResponseType>
  friend void grpc::internal::UnaryRunHandlerHelper(
      const internal::MethodHandler::HandlerParameter& param, ResponseType* rsp,
      Status& status);
  template <class ServiceType, class RequestType, class ResponseType,
            class BaseRequestType, class BaseResponseType>
  friend class grpc::internal::RpcMethodHandler;
  template <class ServiceType, class RequestType, class ResponseType>
  friend class grpc::internal::ClientStreamingHandler;
  template <class ServiceType, class RequestType, class ResponseType>
  friend class grpc::internal::ServerStreamingHandler;
  template <class Streamer, bool WriteNeeded>
  friend class grpc::internal::TemplatedBidiStreamingHandler;
  template <class RequestType, class ResponseType>
  friend class grpc::internal::CallbackUnaryHandler;
  template <class RequestType, class ResponseType>
  friend class grpc::internal::CallbackClientStreamingHandler;
  template <class RequestType, class ResponseType>
  friend class grpc::internal::CallbackServerStreamingHandler;
  template <class RequestType, class ResponseType>
  friend class grpc::internal::CallbackBidiHandler;
  template <grpc::StatusCode code>
  friend class grpc::internal::ErrorMethodHandler;
  template <class Base>
  friend class grpc::internal::FinishOnlyReactor;
  friend class grpc::ClientContext;
  friend class grpc::GenericServerContext;
  friend class grpc::GenericCallbackServerContext;

  ServerContextBase(const ServerContextBase&);
  ServerContextBase& operator=(const ServerContextBase&);

  class CompletionOp;

  void BeginCompletionOp(
      grpc::internal::Call* call, std::function<void(bool)> callback,
      grpc::internal::ServerCallbackCall* callback_controller);

  grpc::internal::CompletionQueueTag* GetCompletionOpTag();

  void set_call(grpc_call* call, bool call_metric_recording_enabled,
                experimental::ServerMetricRecorder* server_metric_recorder) {
    call_.call = call;
    if (call_metric_recording_enabled) {
      CreateCallMetricRecorder(server_metric_recorder);
    }
  }

  void BindDeadlineAndMetadata(gpr_timespec deadline, grpc_metadata_array* arr);

  uint32_t initial_metadata_flags() const { return 0; }

  grpc::experimental::ServerRpcInfo* set_server_rpc_info(
      const char* method, grpc::internal::RpcMethod::RpcType type,
      const std::vector<std::unique_ptr<
          grpc::experimental::ServerInterceptorFactoryInterface>>& creators) {
    if (!creators.empty()) {
      rpc_info_ = new grpc::experimental::ServerRpcInfo(this, method, type);
      rpc_info_->RegisterInterceptors(creators);
    }
    return rpc_info_;
  }

  void set_message_allocator_state(RpcAllocatorState* allocator_state) {
    message_allocator_state_ = allocator_state;
  }

  void MaybeMarkCancelledOnRead() {
    if (grpc_call_failed_before_recv_message(call_.call)) {
      marked_cancelled_.store(true, std::memory_order_release);
    }
  }

  void CreateCallMetricRecorder(
      experimental::ServerMetricRecorder* server_metric_recorder = nullptr);

  struct CallWrapper {
    ~CallWrapper();

    grpc_call* call = nullptr;
  };

  // NOTE: call_ must be the first data member of this object so that its

  CallWrapper call_;

  CompletionOp* completion_op_ = nullptr;
  bool has_notify_when_done_tag_ = false;
  void* async_notify_when_done_tag_ = nullptr;
  grpc::internal::CallbackWithSuccessTag completion_tag_;

  gpr_timespec deadline_;
  grpc::CompletionQueue* cq_ = nullptr;
  bool sent_initial_metadata_ = false;
  mutable std::shared_ptr<const grpc::AuthContext> auth_context_;
  mutable grpc::internal::MetadataMap client_metadata_;
  std::multimap<std::string, std::string> initial_metadata_;
  std::multimap<std::string, std::string> trailing_metadata_;

  bool compression_level_set_ = false;
  grpc_compression_level compression_level_;
  grpc_compression_algorithm compression_algorithm_;

  grpc::internal::CallOpSet<grpc::internal::CallOpSendInitialMetadata,
                            grpc::internal::CallOpSendMessage>
      pending_ops_;
  bool has_pending_ops_ = false;

  grpc::experimental::ServerRpcInfo* rpc_info_ = nullptr;
  RpcAllocatorState* message_allocator_state_ = nullptr;
  ContextAllocator* context_allocator_ = nullptr;
  experimental::CallMetricRecorder* call_metric_recorder_ = nullptr;

  class Reactor : public grpc::ServerUnaryReactor {
   public:
    void OnCancel() override {}
    void OnDone() override {}

    bool InternalInlineable() override { return true; }
  };

  void SetupTestDefaultReactor(std::function<void(grpc::Status)> func) {

    test_unary_.reset(new TestServerCallbackUnary(this, std::move(func)));
  }
  bool test_status_set() const {
    return (test_unary_ != nullptr) && test_unary_->status_set();
  }
  grpc::Status test_status() const { return test_unary_->status(); }

  class TestServerCallbackUnary : public grpc::ServerCallbackUnary {
   public:
    TestServerCallbackUnary(ServerContextBase* ctx,
                            std::function<void(grpc::Status)> func)
        : reactor_(ctx->DefaultReactor()),
          func_(std::move(func)),
          call_(ctx->c_call()) {
      this->BindReactor(reactor_);
    }
    void Finish(grpc::Status s) override {
      status_ = s;
      func_(std::move(s));
      status_set_.store(true, std::memory_order_release);
    }
    void SendInitialMetadata() override {}

    bool status_set() const {
      return status_set_.load(std::memory_order_acquire);
    }
    grpc::Status status() const { return status_; }

   private:
    void CallOnDone() override {}

    grpc_call* call() override { return call_; }

    grpc::internal::ServerReactor* reactor() override { return reactor_; }

    grpc::ServerUnaryReactor* const reactor_;
    std::atomic_bool status_set_{false};
    grpc::Status status_;
    const std::function<void(grpc::Status s)> func_;
    grpc_call* call_;
  };

  alignas(Reactor) char default_reactor_[sizeof(Reactor)];
  std::atomic_bool default_reactor_used_{false};

  std::atomic_bool marked_cancelled_{false};

  std::unique_ptr<TestServerCallbackUnary> test_unary_;
};

class ServerContext : public ServerContextBase {
 public:
  ServerContext() {}

  using ServerContextBase::AddInitialMetadata;
  using ServerContextBase::AddTrailingMetadata;
  using ServerContextBase::auth_context;
  using ServerContextBase::c_call;
  using ServerContextBase::census_context;
  using ServerContextBase::client_metadata;
  using ServerContextBase::compression_algorithm;
  using ServerContextBase::compression_level;
  using ServerContextBase::compression_level_set;
  using ServerContextBase::deadline;
  using ServerContextBase::IsCancelled;
  using ServerContextBase::peer;
  using ServerContextBase::raw_deadline;
  using ServerContextBase::set_compression_algorithm;
  using ServerContextBase::set_compression_level;
  using ServerContextBase::SetLoadReportingCosts;
  using ServerContextBase::TryCancel;

  using ServerContextBase::AsyncNotifyWhenDone;

 private:

  friend class grpc::Server;
  ServerContext(gpr_timespec deadline, grpc_metadata_array* arr)
      : ServerContextBase(deadline, arr) {}

  using ServerContextBase::DefaultReactor;
  using ServerContextBase::GetRpcAllocatorState;

  ServerContext(const ServerContext&) = delete;
  ServerContext& operator=(const ServerContext&) = delete;
};

class CallbackServerContext : public ServerContextBase {
 public:

  CallbackServerContext() {}

  using ServerContextBase::AddInitialMetadata;
  using ServerContextBase::AddTrailingMetadata;
  using ServerContextBase::auth_context;
  using ServerContextBase::c_call;
  using ServerContextBase::census_context;
  using ServerContextBase::client_metadata;
  using ServerContextBase::compression_algorithm;
  using ServerContextBase::compression_level;
  using ServerContextBase::compression_level_set;
  using ServerContextBase::context_allocator;
  using ServerContextBase::deadline;
  using ServerContextBase::IsCancelled;
  using ServerContextBase::peer;
  using ServerContextBase::raw_deadline;
  using ServerContextBase::set_compression_algorithm;
  using ServerContextBase::set_compression_level;
  using ServerContextBase::set_context_allocator;
  using ServerContextBase::SetLoadReportingCosts;
  using ServerContextBase::TryCancel;

  using ServerContextBase::DefaultReactor;
  using ServerContextBase::GetRpcAllocatorState;

 private:

  using ServerContextBase::AsyncNotifyWhenDone;

  CallbackServerContext(const CallbackServerContext&) = delete;
  CallbackServerContext& operator=(const CallbackServerContext&) = delete;
};

class ContextAllocator {
 public:
  virtual ~ContextAllocator() {}

  virtual CallbackServerContext* NewCallbackServerContext() { return nullptr; }

  virtual GenericCallbackServerContext* NewGenericCallbackServerContext() {
    return nullptr;
  }

  virtual void Release(CallbackServerContext*) {}

  virtual void Release(GenericCallbackServerContext*) {}
};

}

static_assert(
    std::is_base_of<grpc::ServerContextBase, grpc::ServerContext>::value,
    "improper base class");
static_assert(std::is_base_of<grpc::ServerContextBase,
                              grpc::CallbackServerContext>::value,
              "improper base class");
static_assert(sizeof(grpc::ServerContextBase) == sizeof(grpc::ServerContext),
              "wrong size");
static_assert(sizeof(grpc::ServerContextBase) ==
                  sizeof(grpc::CallbackServerContext),
              "wrong size");

#endif
