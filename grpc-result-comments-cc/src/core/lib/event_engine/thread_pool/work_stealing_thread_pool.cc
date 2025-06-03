Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

// Includes necessary headers for thread pool implementation
#include "src/core/lib/event_engine/thread_pool/work_stealing_thread_pool.h"

#include <grpc/support/port_platform.h>
#include <grpc/support/thd_id.h>
#include <inttypes.h>

#include <atomic>
#include <chrono>
#include <cstddef>
#include <memory>
#include <optional>
#include <utility>

// ABSL headers for utilities and logging
#include "absl/functional/any_invocable.h"
#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/time/clock.h"
#include "absl/time/time.h"

// gRPC core headers
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/event_engine/common_closures.h"
#include "src/core/lib/event_engine/thread_local.h"
#include "src/core/lib/event_engine/work_queue/basic_work_queue.h"
#include "src/core/lib/event_engine/work_queue/work_queue.h"
#include "src/core/util/backoff.h"
#include "src/core/util/crash.h"
#include "src/core/util/env.h"
#include "src/core/util/examine_stack.h"
#include "src/core/util/thd.h"
#include "src/core/util/time.h"

// Platform-specific signal handling headers
#ifdef GPR_POSIX_SYNC
#include <csignal>
#elif defined(GPR_WINDOWS)
#include <signal.h>
#endif

