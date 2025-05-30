
// Copyright 2015 gRPC authors.

#include <grpc/support/alloc.h>
#include <grpc/support/port_platform.h>
#include <stdlib.h>
#include <string.h>

#include "absl/log/check.h"
#include "src/core/util/crash.h"

void* gpr_malloc(size_t size) {
  void* p;
  if (size == 0) return nullptr;
  p = malloc(size);
  if (!p) {
    abort();
  }
  return p;
}

void* gpr_zalloc(size_t size) {
  void* p;
  if (size == 0) return nullptr;
  p = calloc(size, 1);
  if (!p) {
    abort();
  }
  return p;
}

void gpr_free(void* p) { free(p); }

void* gpr_realloc(void* p, size_t size) {
  if ((size == 0) && (p == nullptr)) return nullptr;

  p = realloc(p, size);
  if (!p) {
    abort();
  }
  return p;
}

void* gpr_malloc_aligned(size_t size, size_t alignment) {
  CHECK_EQ(((alignment - 1) & alignment), 0u);
  size_t extra = alignment - 1 + sizeof(void*);
  void* p = gpr_malloc(size + extra);
  void** ret = reinterpret_cast<void**>(
      (reinterpret_cast<uintptr_t>(p) + extra) & ~(alignment - 1));
  ret[-1] = p;
  return ret;
}

void gpr_free_aligned(void* ptr) { gpr_free((static_cast<void**>(ptr))[-1]); }
