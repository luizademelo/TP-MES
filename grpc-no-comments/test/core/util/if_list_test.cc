// Copyright 2023 gRPC authors.

#include "src/core/util/if_list.h"

#include <memory>

#include "gtest/gtest.h"

namespace grpc_core {

TEST(IfListTest, Works) {
  EXPECT_EQ(IfList(
                0, 42, [](int) { return -1; }, [](int x) { return x == 0; },
                [](int x) { return x; }),
            42);
  EXPECT_EQ(IfList(
                1, 42, [](int) { return -1; }, [](int x) { return x == 0; },
                [](int x) { return x; }),
            -1);
}

}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
