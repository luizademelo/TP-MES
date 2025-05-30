// Copyright 2025 gRPC authors.

#include "src/core/util/shared_bit_gen.h"

#include <stdint.h>

#include "absl/random/distributions.h"
#include "gtest/gtest.h"

namespace grpc_core {

TEST(SharedBitGenTest, Works) {
  SharedBitGen gen;
  for (int i = 0; i < 100; ++i) {
    auto x = absl::Uniform(gen, 0, 100);
    EXPECT_GE(x, 0);
    EXPECT_LT(x, 100);
  }
}

}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
