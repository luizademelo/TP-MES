
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_EVENT_ENGINE_THREAD_POOL_WORK_STEALING_THREAD_POOL_H
#define GRPC_SRC_CORE_LIB_EVENT_ENGINE_THREAD_POOL_WORK_STEALING_THREAD_POOL_H

#include <grpc/event_engine/event_engine.h>
#include <grpc/support/port_platform.h>
#include <grpc/support/thd_id.h>
#include <stddef.h>
#include <stdint.h>

#include <atomic>
#include <memory>

#include "absl/base/thread_annotations.h"
#include "absl/container/flat_hash_set.h"
#include "absl/functional/any_invocable.h"
#include "src/core/lib/event_engine/thread_pool/thread_count.h"
#include "src/core/lib/event_engine/thread_pool/thread_pool.h"
#include "src/core/lib/event_engine/work_queue/basic_work_queue.h"
#include "src/core/lib/event_engine/work_queue/work_queue.h"
#include "src/core/util/backoff.h"
#include "src/core/util/notification.h"
#include "src/core/util/sync.h"
#include "src/core/util/time.h"

namespace grpc_event_engine::experimental {

class WorkStealingThreadPool final : public ThreadPool {
 public:
  explicit WorkStealingThreadPool(size_t reserve_threads);

  ~WorkStealingThreadPool() override;

  void Quiesce() override;

  void Run(absl::AnyInvocable<void()> callback) override;
  void Run(EventEngine::Closure* closure) override;

  void PrepareFork() override;
  void PostforkParent() override;
  void PostforkChild() override;

 private:

  class WorkSignal {
   public:
    void Signal();
    void SignalAll();

    bool WaitWithTimeout(grpc_core::Duration time);

   private:
    grpc_core::Mutex mu_;
    grpc_core::CondVar cv_ ABSL_GUARDED_BY(mu_);
  };

  class TheftRegistry {
   public:

    void Enroll(WorkQueue* queue) ABSL_LOCKS_EXCLUDED(mu_);

    void Unenroll(WorkQueue* queue) ABSL_LOCKS_EXCLUDED(mu_);

    EventEngine::Closure* StealOne() ABSL_LOCKS_EXCLUDED(mu_);

   private:
    grpc_core::Mutex mu_;
    absl::flat_hash_set<WorkQueue*> queues_ ABSL_GUARDED_BY(mu_);
  };

  class WorkStealingThreadPoolImpl
      : public std::enable_shared_from_this<WorkStealingThreadPoolImpl> {
   public:
    explicit WorkStealingThreadPoolImpl(size_t reserve_threads);

    void Start();

    void Run(EventEngine::Closure* closure);

    void StartThread();

    void Quiesce();

    bool SetThrottled(bool throttle);

    void SetShutdown(bool is_shutdown);

    void SetForking(bool is_forking);

    void PrepareFork();
    void Postfork();

    void TrackThread(gpr_thd_id tid);
    void UntrackThread(gpr_thd_id tid);

    bool IsShutdown();
    bool IsForking();
    bool IsQuiesced();
    size_t reserve_threads() { return reserve_threads_; }
    BusyThreadCount* busy_thread_count() { return &busy_thread_count_; }
    LivingThreadCount* living_thread_count() { return &living_thread_count_; }
    TheftRegistry* theft_registry() { return &theft_registry_; }
    WorkQueue* queue() { return &queue_; }
    WorkSignal* work_signal() { return &work_signal_; }

   private:

    class Lifeguard {
     public:
      explicit Lifeguard(WorkStealingThreadPoolImpl* pool);
      ~Lifeguard();

     private:

      void LifeguardMain();

      bool MaybeStartNewThread();

      WorkStealingThreadPoolImpl* pool_;
      grpc_core::BackOff backoff_;

      std::unique_ptr<grpc_core::Notification> lifeguard_should_shut_down_;
      std::unique_ptr<grpc_core::Notification> lifeguard_is_shut_down_;
      std::atomic<bool> lifeguard_running_{false};
    };

    void DumpStacksAndCrash();

    const size_t reserve_threads_;
    BusyThreadCount busy_thread_count_;
    LivingThreadCount living_thread_count_;
    TheftRegistry theft_registry_;
    BasicWorkQueue queue_;

    std::atomic<bool> shutdown_{false};
    std::atomic<bool> forking_{false};
    std::atomic<bool> quiesced_{false};
    std::atomic<uint64_t> last_started_thread_{0};

    std::atomic<bool> throttled_{false};
    WorkSignal work_signal_;
    grpc_core::Mutex lifeguard_ptr_mu_;
    std::unique_ptr<Lifeguard> lifeguard_ ABSL_GUARDED_BY(lifeguard_ptr_mu_);

    grpc_core::Mutex thd_set_mu_;
    absl::flat_hash_set<gpr_thd_id> thds_ ABSL_GUARDED_BY(thd_set_mu_);
  };

  class ThreadState {
   public:
    explicit ThreadState(std::shared_ptr<WorkStealingThreadPoolImpl> pool);
    void ThreadBody();
    void SleepIfRunning();
    bool Step();

    void FinishDraining();

   private:

    std::shared_ptr<WorkStealingThreadPoolImpl> pool_;

    LivingThreadCount::AutoThreadCounter auto_thread_counter_;
    grpc_core::BackOff backoff_;
    size_t busy_count_idx_;
  };

  const std::shared_ptr<WorkStealingThreadPoolImpl> pool_;
};

}

#endif
