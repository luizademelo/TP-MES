// Copyright 2021 gRPC authors.

#include "src/core/util/match.h"

#include <stdlib.h>

#include <memory>

#include "gtest/gtest.h"

namespace grpc_core {
namespace testing {

TEST(MatchTest, Test) {
  EXPECT_EQ(Match(
                std::variant<int, double>(1.9), [](int) -> int { abort(); },
                [](double x) -> int {
                  EXPECT_EQ(x, 1.9);
                  return 42;
                }),
            42);
  EXPECT_EQ(Match(
                std::variant<int, double>(3),
                [](int x) -> int {
                  EXPECT_EQ(x, 3);
                  return 42;
                },
                [](double) -> int { abort(); }),
            42);
}

TEST(MatchTest, TestVoidReturn) {
  bool triggered = false;
  Match(
      std::variant<int, double>(1.9), [](int) { abort(); },
      [&triggered](double x) {
        EXPECT_EQ(x, 1.9);
        triggered = true;
      });
  EXPECT_TRUE(triggered);
}

TEST(MatchTest, TestMutable) {
  std::variant<int, double> v = 1.9;
  MatchMutable(&v, [](int*) { abort(); }, [](double* x) { *x = 0.0; });
  EXPECT_EQ(v, (std::variant<int, double>(0.0)));
}

TEST(MatchTest, TestMutableWithReturn) {
  std::variant<int, double> v = 1.9;
  EXPECT_EQ(MatchMutable(
                &v, [](int*) -> int { abort(); },
                [](double* x) -> int {
                  *x = 0.0;
                  return 1;
                }),
            1);
  EXPECT_EQ(v, (std::variant<int, double>(0.0)));
}

}
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
