// Copyright 2023 gRPC authors.

#include <string>
#include <vector>

#include "absl/log/log.h"
#include "absl/strings/str_format.h"
#include "absl/strings/str_join.h"
#include "absl/strings/str_split.h"
#include "envoy/extensions/filters/http/stateful_session/v3/stateful_session.pb.h"
#include "envoy/extensions/http/stateful_session/cookie/v3/cookie.pb.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "src/core/config/config_vars.h"
#include "src/core/util/time.h"
#include "test/core/test_util/scoped_env_var.h"
#include "test/cpp/end2end/xds/xds_end2end_test_lib.h"

namespace grpc {
namespace testing {
namespace {
using ::envoy::config::core::v3::HealthStatus;
using ::envoy::config::route::v3::Route;
using ::envoy::extensions::filters::http::stateful_session::v3::StatefulSession;
using ::envoy::extensions::filters::http::stateful_session::v3::
    StatefulSessionPerRoute;
using ::envoy::extensions::filters::network::http_connection_manager::v3::
    HttpFilter;
using ::envoy::extensions::http::stateful_session::cookie::v3 ::
    CookieBasedSessionState;

constexpr absl::string_view kCookieName = "grpc_session_cookie";
constexpr absl::string_view kFilterName = "envoy.stateful_session";

class OverrideHostTest : public XdsEnd2endTest {
 protected:
  struct Cookie {
    std::string name;
    std::string value;
    std::set<std::string> attributes;

    std::pair<std::string, std::string> Header() const {
      return std::pair("cookie", absl::StrFormat("%s=%s", name, value));
    }

    template <typename Sink>
    friend void AbslStringify(Sink& sink, const Cookie& cookie) {
      absl::Format(&sink, "(Cookie: %s, value: %s, attributes: {%s})",
                   cookie.name, cookie.value,
                   absl::StrJoin(cookie.attributes, ", "));
    }
  };

  static Cookie ParseCookie(absl::string_view header) {
    Cookie cookie;
    std::pair<absl::string_view, absl::string_view> string_pair =
        absl::StrSplit(header, absl::MaxSplits('=', 1));
    auto [name, rest] = string_pair;
    string_pair = absl::StrSplit(rest, absl::MaxSplits(';', 1));
    auto& [value, attributes] = string_pair;
    cookie.name = std::string(name);
    cookie.value = std::string(value);
    std::string decoded;
    EXPECT_TRUE(absl::Base64Unescape(value, &decoded));
    LOG(INFO) << "set-cookie header: " << header << " (decoded: " << decoded
              << ")";
    for (absl::string_view attribute : absl::StrSplit(attributes, ';')) {
      cookie.attributes.emplace(absl::StripAsciiWhitespace(attribute));
    }
    return cookie;
  }

  static std::vector<Cookie> GetCookies(
      const std::multimap<std::string, std::string>& server_initial_metadata) {
    std::vector<Cookie> values;
    auto [start, end] = server_initial_metadata.equal_range("set-cookie");
    for (auto it = start; it != end; ++it) {
      values.emplace_back(ParseCookie(it->second));
      EXPECT_FALSE(values.back().value.empty());
      EXPECT_THAT(values.back().attributes, ::testing::Contains("HttpOnly"));
    }
    return values;
  }

  Listener BuildListenerWithStatefulSessionFilter(
      absl::string_view cookie_name = kCookieName) {
    StatefulSession stateful_session;
    if (!cookie_name.empty()) {
      CookieBasedSessionState cookie_state;
      cookie_state.mutable_cookie()->set_name(std::string(cookie_name));
      stateful_session.mutable_session_state()
          ->mutable_typed_config()
          ->PackFrom(cookie_state);
    }

    Listener listener = default_listener_;
    HttpConnectionManager http_connection_manager =
        ClientHcmAccessor().Unpack(listener);

    HttpFilter* session_filter =
        http_connection_manager.mutable_http_filters(0);
    *http_connection_manager.add_http_filters() = *session_filter;
    session_filter->set_name(kFilterName);
    session_filter->mutable_typed_config()->PackFrom(stateful_session);
    ClientHcmAccessor().Pack(http_connection_manager, &listener);
    return listener;
  }

  std::vector<Cookie> GetCookiesForBackend(
      grpc_core::DebugLocation debug_location, size_t backend_index,
      size_t max_requests_per_backend = 1,
      const RpcOptions& options = RpcOptions()) {
    EXPECT_LT(backend_index, backends_.size());
    if (backend_index >= backends_.size()) {
      return {};
    }
    const auto& backend = backends_[backend_index];
    for (size_t i = 0; i < max_requests_per_backend * backends_.size(); ++i) {
      std::multimap<std::string, std::string> server_initial_metadata;
      grpc::Status status = SendRpc(options, nullptr, &server_initial_metadata);
      EXPECT_TRUE(status.ok())
          << "code=" << status.error_code()
          << ", message=" << status.error_message() << "\n"
          << debug_location.file() << ":" << debug_location.line();
      if (!status.ok()) {
        return {};
      }
      size_t count = backend->backend_service()->request_count() +
                     backend->backend_service1()->request_count() +
                     backend->backend_service2()->request_count();
      ResetBackendCounters();
      if (count == 1) {
        return GetCookies(server_initial_metadata);
      }
    }
    ADD_FAILURE_AT(debug_location.file(), debug_location.line())
        << "Desired backend had not been hit";
    return {};
  }

