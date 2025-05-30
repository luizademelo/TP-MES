
// Copyright 2015 gRPC authors.

#include <grpc/support/port_platform.h>

#ifdef GPR_POSIX_ENV

#include <stdlib.h>

#include "src/core/util/env.h"

namespace grpc_core {

std::optional<std::string> GetEnv(const char* name) {
  char* result = getenv(name);
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
