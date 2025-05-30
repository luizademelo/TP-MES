// Copyright 2017 gRPC authors.

#include <chrono>
#include <string>
#include <thread>
#include <vector>

#include "absl/log/log.h"
#include "envoy/extensions/filters/http/fault/v3/fault.pb.h"
#include "envoy/extensions/filters/http/router/v3/router.pb.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "src/core/client_channel/backup_poller.h"
#include "src/core/config/config_vars.h"
#include "test/core/test_util/scoped_env_var.h"
#include "test/cpp/end2end/xds/xds_end2end_test_lib.h"

namespace grpc {
namespace testing {
namespace {

using std::chrono::system_clock;

using LdsTest = XdsEnd2endTest;

INSTANTIATE_TEST_SUITE_P(XdsTest, LdsTest, ::testing::Values(XdsTestType()),
                         &XdsTestType::Name);

TEST_P(LdsTest, NacksInvalidListener) {
  auto listener = default_listener_;
  listener.clear_api_listener();
  balancer_->ads_service()->SetLdsResource(listener);
  const auto response_state = WaitForLdsNack(DEBUG_LOCATION);
  ASSERT_TRUE(response_state.has_value()) << "timed out waiting for NACK";
  EXPECT_THAT(
      response_state->error_message,
      ::testing::HasSubstr("Listener has neither address nor ApiListener"));
}

TEST_P(LdsTest, NotAnApiListener) {
  Listener listener = default_server_listener_;
  listener.set_name(kServerName);
  auto hcm = ServerHcmAccessor().Unpack(listener);
  auto* rds = hcm.mutable_rds();
  rds->set_route_config_name(kDefaultRouteConfigurationName);
  rds->mutable_config_source()->mutable_self();
  ServerHcmAccessor().Pack(hcm, &listener);
  balancer_->ads_service()->SetLdsResource(listener);

  CheckRpcSendFailure(DEBUG_LOCATION, StatusCode::UNAVAILABLE,
                      absl::StrCat("empty address list \\(LDS resource ",
                                   kServerName, ": not an API listener\\)"));

  const auto deadline =
      absl::Now() + (absl::Seconds(30) * grpc_test_slowdown_factor());
  while (true) {
    ASSERT_LT(absl::Now(), deadline) << "timed out waiting for LDS ACK";
    auto response_state = balancer_->ads_service()->lds_response_state();
    if (response_state.has_value()) {
      EXPECT_EQ(response_state->state, AdsServiceImpl::ResponseState::ACKED);
      break;
    }
    absl::SleepFor(absl::Seconds(1) * grpc_test_slowdown_factor());
  }
}

class LdsDeletionTest : public XdsEnd2endTest {
 protected:
  void SetUp() override {}
};

INSTANTIATE_TEST_SUITE_P(XdsTest, LdsDeletionTest,
                         ::testing::Values(XdsTestType()), &XdsTestType::Name);

TEST_P(LdsDeletionTest, ListenerDeletedFailsByDefault) {
  InitClient();
  CreateAndStartBackends(1);
  EdsResourceArgs args({{"locality0", CreateEndpointsForBackends()}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  WaitForAllBackends(DEBUG_LOCATION);

  balancer_->ads_service()->UnsetResource(kLdsTypeUrl, kServerName);

  SendRpcsUntilFailure(
      DEBUG_LOCATION, StatusCode::UNAVAILABLE,
      absl::StrCat("empty address list \\(LDS resource ", kServerName,
                   ": does not exist \\(node ID:xds_end2end_test\\)\\)"));

  auto response_state = balancer_->ads_service()->lds_response_state();
  ASSERT_TRUE(response_state.has_value());
  EXPECT_EQ(response_state->state, AdsServiceImpl::ResponseState::ACKED);
}

TEST_P(LdsDeletionTest, ListenerDeletionIgnored) {
  InitClient(MakeBootstrapBuilder().SetIgnoreResourceDeletion());
  CreateAndStartBackends(2);

  EdsResourceArgs args({{"locality0", CreateEndpointsForBackends(0, 1)}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));
  WaitForAllBackends(DEBUG_LOCATION, 0, 1);

  auto response_state = balancer_->ads_service()->lds_response_state();
  ASSERT_TRUE(response_state.has_value());
  EXPECT_EQ(response_state->state, AdsServiceImpl::ResponseState::ACKED);

  balancer_->ads_service()->UnsetResource(kLdsTypeUrl, kServerName);
  const auto deadline =
      absl::Now() + (absl::Seconds(30) * grpc_test_slowdown_factor());
  while (true) {
    ASSERT_LT(absl::Now(), deadline) << "timed out waiting for LDS ACK";
    response_state = balancer_->ads_service()->lds_response_state();
    if (response_state.has_value()) break;
    absl::SleepFor(absl::Seconds(1) * grpc_test_slowdown_factor());
  }
  EXPECT_EQ(response_state->state, AdsServiceImpl::ResponseState::ACKED);

  CheckRpcSendOk(DEBUG_LOCATION);

  const char* kNewClusterName = "new_cluster_name";
  const char* kNewEdsResourceName = "new_eds_resource_name";
  auto cluster = default_cluster_;
  cluster.set_name(kNewClusterName);
  cluster.mutable_eds_cluster_config()->set_service_name(kNewEdsResourceName);
  balancer_->ads_service()->SetCdsResource(cluster);
  args = EdsResourceArgs({{"locality0", CreateEndpointsForBackends(1, 2)}});
  balancer_->ads_service()->SetEdsResource(
      BuildEdsResource(args, kNewEdsResourceName));
  RouteConfiguration new_route_config = default_route_config_;
  new_route_config.mutable_virtual_hosts(0)
      ->mutable_routes(0)
      ->mutable_route()
      ->set_cluster(kNewClusterName);
  SetListenerAndRouteConfiguration(balancer_.get(), default_listener_,
                                   new_route_config);

  WaitForAllBackends(DEBUG_LOCATION, 1, 2);
}

TEST_P(LdsDeletionTest,
       ListenerDeletionIgnoredByDefaultWhenDataErrorHandlingEnabled) {
  grpc_core::testing::ScopedExperimentalEnvVar env(
      "GRPC_EXPERIMENTAL_XDS_DATA_ERROR_HANDLING");
  InitClient();
  CreateAndStartBackends(2);

  EdsResourceArgs args({{"locality0", CreateEndpointsForBackends(0, 1)}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));
  WaitForAllBackends(DEBUG_LOCATION, 0, 1);

  auto response_state = balancer_->ads_service()->lds_response_state();
  ASSERT_TRUE(response_state.has_value());
  EXPECT_EQ(response_state->state, AdsServiceImpl::ResponseState::ACKED);

  balancer_->ads_service()->UnsetResource(kLdsTypeUrl, kServerName);
  const auto deadline =
      absl::Now() + (absl::Seconds(30) * grpc_test_slowdown_factor());
  while (true) {
    ASSERT_LT(absl::Now(), deadline) << "timed out waiting for LDS ACK";
    response_state = balancer_->ads_service()->lds_response_state();
    if (response_state.has_value()) break;
    absl::SleepFor(absl::Seconds(1) * grpc_test_slowdown_factor());
  }
  EXPECT_EQ(response_state->state, AdsServiceImpl::ResponseState::ACKED);

  CheckRpcSendOk(DEBUG_LOCATION);

  const char* kNewClusterName = "new_cluster_name";
  const char* kNewEdsResourceName = "new_eds_resource_name";
  auto cluster = default_cluster_;
  cluster.set_name(kNewClusterName);
  cluster.mutable_eds_cluster_config()->set_service_name(kNewEdsResourceName);
  balancer_->ads_service()->SetCdsResource(cluster);
  args = EdsResourceArgs({{"locality0", CreateEndpointsForBackends(1, 2)}});
  balancer_->ads_service()->SetEdsResource(
      BuildEdsResource(args, kNewEdsResourceName));
  RouteConfiguration new_route_config = default_route_config_;
  new_route_config.mutable_virtual_hosts(0)
      ->mutable_routes(0)
      ->mutable_route()
      ->set_cluster(kNewClusterName);
  SetListenerAndRouteConfiguration(balancer_.get(), default_listener_,
                                   new_route_config);

  WaitForAllBackends(DEBUG_LOCATION, 1, 2);
}

TEST_P(LdsDeletionTest, ListenerDeletedFailsWithFailOnDataErrors) {
  grpc_core::testing::ScopedExperimentalEnvVar env(
      "GRPC_EXPERIMENTAL_XDS_DATA_ERROR_HANDLING");
  InitClient(MakeBootstrapBuilder().SetFailOnDataErrors());
  CreateAndStartBackends(1);
  EdsResourceArgs args({{"locality0", CreateEndpointsForBackends()}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  WaitForAllBackends(DEBUG_LOCATION);

  balancer_->ads_service()->UnsetResource(kLdsTypeUrl, kServerName);

  SendRpcsUntilFailure(
      DEBUG_LOCATION, StatusCode::UNAVAILABLE,
      absl::StrCat("empty address list \\(LDS resource ", kServerName,
                   ": does not exist \\(node ID:xds_end2end_test\\)\\)"));

  auto response_state = balancer_->ads_service()->lds_response_state();
  ASSERT_TRUE(response_state.has_value());
  EXPECT_EQ(response_state->state, AdsServiceImpl::ResponseState::ACKED);
}

using LdsRdsInteractionTest = XdsEnd2endTest;

INSTANTIATE_TEST_SUITE_P(
    XdsTest, LdsRdsInteractionTest,
    ::testing::Values(XdsTestType().set_enable_rds_testing()),
    &XdsTestType::Name);

TEST_P(LdsRdsInteractionTest, SwitchFromRdsToInlineRouteConfig) {
  CreateAndStartBackends(2);

  EdsResourceArgs args({{"locality0", CreateEndpointsForBackends(0, 1)}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));
  WaitForBackend(DEBUG_LOCATION, 0);

  auto response_state = balancer_->ads_service()->rds_response_state();
  ASSERT_TRUE(response_state.has_value());
  EXPECT_EQ(response_state->state, AdsServiceImpl::ResponseState::ACKED);

  const char* kNewClusterName = "new_cluster_name";
  const char* kNewEdsResourceName = "new_eds_resource_name";
  auto cluster = default_cluster_;
  cluster.set_name(kNewClusterName);
  cluster.mutable_eds_cluster_config()->set_service_name(kNewEdsResourceName);
  balancer_->ads_service()->SetCdsResource(cluster);
  args = EdsResourceArgs({{"locality0", CreateEndpointsForBackends(1, 2)}});
  balancer_->ads_service()->SetEdsResource(
      BuildEdsResource(args, kNewEdsResourceName));
  RouteConfiguration new_route_config = default_route_config_;
  new_route_config.mutable_virtual_hosts(0)
      ->mutable_routes(0)
      ->mutable_route()
      ->set_cluster(kNewClusterName);
  Listener listener = default_listener_;
  HttpConnectionManager http_connection_manager =
      ClientHcmAccessor().Unpack(listener);
  *http_connection_manager.mutable_route_config() = new_route_config;
  ClientHcmAccessor().Pack(http_connection_manager, &listener);
  balancer_->ads_service()->SetLdsResource(listener);

  WaitForBackend(DEBUG_LOCATION, 1);

  new_route_config = default_route_config_;
  new_route_config.mutable_virtual_hosts(0)->add_domains("foo.example.com");
  balancer_->ads_service()->SetRdsResource(new_route_config);

  const auto deadline =
      absl::Now() + (absl::Seconds(30) * grpc_test_slowdown_factor());
  while (true) {
    ASSERT_LT(absl::Now(), deadline) << "timed out waiting for RDS ACK";
    response_state = balancer_->ads_service()->rds_response_state();
    if (response_state.has_value()) break;
    absl::SleepFor(absl::Seconds(1) * grpc_test_slowdown_factor());
  }
  EXPECT_EQ(response_state->state, AdsServiceImpl::ResponseState::ACKED);

  ResetBackendCounters();
  CheckRpcSendOk(DEBUG_LOCATION);
  EXPECT_EQ(0, backends_[0]->backend_service()->request_count());
  EXPECT_EQ(1, backends_[1]->backend_service()->request_count());
}

TEST_P(LdsRdsInteractionTest, SwitchFromInlineRouteConfigToRds) {
  CreateAndStartBackends(2);

  const char* kNewClusterName = "new_cluster_name";
  const char* kNewEdsResourceName = "new_eds_resource_name";
  auto cluster = default_cluster_;
  cluster.set_name(kNewClusterName);
  cluster.mutable_eds_cluster_config()->set_service_name(kNewEdsResourceName);
  balancer_->ads_service()->SetCdsResource(cluster);
  EdsResourceArgs args({{"locality0", CreateEndpointsForBackends(0, 1)}});
  balancer_->ads_service()->SetEdsResource(
      BuildEdsResource(args, kNewEdsResourceName));
  RouteConfiguration route_config = default_route_config_;
  route_config.mutable_virtual_hosts(0)
      ->mutable_routes(0)
      ->mutable_route()
      ->set_cluster(kNewClusterName);
  Listener listener = default_listener_;
  HttpConnectionManager http_connection_manager =
      ClientHcmAccessor().Unpack(listener);
  *http_connection_manager.mutable_route_config() = route_config;
  ClientHcmAccessor().Pack(http_connection_manager, &listener);
  balancer_->ads_service()->SetLdsResource(listener);

  WaitForBackend(DEBUG_LOCATION, 0);

  ASSERT_FALSE(balancer_->ads_service()->rds_response_state().has_value());

  args = EdsResourceArgs({{"locality0", CreateEndpointsForBackends(1, 2)}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));
  route_config = default_route_config_;
  auto* config_map = route_config.mutable_virtual_hosts(0)
                         ->mutable_routes(0)
                         ->mutable_typed_per_filter_config();
  (*config_map)["envoy.fault"].PackFrom(
      envoy::extensions::filters::http::fault::v3::HTTPFault());
  envoy::extensions::filters::http::fault::v3::HTTPFault http_fault;
  auto* abort_percentage = http_fault.mutable_abort()->mutable_percentage();
  abort_percentage->set_numerator(100);
  abort_percentage->set_denominator(abort_percentage->HUNDRED);
  http_fault.mutable_abort()->set_grpc_status(
      static_cast<uint32_t>(StatusCode::ABORTED));
  listener = default_listener_;
  http_connection_manager = ClientHcmAccessor().Unpack(listener);
  *http_connection_manager.add_http_filters() =
      http_connection_manager.http_filters(0);
  auto* filter = http_connection_manager.mutable_http_filters(0);
  filter->set_name("envoy.fault");
  filter->mutable_typed_config()->PackFrom(http_fault);
  ClientHcmAccessor().Pack(http_connection_manager, &listener);
  SetListenerAndRouteConfiguration(balancer_.get(), std::move(listener),
                                   route_config);

  WaitForBackend(DEBUG_LOCATION, 1);
}

TEST_P(LdsRdsInteractionTest, HcmConfigUpdatedWithoutRdsChange) {
  CreateAndStartBackends(1);

  EdsResourceArgs args({{"locality0", CreateEndpointsForBackends(0, 1)}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));
  WaitForBackend(DEBUG_LOCATION, 0);

  auto response_state = balancer_->ads_service()->lds_response_state();
  ASSERT_TRUE(response_state.has_value());
  EXPECT_EQ(response_state->state, AdsServiceImpl::ResponseState::ACKED);

  envoy::extensions::filters::http::fault::v3::HTTPFault http_fault;
  auto* abort_percentage = http_fault.mutable_abort()->mutable_percentage();
  abort_percentage->set_numerator(100);
  abort_percentage->set_denominator(abort_percentage->HUNDRED);
  http_fault.mutable_abort()->set_grpc_status(
      static_cast<uint32_t>(StatusCode::ABORTED));
  Listener listener = default_listener_;
  HttpConnectionManager http_connection_manager =
      ClientHcmAccessor().Unpack(listener);
  *http_connection_manager.add_http_filters() =
      http_connection_manager.http_filters(0);
  auto* filter = http_connection_manager.mutable_http_filters(0);
  filter->set_name("envoy.fault");
  filter->mutable_typed_config()->PackFrom(http_fault);
  ClientHcmAccessor().Pack(http_connection_manager, &listener);
  SetListenerAndRouteConfiguration(balancer_.get(), std::move(listener),
                                   default_route_config_);

  const auto deadline =
      absl::Now() + (absl::Seconds(30) * grpc_test_slowdown_factor());
  while (true) {
    ASSERT_LT(absl::Now(), deadline) << "timed out waiting for LDS ACK";
    response_state = balancer_->ads_service()->lds_response_state();
    if (response_state.has_value()) break;
    absl::SleepFor(absl::Seconds(1) * grpc_test_slowdown_factor());
  }
  EXPECT_EQ(response_state->state, AdsServiceImpl::ResponseState::ACKED);

  CheckRpcSendFailure(DEBUG_LOCATION, StatusCode::ABORTED, "Fault injected");
}

TEST_P(LdsRdsInteractionTest, LdsUpdateChangesHcmConfigAndRdsResourceName) {
  CreateAndStartBackends(2);

  EdsResourceArgs args({{"locality0", CreateEndpointsForBackends(0, 1)}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));
  WaitForBackend(DEBUG_LOCATION, 0);

  const char* kNewClusterName = "new_cluster_name";
  const char* kNewEdsResourceName = "new_eds_resource_name";
  auto cluster = default_cluster_;
  cluster.set_name(kNewClusterName);
  cluster.mutable_eds_cluster_config()->set_service_name(kNewEdsResourceName);
  balancer_->ads_service()->SetCdsResource(cluster);
  args = EdsResourceArgs({{"locality0", CreateEndpointsForBackends(1, 2)}});
  balancer_->ads_service()->SetEdsResource(
      BuildEdsResource(args, kNewEdsResourceName));
  RouteConfiguration route_config = default_route_config_;
  route_config.set_name("new_route_config");
  route_config.mutable_virtual_hosts(0)
      ->mutable_routes(0)
      ->mutable_route()
      ->set_cluster(kNewClusterName);
  auto* config_map = route_config.mutable_virtual_hosts(0)
                         ->mutable_routes(0)
                         ->mutable_typed_per_filter_config();
  (*config_map)["envoy.fault"].PackFrom(
      envoy::extensions::filters::http::fault::v3::HTTPFault());
  envoy::extensions::filters::http::fault::v3::HTTPFault http_fault;
  auto* abort_percentage = http_fault.mutable_abort()->mutable_percentage();
  abort_percentage->set_numerator(100);
  abort_percentage->set_denominator(abort_percentage->HUNDRED);
  http_fault.mutable_abort()->set_grpc_status(
      static_cast<uint32_t>(StatusCode::ABORTED));
  Listener listener = default_listener_;
  HttpConnectionManager http_connection_manager =
      ClientHcmAccessor().Unpack(listener);
  *http_connection_manager.add_http_filters() =
      http_connection_manager.http_filters(0);
  auto* filter = http_connection_manager.mutable_http_filters(0);
  filter->set_name("envoy.fault");
  filter->mutable_typed_config()->PackFrom(http_fault);
  ClientHcmAccessor().Pack(http_connection_manager, &listener);
  SetListenerAndRouteConfiguration(balancer_.get(), std::move(listener),
                                   route_config);

  WaitForBackend(DEBUG_LOCATION, 1);
}

using LdsRdsTest = XdsEnd2endTest;

INSTANTIATE_TEST_SUITE_P(
    XdsTest, LdsRdsTest,
    ::testing::Values(XdsTestType(), XdsTestType().set_enable_rds_testing()),
    &XdsTestType::Name);

MATCHER_P2(AdjustedClockInRange, t1, t2,
           absl::StrFormat("time between %s and %s", t1.ToString().c_str(),
                           t2.ToString().c_str())) {
  gpr_cycle_counter cycle_now = gpr_get_cycle_counter();
  grpc_core::Timestamp cycle_time =
      grpc_core::Timestamp::FromCycleCounterRoundDown(cycle_now);
  grpc_core::Timestamp time_spec =
      grpc_core::Timestamp::FromTimespecRoundDown(gpr_now(GPR_CLOCK_MONOTONIC));
  grpc_core::Timestamp now = arg + (time_spec - cycle_time);
  bool ok = true;
  ok &= ::testing::ExplainMatchResult(::testing::Ge(t1), now, result_listener);
  ok &= ::testing::ExplainMatchResult(::testing::Lt(t2), now, result_listener);
  return ok;
}

TEST_P(LdsRdsTest, NoMatchedDomain) {
  RouteConfiguration route_config = default_route_config_;
  route_config.mutable_virtual_hosts(0)->clear_domains();
  route_config.mutable_virtual_hosts(0)->add_domains("unmatched_domain");
  SetRouteConfiguration(balancer_.get(), route_config);
  CheckRpcSendFailure(
      DEBUG_LOCATION, StatusCode::UNAVAILABLE,
      absl::StrCat(
          "empty address list \\(",
          (GetParam().enable_rds_testing() ? "RDS" : "LDS"), " resource ",
          (GetParam().enable_rds_testing() ? kDefaultRouteConfigurationName
                                           : kServerName),
          ": could not find VirtualHost for ", kServerName,
          " in RouteConfiguration\\)"));

  channel_->WaitForConnected(grpc_timeout_milliseconds_to_deadline(100));
  auto response_state = RouteConfigurationResponseState(balancer_.get());
  ASSERT_TRUE(response_state.has_value());
  EXPECT_EQ(response_state->state, AdsServiceImpl::ResponseState::ACKED);
}

TEST_P(LdsRdsTest, ChooseMatchedDomain) {
  RouteConfiguration route_config = default_route_config_;
  *(route_config.add_virtual_hosts()) = route_config.virtual_hosts(0);
  route_config.mutable_virtual_hosts(0)->clear_domains();
  route_config.mutable_virtual_hosts(0)->add_domains("unmatched_domain");
  SetRouteConfiguration(balancer_.get(), route_config);
  (void)SendRpc();
  auto response_state = RouteConfigurationResponseState(balancer_.get());
  ASSERT_TRUE(response_state.has_value());
  EXPECT_EQ(response_state->state, AdsServiceImpl::ResponseState::ACKED);
}

TEST_P(LdsRdsTest, ChooseLastRoute) {
  RouteConfiguration route_config = default_route_config_;
  *(route_config.mutable_virtual_hosts(0)->add_routes()) =
      route_config.virtual_hosts(0).routes(0);
  route_config.mutable_virtual_hosts(0)
      ->mutable_routes(0)
      ->mutable_route()
      ->mutable_cluster_header();
  SetRouteConfiguration(balancer_.get(), route_config);
  (void)SendRpc();
  auto response_state = RouteConfigurationResponseState(balancer_.get());
  ASSERT_TRUE(response_state.has_value());
  EXPECT_EQ(response_state->state, AdsServiceImpl::ResponseState::ACKED);
}

TEST_P(LdsRdsTest, NoMatchingRoute) {
  EdsResourceArgs args({{"locality0", {MakeNonExistentEndpoint()}}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));
  RouteConfiguration route_config = default_route_config_;
  route_config.mutable_virtual_hosts(0)
      ->mutable_routes(0)
      ->mutable_match()
      ->set_prefix("/unknown/method");
  SetRouteConfiguration(balancer_.get(), route_config);
  CheckRpcSendFailure(DEBUG_LOCATION, StatusCode::UNAVAILABLE,
                      "No matching route found in xDS route config");

  channel_->WaitForConnected(grpc_timeout_milliseconds_to_deadline(100));
  auto response_state = RouteConfigurationResponseState(balancer_.get());
  ASSERT_TRUE(response_state.has_value());
  EXPECT_EQ(response_state->state, AdsServiceImpl::ResponseState::ACKED);
}

TEST_P(LdsRdsTest, EmptyRouteList) {
  RouteConfiguration route_config = default_route_config_;
  route_config.mutable_virtual_hosts(0)->clear_routes();
  SetRouteConfiguration(balancer_.get(), route_config);
  CheckRpcSendFailure(DEBUG_LOCATION, StatusCode::UNAVAILABLE,
                      "No matching route found in xDS route config");

  channel_->WaitForConnected(grpc_timeout_milliseconds_to_deadline(100));
  auto response_state = RouteConfigurationResponseState(balancer_.get());
  ASSERT_TRUE(response_state.has_value());
  EXPECT_EQ(response_state->state, AdsServiceImpl::ResponseState::ACKED);
}

TEST_P(LdsRdsTest, NacksInvalidRouteConfig) {
  RouteConfiguration route_config = default_route_config_;
  route_config.mutable_virtual_hosts(0)->mutable_routes(0)->clear_match();
  SetRouteConfiguration(balancer_.get(), route_config);
  const auto response_state = WaitForRdsNack(DEBUG_LOCATION);
  ASSERT_TRUE(response_state.has_value()) << "timed out waiting for NACK";
  EXPECT_EQ(
      response_state->error_message,
      absl::StrCat(
          "xDS response validation errors: [resource index 0: ",
          GetParam().enable_rds_testing()
              ? "route_config_name: INVALID_ARGUMENT: "
                "errors validating RouteConfiguration resource: ["
                "field:"
              : "server.example.com: INVALID_ARGUMENT: "
                "errors validating ApiListener: ["
                "field:api_listener.api_listener.value["
                "envoy.extensions.filters.network.http_connection_manager.v3"
                ".HttpConnectionManager].route_config.",
          "virtual_hosts[0].routes[0].match "
          "error:field not present]]"));
}

TEST_P(LdsRdsTest, MatchingRouteHasNoRouteAction) {
  EdsResourceArgs args({{"locality0", {MakeNonExistentEndpoint()}}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));
  RouteConfiguration route_config = default_route_config_;

  auto* vhost = route_config.mutable_virtual_hosts(0);
  vhost->mutable_routes(0)->mutable_redirect();

  auto* route = vhost->add_routes();
  route->mutable_match()->set_prefix("");
  route->mutable_route()->set_cluster(kDefaultClusterName);
  SetRouteConfiguration(balancer_.get(), route_config);
  CheckRpcSendFailure(DEBUG_LOCATION, StatusCode::UNAVAILABLE,
                      "Matching route has inappropriate action");
}

TEST_P(LdsRdsTest, XdsRoutingPathMatching) {
  CreateAndStartBackends(4);
  const char* kNewCluster1Name = "new_cluster_1";
  const char* kNewEdsService1Name = "new_eds_service_name_1";
  const char* kNewCluster2Name = "new_cluster_2";
  const char* kNewEdsService2Name = "new_eds_service_name_2";
  const size_t kNumEcho1Rpcs = 10;
  const size_t kNumEcho2Rpcs = 20;
  const size_t kNumEchoRpcs = 30;

  EdsResourceArgs args({
      {"locality0", CreateEndpointsForBackends(0, 2)},
  });
  EdsResourceArgs args1({
      {"locality0", CreateEndpointsForBackends(2, 3)},
  });
  EdsResourceArgs args2({
      {"locality0", CreateEndpointsForBackends(3, 4)},
  });
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));
  balancer_->ads_service()->SetEdsResource(
      BuildEdsResource(args1, kNewEdsService1Name));
  balancer_->ads_service()->SetEdsResource(
      BuildEdsResource(args2, kNewEdsService2Name));

  Cluster new_cluster1 = default_cluster_;
  new_cluster1.set_name(kNewCluster1Name);
  new_cluster1.mutable_eds_cluster_config()->set_service_name(
      kNewEdsService1Name);
  balancer_->ads_service()->SetCdsResource(new_cluster1);
  Cluster new_cluster2 = default_cluster_;
  new_cluster2.set_name(kNewCluster2Name);
  new_cluster2.mutable_eds_cluster_config()->set_service_name(
      kNewEdsService2Name);
  balancer_->ads_service()->SetCdsResource(new_cluster2);

  RouteConfiguration new_route_config = default_route_config_;
  auto* route1 = new_route_config.mutable_virtual_hosts(0)->mutable_routes(0);
  route1->mutable_match()->set_path("/grpc.testing.EchoTest1Service/Echo1");
  route1->mutable_route()->set_cluster(kNewCluster1Name);
  auto* route2 = new_route_config.mutable_virtual_hosts(0)->add_routes();
  route2->mutable_match()->set_path("/grpc.testing.EchoTest2Service/Echo2");
  route2->mutable_route()->set_cluster(kNewCluster2Name);
  auto* route3 = new_route_config.mutable_virtual_hosts(0)->add_routes();
  route3->mutable_match()->set_path("/grpc.testing.EchoTest3Service/Echo3");
  route3->mutable_route()->set_cluster(kDefaultClusterName);
  auto* default_route = new_route_config.mutable_virtual_hosts(0)->add_routes();
  default_route->mutable_match()->set_prefix("");
  default_route->mutable_route()->set_cluster(kDefaultClusterName);
  SetRouteConfiguration(balancer_.get(), new_route_config);
  WaitForAllBackends(DEBUG_LOCATION, 0, 2, nullptr,
                     WaitForBackendOptions(),
                     RpcOptions().set_timeout_ms(5000));
  CheckRpcSendOk(DEBUG_LOCATION, kNumEchoRpcs,
                 RpcOptions().set_wait_for_ready(true));
  CheckRpcSendOk(DEBUG_LOCATION, kNumEcho1Rpcs,
                 RpcOptions()
                     .set_rpc_service(SERVICE_ECHO1)
                     .set_rpc_method(METHOD_ECHO1)
                     .set_wait_for_ready(true));
  CheckRpcSendOk(DEBUG_LOCATION, kNumEcho2Rpcs,
                 RpcOptions()
                     .set_rpc_service(SERVICE_ECHO2)
                     .set_rpc_method(METHOD_ECHO2)
                     .set_wait_for_ready(true));

  for (size_t i = 0; i < 2; ++i) {
    EXPECT_EQ(kNumEchoRpcs / 2,
              backends_[i]->backend_service()->request_count());
    EXPECT_EQ(0, backends_[i]->backend_service1()->request_count());
    EXPECT_EQ(0, backends_[i]->backend_service2()->request_count());
  }
  EXPECT_EQ(0, backends_[2]->backend_service()->request_count());
  EXPECT_EQ(kNumEcho1Rpcs, backends_[2]->backend_service1()->request_count());
  EXPECT_EQ(0, backends_[2]->backend_service2()->request_count());
  EXPECT_EQ(0, backends_[3]->backend_service()->request_count());
  EXPECT_EQ(0, backends_[3]->backend_service1()->request_count());
  EXPECT_EQ(kNumEcho2Rpcs, backends_[3]->backend_service2()->request_count());
}

TEST_P(LdsRdsTest, XdsRoutingPathMatchingCaseInsensitive) {
  CreateAndStartBackends(4);
  const char* kNewCluster1Name = "new_cluster_1";
  const char* kNewEdsService1Name = "new_eds_service_name_1";
  const char* kNewCluster2Name = "new_cluster_2";
  const char* kNewEdsService2Name = "new_eds_service_name_2";
  const size_t kNumEcho1Rpcs = 10;
  const size_t kNumEchoRpcs = 30;

  EdsResourceArgs args({
      {"locality0", CreateEndpointsForBackends(0, 1)},
  });
  EdsResourceArgs args1({
      {"locality0", CreateEndpointsForBackends(1, 2)},
  });
  EdsResourceArgs args2({
      {"locality0", CreateEndpointsForBackends(2, 3)},
  });
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));
  balancer_->ads_service()->SetEdsResource(
      BuildEdsResource(args1, kNewEdsService1Name));
  balancer_->ads_service()->SetEdsResource(
      BuildEdsResource(args2, kNewEdsService2Name));

  Cluster new_cluster1 = default_cluster_;
  new_cluster1.set_name(kNewCluster1Name);
  new_cluster1.mutable_eds_cluster_config()->set_service_name(
      kNewEdsService1Name);
  balancer_->ads_service()->SetCdsResource(new_cluster1);
  Cluster new_cluster2 = default_cluster_;
  new_cluster2.set_name(kNewCluster2Name);
  new_cluster2.mutable_eds_cluster_config()->set_service_name(
      kNewEdsService2Name);
  balancer_->ads_service()->SetCdsResource(new_cluster2);

  RouteConfiguration new_route_config = default_route_config_;

  auto* route1 = new_route_config.mutable_virtual_hosts(0)->mutable_routes(0);
  route1->mutable_match()->set_path("/GrPc.TeStInG.EcHoTeSt1SErViCe/EcHo1");
  route1->mutable_route()->set_cluster(kNewCluster1Name);
  auto* route2 = new_route_config.mutable_virtual_hosts(0)->add_routes();
  route2->mutable_match()->set_path("/GrPc.TeStInG.EcHoTeSt1SErViCe/EcHo1");
  route2->mutable_match()->mutable_case_sensitive()->set_value(false);
  route2->mutable_route()->set_cluster(kNewCluster2Name);
  auto* default_route = new_route_config.mutable_virtual_hosts(0)->add_routes();
  default_route->mutable_match()->set_prefix("");
  default_route->mutable_route()->set_cluster(kDefaultClusterName);
  SetRouteConfiguration(balancer_.get(), new_route_config);
  CheckRpcSendOk(DEBUG_LOCATION, kNumEchoRpcs,
                 RpcOptions().set_wait_for_ready(true));
  CheckRpcSendOk(DEBUG_LOCATION, kNumEcho1Rpcs,
                 RpcOptions()
                     .set_rpc_service(SERVICE_ECHO1)
                     .set_rpc_method(METHOD_ECHO1)
                     .set_wait_for_ready(true));

  EXPECT_EQ(kNumEchoRpcs, backends_[0]->backend_service()->request_count());
  EXPECT_EQ(0, backends_[0]->backend_service1()->request_count());
  EXPECT_EQ(0, backends_[1]->backend_service()->request_count());
  EXPECT_EQ(0, backends_[1]->backend_service1()->request_count());
  EXPECT_EQ(0, backends_[2]->backend_service()->request_count());
  EXPECT_EQ(kNumEcho1Rpcs, backends_[2]->backend_service1()->request_count());
}

TEST_P(LdsRdsTest, XdsRoutingPrefixMatching) {
  CreateAndStartBackends(4);
  const char* kNewCluster1Name = "new_cluster_1";
  const char* kNewEdsService1Name = "new_eds_service_name_1";
  const char* kNewCluster2Name = "new_cluster_2";
  const char* kNewEdsService2Name = "new_eds_service_name_2";
  const size_t kNumEcho1Rpcs = 10;
  const size_t kNumEcho2Rpcs = 20;
  const size_t kNumEchoRpcs = 30;

  EdsResourceArgs args({
      {"locality0", CreateEndpointsForBackends(0, 2)},
  });
  EdsResourceArgs args1({
      {"locality0", CreateEndpointsForBackends(2, 3)},
  });
  EdsResourceArgs args2({
      {"locality0", CreateEndpointsForBackends(3, 4)},
  });
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));
  balancer_->ads_service()->SetEdsResource(
      BuildEdsResource(args1, kNewEdsService1Name));
  balancer_->ads_service()->SetEdsResource(
      BuildEdsResource(args2, kNewEdsService2Name));