  std::optional<std::pair<std::string, std::string>>
  GetAffinityCookieHeaderForBackend(
      grpc_core::DebugLocation debug_location, size_t backend_index,
      size_t max_requests_per_backend = 1,
      const RpcOptions& options = RpcOptions(),
      absl::string_view cookie_name = kCookieName) {
    auto cookies = GetCookiesForBackend(debug_location, backend_index,
                                        max_requests_per_backend, options);
    for (const auto& cookie : cookies) {
      if (cookie.name == cookie_name) {
        return cookie.Header();
      }
    }
    return std::nullopt;
  }

  void SetClusterResource(absl::string_view cluster_name,
                          absl::string_view eds_resource_name) {
    Cluster cluster = default_cluster_;
    cluster.set_name(cluster_name);
    cluster.mutable_eds_cluster_config()->set_service_name(eds_resource_name);
    balancer_->ads_service()->SetCdsResource(cluster);
  }

  RouteConfiguration BuildRouteConfigurationWithWeightedClusters(
      const std::map<absl::string_view, uint32_t>& clusters) {
    RouteConfiguration new_route_config = default_route_config_;
    auto* route1 = new_route_config.mutable_virtual_hosts(0)->mutable_routes(0);
    for (const auto& [cluster, weight] : clusters) {
      auto* weighted_cluster =
          route1->mutable_route()->mutable_weighted_clusters()->add_clusters();
      weighted_cluster->set_name(cluster);
      weighted_cluster->mutable_weight()->set_value(weight);
    }
    return new_route_config;
  }

  void SetCdsAndEdsResources(absl::string_view cluster_name,
                             absl::string_view eds_service_name,
                             size_t start_index, size_t end_index) {
    balancer_->ads_service()->SetEdsResource(BuildEdsResource(
        EdsResourceArgs({{"locality0",
                          CreateEndpointsForBackends(start_index, end_index)}}),
        eds_service_name));
    SetClusterResource(cluster_name, eds_service_name);
  }

  static double BackendRequestPercentage(
      const std::unique_ptr<BackendServerThread>& backend,
      size_t num_requests) {
    return static_cast<double>(backend->backend_service()->request_count()) /
           num_requests;
  }

  static Route BuildStatefulSessionRouteConfig(
      absl::string_view match_prefix, absl::string_view cookie_name,
      std::optional<grpc_core::Duration> opt_duration = std::nullopt) {
    StatefulSessionPerRoute stateful_session_per_route;
    if (!cookie_name.empty()) {
      auto* session_state =
          stateful_session_per_route.mutable_stateful_session()
              ->mutable_session_state();
      session_state->set_name("envoy.http.stateful_session.cookie");
      CookieBasedSessionState cookie_config;
      cookie_config.mutable_cookie()->set_name(cookie_name);
      if (opt_duration.has_value()) {
        cookie_config.mutable_cookie()->mutable_ttl()->set_seconds(
            opt_duration->seconds());
      }
      session_state->mutable_typed_config()->PackFrom(cookie_config);
    }
    google::protobuf::Any any;
    any.PackFrom(stateful_session_per_route);
    Route route;
    route.mutable_match()->set_prefix(match_prefix);
    route.mutable_route()->set_cluster(kDefaultClusterName);
    route.mutable_typed_per_filter_config()->emplace(kFilterName, any);
    return route;
  }

  static std::string CookieNames(absl::Span<const Cookie> cookies) {
    std::vector<absl::string_view> names;
    for (const auto& cookie : cookies) {
      names.emplace_back(cookie.name);
    }
    absl::c_sort(names);
    return absl::StrJoin(names, ", ");
  }
};

INSTANTIATE_TEST_SUITE_P(XdsTest, OverrideHostTest,
                         ::testing::Values(XdsTestType()), &XdsTestType::Name);

TEST_P(OverrideHostTest, HappyPath) {
  CreateAndStartBackends(2);
  SetListenerAndRouteConfiguration(balancer_.get(),
                                   BuildListenerWithStatefulSessionFilter(),
                                   default_route_config_);
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(
      EdsResourceArgs({{"locality0",
                        {CreateEndpoint(0, HealthStatus::HEALTHY),
                         CreateEndpoint(1, HealthStatus::UNKNOWN)}}})));
  WaitForAllBackends(DEBUG_LOCATION);

