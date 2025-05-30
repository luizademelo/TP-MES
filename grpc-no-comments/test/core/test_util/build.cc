// Copyright 2021 gRPC authors.

#if defined(__has_feature)
#if __has_feature(address_sanitizer)
#define GRPC_BUILD_HAS_ASAN 1
#else
#define GRPC_BUILD_HAS_ASAN 0
#endif
#else
#ifdef ADDRESS_SANITIZER
#define GRPC_BUILD_HAS_ASAN 1
#else
#define GRPC_BUILD_HAS_ASAN 0
#endif
#endif

#if defined(__has_feature)
#if __has_feature(thread_sanitizer)
#define GRPC_BUILD_HAS_TSAN 1
#else
#define GRPC_BUILD_HAS_TSAN 0
#endif
#else
#ifdef THREAD_SANITIZER
#define GRPC_BUILD_HAS_TSAN 1
#else
#define GRPC_BUILD_HAS_TSAN 0
#endif
#endif

#if defined(__has_feature)
#if __has_feature(memory_sanitizer)
#define GRPC_BUILD_HAS_MSAN 1
#else
#define GRPC_BUILD_HAS_MSAN 0
#endif
#else
#ifdef MEMORY_SANITIZER
#define GRPC_BUILD_HAS_MSAN 1
#else
#define GRPC_BUILD_HAS_MSAN 0
#endif
#endif

#if GRPC_BUILD_HAS_ASAN
#include <sanitizer/lsan_interface.h>
#endif

bool BuiltUnderValgrind() {
#ifdef RUNNING_ON_VALGRIND
  return true;
#else
  return false;
#endif
}

bool BuiltUnderTsan() { return GRPC_BUILD_HAS_TSAN != 0; }

bool BuiltUnderAsan() { return GRPC_BUILD_HAS_ASAN != 0; }

void AsanAssertNoLeaks() {
#if GRPC_BUILD_HAS_ASAN
  __lsan_do_leak_check();
#endif
}

bool BuiltUnderMsan() { return GRPC_BUILD_HAS_MSAN != 0; }

bool BuiltUnderUbsan() {
#ifdef GRPC_UBSAN
  return true;
#else
  return false;
#endif
}