  Cluster new_cluster1 = default_cluster_;
  new_cluster1.set_name(kNewCluster1Name);
  new_cluster1.mutable_eds_cluster_config()->set_service_name(
      kNewEdsService1Name);
  balancer_->ads_service()->SetCdsResource(new_cluster1);
  Cluster new_cluster2 = default_cluster_;
  new_cluster2.set_name(kNewCluster2Name);
  new_cluster2.mutable_eds_cluster_config()->set_service_name(
      kNewEdsService2Name);
  balancer_->ads_service()->SetCdsResource(new_cluster2);

  RouteConfiguration new_route_config = default_route_config_;
  auto* route1 = new_route_config.mutable_virtual_hosts(0)->mutable_routes(0);
  route1->mutable_match()->set_prefix("/grpc.testing.EchoTest1Service/");
  route1->mutable_route()->set_cluster(kNewCluster1Name);
  auto* route2 = new_route_config.mutable_virtual_hosts(0)->add_routes();
  route2->mutable_match()->set_prefix("/grpc.testing.EchoTest2Service/");
  route2->mutable_route()->set_cluster(kNewCluster2Name);
  auto* default_route = new_route_config.mutable_virtual_hosts(0)->add_routes();
  default_route->mutable_match()->set_prefix("");
  default_route->mutable_route()->set_cluster(kDefaultClusterName);
  SetRouteConfiguration(balancer_.get(), new_route_config);
  WaitForAllBackends(DEBUG_LOCATION, 0, 2);
  CheckRpcSendOk(DEBUG_LOCATION, kNumEchoRpcs,
                 RpcOptions().set_wait_for_ready(true));
  CheckRpcSendOk(
      DEBUG_LOCATION, kNumEcho1Rpcs,
      RpcOptions().set_rpc_service(SERVICE_ECHO1).set_wait_for_ready(true));
  CheckRpcSendOk(
      DEBUG_LOCATION, kNumEcho2Rpcs,
      RpcOptions().set_rpc_service(SERVICE_ECHO2).set_wait_for_ready(true));