  auto cookies = GetCookiesForBackend(DEBUG_LOCATION, 0);
  ASSERT_THAT(cookies,
              ::testing::ElementsAre(::testing::AllOf(
                  ::testing::Field("name", &Cookie::name, kCookieName),
                  ::testing::Field("attributes", &Cookie::attributes,
                                   ::testing::ElementsAre("HttpOnly")),
                  ::testing::Field("value", &Cookie::value,
                                   ::testing::Not(::testing::IsEmpty())))));

  CheckRpcSendOk(DEBUG_LOCATION, 5,
                 RpcOptions().set_metadata({cookies.front().Header()}));
  EXPECT_EQ(backends_[0]->backend_service()->request_count(), 5);

  ResetBackendCounters();
  CheckRpcSendOk(DEBUG_LOCATION, backends_.size() * 2);
  EXPECT_EQ(2, backends_[0]->backend_service()->request_count());
  EXPECT_EQ(2, backends_[1]->backend_service()->request_count());

  ResetBackendCounters();
  CheckRpcSendOk(DEBUG_LOCATION, 5,
                 RpcOptions()
                     .set_metadata({cookies.front().Header()})
                     .set_rpc_service(RpcService::SERVICE_ECHO2));
  EXPECT_EQ(backends_[0]->backend_service2()->request_count(), 5);
}

TEST_P(OverrideHostTest, AffinityWorksAcrossPriorities) {
  CreateAndStartBackends(3);
  SetListenerAndRouteConfiguration(balancer_.get(),
                                   BuildListenerWithStatefulSessionFilter(),
                                   default_route_config_);

  balancer_->ads_service()->SetEdsResource(BuildEdsResource(
      EdsResourceArgs({{"locality0", CreateEndpointsForBackends(0, 2)}})));
  WaitForAllBackends(DEBUG_LOCATION, 0, 2);

  auto cookies = GetCookiesForBackend(DEBUG_LOCATION, 1);
  ASSERT_THAT(cookies,
              ::testing::ElementsAre(::testing::AllOf(
                  ::testing::Field("name", &Cookie::name, kCookieName),
                  ::testing::Field("attributes", &Cookie::attributes,
                                   ::testing::ElementsAre("HttpOnly")),
                  ::testing::Field("value", &Cookie::value,
                                   ::testing::Not(::testing::IsEmpty())))));

  CheckRpcSendOk(DEBUG_LOCATION, 5,
                 RpcOptions().set_metadata({cookies.front().Header()}));
  EXPECT_EQ(backends_[1]->backend_service()->request_count(), 5);

  balancer_->ads_service()->SetEdsResource(BuildEdsResource(EdsResourceArgs({
      {"locality1", CreateEndpointsForBackends(2, 3)},
      {"locality0", CreateEndpointsForBackends(0, 2), kDefaultLocalityWeight,
       1},
  })));
  WaitForBackend(DEBUG_LOCATION, 2);

  CheckRpcSendOk(DEBUG_LOCATION, 5,
                 RpcOptions().set_metadata({cookies.front().Header()}));
  EXPECT_EQ(backends_[1]->backend_service()->request_count(), 5);
}

TEST_P(OverrideHostTest,
       AffinityWorksAcrossPrioritiesHeuristicChangesChildName) {
  CreateAndStartBackends(3);
  SetListenerAndRouteConfiguration(balancer_.get(),
                                   BuildListenerWithStatefulSessionFilter(),
                                   default_route_config_);

  balancer_->ads_service()->SetEdsResource(BuildEdsResource(EdsResourceArgs({
      {"locality0", CreateEndpointsForBackends(0, 1)},
      {"locality1", CreateEndpointsForBackends(1, 2)},
  })));
  WaitForAllBackends(DEBUG_LOCATION, 0, 2);

  auto cookies =
      GetCookiesForBackend(DEBUG_LOCATION, 1, 10);
  ASSERT_THAT(cookies,
              ::testing::ElementsAre(::testing::AllOf(
                  ::testing::Field("name", &Cookie::name, kCookieName),
                  ::testing::Field("attributes", &Cookie::attributes,
                                   ::testing::ElementsAre("HttpOnly")),
                  ::testing::Field("value", &Cookie::value,
                                   ::testing::Not(::testing::IsEmpty())))));

  CheckRpcSendOk(DEBUG_LOCATION, 5,
                 RpcOptions().set_metadata({cookies.front().Header()}));
  EXPECT_EQ(backends_[1]->backend_service()->request_count(), 5);

  balancer_->ads_service()->SetEdsResource(BuildEdsResource(EdsResourceArgs({
      {"locality0", CreateEndpointsForBackends(0, 1)},
      {"locality2", CreateEndpointsForBackends(2, 3)},
      {"locality1", CreateEndpointsForBackends(1, 2), kDefaultLocalityWeight,
       1},
  })));
  WaitForBackend(DEBUG_LOCATION, 2);

  CheckRpcSendOk(DEBUG_LOCATION, 5,
                 RpcOptions().set_metadata({cookies.front().Header()}));
  EXPECT_EQ(backends_[1]->backend_service()->request_count(), 5);
}

TEST_P(OverrideHostTest, DrainingIncludedFromOverrideSet) {
  CreateAndStartBackends(3);
  Cluster cluster = default_cluster_;
  auto* lb_config = cluster.mutable_common_lb_config();
  auto* override_health_status_set = lb_config->mutable_override_host_status();
  override_health_status_set->add_statuses(HealthStatus::HEALTHY);
  override_health_status_set->add_statuses(HealthStatus::UNKNOWN);
  override_health_status_set->add_statuses(HealthStatus::DRAINING);
  balancer_->ads_service()->SetCdsResource(cluster);
  SetListenerAndRouteConfiguration(balancer_.get(),
                                   BuildListenerWithStatefulSessionFilter(),
                                   default_route_config_);
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(
      EdsResourceArgs({{"locality0",
                        {CreateEndpoint(0, HealthStatus::HEALTHY),
                         CreateEndpoint(1, HealthStatus::HEALTHY)}}})));
  WaitForAllBackends(DEBUG_LOCATION, 0, 2);
  CheckRpcSendOk(DEBUG_LOCATION, 4);
  EXPECT_EQ(2, backends_[0]->backend_service()->request_count());
  EXPECT_EQ(2, backends_[1]->backend_service()->request_count());
  EXPECT_EQ(0, backends_[2]->backend_service()->request_count());
  ResetBackendCounters();

