
// Copyright 2015 gRPC authors.

#include <grpc/event_engine/event_engine.h>
#include <grpc/support/time.h>

#include <cstdint>
#include <limits>
#include <optional>
#include <vector>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "src/core/lib/event_engine/posix_engine/timer.h"
#include "src/core/util/time.h"

using testing::Mock;
using testing::Return;
using testing::StrictMock;

namespace grpc_event_engine {
namespace experimental {

namespace {
const int64_t kHoursIn25Days = 25 * 24;
const grpc_core::Duration k25Days = grpc_core::Duration::Hours(kHoursIn25Days);

class MockClosure : public experimental::EventEngine::Closure {
 public:
  MOCK_METHOD(void, Run, ());
};

class MockHost : public TimerListHost {
 public:
  virtual ~MockHost() {}
  MOCK_METHOD(grpc_core::Timestamp, Now, ());
  MOCK_METHOD(void, Kick, ());
};

enum class CheckResult { kTimersFired, kCheckedAndEmpty, kNotChecked };

CheckResult FinishCheck(
    std::optional<std::vector<experimental::EventEngine::Closure*>> result) {
  if (!result.has_value()) return CheckResult::kNotChecked;
  if (result->empty()) return CheckResult::kCheckedAndEmpty;
  for (auto closure : *result) {
    closure->Run();
  }
  return CheckResult::kTimersFired;
}

}

TEST(TimerListTest, Add) {
  Timer timers[20];
  StrictMock<MockClosure> closures[20];

  const auto kStart =
      grpc_core::Timestamp::FromMillisecondsAfterProcessEpoch(100);

  StrictMock<MockHost> host;
  EXPECT_CALL(host, Now()).WillOnce(Return(kStart));
  TimerList timer_list(&host);

  for (int i = 0; i < 10; i++) {
    EXPECT_CALL(host, Now()).WillOnce(Return(kStart));
    timer_list.TimerInit(&timers[i],
                         kStart + grpc_core::Duration::Milliseconds(10),
                         &closures[i]);
  }

  for (int i = 10; i < 20; i++) {
    EXPECT_CALL(host, Now()).WillOnce(Return(kStart));
    timer_list.TimerInit(&timers[i],
                         kStart + grpc_core::Duration::Milliseconds(1010),
                         &closures[i]);
  }

  EXPECT_CALL(host, Now())
      .WillOnce(Return(kStart + grpc_core::Duration::Milliseconds(500)));
  for (int i = 0; i < 10; i++) {
    EXPECT_CALL(closures[i], Run());
  }
  EXPECT_EQ(FinishCheck(timer_list.TimerCheck(nullptr)),
            CheckResult::kTimersFired);
  for (int i = 0; i < 10; i++) {
    Mock::VerifyAndClearExpectations(&closures[i]);
  }

  EXPECT_CALL(host, Now())
      .WillOnce(Return(kStart + grpc_core::Duration::Milliseconds(600)));
  EXPECT_EQ(FinishCheck(timer_list.TimerCheck(nullptr)),
            CheckResult::kCheckedAndEmpty);

  EXPECT_CALL(host, Now())
      .WillOnce(Return(kStart + grpc_core::Duration::Milliseconds(1500)));
  for (int i = 10; i < 20; i++) {
    EXPECT_CALL(closures[i], Run());
  }
  EXPECT_EQ(FinishCheck(timer_list.TimerCheck(nullptr)),
            CheckResult::kTimersFired);
  for (int i = 10; i < 20; i++) {
    Mock::VerifyAndClearExpectations(&closures[i]);
  }

  EXPECT_CALL(host, Now())
      .WillOnce(Return(kStart + grpc_core::Duration::Milliseconds(1600)));
  EXPECT_EQ(FinishCheck(timer_list.TimerCheck(nullptr)),
            CheckResult::kCheckedAndEmpty);
}

TEST(TimerListTest, Destruction) {
  Timer timers[5];
  StrictMock<MockClosure> closures[5];

  StrictMock<MockHost> host;
  EXPECT_CALL(host, Now())
      .WillOnce(
          Return(grpc_core::Timestamp::FromMillisecondsAfterProcessEpoch(0)));
  TimerList timer_list(&host);

  EXPECT_CALL(host, Now())
      .WillOnce(
          Return(grpc_core::Timestamp::FromMillisecondsAfterProcessEpoch(0)));
  timer_list.TimerInit(
      &timers[0], grpc_core::Timestamp::FromMillisecondsAfterProcessEpoch(100),
      &closures[0]);
  EXPECT_CALL(host, Now())
      .WillOnce(
          Return(grpc_core::Timestamp::FromMillisecondsAfterProcessEpoch(0)));
  timer_list.TimerInit(
      &timers[1], grpc_core::Timestamp::FromMillisecondsAfterProcessEpoch(3),
      &closures[1]);
  EXPECT_CALL(host, Now())
      .WillOnce(
          Return(grpc_core::Timestamp::FromMillisecondsAfterProcessEpoch(0)));
  timer_list.TimerInit(
      &timers[2], grpc_core::Timestamp::FromMillisecondsAfterProcessEpoch(100),
      &closures[2]);
  EXPECT_CALL(host, Now())
      .WillOnce(
          Return(grpc_core::Timestamp::FromMillisecondsAfterProcessEpoch(0)));
  timer_list.TimerInit(
      &timers[3], grpc_core::Timestamp::FromMillisecondsAfterProcessEpoch(3),
      &closures[3]);
  EXPECT_CALL(host, Now())
      .WillOnce(
          Return(grpc_core::Timestamp::FromMillisecondsAfterProcessEpoch(0)));
  timer_list.TimerInit(
      &timers[4], grpc_core::Timestamp::FromMillisecondsAfterProcessEpoch(1),
      &closures[4]);
  EXPECT_CALL(host, Now())
      .WillOnce(
          Return(grpc_core::Timestamp::FromMillisecondsAfterProcessEpoch(2)));
  EXPECT_CALL(closures[4], Run());
  EXPECT_EQ(FinishCheck(timer_list.TimerCheck(nullptr)),
            CheckResult::kTimersFired);
  Mock::VerifyAndClearExpectations(&closures[4]);
  EXPECT_FALSE(timer_list.TimerCancel(&timers[4]));
  EXPECT_TRUE(timer_list.TimerCancel(&timers[0]));
  EXPECT_TRUE(timer_list.TimerCancel(&timers[3]));
  EXPECT_TRUE(timer_list.TimerCancel(&timers[1]));
  EXPECT_TRUE(timer_list.TimerCancel(&timers[2]));
}

TEST(TimerListTest, LongRunningServiceCleanup) {
  Timer timers[4];
  StrictMock<MockClosure> closures[4];

  const auto kStart =
      grpc_core::Timestamp::FromMillisecondsAfterProcessEpoch(k25Days.millis());

  StrictMock<MockHost> host;
  EXPECT_CALL(host, Now()).WillOnce(Return(kStart));
  TimerList timer_list(&host);

  EXPECT_CALL(host, Now()).WillOnce(Return(kStart));
  timer_list.TimerInit(&timers[0], kStart + k25Days, &closures[0]);
  EXPECT_CALL(host, Now()).WillOnce(Return(kStart));
  timer_list.TimerInit(
      &timers[1], kStart + grpc_core::Duration::Milliseconds(3), &closures[1]);
  EXPECT_CALL(host, Now()).WillOnce(Return(kStart));
  timer_list.TimerInit(&timers[2],
                       grpc_core::Timestamp::FromMillisecondsAfterProcessEpoch(
                           std::numeric_limits<int64_t>::max() - 1),
                       &closures[2]);

  gpr_timespec deadline_spec =
      (kStart + k25Days).as_timespec(gpr_clock_type::GPR_CLOCK_MONOTONIC);

  EXPECT_CALL(host, Now()).WillOnce(Return(kStart));
  timer_list.TimerInit(&timers[3],
                       grpc_core::Timestamp::FromTimespecRoundUp(deadline_spec),
                       &closures[3]);

  EXPECT_CALL(host, Now())
      .WillOnce(Return(kStart + grpc_core::Duration::Milliseconds(4)));
  EXPECT_CALL(closures[1], Run());
  EXPECT_EQ(FinishCheck(timer_list.TimerCheck(nullptr)),
            CheckResult::kTimersFired);
  EXPECT_TRUE(timer_list.TimerCancel(&timers[0]));
  EXPECT_FALSE(timer_list.TimerCancel(&timers[1]));
  EXPECT_TRUE(timer_list.TimerCancel(&timers[2]));
  EXPECT_TRUE(timer_list.TimerCancel(&timers[3]));
}

}
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
