Here's the commented version of the code:

```c++
// Copyright 2024 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_PROMISE_OBSERVABLE_H
#define GRPC_SRC_CORE_LIB_PROMISE_OBSERVABLE_H

#include <grpc/support/port_platform.h>

#include "absl/container/flat_hash_set.h"
#include "absl/functional/any_invocable.h"
#include "absl/log/check.h"
#include "src/core/lib/promise/activity.h"
#include "src/core/lib/promise/poll.h"
#include "src/core/util/sync.h"

namespace grpc_core {

// A thread-safe observable value that allows observers to wait for changes.
// Observers can register to be notified when the value changes to a state that
// meets certain conditions.
template <typename T>
class Observable {
 public:
  // Constructs an Observable with the given initial value.
  explicit Observable(T initial)
      : state_(MakeRefCounted<State>(std::move(initial))) {}

  // Updates the observable value and notifies all observers.
  void Set(T value) { state_->Set(std::move(value)); }

  // Returns a promise that completes when the value changes to one that satisfies
  // the given predicate.
  template <typename F>
  auto NextWhen(F is_acceptable) {
    return ObserverWhen<F>(state_, std::move(is_acceptable));
  }

  // Returns a promise that completes when the value changes from the given current value.
  auto Next(T current) {
    return NextWhen([current = std::move(current)](const T& value) {
      return value != current;
    });
  }

 private:
  // Forward declaration of Observer class
  class Observer;

  // Internal state shared between Observable and its observers.
  // Uses reference counting for lifetime management.
  class State : public RefCounted<State> {
   public:
    explicit State(T value) : value_(std::move(value)) {}

    // Updates the current value and wakes all registered observers.
    void Set(T value) {
      MutexLock lock(&mu_);
      std::swap(value_, value);
      WakeAll();
    }

    // Returns a pointer to the mutex protecting the state.
    Mutex* mu() ABSL_LOCK_RETURNED(mu_) { return &mu_; }

    // Returns the current value (must be called with mutex held).
    const T& current() const ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_) {
      return value_;
    }

    // Removes an observer from the notification set (must be called with mutex held).
    void Remove(Observer* observer) ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_) {
      observers_.erase(observer);
    }

    // Adds an observer to the notification set and returns a waker for it.
    // Must be called with mutex held.
    GRPC_MUST_USE_RESULT Waker Add(Observer* observer)
        ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_) {
      observers_.insert(observer);
      return GetContext<Activity>()->MakeNonOwningWaker();
    }

   private:
    // Wakes all registered observers (must be called with mutex held).
    void WakeAll() ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_) {
      for (auto* observer : observers_) {
        observer->Wakeup();
      }
    }

    Mutex mu_;  // Protects all state below
    absl::flat_hash_set<Observer*> observers_ ABSL_GUARDED_BY(mu_);  // Set of active observers
    T value_ ABSL_GUARDED_BY(mu_);  // Current observable value
  };

  // Base class for observers that wait for specific conditions on the observable value.
  class Observer {
   public:
    explicit Observer(RefCountedPtr<State> state) : state_(std::move(state)) {}

    virtual ~Observer() {
      // Clean up only if we've seen a pending state (i.e., we're registered as an observer)
      if (!saw_pending_) return;
      MutexLock lock(state_->mu());
      auto w = std::move(waker_);
      state_->Remove(this);
    }

    // Non-copyable
    Observer(const Observer&) = delete;
    Observer& operator=(const Observer&) = delete;
    
    // Movable, but with strict checks
    Observer(Observer&& other) noexcept : state_(std::move(other.state_)) {
      CHECK(other.waker_.is_unwakeable());
      DCHECK(waker_.is_unwakeable());
      CHECK(!other.saw_pending_);
    }
    Observer& operator=(Observer&& other) noexcept = delete;

    // Called by State to wake this observer
    void Wakeup() { waker_.WakeupAsync(); }

    // Pure virtual method to determine if the current value should trigger completion
    virtual bool ShouldReturn(const T& current) = 0;

    // Polls the observer state - returns the current value if ShouldReturn is true,
    // otherwise returns Pending and registers for wakeup.
    Poll<T> operator()() {
      MutexLock lock(state_->mu());

      if (ShouldReturn(state_->current())) {
        // If we're completing and were previously pending, clean up
        if (saw_pending_ && !waker_.is_unwakeable()) state_->Remove(this);
        return state_->current();
      }

      // Register for wakeup if we haven't already
      saw_pending_ = true;
      if (waker_.is_unwakeable()) waker_ = state_->Add(this);
      return Pending{};
    }

   private:
    RefCountedPtr<State> state_;  // Shared state with the Observable
    Waker waker_;                // Used to wake this observer
    bool saw_pending_ = false;   // True if we've registered for wakeup
  };

  // Observer implementation that uses a predicate function to determine completion.
  template <typename F>
  class ObserverWhen : public Observer {
   public:
    ObserverWhen(RefCountedPtr<State> state, F is_acceptable)
        : Observer(std::move(state)),
          is_acceptable_(std::move(is_acceptable)) {}

    ObserverWhen(ObserverWhen&& other) noexcept
        : Observer(std::move(other)),
          is_acceptable_(std::move(other.is_acceptable_)) {}

    // Returns true if the current value satisfies the predicate.
    bool ShouldReturn(const T& current) override {
      return is_acceptable_(current);
    }

   private:
    F is_acceptable_;  // Predicate function to determine completion
  };

  RefCountedPtr<State> state_;  // Shared state for this Observable
};

}  // namespace grpc_core

#endif  // GRPC_SRC_CORE_LIB_PROMISE_OBSERVABLE_H
```