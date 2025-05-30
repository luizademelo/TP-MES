
// Copyright 2022 gRPC authors.

#include "src/core/load_balancing/weighted_round_robin/static_stride_scheduler.h"

#include <limits>
#include <optional>
#include <vector>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace grpc_core {
namespace {

using ::testing::ElementsAre;
using ::testing::UnorderedElementsAre;

TEST(StaticStrideSchedulerTest, EmptyWeightsIsNullopt) {
  uint32_t sequence = 0;
  const std::vector<float> weights = {};
  ASSERT_FALSE(StaticStrideScheduler::Make(absl::MakeSpan(weights), [&] {
                 return sequence++;
               }).has_value());
}

TEST(StaticStrideSchedulerTest, OneZeroWeightIsNullopt) {
  uint32_t sequence = 0;
  const std::vector<float> weights = {0};
  ASSERT_FALSE(StaticStrideScheduler::Make(absl::MakeSpan(weights), [&] {
                 return sequence++;
               }).has_value());
}

TEST(StaticStrideSchedulerTest, AllZeroWeightsIsNullopt) {
  uint32_t sequence = 0;
  const std::vector<float> weights = {0, 0, 0, 0};
  ASSERT_FALSE(StaticStrideScheduler::Make(absl::MakeSpan(weights), [&] {
                 return sequence++;
               }).has_value());
}

TEST(StaticStrideSchedulerTest, OneWeightsIsNullopt) {
  uint32_t sequence = 0;
  const std::vector<float> weights = {1};
  ASSERT_FALSE(StaticStrideScheduler::Make(absl::MakeSpan(weights), [&] {
                 return sequence++;
               }).has_value());
}

TEST(StaticStrideSchedulerTest, PicksAreWeightedExactly) {
  uint32_t sequence = 0;
  const std::vector<float> weights = {1, 2, 3};
  const std::optional<StaticStrideScheduler> scheduler =
      StaticStrideScheduler::Make(absl::MakeSpan(weights),
                                  [&] { return sequence++; });
  ASSERT_TRUE(scheduler.has_value());

  std::vector<int> picks(weights.size());
  for (int i = 0; i < 6; ++i) {
    ++picks[scheduler->Pick()];
  }
  EXPECT_THAT(picks, ElementsAre(1, 2, 3));
}

TEST(StaticStrideSchedulerTest, ZeroWeightUsesMean) {
  uint32_t sequence = 0;
  const std::vector<float> weights = {3, 0, 1};
  const std::optional<StaticStrideScheduler> scheduler =
      StaticStrideScheduler::Make(absl::MakeSpan(weights),
                                  [&] { return sequence++; });
  ASSERT_TRUE(scheduler.has_value());

  std::vector<int> picks(weights.size());
  for (int i = 0; i < 6; ++i) {
    ++picks[scheduler->Pick()];
  }
  EXPECT_THAT(picks, ElementsAre(3, 2, 1));
}

TEST(StaticStrideSchedulerTest, AllWeightsEqualIsRoundRobin) {
  uint32_t sequence = 0;
  const std::vector<float> weights = {300, 300, 0};
  const std::optional<StaticStrideScheduler> scheduler =
      StaticStrideScheduler::Make(absl::MakeSpan(weights),
                                  [&] { return sequence++; });
  ASSERT_TRUE(scheduler.has_value());

  std::vector<size_t> picks(weights.size());
  for (int i = 0; i < 3; ++i) {
    picks[i] = scheduler->Pick();
  }

  EXPECT_THAT(picks, UnorderedElementsAre(0, 1, 2));

  for (int i = 0; i < 1000; ++i) {
    EXPECT_EQ(scheduler->Pick(), picks[i % 3]);
  }
}

TEST(StaticStrideSchedulerTest, PicksAreDeterministic) {
  uint32_t sequence = 0;
  const std::vector<float> weights = {1, 2, 3};
  const std::optional<StaticStrideScheduler> scheduler =
      StaticStrideScheduler::Make(absl::MakeSpan(weights),
                                  [&] { return sequence++; });
  ASSERT_TRUE(scheduler.has_value());

  const int n = 100;
  std::vector<size_t> picks;
  picks.reserve(n);
  for (int i = 0; i < n; ++i) {
    picks.push_back(scheduler->Pick());
  }
  for (int i = 0; i < 5; ++i) {
    sequence = 0;
    for (int j = 0; j < n; ++j) {
      EXPECT_EQ(scheduler->Pick(), picks[j]);
    }
  }
}

TEST(StaticStrideSchedulerTest, RebuildGiveSamePicks) {
  uint32_t sequence = 0;
  const std::vector<float> weights = {1, 2, 3};
  const std::optional<StaticStrideScheduler> scheduler =
      StaticStrideScheduler::Make(absl::MakeSpan(weights),
                                  [&] { return sequence++; });
  ASSERT_TRUE(scheduler.has_value());

  const int n = 100;
  std::vector<size_t> picks;
  picks.reserve(n);
  for (int i = 0; i < n; ++i) {
    picks.push_back(scheduler->Pick());
  }

  sequence = 0;
  for (int i = 0; i < n; ++i) {
    const std::optional<StaticStrideScheduler> rebuild =
        StaticStrideScheduler::Make(absl::MakeSpan(weights),
                                    [&] { return sequence++; });
    ASSERT_TRUE(rebuild.has_value());

    EXPECT_EQ(rebuild->Pick(), picks[i]);
  }
}

TEST(StaticStrideSchedulerTest, LargestIsPickedEveryGeneration) {
  uint32_t sequence = 0;
  const std::vector<float> weights = {1, 2, 3};
  const int mean = 2;
  const std::optional<StaticStrideScheduler> scheduler =
      StaticStrideScheduler::Make(absl::MakeSpan(weights),
                                  [&] { return sequence++; });
  ASSERT_TRUE(scheduler.has_value());

  const int kMaxWeight = std::numeric_limits<uint16_t>::max();
  int largest_weight_pick_count = 0;
  for (int i = 0; i < kMaxWeight * mean; ++i) {
    if (scheduler->Pick() == 2) {
      ++largest_weight_pick_count;
    }
  }
  EXPECT_EQ(largest_weight_pick_count, kMaxWeight);
}

TEST(StaticStrideSchedulerTest, MaxIsClampedForHighRatio) {
  uint32_t sequence = 0;
  const std::vector<float> weights{81, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                   1,  1, 1, 1, 1, 1, 1, 1, 1, 1};
  const std::optional<StaticStrideScheduler> scheduler =
      StaticStrideScheduler::Make(absl::MakeSpan(weights),
                                  [&] { return sequence++; });
  ASSERT_TRUE(scheduler.has_value());

  std::vector<int> picks(weights.size());
  for (int i = 0; i < 69; ++i) {
    ++picks[scheduler->Pick()];
  }
  EXPECT_THAT(picks, ElementsAre(50, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                 1, 1, 1, 1, 1));
}

TEST(StaticStrideSchedulerTest, MinIsClampedForHighRatio) {
  uint32_t sequence = 0;
  const std::vector<float> weights{100, 1e-10};
  const std::optional<StaticStrideScheduler> scheduler =
      StaticStrideScheduler::Make(absl::MakeSpan(weights),
                                  [&] { return sequence++; });
  ASSERT_TRUE(scheduler.has_value());

  std::vector<int> picks(weights.size());
  for (int i = 0; i < 201; ++i) {
    ++picks[scheduler->Pick()];
  }
  EXPECT_THAT(picks, ElementsAre(200, 1));
}

}
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
