Here's the commented version of the code:

```c++
// Copyright 2017 gRPC authors.

#include "src/core/lib/iomgr/call_combiner.h"

#include <grpc/support/port_platform.h>
#include <inttypes.h>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "src/core/telemetry/stats.h"
#include "src/core/telemetry/stats_data.h"
#include "src/core/util/crash.h"

namespace grpc_core {

namespace {
// Bitmask to identify error state in cancel_state_
constexpr intptr_t kErrorBit = 1;

// Decodes the error from cancel_state atomic variable
// If error bit is set, extracts and returns the error from the status pointer
// Otherwise returns OK status
grpc_error_handle DecodeCancelStateError(gpr_atm cancel_state) {
  if (cancel_state & kErrorBit) {
    return internal::StatusGetFromHeapPtr(cancel_state & ~kErrorBit);
  }
  return absl::OkStatus();
}

}  // namespace

// Constructor initializes atomic counters
CallCombiner::CallCombiner() {
  gpr_atm_no_barrier_store(&cancel_state_, 0);
  gpr_atm_no_barrier_store(&size_, 0);
#ifdef GRPC_TSAN_ENABLED
  // Initialize TSAN closure if TSAN is enabled
  GRPC_CLOSURE_INIT(&tsan_closure_, TsanClosure, this,
                    grpc_schedule_on_exec_ctx);
#endif
}

// Destructor cleans up any stored error status
CallCombiner::~CallCombiner() {
  if (cancel_state_ & kErrorBit) {
    internal::StatusFreeHeapPtr(cancel_state_ & ~kErrorBit);
  }
}

#ifdef GRPC_TSAN_ENABLED
// TSAN closure handler to manage thread sanitizer annotations
// Acquires lock before running original closure and releases after
void CallCombiner::TsanClosure(void* arg, grpc_error_handle error) {
  CallCombiner* self = static_cast<CallCombiner*>(arg);

  RefCountedPtr<TsanLock> lock = self->tsan_lock_;
  bool prev = false;
  if (lock->taken.compare_exchange_strong(prev, true)) {
    TSAN_ANNOTATE_RWLOCK_ACQUIRED(&lock->taken, true);
  } else {
    lock.reset();
  }
  Closure::Run(DEBUG_LOCATION, self->original_closure_, error);
  if (lock != nullptr) {
    TSAN_ANNOTATE_RWLOCK_RELEASED(&lock->taken, true);
    bool prev = true;
    CHECK(lock->taken.compare_exchange_strong(prev, false));
  }
}
#endif

// Schedules a closure to be run
// Under TSAN, wraps the closure in TSAN-aware handling
void CallCombiner::ScheduleClosure(grpc_closure* closure,
                                   grpc_error_handle error) {
#ifdef GRPC_TSAN_ENABLED
  original_closure_ = closure;
  ExecCtx::Run(DEBUG_LOCATION, &tsan_closure_, error);
#else
  ExecCtx::Run(DEBUG_LOCATION, closure, error);
#endif
}

// Debug macro definitions for logging
#ifndef NDEBUG
#define DEBUG_ARGS const char *file, int line,
#define DEBUG_FMT_STR "%s:%d: "
#define DEBUG_FMT_ARGS , file, line
#else
#define DEBUG_ARGS
#define DEBUG_FMT_STR
#define DEBUG_FMT_ARGS
#endif

// Starts executing a closure in the call combiner
// If no other operations are active, executes immediately
// Otherwise queues the closure for later execution
void CallCombiner::Start(grpc_closure* closure, grpc_error_handle error,
                         DEBUG_ARGS const char* reason) {
  GRPC_TRACE_LOG(call_combiner, INFO) << absl::StrFormat(
      "==> CallCombiner::Start() [%p] closure=%s [" DEBUG_FMT_STR
      "%s] error=%s",
      this, closure->DebugString().c_str() DEBUG_FMT_ARGS, reason,
      StatusToString(error).c_str());
  size_t prev_size =
      static_cast<size_t>(gpr_atm_full_fetch_add(&size_, (gpr_atm)1));
  GRPC_TRACE_LOG(call_combiner, INFO)
      << "  size: " << prev_size << " -> " << prev_size + 1;
  if (prev_size == 0) {
    GRPC_TRACE_LOG(call_combiner, INFO) << "  EXECUTING IMMEDIATELY";
    ScheduleClosure(closure, error);
  } else {
    GRPC_TRACE_LOG(call_combiner, INFO) << "  QUEUING";
    // Store error in closure and add to queue
    closure->error_data.error = internal::StatusAllocHeapPtr(error);
    queue_.Push(
        reinterpret_cast<MultiProducerSingleConsumerQueue::Node*>(closure));
  }
}

// Stops an operation in the call combiner
// If this was the last operation, executes any queued closures
void CallCombiner::Stop(DEBUG_ARGS const char* reason) {
  GRPC_TRACE_LOG(call_combiner, INFO)
      << absl::StrFormat("==> CallCombiner::Stop() [%p] [" DEBUG_FMT_STR "%s]",
                         this DEBUG_FMT_ARGS, reason);
  size_t prev_size =
      static_cast<size_t>(gpr_atm_full_fetch_add(&size_, (gpr_atm)-1));
  GRPC_TRACE_LOG(call_combiner, INFO)
      << "  size: " << prev_size << " -> " << prev_size - 1;
  CHECK_GE(prev_size, 1u);
  if (prev_size > 1) {
    // Process queue until we find an item to execute
    while (true) {
      GRPC_TRACE_LOG(call_combiner, INFO) << "  checking queue";
      bool empty;
      grpc_closure* closure =
          reinterpret_cast<grpc_closure*>(queue_.PopAndCheckEnd(&empty));
      if (closure == nullptr) {
        GRPC_TRACE_LOG(call_combiner, INFO)
            << "  queue returned no result; checking again";
        continue;
      }
      // Retrieve error from closure and execute
      grpc_error_handle error =
          internal::StatusMoveFromHeapPtr(closure->error_data.error);
      closure->error_data.error = 0;
      GRPC_TRACE_LOG(call_combiner, INFO)
          << "  EXECUTING FROM QUEUE: closure=" << closure->DebugString()
          << " error=" << StatusToString(error);
      ScheduleClosure(closure, error);
      break;
    }
    GRPC_TRACE_LOG(call_combiner, INFO) << "  queue empty";
  }
}

// Sets a closure to be notified if the call is cancelled
// If cancellation already occurred, runs the closure immediately
void CallCombiner::SetNotifyOnCancel(grpc_closure* closure) {
  while (true) {
    gpr_atm original_state = gpr_atm_acq_load(&cancel_state_);
    grpc_error_handle original_error = DecodeCancelStateError(original_state);

    if (!original_error.ok()) {
      // Already cancelled - run callback immediately
      GRPC_TRACE_LOG(call_combiner, INFO)
          << "call_combiner=" << this
          << ": scheduling notify_on_cancel callback=" << closure
          << " for pre-existing cancellation";
      ExecCtx::Run(DEBUG_LOCATION, closure, original_error);
      break;
    } else {
      // Try to set the new closure
      if (gpr_atm_full_cas(&cancel_state_, original_state,
                           reinterpret_cast<gpr_atm>(closure))) {
        GRPC_TRACE_LOG(call_combiner, INFO)
            << "call_combiner=" << this
            << ": setting notify_on_cancel=" << closure;

        // If there was a previous callback, run it with OK status
        if (original_state != 0) {
          closure = reinterpret_cast<grpc_closure*>(original_state);
          GRPC_TRACE_LOG(call_combiner, INFO)
              << "call_combiner=" << this
              << ": scheduling old cancel callback=" << closure;
          ExecCtx::Run(DEBUG_LOCATION, closure, absl::OkStatus());
        }
        break;
      }
    }
  }
}

// Cancels the call combiner with the given error
// Notifies any registered cancellation callback
void CallCombiner::Cancel(grpc_error_handle error) {
  intptr_t status_ptr = internal::StatusAllocHeapPtr(error);
  gpr_atm new_state = kErrorBit | status_ptr;
  while (true) {
    gpr_atm original_state = gpr_atm_acq_load(&cancel_state_);
    grpc_error_handle original_error = DecodeCancelStateError(original_state);
    if (!original_error.ok()) {
      // Already cancelled - clean up and exit
      internal::StatusFreeHeapPtr(status_ptr);
      break;
    }
    if (gpr_atm_full_cas(&cancel_state_, original_state, new_state)) {
      // If there was a callback, run it with the cancellation error
      if (original_state != 0) {
        grpc_closure* notify_on_cancel =
            reinterpret_cast<grpc_closure*>(original_state);
        GRPC_TRACE_LOG(call_combiner, INFO)
            << "call_combiner=" << this
            << ": scheduling notify_on_cancel callback=" << notify_on_cancel;
        ExecCtx::Run(DEBUG_LOCATION, notify_on_cancel, error);
      }
      break;
    }
  }
}

}  // namespace grpc_core
```