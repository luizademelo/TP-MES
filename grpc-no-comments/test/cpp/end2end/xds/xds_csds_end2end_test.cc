// Copyright 2017 gRPC authors.

#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>

#include <memory>
#include <string>
#include <vector>

#include "absl/log/log.h"
#include "absl/memory/memory.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/strip.h"
#include "envoy/config/cluster/v3/cluster.pb.h"
#include "envoy/config/endpoint/v3/endpoint.pb.h"
#include "envoy/config/listener/v3/listener.pb.h"
#include "envoy/config/route/v3/route.pb.h"
#include "envoy/extensions/filters/network/http_connection_manager/v3/http_connection_manager.pb.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "src/core/client_channel/backup_poller.h"
#include "src/core/config/config_vars.h"
#include "test/core/test_util/resolve_localhost_ip46.h"
#include "test/core/test_util/test_config.h"
#include "test/cpp/end2end/xds/xds_end2end_test_lib.h"
#include "test/cpp/util/credentials.h"

#ifndef DISABLED_XDS_PROTO_IN_CC

#include "src/cpp/server/csds/csds.h"
#include "src/proto/grpc/testing/xds/v3/csds.grpc.pb.h"

namespace grpc {
namespace testing {
namespace {

using ::envoy::admin::v3::ClientResourceStatus;
using ::envoy::config::cluster::v3::Cluster;
using ::envoy::config::endpoint::v3::ClusterLoadAssignment;
using ::envoy::config::listener::v3::Listener;
using ::envoy::config::route::v3::RouteConfiguration;
using ::envoy::extensions::filters::network::http_connection_manager::v3::
    HttpConnectionManager;

MATCHER_P4(EqNode, id, user_agent_name, user_agent_version, client_features,
           "equals Node") {
  bool ok = true;
  ok &= ::testing::ExplainMatchResult(id, arg.id(), result_listener);
  ok &= ::testing::ExplainMatchResult(user_agent_name, arg.user_agent_name(),
                                      result_listener);
  ok &= ::testing::ExplainMatchResult(
      user_agent_version, arg.user_agent_version(), result_listener);
  ok &= ::testing::ExplainMatchResult(client_features, arg.client_features(),
                                      result_listener);
  return ok;
}

MATCHER_P6(EqGenericXdsConfig, type_url, name, version_info, xds_config,
           client_status, error_state, "equals GenericXdsConfig") {
  bool ok = true;
  ok &=
      ::testing::ExplainMatchResult(type_url, arg.type_url(), result_listener);
  ok &= ::testing::ExplainMatchResult(name, arg.name(), result_listener);
  ok &= ::testing::ExplainMatchResult(version_info, arg.version_info(),
                                      result_listener);
  ok &= ::testing::ExplainMatchResult(xds_config, arg.xds_config(),
                                      result_listener);
  ok &= ::testing::ExplainMatchResult(client_status, arg.client_status(),
                                      result_listener);
  ok &= ::testing::ExplainMatchResult(error_state, arg.error_state(),
                                      result_listener);
  return ok;
}

MATCHER_P2(EqListener, name, api_listener, "equals Listener") {
  bool ok = true;
  ok &= ::testing::ExplainMatchResult(name, arg.name(), result_listener);
  ok &= ::testing::ExplainMatchResult(
      api_listener, arg.api_listener().api_listener(), result_listener);
  return ok;
}

MATCHER_P(EqHttpConnectionManagerNotRds, route_config,
          "equals HttpConnectionManager") {
  bool ok = true;
  ok &= ::testing::ExplainMatchResult(route_config, arg.route_config(),
                                      result_listener);
  return ok;
}

MATCHER_P(EqRouteConfigurationName, name, "equals RouteConfiguration") {
  bool ok = true;
  ok &= ::testing::ExplainMatchResult(name, arg.name(), result_listener);
  return ok;
}

MATCHER_P2(EqRouteConfiguration, name, cluster_name,
           "equals RouteConfiguration") {
  bool ok = true;
  ok &= ::testing::ExplainMatchResult(name, arg.name(), result_listener);
  ok &= ::testing::ExplainMatchResult(
      ::testing::ElementsAre(::testing::Property(
          &envoy::config::route::v3::VirtualHost::routes,
          ::testing::ElementsAre(::testing::Property(
              &envoy::config::route::v3::Route::route,
              ::testing::Property(
                  &envoy::config::route::v3::RouteAction::cluster,
                  cluster_name))))),
      arg.virtual_hosts(), result_listener);
  return ok;
}

MATCHER_P(EqCluster, name, "equals Cluster") {
  bool ok = true;
  ok &= ::testing::ExplainMatchResult(name, arg.name(), result_listener);
  return ok;
}

MATCHER_P(EqEndpoint, port, "equals Endpoint") {
  bool ok = true;
  ok &= ::testing::ExplainMatchResult(
      port, arg.address().socket_address().port_value(), result_listener);
  return ok;
}

MATCHER_P2(EqLocalityLbEndpoints, port, weight, "equals LocalityLbEndpoints") {
  bool ok = true;
  ok &= ::testing::ExplainMatchResult(
      ::testing::ElementsAre(::testing::Property(
          &envoy::config::endpoint::v3::LbEndpoint::endpoint,
          EqEndpoint(port))),
      arg.lb_endpoints(), result_listener);
  ok &= ::testing::ExplainMatchResult(
      weight, arg.load_balancing_weight().value(), result_listener);
  return ok;
}

MATCHER_P(EqClusterLoadAssignmentName, cluster_name,
          "equals ClusterLoadAssignment") {
  bool ok = true;
  ok &= ::testing::ExplainMatchResult(cluster_name, arg.cluster_name(),
                                      result_listener);
  return ok;
}

MATCHER_P3(EqClusterLoadAssignment, cluster_name, port, weight,
           "equals ClusterLoadAssignment") {
  bool ok = true;
  ok &= ::testing::ExplainMatchResult(cluster_name, arg.cluster_name(),
                                      result_listener);
  ok &= ::testing::ExplainMatchResult(
      ::testing::ElementsAre(EqLocalityLbEndpoints(port, weight)),
      arg.endpoints(), result_listener);
  return ok;
}

MATCHER_P2(EqUpdateFailureState, details, version_info,
           "equals UpdateFailureState") {
  bool ok = true;
  ok &= ::testing::ExplainMatchResult(details, arg.details(), result_listener);
  ok &= ::testing::ExplainMatchResult(version_info, arg.version_info(),
                                      result_listener);
  return ok;
}

MATCHER_P(UnpackListener, matcher, "is a Listener") {
  Listener config;
  if (!::testing::ExplainMatchResult(true, arg.UnpackTo(&config),
                                     result_listener)) {
    return false;
  }
  return ::testing::ExplainMatchResult(matcher, config, result_listener);
}

MATCHER_P(UnpackRouteConfiguration, matcher, "is a RouteConfiguration") {
  RouteConfiguration config;
  if (!::testing::ExplainMatchResult(true, arg.UnpackTo(&config),
                                     result_listener)) {
    return false;
  }
  return ::testing::ExplainMatchResult(matcher, config, result_listener);
}

MATCHER_P(UnpackHttpConnectionManager, matcher, "is a HttpConnectionManager") {
  HttpConnectionManager config;
  if (!::testing::ExplainMatchResult(true, arg.UnpackTo(&config),
                                     result_listener)) {
    return false;
  }
  return ::testing::ExplainMatchResult(matcher, config, result_listener);
}

MATCHER_P(UnpackCluster, matcher, "is a Cluster") {
  Cluster config;
  if (!::testing::ExplainMatchResult(true, arg.UnpackTo(&config),
                                     result_listener)) {
    return false;
  }
  return ::testing::ExplainMatchResult(matcher, config, result_listener);
}

MATCHER_P(UnpackClusterLoadAssignment, matcher, "is a ClusterLoadAssignment") {
  ClusterLoadAssignment config;
  if (!::testing::ExplainMatchResult(true, arg.UnpackTo(&config),
                                     result_listener)) {
    return false;
  }
  return ::testing::ExplainMatchResult(matcher, config, result_listener);
}

MATCHER(IsRdsEnabledHCM, "is a RDS enabled HttpConnectionManager") {
  return ::testing::ExplainMatchResult(
      UnpackHttpConnectionManager(
          ::testing::Property(&HttpConnectionManager::has_rds, true)),
      arg, result_listener);
}

MATCHER_P2(EqNoRdsHCM, route_configuration_name, cluster_name,
           "equals RDS disabled HttpConnectionManager") {
  return ::testing::ExplainMatchResult(
      UnpackHttpConnectionManager(EqHttpConnectionManagerNotRds(
          EqRouteConfiguration(route_configuration_name, cluster_name))),
      arg, result_listener);
}

class ClientStatusDiscoveryServiceTest : public XdsEnd2endTest {
 public:
  ClientStatusDiscoveryServiceTest() {
    admin_server_thread_ = std::make_unique<AdminServerThread>(this);
    admin_server_thread_->Start();
    std::string admin_server_address =
        grpc_core::LocalIpAndPort(admin_server_thread_->port());
    admin_channel_ = grpc::CreateChannel(
        admin_server_address,
        std::make_shared<FakeTransportSecurityChannelCredentials>());
    csds_stub_ =
        envoy::service::status::v3::ClientStatusDiscoveryService::NewStub(
            admin_channel_);
    if (GetParam().use_csds_streaming()) {
      stream_ = csds_stub_->StreamClientStatus(&stream_context_);
    }
  }