  for (size_t i = 0; i < 2; ++i) {
    EXPECT_EQ(kNumEchoRpcs / 2,
              backends_[i]->backend_service()->request_count());
    EXPECT_EQ(0, backends_[i]->backend_service1()->request_count());
    EXPECT_EQ(0, backends_[i]->backend_service2()->request_count());
  }
  EXPECT_EQ(0, backends_[2]->backend_service()->request_count());
  EXPECT_EQ(kNumEcho1Rpcs, backends_[2]->backend_service1()->request_count());
  EXPECT_EQ(0, backends_[2]->backend_service2()->request_count());
  EXPECT_EQ(0, backends_[3]->backend_service()->request_count());
  EXPECT_EQ(0, backends_[3]->backend_service1()->request_count());
  EXPECT_EQ(kNumEcho2Rpcs, backends_[3]->backend_service2()->request_count());
}

TEST_P(LdsRdsTest, XdsRoutingPrefixMatchingCaseInsensitive) {
  CreateAndStartBackends(3);
  const char* kNewCluster1Name = "new_cluster_1";
  const char* kNewEdsService1Name = "new_eds_service_name_1";
  const char* kNewCluster2Name = "new_cluster_2";
  const char* kNewEdsService2Name = "new_eds_service_name_2";
  const size_t kNumEcho1Rpcs = 10;
  const size_t kNumEchoRpcs = 30;

  EdsResourceArgs args({
      {"locality0", CreateEndpointsForBackends(0, 1)},
  });
  EdsResourceArgs args1({
      {"locality0", CreateEndpointsForBackends(1, 2)},
  });
  EdsResourceArgs args2({
      {"locality0", CreateEndpointsForBackends(2, 3)},
  });
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));
  balancer_->ads_service()->SetEdsResource(
      BuildEdsResource(args1, kNewEdsService1Name));
  balancer_->ads_service()->SetEdsResource(
      BuildEdsResource(args2, kNewEdsService2Name));

  Cluster new_cluster1 = default_cluster_;
  new_cluster1.set_name(kNewCluster1Name);
  new_cluster1.mutable_eds_cluster_config()->set_service_name(
      kNewEdsService1Name);
  balancer_->ads_service()->SetCdsResource(new_cluster1);
  Cluster new_cluster2 = default_cluster_;
  new_cluster2.set_name(kNewCluster2Name);
  new_cluster2.mutable_eds_cluster_config()->set_service_name(
      kNewEdsService2Name);
  balancer_->ads_service()->SetCdsResource(new_cluster2);

  RouteConfiguration new_route_config = default_route_config_;

  auto* route1 = new_route_config.mutable_virtual_hosts(0)->mutable_routes(0);
  route1->mutable_match()->set_prefix("/GrPc.TeStInG.EcHoTeSt1SErViCe");
  route1->mutable_route()->set_cluster(kNewCluster1Name);
  auto* route2 = new_route_config.mutable_virtual_hosts(0)->add_routes();
  route2->mutable_match()->set_prefix("/GrPc.TeStInG.EcHoTeSt1SErViCe");
  route2->mutable_match()->mutable_case_sensitive()->set_value(false);
  route2->mutable_route()->set_cluster(kNewCluster2Name);
  auto* default_route = new_route_config.mutable_virtual_hosts(0)->add_routes();
  default_route->mutable_match()->set_prefix("");
  default_route->mutable_route()->set_cluster(kDefaultClusterName);
  SetRouteConfiguration(balancer_.get(), new_route_config);
  CheckRpcSendOk(DEBUG_LOCATION, kNumEchoRpcs,
                 RpcOptions().set_wait_for_ready(true));
  CheckRpcSendOk(DEBUG_LOCATION, kNumEcho1Rpcs,
                 RpcOptions()
                     .set_rpc_service(SERVICE_ECHO1)
                     .set_rpc_method(METHOD_ECHO1)
                     .set_wait_for_ready(true));

  EXPECT_EQ(kNumEchoRpcs, backends_[0]->backend_service()->request_count());
  EXPECT_EQ(0, backends_[0]->backend_service1()->request_count());
  EXPECT_EQ(0, backends_[1]->backend_service()->request_count());
  EXPECT_EQ(0, backends_[1]->backend_service1()->request_count());
  EXPECT_EQ(0, backends_[2]->backend_service()->request_count());
  EXPECT_EQ(kNumEcho1Rpcs, backends_[2]->backend_service1()->request_count());
}

TEST_P(LdsRdsTest, XdsRoutingPathRegexMatching) {
  CreateAndStartBackends(4);
  const char* kNewCluster1Name = "new_cluster_1";
  const char* kNewEdsService1Name = "new_eds_service_name_1";
  const char* kNewCluster2Name = "new_cluster_2";
  const char* kNewEdsService2Name = "new_eds_service_name_2";
  const size_t kNumEcho1Rpcs = 10;
  const size_t kNumEcho2Rpcs = 20;
  const size_t kNumEchoRpcs = 30;

  EdsResourceArgs args({
      {"locality0", CreateEndpointsForBackends(0, 2)},
  });
  EdsResourceArgs args1({
      {"locality0", CreateEndpointsForBackends(2, 3)},
  });
  EdsResourceArgs args2({
      {"locality0", CreateEndpointsForBackends(3, 4)},
  });
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));
  balancer_->ads_service()->SetEdsResource(
      BuildEdsResource(args1, kNewEdsService1Name));
  balancer_->ads_service()->SetEdsResource(
      BuildEdsResource(args2, kNewEdsService2Name));

  Cluster new_cluster1 = default_cluster_;
  new_cluster1.set_name(kNewCluster1Name);
  new_cluster1.mutable_eds_cluster_config()->set_service_name(
      kNewEdsService1Name);
  balancer_->ads_service()->SetCdsResource(new_cluster1);
  Cluster new_cluster2 = default_cluster_;
  new_cluster2.set_name(kNewCluster2Name);
  new_cluster2.mutable_eds_cluster_config()->set_service_name(
      kNewEdsService2Name);
  balancer_->ads_service()->SetCdsResource(new_cluster2);

  RouteConfiguration new_route_config = default_route_config_;
  auto* route1 = new_route_config.mutable_virtual_hosts(0)->mutable_routes(0);

  route1->mutable_match()->mutable_safe_regex()->set_regex(".*1.*");
  route1->mutable_route()->set_cluster(kNewCluster1Name);
  auto* route2 = new_route_config.mutable_virtual_hosts(0)->add_routes();

  route2->mutable_match()->mutable_safe_regex()->set_regex(".*2.*");
  route2->mutable_route()->set_cluster(kNewCluster2Name);
  auto* default_route = new_route_config.mutable_virtual_hosts(0)->add_routes();
  default_route->mutable_match()->set_prefix("");
  default_route->mutable_route()->set_cluster(kDefaultClusterName);
  SetRouteConfiguration(balancer_.get(), new_route_config);
  WaitForAllBackends(DEBUG_LOCATION, 0, 2);
  CheckRpcSendOk(DEBUG_LOCATION, kNumEchoRpcs,
                 RpcOptions().set_wait_for_ready(true));
  CheckRpcSendOk(
      DEBUG_LOCATION, kNumEcho1Rpcs,
      RpcOptions().set_rpc_service(SERVICE_ECHO1).set_wait_for_ready(true));
  CheckRpcSendOk(
      DEBUG_LOCATION, kNumEcho2Rpcs,
      RpcOptions().set_rpc_service(SERVICE_ECHO2).set_wait_for_ready(true));

  for (size_t i = 0; i < 2; ++i) {
    EXPECT_EQ(kNumEchoRpcs / 2,
              backends_[i]->backend_service()->request_count());
    EXPECT_EQ(0, backends_[i]->backend_service1()->request_count());
    EXPECT_EQ(0, backends_[i]->backend_service2()->request_count());
  }
  EXPECT_EQ(0, backends_[2]->backend_service()->request_count());
  EXPECT_EQ(kNumEcho1Rpcs, backends_[2]->backend_service1()->request_count());
  EXPECT_EQ(0, backends_[2]->backend_service2()->request_count());
  EXPECT_EQ(0, backends_[3]->backend_service()->request_count());
  EXPECT_EQ(0, backends_[3]->backend_service1()->request_count());
  EXPECT_EQ(kNumEcho2Rpcs, backends_[3]->backend_service2()->request_count());
}