  auto session_cookie = GetAffinityCookieHeaderForBackend(DEBUG_LOCATION, 0);
  ASSERT_TRUE(session_cookie.has_value());
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(
      EdsResourceArgs({{"locality0",
                        {CreateEndpoint(0, HealthStatus::DRAINING),
                         CreateEndpoint(1, HealthStatus::HEALTHY),
                         CreateEndpoint(2, HealthStatus::HEALTHY)}}})));
  WaitForAllBackends(DEBUG_LOCATION, 2);

  CheckRpcSendOk(DEBUG_LOCATION, 4,
                 RpcOptions().set_metadata({*session_cookie}));
  EXPECT_EQ(4, backends_[0]->backend_service()->request_count());
  EXPECT_EQ(0, backends_[1]->backend_service()->request_count());
  EXPECT_EQ(0, backends_[2]->backend_service()->request_count());
  ResetBackendCounters();

  CheckRpcSendOk(DEBUG_LOCATION, 4);
  EXPECT_EQ(0, backends_[0]->backend_service()->request_count());
  EXPECT_EQ(2, backends_[1]->backend_service()->request_count());
  EXPECT_EQ(2, backends_[2]->backend_service()->request_count());
  ResetBackendCounters();
}

TEST_P(OverrideHostTest, DrainingExcludedFromOverrideSet) {
  CreateAndStartBackends(3);
  Cluster cluster = default_cluster_;
  auto* lb_config = cluster.mutable_common_lb_config();
  auto* override_health_status_set = lb_config->mutable_override_host_status();
  override_health_status_set->add_statuses(HealthStatus::HEALTHY);
  override_health_status_set->add_statuses(HealthStatus::UNKNOWN);
  balancer_->ads_service()->SetCdsResource(cluster);
  SetListenerAndRouteConfiguration(balancer_.get(),
                                   BuildListenerWithStatefulSessionFilter(),
                                   default_route_config_);
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(
      EdsResourceArgs({{"locality0",
                        {CreateEndpoint(0, HealthStatus::HEALTHY),
                         CreateEndpoint(1, HealthStatus::HEALTHY)}}})));
  WaitForAllBackends(DEBUG_LOCATION, 0, 2);
  CheckRpcSendOk(DEBUG_LOCATION, 4);
  EXPECT_EQ(2, backends_[0]->backend_service()->request_count());
  EXPECT_EQ(2, backends_[1]->backend_service()->request_count());
  EXPECT_EQ(0, backends_[2]->backend_service()->request_count());
  ResetBackendCounters();

  auto session_cookie = GetAffinityCookieHeaderForBackend(DEBUG_LOCATION, 0);
  ASSERT_TRUE(session_cookie.has_value());
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(
      EdsResourceArgs({{"locality0",
                        {CreateEndpoint(0, HealthStatus::DRAINING),
                         CreateEndpoint(1, HealthStatus::HEALTHY),
                         CreateEndpoint(2, HealthStatus::UNKNOWN)}}})));
  WaitForAllBackends(DEBUG_LOCATION, 2);

  CheckRpcSendOk(DEBUG_LOCATION, 4,
                 RpcOptions().set_metadata({*session_cookie}));
  EXPECT_EQ(0, backends_[0]->backend_service()->request_count());
  EXPECT_EQ(2, backends_[1]->backend_service()->request_count());
  EXPECT_EQ(2, backends_[2]->backend_service()->request_count());
  ResetBackendCounters();
}

