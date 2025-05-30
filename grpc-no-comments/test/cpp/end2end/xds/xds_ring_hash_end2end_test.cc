// Copyright 2017 gRPC authors.

#include <grpc/event_engine/endpoint_config.h>

#include <string>
#include <vector>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_format.h"
#include "envoy/config/cluster/v3/cluster.pb.h"
#include "envoy/extensions/clusters/aggregate/v3/cluster.pb.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "src/core/client_channel/backup_poller.h"
#include "src/core/config/config_vars.h"
#include "src/core/lib/address_utils/sockaddr_utils.h"
#include "src/core/load_balancing/xds/xds_channel_args.h"
#include "src/core/resolver/fake/fake_resolver.h"
#include "src/core/util/env.h"
#include "test/core/test_util/resolve_localhost_ip46.h"
#include "test/core/test_util/scoped_env_var.h"
#include "test/cpp/end2end/connection_attempt_injector.h"
#include "test/cpp/end2end/xds/xds_end2end_test_lib.h"

namespace grpc {
namespace testing {
namespace {

using ::envoy::config::core::v3::HealthStatus;
using ::envoy::extensions::clusters::aggregate::v3::ClusterConfig;

class RingHashTest : public XdsEnd2endTest {
 protected:
  void SetUp() override {
    logical_dns_cluster_resolver_response_generator_ =
        grpc_core::MakeRefCounted<grpc_core::FakeResolverResponseGenerator>();
    InitClient();
    SetUpChannel();
  }

  void SetUpChannel(ChannelArguments* args = nullptr) {
    ChannelArguments local_args;
    if (args == nullptr) args = &local_args;
    args->SetPointerWithVtable(
        GRPC_ARG_XDS_LOGICAL_DNS_CLUSTER_FAKE_RESOLVER_RESPONSE_GENERATOR,
        logical_dns_cluster_resolver_response_generator_.get(),
        &grpc_core::FakeResolverResponseGenerator::kChannelArgPointerVtable);
    ResetStub(0, args);
  }

