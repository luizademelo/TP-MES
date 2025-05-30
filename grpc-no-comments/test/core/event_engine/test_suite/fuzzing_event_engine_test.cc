// Copyright 2022 The gRPC Authors

#include "test/core/event_engine/fuzzing_event_engine/fuzzing_event_engine.h"

#include <chrono>

#include "gtest/gtest.h"
#include "test/core/event_engine/test_suite/event_engine_test_framework.h"
#include "test/core/event_engine/test_suite/tests/timer_test.h"

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  std::shared_ptr<grpc_event_engine::experimental::FuzzingEventEngine> engine =
      std::make_shared<
          grpc_event_engine::experimental::ThreadedFuzzingEventEngine>(
          std::chrono::milliseconds(2));
  SetEventEngineFactories([engine]() { return engine; },
                          [engine]() { return engine; });
  grpc_event_engine::experimental::InitTimerTests();
  return RUN_ALL_TESTS();
}