TEST_P(OverrideHostTest, UnhealthyEndpoint) {
  CreateAndStartBackends(3);
  Cluster cluster = default_cluster_;
  auto* lb_config = cluster.mutable_common_lb_config();
  auto* override_health_status_set = lb_config->mutable_override_host_status();
  override_health_status_set->add_statuses(HealthStatus::HEALTHY);
  override_health_status_set->add_statuses(HealthStatus::DRAINING);
  override_health_status_set->add_statuses(HealthStatus::DEGRADED);
  override_health_status_set->add_statuses(HealthStatus::UNKNOWN);
  balancer_->ads_service()->SetCdsResource(cluster);
  SetListenerAndRouteConfiguration(balancer_.get(),
                                   BuildListenerWithStatefulSessionFilter(),
                                   default_route_config_);
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(
      EdsResourceArgs({{"locality0",
                        {CreateEndpoint(0, HealthStatus::HEALTHY),
                         CreateEndpoint(1, HealthStatus::HEALTHY)}}})));
  WaitForAllBackends(DEBUG_LOCATION, 0, 2);
  CheckRpcSendOk(DEBUG_LOCATION, 4);
  EXPECT_EQ(2, backends_[0]->backend_service()->request_count());
  EXPECT_EQ(2, backends_[1]->backend_service()->request_count());
  EXPECT_EQ(0, backends_[2]->backend_service()->request_count());
  ResetBackendCounters();

  auto session_cookie = GetAffinityCookieHeaderForBackend(DEBUG_LOCATION, 0);
  ASSERT_TRUE(session_cookie.has_value());
  LOG(INFO) << session_cookie->first << " " << session_cookie->second;
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(
      EdsResourceArgs({{"locality0",
                        {CreateEndpoint(0, HealthStatus::UNHEALTHY),
                         CreateEndpoint(1, HealthStatus::HEALTHY),
                         CreateEndpoint(2, HealthStatus::HEALTHY)}}})));
  WaitForAllBackends(DEBUG_LOCATION, 2);

  CheckRpcSendOk(DEBUG_LOCATION, 2,
                 RpcOptions().set_metadata({*session_cookie}));
  EXPECT_EQ(0, backends_[0]->backend_service()->request_count());
  EXPECT_EQ(1, backends_[1]->backend_service()->request_count());
  EXPECT_EQ(1, backends_[2]->backend_service()->request_count());
  ResetBackendCounters();
}

TEST_P(OverrideHostTest, OverrideWithWeightedClusters) {
  CreateAndStartBackends(3);
  const char* kNewCluster1Name = "new_cluster_1";
  const char* kNewEdsService1Name = "new_eds_service_name_1";
  const char* kNewCluster2Name = "new_cluster_2";
  const char* kNewEdsService2Name = "new_eds_service_name_2";
  const uint32_t kWeight1 = 1;
  const uint32_t kWeight2 = 3;
  const double kErrorTolerance = 0.025;
  const size_t kNumEchoRpcs = ComputeIdealNumRpcs(
      static_cast<double>(kWeight1) / (kWeight1 + kWeight2), kErrorTolerance);

  SetCdsAndEdsResources(kNewCluster1Name, kNewEdsService1Name, 0, 1);
  SetCdsAndEdsResources(kNewCluster2Name, kNewEdsService2Name, 1, 3);

  SetListenerAndRouteConfiguration(
      balancer_.get(), BuildListenerWithStatefulSessionFilter(),
      BuildRouteConfigurationWithWeightedClusters(
          {{kNewCluster1Name, kWeight1}, {kNewCluster2Name, kWeight2}}));
  WaitForAllBackends(DEBUG_LOCATION, 0, 3);

  auto session_cookie =
      GetAffinityCookieHeaderForBackend(DEBUG_LOCATION, 1, kNumEchoRpcs / 3);
  ASSERT_TRUE(session_cookie.has_value());

  CheckRpcSendOk(DEBUG_LOCATION, kNumEchoRpcs,
                 RpcOptions().set_metadata({*session_cookie}));
  EXPECT_EQ(backends_[0]->backend_service()->request_count(), 0);
  EXPECT_EQ(backends_[1]->backend_service()->request_count(), kNumEchoRpcs);
  EXPECT_EQ(backends_[2]->backend_service()->request_count(), 0);
}

