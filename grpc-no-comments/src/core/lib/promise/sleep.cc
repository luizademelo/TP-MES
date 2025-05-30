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

Sleep::Sleep(Timestamp deadline) : deadline_(deadline) {}

Sleep::~Sleep() {
  if (closure_ != nullptr) closure_->Cancel();
}

Poll<absl::Status> Sleep::operator()() {
  if (!IsSleepPromiseExecCtxRemovalEnabled()) {

    ExecCtx::Get()->InvalidateNow();
  }
  const auto now = Timestamp::Now();

  if (deadline_ <= now) return absl::OkStatus();
  if (closure_ == nullptr) {

    closure_ = new ActiveClosure(deadline_);
  }
  if (closure_->HasRun()) return absl::OkStatus();
  return Pending{};
}

Sleep::ActiveClosure::ActiveClosure(Timestamp deadline)
    : waker_(GetContext<Activity>()->MakeOwningWaker()),
      event_engine_(GetContext<EventEngine>()->shared_from_this()),
      timer_handle_(
          event_engine_->RunAfter(deadline - Timestamp::Now(), this)) {}

void Sleep::ActiveClosure::Run() {
  ExecCtx exec_ctx;
  auto waker = std::move(waker_);
  if (Unref()) {
    delete this;
  } else {
    waker.Wakeup();
  }
}

void Sleep::ActiveClosure::Cancel() {

  if (HasRun() || GetContext<EventEngine>()->Cancel(timer_handle_) || Unref()) {
    delete this;
  }
}

bool Sleep::ActiveClosure::Unref() {
  return (refs_.fetch_sub(1, std::memory_order_acq_rel) == 1);
}

bool Sleep::ActiveClosure::HasRun() const {

  return refs_.load(std::memory_order_acquire) == 1;
}

}
