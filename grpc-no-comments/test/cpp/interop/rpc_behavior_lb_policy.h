
// Copyright 2023 gRPC authors.

#ifndef GRPC_TEST_CPP_INTEROP_RPC_BEHAVIOR_LB_POLICY_H
#define GRPC_TEST_CPP_INTEROP_RPC_BEHAVIOR_LB_POLICY_H

#include <grpc/support/port_platform.h>

#include "src/core/config/core_configuration.h"

namespace grpc {
namespace testing {
void RegisterRpcBehaviorLbPolicy(
    grpc_core::CoreConfiguration::Builder* builder);
}
}

#endif