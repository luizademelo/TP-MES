// Copyright 2022 gRPC authors.

#include "src/core/lib/event_engine/forkable.h"

#include <grpc/support/port_platform.h>

#include "absl/log/check.h"

#ifdef GRPC_POSIX_FORK_ALLOW_PTHREAD_ATFORK
#include <pthread.h>
#endif

#include <algorithm>
#include <utility>
#include <vector>

#include "src/core/config/config_vars.h"
#include "src/core/lib/debug/trace.h"

namespace grpc_event_engine::experimental {

namespace {
bool IsForkEnabled() {
  static bool enabled = grpc_core::ConfigVars::Get().EnableForkSupport();
  return enabled;
}
}

void ObjectGroupForkHandler::RegisterForkable(
    std::shared_ptr<Forkable> forkable, GRPC_UNUSED void (*prepare)(void),
    GRPC_UNUSED void (*parent)(void), GRPC_UNUSED void (*child)(void)) {
  if (IsForkEnabled()) {
    CHECK(!is_forking_);
    forkables_.emplace_back(forkable);
#ifdef GRPC_POSIX_FORK_ALLOW_PTHREAD_ATFORK
    if (!std::exchange(registered_, true)) {
      pthread_atfork(prepare, parent, child);
    }
#endif
  }
}

void ObjectGroupForkHandler::Prefork() {
  if (IsForkEnabled()) {
    CHECK(!std::exchange(is_forking_, true));
    GRPC_TRACE_LOG(fork, INFO) << "PrepareFork";
    for (auto it = forkables_.begin(); it != forkables_.end();) {
      auto shared = it->lock();
      if (shared) {
        shared->PrepareFork();
        ++it;
      } else {
        it = forkables_.erase(it);
      }
    }
  }
}

void ObjectGroupForkHandler::PostforkParent() {
  if (IsForkEnabled()) {
    CHECK(is_forking_);
    GRPC_TRACE_LOG(fork, INFO) << "PostforkParent";
    for (auto it = forkables_.begin(); it != forkables_.end();) {
      auto shared = it->lock();
      if (shared) {
        shared->PostforkParent();
        ++it;
      } else {
        it = forkables_.erase(it);
      }
    }
    is_forking_ = false;
  }
}

void ObjectGroupForkHandler::PostforkChild() {
  if (IsForkEnabled()) {
    CHECK(is_forking_);
    GRPC_TRACE_LOG(fork, INFO) << "PostforkChild";
    for (auto it = forkables_.begin(); it != forkables_.end();) {
      auto shared = it->lock();
      if (shared) {
        shared->PostforkChild();
        ++it;
      } else {
        it = forkables_.erase(it);
      }
    }
    is_forking_ = false;
  }
}

}
