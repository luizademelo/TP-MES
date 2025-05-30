// Copyright 2021 gRPC authors.

#include "src/core/util/avl.h"

#include <memory>

#include "gtest/gtest.h"

namespace grpc_core {

TEST(AvlTest, NoOp) { AVL<int, int> avl; }

TEST(AvlTest, Lookup) {
  auto avl = AVL<int, int>().Add(1, 42);
  EXPECT_EQ(nullptr, avl.Lookup(2));
  EXPECT_EQ(42, *avl.Lookup(1));
  avl = avl.Remove(1);
  EXPECT_EQ(nullptr, avl.Lookup(1));
  avl = avl.Add(1, 42).Add(1, 1);
  EXPECT_EQ(1, *avl.Lookup(1));
  avl = avl.Add(2, 2).Add(3, 3).Add(4, 4);
  EXPECT_EQ(1, *avl.Lookup(1));
  EXPECT_EQ(2, *avl.Lookup(2));
  EXPECT_EQ(3, *avl.Lookup(3));
  EXPECT_EQ(4, *avl.Lookup(4));
  EXPECT_EQ(nullptr, avl.Lookup(5));
}

}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