TEST_P(LdsRdsTest, XdsRoutingWeightedCluster) {
  CreateAndStartBackends(3);
  const char* kNewCluster1Name = "new_cluster_1";
  const char* kNewEdsService1Name = "new_eds_service_name_1";
  const char* kNewCluster2Name = "new_cluster_2";
  const char* kNewEdsService2Name = "new_eds_service_name_2";
  const char* kNotUsedClusterName = "not_used_cluster";
  const size_t kNumEchoRpcs = 10;
  const size_t kWeight75 = 75;
  const size_t kWeight25 = 25;
  const double kErrorTolerance = 0.05;
  const double kWeight75Percent = static_cast<double>(kWeight75) / 100;
  const double kWeight25Percent = static_cast<double>(kWeight25) / 100;
  const size_t kNumEcho1Rpcs =
      ComputeIdealNumRpcs(kWeight75Percent, kErrorTolerance);

  EdsResourceArgs args({
      {"locality0", CreateEndpointsForBackends(0, 1)},
  });
  EdsResourceArgs args1({
      {"locality0", CreateEndpointsForBackends(1, 2)},
  });
  EdsResourceArgs args2({
      {"locality0", CreateEndpointsForBackends(2, 3)},
  });
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));
  balancer_->ads_service()->SetEdsResource(
      BuildEdsResource(args1, kNewEdsService1Name));
  balancer_->ads_service()->SetEdsResource(
      BuildEdsResource(args2, kNewEdsService2Name));

  Cluster new_cluster1 = default_cluster_;
  new_cluster1.set_name(kNewCluster1Name);
  new_cluster1.mutable_eds_cluster_config()->set_service_name(
      kNewEdsService1Name);
  balancer_->ads_service()->SetCdsResource(new_cluster1);
  Cluster new_cluster2 = default_cluster_;
  new_cluster2.set_name(kNewCluster2Name);
  new_cluster2.mutable_eds_cluster_config()->set_service_name(
      kNewEdsService2Name);
  balancer_->ads_service()->SetCdsResource(new_cluster2);

  RouteConfiguration new_route_config = default_route_config_;
  auto* route1 = new_route_config.mutable_virtual_hosts(0)->mutable_routes(0);
  route1->mutable_match()->set_prefix("/grpc.testing.EchoTest1Service/");
  auto* weighted_cluster1 =
      route1->mutable_route()->mutable_weighted_clusters()->add_clusters();
  weighted_cluster1->set_name(kNewCluster1Name);
  weighted_cluster1->mutable_weight()->set_value(kWeight75);
  auto* weighted_cluster2 =
      route1->mutable_route()->mutable_weighted_clusters()->add_clusters();
  weighted_cluster2->set_name(kNewCluster2Name);
  weighted_cluster2->mutable_weight()->set_value(kWeight25);

  auto* weighted_cluster3 =
      route1->mutable_route()->mutable_weighted_clusters()->add_clusters();
  weighted_cluster3->set_name(kNotUsedClusterName);
  weighted_cluster3->mutable_weight()->set_value(0);
  auto* default_route = new_route_config.mutable_virtual_hosts(0)->add_routes();
  default_route->mutable_match()->set_prefix("");
  default_route->mutable_route()->set_cluster(kDefaultClusterName);
  SetRouteConfiguration(balancer_.get(), new_route_config);
  WaitForAllBackends(DEBUG_LOCATION, 0, 1);
  WaitForAllBackends(DEBUG_LOCATION, 1, 3, nullptr,
                     WaitForBackendOptions(),
                     RpcOptions().set_rpc_service(SERVICE_ECHO1));
  CheckRpcSendOk(DEBUG_LOCATION, kNumEchoRpcs);
  CheckRpcSendOk(DEBUG_LOCATION, kNumEcho1Rpcs,
                 RpcOptions().set_rpc_service(SERVICE_ECHO1));

  EXPECT_EQ(kNumEchoRpcs, backends_[0]->backend_service()->request_count());
  EXPECT_EQ(0, backends_[0]->backend_service1()->request_count());
  EXPECT_EQ(0, backends_[1]->backend_service()->request_count());
  const int weight_75_request_count =
      backends_[1]->backend_service1()->request_count();
  EXPECT_EQ(0, backends_[2]->backend_service()->request_count());
  const int weight_25_request_count =
      backends_[2]->backend_service1()->request_count();
  LOG(INFO) << "target_75 received " << weight_75_request_count
            << " rpcs and target_25 received " << weight_25_request_count
            << " rpcs";
  EXPECT_THAT(static_cast<double>(weight_75_request_count) / kNumEcho1Rpcs,
              ::testing::DoubleNear(kWeight75Percent, kErrorTolerance));
  EXPECT_THAT(static_cast<double>(weight_25_request_count) / kNumEcho1Rpcs,
              ::testing::DoubleNear(kWeight25Percent, kErrorTolerance));
}

TEST_P(LdsRdsTest, XdsRoutingWeightedClusterNoIntegerOverflow) {
  CreateAndStartBackends(3);
  const char* kNewCluster1Name = "new_cluster_1";
  const char* kNewEdsService1Name = "new_eds_service_name_1";
  const char* kNewCluster2Name = "new_cluster_2";
  const char* kNewEdsService2Name = "new_eds_service_name_2";
  const size_t kNumEchoRpcs = 10;
  const uint32_t kWeight1 = std::numeric_limits<uint32_t>::max() / 3;
  const uint32_t kWeight2 = std::numeric_limits<uint32_t>::max() - kWeight1;
  const double kErrorTolerance = 0.05;
  const double kWeight1Percent =
      static_cast<double>(kWeight1) / std::numeric_limits<uint32_t>::max();
  const double kWeight2Percent =
      static_cast<double>(kWeight2) / std::numeric_limits<uint32_t>::max();
  const size_t kNumEcho1Rpcs =
      ComputeIdealNumRpcs(kWeight2Percent, kErrorTolerance);

  EdsResourceArgs args({
      {"locality0", CreateEndpointsForBackends(0, 1)},
  });
  EdsResourceArgs args1({
      {"locality0", CreateEndpointsForBackends(1, 2)},
  });
  EdsResourceArgs args2({
      {"locality0", CreateEndpointsForBackends(2, 3)},
  });
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));
  balancer_->ads_service()->SetEdsResource(
      BuildEdsResource(args1, kNewEdsService1Name));
  balancer_->ads_service()->SetEdsResource(
      BuildEdsResource(args2, kNewEdsService2Name));

  Cluster new_cluster1 = default_cluster_;
  new_cluster1.set_name(kNewCluster1Name);
  new_cluster1.mutable_eds_cluster_config()->set_service_name(
      kNewEdsService1Name);
  balancer_->ads_service()->SetCdsResource(new_cluster1);
  Cluster new_cluster2 = default_cluster_;
  new_cluster2.set_name(kNewCluster2Name);
  new_cluster2.mutable_eds_cluster_config()->set_service_name(
      kNewEdsService2Name);
  balancer_->ads_service()->SetCdsResource(new_cluster2);

  RouteConfiguration new_route_config = default_route_config_;
  auto* route1 = new_route_config.mutable_virtual_hosts(0)->mutable_routes(0);
  route1->mutable_match()->set_prefix("/grpc.testing.EchoTest1Service/");
  auto* weighted_cluster1 =
      route1->mutable_route()->mutable_weighted_clusters()->add_clusters();
  weighted_cluster1->set_name(kNewCluster1Name);
  weighted_cluster1->mutable_weight()->set_value(kWeight1);
  auto* weighted_cluster2 =
      route1->mutable_route()->mutable_weighted_clusters()->add_clusters();
  weighted_cluster2->set_name(kNewCluster2Name);
  weighted_cluster2->mutable_weight()->set_value(kWeight2);
  auto* default_route = new_route_config.mutable_virtual_hosts(0)->add_routes();
  default_route->mutable_match()->set_prefix("");
  default_route->mutable_route()->set_cluster(kDefaultClusterName);
  SetRouteConfiguration(balancer_.get(), new_route_config);
  WaitForAllBackends(DEBUG_LOCATION, 0, 1);
  WaitForAllBackends(DEBUG_LOCATION, 1, 3, nullptr,
                     WaitForBackendOptions(),
                     RpcOptions().set_rpc_service(SERVICE_ECHO1));
  CheckRpcSendOk(DEBUG_LOCATION, kNumEchoRpcs);
  CheckRpcSendOk(DEBUG_LOCATION, kNumEcho1Rpcs,
                 RpcOptions().set_rpc_service(SERVICE_ECHO1));

  EXPECT_EQ(kNumEchoRpcs, backends_[0]->backend_service()->request_count());
  EXPECT_EQ(0, backends_[0]->backend_service1()->request_count());
  EXPECT_EQ(0, backends_[1]->backend_service()->request_count());
  const int weight1_request_count =
      backends_[1]->backend_service1()->request_count();
  EXPECT_EQ(0, backends_[2]->backend_service()->request_count());
  const int weight2_request_count =
      backends_[2]->backend_service1()->request_count();
  LOG(INFO) << "target1 received " << weight1_request_count
            << " rpcs and target2 received " << weight2_request_count
            << " rpcs";
  EXPECT_THAT(static_cast<double>(weight1_request_count) / kNumEcho1Rpcs,
              ::testing::DoubleNear(kWeight1Percent, kErrorTolerance));
  EXPECT_THAT(static_cast<double>(weight2_request_count) / kNumEcho1Rpcs,
              ::testing::DoubleNear(kWeight2Percent, kErrorTolerance));
}

TEST_P(LdsRdsTest, RouteActionWeightedTargetDefaultRoute) {
  CreateAndStartBackends(3);
  const char* kNewCluster1Name = "new_cluster_1";
  const char* kNewEdsService1Name = "new_eds_service_name_1";
  const char* kNewCluster2Name = "new_cluster_2";
  const char* kNewEdsService2Name = "new_eds_service_name_2";
  const size_t kWeight75 = 75;
  const size_t kWeight25 = 25;
  const double kErrorTolerance = 0.05;
  const double kWeight75Percent = static_cast<double>(kWeight75) / 100;
  const double kWeight25Percent = static_cast<double>(kWeight25) / 100;
  const size_t kNumEchoRpcs =
      ComputeIdealNumRpcs(kWeight75Percent, kErrorTolerance);

  EdsResourceArgs args({
      {"locality0", CreateEndpointsForBackends(0, 1)},
  });
  EdsResourceArgs args1({
      {"locality0", CreateEndpointsForBackends(1, 2)},
  });
  EdsResourceArgs args2({
      {"locality0", CreateEndpointsForBackends(2, 3)},
  });
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));
  balancer_->ads_service()->SetEdsResource(
      BuildEdsResource(args1, kNewEdsService1Name));
  balancer_->ads_service()->SetEdsResource(
      BuildEdsResource(args2, kNewEdsService2Name));

  Cluster new_cluster1 = default_cluster_;
  new_cluster1.set_name(kNewCluster1Name);
  new_cluster1.mutable_eds_cluster_config()->set_service_name(
      kNewEdsService1Name);
  balancer_->ads_service()->SetCdsResource(new_cluster1);
  Cluster new_cluster2 = default_cluster_;
  new_cluster2.set_name(kNewCluster2Name);
  new_cluster2.mutable_eds_cluster_config()->set_service_name(
      kNewEdsService2Name);
  balancer_->ads_service()->SetCdsResource(new_cluster2);

  RouteConfiguration new_route_config = default_route_config_;
  auto* route1 = new_route_config.mutable_virtual_hosts(0)->mutable_routes(0);
  route1->mutable_match()->set_prefix("");
  auto* weighted_cluster1 =
      route1->mutable_route()->mutable_weighted_clusters()->add_clusters();
  weighted_cluster1->set_name(kNewCluster1Name);
  weighted_cluster1->mutable_weight()->set_value(kWeight75);
  auto* weighted_cluster2 =
      route1->mutable_route()->mutable_weighted_clusters()->add_clusters();
  weighted_cluster2->set_name(kNewCluster2Name);
  weighted_cluster2->mutable_weight()->set_value(kWeight25);
  SetRouteConfiguration(balancer_.get(), new_route_config);
  WaitForAllBackends(DEBUG_LOCATION, 1, 3);
  CheckRpcSendOk(DEBUG_LOCATION, kNumEchoRpcs);

  EXPECT_EQ(0, backends_[0]->backend_service()->request_count());
  const int weight_75_request_count =
      backends_[1]->backend_service()->request_count();
  const int weight_25_request_count =
      backends_[2]->backend_service()->request_count();
  LOG(INFO) << "target_75 received " << weight_75_request_count
            << " rpcs and target_25 received " << weight_25_request_count
            << " rpcs";
  EXPECT_THAT(static_cast<double>(weight_75_request_count) / kNumEchoRpcs,
              ::testing::DoubleNear(kWeight75Percent, kErrorTolerance));
  EXPECT_THAT(static_cast<double>(weight_25_request_count) / kNumEchoRpcs,
              ::testing::DoubleNear(kWeight25Percent, kErrorTolerance));
}

