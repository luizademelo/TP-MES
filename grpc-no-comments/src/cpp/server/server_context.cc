
// Copyright 2015 gRPC authors.

#include <assert.h>
#include <grpc/compression.h>
#include <grpc/grpc.h>
#include <grpc/impl/compression_types.h>
#include <grpc/load_reporting.h>
#include <grpc/status.h>
#include <grpc/support/alloc.h>
#include <grpc/support/time.h>
#include <grpcpp/completion_queue.h>
#include <grpcpp/ext/call_metric_recorder.h>
#include <grpcpp/ext/server_metric_recorder.h>
#include <grpcpp/impl/call.h>
#include <grpcpp/impl/call_op_set.h>
#include <grpcpp/impl/call_op_set_interface.h>
#include <grpcpp/impl/completion_queue_tag.h>
#include <grpcpp/impl/interceptor_common.h>
#include <grpcpp/impl/metadata_map.h>
#include <grpcpp/server_context.h>
#include <grpcpp/support/callback_common.h>
#include <grpcpp/support/interceptor.h>
#include <grpcpp/support/server_callback.h>
#include <grpcpp/support/server_interceptor.h>
#include <grpcpp/support/string_ref.h>

#include <atomic>
#include <cstdlib>
#include <functional>
#include <map>
#include <memory>
#include <new>
#include <string>
#include <utility>
#include <vector>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/strings/str_format.h"
#include "absl/strings/string_view.h"
#include "src/core/lib/resource_quota/arena.h"
#include "src/core/lib/surface/call.h"
#include "src/core/util/crash.h"
#include "src/core/util/ref_counted.h"
#include "src/core/util/sync.h"
#include "src/cpp/server/backend_metric_recorder.h"

