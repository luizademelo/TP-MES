
// Copyright 2022 gRPC authors.

#include "src/core/xds/grpc/xds_lb_policy_registry.h"

#include <google/protobuf/any.pb.h>
#include <google/protobuf/duration.pb.h>
#include <google/protobuf/struct.pb.h>
#include <google/protobuf/wrappers.pb.h>
#include <grpc/grpc.h>

#include <string>

#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "envoy/config/cluster/v3/cluster.pb.h"
#include "envoy/config/core/v3/extension.pb.h"
#include "envoy/extensions/load_balancing_policies/client_side_weighted_round_robin/v3/client_side_weighted_round_robin.pb.h"
#include "envoy/extensions/load_balancing_policies/pick_first/v3/pick_first.pb.h"
#include "envoy/extensions/load_balancing_policies/ring_hash/v3/ring_hash.pb.h"
#include "envoy/extensions/load_balancing_policies/round_robin/v3/round_robin.pb.h"
#include "envoy/extensions/load_balancing_policies/wrr_locality/v3/wrr_locality.pb.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "src/core/config/core_configuration.h"
#include "src/core/load_balancing/lb_policy.h"
#include "src/core/load_balancing/lb_policy_factory.h"
#include "src/core/util/crash.h"
#include "src/core/util/json/json_writer.h"
#include "src/core/util/orphanable.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/validation_errors.h"
#include "src/core/xds/grpc/xds_bootstrap_grpc.h"
#include "test/core/test_util/test_config.h"
#include "upb/mem/arena.hpp"
#include "upb/reflection/def.hpp"
#include "xds/type/v3/typed_struct.pb.h"

namespace grpc_core {
namespace testing {
namespace {

using LoadBalancingPolicyProto =
    ::envoy::config::cluster::v3::LoadBalancingPolicy;
using ::envoy::extensions::load_balancing_policies::
    client_side_weighted_round_robin::v3::ClientSideWeightedRoundRobin;
using ::envoy::extensions::load_balancing_policies::pick_first::v3::PickFirst;
using ::envoy::extensions::load_balancing_policies::ring_hash::v3::RingHash;
using ::envoy::extensions::load_balancing_policies::round_robin::v3::RoundRobin;
using ::envoy::extensions::load_balancing_policies::wrr_locality::v3::
    WrrLocality;
using ::xds::type::v3::TypedStruct;

absl::StatusOr<std::string> ConvertXdsPolicy(
    const LoadBalancingPolicyProto& policy) {
  std::string serialized_policy = policy.SerializeAsString();
  upb::Arena arena;
  upb::DefPool def_pool;
  XdsResourceType::DecodeContext context = {nullptr, GrpcXdsServer(),
                                            def_pool.ptr(), arena.ptr()};
  auto* upb_policy = envoy_config_cluster_v3_LoadBalancingPolicy_parse(
      serialized_policy.data(), serialized_policy.size(), arena.ptr());
  ValidationErrors errors;
  ValidationErrors::ScopedField field(&errors, ".load_balancing_policy");
  auto config = XdsLbPolicyRegistry().ConvertXdsLbPolicyConfig(
      context, upb_policy, &errors);
  if (!errors.ok()) {
    return errors.status(absl::StatusCode::kInvalidArgument,
                         "validation errors");
  }
  EXPECT_EQ(config.size(), 1);
  return JsonDump(Json{config[0]});
}

class CustomLbPolicyFactory : public LoadBalancingPolicyFactory {
 public:
  OrphanablePtr<LoadBalancingPolicy> CreateLoadBalancingPolicy(
      LoadBalancingPolicy::Args ) const override {
    Crash("unreachable");
    return nullptr;
  }

  absl::string_view name() const override { return "test.CustomLb"; }

