// Copyright 2022 gRPC authors.

#include "test/core/event_engine/test_suite/posix/oracle_event_engine_posix.h"

#include "gtest/gtest.h"
#include "test/core/event_engine/test_suite/event_engine_test_framework.h"
#include "test/core/test_util/test_config.h"

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  grpc::testing::TestEnvironment env(&argc, argv);
  auto ee_factory = []() {
    return std::make_unique<
        grpc_event_engine::experimental::PosixOracleEventEngine>();
  };
  SetEventEngineFactories(ee_factory,
                          ee_factory);
  return RUN_ALL_TESTS();
}