namespace grpc_event_engine::experimental {

namespace {
// Constants for thread pool configuration

// Maximum idle time before a thread exits
constexpr auto kIdleThreadLimit = std::chrono::seconds(20);

// Rate limit for logging during blocking quiesce
constexpr size_t kBlockingQuiesceLogRateSeconds = 3;

// Minimum time between starting new threads when throttled
constexpr grpc_core::Duration kTimeBetweenThrottledThreadStarts =
    grpc_core::Duration::Seconds(1);

// Worker thread sleep time configuration
constexpr grpc_core::Duration kWorkerThreadMinSleepBetweenChecks{
    grpc_core::Duration::Milliseconds(15)};
constexpr grpc_core::Duration kWorkerThreadMaxSleepBetweenChecks{
    grpc_core::Duration::Seconds(3)};

// Lifeguard thread sleep time configuration
constexpr grpc_core::Duration kLifeguardMinSleepBetweenChecks{
    grpc_core::Duration::Milliseconds(15)};
constexpr grpc_core::Duration kLifeguardMaxSleepBetweenChecks{
    grpc_core::Duration::Seconds(1)};

// Timeout for waiting for threads to shutdown
constexpr grpc_core::Duration kBlockUntilThreadCountTimeout{
    grpc_core::Duration::Seconds(60)};

// Platform-specific configuration for verbose logging and stack dumping
#ifdef GPR_POSIX_SYNC
const bool g_log_verbose_failures =
    grpc_core::GetEnv("GRPC_THREAD_POOL_VERBOSE_FAILURES").has_value();
constexpr int kDumpStackSignal = SIGUSR1;
#elif defined(GPR_WINDOWS)
const bool g_log_verbose_failures =
    grpc_core::GetEnv("GRPC_THREAD_POOL_VERBOSE_FAILURES").has_value();
constexpr int kDumpStackSignal = SIGTERM;
#else
constexpr bool g_log_verbose_failures = false;
constexpr int kDumpStackSignal = -1;
#endif

// Global counter for reported stack dumps
std::atomic<size_t> g_reported_dump_count{0};

// Signal handler for dumping thread stacks
void DumpSignalHandler(int) {
  const auto trace = grpc_core::GetCurrentStackTrace();
  if (!trace.has_value()) {
    LOG(ERROR) << "DumpStack::" << gpr_thd_currentid()
               << ": Stack trace not available";
  } else {
    LOG(ERROR) << "DumpStack::" << gpr_thd_currentid() << ": " << trace.value();
  }
  g_reported_dump_count.fetch_add(1);
  grpc_core::Thread::Kill(gpr_thd_currentid());
}

}  // namespace

// Thread-local work queue pointer
thread_local WorkQueue* g_local_queue = nullptr;

// WorkStealingThreadPool implementation

// Constructor initializes the thread pool with reserve_threads
WorkStealingThreadPool::WorkStealingThreadPool(size_t reserve_threads)
    : pool_{std::make_shared<WorkStealingThreadPoolImpl>(reserve_threads)} {
  if (g_log_verbose_failures) {
    GRPC_TRACE_LOG(event_engine, INFO)
        << "WorkStealingThreadPool verbose failures are enabled";
  }
  pool_->Start();
}

// Quiesce the thread pool (graceful shutdown)
void WorkStealingThreadPool::Quiesce() { pool_->Quiesce(); }

// Destructor checks if pool is properly quiesced
WorkStealingThreadPool::~WorkStealingThreadPool() {
  CHECK(pool_->IsQuiesced());
}

// Run a callback in the thread pool
void WorkStealingThreadPool::Run(absl::AnyInvocable<void()> callback) {
  Run(SelfDeletingClosure::Create(std::move(callback)));
}

// Run a closure in the thread pool
void WorkStealingThreadPool::Run(EventEngine::Closure* closure) {
  pool_->Run(closure);
}

// TheftRegistry implementation (for work stealing)

// Enroll a work queue in the theft registry
void WorkStealingThreadPool::TheftRegistry::Enroll(WorkQueue* queue) {
  grpc_core::MutexLock lock(&mu_);
  queues_.emplace(queue);
}

// Unenroll a work queue from the theft registry
void WorkStealingThreadPool::TheftRegistry::Unenroll(WorkQueue* queue) {
  grpc_core::MutexLock lock(&mu_);
  queues_.erase(queue);
}

// Attempt to steal a closure from any enrolled queue
EventEngine::Closure* WorkStealingThreadPool::TheftRegistry::StealOne() {
  grpc_core::MutexLock lock(&mu_);
  EventEngine::Closure* closure;
  for (auto* queue : queues_) {
    closure = queue->PopMostRecent();
    if (closure != nullptr) return closure;
  }
  return nullptr;
}

// Fork-related methods

void WorkStealingThreadPool::PrepareFork() { pool_->PrepareFork(); }
void WorkStealingThreadPool::PostforkParent() { pool_->Postfork(); }
void WorkStealingThreadPool::PostforkChild() { pool_->Postfork(); }

// WorkStealingThreadPoolImpl implementation

// Constructor initializes with reserve threads count
WorkStealingThreadPool::WorkStealingThreadPoolImpl::WorkStealingThreadPoolImpl(
    size_t reserve_threads)
    : reserve_threads_(reserve_threads), queue_(this) {}

// Start the thread pool by creating reserve threads
void WorkStealingThreadPool::WorkStealingThreadPoolImpl::Start() {
  for (size_t i = 0; i < reserve_threads_; i++) {
    StartThread();
  }
  grpc_core::MutexLock lock(&lifeguard_ptr_mu_);
  lifeguard_ = std::make_unique<Lifeguard>(this);
}

// Run a closure in the thread pool
void WorkStealingThreadPool::WorkStealingThreadPoolImpl::Run(
    EventEngine::Closure* closure) {
  CHECK(!IsQuiesced());
  // Add to local queue if running in pool thread, otherwise to main queue
  if (g_local_queue != nullptr && g_local_queue->owner() == this) {
    g_local_queue->Add(closure);
  } else {
    queue_.Add(closure);
  }
  work_signal_.Signal();
}

// Start a new worker thread
void WorkStealingThreadPool::WorkStealingThreadPoolImpl::StartThread() {
  last_started_thread_.store(
      grpc_core::Timestamp::Now().milliseconds_after_process_epoch(),
      std::memory_order_relaxed);
  grpc_core::Thread(
      "event_engine",
      [](void* arg) {
        ThreadState* worker = static_cast<ThreadState*>(arg);
        worker->ThreadBody();
        delete worker;
      },
      new ThreadState(shared_from_this()), nullptr,
      grpc_core::Thread::Options().set_tracked(false).set_joinable(false))
      .Start();
}

// Quiesce the thread pool (graceful shutdown)
void WorkStealingThreadPool::WorkStealingThreadPoolImpl::Quiesce() {
  SetShutdown(true);

  bool is_threadpool_thread = g_local_queue != nullptr;
  work_signal()->SignalAll();
  auto threads_were_shut_down = living_thread_count_.BlockUntilThreadCount(
      is_threadpool_thread ? 1 : 0, "shutting down",
      g_log_verbose_failures ? kBlockUntilThreadCountTimeout
                             : grpc_core::Duration::Infinity());
  if (!threads_were_shut_down.ok() && g_log_verbose_failures) {
    DumpStacksAndCrash();
  }
  CHECK(queue_.Empty());
  quiesced_.store(true, std::memory_order_relaxed);
  grpc_core::MutexLock lock(&lifeguard_ptr_mu_);
  lifeguard_.reset();
}

// Set throttled state for thread creation
bool WorkStealingThreadPool::WorkStealingThreadPoolImpl::SetThrottled(
    bool throttled) {
  return throttled_.exchange(throttled, std::memory_order_relaxed);
}

// Set shutdown state
void WorkStealingThreadPool::WorkStealingThreadPoolImpl::SetShutdown(
    bool is_shutdown) {
  auto was_shutdown = shutdown_.exchange(is_shutdown);
  CHECK(is_shutdown != was_shutdown);
  work_signal_.SignalAll();
}

// Set forking state
void WorkStealingThreadPool::WorkStealingThreadPoolImpl::SetForking(
    bool is_forking) {
  auto was_forking = forking_.exchange(is_forking);
  CHECK(is_forking != was_forking);
}

// Check if in forking state
bool WorkStealingThreadPool::WorkStealingThreadPoolImpl::IsForking() {
  return forking_.load(std::memory_order_relaxed);
}

// Check if in shutdown state
bool WorkStealingThreadPool::WorkStealingThreadPoolImpl::IsShutdown() {
  return shutdown_.load(std::memory_order_relaxed);
}

// Check if pool is quiesced
bool WorkStealingThreadPool::WorkStealingThreadPoolImpl::IsQuiesced() {
  return quiesced_.load(std::memory_order_relaxed);
}

// Prepare for fork - shutdown all threads
void WorkStealingThreadPool::WorkStealingThreadPoolImpl::PrepareFork() {
  GRPC_TRACE_LOG(event_engine, INFO)
      << "WorkStealingThreadPoolImpl::PrepareFork";
  SetForking(true);
  work_signal_.SignalAll();
  auto threads_were_shut_down = living_thread_count_.BlockUntilThreadCount(
      0, "forking", kBlockUntilThreadCountTimeout);
  if (!threads_were_shut_down.ok() && g_log_verbose_failures) {
    DumpStacksAndCrash();
  }
  grpc_core::MutexLock lock(&lifeguard_ptr_mu_);
  lifeguard_.reset();
}

// Post-fork handler - restart the pool
void WorkStealingThreadPool::WorkStealingThreadPoolImpl::Postfork() {
  SetForking(false);
  Start();
}

// Track a thread in the pool
void WorkStealingThreadPool::WorkStealingThreadPoolImpl::TrackThread(
    gpr_thd_id tid) {
  grpc_core::MutexLock lock(&thd_set_mu_);
  thds_.insert(tid);
}

// Untrack a thread from the pool
void WorkStealingThreadPool::WorkStealingThreadPoolImpl::UntrackThread(
    gpr_thd_id tid) {
  grpc_core::MutexLock lock(&thd_set_mu_);
  thds_.erase(tid);
}

// Dump all thread stacks and crash (for debugging)
void WorkStealingThreadPool::WorkStealingThreadPoolImpl::DumpStacksAndCrash() {
  grpc_core::MutexLock lock(&thd_set_mu_);
  LOG(ERROR) << "Pool did not quiesce in time, gRPC will not shut down "
                "cleanly. Dumping all "
             << thds_.size() << " thread stacks.";
  for (const auto tid : thds_) {
    grpc_core::Thread::Signal(tid, kDumpStackSignal);
  }

  auto ignore_thread_count = g_local_queue != nullptr ? 1 : 0;
  while (living_thread_count_.count() - ignore_thread_count >
         g_reported_dump_count.load()) {
    absl::SleepFor(absl::Milliseconds(200));
  }
  grpc_core::Crash(
      "Pool did not quiesce in time, gRPC will not shut down cleanly.");
}

// Lifeguard implementation (manages thread pool size)

// Lifeguard constructor
WorkStealingThreadPool::WorkStealingThreadPoolImpl::Lifeguard::Lifeguard(
    WorkStealingThreadPoolImpl* pool)
    : pool_(pool),
      backoff_(grpc_core::BackOff::Options()
                   .set_initial_backoff(kLifeguardMinSleepBetweenChecks)
                   .set_max_backoff(kLifeguardMaxSleepBetweenChecks)
                   .set_multiplier(1.3)),
      lifeguard_should_shut_down_(std::make_unique<grpc_core::Notification>()),
      lifeguard_is_shut_down_(std::make_unique<grpc_core::Notification>()) {

  lifeguard_running_.store(true);
  grpc_core::Thread(
      "lifeguard",
      [](void* arg) {
        auto* lifeguard = static_cast<Lifeguard*>(arg);
        lifeguard->LifeguardMain();
      },
      this, nullptr,
      grpc_core::Thread::Options().set_tracked(false).set_joinable(false))
      .Start();
}

// Lifeguard main loop - manages thread pool size
void WorkStealingThreadPool::WorkStealingThreadPoolImpl::Lifeguard::
    LifeguardMain() {
  while (true) {
    if (pool_->IsForking()) break;

    if (pool_->IsShutdown()) {
      if (pool_->IsQuiesced()) break;
      if (MaybeStartNewThread()) {
        backoff_.Reset();
      }
      pool_->work_signal()->WaitWithTimeout(backoff_.NextAttemptDelay());
      continue;
    }
    lifeguard_should_shut_down_->WaitForNotificationWithTimeout(
        absl::Milliseconds(backoff_.NextAttemptDelay().millis()));
    MaybeStartNewThread();
  }
  lifeguard_running_.store(false, std::memory_order_relaxed);
  lifeguard_is_shut_down_->Notify();
}

// Lifeguard destructor
WorkStealingThreadPool::WorkStealingThreadPoolImpl::Lifeguard::~Lifeguard() {
  lifeguard_should_shut_down_->Notify();
  while (lifeguard_running_.load(std::memory_order_relaxed)) {
    GRPC_LOG_EVERY_N_SEC_DELAYED_DEBUG(
        kBlockingQuiesceLogRateSeconds, "%s",
        "Waiting for lifeguard thread to shut down");
    lifeguard_is_shut_down_->WaitForNotification();
  }

  lifeguard_is_shut_down_->WaitForNotification();
  backoff_.Reset();
  lifeguard_should_shut_down_ = std::make_unique<grpc_core::Notification>();
  lifeguard_is_shut_down_ = std::make_unique<grpc_core::Notification>();
}

// Decide whether to start a new thread
bool WorkStealingThreadPool::WorkStealingThreadPoolImpl::Lifeguard::
    MaybeStartNewThread() {
  if (pool_->forking_.load()) return false;
  const auto living_thread_count = pool_->living_thread_count()->count();

  // Don't start new thread if there are idle threads
  if (pool_->busy_thread_count()->count() < living_thread_count) {
    if (!pool_->queue_.Empty()) {
      pool_->work_signal()->Signal();
      backoff_.Reset();
    }
    return false;
  }

  // Throttle thread creation
  if (grpc_core::Timestamp::Now() -
          grpc_core::Timestamp::FromMillisecondsAfterProcessEpoch(
              pool_->last_started_thread_) <
      kTimeBetweenThrottledThreadStarts) {
    backoff_.Reset();
    return false;
  }

  GRPC_TRACE_LOG(event_engine, INFO)
      << "Starting new ThreadPool thread due to backlog (total threads: "
      << living_thread_count + 1;
  pool_->StartThread();

  backoff_.Reset();
  return true;
}

// ThreadState implementation (worker thread)

// ThreadState constructor
WorkStealingThreadPool::ThreadState::ThreadState(
    std::shared_ptr<WorkStealingThreadPoolImpl> pool)
    : pool_(std::move(pool)),
      auto_thread_counter_(
          pool_->living_thread_count()->MakeAutoThreadCounter()),
      backoff_(grpc_core::BackOff::Options()
                   .set_initial_backoff(kWorkerThreadMinSleepBetweenChecks)
                   .set_max_backoff(kWorkerThreadMaxSleepBetweenChecks)
                   .set_multiplier(1.3)),
      busy_count_idx_(pool_->busy_thread_count()->NextIndex()) {}

// Main worker thread body
void WorkStealingThreadPool::ThreadState::ThreadBody() {
  // Set up signal handler for verbose failures if enabled
  if (g_log_verbose_failures) {
#ifdef GPR_POSIX_SYNC
    std::signal(kDumpStackSignal, DumpSignalHandler);
#elif defined(GPR_WINDOWS)
    signal(kDumpStackSignal, DumpSignalHandler);
#endif
    pool_->TrackThread(gpr_thd_currentid());
  }
  
  // Initialize thread-local work queue