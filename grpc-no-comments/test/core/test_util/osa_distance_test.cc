// Copyright 2023 gRPC authors.

#include "test/core/test_util/osa_distance.h"

#include <memory>

#include "gtest/gtest.h"

namespace grpc_core {

TEST(OsaDistanceTest, Works) {
  EXPECT_EQ(OsaDistance("", ""), 0);
  EXPECT_EQ(OsaDistance("a", "a"), 0);
  EXPECT_EQ(OsaDistance("abc", "abc"), 0);
  EXPECT_EQ(OsaDistance("abc", "abd"), 1);
  EXPECT_EQ(OsaDistance("abc", "acb"), 1);
  EXPECT_EQ(OsaDistance("abcd", "acbd"), 1);
}

}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
