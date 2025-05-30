
// Copyright 2018 gRPC authors.

#ifndef GRPC_SRC_CORE_XDS_GRPC_XDS_ROUTE_CONFIG_PARSER_H
#define GRPC_SRC_CORE_XDS_GRPC_XDS_ROUTE_CONFIG_PARSER_H

#include <stdint.h>

#include <algorithm>
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <variant>
#include <vector>

#include "absl/strings/string_view.h"
#include "envoy/config/route/v3/route.upb.h"
#include "envoy/config/route/v3/route.upbdefs.h"
#include "re2/re2.h"
#include "src/core/call/status_util.h"
#include "src/core/util/down_cast.h"
#include "src/core/util/time.h"
#include "src/core/util/validation_errors.h"
#include "src/core/xds/grpc/xds_bootstrap_grpc.h"
#include "src/core/xds/grpc/xds_cluster_specifier_plugin.h"
#include "src/core/xds/grpc/xds_http_filter.h"
#include "src/core/xds/grpc/xds_route_config.h"
#include "src/core/xds/xds_client/xds_client.h"
#include "src/core/xds/xds_client/xds_resource_type.h"
#include "src/core/xds/xds_client/xds_resource_type_impl.h"
#include "upb/reflection/def.h"

namespace grpc_core {

std::shared_ptr<const XdsRouteConfigResource> XdsRouteConfigResourceParse(
    const XdsResourceType::DecodeContext& context,
    const envoy_config_route_v3_RouteConfiguration* route_config,
    ValidationErrors* errors);

class XdsRouteConfigResourceType final
    : public XdsResourceTypeImpl<XdsRouteConfigResourceType,
                                 XdsRouteConfigResource> {
 public:
  absl::string_view type_url() const override {
    return "envoy.config.route.v3.RouteConfiguration";
  }

  DecodeResult Decode(const XdsResourceType::DecodeContext& context,
                      absl::string_view serialized_resource) const override;

  void InitUpbSymtab(XdsClient* xds_client,
                     upb_DefPool* symtab) const override {
    envoy_config_route_v3_RouteConfiguration_getmsgdef(symtab);
    const auto& cluster_specifier_plugin_registry =
        DownCast<const GrpcXdsBootstrap&>(xds_client->bootstrap())
            .cluster_specifier_plugin_registry();
    cluster_specifier_plugin_registry.PopulateSymtab(symtab);
  }
};

}

#endif
