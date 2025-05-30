// Copyright 2022 gRPC authors.

#include "src/core/util/sorted_pack.h"

#include <vector>

#include "gtest/gtest.h"

using grpc_core::WithSortedPack;

template <int I>
struct Int {
  int value() const { return I; }
};

template <typename A, typename B>
struct Cmp;

template <int A, int B>
struct Cmp<Int<A>, Int<B>> {
  static constexpr bool kValue = A < B;
};

template <typename... Args>
struct VecMaker {
  static std::vector<int> Make() { return {Args().value()...}; }
};

template <int... Args>
std::vector<int> TestVec() {
  return WithSortedPack<VecMaker, Cmp, Int<Args>...>::Type::Make();
}

TEST(SortedPackTest, Empty) { EXPECT_EQ(TestVec<>(), std::vector<int>{}); }

TEST(SortedPackTest, LenOne) {
  EXPECT_EQ((TestVec<1>()), (std::vector<int>{1}));
  EXPECT_EQ((TestVec<2>()), (std::vector<int>{2}));
}

TEST(SortedPackTest, Len2) {
  EXPECT_EQ((TestVec<1, 2>()), (std::vector<int>{1, 2}));
  EXPECT_EQ((TestVec<2, 1>()), (std::vector<int>{1, 2}));
}

TEST(SortedPackTest, Len3) {
  EXPECT_EQ((TestVec<1, 2, 3>()), (std::vector<int>{1, 2, 3}));
  EXPECT_EQ((TestVec<1, 3, 2>()), (std::vector<int>{1, 2, 3}));
  EXPECT_EQ((TestVec<2, 1, 3>()), (std::vector<int>{1, 2, 3}));
  EXPECT_EQ((TestVec<2, 3, 1>()), (std::vector<int>{1, 2, 3}));
  EXPECT_EQ((TestVec<3, 1, 2>()), (std::vector<int>{1, 2, 3}));
  EXPECT_EQ((TestVec<3, 2, 1>()), (std::vector<int>{1, 2, 3}));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
