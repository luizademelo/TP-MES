// Copyright 2021 gRPC authors.

#include "src/core/lib/resource_quota/resource_quota.h"

#include "gtest/gtest.h"
#include "test/core/test_util/test_config.h"

namespace grpc_core {
namespace testing {

TEST(ResourceQuotaTest, Works) {
  auto q = MakeRefCounted<ResourceQuota>("foo");
  EXPECT_NE(q->thread_quota(), nullptr);
  EXPECT_NE(q->memory_quota(), nullptr);
}

}
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment give_me_a_name(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
