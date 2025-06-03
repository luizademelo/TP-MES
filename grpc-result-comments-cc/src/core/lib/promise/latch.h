Here's the commented version of the code:

```c++
// Copyright 2021 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_PROMISE_LATCH_H
#define GRPC_SRC_CORE_LIB_PROMISE_LATCH_H

#include <grpc/support/port_platform.h>
#include <stdint.h>

#include <atomic>
#include <string>
#include <utility>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/strings/str_cat.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/promise/activity.h"
#include "src/core/lib/promise/poll.h"

namespace grpc_core {

// A synchronization primitive that allows one thread to wait for a value to be
// set by another thread. Similar to std::latch but with promise integration.
template <typename T>
class Latch {
 public:
  // Default constructor creates an unset latch
  Latch() = default;
  // Disallow copy construction
  Latch(const Latch&) = delete;
  // Constructor that initializes with a value (latch starts as set)
  explicit Latch(T value) : value_(std::move(value)), has_value_(true) {}
  // Disallow copy assignment
  Latch& operator=(const Latch&) = delete;
  // Move constructor
  Latch(Latch&& other) noexcept
      : value_(std::move(other.value_)), has_value_(other.has_value_) {
#ifndef NDEBUG
    DCHECK(!other.has_had_waiters_);
#endif
  }
  // Move assignment operator
  Latch& operator=(Latch&& other) noexcept {
#ifndef NDEBUG
    DCHECK(!other.has_had_waiters_);
#endif
    value_ = std::move(other.value_);
    has_value_ = other.has_value_;
    return *this;
  }

  // Returns a promise that will wait for the latch to be set and return the value
  auto Wait() {
#ifndef NDEBUG
    has_had_waiters_ = true;
#endif
    return [this]() -> Poll<T> {
      GRPC_TRACE_LOG(promise_primitives, INFO)
          << DebugTag() << "Wait " << StateString();
      if (has_value_) {
        return std::move(value_);
      } else {
        return waiter_.pending();
      }
    };
  }

  // Returns a promise that will wait for the latch to be set and return a copy of the value
  auto WaitAndCopy() {
#ifndef NDEBUG
    has_had_waiters_ = true;
#endif
    return [this]() -> Poll<T> {
      GRPC_TRACE_LOG(promise_primitives, INFO)
          << DebugTag() << "WaitAndCopy " << StateString();
      if (has_value_) {
        return value_;
      } else {
        return waiter_.pending();
      }
    };
  }

  // Sets the value and wakes any waiting promises
  void Set(T value) {
    GRPC_TRACE_LOG(promise_primitives, INFO)
        << DebugTag() << "Set " << StateString();
    DCHECK(!has_value_);
    value_ = std::move(value);
    has_value_ = true;
    waiter_.Wake();
  }

  // Returns true if the latch has been set
  bool is_set() const { return has_value_; }

 private:
  // Creates a debug tag string for tracing
  std::string DebugTag() {
    return absl::StrCat(GetContext<Activity>()->DebugTag(), " LATCH[0x",
                        reinterpret_cast<uintptr_t>(this), "]: ");
  }

  // Creates a string describing the current state
  std::string StateString() {
    return absl::StrCat("has_value:", has_value_ ? "true" : "false",
                        " waiter:", waiter_.DebugString());
  }

  GPR_NO_UNIQUE_ADDRESS T value_;  // The stored value

  bool has_value_ = false;  // Whether the value has been set
#ifndef NDEBUG
  bool has_had_waiters_ = false;  // Debug flag to track if waiters existed
#endif
  IntraActivityWaiter waiter_;  // Mechanism for waiting/signaling
};

// Specialization of Latch for void type (just signals completion without a value)
template <>
class Latch<void> {
 public:
  Latch() = default;
  Latch(const Latch&) = delete;
  Latch& operator=(const Latch&) = delete;
  Latch(Latch&& other) noexcept : is_set_(other.is_set_) {
#ifndef NDEBUG
    DCHECK(!other.has_had_waiters_);
#endif
  }
  Latch& operator=(Latch&& other) noexcept {
#ifndef NDEBUG
    DCHECK(!other.has_had_waiters_);
#endif
    is_set_ = other.is_set_;
    return *this;
  }

  // Returns a promise that will wait for the latch to be set
  auto Wait() {
#ifndef NDEBUG
    has_had_waiters_ = true;
#endif
    return [this]() -> Poll<Empty> {
      GRPC_TRACE_LOG(promise_primitives, INFO)
          << DebugTag() << "PollWait " << StateString();
      if (is_set_) {
        return Empty{};
      } else {
        return waiter_.pending();
      }
    };
  }

  // Sets the latch and wakes any waiting promises
  void Set() {
    GRPC_TRACE_LOG(promise_primitives, INFO)
        << DebugTag() << "Set " << StateString();
    DCHECK(!is_set_);
    is_set_ = true;
    waiter_.Wake();
  }

  // Returns true if the latch has been set
  bool is_set() const { return is_set_; }

 private:
  // Creates a debug tag string for tracing
  std::string DebugTag() {
    return absl::StrCat(GetContext<Activity>()->DebugTag(), " LATCH(void)[0x",
                        reinterpret_cast<uintptr_t>(this), "]: ");
  }

  // Creates a string describing the current state
  std::string StateString() {
    return absl::StrCat("is_set:", is_set_ ? "true" : "false",
                        " waiter:", waiter_.DebugString());
  }

  bool is_set_ = false;  // Whether the latch has been set
#ifndef NDEBUG
  bool has_had_waiters_ = false;  // Debug flag to track if waiters existed
#endif
  IntraActivityWaiter waiter_;  // Mechanism for waiting/signaling
};

// Helper type for the promise returned by Latch::Wait
template <typename T>
using LatchWaitPromise = decltype(std::declval<Latch<T>>().Wait());

// A version of Latch<void> that can be observed externally and reset
template <typename T>
class ExternallyObservableLatch;

// Specialization for void type
template <>
class ExternallyObservableLatch<void> {
 public:
  ExternallyObservableLatch() = default;
  ExternallyObservableLatch(const ExternallyObservableLatch&) = delete;
  ExternallyObservableLatch& operator=(const ExternallyObservableLatch&) =
      delete;

  // Returns a promise that will wait for the latch to be set
  auto Wait() {
    return [this]() -> Poll<Empty> {
      GRPC_TRACE_LOG(promise_primitives, INFO)
          << DebugTag() << "PollWait " << StateString();
      if (IsSet()) {
        return Empty{};
      } else {
        return waiter_.pending();
      }
    };
  }

  // Sets the latch and wakes any waiting promises
  void Set() {
    GRPC_TRACE_LOG(promise_primitives, INFO)
        << DebugTag() << "Set " << StateString();
    is_set_.store(true, std::memory_order_relaxed);
    waiter_.Wake();
  }

  // Returns true if the latch has been set
  bool IsSet() const { return is_set_.load(std::memory_order_relaxed); }

  // Resets the latch to unset state
  void Reset() {
    GRPC_TRACE_LOG(promise_primitives, INFO)
        << DebugTag() << "Reset " << StateString();
    is_set_.store(false, std::memory_order_relaxed);
  }

 private:
  // Creates a debug tag string for tracing
  std::string DebugTag() {
    return absl::StrCat(GetContext<Activity>()->DebugTag(), " LATCH(void)[0x",
                        reinterpret_cast<uintptr_t>(this), "]: ");
  }

  // Creates a string describing the current state
  std::string StateString() {
    return absl::StrCat(
        "is_set:", is_set_.load(std::memory_order_relaxed) ? "true" : "false",
        " waiter:", waiter_.DebugString());
  }

  std::atomic<bool> is_set_{false};  // Atomic flag for thread-safe operations
  IntraActivityWaiter waiter_;       // Mechanism for waiting/signaling
};

}  // namespace grpc_core

#endif  // GRPC_SRC_CORE_LIB_PROMISE_LATCH_H
```