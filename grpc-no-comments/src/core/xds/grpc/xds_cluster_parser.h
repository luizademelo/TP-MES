
// Copyright 2018 gRPC authors.

#ifndef GRPC_SRC_CORE_XDS_GRPC_XDS_CLUSTER_PARSER_H
#define GRPC_SRC_CORE_XDS_GRPC_XDS_CLUSTER_PARSER_H

#include "absl/strings/string_view.h"
#include "envoy/config/cluster/v3/cluster.upbdefs.h"
#include "envoy/extensions/clusters/aggregate/v3/cluster.upbdefs.h"
#include "envoy/extensions/transport_sockets/http_11_proxy/v3/upstream_http_11_connect.upbdefs.h"
#include "envoy/extensions/transport_sockets/tls/v3/tls.upbdefs.h"
#include "envoy/extensions/upstreams/http/v3/http_protocol_options.upbdefs.h"
#include "src/core/xds/grpc/xds_cluster.h"
#include "src/core/xds/xds_client/xds_client.h"
#include "src/core/xds/xds_client/xds_resource_type.h"
#include "src/core/xds/xds_client/xds_resource_type_impl.h"
#include "upb/reflection/def.h"

namespace grpc_core {

bool XdsHttpConnectEnabled();

class XdsClusterResourceType
    : public XdsResourceTypeImpl<XdsClusterResourceType, XdsClusterResource> {
 public:
  absl::string_view type_url() const override {
    return "envoy.config.cluster.v3.Cluster";
  }

  DecodeResult Decode(const XdsResourceType::DecodeContext& context,
                      absl::string_view serialized_resource) const override;

  bool AllResourcesRequiredInSotW() const override { return true; }

  void InitUpbSymtab(XdsClient*, upb_DefPool* symtab) const override {
    envoy_config_cluster_v3_Cluster_getmsgdef(symtab);
    envoy_extensions_clusters_aggregate_v3_ClusterConfig_getmsgdef(symtab);
    envoy_extensions_transport_sockets_http_11_proxy_v3_Http11ProxyUpstreamTransport_getmsgdef(
        symtab);
    envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext_getmsgdef(
        symtab);
    envoy_extensions_upstreams_http_v3_HttpProtocolOptions_getmsgdef(symtab);
  }
};

}

#endif
