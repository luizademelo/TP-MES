
// Copyright 2018 gRPC authors.

#ifndef GRPC_TEST_CORE_TEST_UTIL_TEST_LB_POLICIES_H
#define GRPC_TEST_CORE_TEST_UTIL_TEST_LB_POLICIES_H

#include <grpc/support/port_platform.h>

#include <atomic>
#include <functional>
#include <string>
#include <utility>
#include <vector>

#include "absl/status/status.h"
#include "absl/strings/string_view.h"
#include "src/core/config/core_configuration.h"
#include "src/core/load_balancing/backend_metric_data.h"
#include "src/core/resolver/endpoint_addresses.h"

namespace grpc_core {

using MetadataVector = std::vector<std::pair<std::string, std::string>>;

struct PickArgsSeen {
  std::string path;
  MetadataVector metadata;
};

using TestPickArgsCallback = std::function<void(const PickArgsSeen&)>;

void RegisterTestPickArgsLoadBalancingPolicy(
    CoreConfiguration::Builder* builder, TestPickArgsCallback cb,
    absl::string_view delegate_policy_name = "pick_first");

struct TrailingMetadataArgsSeen {
  absl::Status status;
  const BackendMetricData* backend_metric_data;
  MetadataVector metadata;
};

using InterceptRecvTrailingMetadataCallback =
    std::function<void(const TrailingMetadataArgsSeen&)>;

void RegisterInterceptRecvTrailingMetadataLoadBalancingPolicy(
    CoreConfiguration::Builder* builder,
    InterceptRecvTrailingMetadataCallback cb);

using AddressTestCallback = std::function<void(const EndpointAddresses&)>;

void RegisterAddressTestLoadBalancingPolicy(CoreConfiguration::Builder* builder,
                                            AddressTestCallback cb);

void RegisterFixedAddressLoadBalancingPolicy(
    CoreConfiguration::Builder* builder);

using OobBackendMetricCallback =
    std::function<void(EndpointAddresses, const BackendMetricData&)>;

void RegisterOobBackendMetricTestLoadBalancingPolicy(
    CoreConfiguration::Builder* builder, OobBackendMetricCallback cb);

void RegisterFailLoadBalancingPolicy(CoreConfiguration::Builder* builder,
                                     absl::Status status,
                                     std::atomic<int>* pick_counter = nullptr);

void RegisterQueueOnceLoadBalancingPolicy(CoreConfiguration::Builder* builder);

#define GRPC_ARG_TEST_LB_AUTHORITY_OVERRIDE "grpc.test.lb_authority_override"
void RegisterAuthorityOverrideLoadBalancingPolicy(
    CoreConfiguration::Builder* builder);

}

#endif