TEST_P(LdsRdsTest, XdsRoutingWeightedClusterUpdateWeights) {
  CreateAndStartBackends(4);
  const char* kNewCluster1Name = "new_cluster_1";
  const char* kNewEdsService1Name = "new_eds_service_name_1";
  const char* kNewCluster2Name = "new_cluster_2";
  const char* kNewEdsService2Name = "new_eds_service_name_2";
  const char* kNewCluster3Name = "new_cluster_3";
  const char* kNewEdsService3Name = "new_eds_service_name_3";
  const size_t kNumEchoRpcs = 10;
  const size_t kWeight75 = 75;
  const size_t kWeight25 = 25;
  const size_t kWeight50 = 50;
  const double kErrorTolerance = 0.05;
  const double kWeight75Percent = static_cast<double>(kWeight75) / 100;
  const double kWeight25Percent = static_cast<double>(kWeight25) / 100;
  const double kWeight50Percent = static_cast<double>(kWeight50) / 100;
  const size_t kNumEcho1Rpcs7525 =
      ComputeIdealNumRpcs(kWeight75Percent, kErrorTolerance);
  const size_t kNumEcho1Rpcs5050 =
      ComputeIdealNumRpcs(kWeight50Percent, kErrorTolerance);

  EdsResourceArgs args({
      {"locality0", CreateEndpointsForBackends(0, 1)},
  });
  EdsResourceArgs args1({
      {"locality0", CreateEndpointsForBackends(1, 2)},
  });
  EdsResourceArgs args2({
      {"locality0", CreateEndpointsForBackends(2, 3)},
  });
  EdsResourceArgs args3({
      {"locality0", CreateEndpointsForBackends(3, 4)},
  });
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));
  balancer_->ads_service()->SetEdsResource(
      BuildEdsResource(args1, kNewEdsService1Name));
  balancer_->ads_service()->SetEdsResource(
      BuildEdsResource(args2, kNewEdsService2Name));
  balancer_->ads_service()->SetEdsResource(
      BuildEdsResource(args3, kNewEdsService3Name));

  Cluster new_cluster1 = default_cluster_;
  new_cluster1.set_name(kNewCluster1Name);
  new_cluster1.mutable_eds_cluster_config()->set_service_name(
      kNewEdsService1Name);
  balancer_->ads_service()->SetCdsResource(new_cluster1);
  Cluster new_cluster2 = default_cluster_;
  new_cluster2.set_name(kNewCluster2Name);
  new_cluster2.mutable_eds_cluster_config()->set_service_name(
      kNewEdsService2Name);
  balancer_->ads_service()->SetCdsResource(new_cluster2);
  Cluster new_cluster3 = default_cluster_;
  new_cluster3.set_name(kNewCluster3Name);
  new_cluster3.mutable_eds_cluster_config()->set_service_name(
      kNewEdsService3Name);
  balancer_->ads_service()->SetCdsResource(new_cluster3);

  RouteConfiguration new_route_config = default_route_config_;
  auto* route1 = new_route_config.mutable_virtual_hosts(0)->mutable_routes(0);
  route1->mutable_match()->set_prefix("/grpc.testing.EchoTest1Service/");
  auto* weighted_cluster1 =
      route1->mutable_route()->mutable_weighted_clusters()->add_clusters();
  weighted_cluster1->set_name(kNewCluster1Name);
  weighted_cluster1->mutable_weight()->set_value(kWeight75);
  auto* weighted_cluster2 =
      route1->mutable_route()->mutable_weighted_clusters()->add_clusters();
  weighted_cluster2->set_name(kNewCluster2Name);
  weighted_cluster2->mutable_weight()->set_value(kWeight25);
  auto* default_route = new_route_config.mutable_virtual_hosts(0)->add_routes();
  default_route->mutable_match()->set_prefix("");
  default_route->mutable_route()->set_cluster(kDefaultClusterName);
  SetRouteConfiguration(balancer_.get(), new_route_config);
  WaitForAllBackends(DEBUG_LOCATION, 0, 1, nullptr,
                     WaitForBackendOptions(),
                     RpcOptions().set_timeout_ms(5000));
  WaitForAllBackends(
      DEBUG_LOCATION, 1, 3, nullptr, WaitForBackendOptions(),
      RpcOptions().set_rpc_service(SERVICE_ECHO1).set_timeout_ms(5000));
  CheckRpcSendOk(DEBUG_LOCATION, kNumEchoRpcs,
                 RpcOptions().set_timeout_ms(5000));
  CheckRpcSendOk(
      DEBUG_LOCATION, kNumEcho1Rpcs7525,
      RpcOptions().set_rpc_service(SERVICE_ECHO1).set_timeout_ms(5000));

  EXPECT_EQ(kNumEchoRpcs, backends_[0]->backend_service()->request_count());
  EXPECT_EQ(0, backends_[0]->backend_service1()->request_count());
  EXPECT_EQ(0, backends_[1]->backend_service()->request_count());
  const int weight_75_request_count =
      backends_[1]->backend_service1()->request_count();
  EXPECT_EQ(0, backends_[1]->backend_service2()->request_count());
  EXPECT_EQ(0, backends_[2]->backend_service()->request_count());
  const int weight_25_request_count =
      backends_[2]->backend_service1()->request_count();
  EXPECT_EQ(0, backends_[3]->backend_service()->request_count());
  EXPECT_EQ(0, backends_[3]->backend_service1()->request_count());
  LOG(INFO) << "target_75 received " << weight_75_request_count
            << " rpcs and target_25 received " << weight_25_request_count
            << " rpcs";
  EXPECT_THAT(static_cast<double>(weight_75_request_count) / kNumEcho1Rpcs7525,
              ::testing::DoubleNear(kWeight75Percent, kErrorTolerance));
  EXPECT_THAT(static_cast<double>(weight_25_request_count) / kNumEcho1Rpcs7525,
              ::testing::DoubleNear(kWeight25Percent, kErrorTolerance));

  weighted_cluster1->mutable_weight()->set_value(kWeight50);
  weighted_cluster2->mutable_weight()->set_value(kWeight50);

  default_route->mutable_route()->set_cluster(kNewCluster3Name);
  SetRouteConfiguration(balancer_.get(), new_route_config);
  ResetBackendCounters();
  WaitForAllBackends(DEBUG_LOCATION, 3, 4, nullptr,
                     WaitForBackendOptions(),
                     RpcOptions().set_timeout_ms(5000));
  CheckRpcSendOk(DEBUG_LOCATION, kNumEchoRpcs,
                 RpcOptions().set_timeout_ms(5000));
  CheckRpcSendOk(
      DEBUG_LOCATION, kNumEcho1Rpcs5050,
      RpcOptions().set_rpc_service(SERVICE_ECHO1).set_timeout_ms(5000));

  EXPECT_EQ(0, backends_[0]->backend_service()->request_count());
  EXPECT_EQ(0, backends_[0]->backend_service1()->request_count());
  EXPECT_EQ(0, backends_[1]->backend_service()->request_count());
  const int weight_50_request_count_1 =
      backends_[1]->backend_service1()->request_count();
  EXPECT_EQ(0, backends_[2]->backend_service()->request_count());
  const int weight_50_request_count_2 =
      backends_[2]->backend_service1()->request_count();
  EXPECT_EQ(kNumEchoRpcs, backends_[3]->backend_service()->request_count());
  EXPECT_EQ(0, backends_[3]->backend_service1()->request_count());
  EXPECT_THAT(
      static_cast<double>(weight_50_request_count_1) / kNumEcho1Rpcs5050,
      ::testing::DoubleNear(kWeight50Percent, kErrorTolerance));
  EXPECT_THAT(
      static_cast<double>(weight_50_request_count_2) / kNumEcho1Rpcs5050,
      ::testing::DoubleNear(kWeight50Percent, kErrorTolerance));
}

TEST_P(LdsRdsTest, XdsRoutingWeightedClusterUpdateClusters) {
  CreateAndStartBackends(4);
  const char* kNewCluster1Name = "new_cluster_1";
  const char* kNewEdsService1Name = "new_eds_service_name_1";
  const char* kNewCluster2Name = "new_cluster_2";
  const char* kNewEdsService2Name = "new_eds_service_name_2";
  const char* kNewCluster3Name = "new_cluster_3";
  const char* kNewEdsService3Name = "new_eds_service_name_3";
  const size_t kNumEchoRpcs = 10;
  const size_t kWeight75 = 75;
  const size_t kWeight25 = 25;
  const size_t kWeight50 = 50;
  const double kErrorTolerance = 0.05;
  const double kWeight75Percent = static_cast<double>(kWeight75) / 100;
  const double kWeight25Percent = static_cast<double>(kWeight25) / 100;
  const double kWeight50Percent = static_cast<double>(kWeight50) / 100;
  const size_t kNumEcho1Rpcs7525 =
      ComputeIdealNumRpcs(kWeight75Percent, kErrorTolerance);
  const size_t kNumEcho1Rpcs5050 =
      ComputeIdealNumRpcs(kWeight50Percent, kErrorTolerance);

  EdsResourceArgs args({
      {"locality0", CreateEndpointsForBackends(0, 1)},
  });
  EdsResourceArgs args1({
      {"locality0", CreateEndpointsForBackends(1, 2)},
  });
  EdsResourceArgs args2({
      {"locality0", CreateEndpointsForBackends(2, 3)},
  });
  EdsResourceArgs args3({
      {"locality0", CreateEndpointsForBackends(3, 4)},
  });
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));
  balancer_->ads_service()->SetEdsResource(
      BuildEdsResource(args1, kNewEdsService1Name));
  balancer_->ads_service()->SetEdsResource(
      BuildEdsResource(args2, kNewEdsService2Name));
  balancer_->ads_service()->SetEdsResource(
      BuildEdsResource(args3, kNewEdsService3Name));

  Cluster new_cluster1 = default_cluster_;
  new_cluster1.set_name(kNewCluster1Name);
  new_cluster1.mutable_eds_cluster_config()->set_service_name(
      kNewEdsService1Name);
  balancer_->ads_service()->SetCdsResource(new_cluster1);
  Cluster new_cluster2 = default_cluster_;
  new_cluster2.set_name(kNewCluster2Name);
  new_cluster2.mutable_eds_cluster_config()->set_service_name(
      kNewEdsService2Name);
  balancer_->ads_service()->SetCdsResource(new_cluster2);
  Cluster new_cluster3 = default_cluster_;
  new_cluster3.set_name(kNewCluster3Name);
  new_cluster3.mutable_eds_cluster_config()->set_service_name(
      kNewEdsService3Name);
  balancer_->ads_service()->SetCdsResource(new_cluster3);

  RouteConfiguration new_route_config = default_route_config_;
  auto* route1 = new_route_config.mutable_virtual_hosts(0)->mutable_routes(0);
  route1->mutable_match()->set_prefix("/grpc.testing.EchoTest1Service/");
  auto* weighted_cluster1 =
      route1->mutable_route()->mutable_weighted_clusters()->add_clusters();
  weighted_cluster1->set_name(kNewCluster1Name);
  weighted_cluster1->mutable_weight()->set_value(kWeight75);
  auto* weighted_cluster2 =
      route1->mutable_route()->mutable_weighted_clusters()->add_clusters();
  weighted_cluster2->set_name(kDefaultClusterName);
  weighted_cluster2->mutable_weight()->set_value(kWeight25);
  auto* default_route = new_route_config.mutable_virtual_hosts(0)->add_routes();
  default_route->mutable_match()->set_prefix("");
  default_route->mutable_route()->set_cluster(kDefaultClusterName);
  SetRouteConfiguration(balancer_.get(), new_route_config);
  WaitForBackend(DEBUG_LOCATION, 0);
  WaitForBackend(DEBUG_LOCATION, 1, nullptr,
                 WaitForBackendOptions(),
                 RpcOptions().set_rpc_service(SERVICE_ECHO1));
  CheckRpcSendOk(DEBUG_LOCATION, kNumEchoRpcs);
  CheckRpcSendOk(DEBUG_LOCATION, kNumEcho1Rpcs7525,
                 RpcOptions().set_rpc_service(SERVICE_ECHO1));

  EXPECT_EQ(kNumEchoRpcs, backends_[0]->backend_service()->request_count());
  int weight_25_request_count =
      backends_[0]->backend_service1()->request_count();
  EXPECT_EQ(0, backends_[1]->backend_service()->request_count());
  int weight_75_request_count =
      backends_[1]->backend_service1()->request_count();
  EXPECT_EQ(0, backends_[2]->backend_service()->request_count());
  EXPECT_EQ(0, backends_[2]->backend_service1()->request_count());
  EXPECT_EQ(0, backends_[3]->backend_service()->request_count());
  EXPECT_EQ(0, backends_[3]->backend_service1()->request_count());
  LOG(INFO) << "target_75 received " << weight_75_request_count
            << " rpcs and target_25 received " << weight_25_request_count
            << " rpcs";
  EXPECT_THAT(static_cast<double>(weight_75_request_count) / kNumEcho1Rpcs7525,
              ::testing::DoubleNear(kWeight75Percent, kErrorTolerance));
  EXPECT_THAT(static_cast<double>(weight_25_request_count) / kNumEcho1Rpcs7525,
              ::testing::DoubleNear(kWeight25Percent, kErrorTolerance));

  weighted_cluster1->mutable_weight()->set_value(kWeight50);
  weighted_cluster2->set_name(kNewCluster2Name);
  weighted_cluster2->mutable_weight()->set_value(kWeight50);
  SetRouteConfiguration(balancer_.get(), new_route_config);
  ResetBackendCounters();
  WaitForBackend(DEBUG_LOCATION, 2, nullptr,
                 WaitForBackendOptions(),
                 RpcOptions().set_rpc_service(SERVICE_ECHO1));
  CheckRpcSendOk(DEBUG_LOCATION, kNumEchoRpcs);
  CheckRpcSendOk(DEBUG_LOCATION, kNumEcho1Rpcs5050,
                 RpcOptions().set_rpc_service(SERVICE_ECHO1));

  EXPECT_EQ(kNumEchoRpcs, backends_[0]->backend_service()->request_count());
  EXPECT_EQ(0, backends_[0]->backend_service1()->request_count());
  EXPECT_EQ(0, backends_[1]->backend_service()->request_count());
  const int weight_50_request_count_1 =
      backends_[1]->backend_service1()->request_count();
  EXPECT_EQ(0, backends_[2]->backend_service()->request_count());
  const int weight_50_request_count_2 =
      backends_[2]->backend_service1()->request_count();
  EXPECT_EQ(0, backends_[3]->backend_service()->request_count());
  EXPECT_EQ(0, backends_[3]->backend_service1()->request_count());
  EXPECT_THAT(
      static_cast<double>(weight_50_request_count_1) / kNumEcho1Rpcs5050,
      ::testing::DoubleNear(kWeight50Percent, kErrorTolerance));
  EXPECT_THAT(
      static_cast<double>(weight_50_request_count_2) / kNumEcho1Rpcs5050,
      ::testing::DoubleNear(kWeight50Percent, kErrorTolerance));

  weighted_cluster1->mutable_weight()->set_value(kWeight75);
  weighted_cluster2->set_name(kNewCluster3Name);
  weighted_cluster2->mutable_weight()->set_value(kWeight25);
  SetRouteConfiguration(balancer_.get(), new_route_config);
  ResetBackendCounters();
  WaitForBackend(DEBUG_LOCATION, 3, nullptr,
                 WaitForBackendOptions(),
                 RpcOptions().set_rpc_service(SERVICE_ECHO1));
  CheckRpcSendOk(DEBUG_LOCATION, kNumEchoRpcs);
  CheckRpcSendOk(DEBUG_LOCATION, kNumEcho1Rpcs7525,
                 RpcOptions().set_rpc_service(SERVICE_ECHO1));

  EXPECT_EQ(kNumEchoRpcs, backends_[0]->backend_service()->request_count());
  EXPECT_EQ(0, backends_[0]->backend_service1()->request_count());
  EXPECT_EQ(0, backends_[1]->backend_service()->request_count());
  weight_75_request_count = backends_[1]->backend_service1()->request_count();
  EXPECT_EQ(0, backends_[2]->backend_service()->request_count());
  EXPECT_EQ(0, backends_[2]->backend_service1()->request_count());
  EXPECT_EQ(0, backends_[3]->backend_service()->request_count());
  weight_25_request_count = backends_[3]->backend_service1()->request_count();
  LOG(INFO) << "target_75 received " << weight_75_request_count
            << " rpcs and target_25 received " << weight_25_request_count
            << " rpcs";
  EXPECT_THAT(static_cast<double>(weight_75_request_count) / kNumEcho1Rpcs7525,
              ::testing::DoubleNear(kWeight75Percent, kErrorTolerance));
  EXPECT_THAT(static_cast<double>(weight_25_request_count) / kNumEcho1Rpcs7525,
              ::testing::DoubleNear(kWeight25Percent, kErrorTolerance));
}

TEST_P(LdsRdsTest, XdsRoutingClusterUpdateClusters) {
  CreateAndStartBackends(2);
  const char* kNewClusterName = "new_cluster";
  const char* kNewEdsServiceName = "new_eds_service_name";
  const size_t kNumEchoRpcs = 5;

  EdsResourceArgs args({
      {"locality0", CreateEndpointsForBackends(0, 1)},
  });
  EdsResourceArgs args1({
      {"locality0", CreateEndpointsForBackends(1, 2)},
  });
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));
  balancer_->ads_service()->SetEdsResource(
      BuildEdsResource(args1, kNewEdsServiceName));

  Cluster new_cluster = default_cluster_;
  new_cluster.set_name(kNewClusterName);
  new_cluster.mutable_eds_cluster_config()->set_service_name(
      kNewEdsServiceName);
  balancer_->ads_service()->SetCdsResource(new_cluster);

  RouteConfiguration new_route_config = default_route_config_;
  SetRouteConfiguration(balancer_.get(), new_route_config);
  WaitForAllBackends(DEBUG_LOCATION, 0, 1);
  CheckRpcSendOk(DEBUG_LOCATION, kNumEchoRpcs);

  EXPECT_EQ(kNumEchoRpcs, backends_[0]->backend_service()->request_count());

  auto* default_route =
      new_route_config.mutable_virtual_hosts(0)->mutable_routes(0);
  default_route->mutable_route()->set_cluster(kNewClusterName);
  SetRouteConfiguration(balancer_.get(), new_route_config);
  WaitForAllBackends(DEBUG_LOCATION, 1, 2);
  CheckRpcSendOk(DEBUG_LOCATION, kNumEchoRpcs);

  EXPECT_EQ(kNumEchoRpcs, backends_[1]->backend_service()->request_count());
}

