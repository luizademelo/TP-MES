
// Copyright 2017 gRPC authors.

#ifndef GRPC_SRC_CORE_UTIL_MEMORY_H
#define GRPC_SRC_CORE_UTIL_MEMORY_H

#include <grpc/support/alloc.h>
#include <grpc/support/port_platform.h>

#include <memory>
#include <type_traits>

namespace grpc_core {

class DefaultDeleteChar {
 public:
  void operator()(char* p) {
    if (p == nullptr) return;
    gpr_free(p);
  }
};

template <typename T>
using UniquePtr = std::unique_ptr<T, DefaultDeleteChar>;

template <class T>
T* Zalloc() {
  static_assert(std::is_trivial<T>::value, "Type should be trivial");
  return static_cast<T*>(gpr_zalloc(sizeof(T)));
}

}

#endif
