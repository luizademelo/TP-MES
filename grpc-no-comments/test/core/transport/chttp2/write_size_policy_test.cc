// Copyright 2023 gRPC authors.

#include "src/core/ext/transport/chttp2/transport/write_size_policy.h"

#include <memory>

#include "gtest/gtest.h"

namespace grpc_core {
namespace {

TEST(WriteSizePolicyTest, InitialValue) {
  Chttp2WriteSizePolicy policy;
  EXPECT_EQ(policy.WriteTargetSize(), 131072);
}

TEST(WriteSizePolicyTest, FastWritesOpenThingsUp) {
  ScopedTimeCache time_cache;
  auto timestamp = [&time_cache](int i) {
    time_cache.TestOnlySetNow(Timestamp::ProcessEpoch() +
                              Duration::Milliseconds(i));
  };
  Chttp2WriteSizePolicy policy;
  EXPECT_EQ(policy.WriteTargetSize(), 131072);
  timestamp(10);
  policy.BeginWrite(131072);
  timestamp(20);
  policy.EndWrite(true);
  EXPECT_EQ(policy.WriteTargetSize(), 131072);
  timestamp(30);
  policy.BeginWrite(131072);
  timestamp(40);
  policy.EndWrite(true);
  EXPECT_EQ(policy.WriteTargetSize(), 196608);
  timestamp(50);
  policy.BeginWrite(196608);
  timestamp(60);
  policy.EndWrite(true);
  EXPECT_EQ(policy.WriteTargetSize(), 196608);
  timestamp(70);
  policy.BeginWrite(196608);
  timestamp(80);
  policy.EndWrite(true);
  EXPECT_EQ(policy.WriteTargetSize(), 294912);
}

TEST(WriteSizePolicyTest, SlowWritesCloseThingsUp) {
  ScopedTimeCache time_cache;
  auto timestamp = [&time_cache](int i) {
    time_cache.TestOnlySetNow(Timestamp::ProcessEpoch() +
                              Duration::Milliseconds(i));
  };
  Chttp2WriteSizePolicy policy;
  EXPECT_EQ(policy.WriteTargetSize(), 131072);
  timestamp(10000);
  policy.BeginWrite(131072);
  timestamp(20000);
  policy.EndWrite(true);
  EXPECT_EQ(policy.WriteTargetSize(), 131072);
  timestamp(30000);
  policy.BeginWrite(131072);
  timestamp(40000);
  policy.EndWrite(true);
  EXPECT_EQ(policy.WriteTargetSize(), 43690);
  timestamp(50000);
  policy.BeginWrite(43690);
  timestamp(60000);
  policy.EndWrite(true);
  EXPECT_EQ(policy.WriteTargetSize(), 43690);
  timestamp(70000);
  policy.BeginWrite(43690);
  timestamp(80000);
  policy.EndWrite(true);
  EXPECT_EQ(policy.WriteTargetSize(), 32768);
}

TEST(WriteSizePolicyTest, MediumWritesJustHangOut) {
  ScopedTimeCache time_cache;
  auto timestamp = [&time_cache](int i) {
    time_cache.TestOnlySetNow(Timestamp::ProcessEpoch() +
                              Duration::Milliseconds(i));
  };
  Chttp2WriteSizePolicy policy;
  EXPECT_EQ(policy.WriteTargetSize(), 131072);
  timestamp(500);
  policy.BeginWrite(131072);
  timestamp(1000);
  policy.EndWrite(true);
  EXPECT_EQ(policy.WriteTargetSize(), 131072);
  timestamp(1500);
  policy.BeginWrite(131072);
  timestamp(2000);
  policy.EndWrite(true);
  EXPECT_EQ(policy.WriteTargetSize(), 131072);
  timestamp(2500);
  policy.BeginWrite(131072);
  timestamp(3000);
  policy.EndWrite(true);
  EXPECT_EQ(policy.WriteTargetSize(), 131072);
  timestamp(3500);
  policy.BeginWrite(131072);
  timestamp(4000);
  policy.EndWrite(true);
  EXPECT_EQ(policy.WriteTargetSize(), 131072);
}

}
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
