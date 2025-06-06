// Copyright 2018 gRPC authors.

#include "src/core/xds/grpc/xds_cluster_parser.h"

#include <algorithm>
#include <memory>
#include <utility>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/strip.h"
#include "envoy/config/cluster/v3/circuit_breaker.upb.h"
#include "envoy/config/cluster/v3/cluster.upb.h"
#include "envoy/config/cluster/v3/cluster.upbdefs.h"
#include "envoy/config/cluster/v3/outlier_detection.upb.h"
#include "envoy/config/core/v3/address.upb.h"
#include "envoy/config/core/v3/base.upb.h"
#include "envoy/config/core/v3/config_source.upb.h"
#include "envoy/config/core/v3/extension.upb.h"
#include "envoy/config/core/v3/health_check.upb.h"
#include "envoy/config/core/v3/protocol.upb.h"
#include "envoy/config/endpoint/v3/endpoint.upb.h"
#include "envoy/config/endpoint/v3/endpoint_components.upb.h"
#include "envoy/extensions/clusters/aggregate/v3/cluster.upb.h"
#include "envoy/extensions/transport_sockets/http_11_proxy/v3/upstream_http_11_connect.upb.h"
#include "envoy/extensions/transport_sockets/tls/v3/tls.upb.h"
#include "envoy/extensions/upstreams/http/v3/http_protocol_options.upb.h"
#include "google/protobuf/any.upb.h"
#include "google/protobuf/duration.upb.h"
#include "google/protobuf/struct.upb.h"
#include "google/protobuf/wrappers.upb.h"
#include "src/core/config/core_configuration.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/load_balancing/lb_policy_registry.h"
#include "src/core/util/down_cast.h"
#include "src/core/util/env.h"
#include "src/core/util/host_port.h"
#include "src/core/util/time.h"
#include "src/core/util/upb_utils.h"
#include "src/core/util/validation_errors.h"
#include "src/core/xds/grpc/xds_bootstrap_grpc.h"
#include "src/core/xds/grpc/xds_common_types.h"
#include "src/core/xds/grpc/xds_common_types_parser.h"
#include "src/core/xds/grpc/xds_lb_policy_registry.h"
#include "src/core/xds/grpc/xds_metadata_parser.h"
#include "src/core/xds/xds_client/lrs_client.h"
#include "src/core/xds/xds_client/xds_backend_metric_propagation.h"
#include "upb/base/string_view.h"
#include "upb/text/encode.h"

