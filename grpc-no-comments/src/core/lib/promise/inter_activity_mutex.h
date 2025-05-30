// Copyright 2025 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_PROMISE_INTER_ACTIVITY_MUTEX_H
#define GRPC_SRC_CORE_LIB_PROMISE_INTER_ACTIVITY_MUTEX_H

#include <atomic>
#include <utility>

#include "absl/log/log.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/promise/activity.h"
#include "src/core/lib/promise/poll.h"
#include "src/core/util/dump_args.h"

namespace grpc_core {

template <typename T>
class InterActivityMutex {
 public:
  class Lock {
   public:
    Lock(const Lock&) = delete;
    Lock& operator=(const Lock&) = delete;
    Lock(Lock&& other) noexcept
        : mutex_(std::exchange(other.mutex_, nullptr)) {}
    Lock& operator=(Lock&& other) noexcept {
      if (mutex_ != nullptr) mutex_->Unlock();
      mutex_ = std::exchange(other.mutex_, nullptr);
      return *this;
    }
    ~Lock() {
      if (mutex_ != nullptr) mutex_->Unlock();
    }

    T& operator*() { return mutex_->value_; }
    T* operator->() { return &mutex_->value_; }
    const T& operator*() const { return mutex_->value_; }
    const T* operator->() const { return &mutex_->value_; }

    template <typename Sink>
    friend void AbslStringify(Sink& sink, const Lock& lock) {
      if (lock.mutex_ == nullptr) {
        sink.Append("<unlocked>");
      } else {
        absl::Format(&sink, "%v", lock.mutex_->value_);
      }
    }

   private:
    friend class InterActivityMutex;
    explicit Lock(InterActivityMutex* mutex) : mutex_(mutex) {
      GRPC_TRACE_LOG(promise_primitives, INFO)
          << "[mutex " << mutex_ << "] Lock acquired";
    }
    InterActivityMutex* mutex_;
  };

  InterActivityMutex() = default;
  ~InterActivityMutex() {

    while (waiters_ != nullptr) {
      Waiter* next = waiters_->next_;

      waiters_->RemovedFromQueue();
      waiters_ = next;
    }
  }
  explicit InterActivityMutex(T value) : value_(std::move(value)) {}

 private:
  template <typename F>
  class Acquirer;
  class Unlocker;

  class Waiter {
   public:
    explicit Waiter(InterActivityMutex* mutex, Waiter* next = nullptr)
        : mutex_(mutex), next_(next) {}

    bool WasAcquisitionCancelled() {
      return state_.load(std::memory_order_relaxed) ==
             State::kAcquisitionCancelled;
    }

    virtual bool CanAcquire() = 0;

    void FailedAddToQueue() {
      DCHECK_EQ(state_, State::kWaiting);
      delete this;
    }

    void RemovedFromQueue() {
      DCHECK_EQ(state_, State::kAcquisitionCancelled);
      delete this;
    }

    void AcquisitionCancelled() {
      State prev_state = State::kWaiting;
      while (true) {
        GRPC_TRACE_LOG(promise_primitives, INFO)
            << "[mutex " << mutex_ << " waiter " << this
            << "] AcquisitionCancelled: " << GRPC_DUMP_ARGS(prev_state);
        switch (prev_state) {
          case State::kWaiting:
            if (state_.compare_exchange_weak(
                    prev_state, State::kAcquisitionCancelled,
                    std::memory_order_relaxed, std::memory_order_relaxed)) {
              return;
            }
            break;
          case State::kAcquisitionCancelled:
            LOG(DFATAL) << "unreachable";
            return;
          case State::kAcquired:
            mutex_->Unlock();
            delete this;
            return;
        }
      }
    }

    bool CheckAcquired() {
      bool acquired =
          state_.load(std::memory_order_acquire) == State::kAcquired;
      if (acquired) delete this;
      return acquired;
    }

    void BecomeAcquired() {
      State prev_state = State::kWaiting;
      while (true) {
        switch (prev_state) {
          case State::kWaiting:
            if (state_.compare_exchange_weak(prev_state, State::kAcquired,
                                             std::memory_order_release,
                                             std::memory_order_relaxed)) {
              waker_.Wakeup();
              return;
            }
            break;
          case State::kAcquisitionCancelled:
            mutex_->Unlock();
            delete this;
            return;
          case State::kAcquired:
            LOG(DFATAL) << "unreachable";
            return;
        }
      }
    }

    Waiter* Reverse() {

      std::vector<Waiter*> waiters;
      for (Waiter* waiter = this; waiter != nullptr; waiter = waiter->next_) {
        waiters.push_back(waiter);
      }
      waiters[0]->next_ = nullptr;
      for (size_t i = 1; i < waiters.size(); ++i) {
        waiters[i]->next_ = waiters[i - 1];
      }
      return waiters[waiters.size() - 1];
    }

   protected:
    const T& value() const { return mutex_->value_; }

    virtual ~Waiter() = default;

   private:
    template <typename F>
    friend class Acquirer;
    friend class Unlocker;
    friend class InterActivityMutex;

