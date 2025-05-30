// Copyright 2021 gRPC authors.

#include "src/core/lib/promise/latch.h"

#include <tuple>
#include <utility>

#include "absl/status/status.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "src/core/lib/promise/activity.h"
#include "src/core/lib/promise/join.h"
#include "src/core/lib/promise/seq.h"
#include "test/core/promise/test_wakeup_schedulers.h"

using testing::MockFunction;
using testing::StrictMock;

namespace grpc_core {

TEST(LatchTest, Works) {
  Latch<int> latch;
  StrictMock<MockFunction<void(absl::Status)>> on_done;
  EXPECT_CALL(on_done, Call(absl::OkStatus()));
  MakeActivity(
      [&latch] {
        return Seq(Join(latch.Wait(),
                        [&latch]() {
                          latch.Set(42);
                          return true;
                        }),
                   [](std::tuple<int, bool> result) {
                     EXPECT_EQ(std::get<0>(result), 42);
                     return absl::OkStatus();
                   });
      },
      NoWakeupScheduler(),
      [&on_done](absl::Status status) { on_done.Call(std::move(status)); });
}

TEST(LatchTest, WaitAndCopyWorks) {
  Latch<std::string> latch;
  StrictMock<MockFunction<void(absl::Status)>> on_done;
  EXPECT_CALL(on_done, Call(absl::OkStatus()));
  MakeActivity(
      [&latch] {
        return Seq(Join(latch.WaitAndCopy(), latch.WaitAndCopy(),
                        [&latch]() {
                          latch.Set(
                              "Once a jolly swagman camped by a billabong, "
                              "under the shade of a coolibah tree.");
                          return true;
                        }),
                   [](std::tuple<std::string, std::string, bool> result) {
                     EXPECT_EQ(std::get<0>(result),
                               "Once a jolly swagman camped by a billabong, "
                               "under the shade of a coolibah tree.");
                     EXPECT_EQ(std::get<1>(result),
                               "Once a jolly swagman camped by a billabong, "
                               "under the shade of a coolibah tree.");
                     return absl::OkStatus();
                   });
      },
      NoWakeupScheduler(),
      [&on_done](absl::Status status) { on_done.Call(std::move(status)); });
}

TEST(LatchTest, Void) {
  Latch<void> latch;
  StrictMock<MockFunction<void(absl::Status)>> on_done;
  EXPECT_CALL(on_done, Call(absl::OkStatus()));
  MakeActivity(
      [&latch] {
        return Seq(Join(latch.Wait(),
                        [&latch]() {
                          latch.Set();
                          return true;
                        }),
                   [](std::tuple<Empty, bool>) { return absl::OkStatus(); });
      },
      NoWakeupScheduler(),
      [&on_done](absl::Status status) { on_done.Call(std::move(status)); });
}

TEST(LatchTest, ExternallyObservableVoid) {
  ExternallyObservableLatch<void> latch;
  StrictMock<MockFunction<void(absl::Status)>> on_done;
  EXPECT_CALL(on_done, Call(absl::OkStatus()));
  MakeActivity(
      [&latch] {
        return Seq(Join(latch.Wait(),
                        [&latch]() {
                          latch.Set();
                          return true;
                        }),
                   [](std::tuple<Empty, bool>) { return absl::OkStatus(); });
      },
      NoWakeupScheduler(),
      [&on_done](absl::Status status) { on_done.Call(std::move(status)); });
}

}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
