// Copyright 2021 gRPC authors.

#ifndef GRPC_SRC_CORE_UTIL_CONSTRUCT_DESTRUCT_H
#define GRPC_SRC_CORE_UTIL_CONSTRUCT_DESTRUCT_H

#include <grpc/support/port_platform.h>

#include <new>
#include <utility>

namespace grpc_core {

template <typename T>
GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION inline void Destruct(T* p) {
  p->~T();
}

template <typename T, typename... Args>
GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION inline void Construct(T* p,
                                                           Args&&... args) {
  new (p) T(std::forward<Args>(args)...);
}

}

#endif
