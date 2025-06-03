Here's the commented version of the code:

```c++
// Copyright 2018 gRPC authors.

#ifndef GRPC_SRC_CORE_XDS_GRPC_XDS_ROUTE_CONFIG_H
#define GRPC_SRC_CORE_XDS_GRPC_XDS_ROUTE_CONFIG_H

#include <stdint.h>

#include <algorithm>
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <variant>
#include <vector>

#include "re2/re2.h"
#include "src/core/call/status_util.h"
#include "src/core/util/matchers.h"
#include "src/core/util/time.h"
#include "src/core/xds/grpc/xds_http_filter.h"
#include "src/core/xds/xds_client/xds_resource_type.h"
#include "src/core/xds/xds_client/xds_resource_type_impl.h"

namespace grpc_core {

// XdsRouteConfigResource represents xDS Route Configuration resource data.
// It contains route configuration details including virtual hosts,
// routes, and cluster specifications.
struct XdsRouteConfigResource : public XdsResourceType::ResourceData {
  // TypedPerFilterConfig stores filter-specific configuration per filter name.
  using TypedPerFilterConfig =
      std::map<std::string, XdsHttpFilterImpl::FilterConfig>;

  // ClusterSpecifierPluginMap maps plugin names to their configurations.
  using ClusterSpecifierPluginMap =
      std::map<std::string, std::string>;

  // RetryPolicy defines the retry behavior for failed requests.
  struct RetryPolicy {
    // Status codes that should trigger retries.
    internal::StatusCodeSet retry_on;
    // Maximum number of retry attempts.
    uint32_t num_retries;

    // RetryBackOff defines the backoff policy for retries.
    struct RetryBackOff {
      // Initial retry delay.
      Duration base_interval;
      // Maximum retry delay.
      Duration max_interval;

      bool operator==(const RetryBackOff& other) const {
        return base_interval == other.base_interval &&
               max_interval == other.max_interval;
      }
      std::string ToString() const;
    };
    RetryBackOff retry_back_off;

    bool operator==(const RetryPolicy& other) const {
      return (retry_on == other.retry_on && num_retries == other.num_retries &&
              retry_back_off == other.retry_back_off);
    }
    std::string ToString() const;
  };

  // Route defines a single route with matching criteria and actions.
  struct Route {
    // Matchers defines the criteria for matching requests to this route.
    struct Matchers {
      // Path matcher for the route.
      StringMatcher path_matcher;
      // Header matchers for the route.
      std::vector<HeaderMatcher> header_matchers;
      // Fraction of requests that should be matched (in millionths).
      std::optional<uint32_t> fraction_per_million;

      bool operator==(const Matchers& other) const {
        return path_matcher == other.path_matcher &&
               header_matchers == other.header_matchers &&
               fraction_per_million == other.fraction_per_million;
      }
      std::string ToString() const;
    };

    Matchers matchers;

    // UnknownAction represents an undefined route action.
    struct UnknownAction {
      bool operator==(const UnknownAction&) const { return true; }
    };

    // RouteAction defines what to do when a route is matched.
    struct RouteAction {
      // HashPolicy defines how to compute hash for load balancing.
      struct HashPolicy {
        // Header defines hash computation based on request headers.
        struct Header {
          std::string header_name;
          std::unique_ptr<RE2> regex;
          std::string regex_substitution;

          Header() = default;

          Header(const Header& other);
          Header& operator=(const Header& other);

          Header(Header&& other) noexcept;
          Header& operator=(Header&& other) noexcept;

          bool operator==(const Header& other) const;
          std::string ToString() const;
        };

        // ChannelId defines hash computation based on channel ID.
        struct ChannelId {
          bool operator==(const ChannelId&) const { return true; }
        };

        std::variant<Header, ChannelId> policy;
        // If true, subsequent hash policies will be ignored.
        bool terminal = false;

        bool operator==(const HashPolicy& other) const {
          return policy == other.policy && terminal == other.terminal;
        }
        std::string ToString() const;
      };

      // ClusterName defines a direct route to a single cluster.
      struct ClusterName {
        std::string cluster_name;

        bool operator==(const ClusterName& other) const {
          return cluster_name == other.cluster_name;
        }
      };

      // ClusterWeight defines a weighted set of clusters for traffic splitting.
      struct ClusterWeight {
        std::string name;
        uint32_t weight;
        TypedPerFilterConfig typed_per_filter_config;

        bool operator==(const ClusterWeight& other) const {
          return name == other.name && weight == other.weight &&
                 typed_per_filter_config == other.typed_per_filter_config;
        }
        std::string ToString() const;
      };

      // ClusterSpecifierPluginName defines a route using a cluster specifier plugin.
      struct ClusterSpecifierPluginName {
        std::string cluster_specifier_plugin_name;

        bool operator==(const ClusterSpecifierPluginName& other) const {
          return cluster_specifier_plugin_name ==
                 other.cluster_specifier_plugin_name;
        }
      };

      std::vector<HashPolicy> hash_policies;
      std::optional<RetryPolicy> retry_policy;

      // Action can be either a direct cluster, weighted clusters, or plugin.
      std::variant<ClusterName, std::vector<ClusterWeight>,
                   ClusterSpecifierPluginName>
          action;

      // Maximum duration for the stream.
      std::optional<Duration> max_stream_duration;

      // If true, automatically rewrite the Host header.
      bool auto_host_rewrite = false;

      bool operator==(const RouteAction& other) const {
        return hash_policies == other.hash_policies &&
               retry_policy == other.retry_policy && action == other.action &&
               max_stream_duration == other.max_stream_duration &&
               auto_host_rewrite == other.auto_host_rewrite;
      }
      std::string ToString() const;
    };

    // NonForwardingAction represents an action that doesn't forward requests.
    struct NonForwardingAction {
      bool operator==(const NonForwardingAction&) const {
        return true;
      }
    };

    // Action can be unknown, route, or non-forwarding.
    std::variant<UnknownAction, RouteAction, NonForwardingAction> action;
    // Filter-specific configuration for this route.
    TypedPerFilterConfig typed_per_filter_config;

    bool operator==(const Route& other) const {
      return matchers == other.matchers && action == other.action &&
             typed_per_filter_config == other.typed_per_filter_config;
    }
    std::string ToString() const;
  };

  // VirtualHost represents a set of routes for a set of domains.
  struct VirtualHost {
    // List of domains (host/authority header values) this VirtualHost matches.
    std::vector<std::string> domains;
    // List of routes for this VirtualHost.
    std::vector<Route> routes;
    // Filter-specific configuration for this VirtualHost.
    TypedPerFilterConfig typed_per_filter_config;

    bool operator==(const VirtualHost& other) const {
      return domains == other.domains && routes == other.routes &&
             typed_per_filter_config == other.typed_per_filter_config;
    }
    std::string ToString() const;
  };

  // List of VirtualHosts in this route configuration.
  std::vector<VirtualHost> virtual_hosts;
  // Map of cluster specifier plugins.
  ClusterSpecifierPluginMap cluster_specifier_plugin_map;

  bool operator==(const XdsRouteConfigResource& other) const {
    return virtual_hosts == other.virtual_hosts &&
           cluster_specifier_plugin_map == other.cluster_specifier_plugin_map;
  }
  std::string ToString() const;
};

}  // namespace grpc_core

#endif  // GRPC_SRC_CORE_XDS_GRPC_XDS_ROUTE_CONFIG_H
```

The comments added:
1. Describe the overall purpose of each major struct
2. Explain the purpose of each field in the structs
3. Clarify the relationships between different components
4. Note important implementation details
5. Maintain consistency with existing code style
6. Provide context for complex or non-obvious functionality

The comments are designed to help future developers understand:
- What each component does
- How components relate to each other
- Important behavioral characteristics
- The purpose of configuration options