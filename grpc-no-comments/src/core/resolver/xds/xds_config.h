
// Copyright 2019 gRPC authors.

#ifndef GRPC_SRC_CORE_RESOLVER_XDS_XDS_CONFIG_H
#define GRPC_SRC_CORE_RESOLVER_XDS_XDS_CONFIG_H

#include <memory>
#include <string>
#include <utility>
#include <variant>
#include <vector>

#include "absl/container/flat_hash_map.h"
#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"
#include "src/core/util/ref_counted.h"
#include "src/core/xds/grpc/xds_cluster.h"
#include "src/core/xds/grpc/xds_endpoint.h"
#include "src/core/xds/grpc/xds_listener.h"
#include "src/core/xds/grpc/xds_route_config.h"

namespace grpc_core {

struct XdsConfig : public RefCounted<XdsConfig> {

  std::shared_ptr<const XdsListenerResource> listener;

  std::shared_ptr<const XdsRouteConfigResource> route_config;

  const XdsRouteConfigResource::VirtualHost* virtual_host;

  struct ClusterConfig {

    std::shared_ptr<const XdsClusterResource> cluster;

    struct EndpointConfig {
      std::shared_ptr<const XdsEndpointResource> endpoints;
      std::string resolution_note;

      EndpointConfig(std::shared_ptr<const XdsEndpointResource> endpoints,
                     std::string resolution_note)
          : endpoints(std::move(endpoints)),
            resolution_note(std::move(resolution_note)) {}
      bool operator==(const EndpointConfig& other) const {
        return endpoints == other.endpoints &&
               resolution_note == other.resolution_note;
      }
    };

    struct AggregateConfig {
      std::vector<absl::string_view> leaf_clusters;

      explicit AggregateConfig(std::vector<absl::string_view> leaf_clusters)
          : leaf_clusters(std::move(leaf_clusters)) {}
      bool operator==(const AggregateConfig& other) const {
        return leaf_clusters == other.leaf_clusters;
      }
    };
    std::variant<EndpointConfig, AggregateConfig> children;

    ClusterConfig(std::shared_ptr<const XdsClusterResource> cluster,
                  std::shared_ptr<const XdsEndpointResource> endpoints,
                  std::string resolution_note);

    ClusterConfig(std::shared_ptr<const XdsClusterResource> cluster,
                  std::vector<absl::string_view> leaf_clusters);

    bool operator==(const ClusterConfig& other) const {
      return cluster == other.cluster && children == other.children;
    }
  };

  absl::flat_hash_map<std::string, absl::StatusOr<ClusterConfig>> clusters;

  std::string ToString() const;

  static absl::string_view ChannelArgName() {
    return GRPC_ARG_NO_SUBCHANNEL_PREFIX "xds_config";
  }
  static int ChannelArgsCompare(const XdsConfig* a, const XdsConfig* b) {
    return QsortCompare(a, b);
  }
  static constexpr bool ChannelArgUseConstPtr() { return true; }
};

}

#endif
