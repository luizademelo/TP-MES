// Copyright 2017 gRPC authors.

#include <numeric>
#include <string>
#include <vector>

#include "absl/log/log.h"
#include "absl/strings/match.h"
#include "absl/strings/str_cat.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "src/core/client_channel/backup_poller.h"
#include "src/core/config/config_vars.h"
#include "src/core/lib/address_utils/sockaddr_utils.h"
#include "src/core/lib/surface/call.h"
#include "src/core/telemetry/call_tracer.h"
#include "test/core/test_util/fake_stats_plugin.h"
#include "test/core/test_util/scoped_env_var.h"
#include "test/cpp/end2end/connection_attempt_injector.h"
#include "test/cpp/end2end/xds/xds_end2end_test_lib.h"
#include "xds/data/orca/v3/orca_load_report.pb.h"

namespace grpc {
namespace testing {
namespace {

using ::envoy::config::cluster::v3::CircuitBreakers;
using ::envoy::config::core::v3::HealthStatus;
using ::envoy::config::core::v3::RoutingPriority;
using ::envoy::type::v3::FractionalPercent;

using ClientStats = LrsServiceImpl::ClientStats;
using OptionalLabelKey =
    grpc_core::ClientCallTracer::CallAttemptTracer::OptionalLabelKey;

constexpr char kLbDropType[] = "lb";
constexpr char kThrottleDropType[] = "throttle";
constexpr char kStatusMessageDropPrefix[] = "EDS-configured drop: ";

using CdsTest = XdsEnd2endTest;

INSTANTIATE_TEST_SUITE_P(XdsTest, CdsTest, ::testing::Values(XdsTestType()),
                         &XdsTestType::Name);

TEST_P(CdsTest, Vanilla) {
  (void)SendRpc();
  auto response_state = balancer_->ads_service()->cds_response_state();
  ASSERT_TRUE(response_state.has_value());
  EXPECT_EQ(response_state->state, AdsServiceImpl::ResponseState::ACKED);
}

TEST_P(CdsTest, InvalidClusterResource) {
  auto cluster = default_cluster_;
  cluster.set_type(Cluster::STATIC);
  balancer_->ads_service()->SetCdsResource(cluster);
  const auto response_state = WaitForCdsNack(DEBUG_LOCATION);
  ASSERT_TRUE(response_state.has_value()) << "timed out waiting for NACK";
  EXPECT_EQ(response_state->error_message,
            "xDS response validation errors: ["
            "resource index 0: cluster_name: "
            "INVALID_ARGUMENT: errors validating Cluster resource: ["
            "field:type error:unknown discovery type]]");
}

TEST_P(CdsTest, InvalidClusterStillExistsIfPreviouslyCached) {
  CreateAndStartBackends(1);
  EdsResourceArgs args({{"locality0", CreateEndpointsForBackends()}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  CheckRpcSendOk(DEBUG_LOCATION);

  auto cluster = default_cluster_;
  cluster.set_type(Cluster::STATIC);
  balancer_->ads_service()->SetCdsResource(cluster);
  const auto response_state =
      WaitForCdsNack(DEBUG_LOCATION, RpcOptions(), StatusCode::OK);
  ASSERT_TRUE(response_state.has_value()) << "timed out waiting for NACK";
  EXPECT_EQ(response_state->error_message,
            "xDS response validation errors: ["
            "resource index 0: cluster_name: "
            "INVALID_ARGUMENT: errors validating Cluster resource: ["
            "field:type error:unknown discovery type]]");
  CheckRpcSendOk(DEBUG_LOCATION);
}

TEST_P(CdsTest, EndpointWeightDoesNotImpactWeightedRoundRobin) {
  CreateAndStartBackends(2);
  const int kLocalityWeight0 = 2;
  const int kLocalityWeight1 = 8;
  const int kTotalLocalityWeight = kLocalityWeight0 + kLocalityWeight1;
  const double kLocalityWeightRate0 =
      static_cast<double>(kLocalityWeight0) / kTotalLocalityWeight;
  const double kLocalityWeightRate1 =
      static_cast<double>(kLocalityWeight1) / kTotalLocalityWeight;
  const double kErrorTolerance = 0.05;
  const size_t kNumRpcs =
      ComputeIdealNumRpcs(kLocalityWeightRate0, kErrorTolerance);

  EdsResourceArgs args({
      {"locality0",
       {CreateEndpoint(0, HealthStatus::UNKNOWN, 8)},
       kLocalityWeight0},
      {"locality1",
       {CreateEndpoint(1, HealthStatus::UNKNOWN, 2)},
       kLocalityWeight1},
  });
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  WaitForAllBackends(DEBUG_LOCATION, 0, 2);

  CheckRpcSendOk(DEBUG_LOCATION, kNumRpcs);

  const double locality_picked_rate_0 =
      static_cast<double>(backends_[0]->backend_service()->request_count()) /
      kNumRpcs;
  const double locality_picked_rate_1 =
      static_cast<double>(backends_[1]->backend_service()->request_count()) /
      kNumRpcs;
  EXPECT_THAT(locality_picked_rate_0,
              ::testing::DoubleNear(kLocalityWeightRate0, kErrorTolerance));
  EXPECT_THAT(locality_picked_rate_1,
              ::testing::DoubleNear(kLocalityWeightRate1, kErrorTolerance));
}

TEST_P(CdsTest, EdsServiceNameDefaultsToClusterName) {
  CreateAndStartBackends(1);
  EdsResourceArgs args({{"locality0", CreateEndpointsForBackends()}});
  balancer_->ads_service()->SetEdsResource(
      BuildEdsResource(args, kDefaultClusterName));
  Cluster cluster = default_cluster_;
  cluster.mutable_eds_cluster_config()->clear_service_name();
  balancer_->ads_service()->SetCdsResource(cluster);
  CheckRpcSendOk(DEBUG_LOCATION, 1,
                 RpcOptions().set_timeout_ms(5000));
}

TEST_P(CdsTest, ChangeClusters) {
  CreateAndStartBackends(2);
  const char* kNewClusterName = "new_cluster_name";
  const char* kNewEdsServiceName = "new_eds_service_name";
  EdsResourceArgs args({{"locality0", CreateEndpointsForBackends(0, 1)}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  WaitForAllBackends(DEBUG_LOCATION, 0, 1);

  args = EdsResourceArgs({{"locality0", CreateEndpointsForBackends(1, 2)}});
  balancer_->ads_service()->SetEdsResource(
      BuildEdsResource(args, kNewEdsServiceName));

  Cluster new_cluster = default_cluster_;
  new_cluster.set_name(kNewClusterName);
  new_cluster.mutable_eds_cluster_config()->set_service_name(
      kNewEdsServiceName);
  balancer_->ads_service()->SetCdsResource(new_cluster);

  RouteConfiguration new_route_config = default_route_config_;
  new_route_config.mutable_virtual_hosts(0)
      ->mutable_routes(0)
      ->mutable_route()
      ->set_cluster(kNewClusterName);
  SetListenerAndRouteConfiguration(balancer_.get(), default_listener_,
                                   new_route_config);

  WaitForAllBackends(DEBUG_LOCATION, 1, 2);
}

TEST_P(CdsTest, CircuitBreaking) {
  CreateAndStartBackends(1);
  constexpr size_t kMaxConcurrentRequests = 10;

  EdsResourceArgs args({{"locality0", CreateEndpointsForBackends()}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  CircuitBreakers circuit_breaks;
  Cluster cluster = default_cluster_;
  auto* threshold = cluster.mutable_circuit_breakers()->add_thresholds();
  threshold->set_priority(RoutingPriority::DEFAULT);
  threshold->mutable_max_requests()->set_value(kMaxConcurrentRequests);
  balancer_->ads_service()->SetCdsResource(cluster);

  LongRunningRpc rpcs[kMaxConcurrentRequests];
  for (size_t i = 0; i < kMaxConcurrentRequests; ++i) {
    rpcs[i].StartRpc(stub_.get());
  }

  while (backends_[0]->backend_service()->RpcsWaitingForClientCancel() <
         kMaxConcurrentRequests) {
    gpr_sleep_until(gpr_time_add(gpr_now(GPR_CLOCK_REALTIME),
                                 gpr_time_from_micros(1 * 1000, GPR_TIMESPAN)));
  }

  CheckRpcSendFailure(DEBUG_LOCATION, StatusCode::UNAVAILABLE,
                      "circuit breaker drop");

  rpcs[0].CancelRpc();

  gpr_sleep_until(gpr_time_add(gpr_now(GPR_CLOCK_REALTIME),
                               gpr_time_from_millis(1000, GPR_TIMESPAN)));
  CheckRpcSendOk(DEBUG_LOCATION);

  for (size_t i = 1; i < kMaxConcurrentRequests; ++i) {
    rpcs[i].CancelRpc();
  }
}

TEST_P(CdsTest, CircuitBreakingMultipleChannelsShareCallCounter) {
  CreateAndStartBackends(1);
  constexpr size_t kMaxConcurrentRequests = 10;

  EdsResourceArgs args({{"locality0", CreateEndpointsForBackends()}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  CircuitBreakers circuit_breaks;
  Cluster cluster = default_cluster_;
  auto* threshold = cluster.mutable_circuit_breakers()->add_thresholds();
  threshold->set_priority(RoutingPriority::DEFAULT);
  threshold->mutable_max_requests()->set_value(kMaxConcurrentRequests);
  balancer_->ads_service()->SetCdsResource(cluster);
  auto channel2 = CreateChannel();
  auto stub2 = grpc::testing::EchoTestService::NewStub(channel2);

  LongRunningRpc rpcs[kMaxConcurrentRequests];
  for (size_t i = 0; i < kMaxConcurrentRequests; ++i) {
    rpcs[i].StartRpc(i % 2 == 0 ? stub_.get() : stub2.get());
  }

  while (backends_[0]->backend_service()->RpcsWaitingForClientCancel() <
         kMaxConcurrentRequests) {
    gpr_sleep_until(gpr_time_add(gpr_now(GPR_CLOCK_REALTIME),
                                 gpr_time_from_micros(1 * 1000, GPR_TIMESPAN)));
  }

  CheckRpcSendFailure(DEBUG_LOCATION, StatusCode::UNAVAILABLE,
                      "circuit breaker drop");

  rpcs[0].CancelRpc();

  gpr_sleep_until(gpr_time_add(gpr_now(GPR_CLOCK_REALTIME),
                               gpr_time_from_millis(1000, GPR_TIMESPAN)));
  CheckRpcSendOk(DEBUG_LOCATION);

  for (size_t i = 1; i < kMaxConcurrentRequests; ++i) {
    rpcs[i].CancelRpc();
  }
}

TEST_P(CdsTest, ClusterChangeAfterAdsCallFails) {
  CreateAndStartBackends(2);
  const char* kNewEdsResourceName = "new_eds_resource_name";

  EdsResourceArgs args({{"locality0", CreateEndpointsForBackends(0, 1)}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  CheckRpcSendOk(DEBUG_LOCATION);

  balancer_->Shutdown();
  balancer_->Start();

  args = EdsResourceArgs({{"locality0", CreateEndpointsForBackends(1, 2)}});
  balancer_->ads_service()->SetEdsResource(
      BuildEdsResource(args, kNewEdsResourceName));

  auto cluster = default_cluster_;
  cluster.mutable_eds_cluster_config()->set_service_name(kNewEdsResourceName);
  balancer_->ads_service()->SetCdsResource(cluster);

  WaitForBackend(DEBUG_LOCATION, 1);
}

TEST_P(CdsTest, MetricLabels) {

  grpc_core::FakeClientCallTracerFactory fake_client_call_tracer_factory;
  CreateAndStartBackends(2);

  EdsResourceArgs args({{"locality0", CreateEndpointsForBackends(0, 1)},
                        {"locality1", CreateEndpointsForBackends(1, 2)}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  auto cluster = default_cluster_;
  auto& filter_map = *cluster.mutable_metadata()->mutable_filter_metadata();
  auto& label_map =
      *filter_map["com.google.csm.telemetry_labels"].mutable_fields();
  *label_map["service_name"].mutable_string_value() = "myservice";
  *label_map["service_namespace"].mutable_string_value() = "mynamespace";
  balancer_->ads_service()->SetCdsResource(cluster);
  ChannelArguments channel_args;
  channel_args.SetPointer(GRPC_ARG_INJECT_FAKE_CLIENT_CALL_TRACER_FACTORY,
                          &fake_client_call_tracer_factory);
  ResetStub(0, &channel_args);

  WaitForBackend(DEBUG_LOCATION, 0);

  EXPECT_THAT(
      fake_client_call_tracer_factory.GetLastFakeClientCallTracer()
          ->GetLastCallAttemptTracer()
          ->GetOptionalLabels(),
      ::testing::ElementsAre(
          ::testing::Pair(OptionalLabelKey::kXdsServiceName, "myservice"),
          ::testing::Pair(OptionalLabelKey::kXdsServiceNamespace,
                          "mynamespace"),
          ::testing::Pair(OptionalLabelKey::kLocality,
                          LocalityNameString("locality0"))));

  WaitForBackend(DEBUG_LOCATION, 1);

  EXPECT_THAT(
      fake_client_call_tracer_factory.GetLastFakeClientCallTracer()
          ->GetLastCallAttemptTracer()
          ->GetOptionalLabels(),
      ::testing::ElementsAre(
          ::testing::Pair(OptionalLabelKey::kXdsServiceName, "myservice"),
          ::testing::Pair(OptionalLabelKey::kXdsServiceNamespace,
                          "mynamespace"),
          ::testing::Pair(OptionalLabelKey::kLocality,
                          LocalityNameString("locality1"))));
}

class CdsDeletionTest : public XdsEnd2endTest {
 protected:
  void SetUp() override {}
};

INSTANTIATE_TEST_SUITE_P(XdsTest, CdsDeletionTest,
                         ::testing::Values(XdsTestType()), &XdsTestType::Name);

TEST_P(CdsDeletionTest, ClusterDeletedFailsByDefault) {
  InitClient();
  CreateAndStartBackends(1);
  EdsResourceArgs args({{"locality0", CreateEndpointsForBackends()}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  WaitForAllBackends(DEBUG_LOCATION);

  balancer_->ads_service()->UnsetResource(kCdsTypeUrl, kDefaultClusterName);

  SendRpcsUntilFailure(
      DEBUG_LOCATION, StatusCode::UNAVAILABLE,
      absl::StrCat("CDS resource ", kDefaultClusterName,
                   ": does not exist \\(node ID:xds_end2end_test\\)"));

  auto response_state = balancer_->ads_service()->cds_response_state();
  ASSERT_TRUE(response_state.has_value());
  EXPECT_EQ(response_state->state, AdsServiceImpl::ResponseState::ACKED);
}

TEST_P(CdsDeletionTest, ClusterDeletionIgnored) {
  InitClient(MakeBootstrapBuilder().SetIgnoreResourceDeletion());
  CreateAndStartBackends(2);

  EdsResourceArgs args({{"locality0", CreateEndpointsForBackends(0, 1)}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));
  WaitForAllBackends(DEBUG_LOCATION, 0, 1);

  auto response_state = balancer_->ads_service()->cds_response_state();
  ASSERT_TRUE(response_state.has_value());
  EXPECT_EQ(response_state->state, AdsServiceImpl::ResponseState::ACKED);

  balancer_->ads_service()->UnsetResource(kCdsTypeUrl, kDefaultClusterName);
  const auto deadline = absl::Now() + absl::Seconds(30);
  while (true) {
    ASSERT_LT(absl::Now(), deadline) << "timed out waiting for CDS ACK";
    response_state = balancer_->ads_service()->cds_response_state();
    if (response_state.has_value()) break;
  }
  EXPECT_EQ(response_state->state, AdsServiceImpl::ResponseState::ACKED);

  CheckRpcSendOk(DEBUG_LOCATION);

  const char* kNewEdsResourceName = "new_eds_resource_name";
  auto cluster = default_cluster_;
  cluster.mutable_eds_cluster_config()->set_service_name(kNewEdsResourceName);
  balancer_->ads_service()->SetCdsResource(cluster);
  args = EdsResourceArgs({{"locality0", CreateEndpointsForBackends(1, 2)}});
  balancer_->ads_service()->SetEdsResource(
      BuildEdsResource(args, kNewEdsResourceName));

  WaitForAllBackends(DEBUG_LOCATION, 1, 2);
}

TEST_P(CdsDeletionTest,
       ClusterDeletionIgnoredByDefaultWithDataErrorHandlingEnabled) {
  grpc_core::testing::ScopedExperimentalEnvVar env(
      "GRPC_EXPERIMENTAL_XDS_DATA_ERROR_HANDLING");
  InitClient();
  CreateAndStartBackends(2);

  EdsResourceArgs args({{"locality0", CreateEndpointsForBackends(0, 1)}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));
  WaitForAllBackends(DEBUG_LOCATION, 0, 1);

  auto response_state = balancer_->ads_service()->cds_response_state();
  ASSERT_TRUE(response_state.has_value());
  EXPECT_EQ(response_state->state, AdsServiceImpl::ResponseState::ACKED);

  balancer_->ads_service()->UnsetResource(kCdsTypeUrl, kDefaultClusterName);
  const auto deadline = absl::Now() + absl::Seconds(30);
  while (true) {
    ASSERT_LT(absl::Now(), deadline) << "timed out waiting for CDS ACK";
    response_state = balancer_->ads_service()->cds_response_state();
    if (response_state.has_value()) break;
  }
  EXPECT_EQ(response_state->state, AdsServiceImpl::ResponseState::ACKED);

  CheckRpcSendOk(DEBUG_LOCATION);

  const char* kNewEdsResourceName = "new_eds_resource_name";
  auto cluster = default_cluster_;
  cluster.mutable_eds_cluster_config()->set_service_name(kNewEdsResourceName);
  balancer_->ads_service()->SetCdsResource(cluster);
  args = EdsResourceArgs({{"locality0", CreateEndpointsForBackends(1, 2)}});
  balancer_->ads_service()->SetEdsResource(
      BuildEdsResource(args, kNewEdsResourceName));

  WaitForAllBackends(DEBUG_LOCATION, 1, 2);
}

TEST_P(CdsDeletionTest,
       ClusterDeletedFailsWithDataErrorHandlingEnabledWithFailOnDataErrors) {
  grpc_core::testing::ScopedExperimentalEnvVar env(
      "GRPC_EXPERIMENTAL_XDS_DATA_ERROR_HANDLING");
  InitClient(MakeBootstrapBuilder().SetFailOnDataErrors());
  CreateAndStartBackends(1);
  EdsResourceArgs args({{"locality0", CreateEndpointsForBackends()}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  WaitForAllBackends(DEBUG_LOCATION);

  balancer_->ads_service()->UnsetResource(kCdsTypeUrl, kDefaultClusterName);

  SendRpcsUntilFailure(
      DEBUG_LOCATION, StatusCode::UNAVAILABLE,
      absl::StrCat("CDS resource ", kDefaultClusterName,
                   ": does not exist \\(node ID:xds_end2end_test\\)"));

  auto response_state = balancer_->ads_service()->cds_response_state();
  ASSERT_TRUE(response_state.has_value());
  EXPECT_EQ(response_state->state, AdsServiceImpl::ResponseState::ACKED);
}

using EdsTest = XdsEnd2endTest;

INSTANTIATE_TEST_SUITE_P(
    XdsTest, EdsTest,
    ::testing::Values(XdsTestType(), XdsTestType().set_enable_load_reporting()),
    &XdsTestType::Name);

TEST_P(EdsTest, Vanilla) {
  CreateAndStartBackends(3);
  const size_t kNumRpcsPerAddress = 100;
  EdsResourceArgs args({
      {"locality0", CreateEndpointsForBackends()},
  });
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  channel_->GetState(true );

  WaitForAllBackends(DEBUG_LOCATION);

  CheckRpcSendOk(DEBUG_LOCATION, kNumRpcsPerAddress * backends_.size());

  for (size_t i = 0; i < backends_.size(); ++i) {
    EXPECT_EQ(kNumRpcsPerAddress,
              backends_[i]->backend_service()->request_count());
  }

  EXPECT_EQ("xds_cluster_manager_experimental",
            channel_->GetLoadBalancingPolicyName());
}

TEST_P(EdsTest, MultipleAddressesPerEndpoint) {
  grpc_core::testing::ScopedExperimentalEnvVar env(
      "GRPC_EXPERIMENTAL_XDS_DUALSTACK_ENDPOINTS");
  const size_t kNumRpcsPerAddress = 10;

  CreateBackends(3);
  StartBackend(1);
  StartBackend(2);

  EdsResourceArgs args({
      {"locality0",
       {CreateEndpoint(0, HealthStatus::UNKNOWN, 1, {1}), CreateEndpoint(2)}},
  });
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  WaitForAllBackends(DEBUG_LOCATION, 1);
  CheckRpcSendOk(DEBUG_LOCATION, kNumRpcsPerAddress * 2);
  EXPECT_EQ(kNumRpcsPerAddress,
            backends_[1]->backend_service()->request_count());
  EXPECT_EQ(kNumRpcsPerAddress,
            backends_[2]->backend_service()->request_count());

  StartBackend(0);
  ShutdownBackend(1);

  WaitForBackend(DEBUG_LOCATION, 0);

  CheckRpcSendOk(DEBUG_LOCATION, kNumRpcsPerAddress * 2);
  EXPECT_EQ(kNumRpcsPerAddress,
            backends_[0]->backend_service()->request_count());
  EXPECT_EQ(kNumRpcsPerAddress,
            backends_[2]->backend_service()->request_count());
}

TEST_P(EdsTest, IgnoresUnhealthyEndpoints) {
  CreateAndStartBackends(2);
  const size_t kNumRpcsPerAddress = 100;
  auto endpoints = CreateEndpointsForBackends();
  endpoints.push_back(MakeNonExistentEndpoint());
  endpoints.back().health_status = HealthStatus::DRAINING;
  EdsResourceArgs args({
      {"locality0", std::move(endpoints), kDefaultLocalityWeight,
       kDefaultLocalityPriority},
  });
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  channel_->GetState(true );

  WaitForAllBackends(DEBUG_LOCATION);

  CheckRpcSendOk(DEBUG_LOCATION, kNumRpcsPerAddress * backends_.size());

  for (size_t i = 0; i < backends_.size(); ++i) {
    EXPECT_EQ(kNumRpcsPerAddress,
              backends_[i]->backend_service()->request_count());
  }
}

TEST_P(EdsTest, LocalityBecomesEmptyWithDeactivatedChildStateUpdate) {
  CreateAndStartBackends(1);

  EdsResourceArgs args({{"locality0", CreateEndpointsForBackends()}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));
  WaitForAllBackends(DEBUG_LOCATION);

  EdsResourceArgs::Locality empty_locality("locality0", {});
  args = EdsResourceArgs({std::move(empty_locality)});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  constexpr char kErrorMessage[] =
      "no children in weighted_target policy \\("
      "EDS resource eds_service_name: contains empty localities: "
      "\\[\\{region=\"xds_default_locality_region\", "
      "zone=\"xds_default_locality_zone\", sub_zone=\"locality0\"\\}\\]\\)";
  SendRpcsUntilFailure(DEBUG_LOCATION, StatusCode::UNAVAILABLE, kErrorMessage);

  ShutdownAllBackends();

  StartAllBackends();

  args = EdsResourceArgs({{"locality0", CreateEndpointsForBackends()}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  WaitForAllBackends(DEBUG_LOCATION, 0, 1, [&](const RpcResult& result) {
    if (!result.status.ok()) {
      EXPECT_EQ(result.status.error_code(), StatusCode::UNAVAILABLE);
      EXPECT_THAT(result.status.error_message(),
                  ::testing::MatchesRegex(absl::StrCat(

                      MakeConnectionFailureRegex(
                          "connections to all backends failing; last error: "),
                      "|", kErrorMessage)));
    }
  });
}

TEST_P(EdsTest, NoLocalities) {
  CreateAndStartBackends(1);

  EdsResourceArgs args;
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  constexpr char kErrorMessage[] =
      "no children in weighted_target policy "
      "\\(EDS resource eds_service_name: contains no localities\\)";
  CheckRpcSendFailure(DEBUG_LOCATION, StatusCode::UNAVAILABLE, kErrorMessage);

  args = EdsResourceArgs({{"locality0", CreateEndpointsForBackends()}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  WaitForAllBackends(DEBUG_LOCATION, 0, 1, [&](const RpcResult& result) {
    if (!result.status.ok()) {
      EXPECT_EQ(result.status.error_code(), StatusCode::UNAVAILABLE);
      EXPECT_THAT(result.status.error_message(),
                  ::testing::MatchesRegex(kErrorMessage));
    }
  });
}

TEST_P(EdsTest, AllServersUnreachableFailFast) {

  const uint32_t kRpcTimeoutMs = 5000;
  const size_t kNumUnreachableServers = 5;
  std::vector<EdsResourceArgs::Endpoint> endpoints;
  for (size_t i = 0; i < kNumUnreachableServers; ++i) {
    endpoints.emplace_back(MakeNonExistentEndpoint());
  }
  EdsResourceArgs args({{"locality0", std::move(endpoints)}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  CheckRpcSendFailure(DEBUG_LOCATION, StatusCode::UNAVAILABLE,
                      MakeConnectionFailureRegex(
                          "connections to all backends failing; last error: "),
                      RpcOptions().set_timeout_ms(kRpcTimeoutMs));
}

TEST_P(EdsTest, BackendsRestart) {
  CreateAndStartBackends(3);
  EdsResourceArgs args({{"locality0", CreateEndpointsForBackends()}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));
  WaitForAllBackends(DEBUG_LOCATION);

  ShutdownAllBackends();

  EXPECT_TRUE(channel_->WaitForStateChange(
      GRPC_CHANNEL_READY, grpc_timeout_seconds_to_deadline(5)));
  EXPECT_THAT(channel_->GetState(false),
              ::testing::AnyOf(::testing::Eq(GRPC_CHANNEL_TRANSIENT_FAILURE),
                               ::testing::Eq(GRPC_CHANNEL_CONNECTING)));

  CheckRpcSendFailure(DEBUG_LOCATION, StatusCode::UNAVAILABLE,
                      MakeConnectionFailureRegex(
                          "connections to all backends failing; last error: "));

  StartAllBackends();
  CheckRpcSendOk(DEBUG_LOCATION, 1,
                 RpcOptions().set_timeout_ms(2000).set_wait_for_ready(true));
}

TEST_P(EdsTest, IgnoresDuplicateUpdates) {
  CreateAndStartBackends(1);
  const size_t kNumRpcsPerAddress = 100;
  EdsResourceArgs args({
      {"locality0", CreateEndpointsForBackends()},
  });
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  WaitForAllBackends(DEBUG_LOCATION);

  for (size_t i = 0; i < kNumRpcsPerAddress; ++i) {
    CheckRpcSendOk(DEBUG_LOCATION, 2);
    balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));
    CheckRpcSendOk(DEBUG_LOCATION, 2);
  }

  for (size_t i = 1; i < backends_.size(); ++i) {
    EXPECT_EQ(kNumRpcsPerAddress,
              backends_[i]->backend_service()->request_count());
  }
}

TEST_P(EdsTest, NacksInvalidResource) {
  EdsResourceArgs args({
      {"locality0", {MakeNonExistentEndpoint()}, kDefaultLocalityWeight, 1},
  });
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));
  const auto response_state = WaitForEdsNack(DEBUG_LOCATION);
  ASSERT_TRUE(response_state.has_value()) << "timed out waiting for NACK";
  EXPECT_EQ(response_state->error_message,
            "xDS response validation errors: ["
            "resource index 0: eds_service_name: "
            "INVALID_ARGUMENT: errors parsing EDS resource: ["
            "field:endpoints error:priority 0 empty]]");
}

TEST_P(EdsTest, KeepUsingLastDataIfBalancerGoesDown) {
  CreateAndStartBackends(2);

  EdsResourceArgs args({{"locality0", CreateEndpointsForBackends(0, 1)}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  WaitForBackend(DEBUG_LOCATION, 0);

  balancer_->Shutdown();
  auto deadline = grpc_timeout_seconds_to_deadline(5);
  do {
    CheckRpcSendOk(DEBUG_LOCATION);
  } while (gpr_time_cmp(gpr_now(GPR_CLOCK_MONOTONIC), deadline) < 0);

  args = EdsResourceArgs({{"locality0", CreateEndpointsForBackends(1, 2)}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));
  balancer_->Start();

  WaitForBackend(DEBUG_LOCATION, 1);
}

TEST_P(EdsTest, LocalityWeights) {
  CreateAndStartBackends(2);
  const int kLocalityWeight0 = 2;
  const int kLocalityWeight1 = 8;
  const int kTotalLocalityWeight = kLocalityWeight0 + kLocalityWeight1;
  const double kLocalityWeightRate0 =
      static_cast<double>(kLocalityWeight0) / kTotalLocalityWeight;
  const double kLocalityWeightRate1 =
      static_cast<double>(kLocalityWeight1) / kTotalLocalityWeight;
  const double kErrorTolerance = 0.05;
  const size_t kNumRpcs =
      ComputeIdealNumRpcs(kLocalityWeightRate0, kErrorTolerance);

  EdsResourceArgs args({
      {"locality0", CreateEndpointsForBackends(0, 1), kLocalityWeight0},
      {"locality1", CreateEndpointsForBackends(1, 2), kLocalityWeight1},
  });
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  WaitForAllBackends(DEBUG_LOCATION, 0, 2);

  CheckRpcSendOk(DEBUG_LOCATION, kNumRpcs);

  const double locality_picked_rate_0 =
      static_cast<double>(backends_[0]->backend_service()->request_count()) /
      kNumRpcs;
  const double locality_picked_rate_1 =
      static_cast<double>(backends_[1]->backend_service()->request_count()) /
      kNumRpcs;
  EXPECT_THAT(locality_picked_rate_0,
              ::testing::DoubleNear(kLocalityWeightRate0, kErrorTolerance));
  EXPECT_THAT(locality_picked_rate_1,
              ::testing::DoubleNear(kLocalityWeightRate1, kErrorTolerance));
}

TEST_P(EdsTest, NoIntegerOverflowInLocalityWeights) {
  CreateAndStartBackends(2);
  const uint32_t kLocalityWeight1 = std::numeric_limits<uint32_t>::max() / 3;
  const uint32_t kLocalityWeight0 =
      std::numeric_limits<uint32_t>::max() - kLocalityWeight1;
  const uint64_t kTotalLocalityWeight =
      static_cast<uint64_t>(kLocalityWeight0) +
      static_cast<uint64_t>(kLocalityWeight1);
  const double kLocalityWeightRate0 =
      static_cast<double>(kLocalityWeight0) / kTotalLocalityWeight;
  const double kLocalityWeightRate1 =
      static_cast<double>(kLocalityWeight1) / kTotalLocalityWeight;
  const double kErrorTolerance = 0.05;
  const size_t kNumRpcs =
      ComputeIdealNumRpcs(kLocalityWeightRate0, kErrorTolerance);

  EdsResourceArgs args({
      {"locality0", CreateEndpointsForBackends(0, 1), kLocalityWeight0},
      {"locality1", CreateEndpointsForBackends(1, 2), kLocalityWeight1},
  });
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  WaitForAllBackends(DEBUG_LOCATION, 0, 2);

  CheckRpcSendOk(DEBUG_LOCATION, kNumRpcs);

  const double locality_picked_rate_0 =
      static_cast<double>(backends_[0]->backend_service()->request_count()) /
      kNumRpcs;
  const double locality_picked_rate_1 =
      static_cast<double>(backends_[1]->backend_service()->request_count()) /
      kNumRpcs;
  EXPECT_THAT(locality_picked_rate_0,
              ::testing::DoubleNear(kLocalityWeightRate0, kErrorTolerance));
  EXPECT_THAT(locality_picked_rate_1,
              ::testing::DoubleNear(kLocalityWeightRate1, kErrorTolerance));
}

TEST_P(EdsTest, OneLocalityWithNoEndpoints) {
  CreateAndStartBackends(1);

  EdsResourceArgs::Locality empty_locality("locality0", {});
  EdsResourceArgs args({std::move(empty_locality)});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  constexpr char kErrorMessage[] =
      "no children in weighted_target policy \\("
      "EDS resource eds_service_name: contains empty localities: "
      "\\[\\{region=\"xds_default_locality_region\", "
      "zone=\"xds_default_locality_zone\", sub_zone=\"locality0\"\\}\\]\\)";
  CheckRpcSendFailure(DEBUG_LOCATION, StatusCode::UNAVAILABLE, kErrorMessage);

  args = EdsResourceArgs({{"locality0", CreateEndpointsForBackends()}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  WaitForAllBackends(DEBUG_LOCATION, 0, 1, [&](const RpcResult& result) {
    if (!result.status.ok()) {
      EXPECT_EQ(result.status.error_code(), StatusCode::UNAVAILABLE);
      EXPECT_THAT(result.status.error_message(),
                  ::testing::MatchesRegex(kErrorMessage));
    }
  });
}

TEST_P(EdsTest, LocalityContainingNoEndpoints) {
  CreateAndStartBackends(2);
  const size_t kNumRpcs = 5000;

  EdsResourceArgs args({
      {"locality0", CreateEndpointsForBackends()},
      {"locality1", {}},
  });
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  WaitForAllBackends(DEBUG_LOCATION);

  CheckRpcSendOk(DEBUG_LOCATION, kNumRpcs);

  EXPECT_EQ(backends_[0]->backend_service()->request_count(),
            kNumRpcs / backends_.size());
  EXPECT_EQ(backends_[1]->backend_service()->request_count(),
            kNumRpcs / backends_.size());
}

TEST_P(EdsTest, ManyLocalitiesStressTest) {
  const size_t kNumLocalities = 50;
  CreateAndStartBackends(kNumLocalities + 1);
  const uint32_t kRpcTimeoutMs = 5000;

  EdsResourceArgs args;
  for (size_t i = 0; i < kNumLocalities; ++i) {
    std::string name = absl::StrCat("locality", i);
    EdsResourceArgs::Locality locality(name,
                                       CreateEndpointsForBackends(i, i + 1));
    args.locality_list.emplace_back(std::move(locality));
  }
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  WaitForAllBackends(DEBUG_LOCATION, 0, kNumLocalities,
                     nullptr,
                     WaitForBackendOptions().set_reset_counters(false),
                     RpcOptions().set_timeout_ms(kRpcTimeoutMs));

  args =
      EdsResourceArgs({{"locality0", CreateEndpointsForBackends(
                                         kNumLocalities, kNumLocalities + 1)}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  WaitForBackend(DEBUG_LOCATION, kNumLocalities);
}

TEST_P(EdsTest, LocalityMapUpdateChurn) {
  CreateAndStartBackends(4);
  const size_t kNumRpcs = 3000;

  const std::vector<int> kLocalityWeights0 = {2, 3, 4};
  const double kTotalLocalityWeight0 =
      std::accumulate(kLocalityWeights0.begin(), kLocalityWeights0.end(), 0);
  std::vector<double> locality_weight_rate_0;
  locality_weight_rate_0.reserve(kLocalityWeights0.size());
  for (int weight : kLocalityWeights0) {
    locality_weight_rate_0.push_back(weight / kTotalLocalityWeight0);
  }

  const std::vector<int> kLocalityWeights1 = {3, 2, 6};
  const double kTotalLocalityWeight1 =
      std::accumulate(kLocalityWeights1.begin(), kLocalityWeights1.end(), 0);
  std::vector<double> locality_weight_rate_1 = {
      0 };
  for (int weight : kLocalityWeights1) {
    locality_weight_rate_1.push_back(weight / kTotalLocalityWeight1);
  }
  EdsResourceArgs args({
      {"locality0", CreateEndpointsForBackends(0, 1), 2},
      {"locality1", CreateEndpointsForBackends(1, 2), 3},
      {"locality2", CreateEndpointsForBackends(2, 3), 4},
  });
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  WaitForAllBackends(DEBUG_LOCATION, 0, 3);
  LOG(INFO) << "========= BEFORE FIRST BATCH ==========";

  CheckRpcSendOk(DEBUG_LOCATION, kNumRpcs);
  LOG(INFO) << "========= DONE WITH FIRST BATCH ==========";

  std::vector<double> locality_picked_rates;
  for (size_t i = 0; i < 3; ++i) {
    locality_picked_rates.push_back(
        static_cast<double>(backends_[i]->backend_service()->request_count()) /
        kNumRpcs);
  }
  const double kErrorTolerance = 0.2;
  for (size_t i = 0; i < 3; ++i) {
    LOG(INFO) << "Locality " << i << " rate " << locality_picked_rates[i];
    EXPECT_THAT(
        locality_picked_rates[i],
        ::testing::AllOf(
            ::testing::Ge(locality_weight_rate_0[i] * (1 - kErrorTolerance)),
            ::testing::Le(locality_weight_rate_0[i] * (1 + kErrorTolerance))));
  }
  args = EdsResourceArgs({
      {"locality1", CreateEndpointsForBackends(1, 2), 3},
      {"locality2", CreateEndpointsForBackends(2, 3), 2},
      {"locality3", CreateEndpointsForBackends(3, 4), 6},
  });
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  EXPECT_EQ(0U, backends_[3]->backend_service()->request_count());

  WaitForAllBackends(DEBUG_LOCATION, 3, 4);
  LOG(INFO) << "========= BEFORE SECOND BATCH ==========";

  CheckRpcSendOk(DEBUG_LOCATION, kNumRpcs);
  LOG(INFO) << "========= DONE WITH SECOND BATCH ==========";

  EXPECT_EQ(0U, backends_[0]->backend_service()->request_count());

  locality_picked_rates = {0 };
  for (size_t i = 1; i < 4; ++i) {
    locality_picked_rates.push_back(
        static_cast<double>(backends_[i]->backend_service()->request_count()) /
        kNumRpcs);
  }
  for (size_t i = 1; i < 4; ++i) {
    LOG(INFO) << "Locality " << i << " rate " << locality_picked_rates[i];
    EXPECT_THAT(
        locality_picked_rates[i],
        ::testing::AllOf(
            ::testing::Ge(locality_weight_rate_1[i] * (1 - kErrorTolerance)),
            ::testing::Le(locality_weight_rate_1[i] * (1 + kErrorTolerance))));
  }
}

TEST_P(EdsTest, ReplaceAllLocalitiesInPriority) {
  CreateAndStartBackends(2);

  EdsResourceArgs args({{"locality0", CreateEndpointsForBackends(0, 1)}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  WaitForBackend(DEBUG_LOCATION, 0);

  args = EdsResourceArgs({{"locality1", CreateEndpointsForBackends(1, 2)}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  WaitForBackend(DEBUG_LOCATION, 1);
}

TEST_P(EdsTest, ConsistentWeightedTargetUpdates) {
  CreateAndStartBackends(4);

  EdsResourceArgs args({
      {"locality0", CreateEndpointsForBackends(1, 2)},
      {"locality1", CreateEndpointsForBackends(2, 3)},
  });
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));
  WaitForAllBackends(DEBUG_LOCATION, 1, 3);

  args = EdsResourceArgs({
      {"locality0", CreateEndpointsForBackends(0, 2)},
  });
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));
  WaitForBackend(DEBUG_LOCATION, 0);

  args = EdsResourceArgs({
      {"locality0", CreateEndpointsForBackends(0, 2)},
      {"locality1", CreateEndpointsForBackends(2, 4)},
  });
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));
  WaitForBackend(DEBUG_LOCATION, 3);
}

TEST_P(EdsTest, Drops) {
  CreateAndStartBackends(1);
  const uint32_t kDropPerMillionForLb = 100000;
  const uint32_t kDropPerMillionForThrottle = 200000;
  const double kDropRateForLb = kDropPerMillionForLb / 1000000.0;
  const double kDropRateForThrottle = kDropPerMillionForThrottle / 1000000.0;
  const double kDropRateForLbAndThrottle =
      kDropRateForLb + ((1 - kDropRateForLb) * kDropRateForThrottle);
  const double kErrorTolerance = 0.05;
  const size_t kNumRpcs =
      ComputeIdealNumRpcs(kDropRateForLbAndThrottle, kErrorTolerance);

  EdsResourceArgs args({{"locality0", CreateEndpointsForBackends()}});
  args.drop_categories = {{kLbDropType, kDropPerMillionForLb},
                          {kThrottleDropType, kDropPerMillionForThrottle}};
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  size_t num_drops = SendRpcsAndCountFailuresWithMessage(
      DEBUG_LOCATION, kNumRpcs, StatusCode::UNAVAILABLE,
      kStatusMessageDropPrefix);

  const double seen_drop_rate = static_cast<double>(num_drops) / kNumRpcs;
  EXPECT_THAT(seen_drop_rate, ::testing::DoubleNear(kDropRateForLbAndThrottle,
                                                    kErrorTolerance));
}

TEST_P(EdsTest, DropPerHundred) {
  CreateAndStartBackends(1);
  const uint32_t kDropPerHundredForLb = 10;
  const double kDropRateForLb = kDropPerHundredForLb / 100.0;
  const double kErrorTolerance = 0.05;
  const size_t kNumRpcs = ComputeIdealNumRpcs(kDropRateForLb, kErrorTolerance);

  EdsResourceArgs args({{"locality0", CreateEndpointsForBackends()}});
  args.drop_categories = {{kLbDropType, kDropPerHundredForLb}};
  args.drop_denominator = FractionalPercent::HUNDRED;
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  size_t num_drops = SendRpcsAndCountFailuresWithMessage(
      DEBUG_LOCATION, kNumRpcs, StatusCode::UNAVAILABLE,
      kStatusMessageDropPrefix);

  const double seen_drop_rate = static_cast<double>(num_drops) / kNumRpcs;
  EXPECT_THAT(seen_drop_rate,
              ::testing::DoubleNear(kDropRateForLb, kErrorTolerance));
}

TEST_P(EdsTest, DropPerTenThousand) {
  CreateAndStartBackends(1);
  const uint32_t kDropPerTenThousandForLb = 1000;
  const double kDropRateForLb = kDropPerTenThousandForLb / 10000.0;
  const double kErrorTolerance = 0.05;
  const size_t kNumRpcs = ComputeIdealNumRpcs(kDropRateForLb, kErrorTolerance);

  EdsResourceArgs args({{"locality0", CreateEndpointsForBackends()}});
  args.drop_categories = {{kLbDropType, kDropPerTenThousandForLb}};
  args.drop_denominator = FractionalPercent::TEN_THOUSAND;
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  size_t num_drops = SendRpcsAndCountFailuresWithMessage(
      DEBUG_LOCATION, kNumRpcs, StatusCode::UNAVAILABLE,
      kStatusMessageDropPrefix);

  const double seen_drop_rate = static_cast<double>(num_drops) / kNumRpcs;
  EXPECT_THAT(seen_drop_rate,
              ::testing::DoubleNear(kDropRateForLb, kErrorTolerance));
}

TEST_P(EdsTest, DropConfigUpdate) {
  CreateAndStartBackends(2);
  const uint32_t kDropPerMillionForLb = 100000;
  const uint32_t kDropPerMillionForThrottle = 200000;
  const double kErrorTolerance = 0.05;
  const double kDropRateForLb = kDropPerMillionForLb / 1000000.0;
  const double kDropRateForThrottle = kDropPerMillionForThrottle / 1000000.0;
  const double kDropRateForLbAndThrottle =
      kDropRateForLb + ((1 - kDropRateForLb) * kDropRateForThrottle);
  const size_t kNumRpcsLbOnly =
      ComputeIdealNumRpcs(kDropRateForLb, kErrorTolerance);
  const size_t kNumRpcsBoth =
      ComputeIdealNumRpcs(kDropRateForLbAndThrottle, kErrorTolerance);

  EdsResourceArgs args({{"locality0", CreateEndpointsForBackends(0, 1)}});
  args.drop_categories = {{kLbDropType, kDropPerMillionForLb}};
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  LOG(INFO) << "========= BEFORE FIRST BATCH ==========";
  size_t num_drops = SendRpcsAndCountFailuresWithMessage(
      DEBUG_LOCATION, kNumRpcsLbOnly, StatusCode::UNAVAILABLE,
      kStatusMessageDropPrefix);
  LOG(INFO) << "========= DONE WITH FIRST BATCH ==========";

  double seen_drop_rate = static_cast<double>(num_drops) / kNumRpcsLbOnly;
  LOG(INFO) << "First batch drop rate " << seen_drop_rate;
  EXPECT_THAT(seen_drop_rate,
              ::testing::DoubleNear(kDropRateForLb, kErrorTolerance));

  args = EdsResourceArgs({{"locality0", CreateEndpointsForBackends()}});
  args.drop_categories = {{kLbDropType, kDropPerMillionForLb},
                          {kThrottleDropType, kDropPerMillionForThrottle}};
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  WaitForBackend(DEBUG_LOCATION, 1, [&](const RpcResult& result) {
    if (!result.status.ok()) {
      EXPECT_EQ(result.status.error_code(), StatusCode::UNAVAILABLE);
      EXPECT_THAT(result.status.error_message(),
                  ::testing::StartsWith(kStatusMessageDropPrefix));
    }
  });

  LOG(INFO) << "========= BEFORE SECOND BATCH ==========";
  num_drops = SendRpcsAndCountFailuresWithMessage(DEBUG_LOCATION, kNumRpcsBoth,
                                                  StatusCode::UNAVAILABLE,
                                                  kStatusMessageDropPrefix);
  LOG(INFO) << "========= DONE WITH SECOND BATCH ==========";

  seen_drop_rate = static_cast<double>(num_drops) / kNumRpcsBoth;
  LOG(INFO) << "Second batch drop rate " << seen_drop_rate;
  EXPECT_THAT(seen_drop_rate, ::testing::DoubleNear(kDropRateForLbAndThrottle,
                                                    kErrorTolerance));
}

TEST_P(EdsTest, DropAll) {
  const size_t kNumRpcs = 1000;
  const uint32_t kDropPerMillionForLb = 100000;
  const uint32_t kDropPerMillionForThrottle = 1000000;

  EdsResourceArgs args;
  args.drop_categories = {{kLbDropType, kDropPerMillionForLb},
                          {kThrottleDropType, kDropPerMillionForThrottle}};
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  size_t num_drops = SendRpcsAndCountFailuresWithMessage(
      DEBUG_LOCATION, kNumRpcs, StatusCode::UNAVAILABLE,
      kStatusMessageDropPrefix);
  EXPECT_EQ(num_drops, kNumRpcs);
}

class EdsAuthorityRewriteTest : public XdsEnd2endTest {
 protected:
  void SetUp() override {}
};

INSTANTIATE_TEST_SUITE_P(XdsTest, EdsAuthorityRewriteTest,
                         ::testing::Values(XdsTestType()), &XdsTestType::Name);

TEST_P(EdsAuthorityRewriteTest, AutoAuthorityRewrite) {
  constexpr char kAltAuthority1[] = "alt_authority1";
  constexpr char kAltAuthority2[] = "alt_authority2";
  // Note: We use InsecureCreds, since FakeCreds are too picky about

  InitClient(MakeBootstrapBuilder().SetTrustedXdsServer(),
             "",
             0,
             "", nullptr,
             InsecureChannelCredentials());

  RouteConfiguration new_route_config = default_route_config_;
  new_route_config.mutable_virtual_hosts(0)
      ->mutable_routes(0)
      ->mutable_route()
      ->mutable_auto_host_rewrite()
      ->set_value(true);
  SetRouteConfiguration(balancer_.get(), new_route_config);

  CreateAndStartBackends(3, false, InsecureServerCredentials());
  EdsResourceArgs args(
      {{"locality0",
        {
            CreateEndpoint(0),
            CreateEndpoint(1, ::envoy::config::core::v3::HealthStatus::UNKNOWN,
                           1, {},
                           kAltAuthority1),
            CreateEndpoint(2, ::envoy::config::core::v3::HealthStatus::UNKNOWN,
                           1, {},
                           kAltAuthority2),
        }}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));
  WaitForAllBackends(DEBUG_LOCATION);

  std::set<std::string> authorities_seen;
  for (size_t i = 0; i < backends_.size(); ++i) {
    EchoResponse response;
    Status status = SendRpc(
        RpcOptions().set_echo_host_from_authority_header(true), &response);
    EXPECT_TRUE(status.ok()) << "code=" << status.error_code()
                             << " message=" << status.error_message();
    authorities_seen.insert(response.param().host());
  }
  EXPECT_THAT(
      authorities_seen,
      ::testing::ElementsAre(kAltAuthority1, kAltAuthority2, kServerName));
}

TEST_P(EdsAuthorityRewriteTest, NoRewriteIfServerNotTrustedInBootstrap) {
  constexpr char kAltAuthority[] = "alt_authority";
  InitClient();

  RouteConfiguration new_route_config = default_route_config_;
  new_route_config.mutable_virtual_hosts(0)
      ->mutable_routes(0)
      ->mutable_route()
      ->mutable_auto_host_rewrite()
      ->set_value(true);
  SetRouteConfiguration(balancer_.get(), new_route_config);

  CreateAndStartBackends(1);
  EdsResourceArgs args(
      {{"locality0",
        {CreateEndpoint(0, ::envoy::config::core::v3::HealthStatus::UNKNOWN,
                        1, {},
                        kAltAuthority)}}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  EchoResponse response;
  Status status = SendRpc(
      RpcOptions().set_echo_host_from_authority_header(true), &response);
  EXPECT_TRUE(status.ok()) << "code=" << status.error_code()
                           << " message=" << status.error_message();
  EXPECT_EQ(response.param().host(), kServerName);
}

TEST_P(EdsAuthorityRewriteTest, NoRewriteIfNoHostnameInEds) {
  InitClient(MakeBootstrapBuilder().SetTrustedXdsServer());

  RouteConfiguration new_route_config = default_route_config_;
  new_route_config.mutable_virtual_hosts(0)
      ->mutable_routes(0)
      ->mutable_route()
      ->mutable_auto_host_rewrite()
      ->set_value(true);
  SetRouteConfiguration(balancer_.get(), new_route_config);

  CreateAndStartBackends(1);
  EdsResourceArgs args({{"locality0", {CreateEndpoint(0)}}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  EchoResponse response;
  Status status = SendRpc(
      RpcOptions().set_echo_host_from_authority_header(true), &response);
  EXPECT_TRUE(status.ok()) << "code=" << status.error_code()
                           << " message=" << status.error_message();
  EXPECT_EQ(response.param().host(), kServerName);
}

TEST_P(EdsAuthorityRewriteTest, NoRewriteIfNotEnabledInRoute) {
  constexpr char kAltAuthority[] = "alt_authority";
  InitClient(MakeBootstrapBuilder().SetTrustedXdsServer());

  CreateAndStartBackends(1);
  EdsResourceArgs args(
      {{"locality0",
        {CreateEndpoint(0, ::envoy::config::core::v3::HealthStatus::UNKNOWN,
                        1, {},
                        kAltAuthority)}}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  EchoResponse response;
  Status status = SendRpc(
      RpcOptions().set_echo_host_from_authority_header(true), &response);
  EXPECT_TRUE(status.ok()) << "code=" << status.error_code()
                           << " message=" << status.error_message();
  EXPECT_EQ(response.param().host(), kServerName);
}

class FailoverTest : public XdsEnd2endTest {
 public:
  void SetUp() override {
    XdsEnd2endTest::SetUp();
    ResetStub(500);
  }
};

INSTANTIATE_TEST_SUITE_P(
    XdsTest, FailoverTest,
    ::testing::Values(XdsTestType(), XdsTestType().set_enable_load_reporting()),
    &XdsTestType::Name);

TEST_P(FailoverTest, ChooseHighestPriority) {
  CreateAndStartBackends(4);
  EdsResourceArgs args({
      {"locality0", CreateEndpointsForBackends(0, 1), kDefaultLocalityWeight,
       1},
      {"locality1", CreateEndpointsForBackends(1, 2), kDefaultLocalityWeight,
       2},
      {"locality2", CreateEndpointsForBackends(2, 3), kDefaultLocalityWeight,
       3},
      {"locality3", CreateEndpointsForBackends(3, 4), kDefaultLocalityWeight,
       0},
  });
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));
  WaitForBackend(DEBUG_LOCATION, 3, nullptr,
                 WaitForBackendOptions().set_reset_counters(false));
  for (size_t i = 0; i < 3; ++i) {
    EXPECT_EQ(0U, backends_[i]->backend_service()->request_count());
  }
}

TEST_P(FailoverTest, DoesNotUsePriorityWithNoEndpoints) {
  CreateAndStartBackends(3);
  EdsResourceArgs args({
      {"locality0", CreateEndpointsForBackends(0, 1), kDefaultLocalityWeight,
       1},
      {"locality1", CreateEndpointsForBackends(1, 2), kDefaultLocalityWeight,
       2},
      {"locality2", CreateEndpointsForBackends(2, 3), kDefaultLocalityWeight,
       3},
      {"locality3", {}, kDefaultLocalityWeight, 0},
  });
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));
  WaitForBackend(DEBUG_LOCATION, 0, nullptr,
                 WaitForBackendOptions().set_reset_counters(false));
  for (size_t i = 1; i < 3; ++i) {
    EXPECT_EQ(0U, backends_[i]->backend_service()->request_count());
  }
}

TEST_P(FailoverTest, DoesNotUseLocalityWithNoEndpoints) {
  CreateAndStartBackends(1);
  EdsResourceArgs args({
      {"locality0", {}, kDefaultLocalityWeight, 0},
      {"locality1", CreateEndpointsForBackends(), kDefaultLocalityWeight, 0},
  });
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  WaitForAllBackends(DEBUG_LOCATION);
}

TEST_P(FailoverTest, Failover) {
  CreateAndStartBackends(2);
  EdsResourceArgs args({
      {"locality0", {MakeNonExistentEndpoint()}, kDefaultLocalityWeight, 1},
      {"locality1", CreateEndpointsForBackends(0, 1), kDefaultLocalityWeight,
       2},
      {"locality2", CreateEndpointsForBackends(1, 2), kDefaultLocalityWeight,
       3},
      {"locality3", {MakeNonExistentEndpoint()}, kDefaultLocalityWeight, 0},
  });
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));
  WaitForBackend(DEBUG_LOCATION, 0, nullptr,
                 WaitForBackendOptions().set_reset_counters(false));
  EXPECT_EQ(0U, backends_[1]->backend_service()->request_count());
}

TEST_P(FailoverTest, ReportsConnectingDuringFailover) {
  CreateAndStartBackends(1);

  EdsResourceArgs args({
      {"locality0", {MakeNonExistentEndpoint()}, kDefaultLocalityWeight, 0},
      {"locality1", CreateEndpointsForBackends(), kDefaultLocalityWeight, 1},
  });
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));
  ConnectionAttemptInjector injector;
  auto hold = injector.AddHold(backends_[0]->port());

  LongRunningRpc rpc;
  rpc.StartRpc(stub_.get(), RpcOptions());

  hold->Wait();

  EXPECT_EQ(channel_->GetState(false), GRPC_CHANNEL_CONNECTING);

  hold->Resume();

  LOG(INFO) << "=== WAITING FOR RPC TO FINISH ===";
  Status status = rpc.GetStatus();
  LOG(INFO) << "=== RPC FINISHED ===";
  EXPECT_TRUE(status.ok()) << "code=" << status.error_code()
                           << " message=" << status.error_message();
}

TEST_P(FailoverTest, SwitchBackToHigherPriority) {
  CreateAndStartBackends(4);
  const size_t kNumRpcs = 100;
  EdsResourceArgs args({
      {"locality0", CreateEndpointsForBackends(0, 1), kDefaultLocalityWeight,
       1},
      {"locality1", CreateEndpointsForBackends(1, 2), kDefaultLocalityWeight,
       2},
      {"locality2", CreateEndpointsForBackends(2, 3), kDefaultLocalityWeight,
       3},
      {"locality3", CreateEndpointsForBackends(3, 4), kDefaultLocalityWeight,
       0},
  });
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));
  WaitForBackend(DEBUG_LOCATION, 3);
  backends_[3]->StopListeningAndSendGoaways();
  backends_[0]->StopListeningAndSendGoaways();
  WaitForBackend(DEBUG_LOCATION, 1);
  ShutdownBackend(0);
  StartBackend(0);
  WaitForBackend(DEBUG_LOCATION, 0);
  CheckRpcSendOk(DEBUG_LOCATION, kNumRpcs);
  EXPECT_EQ(kNumRpcs, backends_[0]->backend_service()->request_count());
}

TEST_P(FailoverTest, UpdateInitialUnavailable) {
  CreateAndStartBackends(2);
  EdsResourceArgs args({
      {"locality0", {MakeNonExistentEndpoint()}, kDefaultLocalityWeight, 0},
      {"locality1", {MakeNonExistentEndpoint()}, kDefaultLocalityWeight, 1},
  });
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));
  CheckRpcSendFailure(DEBUG_LOCATION, StatusCode::UNAVAILABLE,
                      MakeConnectionFailureRegex(
                          "connections to all backends failing; last error: "));
  args = EdsResourceArgs({
      {"locality0", CreateEndpointsForBackends(0, 1), kDefaultLocalityWeight,
       0},
      {"locality1", CreateEndpointsForBackends(1, 2), kDefaultLocalityWeight,
       1},
  });
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));
  WaitForBackend(DEBUG_LOCATION, 0, [&](const RpcResult& result) {
    if (!result.status.ok()) {
      EXPECT_EQ(result.status.error_code(), StatusCode::UNAVAILABLE);
      EXPECT_THAT(result.status.error_message(),
                  ::testing::MatchesRegex(MakeConnectionFailureRegex(
                      "connections to all backends failing; last error: ")));
    }
  });
}

TEST_P(FailoverTest, UpdatePriority) {
  CreateAndStartBackends(4);
  const size_t kNumRpcs = 100;
  EdsResourceArgs args({
      {"locality0", CreateEndpointsForBackends(0, 1), kDefaultLocalityWeight,
       1},
      {"locality1", CreateEndpointsForBackends(1, 2), kDefaultLocalityWeight,
       2},
      {"locality2", CreateEndpointsForBackends(2, 3), kDefaultLocalityWeight,
       3},
      {"locality3", CreateEndpointsForBackends(3, 4), kDefaultLocalityWeight,
       0},
  });
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));
  WaitForBackend(DEBUG_LOCATION, 3, nullptr,
                 WaitForBackendOptions().set_reset_counters(false));
  EXPECT_EQ(0U, backends_[0]->backend_service()->request_count());
  EXPECT_EQ(0U, backends_[1]->backend_service()->request_count());
  EXPECT_EQ(0U, backends_[2]->backend_service()->request_count());
  args = EdsResourceArgs({
      {"locality0", CreateEndpointsForBackends(0, 1), kDefaultLocalityWeight,
       2},
      {"locality1", CreateEndpointsForBackends(1, 2), kDefaultLocalityWeight,
       0},
      {"locality2", CreateEndpointsForBackends(2, 3), kDefaultLocalityWeight,
       1},
      {"locality3", CreateEndpointsForBackends(3, 4), kDefaultLocalityWeight,
       3},
  });
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));
  WaitForBackend(DEBUG_LOCATION, 1);
  CheckRpcSendOk(DEBUG_LOCATION, kNumRpcs);
  EXPECT_EQ(kNumRpcs, backends_[1]->backend_service()->request_count());
}

TEST_P(FailoverTest, MoveAllLocalitiesInCurrentPriorityToHigherPriority) {
  CreateAndStartBackends(3);
  auto non_existent_endpoint = MakeNonExistentEndpoint();

  EdsResourceArgs args({
      {"locality0", {non_existent_endpoint}, kDefaultLocalityWeight, 0},
      {"locality1", CreateEndpointsForBackends(0, 2), kDefaultLocalityWeight,
       1},
  });
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  WaitForAllBackends(DEBUG_LOCATION, 0, 2, nullptr,
                     WaitForBackendOptions().set_reset_counters(false));
  EXPECT_EQ(0UL, backends_[2]->backend_service()->request_count());

  args = EdsResourceArgs({
      {"locality0", {non_existent_endpoint}, kDefaultLocalityWeight, 0},
      {"locality1", CreateEndpointsForBackends(0, 3), kDefaultLocalityWeight,
       0},
  });
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  WaitForBackend(DEBUG_LOCATION, 2);
}

TEST_P(FailoverTest, PriorityChildNameChurn) {
  CreateAndStartBackends(4);
  auto non_existent_endpoint = MakeNonExistentEndpoint();

  EdsResourceArgs args({
      {"locality0", {non_existent_endpoint}, kDefaultLocalityWeight, 0},
      {"locality1", CreateEndpointsForBackends(0, 1), kDefaultLocalityWeight,
       1},
      {"locality2", CreateEndpointsForBackends(1, 2), kDefaultLocalityWeight,
       2},
  });
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));
  WaitForBackend(DEBUG_LOCATION, 0);

  args = EdsResourceArgs({
      {"locality0", {non_existent_endpoint}, kDefaultLocalityWeight, 0},
      {"locality2", CreateEndpointsForBackends(1, 2), kDefaultLocalityWeight,
       1},
      {"locality3", CreateEndpointsForBackends(2, 3), kDefaultLocalityWeight,
       2},
  });
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));
  WaitForBackend(DEBUG_LOCATION, 1);

  args = EdsResourceArgs({
      {"locality0", {non_existent_endpoint}, kDefaultLocalityWeight, 0},
      {"locality4", CreateEndpointsForBackends(3, 4), kDefaultLocalityWeight,
       1},
      {"locality3", CreateEndpointsForBackends(2, 3), kDefaultLocalityWeight,
       2},
  });
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));
  WaitForBackend(DEBUG_LOCATION, 3, nullptr,
                 WaitForBackendOptions().set_reset_counters(false));

  EXPECT_EQ(0UL, backends_[2]->backend_service()->request_count());
}

using ClientLoadReportingTest = XdsEnd2endTest;

INSTANTIATE_TEST_SUITE_P(
    XdsTest, ClientLoadReportingTest,
    ::testing::Values(XdsTestType().set_enable_load_reporting()),
    &XdsTestType::Name);

MATCHER_P2(LoadMetricEq, num_requests_finished_with_metric, total_metric_value,
           "equals LoadMetric") {
  bool match = true;
  match &= ::testing::ExplainMatchResult(num_requests_finished_with_metric,
                                         arg.num_requests_finished_with_metric,
                                         result_listener);
  match &=
      ::testing::ExplainMatchResult(::testing::DoubleEq(total_metric_value),
                                    arg.total_metric_value, result_listener);
  return match;
}

TEST_P(ClientLoadReportingTest, Vanilla) {
  CreateAndStartBackends(4);
  const size_t kNumRpcsPerAddress = 10;
  const size_t kNumFailuresPerAddress = 3;
  EdsResourceArgs args({
      {"locality0", CreateEndpointsForBackends(0, 2)},
      {"locality1", CreateEndpointsForBackends(2, 4)},
  });
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  size_t num_warmup_rpcs =
      WaitForAllBackends(DEBUG_LOCATION, 0, 4, nullptr,
                         WaitForBackendOptions().set_reset_counters(false));

  xds::data::orca::v3::OrcaLoadReport backend_metrics;
  auto& named_metrics = (*backend_metrics.mutable_named_metrics());
  named_metrics["foo"] = 1.0;
  named_metrics["bar"] = 2.0;
  CheckRpcSendOk(DEBUG_LOCATION, kNumRpcsPerAddress * backends_.size(),
                 RpcOptions().set_backend_metrics(backend_metrics));
  named_metrics["foo"] = 0.3;
  named_metrics["bar"] = 0.4;
  for (size_t i = 0; i < kNumFailuresPerAddress * backends_.size(); ++i) {
    CheckRpcSendFailure(DEBUG_LOCATION, StatusCode::FAILED_PRECONDITION, "",
                        RpcOptions().set_server_fail(true).set_backend_metrics(
                            backend_metrics));
  }
  const size_t total_successful_rpcs_sent =
      (kNumRpcsPerAddress * backends_.size()) + num_warmup_rpcs;
  const size_t total_failed_rpcs_sent =
      kNumFailuresPerAddress * backends_.size();

  size_t total_rpcs_sent = 0;
  for (const auto& backend : backends_) {
    total_rpcs_sent += backend->backend_service()->request_count();
  }
  EXPECT_EQ(total_rpcs_sent,
            total_successful_rpcs_sent + total_failed_rpcs_sent);

  std::vector<ClientStats> load_report =
      balancer_->lrs_service()->WaitForLoadReport();
  ASSERT_EQ(load_report.size(), 1UL);
  ClientStats& client_stats = load_report.front();
  EXPECT_EQ(client_stats.cluster_name(), kDefaultClusterName);
  EXPECT_EQ(client_stats.eds_service_name(), kDefaultEdsServiceName);
  EXPECT_EQ(total_successful_rpcs_sent,
            client_stats.total_successful_requests());
  EXPECT_EQ(0U, client_stats.total_requests_in_progress());
  EXPECT_EQ(total_rpcs_sent, client_stats.total_issued_requests());
  EXPECT_EQ(total_failed_rpcs_sent, client_stats.total_error_requests());
  EXPECT_EQ(0U, client_stats.total_dropped_requests());
  ASSERT_THAT(
      client_stats.locality_stats(),
      ::testing::ElementsAre(::testing::Pair("locality0", ::testing::_),
                             ::testing::Pair("locality1", ::testing::_)));
  size_t num_successful_rpcs = 0;
  size_t num_failed_rpcs = 0;
  std::map<std::string, ClientStats::LocalityStats::LoadMetric>
      named_metrics_total;
  for (const auto& [_, stats] : client_stats.locality_stats()) {
    EXPECT_EQ(stats.total_requests_in_progress, 0U);
    EXPECT_EQ(stats.total_issued_requests,
              stats.total_successful_requests + stats.total_error_requests);
    num_successful_rpcs += stats.total_successful_requests;
    num_failed_rpcs += stats.total_error_requests;
    for (const auto& [name, value] : stats.load_metrics) {
      named_metrics_total[name] += value;
    }
  }
  EXPECT_EQ(num_successful_rpcs, total_successful_rpcs_sent);
  EXPECT_EQ(num_failed_rpcs, total_failed_rpcs_sent);
  EXPECT_EQ(num_successful_rpcs + num_failed_rpcs, total_rpcs_sent);
  EXPECT_THAT(
      named_metrics_total,
      ::testing::UnorderedElementsAre(
          ::testing::Pair(
              "foo",
              LoadMetricEq(
                  (kNumRpcsPerAddress + kNumFailuresPerAddress) *
                      backends_.size(),
                  (kNumRpcsPerAddress * backends_.size()) * 1.0 +
                      (kNumFailuresPerAddress * backends_.size()) * 0.3)),
          ::testing::Pair(
              "bar",
              LoadMetricEq(
                  (kNumRpcsPerAddress + kNumFailuresPerAddress) *
                      backends_.size(),
                  (kNumRpcsPerAddress * backends_.size()) * 2.0 +
                      (kNumFailuresPerAddress * backends_.size()) * 0.4))));

  EXPECT_EQ(1U, balancer_->lrs_service()->request_count());
  EXPECT_EQ(1U, balancer_->lrs_service()->response_count());
}

TEST_P(ClientLoadReportingTest, OrcaPropagation) {
  grpc_core::testing::ScopedExperimentalEnvVar env(
      "GRPC_EXPERIMENTAL_XDS_ORCA_LRS_PROPAGATION");
  CreateAndStartBackends(4);
  const size_t kNumRpcsPerAddress = 10;
  const size_t kNumFailuresPerAddress = 3;
  Cluster cluster = default_cluster_;
  cluster.add_lrs_report_endpoint_metrics("named_metrics.foo");
  cluster.add_lrs_report_endpoint_metrics("cpu_utilization");
  cluster.add_lrs_report_endpoint_metrics("mem_utilization");
  cluster.add_lrs_report_endpoint_metrics("application_utilization");
  cluster.add_lrs_report_endpoint_metrics("unknown_field");
  balancer_->ads_service()->SetCdsResource(cluster);
  EdsResourceArgs args({
      {"locality0", CreateEndpointsForBackends(0, 2)},
      {"locality1", CreateEndpointsForBackends(2, 4)},
  });
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  size_t num_warmup_rpcs =
      WaitForAllBackends(DEBUG_LOCATION, 0, 4, nullptr,
                         WaitForBackendOptions().set_reset_counters(false));

  xds::data::orca::v3::OrcaLoadReport backend_metrics;
  backend_metrics.set_cpu_utilization(0.8);
  backend_metrics.set_mem_utilization(0.6);
  backend_metrics.set_application_utilization(0.4);
  auto& named_metrics = (*backend_metrics.mutable_named_metrics());
  named_metrics["foo"] = 1.0;
  named_metrics["bar"] = 2.0;
  CheckRpcSendOk(DEBUG_LOCATION, kNumRpcsPerAddress * backends_.size(),
                 RpcOptions().set_backend_metrics(backend_metrics));
  backend_metrics.set_cpu_utilization(0.4);
  backend_metrics.set_mem_utilization(0.3);
  backend_metrics.set_application_utilization(0.2);
  named_metrics["foo"] = 0.3;
  named_metrics["bar"] = 0.4;
  for (size_t i = 0; i < kNumFailuresPerAddress * backends_.size(); ++i) {
    CheckRpcSendFailure(DEBUG_LOCATION, StatusCode::FAILED_PRECONDITION, "",
                        RpcOptions().set_server_fail(true).set_backend_metrics(
                            backend_metrics));
  }
  const size_t total_successful_rpcs_sent =
      (kNumRpcsPerAddress * backends_.size()) + num_warmup_rpcs;
  const size_t total_failed_rpcs_sent =
      kNumFailuresPerAddress * backends_.size();

  size_t total_rpcs_sent = 0;
  for (const auto& backend : backends_) {
    total_rpcs_sent += backend->backend_service()->request_count();
  }
  EXPECT_EQ(total_rpcs_sent,
            total_successful_rpcs_sent + total_failed_rpcs_sent);

  std::vector<ClientStats> load_report =
      balancer_->lrs_service()->WaitForLoadReport();
  ASSERT_EQ(load_report.size(), 1UL);
  ClientStats& client_stats = load_report.front();
  EXPECT_EQ(client_stats.cluster_name(), kDefaultClusterName);
  EXPECT_EQ(client_stats.eds_service_name(), kDefaultEdsServiceName);
  EXPECT_EQ(total_successful_rpcs_sent,
            client_stats.total_successful_requests());
  EXPECT_EQ(0U, client_stats.total_requests_in_progress());
  EXPECT_EQ(total_rpcs_sent, client_stats.total_issued_requests());
  EXPECT_EQ(total_failed_rpcs_sent, client_stats.total_error_requests());
  EXPECT_EQ(0U, client_stats.total_dropped_requests());
  ASSERT_THAT(
      client_stats.locality_stats(),
      ::testing::ElementsAre(::testing::Pair("locality0", ::testing::_),
                             ::testing::Pair("locality1", ::testing::_)));
  size_t num_successful_rpcs = 0;
  size_t num_failed_rpcs = 0;
  ClientStats::LocalityStats::LoadMetric cpu_utilization;
  ClientStats::LocalityStats::LoadMetric mem_utilization;
  ClientStats::LocalityStats::LoadMetric application_utilization;
  std::map<std::string, ClientStats::LocalityStats::LoadMetric>
      named_metrics_total;
  for (const auto& [_, stats] : client_stats.locality_stats()) {
    EXPECT_EQ(stats.total_requests_in_progress, 0U);
    EXPECT_EQ(stats.total_issued_requests,
              stats.total_successful_requests + stats.total_error_requests);
    num_successful_rpcs += stats.total_successful_requests;
    num_failed_rpcs += stats.total_error_requests;
    cpu_utilization += stats.cpu_utilization;
    mem_utilization += stats.mem_utilization;
    application_utilization += stats.application_utilization;
    for (const auto& [name, value] : stats.load_metrics) {
      named_metrics_total[name] += value;
    }
  }
  EXPECT_EQ(num_successful_rpcs, total_successful_rpcs_sent);
  EXPECT_EQ(num_failed_rpcs, total_failed_rpcs_sent);
  EXPECT_EQ(num_successful_rpcs + num_failed_rpcs, total_rpcs_sent);
  EXPECT_THAT(
      cpu_utilization,
      LoadMetricEq(
          (kNumRpcsPerAddress + kNumFailuresPerAddress) * backends_.size(),
          (kNumRpcsPerAddress * backends_.size()) * 0.8 +
              (kNumFailuresPerAddress * backends_.size()) * 0.4));
  EXPECT_THAT(
      mem_utilization,
      LoadMetricEq(
          (kNumRpcsPerAddress + kNumFailuresPerAddress) * backends_.size(),
          (kNumRpcsPerAddress * backends_.size()) * 0.6 +
              (kNumFailuresPerAddress * backends_.size()) * 0.3));
  EXPECT_THAT(
      application_utilization,
      LoadMetricEq(
          (kNumRpcsPerAddress + kNumFailuresPerAddress) * backends_.size(),
          (kNumRpcsPerAddress * backends_.size()) * 0.4 +
              (kNumFailuresPerAddress * backends_.size()) * 0.2));
  EXPECT_THAT(
      named_metrics_total,
      ::testing::UnorderedElementsAre(::testing::Pair(
          "named_metrics.foo",
          LoadMetricEq(
              (kNumRpcsPerAddress + kNumFailuresPerAddress) * backends_.size(),
              (kNumRpcsPerAddress * backends_.size()) * 1.0 +
                  (kNumFailuresPerAddress * backends_.size()) * 0.3))));

  EXPECT_EQ(1U, balancer_->lrs_service()->request_count());
  EXPECT_EQ(1U, balancer_->lrs_service()->response_count());
}

TEST_P(ClientLoadReportingTest, OrcaPropagationNamedMetricsAll) {
  grpc_core::testing::ScopedExperimentalEnvVar env(
      "GRPC_EXPERIMENTAL_XDS_ORCA_LRS_PROPAGATION");
  CreateAndStartBackends(4);
  const size_t kNumRpcsPerAddress = 10;
  const size_t kNumFailuresPerAddress = 3;
  Cluster cluster = default_cluster_;
  cluster.add_lrs_report_endpoint_metrics("named_metrics.*");
  balancer_->ads_service()->SetCdsResource(cluster);
  EdsResourceArgs args({
      {"locality0", CreateEndpointsForBackends(0, 2)},
      {"locality1", CreateEndpointsForBackends(2, 4)},
  });
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  size_t num_warmup_rpcs =
      WaitForAllBackends(DEBUG_LOCATION, 0, 4, nullptr,
                         WaitForBackendOptions().set_reset_counters(false));

  xds::data::orca::v3::OrcaLoadReport backend_metrics;
  backend_metrics.set_cpu_utilization(0.8);
  backend_metrics.set_mem_utilization(0.6);
  backend_metrics.set_application_utilization(0.4);
  auto& named_metrics = (*backend_metrics.mutable_named_metrics());
  named_metrics["foo"] = 1.0;
  named_metrics["bar"] = 2.0;
  CheckRpcSendOk(DEBUG_LOCATION, kNumRpcsPerAddress * backends_.size(),
                 RpcOptions().set_backend_metrics(backend_metrics));
  backend_metrics.set_cpu_utilization(0.4);
  backend_metrics.set_mem_utilization(0.3);
  backend_metrics.set_application_utilization(0.2);
  named_metrics["foo"] = 0.3;
  named_metrics["bar"] = 0.4;
  for (size_t i = 0; i < kNumFailuresPerAddress * backends_.size(); ++i) {
    CheckRpcSendFailure(DEBUG_LOCATION, StatusCode::FAILED_PRECONDITION, "",
                        RpcOptions().set_server_fail(true).set_backend_metrics(
                            backend_metrics));
  }
  const size_t total_successful_rpcs_sent =
      (kNumRpcsPerAddress * backends_.size()) + num_warmup_rpcs;
  const size_t total_failed_rpcs_sent =
      kNumFailuresPerAddress * backends_.size();

  size_t total_rpcs_sent = 0;
  for (const auto& backend : backends_) {
    total_rpcs_sent += backend->backend_service()->request_count();
  }
  EXPECT_EQ(total_rpcs_sent,
            total_successful_rpcs_sent + total_failed_rpcs_sent);

  std::vector<ClientStats> load_report =
      balancer_->lrs_service()->WaitForLoadReport();
  ASSERT_EQ(load_report.size(), 1UL);
  ClientStats& client_stats = load_report.front();
  EXPECT_EQ(client_stats.cluster_name(), kDefaultClusterName);
  EXPECT_EQ(client_stats.eds_service_name(), kDefaultEdsServiceName);
  EXPECT_EQ(total_successful_rpcs_sent,
            client_stats.total_successful_requests());
  EXPECT_EQ(0U, client_stats.total_requests_in_progress());
  EXPECT_EQ(total_rpcs_sent, client_stats.total_issued_requests());
  EXPECT_EQ(total_failed_rpcs_sent, client_stats.total_error_requests());
  EXPECT_EQ(0U, client_stats.total_dropped_requests());
  ASSERT_THAT(
      client_stats.locality_stats(),
      ::testing::ElementsAre(::testing::Pair("locality0", ::testing::_),
                             ::testing::Pair("locality1", ::testing::_)));
  size_t num_successful_rpcs = 0;
  size_t num_failed_rpcs = 0;
  std::map<std::string, ClientStats::LocalityStats::LoadMetric>
      named_metrics_total;
  for (const auto& [_, stats] : client_stats.locality_stats()) {
    EXPECT_EQ(stats.total_requests_in_progress, 0U);
    EXPECT_EQ(stats.total_issued_requests,
              stats.total_successful_requests + stats.total_error_requests);
    num_successful_rpcs += stats.total_successful_requests;
    num_failed_rpcs += stats.total_error_requests;
    for (const auto& [name, value] : stats.load_metrics) {
      named_metrics_total[name] += value;
    }
  }
  EXPECT_EQ(num_successful_rpcs, total_successful_rpcs_sent);
  EXPECT_EQ(num_failed_rpcs, total_failed_rpcs_sent);
  EXPECT_EQ(num_successful_rpcs + num_failed_rpcs, total_rpcs_sent);
  EXPECT_THAT(
      named_metrics_total,
      ::testing::UnorderedElementsAre(
          ::testing::Pair(
              "named_metrics.foo",
              LoadMetricEq(
                  (kNumRpcsPerAddress + kNumFailuresPerAddress) *
                      backends_.size(),
                  (kNumRpcsPerAddress * backends_.size()) * 1.0 +
                      (kNumFailuresPerAddress * backends_.size()) * 0.3)),
          ::testing::Pair(
              "named_metrics.bar",
              LoadMetricEq(
                  (kNumRpcsPerAddress + kNumFailuresPerAddress) *
                      backends_.size(),
                  (kNumRpcsPerAddress * backends_.size()) * 2.0 +
                      (kNumFailuresPerAddress * backends_.size()) * 0.4))));

  EXPECT_EQ(1U, balancer_->lrs_service()->request_count());
  EXPECT_EQ(1U, balancer_->lrs_service()->response_count());
}

TEST_P(ClientLoadReportingTest, OrcaPropagationNotConfigured) {
  grpc_core::testing::ScopedExperimentalEnvVar env(
      "GRPC_EXPERIMENTAL_XDS_ORCA_LRS_PROPAGATION");
  CreateAndStartBackends(4);
  const size_t kNumRpcsPerAddress = 10;
  const size_t kNumFailuresPerAddress = 3;
  EdsResourceArgs args({
      {"locality0", CreateEndpointsForBackends(0, 2)},
      {"locality1", CreateEndpointsForBackends(2, 4)},
  });
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  size_t num_warmup_rpcs =
      WaitForAllBackends(DEBUG_LOCATION, 0, 4, nullptr,
                         WaitForBackendOptions().set_reset_counters(false));

  xds::data::orca::v3::OrcaLoadReport backend_metrics;
  backend_metrics.set_cpu_utilization(0.8);
  backend_metrics.set_mem_utilization(0.6);
  backend_metrics.set_application_utilization(0.4);
  auto& named_metrics = (*backend_metrics.mutable_named_metrics());
  named_metrics["foo"] = 1.0;
  named_metrics["bar"] = 2.0;
  CheckRpcSendOk(DEBUG_LOCATION, kNumRpcsPerAddress * backends_.size(),
                 RpcOptions().set_backend_metrics(backend_metrics));
  backend_metrics.set_cpu_utilization(0.4);
  backend_metrics.set_mem_utilization(0.3);
  backend_metrics.set_application_utilization(0.2);
  named_metrics["foo"] = 0.3;
  named_metrics["bar"] = 0.4;
  for (size_t i = 0; i < kNumFailuresPerAddress * backends_.size(); ++i) {
    CheckRpcSendFailure(DEBUG_LOCATION, StatusCode::FAILED_PRECONDITION, "",
                        RpcOptions().set_server_fail(true).set_backend_metrics(
                            backend_metrics));
  }
  const size_t total_successful_rpcs_sent =
      (kNumRpcsPerAddress * backends_.size()) + num_warmup_rpcs;
  const size_t total_failed_rpcs_sent =
      kNumFailuresPerAddress * backends_.size();

  size_t total_rpcs_sent = 0;
  for (const auto& backend : backends_) {
    total_rpcs_sent += backend->backend_service()->request_count();
  }
  EXPECT_EQ(total_rpcs_sent,
            total_successful_rpcs_sent + total_failed_rpcs_sent);

  std::vector<ClientStats> load_report =
      balancer_->lrs_service()->WaitForLoadReport();
  ASSERT_EQ(load_report.size(), 1UL);
  ClientStats& client_stats = load_report.front();
  EXPECT_EQ(client_stats.cluster_name(), kDefaultClusterName);
  EXPECT_EQ(client_stats.eds_service_name(), kDefaultEdsServiceName);
  EXPECT_EQ(total_successful_rpcs_sent,
            client_stats.total_successful_requests());
  EXPECT_EQ(0U, client_stats.total_requests_in_progress());
  EXPECT_EQ(total_rpcs_sent, client_stats.total_issued_requests());
  EXPECT_EQ(total_failed_rpcs_sent, client_stats.total_error_requests());
  EXPECT_EQ(0U, client_stats.total_dropped_requests());
  ASSERT_THAT(
      client_stats.locality_stats(),
      ::testing::ElementsAre(::testing::Pair("locality0", ::testing::_),
                             ::testing::Pair("locality1", ::testing::_)));
  size_t num_successful_rpcs = 0;
  size_t num_failed_rpcs = 0;
  std::map<std::string, ClientStats::LocalityStats::LoadMetric>
      named_metrics_total;
  for (const auto& [_, stats] : client_stats.locality_stats()) {
    EXPECT_EQ(stats.total_requests_in_progress, 0U);
    EXPECT_EQ(stats.total_issued_requests,
              stats.total_successful_requests + stats.total_error_requests);
    num_successful_rpcs += stats.total_successful_requests;
    num_failed_rpcs += stats.total_error_requests;
    for (const auto& [name, value] : stats.load_metrics) {
      named_metrics_total[name] += value;
    }
  }
  EXPECT_EQ(num_successful_rpcs, total_successful_rpcs_sent);
  EXPECT_EQ(num_failed_rpcs, total_failed_rpcs_sent);
  EXPECT_EQ(num_successful_rpcs + num_failed_rpcs, total_rpcs_sent);
  EXPECT_THAT(named_metrics_total, ::testing::UnorderedElementsAre());

  EXPECT_EQ(1U, balancer_->lrs_service()->request_count());
  EXPECT_EQ(1U, balancer_->lrs_service()->response_count());
}

TEST_P(ClientLoadReportingTest, SendAllClusters) {
  CreateAndStartBackends(2);
  balancer_->lrs_service()->set_send_all_clusters(true);
  const size_t kNumRpcsPerAddress = 10;
  const size_t kNumFailuresPerAddress = 3;
  EdsResourceArgs args({{"locality0", CreateEndpointsForBackends()}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  size_t num_warmup_rpcs = WaitForAllBackends(DEBUG_LOCATION);

  xds::data::orca::v3::OrcaLoadReport backend_metrics;
  auto& named_metrics = (*backend_metrics.mutable_named_metrics());
  named_metrics["foo"] = 1.0;
  named_metrics["bar"] = 2.0;
  CheckRpcSendOk(DEBUG_LOCATION, kNumRpcsPerAddress * backends_.size(),
                 RpcOptions().set_backend_metrics(backend_metrics));
  named_metrics["foo"] = 0.3;
  named_metrics["bar"] = 0.4;
  for (size_t i = 0; i < kNumFailuresPerAddress * backends_.size(); ++i) {
    CheckRpcSendFailure(DEBUG_LOCATION, StatusCode::FAILED_PRECONDITION, "",
                        RpcOptions().set_server_fail(true).set_backend_metrics(
                            backend_metrics));
  }

  for (size_t i = 0; i < backends_.size(); ++i) {
    EXPECT_EQ(kNumRpcsPerAddress + kNumFailuresPerAddress,
              backends_[i]->backend_service()->request_count());
  }

  std::vector<ClientStats> load_report =
      balancer_->lrs_service()->WaitForLoadReport();
  ASSERT_EQ(load_report.size(), 1UL);
  ClientStats& client_stats = load_report.front();
  EXPECT_EQ(kNumRpcsPerAddress * backends_.size() + num_warmup_rpcs,
            client_stats.total_successful_requests());
  EXPECT_EQ(0U, client_stats.total_requests_in_progress());
  EXPECT_EQ((kNumRpcsPerAddress + kNumFailuresPerAddress) * backends_.size() +
                num_warmup_rpcs,
            client_stats.total_issued_requests());
  EXPECT_EQ(kNumFailuresPerAddress * backends_.size(),
            client_stats.total_error_requests());
  EXPECT_EQ(0U, client_stats.total_dropped_requests());
  EXPECT_THAT(
      client_stats.locality_stats(),
      ::testing::ElementsAre(::testing::Pair(
          "locality0",
          ::testing::Field(
              &ClientStats::LocalityStats::load_metrics,
              ::testing::UnorderedElementsAre(
                  ::testing::Pair(
                      "foo",
                      LoadMetricEq(
                          (kNumRpcsPerAddress + kNumFailuresPerAddress) *
                              backends_.size(),
                          (kNumRpcsPerAddress * backends_.size()) * 1.0 +
                              (kNumFailuresPerAddress * backends_.size()) *
                                  0.3)),
                  ::testing::Pair(
                      "bar",
                      LoadMetricEq(
                          (kNumRpcsPerAddress + kNumFailuresPerAddress) *
                              backends_.size(),
                          (kNumRpcsPerAddress * backends_.size()) * 2.0 +
                              (kNumFailuresPerAddress * backends_.size()) *
                                  0.4)))))));

  EXPECT_EQ(1U, balancer_->lrs_service()->request_count());
  EXPECT_EQ(1U, balancer_->lrs_service()->response_count());
}

TEST_P(ClientLoadReportingTest, HonorsClustersRequestedByLrsServer) {
  CreateAndStartBackends(1);
  balancer_->lrs_service()->set_cluster_names({"bogus"});
  EdsResourceArgs args({{"locality0", CreateEndpointsForBackends()}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  WaitForAllBackends(DEBUG_LOCATION);

  std::vector<ClientStats> load_report =
      balancer_->lrs_service()->WaitForLoadReport();
  ASSERT_EQ(load_report.size(), 0UL);

  EXPECT_EQ(1U, balancer_->lrs_service()->request_count());
  EXPECT_EQ(1U, balancer_->lrs_service()->response_count());
}

TEST_P(ClientLoadReportingTest, BalancerRestart) {
  CreateAndStartBackends(4);
  EdsResourceArgs args({{"locality0", CreateEndpointsForBackends(0, 2)}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  size_t num_rpcs = WaitForAllBackends(DEBUG_LOCATION, 0, 2);
  std::vector<ClientStats> load_report =
      balancer_->lrs_service()->WaitForLoadReport();
  ASSERT_EQ(load_report.size(), 1UL);
  ClientStats client_stats = std::move(load_report.front());
  EXPECT_EQ(num_rpcs, client_stats.total_successful_requests());
  EXPECT_EQ(0U, client_stats.total_requests_in_progress());
  EXPECT_EQ(0U, client_stats.total_error_requests());
  EXPECT_EQ(0U, client_stats.total_dropped_requests());
  EXPECT_THAT(client_stats.locality_stats(),
              ::testing::ElementsAre(::testing::Pair(
                  "locality0",
                  ::testing::Field(&ClientStats::LocalityStats::load_metrics,
                                   ::testing::IsEmpty()))));

  balancer_->Shutdown();

  // Note: We need to use WaitForAllBackends() here instead of just

  ResetBackendCounters();
  num_rpcs = WaitForAllBackends(DEBUG_LOCATION, 0, 2);

  balancer_->Start();
  args = EdsResourceArgs({{"locality0", CreateEndpointsForBackends(2, 4)}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  num_rpcs += WaitForAllBackends(DEBUG_LOCATION, 2, 4);

  xds::data::orca::v3::OrcaLoadReport backend_metrics;
  auto& named_metrics = (*backend_metrics.mutable_named_metrics());
  named_metrics["foo"] = 1.0;
  named_metrics["bar"] = 2.0;
  CheckRpcSendOk(DEBUG_LOCATION, 2,
                 RpcOptions().set_backend_metrics(backend_metrics));
  num_rpcs += 2;

  load_report = balancer_->lrs_service()->WaitForLoadReport();
  ASSERT_EQ(load_report.size(), 1UL);
  client_stats = std::move(load_report.front());
  EXPECT_EQ(num_rpcs, client_stats.total_successful_requests());
  EXPECT_EQ(0U, client_stats.total_requests_in_progress());
  EXPECT_EQ(0U, client_stats.total_error_requests());
  EXPECT_EQ(0U, client_stats.total_dropped_requests());
  EXPECT_THAT(client_stats.locality_stats(),
              ::testing::ElementsAre(::testing::Pair(
                  "locality0",
                  ::testing::Field(
                      &ClientStats::LocalityStats::load_metrics,
                      ::testing::UnorderedElementsAre(
                          ::testing::Pair("foo", LoadMetricEq(2, 2.0)),
                          ::testing::Pair("bar", LoadMetricEq(2, 4.0)))))));
}

TEST_P(ClientLoadReportingTest, ChangeClusters) {
  CreateAndStartBackends(4);
  const char* kNewClusterName = "new_cluster_name";
  const char* kNewEdsServiceName = "new_eds_service_name";
  balancer_->lrs_service()->set_cluster_names(
      {kDefaultClusterName, kNewClusterName});

  EdsResourceArgs args({
      {"locality0", CreateEndpointsForBackends(0, 2)},
  });
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  EdsResourceArgs args2({
      {"locality1", CreateEndpointsForBackends(2, 4)},
  });
  balancer_->ads_service()->SetEdsResource(
      BuildEdsResource(args2, kNewEdsServiceName));

  Cluster new_cluster = default_cluster_;
  new_cluster.set_name(kNewClusterName);
  new_cluster.mutable_eds_cluster_config()->set_service_name(
      kNewEdsServiceName);
  balancer_->ads_service()->SetCdsResource(new_cluster);

  size_t num_rpcs = WaitForAllBackends(DEBUG_LOCATION, 0, 2);

  std::vector<ClientStats> load_report =
      balancer_->lrs_service()->WaitForLoadReport();
  EXPECT_THAT(
      load_report,
      ::testing::ElementsAre(::testing::AllOf(
          ::testing::Property(&ClientStats::cluster_name, kDefaultClusterName),
          ::testing::Property(&ClientStats::eds_service_name,
                              kDefaultEdsServiceName),
          ::testing::Property(
              &ClientStats::locality_stats,
              ::testing::ElementsAre(::testing::Pair(
                  "locality0",
                  ::testing::AllOf(
                      ::testing::Field(&ClientStats::LocalityStats::
                                           total_successful_requests,
                                       num_rpcs),
                      ::testing::Field(&ClientStats::LocalityStats::
                                           total_requests_in_progress,
                                       0UL),
                      ::testing::Field(
                          &ClientStats::LocalityStats::total_error_requests,
                          0UL),
                      ::testing::Field(
                          &ClientStats::LocalityStats::total_issued_requests,
                          num_rpcs),
                      ::testing::Field(
                          &ClientStats::LocalityStats::load_metrics,
                          ::testing::IsEmpty()))))),
          ::testing::Property(&ClientStats::total_dropped_requests, 0UL))));

  RouteConfiguration new_route_config = default_route_config_;
  new_route_config.mutable_virtual_hosts(0)
      ->mutable_routes(0)
      ->mutable_route()
      ->set_cluster(kNewClusterName);
  SetListenerAndRouteConfiguration(balancer_.get(), default_listener_,
                                   new_route_config);

  num_rpcs = WaitForAllBackends(DEBUG_LOCATION, 2, 4);

  load_report = balancer_->lrs_service()->WaitForLoadReport();
  EXPECT_THAT(
      load_report,
      ::testing::ElementsAre(
          ::testing::AllOf(
              ::testing::Property(&ClientStats::cluster_name,
                                  kDefaultClusterName),
              ::testing::Property(&ClientStats::eds_service_name,
                                  kDefaultEdsServiceName),
              ::testing::Property(
                  &ClientStats::locality_stats,
                  ::testing::ElementsAre(::testing::Pair(
                      "locality0",
                      ::testing::AllOf(
                          ::testing::Field(&ClientStats::LocalityStats::
                                               total_successful_requests,
                                           ::testing::Lt(num_rpcs)),
                          ::testing::Field(&ClientStats::LocalityStats::
                                               total_requests_in_progress,
                                           0UL),
                          ::testing::Field(
                              &ClientStats::LocalityStats::total_error_requests,
                              0UL),
                          ::testing::Field(&ClientStats::LocalityStats::
                                               total_issued_requests,
                                           ::testing::Le(num_rpcs)),
                          ::testing::Field(
                              &ClientStats::LocalityStats::load_metrics,
                              ::testing::IsEmpty()))))),
              ::testing::Property(&ClientStats::total_dropped_requests, 0UL)),
          ::testing::AllOf(
              ::testing::Property(&ClientStats::cluster_name, kNewClusterName),
              ::testing::Property(&ClientStats::eds_service_name,
                                  kNewEdsServiceName),
              ::testing::Property(
                  &ClientStats::locality_stats,
                  ::testing::ElementsAre(::testing::Pair(
                      "locality1",
                      ::testing::AllOf(
                          ::testing::Field(&ClientStats::LocalityStats::
                                               total_successful_requests,
                                           ::testing::Le(num_rpcs)),
                          ::testing::Field(&ClientStats::LocalityStats::
                                               total_requests_in_progress,
                                           0UL),
                          ::testing::Field(
                              &ClientStats::LocalityStats::total_error_requests,
                              0UL),
                          ::testing::Field(&ClientStats::LocalityStats::
                                               total_issued_requests,
                                           ::testing::Le(num_rpcs)),
                          ::testing::Field(
                              &ClientStats::LocalityStats::load_metrics,
                              ::testing::IsEmpty()))))),
              ::testing::Property(&ClientStats::total_dropped_requests, 0UL))));
  size_t total_ok = 0;
  for (const ClientStats& client_stats : load_report) {
    total_ok += client_stats.total_successful_requests();
  }
  EXPECT_EQ(total_ok, num_rpcs);

  EXPECT_EQ(1U, balancer_->lrs_service()->request_count());
  EXPECT_EQ(1U, balancer_->lrs_service()->response_count());
}

TEST_P(ClientLoadReportingTest, DropStats) {
  CreateAndStartBackends(1);
  const uint32_t kDropPerMillionForLb = 100000;
  const uint32_t kDropPerMillionForThrottle = 200000;
  const double kErrorTolerance = 0.05;
  const double kDropRateForLb = kDropPerMillionForLb / 1000000.0;
  const double kDropRateForThrottle = kDropPerMillionForThrottle / 1000000.0;
  const double kDropRateForLbAndThrottle =
      kDropRateForLb + ((1 - kDropRateForLb) * kDropRateForThrottle);
  const size_t kNumRpcs =
      ComputeIdealNumRpcs(kDropRateForLbAndThrottle, kErrorTolerance);

  EdsResourceArgs args({{"locality0", CreateEndpointsForBackends()}});
  args.drop_categories = {{kLbDropType, kDropPerMillionForLb},
                          {kThrottleDropType, kDropPerMillionForThrottle}};
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  size_t num_drops = SendRpcsAndCountFailuresWithMessage(
      DEBUG_LOCATION, kNumRpcs, StatusCode::UNAVAILABLE,
      kStatusMessageDropPrefix);

  const double seen_drop_rate = static_cast<double>(num_drops) / kNumRpcs;
  EXPECT_THAT(seen_drop_rate, ::testing::DoubleNear(kDropRateForLbAndThrottle,
                                                    kErrorTolerance));

  ClientStats client_stats;
  do {
    std::vector<ClientStats> load_reports =
        balancer_->lrs_service()->WaitForLoadReport();
    for (const auto& load_report : load_reports) {
      client_stats += load_report;
    }
  } while (client_stats.total_issued_requests() +
               client_stats.total_dropped_requests() <
           kNumRpcs);
  EXPECT_EQ(num_drops, client_stats.total_dropped_requests());
  EXPECT_THAT(static_cast<double>(client_stats.dropped_requests(kLbDropType)) /
                  kNumRpcs,
              ::testing::DoubleNear(kDropRateForLb, kErrorTolerance));
  EXPECT_THAT(
      static_cast<double>(client_stats.dropped_requests(kThrottleDropType)) /
          (kNumRpcs * (1 - kDropRateForLb)),
      ::testing::DoubleNear(kDropRateForThrottle, kErrorTolerance));
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
  grpc_core::RegisterFakeStatsPlugin();
  grpc_init();
  grpc::testing::ConnectionAttemptInjector::Init();
  const auto result = RUN_ALL_TESTS();
  grpc_shutdown();
  return result;
}
