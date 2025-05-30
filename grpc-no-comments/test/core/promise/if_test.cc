// Copyright 2021 gRPC authors.

#include "src/core/lib/promise/if.h"

#include "absl/strings/str_cat.h"
#include "gtest/gtest.h"

namespace grpc_core {

TEST(IfTest, ChooseTrue) {
  std::string execution_order;
  EXPECT_EQ(If(
                [&execution_order]() {
                  absl::StrAppend(&execution_order, 1);
                  return true;
                },
                [&execution_order]() {
                  absl::StrAppend(&execution_order, 2);
                  return 2;
                },
                [&execution_order]() {
                  absl::StrAppend(&execution_order, 3);
                  return 3;
                })(),
            Poll<int>(2));
  EXPECT_STREQ(execution_order.c_str(), "12");
}

TEST(IfTest, ChooseFalse) {
  std::string execution_order;
  EXPECT_EQ(If(
                [&execution_order]() {
                  absl::StrAppend(&execution_order, 1);
                  return false;
                },
                [&execution_order]() {
                  absl::StrAppend(&execution_order, 2);
                  return 2;
                },
                [&execution_order]() {
                  absl::StrAppend(&execution_order, 3);
                  return 3;
                })(),
            Poll<int>(3));
  EXPECT_STREQ(execution_order.c_str(), "13");
}

TEST(IfTest, ChooseSuccessfulTrue) {
  std::string execution_order;
  EXPECT_EQ(If(
                [&execution_order]() {
                  absl::StrAppend(&execution_order, 1);
                  return absl::StatusOr<bool>(true);
                },
                [&execution_order]() {
                  absl::StrAppend(&execution_order, 2);
                  return absl::StatusOr<int>(2);
                },
                [&execution_order]() {
                  absl::StrAppend(&execution_order, 3);
                  return absl::StatusOr<int>(3);
                })(),
            Poll<absl::StatusOr<int>>(absl::StatusOr<int>(2)));
  EXPECT_STREQ(execution_order.c_str(), "12");
}

TEST(IfTest, ChooseSuccessfulFalse) {
  std::string execution_order;
  EXPECT_EQ(If(
                [&execution_order]() {
                  absl::StrAppend(&execution_order, 1);
                  return absl::StatusOr<bool>(false);
                },
                [&execution_order]() {
                  absl::StrAppend(&execution_order, 2);
                  return absl::StatusOr<int>(2);
                },
                [&execution_order]() {
                  absl::StrAppend(&execution_order, 3);
                  return absl::StatusOr<int>(3);
                })(),
            Poll<absl::StatusOr<int>>(absl::StatusOr<int>(3)));
  EXPECT_STREQ(execution_order.c_str(), "13");
}

TEST(IfTest, ChooseFailure) {
  std::string execution_order;
  EXPECT_EQ(If(
                [&execution_order]() {
                  absl::StrAppend(&execution_order, 1);
                  return absl::StatusOr<bool>();
                },
                [&execution_order]() {
                  absl::StrAppend(&execution_order, 2);
                  return absl::StatusOr<int>(2);
                },
                [&execution_order]() {
                  absl::StrAppend(&execution_order, 3);
                  return absl::StatusOr<int>(3);
                })(),
            Poll<absl::StatusOr<int>>(absl::StatusOr<int>()));
  EXPECT_STREQ(execution_order.c_str(), "1");
}

TEST(IfTest, ChoosePending) {
  std::string execution_order;
  int once = false;
  auto if_combiner = If(
      [&execution_order, &once]() -> Poll<bool> {
        absl::StrAppend(&execution_order, 1);
        if (once) return true;
        once = true;
        return Pending{};
      },
      [&execution_order]() {
        absl::StrAppend(&execution_order, 2);
        return 2;
      },
      [&execution_order]() {
        absl::StrAppend(&execution_order, 3);
        return 3;
      });

  Poll<int> first_execution = if_combiner();
  EXPECT_FALSE(first_execution.ready());
  EXPECT_STREQ(execution_order.c_str(), "1");

  execution_order.clear();
  Poll<int> second_execution = if_combiner();
  EXPECT_TRUE(second_execution.ready());
  EXPECT_EQ(second_execution.value(), 2);
  EXPECT_EQ(execution_order, "12");
}

TEST(IfTest, ImmediateChooseTrue) {
  std::string execution_order;
  EXPECT_EQ(If(
                true,
                [&execution_order]() {
                  absl::StrAppend(&execution_order, 2);
                  return 2;
                },
                [&execution_order]() {
                  absl::StrAppend(&execution_order, 3);
                  return 3;
                })(),
            Poll<int>(2));
  EXPECT_STREQ(execution_order.c_str(), "2");
}

TEST(IfTest, ImmediateChooseFalse) {
  std::string execution_order;
  EXPECT_EQ(If(
                false,
                [&execution_order]() {
                  absl::StrAppend(&execution_order, 2);
                  return 2;
                },
                [&execution_order]() {
                  absl::StrAppend(&execution_order, 3);
                  return 3;
                })(),
            Poll<int>(3));
  EXPECT_STREQ(execution_order.c_str(), "3");
}

}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