TEST_P(LdsRdsTest, XdsRoutingClusterUpdateClustersWithPickingDelays) {

  CreateBackends(2);
  StartBackend(1);
  EdsResourceArgs args({{"locality0", CreateEndpointsForBackends(0, 1)}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  LongRunningRpc rpc;
  rpc.StartRpc(stub_.get(),
               RpcOptions().set_wait_for_ready(true).set_timeout_ms(0));

  CheckRpcSendFailure(DEBUG_LOCATION, StatusCode::UNAVAILABLE,
                      MakeConnectionFailureRegex(
                          "connections to all backends failing; last error: "));

  const char* kNewClusterName = "new_cluster";
  const char* kNewEdsServiceName = "new_eds_service_name";
  EdsResourceArgs args1({{"locality0", CreateEndpointsForBackends(1, 2)}});
  balancer_->ads_service()->SetEdsResource(
      BuildEdsResource(args1, kNewEdsServiceName));

  Cluster new_cluster = default_cluster_;
  new_cluster.set_name(kNewClusterName);
  new_cluster.mutable_eds_cluster_config()->set_service_name(
      kNewEdsServiceName);
  balancer_->ads_service()->SetCdsResource(new_cluster);

  RouteConfiguration new_route_config = default_route_config_;
  auto* default_route =
      new_route_config.mutable_virtual_hosts(0)->mutable_routes(0);
  default_route->mutable_route()->set_cluster(kNewClusterName);
  SetRouteConfiguration(balancer_.get(), new_route_config);

  WaitForBackend(
      DEBUG_LOCATION, 1,
      [&](const RpcResult& result) {
        if (!result.status.ok()) {
          EXPECT_EQ(result.status.error_code(), StatusCode::UNAVAILABLE);
          EXPECT_THAT(
              result.status.error_message(),
              ::testing::MatchesRegex(MakeConnectionFailureRegex(
                  "connections to all backends failing; last error: ")));
        }
      },
      WaitForBackendOptions().set_reset_counters(false));

  StartBackend(0);
  Status status = rpc.GetStatus();
  EXPECT_TRUE(status.ok()) << "code=" << status.error_code()
                           << " message=" << status.error_message();

  EXPECT_EQ(1, backends_[0]->backend_service()->request_count());
  EXPECT_EQ(1, backends_[1]->backend_service()->request_count());
}

TEST_P(LdsRdsTest, XdsRoutingApplyXdsTimeout) {
  const auto kTimeoutGrpcHeaderMax = grpc_core::Duration::Milliseconds(1500);
  const auto kTimeoutMaxStreamDuration =
      grpc_core::Duration::Milliseconds(2500);
  const auto kTimeoutHttpMaxStreamDuration =
      grpc_core::Duration::Milliseconds(3500);
  const auto kTimeoutApplication = grpc_core::Duration::Milliseconds(4500);
  const char* kNewCluster1Name = "new_cluster_1";
  const char* kNewEdsService1Name = "new_eds_service_name_1";
  const char* kNewCluster2Name = "new_cluster_2";
  const char* kNewEdsService2Name = "new_eds_service_name_2";
  const char* kNewCluster3Name = "new_cluster_3";
  const char* kNewEdsService3Name = "new_eds_service_name_3";

  EdsResourceArgs args({{"locality0", {MakeNonExistentEndpoint()}}});
  EdsResourceArgs args1({{"locality0", {MakeNonExistentEndpoint()}}});
  EdsResourceArgs args2({{"locality0", {MakeNonExistentEndpoint()}}});
  EdsResourceArgs args3({{"locality0", {MakeNonExistentEndpoint()}}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));
  balancer_->ads_service()->SetEdsResource(
      BuildEdsResource(args1, kNewEdsService1Name));
  balancer_->ads_service()->SetEdsResource(
      BuildEdsResource(args2, kNewEdsService2Name));
  balancer_->ads_service()->SetEdsResource(
      BuildEdsResource(args3, kNewEdsService3Name));

  Cluster new_cluster1 = default_cluster_;
  new_cluster1.set_name(kNewCluster1Name);
  new_cluster1.mutable_eds_cluster_config()->set_service_name(
      kNewEdsService1Name);
  balancer_->ads_service()->SetCdsResource(new_cluster1);
  Cluster new_cluster2 = default_cluster_;
  new_cluster2.set_name(kNewCluster2Name);
  new_cluster2.mutable_eds_cluster_config()->set_service_name(
      kNewEdsService2Name);
  balancer_->ads_service()->SetCdsResource(new_cluster2);
  Cluster new_cluster3 = default_cluster_;
  new_cluster3.set_name(kNewCluster3Name);
  new_cluster3.mutable_eds_cluster_config()->set_service_name(
      kNewEdsService3Name);
  balancer_->ads_service()->SetCdsResource(new_cluster3);

  auto listener = default_listener_;
  HttpConnectionManager http_connection_manager;
  listener.mutable_api_listener()->mutable_api_listener()->UnpackTo(
      &http_connection_manager);

  SetProtoDuration(
      kTimeoutHttpMaxStreamDuration,
      http_connection_manager.mutable_common_http_protocol_options()
          ->mutable_max_stream_duration());
  listener.mutable_api_listener()->mutable_api_listener()->PackFrom(
      http_connection_manager);

  RouteConfiguration new_route_config = default_route_config_;

  auto* route1 = new_route_config.mutable_virtual_hosts(0)->mutable_routes(0);
  route1->mutable_match()->set_path("/grpc.testing.EchoTest1Service/Echo1");
  route1->mutable_route()->set_cluster(kNewCluster1Name);
  auto* max_stream_duration =
      route1->mutable_route()->mutable_max_stream_duration();
  SetProtoDuration(kTimeoutMaxStreamDuration,
                   max_stream_duration->mutable_max_stream_duration());
  SetProtoDuration(kTimeoutGrpcHeaderMax,
                   max_stream_duration->mutable_grpc_timeout_header_max());

  auto* route2 = new_route_config.mutable_virtual_hosts(0)->add_routes();
  route2->mutable_match()->set_path("/grpc.testing.EchoTest2Service/Echo2");
  route2->mutable_route()->set_cluster(kNewCluster2Name);
  max_stream_duration = route2->mutable_route()->mutable_max_stream_duration();
  SetProtoDuration(kTimeoutMaxStreamDuration,
                   max_stream_duration->mutable_max_stream_duration());

  auto* route3 = new_route_config.mutable_virtual_hosts(0)->add_routes();
  route3->mutable_match()->set_path("/grpc.testing.EchoTestService/Echo");
  route3->mutable_route()->set_cluster(kNewCluster3Name);

  SetListenerAndRouteConfiguration(balancer_.get(), std::move(listener),
                                   new_route_config);

  grpc_core::Timestamp t0 = NowFromCycleCounter();
  grpc_core::Timestamp t1 =
      t0 + (kTimeoutGrpcHeaderMax * grpc_test_slowdown_factor());
  grpc_core::Timestamp t2 =
      t0 + (kTimeoutMaxStreamDuration * grpc_test_slowdown_factor());
  CheckRpcSendFailure(DEBUG_LOCATION, StatusCode::DEADLINE_EXCEEDED,
                      "Deadline Exceeded",
                      RpcOptions()
                          .set_rpc_service(SERVICE_ECHO1)
                          .set_rpc_method(METHOD_ECHO1)
                          .set_wait_for_ready(true)
                          .set_timeout(kTimeoutApplication));
  EXPECT_THAT(NowFromCycleCounter(), AdjustedClockInRange(t1, t2));

  t0 = NowFromCycleCounter();
  t1 = t0 + (kTimeoutMaxStreamDuration * grpc_test_slowdown_factor());
  t2 = t0 + (kTimeoutHttpMaxStreamDuration * grpc_test_slowdown_factor());
  CheckRpcSendFailure(DEBUG_LOCATION, StatusCode::DEADLINE_EXCEEDED,
                      "Deadline Exceeded",
                      RpcOptions()
                          .set_rpc_service(SERVICE_ECHO2)
                          .set_rpc_method(METHOD_ECHO2)
                          .set_wait_for_ready(true)
                          .set_timeout(kTimeoutApplication));
  EXPECT_THAT(NowFromCycleCounter(), AdjustedClockInRange(t1, t2));

  t0 = NowFromCycleCounter();
  t1 = t0 + (kTimeoutHttpMaxStreamDuration * grpc_test_slowdown_factor());
  t2 = t0 + (kTimeoutApplication * grpc_test_slowdown_factor());
  CheckRpcSendFailure(
      DEBUG_LOCATION, StatusCode::DEADLINE_EXCEEDED, "Deadline Exceeded",
      RpcOptions().set_wait_for_ready(true).set_timeout(kTimeoutApplication));
  EXPECT_THAT(NowFromCycleCounter(), AdjustedClockInRange(t1, t2));
}

TEST_P(LdsRdsTest, XdsRoutingApplyApplicationTimeoutWhenXdsTimeoutExplicit) {
  const auto kTimeoutMaxStreamDuration =
      grpc_core::Duration::Milliseconds(2500);
  const auto kTimeoutHttpMaxStreamDuration =
      grpc_core::Duration::Milliseconds(3500);
  const auto kTimeoutApplication = grpc_core::Duration::Milliseconds(4500);
  const char* kNewCluster1Name = "new_cluster_1";
  const char* kNewEdsService1Name = "new_eds_service_name_1";
  const char* kNewCluster2Name = "new_cluster_2";
  const char* kNewEdsService2Name = "new_eds_service_name_2";

  EdsResourceArgs args({{"locality0", {MakeNonExistentEndpoint()}}});
  EdsResourceArgs args1({{"locality0", {MakeNonExistentEndpoint()}}});
  EdsResourceArgs args2({{"locality0", {MakeNonExistentEndpoint()}}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));
  balancer_->ads_service()->SetEdsResource(
      BuildEdsResource(args1, kNewEdsService1Name));
  balancer_->ads_service()->SetEdsResource(
      BuildEdsResource(args2, kNewEdsService2Name));

  Cluster new_cluster1 = default_cluster_;
  new_cluster1.set_name(kNewCluster1Name);
  new_cluster1.mutable_eds_cluster_config()->set_service_name(
      kNewEdsService1Name);
  balancer_->ads_service()->SetCdsResource(new_cluster1);
  Cluster new_cluster2 = default_cluster_;
  new_cluster2.set_name(kNewCluster2Name);
  new_cluster2.mutable_eds_cluster_config()->set_service_name(
      kNewEdsService2Name);
  balancer_->ads_service()->SetCdsResource(new_cluster2);

  auto listener = default_listener_;
  HttpConnectionManager http_connection_manager;
  listener.mutable_api_listener()->mutable_api_listener()->UnpackTo(
      &http_connection_manager);

  SetProtoDuration(
      kTimeoutHttpMaxStreamDuration,
      http_connection_manager.mutable_common_http_protocol_options()
          ->mutable_max_stream_duration());
  listener.mutable_api_listener()->mutable_api_listener()->PackFrom(
      http_connection_manager);

  RouteConfiguration new_route_config = default_route_config_;

  auto* route1 = new_route_config.mutable_virtual_hosts(0)->mutable_routes(0);
  route1->mutable_match()->set_path("/grpc.testing.EchoTest1Service/Echo1");
  route1->mutable_route()->set_cluster(kNewCluster1Name);
  auto* max_stream_duration =
      route1->mutable_route()->mutable_max_stream_duration();
  SetProtoDuration(kTimeoutMaxStreamDuration,
                   max_stream_duration->mutable_max_stream_duration());
  SetProtoDuration(grpc_core::Duration::Zero(),
                   max_stream_duration->mutable_grpc_timeout_header_max());

  auto* route2 = new_route_config.mutable_virtual_hosts(0)->add_routes();
  route2->mutable_match()->set_path("/grpc.testing.EchoTest2Service/Echo2");
  route2->mutable_route()->set_cluster(kNewCluster2Name);
  max_stream_duration = route2->mutable_route()->mutable_max_stream_duration();
  SetProtoDuration(grpc_core::Duration::Zero(),
                   max_stream_duration->mutable_max_stream_duration());

  SetListenerAndRouteConfiguration(balancer_.get(), std::move(listener),
                                   new_route_config);

  auto t0 = system_clock::now();
  CheckRpcSendFailure(DEBUG_LOCATION, StatusCode::DEADLINE_EXCEEDED,
                      "Deadline Exceeded",
                      RpcOptions()
                          .set_rpc_service(SERVICE_ECHO1)
                          .set_rpc_method(METHOD_ECHO1)
                          .set_wait_for_ready(true)
                          .set_timeout(kTimeoutApplication));
  auto elapsed_nano_seconds =
      std::chrono::duration_cast<std::chrono::nanoseconds>(system_clock::now() -
                                                           t0);
  EXPECT_GT(
      elapsed_nano_seconds.count(),
      (kTimeoutApplication * grpc_test_slowdown_factor()).millis() * 1000);

  t0 = system_clock::now();
  CheckRpcSendFailure(DEBUG_LOCATION, StatusCode::DEADLINE_EXCEEDED,
                      "Deadline Exceeded",
                      RpcOptions()
                          .set_rpc_service(SERVICE_ECHO2)
                          .set_rpc_method(METHOD_ECHO2)
                          .set_wait_for_ready(true)
                          .set_timeout(kTimeoutApplication));
  elapsed_nano_seconds = std::chrono::duration_cast<std::chrono::nanoseconds>(
      system_clock::now() - t0);
  EXPECT_GT(
      elapsed_nano_seconds.count(),
      (kTimeoutApplication * grpc_test_slowdown_factor()).millis() * 1000);
}

TEST_P(LdsRdsTest, XdsRoutingApplyApplicationTimeoutWhenHttpTimeoutExplicit) {
  const auto kTimeoutApplication = grpc_core::Duration::Milliseconds(4500);

  EdsResourceArgs args({{"locality0", {MakeNonExistentEndpoint()}}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));
  auto listener = default_listener_;
  HttpConnectionManager http_connection_manager;
  listener.mutable_api_listener()->mutable_api_listener()->UnpackTo(
      &http_connection_manager);

  auto* duration =
      http_connection_manager.mutable_common_http_protocol_options()
          ->mutable_max_stream_duration();
  duration->set_seconds(0);
  duration->set_nanos(0);
  listener.mutable_api_listener()->mutable_api_listener()->PackFrom(
      http_connection_manager);

  SetListenerAndRouteConfiguration(balancer_.get(), std::move(listener),
                                   default_route_config_);

  auto t0 = system_clock::now();
  CheckRpcSendFailure(
      DEBUG_LOCATION, StatusCode::DEADLINE_EXCEEDED, "Deadline Exceeded",
      RpcOptions().set_wait_for_ready(true).set_timeout(kTimeoutApplication));
  auto elapsed_nano_seconds =
      std::chrono::duration_cast<std::chrono::nanoseconds>(system_clock::now() -
                                                           t0);
  EXPECT_GT(
      elapsed_nano_seconds.count(),
      (kTimeoutApplication * grpc_test_slowdown_factor()).millis() * 1000);
}

TEST_P(LdsRdsTest, XdsRoutingWithOnlyApplicationTimeout) {
  const auto kTimeoutApplication = grpc_core::Duration::Milliseconds(4500);

  EdsResourceArgs args({{"locality0", {MakeNonExistentEndpoint()}}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));
  auto t0 = system_clock::now();
  CheckRpcSendFailure(
      DEBUG_LOCATION, StatusCode::DEADLINE_EXCEEDED, "Deadline Exceeded",
      RpcOptions().set_wait_for_ready(true).set_timeout(kTimeoutApplication));
  auto elapsed_nano_seconds =
      std::chrono::duration_cast<std::chrono::nanoseconds>(system_clock::now() -
                                                           t0);
  EXPECT_GT(
      elapsed_nano_seconds.count(),
      (kTimeoutApplication * grpc_test_slowdown_factor()).millis() * 1000);
}

TEST_P(LdsRdsTest, XdsRetryPolicyNumRetries) {
  CreateAndStartBackends(1);
  const size_t kNumRetries = 3;

  EdsResourceArgs args({
      {"locality0", CreateEndpointsForBackends(0, 1)},
  });
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  RouteConfiguration new_route_config = default_route_config_;
  auto* route1 = new_route_config.mutable_virtual_hosts(0)->mutable_routes(0);
  auto* retry_policy = route1->mutable_route()->mutable_retry_policy();
  retry_policy->set_retry_on(
      "5xx,cancelled,deadline-exceeded,internal,resource-exhausted,"
      "unavailable");
  retry_policy->mutable_num_retries()->set_value(kNumRetries);
  SetRouteConfiguration(balancer_.get(), new_route_config);

  CheckRpcSendFailure(
      DEBUG_LOCATION, StatusCode::CANCELLED, "",
      RpcOptions().set_server_expected_error(StatusCode::CANCELLED));
  EXPECT_EQ(kNumRetries + 1, backends_[0]->backend_service()->request_count());
  ResetBackendCounters();
  CheckRpcSendFailure(
      DEBUG_LOCATION, StatusCode::DEADLINE_EXCEEDED, "",
      RpcOptions().set_server_expected_error(StatusCode::DEADLINE_EXCEEDED));
  EXPECT_EQ(kNumRetries + 1, backends_[0]->backend_service()->request_count());
  ResetBackendCounters();
  CheckRpcSendFailure(
      DEBUG_LOCATION, StatusCode::INTERNAL, "",
      RpcOptions().set_server_expected_error(StatusCode::INTERNAL));
  EXPECT_EQ(kNumRetries + 1, backends_[0]->backend_service()->request_count());
  ResetBackendCounters();
  CheckRpcSendFailure(
      DEBUG_LOCATION, StatusCode::RESOURCE_EXHAUSTED, "",
      RpcOptions().set_server_expected_error(StatusCode::RESOURCE_EXHAUSTED));
  EXPECT_EQ(kNumRetries + 1, backends_[0]->backend_service()->request_count());
  ResetBackendCounters();
  CheckRpcSendFailure(
      DEBUG_LOCATION, StatusCode::UNAVAILABLE, "",
      RpcOptions().set_server_expected_error(StatusCode::UNAVAILABLE));
  EXPECT_EQ(kNumRetries + 1, backends_[0]->backend_service()->request_count());
  ResetBackendCounters();

  CheckRpcSendFailure(
      DEBUG_LOCATION, StatusCode::UNAUTHENTICATED, "",
      RpcOptions().set_server_expected_error(StatusCode::UNAUTHENTICATED));
  EXPECT_EQ(1, backends_[0]->backend_service()->request_count());
}

TEST_P(LdsRdsTest, XdsRetryPolicyAtVirtualHostLevel) {
  CreateAndStartBackends(1);
  const size_t kNumRetries = 3;

  EdsResourceArgs args({
      {"locality0", CreateEndpointsForBackends(0, 1)},
  });
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  RouteConfiguration new_route_config = default_route_config_;
  auto* retry_policy =
      new_route_config.mutable_virtual_hosts(0)->mutable_retry_policy();
  retry_policy->set_retry_on(
      "cancelled,deadline-exceeded,internal,resource-exhausted,unavailable");
  retry_policy->mutable_num_retries()->set_value(kNumRetries);
  SetRouteConfiguration(balancer_.get(), new_route_config);

  CheckRpcSendFailure(
      DEBUG_LOCATION, StatusCode::DEADLINE_EXCEEDED, "",
      RpcOptions().set_server_expected_error(StatusCode::DEADLINE_EXCEEDED));
  EXPECT_EQ(kNumRetries + 1, backends_[0]->backend_service()->request_count());
}

TEST_P(LdsRdsTest, XdsRetryPolicyLongBackOff) {
  CreateAndStartBackends(1);

  const size_t kNumRetries = 3;

  EdsResourceArgs args({
      {"locality0", CreateEndpointsForBackends(0, 1)},
  });
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  RouteConfiguration new_route_config = default_route_config_;
  auto* route1 = new_route_config.mutable_virtual_hosts(0)->mutable_routes(0);
  auto* retry_policy = route1->mutable_route()->mutable_retry_policy();
  retry_policy->set_retry_on(
      "5xx,cancelled,deadline-exceeded,internal,resource-exhausted,"
      "unavailable");
  retry_policy->mutable_num_retries()->set_value(kNumRetries);

  SetProtoDuration(
      grpc_core::Duration::Milliseconds(1500),
      retry_policy->mutable_retry_back_off()->mutable_base_interval());
  SetRouteConfiguration(balancer_.get(), new_route_config);

  CheckRpcSendFailure(
      DEBUG_LOCATION, StatusCode::DEADLINE_EXCEEDED, "Deadline Exceeded",
      RpcOptions().set_timeout_ms(2500).set_server_expected_error(
          StatusCode::CANCELLED));
  EXPECT_EQ(1 + 1, backends_[0]->backend_service()->request_count());
}

TEST_P(LdsRdsTest, XdsRetryPolicyMaxBackOff) {
  CreateAndStartBackends(1);

  const size_t kNumRetries = 3;

  EdsResourceArgs args({
      {"locality0", CreateEndpointsForBackends(0, 1)},
  });
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  RouteConfiguration new_route_config = default_route_config_;
  auto* route1 = new_route_config.mutable_virtual_hosts(0)->mutable_routes(0);
  auto* retry_policy = route1->mutable_route()->mutable_retry_policy();
  retry_policy->set_retry_on(
      "5xx,cancelled,deadline-exceeded,internal,resource-exhausted,"
      "unavailable");
  retry_policy->mutable_num_retries()->set_value(kNumRetries);

  SetProtoDuration(
      grpc_core::Duration::Seconds(1),
      retry_policy->mutable_retry_back_off()->mutable_base_interval());
  SetProtoDuration(
      grpc_core::Duration::Seconds(3),
      retry_policy->mutable_retry_back_off()->mutable_max_interval());
  SetRouteConfiguration(balancer_.get(), new_route_config);

  CheckRpcSendOk(DEBUG_LOCATION);
  ResetBackendCounters();

  CheckRpcSendFailure(
      DEBUG_LOCATION, StatusCode::DEADLINE_EXCEEDED, "Deadline Exceeded",
      RpcOptions().set_timeout_ms(4200).set_server_expected_error(
          StatusCode::CANCELLED));
  EXPECT_EQ(2 + 1, backends_[0]->backend_service()->request_count());
}

TEST_P(LdsRdsTest, XdsRetryPolicyUnsupportedStatusCode) {
  CreateAndStartBackends(1);
  const size_t kNumRetries = 3;

  EdsResourceArgs args({
      {"locality0", CreateEndpointsForBackends(0, 1)},
  });
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  RouteConfiguration new_route_config = default_route_config_;
  auto* route1 = new_route_config.mutable_virtual_hosts(0)->mutable_routes(0);
  auto* retry_policy = route1->mutable_route()->mutable_retry_policy();
  retry_policy->set_retry_on("5xx");
  retry_policy->mutable_num_retries()->set_value(kNumRetries);
  SetRouteConfiguration(balancer_.get(), new_route_config);

  CheckRpcSendFailure(
      DEBUG_LOCATION, StatusCode::DEADLINE_EXCEEDED, "",
      RpcOptions().set_server_expected_error(StatusCode::DEADLINE_EXCEEDED));
  EXPECT_EQ(1, backends_[0]->backend_service()->request_count());
}

TEST_P(LdsRdsTest,
       XdsRetryPolicyUnsupportedStatusCodeWithVirtualHostLevelRetry) {
  CreateAndStartBackends(1);
  const size_t kNumRetries = 3;

  EdsResourceArgs args({
      {"locality0", CreateEndpointsForBackends(0, 1)},
  });
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  RouteConfiguration new_route_config = default_route_config_;
  auto* route1 = new_route_config.mutable_virtual_hosts(0)->mutable_routes(0);
  auto* retry_policy = route1->mutable_route()->mutable_retry_policy();
  retry_policy->set_retry_on("5xx");
  retry_policy->mutable_num_retries()->set_value(kNumRetries);

  auto* virtual_host_retry_policy =
      new_route_config.mutable_virtual_hosts(0)->mutable_retry_policy();
  virtual_host_retry_policy->set_retry_on(
      "cancelled,deadline-exceeded,internal,resource-exhausted,unavailable");
  virtual_host_retry_policy->mutable_num_retries()->set_value(kNumRetries);
  SetRouteConfiguration(balancer_.get(), new_route_config);

  CheckRpcSendFailure(
      DEBUG_LOCATION, StatusCode::DEADLINE_EXCEEDED, "",
      RpcOptions().set_server_expected_error(StatusCode::DEADLINE_EXCEEDED));
  EXPECT_EQ(1, backends_[0]->backend_service()->request_count());
}

TEST_P(LdsRdsTest, XdsRoutingHeadersMatching) {
  CreateAndStartBackends(2);
  const char* kNewClusterName = "new_cluster";
  const char* kNewEdsServiceName = "new_eds_service_name";
  const size_t kNumEcho1Rpcs = 100;
  const size_t kNumEchoRpcs = 5;

  EdsResourceArgs args({
      {"locality0", CreateEndpointsForBackends(0, 1)},
  });
  EdsResourceArgs args1({
      {"locality0", CreateEndpointsForBackends(1, 2)},
  });
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));
  balancer_->ads_service()->SetEdsResource(
      BuildEdsResource(args1, kNewEdsServiceName));

  Cluster new_cluster = default_cluster_;
  new_cluster.set_name(kNewClusterName);
  new_cluster.mutable_eds_cluster_config()->set_service_name(
      kNewEdsServiceName);
  balancer_->ads_service()->SetCdsResource(new_cluster);

  RouteConfiguration route_config = default_route_config_;
  auto* route1 = route_config.mutable_virtual_hosts(0)->mutable_routes(0);
  route1->mutable_match()->set_prefix("/grpc.testing.EchoTest1Service/");
  auto* header_matcher1 = route1->mutable_match()->add_headers();
  header_matcher1->set_name("header1");
  header_matcher1->set_exact_match("POST,PUT,GET");
  auto* header_matcher2 = route1->mutable_match()->add_headers();
  header_matcher2->set_name("header2");
  header_matcher2->mutable_safe_regex_match()->set_regex("[a-z]*");
  auto* header_matcher3 = route1->mutable_match()->add_headers();
  header_matcher3->set_name("header3");
  header_matcher3->mutable_range_match()->set_start(1);
  header_matcher3->mutable_range_match()->set_end(1000);
  auto* header_matcher4 = route1->mutable_match()->add_headers();
  header_matcher4->set_name("header4");
  header_matcher4->set_present_match(false);
  auto* header_matcher5 = route1->mutable_match()->add_headers();
  header_matcher5->set_name("header5");
  header_matcher5->set_present_match(true);
  auto* header_matcher6 = route1->mutable_match()->add_headers();
  header_matcher6->set_name("header6");
  header_matcher6->set_prefix_match("/grpc");
  auto* header_matcher7 = route1->mutable_match()->add_headers();
  header_matcher7->set_name("header7");
  header_matcher7->set_suffix_match(".cc");
  header_matcher7->set_invert_match(true);
  route1->mutable_route()->set_cluster(kNewClusterName);
  auto* default_route = route_config.mutable_virtual_hosts(0)->add_routes();
  default_route->mutable_match()->set_prefix("");
  default_route->mutable_route()->set_cluster(kDefaultClusterName);
  SetRouteConfiguration(balancer_.get(), route_config);
  std::vector<std::pair<std::string, std::string>> metadata = {
      {"header1", "POST"},
      {"header2", "blah"},
      {"header3", "1"},
      {"header5", "anything"},
      {"header6", "/grpc.testing.EchoTest1Service/"},
      {"header1", "PUT"},
      {"header7", "grpc.java"},
      {"header1", "GET"},
  };
  const auto header_match_rpc_options = RpcOptions()
                                            .set_rpc_service(SERVICE_ECHO1)
                                            .set_rpc_method(METHOD_ECHO1)
                                            .set_metadata(std::move(metadata));

  WaitForBackend(DEBUG_LOCATION, 0);
  WaitForBackend(DEBUG_LOCATION, 1, nullptr,
                 WaitForBackendOptions(), header_match_rpc_options);

  CheckRpcSendOk(DEBUG_LOCATION, kNumEchoRpcs);
  CheckRpcSendOk(DEBUG_LOCATION, kNumEcho1Rpcs, header_match_rpc_options);
  EXPECT_EQ(kNumEchoRpcs, backends_[0]->backend_service()->request_count());
  EXPECT_EQ(0, backends_[0]->backend_service1()->request_count());
  EXPECT_EQ(0, backends_[0]->backend_service2()->request_count());
  EXPECT_EQ(0, backends_[1]->backend_service()->request_count());
  EXPECT_EQ(kNumEcho1Rpcs, backends_[1]->backend_service1()->request_count());
  EXPECT_EQ(0, backends_[1]->backend_service2()->request_count());
  auto response_state = RouteConfigurationResponseState(balancer_.get());
  ASSERT_TRUE(response_state.has_value());
  EXPECT_EQ(response_state->state, AdsServiceImpl::ResponseState::ACKED);
}

