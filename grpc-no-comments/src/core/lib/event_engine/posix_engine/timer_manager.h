
// Copyright 2017 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_EVENT_ENGINE_POSIX_ENGINE_TIMER_MANAGER_H
#define GRPC_SRC_CORE_LIB_EVENT_ENGINE_POSIX_ENGINE_TIMER_MANAGER_H

#include <grpc/event_engine/event_engine.h>
#include <grpc/support/port_platform.h>
#include <stdint.h>

#include <memory>
#include <optional>
#include <vector>

#include "absl/base/thread_annotations.h"
#include "src/core/lib/event_engine/forkable.h"
#include "src/core/lib/event_engine/posix_engine/timer.h"
#include "src/core/lib/event_engine/thread_pool/thread_pool.h"
#include "src/core/util/notification.h"
#include "src/core/util/sync.h"
#include "src/core/util/time.h"

namespace grpc_event_engine::experimental {

class TimerManager final : public grpc_event_engine::experimental::Forkable {
 public:
  explicit TimerManager(
      std::shared_ptr<grpc_event_engine::experimental::ThreadPool> thread_pool);
  ~TimerManager() override;

  grpc_core::Timestamp Now() { return host_.Now(); }

  void TimerInit(Timer* timer, grpc_core::Timestamp deadline,
                 experimental::EventEngine::Closure* closure);
  bool TimerCancel(Timer* timer);

  static bool IsTimerManagerThread();

  void Shutdown();

  void PrepareFork() override;
  void PostforkParent() override;
  void PostforkChild() override;

 private:
  class Host final : public TimerListHost {
   public:
    explicit Host(TimerManager* timer_manager)
        : timer_manager_(timer_manager) {}

    void Kick() override;
    grpc_core::Timestamp Now() override;

   private:
    TimerManager* const timer_manager_;
  };

  void RestartPostFork();
  void MainLoop();
  void RunSomeTimers(std::vector<experimental::EventEngine::Closure*> timers);
  bool WaitUntil(grpc_core::Timestamp next);
  void Kick();

  grpc_core::Mutex mu_;

  grpc_core::CondVar cv_wait_;
  Host host_;

  bool shutdown_ ABSL_GUARDED_BY(mu_) = false;

  bool kicked_ ABSL_GUARDED_BY(mu_) = false;

  uint64_t wakeups_ ABSL_GUARDED_BY(mu_) = false;

  std::unique_ptr<TimerList> timer_list_;
  std::shared_ptr<grpc_event_engine::experimental::ThreadPool> thread_pool_;
  std::optional<grpc_core::Notification> main_loop_exit_signal_;
};

}

#endif
