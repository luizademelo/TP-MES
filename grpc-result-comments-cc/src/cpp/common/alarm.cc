Here's the commented version of the code:

```c++
// Copyright 2018 gRPC authors.

// Include necessary gRPC and support headers
#include <grpc/event_engine/event_engine.h>
#include <grpc/grpc.h>
#include <grpc/support/port_platform.h>
#include <grpc/support/sync.h>
#include <grpc/support/time.h>
#include <grpcpp/alarm.h>
#include <grpcpp/completion_queue.h>
#include <grpcpp/impl/completion_queue_tag.h>

// Standard library includes
#include <atomic>
#include <functional>
#include <memory>
#include <utility>

// Abseil includes for logging and status
#include "absl/log/check.h"
#include "absl/status/status.h"
// Internal gRPC includes
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

// Implementation of Alarm functionality that can be used with gRPC CompletionQueue
// or with direct callbacks
class AlarmImpl : public grpc::internal::CompletionQueueTag {
 public:
  // Constructor initializes the alarm with default event engine and sets initial refcount
  AlarmImpl()
      : event_engine_(grpc_event_engine::experimental::GetDefaultEventEngine()),
        cq_(nullptr),
        tag_(nullptr) {
    gpr_ref_init(&refs_, 1);
  }
  
  // Destructor override
  ~AlarmImpl() override {}
  
  // FinalizeResult is called when the alarm triggers on a CompletionQueue
  // Sets the output tag and decreases reference count
  bool FinalizeResult(void** tag, bool* ) override {
    *tag = tag_;
    Unref();
    return true;
  }
  
  // Sets the alarm to trigger on a CompletionQueue at specified deadline
  void Set(grpc::CompletionQueue* cq, gpr_timespec deadline, void* tag) {
    grpc_core::ExecCtx exec_ctx;
    GRPC_CQ_INTERNAL_REF(cq->cq(), "alarm");
    cq_ = cq->cq();
    tag_ = tag;
    CHECK(grpc_cq_begin_op(cq_, this));
    Ref();
    CHECK(cq_armed_.exchange(true) == false);
    CHECK(!callback_armed_.load());
    // Schedule the alarm using EventEngine
    cq_timer_handle_ = event_engine_->RunAfter(
        grpc_core::Timestamp::FromTimespecRoundUp(deadline) -
            grpc_core::ExecCtx::Get()->Now(),
        [this] { OnCQAlarm(absl::OkStatus()); });
  }
  
  // Sets the alarm to trigger a callback at specified deadline
  void Set(gpr_timespec deadline, std::function<void(bool)> f) {
    grpc_core::ExecCtx exec_ctx;

    callback_ = std::move(f);
    Ref();
    CHECK(callback_armed_.exchange(true) == false);
    CHECK(!cq_armed_.load());
    // Schedule the callback alarm using EventEngine
    callback_timer_handle_ = event_engine_->RunAfter(
        grpc_core::Timestamp::FromTimespecRoundUp(deadline) -
            grpc_core::ExecCtx::Get()->Now(),
        [this] { OnCallbackAlarm(true); });
  }
  
  // Cancels both CompletionQueue and callback alarms if they are armed
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
  
  // Cleanup method that cancels any pending alarms and decreases reference count
  void Destroy() {
    Cancel();
    Unref();
  }

 private:
  // Handler for CompletionQueue alarm triggers
  void OnCQAlarm(grpc_error_handle error) {
    cq_armed_.store(false);
    grpc_core::ExecCtx exec_ctx;

    grpc_completion_queue* cq = cq_;
    cq_ = nullptr;
    // Complete the operation on the completion queue
    grpc_cq_end_op(
        cq, this, error,
        [](void* , grpc_cq_completion* ) {}, nullptr,
        &completion_);
    GRPC_CQ_INTERNAL_UNREF(cq, "alarm");
  }

  // Handler for callback alarm triggers
  void OnCallbackAlarm(bool is_ok) {
    callback_armed_.store(false);
    grpc_core::ExecCtx exec_ctx;
    callback_(is_ok);
    Unref();
  }

  // Reference counting methods
  void Ref() { gpr_ref(&refs_); }
  void Unref() {
    if (gpr_unref(&refs_)) {
      delete this;
    }
  }

  // Member variables
  std::shared_ptr<grpc_event_engine::experimental::EventEngine> event_engine_;
  std::atomic<bool> cq_armed_{false};  // Flag for CompletionQueue alarm state
  EventEngine::TaskHandle cq_timer_handle_ = EventEngine::TaskHandle::kInvalid;
  std::atomic<bool> callback_armed_{false};  // Flag for callback alarm state
  EventEngine::TaskHandle callback_timer_handle_ =
      EventEngine::TaskHandle::kInvalid;
  gpr_refcount refs_;  // Reference counter
  grpc_cq_completion completion_;  // Completion queue completion object

  grpc_completion_queue* cq_;  // Completion queue to trigger on
  void* tag_;  // Tag to return when alarm triggers on CompletionQueue
  std::function<void(bool)> callback_;  // Callback to call when alarm triggers
};
}

// Alarm class implementation

// Constructor creates a new AlarmImpl instance
Alarm::Alarm() : alarm_(new internal::AlarmImpl()) {}

// Sets the alarm to trigger on a CompletionQueue
void Alarm::SetInternal(grpc::CompletionQueue* cq, gpr_timespec deadline,
                        void* tag) {
  static_cast<internal::AlarmImpl*>(alarm_)->Set(cq, deadline, tag);
}

// Sets the alarm to trigger a callback
void Alarm::SetInternal(gpr_timespec deadline, std::function<void(bool)> f) {
  static_cast<internal::AlarmImpl*>(alarm_)->Set(deadline, std::move(f));
}

// Destructor cleans up the alarm implementation
Alarm::~Alarm() {
  if (alarm_ != nullptr) {
    static_cast<internal::AlarmImpl*>(alarm_)->Destroy();
  }
}

// Cancels the alarm if it's pending
void Alarm::Cancel() { static_cast<internal::AlarmImpl*>(alarm_)->Cancel(); }
}
```