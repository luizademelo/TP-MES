// Copyright 2022 gRPC authors.

#include "src/core/config/load_config.h"

#include <grpc/support/port_platform.h>
#include <stdio.h>

#include <optional>

#include "absl/flags/marshalling.h"
#include "absl/log/check.h"
#include "absl/strings/numbers.h"
#include "absl/strings/str_join.h"
#include "src/core/util/env.h"

namespace grpc_core {

namespace {
std::optional<std::string> LoadEnv(absl::string_view environment_variable) {
  return GetEnv(std::string(environment_variable).c_str());
}
}

std::string LoadConfigFromEnv(absl::string_view environment_variable,
                              const char* default_value) {
  CHECK(!environment_variable.empty());
  return LoadEnv(environment_variable).value_or(default_value);
}

int32_t LoadConfigFromEnv(absl::string_view environment_variable,
                          int32_t default_value) {
  auto env = LoadEnv(environment_variable);
  if (env.has_value()) {
    int32_t out;
    if (absl::SimpleAtoi(*env, &out)) return out;
    fprintf(stderr, "Error reading int from %s: '%s' is not a number",
            std::string(environment_variable).c_str(), env->c_str());
  }
  return default_value;
}

bool LoadConfigFromEnv(absl::string_view environment_variable,
                       bool default_value) {
  auto env = LoadEnv(environment_variable);
  if (env.has_value()) {
    bool out;
    std::string error;
    if (absl::ParseFlag(env->c_str(), &out, &error)) return out;
    fprintf(stderr, "Error reading bool from %s: '%s' is not a bool: %s",
            std::string(environment_variable).c_str(), env->c_str(),
            error.c_str());
  }
  return default_value;
}

std::string LoadConfig(const absl::Flag<std::vector<std::string>>& flag,
                       absl::string_view environment_variable,
                       const absl::optional<std::string>& override,
                       const char* default_value) {
  if (override.has_value()) return *override;
  auto from_flag = absl::GetFlag(flag);
  if (!from_flag.empty()) return absl::StrJoin(from_flag, ",");
  return LoadConfigFromEnv(environment_variable, default_value);
}

}
