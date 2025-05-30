// Copyright 2022 gRPC authors.

#include "src/core/lib/experiments/config.h"

#include <grpc/support/port_platform.h>
#include <string.h>

#include <algorithm>
#include <atomic>
#include <map>
#include <string>
#include <utility>
#include <vector>

#include "absl/functional/any_invocable.h"
#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/strings/str_join.h"
#include "absl/strings/str_split.h"
#include "absl/strings/string_view.h"
#include "absl/strings/strip.h"
#include "src/core/config/config_vars.h"
#include "src/core/lib/experiments/experiments.h"
#include "src/core/util/crash.h"
#include "src/core/util/no_destruct.h"

#ifndef GRPC_EXPERIMENTS_ARE_FINAL
namespace grpc_core {

namespace {
struct Experiments {
  bool enabled[kNumExperiments];
};

struct ForcedExperiment {
  bool forced = false;
  bool value;
};

ForcedExperiment* ForcedExperiments() {
  static NoDestruct<ForcedExperiment> forced_experiments[kNumExperiments];
  return &**forced_experiments;
}

std::atomic<bool>* Loaded() {
  static NoDestruct<std::atomic<bool>> loaded(false);
  return &*loaded;
}

absl::AnyInvocable<bool(struct ExperimentMetadata)>* g_check_constraints_cb =
    nullptr;

class TestExperiments {
 public:
  TestExperiments(const ExperimentMetadata* experiment_metadata,
                  size_t num_experiments)
      : enabled_(num_experiments) {
    for (size_t i = 0; i < num_experiments; i++) {
      if (g_check_constraints_cb != nullptr) {
        enabled_[i] = (*g_check_constraints_cb)(experiment_metadata[i]);
      } else {
        enabled_[i] = experiment_metadata[i].default_value;
      }
    }

    for (auto experiment : absl::StrSplit(ConfigVars::Get().Experiments(), ',',
                                          absl::SkipWhitespace())) {

      bool enable = !absl::ConsumePrefix(&experiment, "-");

      for (size_t i = 0; i < num_experiments; i++) {
        if (experiment == experiment_metadata[i].name) {
          enabled_[i] = enable;
          break;
        }
      }
    }
  }

  bool operator[](int index) const { return enabled_[index]; }

