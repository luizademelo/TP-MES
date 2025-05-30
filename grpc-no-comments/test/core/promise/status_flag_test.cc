// Copyright 2023 gRPC authors.

#include "src/core/lib/promise/status_flag.h"

#include <memory>
#include <utility>

#include "gtest/gtest.h"

namespace grpc_core {

TEST(StatusFlagTest, Basics) {
  EXPECT_TRUE(StatusFlag(true).ok());
  EXPECT_FALSE(StatusFlag(false).ok());
  EXPECT_TRUE(StatusCast<absl::Status>(StatusFlag(true)).ok());
  EXPECT_FALSE(StatusCast<absl::Status>(StatusFlag(false)).ok());
  EXPECT_TRUE(ValueOrFailure<int>(42).ok());
  EXPECT_FALSE(ValueOrFailure<int>(Failure{}).ok());
  EXPECT_TRUE(StatusCast<absl::Status>(ValueOrFailure<int>(42).status()).ok());
  EXPECT_FALSE(
      StatusCast<absl::Status>(ValueOrFailure<int>(Failure{}).status()).ok());
  EXPECT_EQ(ValueOrFailure<int>(42).value(), 42);
  EXPECT_EQ(StatusCast<absl::StatusOr<int>>(ValueOrFailure<int>(42)).value(),
            42);
  EXPECT_TRUE(IsStatusOk(Success{}));
  EXPECT_FALSE(IsStatusOk(Failure{}));
}

TEST(StatusFlagTest, StringifyValueOrFailure) {
  EXPECT_EQ(absl::StrCat(ValueOrFailure<int>(42)), "Success(42)");
  EXPECT_EQ(absl::StrCat(ValueOrFailure<int>(Failure{})), "Failure");
}

}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
