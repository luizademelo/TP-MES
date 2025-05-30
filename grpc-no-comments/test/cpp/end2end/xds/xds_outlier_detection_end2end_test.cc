// Copyright 2017 gRPC authors.

#include <chrono>
#include <string>
#include <thread>
#include <vector>

#include "absl/log/check.h"
#include "envoy/config/cluster/v3/cluster.pb.h"
#include "envoy/config/cluster/v3/outlier_detection.pb.h"
#include "envoy/extensions/filters/http/fault/v3/fault.pb.h"
#include "envoy/extensions/filters/http/router/v3/router.pb.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "src/core/client_channel/backup_poller.h"
#include "src/core/config/config_vars.h"
#include "test/core/test_util/resolve_localhost_ip46.h"
#include "test/cpp/end2end/xds/xds_end2end_test_lib.h"

namespace grpc {
namespace testing {
namespace {

class OutlierDetectionTest : public XdsEnd2endTest {
 protected:
  std::string CreateMetadataValueThatHashesToBackend(int index) {
    return absl::StrCat(grpc_core::LocalIp(), ":", backends_[index]->port(),
                        "_0");
  }
};

INSTANTIATE_TEST_SUITE_P(XdsTest, OutlierDetectionTest,
                         ::testing::Values(XdsTestType()), &XdsTestType::Name);

TEST_P(OutlierDetectionTest, SuccessRateEjectionAndUnejection) {
  CreateAndStartBackends(2);
  auto cluster = default_cluster_;
  cluster.set_lb_policy(Cluster::RING_HASH);

  auto* outlier_detection = cluster.mutable_outlier_detection();
  SetProtoDuration(grpc_core::Duration::Seconds(1),
                   outlier_detection->mutable_interval());
  SetProtoDuration(grpc_core::Duration::Seconds(1),
                   outlier_detection->mutable_base_ejection_time());
  outlier_detection->mutable_success_rate_stdev_factor()->set_value(100);
  outlier_detection->mutable_enforcing_success_rate()->set_value(100);
  outlier_detection->mutable_success_rate_minimum_hosts()->set_value(1);
  outlier_detection->mutable_success_rate_request_volume()->set_value(1);
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
  const auto rpc_options = RpcOptions().set_metadata(metadata);
  const auto rpc_options1 = RpcOptions().set_metadata(std::move(metadata1));
  WaitForBackend(DEBUG_LOCATION, 0, nullptr,
                 WaitForBackendOptions(), rpc_options);
  WaitForBackend(DEBUG_LOCATION, 1, nullptr,
                 WaitForBackendOptions(), rpc_options1);

  CheckRpcSendFailure(DEBUG_LOCATION, StatusCode::CANCELLED, "",
                      RpcOptions()
                          .set_metadata(std::move(metadata))
                          .set_server_expected_error(StatusCode::CANCELLED));

  WaitForBackend(DEBUG_LOCATION, 1, nullptr,
                 WaitForBackendOptions().set_timeout_ms(
                     3000 * grpc_test_slowdown_factor()),
                 rpc_options);

  WaitForBackend(DEBUG_LOCATION, 0, nullptr,
                 WaitForBackendOptions().set_timeout_ms(
                     3000 * grpc_test_slowdown_factor()),
                 rpc_options);
}

TEST_P(OutlierDetectionTest, SuccessRateMaxPercent) {
  CreateAndStartBackends(4);
  auto cluster = default_cluster_;
  cluster.set_lb_policy(Cluster::RING_HASH);

  auto* outlier_detection = cluster.mutable_outlier_detection();
  SetProtoDuration(grpc_core::Duration::Seconds(1),
                   outlier_detection->mutable_interval());
  outlier_detection->mutable_success_rate_stdev_factor()->set_value(100);
  outlier_detection->mutable_enforcing_success_rate()->set_value(100);
  outlier_detection->mutable_success_rate_minimum_hosts()->set_value(1);
  outlier_detection->mutable_success_rate_request_volume()->set_value(1);
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
  const auto rpc_options = RpcOptions().set_metadata(metadata);
  const auto rpc_options1 = RpcOptions().set_metadata(metadata1);
  const auto rpc_options2 = RpcOptions().set_metadata(metadata2);
  const auto rpc_options3 = RpcOptions().set_metadata(metadata3);
  WaitForBackend(DEBUG_LOCATION, 0, nullptr,
                 WaitForBackendOptions(), rpc_options);
  WaitForBackend(DEBUG_LOCATION, 1, nullptr,
                 WaitForBackendOptions(), rpc_options1);
  WaitForBackend(DEBUG_LOCATION, 2, nullptr,
                 WaitForBackendOptions(), rpc_options2);
  WaitForBackend(DEBUG_LOCATION, 3, nullptr,
                 WaitForBackendOptions(), rpc_options3);

  CheckRpcSendFailure(DEBUG_LOCATION, StatusCode::CANCELLED, "",
                      RpcOptions()
                          .set_metadata(std::move(metadata))
                          .set_server_expected_error(StatusCode::CANCELLED));
  CheckRpcSendFailure(DEBUG_LOCATION, StatusCode::CANCELLED, "",
                      RpcOptions()
                          .set_metadata(std::move(metadata1))
                          .set_server_expected_error(StatusCode::CANCELLED));
  absl::Time deadline =
      absl::Now() + absl::Seconds(3) * grpc_test_slowdown_factor();
  while (true) {
    ResetBackendCounters();
    CheckRpcSendOk(DEBUG_LOCATION, 1, rpc_options);
    CheckRpcSendOk(DEBUG_LOCATION, 1, rpc_options1);
    if (!SeenAllBackends(0, 2)) {
      break;
    }
    EXPECT_LE(absl::Now(), deadline);
    if (absl::Now() >= deadline) break;
  }

  ResetBackendCounters();
  CheckRpcSendOk(DEBUG_LOCATION, 100, rpc_options);
  CheckRpcSendOk(DEBUG_LOCATION, 100, rpc_options1);
  CheckRpcSendOk(DEBUG_LOCATION, 100, rpc_options2);
  CheckRpcSendOk(DEBUG_LOCATION, 100, rpc_options3);
  size_t empty_load_backend_count = 0;
  size_t double_load_backend_count = 0;
  size_t regular_load_backend_count = 0;
  for (size_t i = 0; i < backends_.size(); ++i) {
    if (backends_[i]->backend_service()->request_count() == 0) {
      ++empty_load_backend_count;
    } else if (backends_[i]->backend_service()->request_count() == 200) {
      ++double_load_backend_count;
    } else if (backends_[i]->backend_service()->request_count() == 100) {
      ++regular_load_backend_count;
    } else {
      CHECK(1);
    }
  }
  EXPECT_EQ(1, empty_load_backend_count);
  EXPECT_EQ(1, double_load_backend_count);
  EXPECT_EQ(2, regular_load_backend_count);
}

TEST_P(OutlierDetectionTest, SuccessRateStdevFactor) {
  CreateAndStartBackends(2);
  auto cluster = default_cluster_;
  cluster.set_lb_policy(Cluster::RING_HASH);

  auto* outlier_detection = cluster.mutable_outlier_detection();
  SetProtoDuration(grpc_core::Duration::Seconds(1),
                   outlier_detection->mutable_interval());
  SetProtoDuration(grpc_core::Duration::Seconds(1),
                   outlier_detection->mutable_base_ejection_time());

  outlier_detection->mutable_success_rate_stdev_factor()->set_value(1000);
  outlier_detection->mutable_enforcing_success_rate()->set_value(100);
  outlier_detection->mutable_success_rate_minimum_hosts()->set_value(1);
  outlier_detection->mutable_success_rate_request_volume()->set_value(1);
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
  const auto rpc_options = RpcOptions().set_metadata(metadata);
  const auto rpc_options1 = RpcOptions().set_metadata(std::move(metadata1));
  WaitForBackend(DEBUG_LOCATION, 0, nullptr,
                 WaitForBackendOptions(), rpc_options);
  WaitForBackend(DEBUG_LOCATION, 1, nullptr,
                 WaitForBackendOptions(), rpc_options1);

  CheckRpcSendFailure(DEBUG_LOCATION, StatusCode::CANCELLED, "",
                      RpcOptions()
                          .set_metadata(std::move(metadata))
                          .set_server_expected_error(StatusCode::CANCELLED));
  gpr_sleep_until(grpc_timeout_milliseconds_to_deadline(
      3000 * grpc_test_slowdown_factor()));
  ResetBackendCounters();

  CheckRpcSendOk(DEBUG_LOCATION, 100, rpc_options);
  CheckRpcSendOk(DEBUG_LOCATION, 100, rpc_options1);
  EXPECT_EQ(100, backends_[0]->backend_service()->request_count());
  EXPECT_EQ(100, backends_[1]->backend_service()->request_count());
}

TEST_P(OutlierDetectionTest, SuccessRateEnforcementPercentage) {
  CreateAndStartBackends(2);
  auto cluster = default_cluster_;
  cluster.set_lb_policy(Cluster::RING_HASH);
  auto* outlier_detection = cluster.mutable_outlier_detection();
  SetProtoDuration(grpc_core::Duration::Seconds(1),
                   outlier_detection->mutable_interval());
  SetProtoDuration(grpc_core::Duration::Seconds(1),
                   outlier_detection->mutable_base_ejection_time());
  outlier_detection->mutable_success_rate_stdev_factor()->set_value(100);

  outlier_detection->mutable_enforcing_success_rate()->set_value(0);
  outlier_detection->mutable_success_rate_minimum_hosts()->set_value(1);
  outlier_detection->mutable_success_rate_request_volume()->set_value(1);
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
  const auto rpc_options = RpcOptions().set_metadata(metadata);
  const auto rpc_options1 = RpcOptions().set_metadata(std::move(metadata1));
  WaitForBackend(DEBUG_LOCATION, 0, nullptr,
                 WaitForBackendOptions(), rpc_options);
  WaitForBackend(DEBUG_LOCATION, 1, nullptr,
                 WaitForBackendOptions(), rpc_options1);

  CheckRpcSendFailure(DEBUG_LOCATION, StatusCode::CANCELLED, "",
                      RpcOptions()
                          .set_metadata(std::move(metadata))
                          .set_server_expected_error(StatusCode::CANCELLED));
  gpr_sleep_until(grpc_timeout_milliseconds_to_deadline(
      3000 * grpc_test_slowdown_factor()));
  ResetBackendCounters();

  CheckRpcSendOk(DEBUG_LOCATION, 100, rpc_options);
  CheckRpcSendOk(DEBUG_LOCATION, 100, rpc_options1);
  EXPECT_EQ(100, backends_[0]->backend_service()->request_count());
  EXPECT_EQ(100, backends_[1]->backend_service()->request_count());
}

TEST_P(OutlierDetectionTest, SuccessRateMinimumHosts) {
  CreateAndStartBackends(2);
  auto cluster = default_cluster_;
  cluster.set_lb_policy(Cluster::RING_HASH);

  auto* outlier_detection = cluster.mutable_outlier_detection();
  SetProtoDuration(grpc_core::Duration::Seconds(1),
                   outlier_detection->mutable_interval());
  outlier_detection->mutable_success_rate_stdev_factor()->set_value(100);
  outlier_detection->mutable_enforcing_success_rate()->set_value(100);

  outlier_detection->mutable_success_rate_minimum_hosts()->set_value(3);
  outlier_detection->mutable_success_rate_request_volume()->set_value(1);
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
  const auto rpc_options = RpcOptions().set_metadata(metadata);
  const auto rpc_options1 = RpcOptions().set_metadata(std::move(metadata1));
  WaitForBackend(DEBUG_LOCATION, 0, nullptr,
                 WaitForBackendOptions(), rpc_options);
  WaitForBackend(DEBUG_LOCATION, 1, nullptr,
                 WaitForBackendOptions(), rpc_options1);

  CheckRpcSendFailure(DEBUG_LOCATION, StatusCode::CANCELLED, "",
                      RpcOptions()
                          .set_metadata(std::move(metadata))
                          .set_server_expected_error(StatusCode::CANCELLED));
  gpr_sleep_until(grpc_timeout_milliseconds_to_deadline(
      3000 * grpc_test_slowdown_factor()));
  ResetBackendCounters();

  CheckRpcSendOk(DEBUG_LOCATION, 100, rpc_options);
  CheckRpcSendOk(DEBUG_LOCATION, 100, rpc_options1);
  EXPECT_EQ(100, backends_[0]->backend_service()->request_count());
  EXPECT_EQ(100, backends_[1]->backend_service()->request_count());
}

TEST_P(OutlierDetectionTest, SuccessRateRequestVolume) {
  CreateAndStartBackends(2);
  auto cluster = default_cluster_;
  cluster.set_lb_policy(Cluster::RING_HASH);

  auto* outlier_detection = cluster.mutable_outlier_detection();
  SetProtoDuration(grpc_core::Duration::Seconds(1),
                   outlier_detection->mutable_interval());
  outlier_detection->mutable_success_rate_stdev_factor()->set_value(100);
  outlier_detection->mutable_enforcing_success_rate()->set_value(100);
  outlier_detection->mutable_success_rate_minimum_hosts()->set_value(1);

  outlier_detection->mutable_success_rate_request_volume()->set_value(4);
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
  const auto rpc_options = RpcOptions().set_metadata(metadata);
  const auto rpc_options1 = RpcOptions().set_metadata(std::move(metadata1));
  WaitForBackend(DEBUG_LOCATION, 0, nullptr,
                 WaitForBackendOptions(), rpc_options);
  WaitForBackend(DEBUG_LOCATION, 1, nullptr,
                 WaitForBackendOptions(), rpc_options1);

  CheckRpcSendFailure(DEBUG_LOCATION, StatusCode::CANCELLED, "",
                      RpcOptions()
                          .set_metadata(std::move(metadata))
                          .set_server_expected_error(StatusCode::CANCELLED));
  gpr_sleep_until(grpc_timeout_milliseconds_to_deadline(
      3000 * grpc_test_slowdown_factor()));
  ResetBackendCounters();

  CheckRpcSendOk(DEBUG_LOCATION, 100, rpc_options);
  CheckRpcSendOk(DEBUG_LOCATION, 100, rpc_options1);
  EXPECT_EQ(100, backends_[0]->backend_service()->request_count());
  EXPECT_EQ(100, backends_[1]->backend_service()->request_count());
}

TEST_P(OutlierDetectionTest, FailurePercentageEjectionAndUnejection) {
  CreateAndStartBackends(2);
  auto cluster = default_cluster_;
  cluster.set_lb_policy(Cluster::RING_HASH);

  auto* outlier_detection = cluster.mutable_outlier_detection();
  SetProtoDuration(grpc_core::Duration::Seconds(1),
                   outlier_detection->mutable_interval());
  SetProtoDuration(grpc_core::Duration::Seconds(3),
                   outlier_detection->mutable_base_ejection_time());
  outlier_detection->mutable_failure_percentage_threshold()->set_value(0);
  outlier_detection->mutable_enforcing_failure_percentage()->set_value(100);
  outlier_detection->mutable_failure_percentage_minimum_hosts()->set_value(1);
  outlier_detection->mutable_failure_percentage_request_volume()->set_value(1);
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
  const auto rpc_options = RpcOptions().set_metadata(metadata);
  const auto rpc_options1 = RpcOptions().set_metadata(std::move(metadata1));
  WaitForBackend(DEBUG_LOCATION, 0, nullptr,
                 WaitForBackendOptions(), rpc_options);
  WaitForBackend(DEBUG_LOCATION, 1, nullptr,
                 WaitForBackendOptions(), rpc_options1);

  CheckRpcSendFailure(DEBUG_LOCATION, StatusCode::CANCELLED, "",
                      RpcOptions()
                          .set_metadata(std::move(metadata))
                          .set_server_expected_error(StatusCode::CANCELLED));
  WaitForBackend(DEBUG_LOCATION, 1, nullptr,
                 WaitForBackendOptions().set_timeout_ms(
                     3000 * grpc_test_slowdown_factor()),
                 rpc_options);

  CheckRpcSendOk(DEBUG_LOCATION, 100, rpc_options);
  EXPECT_EQ(100, backends_[1]->backend_service()->request_count());

  WaitForBackend(DEBUG_LOCATION, 0, nullptr,
                 WaitForBackendOptions().set_timeout_ms(
                     30000 * grpc_test_slowdown_factor()),
                 rpc_options);

  CheckRpcSendOk(DEBUG_LOCATION, 100, rpc_options);
  CheckRpcSendOk(DEBUG_LOCATION, 100, rpc_options1);
  EXPECT_EQ(100, backends_[0]->backend_service()->request_count());
  EXPECT_EQ(100, backends_[1]->backend_service()->request_count());
}

TEST_P(OutlierDetectionTest, FailurePercentageMaxPercentage) {
  CreateAndStartBackends(4);
  auto cluster = default_cluster_;
  cluster.set_lb_policy(Cluster::RING_HASH);

  auto* outlier_detection = cluster.mutable_outlier_detection();
  SetProtoDuration(grpc_core::Duration::Seconds(1),
                   outlier_detection->mutable_interval());
  outlier_detection->mutable_failure_percentage_threshold()->set_value(0);
  outlier_detection->mutable_enforcing_failure_percentage()->set_value(100);
  outlier_detection->mutable_failure_percentage_minimum_hosts()->set_value(1);
  outlier_detection->mutable_failure_percentage_request_volume()->set_value(1);
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
  const auto rpc_options = RpcOptions().set_metadata(metadata);
  const auto rpc_options1 = RpcOptions().set_metadata(metadata1);
  const auto rpc_options2 = RpcOptions().set_metadata(metadata2);
  const auto rpc_options3 = RpcOptions().set_metadata(metadata3);
  WaitForBackend(DEBUG_LOCATION, 0, nullptr,
                 WaitForBackendOptions(), rpc_options);
  WaitForBackend(DEBUG_LOCATION, 1, nullptr,
                 WaitForBackendOptions(), rpc_options1);
  WaitForBackend(DEBUG_LOCATION, 2, nullptr,
                 WaitForBackendOptions(), rpc_options2);
  WaitForBackend(DEBUG_LOCATION, 3, nullptr,
                 WaitForBackendOptions(), rpc_options3);

  CheckRpcSendFailure(DEBUG_LOCATION, StatusCode::CANCELLED, "",
                      RpcOptions()
                          .set_metadata(std::move(metadata))
                          .set_server_expected_error(StatusCode::CANCELLED));
  CheckRpcSendFailure(DEBUG_LOCATION, StatusCode::CANCELLED, "",
                      RpcOptions()
                          .set_metadata(std::move(metadata1))
                          .set_server_expected_error(StatusCode::CANCELLED));
  absl::Time deadline =
      absl::Now() + absl::Seconds(3) * grpc_test_slowdown_factor();
  while (true) {
    ResetBackendCounters();
    CheckRpcSendOk(DEBUG_LOCATION, 1, rpc_options);
    CheckRpcSendOk(DEBUG_LOCATION, 1, rpc_options1);
    if (!SeenAllBackends(0, 2)) {
      break;
    }
    EXPECT_LE(absl::Now(), deadline);
    if (absl::Now() >= deadline) break;
  }

  ResetBackendCounters();
  CheckRpcSendOk(DEBUG_LOCATION, 100, rpc_options);
  CheckRpcSendOk(DEBUG_LOCATION, 100, rpc_options1);
  CheckRpcSendOk(DEBUG_LOCATION, 100, rpc_options2);
  CheckRpcSendOk(DEBUG_LOCATION, 100, rpc_options3);
  size_t empty_load_backend_count = 0;
  size_t double_load_backend_count = 0;
  size_t regular_load_backend_count = 0;
  for (size_t i = 0; i < backends_.size(); ++i) {
    if (backends_[i]->backend_service()->request_count() == 0) {
      ++empty_load_backend_count;
    } else if (backends_[i]->backend_service()->request_count() == 200) {
      ++double_load_backend_count;
    } else if (backends_[i]->backend_service()->request_count() == 100) {
      ++regular_load_backend_count;
    } else {
      CHECK(1);
    }
  }
  EXPECT_EQ(1, empty_load_backend_count);
  EXPECT_EQ(1, double_load_backend_count);
  EXPECT_EQ(2, regular_load_backend_count);
}

TEST_P(OutlierDetectionTest, FailurePercentageThreshold) {
  CreateAndStartBackends(2);
  auto cluster = default_cluster_;
  cluster.set_lb_policy(Cluster::RING_HASH);
  auto* outlier_detection = cluster.mutable_outlier_detection();
  SetProtoDuration(grpc_core::Duration::Seconds(1),
                   outlier_detection->mutable_interval());
  SetProtoDuration(grpc_core::Duration::Seconds(1),
                   outlier_detection->mutable_base_ejection_time());

  outlier_detection->mutable_failure_percentage_threshold()->set_value(50);
  outlier_detection->mutable_enforcing_failure_percentage()->set_value(100);
  outlier_detection->mutable_failure_percentage_minimum_hosts()->set_value(1);
  outlier_detection->mutable_failure_percentage_request_volume()->set_value(1);
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
  const auto rpc_options = RpcOptions().set_metadata(metadata);
  const auto rpc_options1 = RpcOptions().set_metadata(std::move(metadata1));
  WaitForBackend(DEBUG_LOCATION, 0, nullptr,
                 WaitForBackendOptions(), rpc_options);
  WaitForBackend(DEBUG_LOCATION, 1, nullptr,
                 WaitForBackendOptions(), rpc_options1);

  CheckRpcSendFailure(DEBUG_LOCATION, StatusCode::CANCELLED, "",
                      RpcOptions()
                          .set_metadata(std::move(metadata))
                          .set_server_expected_error(StatusCode::CANCELLED));
  gpr_sleep_until(grpc_timeout_milliseconds_to_deadline(
      3000 * grpc_test_slowdown_factor()));
  ResetBackendCounters();

  CheckRpcSendOk(DEBUG_LOCATION, 100, rpc_options);
  CheckRpcSendOk(DEBUG_LOCATION, 100, rpc_options1);
  EXPECT_EQ(100, backends_[0]->backend_service()->request_count());
  EXPECT_EQ(100, backends_[1]->backend_service()->request_count());
}

TEST_P(OutlierDetectionTest, FailurePercentageEnforcementPercentage) {
  CreateAndStartBackends(2);
  auto cluster = default_cluster_;
  cluster.set_lb_policy(Cluster::RING_HASH);
  auto* outlier_detection = cluster.mutable_outlier_detection();
  SetProtoDuration(grpc_core::Duration::Seconds(1),
                   outlier_detection->mutable_interval());
  SetProtoDuration(grpc_core::Duration::Seconds(1),
                   outlier_detection->mutable_base_ejection_time());
  outlier_detection->mutable_failure_percentage_threshold()->set_value(0);

  outlier_detection->mutable_enforcing_failure_percentage()->set_value(0);
  outlier_detection->mutable_failure_percentage_minimum_hosts()->set_value(1);
  outlier_detection->mutable_failure_percentage_request_volume()->set_value(1);
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
  const auto rpc_options = RpcOptions().set_metadata(metadata);
  const auto rpc_options1 = RpcOptions().set_metadata(std::move(metadata1));
  WaitForBackend(DEBUG_LOCATION, 0, nullptr,
                 WaitForBackendOptions(), rpc_options);
  WaitForBackend(DEBUG_LOCATION, 1, nullptr,
                 WaitForBackendOptions(), rpc_options1);

  CheckRpcSendFailure(DEBUG_LOCATION, StatusCode::CANCELLED, "",
                      RpcOptions()
                          .set_metadata(std::move(metadata))
                          .set_server_expected_error(StatusCode::CANCELLED));
  gpr_sleep_until(grpc_timeout_milliseconds_to_deadline(
      3000 * grpc_test_slowdown_factor()));
  ResetBackendCounters();

  CheckRpcSendOk(DEBUG_LOCATION, 100, rpc_options);
  CheckRpcSendOk(DEBUG_LOCATION, 100, rpc_options1);
  EXPECT_EQ(100, backends_[0]->backend_service()->request_count());
  EXPECT_EQ(100, backends_[1]->backend_service()->request_count());
}

TEST_P(OutlierDetectionTest, FailurePercentageMinimumHosts) {
  CreateAndStartBackends(2);
  auto cluster = default_cluster_;
  cluster.set_lb_policy(Cluster::RING_HASH);

  auto* outlier_detection = cluster.mutable_outlier_detection();
  SetProtoDuration(grpc_core::Duration::Seconds(1),
                   outlier_detection->mutable_interval());
  outlier_detection->mutable_failure_percentage_threshold()->set_value(0);
  outlier_detection->mutable_enforcing_failure_percentage()->set_value(100);

  cluster.mutable_outlier_detection()
      ->mutable_failure_percentage_minimum_hosts()
      ->set_value(3);
  cluster.mutable_outlier_detection()
      ->mutable_failure_percentage_request_volume()
      ->set_value(1);
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
  const auto rpc_options = RpcOptions().set_metadata(metadata);
  const auto rpc_options1 = RpcOptions().set_metadata(std::move(metadata1));
  WaitForBackend(DEBUG_LOCATION, 0, nullptr,
                 WaitForBackendOptions(), rpc_options);
  WaitForBackend(DEBUG_LOCATION, 1, nullptr,
                 WaitForBackendOptions(), rpc_options1);

  CheckRpcSendFailure(DEBUG_LOCATION, StatusCode::CANCELLED, "",
                      RpcOptions()
                          .set_metadata(std::move(metadata))
                          .set_server_expected_error(StatusCode::CANCELLED));
  gpr_sleep_until(grpc_timeout_milliseconds_to_deadline(
      3000 * grpc_test_slowdown_factor()));
  ResetBackendCounters();

  CheckRpcSendOk(DEBUG_LOCATION, 100, rpc_options);
  CheckRpcSendOk(DEBUG_LOCATION, 100, rpc_options1);
  EXPECT_EQ(100, backends_[0]->backend_service()->request_count());
  EXPECT_EQ(100, backends_[1]->backend_service()->request_count());
}

TEST_P(OutlierDetectionTest, FailurePercentageRequestVolume) {
  CreateAndStartBackends(2);
  auto cluster = default_cluster_;
  cluster.set_lb_policy(Cluster::RING_HASH);

  auto* outlier_detection = cluster.mutable_outlier_detection();
  SetProtoDuration(grpc_core::Duration::Seconds(1),
                   outlier_detection->mutable_interval());
  outlier_detection->mutable_failure_percentage_threshold()->set_value(0);
  outlier_detection->mutable_enforcing_failure_percentage()->set_value(100);
  outlier_detection->mutable_failure_percentage_minimum_hosts()->set_value(1);

  outlier_detection->mutable_failure_percentage_request_volume()->set_value(4);
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
  const auto rpc_options = RpcOptions().set_metadata(metadata);
  const auto rpc_options1 = RpcOptions().set_metadata(std::move(metadata1));
  WaitForBackend(DEBUG_LOCATION, 0, nullptr,
                 WaitForBackendOptions(), rpc_options);
  WaitForBackend(DEBUG_LOCATION, 1, nullptr,
                 WaitForBackendOptions(), rpc_options1);

  CheckRpcSendFailure(DEBUG_LOCATION, StatusCode::CANCELLED, "",
                      RpcOptions()
                          .set_metadata(std::move(metadata))
                          .set_server_expected_error(StatusCode::CANCELLED));
  gpr_sleep_until(grpc_timeout_milliseconds_to_deadline(
      3000 * grpc_test_slowdown_factor()));
  ResetBackendCounters();

  CheckRpcSendOk(DEBUG_LOCATION, 100, rpc_options);
  CheckRpcSendOk(DEBUG_LOCATION, 100, rpc_options1);
  EXPECT_EQ(100, backends_[0]->backend_service()->request_count());
  EXPECT_EQ(100, backends_[1]->backend_service()->request_count());
}

TEST_P(OutlierDetectionTest, SuccessRateAndFailurePercentage) {
  CreateAndStartBackends(4);
  auto cluster = default_cluster_;
  cluster.set_lb_policy(Cluster::RING_HASH);

  auto* outlier_detection = cluster.mutable_outlier_detection();
  SetProtoDuration(grpc_core::Duration::Seconds(1),
                   outlier_detection->mutable_interval());
  outlier_detection->mutable_max_ejection_percent()->set_value(50);

  outlier_detection->mutable_success_rate_stdev_factor()->set_value(500);
  outlier_detection->mutable_enforcing_success_rate()->set_value(100);
  outlier_detection->mutable_success_rate_minimum_hosts()->set_value(1);
  outlier_detection->mutable_success_rate_request_volume()->set_value(1);
  outlier_detection->mutable_failure_percentage_threshold()->set_value(0);
  outlier_detection->mutable_enforcing_failure_percentage()->set_value(100);
  outlier_detection->mutable_failure_percentage_minimum_hosts()->set_value(1);
  outlier_detection->mutable_failure_percentage_request_volume()->set_value(1);
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
  const auto rpc_options = RpcOptions().set_metadata(metadata);
  const auto rpc_options1 = RpcOptions().set_metadata(metadata1);
  const auto rpc_options2 = RpcOptions().set_metadata(metadata2);
  const auto rpc_options3 = RpcOptions().set_metadata(metadata3);
  WaitForBackend(DEBUG_LOCATION, 0, nullptr,
                 WaitForBackendOptions(), rpc_options);
  WaitForBackend(DEBUG_LOCATION, 1, nullptr,
                 WaitForBackendOptions(), rpc_options1);
  WaitForBackend(DEBUG_LOCATION, 2, nullptr,
                 WaitForBackendOptions(), rpc_options2);
  WaitForBackend(DEBUG_LOCATION, 3, nullptr,
                 WaitForBackendOptions(), rpc_options3);

  CheckRpcSendFailure(
      DEBUG_LOCATION, StatusCode::CANCELLED, "",
      RpcOptions().set_metadata(metadata).set_server_expected_error(
          StatusCode::CANCELLED));
  CheckRpcSendFailure(
      DEBUG_LOCATION, StatusCode::CANCELLED, "",
      RpcOptions().set_metadata(metadata).set_server_expected_error(
          StatusCode::CANCELLED));
  CheckRpcSendFailure(
      DEBUG_LOCATION, StatusCode::CANCELLED, "",
      RpcOptions().set_metadata(metadata1).set_server_expected_error(
          StatusCode::CANCELLED));
  CheckRpcSendFailure(
      DEBUG_LOCATION, StatusCode::CANCELLED, "",
      RpcOptions().set_metadata(metadata2).set_server_expected_error(
          StatusCode::CANCELLED));
  absl::Time deadline =
      absl::Now() + absl::Seconds(3) * grpc_test_slowdown_factor();
  std::vector<size_t> idx = {0, 1, 2, 3};
  while (true) {
    ResetBackendCounters();
    CheckRpcSendOk(DEBUG_LOCATION, 1, rpc_options);
    CheckRpcSendOk(DEBUG_LOCATION, 1, rpc_options1);
    CheckRpcSendOk(DEBUG_LOCATION, 1, rpc_options2);
    CheckRpcSendOk(DEBUG_LOCATION, 1, rpc_options3);
    if (std::count_if(idx.begin(), idx.end(),
                      [this](size_t i) { return SeenBackend(i); }) == 2) {
      break;
    }
    EXPECT_LE(absl::Now(), deadline);
    if (absl::Now() >= deadline) break;
  }
  ResetBackendCounters();
  CheckRpcSendOk(DEBUG_LOCATION, 100, rpc_options);
  CheckRpcSendOk(DEBUG_LOCATION, 100, rpc_options1);
  CheckRpcSendOk(DEBUG_LOCATION, 100, rpc_options2);
  CheckRpcSendOk(DEBUG_LOCATION, 100, rpc_options3);
  size_t empty_load_backend_count = 0;
  size_t double_load_backend_count = 0;
  for (size_t i = 0; i < backends_.size(); ++i) {
    if (backends_[i]->backend_service()->request_count() == 0) {
      ++empty_load_backend_count;
    } else if (backends_[i]->backend_service()->request_count() >= 100) {

      ++double_load_backend_count;
    } else if (backends_[i]->backend_service()->request_count() > 300) {
      CHECK(1);
    }
  }
  EXPECT_EQ(2, empty_load_backend_count);
  EXPECT_EQ(2, double_load_backend_count);
}

TEST_P(OutlierDetectionTest, SuccessRateAndFailurePercentageBothDisabled) {
  CreateAndStartBackends(2);
  auto cluster = default_cluster_;
  cluster.set_lb_policy(Cluster::RING_HASH);
  auto* outlier_detection = cluster.mutable_outlier_detection();
  SetProtoDuration(grpc_core::Duration::Seconds(1),
                   outlier_detection->mutable_interval());
  SetProtoDuration(grpc_core::Duration::Seconds(1),
                   outlier_detection->mutable_base_ejection_time());
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
  const auto rpc_options = RpcOptions().set_metadata(metadata);
  const auto rpc_options1 = RpcOptions().set_metadata(std::move(metadata1));
  WaitForBackend(DEBUG_LOCATION, 0, nullptr,
                 WaitForBackendOptions(), rpc_options);
  WaitForBackend(DEBUG_LOCATION, 1, nullptr,
                 WaitForBackendOptions(), rpc_options1);

  CheckRpcSendFailure(DEBUG_LOCATION, StatusCode::CANCELLED, "",
                      RpcOptions()
                          .set_metadata(std::move(metadata))
                          .set_server_expected_error(StatusCode::CANCELLED));
  gpr_sleep_until(grpc_timeout_milliseconds_to_deadline(
      3000 * grpc_test_slowdown_factor()));
  ResetBackendCounters();

  CheckRpcSendOk(DEBUG_LOCATION, 100, rpc_options);
  CheckRpcSendOk(DEBUG_LOCATION, 100, rpc_options1);
  EXPECT_EQ(100, backends_[0]->backend_service()->request_count());
  EXPECT_EQ(100, backends_[1]->backend_service()->request_count());
}

TEST_P(OutlierDetectionTest, DisableOutlierDetectionWhileAddressesAreEjected) {
  CreateAndStartBackends(2);
  auto cluster = default_cluster_;
  cluster.set_lb_policy(Cluster::RING_HASH);

  auto* outlier_detection = cluster.mutable_outlier_detection();
  SetProtoDuration(grpc_core::Duration::Seconds(1),
                   outlier_detection->mutable_interval());
  SetProtoDuration(grpc_core::Duration::Seconds(3),
                   outlier_detection->mutable_base_ejection_time());
  outlier_detection->mutable_failure_percentage_threshold()->set_value(0);
  outlier_detection->mutable_enforcing_failure_percentage()->set_value(100);
  outlier_detection->mutable_failure_percentage_minimum_hosts()->set_value(1);
  outlier_detection->mutable_failure_percentage_request_volume()->set_value(1);
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
  const auto rpc_options = RpcOptions().set_metadata(metadata);
  const auto rpc_options1 = RpcOptions().set_metadata(std::move(metadata1));
  WaitForBackend(DEBUG_LOCATION, 0, nullptr,
                 WaitForBackendOptions(), rpc_options);
  WaitForBackend(DEBUG_LOCATION, 1, nullptr,
                 WaitForBackendOptions(), rpc_options1);

  CheckRpcSendFailure(
      DEBUG_LOCATION, StatusCode::CANCELLED, "",
      RpcOptions().set_metadata(metadata).set_server_expected_error(
          StatusCode::CANCELLED));
  WaitForBackend(DEBUG_LOCATION, 1, nullptr,
                 WaitForBackendOptions().set_timeout_ms(
                     3000 * grpc_test_slowdown_factor()),
                 rpc_options);

  CheckRpcSendOk(DEBUG_LOCATION, 1, rpc_options);
  EXPECT_EQ(1, backends_[1]->backend_service()->request_count());

  cluster.clear_outlier_detection();
  balancer_->ads_service()->SetCdsResource(cluster);

  WaitForBackend(
      DEBUG_LOCATION, 0,
      [](const RpcResult& result) {
        EXPECT_EQ(result.status.error_code(), StatusCode::CANCELLED)
            << "Error: " << result.status.error_message();
      },
      WaitForBackendOptions(),
      RpcOptions()
          .set_metadata(std::move(metadata))
          .set_server_expected_error(StatusCode::CANCELLED));
}

TEST_P(OutlierDetectionTest, EjectionRetainedAcrossPriorities) {
  CreateAndStartBackends(3);
  auto cluster = default_cluster_;

  auto* outlier_detection = cluster.mutable_outlier_detection();
  SetProtoDuration(grpc_core::Duration::Seconds(1),
                   outlier_detection->mutable_interval());
  SetProtoDuration(grpc_core::Duration::Minutes(10),
                   outlier_detection->mutable_base_ejection_time());
  outlier_detection->mutable_failure_percentage_threshold()->set_value(0);
  outlier_detection->mutable_enforcing_failure_percentage()->set_value(100);
  outlier_detection->mutable_failure_percentage_minimum_hosts()->set_value(1);
  outlier_detection->mutable_failure_percentage_request_volume()->set_value(1);
  balancer_->ads_service()->SetCdsResource(cluster);

  EdsResourceArgs args({
      {"locality0", {CreateEndpoint(0), MakeNonExistentEndpoint()}},
      {"locality1", {CreateEndpoint(1)}, kDefaultLocalityWeight, 1},
  });
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));
  WaitForBackend(DEBUG_LOCATION, 0);

  CheckRpcSendFailure(
      DEBUG_LOCATION, StatusCode::CANCELLED, "",
      RpcOptions().set_server_expected_error(StatusCode::CANCELLED));

  WaitForBackend(DEBUG_LOCATION, 1, nullptr,
                 WaitForBackendOptions().set_timeout_ms(
                     3000 * grpc_test_slowdown_factor()));

  args = EdsResourceArgs({
      {"locality0", {MakeNonExistentEndpoint()}},
      {"locality1", CreateEndpointsForBackends(), kDefaultLocalityWeight, 1},
  });
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));
  WaitForBackend(DEBUG_LOCATION, 2);

  CheckRpcSendOk(DEBUG_LOCATION, 100);
  EXPECT_EQ(0, backends_[0]->backend_service()->request_count());
  EXPECT_EQ(50, backends_[1]->backend_service()->request_count());
  EXPECT_EQ(50, backends_[2]->backend_service()->request_count());
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
