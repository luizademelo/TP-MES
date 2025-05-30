
// Copyright 2015 gRPC authors.

#include "src/core/util/unique_ptr_with_bitset.h"

#include <grpc/support/port_platform.h>
#include <stdint.h>

#include <limits>
#include <memory>

#include "gtest/gtest.h"

namespace grpc_core {

TEST(UniquePtrWithBitsetTest, Basic) {
  UniquePtrWithBitset<int, 1> ptr;
  EXPECT_EQ(ptr.get(), nullptr);
  EXPECT_EQ(ptr.TestBit(0), false);
  ptr.reset(new int(42));
  EXPECT_EQ(*ptr, 42);
  EXPECT_EQ(ptr.TestBit(0), false);
  ptr.SetBit(0);
  EXPECT_EQ(ptr.TestBit(0), true);
  ptr.reset();
  EXPECT_EQ(ptr.get(), nullptr);
  EXPECT_EQ(ptr.TestBit(0), true);
  ptr.ClearBit(0);
  EXPECT_EQ(ptr.TestBit(0), false);
  ptr.reset(new int(43));
  ptr.SetBit(0);

  UniquePtrWithBitset<int, 1> ptr2;
  ptr2 = std::move(ptr);
  EXPECT_EQ(*ptr2, 43);
  EXPECT_EQ(ptr2.TestBit(0), true);
}

}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
