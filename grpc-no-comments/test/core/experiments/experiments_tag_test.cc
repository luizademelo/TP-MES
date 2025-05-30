// Copyright 2023 gRPC authors.

#include <grpc/support/port_platform.h>

#include <string>

#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/str_split.h"
#include "absl/strings/string_view.h"
#include "absl/strings/strip.h"
#include "gtest/gtest.h"
#include "src/core/config/config_vars.h"
#include "src/core/lib/experiments/config.h"
#include "test/core/experiments/fixtures/experiments.h"

#ifndef GRPC_EXPERIMENTS_ARE_FINAL

absl::StatusOr<bool> IsExperimentEnabledThroughFlag(
    std::string experiment_name) {
  for (auto experiment :
       absl::StrSplit(grpc_core::ConfigVars::Get().Experiments(), ',',
                      absl::SkipWhitespace())) {

    bool enable = !absl::ConsumePrefix(&experiment, "-");

    if (experiment == experiment_name) {
      return enable;
    }
  }
  return absl::NotFoundError("experiment not found");
}

TEST(ExperimentsTestTagTest, CheckExperimentValuesTest) {
  auto is_experiment_enabled_through_flag =
      IsExperimentEnabledThroughFlag("test_experiment_1");
  if (!is_experiment_enabled_through_flag.ok()) {
    return;
  }
#ifdef GRPC_CFSTREAM
  FAIL() << "test_experiment_1 is broken on ios. so this test should not have "
            "executed on RBE."
#elif GPR_WINDOWS

  EXPECT_TRUE(*is_experiment_enabled_through_flag);
  EXPECT_TRUE(grpc_core::IsTestExperiment1Enabled());
#else

  EXPECT_FALSE(*is_experiment_enabled_through_flag);
  EXPECT_FALSE(grpc_core::IsTestExperiment1Enabled());
#endif
}

#endif

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  grpc_core::LoadTestOnlyExperimentsFromMetadata(
      grpc_core::g_test_experiment_metadata, grpc_core::kNumTestExperiments);
  return RUN_ALL_TESTS();
}
