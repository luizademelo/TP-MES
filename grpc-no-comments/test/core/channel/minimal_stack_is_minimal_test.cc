
// Copyright 2017 gRPC authors.

#include <grpc/grpc.h>
#include <grpc/impl/channel_arg_names.h>

#include <algorithm>
#include <memory>
#include <string>
#include <vector>

#include "absl/log/check.h"
#include "absl/memory/memory.h"
#include "absl/strings/string_view.h"
#include "gtest/gtest.h"
#include "src/core/config/core_configuration.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/channel/channel_stack.h"
#include "src/core/lib/channel/channel_stack_builder_impl.h"
#include "src/core/lib/experiments/experiments.h"
#include "src/core/lib/iomgr/endpoint.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/iomgr/iomgr_fwd.h"
#include "src/core/lib/surface/channel_init.h"
#include "src/core/lib/surface/channel_stack_type.h"
#include "src/core/lib/transport/transport.h"
#include "test/core/test_util/test_config.h"

namespace {
class FakeTransport final : public grpc_core::Transport {
 public:
  explicit FakeTransport(absl::string_view transport_name)
      : transport_name_(transport_name) {}

  grpc_core::FilterStackTransport* filter_stack_transport() override {
    return nullptr;
  }
  grpc_core::ClientTransport* client_transport() override { return nullptr; }
  grpc_core::ServerTransport* server_transport() override { return nullptr; }

  absl::string_view GetTransportName() const override {
    return transport_name_;
  }
  void SetPollset(grpc_stream*, grpc_pollset*) override {}
  void SetPollsetSet(grpc_stream*, grpc_pollset_set*) override {}
  void PerformOp(grpc_transport_op*) override {}
  void Orphan() override {}
  grpc_core::RefCountedPtr<grpc_core::channelz::SocketNode> GetSocketNode()
      const override {
    return nullptr;
  }

 private:
  absl::string_view transport_name_;
};
}

std::vector<std::string> MakeStack(const char* transport_name,
                                   grpc_core::ChannelArgs channel_args,
                                   grpc_channel_stack_type channel_stack_type) {

  std::unique_ptr<FakeTransport> fake_transport;
  if (transport_name != nullptr) {
    fake_transport = absl::make_unique<FakeTransport>(transport_name);
    channel_args = channel_args.SetObject(fake_transport.get());
  }
  grpc_core::ChannelStackBuilderImpl builder("test", channel_stack_type,
                                             channel_args);
  builder.SetTarget("foo.test.google.fr");
  {
    grpc_core::ExecCtx exec_ctx;
    CHECK(grpc_core::CoreConfiguration::Get().channel_init().CreateStack(
        &builder));
  }

  std::vector<std::string> parts;
  for (const auto& entry : *builder.mutable_stack()) {
    parts.push_back(std::string(entry->name.name()));
  }

  return parts;
}

TEST(ChannelStackFilters, LooksAsExpected) {
  const auto minimal_stack_args =
      grpc_core::ChannelArgs().Set(GRPC_ARG_MINIMAL_STACK, true);
  const auto no_args = grpc_core::ChannelArgs();

  EXPECT_EQ(
      MakeStack("unknown", minimal_stack_args, GRPC_CLIENT_DIRECT_CHANNEL),
      std::vector<std::string>({"authority", "connected"}));
  EXPECT_EQ(MakeStack("unknown", minimal_stack_args, GRPC_CLIENT_SUBCHANNEL),
            std::vector<std::string>({"authority", "connected"}));
  EXPECT_EQ(
      MakeStack("unknown", minimal_stack_args, GRPC_SERVER_CHANNEL),
      std::vector<std::string>({"server", "server_call_tracer", "connected"}));

  EXPECT_EQ(MakeStack("chttp2", minimal_stack_args, GRPC_CLIENT_DIRECT_CHANNEL),
            std::vector<std::string>(
                {"authority", "http-client", "compression", "connected"}));
  EXPECT_EQ(MakeStack("chttp2", minimal_stack_args, GRPC_CLIENT_SUBCHANNEL),
            std::vector<std::string>(
                {"authority", "http-client", "compression", "connected"}));
  EXPECT_EQ(MakeStack("chttp2", minimal_stack_args, GRPC_SERVER_CHANNEL),
            std::vector<std::string>({"server", "http-server", "compression",
                                      "server_call_tracer", "connected"}));
  EXPECT_EQ(MakeStack(nullptr, minimal_stack_args, GRPC_CLIENT_CHANNEL),
            std::vector<std::string>({"client-channel"}));

  EXPECT_EQ(
      MakeStack("unknown", no_args, GRPC_CLIENT_DIRECT_CHANNEL),
      std::vector<std::string>({"authority", "message_size", "connected"}));
  EXPECT_EQ(
      MakeStack("unknown", no_args, GRPC_CLIENT_SUBCHANNEL),
      std::vector<std::string>({"authority", "message_size", "connected"}));
  EXPECT_EQ(MakeStack("unknown", no_args, GRPC_SERVER_CHANNEL),
            std::vector<std::string>(
                {"server", "message_size", "server_call_tracer", "connected"}));

  EXPECT_EQ(
      MakeStack("chttp2", no_args, GRPC_CLIENT_DIRECT_CHANNEL),
      std::vector<std::string>({"authority", "message_size", "http-client",
                                "compression", "connected"}));
  EXPECT_EQ(
      MakeStack("chttp2", no_args, GRPC_CLIENT_SUBCHANNEL),
      std::vector<std::string>({"authority", "message_size", "http-client",
                                "compression", "connected"}));

  EXPECT_EQ(MakeStack("chttp2", no_args, GRPC_SERVER_CHANNEL),
            std::vector<std::string>({"server", "message_size", "http-server",
                                      "compression", "server_call_tracer",
                                      "connected"}));
  EXPECT_EQ(MakeStack(nullptr, no_args, GRPC_CLIENT_CHANNEL),
            std::vector<std::string>({"client_idle", "client-channel"}));
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  grpc_init();
  int r = RUN_ALL_TESTS();
  grpc_shutdown();
  return r;
}
