// Copyright 2024 The gRPC Authors

#ifndef GRPC_SRC_CORE_UTIL_WAIT_FOR_SINGLE_OWNER_H
#define GRPC_SRC_CORE_UTIL_WAIT_FOR_SINGLE_OWNER_H

#include <memory>

#include "absl/log/log.h"
#include "src/core/util/crash.h"
#include "src/core/util/time.h"

namespace grpc_core {

template <typename T>
void WaitForSingleOwner(std::shared_ptr<T> obj) {
  WaitForSingleOwnerWithTimeout(std::move(obj), Duration::Hours(24));
}

template <typename T>
void WaitForSingleOwnerWithTimeout(std::shared_ptr<T> obj, Duration timeout) {
  auto start = Timestamp::Now();
  while (obj.use_count() > 1) {
    auto elapsed = Timestamp::Now() - start;
    auto remaining = timeout - elapsed;
    if (remaining < Duration::Zero()) {
      Crash("Timed out waiting for a single shared_ptr owner");
    }

    if (elapsed >= Duration::Seconds(2)) {
      LOG_EVERY_N_SEC(INFO, 2)
          << "obj.use_count() = " << obj.use_count() << " timeout_remaining = "
          << absl::FormatDuration(absl::Milliseconds(remaining.millis()));
    }
    absl::SleepFor(absl::Milliseconds(100));
  }
}

}

#endif
