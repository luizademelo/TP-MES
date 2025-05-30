// Copyright 2024 gRPC authors.

#include "src/core/util/dump_args.h"

#include <sstream>

#include "gtest/gtest.h"

int add(int a, int b) { return a + b; }

TEST(DumpArgsTest, Basic) {
  int a = 1;
  int b = 2;
  int c = 3;
  EXPECT_EQ("a = 1, b = 2, c = 3", absl::StrCat(GRPC_DUMP_ARGS(a, b, c)));
}

TEST(DumpArgsTest, FunctionCall) {
  EXPECT_EQ("add(1, 2) = 3", absl::StrCat(GRPC_DUMP_ARGS(add(1, 2))));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
