// Copyright 2021 The gRPC Authors

#include <grpc/support/port_platform.h>

#include <memory>
#include <optional>

#include "gtest/gtest.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/event_engine/channel_args_endpoint_config.h"

using ::grpc_event_engine::experimental::ChannelArgsEndpointConfig;

TEST(EndpointConfigTest, CanSRetrieveValuesFromChannelArgs) {
  grpc_core::ChannelArgs args;
  args = args.Set("arst", 3);
  ChannelArgsEndpointConfig config(args);
  EXPECT_EQ(*config.GetInt("arst"), 3);
}

TEST(EndpointConfigTest, ReturnsNoValueForMissingKeys) {
  ChannelArgsEndpointConfig config;
  EXPECT_TRUE(!config.GetInt("nonexistent").has_value());
  EXPECT_TRUE(!config.GetString("nonexistent").has_value());
  EXPECT_EQ(config.GetVoidPointer("nonexistent"), nullptr);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  auto result = RUN_ALL_TESTS();
  return result;
}
