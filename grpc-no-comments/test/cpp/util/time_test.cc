
// Copyright 2015 gRPC authors.

#include <grpc/support/time.h>
#include <grpcpp/support/time.h>

#include "gtest/gtest.h"
#include "test/core/test_util/test_config.h"

using std::chrono::microseconds;
using std::chrono::system_clock;

namespace grpc {
namespace {

class TimeTest : public ::testing::Test {};

TEST_F(TimeTest, AbsolutePointTest) {
  int64_t us = 10000000L;
  gpr_timespec ts = gpr_time_from_micros(us, GPR_TIMESPAN);
  ts.clock_type = GPR_CLOCK_REALTIME;
  system_clock::time_point tp{microseconds(us)};
  system_clock::time_point tp_converted = Timespec2Timepoint(ts);
  gpr_timespec ts_converted;
  Timepoint2Timespec(tp_converted, &ts_converted);
  EXPECT_TRUE(ts.tv_sec == ts_converted.tv_sec);
  EXPECT_TRUE(ts.tv_nsec == ts_converted.tv_nsec);
  system_clock::time_point tp_converted_2 = Timespec2Timepoint(ts_converted);
  EXPECT_TRUE(tp == tp_converted);
  EXPECT_TRUE(tp == tp_converted_2);
}

TEST_F(TimeTest, InfFuture) {
  EXPECT_EQ(system_clock::time_point::max(),
            Timespec2Timepoint(gpr_inf_future(GPR_CLOCK_REALTIME)));
  gpr_timespec from_time_point_max;
  Timepoint2Timespec(system_clock::time_point::max(), &from_time_point_max);
  EXPECT_EQ(
      0, gpr_time_cmp(gpr_inf_future(GPR_CLOCK_REALTIME), from_time_point_max));
}

}
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