  absl::StatusOr<RefCountedPtr<LoadBalancingPolicy::Config>>
  ParseLoadBalancingConfig(const Json& ) const override {
    return nullptr;
  }
};

TEST(RoundRobin, Basic) {
  LoadBalancingPolicyProto policy;
  auto* lb_policy = policy.add_policies();
  lb_policy->mutable_typed_extension_config()->mutable_typed_config()->PackFrom(
      RoundRobin());
  auto result = ConvertXdsPolicy(policy);
  ASSERT_TRUE(result.ok()) << result.status();
  EXPECT_EQ(*result, "{\"round_robin\":{}}");
}

TEST(ClientSideWeightedRoundRobinTest, DefaultConfig) {
  LoadBalancingPolicyProto policy;
  policy.add_policies()
      ->mutable_typed_extension_config()
      ->mutable_typed_config()
      ->PackFrom(ClientSideWeightedRoundRobin());
  auto result = ConvertXdsPolicy(policy);
  ASSERT_TRUE(result.ok()) << result.status();
  EXPECT_EQ(*result, "{\"weighted_round_robin\":{}}");
}

TEST(ClientSideWeightedRoundRobinTest, FieldsExplicitlySet) {
  ClientSideWeightedRoundRobin wrr;
  wrr.mutable_enable_oob_load_report()->set_value(true);
  wrr.mutable_oob_reporting_period()->set_seconds(1);
  wrr.mutable_blackout_period()->set_seconds(2);
  wrr.mutable_weight_expiration_period()->set_seconds(3);
  wrr.mutable_weight_update_period()->set_seconds(4);
  wrr.mutable_error_utilization_penalty()->set_value(5.0);
  LoadBalancingPolicyProto policy;
  policy.add_policies()
      ->mutable_typed_extension_config()
      ->mutable_typed_config()
      ->PackFrom(wrr);
  auto result = ConvertXdsPolicy(policy);
  ASSERT_TRUE(result.ok()) << result.status();
  EXPECT_EQ(*result,
            "{\"weighted_round_robin\":{"
            "\"blackoutPeriod\":\"2.000000000s\","
            "\"enableOobLoadReport\":true,"
            "\"errorUtilizationPenalty\":5,"
            "\"oobReportingPeriod\":\"1.000000000s\","
            "\"weightExpirationPeriod\":\"3.000000000s\","
            "\"weightUpdatePeriod\":\"4.000000000s\""
            "}}");
}

TEST(ClientSideWeightedRoundRobinTest, InvalidValues) {
  ClientSideWeightedRoundRobin wrr;
  wrr.mutable_oob_reporting_period()->set_seconds(-1);
  wrr.mutable_blackout_period()->set_seconds(-2);
  wrr.mutable_weight_expiration_period()->set_seconds(-3);
  wrr.mutable_weight_update_period()->set_seconds(-4);
  wrr.mutable_error_utilization_penalty()->set_value(-1);
  LoadBalancingPolicyProto policy;
  policy.add_policies()
      ->mutable_typed_extension_config()
      ->mutable_typed_config()
      ->PackFrom(wrr);
  auto result = ConvertXdsPolicy(policy);
  EXPECT_EQ(result.status().code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(result.status().message(),
            "validation errors: ["
            "field:load_balancing_policy.policies[0].typed_extension_config"
            ".typed_config.value[envoy.extensions.load_balancing_policies"
            ".client_side_weighted_round_robin.v3.ClientSideWeightedRoundRobin]"
            ".blackout_period.seconds "
            "error:value must be in the range [0, 315576000000]; "
            "field:load_balancing_policy.policies[0].typed_extension_config"
            ".typed_config.value[envoy.extensions.load_balancing_policies"
            ".client_side_weighted_round_robin.v3.ClientSideWeightedRoundRobin]"
            ".error_utilization_penalty error:value must be non-negative; "
            "field:load_balancing_policy.policies[0].typed_extension_config"
            ".typed_config.value[envoy.extensions.load_balancing_policies"
            ".client_side_weighted_round_robin.v3.ClientSideWeightedRoundRobin]"
            ".oob_reporting_period.seconds "
            "error:value must be in the range [0, 315576000000]; "
            "field:load_balancing_policy.policies[0].typed_extension_config"
            ".typed_config.value[envoy.extensions.load_balancing_policies"
            ".client_side_weighted_round_robin.v3.ClientSideWeightedRoundRobin]"
            ".weight_expiration_period.seconds "
            "error:value must be in the range [0, 315576000000]; "
            "field:load_balancing_policy.policies[0].typed_extension_config"
            ".typed_config.value[envoy.extensions.load_balancing_policies"
            ".client_side_weighted_round_robin.v3.ClientSideWeightedRoundRobin]"
            ".weight_update_period.seconds "
            "error:value must be in the range [0, 315576000000]]")
      << result.status();
}

TEST(RingHashConfig, DefaultConfig) {
  LoadBalancingPolicyProto policy;
  policy.add_policies()
      ->mutable_typed_extension_config()
      ->mutable_typed_config()
      ->PackFrom(RingHash());
  auto result = ConvertXdsPolicy(policy);
  ASSERT_TRUE(result.ok()) << result.status();
  EXPECT_EQ(*result,
            "{\"ring_hash_experimental\":{"
            "\"maxRingSize\":8388608,\"minRingSize\":1024}}");
}

TEST(RingHashConfig, FieldsExplicitlySet) {
  RingHash ring_hash;
  ring_hash.set_hash_function(RingHash::XX_HASH);
  ring_hash.mutable_minimum_ring_size()->set_value(1234);
  ring_hash.mutable_maximum_ring_size()->set_value(4567);
  LoadBalancingPolicyProto policy;
  policy.add_policies()
      ->mutable_typed_extension_config()
      ->mutable_typed_config()
      ->PackFrom(ring_hash);
  auto result = ConvertXdsPolicy(policy);
  ASSERT_TRUE(result.ok()) << result.status();
  EXPECT_EQ(*result,
            "{\"ring_hash_experimental\":{"
            "\"maxRingSize\":4567,\"minRingSize\":1234}}");
}

TEST(RingHashConfig, InvalidHashFunction) {
  RingHash ring_hash;
  ring_hash.set_hash_function(RingHash::MURMUR_HASH_2);
  LoadBalancingPolicyProto policy;
  policy.add_policies()
      ->mutable_typed_extension_config()
      ->mutable_typed_config()
      ->PackFrom(ring_hash);
  auto result = ConvertXdsPolicy(policy);
  EXPECT_EQ(result.status().code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(result.status().message(),
            "validation errors: ["
            "field:load_balancing_policy.policies[0].typed_extension_config"
            ".typed_config.value[envoy.extensions.load_balancing_policies"
            ".ring_hash.v3.RingHash].hash_function "
            "error:unsupported value (must be XX_HASH)]")
      << result.status();
}

TEST(RingHashConfig, RingSizesTooHigh) {
  RingHash ring_hash;
  ring_hash.mutable_minimum_ring_size()->set_value(8388609);
  ring_hash.mutable_maximum_ring_size()->set_value(8388609);
  LoadBalancingPolicyProto policy;
  policy.add_policies()
      ->mutable_typed_extension_config()
      ->mutable_typed_config()
      ->PackFrom(ring_hash);
  auto result = ConvertXdsPolicy(policy);
  EXPECT_EQ(result.status().code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(result.status().message(),
            "validation errors: ["
            "field:load_balancing_policy.policies[0].typed_extension_config"
            ".typed_config.value[envoy.extensions.load_balancing_policies"
            ".ring_hash.v3.RingHash].maximum_ring_size "
            "error:value must be in the range [1, 8388608]; "
            "field:load_balancing_policy.policies[0].typed_extension_config"
            ".typed_config.value[envoy.extensions.load_balancing_policies"
            ".ring_hash.v3.RingHash].minimum_ring_size "
            "error:value must be in the range [1, 8388608]]")
      << result.status();
}

TEST(RingHashConfig, RingSizesTooLow) {
  RingHash ring_hash;
  ring_hash.mutable_minimum_ring_size()->set_value(0);
  ring_hash.mutable_maximum_ring_size()->set_value(0);
  LoadBalancingPolicyProto policy;
  policy.add_policies()
      ->mutable_typed_extension_config()
      ->mutable_typed_config()
      ->PackFrom(ring_hash);
  auto result = ConvertXdsPolicy(policy);
  EXPECT_EQ(result.status().code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(result.status().message(),
            "validation errors: ["
            "field:load_balancing_policy.policies[0].typed_extension_config"
            ".typed_config.value[envoy.extensions.load_balancing_policies"
            ".ring_hash.v3.RingHash].maximum_ring_size "
            "error:value must be in the range [1, 8388608]; "
            "field:load_balancing_policy.policies[0].typed_extension_config"
            ".typed_config.value[envoy.extensions.load_balancing_policies"
            ".ring_hash.v3.RingHash].minimum_ring_size "
            "error:value must be in the range [1, 8388608]]")
      << result.status();
}

TEST(RingHashConfig, MinRingSizeGreaterThanMaxRingSize) {
  RingHash ring_hash;
  ring_hash.mutable_minimum_ring_size()->set_value(1000);
  ring_hash.mutable_maximum_ring_size()->set_value(999);
  LoadBalancingPolicyProto policy;
  policy.add_policies()
      ->mutable_typed_extension_config()
      ->mutable_typed_config()
      ->PackFrom(ring_hash);
  auto result = ConvertXdsPolicy(policy);
  EXPECT_EQ(result.status().code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(result.status().message(),
            "validation errors: ["
            "field:load_balancing_policy.policies[0].typed_extension_config"
            ".typed_config.value[envoy.extensions.load_balancing_policies"
            ".ring_hash.v3.RingHash].minimum_ring_size "
            "error:cannot be greater than maximum_ring_size]")
      << result.status();
}

TEST(WrrLocality, RoundRobinChild) {
  WrrLocality wrr_locality;
  wrr_locality.mutable_endpoint_picking_policy()
      ->add_policies()
      ->mutable_typed_extension_config()
      ->mutable_typed_config()
      ->PackFrom(RoundRobin());
  LoadBalancingPolicyProto policy;
  auto* lb_policy = policy.add_policies();
  lb_policy->mutable_typed_extension_config()->mutable_typed_config()->PackFrom(
      wrr_locality);
  auto result = ConvertXdsPolicy(policy);
  ASSERT_TRUE(result.ok()) << result.status();
  EXPECT_EQ(*result,
            "{\"xds_wrr_locality_experimental\":{"
            "\"childPolicy\":[{\"round_robin\":{}}]}}");
}

TEST(WrrLocality, MissingEndpointPickingPolicy) {
  LoadBalancingPolicyProto policy;
  auto* lb_policy = policy.add_policies();
  lb_policy->mutable_typed_extension_config()->mutable_typed_config()->PackFrom(
      WrrLocality());
  auto result = ConvertXdsPolicy(policy);
  EXPECT_EQ(result.status().code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(result.status().message(),
            "validation errors: ["
            "field:load_balancing_policy.policies[0].typed_extension_config"
            ".typed_config.value[envoy.extensions.load_balancing_policies"
            ".wrr_locality.v3.WrrLocality].endpoint_picking_policy "
            "error:field not present]")
      << result.status();
}

TEST(WrrLocality, ChildPolicyInvalid) {
  RingHash ring_hash;
  ring_hash.set_hash_function(RingHash::MURMUR_HASH_2);
  WrrLocality wrr_locality;
  wrr_locality.mutable_endpoint_picking_policy()
      ->add_policies()
      ->mutable_typed_extension_config()
      ->mutable_typed_config()
      ->PackFrom(ring_hash);
  LoadBalancingPolicyProto policy;
  auto* lb_policy = policy.add_policies();
  lb_policy->mutable_typed_extension_config()->mutable_typed_config()->PackFrom(
      wrr_locality);
  auto result = ConvertXdsPolicy(policy);
  EXPECT_EQ(result.status().code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(result.status().message(),
            "validation errors: ["
            "field:load_balancing_policy.policies[0].typed_extension_config"
            ".typed_config.value[envoy.extensions.load_balancing_policies"
            ".wrr_locality.v3.WrrLocality].endpoint_picking_policy.policies[0]"
            ".typed_extension_config.typed_config.value["
            "envoy.extensions.load_balancing_policies.ring_hash.v3.RingHash]"
            ".hash_function "
            "error:unsupported value (must be XX_HASH)]")
      << result.status();
}

TEST(WrrLocality, NoSupportedChildPolicy) {
  WrrLocality wrr_locality;
  wrr_locality.mutable_endpoint_picking_policy()
      ->add_policies()
      ->mutable_typed_extension_config()
      ->mutable_typed_config()
      ->PackFrom(LoadBalancingPolicyProto());
  LoadBalancingPolicyProto policy;
  auto* lb_policy = policy.add_policies();
  lb_policy->mutable_typed_extension_config()->mutable_typed_config()->PackFrom(
      wrr_locality);
  auto result = ConvertXdsPolicy(policy);
  EXPECT_EQ(result.status().code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(result.status().message(),
            "validation errors: ["
            "field:load_balancing_policy.policies[0].typed_extension_config"
            ".typed_config.value[envoy.extensions.load_balancing_policies"
            ".wrr_locality.v3.WrrLocality].endpoint_picking_policy "
            "error:no supported load balancing policy config found]")
      << result.status();
}

TEST(WrrLocality, UnsupportedChildPolicyTypeSkipped) {

  WrrLocality wrr_locality;
  wrr_locality.mutable_endpoint_picking_policy()
      ->add_policies()
      ->mutable_typed_extension_config()
      ->mutable_typed_config()
      ->PackFrom(LoadBalancingPolicyProto());
  wrr_locality.mutable_endpoint_picking_policy()
      ->add_policies()
      ->mutable_typed_extension_config()
      ->mutable_typed_config()
      ->PackFrom(RoundRobin());
  LoadBalancingPolicyProto policy;
  auto* lb_policy = policy.add_policies();
  lb_policy->mutable_typed_extension_config()->mutable_typed_config()->PackFrom(
      wrr_locality);
  auto result = ConvertXdsPolicy(policy);
  EXPECT_EQ(*result,
            "{\"xds_wrr_locality_experimental\":{"
            "\"childPolicy\":[{\"round_robin\":{}}]}}");
}

TEST(PickFirst, NoShuffle) {
  LoadBalancingPolicyProto policy;
  auto* lb_policy = policy.add_policies();
  PickFirst pick_first;
  pick_first.set_shuffle_address_list(false);
  lb_policy->mutable_typed_extension_config()->mutable_typed_config()->PackFrom(
      pick_first);
  auto result = ConvertXdsPolicy(policy);
  ASSERT_TRUE(result.ok()) << result.status();
  EXPECT_EQ(*result, "{\"pick_first\":{\"shuffleAddressList\":false}}");
}

TEST(PickFirst, Shuffle) {
  LoadBalancingPolicyProto policy;
  auto* lb_policy = policy.add_policies();
  PickFirst pick_first;
  pick_first.set_shuffle_address_list(true);
  lb_policy->mutable_typed_extension_config()->mutable_typed_config()->PackFrom(
      pick_first);
  auto result = ConvertXdsPolicy(policy);
  ASSERT_TRUE(result.ok()) << result.status();
  EXPECT_EQ(*result, "{\"pick_first\":{\"shuffleAddressList\":true}}");
}

TEST(PickFirst, ShuffleOmitted) {
  LoadBalancingPolicyProto policy;
  auto* lb_policy = policy.add_policies();
  lb_policy->mutable_typed_extension_config()->mutable_typed_config()->PackFrom(
      PickFirst());
  auto result = ConvertXdsPolicy(policy);
  ASSERT_TRUE(result.ok()) << result.status();
  EXPECT_EQ(*result, "{\"pick_first\":{\"shuffleAddressList\":false}}");
}

TEST(CustomPolicy, Basic) {
  TypedStruct typed_struct;
  typed_struct.set_type_url("type.googleapis.com/test.CustomLb");
  auto* fields = typed_struct.mutable_value()->mutable_fields();
  (*fields)["foo"].set_string_value("bar");
  LoadBalancingPolicyProto policy;
  auto* lb_policy = policy.add_policies();
  lb_policy->mutable_typed_extension_config()->mutable_typed_config()->PackFrom(
      typed_struct);
  auto result = ConvertXdsPolicy(policy);
  ASSERT_TRUE(result.ok()) << result.status();
  EXPECT_EQ(*result, "{\"test.CustomLb\":{\"foo\":\"bar\"}}");
}

TEST(XdsLbPolicyRegistryTest, EmptyLoadBalancingPolicy) {
  auto result = ConvertXdsPolicy(LoadBalancingPolicyProto());
  EXPECT_EQ(result.status().code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(result.status().message(),
            "validation errors: [field:load_balancing_policy "
            "error:no supported load balancing policy config found]")
      << result.status();
}

TEST(XdsLbPolicyRegistryTest, MissingTypedExtensionConfig) {
  LoadBalancingPolicyProto policy;
  policy.add_policies();
  auto result = ConvertXdsPolicy(policy);
  EXPECT_EQ(result.status().code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(result.status().message(),
            "validation errors: ["
            "field:load_balancing_policy.policies[0].typed_extension_config "
            "error:field not present]")
      << result.status();
}

TEST(XdsLbPolicyRegistryTest, MissingTypedConfig) {
  LoadBalancingPolicyProto policy;
  policy.add_policies()->mutable_typed_extension_config();
  auto result = ConvertXdsPolicy(policy);
  EXPECT_EQ(result.status().code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(result.status().message(),
            "validation errors: ["
            "field:load_balancing_policy.policies[0].typed_extension_config"
            ".typed_config error:field not present]")
      << result.status();
}

TEST(XdsLbPolicyRegistryTest, ErrorExtractingExtension) {
  TypedStruct typed_struct;
  typed_struct.set_type_url("type.googleapis.com/");
  LoadBalancingPolicyProto policy;
  auto* lb_policy = policy.add_policies();
  lb_policy->mutable_typed_extension_config()->mutable_typed_config()->PackFrom(
      typed_struct);
  auto result = ConvertXdsPolicy(policy);
  EXPECT_EQ(result.status().code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(result.status().message(),
            "validation errors: ["
            "field:load_balancing_policy.policies[0].typed_extension_config"
            ".typed_config.value[xds.type.v3.TypedStruct].type_url "
            "error:invalid value \"type.googleapis.com/\"]")
      << result.status();
}

TEST(XdsLbPolicyRegistryTest, NoSupportedType) {
  LoadBalancingPolicyProto policy;

  policy.add_policies()
      ->mutable_typed_extension_config()
      ->mutable_typed_config()
      ->PackFrom(LoadBalancingPolicyProto());

  TypedStruct typed_struct;
  typed_struct.set_type_url("myorg/foo/bar/test.UnknownLb");
  policy.add_policies()
      ->mutable_typed_extension_config()
      ->mutable_typed_config()
      ->PackFrom(typed_struct);
  auto result = ConvertXdsPolicy(policy);
  EXPECT_EQ(result.status().code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(result.status().message(),
            "validation errors: [field:load_balancing_policy "
            "error:no supported load balancing policy config found]")
      << result.status();
}

TEST(XdsLbPolicyRegistryTest, UnsupportedTypesSkipped) {
  LoadBalancingPolicyProto policy;

  policy.add_policies()
      ->mutable_typed_extension_config()
      ->mutable_typed_config()
      ->PackFrom(LoadBalancingPolicyProto());

  TypedStruct typed_struct;
  typed_struct.set_type_url("myorg/foo/bar/test.UnknownLb");
  policy.add_policies()
      ->mutable_typed_extension_config()
      ->mutable_typed_config()
      ->PackFrom(typed_struct);

  policy.add_policies()
      ->mutable_typed_extension_config()
      ->mutable_typed_config()
      ->PackFrom(RoundRobin());
  auto result = ConvertXdsPolicy(policy);
  ASSERT_TRUE(result.ok()) << result.status();
  EXPECT_EQ(*result, "{\"round_robin\":{}}");
}

LoadBalancingPolicyProto BuildRecursiveLoadBalancingPolicy(int depth) {
  LoadBalancingPolicyProto policy;
  if (depth >= 16) {
    policy.add_policies()
        ->mutable_typed_extension_config()
        ->mutable_typed_config()
        ->PackFrom(RoundRobin());
    return policy;
  }
  WrrLocality wrr_locality;
  *wrr_locality.mutable_endpoint_picking_policy() =
      BuildRecursiveLoadBalancingPolicy(depth + 1);
  policy.add_policies()
      ->mutable_typed_extension_config()
      ->mutable_typed_config()
      ->PackFrom(wrr_locality);
  return policy;
}

TEST(XdsLbPolicyRegistryTest, MaxRecursion) {
  auto result = ConvertXdsPolicy(BuildRecursiveLoadBalancingPolicy(0));
  EXPECT_EQ(result.status().code(), absl::StatusCode::kInvalidArgument);
  EXPECT_THAT(std::string(result.status().message()),
              ::testing::EndsWith("error:exceeded max recursion depth of 16]"));
}

}
}
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  grpc::testing::TestEnvironment env(&argc, argv);
  grpc_core::CoreConfiguration::RegisterEphemeralBuilder(
      [](grpc_core::CoreConfiguration::Builder* builder) {
        builder->lb_policy_registry()->RegisterLoadBalancingPolicyFactory(
            std::make_unique<grpc_core::testing::CustomLbPolicyFactory>());
      });
  grpc_init();
  auto result = RUN_ALL_TESTS();
  grpc_shutdown();
  return result;
}