namespace grpc_core {

bool XdsHttpConnectEnabled() {
  auto value = GetEnv("GRPC_EXPERIMENTAL_XDS_HTTP_CONNECT");
  if (!value.has_value()) return false;
  bool parsed_value;
  bool parse_succeeded = gpr_parse_bool_value(value->c_str(), &parsed_value);
  return parse_succeeded && parsed_value;
}

namespace {

constexpr absl::string_view kUpstreamTlsContextType =
    "envoy.extensions.transport_sockets.tls.v3.UpstreamTlsContext";

constexpr absl::string_view kHttp11ProxyType =
    "envoy.extensions.transport_sockets.http_11_proxy.v3"
    ".Http11ProxyUpstreamTransport";

CommonTlsContext UpstreamTlsContextParse(
    const XdsResourceType::DecodeContext& context,
    const XdsExtension& extension, ValidationErrors* errors) {
  const absl::string_view* serialized_upstream_tls_context =
      std::get_if<absl::string_view>(&extension.value);
  if (serialized_upstream_tls_context == nullptr) {
    errors->AddError("can't decode UpstreamTlsContext");
    return {};
  }
  const auto* upstream_tls_context =
      envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext_parse(
          serialized_upstream_tls_context->data(),
          serialized_upstream_tls_context->size(), context.arena);
  if (upstream_tls_context == nullptr) {
    errors->AddError("can't decode UpstreamTlsContext");
    return {};
  }
  ValidationErrors::ScopedField field3(errors, ".common_tls_context");
  const auto* common_tls_context_proto =
      envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext_common_tls_context(
          upstream_tls_context);
  CommonTlsContext common_tls_context;
  if (common_tls_context_proto != nullptr) {
    common_tls_context =
        CommonTlsContextParse(context, common_tls_context_proto, errors);
  }
  if (std::holds_alternative<std::monostate>(
          common_tls_context.certificate_validation_context.ca_certs)) {
    errors->AddError("no CA certs configured");
  }
  return common_tls_context;
}

CommonTlsContext Http11ProxyUpstreamTransportParse(
    const XdsResourceType::DecodeContext& context,
    const XdsExtension& extension, ValidationErrors* errors) {
  const absl::string_view* serialized =
      std::get_if<absl::string_view>(&extension.value);
  if (serialized == nullptr) {
    errors->AddError("can't decode Http11ProxyUpstreamTransport");
    return {};
  }
  const auto* http_11_proxy =
      envoy_extensions_transport_sockets_http_11_proxy_v3_Http11ProxyUpstreamTransport_parse(
          serialized->data(), serialized->size(), context.arena);
  if (http_11_proxy == nullptr) {
    errors->AddError("can't decode Http11ProxyUpstreamTransport");
    return {};
  }
  const auto* transport_socket =
      envoy_extensions_transport_sockets_http_11_proxy_v3_Http11ProxyUpstreamTransport_transport_socket(
          http_11_proxy);
  if (transport_socket == nullptr) return {};
  ValidationErrors::ScopedField field(errors, ".transport_socket.typed_config");
  const auto* typed_config =
      envoy_config_core_v3_TransportSocket_typed_config(transport_socket);
  auto wrapped_extension = ExtractXdsExtension(context, typed_config, errors);
  if (!wrapped_extension.has_value()) return {};
  if (wrapped_extension->type != kUpstreamTlsContextType) {
    ValidationErrors::ScopedField field(errors, ".type_url");
    errors->AddError("unsupported transport socket type");
    return {};
  }
  return UpstreamTlsContextParse(context, *wrapped_extension, errors);
}

XdsClusterResource::Eds EdsConfigParse(
    const envoy_config_cluster_v3_Cluster* cluster, ValidationErrors* errors) {
  XdsClusterResource::Eds eds;
  ValidationErrors::ScopedField field(errors, ".eds_cluster_config");
  const envoy_config_cluster_v3_Cluster_EdsClusterConfig* eds_cluster_config =
      envoy_config_cluster_v3_Cluster_eds_cluster_config(cluster);
  if (eds_cluster_config == nullptr) {
    errors->AddError("field not present");
  } else {

    {
      ValidationErrors::ScopedField field(errors, ".eds_config");
      const envoy_config_core_v3_ConfigSource* eds_config =
          envoy_config_cluster_v3_Cluster_EdsClusterConfig_eds_config(
              eds_cluster_config);
      if (eds_config == nullptr) {
        errors->AddError("field not present");
      } else {
        if (!envoy_config_core_v3_ConfigSource_has_ads(eds_config) &&
            !envoy_config_core_v3_ConfigSource_has_self(eds_config)) {
          errors->AddError("ConfigSource is not ads or self");
        }
      }
    }

    eds.eds_service_name = UpbStringToStdString(
        envoy_config_cluster_v3_Cluster_EdsClusterConfig_service_name(
            eds_cluster_config));
    if (eds.eds_service_name.empty()) {
      absl::string_view cluster_name =
          UpbStringToAbsl(envoy_config_cluster_v3_Cluster_name(cluster));
      if (absl::StartsWith(cluster_name, "xdstp:")) {
        ValidationErrors::ScopedField field(errors, ".service_name");
        errors->AddError("must be set if Cluster resource has an xdstp name");
      }
    }
  }
  return eds;
}

XdsClusterResource::LogicalDns LogicalDnsParse(
    const envoy_config_cluster_v3_Cluster* cluster, ValidationErrors* errors) {
  XdsClusterResource::LogicalDns logical_dns;
  ValidationErrors::ScopedField field(errors, ".load_assignment");
  const auto* load_assignment =
      envoy_config_cluster_v3_Cluster_load_assignment(cluster);
  if (load_assignment == nullptr) {
    errors->AddError("field not present for LOGICAL_DNS cluster");
    return logical_dns;
  }
  ValidationErrors::ScopedField field2(errors, ".endpoints");
  size_t num_localities;
  const auto* const* localities =
      envoy_config_endpoint_v3_ClusterLoadAssignment_endpoints(load_assignment,
                                                               &num_localities);
  if (num_localities != 1) {
    errors->AddError(absl::StrCat(
        "must contain exactly one locality for LOGICAL_DNS cluster, found ",
        num_localities));
    return logical_dns;
  }
  ValidationErrors::ScopedField field3(errors, "[0].lb_endpoints");
  size_t num_endpoints;
  const auto* const* endpoints =
      envoy_config_endpoint_v3_LocalityLbEndpoints_lb_endpoints(localities[0],
                                                                &num_endpoints);
  if (num_endpoints != 1) {
    errors->AddError(absl::StrCat(
        "must contain exactly one endpoint for LOGICAL_DNS cluster, found ",
        num_endpoints));
    return logical_dns;
  }
  ValidationErrors::ScopedField field4(errors, "[0].endpoint");
  const auto* endpoint =
      envoy_config_endpoint_v3_LbEndpoint_endpoint(endpoints[0]);
  if (endpoint == nullptr) {
    errors->AddError("field not present");
    return logical_dns;
  }
  ValidationErrors::ScopedField field5(errors, ".address");
  const auto* address = envoy_config_endpoint_v3_Endpoint_address(endpoint);
  if (address == nullptr) {
    errors->AddError("field not present");
    return logical_dns;
  }
  ValidationErrors::ScopedField field6(errors, ".socket_address");
  const auto* socket_address =
      envoy_config_core_v3_Address_socket_address(address);
  if (socket_address == nullptr) {
    errors->AddError("field not present");
    return logical_dns;
  }
  if (envoy_config_core_v3_SocketAddress_resolver_name(socket_address).size !=
      0) {
    ValidationErrors::ScopedField field(errors, ".resolver_name");
    errors->AddError(
        "LOGICAL_DNS clusters must NOT have a custom resolver name set");
  }
  absl::string_view address_str = UpbStringToAbsl(
      envoy_config_core_v3_SocketAddress_address(socket_address));
  if (address_str.empty()) {
    ValidationErrors::ScopedField field(errors, ".address");
    errors->AddError("field not present");
  }
  if (!envoy_config_core_v3_SocketAddress_has_port_value(socket_address)) {
    ValidationErrors::ScopedField field(errors, ".port_value");
    errors->AddError("field not present");
  }
  logical_dns.hostname = JoinHostPort(
      address_str,
      envoy_config_core_v3_SocketAddress_port_value(socket_address));
  return logical_dns;
}

XdsClusterResource::Aggregate AggregateClusterParse(
    const XdsResourceType::DecodeContext& context,
    absl::string_view serialized_config, ValidationErrors* errors) {
  XdsClusterResource::Aggregate aggregate;
  const auto* aggregate_cluster_config =
      envoy_extensions_clusters_aggregate_v3_ClusterConfig_parse(
          serialized_config.data(), serialized_config.size(), context.arena);
  if (aggregate_cluster_config == nullptr) {
    errors->AddError("can't parse aggregate cluster config");
    return aggregate;
  }
  size_t size;
  const upb_StringView* clusters =
      envoy_extensions_clusters_aggregate_v3_ClusterConfig_clusters(
          aggregate_cluster_config, &size);
  if (size == 0) {
    ValidationErrors::ScopedField field(errors, ".clusters");
    errors->AddError("must be non-empty");
  }
  for (size_t i = 0; i < size; ++i) {
    aggregate.prioritized_cluster_names.emplace_back(
        UpbStringToStdString(clusters[i]));
  }
  return aggregate;
}

void ParseLbPolicyConfig(const XdsResourceType::DecodeContext& context,
                         const envoy_config_cluster_v3_Cluster* cluster,
                         XdsClusterResource* cds_update,
                         ValidationErrors* errors) {

  const auto* load_balancing_policy =
      envoy_config_cluster_v3_Cluster_load_balancing_policy(cluster);
  if (load_balancing_policy != nullptr) {
    const auto& registry =
        DownCast<const GrpcXdsBootstrap&>(context.client->bootstrap())
            .lb_policy_registry();
    ValidationErrors::ScopedField field(errors, ".load_balancing_policy");
    const size_t original_error_count = errors->size();
    cds_update->lb_policy_config = registry.ConvertXdsLbPolicyConfig(
        context, load_balancing_policy, errors);

    if (original_error_count == errors->size()) {
      auto config = CoreConfiguration::Get()
                        .lb_policy_registry()
                        .ParseLoadBalancingConfig(
                            Json::FromArray(cds_update->lb_policy_config));
      if (!config.ok()) errors->AddError(config.status().message());
    }
    return;
  }

  if (envoy_config_cluster_v3_Cluster_lb_policy(cluster) ==
      envoy_config_cluster_v3_Cluster_ROUND_ROBIN) {
    cds_update->lb_policy_config = {
        Json::FromObject({
            {"xds_wrr_locality_experimental",
             Json::FromObject({
                 {"childPolicy", Json::FromArray({
                                     Json::FromObject({
                                         {"round_robin", Json::FromObject({})},
                                     }),
                                 })},
             })},
        }),
    };
  } else if (envoy_config_cluster_v3_Cluster_lb_policy(cluster) ==
             envoy_config_cluster_v3_Cluster_RING_HASH) {

    auto* ring_hash_config =
        envoy_config_cluster_v3_Cluster_ring_hash_lb_config(cluster);
    uint64_t min_ring_size = 1024;
    uint64_t max_ring_size = 8388608;
    if (ring_hash_config != nullptr) {
      ValidationErrors::ScopedField field(errors, ".ring_hash_lb_config");
      auto value = ParseUInt64Value(
          envoy_config_cluster_v3_Cluster_RingHashLbConfig_maximum_ring_size(
              ring_hash_config));
      if (value.has_value()) {
        ValidationErrors::ScopedField field(errors, ".maximum_ring_size");
        max_ring_size = *value;
        if (max_ring_size > 8388608 || max_ring_size == 0) {
          errors->AddError("must be in the range of 1 to 8388608");
        }
      }
      value = ParseUInt64Value(
          envoy_config_cluster_v3_Cluster_RingHashLbConfig_minimum_ring_size(
              ring_hash_config));
      if (value.has_value()) {
        ValidationErrors::ScopedField field(errors, ".minimum_ring_size");
        min_ring_size = *value;
        if (min_ring_size > 8388608 || min_ring_size == 0) {
          errors->AddError("must be in the range of 1 to 8388608");
        }
        if (min_ring_size > max_ring_size) {
          errors->AddError("cannot be greater than maximum_ring_size");
        }
      }
      if (envoy_config_cluster_v3_Cluster_RingHashLbConfig_hash_function(
              ring_hash_config) !=
          envoy_config_cluster_v3_Cluster_RingHashLbConfig_XX_HASH) {
        ValidationErrors::ScopedField field(errors, ".hash_function");
        errors->AddError("invalid hash function");
      }
    }
    cds_update->lb_policy_config = {
        Json::FromObject({
            {"ring_hash_experimental",
             Json::FromObject({
                 {"minRingSize", Json::FromNumber(min_ring_size)},
                 {"maxRingSize", Json::FromNumber(max_ring_size)},
             })},
        }),
    };
  } else {
    ValidationErrors::ScopedField field(errors, ".lb_policy");
    errors->AddError("LB policy is not supported");
  }
}

void ParseUpstreamConfig(
    const XdsResourceType::DecodeContext& context,
    const envoy_config_core_v3_TypedExtensionConfig* upstream_config,
    XdsClusterResource* cds_update, ValidationErrors* errors) {
  ValidationErrors::ScopedField field(errors, ".typed_config");
  const auto* typed_config =
      envoy_config_core_v3_TypedExtensionConfig_typed_config(upstream_config);
  auto extension = ExtractXdsExtension(context, typed_config, errors);
  if (!extension.has_value()) return;
  if (extension->type !=
      "envoy.extensions.upstreams.http.v3.HttpProtocolOptions") {
    ValidationErrors::ScopedField field(errors, ".type_url");
    errors->AddError("unsupported upstream config type");
    return;
  }
  absl::string_view* serialized_http_protocol_options =
      std::get_if<absl::string_view>(&extension->value);
  if (serialized_http_protocol_options == nullptr) {
    errors->AddError("can't decode HttpProtocolOptions");
    return;
  }
  const auto* http_protocol_options =
      envoy_extensions_upstreams_http_v3_HttpProtocolOptions_parse(
          serialized_http_protocol_options->data(),
          serialized_http_protocol_options->size(), context.arena);
  if (http_protocol_options == nullptr) {
    errors->AddError("can't decode HttpProtocolOptions");
    return;
  }
  ValidationErrors::ScopedField field2(errors, ".common_http_protocol_options");
  const auto* common_http_protocol_options =
      envoy_extensions_upstreams_http_v3_HttpProtocolOptions_common_http_protocol_options(
          http_protocol_options);
  if (common_http_protocol_options != nullptr) {
    const auto* idle_timeout =
        envoy_config_core_v3_HttpProtocolOptions_idle_timeout(
            common_http_protocol_options);
    if (idle_timeout != nullptr) {
      ValidationErrors::ScopedField field(errors, ".idle_timeout");
      cds_update->connection_idle_timeout = ParseDuration(idle_timeout, errors);
    }
  }
}

absl::StatusOr<std::shared_ptr<const XdsClusterResource>> CdsResourceParse(
    const XdsResourceType::DecodeContext& context,
    const envoy_config_cluster_v3_Cluster* cluster) {
  auto cds_update = std::make_shared<XdsClusterResource>();
  ValidationErrors errors;

  if (envoy_config_cluster_v3_Cluster_type(cluster) ==
      envoy_config_cluster_v3_Cluster_EDS) {
    cds_update->type = EdsConfigParse(cluster, &errors);
  } else if (envoy_config_cluster_v3_Cluster_type(cluster) ==
             envoy_config_cluster_v3_Cluster_LOGICAL_DNS) {
    cds_update->type = LogicalDnsParse(cluster, &errors);
  } else if (envoy_config_cluster_v3_Cluster_has_cluster_type(cluster)) {
    ValidationErrors::ScopedField field(&errors, ".cluster_type");
    const auto* custom_cluster_type =
        envoy_config_cluster_v3_Cluster_cluster_type(cluster);
    CHECK_NE(custom_cluster_type, nullptr);
    ValidationErrors::ScopedField field2(&errors, ".typed_config");
    const auto* typed_config =
        envoy_config_cluster_v3_Cluster_CustomClusterType_typed_config(
            custom_cluster_type);
    if (typed_config == nullptr) {
      errors.AddError("field not present");
    } else if (absl::string_view type_url = absl::StripPrefix(
                   UpbStringToAbsl(google_protobuf_Any_type_url(typed_config)),
                   "type.googleapis.com/");
               type_url ==
               "envoy.extensions.clusters.aggregate.v3.ClusterConfig") {

      ValidationErrors::ScopedField field(
          &errors,
          ".value[envoy.extensions.clusters.aggregate.v3.ClusterConfig]");
      absl::string_view serialized_config =
          UpbStringToAbsl(google_protobuf_Any_value(typed_config));
      cds_update->type =
          AggregateClusterParse(context, serialized_config, &errors);
    } else {
      ValidationErrors::ScopedField field(&errors, ".type_url");
      errors.AddError(
          absl::StrCat("unknown cluster_type extension: ", type_url));
    }
  } else {
    ValidationErrors::ScopedField field(&errors, ".type");
    errors.AddError("unknown discovery type");
  }

  ParseLbPolicyConfig(context, cluster, cds_update.get(), &errors);

  auto* transport_socket =
      envoy_config_cluster_v3_Cluster_transport_socket(cluster);
  if (transport_socket != nullptr) {
    ValidationErrors::ScopedField field(&errors,
                                        ".transport_socket.typed_config");
    const auto* typed_config =
        envoy_config_core_v3_TransportSocket_typed_config(transport_socket);
    auto extension = ExtractXdsExtension(context, typed_config, &errors);
    if (extension.has_value()) {
      if (XdsHttpConnectEnabled() && extension->type == kHttp11ProxyType) {
        cds_update->use_http_connect = true;
        cds_update->common_tls_context =
            Http11ProxyUpstreamTransportParse(context, *extension, &errors);
      } else if (extension->type == kUpstreamTlsContextType) {
        cds_update->common_tls_context =
            UpstreamTlsContextParse(context, *extension, &errors);
      } else {
        ValidationErrors::ScopedField field(&errors, ".type_url");
        errors.AddError("unsupported transport socket type");
      }
    }
  }

  const envoy_config_core_v3_ConfigSource* lrs_server =
      envoy_config_cluster_v3_Cluster_lrs_server(cluster);
  if (lrs_server != nullptr) {
    if (!envoy_config_core_v3_ConfigSource_has_self(lrs_server)) {
      ValidationErrors::ScopedField field(&errors, ".lrs_server");
      errors.AddError("ConfigSource is not self");
    }
    cds_update->lrs_load_reporting_server =
        std::static_pointer_cast<const GrpcXdsServerTarget>(
            context.server.target());
  }

  auto propagation = MakeRefCounted<BackendMetricPropagation>();
  if (XdsOrcaLrsPropagationChangesEnabled()) {
    size_t size;
    upb_StringView const* metrics =
        envoy_config_cluster_v3_Cluster_lrs_report_endpoint_metrics(cluster,
                                                                    &size);
    for (size_t i = 0; i < size; ++i) {
      absl::string_view metric_name = UpbStringToAbsl(metrics[i]);
      if (metric_name == "cpu_utilization") {
        propagation->propagation_bits |= propagation->kCpuUtilization;
      } else if (metric_name == "mem_utilization") {
        propagation->propagation_bits |= propagation->kMemUtilization;
      } else if (metric_name == "application_utilization") {
        propagation->propagation_bits |= propagation->kApplicationUtilization;
      } else if (absl::ConsumePrefix(&metric_name, "named_metrics.")) {
        if (metric_name == "*") {
          propagation->propagation_bits |= propagation->kNamedMetricsAll;
        } else {
          propagation->named_metric_keys.emplace(metric_name);
        }
      }
    }
  }
  cds_update->lrs_backend_metric_propagation = std::move(propagation);

  auto* upstream_config =
      envoy_config_cluster_v3_Cluster_upstream_config(cluster);
  if (upstream_config != nullptr) {
    ValidationErrors::ScopedField field(&errors, ".upstream_config");
    ParseUpstreamConfig(context, upstream_config, cds_update.get(), &errors);
  }

  if (envoy_config_cluster_v3_Cluster_has_circuit_breakers(cluster)) {
    const envoy_config_cluster_v3_CircuitBreakers* circuit_breakers =
        envoy_config_cluster_v3_Cluster_circuit_breakers(cluster);
    size_t num_thresholds;
    const envoy_config_cluster_v3_CircuitBreakers_Thresholds* const*
        thresholds = envoy_config_cluster_v3_CircuitBreakers_thresholds(
            circuit_breakers, &num_thresholds);
    for (size_t i = 0; i < num_thresholds; ++i) {
      const auto* threshold = thresholds[i];
      if (envoy_config_cluster_v3_CircuitBreakers_Thresholds_priority(
              threshold) == envoy_config_core_v3_DEFAULT) {
        auto value = ParseUInt32Value(
            envoy_config_cluster_v3_CircuitBreakers_Thresholds_max_requests(
                threshold));
        if (value.has_value()) cds_update->max_concurrent_requests = *value;
        break;
      }
    }
  }

  if (envoy_config_cluster_v3_Cluster_has_outlier_detection(cluster)) {
    ValidationErrors::ScopedField field(&errors, ".outlier_detection");
    OutlierDetectionConfig outlier_detection_update;
    const envoy_config_cluster_v3_OutlierDetection* outlier_detection =
        envoy_config_cluster_v3_Cluster_outlier_detection(cluster);
    const google_protobuf_Duration* duration =
        envoy_config_cluster_v3_OutlierDetection_interval(outlier_detection);
    if (duration != nullptr) {
      ValidationErrors::ScopedField field(&errors, ".interval");
      outlier_detection_update.interval = ParseDuration(duration, &errors);
    }
    duration = envoy_config_cluster_v3_OutlierDetection_base_ejection_time(
        outlier_detection);
    if (duration != nullptr) {
      ValidationErrors::ScopedField field(&errors, ".base_ejection_time");
      outlier_detection_update.base_ejection_time =
          ParseDuration(duration, &errors);
    }
    duration = envoy_config_cluster_v3_OutlierDetection_max_ejection_time(
        outlier_detection);
    if (duration != nullptr) {
      ValidationErrors::ScopedField field(&errors, ".max_ejection_time");
      outlier_detection_update.max_ejection_time =
          ParseDuration(duration, &errors);
    }
    auto max_ejection_percent = ParseUInt32Value(
        envoy_config_cluster_v3_OutlierDetection_max_ejection_percent(
            outlier_detection));
    if (max_ejection_percent.has_value()) {
      outlier_detection_update.max_ejection_percent = *max_ejection_percent;
      if (outlier_detection_update.max_ejection_percent > 100) {
        ValidationErrors::ScopedField field(&errors, ".max_ejection_percent");
        errors.AddError("value must be <= 100");
      }
    }
    auto enforcement_percentage = ParseUInt32Value(
        envoy_config_cluster_v3_OutlierDetection_enforcing_success_rate(
            outlier_detection));
    if (enforcement_percentage.has_value()) {
      if (*enforcement_percentage > 100) {
        ValidationErrors::ScopedField field(&errors, ".enforcing_success_rate");
        errors.AddError("value must be <= 100");
      }
      if (*enforcement_percentage != 0) {
        OutlierDetectionConfig::SuccessRateEjection success_rate_ejection;
        success_rate_ejection.enforcement_percentage = *enforcement_percentage;
        auto minimum_hosts = ParseUInt32Value(
            envoy_config_cluster_v3_OutlierDetection_success_rate_minimum_hosts(
                outlier_detection));
        if (minimum_hosts.has_value()) {
          success_rate_ejection.minimum_hosts = *minimum_hosts;
        }
        auto request_volume = ParseUInt32Value(
            envoy_config_cluster_v3_OutlierDetection_success_rate_request_volume(
                outlier_detection));
        if (request_volume.has_value()) {
          success_rate_ejection.request_volume = *request_volume;
        }
        auto stdev_factor = ParseUInt32Value(
            envoy_config_cluster_v3_OutlierDetection_success_rate_stdev_factor(
                outlier_detection));
        if (stdev_factor.has_value()) {
          success_rate_ejection.stdev_factor = *stdev_factor;
        }
        outlier_detection_update.success_rate_ejection = success_rate_ejection;
      }
    }
    enforcement_percentage = ParseUInt32Value(
        envoy_config_cluster_v3_OutlierDetection_enforcing_failure_percentage(
            outlier_detection));
    if (enforcement_percentage.has_value()) {
      if (*enforcement_percentage > 100) {
        ValidationErrors::ScopedField field(&errors,
                                            ".enforcing_failure_percentage");
        errors.AddError("value must be <= 100");
      }
      if (*enforcement_percentage != 0) {
        OutlierDetectionConfig::FailurePercentageEjection
            failure_percentage_ejection;
        failure_percentage_ejection.enforcement_percentage =
            *enforcement_percentage;
        auto minimum_hosts = ParseUInt32Value(
            envoy_config_cluster_v3_OutlierDetection_failure_percentage_minimum_hosts(
                outlier_detection));
        if (minimum_hosts.has_value()) {
          failure_percentage_ejection.minimum_hosts = *minimum_hosts;
        }
        auto request_volume = ParseUInt32Value(
            envoy_config_cluster_v3_OutlierDetection_failure_percentage_request_volume(
                outlier_detection));
        if (request_volume.has_value()) {
          failure_percentage_ejection.request_volume = *request_volume;
        }
        auto threshold = ParseUInt32Value(
            envoy_config_cluster_v3_OutlierDetection_failure_percentage_threshold(
                outlier_detection));
        if (threshold.has_value()) {
          failure_percentage_ejection.threshold = *threshold;
          if (*enforcement_percentage > 100) {
            ValidationErrors::ScopedField field(
                &errors, ".failure_percentage_threshold");
            errors.AddError("value must be <= 100");
          }
        }
        outlier_detection_update.failure_percentage_ejection =
            failure_percentage_ejection;
      }
    }
    cds_update->outlier_detection = outlier_detection_update;
  }

  const auto* common_lb_config =
      envoy_config_cluster_v3_Cluster_common_lb_config(cluster);
  bool override_host_status_found = false;
  if (common_lb_config != nullptr) {
    ValidationErrors::ScopedField field(&errors, ".common_lb_config");
    const auto* override_host_status =
        envoy_config_cluster_v3_Cluster_CommonLbConfig_override_host_status(
            common_lb_config);
    if (override_host_status != nullptr) {
      ValidationErrors::ScopedField field(&errors, ".override_host_status");
      size_t size;
      const int32_t* statuses = envoy_config_core_v3_HealthStatusSet_statuses(
          override_host_status, &size);
      for (size_t i = 0; i < size; ++i) {
        auto status = XdsHealthStatus::FromUpb(statuses[i]);
        if (status.has_value()) {
          cds_update->override_host_statuses.Add(*status);
        }
      }
      override_host_status_found = true;
    }
  }

  if (!override_host_status_found) {
    cds_update->override_host_statuses.Add(
        XdsHealthStatus(XdsHealthStatus::kUnknown));
    cds_update->override_host_statuses.Add(
        XdsHealthStatus(XdsHealthStatus::kHealthy));
  }

  {
    ValidationErrors::ScopedField field(&errors, ".metadata");
    cds_update->metadata = ParseXdsMetadataMap(
        context, envoy_config_cluster_v3_Cluster_metadata(cluster), &errors);
  }

  if (!errors.ok()) {
    return errors.status(absl::StatusCode::kInvalidArgument,
                         "errors validating Cluster resource");
  }
  return cds_update;
}

void MaybeLogCluster(const XdsResourceType::DecodeContext& context,
                     const envoy_config_cluster_v3_Cluster* cluster) {
  if (GRPC_TRACE_FLAG_ENABLED(xds_client) && ABSL_VLOG_IS_ON(2)) {
    const upb_MessageDef* msg_type =
        envoy_config_cluster_v3_Cluster_getmsgdef(context.symtab);
    char buf[10240];
    upb_TextEncode(reinterpret_cast<const upb_Message*>(cluster), msg_type,
                   nullptr, 0, buf, sizeof(buf));
    VLOG(2) << "[xds_client " << context.client << "] Cluster: " << buf;
  }
}

}

XdsResourceType::DecodeResult XdsClusterResourceType::Decode(
    const XdsResourceType::DecodeContext& context,
    absl::string_view serialized_resource) const {
  DecodeResult result;

  auto* resource = envoy_config_cluster_v3_Cluster_parse(
      serialized_resource.data(), serialized_resource.size(), context.arena);
  if (resource == nullptr) {
    result.resource =
        absl::InvalidArgumentError("Can't parse Cluster resource.");
    return result;
  }
  MaybeLogCluster(context, resource);

  result.name =
      UpbStringToStdString(envoy_config_cluster_v3_Cluster_name(resource));
  auto cds_resource = CdsResourceParse(context, resource);
  if (!cds_resource.ok()) {
    if (GRPC_TRACE_FLAG_ENABLED(xds_client)) {
      LOG(ERROR) << "[xds_client " << context.client << "] invalid Cluster "
                 << *result.name << ": " << cds_resource.status();
    }
    result.resource = cds_resource.status();
  } else {
    if (GRPC_TRACE_FLAG_ENABLED(xds_client)) {
      LOG(INFO) << "[xds_client " << context.client << "] parsed Cluster "
                << *result.name << ": " << (*cds_resource)->ToString();
    }
    result.resource = std::move(*cds_resource);
  }
  return result;
}

}
