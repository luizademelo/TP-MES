Here's the commented version of the code:

```c++
// Copyright 2018 gRPC authors.

#ifndef GRPC_SRC_CORE_XDS_GRPC_XDS_LISTENER_H
#define GRPC_SRC_CORE_XDS_GRPC_XDS_LISTENER_H

#include <stdint.h>
#include <string.h>

#include <algorithm>
#include <array>
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <variant>
#include <vector>

#include "src/core/lib/iomgr/resolved_address.h"
#include "src/core/util/time.h"
#include "src/core/xds/grpc/xds_common_types.h"
#include "src/core/xds/grpc/xds_http_filter.h"
#include "src/core/xds/grpc/xds_route_config.h"
#include "src/core/xds/xds_client/xds_resource_type.h"
#include "src/core/xds/xds_client/xds_resource_type_impl.h"

namespace grpc_core {

// XdsListenerResource represents an xDS Listener resource, containing
// configuration for how the server should handle incoming connections.
struct XdsListenerResource : public XdsResourceType::ResourceData {
  // HttpConnectionManager contains configuration for HTTP connections
  struct HttpConnectionManager {
    // Route configuration can be either:
    // 1. A direct string reference to a route config resource
    // 2. An inline route config resource
    std::variant<std::string, std::shared_ptr<const XdsRouteConfigResource>>
        route_config;

    // Maximum duration for HTTP streams
    Duration http_max_stream_duration;

    // Configuration for an HTTP filter
    struct HttpFilter {
      std::string name;  // Name of the filter
      XdsHttpFilterImpl::FilterConfig config;  // Filter-specific configuration

      // Equality comparison operator
      bool operator==(const HttpFilter& other) const {
        return name == other.name && config == other.config;
      }

      // Returns a string representation of the filter
      std::string ToString() const;
    };
    
    // List of HTTP filters to apply
    std::vector<HttpFilter> http_filters;

    // Equality comparison operator
    bool operator==(const HttpConnectionManager& other) const {
      if (std::holds_alternative<std::string>(route_config)) {
        if (route_config != other.route_config) return false;
      } else {
        auto& rc1 = std::get<std::shared_ptr<const XdsRouteConfigResource>>(
            route_config);
        auto* rc2 = std::get_if<std::shared_ptr<const XdsRouteConfigResource>>(
            &other.route_config);
        if (rc2 == nullptr) return false;
        if (!(*rc1 == **rc2)) return false;
      }
      return http_max_stream_duration == other.http_max_stream_duration &&
             http_filters == other.http_filters;
    }

    // Returns a string representation of the HTTP connection manager
    std::string ToString() const;
  };

  // DownstreamTlsContext contains TLS configuration for downstream connections
  struct DownstreamTlsContext {
    DownstreamTlsContext() {}

    // Common TLS context settings
    CommonTlsContext common_tls_context;
    // Whether client certificates are required
    bool require_client_certificate = false;

    // Equality comparison operator
    bool operator==(const DownstreamTlsContext& other) const {
      return common_tls_context == other.common_tls_context &&
             require_client_certificate == other.require_client_certificate;
    }

    // Returns a string representation of the TLS context
    std::string ToString() const;
    // Checks if the TLS context is empty
    bool Empty() const;
  };

  // FilterChainData contains configuration for a filter chain
  struct FilterChainData {
    // TLS configuration for downstream connections
    DownstreamTlsContext downstream_tls_context;

    // HTTP connection manager configuration
    HttpConnectionManager http_connection_manager;

    // Equality comparison operator
    bool operator==(const FilterChainData& other) const {
      return downstream_tls_context == other.downstream_tls_context &&
             http_connection_manager == other.http_connection_manager;
    }

    // Returns a string representation of the filter chain
    std::string ToString() const;
  };

  // FilterChainMap contains mappings for filter chains based on connection properties
  struct FilterChainMap {
    // Wrapper for shared pointer to FilterChainData with equality comparison
    struct FilterChainDataSharedPtr {
      std::shared_ptr<FilterChainData> data;
      bool operator==(const FilterChainDataSharedPtr& other) const {
        return *data == *other.data;
      }
    };
    
    // Represents a CIDR range for IP address matching
    struct CidrRange {
      grpc_resolved_address address;  // IP address
      uint32_t prefix_len;            // Prefix length for CIDR range

      // Equality comparison operator
      bool operator==(const CidrRange& other) const {
        return memcmp(&address, &other.address, sizeof(address)) == 0 &&
               prefix_len == other.prefix_len;
      }

      // Returns a string representation of the CIDR range
      std::string ToString() const;
    };
    
    // Maps source ports to filter chain data
    using SourcePortsMap = std::map<uint16_t, FilterChainDataSharedPtr>;
    
    // Represents source IP configuration
    struct SourceIp {
      std::optional<CidrRange> prefix_range;  // Optional CIDR range for source IP
      SourcePortsMap ports_map;               // Port mappings for this source IP

      // Equality comparison operator
      bool operator==(const SourceIp& other) const {
        return prefix_range == other.prefix_range &&
               ports_map == other.ports_map;
      }
    };
    
    using SourceIpVector = std::vector<SourceIp>;
    
    // Enum for connection source types
    enum class ConnectionSourceType { kAny = 0, kSameIpOrLoopback, kExternal };
    
    // Array of source IP vectors indexed by connection source type
    using ConnectionSourceTypesArray = std::array<SourceIpVector, 3>;
    
    // Represents destination IP configuration
    struct DestinationIp {
      std::optional<CidrRange> prefix_range;  // Optional CIDR range for destination IP

      // Source type configurations for this destination IP
      ConnectionSourceTypesArray source_types_array;

      // Equality comparison operator
      bool operator==(const DestinationIp& other) const {
        return prefix_range == other.prefix_range &&
               source_types_array == other.source_types_array;
      }
    };

    // Vector of destination IP configurations
    using DestinationIpVector = std::vector<DestinationIp>;
    DestinationIpVector destination_ip_vector;

    // Equality comparison operator
    bool operator==(const FilterChainMap& other) const {
      return destination_ip_vector == other.destination_ip_vector;
    }

    // Returns a string representation of the filter chain map
    std::string ToString() const;
  };

  // TcpListener contains configuration for TCP listeners
  struct TcpListener {
    std::string address;  // Listener address
    FilterChainMap filter_chain_map;  // Filter chain mappings
    std::optional<FilterChainData> default_filter_chain;  // Optional default filter chain

    // Equality comparison operator
    bool operator==(const TcpListener& other) const {
      return address == other.address &&
             filter_chain_map == other.filter_chain_map &&
             default_filter_chain == other.default_filter_chain;
    }

    // Returns a string representation of the TCP listener
    std::string ToString() const;
  };

  // Listener can be either an HTTP connection manager or TCP listener
  std::variant<HttpConnectionManager, TcpListener> listener;

  // Equality comparison operator
  bool operator==(const XdsListenerResource& other) const {
    return listener == other.listener;
  }

  // Returns a string representation of the listener resource
  std::string ToString() const;
};

}  // namespace grpc_core

#endif
```

The comments provide:
1. Overview of each major component
2. Explanation of key data structures and their relationships
3. Purpose of each member variable
4. Behavior of comparison operators
5. Functionality of ToString() methods
6. Clarification of complex types like variants and optionals

The comments are concise yet informative, helping future developers understand the structure and purpose of the code without being overly verbose.