    enum State {

      kWaiting,

      kAcquisitionCancelled,

      kAcquired,
    };

    template <typename Sink>
    friend void AbslStringify(Sink& sink, State state) {
      switch (state) {
        case State::kWaiting:
          sink.Append("Waiting");
          break;
        case State::kAcquisitionCancelled:
          sink.Append("AcquisitionCancelled");
          break;
        case State::kAcquired:
          sink.Append("Acquired");
          break;
      }
    }

    std::atomic<State> state_{State::kWaiting};
    InterActivityMutex* const mutex_;
    Waiter* next_;
    Waker waker_ = GetContext<Activity>()->MakeNonOwningWaker();
  };

  template <class F>
  class WaiterImpl : public Waiter {
   public:
    WaiterImpl(InterActivityMutex* mutex, Waiter* next, F f)
        : Waiter(mutex, next), f_(std::move(f)) {}
    bool CanAcquire() override { return f_(this->value()); }

   private:
    GPR_NO_UNIQUE_ADDRESS F f_;
  };

  template <class F>
  class Acquirer {
   public:
    explicit Acquirer(InterActivityMutex* mutex, F f)
        : mutex_(mutex), f_(std::move(f)) {}
    ~Acquirer() {

      switch (state_) {
        case State::kStart:
          break;
        case State::kFastLocked:
          mutex_->Unlock();
          break;
        case State::kMovedFrom:
          break;
        case State::kWaiting:
          waiter_->AcquisitionCancelled();
          break;
      }
    }
    Acquirer(const Acquirer&) = delete;
    Acquirer& operator=(const Acquirer&) = delete;
    Acquirer(Acquirer&& other) noexcept
        : mutex_(other.mutex_),
          prev_state_(other.prev_state_),
          state_(std::exchange(other.state_, State::kMovedFrom)),
          f_(std::move(other.f_)),
          waiter_(other.waiter_) {}
    Acquirer& operator=(Acquirer&& other) noexcept = delete;
    Poll<Lock> operator()() {
      GRPC_TRACE_LOG(promise_primitives, INFO)
          << "[mutex " << mutex_ << " aquirerer " << this
          << "] Poll: " << GRPC_DUMP_ARGS(state_);
      switch (state_) {
        case State::kStart:
          return PollStart();
        case State::kFastLocked:
          return PollFastLocked();
        case State::kWaiting:
          return PollWaiting();
        case State::kMovedFrom:
          LOG(FATAL) << "Mutex acquirer already moved from";
      }
    }

   private:
    enum class State : uint8_t {

      kStart,

      kFastLocked,

      kWaiting,

      kMovedFrom
    };

    template <typename Sink>
    friend void AbslStringify(Sink& sink, State state) {
      switch (state) {
        case State::kStart:
          sink.Append("Start");
          break;
        case State::kFastLocked:
          sink.Append("FastLocked");
          break;
        case State::kWaiting:
          sink.Append("Waiting");
          break;
        case State::kMovedFrom:
          sink.Append("MovedFrom");
          break;
      }
    }

    Poll<Lock> PollStart() {
      while (true) {
        GRPC_TRACE_LOG(promise_primitives, INFO)
            << "[mutex " << mutex_ << " aquirerer " << this
            << "] PollStart: " << GRPC_DUMP_ARGS(prev_state_);
        if (prev_state_ == kUnlocked) {

          if (mutex_->state_.compare_exchange_weak(prev_state_, kLocked,
                                                   std::memory_order_acquire,
                                                   std::memory_order_relaxed)) {
            return PollFastLocked();
          }
        } else if (prev_state_ == kLocked) {

          waiter_ = new WaiterImpl<F>(mutex_, nullptr, std::move(f_));
          state_ = State::kWaiting;
          if (mutex_->state_.compare_exchange_weak(
                  prev_state_, reinterpret_cast<uintptr_t>(waiter_),
                  std::memory_order_release, std::memory_order_relaxed)) {
            return Pending{};
          }
          state_ = State::kStart;
          waiter_->FailedAddToQueue();
        } else {

          waiter_ = new WaiterImpl<F>(
              mutex_, reinterpret_cast<Waiter*>(prev_state_), std::move(f_));
          state_ = State::kWaiting;
          if (mutex_->state_.compare_exchange_weak(
                  prev_state_, reinterpret_cast<uintptr_t>(waiter_),
                  std::memory_order_release, std::memory_order_relaxed)) {
            return Pending{};
          }
          state_ = State::kStart;
          waiter_->FailedAddToQueue();
        }
      }
    }

    Poll<Lock> PollFastLocked() {

      if (f_(mutex_->value_)) {
        state_ = State::kMovedFrom;
        return Lock(mutex_);
      }
      GRPC_TRACE_LOG(promise_primitives, INFO)
          << "[mutex " << mutex_ << " acquirer " << this
          << "]: PollFastLocked but not ready: insert waiter @ tail";
      waiter_ = new WaiterImpl<F>(mutex_, nullptr, std::move(f_));
      if (mutex_->waiters_ == nullptr) {
        mutex_->waiters_ = waiter_;
      } else {
        Waiter* w = mutex_->waiters_;
        while (w->next_ != nullptr) w = w->next_;
        w->next_ = waiter_;
      }
      state_ = State::kWaiting;
      if (mutex_->state_.compare_exchange_strong(prev_state_, kUnlocked,
                                                 std::memory_order_release,
                                                 std::memory_order_release)) {
        return Pending{};
      }
      DCHECK_NE(prev_state_, kUnlocked);

      mutex_->Unlock();
      return Pending{};
    }

