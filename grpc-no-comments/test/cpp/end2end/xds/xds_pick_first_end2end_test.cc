// Copyright 2017 gRPC authors.

#include <grpc/event_engine/endpoint_config.h>
#include <grpcpp/support/status.h>
#include <unistd.h>

#include <cstddef>
#include <optional>
#include <string>
#include <utility>
#include <vector>

#include "absl/strings/str_cat.h"
#include "envoy/config/cluster/v3/cluster.pb.h"
#include "envoy/extensions/load_balancing_policies/pick_first/v3/pick_first.pb.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "src/core/client_channel/backup_poller.h"
#include "src/core/config/config_vars.h"
#include "src/core/lib/address_utils/sockaddr_utils.h"
#include "src/core/load_balancing/xds/xds_channel_args.h"
#include "src/core/resolver/fake/fake_resolver.h"
#include "src/core/util/env.h"
#include "test/core/test_util/test_config.h"
#include "test/cpp/end2end/connection_attempt_injector.h"
#include "test/cpp/end2end/xds/xds_end2end_test_lib.h"

namespace grpc {
namespace testing {
namespace {

using ::envoy::extensions::load_balancing_policies::pick_first::v3::PickFirst;

class PickFirstTest : public XdsEnd2endTest {
 protected:

  absl::StatusOr<size_t> WaitForAnyBackendHit(size_t start, size_t end) {
    absl::StatusOr<size_t> output;
    SendRpcsUntil(DEBUG_LOCATION, [&](const RpcResult& result) -> bool {
      if (!result.status.ok()) {
        output = absl::Status(
            static_cast<absl::StatusCode>(result.status.error_code()),
            result.status.error_message());
        return false;
      }
      for (size_t i = start; i < end; ++i) {
        if (backends_[i]->backend_service()->request_count() > 0) {
          backends_[i]->backend_service()->ResetCounters();
          output = i;
          return false;
        }
      }
      return true;
    });
    return output;
  }
};

INSTANTIATE_TEST_SUITE_P(XdsTest, PickFirstTest,
                         ::testing::Values(XdsTestType()), &XdsTestType::Name);

TEST_P(PickFirstTest, PickFirstConfigurationIsPropagated) {
  CreateAndStartBackends(6);

  auto cluster = default_cluster_;
  PickFirst pick_first;
  pick_first.set_shuffle_address_list(true);
  cluster.mutable_load_balancing_policy()
      ->add_policies()
      ->mutable_typed_extension_config()
      ->mutable_typed_config()
      ->PackFrom(pick_first);
  balancer_->ads_service()->SetCdsResource(cluster);
  size_t start_index = 0;
  for (size_t i = 0; i < 100; ++i) {

    balancer_->ads_service()->SetEdsResource(BuildEdsResource(
        EdsResourceArgs({{"locality0", CreateEndpointsForBackends(
                                           start_index, start_index + 3)}})));
    auto result = WaitForAnyBackendHit(start_index, start_index + 3);
    ASSERT_TRUE(result.ok()) << result.status();
    if (*result != start_index) return;

    start_index = 3 - start_index;
  }
  FAIL() << "did not choose a different backend";
}
}
}
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);

  grpc_core::ConfigVars::Overrides overrides;
  overrides.client_channel_backup_poll_interval_ms = 1;
  grpc_core::ConfigVars::SetOverrides(overrides);
#if TARGET_OS_IPHONE

  grpc_core::SetEnv("grpc_cfstream", "0");
#endif
  grpc_init();
  grpc::testing::ConnectionAttemptInjector::Init();
  const auto result = RUN_ALL_TESTS();
  grpc_shutdown();
  return result;
}