TEST_P(OverrideHostTest, ClusterOverrideHonoredButHostGone) {
  CreateAndStartBackends(4);
  const char* kNewCluster1Name = "new_cluster_1";
  const char* kNewEdsService1Name = "new_eds_service_name_1";
  const char* kNewCluster2Name = "new_cluster_2";
  const char* kNewEdsService2Name = "new_eds_service_name_2";
  const uint32_t kWeight1 = 1;
  const uint32_t kWeight2 = 3;
  const double kErrorTolerance = 0.025;
  const double kWeight2Percent =
      static_cast<double>(kWeight2) / (kWeight1 + kWeight2);
  const size_t kNumEchoRpcs =
      ComputeIdealNumRpcs(kWeight2Percent, kErrorTolerance);

  SetCdsAndEdsResources(kNewCluster1Name, kNewEdsService1Name, 0, 1);
  SetCdsAndEdsResources(kNewCluster2Name, kNewEdsService2Name, 1, 3);

  SetListenerAndRouteConfiguration(
      balancer_.get(), BuildListenerWithStatefulSessionFilter(),
      BuildRouteConfigurationWithWeightedClusters(
          {{kNewCluster1Name, kWeight1}, {kNewCluster2Name, kWeight2}}));
  WaitForAllBackends(DEBUG_LOCATION, 0, 3);
  auto session_cookie =
      GetAffinityCookieHeaderForBackend(DEBUG_LOCATION, 1, kNumEchoRpcs / 4);
  ASSERT_TRUE(session_cookie.has_value());

  balancer_->ads_service()->SetEdsResource(BuildEdsResource(
      EdsResourceArgs({{"locality0", CreateEndpointsForBackends(2, 4)}}),
      kNewEdsService2Name));
  WaitForAllBackends(DEBUG_LOCATION, 3, 4);
  CheckRpcSendOk(DEBUG_LOCATION, kNumEchoRpcs,
                 RpcOptions().set_metadata({*session_cookie}));

  EXPECT_THAT(BackendRequestPercentage(backends_[2], kNumEchoRpcs),
              ::testing::DoubleNear(.5, kErrorTolerance));
  EXPECT_THAT(BackendRequestPercentage(backends_[3], kNumEchoRpcs),
              ::testing::DoubleNear(.5, kErrorTolerance));
  EXPECT_NE(session_cookie, GetAffinityCookieHeaderForBackend(
                                DEBUG_LOCATION, 2, kNumEchoRpcs / 3));
}

TEST_P(OverrideHostTest, ClusterGoneHostStays) {
  CreateAndStartBackends(3);
  const char* kNewCluster1Name = "new_cluster_1";
  const char* kNewEdsService1Name = "new_eds_service_name_1";
  const char* kNewCluster2Name = "new_cluster_2";
  const char* kNewEdsService2Name = "new_eds_service_name_2";
  const char* kNewCluster3Name = "new_cluster_3";
  const char* kNewEdsService3Name = "new_eds_service_name_3";
  const uint32_t kWeight1 = 1;
  const uint32_t kWeight2 = 3;
  const double kErrorTolerance = 0.025;
  const double kPercentage1 =
      static_cast<double>(kWeight1) / (kWeight1 + kWeight2);
  const size_t kNumEchoRpcs =
      ComputeIdealNumRpcs(kPercentage1, kErrorTolerance);

  SetCdsAndEdsResources(kNewCluster1Name, kNewEdsService1Name, 0, 1);
  SetCdsAndEdsResources(kNewCluster2Name, kNewEdsService2Name, 1, 2);

  SetListenerAndRouteConfiguration(
      balancer_.get(), BuildListenerWithStatefulSessionFilter(),
      BuildRouteConfigurationWithWeightedClusters(
          {{kNewCluster1Name, kWeight1}, {kNewCluster2Name, kWeight2}}));
  WaitForAllBackends(DEBUG_LOCATION, 0, 2);
  auto backend1_in_cluster2_cookie =
      GetAffinityCookieHeaderForBackend(DEBUG_LOCATION, 1, kNumEchoRpcs / 3);
  ASSERT_TRUE(backend1_in_cluster2_cookie.has_value());

  SetCdsAndEdsResources(kNewCluster3Name, kNewEdsService3Name, 2, 3);

  balancer_->ads_service()->SetEdsResource(BuildEdsResource(
      EdsResourceArgs({{"locality0", CreateEndpointsForBackends(0, 2)}}),
      kNewEdsService1Name));
  SetListenerAndRouteConfiguration(
      balancer_.get(), BuildListenerWithStatefulSessionFilter(),
      BuildRouteConfigurationWithWeightedClusters(
          {{kNewCluster1Name, kWeight1}, {kNewCluster3Name, kWeight2}}));
  WaitForAllBackends(DEBUG_LOCATION, 2);
  CheckRpcSendOk(DEBUG_LOCATION, kNumEchoRpcs,
                 RpcOptions().set_metadata({*backend1_in_cluster2_cookie}));

  EXPECT_THAT(BackendRequestPercentage(backends_[0], kNumEchoRpcs),
              ::testing::DoubleNear(0, kErrorTolerance));
  EXPECT_THAT(BackendRequestPercentage(backends_[1], kNumEchoRpcs),
              ::testing::DoubleNear(kPercentage1, kErrorTolerance));
  EXPECT_THAT(BackendRequestPercentage(backends_[2], kNumEchoRpcs),
              ::testing::DoubleNear(1 - kPercentage1, kErrorTolerance));

  EXPECT_NE(
      backend1_in_cluster2_cookie,
      GetAffinityCookieHeaderForBackend(DEBUG_LOCATION, 1, kNumEchoRpcs / 3));
}

