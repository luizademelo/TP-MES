Here's the commented version of the code:

```c++
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

// Thread-local variable to identify timer manager threads
static thread_local bool g_timer_thread;

namespace grpc_event_engine::experimental {

// Executes a batch of timer callbacks by scheduling them in the thread pool
void TimerManager::RunSomeTimers(
    std::vector<experimental::EventEngine::Closure*> timers) {
  for (auto* timer : timers) {
    thread_pool_->Run(timer);
  }
}

// Waits until the specified timestamp or until kicked (interrupted)
// Returns false if shutdown was requested during wait
bool TimerManager::WaitUntil(grpc_core::Timestamp next) {
  grpc_core::MutexLock lock(&mu_);
  if (shutdown_) return false;

  // Only wait if not already kicked (interrupted)
  if (!kicked_) {
    cv_wait_.WaitWithTimeout(&mu_,
                             absl::Milliseconds((next - host_.Now()).millis()));
    ++wakeups_;
  }
  kicked_ = false;
  return true;
}

// Main event loop for the timer manager
void TimerManager::MainLoop() {
  // Check for expired timers and get the next deadline
  grpc_core::Timestamp next = grpc_core::Timestamp::InfFuture();
  std::optional<std::vector<experimental::EventEngine::Closure*>> check_result =
      timer_list_->TimerCheck(&next);
  
  // Ensure only one main loop is running
  CHECK(check_result.has_value())
      << "ERROR: More than one MainLoop is running.";
  
  bool timers_found = !check_result->empty();
  if (timers_found) {
    RunSomeTimers(std::move(*check_result));
  }
  
  // Schedule next iteration of the loop
  thread_pool_->Run([this, next, timers_found]() {
    if (!timers_found && !WaitUntil(next)) {
      // Exit if no timers found and shutdown requested
      main_loop_exit_signal_->Notify();
      return;
    }
    MainLoop();
  });
}

// Returns true if called from a timer manager thread
bool TimerManager::IsTimerManagerThread() { return g_timer_thread; }

// Constructor - initializes timer manager with a thread pool
TimerManager::TimerManager(
    std::shared_ptr<grpc_event_engine::experimental::ThreadPool> thread_pool)
    : host_(this), thread_pool_(std::move(thread_pool)) {
  timer_list_ = std::make_unique<TimerList>(&host_);
  main_loop_exit_signal_.emplace();
  // Start the main loop
  thread_pool_->Run([this]() { MainLoop(); });
}

// Returns current time as a Timestamp
grpc_core::Timestamp TimerManager::Host::Now() {
  return grpc_core::Timestamp::FromTimespecRoundDown(
      gpr_now(GPR_CLOCK_MONOTONIC));
}

// Initializes a new timer with a deadline and callback
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

// Attempts to cancel a timer
// Returns true if the timer was successfully cancelled
bool TimerManager::TimerCancel(Timer* timer) {
  return timer_list_->TimerCancel(timer);
}

// Shuts down the timer manager gracefully
void TimerManager::Shutdown() {
  {
    grpc_core::MutexLock lock(&mu_);
    if (shutdown_) return;
    GRPC_TRACE_VLOG(timer, 2) << "TimerManager::" << this << " shutting down";
    shutdown_ = true;

    // Wake up any waiting threads
    cv_wait_.Signal();
  }
  // Wait for main loop to exit
  main_loop_exit_signal_->WaitForNotification();
  GRPC_TRACE_VLOG(timer, 2) << "TimerManager::" << this << " shutdown complete";
}

// Destructor - ensures clean shutdown
TimerManager::~TimerManager() { Shutdown(); }

// Wrapper to kick the timer manager
void TimerManager::Host::Kick() { timer_manager_->Kick(); }

// Interrupts any current wait operation
void TimerManager::Kick() {
  grpc_core::MutexLock lock(&mu_);
  kicked_ = true;
  cv_wait_.Signal();
}

// Restarts the timer manager after a shutdown (used for fork handling)
void TimerManager::RestartPostFork() {
  grpc_core::MutexLock lock(&mu_);
  CHECK(GPR_LIKELY(shutdown_));
  GRPC_TRACE_VLOG(timer, 2)
      << "TimerManager::" << this << " restarting after shutdown";
  shutdown_ = false;
  main_loop_exit_signal_.emplace();
  thread_pool_->Run([this]() { MainLoop(); });
}

// Fork handling methods
void TimerManager::PrepareFork() { Shutdown(); }
void TimerManager::PostforkParent() { RestartPostFork(); }
void TimerManager::PostforkChild() { RestartPostFork(); }

}
```