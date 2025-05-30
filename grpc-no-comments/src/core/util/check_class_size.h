
// Copyright 2025 gRPC authors.

#ifndef GRPC_SRC_CORE_UTIL_CHECK_CLASS_SIZE_H
#define GRPC_SRC_CORE_UTIL_CHECK_CLASS_SIZE_H

#include <grpc/support/port_platform.h>

#if defined(__has_feature)
#if __has_feature(memory_sanitizer)
#define GRPC_MSAN_ENABLED 1
#else
#define GRPC_MSAN_ENABLED 0
#endif
#else
#ifdef MEMORY_SANITIZER
#define GRPC_MSAN_ENABLED 1
#else
#define GRPC_MSAN_ENABLED 0
#endif
#endif

#if defined(GPR_LINUX) && !defined(NDEBUG) && !defined(GRPC_ASAN_ENABLED) && \
    !defined(GRPC_MSAN_ENABLED)

#define GRPC_CHECK_CLASS_SIZE(class_name, class_size) \
  static_assert(sizeof(class_name) <= (class_size), "Class size too large");
#else
#define GRPC_CHECK_CLASS_SIZE(class_name, class_size)
#endif

#endif
