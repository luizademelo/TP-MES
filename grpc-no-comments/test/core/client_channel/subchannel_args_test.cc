
// Copyright 2022 gRPC authors.

#include <grpc/impl/channel_arg_names.h>
#include <grpc/support/port_platform.h>

#include <memory>
#include <optional>

#include "gtest/gtest.h"
#include "src/core/client_channel/subchannel.h"
#include "src/core/client_channel/subchannel_pool_interface.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/resolver/endpoint_addresses.h"
#include "test/core/test_util/test_config.h"

namespace grpc_core {
namespace testing {
namespace {

TEST(MakeSubchannelArgs, UsesChannelDefaultAuthorityByDefault) {
  ChannelArgs args = Subchannel::MakeSubchannelArgs(
      ChannelArgs(), ChannelArgs(), nullptr, "foo.example.com");
  EXPECT_EQ(args.GetString(GRPC_ARG_DEFAULT_AUTHORITY), "foo.example.com");
}

TEST(MakeSubchannelArgs, DefaultAuthorityFromChannelArgs) {
  ChannelArgs args = Subchannel::MakeSubchannelArgs(
      ChannelArgs().Set(GRPC_ARG_DEFAULT_AUTHORITY, "bar.example.com"),
      ChannelArgs(), nullptr, "foo.example.com");
  EXPECT_EQ(args.GetString(GRPC_ARG_DEFAULT_AUTHORITY), "bar.example.com");
}

TEST(MakeSubchannelArgs, DefaultAuthorityFromResolver) {
  ChannelArgs args = Subchannel::MakeSubchannelArgs(
      ChannelArgs(),
      ChannelArgs().Set(GRPC_ARG_DEFAULT_AUTHORITY, "bar.example.com"), nullptr,
      "foo.example.com");
  EXPECT_EQ(args.GetString(GRPC_ARG_DEFAULT_AUTHORITY), "bar.example.com");
}

TEST(MakeSubchannelArgs,
     DefaultAuthorityFromChannelArgsOverridesValueFromResolver) {
  ChannelArgs args = Subchannel::MakeSubchannelArgs(
      ChannelArgs().Set(GRPC_ARG_DEFAULT_AUTHORITY, "bar.example.com"),
      ChannelArgs().Set(GRPC_ARG_DEFAULT_AUTHORITY, "baz.example.com"), nullptr,
      "foo.example.com");
  EXPECT_EQ(args.GetString(GRPC_ARG_DEFAULT_AUTHORITY), "bar.example.com");
}

TEST(MakeSubchannelArgs, ArgsFromChannelTrumpPerAddressArgs) {
  ChannelArgs args = Subchannel::MakeSubchannelArgs(ChannelArgs().Set("foo", 1),
                                                    ChannelArgs().Set("foo", 2),
                                                    nullptr, "foo.example.com");
  EXPECT_EQ(args.GetInt("foo"), 1);
}

TEST(MakeSubchannelArgs, StripsOutNoSubchannelArgs) {
  ChannelArgs args = Subchannel::MakeSubchannelArgs(
      ChannelArgs().Set(GRPC_ARG_NO_SUBCHANNEL_PREFIX "foo", 1),
      ChannelArgs().Set(GRPC_ARG_NO_SUBCHANNEL_PREFIX "bar", 1), nullptr,
      "foo.example.com");
  EXPECT_EQ(args.GetString(GRPC_ARG_NO_SUBCHANNEL_PREFIX "foo"), std::nullopt);
  EXPECT_EQ(args.GetString(GRPC_ARG_NO_SUBCHANNEL_PREFIX "bar"), std::nullopt);
}

}
}
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  grpc::testing::TestEnvironment env(&argc, argv);
  auto result = RUN_ALL_TESTS();
  return result;
}
