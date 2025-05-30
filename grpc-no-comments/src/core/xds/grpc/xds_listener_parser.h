
// Copyright 2018 gRPC authors.

#ifndef GRPC_SRC_CORE_XDS_GRPC_XDS_LISTENER_PARSER_H
#define GRPC_SRC_CORE_XDS_GRPC_XDS_LISTENER_PARSER_H

#include "absl/strings/string_view.h"
#include "envoy/config/listener/v3/listener.upbdefs.h"
#include "envoy/extensions/filters/network/http_connection_manager/v3/http_connection_manager.upbdefs.h"
#include "src/core/util/down_cast.h"
#include "src/core/xds/grpc/xds_bootstrap_grpc.h"
#include "src/core/xds/grpc/xds_http_filter_registry.h"
#include "src/core/xds/grpc/xds_listener.h"
#include "src/core/xds/xds_client/xds_client.h"
#include "src/core/xds/xds_client/xds_resource_type.h"
#include "src/core/xds/xds_client/xds_resource_type_impl.h"
#include "upb/reflection/def.h"

namespace grpc_core {

class XdsListenerResourceType final
    : public XdsResourceTypeImpl<XdsListenerResourceType, XdsListenerResource> {
 public:
  absl::string_view type_url() const override {
    return "envoy.config.listener.v3.Listener";
  }

  DecodeResult Decode(const XdsResourceType::DecodeContext& context,
                      absl::string_view serialized_resource) const override;

  bool AllResourcesRequiredInSotW() const override { return true; }

  void InitUpbSymtab(XdsClient* xds_client,
                     upb_DefPool* symtab) const override {
    envoy_config_listener_v3_Listener_getmsgdef(symtab);
    envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_getmsgdef(
        symtab);
    const auto& http_filter_registry =
        DownCast<const GrpcXdsBootstrap&>(xds_client->bootstrap())
            .http_filter_registry();
    http_filter_registry.PopulateSymtab(symtab);
  }
};

}

#endif
