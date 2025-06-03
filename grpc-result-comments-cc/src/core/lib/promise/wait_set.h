Here's the commented version of the code:

```c++
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

// A WaitSet is a collection of wakers (objects that can wake up activities)
// that provides functionality to manage and trigger them.
class WaitSet final {
  // Using a flat_hash_set for efficient insertion and removal of wakers
  using WakerSet = absl::flat_hash_set<Waker>;

 public:
  // Adds a waker to the pending set and returns a Pending token.
  // The waker will be moved into the set.
  Pending AddPending(Waker waker) {
    pending_.emplace(std::move(waker));
    return Pending();
  }

  // WakeupSet represents a set of wakers that can be triggered together.
  // This is used to batch wakeup operations.
  class WakeupSet {
   public:
    // Triggers all wakers in the set synchronously.
    // Wakers are removed from the set as they are triggered.
    void Wakeup() {
      while (!wakeup_.empty()) {
        wakeup_.extract(wakeup_.begin()).value().Wakeup();
      }
    }

   private:
    friend class WaitSet;
    // Private constructor only accessible by WaitSet
    explicit WakeupSet(WakerSet&& wakeup)
        : wakeup_(std::forward<WakerSet>(wakeup)) {}
    // The set of wakers to be triggered
    WakerSet wakeup_;
  };

  // Moves all pending wakers into a new WakeupSet and clears the pending set.
  // The returned WakeupSet must be used (GRPC_MUST_USE_RESULT enforces this).
  GRPC_MUST_USE_RESULT WakeupSet TakeWakeupSet() {
    auto ret = WakeupSet(std::move(pending_));
    pending_.clear();
    return ret;
  }

  // Triggers all pending wakers asynchronously.
  // Wakers are removed from the pending set as they are triggered.
  void WakeupAsync() {
    while (!pending_.empty()) {
      pending_.extract(pending_.begin()).value().WakeupAsync();
    }
  }

  // Returns a string representation of the WaitSet (for debugging purposes)
  std::string ToString();

 private:
  // The set of wakers waiting to be triggered
  WakerSet pending_;
};

}  // namespace grpc_core

#endif  // GRPC_SRC_CORE_LIB_PROMISE_WAIT_SET_H
```

Key aspects of the comments:
1. Added class-level documentation explaining the purpose of WaitSet
2. Documented each public method's purpose and behavior
3. Explained the WakeupSet nested class and its relationship with WaitSet
4. Added comments for private members
5. Clarified the movement semantics used in TakeWakeupSet
6. Noted the purpose of GRPC_MUST_USE_RESULT
7. Explained the difference between Wakeup and WakeupAsync
8. Added namespace and header guard comments

The comments maintain a consistent style and provide enough detail to understand the code's functionality without being overly verbose.