    Poll<Lock> PollWaiting() {
      if (waiter_->CheckAcquired()) {
        state_ = State::kMovedFrom;
        return Lock(mutex_);
      }
      return Pending{};
    }

    InterActivityMutex* mutex_;
    uintptr_t prev_state_ = kUnlocked;
    State state_ = mutex_->state_.compare_exchange_weak(prev_state_, kLocked)
                       ? State::kFastLocked
                       : State::kStart;
    GPR_NO_UNIQUE_ADDRESS F f_;
    Waiter* waiter_;
  };

 public:
  auto Acquire() {
    return AcquireWhen([](const T&) { return true; });
  }
  template <typename F>
  auto AcquireWhen(F f) {
    return Acquirer<F>(this, std::move(f));
  }

 private:
  static constexpr uintptr_t kUnlocked = 0;
  static constexpr uintptr_t kLocked = 1;

  class Unlocker {
   public:
    explicit Unlocker(InterActivityMutex* mutex) : mutex_(mutex) {}

    void Run() {
      while (DrainSeenWaiters() && MaybeRefillWaiters()) {
      }
    }

   private:
    bool DrainSeenWaiters() {

      while (waiter_ != nullptr) {
        GRPC_TRACE_LOG(promise_primitives, INFO)
            << "[mutex " << mutex_
            << "] DrainSeenWaiters: " << GRPC_DUMP_ARGS(prev_waiter_, waiter_);
        if (waiter_->WasAcquisitionCancelled()) {
          GRPC_TRACE_LOG(promise_primitives, INFO)
              << "[mutex " << mutex_
              << "] DrainSeenWaiters acquisition cancelled: "
              << GRPC_DUMP_ARGS(prev_waiter_, waiter_);
          Waiter* next = waiter_->next_;
          DCHECK_NE(next, waiter_);
          if (prev_waiter_ == nullptr) {
            DCHECK_EQ(mutex_->waiters_, waiter_);
            mutex_->waiters_ = next;
          } else {
            DCHECK_EQ(prev_waiter_->next_, waiter_);
            prev_waiter_->next_ = next;
          }
          waiter_->RemovedFromQueue();
          waiter_ = next;
          continue;
        }
        if (waiter_->CanAcquire()) {
          GRPC_TRACE_LOG(promise_primitives, INFO)
              << "[mutex " << mutex_
              << "] DrainSeenWaiters acquisition successful: "
              << GRPC_DUMP_ARGS(prev_waiter_, waiter_);
          if (prev_waiter_ == nullptr) {
            mutex_->waiters_ = waiter_->next_;
          } else {
            prev_waiter_->next_ = waiter_->next_;
          }
          waiter_->BecomeAcquired();
          return false;
        }
        prev_waiter_ = waiter_;
        waiter_ = waiter_->next_;
      }
      return true;
    }

    bool MaybeRefillWaiters() {

      auto prev_state = mutex_->state_.load(std::memory_order_relaxed);
      while (true) {
        GRPC_TRACE_LOG(promise_primitives, INFO)
            << "[mutex " << mutex_
            << "] MaybeRefillWaiters: " << GRPC_DUMP_ARGS(prev_state);
        DCHECK_NE(prev_state, kUnlocked);
        if (prev_state == kLocked) {
          if (mutex_->state_.compare_exchange_weak(prev_state, kUnlocked,
                                                   std::memory_order_release,
                                                   std::memory_order_relaxed)) {
            return false;
          }
        } else {
          if (mutex_->state_.compare_exchange_weak(prev_state, kLocked,
                                                   std::memory_order_acquire,
                                                   std::memory_order_release)) {
            Waiter* next = reinterpret_cast<Waiter*>(prev_state);
            if (prev_waiter_ == nullptr) {
              mutex_->waiters_ = next->Reverse();
              waiter_ = mutex_->waiters_;
            } else {
              DCHECK_EQ(prev_waiter_->next_, nullptr);
              prev_waiter_->next_ = next->Reverse();
              waiter_ = prev_waiter_->next_;
            }
            return true;
          }
        }
      }
    }

    InterActivityMutex* const mutex_;
    Waiter* prev_waiter_ = nullptr;
    Waiter* waiter_ = mutex_->waiters_;
  };

  void Unlock() {
    GRPC_TRACE_LOG(promise_primitives, INFO)
        << "[mutex " << this << "] Unlocking";
    Unlocker(this).Run();
  }

  std::atomic<uintptr_t> state_{kUnlocked};
  Waiter* waiters_ = nullptr;
  T value_;
};

}

#endif
