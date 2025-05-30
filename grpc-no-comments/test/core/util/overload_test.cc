// Copyright 2021 gRPC authors.

#include "src/core/util/overload.h"

#include <string>

#include "gtest/gtest.h"

namespace grpc_core {
namespace testing {

TEST(Overload, Test) {
  auto a = [](int x) { return x; };
  auto b = [](std::string x) -> int { return x.length(); };
  auto overload = Overload(a, b);
  EXPECT_EQ(overload(1), 1);
  EXPECT_EQ(overload("1"), 1);
  EXPECT_EQ(overload("abc"), 3);
}

}
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
