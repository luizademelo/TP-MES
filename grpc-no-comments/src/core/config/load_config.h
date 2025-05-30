// Copyright 2022 gRPC authors.

#ifndef GRPC_SRC_CORE_CONFIG_LOAD_CONFIG_H
#define GRPC_SRC_CORE_CONFIG_LOAD_CONFIG_H

#include <grpc/support/port_platform.h>
#include <stdint.h>

#include <optional>
#include <string>
#include <vector>

#include "absl/flags/flag.h"
#include "absl/strings/string_view.h"

namespace grpc_core {

std::string LoadConfigFromEnv(absl::string_view environment_variable,
                              const char* default_value);
int32_t LoadConfigFromEnv(absl::string_view environment_variable,
                          int32_t default_value);
bool LoadConfigFromEnv(absl::string_view environment_variable,
                       bool default_value);

template <typename T, typename D>
T LoadConfig(const absl::Flag<absl::optional<T>>& flag,
             absl::string_view environment_variable,
             const absl::optional<T>& override, D default_value) {
  if (override.has_value()) return *override;
  auto from_flag = absl::GetFlag(flag);
  if (from_flag.has_value()) return std::move(*from_flag);
  return LoadConfigFromEnv(environment_variable, default_value);
}

std::string LoadConfig(const absl::Flag<std::vector<std::string>>& flag,
                       absl::string_view environment_variable,
                       const absl::optional<std::string>& override,
                       const char* default_value);

}

#endif
