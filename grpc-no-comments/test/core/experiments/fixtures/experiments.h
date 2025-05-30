// Copyright 2023 gRPC authors.

#ifndef GRPC_TEST_CORE_EXPERIMENTS_FIXTURES_EXPERIMENTS_H
#define GRPC_TEST_CORE_EXPERIMENTS_FIXTURES_EXPERIMENTS_H

#include <grpc/support/port_platform.h>

#include "src/core/lib/experiments/config.h"

namespace grpc_core {

#ifdef GRPC_EXPERIMENTS_ARE_FINAL

#if defined(GRPC_CFSTREAM)
inline bool IsTestExperiment1Enabled() { return false; }
#define GRPC_EXPERIMENT_IS_INCLUDED_TEST_EXPERIMENT_2
inline bool IsTestExperiment2Enabled() { return true; }
#ifndef NDEBUG
#define GRPC_EXPERIMENT_IS_INCLUDED_TEST_EXPERIMENT_3
#endif
inline bool IsTestExperiment3Enabled() {
#ifdef NDEBUG
  return false;
#else
  return true;
#endif
}
#define GRPC_EXPERIMENT_IS_INCLUDED_TEST_EXPERIMENT_4
inline bool IsTestExperiment4Enabled() { return true; }

#elif defined(GPR_WINDOWS)
inline bool IsTestExperiment1Enabled() { return false; }
inline bool IsTestExperiment2Enabled() { return false; }
#ifndef NDEBUG
#define GRPC_EXPERIMENT_IS_INCLUDED_TEST_EXPERIMENT_3
#endif
inline bool IsTestExperiment3Enabled() {
#ifdef NDEBUG
  return false;
#else
  return true;
#endif
}
#define GRPC_EXPERIMENT_IS_INCLUDED_TEST_EXPERIMENT_4
inline bool IsTestExperiment4Enabled() { return true; }

#else
#ifndef NDEBUG
#define GRPC_EXPERIMENT_IS_INCLUDED_TEST_EXPERIMENT_1
#endif
inline bool IsTestExperiment1Enabled() {
#ifdef NDEBUG
  return false;
#else
  return true;
#endif
}
#ifndef NDEBUG
#define GRPC_EXPERIMENT_IS_INCLUDED_TEST_EXPERIMENT_2
#endif
inline bool IsTestExperiment2Enabled() {
#ifdef NDEBUG
  return false;
#else
  return true;
#endif
}
#ifndef NDEBUG
#define GRPC_EXPERIMENT_IS_INCLUDED_TEST_EXPERIMENT_3
#endif
inline bool IsTestExperiment3Enabled() {
#ifdef NDEBUG
  return false;
#else
  return true;
#endif
}
inline bool IsTestExperiment4Enabled() { return false; }
#endif

#else
enum ExperimentIds {
  kExperimentIdTestExperiment1,
  kExperimentIdTestExperiment2,
  kExperimentIdTestExperiment3,
  kExperimentIdTestExperiment4,
  kNumTestExperiments
};
#define GRPC_EXPERIMENT_IS_INCLUDED_TEST_EXPERIMENT_1
inline bool IsTestExperiment1Enabled() {
  return IsTestExperimentEnabled<kExperimentIdTestExperiment1>();
}
#define GRPC_EXPERIMENT_IS_INCLUDED_TEST_EXPERIMENT_2
inline bool IsTestExperiment2Enabled() {
  return IsTestExperimentEnabled<kExperimentIdTestExperiment2>();
}
#define GRPC_EXPERIMENT_IS_INCLUDED_TEST_EXPERIMENT_3
inline bool IsTestExperiment3Enabled() {
  return IsTestExperimentEnabled<kExperimentIdTestExperiment3>();
}
#define GRPC_EXPERIMENT_IS_INCLUDED_TEST_EXPERIMENT_4
inline bool IsTestExperiment4Enabled() {
  return IsTestExperimentEnabled<kExperimentIdTestExperiment4>();
}

extern const ExperimentMetadata g_test_experiment_metadata[kNumTestExperiments];

#endif
}

#endif
