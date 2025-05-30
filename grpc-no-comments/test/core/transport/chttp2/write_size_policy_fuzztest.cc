// Copyright 2023 gRPC authors.

#include <vector>

#include "fuzztest/fuzztest.h"
#include "gtest/gtest.h"
#include "src/core/ext/transport/chttp2/transport/write_size_policy.h"

namespace grpc_core {

struct OneWrite {
  uint16_t delay_start;
  uint32_t size;
  uint16_t write_time;
  bool success;
};

void WriteSizePolicyStaysWithinBounds(std::vector<OneWrite> ops) {
  ScopedTimeCache time_cache;
  uint32_t now = 100;
  Chttp2WriteSizePolicy policy;
  for (const OneWrite op : ops) {
    const auto start_target = policy.WriteTargetSize();
    now += op.delay_start;
    time_cache.TestOnlySetNow(Timestamp::ProcessEpoch() +
                              Duration::Milliseconds(now));
    policy.BeginWrite(op.size);
    now += op.write_time;
    time_cache.TestOnlySetNow(Timestamp::ProcessEpoch() +
                              Duration::Milliseconds(now));
    policy.EndWrite(op.success);
    if (op.size >= start_target * 7 / 10) {
      if (op.write_time < Chttp2WriteSizePolicy::FastWrite().millis()) {
        EXPECT_GE(policy.WriteTargetSize(), start_target);
        EXPECT_LE(policy.WriteTargetSize(), start_target * 3 / 2);
      } else if (op.write_time > Chttp2WriteSizePolicy::SlowWrite().millis()) {
        EXPECT_LE(policy.WriteTargetSize(), start_target);
        EXPECT_GE(policy.WriteTargetSize(), start_target / 3);
      }
    } else {
      EXPECT_EQ(policy.WriteTargetSize(), start_target);
    }
    EXPECT_GE(policy.WriteTargetSize(), Chttp2WriteSizePolicy::MinTarget());
    EXPECT_LE(policy.WriteTargetSize(), Chttp2WriteSizePolicy::MaxTarget());
  }
}
FUZZ_TEST(MyTestSuite, WriteSizePolicyStaysWithinBounds);

}
