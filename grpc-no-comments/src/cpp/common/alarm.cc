
// Copyright 2018 gRPC authors.

#include <grpc/event_engine/event_engine.h>
#include <grpc/grpc.h>
#include <grpc/support/port_platform.h>
#include <grpc/support/sync.h>
#include <grpc/support/time.h>
#include <grpcpp/alarm.h>
#include <grpcpp/completion_queue.h>
#include <grpcpp/impl/completion_queue_tag.h>

#include <atomic>
#include <functional>
#include <memory>
#include <utility>

#include "absl/log/check.h"
#include "absl/status/status.h"
#include "src/core/lib/event_engine/default_event_engine.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/surface/completion_queue.h"
#include "src/core/util/time.h"

namespace grpc {

namespace internal {

namespace {
using grpc_event_engine::experimental::EventEngine;
}

class AlarmImpl : public grpc::internal::CompletionQueueTag {
 public:
  AlarmImpl()
      : event_engine_(grpc_event_engine::experimental::GetDefaultEventEngine()),
        cq_(nullptr),
        tag_(nullptr) {
    gpr_ref_init(&refs_, 1);
  }
  ~AlarmImpl() override {}
  bool FinalizeResult(void** tag, bool* ) override {
    *tag = tag_;
    Unref();
    return true;
  }
  void Set(grpc::CompletionQueue* cq, gpr_timespec deadline, void* tag) {
    grpc_core::ExecCtx exec_ctx;
    GRPC_CQ_INTERNAL_REF(cq->cq(), "alarm");
    cq_ = cq->cq();
    tag_ = tag;
    CHECK(grpc_cq_begin_op(cq_, this));
    Ref();
    CHECK(cq_armed_.exchange(true) == false);
    CHECK(!callback_armed_.load());
    cq_timer_handle_ = event_engine_->RunAfter(
        grpc_core::Timestamp::FromTimespecRoundUp(deadline) -
            grpc_core::ExecCtx::Get()->Now(),
        [this] { OnCQAlarm(absl::OkStatus()); });
  }
  void Set(gpr_timespec deadline, std::function<void(bool)> f) {
    grpc_core::ExecCtx exec_ctx;

    callback_ = std::move(f);
    Ref();
    CHECK(callback_armed_.exchange(true) == false);
    CHECK(!cq_armed_.load());
    callback_timer_handle_ = event_engine_->RunAfter(
        grpc_core::Timestamp::FromTimespecRoundUp(deadline) -
            grpc_core::ExecCtx::Get()->Now(),
        [this] { OnCallbackAlarm(true); });
  }
  void Cancel() {
    grpc_core::ExecCtx exec_ctx;
    if (callback_armed_.load() &&
        event_engine_->Cancel(callback_timer_handle_)) {
      event_engine_->Run([this] { OnCallbackAlarm(false); });
    }
    if (cq_armed_.load() && event_engine_->Cancel(cq_timer_handle_)) {
      event_engine_->Run(
          [this] { OnCQAlarm(absl::CancelledError("cancelled")); });
    }
  }
  void Destroy() {
    Cancel();
    Unref();
  }

 private:
  void OnCQAlarm(grpc_error_handle error) {
    cq_armed_.store(false);
    grpc_core::ExecCtx exec_ctx;

    grpc_completion_queue* cq = cq_;
    cq_ = nullptr;
    grpc_cq_end_op(
        cq, this, error,
        [](void* , grpc_cq_completion* ) {}, nullptr,
        &completion_);
    GRPC_CQ_INTERNAL_UNREF(cq, "alarm");
  }

  void OnCallbackAlarm(bool is_ok) {
    callback_armed_.store(false);
    grpc_core::ExecCtx exec_ctx;
    callback_(is_ok);
    Unref();
  }

  void Ref() { gpr_ref(&refs_); }
  void Unref() {
    if (gpr_unref(&refs_)) {
      delete this;
    }
  }

  std::shared_ptr<grpc_event_engine::experimental::EventEngine> event_engine_;
  std::atomic<bool> cq_armed_{false};
  EventEngine::TaskHandle cq_timer_handle_ = EventEngine::TaskHandle::kInvalid;
  std::atomic<bool> callback_armed_{false};
  EventEngine::TaskHandle callback_timer_handle_ =
      EventEngine::TaskHandle::kInvalid;
  gpr_refcount refs_;
  grpc_cq_completion completion_;

  grpc_completion_queue* cq_;
  void* tag_;
  std::function<void(bool)> callback_;
};
}

Alarm::Alarm() : alarm_(new internal::AlarmImpl()) {}

void Alarm::SetInternal(grpc::CompletionQueue* cq, gpr_timespec deadline,
                        void* tag) {

  static_cast<internal::AlarmImpl*>(alarm_)->Set(cq, deadline, tag);
}

void Alarm::SetInternal(gpr_timespec deadline, std::function<void(bool)> f) {

  static_cast<internal::AlarmImpl*>(alarm_)->Set(deadline, std::move(f));
}

Alarm::~Alarm() {
  if (alarm_ != nullptr) {
    static_cast<internal::AlarmImpl*>(alarm_)->Destroy();
  }
}

void Alarm::Cancel() { static_cast<internal::AlarmImpl*>(alarm_)->Cancel(); }
}
