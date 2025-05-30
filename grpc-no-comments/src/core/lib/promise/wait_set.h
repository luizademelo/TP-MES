// Copyright 2021 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_PROMISE_WAIT_SET_H
#define GRPC_SRC_CORE_LIB_PROMISE_WAIT_SET_H

#include <grpc/support/port_platform.h>

#include <utility>

#include "absl/container/flat_hash_set.h"
#include "absl/hash/hash.h"
#include "src/core/lib/promise/activity.h"
#include "src/core/lib/promise/poll.h"

namespace grpc_core {

class WaitSet final {
  using WakerSet = absl::flat_hash_set<Waker>;

 public:

  Pending AddPending(Waker waker) {
    pending_.emplace(std::move(waker));
    return Pending();
  }

  class WakeupSet {
   public:
    void Wakeup() {
      while (!wakeup_.empty()) {
        wakeup_.extract(wakeup_.begin()).value().Wakeup();
      }
    }

   private:
    friend class WaitSet;
    explicit WakeupSet(WakerSet&& wakeup)
        : wakeup_(std::forward<WakerSet>(wakeup)) {}
    WakerSet wakeup_;
  };

  GRPC_MUST_USE_RESULT WakeupSet TakeWakeupSet() {
    auto ret = WakeupSet(std::move(pending_));
    pending_.clear();
    return ret;
  }

  void WakeupAsync() {
    while (!pending_.empty()) {
      pending_.extract(pending_.begin()).value().WakeupAsync();
    }
  }

  std::string ToString();

 private:

  WakerSet pending_;
};

}

#endif