  ~ClientStatusDiscoveryServiceTest() override {
    if (stream_ != nullptr) {
      EXPECT_TRUE(stream_->WritesDone());
      Status status = stream_->Finish();
      EXPECT_TRUE(status.ok()) << "code=" << status.error_code()
                               << " message=" << status.error_message();
    }
    admin_server_thread_->Shutdown();
  }

  envoy::service::status::v3::ClientStatusResponse FetchCsdsResponse() {
    envoy::service::status::v3::ClientStatusResponse response;
    if (!GetParam().use_csds_streaming()) {

      ClientContext context;
      Status status = csds_stub_->FetchClientStatus(
          &context, envoy::service::status::v3::ClientStatusRequest(),
          &response);
      EXPECT_TRUE(status.ok()) << "code=" << status.error_code()
                               << " message=" << status.error_message();
    } else {

      EXPECT_TRUE(
          stream_->Write(envoy::service::status::v3::ClientStatusRequest()));
      EXPECT_TRUE(stream_->Read(&response));
    }
    return response;
  }

 private:

  class AdminServerThread : public ServerThread {
   public:
    explicit AdminServerThread(XdsEnd2endTest* test_obj)
        : ServerThread(test_obj) {}

   private:
    const char* Type() override { return "Admin"; }

    void RegisterAllServices(ServerBuilder* builder) override {
      builder->RegisterService(&csds_service_);
    }
    void StartAllServices() override {}
    void ShutdownAllServices() override {}

