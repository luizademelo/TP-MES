
// Copyright 2022 gRPC authors.

#ifndef GRPC_SRC_CORE_HANDSHAKER_ENDPOINT_INFO_ENDPOINT_INFO_HANDSHAKER_H
#define GRPC_SRC_CORE_HANDSHAKER_ENDPOINT_INFO_ENDPOINT_INFO_HANDSHAKER_H

#include <grpc/support/port_platform.h>

#include "src/core/config/core_configuration.h"

#define GRPC_ARG_ENDPOINT_LOCAL_ADDRESS "grpc.internal.endpoint_local_address"

#define GRPC_ARG_ENDPOINT_PEER_ADDRESS "grpc.internal.endpoint_peer_address"

namespace grpc_core {

void RegisterEndpointInfoHandshaker(CoreConfiguration::Builder* builder);

}

#endif