TEST_P(OverrideHostTest, EnabledInRouteConfig) {
  CreateAndStartBackends(2);
  RouteConfiguration route_config = default_route_config_;
  *route_config.mutable_virtual_hosts(0)->mutable_routes(0) =
      BuildStatefulSessionRouteConfig("", kCookieName);
  SetListenerAndRouteConfiguration(balancer_.get(),
                                   BuildListenerWithStatefulSessionFilter(""),
                                   route_config);
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(EdsResourceArgs(
      {{"locality0", {CreateEndpoint(0), CreateEndpoint(1)}}})));
  WaitForAllBackends(DEBUG_LOCATION);

  auto session_cookie = GetAffinityCookieHeaderForBackend(DEBUG_LOCATION, 0);
  ASSERT_TRUE(session_cookie.has_value());

  CheckRpcSendOk(DEBUG_LOCATION, 5,
                 RpcOptions().set_metadata({*session_cookie}));
  EXPECT_EQ(backends_[0]->backend_service()->request_count(), 5);
}

TEST_P(OverrideHostTest, DifferentPerRoute) {
  constexpr absl::string_view kOverriddenCookie = "overridden-cookie-name";
  CreateAndStartBackends(2);
  RouteConfiguration route_config = default_route_config_;
  *route_config.mutable_virtual_hosts(0)->mutable_routes(0) =
      BuildStatefulSessionRouteConfig("/grpc.testing.EchoTestService/Echo1",
                                      "");
  *route_config.mutable_virtual_hosts(0)->add_routes() =
      BuildStatefulSessionRouteConfig("/grpc.testing.EchoTestService/Echo2",
                                      kOverriddenCookie);
  *route_config.mutable_virtual_hosts(0)->add_routes() =
      default_route_config_.virtual_hosts(0).routes(0);
  SetListenerAndRouteConfiguration(
      balancer_.get(), BuildListenerWithStatefulSessionFilter(), route_config);
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(EdsResourceArgs(
      {{"locality0", {CreateEndpoint(0), CreateEndpoint(1)}}})));
  WaitForAllBackends(DEBUG_LOCATION);

  auto echo1_cookie = GetCookiesForBackend(
      DEBUG_LOCATION, 0, 1, RpcOptions().set_rpc_method(METHOD_ECHO1));
  ASSERT_EQ(CookieNames(echo1_cookie), "");

  auto echo2_cookie = GetCookiesForBackend(
      DEBUG_LOCATION, 0, 1, RpcOptions().set_rpc_method(METHOD_ECHO2));
  ASSERT_EQ(CookieNames(echo2_cookie), kOverriddenCookie);

  auto echo_cookie = GetCookiesForBackend(
      DEBUG_LOCATION, 0, 1, RpcOptions().set_rpc_method(METHOD_ECHO));
  ASSERT_EQ(CookieNames(echo_cookie), kCookieName);

  CheckRpcSendOk(DEBUG_LOCATION, 6,
                 RpcOptions()
                     .set_metadata({
                         echo_cookie.front().Header(),
                         echo2_cookie.front().Header(),
                     })
                     .set_rpc_method(METHOD_ECHO1));
  EXPECT_EQ(backends_[0]->backend_service()->request_count(), 3);
  EXPECT_EQ(backends_[1]->backend_service()->request_count(), 3);

  backends_[0]->backend_service()->ResetCounters();
  backends_[1]->backend_service()->ResetCounters();
  CheckRpcSendOk(DEBUG_LOCATION, 6,
                 RpcOptions()
                     .set_metadata({echo_cookie.front().Header()})
                     .set_rpc_method(METHOD_ECHO2));
  EXPECT_EQ(backends_[0]->backend_service()->request_count(), 3);
  EXPECT_EQ(backends_[1]->backend_service()->request_count(), 3);
  backends_[0]->backend_service()->ResetCounters();
  CheckRpcSendOk(DEBUG_LOCATION, 6,
                 RpcOptions()
                     .set_metadata({echo2_cookie.front().Header()})
                     .set_rpc_method(METHOD_ECHO2));
  EXPECT_EQ(backends_[0]->backend_service()->request_count(), 6);

  backends_[0]->backend_service()->ResetCounters();
  CheckRpcSendOk(DEBUG_LOCATION, 6,
                 RpcOptions()
                     .set_metadata({echo_cookie.front().Header()})
                     .set_rpc_method(METHOD_ECHO));
  EXPECT_EQ(backends_[0]->backend_service()->request_count(), 6);
  backends_[0]->backend_service()->ResetCounters();
  backends_[1]->backend_service()->ResetCounters();
  CheckRpcSendOk(DEBUG_LOCATION, 6,
                 RpcOptions()
                     .set_metadata({echo2_cookie.front().Header()})
                     .set_rpc_method(METHOD_ECHO));
  EXPECT_EQ(backends_[0]->backend_service()->request_count(), 3);
  EXPECT_EQ(backends_[1]->backend_service()->request_count(), 3);
}

