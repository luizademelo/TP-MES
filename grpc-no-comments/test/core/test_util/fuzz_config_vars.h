// Copyright 2023 gRPC authors.

#ifndef GRPC_TEST_CORE_TEST_UTIL_FUZZ_CONFIG_VARS_H
#define GRPC_TEST_CORE_TEST_UTIL_FUZZ_CONFIG_VARS_H

#include <grpc/support/port_platform.h>

#include "src/core/config/config_vars.h"
#include "test/core/test_util/fuzz_config_vars.pb.h"

namespace grpc_core {

ConfigVars::Overrides OverridesFromFuzzConfigVars(
    const grpc::testing::FuzzConfigVars& vars);
void ApplyFuzzConfigVars(const grpc::testing::FuzzConfigVars& vars);

}

#endif
