// Copyright 2023 gRPC authors.

#include "test/core/experiments/fixtures/experiments.h"

#include <grpc/support/port_platform.h>

#include <memory>

#include "gtest/gtest.h"
#include "src/core/lib/experiments/config.h"

#ifndef GRPC_EXPERIMENTS_ARE_FINAL

#if defined(GRPC_CFSTREAM)
bool GetExperimentTestExperiment1ExpectedValue() { return false; }

bool GetExperimentTestExperiment2ExpectedValue() { return true; }

bool GetExperimentTestExperiment3ExpectedValue() {
#ifdef NDEBUG
  return false;
#else
  return true;
#endif
}

bool GetExperimentTestExperiment4ExpectedValue() { return true; }

#elif defined(GPR_WINDOWS)
bool GetExperimentTestExperiment1ExpectedValue() { return false; }

bool GetExperimentTestExperiment2ExpectedValue() { return false; }

bool GetExperimentTestExperiment3ExpectedValue() {

#ifdef NDEBUG
  return false;
#else
  return true;
#endif
}

bool GetExperimentTestExperiment4ExpectedValue() { return true; }

#else
bool GetExperimentTestExperiment1ExpectedValue() {

#ifdef NDEBUG
  return false;
#else
  return true;
#endif
}

bool GetExperimentTestExperiment2ExpectedValue() {

#ifdef NDEBUG
  return false;
#else
  return true;
#endif
}

bool GetExperimentTestExperiment3ExpectedValue() {

#ifdef NDEBUG
  return false;
#else
  return true;
#endif
}

bool GetExperimentTestExperiment4ExpectedValue() { return false; }
#endif

TEST(ExperimentsTest, CheckExperimentValuesTest) {
  ASSERT_EQ(grpc_core::IsTestExperiment1Enabled(),
            GetExperimentTestExperiment1ExpectedValue());

  ASSERT_EQ(grpc_core::IsTestExperiment2Enabled(),
            GetExperimentTestExperiment2ExpectedValue());

  ASSERT_EQ(grpc_core::IsTestExperiment3Enabled(),
            GetExperimentTestExperiment3ExpectedValue());

  ASSERT_EQ(grpc_core::IsTestExperiment4Enabled(),
            GetExperimentTestExperiment4ExpectedValue());
}

#endif

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  grpc_core::LoadTestOnlyExperimentsFromMetadata(
      grpc_core::g_test_experiment_metadata, grpc_core::kNumTestExperiments);
  return RUN_ALL_TESTS();
}
