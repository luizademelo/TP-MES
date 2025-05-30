// Copyright 2024 gRPC authors.

#ifndef GRPC_SRC_CORE_UTIL_DOWN_CAST_H
#define GRPC_SRC_CORE_UTIL_DOWN_CAST_H

#include <grpc/support/port_platform.h>

#include <type_traits>

#include "absl/base/config.h"
#include "absl/log/check.h"

namespace grpc_core {

template <typename To, typename From>
GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION inline To DownCast(From* f) {
  static_assert(
      std::is_base_of<From, typename std::remove_pointer<To>::type>::value,
      "DownCast requires a base-to-derived relationship");

#if ABSL_INTERNAL_HAS_RTTI
#ifndef NDEBUG
  if (f != nullptr) CHECK_NE(dynamic_cast<To>(f), nullptr);
#endif
#endif
  return static_cast<To>(f);
}

template <typename To, typename From>
GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION inline To DownCast(From& f) {
  return *DownCast<typename std::remove_reference<To>::type*>(&f);
}

}

#endif