TEST_P(LdsRdsTest, XdsRoutingHeadersMatchingSpecialHeaderContentType) {
  CreateAndStartBackends(2);
  const char* kNewClusterName = "new_cluster";
  const char* kNewEdsServiceName = "new_eds_service_name";
  const size_t kNumEchoRpcs = 100;

  EdsResourceArgs args({
      {"locality0", CreateEndpointsForBackends(0, 1)},
  });
  EdsResourceArgs args1({
      {"locality0", CreateEndpointsForBackends(1, 2)},
  });
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));
  balancer_->ads_service()->SetEdsResource(
      BuildEdsResource(args1, kNewEdsServiceName));

  Cluster new_cluster = default_cluster_;
  new_cluster.set_name(kNewClusterName);
  new_cluster.mutable_eds_cluster_config()->set_service_name(
      kNewEdsServiceName);
  balancer_->ads_service()->SetCdsResource(new_cluster);

  RouteConfiguration route_config = default_route_config_;
  auto* route1 = route_config.mutable_virtual_hosts(0)->mutable_routes(0);
  route1->mutable_match()->set_prefix("");
  auto* header_matcher1 = route1->mutable_match()->add_headers();
  header_matcher1->set_name("content-type");
  header_matcher1->set_exact_match("notapplication/grpc");
  route1->mutable_route()->set_cluster(kNewClusterName);
  auto* default_route = route_config.mutable_virtual_hosts(0)->add_routes();
  default_route->mutable_match()->set_prefix("");
  auto* header_matcher2 = default_route->mutable_match()->add_headers();
  header_matcher2->set_name("content-type");
  header_matcher2->set_exact_match("application/grpc");
  default_route->mutable_route()->set_cluster(kDefaultClusterName);
  SetRouteConfiguration(balancer_.get(), route_config);

  WaitForAllBackends(DEBUG_LOCATION, 0, 1);

  CheckRpcSendOk(DEBUG_LOCATION, kNumEchoRpcs);
  EXPECT_EQ(kNumEchoRpcs, backends_[0]->backend_service()->request_count());
  EXPECT_EQ(0, backends_[1]->backend_service()->request_count());
  auto response_state = RouteConfigurationResponseState(balancer_.get());
  ASSERT_TRUE(response_state.has_value());
  EXPECT_EQ(response_state->state, AdsServiceImpl::ResponseState::ACKED);
}

