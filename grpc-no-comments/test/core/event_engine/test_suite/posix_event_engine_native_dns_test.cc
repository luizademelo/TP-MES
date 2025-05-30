// Copyright 2023 The gRPC Authors

#include <grpc/grpc.h>

#include <memory>
#include <optional>
#include <string>

#include "gtest/gtest.h"
#include "src/core/config/config_vars.h"
#include "src/core/lib/event_engine/posix_engine/posix_engine.h"
#include "test/core/event_engine/test_suite/event_engine_test_framework.h"
#include "test/core/event_engine/test_suite/posix/oracle_event_engine_posix.h"
#include "test/core/event_engine/test_suite/tests/dns_test.h"
#include "test/core/test_util/test_config.h"

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  grpc::testing::TestEnvironment env(&argc, argv);
  SetEventEngineFactories(
      []() {
        return grpc_event_engine::experimental::PosixEventEngine::
            MakePosixEventEngine();
      },
      []() {
        return std::make_unique<
            grpc_event_engine::experimental::PosixOracleEventEngine>();
      });

  grpc_core::ConfigVars::Overrides overrides;
  overrides.dns_resolver = "native";
  grpc_core::ConfigVars::SetOverrides(overrides);
  grpc_event_engine::experimental::InitDNSTests();
  grpc_init();
  int r = RUN_ALL_TESTS();
  grpc_shutdown();
  return r;
}
