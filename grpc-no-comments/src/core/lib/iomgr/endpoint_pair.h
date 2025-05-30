
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_IOMGR_ENDPOINT_PAIR_H
#define GRPC_SRC_CORE_LIB_IOMGR_ENDPOINT_PAIR_H

#include <grpc/support/port_platform.h>

#include "src/core/lib/iomgr/endpoint.h"

struct grpc_endpoint_pair {
  grpc_endpoint* client;
  grpc_endpoint* server;
};

grpc_endpoint_pair grpc_iomgr_create_endpoint_pair(
    const char* name, const grpc_channel_args* args);

#endif
