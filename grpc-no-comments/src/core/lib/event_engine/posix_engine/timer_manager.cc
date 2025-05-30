
// Copyright 2017 gRPC authors.

#include "src/core/lib/event_engine/posix_engine/timer_manager.h"

#include <grpc/support/port_platform.h>
#include <grpc/support/time.h>

#include <memory>
#include <optional>
#include <utility>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/time/time.h"
#include "src/core/lib/debug/trace.h"

static thread_local bool g_timer_thread;

namespace grpc_event_engine::experimental {

void TimerManager::RunSomeTimers(
    std::vector<experimental::EventEngine::Closure*> timers) {
  for (auto* timer : timers) {
    thread_pool_->Run(timer);
  }
}

bool TimerManager::WaitUntil(grpc_core::Timestamp next) {
  grpc_core::MutexLock lock(&mu_);
  if (shutdown_) return false;

  if (!kicked_) {
    cv_wait_.WaitWithTimeout(&mu_,
                             absl::Milliseconds((next - host_.Now()).millis()));
    ++wakeups_;
  }
  kicked_ = false;
  return true;
}

void TimerManager::MainLoop() {
  grpc_core::Timestamp next = grpc_core::Timestamp::InfFuture();
  std::optional<std::vector<experimental::EventEngine::Closure*>> check_result =
      timer_list_->TimerCheck(&next);
  CHECK(check_result.has_value())
      << "ERROR: More than one MainLoop is running.";
  bool timers_found = !check_result->empty();
  if (timers_found) {
    RunSomeTimers(std::move(*check_result));
  }
  thread_pool_->Run([this, next, timers_found]() {
    if (!timers_found && !WaitUntil(next)) {
      main_loop_exit_signal_->Notify();
      return;
    }
    MainLoop();
  });
}

bool TimerManager::IsTimerManagerThread() { return g_timer_thread; }

TimerManager::TimerManager(
    std::shared_ptr<grpc_event_engine::experimental::ThreadPool> thread_pool)
    : host_(this), thread_pool_(std::move(thread_pool)) {
  timer_list_ = std::make_unique<TimerList>(&host_);
  main_loop_exit_signal_.emplace();
  thread_pool_->Run([this]() { MainLoop(); });
}

grpc_core::Timestamp TimerManager::Host::Now() {
  return grpc_core::Timestamp::FromTimespecRoundDown(
      gpr_now(GPR_CLOCK_MONOTONIC));
}

void TimerManager::TimerInit(Timer* timer, grpc_core::Timestamp deadline,
                             experimental::EventEngine::Closure* closure) {
  if (GRPC_TRACE_FLAG_ENABLED(timer)) {
    grpc_core::MutexLock lock(&mu_);
    if (shutdown_) {
      LOG(ERROR) << "WARNING: TimerManager::" << this
                 << ": scheduling Closure::" << closure
                 << " after TimerManager has been shut down.";
    }
  }
  timer_list_->TimerInit(timer, deadline, closure);
}

bool TimerManager::TimerCancel(Timer* timer) {
  return timer_list_->TimerCancel(timer);
}

void TimerManager::Shutdown() {
  {
    grpc_core::MutexLock lock(&mu_);
    if (shutdown_) return;
    GRPC_TRACE_VLOG(timer, 2) << "TimerManager::" << this << " shutting down";
    shutdown_ = true;

    cv_wait_.Signal();
  }
  main_loop_exit_signal_->WaitForNotification();
  GRPC_TRACE_VLOG(timer, 2) << "TimerManager::" << this << " shutdown complete";
}

TimerManager::~TimerManager() { Shutdown(); }

void TimerManager::Host::Kick() { timer_manager_->Kick(); }

void TimerManager::Kick() {
  grpc_core::MutexLock lock(&mu_);
  kicked_ = true;
  cv_wait_.Signal();
}

void TimerManager::RestartPostFork() {
  grpc_core::MutexLock lock(&mu_);
  CHECK(GPR_LIKELY(shutdown_));
  GRPC_TRACE_VLOG(timer, 2)
      << "TimerManager::" << this << " restarting after shutdown";
  shutdown_ = false;
  main_loop_exit_signal_.emplace();
  thread_pool_->Run([this]() { MainLoop(); });
}

void TimerManager::PrepareFork() { Shutdown(); }
void TimerManager::PostforkParent() { RestartPostFork(); }
void TimerManager::PostforkChild() { RestartPostFork(); }

}
