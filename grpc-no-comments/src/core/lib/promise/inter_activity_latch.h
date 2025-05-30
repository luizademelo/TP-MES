// Copyright 2021 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_PROMISE_INTER_ACTIVITY_LATCH_H
#define GRPC_SRC_CORE_LIB_PROMISE_INTER_ACTIVITY_LATCH_H

#include <grpc/support/port_platform.h>
#include <stdint.h>

#include <string>

#include "absl/base/thread_annotations.h"
#include "absl/log/log.h"
#include "absl/strings/str_cat.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/promise/activity.h"
#include "src/core/lib/promise/poll.h"
#include "src/core/lib/promise/wait_set.h"
#include "src/core/util/sync.h"

namespace grpc_core {

template <typename T>
class InterActivityLatch {
 public:
  InterActivityLatch() = default;
  InterActivityLatch(const InterActivityLatch&) = delete;
  InterActivityLatch& operator=(const InterActivityLatch&) = delete;

  auto Wait() {
    return [this]() -> Poll<T> {
      MutexLock lock(&mu_);
      GRPC_TRACE_LOG(promise_primitives, INFO)
          << DebugTag() << "PollWait " << StateString();
      if (is_set_) {
        return std::move(value_);
      } else {
        return waiters_.AddPending(
            GetContext<Activity>()->MakeNonOwningWaker());
      }
    };
  }

  void Set(T value) {
    MutexLock lock(&mu_);
    GRPC_TRACE_LOG(promise_primitives, INFO)
        << DebugTag() << "Set " << StateString();
    is_set_ = true;
    value_ = std::move(value);
    waiters_.WakeupAsync();
  }

  bool IsSet() const ABSL_LOCKS_EXCLUDED(mu_) {
    MutexLock lock(&mu_);
    return is_set_;
  }

 private:
  std::string DebugTag() {
    return absl::StrCat(
        HasContext<Activity>() ? GetContext<Activity>()->DebugTag()
                               : "NO_ACTIVITY:",
        " INTER_ACTIVITY_LATCH[0x", reinterpret_cast<uintptr_t>(this), "]: ");
  }

  std::string StateString() ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_) {
    return absl::StrCat("is_set:", is_set_);
  }

  mutable Mutex mu_;

  bool is_set_ ABSL_GUARDED_BY(mu_) = false;
  WaitSet waiters_ ABSL_GUARDED_BY(mu_);
  T value_ ABSL_GUARDED_BY(mu_);
};

template <>
class InterActivityLatch<void> {
 public:
  InterActivityLatch() = default;
  InterActivityLatch(const InterActivityLatch&) = delete;
  InterActivityLatch& operator=(const InterActivityLatch&) = delete;

  auto Wait() {
    return [this]() -> Poll<Empty> {
      MutexLock lock(&mu_);
      GRPC_TRACE_LOG(promise_primitives, INFO)
          << DebugTag() << "PollWait " << StateString();
      if (is_set_) {
        return Empty{};
      } else {
        return waiters_.AddPending(
            GetContext<Activity>()->MakeNonOwningWaker());
      }
    };
  }

  void Set() {
    MutexLock lock(&mu_);
    GRPC_TRACE_LOG(promise_primitives, INFO)
        << DebugTag() << "Set " << StateString();
    is_set_ = true;
    waiters_.WakeupAsync();
  }

  bool IsSet() const ABSL_LOCKS_EXCLUDED(mu_) {
    MutexLock lock(&mu_);
    return is_set_;
  }

 private:
  std::string DebugTag() {
    return absl::StrCat(
        HasContext<Activity>() ? GetContext<Activity>()->DebugTag()
                               : "NO_ACTIVITY:",
        " INTER_ACTIVITY_LATCH[0x", reinterpret_cast<uintptr_t>(this), "]: ");
  }

  std::string StateString() ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_) {
    return absl::StrCat("is_set:", is_set_, " waiters:", waiters_.ToString());
  }

  mutable Mutex mu_;

  bool is_set_ ABSL_GUARDED_BY(mu_) = false;
  WaitSet waiters_ ABSL_GUARDED_BY(mu_);
};

}

#endif
