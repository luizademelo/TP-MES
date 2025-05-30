
// Copyright 2015 gRPC authors.

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <grpc/support/port_platform.h>

#include <optional>
#include <string>

#ifdef GPR_LINUX_ENV

#include <features.h>
#include <stdlib.h>

#include "src/core/util/env.h"

namespace grpc_core {

std::optional<std::string> GetEnv(const char* name) {
  char* result = nullptr;
#if (__GLIBC__ > 2 || (__GLIBC__ == 2 && __GLIBC_MINOR__ >= 17)) && \
    !defined(GRPC_FORCE_UNSECURE_GETENV)
  result = secure_getenv(name);
#else
  result = getenv(name);

#endif
  if (result == nullptr) return std::nullopt;
  return result;
}

void SetEnv(const char* name, const char* value) {
  int res = setenv(name, value, 1);
  if (res != 0) abort();
}

void UnsetEnv(const char* name) {
  int res = unsetenv(name);
  if (res != 0) abort();
}

}

#endif
