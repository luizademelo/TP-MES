// Copyright 2021 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_SLICE_SLICE_REFCOUNT_H
#define GRPC_SRC_CORE_LIB_SLICE_SLICE_REFCOUNT_H

#include <grpc/support/port_platform.h>
#include <inttypes.h>
#include <stddef.h>

#include <atomic>

#include "src/core/lib/debug/trace.h"
#include "src/core/util/debug_location.h"

struct grpc_slice_refcount {
 public:
  typedef void (*DestroyerFn)(grpc_slice_refcount*);

  static grpc_slice_refcount* NoopRefcount() {
    return reinterpret_cast<grpc_slice_refcount*>(1);
  }

  grpc_slice_refcount() = default;

  explicit grpc_slice_refcount(DestroyerFn destroyer_fn)
      : destroyer_fn_(destroyer_fn) {}

  void Ref(grpc_core::DebugLocation location) {
    auto prev_refs = ref_.fetch_add(1, std::memory_order_relaxed);
    GRPC_TRACE_LOG(slice_refcount, INFO)
            .AtLocation(location.file(), location.line())
        << "REF " << this << " " << prev_refs << "->" << prev_refs + 1;
  }
  void Unref(grpc_core::DebugLocation location) {
    auto prev_refs = ref_.fetch_sub(1, std::memory_order_acq_rel);
    GRPC_TRACE_LOG(slice_refcount, INFO)
            .AtLocation(location.file(), location.line())
        << "UNREF " << this << " " << prev_refs << "->" << prev_refs - 1;
    if (prev_refs == 1) {
      destroyer_fn_(this);
    }
  }

  bool IsUnique() const { return ref_.load(std::memory_order_relaxed) == 1; }

 private:
  std::atomic<size_t> ref_{1};
  DestroyerFn destroyer_fn_ = nullptr;
};

#endif
