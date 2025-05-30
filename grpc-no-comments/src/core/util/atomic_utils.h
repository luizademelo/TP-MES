
// Copyright 2017 gRPC authors.

#ifndef GRPC_SRC_CORE_UTIL_ATOMIC_UTILS_H
#define GRPC_SRC_CORE_UTIL_ATOMIC_UTILS_H

#include <grpc/support/port_platform.h>

#include <atomic>

namespace grpc_core {

template <typename T>
inline bool IncrementIfNonzero(std::atomic<T>* p) {
  T count = p->load(std::memory_order_acquire);
  do {

    if (count == 0) {
      return false;
    }
  } while (!p->compare_exchange_weak(
      count, count + 1, std::memory_order_acq_rel, std::memory_order_acquire));
  return true;
}

}

#endif
