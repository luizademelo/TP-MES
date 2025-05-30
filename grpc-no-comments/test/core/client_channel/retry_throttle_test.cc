
// Copyright 2018 gRPC authors.

#include "src/core/client_channel/retry_throttle.h"

#include "gtest/gtest.h"
#include "test/core/test_util/test_config.h"

namespace grpc_core {
namespace internal {
namespace {

TEST(ServerRetryThrottleData, Basic) {

  auto throttle_data =
      MakeRefCounted<ServerRetryThrottleData>(4000, 1600, 4000);

  EXPECT_TRUE(throttle_data->RecordFailure());

  throttle_data->RecordSuccess();

  EXPECT_TRUE(throttle_data->RecordFailure());

  EXPECT_FALSE(throttle_data->RecordFailure());

  EXPECT_FALSE(throttle_data->RecordFailure());

  EXPECT_FALSE(throttle_data->RecordFailure());

  EXPECT_FALSE(throttle_data->RecordFailure());

  throttle_data->RecordSuccess();

  throttle_data->RecordSuccess();

  EXPECT_TRUE(throttle_data->RecordFailure());

  EXPECT_FALSE(throttle_data->RecordFailure());

  throttle_data->RecordSuccess();

  EXPECT_FALSE(throttle_data->RecordFailure());

  throttle_data->RecordSuccess();

  EXPECT_TRUE(throttle_data->RecordFailure());
}

TEST(ServerRetryThrottleMap, Replacement) {
  const std::string kServerName = "server_name";

  auto old_throttle_data =
      ServerRetryThrottleMap::Get()->GetDataForServer(kServerName, 4000, 1000);
  EXPECT_EQ(old_throttle_data->max_milli_tokens(), 4000);
  EXPECT_EQ(old_throttle_data->milli_token_ratio(), 1000);
  EXPECT_EQ(old_throttle_data->milli_tokens(), 4000);

  EXPECT_TRUE(old_throttle_data->RecordFailure());

  auto throttle_data =
      ServerRetryThrottleMap::Get()->GetDataForServer(kServerName, 4000, 1000);
  EXPECT_EQ(old_throttle_data, throttle_data);

  throttle_data =
      ServerRetryThrottleMap::Get()->GetDataForServer(kServerName, 10000, 3000);
  EXPECT_NE(old_throttle_data, throttle_data);
  EXPECT_EQ(throttle_data->max_milli_tokens(), 10000);
  EXPECT_EQ(throttle_data->milli_token_ratio(), 3000);
  EXPECT_EQ(throttle_data->milli_tokens(), 7500);

  EXPECT_TRUE(old_throttle_data->RecordFailure());

  EXPECT_TRUE(old_throttle_data->RecordFailure());

  EXPECT_FALSE(old_throttle_data->RecordFailure());

  EXPECT_FALSE(throttle_data->RecordFailure());

  throttle_data->RecordSuccess();

  EXPECT_TRUE(old_throttle_data->RecordFailure());

  EXPECT_FALSE(throttle_data->RecordFailure());
}

}
}
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
