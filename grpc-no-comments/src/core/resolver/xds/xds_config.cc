
// Copyright 2019 gRPC authors.

#include "src/core/resolver/xds/xds_config.h"

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "absl/strings/str_cat.h"
#include "absl/strings/str_join.h"
#include "src/core/util/match.h"

namespace grpc_core {

XdsConfig::ClusterConfig::ClusterConfig(
    std::shared_ptr<const XdsClusterResource> cluster,
    std::shared_ptr<const XdsEndpointResource> endpoints,
    std::string resolution_note)
    : cluster(std::move(cluster)),
      children(absl::in_place_type_t<EndpointConfig>(), std::move(endpoints),
               std::move(resolution_note)) {}

XdsConfig::ClusterConfig::ClusterConfig(
    std::shared_ptr<const XdsClusterResource> cluster,
    std::vector<absl::string_view> leaf_clusters)
    : cluster(std::move(cluster)),
      children(absl::in_place_type_t<AggregateConfig>(),
               std::move(leaf_clusters)) {}

std::string XdsConfig::ToString() const {
  std::vector<std::string> parts = {
      "{\n  listener: {",     listener->ToString(),
      "}\n  route_config: {", route_config->ToString(),
      "}\n  virtual_host: {", virtual_host->ToString(),
      "}\n  clusters: {\n"};
  for (const auto& [name, cluster_config] : clusters) {
    parts.push_back(absl::StrCat("    \"", name, "\": "));
    if (!cluster_config.ok()) {
      parts.push_back(cluster_config.status().ToString());
      parts.push_back("\n");
    } else {
      parts.push_back(
          absl::StrCat("      {\n"
                       "        cluster: {",
                       cluster_config->cluster->ToString(), "}\n"));
      Match(
          cluster_config->children,
          [&](const ClusterConfig::EndpointConfig& endpoint_config) {
            parts.push_back(
                absl::StrCat("        endpoints: {",
                             endpoint_config.endpoints == nullptr
                                 ? "<null>"
                                 : endpoint_config.endpoints->ToString(),
                             "}\n"
                             "        resolution_note: \"",
                             endpoint_config.resolution_note, "\"\n"));
          },
          [&](const ClusterConfig::AggregateConfig& aggregate_config) {
            parts.push_back(absl::StrCat(
                "        leaf_clusters: [",
                absl::StrJoin(aggregate_config.leaf_clusters, ", "), "]\n"));
          });
      parts.push_back(
          "      }\n"
          "    ]\n");
    }
  }
  parts.push_back("  }\n}");
  return absl::StrJoin(parts, "");
}

}
