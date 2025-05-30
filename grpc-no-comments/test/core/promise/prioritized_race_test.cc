// Copyright 2023 gRPC authors.

#include "src/core/lib/promise/prioritized_race.h"

#include <memory>

#include "gtest/gtest.h"
#include "src/core/lib/promise/poll.h"

namespace grpc_core {

Poll<int> instant() { return 1; }
Poll<int> never() { return Pending(); }

TEST(PrioritizedRaceTest, Race1) {
  EXPECT_EQ(PrioritizedRace(instant)(), Poll<int>(1));
}

TEST(PrioritizedRaceTest, Race2A) {
  EXPECT_EQ(PrioritizedRace(instant, never)(), Poll<int>(1));
}

TEST(PrioritizedRaceTest, Race2B) {
  EXPECT_EQ(PrioritizedRace(never, instant)(), Poll<int>(1));
}

TEST(PrioritizedRaceTest, PrioritizedCompletion2A) {
  int first_polls = 0;
  int second_polls = 0;
  auto r = PrioritizedRace(
      [&first_polls]() -> Poll<int> {
        ++first_polls;
        return 1;
      },
      [&second_polls]() {
        ++second_polls;
        return 2;
      })();
  EXPECT_EQ(r, Poll<int>(1));

  EXPECT_EQ(first_polls, 1);
  EXPECT_EQ(second_polls, 0);
}

TEST(PrioritizedRaceTest, PrioritizedCompletion2B) {
  int first_polls = 0;
  int second_polls = 0;
  auto r = PrioritizedRace(
      [&first_polls]() -> Poll<int> {
        ++first_polls;
        if (first_polls > 1) return 1;
        return Pending{};
      },
      [&second_polls]() {
        ++second_polls;
        return 2;
      })();
  EXPECT_EQ(r, Poll<int>(1));

  EXPECT_EQ(first_polls, 2);
  EXPECT_EQ(second_polls, 1);
}

TEST(PrioritizedRaceTest, MoveOnlyPromise) {
  auto r = PrioritizedRace(
      [x = std::make_unique<int>(1)]() -> Poll<int> { return Pending{}; },
      [y = std::make_unique<int>(2)]() -> Poll<int> { return Pending{}; });
  EXPECT_EQ(r(), Poll<int>(Pending{}));
}

}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
