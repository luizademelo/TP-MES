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

template <typename T>
class Observable {
 public:

  explicit Observable(T initial)
      : state_(MakeRefCounted<State>(std::move(initial))) {}

  void Set(T value) { state_->Set(std::move(value)); }

  template <typename F>
  auto NextWhen(F is_acceptable) {
    return ObserverWhen<F>(state_, std::move(is_acceptable));
  }

  auto Next(T current) {
    return NextWhen([current = std::move(current)](const T& value) {
      return value != current;
    });
  }

 private:

  class Observer;

  class State : public RefCounted<State> {
   public:
    explicit State(T value) : value_(std::move(value)) {}

    void Set(T value) {
      MutexLock lock(&mu_);
      std::swap(value_, value);
      WakeAll();
    }

    Mutex* mu() ABSL_LOCK_RETURNED(mu_) { return &mu_; }

    const T& current() const ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_) {
      return value_;
    }

    void Remove(Observer* observer) ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_) {
      observers_.erase(observer);
    }

    GRPC_MUST_USE_RESULT Waker Add(Observer* observer)
        ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_) {
      observers_.insert(observer);
      return GetContext<Activity>()->MakeNonOwningWaker();
    }

   private:

    void WakeAll() ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_) {
      for (auto* observer : observers_) {
        observer->Wakeup();
      }
    }

    Mutex mu_;

    absl::flat_hash_set<Observer*> observers_ ABSL_GUARDED_BY(mu_);

    T value_ ABSL_GUARDED_BY(mu_);
  };

  class Observer {
   public:
    explicit Observer(RefCountedPtr<State> state) : state_(std::move(state)) {}

    virtual ~Observer() {

      if (!saw_pending_) return;
      MutexLock lock(state_->mu());
      auto w = std::move(waker_);
      state_->Remove(this);
    }

    Observer(const Observer&) = delete;
    Observer& operator=(const Observer&) = delete;
    Observer(Observer&& other) noexcept : state_(std::move(other.state_)) {
      CHECK(other.waker_.is_unwakeable());
      DCHECK(waker_.is_unwakeable());
      CHECK(!other.saw_pending_);
    }
    Observer& operator=(Observer&& other) noexcept = delete;

    void Wakeup() { waker_.WakeupAsync(); }

    virtual bool ShouldReturn(const T& current) = 0;

    Poll<T> operator()() {
      MutexLock lock(state_->mu());

      if (ShouldReturn(state_->current())) {
        if (saw_pending_ && !waker_.is_unwakeable()) state_->Remove(this);
        return state_->current();
      }

      saw_pending_ = true;
      if (waker_.is_unwakeable()) waker_ = state_->Add(this);
      return Pending{};
    }

   private:
    RefCountedPtr<State> state_;
    Waker waker_;
    bool saw_pending_ = false;
  };

  template <typename F>
  class ObserverWhen : public Observer {
   public:
    ObserverWhen(RefCountedPtr<State> state, F is_acceptable)
        : Observer(std::move(state)),
          is_acceptable_(std::move(is_acceptable)) {}

    ObserverWhen(ObserverWhen&& other) noexcept
        : Observer(std::move(other)),
          is_acceptable_(std::move(other.is_acceptable_)) {}

    bool ShouldReturn(const T& current) override {
      return is_acceptable_(current);
    }

   private:
    F is_acceptable_;
  };

  RefCountedPtr<State> state_;
};

}

#endif