  grpc_core::EndpointAddressesList CreateAddressListFromPortList(
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

  std::string CreateMetadataValueThatHashesToBackendPort(int port) {
    return absl::StrCat(grpc_core::LocalIp(), ":", port, "_0");
  }

  std::string CreateMetadataValueThatHashesToBackend(int index) {
    return CreateMetadataValueThatHashesToBackendPort(backends_[index]->port());
  }

  grpc_core::RefCountedPtr<grpc_core::FakeResolverResponseGenerator>
      logical_dns_cluster_resolver_response_generator_;
};

INSTANTIATE_TEST_SUITE_P(
    XdsTest, RingHashTest,
    ::testing::Values(XdsTestType(), XdsTestType().set_enable_load_reporting()),
    &XdsTestType::Name);

TEST_P(RingHashTest, AggregateClusterFallBackFromRingHashAtStartup) {
  CreateAndStartBackends(2);
  const char* kNewCluster1Name = "new_cluster_1";
  const char* kNewEdsService1Name = "new_eds_service_name_1";
  const char* kNewCluster2Name = "new_cluster_2";
  const char* kNewEdsService2Name = "new_eds_service_name_2";

  EdsResourceArgs args1({
      {"locality0", {MakeNonExistentEndpoint(), MakeNonExistentEndpoint()}},
  });
  EdsResourceArgs args2({
      {"locality0", CreateEndpointsForBackends()},
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
  balancer_->ads_service()->SetCdsResource(cluster);

  auto new_route_config = default_route_config_;
  auto* route = new_route_config.mutable_virtual_hosts(0)->mutable_routes(0);
  auto* hash_policy = route->mutable_route()->add_hash_policy();
  hash_policy->mutable_filter_state()->set_key("io.grpc.channel_id");
  SetListenerAndRouteConfiguration(balancer_.get(), default_listener_,
                                   new_route_config);

  CheckRpcSendOk(DEBUG_LOCATION, 100, RpcOptions().set_timeout_ms(5000));
  bool found = false;
  for (size_t i = 0; i < backends_.size(); ++i) {
    if (backends_[i]->backend_service()->request_count() > 0) {
      EXPECT_EQ(backends_[i]->backend_service()->request_count(), 100)
          << "backend " << i;
      EXPECT_FALSE(found) << "backend " << i;
      found = true;
    }
  }
  EXPECT_TRUE(found);
}

TEST_P(RingHashTest,
       AggregateClusterFallBackFromRingHashToLogicalDnsAtStartup) {
  CreateAndStartBackends(1);
  const char* kEdsClusterName = "eds_cluster";
  const char* kLogicalDNSClusterName = "logical_dns_cluster";

  EdsResourceArgs args({
      {"locality0",
       {MakeNonExistentEndpoint(), MakeNonExistentEndpoint()},
       kDefaultLocalityWeight,
       0},
      {"locality1",
       {MakeNonExistentEndpoint(), MakeNonExistentEndpoint()},
       kDefaultLocalityWeight,
       1},
  });
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  Cluster eds_cluster = default_cluster_;
  eds_cluster.set_name(kEdsClusterName);
  eds_cluster.set_lb_policy(Cluster::RING_HASH);
  balancer_->ads_service()->SetCdsResource(eds_cluster);

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
  cluster_config.add_clusters(kEdsClusterName);
  cluster_config.add_clusters(kLogicalDNSClusterName);
  custom_cluster->mutable_typed_config()->PackFrom(cluster_config);
  balancer_->ads_service()->SetCdsResource(cluster);

  auto new_route_config = default_route_config_;
  auto* route = new_route_config.mutable_virtual_hosts(0)->mutable_routes(0);
  auto* hash_policy = route->mutable_route()->add_hash_policy();
  hash_policy->mutable_filter_state()->set_key("io.grpc.channel_id");
  SetListenerAndRouteConfiguration(balancer_.get(), default_listener_,
                                   new_route_config);

  {
    grpc_core::ExecCtx exec_ctx;
    grpc_core::Resolver::Result result;
    result.addresses = CreateAddressListFromPortList(GetBackendPorts());
    logical_dns_cluster_resolver_response_generator_->SetResponseSynchronously(
        std::move(result));
  }

  ConnectionAttemptInjector injector;
  injector.SetDelay(grpc_core::Duration::Milliseconds(500) *
                    grpc_test_slowdown_factor());

  CheckRpcSendOk(DEBUG_LOCATION, 1, RpcOptions().set_timeout_ms(5000));
}

TEST_P(RingHashTest,
       AggregateClusterFallBackFromRingHashToLogicalDnsAtStartupNoFailedRpcs) {
  CreateAndStartBackends(1);
  const char* kEdsClusterName = "eds_cluster";
  const char* kLogicalDNSClusterName = "logical_dns_cluster";

  EdsResourceArgs args({
      {"locality0",
       {MakeNonExistentEndpoint(), MakeNonExistentEndpoint()},
       kDefaultLocalityWeight,
       0},
      {"locality1",
       {MakeNonExistentEndpoint(), MakeNonExistentEndpoint()},
       kDefaultLocalityWeight,
       1},
  });
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  Cluster eds_cluster = default_cluster_;
  eds_cluster.set_name(kEdsClusterName);
  eds_cluster.set_lb_policy(Cluster::RING_HASH);
  balancer_->ads_service()->SetCdsResource(eds_cluster);

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
  cluster_config.add_clusters(kEdsClusterName);
  cluster_config.add_clusters(kLogicalDNSClusterName);
  custom_cluster->mutable_typed_config()->PackFrom(cluster_config);
  balancer_->ads_service()->SetCdsResource(cluster);

  auto new_route_config = default_route_config_;
  auto* route = new_route_config.mutable_virtual_hosts(0)->mutable_routes(0);
  auto* hash_policy = route->mutable_route()->add_hash_policy();
  hash_policy->mutable_filter_state()->set_key("io.grpc.channel_id");
  SetListenerAndRouteConfiguration(balancer_.get(), default_listener_,
                                   new_route_config);

  {
    grpc_core::ExecCtx exec_ctx;
    grpc_core::Resolver::Result result;
    result.addresses = CreateAddressListFromPortList(GetBackendPorts());
    logical_dns_cluster_resolver_response_generator_->SetResponseSynchronously(
        std::move(result));
  }

  ConnectionAttemptInjector injector;
  auto hold = injector.AddHold(backends_[0]->port());

  ChannelArguments channel_args;
  channel_args.SetInt(GRPC_ARG_INITIAL_RECONNECT_BACKOFF_MS,
                      10000 * grpc_test_slowdown_factor());
  SetUpChannel(&channel_args);

  LongRunningRpc rpc;
  rpc.StartRpc(stub_.get(), RpcOptions().set_timeout_ms(5000));

  hold->Wait();

  EXPECT_EQ(channel_->GetState(false), GRPC_CHANNEL_CONNECTING);

  LongRunningRpc rpc2;
  rpc2.StartRpc(stub_.get(), RpcOptions().set_timeout_ms(5000));

  hold->Resume();

  LOG(INFO) << "=== WAITING FOR FIRST RPC TO FINISH ===";
  Status status = rpc.GetStatus();
  LOG(INFO) << "=== FIRST RPC FINISHED ===";
  EXPECT_TRUE(status.ok()) << "code=" << status.error_code()
                           << " message=" << status.error_message();
  LOG(INFO) << "=== WAITING FOR SECOND RPC TO FINISH ===";
  status = rpc2.GetStatus();
  LOG(INFO) << "=== SECOND RPC FINISHED ===";
  EXPECT_TRUE(status.ok()) << "code=" << status.error_code()
                           << " message=" << status.error_message();
}

TEST_P(RingHashTest, ChannelIdHashing) {
  CreateAndStartBackends(4);
  auto cluster = default_cluster_;
  cluster.set_lb_policy(Cluster::RING_HASH);
  balancer_->ads_service()->SetCdsResource(cluster);
  auto new_route_config = default_route_config_;
  auto* route = new_route_config.mutable_virtual_hosts(0)->mutable_routes(0);
  auto* hash_policy = route->mutable_route()->add_hash_policy();
  hash_policy->mutable_filter_state()->set_key("io.grpc.channel_id");
  SetListenerAndRouteConfiguration(balancer_.get(), default_listener_,
                                   new_route_config);
  EdsResourceArgs args({{"locality0", CreateEndpointsForBackends()}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));
  CheckRpcSendOk(DEBUG_LOCATION, 100, RpcOptions().set_timeout_ms(5000));
  bool found = false;
  for (size_t i = 0; i < backends_.size(); ++i) {
    if (backends_[i]->backend_service()->request_count() > 0) {
      EXPECT_EQ(backends_[i]->backend_service()->request_count(), 100)
          << "backend " << i;
      EXPECT_FALSE(found) << "backend " << i;
      found = true;
    }
  }
  EXPECT_TRUE(found);
}

TEST_P(RingHashTest, HeaderHashing) {
  CreateAndStartBackends(4);
  auto cluster = default_cluster_;
  cluster.set_lb_policy(Cluster::RING_HASH);
  balancer_->ads_service()->SetCdsResource(cluster);
  auto new_route_config = default_route_config_;
  auto* route = new_route_config.mutable_virtual_hosts(0)->mutable_routes(0);
  auto* hash_policy = route->mutable_route()->add_hash_policy();
  hash_policy->mutable_header()->set_header_name("address_hash");
  SetListenerAndRouteConfiguration(balancer_.get(), default_listener_,
                                   new_route_config);
  EdsResourceArgs args({{"locality0", CreateEndpointsForBackends()}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  std::vector<std::pair<std::string, std::string>> metadata = {
      {"address_hash", CreateMetadataValueThatHashesToBackend(0)}};
  std::vector<std::pair<std::string, std::string>> metadata1 = {
      {"address_hash", CreateMetadataValueThatHashesToBackend(1)}};
  std::vector<std::pair<std::string, std::string>> metadata2 = {
      {"address_hash", CreateMetadataValueThatHashesToBackend(2)}};
  std::vector<std::pair<std::string, std::string>> metadata3 = {
      {"address_hash", CreateMetadataValueThatHashesToBackend(3)}};
  const auto rpc_options =
      RpcOptions().set_metadata(std::move(metadata)).set_timeout_ms(5000);
  const auto rpc_options1 =
      RpcOptions().set_metadata(std::move(metadata1)).set_timeout_ms(5000);
  const auto rpc_options2 =
      RpcOptions().set_metadata(std::move(metadata2)).set_timeout_ms(5000);
  const auto rpc_options3 =
      RpcOptions().set_metadata(std::move(metadata3)).set_timeout_ms(5000);
  WaitForBackend(DEBUG_LOCATION, 0, nullptr,
                 WaitForBackendOptions(), rpc_options);
  WaitForBackend(DEBUG_LOCATION, 1, nullptr,
                 WaitForBackendOptions(), rpc_options1);
  WaitForBackend(DEBUG_LOCATION, 2, nullptr,
                 WaitForBackendOptions(), rpc_options2);
  WaitForBackend(DEBUG_LOCATION, 3, nullptr,
                 WaitForBackendOptions(), rpc_options3);
  CheckRpcSendOk(DEBUG_LOCATION, 100, rpc_options);
  CheckRpcSendOk(DEBUG_LOCATION, 100, rpc_options1);
  CheckRpcSendOk(DEBUG_LOCATION, 100, rpc_options2);
  CheckRpcSendOk(DEBUG_LOCATION, 100, rpc_options3);
  for (size_t i = 0; i < backends_.size(); ++i) {
    EXPECT_EQ(100, backends_[i]->backend_service()->request_count());
  }
}

TEST_P(RingHashTest, HeaderHashingWithRegexRewrite) {
  CreateAndStartBackends(4);
  auto cluster = default_cluster_;
  cluster.set_lb_policy(Cluster::RING_HASH);
  balancer_->ads_service()->SetCdsResource(cluster);
  auto new_route_config = default_route_config_;
  auto* route = new_route_config.mutable_virtual_hosts(0)->mutable_routes(0);
  auto* hash_policy = route->mutable_route()->add_hash_policy();
  hash_policy->mutable_header()->set_header_name("address_hash");
  hash_policy->mutable_header()
      ->mutable_regex_rewrite()
      ->mutable_pattern()
      ->set_regex("[0-9]+");
  hash_policy->mutable_header()->mutable_regex_rewrite()->set_substitution(
      "foo");
  SetListenerAndRouteConfiguration(balancer_.get(), default_listener_,
                                   new_route_config);
  EdsResourceArgs args({{"locality0", CreateEndpointsForBackends()}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));
  std::vector<std::pair<std::string, std::string>> metadata = {
      {"address_hash", CreateMetadataValueThatHashesToBackend(0)}};
  std::vector<std::pair<std::string, std::string>> metadata1 = {
      {"address_hash", CreateMetadataValueThatHashesToBackend(1)}};
  std::vector<std::pair<std::string, std::string>> metadata2 = {
      {"address_hash", CreateMetadataValueThatHashesToBackend(2)}};
  std::vector<std::pair<std::string, std::string>> metadata3 = {
      {"address_hash", CreateMetadataValueThatHashesToBackend(3)}};
  const auto rpc_options =
      RpcOptions().set_metadata(std::move(metadata)).set_timeout_ms(5000);
  const auto rpc_options1 =
      RpcOptions().set_metadata(std::move(metadata1)).set_timeout_ms(5000);
  const auto rpc_options2 =
      RpcOptions().set_metadata(std::move(metadata2)).set_timeout_ms(5000);
  const auto rpc_options3 =
      RpcOptions().set_metadata(std::move(metadata3)).set_timeout_ms(5000);
  CheckRpcSendOk(DEBUG_LOCATION, 100, rpc_options);
  CheckRpcSendOk(DEBUG_LOCATION, 100, rpc_options1);
  CheckRpcSendOk(DEBUG_LOCATION, 100, rpc_options2);
  CheckRpcSendOk(DEBUG_LOCATION, 100, rpc_options3);
  bool found = false;
  for (size_t i = 0; i < backends_.size(); ++i) {
    if (backends_[i]->backend_service()->request_count() > 0) {
      EXPECT_EQ(backends_[i]->backend_service()->request_count(), 400)
          << "backend " << i;
      EXPECT_FALSE(found) << "backend " << i;
      found = true;
    }
  }
  EXPECT_TRUE(found);
}

TEST_P(RingHashTest, HashKeysInEds) {
  grpc_core::testing::ScopedEnvVar env(
      "GRPC_XDS_ENDPOINT_HASH_KEY_BACKWARD_COMPAT", "false");
  CreateAndStartBackends(4);
  auto cluster = default_cluster_;
  cluster.set_lb_policy(Cluster::RING_HASH);
  balancer_->ads_service()->SetCdsResource(cluster);
  auto new_route_config = default_route_config_;
  auto* route = new_route_config.mutable_virtual_hosts(0)->mutable_routes(0);
  auto* hash_policy = route->mutable_route()->add_hash_policy();
  hash_policy->mutable_header()->set_header_name("address_hash");
  SetListenerAndRouteConfiguration(balancer_.get(), default_listener_,
                                   new_route_config);
  EdsResourceArgs args(
      {{"locality0",
        {
            CreateEndpoint(0,

                           ::envoy::config::core::v3::HealthStatus::UNKNOWN,
                           1, {},
                           "",
                           {{"envoy.lb", "{\"hash_key\":\"foo\"}"}}),
            CreateEndpoint(1,

                           ::envoy::config::core::v3::HealthStatus::UNKNOWN,
                           1, {},
                           "",
                           {{"envoy.lb", "{\"hash_key\":\"bar\"}"}}),
            CreateEndpoint(2,

                           ::envoy::config::core::v3::HealthStatus::UNKNOWN,
                           1, {},
                           "",
                           {{"envoy.lb", "{\"hash_key\":\"baz\"}"}}),
            CreateEndpoint(3,

                           ::envoy::config::core::v3::HealthStatus::UNKNOWN,
                           1, {},
                           "",
                           {{"envoy.lb", "{\"hash_key\":\"quux\"}"}}),
        }}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  std::vector<std::pair<std::string, std::string>> metadata = {
      {"address_hash", "foo_0"}};
  std::vector<std::pair<std::string, std::string>> metadata1 = {
      {"address_hash", "bar_0"}};
  std::vector<std::pair<std::string, std::string>> metadata2 = {
      {"address_hash", "baz_0"}};
  std::vector<std::pair<std::string, std::string>> metadata3 = {
      {"address_hash", "quux_0"}};
  const auto rpc_options =
      RpcOptions().set_metadata(std::move(metadata)).set_timeout_ms(5000);
  const auto rpc_options1 =
      RpcOptions().set_metadata(std::move(metadata1)).set_timeout_ms(5000);
  const auto rpc_options2 =
      RpcOptions().set_metadata(std::move(metadata2)).set_timeout_ms(5000);
  const auto rpc_options3 =
      RpcOptions().set_metadata(std::move(metadata3)).set_timeout_ms(5000);
  WaitForBackend(DEBUG_LOCATION, 0, nullptr,
                 WaitForBackendOptions(), rpc_options);
  WaitForBackend(DEBUG_LOCATION, 1, nullptr,
                 WaitForBackendOptions(), rpc_options1);
  WaitForBackend(DEBUG_LOCATION, 2, nullptr,
                 WaitForBackendOptions(), rpc_options2);
  WaitForBackend(DEBUG_LOCATION, 3, nullptr,
                 WaitForBackendOptions(), rpc_options3);
  CheckRpcSendOk(DEBUG_LOCATION, 100, rpc_options);
  CheckRpcSendOk(DEBUG_LOCATION, 100, rpc_options1);
  CheckRpcSendOk(DEBUG_LOCATION, 100, rpc_options2);
  CheckRpcSendOk(DEBUG_LOCATION, 100, rpc_options3);
  for (size_t i = 0; i < backends_.size(); ++i) {
    EXPECT_EQ(100, backends_[i]->backend_service()->request_count());
  }
}

TEST_P(RingHashTest, HashKeysInEdsNotEnabled) {
  CreateAndStartBackends(4);
  auto cluster = default_cluster_;
  cluster.set_lb_policy(Cluster::RING_HASH);
  balancer_->ads_service()->SetCdsResource(cluster);
  auto new_route_config = default_route_config_;
  auto* route = new_route_config.mutable_virtual_hosts(0)->mutable_routes(0);
  auto* hash_policy = route->mutable_route()->add_hash_policy();
  hash_policy->mutable_header()->set_header_name("address_hash");
  SetListenerAndRouteConfiguration(balancer_.get(), default_listener_,
                                   new_route_config);
  EdsResourceArgs args(
      {{"locality0",
        {
            CreateEndpoint(0,

                           ::envoy::config::core::v3::HealthStatus::UNKNOWN,
                           1, {},
                           "",
                           {{"envoy.lb", "{\"hash_key\":\"foo\"}"}}),
            CreateEndpoint(1,

                           ::envoy::config::core::v3::HealthStatus::UNKNOWN,
                           1, {},
                           "",
                           {{"envoy.lb", "{\"hash_key\":\"bar\"}"}}),
            CreateEndpoint(2,

                           ::envoy::config::core::v3::HealthStatus::UNKNOWN,
                           1, {},
                           "",
                           {{"envoy.lb", "{\"hash_key\":\"baz\"}"}}),
            CreateEndpoint(3,

                           ::envoy::config::core::v3::HealthStatus::UNKNOWN,
                           1, {},
                           "",
                           {{"envoy.lb", "{\"hash_key\":\"quux\"}"}}),
        }}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  std::vector<std::pair<std::string, std::string>> metadata = {
      {"address_hash", CreateMetadataValueThatHashesToBackend(0)}};
  std::vector<std::pair<std::string, std::string>> metadata1 = {
      {"address_hash", CreateMetadataValueThatHashesToBackend(1)}};
  std::vector<std::pair<std::string, std::string>> metadata2 = {
      {"address_hash", CreateMetadataValueThatHashesToBackend(2)}};
  std::vector<std::pair<std::string, std::string>> metadata3 = {
      {"address_hash", CreateMetadataValueThatHashesToBackend(3)}};
  const auto rpc_options =
      RpcOptions().set_metadata(std::move(metadata)).set_timeout_ms(5000);
  const auto rpc_options1 =
      RpcOptions().set_metadata(std::move(metadata1)).set_timeout_ms(5000);
  const auto rpc_options2 =
      RpcOptions().set_metadata(std::move(metadata2)).set_timeout_ms(5000);
  const auto rpc_options3 =
      RpcOptions().set_metadata(std::move(metadata3)).set_timeout_ms(5000);
  WaitForBackend(DEBUG_LOCATION, 0, nullptr,
                 WaitForBackendOptions(), rpc_options);
  WaitForBackend(DEBUG_LOCATION, 1, nullptr,
                 WaitForBackendOptions(), rpc_options1);
  WaitForBackend(DEBUG_LOCATION, 2, nullptr,
                 WaitForBackendOptions(), rpc_options2);
  WaitForBackend(DEBUG_LOCATION, 3, nullptr,
                 WaitForBackendOptions(), rpc_options3);
  CheckRpcSendOk(DEBUG_LOCATION, 100, rpc_options);
  CheckRpcSendOk(DEBUG_LOCATION, 100, rpc_options1);
  CheckRpcSendOk(DEBUG_LOCATION, 100, rpc_options2);
  CheckRpcSendOk(DEBUG_LOCATION, 100, rpc_options3);
  for (size_t i = 0; i < backends_.size(); ++i) {
    EXPECT_EQ(100, backends_[i]->backend_service()->request_count());
  }
}

TEST_P(RingHashTest, NoHashPolicy) {
  CreateAndStartBackends(2);
  const double kDistribution50Percent = 0.5;
  const double kErrorTolerance = 0.05;
  const uint32_t kRpcTimeoutMs = 10000;
  const size_t kNumRpcs =
      ComputeIdealNumRpcs(kDistribution50Percent, kErrorTolerance);
  auto cluster = default_cluster_;

  cluster.mutable_ring_hash_lb_config()->mutable_minimum_ring_size()->set_value(
      100000);
  cluster.set_lb_policy(Cluster::RING_HASH);
  balancer_->ads_service()->SetCdsResource(cluster);
  EdsResourceArgs args({{"locality0", CreateEndpointsForBackends()}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  WaitForAllBackends(DEBUG_LOCATION, 0, 2, nullptr,
                     WaitForBackendOptions().set_timeout_ms(kRpcTimeoutMs),
                     RpcOptions().set_timeout_ms(kRpcTimeoutMs));
  CheckRpcSendOk(DEBUG_LOCATION, kNumRpcs);
  const int request_count_1 = backends_[0]->backend_service()->request_count();
  const int request_count_2 = backends_[1]->backend_service()->request_count();
  EXPECT_THAT(static_cast<double>(request_count_1) / kNumRpcs,
              ::testing::DoubleNear(kDistribution50Percent, kErrorTolerance));
  EXPECT_THAT(static_cast<double>(request_count_2) / kNumRpcs,
              ::testing::DoubleNear(kDistribution50Percent, kErrorTolerance));
}

TEST_P(RingHashTest, EndpointWeights) {
  CreateAndStartBackends(3);
  const double kDistribution50Percent = 0.5;
  const double kDistribution25Percent = 0.25;
  const double kErrorTolerance = 0.05;
  const uint32_t kRpcTimeoutMs = 10000;
  const size_t kNumRpcs =
      ComputeIdealNumRpcs(kDistribution50Percent, kErrorTolerance);
  auto cluster = default_cluster_;

  cluster.mutable_ring_hash_lb_config()->mutable_minimum_ring_size()->set_value(
      100000);
  cluster.set_lb_policy(Cluster::RING_HASH);
  balancer_->ads_service()->SetCdsResource(cluster);

  EdsResourceArgs args(
      {{"locality0",
        {CreateEndpoint(0, ::envoy::config::core::v3::HealthStatus::UNKNOWN, 0),
         CreateEndpoint(1, ::envoy::config::core::v3::HealthStatus::UNKNOWN, 1),
         CreateEndpoint(2, ::envoy::config::core::v3::HealthStatus::UNKNOWN,
                        2)}}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  WaitForAllBackends(DEBUG_LOCATION, 0, 3, nullptr,
                     WaitForBackendOptions().set_timeout_ms(kRpcTimeoutMs),
                     RpcOptions().set_timeout_ms(kRpcTimeoutMs));
  CheckRpcSendOk(DEBUG_LOCATION, kNumRpcs);

  const int request_count_0 = backends_[0]->backend_service()->request_count();
  const int request_count_1 = backends_[1]->backend_service()->request_count();
  const int request_count_2 = backends_[2]->backend_service()->request_count();
  EXPECT_THAT(static_cast<double>(request_count_0) / kNumRpcs,
              ::testing::DoubleNear(kDistribution25Percent, kErrorTolerance));
  EXPECT_THAT(static_cast<double>(request_count_1) / kNumRpcs,
              ::testing::DoubleNear(kDistribution25Percent, kErrorTolerance));
  EXPECT_THAT(static_cast<double>(request_count_2) / kNumRpcs,
              ::testing::DoubleNear(kDistribution50Percent, kErrorTolerance));
}

TEST_P(RingHashTest, ContinuesPastTerminalPolicyThatDoesNotProduceResult) {
  CreateAndStartBackends(2);
  auto cluster = default_cluster_;
  cluster.set_lb_policy(Cluster::RING_HASH);
  balancer_->ads_service()->SetCdsResource(cluster);
  auto new_route_config = default_route_config_;
  auto* route = new_route_config.mutable_virtual_hosts(0)->mutable_routes(0);
  auto* hash_policy = route->mutable_route()->add_hash_policy();
  hash_policy->mutable_header()->set_header_name("header_not_present");
  hash_policy->set_terminal(true);
  auto* hash_policy2 = route->mutable_route()->add_hash_policy();
  hash_policy2->mutable_header()->set_header_name("address_hash");
  SetListenerAndRouteConfiguration(balancer_.get(), default_listener_,
                                   new_route_config);
  EdsResourceArgs args({{"locality0", CreateEndpointsForBackends()}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));
  std::vector<std::pair<std::string, std::string>> metadata = {
      {"address_hash", CreateMetadataValueThatHashesToBackend(0)}};
  const auto rpc_options =
      RpcOptions().set_metadata(std::move(metadata)).set_timeout_ms(5000);
  CheckRpcSendOk(DEBUG_LOCATION, 100, rpc_options);
  EXPECT_EQ(backends_[0]->backend_service()->request_count(), 100);
  EXPECT_EQ(backends_[1]->backend_service()->request_count(), 0);
}

TEST_P(RingHashTest, HashOnHeaderThatIsNotPresent) {
  CreateAndStartBackends(2);
  const double kDistribution50Percent = 0.5;
  const double kErrorTolerance = 0.05;
  const uint32_t kRpcTimeoutMs = 10000;
  const size_t kNumRpcs =
      ComputeIdealNumRpcs(kDistribution50Percent, kErrorTolerance);
  auto cluster = default_cluster_;

  cluster.mutable_ring_hash_lb_config()->mutable_minimum_ring_size()->set_value(
      100000);
  cluster.set_lb_policy(Cluster::RING_HASH);
  balancer_->ads_service()->SetCdsResource(cluster);
  auto new_route_config = default_route_config_;
  auto* route = new_route_config.mutable_virtual_hosts(0)->mutable_routes(0);
  auto* hash_policy = route->mutable_route()->add_hash_policy();
  hash_policy->mutable_header()->set_header_name("header_not_present");
  SetListenerAndRouteConfiguration(balancer_.get(), default_listener_,
                                   new_route_config);
  EdsResourceArgs args({{"locality0", CreateEndpointsForBackends()}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));
  std::vector<std::pair<std::string, std::string>> metadata = {
      {"unmatched_header", absl::StrFormat("%" PRIu32, rand())},
  };
  const auto rpc_options = RpcOptions().set_metadata(std::move(metadata));

  WaitForAllBackends(DEBUG_LOCATION, 0, 2, nullptr,
                     WaitForBackendOptions().set_timeout_ms(kRpcTimeoutMs),
                     RpcOptions().set_timeout_ms(kRpcTimeoutMs));
  CheckRpcSendOk(DEBUG_LOCATION, kNumRpcs, rpc_options);
  const int request_count_1 = backends_[0]->backend_service()->request_count();
  const int request_count_2 = backends_[1]->backend_service()->request_count();
  EXPECT_THAT(static_cast<double>(request_count_1) / kNumRpcs,
              ::testing::DoubleNear(kDistribution50Percent, kErrorTolerance));
  EXPECT_THAT(static_cast<double>(request_count_2) / kNumRpcs,
              ::testing::DoubleNear(kDistribution50Percent, kErrorTolerance));
}

TEST_P(RingHashTest, UnsupportedHashPolicyDefaultToRandomHashing) {
  CreateAndStartBackends(2);
  const double kDistribution50Percent = 0.5;
  const double kErrorTolerance = 0.05;
  const uint32_t kRpcTimeoutMs = 10000;
  const size_t kNumRpcs =
      ComputeIdealNumRpcs(kDistribution50Percent, kErrorTolerance);
  auto cluster = default_cluster_;

  cluster.mutable_ring_hash_lb_config()->mutable_minimum_ring_size()->set_value(
      100000);
  cluster.set_lb_policy(Cluster::RING_HASH);
  balancer_->ads_service()->SetCdsResource(cluster);
  auto new_route_config = default_route_config_;
  auto* route = new_route_config.mutable_virtual_hosts(0)->mutable_routes(0);
  auto* hash_policy_unsupported_1 = route->mutable_route()->add_hash_policy();
  hash_policy_unsupported_1->mutable_cookie()->set_name("cookie");
  auto* hash_policy_unsupported_2 = route->mutable_route()->add_hash_policy();
  hash_policy_unsupported_2->mutable_connection_properties()->set_source_ip(
      true);
  auto* hash_policy_unsupported_3 = route->mutable_route()->add_hash_policy();
  hash_policy_unsupported_3->mutable_query_parameter()->set_name(
      "query_parameter");
  SetListenerAndRouteConfiguration(balancer_.get(), default_listener_,
                                   new_route_config);
  EdsResourceArgs args({{"locality0", CreateEndpointsForBackends()}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  WaitForAllBackends(DEBUG_LOCATION, 0, 2, nullptr,
                     WaitForBackendOptions().set_timeout_ms(kRpcTimeoutMs),
                     RpcOptions().set_timeout_ms(kRpcTimeoutMs));
  CheckRpcSendOk(DEBUG_LOCATION, kNumRpcs);
  const int request_count_1 = backends_[0]->backend_service()->request_count();
  const int request_count_2 = backends_[1]->backend_service()->request_count();
  EXPECT_THAT(static_cast<double>(request_count_1) / kNumRpcs,
              ::testing::DoubleNear(kDistribution50Percent, kErrorTolerance));
  EXPECT_THAT(static_cast<double>(request_count_2) / kNumRpcs,
              ::testing::DoubleNear(kDistribution50Percent, kErrorTolerance));
}

TEST_P(RingHashTest, RandomHashingDistributionAccordingToEndpointWeight) {
  CreateAndStartBackends(2);
  const size_t kWeight1 = 1;
  const size_t kWeight2 = 2;
  const size_t kWeightTotal = kWeight1 + kWeight2;
  const double kWeight33Percent = static_cast<double>(kWeight1) / kWeightTotal;
  const double kWeight66Percent = static_cast<double>(kWeight2) / kWeightTotal;
  const double kErrorTolerance = 0.05;
  const uint32_t kRpcTimeoutMs = 10000;
  const size_t kNumRpcs =
      ComputeIdealNumRpcs(kWeight33Percent, kErrorTolerance);
  auto cluster = default_cluster_;

  cluster.mutable_ring_hash_lb_config()->mutable_minimum_ring_size()->set_value(
      100000);
  cluster.set_lb_policy(Cluster::RING_HASH);
  balancer_->ads_service()->SetCdsResource(cluster);
  EdsResourceArgs args({{"locality0",
                         {CreateEndpoint(0, HealthStatus::UNKNOWN, 1),
                          CreateEndpoint(1, HealthStatus::UNKNOWN, 2)}}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  WaitForAllBackends(DEBUG_LOCATION, 0, 2, nullptr,
                     WaitForBackendOptions().set_timeout_ms(kRpcTimeoutMs),
                     RpcOptions().set_timeout_ms(kRpcTimeoutMs));
  CheckRpcSendOk(DEBUG_LOCATION, kNumRpcs);
  const int weight_33_request_count =
      backends_[0]->backend_service()->request_count();
  const int weight_66_request_count =
      backends_[1]->backend_service()->request_count();
  EXPECT_THAT(static_cast<double>(weight_33_request_count) / kNumRpcs,
              ::testing::DoubleNear(kWeight33Percent, kErrorTolerance));
  EXPECT_THAT(static_cast<double>(weight_66_request_count) / kNumRpcs,
              ::testing::DoubleNear(kWeight66Percent, kErrorTolerance));
}

TEST_P(RingHashTest,
       RandomHashingDistributionAccordingToLocalityAndEndpointWeight) {
  CreateAndStartBackends(2);
  const size_t kWeight1 = 1 * 1;
  const size_t kWeight2 = 2 * 2;
  const size_t kWeightTotal = kWeight1 + kWeight2;
  const double kWeight20Percent = static_cast<double>(kWeight1) / kWeightTotal;
  const double kWeight80Percent = static_cast<double>(kWeight2) / kWeightTotal;
  const double kErrorTolerance = 0.05;
  const uint32_t kRpcTimeoutMs = 10000;
  const size_t kNumRpcs =
      ComputeIdealNumRpcs(kWeight20Percent, kErrorTolerance);
  auto cluster = default_cluster_;

  cluster.mutable_ring_hash_lb_config()->mutable_minimum_ring_size()->set_value(
      100000);
  cluster.set_lb_policy(Cluster::RING_HASH);
  balancer_->ads_service()->SetCdsResource(cluster);
  EdsResourceArgs args(
      {{"locality0", {CreateEndpoint(0, HealthStatus::UNKNOWN, 1)}, 1},
       {"locality1", {CreateEndpoint(1, HealthStatus::UNKNOWN, 2)}, 2}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  WaitForAllBackends(DEBUG_LOCATION, 0, 2, nullptr,
                     WaitForBackendOptions().set_timeout_ms(kRpcTimeoutMs),
                     RpcOptions().set_timeout_ms(kRpcTimeoutMs));
  CheckRpcSendOk(DEBUG_LOCATION, kNumRpcs);
  const int weight_20_request_count =
      backends_[0]->backend_service()->request_count();
  const int weight_80_request_count =
      backends_[1]->backend_service()->request_count();
  EXPECT_THAT(static_cast<double>(weight_20_request_count) / kNumRpcs,
              ::testing::DoubleNear(kWeight20Percent, kErrorTolerance));
  EXPECT_THAT(static_cast<double>(weight_80_request_count) / kNumRpcs,
              ::testing::DoubleNear(kWeight80Percent, kErrorTolerance));
}

TEST_P(RingHashTest, FixedHashingTerminalPolicy) {
  CreateAndStartBackends(2);
  auto cluster = default_cluster_;
  cluster.set_lb_policy(Cluster::RING_HASH);
  balancer_->ads_service()->SetCdsResource(cluster);
  auto new_route_config = default_route_config_;
  auto* route = new_route_config.mutable_virtual_hosts(0)->mutable_routes(0);
  auto* hash_policy = route->mutable_route()->add_hash_policy();
  hash_policy->mutable_header()->set_header_name("fixed_string");
  hash_policy->set_terminal(true);
  auto* hash_policy_to_be_ignored = route->mutable_route()->add_hash_policy();
  hash_policy_to_be_ignored->mutable_header()->set_header_name("random_string");
  SetListenerAndRouteConfiguration(balancer_.get(), default_listener_,
                                   new_route_config);
  EdsResourceArgs args({{"locality0", CreateEndpointsForBackends()}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));
  std::vector<std::pair<std::string, std::string>> metadata = {
      {"fixed_string", "fixed_value"},
      {"random_string", absl::StrFormat("%" PRIu32, rand())},
  };
  const auto rpc_options =
      RpcOptions().set_metadata(std::move(metadata)).set_timeout_ms(5000);
  CheckRpcSendOk(DEBUG_LOCATION, 100, rpc_options);
  bool found = false;
  for (size_t i = 0; i < backends_.size(); ++i) {
    if (backends_[i]->backend_service()->request_count() > 0) {
      EXPECT_EQ(backends_[i]->backend_service()->request_count(), 100)
          << "backend " << i;
      EXPECT_FALSE(found) << "backend " << i;
      found = true;
    }
  }
  EXPECT_TRUE(found);
}

TEST_P(RingHashTest, IdleToReady) {
  CreateAndStartBackends(1);
  auto cluster = default_cluster_;
  cluster.set_lb_policy(Cluster::RING_HASH);
  balancer_->ads_service()->SetCdsResource(cluster);
  auto new_route_config = default_route_config_;
  auto* route = new_route_config.mutable_virtual_hosts(0)->mutable_routes(0);
  auto* hash_policy = route->mutable_route()->add_hash_policy();
  hash_policy->mutable_filter_state()->set_key("io.grpc.channel_id");
  SetListenerAndRouteConfiguration(balancer_.get(), default_listener_,
                                   new_route_config);
  EdsResourceArgs args({{"locality0", CreateEndpointsForBackends()}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));
  EXPECT_EQ(GRPC_CHANNEL_IDLE, channel_->GetState(false));
  CheckRpcSendOk(DEBUG_LOCATION, 1, RpcOptions().set_timeout_ms(5000));
  EXPECT_EQ(GRPC_CHANNEL_READY, channel_->GetState(false));
}

TEST_P(RingHashTest, ContinuesConnectingWithoutPicks) {

  CreateAndStartBackends(1);
  auto non_existent_endpoint = MakeNonExistentEndpoint();
  EdsResourceArgs args(
      {{"locality0", {non_existent_endpoint, CreateEndpoint(0)}}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  auto cluster = default_cluster_;
  cluster.set_lb_policy(Cluster::RING_HASH);
  balancer_->ads_service()->SetCdsResource(cluster);

  auto new_route_config = default_route_config_;
  auto* route = new_route_config.mutable_virtual_hosts(0)->mutable_routes(0);
  auto* hash_policy = route->mutable_route()->add_hash_policy();
  hash_policy->mutable_header()->set_header_name("address_hash");
  SetListenerAndRouteConfiguration(balancer_.get(), default_listener_,
                                   new_route_config);

  ConnectionAttemptInjector injector;
  auto hold = injector.AddHold(non_existent_endpoint.port);

  LongRunningRpc rpc;
  std::vector<std::pair<std::string, std::string>> metadata = {
      {"address_hash",
       CreateMetadataValueThatHashesToBackendPort(non_existent_endpoint.port)}};
  rpc.StartRpc(stub_.get(), RpcOptions().set_timeout_ms(0).set_metadata(
                                std::move(metadata)));

  hold->Wait();
  rpc.CancelRpc();
  EXPECT_EQ(StatusCode::CANCELLED, rpc.GetStatus().error_code());
  hold->Resume();

  EXPECT_TRUE(channel_->WaitForConnected(grpc_timeout_seconds_to_deadline(5)));

  EXPECT_EQ(0UL, backends_[0]->backend_service()->request_count());
}

TEST_P(RingHashTest, TransientFailureCheckNextOne) {
  CreateAndStartBackends(1);
  auto cluster = default_cluster_;
  cluster.set_lb_policy(Cluster::RING_HASH);
  balancer_->ads_service()->SetCdsResource(cluster);
  auto new_route_config = default_route_config_;
  auto* route = new_route_config.mutable_virtual_hosts(0)->mutable_routes(0);
  auto* hash_policy = route->mutable_route()->add_hash_policy();
  hash_policy->mutable_header()->set_header_name("address_hash");
  SetListenerAndRouteConfiguration(balancer_.get(), default_listener_,
                                   new_route_config);
  std::vector<EdsResourceArgs::Endpoint> endpoints;
  const int unused_port = grpc_pick_unused_port_or_die();
  endpoints.emplace_back(unused_port);
  endpoints.emplace_back(backends_[0]->port());
  EdsResourceArgs args({{"locality0", std::move(endpoints)}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));
  std::vector<std::pair<std::string, std::string>> metadata = {
      {"address_hash",
       CreateMetadataValueThatHashesToBackendPort(unused_port)}};
  const auto rpc_options =
      RpcOptions().set_metadata(std::move(metadata)).set_timeout_ms(5000);
  WaitForBackend(DEBUG_LOCATION, 0, nullptr,
                 WaitForBackendOptions(), rpc_options);
  CheckRpcSendOk(DEBUG_LOCATION, 100, rpc_options);
}

TEST_P(RingHashTest, SwitchToLowerPriorityAndThenBack) {
  CreateAndStartBackends(2);
  auto cluster = default_cluster_;
  cluster.set_lb_policy(Cluster::RING_HASH);
  balancer_->ads_service()->SetCdsResource(cluster);
  auto new_route_config = default_route_config_;
  auto* route = new_route_config.mutable_virtual_hosts(0)->mutable_routes(0);
  auto* hash_policy = route->mutable_route()->add_hash_policy();
  hash_policy->mutable_header()->set_header_name("address_hash");
  SetListenerAndRouteConfiguration(balancer_.get(), default_listener_,
                                   new_route_config);
  EdsResourceArgs args({
      {"locality0", CreateEndpointsForBackends(0, 1), kDefaultLocalityWeight,
       0},
      {"locality1", CreateEndpointsForBackends(1, 2), kDefaultLocalityWeight,
       1},
  });
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));
  std::vector<std::pair<std::string, std::string>> metadata = {
      {"address_hash", CreateMetadataValueThatHashesToBackend(0)}};
  const auto rpc_options =
      RpcOptions().set_metadata(std::move(metadata)).set_timeout_ms(5000);
  WaitForBackend(DEBUG_LOCATION, 0, nullptr,
                 WaitForBackendOptions(), rpc_options);
  backends_[0]->StopListeningAndSendGoaways();
  WaitForBackend(DEBUG_LOCATION, 1, nullptr,
                 WaitForBackendOptions(), rpc_options);
  ShutdownBackend(0);
  StartBackend(0);
  WaitForBackend(DEBUG_LOCATION, 0, nullptr,
                 WaitForBackendOptions(), rpc_options);
  CheckRpcSendOk(DEBUG_LOCATION, 100, rpc_options);
  EXPECT_EQ(100, backends_[0]->backend_service()->request_count());
  EXPECT_EQ(0, backends_[1]->backend_service()->request_count());
}

TEST_P(RingHashTest, ReattemptWhenAllEndpointsUnreachable) {
  CreateAndStartBackends(1);
  const uint32_t kConnectionTimeoutMilliseconds = 5000;
  auto cluster = default_cluster_;
  cluster.set_lb_policy(Cluster::RING_HASH);
  balancer_->ads_service()->SetCdsResource(cluster);
  auto new_route_config = default_route_config_;
  auto* route = new_route_config.mutable_virtual_hosts(0)->mutable_routes(0);
  auto* hash_policy = route->mutable_route()->add_hash_policy();
  hash_policy->mutable_header()->set_header_name("address_hash");
  SetListenerAndRouteConfiguration(balancer_.get(), default_listener_,
                                   new_route_config);
  EdsResourceArgs args(
      {{"locality0", {MakeNonExistentEndpoint(), CreateEndpoint(0)}}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));
  std::vector<std::pair<std::string, std::string>> metadata = {
      {"address_hash", CreateMetadataValueThatHashesToBackend(0)}};
  EXPECT_EQ(GRPC_CHANNEL_IDLE, channel_->GetState(false));
  ShutdownBackend(0);
  CheckRpcSendFailure(
      DEBUG_LOCATION, StatusCode::UNAVAILABLE,
      MakeConnectionFailureRegex(
          "ring hash cannot find a connected endpoint; first failure: "),
      RpcOptions().set_metadata(std::move(metadata)));
  StartBackend(0);

  EXPECT_TRUE(channel_->WaitForConnected(
      grpc_timeout_milliseconds_to_deadline(kConnectionTimeoutMilliseconds)));
}

TEST_P(RingHashTest, TransientFailureSkipToAvailableReady) {
  CreateBackends(2);
  const uint32_t kConnectionTimeoutMilliseconds = 5000;
  auto cluster = default_cluster_;
  cluster.set_lb_policy(Cluster::RING_HASH);
  balancer_->ads_service()->SetCdsResource(cluster);
  auto new_route_config = default_route_config_;
  auto* route = new_route_config.mutable_virtual_hosts(0)->mutable_routes(0);
  auto* hash_policy = route->mutable_route()->add_hash_policy();
  hash_policy->mutable_header()->set_header_name("address_hash");
  SetListenerAndRouteConfiguration(balancer_.get(), default_listener_,
                                   new_route_config);

  EdsResourceArgs args({
      {"locality0",
       {CreateEndpoint(0), CreateEndpoint(1), MakeNonExistentEndpoint(),
        MakeNonExistentEndpoint()}},
  });
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));
  std::vector<std::pair<std::string, std::string>> metadata = {
      {"address_hash", CreateMetadataValueThatHashesToBackend(0)}};
  const auto rpc_options = RpcOptions()
                               .set_metadata(std::move(metadata))
                               .set_timeout_ms(kConnectionTimeoutMilliseconds);
  EXPECT_EQ(GRPC_CHANNEL_IDLE, channel_->GetState(false));
  LOG(INFO) << "=== SENDING FIRST RPC ===";
  CheckRpcSendFailure(
      DEBUG_LOCATION, StatusCode::UNAVAILABLE,
      MakeConnectionFailureRegex(
          "ring hash cannot find a connected endpoint; first failure: "),
      rpc_options);
  LOG(INFO) << "=== DONE WITH FIRST RPC ===";
  EXPECT_EQ(GRPC_CHANNEL_TRANSIENT_FAILURE, channel_->GetState(false));

  LOG(INFO) << "=== STARTING BACKEND 0 ===";
  StartBackend(0);
  LOG(INFO) << "=== WAITING FOR CHANNEL TO BECOME READY ===";
  EXPECT_TRUE(channel_->WaitForConnected(
      grpc_timeout_milliseconds_to_deadline(kConnectionTimeoutMilliseconds)));

  LOG(INFO) << "=== WAITING FOR BACKEND 0 ===";
  WaitForBackend(DEBUG_LOCATION, 0, nullptr,
                 WaitForBackendOptions(), rpc_options);
  EXPECT_EQ(GRPC_CHANNEL_READY, channel_->GetState(false));

  LOG(INFO) << "=== SHUTTING DOWN BACKEND 0 ===";
  ShutdownBackend(0);
  LOG(INFO) << "=== WAITING FOR STATE CHANGE ===";
  EXPECT_TRUE(channel_->WaitForStateChange(
      GRPC_CHANNEL_READY,
      grpc_timeout_milliseconds_to_deadline(kConnectionTimeoutMilliseconds)));
  EXPECT_EQ(GRPC_CHANNEL_TRANSIENT_FAILURE, channel_->GetState(false));
  LOG(INFO) << "=== SENDING SECOND RPC ===";
  CheckRpcSendFailure(
      DEBUG_LOCATION, StatusCode::UNAVAILABLE,
      MakeConnectionFailureRegex(
          "ring hash cannot find a connected endpoint; first failure: "),
      rpc_options);
  LOG(INFO) << "=== STARTING BACKEND 1 ===";
  StartBackend(1);
  LOG(INFO) << "=== WAITING FOR CHANNEL TO BECOME READY ===";
  EXPECT_TRUE(channel_->WaitForConnected(
      grpc_timeout_milliseconds_to_deadline(kConnectionTimeoutMilliseconds)));
  LOG(INFO) << "=== WAITING FOR BACKEND 1 ===";
  WaitForBackend(DEBUG_LOCATION, 1, nullptr,
                 WaitForBackendOptions(), rpc_options);
  LOG(INFO) << "=== DONE ===";
}

TEST_P(RingHashTest, ReattemptWhenGoingFromTransientFailureToIdle) {
  CreateAndStartBackends(1);
  const uint32_t kConnectionTimeoutMilliseconds = 5000;
  auto cluster = default_cluster_;
  cluster.set_lb_policy(Cluster::RING_HASH);
  balancer_->ads_service()->SetCdsResource(cluster);
  auto new_route_config = default_route_config_;
  SetListenerAndRouteConfiguration(balancer_.get(), default_listener_,
                                   new_route_config);

  EdsResourceArgs args(
      {{"locality0", std::vector<EdsResourceArgs::Endpoint>()}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));
  EXPECT_EQ(GRPC_CHANNEL_IDLE, channel_->GetState(false));

  CheckRpcSendFailure(
      DEBUG_LOCATION, StatusCode::UNAVAILABLE,
      "empty address list: EDS resource eds_service_name: contains empty "
      "localities: \\[\\{region=\"xds_default_locality_region\", "
      "zone=\"xds_default_locality_zone\", sub_zone=\"locality0\"\\}\\]",
      RpcOptions().set_timeout_ms(kConnectionTimeoutMilliseconds));
  EXPECT_EQ(GRPC_CHANNEL_TRANSIENT_FAILURE, channel_->GetState(false));

  args = EdsResourceArgs({{"locality0", CreateEndpointsForBackends()}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  CheckRpcSendOk(DEBUG_LOCATION, 1,
                 RpcOptions()
                     .set_timeout_ms(kConnectionTimeoutMilliseconds)
                     .set_wait_for_ready(true));
  EXPECT_EQ(GRPC_CHANNEL_READY, channel_->GetState(false));
}

TEST_P(RingHashTest, UnsupportedHashPolicyUntilChannelIdHashing) {
  CreateAndStartBackends(2);
  auto cluster = default_cluster_;
  cluster.set_lb_policy(Cluster::RING_HASH);
  balancer_->ads_service()->SetCdsResource(cluster);
  auto new_route_config = default_route_config_;
  auto* route = new_route_config.mutable_virtual_hosts(0)->mutable_routes(0);
  auto* hash_policy_unsupported_1 = route->mutable_route()->add_hash_policy();
  hash_policy_unsupported_1->mutable_cookie()->set_name("cookie");
  auto* hash_policy_unsupported_2 = route->mutable_route()->add_hash_policy();
  hash_policy_unsupported_2->mutable_connection_properties()->set_source_ip(
      true);
  auto* hash_policy_unsupported_3 = route->mutable_route()->add_hash_policy();
  hash_policy_unsupported_3->mutable_query_parameter()->set_name(
      "query_parameter");
  auto* hash_policy = route->mutable_route()->add_hash_policy();
  hash_policy->mutable_filter_state()->set_key("io.grpc.channel_id");
  SetListenerAndRouteConfiguration(balancer_.get(), default_listener_,
                                   new_route_config);
  EdsResourceArgs args({{"locality0", CreateEndpointsForBackends()}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));
  CheckRpcSendOk(DEBUG_LOCATION, 100, RpcOptions().set_timeout_ms(5000));
  bool found = false;
  for (size_t i = 0; i < backends_.size(); ++i) {
    if (backends_[i]->backend_service()->request_count() > 0) {
      EXPECT_EQ(backends_[i]->backend_service()->request_count(), 100)
          << "backend " << i;
      EXPECT_FALSE(found) << "backend " << i;
      found = true;
    }
  }
  EXPECT_TRUE(found);
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
