
// Copyright 2023 gRPC authors.

#ifndef GRPC_SRC_CORE_LOAD_BALANCING_PICK_FIRST_PICK_FIRST_H
#define GRPC_SRC_CORE_LOAD_BALANCING_PICK_FIRST_PICK_FIRST_H

#include <grpc/support/port_platform.h>

#include "src/core/resolver/endpoint_addresses.h"

#define GRPC_ARG_INTERNAL_PICK_FIRST_ENABLE_HEALTH_CHECKING \
  GRPC_ARG_NO_SUBCHANNEL_PREFIX "pick_first_enable_health_checking"

#define GRPC_ARG_INTERNAL_PICK_FIRST_OMIT_STATUS_MESSAGE_PREFIX \
  GRPC_ARG_NO_SUBCHANNEL_PREFIX "pick_first_omit_status_message_prefix"

#endif
