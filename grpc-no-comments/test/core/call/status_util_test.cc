
// Copyright 2017 gRPC authors.

#include "src/core/call/status_util.h"

#include "gtest/gtest.h"

namespace grpc_core {
namespace internal {
namespace {

TEST(StatusCodeSet, Basic) {
  StatusCodeSet set;
  EXPECT_TRUE(set.Empty());
  EXPECT_FALSE(set.Contains(GRPC_STATUS_OK));
  EXPECT_FALSE(set.Contains(GRPC_STATUS_UNAVAILABLE));
  set.Add(GRPC_STATUS_OK);
  EXPECT_FALSE(set.Empty());
  EXPECT_TRUE(set.Contains(GRPC_STATUS_OK));
  EXPECT_FALSE(set.Contains(GRPC_STATUS_UNAVAILABLE));
  set.Add(GRPC_STATUS_UNAVAILABLE);
  EXPECT_FALSE(set.Empty());
  EXPECT_TRUE(set.Contains(GRPC_STATUS_OK));
  EXPECT_TRUE(set.Contains(GRPC_STATUS_UNAVAILABLE));
}

}
}
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
