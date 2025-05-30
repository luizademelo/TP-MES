// Copyright 2023 gRPC authors.

#include "test/core/experiments/fixtures/experiments.h"

#include <grpc/support/port_platform.h>

#ifndef GRPC_EXPERIMENTS_ARE_FINAL

#if defined(GRPC_CFSTREAM)
namespace {
const char* const description_test_experiment_1 = "Test Experiment 1";
const char* const additional_constraints_test_experiment_1 = "{}";
const char* const description_test_experiment_2 = "Test Experiment 2";
const char* const additional_constraints_test_experiment_2 = "{}";
const char* const description_test_experiment_3 = "Test Experiment 3";
const char* const additional_constraints_test_experiment_3 = "{}";
const char* const description_test_experiment_4 = "Test Experiment 4";
const char* const additional_constraints_test_experiment_4 = "{}";
#ifdef NDEBUG
const bool kDefaultForDebugOnly = false;
#else
const bool kDefaultForDebugOnly = true;
#endif
}

namespace grpc_core {

const ExperimentMetadata g_test_experiment_metadata[] = {
    {"test_experiment_1", description_test_experiment_1,
     additional_constraints_test_experiment_1, nullptr, 0, false, true},
    {"test_experiment_2", description_test_experiment_2,
     additional_constraints_test_experiment_2, nullptr, 0, true, true},
    {"test_experiment_3", description_test_experiment_3,
     additional_constraints_test_experiment_3, nullptr, 0, kDefaultForDebugOnly,
     true},
    {"test_experiment_4", description_test_experiment_4,
     additional_constraints_test_experiment_4, nullptr, 0, true, true},
};

}

#elif defined(GPR_WINDOWS)
namespace {
const char* const description_test_experiment_1 = "Test Experiment 1";
const char* const additional_constraints_test_experiment_1 = "{}";
const char* const description_test_experiment_2 = "Test Experiment 2";
const char* const additional_constraints_test_experiment_2 = "{}";
const char* const description_test_experiment_3 = "Test Experiment 3";
const char* const additional_constraints_test_experiment_3 = "{}";
const char* const description_test_experiment_4 = "Test Experiment 4";
const char* const additional_constraints_test_experiment_4 = "{}";
#ifdef NDEBUG
const bool kDefaultForDebugOnly = false;
#else
const bool kDefaultForDebugOnly = true;
#endif
}

namespace grpc_core {

const ExperimentMetadata g_test_experiment_metadata[] = {
    {"test_experiment_1", description_test_experiment_1,
     additional_constraints_test_experiment_1, nullptr, 0, false, true},
    {"test_experiment_2", description_test_experiment_2,
     additional_constraints_test_experiment_2, nullptr, 0, false, true},
    {"test_experiment_3", description_test_experiment_3,
     additional_constraints_test_experiment_3, nullptr, 0, kDefaultForDebugOnly,
     true},
    {"test_experiment_4", description_test_experiment_4,
     additional_constraints_test_experiment_4, nullptr, 0, true, true},
};

}

#else
namespace {
const char* const description_test_experiment_1 = "Test Experiment 1";
const char* const additional_constraints_test_experiment_1 = "{}";
const char* const description_test_experiment_2 = "Test Experiment 2";
const char* const additional_constraints_test_experiment_2 = "{}";
const char* const description_test_experiment_3 = "Test Experiment 3";
const char* const additional_constraints_test_experiment_3 = "{}";
const char* const description_test_experiment_4 = "Test Experiment 4";
const char* const additional_constraints_test_experiment_4 = "{}";
#ifdef NDEBUG
const bool kDefaultForDebugOnly = false;
#else
const bool kDefaultForDebugOnly = true;
#endif
}

namespace grpc_core {

const ExperimentMetadata g_test_experiment_metadata[] = {
    {"test_experiment_1", description_test_experiment_1,
     additional_constraints_test_experiment_1, nullptr, 0, kDefaultForDebugOnly,
     true},
    {"test_experiment_2", description_test_experiment_2,
     additional_constraints_test_experiment_2, nullptr, 0, kDefaultForDebugOnly,
     true},
    {"test_experiment_3", description_test_experiment_3,
     additional_constraints_test_experiment_3, nullptr, 0, kDefaultForDebugOnly,
     true},
    {"test_experiment_4", description_test_experiment_4,
     additional_constraints_test_experiment_4, nullptr, 0, false, true},
};

}
#endif
#endif
