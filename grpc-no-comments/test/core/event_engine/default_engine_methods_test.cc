// Copyright 2022 gRPC authors.

#include <grpc/event_engine/endpoint_config.h>
#include <grpc/event_engine/event_engine.h>
#include <grpc/event_engine/memory_allocator.h>
#include <grpc/grpc.h>
#include <grpc/support/port_platform.h>

#include <algorithm>
#include <memory>
#include <thread>
#include <vector>

#include "absl/functional/any_invocable.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/time/clock.h"
#include "absl/time/time.h"
#include "gtest/gtest.h"
#include "src/core/lib/event_engine/default_event_engine.h"
#include "src/core/util/notification.h"
#include "test/core/event_engine/mock_event_engine.h"
#include "test/core/test_util/test_config.h"

namespace {

using ::grpc_event_engine::experimental::GetDefaultEventEngine;

class DefaultEngineTest : public testing::Test {
 protected:
  class CountingEngine
      : public grpc_event_engine::experimental::MockEventEngine {
   public:
    struct EngineOpCounts {
      EngineOpCounts() : constructed(0), destroyed(0), ran(0), ran_after(0) {};
      int constructed;
      int destroyed;
      int ran;
      int ran_after;
    };
    explicit CountingEngine(EngineOpCounts& counter) : counter_(counter) {
      ++counter_.constructed;
    }
    ~CountingEngine() override { ++counter_.destroyed; }
    void Run(Closure* ) override { ++counter_.ran; };
    void Run(absl::AnyInvocable<void()> ) override {
      ++counter_.ran;
    };
    TaskHandle RunAfter(Duration , Closure* ) override {
      ++counter_.ran_after;
      return {-1, -1};
    }
    TaskHandle RunAfter(Duration ,
                        absl::AnyInvocable<void()> ) override {
      ++counter_.ran_after;
      return {-1, -1};
    }

   private:
    EngineOpCounts& counter_;
  };
};

TEST_F(DefaultEngineTest, ScopedEngineLifetime) {
  DefaultEngineTest::CountingEngine::EngineOpCounts op_counts;
  {
    auto engine =
        std::make_shared<DefaultEngineTest::CountingEngine>(op_counts);
    grpc_event_engine::experimental::DefaultEventEngineScope engine_scope(
        std::move(engine));
    ASSERT_EQ(op_counts.constructed, 1);
    ASSERT_EQ(op_counts.ran, 0);
    {
      auto ee2 = GetDefaultEventEngine();
      ASSERT_EQ(op_counts.constructed, 1);
      ee2->Run([]() {});

      ASSERT_EQ(op_counts.ran, 1);
    }

    ASSERT_EQ(op_counts.destroyed, 0);
  }

  ASSERT_EQ(op_counts.destroyed, 1);

  auto ee3 = GetDefaultEventEngine();
  grpc_core::Notification notification;
  ee3->Run([&notification]() { notification.Notify(); });
  notification.WaitForNotification();
  ASSERT_EQ(op_counts.constructed, 1);
  ASSERT_EQ(op_counts.destroyed, 1);
  ASSERT_EQ(op_counts.ran, 1);
}

TEST_F(DefaultEngineTest, ProvidedDefaultEngineHasPrecedenceOverFactory) {
  DefaultEngineTest::CountingEngine::EngineOpCounts ee1_op_counts;
  DefaultEngineTest::CountingEngine::EngineOpCounts ee2_op_counts;
  grpc_event_engine::experimental::SetEventEngineFactory([&ee2_op_counts]() {
    return std::make_shared<DefaultEngineTest::CountingEngine>(ee2_op_counts);
  });
  ASSERT_EQ(ee2_op_counts.constructed, 0);

  {
    auto tmp_engine = GetDefaultEventEngine();
    ASSERT_EQ(ee2_op_counts.constructed, 1);
  }
  ASSERT_EQ(ee2_op_counts.destroyed, 1);

  {
    grpc_event_engine::experimental::DefaultEventEngineScope engine_scope(
        std::make_shared<DefaultEngineTest::CountingEngine>(ee1_op_counts));
    auto tmp_engine = GetDefaultEventEngine();
    ASSERT_EQ(ee2_op_counts.constructed, 1)
        << "The factory should not have been used to create a default engine";
    ASSERT_EQ(ee1_op_counts.constructed, 1);
  }

  auto tmp_engine = GetDefaultEventEngine();
  ASSERT_EQ(ee2_op_counts.constructed, 2);
  grpc_event_engine::experimental::EventEngineFactoryReset();
}

TEST_F(DefaultEngineTest, ProvidedDefaultEngineResetsExistingInternalEngine) {
  auto internal_engine = GetDefaultEventEngine();
  DefaultEngineTest::CountingEngine::EngineOpCounts op_counts;
  {
    grpc_event_engine::experimental::DefaultEventEngineScope engine_scope(
        std::make_shared<DefaultEngineTest::CountingEngine>(op_counts));
    auto user_engine = GetDefaultEventEngine();
    ASSERT_GE(internal_engine.use_count(), 1);
    ASSERT_EQ(op_counts.constructed, 1);
  }
  ASSERT_EQ(op_counts.destroyed, 1);

  auto third_engine = GetDefaultEventEngine();
  ASSERT_NE(third_engine.get(), internal_engine.get());

  grpc_core::Notification ran1, ran2;
  internal_engine->Run([&ran1]() { ran1.Notify(); });
  third_engine->Run([&ran2]() { ran2.Notify(); });
  ran1.WaitForNotification();
  ran2.WaitForNotification();
  ASSERT_EQ(op_counts.constructed, 1);
  ASSERT_EQ(op_counts.destroyed, 1);
}

TEST_F(DefaultEngineTest, StressTestSharedPtr) {
  constexpr int thread_count = 13;
  constexpr absl::Duration spin_time = absl::Seconds(3);
  std::vector<std::thread> threads;
  threads.reserve(thread_count);
  for (int i = 0; i < thread_count; i++) {
    threads.emplace_back([&spin_time] {
      auto timeout = absl::Now() + spin_time;
      do {
        GetDefaultEventEngine().reset();
      } while (timeout > absl::Now());
    });
  }
  for (auto& thd : threads) {
    thd.join();
  }
}
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  grpc::testing::TestEnvironment env(&argc, argv);
  grpc_init();
  auto result = RUN_ALL_TESTS();
  grpc_shutdown();
  return result;
}
