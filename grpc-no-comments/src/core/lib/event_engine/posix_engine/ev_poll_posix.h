// Copyright 2022 The gRPC Authors

#ifndef GRPC_SRC_CORE_LIB_EVENT_ENGINE_POSIX_ENGINE_EV_POLL_POSIX_H
#define GRPC_SRC_CORE_LIB_EVENT_ENGINE_POSIX_ENGINE_EV_POLL_POSIX_H

#include <grpc/event_engine/event_engine.h>
#include <grpc/support/port_platform.h>

#include <memory>
#include <string>

#include "absl/base/thread_annotations.h"
#include "absl/functional/function_ref.h"
#include "absl/strings/string_view.h"
#include "src/core/lib/event_engine/poller.h"
#include "src/core/lib/event_engine/posix_engine/event_poller.h"
#include "src/core/lib/event_engine/posix_engine/wakeup_fd_posix.h"
#include "src/core/util/sync.h"

namespace grpc_event_engine::experimental {

class PollEventHandle;

class PollPoller : public PosixEventPoller,
                   public std::enable_shared_from_this<PollPoller> {
 public:
  explicit PollPoller(Scheduler* scheduler);
  PollPoller(Scheduler* scheduler, bool use_phony_poll);
  EventHandle* CreateHandle(int fd, absl::string_view name,
                            bool track_err) override;
  Poller::WorkResult Work(
      grpc_event_engine::experimental::EventEngine::Duration timeout,
      absl::FunctionRef<void()> schedule_poll_again) override;
  std::string Name() override { return "poll"; }
  void Kick() override;
  Scheduler* GetScheduler() { return scheduler_; }
  void Shutdown() override;
  bool CanTrackErrors() const override { return false; }
  ~PollPoller() override;

  void PrepareFork() override;
  void PostforkParent() override;
  void PostforkChild() override;

  void Close();

 private:
  void KickExternal(bool ext);
  void PollerHandlesListAddHandle(PollEventHandle* handle)
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_);
  void PollerHandlesListRemoveHandle(PollEventHandle* handle)
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_);
  friend class PollEventHandle;
  class HandlesList {
   public:
    explicit HandlesList(PollEventHandle* handle) : handle(handle) {}
    PollEventHandle* handle;
    PollEventHandle* next = nullptr;
    PollEventHandle* prev = nullptr;
  };
  grpc_core::Mutex mu_;
  Scheduler* scheduler_;
  bool use_phony_poll_;
  bool was_kicked_ ABSL_GUARDED_BY(mu_);
  bool was_kicked_ext_ ABSL_GUARDED_BY(mu_);
  int num_poll_handles_ ABSL_GUARDED_BY(mu_);
  PollEventHandle* poll_handles_list_head_ ABSL_GUARDED_BY(mu_) = nullptr;
  std::unique_ptr<WakeupFd> wakeup_fd_;
  bool closed_ ABSL_GUARDED_BY(mu_);
};

std::shared_ptr<PollPoller> MakePollPoller(Scheduler* scheduler,
                                           bool use_phony_poll);

}

#endif
