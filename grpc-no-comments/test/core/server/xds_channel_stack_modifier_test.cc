
// Copyright 2021 gRPC authors.

#include "src/core/server/xds_channel_stack_modifier.h"

#include <grpc/grpc.h>

#include <algorithm>
#include <string>

#include "gtest/gtest.h"
#include "src/core/config/core_configuration.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/channel/channel_stack.h"
#include "src/core/lib/channel/channel_stack_builder_impl.h"
#include "src/core/lib/iomgr/endpoint.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/iomgr/iomgr_fwd.h"
#include "src/core/lib/surface/channel_init.h"
#include "src/core/lib/surface/channel_stack_type.h"
#include "src/core/lib/transport/transport.h"
#include "test/core/test_util/test_config.h"

namespace grpc_core {
namespace testing {
namespace {

TEST(XdsChannelStackModifierTest, CopyChannelArgs) {
  grpc_init();
  auto channel_stack_modifier = MakeRefCounted<XdsChannelStackModifier>(
      std::vector<const grpc_channel_filter*>{});
  grpc_arg arg = channel_stack_modifier->MakeChannelArg();
  grpc_channel_args* args = grpc_channel_args_copy_and_add(nullptr, &arg, 1);
  EXPECT_EQ(channel_stack_modifier,
            XdsChannelStackModifier::GetFromChannelArgs(*args));
  grpc_channel_args_destroy(args);
  grpc_shutdown();
}

TEST(XdsChannelStackModifierTest, ChannelArgsCompare) {
  grpc_init();
  auto channel_stack_modifier = MakeRefCounted<XdsChannelStackModifier>(
      std::vector<const grpc_channel_filter*>{});
  grpc_arg arg = channel_stack_modifier->MakeChannelArg();
  grpc_channel_args* args = grpc_channel_args_copy_and_add(nullptr, &arg, 1);
  grpc_channel_args* new_args = grpc_channel_args_copy(args);
  EXPECT_EQ(XdsChannelStackModifier::GetFromChannelArgs(*new_args),
            XdsChannelStackModifier::GetFromChannelArgs(*args));
  grpc_channel_args_destroy(args);
  grpc_channel_args_destroy(new_args);
  grpc_shutdown();
}

const UniqueTypeName kTestFilter1 = GRPC_UNIQUE_TYPE_NAME_HERE("test_filter_1");
const UniqueTypeName kTestFilter2 = GRPC_UNIQUE_TYPE_NAME_HERE("test_filter_2");

namespace {
class FakeTransport final : public Transport {
 public:
  FilterStackTransport* filter_stack_transport() override { return nullptr; }
  ClientTransport* client_transport() override { return nullptr; }
  ServerTransport* server_transport() override { return nullptr; }

  absl::string_view GetTransportName() const override { return "fake"; }
  void SetPollset(grpc_stream*, grpc_pollset*) override {}
  void SetPollsetSet(grpc_stream*, grpc_pollset_set*) override {}
  void PerformOp(grpc_transport_op*) override {}
  void Orphan() override {}
  RefCountedPtr<channelz::SocketNode> GetSocketNode() const override {
    return nullptr;
  }
};
}

TEST(XdsChannelStackModifierTest, XdsHttpFiltersInsertion) {
  CoreConfiguration::
      ResetEverythingIncludingPersistentBuildersAbsolutelyNotRecommended();
  grpc_init();

  const grpc_channel_filter test_filter_1 = {
      nullptr, nullptr, 0,       nullptr, nullptr, nullptr,
      0,       nullptr, nullptr, nullptr, nullptr, kTestFilter1};
  const grpc_channel_filter test_filter_2 = {
      nullptr, nullptr, 0,       nullptr, nullptr, nullptr,
      0,       nullptr, nullptr, nullptr, nullptr, kTestFilter2};
  auto channel_stack_modifier = MakeRefCounted<XdsChannelStackModifier>(
      std::vector<const grpc_channel_filter*>{&test_filter_1, &test_filter_2});
  grpc_arg arg = channel_stack_modifier->MakeChannelArg();
  FakeTransport fake_transport;

  grpc_channel_args* args = grpc_channel_args_copy_and_add(nullptr, &arg, 1);
  ChannelStackBuilderImpl builder(
      "test", GRPC_SERVER_CHANNEL,
      ChannelArgs::FromC(args).SetObject<Transport>(&fake_transport));
  grpc_channel_args_destroy(args);

  {
    ExecCtx exec_ctx;
    ASSERT_TRUE(CoreConfiguration::Get().channel_init().CreateStack(&builder));
  }
  std::vector<std::string> filters;
  for (const auto& entry : *builder.mutable_stack()) {
    filters.push_back(std::string(entry->name.name()));
  }
  filters.resize(3);
  EXPECT_EQ(filters, std::vector<std::string>(
                         {"server", std::string(kTestFilter1.name()),
                          std::string(kTestFilter2.name())}));
  grpc_shutdown();
}

}
}
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  grpc::testing::TestEnvironment env(&argc, argv);
  int ret = RUN_ALL_TESTS();
  return ret;
}
