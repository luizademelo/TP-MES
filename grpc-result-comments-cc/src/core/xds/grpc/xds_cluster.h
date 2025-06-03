Here's the commented version of the code:

```c++
// Copyright 2018 gRPC authors.

#ifndef GRPC_SRC_CORE_XDS_GRPC_XDS_CLUSTER_H
#define GRPC_SRC_CORE_XDS_GRPC_XDS_CLUSTER_H

#include <optional>
#include <string>
#include <variant>
#include <vector>

#include "absl/container/flat_hash_map.h"
#include "src/core/load_balancing/outlier_detection/outlier_detection.h"
#include "src/core/util/json/json.h"
#include "src/core/xds/grpc/xds_common_types.h"
#include "src/core/xds/grpc/xds_health_status.h"
#include "src/core/xds/grpc/xds_metadata.h"
#include "src/core/xds/grpc/xds_server_grpc.h"
#include "src/core/xds/xds_client/xds_backend_metric_propagation.h"
#include "src/core/xds/xds_client/xds_resource_type.h"
#include "src/core/xds/xds_client/xds_resource_type_impl.h"

namespace grpc_core {

// Compares two LRS (Load Reporting Service) server targets for equality.
// Returns true if both are null or if both point to equivalent server targets.
inline bool LrsServersEqual(
    const std::shared_ptr<const GrpcXdsServerTarget>& lrs_server1,
    const std::shared_ptr<const GrpcXdsServerTarget>& lrs_server2) {
  if (lrs_server1 == nullptr) return lrs_server2 == nullptr;
  if (lrs_server2 == nullptr) return false;
  return *lrs_server1 == *lrs_server2;
}

// Compares two BackendMetricPropagation instances for equality.
// Returns true if both are null or if both point to equivalent instances.
inline bool LrsBackendMetricPropagationEqual(
    const RefCountedPtr<const BackendMetricPropagation>& p1,
    const RefCountedPtr<const BackendMetricPropagation>& p2) {
  if (p1 == nullptr) return p2 == nullptr;
  if (p2 == nullptr) return false;
  return *p1 == *p2;
}

// Represents an xDS Cluster resource containing configuration for how
// gRPC clients should connect to upstream services.
struct XdsClusterResource : public XdsResourceType::ResourceData {
  // Configuration for EDS (Endpoint Discovery Service) based clusters
  struct Eds {
    std::string eds_service_name;  // The EDS service name to use for discovery

    bool operator==(const Eds& other) const {
      return eds_service_name == other.eds_service_name;
    }
  };

  // Configuration for logical DNS based clusters
  struct LogicalDns {
    std::string hostname;  // The DNS hostname to resolve

    bool operator==(const LogicalDns& other) const {
      return hostname == other.hostname;
    }
  };

  // Configuration for aggregate clusters that combine multiple clusters
  struct Aggregate {
    // List of cluster names in priority order
    std::vector<std::string> prioritized_cluster_names;

    bool operator==(const Aggregate& other) const {
      return prioritized_cluster_names == other.prioritized_cluster_names;
    }
  };

  // The cluster type, which can be one of Eds, LogicalDns, or Aggregate
  std::variant<Eds, LogicalDns, Aggregate> type;

  // Load balancing policy configuration in JSON format
  Json::Array lb_policy_config;

  // Note: Remaining fields are not used for aggregate clusters.

  // Optional LRS server for load reporting
  std::shared_ptr<const GrpcXdsServerTarget> lrs_load_reporting_server;

  // Configuration for backend metric propagation
  RefCountedPtr<const BackendMetricPropagation> lrs_backend_metric_propagation;

  // Whether to use HTTP CONNECT for proxying
  bool use_http_connect = false;

  // TLS context configuration for secure connections
  CommonTlsContext common_tls_context;

  // Timeout for idle connections before they are closed
  Duration connection_idle_timeout = Duration::Hours(1);

  // Maximum number of concurrent requests allowed
  uint32_t max_concurrent_requests = 1024;

  // Optional outlier detection configuration
  std::optional<OutlierDetectionConfig> outlier_detection;

  // Set of health statuses that can override host status
  XdsHealthStatusSet override_host_statuses;

  // Additional metadata associated with the cluster
  XdsMetadataMap metadata;

  // Equality comparison operator for XdsClusterResource
  bool operator==(const XdsClusterResource& other) const {
    return type == other.type && lb_policy_config == other.lb_policy_config &&
           LrsServersEqual(lrs_load_reporting_server,
                           other.lrs_load_reporting_server) &&
           LrsBackendMetricPropagationEqual(
               lrs_backend_metric_propagation,
               other.lrs_backend_metric_propagation) &&
           common_tls_context == other.common_tls_context &&
           connection_idle_timeout == other.connection_idle_timeout &&
           max_concurrent_requests == other.max_concurrent_requests &&
           outlier_detection == other.outlier_detection &&
           override_host_statuses == other.override_host_statuses &&
           metadata == other.metadata;
  }

  // Returns a string representation of the cluster resource
  std::string ToString() const;
};

}  // namespace grpc_core

#endif  // GRPC_SRC_CORE_XDS_GRPC_XDS_CLUSTER_H
```

The comments added explain:
1. The purpose of each struct and its components
2. The meaning of important fields
3. The functionality of comparison operators
4. The relationship between different components
5. Default values where applicable
6. The overall purpose of the XdsClusterResource struct

The comments are concise yet informative, helping future developers understand both the high-level purpose and implementation details of the code.