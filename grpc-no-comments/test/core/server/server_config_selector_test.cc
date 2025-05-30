
// Copyright 2021 gRPC authors.

#include "src/core/server/server_config_selector.h"

#include <grpc/grpc.h>

#include "absl/status/status.h"
#include "gtest/gtest.h"
#include "src/core/lib/channel/channel_args.h"
#include "test/core/test_util/test_config.h"

namespace grpc_core {
namespace testing {
namespace {

class TestServerConfigSelectorProvider : public ServerConfigSelectorProvider {
  absl::StatusOr<RefCountedPtr<ServerConfigSelector>> Watch(
      std::unique_ptr<ServerConfigSelectorWatcher> ) override {
    return absl::UnavailableError("Test ServerConfigSelector");
  }

  void Orphaned() override {}

  void CancelWatch() override {}
};

TEST(ServerConfigSelectorProviderTest, CopyChannelArgs) {
  RefCountedPtr<ServerConfigSelectorProvider> server_config_selector_provider =
      MakeRefCounted<TestServerConfigSelectorProvider>();
  auto args = ChannelArgs().SetObject(server_config_selector_provider);
  EXPECT_EQ(server_config_selector_provider,
            args.GetObject<ServerConfigSelectorProvider>());
}

TEST(ServerConfigSelectorProviderTest, ChannelArgsCompare) {
  auto server_config_selector_provider =
      MakeRefCounted<TestServerConfigSelectorProvider>();
  auto args = ChannelArgs().SetObject(server_config_selector_provider);
  auto args2 = ChannelArgs().SetObject(server_config_selector_provider);
  EXPECT_EQ(args, args2);
}

}
}
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  grpc::testing::TestEnvironment env(&argc, argv);
  grpc_init();
  int ret = RUN_ALL_TESTS();
  grpc_shutdown();
  return ret;
}
