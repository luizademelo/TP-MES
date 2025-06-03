Here's the commented version of the code:

```c++
// Copyright 2018 gRPC authors.

#include "src/core/xds/grpc/xds_listener_parser.h"

#include <stdint.h>

#include <set>
#include <utility>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_format.h"
#include "absl/strings/str_join.h"
#include "envoy/config/core/v3/address.upb.h"
#include "envoy/config/core/v3/base.upb.h"
#include "envoy/config/core/v3/config_source.upb.h"
#include "envoy/config/core/v3/protocol.upb.h"
#include "envoy/config/listener/v3/api_listener.upb.h"
#include "envoy/config/listener/v3/listener.upb.h"
#include "envoy/config/listener/v3/listener.upbdefs.h"
#include "envoy/config/listener/v3/listener_components.upb.h"
#include "envoy/config/route/v3/route.upb.h"
#include "envoy/extensions/filters/network/http_connection_manager/v3/http_connection_manager.upb.h"
#include "envoy/extensions/filters/network/http_connection_manager/v3/http_connection_manager.upbdefs.h"
#include "envoy/extensions/transport_sockets/tls/v3/tls.upb.h"
#include "google/protobuf/any.upb.h"
#include "google/protobuf/duration.upb.h"
#include "google/protobuf/wrappers.upb.h"
#include "src/core/lib/address_utils/parse_address.h"
#include "src/core/lib/address_utils/sockaddr_utils.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/iomgr/sockaddr.h"
#include "src/core/util/down_cast.h"
#include "src/core/util/host_port.h"
#include "src/core/util/match.h"
#include "src/core/util/upb_utils.h"
#include "src/core/util/validation_errors.h"
#include "src/core/xds/grpc/xds_common_types.h"
#include "src/core/xds/grpc/xds_common_types_parser.h"
#include "src/core/xds/grpc/xds_route_config_parser.h"
#include "src/core/xds/xds_client/xds_resource_type.h"
#include "upb/text/encode.h"

namespace grpc_core {

namespace {

// Represents a filter chain configuration for a listener
struct FilterChain {
  // Represents matching criteria for a filter chain
  struct FilterChainMatch {
    uint32_t destination_port = 0;  // Destination port to match (0 means any)
    std::vector<XdsListenerResource::FilterChainMap::CidrRange> prefix_ranges; // Destination IP ranges
    XdsListenerResource::FilterChainMap::ConnectionSourceType source_type =
        XdsListenerResource::FilterChainMap::ConnectionSourceType::kAny; // Source type
    std::vector<XdsListenerResource::FilterChainMap::CidrRange>
        source_prefix_ranges; // Source IP ranges
    std::vector<uint32_t> source_ports; // Source ports
    std::vector<std::string> server_names; // Server names (SNI)
    std::string transport_protocol; // Transport protocol (e.g., "raw_buffer")
    std::vector<std::string> application_protocols; // ALPN protocols

    // Converts the match criteria to a string for logging/debugging
    std::string ToString() const;
  } filter_chain_match;

  // The actual filter chain data to use when this chain matches
  std::shared_ptr<XdsListenerResource::FilterChainData> filter_chain_data;
};

// Implementation of ToString() for FilterChainMatch
std::string FilterChain::FilterChainMatch::ToString() const {
  std::vector<std::string> contents;
  if (destination_port != 0) {
    contents.push_back(absl::StrCat("destination_port=", destination_port));
  }
  if (!prefix_ranges.empty()) {
    std::vector<std::string> prefix_ranges_content;
    prefix_ranges_content.reserve(prefix_ranges.size());
    for (const auto& range : prefix_ranges) {
      prefix_ranges_content.push_back(range.ToString());
    }
    contents.push_back(absl::StrCat(
        "prefix_ranges={", absl::StrJoin(prefix_ranges_content, ", "), "}"));
  }
  if (source_type == XdsListenerResource::FilterChainMap::ConnectionSourceType::
                         kSameIpOrLoopback) {
    contents.push_back("source_type=SAME_IP_OR_LOOPBACK");
  } else if (source_type == XdsListenerResource::FilterChainMap::
                                ConnectionSourceType::kExternal) {
    contents.push_back("source_type=EXTERNAL");
  }
  if (!source_prefix_ranges.empty()) {
    std::vector<std::string> source_prefix_ranges_content;
    source_prefix_ranges_content.reserve(source_prefix_ranges.size());
    for (const auto& range : source_prefix_ranges) {
      source_prefix_ranges_content.push_back(range.ToString());
    }
    contents.push_back(
        absl::StrCat("source_prefix_ranges={",
                     absl::StrJoin(source_prefix_ranges_content, ", "), "}"));
  }
  if (!source_ports.empty()) {
    contents.push_back(
        absl::StrCat("source_ports={", absl::StrJoin(source_ports, ", "), "}"));
  }
  if (!server_names.empty()) {
    contents.push_back(
        absl::StrCat("server_names={", absl::StrJoin(server_names, ", "), "}"));
  }
  if (!transport_protocol.empty()) {
    contents.push_back(absl::StrCat("transport_protocol=", transport_protocol));
  }
  if (!application_protocols.empty()) {
    contents.push_back(absl::StrCat("application_protocols={",
                                    absl::StrJoin(application_protocols, ", "),
                                    "}"));
  }
  return absl::StrCat("{", absl::StrJoin(contents, ", "), "}");
}

// Logs HttpConnectionManager configuration if tracing is enabled
void MaybeLogHttpConnectionManager(
    const XdsResourceType::DecodeContext& context,
    const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager*
        http_connection_manager_config) {
  if (GRPC_TRACE_FLAG_ENABLED(xds_client) && ABSL_VLOG_IS_ON(2)) {
    const upb_MessageDef* msg_type =
        envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_getmsgdef(
            context.symtab);
    char buf[10240];
    upb_TextEncode(
        reinterpret_cast<const upb_Message*>(http_connection_manager_config),
        msg_type, nullptr, 0, buf, sizeof(buf));
    VLOG(2) << "[xds_client " << context.client
            << "] HttpConnectionManager: " << buf;
  }
}

// Parses HttpConnectionManager configuration from an extension
XdsListenerResource::HttpConnectionManager HttpConnectionManagerParse(
    bool is_client, const XdsResourceType::DecodeContext& context,
    XdsExtension extension, ValidationErrors* errors) {
  // Validate extension type
  if (extension.type !=
      "envoy.extensions.filters.network.http_connection_manager.v3"
      ".HttpConnectionManager") {
    errors->AddError("unsupported filter type");
    return {};
  }
  
  // Get serialized config
  auto* serialized_hcm_config =
      std::get_if<absl::string_view>(&extension.value);
  if (serialized_hcm_config == nullptr) {
    errors->AddError("could not parse HttpConnectionManager config");
    return {};
  }
  
  // Parse protobuf
  const auto* http_connection_manager_proto =
      envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_parse(
          serialized_hcm_config->data(), serialized_hcm_config->size(),
          context.arena);
  if (http_connection_manager_proto == nullptr) {
    errors->AddError("could not parse HttpConnectionManager config");
    return {};
  }
  
  MaybeLogHttpConnectionManager(context, http_connection_manager_proto);
  XdsListenerResource::HttpConnectionManager http_connection_manager;

  // Validate xff_num_trusted_hops (must be 0)
  if (envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_xff_num_trusted_hops(
          http_connection_manager_proto) != 0) {
    ValidationErrors::ScopedField field(errors, ".xff_num_trusted_hops");
    errors->AddError("must be zero");
  }

  // Validate original_ip_detection_extensions (must be empty)
  {
    size_t size;
    envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_original_ip_detection_extensions(
        http_connection_manager_proto, &size);
    if (size != 0) {
      ValidationErrors::ScopedField field(errors,
                                          ".original_ip_detection_extensions");
      errors->AddError("must be empty");
    }
  }

  // Parse common HTTP protocol options
  const envoy_config_core_v3_HttpProtocolOptions* options =
      envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_common_http_protocol_options(
          http_connection_manager_proto);
  if (options != nullptr) {
    // Parse max stream duration
    const google_protobuf_Duration* duration =
        envoy_config_core_v3_HttpProtocolOptions_max_stream_duration(options);
    if (duration != nullptr) {
      ValidationErrors::ScopedField field(
          errors, ".common_http_protocol_options.max_stream_duration");
      http_connection_manager.http_max_stream_duration =
          ParseDuration(duration, errors);
    }
  }

  // Parse HTTP filters
  {
    ValidationErrors::ScopedField field(errors, ".http_filters");
    const auto& http_filter_registry =
        DownCast<const GrpcXdsBootstrap&>(context.client->bootstrap())
            .http_filter_registry();
    size_t num_filters = 0;
    const auto* http_filters =
        envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_http_filters(
            http_connection_manager_proto, &num_filters);
    std::set<absl::string_view> names_seen;
    const size_t original_error_size = errors->size();
    
    // Process each filter
    for (size_t i = 0; i < num_filters; ++i) {
      ValidationErrors::ScopedField field(errors, absl::StrCat("[", i, "]"));
      const auto* http_filter = http_filters[i];

      // Get filter name
      absl::string_view name = UpbStringToAbsl(
          envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter_name(
              http_filter));
      {
        ValidationErrors::ScopedField field(errors, ".name");
        if (name.empty()) {
          errors->AddError("empty filter name");
          continue;
        }
        if (names_seen.find(name) != names_seen.end()) {
          errors->AddError(absl::StrCat("duplicate HTTP filter name: ", name));
          continue;
        }
      }
      names_seen.insert(name);

      // Check if filter is optional
      const bool is_optional =
          envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter_is_optional(
              http_filter);

      // Parse filter config
      {
        ValidationErrors::ScopedField field(errors, ".typed_config");
        const google_protobuf_Any* typed_config =
            envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter_typed_config(
                http_filter);
        auto extension = ExtractXdsExtension(context, typed_config, errors);
        if (!extension.has_value()) continue;
        
        // Get filter implementation
        const XdsHttpFilterImpl* filter_impl =
            http_filter_registry.GetFilterForType(extension->type);
        if (filter_impl == nullptr) {
          if (!is_optional) errors->AddError("unsupported filter type");
          continue;
        }
        
        // Check if filter is supported on client/server
        if ((is_client && !filter_impl->IsSupportedOnClients()) ||
            (!is_client && !filter_impl->IsSupportedOnServers())) {
          if (!is_optional) {
            errors->AddError(absl::StrCat("filter is not supported on ",
                                          is_client ? "clients" : "servers"));
          }
          continue;
        }
        
        // Generate filter config
        std::optional<XdsHttpFilterImpl::FilterConfig> filter_config =
            filter_impl->GenerateFilterConfig(name, context,
                                              std::move(*extension), errors);
        if (filter_config.has_value()) {
          http_connection_manager.http_filters.emplace_back(
              XdsListenerResource::HttpConnectionManager::HttpFilter{
                  std::string(name), std::move(*filter_config)});
        }
      }
    }
    
    // Ensure at least one filter is present
    if (errors->size() == original_error_size &&
        http_connection_manager.http_filters.empty()) {
      errors->AddError("expected at least one HTTP filter");
    }

    // Validate filter chain ordering (terminal filters must be last)
    for (const auto& http_filter : http_connection_manager.http_filters) {
      const XdsHttpFilterImpl* filter_impl =
          http_filter_registry.GetFilterForType(
              http_filter.config.config_proto_type_name);
      if (&http_filter != &http_connection_manager.http_filters.back()) {
        // Not the last filter - shouldn't be terminal
        if (filter_impl->IsTerminalFilter()) {
          errors->AddError(
              absl::StrCat("terminal filter for config type ",
                           http_filter.config.config_proto_type_name,
                           " must be the last filter in the chain"));
        }
      } else {
        // Last filter - must be terminal
        if (!filter_impl->IsTerminalFilter()) {
          errors->AddError(
              absl::StrCat("non-terminal filter for config type ",
                           http_filter.config.config_proto_type_name,
                           " is the last filter in the chain"));
        }
      }
    }
  }

  // Parse route configuration
  if (envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_has_route_config(
          http_connection_manager_proto)) {
    // Static route config
    const envoy_config_route_v3_RouteConfiguration* route_config =
        envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_route_config(
            http_connection_manager_proto);
    ValidationErrors::ScopedField field(errors, ".route_config");
    http_connection_manager.route_config =
        XdsRouteConfigResourceParse(context, route_config, errors);
  } else {
    // RDS config
    const envoy_extensions_filters_network_http_connection_manager_v3_Rds* rds =
        envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_rds(
            http_connection_manager_proto);
    if (rds == nullptr) {
      errors->AddError("neither route_config nor rds fields are present");
    } else {
      // Get route config name
      http_connection_manager.route_config = UpbStringToStdString(
          envoy_extensions_filters_network_http_connection_manager_v3_Rds_route_config_name(
              rds));

      // Validate config source
      const envoy_config_core_v3_ConfigSource* config_source =
          envoy_extensions_filters_network_http_connection_manager_v3_Rds_config_source(
              rds);
      ValidationErrors::ScopedField field(errors, ".rds.config_source");
      if (config_source == nullptr) {
        errors->AddError("field not present");
      } else if (!envoy_config_core_v3_ConfigSource_has_ads(config_source) &&
                 !envoy_config_core_v3_ConfigSource_has_self(config_source)) {
        errors->AddError("ConfigSource does not specify ADS or SELF");
      }
    }
  }
  return http_connection_manager;
}

// Parses a client-side Listener resource with ApiListener
absl::StatusOr<std::shared_ptr<const XdsListenerResource>>
LdsResourceParseClient(
    const XdsResourceType::DecodeContext& context,
    const envoy_config_listener_v3_ApiListener* api_listener) {
  auto lds_update = std::make_shared<XdsListenerResource>();
  ValidationErrors errors;
  ValidationErrors::ScopedField field(&errors, "api_listener.api_listener");
  auto* api_listener_field =
      envoy_config_listener_v3_ApiListener_api_listener(api_listener);
  auto extension = ExtractXdsExtension(context, api_listener_field, &errors);
  if (extension.has_value()) {
    lds_update->listener = HttpConnectionManagerParse(
        true, context, std::move(*extension), &errors);
  }
  if (!errors.ok()) {
    return errors.status(absl::StatusCode::kInvalidArgument,
                         "errors validating ApiListener");
  }
  return std::move(lds_update);
}

// Parses DownstreamTlsContext configuration
XdsListenerResource::DownstreamTlsContext DownstreamTlsContextParse(
    const XdsResourceType::DecodeContext& context,
    const envoy_config_core_v3_TransportSocket* transport_socket,
    ValidationErrors* errors) {
  ValidationErrors::ScopedField field(errors, ".typed_config");
  const auto* typed_config =
      envoy_config_core_v3_TransportSocket_typed_config(transport_socket);
  auto extension = ExtractXdsExtension(context, typed_config, errors);
  if (!extension.has_value()) return {};
  
  // Validate extension type
  if (extension->type !=
      "envoy.extensions.transport_sockets.tls.v3.DownstreamTlsContext") {
    ValidationErrors::ScopedField field(errors, ".type_url");
    errors->AddError("unsupported transport socket type");
    return {};
  }