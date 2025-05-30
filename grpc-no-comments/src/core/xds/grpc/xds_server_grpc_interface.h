
// Copyright 2025 gRPC authors.

#ifndef GRPC_SRC_CORE_XDS_GRPC_XDS_SERVER_GRPC_INTERFACE_H
#define GRPC_SRC_CORE_XDS_GRPC_XDS_SERVER_GRPC_INTERFACE_H

#include "src/core/credentials/transport/channel_creds_registry.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/xds/xds_client/xds_bootstrap.h"

namespace grpc_core {

class GrpcXdsServerInterface : public XdsBootstrap::XdsServerTarget {
 public:
  virtual RefCountedPtr<ChannelCredsConfig> channel_creds_config() const = 0;
};

}

#endif
