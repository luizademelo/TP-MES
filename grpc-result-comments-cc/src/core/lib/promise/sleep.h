Here's the commented version of the code:

```c++
// Copyright 2022 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_PROMISE_SLEEP_H
#define GRPC_SRC_CORE_LIB_PROMISE_SLEEP_H

#include <grpc/event_engine/event_engine.h>
#include <grpc/support/port_platform.h>

#include <atomic>
#include <utility>

#include "absl/status/status.h"
#include "src/core/lib/promise/activity.h"
#include "src/core/lib/promise/poll.h"
#include "src/core/util/time.h"

namespace grpc_core {

// A promise that completes after a specified deadline/timeout has passed.
// The promise returns an absl::Status which will be OK if the sleep completed
// normally, or an error if it was cancelled.
class Sleep final {
 public:
  // Construct a Sleep promise that will complete at the specified deadline.
  explicit Sleep(Timestamp deadline);
  // Construct a Sleep promise that will complete after the specified duration.
  explicit Sleep(Duration timeout) : Sleep(Timestamp::Now() + timeout) {}
  ~Sleep();

  // Disallow copying
  Sleep(const Sleep&) = delete;
  Sleep& operator=(const Sleep&) = delete;
  
  // Allow moving
  Sleep(Sleep&& other) noexcept
      : deadline_(other.deadline_),
        closure_(std::exchange(other.closure_, nullptr)) {}
  Sleep& operator=(Sleep&& other) noexcept {
    deadline_ = other.deadline_;
    std::swap(closure_, other.closure_);
    return *this;
  };

  // Poll the sleep promise:
  // Returns Pending if the deadline hasn't been reached yet,
  // or Ready with OK status if the deadline has passed.
  Poll<absl::Status> operator()();

 private:
  // Internal class that manages the timer and callback with the EventEngine.
  // Implements EventEngine::Closure to handle the timer callback.
  class ActiveClosure final
      : public grpc_event_engine::experimental::EventEngine::Closure {
   public:
    // Create an ActiveClosure that will call back at the specified deadline.
    explicit ActiveClosure(Timestamp deadline);

    // Called by the EventEngine when the timer fires.
    void Run() override;

    // Cancel the pending timer if it hasn't fired yet.
    void Cancel();

    // Returns true if the timer has already fired.
    bool HasRun() const;

   private:
    // Decrement the reference count and return true if it reached zero.
    bool Unref();

    // Waker to notify the activity when the timer fires.
    Waker waker_;

    // Reference count (starts at 2 for both the Sleep object and the timer).
    std::atomic<int> refs_{2};
    // EventEngine used to schedule the timer.
    std::shared_ptr<grpc_event_engine::experimental::EventEngine> event_engine_;
    // Handle to the scheduled timer task.
    grpc_event_engine::experimental::EventEngine::TaskHandle timer_handle_;
  };

  // The deadline when the sleep should complete.
  Timestamp deadline_;
  // Pointer to the active closure managing the timer (null if completed/moved).
  ActiveClosure* closure_{nullptr};
};

}  // namespace grpc_core

#endif  // GRPC_SRC_CORE_LIB_PROMISE_SLEEP_H
```

The comments explain:
1. The overall purpose of the Sleep class (a promise that completes after a timeout)
2. Each constructor's purpose and behavior
3. The move/copy semantics
4. The polling operator's behavior
5. The internal ActiveClosure class and its role
6. Each member variable's purpose
7. The reference counting mechanism
8. The relationship with EventEngine for timer functionality

The comments are designed to help future developers understand both the high-level behavior and implementation details of the code.