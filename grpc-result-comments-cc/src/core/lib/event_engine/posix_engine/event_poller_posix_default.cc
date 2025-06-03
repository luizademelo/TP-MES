Here's the commented version of the code:

```c++
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

// Only compile this code if POSIX socket TCP support is enabled
#ifdef GRPC_POSIX_SOCKET_TCP
namespace {

// Global poller fork handler instance that will manage fork events for pollers
// Uses NoDestruct to ensure it's never destroyed (as it may be needed until program exit)
grpc_core::NoDestruct<ObjectGroupForkHandler> g_poller_fork_manager;

// Helper class containing static methods for fork event callbacks
class PollerForkCallbackMethods {
 public:
  // Called before forking
  static void Prefork() { g_poller_fork_manager->Prefork(); }
  // Called after forking in the parent process
  static void PostforkParent() { g_poller_fork_manager->PostforkParent(); }
  // Called after forking in the child process
  static void PostforkChild() { g_poller_fork_manager->PostforkChild(); }
};

// Helper function to check if a poll strategy matches a desired value
// Returns true if strategy equals "all" or matches the wanted strategy
bool PollStrategyMatches(absl::string_view strategy, absl::string_view want) {
  return strategy == "all" || strategy == want;
}
}

// Creates and returns the default poller based on configuration
// The poller type is determined by the PollStrategy config value
std::shared_ptr<PosixEventPoller> MakeDefaultPoller(Scheduler* scheduler) {
  std::shared_ptr<PosixEventPoller> poller;
  // Split the PollStrategy config string into individual strategies
  auto strings =
      absl::StrSplit(grpc_core::ConfigVars::Get().PollStrategy(), ',');
  
  // Try each strategy in order until we successfully create a poller
  for (auto it = strings.begin(); it != strings.end() && poller == nullptr;
       it++) {
    // Try to create epoll1 poller if strategy matches
    if (PollStrategyMatches(*it, "epoll1")) {
      poller = MakeEpoll1Poller(scheduler);
    }
    // If no poller created yet, try to create poll-based poller
    if (poller == nullptr && PollStrategyMatches(*it, "poll")) {
      poller = MakePollPoller(scheduler, false);
    } 
    // If no poller created yet, try to create "none" poller (disabled polling)
    else if (poller == nullptr && PollStrategyMatches(*it, "none")) {
      poller = MakePollPoller(scheduler, true);
    }
  }
  
  // Register the created poller with the fork handler
  g_poller_fork_manager->RegisterForkable(
      poller, PollerForkCallbackMethods::Prefork,
      PollerForkCallbackMethods::PostforkParent,
      PollerForkCallbackMethods::PostforkChild);
  return poller;
}

#else

// Stub implementation when POSIX socket TCP support is not enabled
std::shared_ptr<PosixEventPoller> MakeDefaultPoller(Scheduler* ) {
  return nullptr;
}

#endif

}
```