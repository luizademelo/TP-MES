// Copyright 2024 gRPC authors.

#ifndef GRPC_SRC_CORE_CALL_CALL_ARENA_ALLOCATOR_H
#define GRPC_SRC_CORE_CALL_CALL_ARENA_ALLOCATOR_H

#include <grpc/support/port_platform.h>
#include <stddef.h>

#include <atomic>
#include <cstddef>

#include "src/core/lib/resource_quota/arena.h"
#include "src/core/lib/resource_quota/memory_quota.h"
#include "src/core/util/ref_counted.h"

namespace grpc_core {

class CallSizeEstimator final {
 public:
  explicit CallSizeEstimator(size_t initial_estimate)
      : call_size_estimate_(initial_estimate) {}

  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION size_t CallSizeEstimate() {

    static constexpr size_t kRoundUpSize = 256;
    return (call_size_estimate_.load(std::memory_order_relaxed) +
            2 * kRoundUpSize) &
           ~(kRoundUpSize - 1);
  }

  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION void UpdateCallSizeEstimate(
      size_t size) {
    size_t cur = call_size_estimate_.load(std::memory_order_relaxed);
    if (cur < size) {

      call_size_estimate_.compare_exchange_weak(
          cur, size, std::memory_order_relaxed, std::memory_order_relaxed);

    } else if (cur == size) {

    } else if (cur > 0) {

      call_size_estimate_.compare_exchange_weak(
          cur, std::min(cur - 1, (255 * cur + size) / 256),
          std::memory_order_relaxed, std::memory_order_relaxed);

    }
  }

 private:
  std::atomic<size_t> call_size_estimate_;
};

class CallArenaAllocator final : public ArenaFactory {
 public:
  CallArenaAllocator(MemoryAllocator allocator, size_t initial_size)
      : ArenaFactory(std::move(allocator)),
        call_size_estimator_(initial_size) {}

  RefCountedPtr<Arena> MakeArena() override {
    return Arena::Create(call_size_estimator_.CallSizeEstimate(), Ref());
  }

  void FinalizeArena(Arena* arena) override;

  size_t CallSizeEstimate() { return call_size_estimator_.CallSizeEstimate(); }

 private:
  CallSizeEstimator call_size_estimator_;
};

}

#endif
