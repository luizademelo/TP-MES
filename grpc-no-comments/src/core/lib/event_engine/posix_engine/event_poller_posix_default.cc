// Copyright 2022 The gRPC Authors

#include <grpc/support/port_platform.h>

#include <memory>
#include <string>

#include "absl/strings/str_split.h"
#include "absl/strings/string_view.h"
#include "src/core/config/config_vars.h"
#include "src/core/lib/event_engine/forkable.h"
#include "src/core/lib/event_engine/posix_engine/ev_epoll1_linux.h"
#include "src/core/lib/event_engine/posix_engine/ev_poll_posix.h"
#include "src/core/lib/event_engine/posix_engine/event_poller.h"
#include "src/core/lib/iomgr/port.h"
#include "src/core/util/no_destruct.h"

namespace grpc_event_engine::experimental {

#ifdef GRPC_POSIX_SOCKET_TCP
namespace {

grpc_core::NoDestruct<ObjectGroupForkHandler> g_poller_fork_manager;

class PollerForkCallbackMethods {
 public:
  static void Prefork() { g_poller_fork_manager->Prefork(); }
  static void PostforkParent() { g_poller_fork_manager->PostforkParent(); }
  static void PostforkChild() { g_poller_fork_manager->PostforkChild(); }
};

bool PollStrategyMatches(absl::string_view strategy, absl::string_view want) {
  return strategy == "all" || strategy == want;
}
}

std::shared_ptr<PosixEventPoller> MakeDefaultPoller(Scheduler* scheduler) {
  std::shared_ptr<PosixEventPoller> poller;
  auto strings =
      absl::StrSplit(grpc_core::ConfigVars::Get().PollStrategy(), ',');
  for (auto it = strings.begin(); it != strings.end() && poller == nullptr;
       it++) {
    if (PollStrategyMatches(*it, "epoll1")) {
      poller = MakeEpoll1Poller(scheduler);
    }
    if (poller == nullptr && PollStrategyMatches(*it, "poll")) {

      poller = MakePollPoller(scheduler, false);
    } else if (poller == nullptr && PollStrategyMatches(*it, "none")) {

      poller = MakePollPoller(scheduler, true);
    }
  }
  g_poller_fork_manager->RegisterForkable(
      poller, PollerForkCallbackMethods::Prefork,
      PollerForkCallbackMethods::PostforkParent,
      PollerForkCallbackMethods::PostforkChild);
  return poller;
}

#else

std::shared_ptr<PosixEventPoller> MakeDefaultPoller(Scheduler* ) {
  return nullptr;
}

#endif

}
