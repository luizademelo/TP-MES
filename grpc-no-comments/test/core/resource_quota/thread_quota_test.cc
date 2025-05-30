// Copyright 2021 gRPC authors.

#include "src/core/lib/resource_quota/thread_quota.h"

#include <memory>

#include "gtest/gtest.h"

namespace grpc_core {
namespace testing {

TEST(ThreadQuotaTest, Works) {
  auto q = MakeRefCounted<ThreadQuota>();
  EXPECT_TRUE(q->Reserve(128));
  q->SetMax(10);
  EXPECT_FALSE(q->Reserve(128));
  EXPECT_FALSE(q->Reserve(1));
  q->Release(118);
  EXPECT_FALSE(q->Reserve(1));
  q->Release(1);
  EXPECT_TRUE(q->Reserve(1));
  EXPECT_FALSE(q->Reserve(1));
  q->Release(10);
}

}
}

void grpc_set_default_iomgr_platform() {}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
