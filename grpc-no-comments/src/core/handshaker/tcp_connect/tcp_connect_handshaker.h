
// Copyright 2022 gRPC authors.

#ifndef GRPC_SRC_CORE_HANDSHAKER_TCP_CONNECT_TCP_CONNECT_HANDSHAKER_H
#define GRPC_SRC_CORE_HANDSHAKER_TCP_CONNECT_TCP_CONNECT_HANDSHAKER_H

#include <grpc/support/port_platform.h>

#include "src/core/config/core_configuration.h"

#define GRPC_ARG_TCP_HANDSHAKER_RESOLVED_ADDRESS \
  "grpc.internal.tcp_handshaker_resolved_address"

#define GRPC_ARG_TCP_HANDSHAKER_BIND_ENDPOINT_TO_POLLSET \
  "grpc.internal.tcp_handshaker_bind_endpoint_to_pollset"

namespace grpc_core {

void RegisterTCPConnectHandshaker(CoreConfiguration::Builder* builder);

}

#endif
