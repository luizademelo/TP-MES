
// Copyright 2016 gRPC authors.

#include "src/core/lib/transport/bdp_estimator.h"

#include <grpc/grpc.h>
#include <stdlib.h>

#include <algorithm>
#include <atomic>

#include "gtest/gtest.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/iomgr/timer_manager.h"
#include "test/core/test_util/test_config.h"

extern gpr_timespec (*gpr_now_impl)(gpr_clock_type clock_type);

namespace grpc_core {
namespace testing {
namespace {
std::atomic<int> g_clock{123};

gpr_timespec fake_gpr_now(gpr_clock_type clock_type) {
  gpr_timespec ts;
  ts.tv_sec = g_clock.load();
  ts.tv_nsec = 0;
  ts.clock_type = clock_type;
  return ts;
}

void inc_time(void) { g_clock.fetch_add(30); }
}

TEST(BdpEstimatorTest, NoOp) { BdpEstimator est("test"); }

TEST(BdpEstimatorTest, EstimateBdpNoSamples) {
  BdpEstimator est("test");
  est.EstimateBdp();
}

namespace {
void AddSamples(BdpEstimator* estimator, int64_t* samples, size_t n) {
  estimator->AddIncomingBytes(1234567);
  inc_time();
  ExecCtx exec_ctx;
  estimator->SchedulePing();
  estimator->StartPing();
  for (size_t i = 0; i < n; i++) {
    estimator->AddIncomingBytes(samples[i]);
  }
  gpr_sleep_until(gpr_time_add(gpr_now(GPR_CLOCK_REALTIME),
                               gpr_time_from_millis(1, GPR_TIMESPAN)));
  ExecCtx::Get()->InvalidateNow();
  estimator->CompletePing();
}

void AddSample(BdpEstimator* estimator, int64_t sample) {
  AddSamples(estimator, &sample, 1);
}
}

TEST(BdpEstimatorTest, GetEstimate1Sample) {
  BdpEstimator est("test");
  AddSample(&est, 100);
  est.EstimateBdp();
}

TEST(BdpEstimatorTest, GetEstimate2Samples) {
  BdpEstimator est("test");
  AddSample(&est, 100);
  AddSample(&est, 100);
  est.EstimateBdp();
}

TEST(BdpEstimatorTest, GetEstimate3Samples) {
  BdpEstimator est("test");
  AddSample(&est, 100);
  AddSample(&est, 100);
  AddSample(&est, 100);
  est.EstimateBdp();
}

namespace {
int64_t NextPow2(int64_t v) {
  v--;
  v |= v >> 1;
  v |= v >> 2;
  v |= v >> 4;
  v |= v >> 8;
  v |= v >> 16;
  v |= v >> 32;
  v++;
  return v;
}
}

class BdpEstimatorRandomTest : public ::testing::TestWithParam<size_t> {};

TEST_P(BdpEstimatorRandomTest, GetEstimateRandomValues) {
  BdpEstimator est("test");
  const int kMaxSample = 65535;
  int min = kMaxSample;
  int max = 0;
  for (size_t i = 0; i < GetParam(); i++) {
    int sample = rand() % (kMaxSample + 1);
    if (sample < min) min = sample;
    if (sample > max) max = sample;
    AddSample(&est, sample);
    if (i >= 3) {
      EXPECT_LE(est.EstimateBdp(), std::max(int64_t(65536), 2 * NextPow2(max)))
          << " min:" << min << " max:" << max << " sample:" << sample;
    }
  }
}

INSTANTIATE_TEST_SUITE_P(TooManyNames, BdpEstimatorRandomTest,
                         ::testing::Values(3, 4, 6, 9, 13, 19, 28, 42, 63, 94,
                                           141, 211, 316, 474, 711));

}
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  gpr_now_impl = grpc_core::testing::fake_gpr_now;
  grpc_init();
  grpc_timer_manager_set_threading(false);
  ::testing::InitGoogleTest(&argc, argv);
  int ret = RUN_ALL_TESTS();
  grpc_shutdown();
  return ret;
}
