// Copyright 2022 The gRPC Authors

#include <grpc/support/port_platform.h>

#ifdef GPR_APPLE

#include <grpc/grpc.h>

#include "src/core/lib/event_engine/cf_engine/cf_engine.h"
#include "test/core/event_engine/test_suite/event_engine_test_framework.h"
#include "test/core/event_engine/test_suite/posix/oracle_event_engine_posix.h"
#include "test/core/event_engine/test_suite/tests/client_test.h"
#include "test/core/event_engine/test_suite/tests/timer_test.h"
#include "test/core/test_util/test_config.h"

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  grpc::testing::TestEnvironment env(&argc, argv);
  auto factory = []() {
    return std::make_unique<grpc_event_engine::experimental::CFEventEngine>();
  };
  auto oracle_factory = []() {
    return std::make_unique<
        grpc_event_engine::experimental::PosixOracleEventEngine>();
  };
  SetEventEngineFactories(factory, oracle_factory);
  grpc_event_engine::experimental::InitTimerTests();
  grpc_event_engine::experimental::InitClientTests();

  grpc_init();
  int r = RUN_ALL_TESTS();
  grpc_shutdown();
  return r;
}

#else

int main(int , char** ) { return 0; }

#endif
