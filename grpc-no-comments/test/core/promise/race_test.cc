// Copyright 2021 gRPC authors.

#include "src/core/lib/promise/race.h"

#include <memory>

#include "gtest/gtest.h"
#include "src/core/lib/promise/poll.h"

namespace grpc_core {

Poll<int> instant() { return 1; }
Poll<int> never() { return Pending(); }

TEST(RaceTest, Race1) { EXPECT_EQ(Race(instant)(), Poll<int>(1)); }
TEST(RaceTest, Race2A) { EXPECT_EQ(Race(instant, never)(), Poll<int>(1)); }
TEST(RaceTest, Race2B) { EXPECT_EQ(Race(never, instant)(), Poll<int>(1)); }

}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
