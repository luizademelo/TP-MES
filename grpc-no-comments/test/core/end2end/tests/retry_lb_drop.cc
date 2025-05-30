
// Copyright 2017 gRPC authors.

#include <grpc/grpc.h>
#include <grpc/impl/channel_arg_names.h>
#include <grpc/status.h>

#include <algorithm>
#include <memory>
#include <utility>
#include <vector>

#include "absl/log/check.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"
#include "gtest/gtest.h"
#include "src/core/config/core_configuration.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/load_balancing/lb_policy.h"
#include "src/core/load_balancing/lb_policy_factory.h"
#include "src/core/util/json/json.h"
#include "src/core/util/orphanable.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/time.h"
#include "test/core/end2end/end2end_tests.h"
#include "test/core/test_util/test_lb_policies.h"

namespace grpc_core {
namespace {

constexpr absl::string_view kDropPolicyName = "drop_lb";

class DropPolicy : public LoadBalancingPolicy {
 public:
  explicit DropPolicy(Args args) : LoadBalancingPolicy(std::move(args)) {}

  absl::string_view name() const override { return kDropPolicyName; }

  absl::Status UpdateLocked(UpdateArgs) override {
    channel_control_helper()->UpdateState(GRPC_CHANNEL_READY, absl::Status(),
                                          MakeRefCounted<DropPicker>());
    return absl::OkStatus();
  }

  void ResetBackoffLocked() override {}
  void ShutdownLocked() override {}

 private:
  class DropPicker : public SubchannelPicker {
   public:
    PickResult Pick(PickArgs ) override {
      return PickResult::Drop(
          absl::UnavailableError("Call dropped by drop LB policy"));
    }
  };
};

class DropLbConfig : public LoadBalancingPolicy::Config {
 public:
  absl::string_view name() const override { return kDropPolicyName; }
};

class DropPolicyFactory : public LoadBalancingPolicyFactory {
 public:
  OrphanablePtr<LoadBalancingPolicy> CreateLoadBalancingPolicy(
      LoadBalancingPolicy::Args args) const override {
    return MakeOrphanable<DropPolicy>(std::move(args));
  }

  absl::string_view name() const override { return kDropPolicyName; }

  absl::StatusOr<RefCountedPtr<LoadBalancingPolicy::Config>>
  ParseLoadBalancingConfig(const Json& ) const override {
    return MakeRefCounted<DropLbConfig>();
  }
};

std::vector<PickArgsSeen>* g_pick_args_vector = nullptr;

void RegisterDropPolicy(CoreConfiguration::Builder* builder) {
  builder->lb_policy_registry()->RegisterLoadBalancingPolicyFactory(
      std::make_unique<DropPolicyFactory>());
}

CORE_END2END_TEST(RetryTests, RetryLbDrop) {
  SKIP_IF_V3();
  CoreConfiguration::RegisterEphemeralBuilder(
      [](CoreConfiguration::Builder* builder) {
        RegisterTestPickArgsLoadBalancingPolicy(
            builder,
            [](const PickArgsSeen& pick_args) {
              CHECK_NE(g_pick_args_vector, nullptr);
              g_pick_args_vector->push_back(pick_args);
            },
            kDropPolicyName);
      });
  CoreConfiguration::RegisterEphemeralBuilder(RegisterDropPolicy);
  std::vector<PickArgsSeen> pick_args_seen;
  g_pick_args_vector = &pick_args_seen;
  InitServer(ChannelArgs());
  InitClient(ChannelArgs().Set(
      GRPC_ARG_SERVICE_CONFIG,
      "{\n"
      "  \"loadBalancingConfig\": [ {\n"
      "    \"test_pick_args_lb\": {}\n"
      "  } ],\n"
      "  \"methodConfig\": [ {\n"
      "    \"name\": [\n"
      "      { \"service\": \"service\", \"method\": \"method\" }\n"
      "    ],\n"
      "    \"retryPolicy\": {\n"
      "      \"maxAttempts\": 2,\n"
      "      \"initialBackoff\": \"1s\",\n"
      "      \"maxBackoff\": \"120s\",\n"
      "      \"backoffMultiplier\": 1.6,\n"
      "      \"retryableStatusCodes\": [ \"UNAVAILABLE\" ]\n"
      "    }\n"
      "  } ]\n"
      "}"));
  auto c =
      NewClientCall("/service/method").Timeout(Duration::Seconds(5)).Create();
  IncomingMessage server_message;
  IncomingMetadata server_initial_metadata;
  IncomingStatusOnClient server_status;
  c.NewBatch(1)
      .SendInitialMetadata({})
      .SendMessage("foo")
      .RecvMessage(server_message)
      .SendCloseFromClient()
      .RecvInitialMetadata(server_initial_metadata)
      .RecvStatusOnClient(server_status);
  Expect(1, true);
  Step();
  EXPECT_EQ(server_status.status(), GRPC_STATUS_UNAVAILABLE);
  EXPECT_EQ(server_status.message(), "Call dropped by drop LB policy");
  EXPECT_EQ(pick_args_seen.size(), 1);
  g_pick_args_vector = nullptr;
}

}
}
