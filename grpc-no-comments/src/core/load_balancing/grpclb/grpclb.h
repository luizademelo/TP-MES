
// Copyright 2018 gRPC authors.

#ifndef GRPC_SRC_CORE_LOAD_BALANCING_GRPCLB_GRPCLB_H
#define GRPC_SRC_CORE_LOAD_BALANCING_GRPCLB_GRPCLB_H

#include <grpc/support/port_platform.h>

#define GRPC_ARG_ADDRESS_IS_GRPCLB_LOAD_BALANCER \
  "grpc.address_is_grpclb_load_balancer"

#define GRPC_ARG_ADDRESS_IS_BACKEND_FROM_GRPCLB_LOAD_BALANCER \
  "grpc.address_is_backend_from_grpclb_load_balancer"

#define GRPC_ARG_GRPCLB_SUBCHANNEL_CACHE_INTERVAL_MS \
  "grpc.internal.grpclb_subchannel_cache_interval_ms"

#endif
