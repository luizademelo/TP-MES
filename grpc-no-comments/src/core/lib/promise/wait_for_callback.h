// Copyright 2023 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_PROMISE_WAIT_FOR_CALLBACK_H
#define GRPC_SRC_CORE_LIB_PROMISE_WAIT_FOR_CALLBACK_H

#include <grpc/support/port_platform.h>

#include <memory>
#include <utility>

#include "absl/base/thread_annotations.h"
#include "src/core/lib/promise/activity.h"
#include "src/core/lib/promise/poll.h"
#include "src/core/util/sync.h"

namespace grpc_core {

class WaitForCallback {
 public:

  auto MakeWaitPromise() {
    return [state = state_]() -> Poll<Empty> {
      MutexLock lock(&state->mutex);
      if (state->done) return Empty{};
      state->waker = GetContext<Activity>()->MakeNonOwningWaker();
      return Pending{};
    };
  }

  auto MakeCallback() {
    return [state = state_]() {
      ReleasableMutexLock lock(&state->mutex);
      state->done = true;
      auto waker = std::move(state->waker);
      lock.Release();
      waker.Wakeup();
    };
  }

 private:
  struct State {
    Mutex mutex;
    bool done ABSL_GUARDED_BY(mutex) = false;
    Waker waker ABSL_GUARDED_BY(mutex);
  };
  const std::shared_ptr<State> state_{std::make_shared<State>()};
};

}

#endif
