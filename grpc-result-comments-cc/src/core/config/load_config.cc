Here's the commented version of the code:

```c++
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
// Helper function to load an environment variable
// Args:
//   environment_variable: The name of the environment variable to load
// Returns:
//   std::optional<std::string> containing the value if the variable exists,
//   or std::nullopt if it doesn't exist
std::optional<std::string> LoadEnv(absl::string_view environment_variable) {
  return GetEnv(std::string(environment_variable).c_str());
}
}

// Loads a string configuration value from an environment variable with a fallback default
// Args:
//   environment_variable: The name of the environment variable to load
//   default_value: The default value to return if the variable isn't set
// Returns:
//   The environment variable value if set, otherwise the default value
// Note:
//   The function asserts that environment_variable is not empty
std::string LoadConfigFromEnv(absl::string_view environment_variable,
                              const char* default_value) {
  CHECK(!environment_variable.empty());
  return LoadEnv(environment_variable).value_or(default_value);
}

// Loads an integer configuration value from an environment variable with a fallback default
// Args:
//   environment_variable: The name of the environment variable to load
//   default_value: The default value to return if the variable isn't set or is invalid
// Returns:
//   The parsed integer value if the variable is set and valid,
//   otherwise the default value
// Note:
//   Prints an error message to stderr if the variable exists but contains invalid data
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

// Loads a boolean configuration value from an environment variable with a fallback default
// Args:
//   environment_variable: The name of the environment variable to load
//   default_value: The default value to return if the variable isn't set or is invalid
// Returns:
//   The parsed boolean value if the variable is set and valid,
//   otherwise the default value
// Note:
//   Prints an error message to stderr if the variable exists but contains invalid data
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

// Loads a configuration value from multiple possible sources with a precedence order
// Args:
//   flag: The command line flag that might contain the configuration
//   environment_variable: The environment variable that might contain the configuration
//   override: An explicit override value that takes highest precedence
//   default_value: The default value to use if no other sources are available
// Returns:
//   The configuration value based on the following precedence:
//   1. override value if present
//   2. command line flag if set
//   3. environment variable if set
//   4. default value
// Note:
//   For flag values (which can be multiple strings), they are joined with commas
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
```