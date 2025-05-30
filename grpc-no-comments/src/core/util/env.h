
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_UTIL_ENV_H
#define GRPC_SRC_CORE_UTIL_ENV_H

#include <grpc/support/port_platform.h>

#include <optional>
#include <string>

namespace grpc_core {

std::optional<std::string> GetEnv(const char* name);

void SetEnv(const char* name, const char* value);
inline void SetEnv(const char* name, const std::string& value) {
  SetEnv(name, value.c_str());
}

void UnsetEnv(const char* name);

template <typename T>
void SetOrUnsetEnv(const char* name, const std::optional<T>& value) {
  if (value.has_value()) {
    SetEnv(name, value.value());
  } else {
    UnsetEnv(name);
  }
}

}

#endif
