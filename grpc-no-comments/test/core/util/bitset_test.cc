// Copyright 2021 gRPC authors.

#include "src/core/util/bitset.h"

#include <random>
#include <set>

#include "gtest/gtest.h"

namespace grpc_core {
namespace testing {

template <size_t K>
struct Size {
  static constexpr size_t kBits = K;
};

using TestSizes = ::testing::Types<

    Size<1>, Size<2>, Size<3>, Size<4>, Size<5>, Size<6>, Size<7>, Size<8>,
    Size<9>, Size<10>, Size<11>, Size<12>, Size<13>, Size<14>, Size<15>,
    Size<16>, Size<17>,

    Size<24>, Size<25>, Size<26>, Size<27>, Size<28>, Size<29>, Size<30>,
    Size<31>, Size<32>, Size<33>,

    Size<47>, Size<48>, Size<49>,

    Size<62>, Size<63>, Size<64>, Size<65>, Size<66>,

    Size<95>, Size<96>, Size<97>,

    Size<1024>, Size<4000>, Size<4321> >;

template <typename S>
struct BitSetTest : public ::testing::Test {};

TYPED_TEST_SUITE(BitSetTest, TestSizes);

TYPED_TEST(BitSetTest, NoneAtInit) {
  BitSet<TypeParam::kBits> b;
  EXPECT_TRUE(b.none());
}

TYPED_TEST(BitSetTest, OneBit) {
  constexpr size_t kBits = TypeParam::kBits;
  for (size_t i = 0; i < kBits; i++) {
    BitSet<kBits> b;
    b.set(i);
    EXPECT_FALSE(b.none());
    for (size_t j = 0; j < kBits; j++) {
      EXPECT_EQ(b.is_set(j), i == j);
    }
  }
}

TYPED_TEST(BitSetTest, AllSet) {
  constexpr size_t kBits = TypeParam::kBits;
  BitSet<kBits> b;
  for (size_t i = 0; i < kBits; i++) {
    EXPECT_FALSE(b.all());
    b.set(i);
  }
  EXPECT_TRUE(b.all());
}

TYPED_TEST(BitSetTest, Count) {
  constexpr size_t kBits = TypeParam::kBits;
  BitSet<kBits> b;
  std::set<size_t> bits_set;
  std::random_device rd;
  std::uniform_int_distribution<size_t> dist(0, kBits - 1);
  for (size_t i = 0; i < 4 * kBits; i++) {
    size_t bit = dist(rd);
    bits_set.insert(bit);
    b.set(bit);
    EXPECT_EQ(b.count(), bits_set.size());
  }
}

TEST(ToIntTest, ToInt) {
  auto make_bitset = [](bool b0, bool b1, bool b2) {
    BitSet<3> b;
    b.set(0, b0);
    b.set(1, b1);
    b.set(2, b2);
    return b;
  };
  EXPECT_EQ(make_bitset(false, false, false).ToInt<uint32_t>(), 0);
  EXPECT_EQ(make_bitset(true, false, false).ToInt<uint32_t>(), 1);
  EXPECT_EQ(make_bitset(false, true, false).ToInt<uint32_t>(), 2);
  EXPECT_EQ(make_bitset(true, true, false).ToInt<uint32_t>(), 3);
  EXPECT_EQ(make_bitset(false, false, true).ToInt<uint32_t>(), 4);
  EXPECT_EQ(make_bitset(true, false, true).ToInt<uint32_t>(), 5);
  EXPECT_EQ(make_bitset(false, true, true).ToInt<uint32_t>(), 6);
  EXPECT_EQ(make_bitset(true, true, true).ToInt<uint32_t>(), 7);
}

TEST(EmptyBitSet, Empty) {
  BitSet<0> b;
  EXPECT_TRUE(b.all());
  EXPECT_TRUE(b.none());
  EXPECT_EQ(b.count(), 0);
}

}
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
