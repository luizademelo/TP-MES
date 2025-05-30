
// Copyright 2018 gRPC authors.

#include "src/cpp/server/load_reporter/get_cpu_stats.h"

#include <grpc/grpc.h>
#include <grpc/support/port_platform.h>

#include "gtest/gtest.h"
#include "test/core/test_util/port.h"
#include "test/core/test_util/test_config.h"

namespace grpc {
namespace testing {
namespace {

TEST(GetCpuStatsTest, ReadOnce) { grpc::load_reporter::GetCpuStatsImpl(); }

TEST(GetCpuStatsTest, BusyNoLargerThanTotal) {
  auto p = grpc::load_reporter::GetCpuStatsImpl();
  uint64_t busy = p.first;
  uint64_t total = p.second;
  ASSERT_LE(busy, total);
}

TEST(GetCpuStatsTest, Ascending) {
  const size_t kRuns = 100;
  auto prev = grpc::load_reporter::GetCpuStatsImpl();
  for (size_t i = 0; i < kRuns; ++i) {
    auto cur = grpc::load_reporter::GetCpuStatsImpl();
    ASSERT_LE(prev.first, cur.first);
    ASSERT_LE(prev.second, cur.second);
    prev = cur;
  }
}

}
}
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
