// Copyright 2021 gRPC authors.

#include "src/core/lib/promise/join.h"

#include <memory>
#include <tuple>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "src/core/lib/promise/poll.h"
#include "src/core/lib/promise/status_flag.h"
#include "test/core/promise/poll_matcher.h"

namespace grpc_core {

TEST(JoinTest, Join1) {
  std::string execution_order;
  EXPECT_THAT(Join([&execution_order]() mutable -> Poll<int> {
                absl::StrAppend(&execution_order, "1");
                return 3;
              })(),
              IsReady(std::tuple(3)));
  EXPECT_STREQ(execution_order.c_str(), "1");
}

TEST(JoinTest, Join2) {
  std::string execution_order;
  EXPECT_THAT(Join(
                  [&execution_order]() mutable -> Poll<int> {
                    absl::StrAppend(&execution_order, "3");
                    return 3;
                  },
                  [&execution_order]() mutable -> Poll<int> {
                    absl::StrAppend(&execution_order, "4");
                    return 4;
                  })(),
              IsReady(std::tuple(3, 4)));
  EXPECT_STREQ(execution_order.c_str(), "34");
}

TEST(JoinTest, Join3) {
  std::string execution_order;
  EXPECT_THAT(Join(
                  [&execution_order]() mutable -> Poll<int> {
                    absl::StrAppend(&execution_order, "3");
                    return 3;
                  },
                  [&execution_order]() mutable -> Poll<int> {
                    absl::StrAppend(&execution_order, "4");
                    return 4;
                  },
                  [&execution_order]() mutable -> Poll<int> {
                    absl::StrAppend(&execution_order, "5");
                    return 5;
                  })(),
              IsReady(std::tuple(3, 4, 5)));
  EXPECT_STREQ(execution_order.c_str(), "345");
}

TEST(JoinTest, JoinPendingFailure) {

  std::string execution_order;
  auto first_promise = [&execution_order]() mutable -> Poll<int> {
    absl::StrAppend(&execution_order, "1");
    return 1;
  };
  auto second_promise = [&execution_order]() mutable -> Poll<StatusFlag> {
    absl::StrAppend(&execution_order, "2");
    return Failure{};
  };
  auto third_promise = [&execution_order,
                        once = false]() mutable -> Poll<std::string> {
    absl::StrAppend(&execution_order, "3");
    if (once) return "Hello World";
    once = true;
    return Pending{};
  };

  auto join_1_2_3 = Join(first_promise, second_promise, third_promise);

  using JoinTuple = std::tuple<int, StatusFlag, std::string>;
  Poll<JoinTuple> first_execution = join_1_2_3();
  EXPECT_FALSE(first_execution.ready());
  absl::StrAppend(&execution_order, "0");

  Poll<JoinTuple> second_execution = join_1_2_3();
  EXPECT_TRUE(second_execution.ready());

  JoinTuple& tuple = *(second_execution.value_if_ready());
  EXPECT_EQ(std::get<0>(tuple), 1);
  EXPECT_EQ(std::get<1>(tuple), Failure{});
  EXPECT_STREQ(std::get<2>(tuple).c_str(), "Hello World");

  EXPECT_STREQ(execution_order.c_str(), "12303");
}

}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