TEST_P(OverrideHostTest, TTLSetsMaxAge) {
  CreateAndStartBackends(1);
  RouteConfiguration route_config = default_route_config_;
  *route_config.mutable_virtual_hosts(0)->mutable_routes(0) =
      BuildStatefulSessionRouteConfig("", kCookieName,
                                      grpc_core::Duration::Seconds(42));
  SetListenerAndRouteConfiguration(balancer_.get(),
                                   BuildListenerWithStatefulSessionFilter(""),
                                   route_config);
  balancer_->ads_service()->SetEdsResource(
      BuildEdsResource(EdsResourceArgs({{"locality0", {CreateEndpoint(0)}}})));
  WaitForAllBackends(DEBUG_LOCATION);

  auto cookies = GetCookiesForBackend(DEBUG_LOCATION, 0);
  ASSERT_EQ(cookies.size(), 1);
  EXPECT_THAT(cookies.front().attributes,
              ::testing::UnorderedElementsAre("Max-Age=42", "HttpOnly"));
}

TEST_P(OverrideHostTest, MultipleAddressesPerEndpoint) {

  CreateBackends(3);
  StartBackend(1);
  StartBackend(2);
  SetListenerAndRouteConfiguration(balancer_.get(),
                                   BuildListenerWithStatefulSessionFilter(),
                                   default_route_config_);
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(
      EdsResourceArgs({{"locality0",
                        {CreateEndpoint(0, HealthStatus::HEALTHY, 1, {1}),
                         CreateEndpoint(2, HealthStatus::UNKNOWN)}}})));
  WaitForAllBackends(DEBUG_LOCATION, 1);

  CheckRpcSendOk(DEBUG_LOCATION, 10);
  EXPECT_EQ(backends_[0]->backend_service()->request_count(), 0);
  EXPECT_EQ(backends_[1]->backend_service()->request_count(), 5);
  EXPECT_EQ(backends_[2]->backend_service()->request_count(), 5);
  ResetBackendCounters();

  auto cookies = GetCookiesForBackend(DEBUG_LOCATION, 1);
  ASSERT_THAT(cookies,
              ::testing::ElementsAre(::testing::AllOf(
                  ::testing::Field("name", &Cookie::name, kCookieName),
                  ::testing::Field("attributes", &Cookie::attributes,
                                   ::testing::ElementsAre("HttpOnly")),
                  ::testing::Field("value", &Cookie::value,
                                   ::testing::Not(::testing::IsEmpty())))));

  CheckRpcSendOk(DEBUG_LOCATION, 5,
                 RpcOptions().set_metadata({cookies.front().Header()}));
  EXPECT_EQ(backends_[1]->backend_service()->request_count(), 5);

  StartBackend(0);
  ShutdownBackend(1);

  WaitForBackend(DEBUG_LOCATION, 0);

  CheckRpcSendOk(DEBUG_LOCATION, 10);
  EXPECT_EQ(backends_[0]->backend_service()->request_count(), 5);
  EXPECT_EQ(backends_[1]->backend_service()->request_count(), 0);
  EXPECT_EQ(backends_[2]->backend_service()->request_count(), 5);
  ResetBackendCounters();

  CheckRpcSendOk(DEBUG_LOCATION, 5,
                 RpcOptions().set_metadata({cookies.front().Header()}));
  EXPECT_EQ(backends_[0]->backend_service()->request_count(), 5);
}

class OverrideHostLoadReportingTest : public OverrideHostTest {
 protected:
  std::string ConstructCookieValueForEndpoint(size_t idx) const {
    return absl::Base64Escape(absl::StrCat("127.0.0.1:", backends_[idx]->port(),
                                           ";", kDefaultClusterName));
  }
};

INSTANTIATE_TEST_SUITE_P(
    XdsTest, OverrideHostLoadReportingTest,
    ::testing::Values(XdsTestType().set_enable_load_reporting()),
    &XdsTestType::Name);

TEST_P(OverrideHostLoadReportingTest, SubchannelNotYetCreated) {
  CreateAndStartBackends(3);
  SetListenerAndRouteConfiguration(balancer_.get(),
                                   BuildListenerWithStatefulSessionFilter(),
                                   default_route_config_);

  balancer_->ads_service()->SetEdsResource(BuildEdsResource(
      EdsResourceArgs({{"locality0", CreateEndpointsForBackends(0, 2)},
                       {"locality1", CreateEndpointsForBackends(2, 3),
                        kDefaultLocalityWeight, 1}})));
  WaitForAllBackends(DEBUG_LOCATION, 0, 2);

  Cookie cookie{std::string(kCookieName), ConstructCookieValueForEndpoint(2)};
  CheckRpcSendOk(DEBUG_LOCATION, 5,
                 RpcOptions().set_metadata({cookie.Header()}));
  EXPECT_EQ(backends_[2]->backend_service()->request_count(), 5);

  balancer_->lrs_service()->WaitForLoadReport();
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
