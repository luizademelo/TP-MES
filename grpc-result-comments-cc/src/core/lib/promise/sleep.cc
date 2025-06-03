Here's the commented version of the code:

```c++
// Copyright 2022 gRPC authors.

#include "src/core/lib/promise/sleep.h"

#include <grpc/event_engine/event_engine.h>
#include <grpc/support/port_platform.h>

#include <utility>

#include "src/core/lib/event_engine/event_engine_context.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/promise/activity.h"
#include "src/core/lib/promise/context.h"
#include "src/core/lib/promise/poll.h"
#include "src/core/util/time.h"

namespace grpc_core {

using ::grpc_event_engine::experimental::EventEngine;

// Constructor for Sleep class that initializes the deadline timestamp
Sleep::Sleep(Timestamp deadline) : deadline_(deadline) {}

// Destructor for Sleep class that cancels any pending timer operation
Sleep::~Sleep() {
  if (closure_ != nullptr) closure_->Cancel();
}

// Function call operator that implements the sleep promise logic
// Returns Poll<absl::Status> which indicates if sleep is complete (OkStatus),
// still pending (Pending), or if an error occurred
Poll<absl::Status> Sleep::operator()() {
  // If sleep promise exec ctx removal is disabled, invalidate current time
  if (!IsSleepPromiseExecCtxRemovalEnabled()) {
    ExecCtx::Get()->InvalidateNow();
  }
  const auto now = Timestamp::Now();

  // If deadline has passed, return OkStatus indicating sleep is complete
  if (deadline_ <= now) return absl::OkStatus();
  // If no closure exists yet, create one with the remaining time
  if (closure_ == nullptr) {
    closure_ = new ActiveClosure(deadline_);
  }
  // If closure has already run, return OkStatus
  if (closure_->HasRun()) return absl::OkStatus();
  // Otherwise return Pending to indicate sleep is still in progress
  return Pending{};
}

// Constructor for ActiveClosure which sets up the timer
Sleep::ActiveClosure::ActiveClosure(Timestamp deadline)
    : waker_(GetContext<Activity>()->MakeOwningWaker()),  // Store waker for the owning activity
      event_engine_(GetContext<EventEngine>()->shared_from_this()),  // Get shared EventEngine
      timer_handle_(
          event_engine_->RunAfter(deadline - Timestamp::Now(), this)) {}  // Schedule timer

// Method called when timer expires or is cancelled
void Sleep::ActiveClosure::Run() {
  ExecCtx exec_ctx;  // Create execution context
  auto waker = std::move(waker_);
  // If this is the last reference, delete the closure
  // Otherwise wake up the owning activity
  if (Unref()) {
    delete this;
  } else {
    waker.Wakeup();
  }
}

// Method to cancel the pending timer operation
void Sleep::ActiveClosure::Cancel() {
  // If already run, or successfully cancelled, or last reference, delete the closure
  if (HasRun() || GetContext<EventEngine>()->Cancel(timer_handle_) || Unref()) {
    delete this;
  }
}

// Method to decrement reference count
// Returns true if this was the last reference
bool Sleep::ActiveClosure::Unref() {
  return (refs_.fetch_sub(1, std::memory_order_acq_rel) == 1);
}

// Method to check if the closure has already executed
bool Sleep::ActiveClosure::HasRun() const {
  // When ref count reaches 1, it means the closure has run
  return refs_.load(std::memory_order_acquire) == 1;
}

}
```