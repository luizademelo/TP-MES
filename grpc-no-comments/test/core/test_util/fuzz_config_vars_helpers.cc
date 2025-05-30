// Copyright 2023 gRPC authors.

#include "test/core/test_util/fuzz_config_vars_helpers.h"

#include <stddef.h>
#include <stdint.h>

#include <algorithm>
#include <string>
#include <vector>

#include "absl/strings/str_join.h"
#include "src/core/lib/experiments/config.h"
#include "src/core/lib/experiments/experiments.h"

namespace grpc_core {

std::vector<std::string> ExperimentConfigChoices() {
  std::vector<std::string> choices;
  for (size_t i = 0; i < kNumExperiments; i++) {
    if (!g_experiment_metadata[i].allow_in_fuzzing_config) continue;
    choices.push_back(g_experiment_metadata[i].name);
    choices.push_back(absl::StrCat("-", g_experiment_metadata[i].name));
  }
  return choices;
}

std::vector<std::string> TracerConfigChoices() {
  std::vector<std::string> choices;
  for (const auto& [name, _] : GetAllTraceFlags()) {
    choices.push_back(name);
    choices.push_back(absl::StrCat("-", name));
  }
  return choices;
}

}
