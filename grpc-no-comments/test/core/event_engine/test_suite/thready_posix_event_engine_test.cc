// Copyright 2023 The gRPC Authors

#include <grpc/grpc.h>

#include <memory>

#include "gtest/gtest.h"
#include "src/core/lib/event_engine/posix_engine/posix_engine.h"
#include "src/core/lib/event_engine/thready_event_engine/thready_event_engine.h"
#include "test/core/event_engine/test_suite/event_engine_test_framework.h"
#include "test/core/event_engine/test_suite/posix/oracle_event_engine_posix.h"
#include "test/core/event_engine/test_suite/tests/client_test.h"
#include "test/core/event_engine/test_suite/tests/server_test.h"
#include "test/core/event_engine/test_suite/tests/timer_test.h"
#include "test/core/test_util/test_config.h"

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  grpc::testing::TestEnvironment env(&argc, argv);
  SetEventEngineFactories(
      []() {
        return std::make_unique<
            grpc_event_engine::experimental::ThreadyEventEngine>(
            grpc_event_engine::experimental::PosixEventEngine::
                MakePosixEventEngine());
      },
      []() {
        return std::make_unique<
            grpc_event_engine::experimental::ThreadyEventEngine>(
            std::make_unique<
                grpc_event_engine::experimental::PosixOracleEventEngine>());
      });
  grpc_event_engine::experimental::InitTimerTests();
  grpc_event_engine::experimental::InitClientTests();
  grpc_event_engine::experimental::InitServerTests();

  grpc_init();
  int r = RUN_ALL_TESTS();
  grpc_shutdown();
  return r;
}
