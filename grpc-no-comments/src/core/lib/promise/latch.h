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

template <typename T>
class Latch {
 public:
  Latch() = default;
  Latch(const Latch&) = delete;
  explicit Latch(T value) : value_(std::move(value)), has_value_(true) {}
  Latch& operator=(const Latch&) = delete;
  Latch(Latch&& other) noexcept
      : value_(std::move(other.value_)), has_value_(other.has_value_) {
#ifndef NDEBUG
    DCHECK(!other.has_had_waiters_);
#endif
  }
  Latch& operator=(Latch&& other) noexcept {
#ifndef NDEBUG
    DCHECK(!other.has_had_waiters_);
#endif
    value_ = std::move(other.value_);
    has_value_ = other.has_value_;
    return *this;
  }

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

  void Set(T value) {
    GRPC_TRACE_LOG(promise_primitives, INFO)
        << DebugTag() << "Set " << StateString();
    DCHECK(!has_value_);
    value_ = std::move(value);
    has_value_ = true;
    waiter_.Wake();
  }

  bool is_set() const { return has_value_; }

 private:
  std::string DebugTag() {
    return absl::StrCat(GetContext<Activity>()->DebugTag(), " LATCH[0x",
                        reinterpret_cast<uintptr_t>(this), "]: ");
  }

  std::string StateString() {
    return absl::StrCat("has_value:", has_value_ ? "true" : "false",
                        " waiter:", waiter_.DebugString());
  }

  GPR_NO_UNIQUE_ADDRESS T value_;

  bool has_value_ = false;
#ifndef NDEBUG

  bool has_had_waiters_ = false;
#endif
  IntraActivityWaiter waiter_;
};

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

  void Set() {
    GRPC_TRACE_LOG(promise_primitives, INFO)
        << DebugTag() << "Set " << StateString();
    DCHECK(!is_set_);
    is_set_ = true;
    waiter_.Wake();
  }

  bool is_set() const { return is_set_; }

 private:
  std::string DebugTag() {
    return absl::StrCat(GetContext<Activity>()->DebugTag(), " LATCH(void)[0x",
                        reinterpret_cast<uintptr_t>(this), "]: ");
  }

  std::string StateString() {
    return absl::StrCat("is_set:", is_set_ ? "true" : "false",
                        " waiter:", waiter_.DebugString());
  }

  bool is_set_ = false;
#ifndef NDEBUG

  bool has_had_waiters_ = false;
#endif
  IntraActivityWaiter waiter_;
};

template <typename T>
using LatchWaitPromise = decltype(std::declval<Latch<T>>().Wait());

template <typename T>
class ExternallyObservableLatch;

template <>
class ExternallyObservableLatch<void> {
 public:
  ExternallyObservableLatch() = default;
  ExternallyObservableLatch(const ExternallyObservableLatch&) = delete;
  ExternallyObservableLatch& operator=(const ExternallyObservableLatch&) =
      delete;

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

  void Set() {
    GRPC_TRACE_LOG(promise_primitives, INFO)
        << DebugTag() << "Set " << StateString();
    is_set_.store(true, std::memory_order_relaxed);
    waiter_.Wake();
  }

  bool IsSet() const { return is_set_.load(std::memory_order_relaxed); }

  void Reset() {
    GRPC_TRACE_LOG(promise_primitives, INFO)
        << DebugTag() << "Reset " << StateString();
    is_set_.store(false, std::memory_order_relaxed);
  }

 private:
  std::string DebugTag() {
    return absl::StrCat(GetContext<Activity>()->DebugTag(), " LATCH(void)[0x",
                        reinterpret_cast<uintptr_t>(this), "]: ");
  }

  std::string StateString() {
    return absl::StrCat(
        "is_set:", is_set_.load(std::memory_order_relaxed) ? "true" : "false",
        " waiter:", waiter_.DebugString());
  }

  std::atomic<bool> is_set_{false};
  IntraActivityWaiter waiter_;
};

}

#endif
