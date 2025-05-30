
// Copyright 2016 gRPC authors.

#ifndef GRPC_SRC_CORE_HANDSHAKER_HTTP_CONNECT_HTTP_CONNECT_HANDSHAKER_H
#define GRPC_SRC_CORE_HANDSHAKER_HTTP_CONNECT_HTTP_CONNECT_HANDSHAKER_H

#include <grpc/support/port_platform.h>

#include "src/core/config/core_configuration.h"

#define GRPC_ARG_HTTP_CONNECT_SERVER "grpc.http_connect_server"

#define GRPC_ARG_HTTP_CONNECT_HEADERS "grpc.http_connect_headers"

namespace grpc_core {

void RegisterHttpConnectHandshaker(CoreConfiguration::Builder* builder);

}

#endif