 private:
  std::vector<bool> enabled_;
};

TestExperiments* g_test_experiments = nullptr;

GPR_ATTRIBUTE_NOINLINE Experiments LoadExperimentsFromConfigVariableInner() {

  Experiments experiments;
  for (size_t i = 0; i < kNumExperiments; i++) {
    if (!ForcedExperiments()[i].forced) {
      if (g_check_constraints_cb != nullptr) {
        experiments.enabled[i] =
            (*g_check_constraints_cb)(g_experiment_metadata[i]);
      } else {
        experiments.enabled[i] = g_experiment_metadata[i].default_value;
      }
    } else {
      experiments.enabled[i] = ForcedExperiments()[i].value;
    }
  }

  for (auto experiment : absl::StrSplit(ConfigVars::Get().Experiments(), ',',
                                        absl::SkipWhitespace())) {

    bool enable = true;
    if (experiment[0] == '-') {
      enable = false;
      experiment.remove_prefix(1);
    }

    bool found = false;
    for (size_t i = 0; i < kNumExperiments; i++) {
      if (experiment == g_experiment_metadata[i].name) {
        experiments.enabled[i] = enable;
        found = true;
        break;
      }
    }

    if (!found) {
      LOG(ERROR) << "Unknown experiment: " << experiment;
    }
  }
  for (size_t i = 0; i < kNumExperiments; i++) {

    for (size_t j = 0; j < g_experiment_metadata[i].num_required_experiments;
         j++) {

      CHECK(g_experiment_metadata[i].required_experiments[j] < i);
      if (!experiments
               .enabled[g_experiment_metadata[i].required_experiments[j]]) {
        experiments.enabled[i] = false;
      }
    }
  }
  return experiments;
}

Experiments LoadExperimentsFromConfigVariable() {
  Loaded()->store(true, std::memory_order_relaxed);
  return LoadExperimentsFromConfigVariableInner();
}

Experiments& ExperimentsSingleton() {

  static NoDestruct<Experiments> experiments{
      LoadExperimentsFromConfigVariable()};
  return *experiments;
}
}

void TestOnlyReloadExperimentsFromConfigVariables() {
  ExperimentFlags::TestOnlyClear();
  ExperimentsSingleton() = LoadExperimentsFromConfigVariable();
  PrintExperimentsList();
}

void LoadTestOnlyExperimentsFromMetadata(
    const ExperimentMetadata* experiment_metadata, size_t num_experiments) {
  g_test_experiments =
      new TestExperiments(experiment_metadata, num_experiments);
}

std::atomic<uint64_t>
    ExperimentFlags::experiment_flags_[kNumExperimentFlagsWords];

bool ExperimentFlags::LoadFlagsAndCheck(size_t experiment_id) {
  static_assert(kNumExperiments < kNumExperimentFlagsWords * kFlagsPerWord,
                "kNumExperiments must be less than "
                "kNumExperimentFlagsWords*kFlagsPerWord; if this fails then "
                "make kNumExperimentFlagsWords bigger.");
  const auto& experiments = ExperimentsSingleton();
  uint64_t building[kNumExperimentFlagsWords];
  for (size_t i = 0; i < kNumExperimentFlagsWords; i++) {
    building[i] = kLoadedFlag;
  }
  for (size_t i = 0; i < kNumExperiments; i++) {
    if (!experiments.enabled[i]) continue;
    auto bit = i % kFlagsPerWord;
    auto word = i / kFlagsPerWord;
    building[word] |= 1ull << bit;
  }
  for (size_t i = 0; i < kNumExperimentFlagsWords; i++) {
    experiment_flags_[i].store(building[i], std::memory_order_relaxed);
  }
  return experiments.enabled[experiment_id];
}

void ExperimentFlags::TestOnlyClear() {
  for (size_t i = 0; i < kNumExperimentFlagsWords; i++) {
    experiment_flags_[i].store(0, std::memory_order_relaxed);
  }
}

bool IsExperimentEnabledInConfiguration(size_t experiment_id) {
  return LoadExperimentsFromConfigVariableInner().enabled[experiment_id];
}

bool IsTestExperimentEnabled(size_t experiment_id) {
  return (*g_test_experiments)[experiment_id];
}

#define GRPC_EXPERIMENT_LOG VLOG(2)

void PrintExperimentsList() {
  std::map<std::string, std::string> experiment_status;
  std::set<std::string> defaulted_on_experiments;
  for (size_t i = 0; i < kNumExperiments; i++) {
    const char* name = g_experiment_metadata[i].name;
    const bool enabled = IsExperimentEnabled(i);
    const bool default_enabled = g_experiment_metadata[i].default_value;
    const bool forced = ForcedExperiments()[i].forced;
    if (!default_enabled && !enabled) continue;
    if (default_enabled && enabled) {
      defaulted_on_experiments.insert(name);
      continue;
    }
    if (enabled) {
      if (g_check_constraints_cb != nullptr &&
          (*g_check_constraints_cb)(g_experiment_metadata[i])) {
        experiment_status[name] = "on:constraints";
        continue;
      }
      if (forced && ForcedExperiments()[i].value) {
        experiment_status[name] = "on:forced";
        continue;
      }
      experiment_status[name] = "on";
    } else {
      if (forced && !ForcedExperiments()[i].value) {
        experiment_status[name] = "off:forced";
        continue;
      }
      experiment_status[name] = "off";
    }
  }
  if (experiment_status.empty()) {
    if (!defaulted_on_experiments.empty()) {
      GRPC_EXPERIMENT_LOG << "gRPC experiments enabled: "
                          << absl::StrJoin(defaulted_on_experiments, ", ");
    }
  } else {
    if (defaulted_on_experiments.empty()) {
      GRPC_EXPERIMENT_LOG << "gRPC experiments: "
                          << absl::StrJoin(experiment_status, ", ",
                                           absl::PairFormatter(":"));
    } else {
      GRPC_EXPERIMENT_LOG << "gRPC experiments: "
                          << absl::StrJoin(experiment_status, ", ",
                                           absl::PairFormatter(":"))
                          << "; default-enabled: "
                          << absl::StrJoin(defaulted_on_experiments, ", ");
    }
  }
}

void ForceEnableExperiment(absl::string_view experiment, bool enable) {
  CHECK(Loaded()->load(std::memory_order_relaxed) == false);
  for (size_t i = 0; i < kNumExperiments; i++) {
    if (g_experiment_metadata[i].name != experiment) continue;
    if (ForcedExperiments()[i].forced) {
      CHECK(ForcedExperiments()[i].value == enable);
    } else {
      ForcedExperiments()[i].forced = true;
      ForcedExperiments()[i].value = enable;
    }
    return;
  }
  LOG(INFO) << "gRPC EXPERIMENT " << experiment << " not found to force "
            << (enable ? "enable" : "disable");
}

void RegisterExperimentConstraintsValidator(
    absl::AnyInvocable<bool(struct ExperimentMetadata)> check_constraints_cb) {
  g_check_constraints_cb =
      new absl::AnyInvocable<bool(struct ExperimentMetadata)>(
          std::move(check_constraints_cb));
}

}
#else
namespace grpc_core {
void PrintExperimentsList() {}
void ForceEnableExperiment(absl::string_view experiment_name, bool) {
  Crash(absl::StrCat("ForceEnableExperiment(\"", experiment_name,
                     "\") called in final build"));
}

void RegisterExperimentConstraintsValidator(
    absl::AnyInvocable<
        bool(struct ExperimentMetadata)> ) {}

}
#endif