    grpc::xds::experimental::ClientStatusDiscoveryService csds_service_;
  };

  std::unique_ptr<AdminServerThread> admin_server_thread_;
  std::shared_ptr<Channel> admin_channel_;
  std::unique_ptr<
      envoy::service::status::v3::ClientStatusDiscoveryService::Stub>
      csds_stub_;
  ClientContext stream_context_;
  std::unique_ptr<
      ClientReaderWriter<envoy::service::status::v3::ClientStatusRequest,
                         envoy::service::status::v3::ClientStatusResponse>>
      stream_;
};

INSTANTIATE_TEST_SUITE_P(
    XdsTest, ClientStatusDiscoveryServiceTest,
    ::testing::Values(
        XdsTestType().set_bootstrap_source(XdsTestType::kBootstrapFromEnvVar),
        XdsTestType()
            .set_bootstrap_source(XdsTestType::kBootstrapFromEnvVar)
            .set_enable_rds_testing(),
        XdsTestType()
            .set_bootstrap_source(XdsTestType::kBootstrapFromEnvVar)
            .set_use_csds_streaming(),
        XdsTestType()
            .set_bootstrap_source(XdsTestType::kBootstrapFromEnvVar)
            .set_enable_rds_testing()
            .set_use_csds_streaming()),
    &XdsTestType::Name);

TEST_P(ClientStatusDiscoveryServiceTest, XdsConfigDumpVanilla) {
  CreateAndStartBackends(1);
  const size_t kNumRpcs = 5;
  EdsResourceArgs args({{"locality0", CreateEndpointsForBackends(0, 1)}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  CheckRpcSendOk(DEBUG_LOCATION, kNumRpcs);

  auto csds_response = FetchCsdsResponse();
  LOG(INFO) << "xDS config dump: " << csds_response.DebugString();
  ASSERT_EQ(1, csds_response.config_size());
  const auto& client_config = csds_response.config(0);

  EXPECT_THAT(client_config.node(),
              EqNode("xds_end2end_test", ::testing::HasSubstr("C-core"),
                     ::testing::HasSubstr(grpc_version_string()),
                     ::testing::ElementsAre(
                         "envoy.lb.does_not_support_overprovisioning")));

  ::testing::Matcher<google::protobuf::Any> api_listener_matcher;
  if (GetParam().enable_rds_testing()) {
    api_listener_matcher = IsRdsEnabledHCM();
  } else {
    api_listener_matcher =
        EqNoRdsHCM(kDefaultRouteConfigurationName, kDefaultClusterName);
  }

  std::vector<::testing::Matcher<
      envoy::service::status::v3::ClientConfig_GenericXdsConfig>>
      matchers = {

          EqGenericXdsConfig(
              kLdsTypeUrl, kServerName, "1",
              UnpackListener(EqListener(kServerName, api_listener_matcher)),
              ClientResourceStatus::ACKED, ::testing::_),

          EqGenericXdsConfig(kCdsTypeUrl, kDefaultClusterName, "1",
                             UnpackCluster(EqCluster(kDefaultClusterName)),
                             ClientResourceStatus::ACKED, ::testing::_),

          EqGenericXdsConfig(
              kEdsTypeUrl, kDefaultEdsServiceName, "1",
              UnpackClusterLoadAssignment(EqClusterLoadAssignment(
                  kDefaultEdsServiceName, backends_[0]->port(),
                  kDefaultLocalityWeight)),
              ClientResourceStatus::ACKED, ::testing::_),
      };

  if (GetParam().enable_rds_testing()) {
    matchers.push_back(EqGenericXdsConfig(
        kRdsTypeUrl, kDefaultRouteConfigurationName, "1",
        UnpackRouteConfiguration(EqRouteConfiguration(
            kDefaultRouteConfigurationName, kDefaultClusterName)),
        ClientResourceStatus::ACKED, ::testing::_));
  }

  EXPECT_THAT(client_config.generic_xds_configs(),
              ::testing::UnorderedElementsAreArray(matchers))
      << "Actual: " << client_config.DebugString();
}

TEST_P(ClientStatusDiscoveryServiceTest, XdsConfigDumpEmpty) {

  FetchCsdsResponse();
}

TEST_P(ClientStatusDiscoveryServiceTest, XdsConfigDumpListenerError) {
  CreateAndStartBackends(1);
  int kFetchConfigRetries = 3;
  int kFetchIntervalMilliseconds = 200;
  EdsResourceArgs args({{"locality0", CreateEndpointsForBackends(0, 1)}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  CheckRpcSendOk(DEBUG_LOCATION);

  Listener listener;
  listener.set_name(kServerName);
  balancer_->ads_service()->SetLdsResource(listener);

  CheckRpcSendOk(DEBUG_LOCATION);
  ::testing::Matcher<google::protobuf::Any> api_listener_matcher;
  if (GetParam().enable_rds_testing()) {
    api_listener_matcher = IsRdsEnabledHCM();
  } else {
    api_listener_matcher =
        EqNoRdsHCM(kDefaultRouteConfigurationName, kDefaultClusterName);
  }
  for (int i = 0; i < kFetchConfigRetries; ++i) {
    auto csds_response = FetchCsdsResponse();

    bool ok = ::testing::Value(
        csds_response.config(0).generic_xds_configs(),
        ::testing::Contains(EqGenericXdsConfig(
            kLdsTypeUrl, kServerName, "1",
            UnpackListener(EqListener(kServerName, api_listener_matcher)),
            ClientResourceStatus::NACKED,
            EqUpdateFailureState(
                ::testing::HasSubstr(
                    "Listener has neither address nor ApiListener"),
                "2"))));
    if (ok) return;
    gpr_sleep_until(
        grpc_timeout_milliseconds_to_deadline(kFetchIntervalMilliseconds));
  }
  FAIL() << "error_state not seen in CSDS responses";
}

TEST_P(ClientStatusDiscoveryServiceTest, XdsConfigDumpRouteError) {
  CreateAndStartBackends(1);
  int kFetchConfigRetries = 3;
  int kFetchIntervalMilliseconds = 200;
  EdsResourceArgs args({{"locality0", CreateEndpointsForBackends(0, 1)}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  CheckRpcSendOk(DEBUG_LOCATION);

  RouteConfiguration route_config;
  route_config.set_name(kDefaultRouteConfigurationName);
  route_config.add_virtual_hosts();
  SetRouteConfiguration(balancer_.get(), route_config);

  CheckRpcSendOk(DEBUG_LOCATION);
  for (int i = 0; i < kFetchConfigRetries; ++i) {
    auto csds_response = FetchCsdsResponse();
    bool ok = false;
    if (GetParam().enable_rds_testing()) {
      ok = ::testing::Value(
          csds_response.config(0).generic_xds_configs(),
          ::testing::Contains(EqGenericXdsConfig(
              kRdsTypeUrl, kDefaultRouteConfigurationName, "1",
              UnpackRouteConfiguration(EqRouteConfiguration(
                  kDefaultRouteConfigurationName, kDefaultClusterName)),
              ClientResourceStatus::NACKED,
              EqUpdateFailureState(
                  ::testing::HasSubstr(
                      "field:virtual_hosts[0].domains error:must be non-empty"),
                  "2"))));
    } else {
      ok = ::testing::Value(
          csds_response.config(0).generic_xds_configs(),
          ::testing::Contains(EqGenericXdsConfig(
              kLdsTypeUrl, kServerName, "1",
              UnpackListener(EqListener(
                  kServerName, EqNoRdsHCM(kDefaultRouteConfigurationName,
                                          kDefaultClusterName))),
              ClientResourceStatus::NACKED,
              EqUpdateFailureState(
                  ::testing::HasSubstr(
                      "field:api_listener.api_listener.value[envoy.extensions"
                      ".filters.network.http_connection_manager.v3"
                      ".HttpConnectionManager].route_config.virtual_hosts[0]"
                      ".domains error:must be non-empty"),
                  "2"))));
    }
    if (ok) return;
    gpr_sleep_until(
        grpc_timeout_milliseconds_to_deadline(kFetchIntervalMilliseconds));
  }
  FAIL() << "error_state not seen in CSDS responses";
}

TEST_P(ClientStatusDiscoveryServiceTest, XdsConfigDumpClusterError) {
  CreateAndStartBackends(1);
  int kFetchConfigRetries = 3;
  int kFetchIntervalMilliseconds = 200;
  EdsResourceArgs args({{"locality0", CreateEndpointsForBackends(0, 1)}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  CheckRpcSendOk(DEBUG_LOCATION);

  Cluster cluster;
  cluster.set_name(kDefaultClusterName);
  balancer_->ads_service()->SetCdsResource(cluster);

  CheckRpcSendOk(DEBUG_LOCATION);
  for (int i = 0; i < kFetchConfigRetries; ++i) {
    auto csds_response = FetchCsdsResponse();

    bool ok = ::testing::Value(
        csds_response.config(0).generic_xds_configs(),
        ::testing::Contains(EqGenericXdsConfig(
            kCdsTypeUrl, kDefaultClusterName, "1",
            UnpackCluster(EqCluster(kDefaultClusterName)),
            ClientResourceStatus::NACKED,
            EqUpdateFailureState(::testing::HasSubstr("unknown discovery type"),
                                 "2"))));
    if (ok) return;
    gpr_sleep_until(
        grpc_timeout_milliseconds_to_deadline(kFetchIntervalMilliseconds));
  }
  FAIL() << "error_state not seen in CSDS responses";
}

TEST_P(ClientStatusDiscoveryServiceTest, XdsConfigDumpEndpointError) {
  CreateAndStartBackends(1);
  int kFetchConfigRetries = 3;
  int kFetchIntervalMilliseconds = 200;
  EdsResourceArgs args({{"locality0", CreateEndpointsForBackends(0, 1)}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  CheckRpcSendOk(DEBUG_LOCATION);

  ClusterLoadAssignment cluster_load_assignment;
  cluster_load_assignment.set_cluster_name(kDefaultEdsServiceName);
  auto* endpoints = cluster_load_assignment.add_endpoints();
  endpoints->mutable_load_balancing_weight()->set_value(1);
  auto* endpoint = endpoints->add_lb_endpoints()->mutable_endpoint();
  endpoint->mutable_address()->mutable_socket_address()->set_port_value(1 << 1);
  balancer_->ads_service()->SetEdsResource(cluster_load_assignment);

  CheckRpcSendOk(DEBUG_LOCATION);
  for (int i = 0; i < kFetchConfigRetries; ++i) {
    auto csds_response = FetchCsdsResponse();

    bool ok = ::testing::Value(
        csds_response.config(0).generic_xds_configs(),
        ::testing::Contains(EqGenericXdsConfig(
            kEdsTypeUrl, kDefaultEdsServiceName, "1",
            UnpackClusterLoadAssignment(EqClusterLoadAssignment(
                kDefaultEdsServiceName, backends_[0]->port(),
                kDefaultLocalityWeight)),
            ClientResourceStatus::NACKED,
            EqUpdateFailureState(
                ::testing::HasSubstr(
                    "errors parsing EDS resource: ["
                    "field:endpoints[0].locality error:field not present]"),
                "2"))));
    if (ok) return;
    gpr_sleep_until(
        grpc_timeout_milliseconds_to_deadline(kFetchIntervalMilliseconds));
  }
  FAIL() << "error_state not seen in CSDS responses";
}

TEST_P(ClientStatusDiscoveryServiceTest, XdsConfigDumpListenerRequested) {
  int kTimeoutMillisecond = 1000;
  balancer_->ads_service()->UnsetResource(kLdsTypeUrl, kServerName);
  CheckRpcSendFailure(DEBUG_LOCATION, StatusCode::DEADLINE_EXCEEDED,
                      "Deadline Exceeded",
                      RpcOptions().set_timeout_ms(kTimeoutMillisecond));
  auto csds_response = FetchCsdsResponse();
  EXPECT_THAT(csds_response.config(0).generic_xds_configs(),
              ::testing::Contains(EqGenericXdsConfig(
                  kLdsTypeUrl, kServerName, ::testing::_, ::testing::_,
                  ClientResourceStatus::REQUESTED, ::testing::_)));
}

TEST_P(ClientStatusDiscoveryServiceTest, XdsConfigDumpClusterRequested) {
  int kTimeoutMillisecond = 1000;
  std::string kClusterName1 = "cluster-1";
  std::string kClusterName2 = "cluster-2";

  RouteConfiguration route_config;
  route_config.set_name(kDefaultRouteConfigurationName);
  auto* vh = route_config.add_virtual_hosts();

  vh->add_domains("*");
  auto* routes1 = vh->add_routes();
  routes1->mutable_match()->set_prefix("");
  routes1->mutable_route()->set_cluster(kClusterName1);
  auto* routes2 = vh->add_routes();
  routes2->mutable_match()->set_prefix("");
  routes2->mutable_route()->set_cluster(kClusterName2);
  SetRouteConfiguration(balancer_.get(), route_config);

  CheckRpcSendFailure(DEBUG_LOCATION, StatusCode::DEADLINE_EXCEEDED,
                      "Deadline Exceeded",
                      RpcOptions().set_timeout_ms(kTimeoutMillisecond));
  auto csds_response = FetchCsdsResponse();
  EXPECT_THAT(csds_response.config(0).generic_xds_configs(),
              ::testing::AllOf(
                  ::testing::Contains(EqGenericXdsConfig(
                      kCdsTypeUrl, kClusterName1, ::testing::_, ::testing::_,
                      ClientResourceStatus::REQUESTED, ::testing::_)),
                  ::testing::Contains(EqGenericXdsConfig(
                      kCdsTypeUrl, kClusterName2, ::testing::_, ::testing::_,
                      ClientResourceStatus::REQUESTED, ::testing::_))));
}

TEST_P(ClientStatusDiscoveryServiceTest, XdsConfigDumpMultiClient) {
  Listener listener = default_listener_;
  const char* kServer2Name = "server2.example.com";
  listener.set_name(kServer2Name);
  balancer_->ads_service()->SetLdsResource(listener);
  SetListenerAndRouteConfiguration(balancer_.get(), listener,
                                   default_route_config_);
  CreateAndStartBackends(1);
  const size_t kNumRpcs = 5;
  EdsResourceArgs args({{"locality0", CreateEndpointsForBackends(0, 1)}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  CheckRpcSendOk(DEBUG_LOCATION, kNumRpcs);

  auto channel2 = CreateChannel(0, kServer2Name);
  channel2->GetState(true);
  ASSERT_TRUE(channel2->WaitForConnected(grpc_timeout_seconds_to_deadline(1)));

  auto csds_response = FetchCsdsResponse();
  ASSERT_EQ(2, csds_response.config_size());
  std::vector<std::string> scopes;
  for (const auto& client_config : csds_response.config()) {

    EXPECT_THAT(client_config.node(),
                EqNode("xds_end2end_test", ::testing::HasSubstr("C-core"),
                       ::testing::HasSubstr(grpc_version_string()),
                       ::testing::ElementsAre(
                           "envoy.lb.does_not_support_overprovisioning")));
    scopes.emplace_back(client_config.client_scope());
    absl::string_view server = client_config.client_scope();

    ::testing::Matcher<google::protobuf::Any> api_listener_matcher;
    if (GetParam().enable_rds_testing()) {
      api_listener_matcher = IsRdsEnabledHCM();
    } else {
      api_listener_matcher =
          EqNoRdsHCM(kDefaultRouteConfigurationName, kDefaultClusterName);
    }

    std::vector<::testing::Matcher<
        envoy::service::status::v3::ClientConfig_GenericXdsConfig>>
        matchers = {

            EqGenericXdsConfig(
                kLdsTypeUrl, absl::StripPrefix(server, "xds:"), "3",
                UnpackListener(EqListener(absl::StripPrefix(server, "xds:"),
                                          api_listener_matcher)),
                ClientResourceStatus::ACKED, ::testing::_),

            EqGenericXdsConfig(kCdsTypeUrl, kDefaultClusterName, "1",
                               UnpackCluster(EqCluster(kDefaultClusterName)),
                               ClientResourceStatus::ACKED, ::testing::_),

            EqGenericXdsConfig(
                kEdsTypeUrl, kDefaultEdsServiceName, "1",
                UnpackClusterLoadAssignment(EqClusterLoadAssignment(
                    kDefaultEdsServiceName, backends_[0]->port(),
                    kDefaultLocalityWeight)),
                ClientResourceStatus::ACKED, ::testing::_),
        };

    if (GetParam().enable_rds_testing()) {
      matchers.push_back(EqGenericXdsConfig(
          kRdsTypeUrl, kDefaultRouteConfigurationName, "2",
          UnpackRouteConfiguration(EqRouteConfiguration(
              kDefaultRouteConfigurationName, kDefaultClusterName)),
          ClientResourceStatus::ACKED, ::testing::_));
    }

    EXPECT_THAT(client_config.generic_xds_configs(),
                ::testing::UnorderedElementsAreArray(matchers));
  }
  EXPECT_THAT(scopes, ::testing::UnorderedElementsAre(
                          "xds:server.example.com", "xds:server2.example.com"));
}

class CsdsShortAdsTimeoutTest : public ClientStatusDiscoveryServiceTest {
 protected:
  void SetUp() override {

    InitClient(std::nullopt, "",
               2000);
  }
};

INSTANTIATE_TEST_SUITE_P(
    XdsTest, CsdsShortAdsTimeoutTest,
    ::testing::Values(
        XdsTestType().set_bootstrap_source(XdsTestType::kBootstrapFromEnvVar),
        XdsTestType()
            .set_bootstrap_source(XdsTestType::kBootstrapFromEnvVar)
            .set_enable_rds_testing(),
        XdsTestType()
            .set_bootstrap_source(XdsTestType::kBootstrapFromEnvVar)
            .set_use_csds_streaming(),
        XdsTestType()
            .set_bootstrap_source(XdsTestType::kBootstrapFromEnvVar)
            .set_enable_rds_testing()
            .set_use_csds_streaming()),
    &XdsTestType::Name);

TEST_P(CsdsShortAdsTimeoutTest, XdsConfigDumpListenerDoesNotExist) {
  int kTimeoutMillisecond = 1000000;
  balancer_->ads_service()->UnsetResource(kLdsTypeUrl, kServerName);
  CheckRpcSendFailure(
      DEBUG_LOCATION, StatusCode::UNAVAILABLE,
      absl::StrCat("empty address list \\(LDS resource ", kServerName,
                   ": does not exist \\(node ID:xds_end2end_test\\)\\)"),
      RpcOptions().set_timeout_ms(kTimeoutMillisecond));
  auto csds_response = FetchCsdsResponse();
  EXPECT_THAT(csds_response.config(0).generic_xds_configs(),
              ::testing::Contains(EqGenericXdsConfig(
                  kLdsTypeUrl, kServerName, ::testing::_, ::testing::_,
                  ClientResourceStatus::DOES_NOT_EXIST, ::testing::_)));
}

TEST_P(CsdsShortAdsTimeoutTest, XdsConfigDumpRouteConfigDoesNotExist) {
  if (!GetParam().enable_rds_testing()) return;
  int kTimeoutMillisecond = 1000000;
  balancer_->ads_service()->UnsetResource(kRdsTypeUrl,
                                          kDefaultRouteConfigurationName);
  CheckRpcSendFailure(
      DEBUG_LOCATION, StatusCode::UNAVAILABLE,
      absl::StrCat("empty address list \\(RDS resource ",
                   kDefaultRouteConfigurationName,
                   ": does not exist \\(node ID:xds_end2end_test\\)\\)"),
      RpcOptions().set_timeout_ms(kTimeoutMillisecond));
  auto csds_response = FetchCsdsResponse();
  EXPECT_THAT(
      csds_response.config(0).generic_xds_configs(),
      ::testing::Contains(EqGenericXdsConfig(
          kRdsTypeUrl, kDefaultRouteConfigurationName, ::testing::_,
          ::testing::_, ClientResourceStatus::DOES_NOT_EXIST, ::testing::_)));
}

TEST_P(CsdsShortAdsTimeoutTest, XdsConfigDumpClusterDoesNotExist) {
  int kTimeoutMillisecond = 1000000;
  balancer_->ads_service()->UnsetResource(kCdsTypeUrl, kDefaultClusterName);
  CheckRpcSendFailure(
      DEBUG_LOCATION, StatusCode::UNAVAILABLE,
      absl::StrCat("CDS resource ", kDefaultClusterName,
                   ": does not exist \\(node ID:xds_end2end_test\\)"),
      RpcOptions().set_timeout_ms(kTimeoutMillisecond));
  auto csds_response = FetchCsdsResponse();
  EXPECT_THAT(csds_response.config(0).generic_xds_configs(),
              ::testing::Contains(EqGenericXdsConfig(
                  kCdsTypeUrl, kDefaultClusterName, ::testing::_, ::testing::_,
                  ClientResourceStatus::DOES_NOT_EXIST, ::testing::_)));
}

TEST_P(CsdsShortAdsTimeoutTest, XdsConfigDumpEndpointDoesNotExist) {
  int kTimeoutMillisecond = 1000000;
  balancer_->ads_service()->UnsetResource(kEdsTypeUrl, kDefaultEdsServiceName);
  CheckRpcSendFailure(
      DEBUG_LOCATION, StatusCode::UNAVAILABLE,
      "no children in weighted_target policy \\(EDS resource eds_service_name: "
      "does not exist \\(node ID:xds_end2end_test\\)\\)",
      RpcOptions().set_timeout_ms(kTimeoutMillisecond));
  auto csds_response = FetchCsdsResponse();
  EXPECT_THAT(
      csds_response.config(0).generic_xds_configs(),
      ::testing::Contains(EqGenericXdsConfig(
          kEdsTypeUrl, kDefaultEdsServiceName, ::testing::_, ::testing::_,
          ClientResourceStatus::DOES_NOT_EXIST, ::testing::_)));
}

}
}
}

#endif

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
