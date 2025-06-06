// Copyright 2017 gRPC authors.

#include <string>
#include <vector>

#include "envoy/config/cluster/v3/cluster.pb.h"
#include "envoy/extensions/filters/http/fault/v3/fault.pb.h"
#include "envoy/extensions/filters/http/router/v3/router.pb.h"
#include "envoy/extensions/filters/network/http_connection_manager/v3/http_connection_manager.pb.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "src/core/client_channel/backup_poller.h"
#include "src/core/config/config_vars.h"
#include "test/core/test_util/test_config.h"
#include "test/cpp/end2end/xds/xds_end2end_test_lib.h"

namespace grpc {
namespace testing {
namespace {

using ::envoy::config::core::v3::RoutingPriority;
using ::envoy::extensions::filters::http::fault::v3::HTTPFault;
using ::envoy::extensions::filters::network::http_connection_manager::v3::
    HttpFilter;
using ::envoy::type::v3::FractionalPercent;

class FaultInjectionTest : public XdsEnd2endTest {
 public:

  static Listener BuildListenerWithFaultInjection(
      const HTTPFault& http_fault = HTTPFault()) {
    HttpConnectionManager http_connection_manager;
    Listener listener;
    listener.set_name(kServerName);
    HttpFilter* fault_filter = http_connection_manager.add_http_filters();
    fault_filter->set_name("envoy.fault");
    fault_filter->mutable_typed_config()->PackFrom(http_fault);
    HttpFilter* router_filter = http_connection_manager.add_http_filters();
    router_filter->set_name("router");
    router_filter->mutable_typed_config()->PackFrom(
        envoy::extensions::filters::http::router::v3::Router());
    listener.mutable_api_listener()->mutable_api_listener()->PackFrom(
        http_connection_manager);
    return listener;
  }

  RouteConfiguration BuildRouteConfigurationWithFaultInjection(
      const HTTPFault& http_fault) {

    google::protobuf::Any filter_config;
    filter_config.PackFrom(http_fault);

    RouteConfiguration new_route_config = default_route_config_;
    auto* config_map = new_route_config.mutable_virtual_hosts(0)
                           ->mutable_routes(0)
                           ->mutable_typed_per_filter_config();
    (*config_map)["envoy.fault"] = std::move(filter_config);
    return new_route_config;
  }

