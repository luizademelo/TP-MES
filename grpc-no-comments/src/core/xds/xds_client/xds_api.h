
// Copyright 2018 gRPC authors.

#ifndef GRPC_SRC_CORE_XDS_XDS_CLIENT_XDS_API_H
#define GRPC_SRC_CORE_XDS_XDS_CLIENT_XDS_API_H

#include "absl/strings/string_view.h"
#include "envoy/config/core/v3/base.upb.h"
#include "src/core/xds/xds_client/xds_bootstrap.h"
#include "upb/mem/arena.h"

namespace grpc_core {

void PopulateXdsNode(const XdsBootstrap::Node* node,
                     absl::string_view user_agent_name,
                     absl::string_view user_agent_version,
                     envoy_config_core_v3_Node* node_msg, upb_Arena* arena);

}

#endif
