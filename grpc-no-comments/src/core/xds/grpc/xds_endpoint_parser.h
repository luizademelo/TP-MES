
// Copyright 2018 gRPC authors.

#ifndef GRPC_SRC_CORE_XDS_GRPC_XDS_ENDPOINT_PARSER_H
#define GRPC_SRC_CORE_XDS_GRPC_XDS_ENDPOINT_PARSER_H

#include "absl/strings/string_view.h"
#include "envoy/config/endpoint/v3/endpoint.upbdefs.h"
#include "src/core/xds/grpc/xds_endpoint.h"
#include "src/core/xds/xds_client/xds_client.h"
#include "src/core/xds/xds_client/xds_resource_type.h"
#include "src/core/xds/xds_client/xds_resource_type_impl.h"
#include "upb/reflection/def.h"

namespace grpc_core {

class XdsEndpointResourceType final
    : public XdsResourceTypeImpl<XdsEndpointResourceType, XdsEndpointResource> {
 public:
  absl::string_view type_url() const override {
    return "envoy.config.endpoint.v3.ClusterLoadAssignment";
  }

  DecodeResult Decode(const XdsResourceType::DecodeContext& context,
                      absl::string_view serialized_resource) const override;

  void InitUpbSymtab(XdsClient*, upb_DefPool* symtab) const override {
    envoy_config_endpoint_v3_ClusterLoadAssignment_getmsgdef(symtab);
  }
};

}

#endif
