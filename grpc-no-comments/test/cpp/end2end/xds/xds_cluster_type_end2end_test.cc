// Copyright 2017 gRPC authors.

#include <grpc/event_engine/endpoint_config.h>

#include <vector>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/status/statusor.h"
#include "absl/strings/str_cat.h"
#include "envoy/extensions/clusters/aggregate/v3/cluster.pb.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "src/core/client_channel/backup_poller.h"
#include "src/core/config/config_vars.h"
#include "src/core/lib/address_utils/sockaddr_utils.h"
#include "src/core/load_balancing/xds/xds_channel_args.h"
#include "src/core/resolver/endpoint_addresses.h"
#include "src/core/resolver/fake/fake_resolver.h"
#include "src/core/util/env.h"
#include "test/core/test_util/resolve_localhost_ip46.h"
#include "test/core/test_util/scoped_env_var.h"
#include "test/cpp/end2end/connection_attempt_injector.h"
#include "test/cpp/end2end/xds/xds_end2end_test_lib.h"

namespace grpc {
namespace testing {
namespace {

using ::envoy::extensions::clusters::aggregate::v3::ClusterConfig;

class ClusterTypeTest : public XdsEnd2endTest {
 protected:
  ClusterTypeTest()
      : logical_dns_cluster_resolver_response_generator_(
            grpc_core::MakeRefCounted<
                grpc_core::FakeResolverResponseGenerator>()) {}

  void LogicalDnsInitClient(
      std::optional<XdsBootstrapBuilder> builder = std::nullopt,
      std::shared_ptr<ChannelCredentials> credentials = nullptr) {
    ChannelArguments args;
    args.SetPointerWithVtable(
        GRPC_ARG_XDS_LOGICAL_DNS_CLUSTER_FAKE_RESOLVER_RESPONSE_GENERATOR,
        logical_dns_cluster_resolver_response_generator_.get(),
        &grpc_core::FakeResolverResponseGenerator::kChannelArgPointerVtable);
    InitClient(builder, "",
               0,
               "", &args,
               std::move(credentials));
  }

  static grpc_core::EndpointAddressesList CreateAddressListFromPortList(
      const std::vector<int>& ports) {
    grpc_core::EndpointAddressesList addresses;
    for (int port : ports) {
      absl::StatusOr<grpc_core::URI> lb_uri =
          grpc_core::URI::Parse(grpc_core::LocalIpUri(port));
      CHECK_OK(lb_uri);
      grpc_resolved_address address;
      CHECK(grpc_parse_uri(*lb_uri, &address));
      addresses.emplace_back(address, grpc_core::ChannelArgs());
    }
    return addresses;
  }

