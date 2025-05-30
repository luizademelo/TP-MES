// Copyright 2022 The gRPC Authors

#ifndef GRPC_SRC_CORE_UTIL_NOTIFICATION_H
#define GRPC_SRC_CORE_UTIL_NOTIFICATION_H

#include <grpc/support/port_platform.h>

#include "absl/time/clock.h"
#include "absl/time/time.h"
#include "src/core/util/sync.h"

namespace grpc_core {

class Notification {
 public:
  void Notify() {
    MutexLock lock(&mu_);
    notified_ = true;
    cv_.SignalAll();
  }

  void WaitForNotification() {
    MutexLock lock(&mu_);
    while (!notified_) {
      cv_.Wait(&mu_);
    }
  }

  bool WaitForNotificationWithTimeout(absl::Duration timeout) {
    auto now = absl::Now();
    auto deadline = now + timeout;
    MutexLock lock(&mu_);
    while (!notified_ && now < deadline) {
      cv_.WaitWithTimeout(&mu_, deadline - now);
      now = absl::Now();
    }
    return notified_;
  }

  bool HasBeenNotified() {
    MutexLock lock(&mu_);
    return notified_;
  }

 private:
  Mutex mu_;
  CondVar cv_;
  bool notified_ = false;
};

}

#endif
