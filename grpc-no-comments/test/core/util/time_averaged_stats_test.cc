
// Copyright 2015 gRPC authors.

#include "src/core/util/time_averaged_stats.h"

#include <math.h>

#include "gtest/gtest.h"

namespace grpc_core {
namespace {

TEST(TimeAveragedStatsTest, NoRegressNoPersistTest1) {
  TimeAveragedStats tas(1000, 0, 0.0);
  EXPECT_DOUBLE_EQ(1000, tas.aggregate_weighted_avg());
  EXPECT_DOUBLE_EQ(0, tas.aggregate_total_weight());

  tas.UpdateAverage();
  EXPECT_DOUBLE_EQ(1000, tas.aggregate_weighted_avg());
  EXPECT_DOUBLE_EQ(0, tas.aggregate_total_weight());

  tas.AddSample(2000);
  tas.UpdateAverage();
  EXPECT_DOUBLE_EQ(2000, tas.aggregate_weighted_avg());
  EXPECT_DOUBLE_EQ(1, tas.aggregate_total_weight());
}

TEST(TimeAveragedStatsTest, NoRegressNoPersistTest2) {
  TimeAveragedStats tas(1000, 0, 0.0);
  EXPECT_DOUBLE_EQ(1000, tas.aggregate_weighted_avg());

  tas.AddSample(2000);
  tas.UpdateAverage();
  EXPECT_DOUBLE_EQ(2000, tas.aggregate_weighted_avg());
  EXPECT_DOUBLE_EQ(1, tas.aggregate_total_weight());

  tas.AddSample(3000);
  tas.UpdateAverage();
  EXPECT_DOUBLE_EQ(3000, tas.aggregate_weighted_avg());
  EXPECT_DOUBLE_EQ(1, tas.aggregate_total_weight());
}

TEST(TimeAveragedStatsTest, NoRegressNoPersistTest3) {
  TimeAveragedStats tas(1000, 0, 0.0);
  EXPECT_DOUBLE_EQ(1000, tas.aggregate_weighted_avg());

  tas.AddSample(2500);
  tas.UpdateAverage();
  EXPECT_DOUBLE_EQ(2500, tas.aggregate_weighted_avg());
  EXPECT_DOUBLE_EQ(1, tas.aggregate_total_weight());

  tas.AddSample(3500);
  tas.AddSample(4500);
  tas.UpdateAverage();
  EXPECT_DOUBLE_EQ(4000, tas.aggregate_weighted_avg());
  EXPECT_DOUBLE_EQ(2, tas.aggregate_total_weight());
}

TEST(TimeAveragedStatsTest, SomeRegressNoPersistTest) {
  TimeAveragedStats tas(1000, 0.5, 0.0);
  EXPECT_DOUBLE_EQ(1000, tas.aggregate_weighted_avg());
  EXPECT_DOUBLE_EQ(0, tas.aggregate_total_weight());
  tas.AddSample(2000);
  tas.AddSample(2000);
  tas.UpdateAverage();

  EXPECT_DOUBLE_EQ(1800, tas.aggregate_weighted_avg());
  EXPECT_DOUBLE_EQ(2.5, tas.aggregate_total_weight());
}

TEST(TimeAveragedStatsTest, SomeDecayTest) {
  TimeAveragedStats tas(1000, 1, 0.0);
  EXPECT_EQ(1000, tas.aggregate_weighted_avg());

  tas.AddSample(2000);
  tas.UpdateAverage();
  EXPECT_DOUBLE_EQ(1500, tas.aggregate_weighted_avg());
  EXPECT_DOUBLE_EQ(2, tas.aggregate_total_weight());

  tas.AddSample(2000);
  tas.UpdateAverage();
  EXPECT_DOUBLE_EQ(1500, tas.aggregate_weighted_avg());
  EXPECT_DOUBLE_EQ(2, tas.aggregate_total_weight());

  tas.AddSample(2000);
  tas.UpdateAverage();
  EXPECT_DOUBLE_EQ(1500, tas.aggregate_weighted_avg());
  EXPECT_DOUBLE_EQ(2, tas.aggregate_total_weight());
}

TEST(TimeAveragedStatsTest, NoRegressFullPersistTest) {
  TimeAveragedStats tas(1000, 0, 1.0);
  EXPECT_DOUBLE_EQ(1000, tas.aggregate_weighted_avg());
  EXPECT_DOUBLE_EQ(0, tas.aggregate_total_weight());

  tas.AddSample(2000);
  tas.UpdateAverage();
  EXPECT_EQ(2000, tas.aggregate_weighted_avg());
  EXPECT_EQ(1, tas.aggregate_total_weight());

  tas.AddSample(2300);
  tas.AddSample(2300);
  tas.UpdateAverage();
  EXPECT_DOUBLE_EQ(2200, tas.aggregate_weighted_avg());
  EXPECT_DOUBLE_EQ(3, tas.aggregate_total_weight());
}

TEST(TimeAveragedStatsTest, NoRegressSomePersistTest) {
  TimeAveragedStats tas(1000, 0, 0.5);

  tas.AddSample(2000);
  tas.UpdateAverage();
  EXPECT_DOUBLE_EQ(2000, tas.aggregate_weighted_avg());
  EXPECT_DOUBLE_EQ(1, tas.aggregate_total_weight());

  tas.AddSample(2500);
  tas.AddSample(4000);
  tas.UpdateAverage();
  EXPECT_DOUBLE_EQ(3000, tas.aggregate_weighted_avg());
  EXPECT_DOUBLE_EQ(2.5, tas.aggregate_total_weight());
}

TEST(TimeAveragedStatsTest, SomeRegressSomePersistTest) {
  TimeAveragedStats tas(1000, 0.4, 0.6);

  EXPECT_EQ(1000, tas.aggregate_weighted_avg());
  EXPECT_EQ(0, tas.aggregate_total_weight());

  tas.UpdateAverage();

  EXPECT_DOUBLE_EQ(1000, tas.aggregate_weighted_avg());
  EXPECT_DOUBLE_EQ(0.4, tas.aggregate_total_weight());

  tas.AddSample(2640);
  tas.UpdateAverage();

  EXPECT_DOUBLE_EQ(2000, tas.aggregate_weighted_avg());
  EXPECT_DOUBLE_EQ(1.64, tas.aggregate_total_weight());

  tas.AddSample(2876.8);
  tas.UpdateAverage();

  EXPECT_DOUBLE_EQ(2200, tas.aggregate_weighted_avg());
  EXPECT_DOUBLE_EQ(2.384, tas.aggregate_total_weight());

  tas.AddSample(4944.32);
  tas.UpdateAverage();

  EXPECT_DOUBLE_EQ(3000, tas.aggregate_weighted_avg());
  EXPECT_DOUBLE_EQ(2.8304, tas.aggregate_total_weight());
}

}
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