  grpc_core::RefCountedPtr<grpc_core::FakeResolverResponseGenerator>
      logical_dns_cluster_resolver_response_generator_;
};

class LogicalDNSClusterTest : public ClusterTypeTest {
 protected:
  void SetUp() override {}
};

INSTANTIATE_TEST_SUITE_P(XdsTest, LogicalDNSClusterTest,
                         ::testing::Values(XdsTestType()), &XdsTestType::Name);

TEST_P(LogicalDNSClusterTest, Basic) {
  LogicalDnsInitClient();
  CreateAndStartBackends(1);

  auto cluster = default_cluster_;
  cluster.set_type(Cluster::LOGICAL_DNS);
  auto* address = cluster.mutable_load_assignment()
                      ->add_endpoints()
                      ->add_lb_endpoints()
                      ->mutable_endpoint()
                      ->mutable_address()
                      ->mutable_socket_address();
  address->set_address(kServerName);
  address->set_port_value(443);
  balancer_->ads_service()->SetCdsResource(cluster);

  {
    grpc_core::ExecCtx exec_ctx;
    grpc_core::Resolver::Result result;
    result.addresses = CreateAddressListFromPortList(GetBackendPorts());
    logical_dns_cluster_resolver_response_generator_->SetResponseSynchronously(
        std::move(result));
  }

  CheckRpcSendOk(DEBUG_LOCATION);
}

TEST_P(LogicalDNSClusterTest, FailedBackendConnectionCausesReresolution) {
  LogicalDnsInitClient();
  CreateAndStartBackends(2);

  auto cluster = default_cluster_;
  cluster.set_type(Cluster::LOGICAL_DNS);
  auto* address = cluster.mutable_load_assignment()
                      ->add_endpoints()
                      ->add_lb_endpoints()
                      ->mutable_endpoint()
                      ->mutable_address()
                      ->mutable_socket_address();
  address->set_address(kServerName);
  address->set_port_value(443);
  balancer_->ads_service()->SetCdsResource(cluster);

  {
    grpc_core::ExecCtx exec_ctx;
    grpc_core::Resolver::Result result;
    result.addresses = CreateAddressListFromPortList(GetBackendPorts(0, 1));
    logical_dns_cluster_resolver_response_generator_->SetResponseSynchronously(
        std::move(result));
  }

  CheckRpcSendOk(DEBUG_LOCATION);

  ShutdownBackend(0);

  {
    grpc_core::ExecCtx exec_ctx;
    ASSERT_TRUE(logical_dns_cluster_resolver_response_generator_
                    ->WaitForReresolutionRequest(absl::Seconds(10) *
                                                 grpc_test_slowdown_factor()));
    grpc_core::Resolver::Result result;
    result.addresses = CreateAddressListFromPortList(GetBackendPorts(1, 2));
    logical_dns_cluster_resolver_response_generator_->SetResponseSynchronously(
        std::move(result));
  }

  WaitForBackend(DEBUG_LOCATION, 1, [](const RpcResult& result) {
    if (!result.status.ok()) {
      EXPECT_EQ(StatusCode::UNAVAILABLE, result.status.error_code());
      EXPECT_THAT(result.status.error_message(),
                  ::testing::MatchesRegex(MakeConnectionFailureRegex(
                      "connections to all backends failing; last error: ")));
    }
  });
}

TEST_P(LogicalDNSClusterTest, AutoHostRewrite) {
  constexpr char kDnsName[] = "dns.example.com";

  RouteConfiguration new_route_config = default_route_config_;
  new_route_config.mutable_virtual_hosts(0)
      ->mutable_routes(0)
      ->mutable_route()
      ->mutable_auto_host_rewrite()
      ->set_value(true);
  SetRouteConfiguration(balancer_.get(), new_route_config);

  auto cluster = default_cluster_;
  cluster.set_type(Cluster::LOGICAL_DNS);
  auto* address = cluster.mutable_load_assignment()
                      ->add_endpoints()
                      ->add_lb_endpoints()
                      ->mutable_endpoint()
                      ->mutable_address()
                      ->mutable_socket_address();
  address->set_address(kDnsName);
  address->set_port_value(443);
  balancer_->ads_service()->SetCdsResource(cluster);

  // Note: We use InsecureCreds, since FakeCreds are too picky about

  LogicalDnsInitClient(MakeBootstrapBuilder().SetTrustedXdsServer(),
                       InsecureChannelCredentials());
  CreateAndStartBackends(1, false, InsecureServerCredentials());

  {
    grpc_core::ExecCtx exec_ctx;
    grpc_core::Resolver::Result result;
    result.addresses = CreateAddressListFromPortList(GetBackendPorts());
    logical_dns_cluster_resolver_response_generator_->SetResponseSynchronously(
        std::move(result));
  }

  EchoResponse response;
  Status status = SendRpc(
      RpcOptions().set_echo_host_from_authority_header(true), &response);
  EXPECT_TRUE(status.ok()) << "code=" << status.error_code()
                           << " message=" << status.error_message();
  EXPECT_EQ(response.param().host(), absl::StrCat(kDnsName, ":443"));
}

TEST_P(LogicalDNSClusterTest, NoAuthorityRewriteIfServerNotTrustedInBootstrap) {
  constexpr char kDnsName[] = "dns.example.com";

  RouteConfiguration new_route_config = default_route_config_;
  new_route_config.mutable_virtual_hosts(0)
      ->mutable_routes(0)
      ->mutable_route()
      ->mutable_auto_host_rewrite()
      ->set_value(true);
  SetRouteConfiguration(balancer_.get(), new_route_config);

  auto cluster = default_cluster_;
  cluster.set_type(Cluster::LOGICAL_DNS);
  auto* address = cluster.mutable_load_assignment()
                      ->add_endpoints()
                      ->add_lb_endpoints()
                      ->mutable_endpoint()
                      ->mutable_address()
                      ->mutable_socket_address();
  address->set_address(kDnsName);
  address->set_port_value(443);
  balancer_->ads_service()->SetCdsResource(cluster);

  LogicalDnsInitClient();
  CreateAndStartBackends(1);

  {
    grpc_core::ExecCtx exec_ctx;
    grpc_core::Resolver::Result result;
    result.addresses = CreateAddressListFromPortList(GetBackendPorts());
    logical_dns_cluster_resolver_response_generator_->SetResponseSynchronously(
        std::move(result));
  }

  EchoResponse response;
  Status status = SendRpc(
      RpcOptions().set_echo_host_from_authority_header(true), &response);
  EXPECT_TRUE(status.ok()) << "code=" << status.error_code()
                           << " message=" << status.error_message();
  EXPECT_EQ(response.param().host(), kServerName);
}

TEST_P(LogicalDNSClusterTest, NoAuthorityRewriteIfNotEnabledInRoute) {
  constexpr char kDnsName[] = "dns.example.com";

  auto cluster = default_cluster_;
  cluster.set_type(Cluster::LOGICAL_DNS);
  auto* address = cluster.mutable_load_assignment()
                      ->add_endpoints()
                      ->add_lb_endpoints()
                      ->mutable_endpoint()
                      ->mutable_address()
                      ->mutable_socket_address();
  address->set_address(kDnsName);
  address->set_port_value(443);
  balancer_->ads_service()->SetCdsResource(cluster);

  LogicalDnsInitClient(MakeBootstrapBuilder().SetTrustedXdsServer());
  CreateAndStartBackends(1);

  {
    grpc_core::ExecCtx exec_ctx;
    grpc_core::Resolver::Result result;
    result.addresses = CreateAddressListFromPortList(GetBackendPorts());
    logical_dns_cluster_resolver_response_generator_->SetResponseSynchronously(
        std::move(result));
  }

  EchoResponse response;
  Status status = SendRpc(
      RpcOptions().set_echo_host_from_authority_header(true), &response);
  EXPECT_TRUE(status.ok()) << "code=" << status.error_code()
                           << " message=" << status.error_message();
  EXPECT_EQ(response.param().host(), kServerName);
}

class AggregateClusterTest : public ClusterTypeTest {
 protected:
  void SetUp() override { LogicalDnsInitClient(); }
};

INSTANTIATE_TEST_SUITE_P(XdsTest, AggregateClusterTest,
                         ::testing::Values(XdsTestType()), &XdsTestType::Name);

TEST_P(AggregateClusterTest, Basic) {
  CreateAndStartBackends(2);
  const char* kNewCluster1Name = "new_cluster_1";
  const char* kNewEdsService1Name = "new_eds_service_name_1";
  const char* kNewCluster2Name = "new_cluster_2";
  const char* kNewEdsService2Name = "new_eds_service_name_2";

  EdsResourceArgs args1({
      {"locality0", CreateEndpointsForBackends(0, 1)},
  });
  EdsResourceArgs args2({
      {"locality0", CreateEndpointsForBackends(1, 2)},
  });
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

  auto cluster = default_cluster_;
  auto* custom_cluster = cluster.mutable_cluster_type();
  custom_cluster->set_name("envoy.clusters.aggregate");
  ClusterConfig cluster_config;
  cluster_config.add_clusters(kNewCluster1Name);
  cluster_config.add_clusters(kNewCluster2Name);
  custom_cluster->mutable_typed_config()->PackFrom(cluster_config);
  balancer_->ads_service()->SetCdsResource(cluster);

  WaitForBackend(DEBUG_LOCATION, 0);

  backends_[0]->StopListeningAndSendGoaways();
  WaitForBackend(DEBUG_LOCATION, 1);
  auto response_state = balancer_->ads_service()->cds_response_state();
  ASSERT_TRUE(response_state.has_value());
  EXPECT_EQ(response_state->state, AdsServiceImpl::ResponseState::ACKED);

  ShutdownBackend(0);
  StartBackend(0);
  WaitForBackend(DEBUG_LOCATION, 0);
}

TEST_P(AggregateClusterTest, LoadBalancingPolicyComesFromUnderlyingCluster) {
  CreateAndStartBackends(4);
  const char* kNewCluster1Name = "new_cluster_1";
  const char* kNewEdsService1Name = "new_eds_service_name_1";
  const char* kNewCluster2Name = "new_cluster_2";
  const char* kNewEdsService2Name = "new_eds_service_name_2";

  EdsResourceArgs args1({
      {"locality0", CreateEndpointsForBackends(0, 2)},
  });
  EdsResourceArgs args2({
      {"locality0", CreateEndpointsForBackends(2, 4)},
  });
  balancer_->ads_service()->SetEdsResource(
      BuildEdsResource(args1, kNewEdsService1Name));
  balancer_->ads_service()->SetEdsResource(
      BuildEdsResource(args2, kNewEdsService2Name));

  Cluster new_cluster1 = default_cluster_;
  new_cluster1.set_name(kNewCluster1Name);
  new_cluster1.mutable_eds_cluster_config()->set_service_name(
      kNewEdsService1Name);
  new_cluster1.set_lb_policy(Cluster::RING_HASH);
  balancer_->ads_service()->SetCdsResource(new_cluster1);
  Cluster new_cluster2 = default_cluster_;
  new_cluster2.set_name(kNewCluster2Name);
  new_cluster2.mutable_eds_cluster_config()->set_service_name(
      kNewEdsService2Name);
  balancer_->ads_service()->SetCdsResource(new_cluster2);

  auto cluster = default_cluster_;
  auto* custom_cluster = cluster.mutable_cluster_type();
  custom_cluster->set_name("envoy.clusters.aggregate");
  ClusterConfig cluster_config;
  cluster_config.add_clusters(kNewCluster1Name);
  cluster_config.add_clusters(kNewCluster2Name);
  custom_cluster->mutable_typed_config()->PackFrom(cluster_config);
  balancer_->ads_service()->SetCdsResource(cluster);

  auto new_route_config = default_route_config_;
  auto* route = new_route_config.mutable_virtual_hosts(0)->mutable_routes(0);
  auto* hash_policy = route->mutable_route()->add_hash_policy();
  hash_policy->mutable_filter_state()->set_key("io.grpc.channel_id");
  SetRouteConfiguration(balancer_.get(), new_route_config);

  CheckRpcSendOk(DEBUG_LOCATION, 100);
  bool found = false;
  for (size_t i = 0; i < 2; ++i) {
    if (backends_[i]->backend_service()->request_count() > 0) {
      EXPECT_EQ(backends_[i]->backend_service()->request_count(), 100)
          << "backend " << i;
      EXPECT_FALSE(found) << "backend " << i;
      found = true;
    }
  }
  EXPECT_TRUE(found);

  backends_[0]->StopListeningAndSendGoaways();
  backends_[1]->StopListeningAndSendGoaways();
  WaitForAllBackends(DEBUG_LOCATION, 2, 4);

  CheckRpcSendOk(DEBUG_LOCATION, 100);
  EXPECT_EQ(backends_[2]->backend_service()->request_count(), 50);
  EXPECT_EQ(backends_[3]->backend_service()->request_count(), 50);
}

TEST_P(AggregateClusterTest, LoadBalancingPolicyComesFromAggregateCluster) {
  grpc_core::testing::ScopedExperimentalEnvVar env(
      "GRPC_XDS_AGGREGATE_CLUSTER_BACKWARD_COMPAT");
  CreateAndStartBackends(4);
  const char* kNewCluster1Name = "new_cluster_1";
  const char* kNewEdsService1Name = "new_eds_service_name_1";
  const char* kNewCluster2Name = "new_cluster_2";
  const char* kNewEdsService2Name = "new_eds_service_name_2";

  EdsResourceArgs args1({
      {"locality0", CreateEndpointsForBackends(0, 2)},
  });
  EdsResourceArgs args2({
      {"locality0", CreateEndpointsForBackends(2, 4)},
  });
  balancer_->ads_service()->SetEdsResource(
      BuildEdsResource(args1, kNewEdsService1Name));
  balancer_->ads_service()->SetEdsResource(
      BuildEdsResource(args2, kNewEdsService2Name));

  Cluster new_cluster1 = default_cluster_;
  new_cluster1.set_name(kNewCluster1Name);
  new_cluster1.mutable_eds_cluster_config()->set_service_name(
      kNewEdsService1Name);
  new_cluster1.set_lb_policy(Cluster::RING_HASH);
  balancer_->ads_service()->SetCdsResource(new_cluster1);
  Cluster new_cluster2 = default_cluster_;
  new_cluster2.set_name(kNewCluster2Name);
  new_cluster2.mutable_eds_cluster_config()->set_service_name(
      kNewEdsService2Name);
  new_cluster2.set_lb_policy(Cluster::RING_HASH);
  balancer_->ads_service()->SetCdsResource(new_cluster2);

  auto cluster = default_cluster_;
  auto* custom_cluster = cluster.mutable_cluster_type();
  custom_cluster->set_name("envoy.clusters.aggregate");
  ClusterConfig cluster_config;
  cluster_config.add_clusters(kNewCluster1Name);
  cluster_config.add_clusters(kNewCluster2Name);
  custom_cluster->mutable_typed_config()->PackFrom(cluster_config);
  cluster.set_lb_policy(Cluster::ROUND_ROBIN);
  balancer_->ads_service()->SetCdsResource(cluster);

  auto new_route_config = default_route_config_;
  auto* route = new_route_config.mutable_virtual_hosts(0)->mutable_routes(0);
  auto* hash_policy = route->mutable_route()->add_hash_policy();
  hash_policy->mutable_filter_state()->set_key("io.grpc.channel_id");
  SetRouteConfiguration(balancer_.get(), new_route_config);

  WaitForAllBackends(DEBUG_LOCATION, 0, 2);

  CheckRpcSendOk(DEBUG_LOCATION, 100);
  EXPECT_EQ(backends_[0]->backend_service()->request_count(), 50);
  EXPECT_EQ(backends_[1]->backend_service()->request_count(), 50);

  backends_[0]->StopListeningAndSendGoaways();
  backends_[1]->StopListeningAndSendGoaways();
  WaitForAllBackends(DEBUG_LOCATION, 2, 4);

  CheckRpcSendOk(DEBUG_LOCATION, 100);
  EXPECT_EQ(backends_[2]->backend_service()->request_count(), 50);
  EXPECT_EQ(backends_[3]->backend_service()->request_count(), 50);
}

TEST_P(AggregateClusterTest, FallBackWithConnectivityChurn) {
  CreateAndStartBackends(2);
  const char* kClusterName1 = "cluster1";
  const char* kClusterName2 = "cluster2";
  const char* kEdsServiceName2 = "eds_service_name2";

  EdsResourceArgs args({{"locality0", CreateEndpointsForBackends(0, 1)}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));
  args = EdsResourceArgs({{"locality1", CreateEndpointsForBackends(1, 2)}});
  balancer_->ads_service()->SetEdsResource(
      BuildEdsResource(args, kEdsServiceName2));

  Cluster cluster1 = default_cluster_;
  cluster1.set_name(kClusterName1);
  balancer_->ads_service()->SetCdsResource(cluster1);
  Cluster cluster2 = default_cluster_;
  cluster2.set_name(kClusterName2);
  cluster2.mutable_eds_cluster_config()->set_service_name(kEdsServiceName2);
  balancer_->ads_service()->SetCdsResource(cluster2);

  auto cluster = default_cluster_;
  auto* custom_cluster = cluster.mutable_cluster_type();
  custom_cluster->set_name("envoy.clusters.aggregate");
  ClusterConfig cluster_config;
  cluster_config.add_clusters(kClusterName1);
  cluster_config.add_clusters(kClusterName2);
  custom_cluster->mutable_typed_config()->PackFrom(cluster_config);
  balancer_->ads_service()->SetCdsResource(cluster);

  ConnectionAttemptInjector injector;
  auto hold0 = injector.AddHold(backends_[0]->port());
  auto hold1 = injector.AddHold(backends_[1]->port());

  LongRunningRpc rpc;
  rpc.StartRpc(stub_.get(), RpcOptions().set_timeout_ms(2000));

  channel_->GetState(true);

  hold0->Wait();
  hold0->Fail(GRPC_ERROR_CREATE("injected connection failure"));

  LOG(INFO) << "=== WAITING FOR RPC TO FINISH === ";
  Status status = rpc.GetStatus();
  LOG(INFO) << "=== RPC FINISHED === ";
  EXPECT_TRUE(status.ok()) << "code=" << status.error_code()
                           << " message=" << status.error_message();
  EXPECT_EQ(1UL, backends_[0]->backend_service()->request_count());

  hold1->Wait();

  backends_[0]->StopListeningAndSendGoaways();

  hold1->Resume();

  WaitForBackend(DEBUG_LOCATION, 1);
}

TEST_P(AggregateClusterTest, EdsToLogicalDns) {
  CreateAndStartBackends(2);
  const char* kNewCluster1Name = "new_cluster_1";
  const char* kNewEdsService1Name = "new_eds_service_name_1";
  const char* kLogicalDNSClusterName = "logical_dns_cluster";

  EdsResourceArgs args1({{"locality0", CreateEndpointsForBackends(0, 1)}});
  balancer_->ads_service()->SetEdsResource(
      BuildEdsResource(args1, kNewEdsService1Name));

  Cluster new_cluster1 = default_cluster_;
  new_cluster1.set_name(kNewCluster1Name);
  new_cluster1.mutable_eds_cluster_config()->set_service_name(
      kNewEdsService1Name);
  balancer_->ads_service()->SetCdsResource(new_cluster1);

  auto logical_dns_cluster = default_cluster_;
  logical_dns_cluster.set_name(kLogicalDNSClusterName);
  logical_dns_cluster.set_type(Cluster::LOGICAL_DNS);
  auto* address = logical_dns_cluster.mutable_load_assignment()
                      ->add_endpoints()
                      ->add_lb_endpoints()
                      ->mutable_endpoint()
                      ->mutable_address()
                      ->mutable_socket_address();
  address->set_address(kServerName);
  address->set_port_value(443);
  balancer_->ads_service()->SetCdsResource(logical_dns_cluster);

  auto cluster = default_cluster_;
  auto* custom_cluster = cluster.mutable_cluster_type();
  custom_cluster->set_name("envoy.clusters.aggregate");
  ClusterConfig cluster_config;
  cluster_config.add_clusters(kNewCluster1Name);
  cluster_config.add_clusters(kLogicalDNSClusterName);
  custom_cluster->mutable_typed_config()->PackFrom(cluster_config);
  balancer_->ads_service()->SetCdsResource(cluster);

  {
    grpc_core::ExecCtx exec_ctx;
    grpc_core::Resolver::Result result;
    result.addresses = CreateAddressListFromPortList(GetBackendPorts(1, 2));
    logical_dns_cluster_resolver_response_generator_->SetResponseSynchronously(
        std::move(result));
  }

  WaitForBackend(DEBUG_LOCATION, 0);

  backends_[0]->StopListeningAndSendGoaways();
  WaitForBackend(DEBUG_LOCATION, 1);
  auto response_state = balancer_->ads_service()->cds_response_state();
  ASSERT_TRUE(response_state.has_value());
  EXPECT_EQ(response_state->state, AdsServiceImpl::ResponseState::ACKED);

  ShutdownBackend(0);
  StartBackend(0);
  WaitForBackend(DEBUG_LOCATION, 0);
}

TEST_P(AggregateClusterTest, LogicalDnsToEds) {
  CreateAndStartBackends(2);
  const char* kNewCluster2Name = "new_cluster_2";
  const char* kNewEdsService2Name = "new_eds_service_name_2";
  const char* kLogicalDNSClusterName = "logical_dns_cluster";

  EdsResourceArgs args2({
      {"locality0", CreateEndpointsForBackends(1, 2)},
  });
  balancer_->ads_service()->SetEdsResource(
      BuildEdsResource(args2, kNewEdsService2Name));

  Cluster new_cluster2 = default_cluster_;
  new_cluster2.set_name(kNewCluster2Name);
  new_cluster2.mutable_eds_cluster_config()->set_service_name(
      kNewEdsService2Name);
  balancer_->ads_service()->SetCdsResource(new_cluster2);

  auto logical_dns_cluster = default_cluster_;
  logical_dns_cluster.set_name(kLogicalDNSClusterName);
  logical_dns_cluster.set_type(Cluster::LOGICAL_DNS);
  auto* address = logical_dns_cluster.mutable_load_assignment()
                      ->add_endpoints()
                      ->add_lb_endpoints()
                      ->mutable_endpoint()
                      ->mutable_address()
                      ->mutable_socket_address();
  address->set_address(kServerName);
  address->set_port_value(443);
  balancer_->ads_service()->SetCdsResource(logical_dns_cluster);

  auto cluster = default_cluster_;
  auto* custom_cluster = cluster.mutable_cluster_type();
  custom_cluster->set_name("envoy.clusters.aggregate");
  ClusterConfig cluster_config;
  cluster_config.add_clusters(kLogicalDNSClusterName);
  cluster_config.add_clusters(kNewCluster2Name);
  custom_cluster->mutable_typed_config()->PackFrom(cluster_config);
  balancer_->ads_service()->SetCdsResource(cluster);

  {
    grpc_core::ExecCtx exec_ctx;
    grpc_core::Resolver::Result result;
    result.addresses = CreateAddressListFromPortList(GetBackendPorts(0, 1));
    logical_dns_cluster_resolver_response_generator_->SetResponseSynchronously(
        std::move(result));
  }

  WaitForBackend(DEBUG_LOCATION, 0);

  backends_[0]->StopListeningAndSendGoaways();
  WaitForBackend(DEBUG_LOCATION, 1);
  auto response_state = balancer_->ads_service()->cds_response_state();
  ASSERT_TRUE(response_state.has_value());
  EXPECT_EQ(response_state->state, AdsServiceImpl::ResponseState::ACKED);

  ShutdownBackend(0);
  StartBackend(0);
  WaitForBackend(DEBUG_LOCATION, 0);
}

TEST_P(AggregateClusterTest, ReconfigEdsWhileLogicalDnsChildFails) {
  CreateAndStartBackends(2);
  const char* kNewCluster1Name = "new_cluster_1";
  const char* kNewEdsService1Name = "new_eds_service_name_1";
  const char* kLogicalDNSClusterName = "logical_dns_cluster";

  EdsResourceArgs args1({
      {"locality0", {MakeNonExistentEndpoint()}, kDefaultLocalityWeight, 0},
      {"locality1", {MakeNonExistentEndpoint()}, kDefaultLocalityWeight, 1},
      {"locality2", {MakeNonExistentEndpoint()}, kDefaultLocalityWeight, 1},
  });
  balancer_->ads_service()->SetEdsResource(
      BuildEdsResource(args1, kNewEdsService1Name));

  Cluster new_cluster1 = default_cluster_;
  new_cluster1.set_name(kNewCluster1Name);
  new_cluster1.mutable_eds_cluster_config()->set_service_name(
      kNewEdsService1Name);
  balancer_->ads_service()->SetCdsResource(new_cluster1);

  auto logical_dns_cluster = default_cluster_;
  logical_dns_cluster.set_name(kLogicalDNSClusterName);
  logical_dns_cluster.set_type(Cluster::LOGICAL_DNS);
  auto* address = logical_dns_cluster.mutable_load_assignment()
                      ->add_endpoints()
                      ->add_lb_endpoints()
                      ->mutable_endpoint()
                      ->mutable_address()
                      ->mutable_socket_address();
  address->set_address(kServerName);
  address->set_port_value(443);
  balancer_->ads_service()->SetCdsResource(logical_dns_cluster);

  auto cluster = default_cluster_;
  auto* custom_cluster = cluster.mutable_cluster_type();
  custom_cluster->set_name("envoy.clusters.aggregate");
  ClusterConfig cluster_config;
  cluster_config.add_clusters(kNewCluster1Name);
  cluster_config.add_clusters(kLogicalDNSClusterName);
  custom_cluster->mutable_typed_config()->PackFrom(cluster_config);
  balancer_->ads_service()->SetCdsResource(cluster);

  {
    grpc_core::ExecCtx exec_ctx;
    grpc_core::Resolver::Result result;
    result.addresses = absl::UnavailableError("injected error");
    logical_dns_cluster_resolver_response_generator_->SetResponseSynchronously(
        std::move(result));
  }

  constexpr char kErrorMessage[] =
      "no children in weighted_target policy \\(DNS resolution failed for "
      "server.example.com:443: UNAVAILABLE: injected error\\)";
  CheckRpcSendFailure(DEBUG_LOCATION, StatusCode::UNAVAILABLE, kErrorMessage);

  args1 = EdsResourceArgs({
      {"locality1", CreateEndpointsForBackends(0, 1), kDefaultLocalityWeight,
       0},
      {"locality2", CreateEndpointsForBackends(1, 2), kDefaultLocalityWeight,
       1},
  });
  balancer_->ads_service()->SetEdsResource(
      BuildEdsResource(args1, kNewEdsService1Name));
  WaitForBackend(DEBUG_LOCATION, 0, [&](const RpcResult& result) {
    if (!result.status.ok()) {
      EXPECT_EQ(result.status.error_code(), StatusCode::UNAVAILABLE);
      EXPECT_THAT(result.status.error_message(),
                  ::testing::MatchesRegex(kErrorMessage));
    }
  });
}

TEST_P(AggregateClusterTest, MultipleClustersWithSameLocalities) {
  CreateAndStartBackends(2);
  const char* kNewClusterName1 = "new_cluster_1";
  const char* kNewEdsServiceName1 = "new_eds_service_name_1";
  const char* kNewClusterName2 = "new_cluster_2";
  const char* kNewEdsServiceName2 = "new_eds_service_name_2";

  EdsResourceArgs args1({{"locality0", {MakeNonExistentEndpoint()}}});
  balancer_->ads_service()->SetEdsResource(
      BuildEdsResource(args1, kNewEdsServiceName1));

  Cluster new_cluster1 = default_cluster_;
  new_cluster1.set_name(kNewClusterName1);
  new_cluster1.mutable_eds_cluster_config()->set_service_name(
      kNewEdsServiceName1);
  balancer_->ads_service()->SetCdsResource(new_cluster1);

  args1 = EdsResourceArgs({{"locality1", CreateEndpointsForBackends(0, 1)}});
  balancer_->ads_service()->SetEdsResource(
      BuildEdsResource(args1, kNewEdsServiceName2));

  Cluster new_cluster2 = default_cluster_;
  new_cluster2.set_name(kNewClusterName2);
  new_cluster2.mutable_eds_cluster_config()->set_service_name(
      kNewEdsServiceName2);
  balancer_->ads_service()->SetCdsResource(new_cluster2);

  auto cluster = default_cluster_;
  auto* custom_cluster = cluster.mutable_cluster_type();
  custom_cluster->set_name("envoy.clusters.aggregate");
  ClusterConfig cluster_config;
  cluster_config.add_clusters(kNewClusterName1);
  cluster_config.add_clusters(kNewClusterName2);
  custom_cluster->mutable_typed_config()->PackFrom(cluster_config);
  balancer_->ads_service()->SetCdsResource(cluster);

  WaitForBackend(DEBUG_LOCATION, 0);

  args1 = EdsResourceArgs({{"locality1", CreateEndpointsForBackends(1, 2)}});
  balancer_->ads_service()->SetEdsResource(
      BuildEdsResource(args1, kNewEdsServiceName1));
  WaitForBackend(DEBUG_LOCATION, 1);
}

TEST_P(AggregateClusterTest, UpdateOfChildCluster) {
  CreateAndStartBackends(2);
  const char* kNewCluster1Name = "new_cluster_1";
  const char* kNewEdsService1Name = "new_eds_service_name_1";
  const char* kNewEdsService2Name = "new_eds_service_name_2";

  EdsResourceArgs args1({
      {"locality0", CreateEndpointsForBackends(0, 1)},
  });
  EdsResourceArgs args2({
      {"locality0", CreateEndpointsForBackends(1, 2)},
  });
  balancer_->ads_service()->SetEdsResource(
      BuildEdsResource(args1, kNewEdsService1Name));
  balancer_->ads_service()->SetEdsResource(
      BuildEdsResource(args2, kNewEdsService2Name));

  Cluster new_cluster1 = default_cluster_;
  new_cluster1.set_name(kNewCluster1Name);
  new_cluster1.mutable_eds_cluster_config()->set_service_name(
      kNewEdsService1Name);
  balancer_->ads_service()->SetCdsResource(new_cluster1);

  auto cluster = default_cluster_;
  auto* custom_cluster = cluster.mutable_cluster_type();
  custom_cluster->set_name("envoy.clusters.aggregate");
  ClusterConfig cluster_config;
  cluster_config.add_clusters(kNewCluster1Name);
  custom_cluster->mutable_typed_config()->PackFrom(cluster_config);
  balancer_->ads_service()->SetCdsResource(cluster);

  WaitForBackend(DEBUG_LOCATION, 0);
  auto response_state = balancer_->ads_service()->cds_response_state();
  ASSERT_TRUE(response_state.has_value());
  EXPECT_EQ(response_state->state, AdsServiceImpl::ResponseState::ACKED);

  new_cluster1.mutable_eds_cluster_config()->set_service_name(
      kNewEdsService2Name);
  balancer_->ads_service()->SetCdsResource(new_cluster1);

  WaitForBackend(DEBUG_LOCATION, 1);
  response_state = balancer_->ads_service()->cds_response_state();
  ASSERT_TRUE(response_state.has_value());
  EXPECT_EQ(response_state->state, AdsServiceImpl::ResponseState::ACKED);
}

TEST_P(AggregateClusterTest, DiamondDependency) {
  const char* kNewClusterName1 = "new_cluster_1";
  const char* kNewEdsServiceName1 = "new_eds_service_name_1";
  const char* kNewClusterName2 = "new_cluster_2";
  const char* kNewEdsServiceName2 = "new_eds_service_name_2";
  const char* kNewAggregateClusterName = "new_aggregate_cluster";

  CreateAndStartBackends(2);
  EdsResourceArgs args1({{"locality0", CreateEndpointsForBackends(0, 1)}});
  balancer_->ads_service()->SetEdsResource(
      BuildEdsResource(args1, kNewEdsServiceName1));
  EdsResourceArgs args2({{"locality0", CreateEndpointsForBackends(1, 2)}});
  balancer_->ads_service()->SetEdsResource(
      BuildEdsResource(args2, kNewEdsServiceName2));

  Cluster new_cluster1 = default_cluster_;
  new_cluster1.set_name(kNewClusterName1);
  new_cluster1.mutable_eds_cluster_config()->set_service_name(
      kNewEdsServiceName1);
  balancer_->ads_service()->SetCdsResource(new_cluster1);
  Cluster new_cluster2 = default_cluster_;
  new_cluster2.set_name(kNewClusterName2);
  new_cluster2.mutable_eds_cluster_config()->set_service_name(
      kNewEdsServiceName2);
  balancer_->ads_service()->SetCdsResource(new_cluster2);

  auto cluster = default_cluster_;
  auto* custom_cluster = cluster.mutable_cluster_type();
  custom_cluster->set_name("envoy.clusters.aggregate");
  ClusterConfig cluster_config;
  cluster_config.add_clusters(kNewClusterName1);
  cluster_config.add_clusters(kNewAggregateClusterName);
  custom_cluster->mutable_typed_config()->PackFrom(cluster_config);
  balancer_->ads_service()->SetCdsResource(cluster);

  auto aggregate_cluster2 = default_cluster_;
  aggregate_cluster2.set_name(kNewAggregateClusterName);
  custom_cluster = aggregate_cluster2.mutable_cluster_type();
  custom_cluster->set_name("envoy.clusters.aggregate");
  cluster_config.Clear();
  cluster_config.add_clusters(kNewClusterName1);
  cluster_config.add_clusters(kNewClusterName2);
  custom_cluster->mutable_typed_config()->PackFrom(cluster_config);
  balancer_->ads_service()->SetCdsResource(aggregate_cluster2);

  WaitForBackend(DEBUG_LOCATION, 0);

  backends_[0]->StopListeningAndSendGoaways();
  WaitForBackend(DEBUG_LOCATION, 1);
  auto response_state = balancer_->ads_service()->cds_response_state();
  ASSERT_TRUE(response_state.has_value());
  EXPECT_EQ(response_state->state, AdsServiceImpl::ResponseState::ACKED);

  ShutdownBackend(0);
  StartBackend(0);
  WaitForBackend(DEBUG_LOCATION, 0);
}

TEST_P(AggregateClusterTest, DependencyLoopWithNoLeafClusters) {
  const char* kNewClusterName1 = "new_cluster_1";

  auto cluster = default_cluster_;
  auto* custom_cluster = cluster.mutable_cluster_type();
  custom_cluster->set_name("envoy.clusters.aggregate");
  ClusterConfig cluster_config;
  cluster_config.add_clusters(kNewClusterName1);
  custom_cluster->mutable_typed_config()->PackFrom(cluster_config);
  balancer_->ads_service()->SetCdsResource(cluster);

  cluster.set_name(kNewClusterName1);
  cluster_config.Clear();
  cluster_config.add_clusters(kDefaultClusterName);
  custom_cluster->mutable_typed_config()->PackFrom(cluster_config);
  balancer_->ads_service()->SetCdsResource(cluster);

  CheckRpcSendFailure(DEBUG_LOCATION, StatusCode::UNAVAILABLE,
                      "aggregate cluster dependency graph for cluster_name "
                      "has no leaf clusters");
}

TEST_P(AggregateClusterTest, DependencyLoopWithLeafClusters) {
  const char* kNewClusterName1 = "new_cluster_1";

  CreateAndStartBackends(1);
  EdsResourceArgs args1({{"locality0", CreateEndpointsForBackends()}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args1));

  Cluster new_cluster1 = default_cluster_;
  new_cluster1.set_name(kNewClusterName1);
  balancer_->ads_service()->SetCdsResource(new_cluster1);

  auto cluster = default_cluster_;
  auto* custom_cluster = cluster.mutable_cluster_type();
  custom_cluster->set_name("envoy.clusters.aggregate");
  ClusterConfig cluster_config;
  cluster_config.add_clusters(kNewClusterName1);
  cluster_config.add_clusters(kDefaultClusterName);
  custom_cluster->mutable_typed_config()->PackFrom(cluster_config);
  balancer_->ads_service()->SetCdsResource(cluster);

  CheckRpcSendOk(DEBUG_LOCATION);
}

TEST_P(AggregateClusterTest, RecursionDepthJustBelowMax) {

  CreateAndStartBackends(1);
  EdsResourceArgs args({{"locality0", CreateEndpointsForBackends()}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  Cluster new_cluster = default_cluster_;
  new_cluster.set_name(absl::StrCat(kDefaultClusterName, 15));
  balancer_->ads_service()->SetCdsResource(new_cluster);

  for (int i = 14; i >= 0; --i) {
    auto cluster = default_cluster_;
    if (i > 0) cluster.set_name(absl::StrCat(kDefaultClusterName, i));
    auto* custom_cluster = cluster.mutable_cluster_type();
    custom_cluster->set_name("envoy.clusters.aggregate");
    ClusterConfig cluster_config;
    cluster_config.add_clusters(absl::StrCat(kDefaultClusterName, i + 1));
    custom_cluster->mutable_typed_config()->PackFrom(cluster_config);
    balancer_->ads_service()->SetCdsResource(cluster);
  }

  CheckRpcSendOk(DEBUG_LOCATION);
}

TEST_P(AggregateClusterTest, RecursionMaxDepth) {

  CreateAndStartBackends(1);
  EdsResourceArgs args({{"locality0", CreateEndpointsForBackends()}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  Cluster new_cluster = default_cluster_;
  new_cluster.set_name(absl::StrCat(kDefaultClusterName, 16));
  balancer_->ads_service()->SetCdsResource(new_cluster);

  for (int i = 15; i >= 0; --i) {
    auto cluster = default_cluster_;
    if (i > 0) cluster.set_name(absl::StrCat(kDefaultClusterName, i));
    auto* custom_cluster = cluster.mutable_cluster_type();
    custom_cluster->set_name("envoy.clusters.aggregate");
    ClusterConfig cluster_config;
    cluster_config.add_clusters(absl::StrCat(kDefaultClusterName, i + 1));
    custom_cluster->mutable_typed_config()->PackFrom(cluster_config);
    balancer_->ads_service()->SetCdsResource(cluster);
  }

  const Status status = SendRpc();
  EXPECT_EQ(StatusCode::UNAVAILABLE, status.error_code());
  EXPECT_THAT(
      status.error_message(),
      ::testing::HasSubstr("aggregate cluster graph exceeds max depth"));
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
