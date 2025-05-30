// Copyright 2022 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_EXPERIMENTS_CONFIG_H
#define GRPC_SRC_CORE_LIB_EXPERIMENTS_CONFIG_H

#include <grpc/support/port_platform.h>
#include <stddef.h>
#include <stdint.h>

#include <atomic>

#include "absl/functional/any_invocable.h"
#include "absl/strings/string_view.h"

namespace grpc_core {

struct ExperimentMetadata {
  const char* name;
  const char* description;
  const char* additional_constaints;
  const uint8_t* required_experiments;
  uint8_t num_required_experiments;
  bool default_value;
  bool allow_in_fuzzing_config;
};

#ifndef GRPC_EXPERIMENTS_ARE_FINAL
class ExperimentFlags {
 public:
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION static bool IsExperimentEnabled(
      size_t experiment_id) {
    auto bit = experiment_id % kFlagsPerWord;
    auto word = experiment_id / kFlagsPerWord;
    auto cur = experiment_flags_[word].load(std::memory_order_relaxed);
    if (cur & (1ull << bit)) return true;
    if (cur & kLoadedFlag) return false;
    return LoadFlagsAndCheck(experiment_id);
  }

  template <size_t kExperimentId>
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION static bool IsExperimentEnabled() {
    auto bit = kExperimentId % kFlagsPerWord;
    auto word = kExperimentId / kFlagsPerWord;
    auto cur = experiment_flags_[word].load(std::memory_order_relaxed);
    if (cur & (1ull << bit)) return true;
    if (cur & kLoadedFlag) return false;
    return LoadFlagsAndCheck(kExperimentId);
  }

  static void TestOnlyClear();

 private:
  static bool LoadFlagsAndCheck(size_t experiment_id);

  static constexpr size_t kNumExperimentFlagsWords = 8;
  static constexpr size_t kFlagsPerWord = 63;
  static constexpr uint64_t kLoadedFlag = 0x8000000000000000ull;
  static std::atomic<uint64_t> experiment_flags_[kNumExperimentFlagsWords];
};

inline bool IsExperimentEnabled(size_t experiment_id) {
  return ExperimentFlags::IsExperimentEnabled(experiment_id);
}

template <size_t kExperimentId>
inline bool IsExperimentEnabled() {
  return ExperimentFlags::IsExperimentEnabled<kExperimentId>();
}

bool IsTestExperimentEnabled(size_t experiment_id);

template <size_t kExperimentId>
inline bool IsTestExperimentEnabled() {
  return IsTestExperimentEnabled(kExperimentId);
}

bool IsExperimentEnabledInConfiguration(size_t experiment_id);

void TestOnlyReloadExperimentsFromConfigVariables();

void LoadTestOnlyExperimentsFromMetadata(
    const ExperimentMetadata* experiment_metadata, size_t num_experiments);
#endif

void PrintExperimentsList();

void ForceEnableExperiment(absl::string_view experiment_name, bool enable);

void RegisterExperimentConstraintsValidator(
    absl::AnyInvocable<bool(struct ExperimentMetadata)> check_constraints_cb);

}

#endif