  void SetFilterConfig(HTTPFault& http_fault) {
    switch (GetParam().filter_config_setup()) {
      case XdsTestType::HttpFilterConfigLocation::kHttpFilterConfigInRoute: {
        Listener listener = BuildListenerWithFaultInjection();
        RouteConfiguration route =
            BuildRouteConfigurationWithFaultInjection(http_fault);
        SetListenerAndRouteConfiguration(balancer_.get(), listener, route);
        break;
      }
      case XdsTestType::HttpFilterConfigLocation::kHttpFilterConfigInListener: {
        Listener listener = BuildListenerWithFaultInjection(http_fault);
        SetListenerAndRouteConfiguration(balancer_.get(), listener,
                                         default_route_config_);
      }
    };
  }
};

INSTANTIATE_TEST_SUITE_P(
    XdsTest, FaultInjectionTest,
    ::testing::Values(
        XdsTestType(), XdsTestType().set_enable_rds_testing(),
        XdsTestType().set_filter_config_setup(
            XdsTestType::HttpFilterConfigLocation::kHttpFilterConfigInRoute),
        XdsTestType().set_enable_rds_testing().set_filter_config_setup(
            XdsTestType::HttpFilterConfigLocation::kHttpFilterConfigInRoute)),
    &XdsTestType::Name);

TEST_P(FaultInjectionTest, XdsFaultInjectionAlwaysAbort) {
  const uint32_t kAbortPercentagePerHundred = 100;

  EdsResourceArgs args({{"locality0", {MakeNonExistentEndpoint()}}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  HTTPFault http_fault;
  auto* abort_percentage = http_fault.mutable_abort()->mutable_percentage();
  abort_percentage->set_numerator(kAbortPercentagePerHundred);
  abort_percentage->set_denominator(FractionalPercent::HUNDRED);
  http_fault.mutable_abort()->set_grpc_status(
      static_cast<uint32_t>(StatusCode::ABORTED));

  SetFilterConfig(http_fault);

  for (size_t i = 0; i < 5; ++i) {
    CheckRpcSendFailure(DEBUG_LOCATION, StatusCode::ABORTED, "Fault injected",
                        RpcOptions().set_wait_for_ready(true));
  }
}

TEST_P(FaultInjectionTest, XdsFaultInjectionWithoutListenerFilter) {
  CreateAndStartBackends(1);
  const uint32_t kAbortPercentagePerHundred = 100;

  EdsResourceArgs args({{"locality0", CreateEndpointsForBackends()}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  HTTPFault http_fault;
  auto* abort_percentage = http_fault.mutable_abort()->mutable_percentage();
  abort_percentage->set_numerator(kAbortPercentagePerHundred);
  abort_percentage->set_denominator(FractionalPercent::HUNDRED);
  http_fault.mutable_abort()->set_grpc_status(
      static_cast<uint32_t>(StatusCode::ABORTED));

  RouteConfiguration route =
      BuildRouteConfigurationWithFaultInjection(http_fault);
  SetListenerAndRouteConfiguration(balancer_.get(), default_listener_, route);

  CheckRpcSendOk(DEBUG_LOCATION, 5, RpcOptions().set_wait_for_ready(true));
}

TEST_P(FaultInjectionTest, XdsFaultInjectionPercentageAbort) {
  CreateAndStartBackends(1);
  const uint32_t kAbortPercentagePerHundred = 50;
  const double kAbortRate = kAbortPercentagePerHundred / 100.0;
  const double kErrorTolerance = 0.1;
  const size_t kNumRpcs = ComputeIdealNumRpcs(kAbortRate, kErrorTolerance);

  EdsResourceArgs args({{"locality0", CreateEndpointsForBackends()}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  HTTPFault http_fault;
  auto* abort_percentage = http_fault.mutable_abort()->mutable_percentage();
  abort_percentage->set_numerator(kAbortPercentagePerHundred);
  abort_percentage->set_denominator(FractionalPercent::HUNDRED);
  http_fault.mutable_abort()->set_grpc_status(
      static_cast<uint32_t>(StatusCode::ABORTED));

  SetFilterConfig(http_fault);

  size_t num_aborted = SendRpcsAndCountFailuresWithMessage(
      DEBUG_LOCATION, kNumRpcs, StatusCode::ABORTED, "Fault injected");

  const double seen_abort_rate = static_cast<double>(num_aborted) / kNumRpcs;
  EXPECT_THAT(seen_abort_rate,
              ::testing::DoubleNear(kAbortRate, kErrorTolerance));
}

TEST_P(FaultInjectionTest, XdsFaultInjectionPercentageAbortViaHeaders) {
  CreateAndStartBackends(1);
  const uint32_t kAbortPercentageCap = 100;
  const uint32_t kAbortPercentage = 50;
  const double kAbortRate = kAbortPercentage / 100.0;
  const double kErrorTolerance = 0.1;
  const size_t kNumRpcs = ComputeIdealNumRpcs(kAbortRate, kErrorTolerance);

  EdsResourceArgs args({{"locality0", CreateEndpointsForBackends()}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  HTTPFault http_fault;
  http_fault.mutable_abort()->mutable_header_abort();
  http_fault.mutable_abort()->mutable_percentage()->set_numerator(
      kAbortPercentageCap);

  SetFilterConfig(http_fault);

  std::vector<std::pair<std::string, std::string>> metadata = {
      {"x-envoy-fault-abort-grpc-request", "10"},
      {"x-envoy-fault-abort-percentage", std::to_string(kAbortPercentage)},
  };
  size_t num_aborted = SendRpcsAndCountFailuresWithMessage(
      DEBUG_LOCATION, kNumRpcs, StatusCode::ABORTED, "Fault injected",
      RpcOptions().set_metadata(metadata));

  const double seen_abort_rate = static_cast<double>(num_aborted) / kNumRpcs;
  EXPECT_THAT(seen_abort_rate,
              ::testing::DoubleNear(kAbortRate, kErrorTolerance));
}

TEST_P(FaultInjectionTest, XdsFaultInjectionPercentageDelay) {
  CreateAndStartBackends(1);
  const auto kRpcTimeout = grpc_core::Duration::Seconds(10);
  const auto kFixedDelay = grpc_core::Duration::Seconds(20);
  const uint32_t kDelayPercentagePerHundred = 50;
  const double kDelayRate = kDelayPercentagePerHundred / 100.0;
  const double kErrorTolerance = 0.1;
  const size_t kNumRpcs = ComputeIdealNumRpcs(kDelayRate, kErrorTolerance);
  const size_t kMaxConcurrentRequests = kNumRpcs;

  EdsResourceArgs args({{"locality0", CreateEndpointsForBackends()}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  Cluster cluster = default_cluster_;
  auto* threshold = cluster.mutable_circuit_breakers()->add_thresholds();
  threshold->set_priority(RoutingPriority::DEFAULT);
  threshold->mutable_max_requests()->set_value(kMaxConcurrentRequests);
  balancer_->ads_service()->SetCdsResource(cluster);

  HTTPFault http_fault;
  auto* delay_percentage = http_fault.mutable_delay()->mutable_percentage();
  delay_percentage->set_numerator(kDelayPercentagePerHundred);
  delay_percentage->set_denominator(FractionalPercent::HUNDRED);
  SetProtoDuration(kFixedDelay,
                   http_fault.mutable_delay()->mutable_fixed_delay());

  SetFilterConfig(http_fault);

  channel_->WaitForConnected(grpc_timeout_milliseconds_to_deadline(15000));

  RpcOptions rpc_options =
      RpcOptions().set_timeout(kRpcTimeout).set_skip_cancelled_check(true);
  std::vector<std::unique_ptr<ConcurrentRpc>> rpcs =
      SendConcurrentRpcs(DEBUG_LOCATION, stub_.get(), kNumRpcs, rpc_options);
  size_t num_delayed = 0;
  for (auto& rpc : rpcs) {
    if (rpc->status.error_code() == StatusCode::OK) continue;
    EXPECT_EQ(StatusCode::DEADLINE_EXCEEDED, rpc->status.error_code());
    ++num_delayed;
  }

  const double seen_delay_rate = static_cast<double>(num_delayed) / kNumRpcs;
  EXPECT_THAT(seen_delay_rate,
              ::testing::DoubleNear(kDelayRate, kErrorTolerance));
}

TEST_P(FaultInjectionTest, XdsFaultInjectionPercentageDelayViaHeaders) {
  CreateAndStartBackends(1);
  const auto kRpcTimeout = grpc_core::Duration::Seconds(10);
  const auto kFixedDelay = grpc_core::Duration::Seconds(20);
  const uint32_t kDelayPercentageCap = 100;
  const uint32_t kDelayPercentage = 50;
  const double kDelayRate = kDelayPercentage / 100.0;
  const double kErrorTolerance = 0.1;
  const size_t kNumRpcs = ComputeIdealNumRpcs(kDelayRate, kErrorTolerance);
  const size_t kMaxConcurrentRequests = kNumRpcs;

  EdsResourceArgs args({{"locality0", CreateEndpointsForBackends()}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  Cluster cluster = default_cluster_;
  auto* threshold = cluster.mutable_circuit_breakers()->add_thresholds();
  threshold->set_priority(RoutingPriority::DEFAULT);
  threshold->mutable_max_requests()->set_value(kMaxConcurrentRequests);
  balancer_->ads_service()->SetCdsResource(cluster);

  HTTPFault http_fault;
  http_fault.mutable_delay()->mutable_header_delay();
  http_fault.mutable_delay()->mutable_percentage()->set_numerator(
      kDelayPercentageCap);

  SetFilterConfig(http_fault);

  channel_->WaitForConnected(grpc_timeout_milliseconds_to_deadline(15000));

  std::vector<std::pair<std::string, std::string>> metadata = {
      {"x-envoy-fault-delay-request",
       std::to_string(kFixedDelay.millis() * grpc_test_slowdown_factor())},
      {"x-envoy-fault-delay-request-percentage",
       std::to_string(kDelayPercentage)},
  };
  RpcOptions rpc_options = RpcOptions()
                               .set_metadata(metadata)
                               .set_timeout(kRpcTimeout)
                               .set_skip_cancelled_check(true);
  std::vector<std::unique_ptr<ConcurrentRpc>> rpcs =
      SendConcurrentRpcs(DEBUG_LOCATION, stub_.get(), kNumRpcs, rpc_options);
  size_t num_delayed = 0;
  for (auto& rpc : rpcs) {
    if (rpc->status.error_code() == StatusCode::OK) continue;
    EXPECT_EQ(StatusCode::DEADLINE_EXCEEDED, rpc->status.error_code());
    ++num_delayed;
  }

  const double seen_delay_rate = static_cast<double>(num_delayed) / kNumRpcs;
  EXPECT_THAT(seen_delay_rate,
              ::testing::DoubleNear(kDelayRate, kErrorTolerance));
}

TEST_P(FaultInjectionTest, XdsFaultInjectionAbortAfterDelayForStreamCall) {
  CreateAndStartBackends(1);
  const auto kRpcTimeout = grpc_core::Duration::Seconds(30);
  const auto kFixedDelay = grpc_core::Duration::Seconds(1);

  EdsResourceArgs args({{"locality0", CreateEndpointsForBackends()}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  HTTPFault http_fault;
  auto* abort_percentage = http_fault.mutable_abort()->mutable_percentage();
  abort_percentage->set_numerator(100);
  abort_percentage->set_denominator(FractionalPercent::HUNDRED);
  http_fault.mutable_abort()->set_grpc_status(
      static_cast<uint32_t>(StatusCode::ABORTED));
  auto* delay_percentage = http_fault.mutable_delay()->mutable_percentage();
  delay_percentage->set_numerator(100);
  delay_percentage->set_denominator(FractionalPercent::HUNDRED);
  SetProtoDuration(kFixedDelay,
                   http_fault.mutable_delay()->mutable_fixed_delay());

  SetFilterConfig(http_fault);

  ClientContext context;
  context.set_deadline(
      grpc_timeout_milliseconds_to_deadline(kRpcTimeout.millis()));
  auto stream = stub_->BidiStream(&context);
  stream->WritesDone();
  auto status = stream->Finish();
  EXPECT_EQ(StatusCode::ABORTED, status.error_code())
      << status.error_message() << ", " << status.error_details() << ", "
      << context.debug_error_string();
}

TEST_P(FaultInjectionTest, XdsFaultInjectionAlwaysDelayPercentageAbort) {
  CreateAndStartBackends(1);
  const auto kRpcTimeout = grpc_core::Duration::Seconds(30);
  const auto kFixedDelay = grpc_core::Duration::Seconds(1);
  const uint32_t kAbortPercentagePerHundred = 50;
  const double kAbortRate = kAbortPercentagePerHundred / 100.0;
  const double kErrorTolerance = 0.1;
  const size_t kNumRpcs = ComputeIdealNumRpcs(kAbortRate, kErrorTolerance);
  const size_t kMaxConcurrentRequests = kNumRpcs;

  EdsResourceArgs args({{"locality0", CreateEndpointsForBackends()}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  Cluster cluster = default_cluster_;
  auto* threshold = cluster.mutable_circuit_breakers()->add_thresholds();
  threshold->set_priority(RoutingPriority::DEFAULT);
  threshold->mutable_max_requests()->set_value(kMaxConcurrentRequests);
  balancer_->ads_service()->SetCdsResource(cluster);

  HTTPFault http_fault;
  auto* abort_percentage = http_fault.mutable_abort()->mutable_percentage();
  abort_percentage->set_numerator(kAbortPercentagePerHundred);
  abort_percentage->set_denominator(FractionalPercent::HUNDRED);
  http_fault.mutable_abort()->set_grpc_status(
      static_cast<uint32_t>(StatusCode::ABORTED));
  auto* delay_percentage = http_fault.mutable_delay()->mutable_percentage();
  delay_percentage->set_numerator(1000000);
  delay_percentage->set_denominator(FractionalPercent::MILLION);
  SetProtoDuration(kFixedDelay,
                   http_fault.mutable_delay()->mutable_fixed_delay());

  SetFilterConfig(http_fault);

  channel_->WaitForConnected(grpc_timeout_milliseconds_to_deadline(15000));

  int num_aborted = 0;
  RpcOptions rpc_options = RpcOptions().set_timeout(kRpcTimeout);
  std::vector<std::unique_ptr<ConcurrentRpc>> rpcs =
      SendConcurrentRpcs(DEBUG_LOCATION, stub_.get(), kNumRpcs, rpc_options);
  for (auto& rpc : rpcs) {
    EXPECT_GE(rpc->elapsed_time, kFixedDelay * grpc_test_slowdown_factor());
    if (rpc->status.error_code() == StatusCode::OK) continue;
    EXPECT_EQ("Fault injected", rpc->status.error_message());
    ++num_aborted;
  }

  const double seen_abort_rate = static_cast<double>(num_aborted) / kNumRpcs;
  EXPECT_THAT(seen_abort_rate,
              ::testing::DoubleNear(kAbortRate, kErrorTolerance));
}

TEST_P(FaultInjectionTest,
       XdsFaultInjectionAlwaysDelayPercentageAbortSwitchDenominator) {
  CreateAndStartBackends(1);
  const auto kRpcTimeout = grpc_core::Duration::Seconds(30);
  const auto kFixedDelay = grpc_core::Duration::Seconds(1);
  const uint32_t kAbortPercentagePerMillion = 500000;
  const double kAbortRate = kAbortPercentagePerMillion / 1000000.0;
  const double kErrorTolerance = 0.1;
  const size_t kNumRpcs = ComputeIdealNumRpcs(kAbortRate, kErrorTolerance);
  const size_t kMaxConcurrentRequests = kNumRpcs;

  EdsResourceArgs args({{"locality0", CreateEndpointsForBackends()}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  Cluster cluster = default_cluster_;
  auto* threshold = cluster.mutable_circuit_breakers()->add_thresholds();
  threshold->set_priority(RoutingPriority::DEFAULT);
  threshold->mutable_max_requests()->set_value(kMaxConcurrentRequests);
  balancer_->ads_service()->SetCdsResource(cluster);

  HTTPFault http_fault;
  auto* abort_percentage = http_fault.mutable_abort()->mutable_percentage();
  abort_percentage->set_numerator(kAbortPercentagePerMillion);
  abort_percentage->set_denominator(FractionalPercent::MILLION);
  http_fault.mutable_abort()->set_grpc_status(
      static_cast<uint32_t>(StatusCode::ABORTED));
  auto* delay_percentage = http_fault.mutable_delay()->mutable_percentage();
  delay_percentage->set_numerator(100);
  delay_percentage->set_denominator(FractionalPercent::HUNDRED);
  SetProtoDuration(kFixedDelay,
                   http_fault.mutable_delay()->mutable_fixed_delay());

  SetFilterConfig(http_fault);

  channel_->WaitForConnected(grpc_timeout_milliseconds_to_deadline(15000));

  int num_aborted = 0;
  RpcOptions rpc_options = RpcOptions().set_timeout(kRpcTimeout);
  std::vector<std::unique_ptr<ConcurrentRpc>> rpcs =
      SendConcurrentRpcs(DEBUG_LOCATION, stub_.get(), kNumRpcs, rpc_options);
  for (auto& rpc : rpcs) {
    EXPECT_GE(rpc->elapsed_time, kFixedDelay * grpc_test_slowdown_factor());
    if (rpc->status.error_code() == StatusCode::OK) continue;
    EXPECT_EQ("Fault injected", rpc->status.error_message());
    ++num_aborted;
  }

  const double seen_abort_rate = static_cast<double>(num_aborted) / kNumRpcs;
  EXPECT_THAT(seen_abort_rate,
              ::testing::DoubleNear(kAbortRate, kErrorTolerance));
}

TEST_P(FaultInjectionTest, XdsFaultInjectionMaxFault) {
  CreateAndStartBackends(1);
  const auto kRpcTimeout = grpc_core::Duration::Seconds(4);
  const auto kFixedDelay = grpc_core::Duration::Seconds(20);
  const uint32_t kMaxFault = 10;
  const uint32_t kNumRpcs = 30;
  const uint32_t kAlwaysDelayPercentage = 100;

  EdsResourceArgs args({{"locality0", CreateEndpointsForBackends()}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  HTTPFault http_fault;
  auto* delay_percentage = http_fault.mutable_delay()->mutable_percentage();
  delay_percentage->set_numerator(
      kAlwaysDelayPercentage);
  delay_percentage->set_denominator(FractionalPercent::HUNDRED);
  SetProtoDuration(kFixedDelay,
                   http_fault.mutable_delay()->mutable_fixed_delay());
  http_fault.mutable_max_active_faults()->set_value(kMaxFault);

  SetFilterConfig(http_fault);

  channel_->WaitForConnected(grpc_timeout_milliseconds_to_deadline(15000));

  int num_delayed = 0;
  RpcOptions rpc_options = RpcOptions().set_timeout(kRpcTimeout);
  std::vector<std::unique_ptr<ConcurrentRpc>> rpcs =
      SendConcurrentRpcs(DEBUG_LOCATION, stub_.get(), kNumRpcs, rpc_options);
  for (auto& rpc : rpcs) {
    if (rpc->status.error_code() == StatusCode::OK) continue;
    EXPECT_EQ(StatusCode::DEADLINE_EXCEEDED, rpc->status.error_code());
    ++num_delayed;
  }

  EXPECT_EQ(kMaxFault, num_delayed);

  num_delayed = 0;
  rpcs = SendConcurrentRpcs(DEBUG_LOCATION, stub_.get(), kNumRpcs, rpc_options);
  for (auto& rpc : rpcs) {
    if (rpc->status.error_code() == StatusCode::OK) continue;
    EXPECT_EQ(StatusCode::DEADLINE_EXCEEDED, rpc->status.error_code());
    ++num_delayed;
  }

  EXPECT_EQ(kMaxFault, num_delayed);
}

TEST_P(FaultInjectionTest, XdsFaultInjectionBidiStreamDelayOk) {
  CreateAndStartBackends(1);
  const auto kRpcTimeout = grpc_core::Duration::Seconds(20);
  const auto kFixedDelay = grpc_core::Duration::Seconds(1);
  const uint32_t kDelayPercentagePerHundred = 100;

  EdsResourceArgs args({{"locality0", CreateEndpointsForBackends()}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  HTTPFault http_fault;
  auto* delay_percentage = http_fault.mutable_delay()->mutable_percentage();
  delay_percentage->set_numerator(kDelayPercentagePerHundred);
  delay_percentage->set_denominator(FractionalPercent::HUNDRED);
  SetProtoDuration(kFixedDelay,
                   http_fault.mutable_delay()->mutable_fixed_delay());

  SetFilterConfig(http_fault);
  ClientContext context;
  context.set_deadline(
      grpc_timeout_milliseconds_to_deadline(kRpcTimeout.millis()));
  auto stream = stub_->BidiStream(&context);
  stream->WritesDone();
  auto status = stream->Finish();
  EXPECT_TRUE(status.ok()) << status.error_message() << ", "
                           << status.error_details() << ", "
                           << context.debug_error_string();
}

TEST_P(FaultInjectionTest, XdsFaultInjectionBidiStreamDelayError) {
  CreateAndStartBackends(1);
  const auto kRpcTimeout = grpc_core::Duration::Seconds(10);
  const auto kFixedDelay = grpc_core::Duration::Seconds(30);
  const uint32_t kDelayPercentagePerHundred = 100;

  EdsResourceArgs args({{"locality0", CreateEndpointsForBackends()}});
  balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));

  HTTPFault http_fault;
  auto* delay_percentage = http_fault.mutable_delay()->mutable_percentage();
  delay_percentage->set_numerator(kDelayPercentagePerHundred);
  delay_percentage->set_denominator(FractionalPercent::HUNDRED);
  SetProtoDuration(kFixedDelay,
                   http_fault.mutable_delay()->mutable_fixed_delay());

  SetFilterConfig(http_fault);
  ClientContext context;
  context.set_deadline(
      grpc_timeout_milliseconds_to_deadline(kRpcTimeout.millis()));
  auto stream = stub_->BidiStream(&context);
  stream->WritesDone();
  auto status = stream->Finish();
  EXPECT_EQ(StatusCode::DEADLINE_EXCEEDED, status.error_code())
      << status.error_message() << ", " << status.error_details() << ", "
      << context.debug_error_string();
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
