Here's the commented version of the code:

```c++
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

// A synchronization primitive that allows a promise to wait for a callback to be invoked.
// This is useful for bridging callback-based APIs with promise-based code.
class WaitForCallback {
 public:
  // Creates and returns a promise that will:
  // - Return immediately with Empty if the callback has already been called
  // - Otherwise, register a waker and return Pending, suspending the promise
  //   until the callback is invoked
  auto MakeWaitPromise() {
    return [state = state_]() -> Poll<Empty> {
      MutexLock lock(&state->mutex);
      if (state->done) return Empty{};  // Callback already completed
      // Store waker to be notified when callback occurs
      state->waker = GetContext<Activity>()->MakeNonOwningWaker();
      return Pending{};  // Suspend the promise
    };
  }

  // Creates and returns a callback that when invoked:
  // - Marks the operation as done
  // - Wakes up any waiting promise
  auto MakeCallback() {
    return [state = state_]() {
      ReleasableMutexLock lock(&state->mutex);
      state->done = true;  // Mark operation complete
      auto waker = std::move(state->waker);  // Take ownership of waker
      lock.Release();  // Release lock before wakeup to avoid lock contention
      waker.Wakeup();  // Wake up waiting promise if any
    };
  }

 private:
  // Internal state shared between the promise and callback
  struct State {
    Mutex mutex;  // Protects access to done and waker
    bool done ABSL_GUARDED_BY(mutex) = false;  // Flag indicating callback completion
    Waker waker ABSL_GUARDED_BY(mutex);  // Waker for pending promise
  };
  // Shared state instance (shared_ptr allows sharing between promise and callback)
  const std::shared_ptr<State> state_{std::make_shared<State>()};
};

}  // namespace grpc_core

#endif  // GRPC_SRC_CORE_LIB_PROMISE_WAIT_FOR_CALLBACK_H
```

Key points explained in the comments:
1. Overall class purpose - bridging callback and promise worlds
2. MakeWaitPromise behavior - returns immediately if done, otherwise suspends
3. MakeCallback behavior - marks done and wakes pending promise
4. State structure and its synchronization requirements
5. Use of shared_ptr for shared state management
6. Thread safety considerations with mutex and ABSL annotations
7. Purpose of each member variable in State

The comments aim to explain both the high-level purpose and the detailed implementation choices while helping future maintainers understand the synchronization requirements.