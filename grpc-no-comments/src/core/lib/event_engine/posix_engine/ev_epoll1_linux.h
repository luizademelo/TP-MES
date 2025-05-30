// Copyright 2022 The gRPC Authors

#ifndef GRPC_SRC_CORE_LIB_EVENT_ENGINE_POSIX_ENGINE_EV_EPOLL1_LINUX_H
#define GRPC_SRC_CORE_LIB_EVENT_ENGINE_POSIX_ENGINE_EV_EPOLL1_LINUX_H
#include <grpc/event_engine/event_engine.h>
#include <grpc/support/port_platform.h>

#include <list>
#include <memory>
#include <string>

#include "absl/base/thread_annotations.h"
#include "absl/container/inlined_vector.h"
#include "absl/functional/function_ref.h"
#include "absl/strings/string_view.h"
#include "src/core/lib/event_engine/poller.h"
#include "src/core/lib/event_engine/posix_engine/event_poller.h"
#include "src/core/lib/event_engine/posix_engine/internal_errqueue.h"
#include "src/core/lib/event_engine/posix_engine/wakeup_fd_posix.h"
#include "src/core/lib/iomgr/port.h"
#include "src/core/util/sync.h"

#ifdef GRPC_LINUX_EPOLL
#include <sys/epoll.h>
#endif

#define MAX_EPOLL_EVENTS 100

namespace grpc_event_engine::experimental {

class Epoll1EventHandle;

class Epoll1Poller : public PosixEventPoller {
 public:
  explicit Epoll1Poller(Scheduler* scheduler);
  EventHandle* CreateHandle(int fd, absl::string_view name,
                            bool track_err) override;
  Poller::WorkResult Work(
      grpc_event_engine::experimental::EventEngine::Duration timeout,
      absl::FunctionRef<void()> schedule_poll_again) override;
  std::string Name() override { return "epoll1"; }
  void Kick() override;
  Scheduler* GetScheduler() { return scheduler_; }
  void Shutdown() override;
  bool CanTrackErrors() const override {
#ifdef GRPC_POSIX_SOCKET_TCP
    return KernelSupportsErrqueue();
#else
    return false;
#endif
  }
  ~Epoll1Poller() override;

  void PrepareFork() override;
  void PostforkParent() override;
  void PostforkChild() override;

  void Close();

 private:

  using Events = absl::InlinedVector<Epoll1EventHandle*, 5>;

  bool ProcessEpollEvents(int max_epoll_events_to_handle,
                          Events& pending_events);

  int DoEpollWait(
      grpc_event_engine::experimental::EventEngine::Duration timeout);
  class HandlesList {
   public:
    explicit HandlesList(Epoll1EventHandle* handle) : handle(handle) {}
    Epoll1EventHandle* handle;
    Epoll1EventHandle* next = nullptr;
    Epoll1EventHandle* prev = nullptr;
  };
  friend class Epoll1EventHandle;
#ifdef GRPC_LINUX_EPOLL
  struct EpollSet {
    int epfd = -1;

    struct epoll_event events[MAX_EPOLL_EVENTS]{};

    int num_events = 0;

    int cursor = 0;
  };
#else
  struct EpollSet {};
#endif
  grpc_core::Mutex mu_;
  Scheduler* scheduler_;

  EpollSet g_epoll_set_;
  bool was_kicked_ ABSL_GUARDED_BY(mu_);
  std::list<EventHandle*> free_epoll1_handles_list_ ABSL_GUARDED_BY(mu_);
  std::unique_ptr<WakeupFd> wakeup_fd_;
  bool closed_;
};

std::shared_ptr<Epoll1Poller> MakeEpoll1Poller(Scheduler* scheduler);

}

#endif
