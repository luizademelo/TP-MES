
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

struct XdsListenerResource : public XdsResourceType::ResourceData {
  struct HttpConnectionManager {

    std::variant<std::string, std::shared_ptr<const XdsRouteConfigResource>>
        route_config;

    Duration http_max_stream_duration;

    struct HttpFilter {
      std::string name;
      XdsHttpFilterImpl::FilterConfig config;

      bool operator==(const HttpFilter& other) const {
        return name == other.name && config == other.config;
      }

      std::string ToString() const;
    };
    std::vector<HttpFilter> http_filters;

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

    std::string ToString() const;
  };

  struct DownstreamTlsContext {
    DownstreamTlsContext() {}

    CommonTlsContext common_tls_context;
    bool require_client_certificate = false;

    bool operator==(const DownstreamTlsContext& other) const {
      return common_tls_context == other.common_tls_context &&
             require_client_certificate == other.require_client_certificate;
    }

    std::string ToString() const;
    bool Empty() const;
  };

  struct FilterChainData {
    DownstreamTlsContext downstream_tls_context;

    HttpConnectionManager http_connection_manager;

    bool operator==(const FilterChainData& other) const {
      return downstream_tls_context == other.downstream_tls_context &&
             http_connection_manager == other.http_connection_manager;
    }

    std::string ToString() const;
  };

  struct FilterChainMap {
    struct FilterChainDataSharedPtr {
      std::shared_ptr<FilterChainData> data;
      bool operator==(const FilterChainDataSharedPtr& other) const {
        return *data == *other.data;
      }
    };
    struct CidrRange {
      grpc_resolved_address address;
      uint32_t prefix_len;

      bool operator==(const CidrRange& other) const {
        return memcmp(&address, &other.address, sizeof(address)) == 0 &&
               prefix_len == other.prefix_len;
      }

      std::string ToString() const;
    };
    using SourcePortsMap = std::map<uint16_t, FilterChainDataSharedPtr>;
    struct SourceIp {
      std::optional<CidrRange> prefix_range;
      SourcePortsMap ports_map;

      bool operator==(const SourceIp& other) const {
        return prefix_range == other.prefix_range &&
               ports_map == other.ports_map;
      }
    };
    using SourceIpVector = std::vector<SourceIp>;
    enum class ConnectionSourceType { kAny = 0, kSameIpOrLoopback, kExternal };
    using ConnectionSourceTypesArray = std::array<SourceIpVector, 3>;
    struct DestinationIp {
      std::optional<CidrRange> prefix_range;

      ConnectionSourceTypesArray source_types_array;

      bool operator==(const DestinationIp& other) const {
        return prefix_range == other.prefix_range &&
               source_types_array == other.source_types_array;
      }
    };

    using DestinationIpVector = std::vector<DestinationIp>;
    DestinationIpVector destination_ip_vector;

    bool operator==(const FilterChainMap& other) const {
      return destination_ip_vector == other.destination_ip_vector;
    }

    std::string ToString() const;
  };

  struct TcpListener {
    std::string address;
    FilterChainMap filter_chain_map;
    std::optional<FilterChainData> default_filter_chain;

    bool operator==(const TcpListener& other) const {
      return address == other.address &&
             filter_chain_map == other.filter_chain_map &&
             default_filter_chain == other.default_filter_chain;
    }

    std::string ToString() const;
  };

  std::variant<HttpConnectionManager, TcpListener> listener;

  bool operator==(const XdsListenerResource& other) const {
    return listener == other.listener;
  }

  std::string ToString() const;
};

}

#endif