namespace grpc {

class ServerContextBase::CompletionOp final
    : public internal::CallOpSetInterface {
 public:

  CompletionOp(internal::Call* call,
               grpc::internal::ServerCallbackCall* callback_controller)
      : call_(*call),
        callback_controller_(callback_controller),
        has_tag_(false),
        tag_(nullptr),
        core_cq_tag_(this),
        refs_(2),
        finalized_(false),
        cancelled_(0),
        done_intercepting_(false) {}

  CompletionOp(const CompletionOp&) = delete;
  CompletionOp& operator=(const CompletionOp&) = delete;
  CompletionOp(CompletionOp&&) = delete;
  CompletionOp& operator=(CompletionOp&&) = delete;

  ~CompletionOp() override {
    if (call_.server_rpc_info()) {
      call_.server_rpc_info()->Unref();
    }
  }

  void FillOps(internal::Call* call) override;

  static void operator delete(void* , std::size_t size) {

    (void)size;
    assert(size == sizeof(CompletionOp));
  }

  static void operator delete(void*, void*) { assert(0); }

  bool FinalizeResult(void** tag, bool* status) override;

  bool CheckCancelled(CompletionQueue* cq) {
    cq->TryPluck(this);
    return CheckCancelledNoPluck();
  }
  bool CheckCancelledAsync() { return CheckCancelledNoPluck(); }

  void set_tag(void* tag) {
    has_tag_ = true;
    tag_ = tag;
  }

  void set_core_cq_tag(void* core_cq_tag) { core_cq_tag_ = core_cq_tag; }

  void* core_cq_tag() override { return core_cq_tag_; }

  void Unref();

  void SetHijackingState() override {

    grpc_core::Crash("unreachable");
  }

  void ContinueFillOpsAfterInterception() override {}

  void ContinueFinalizeResultAfterInterception() override {
    done_intercepting_ = true;
    if (!has_tag_) {

      Unref();

      return;
    }

    CHECK(grpc_call_start_batch(call_.call(), nullptr, 0, core_cq_tag_,
                                nullptr) == GRPC_CALL_OK);
  }

 private:
  bool CheckCancelledNoPluck() {
    grpc_core::MutexLock lock(&mu_);
    return finalized_ ? (cancelled_ != 0) : false;
  }

  internal::Call call_;
  grpc::internal::ServerCallbackCall* const callback_controller_;
  bool has_tag_;
  void* tag_;
  void* core_cq_tag_;
  grpc_core::RefCount refs_;
  grpc_core::Mutex mu_;
  bool finalized_;
  int cancelled_;
  bool done_intercepting_;
  internal::InterceptorBatchMethodsImpl interceptor_methods_;
};

void ServerContextBase::CompletionOp::Unref() {
  if (refs_.Unref()) {
    grpc_call* call = call_.call();
    delete this;
    grpc_call_unref(call);
  }
}

void ServerContextBase::CompletionOp::FillOps(internal::Call* call) {
  grpc_op ops;
  ops.op = GRPC_OP_RECV_CLOSE_ON_SERVER;
  ops.data.recv_close_on_server.cancelled = &cancelled_;
  ops.flags = 0;
  ops.reserved = nullptr;
  interceptor_methods_.SetCall(&call_);
  interceptor_methods_.SetReverse();
  interceptor_methods_.SetCallOpSetInterface(this);

  CHECK(grpc_call_start_batch(call->call(), &ops, 1, core_cq_tag_, nullptr) ==
        GRPC_CALL_OK);

}

bool ServerContextBase::CompletionOp::FinalizeResult(void** tag, bool* status) {

  bool do_unref = false;
  bool has_tag = false;
  bool call_cancel = false;

  {
    grpc_core::MutexLock lock(&mu_);
    if (done_intercepting_) {

      has_tag = has_tag_;
      if (has_tag) {
        *tag = tag_;
      }

      do_unref = true;
    } else {
      finalized_ = true;

      if (!*status) {
        cancelled_ = 1;
      }

      call_cancel = (cancelled_ != 0);

    }
  }

  if (do_unref) {
    Unref();

    return has_tag;
  }
  if (call_cancel && callback_controller_ != nullptr) {
    callback_controller_->MaybeCallOnCancel();
  }

  interceptor_methods_.AddInterceptionHookPoint(
      experimental::InterceptionHookPoints::POST_RECV_CLOSE);
  if (interceptor_methods_.RunInterceptors()) {

    bool has_tag = has_tag_;
    if (has_tag) {
      *tag = tag_;
    }
    Unref();

    return has_tag;
  }

  return false;
}

ServerContextBase::ServerContextBase()
    : deadline_(gpr_inf_future(GPR_CLOCK_REALTIME)) {}

ServerContextBase::ServerContextBase(gpr_timespec deadline,
                                     grpc_metadata_array* arr)
    : deadline_(deadline) {
  std::swap(*client_metadata_.arr(), *arr);
}

void ServerContextBase::BindDeadlineAndMetadata(gpr_timespec deadline,
                                                grpc_metadata_array* arr) {
  deadline_ = deadline;
  std::swap(*client_metadata_.arr(), *arr);
}

ServerContextBase::~ServerContextBase() {
  if (completion_op_) {
    completion_op_->Unref();

  }
  if (rpc_info_) {
    rpc_info_->Unref();
  }
  if (default_reactor_used_.load(std::memory_order_relaxed)) {
    reinterpret_cast<Reactor*>(&default_reactor_)->~Reactor();
  }
  if (call_metric_recorder_ != nullptr) {
    call_metric_recorder_->~CallMetricRecorder();
  }
}

ServerContextBase::CallWrapper::~CallWrapper() {
  if (call) {

    grpc_call_unref(call);
  }
}

void ServerContextBase::BeginCompletionOp(
    internal::Call* call, std::function<void(bool)> callback,
    grpc::internal::ServerCallbackCall* callback_controller) {
  CHECK(!completion_op_);
  if (rpc_info_) {
    rpc_info_->Ref();
  }
  grpc_call_ref(call->call());
  completion_op_ =
      new (grpc_call_arena_alloc(call->call(), sizeof(CompletionOp)))
          CompletionOp(call, callback_controller);
  if (callback_controller != nullptr) {
    completion_tag_.Set(call->call(), std::move(callback), completion_op_,
                        true);
    completion_op_->set_core_cq_tag(&completion_tag_);
    completion_op_->set_tag(completion_op_);
  } else if (has_notify_when_done_tag_) {
    completion_op_->set_tag(async_notify_when_done_tag_);
  }
  call->PerformOps(completion_op_);
}

internal::CompletionQueueTag* ServerContextBase::GetCompletionOpTag() {
  return static_cast<internal::CompletionQueueTag*>(completion_op_);
}

void ServerContextBase::AddInitialMetadata(const std::string& key,
                                           const std::string& value) {
  initial_metadata_.insert(std::pair(key, value));
}

void ServerContextBase::AddTrailingMetadata(const std::string& key,
                                            const std::string& value) {
  trailing_metadata_.insert(std::pair(key, value));
}

void ServerContextBase::TryCancel() const {
  internal::CancelInterceptorBatchMethods cancel_methods;
  if (rpc_info_) {
    for (size_t i = 0; i < rpc_info_->interceptors_.size(); i++) {
      rpc_info_->RunInterceptor(&cancel_methods, i);
    }
  }
  grpc_call_error err =
      grpc_call_cancel_with_status(call_.call, GRPC_STATUS_CANCELLED,
                                   "Cancelled on the server side", nullptr);
  if (err != GRPC_CALL_OK) {
    LOG(ERROR) << "TryCancel failed with: " << err;
  }
}

bool ServerContextBase::IsCancelled() const {
  if (completion_tag_) {

    return marked_cancelled_.load(std::memory_order_acquire) ||
           completion_op_->CheckCancelledAsync();
  } else if (has_notify_when_done_tag_) {

    return completion_op_ && completion_op_->CheckCancelledAsync();
  } else {

    return marked_cancelled_.load(std::memory_order_acquire) ||
           (completion_op_ && completion_op_->CheckCancelled(cq_));
  }
}

void ServerContextBase::set_compression_algorithm(
    grpc_compression_algorithm algorithm) {
  compression_algorithm_ = algorithm;
  const char* algorithm_name = nullptr;
  if (!grpc_compression_algorithm_name(algorithm, &algorithm_name)) {
    grpc_core::Crash(absl::StrFormat(
        "Name for compression algorithm '%d' unknown.", algorithm));
  }
  CHECK_NE(algorithm_name, nullptr);
  AddInitialMetadata(GRPC_COMPRESSION_REQUEST_ALGORITHM_MD_KEY, algorithm_name);
}

std::string ServerContextBase::peer() const {
  std::string peer;
  if (call_.call) {
    char* c_peer = grpc_call_get_peer(call_.call);
    peer = c_peer;
    gpr_free(c_peer);
  }
  return peer;
}

const struct census_context* ServerContextBase::census_context() const {
  return call_.call == nullptr ? nullptr
                               : grpc_census_call_get_context(call_.call);
}

void ServerContextBase::SetLoadReportingCosts(
    const std::vector<std::string>& cost_data) {
  if (call_.call == nullptr) return;
  for (const auto& cost_datum : cost_data) {
    AddTrailingMetadata(GRPC_LB_COST_MD_KEY, cost_datum);
  }
}

void ServerContextBase::CreateCallMetricRecorder(
    experimental::ServerMetricRecorder* server_metric_recorder) {
  if (call_.call == nullptr) return;
  CHECK_EQ(call_metric_recorder_, nullptr);
  grpc_core::Arena* arena = grpc_call_get_arena(call_.call);
  auto* backend_metric_state =
      arena->New<BackendMetricState>(server_metric_recorder);
  call_metric_recorder_ = backend_metric_state;
  arena->SetContext<grpc_core::BackendMetricProvider>(backend_metric_state);
}

grpc::string_ref ServerContextBase::ExperimentalGetAuthority() const {
  absl::string_view authority = grpc_call_server_authority(call_.call);
  return grpc::string_ref(authority.data(), authority.size());
}

}
