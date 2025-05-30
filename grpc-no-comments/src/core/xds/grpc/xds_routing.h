
// Copyright 2021 gRPC authors.

#ifndef GRPC_SRC_CORE_XDS_GRPC_XDS_ROUTING_H
#define GRPC_SRC_CORE_XDS_GRPC_XDS_ROUTING_H

#include <grpc/support/port_platform.h>
#include <stddef.h>

#include <map>
#include <optional>
#include <string>
#include <vector>

#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"
#include "src/core/call/metadata_batch.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/xds/grpc/xds_http_filter_registry.h"
#include "src/core/xds/grpc/xds_listener.h"
#include "src/core/xds/grpc/xds_route_config.h"

namespace grpc_core {

class XdsRouting final {
 public:
  class VirtualHostListIterator {
   public:
    virtual ~VirtualHostListIterator() = default;

    virtual size_t Size() const = 0;

    virtual const std::vector<std::string>& GetDomainsForVirtualHost(
        size_t index) const = 0;
  };

  class RouteListIterator {
   public:
    virtual ~RouteListIterator() = default;

    virtual size_t Size() const = 0;

    virtual const XdsRouteConfigResource::Route::Matchers& GetMatchersForRoute(
        size_t index) const = 0;
  };

  static std::optional<size_t> FindVirtualHostForDomain(
      const VirtualHostListIterator& vhost_iterator, absl::string_view domain);

  static std::optional<size_t> GetRouteForRequest(
      const RouteListIterator& route_list_iterator, absl::string_view path,
      grpc_metadata_batch* initial_metadata);

  static bool IsValidDomainPattern(absl::string_view domain_pattern);

  static std::optional<absl::string_view> GetHeaderValue(
      grpc_metadata_batch* initial_metadata, absl::string_view header_name,
      std::string* concatenated_value);

  struct GeneratePerHttpFilterConfigsResult {

    std::map<std::string, std::vector<std::string>> per_filter_configs;
    ChannelArgs args;
  };

  static absl::StatusOr<GeneratePerHttpFilterConfigsResult>
  GeneratePerHTTPFilterConfigsForMethodConfig(
      const XdsHttpFilterRegistry& http_filter_registry,
      const std::vector<XdsListenerResource::HttpConnectionManager::HttpFilter>&
          http_filters,
      const XdsRouteConfigResource::VirtualHost& vhost,
      const XdsRouteConfigResource::Route& route,
      const XdsRouteConfigResource::Route::RouteAction::ClusterWeight*
          cluster_weight,
      const ChannelArgs& args);

  static absl::StatusOr<GeneratePerHttpFilterConfigsResult>
  GeneratePerHTTPFilterConfigsForServiceConfig(
      const XdsHttpFilterRegistry& http_filter_registry,
      const std::vector<XdsListenerResource::HttpConnectionManager::HttpFilter>&
          http_filters,
      const ChannelArgs& args);
};

}

#endif