TEST_P(LdsRdsTest, XdsRoutingHeadersMatchingSpecialCasesToIgnore) {
  CreateAndStartBackends(2);
  const char* kNewCluster1Name = "new_cluster_1";
  const char* kNewEdsService1Name = "new_eds_service_name_1";
  const size_t kNumEchoRpcs = 100;

  EdsResourceArgs args({
      {"locality0", CreateEndpointsForBackends(0, 1)},
  });
  EdsResourceArgs args1({
      {"locality0", CreateEndpointsForBackends(1, 2)},
  });
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));
  balancer_->ads_service()->SetEdsResource(
      BuildEdsResource(args1, kNewEdsService1Name));

  Cluster new_cluster1 = default_cluster_;
  new_cluster1.set_name(kNewCluster1Name);
  new_cluster1.mutable_eds_cluster_config()->set_service_name(
      kNewEdsService1Name);
  balancer_->ads_service()->SetCdsResource(new_cluster1);

  RouteConfiguration route_config = default_route_config_;
  auto* route1 = route_config.mutable_virtual_hosts(0)->mutable_routes(0);
  route1->mutable_match()->set_prefix("");
  auto* header_matcher1 = route1->mutable_match()->add_headers();
  header_matcher1->set_name("grpc-foo-bin");
  header_matcher1->set_present_match(true);
  route1->mutable_route()->set_cluster(kNewCluster1Name);
  auto* default_route = route_config.mutable_virtual_hosts(0)->add_routes();
  default_route->mutable_match()->set_prefix("");
  default_route->mutable_route()->set_cluster(kDefaultClusterName);
  SetRouteConfiguration(balancer_.get(), route_config);

  std::vector<std::pair<std::string, std::string>> metadata = {
      {"grpc-foo-bin", "grpc-foo-bin"},
  };
  WaitForAllBackends(DEBUG_LOCATION, 0, 1);
  CheckRpcSendOk(DEBUG_LOCATION, kNumEchoRpcs,
                 RpcOptions().set_metadata(metadata));

  EXPECT_EQ(kNumEchoRpcs, backends_[0]->backend_service()->request_count());
  EXPECT_EQ(0, backends_[1]->backend_service()->request_count());
  auto response_state = RouteConfigurationResponseState(balancer_.get());
  ASSERT_TRUE(response_state.has_value());
  EXPECT_EQ(response_state->state, AdsServiceImpl::ResponseState::ACKED);
}

TEST_P(LdsRdsTest, XdsRoutingRuntimeFractionMatching) {
  CreateAndStartBackends(2);
  const char* kNewClusterName = "new_cluster";
  const char* kNewEdsServiceName = "new_eds_service_name";
  const double kErrorTolerance = 0.05;
  const size_t kRouteMatchNumerator = 25;
  const double kRouteMatchPercent =
      static_cast<double>(kRouteMatchNumerator) / 100;
  const size_t kNumRpcs =
      ComputeIdealNumRpcs(kRouteMatchPercent, kErrorTolerance);

  EdsResourceArgs args({
      {"locality0", CreateEndpointsForBackends(0, 1)},
  });
  EdsResourceArgs args1({
      {"locality0", CreateEndpointsForBackends(1, 2)},
  });
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));
  balancer_->ads_service()->SetEdsResource(
      BuildEdsResource(args1, kNewEdsServiceName));

  Cluster new_cluster = default_cluster_;
  new_cluster.set_name(kNewClusterName);
  new_cluster.mutable_eds_cluster_config()->set_service_name(
      kNewEdsServiceName);
  balancer_->ads_service()->SetCdsResource(new_cluster);

  RouteConfiguration route_config = default_route_config_;
  auto* route1 = route_config.mutable_virtual_hosts(0)->mutable_routes(0);
  route1->mutable_match()
      ->mutable_runtime_fraction()
      ->mutable_default_value()
      ->set_numerator(kRouteMatchNumerator);
  route1->mutable_route()->set_cluster(kNewClusterName);
  auto* default_route = route_config.mutable_virtual_hosts(0)->add_routes();
  default_route->mutable_match()->set_prefix("");
  default_route->mutable_route()->set_cluster(kDefaultClusterName);
  SetRouteConfiguration(balancer_.get(), route_config);
  WaitForAllBackends(DEBUG_LOCATION, 0, 2);
  CheckRpcSendOk(DEBUG_LOCATION, kNumRpcs);
  const int default_backend_count =
      backends_[0]->backend_service()->request_count();
  const int matched_backend_count =
      backends_[1]->backend_service()->request_count();
  EXPECT_THAT(static_cast<double>(default_backend_count) / kNumRpcs,
              ::testing::DoubleNear(1 - kRouteMatchPercent, kErrorTolerance));
  EXPECT_THAT(static_cast<double>(matched_backend_count) / kNumRpcs,
              ::testing::DoubleNear(kRouteMatchPercent, kErrorTolerance));
  auto response_state = RouteConfigurationResponseState(balancer_.get());
  ASSERT_TRUE(response_state.has_value());
  EXPECT_EQ(response_state->state, AdsServiceImpl::ResponseState::ACKED);
}

TEST_P(LdsRdsTest, XdsRoutingHeadersMatchingUnmatchCases) {
  CreateAndStartBackends(4);
  const char* kNewCluster1Name = "new_cluster_1";
  const char* kNewEdsService1Name = "new_eds_service_name_1";
  const char* kNewCluster2Name = "new_cluster_2";
  const char* kNewEdsService2Name = "new_eds_service_name_2";
  const char* kNewCluster3Name = "new_cluster_3";
  const char* kNewEdsService3Name = "new_eds_service_name_3";
  const size_t kNumEcho1Rpcs = 100;
  const size_t kNumEchoRpcs = 5;

  EdsResourceArgs args({
      {"locality0", CreateEndpointsForBackends(0, 1)},
  });
  EdsResourceArgs args1({
      {"locality0", CreateEndpointsForBackends(1, 2)},
  });
  EdsResourceArgs args2({
      {"locality0", CreateEndpointsForBackends(2, 3)},
  });
  EdsResourceArgs args3({
      {"locality0", CreateEndpointsForBackends(3, 4)},
  });
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));
  balancer_->ads_service()->SetEdsResource(
      BuildEdsResource(args1, kNewEdsService1Name));
  balancer_->ads_service()->SetEdsResource(
      BuildEdsResource(args2, kNewEdsService2Name));
  balancer_->ads_service()->SetEdsResource(
      BuildEdsResource(args3, kNewEdsService3Name));

  Cluster new_cluster1 = default_cluster_;
  new_cluster1.set_name(kNewCluster1Name);
  new_cluster1.mutable_eds_cluster_config()->set_service_name(
      kNewEdsService1Name);
  balancer_->ads_service()->SetCdsResource(new_cluster1);
  Cluster new_cluster2 = default_cluster_;
  new_cluster2.set_name(kNewCluster2Name);
  new_cluster2.mutable_eds_cluster_config()->set_service_name(
      kNewEdsService2Name);
  balancer_->ads_service()->SetCdsResource(new_cluster2);
  Cluster new_cluster3 = default_cluster_;
  new_cluster3.set_name(kNewCluster3Name);
  new_cluster3.mutable_eds_cluster_config()->set_service_name(
      kNewEdsService3Name);
  balancer_->ads_service()->SetCdsResource(new_cluster3);

  RouteConfiguration route_config = default_route_config_;
  auto* route1 = route_config.mutable_virtual_hosts(0)->mutable_routes(0);
  route1->mutable_match()->set_prefix("/grpc.testing.EchoTest1Service/");
  auto* header_matcher1 = route1->mutable_match()->add_headers();
  header_matcher1->set_name("header1");
  header_matcher1->set_exact_match("POST");
  route1->mutable_route()->set_cluster(kNewCluster1Name);
  auto route2 = route_config.mutable_virtual_hosts(0)->add_routes();
  route2->mutable_match()->set_prefix("/grpc.testing.EchoTest1Service/");
  auto* header_matcher2 = route2->mutable_match()->add_headers();
  header_matcher2->set_name("header2");
  header_matcher2->mutable_range_match()->set_start(1);
  header_matcher2->mutable_range_match()->set_end(1000);
  route2->mutable_route()->set_cluster(kNewCluster2Name);
  auto route3 = route_config.mutable_virtual_hosts(0)->add_routes();
  route3->mutable_match()->set_prefix("/grpc.testing.EchoTest1Service/");
  auto* header_matcher3 = route3->mutable_match()->add_headers();
  header_matcher3->set_name("header3");
  header_matcher3->mutable_safe_regex_match()->set_regex("[a-z]*");
  route3->mutable_route()->set_cluster(kNewCluster3Name);
  auto* default_route = route_config.mutable_virtual_hosts(0)->add_routes();
  default_route->mutable_match()->set_prefix("");
  default_route->mutable_route()->set_cluster(kDefaultClusterName);
  SetRouteConfiguration(balancer_.get(), route_config);

  std::vector<std::pair<std::string, std::string>> metadata = {
      {"header1", "POST"},
      {"header2", "1000"},
      {"header3", "123"},
      {"header1", "GET"},
  };
  WaitForAllBackends(DEBUG_LOCATION, 0, 1);
  CheckRpcSendOk(DEBUG_LOCATION, kNumEchoRpcs,
                 RpcOptions().set_metadata(metadata));
  CheckRpcSendOk(DEBUG_LOCATION, kNumEcho1Rpcs,
                 RpcOptions()
                     .set_rpc_service(SERVICE_ECHO1)
                     .set_rpc_method(METHOD_ECHO1)
                     .set_metadata(metadata));

  for (size_t i = 1; i < 4; ++i) {
    EXPECT_EQ(0, backends_[i]->backend_service()->request_count());
    EXPECT_EQ(0, backends_[i]->backend_service1()->request_count());
    EXPECT_EQ(0, backends_[i]->backend_service2()->request_count());
  }
  EXPECT_EQ(kNumEchoRpcs, backends_[0]->backend_service()->request_count());
  EXPECT_EQ(kNumEcho1Rpcs, backends_[0]->backend_service1()->request_count());
  EXPECT_EQ(0, backends_[0]->backend_service2()->request_count());
  auto response_state = RouteConfigurationResponseState(balancer_.get());
  ASSERT_TRUE(response_state.has_value());
  EXPECT_EQ(response_state->state, AdsServiceImpl::ResponseState::ACKED);
}

TEST_P(LdsRdsTest, XdsRoutingChangeRoutesWithoutChangingClusters) {
  CreateAndStartBackends(2);
  const char* kNewClusterName = "new_cluster";
  const char* kNewEdsServiceName = "new_eds_service_name";

  EdsResourceArgs args({
      {"locality0", CreateEndpointsForBackends(0, 1)},
  });
  EdsResourceArgs args1({
      {"locality0", CreateEndpointsForBackends(1, 2)},
  });
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));
  balancer_->ads_service()->SetEdsResource(
      BuildEdsResource(args1, kNewEdsServiceName));

  Cluster new_cluster = default_cluster_;
  new_cluster.set_name(kNewClusterName);
  new_cluster.mutable_eds_cluster_config()->set_service_name(
      kNewEdsServiceName);
  balancer_->ads_service()->SetCdsResource(new_cluster);

  RouteConfiguration route_config = default_route_config_;
  auto* route1 = route_config.mutable_virtual_hosts(0)->mutable_routes(0);
  route1->mutable_match()->set_prefix("/grpc.testing.EchoTest1Service/");
  route1->mutable_route()->set_cluster(kNewClusterName);
  auto* default_route = route_config.mutable_virtual_hosts(0)->add_routes();
  default_route->mutable_match()->set_prefix("");
  default_route->mutable_route()->set_cluster(kDefaultClusterName);
  SetRouteConfiguration(balancer_.get(), route_config);

  WaitForBackend(DEBUG_LOCATION, 0, nullptr,
                 WaitForBackendOptions().set_reset_counters(false));
  WaitForBackend(DEBUG_LOCATION, 1, nullptr,
                 WaitForBackendOptions().set_reset_counters(false),
                 RpcOptions().set_rpc_service(SERVICE_ECHO1));
  WaitForBackend(DEBUG_LOCATION, 0, nullptr,
                 WaitForBackendOptions().set_reset_counters(false),
                 RpcOptions().set_rpc_service(SERVICE_ECHO2));

  EXPECT_EQ(1, backends_[0]->backend_service()->request_count());
  EXPECT_EQ(0, backends_[0]->backend_service1()->request_count());
  EXPECT_EQ(1, backends_[0]->backend_service2()->request_count());

  EXPECT_EQ(0, backends_[1]->backend_service()->request_count());
  EXPECT_EQ(1, backends_[1]->backend_service1()->request_count());
  EXPECT_EQ(0, backends_[1]->backend_service2()->request_count());

  route1->mutable_match()->set_prefix("/grpc.testing.EchoTest2Service/");
  SetRouteConfiguration(balancer_.get(), route_config);
  WaitForBackend(DEBUG_LOCATION, 1, nullptr,
                 WaitForBackendOptions(),
                 RpcOptions().set_rpc_service(SERVICE_ECHO2));

  WaitForBackend(DEBUG_LOCATION, 0, nullptr,
                 WaitForBackendOptions().set_reset_counters(false));
  WaitForBackend(DEBUG_LOCATION, 0, nullptr,
                 WaitForBackendOptions().set_reset_counters(false),
                 RpcOptions().set_rpc_service(SERVICE_ECHO1));
  WaitForBackend(DEBUG_LOCATION, 1, nullptr,
                 WaitForBackendOptions().set_reset_counters(false),
                 RpcOptions().set_rpc_service(SERVICE_ECHO2));

  EXPECT_EQ(1, backends_[0]->backend_service()->request_count());
  EXPECT_EQ(1, backends_[0]->backend_service1()->request_count());
  EXPECT_EQ(0, backends_[0]->backend_service2()->request_count());

  EXPECT_EQ(0, backends_[1]->backend_service()->request_count());
  EXPECT_EQ(0, backends_[1]->backend_service1()->request_count());
  EXPECT_EQ(1, backends_[1]->backend_service2()->request_count());
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
  const auto result = RUN_ALL_TESTS();
  grpc_shutdown();
  return result;
}
