
// Copyright 2024 gRPC authors.

#ifndef GRPC_SRC_CORE_XDS_GRPC_XDS_METADATA_PARSER_H
#define GRPC_SRC_CORE_XDS_GRPC_XDS_METADATA_PARSER_H

#include "envoy/config/core/v3/base.upb.h"
#include "src/core/util/validation_errors.h"
#include "src/core/xds/grpc/xds_metadata.h"
#include "src/core/xds/xds_client/xds_resource_type.h"

namespace grpc_core {

XdsMetadataMap ParseXdsMetadataMap(
    const XdsResourceType::DecodeContext& context,
    const envoy_config_core_v3_Metadata* metadata, ValidationErrors* errors);

}

#endif
