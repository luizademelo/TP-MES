
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_SURFACE_CHANNEL_STACK_TYPE_H
#define GRPC_SRC_CORE_LIB_SURFACE_CHANNEL_STACK_TYPE_H

#include <grpc/support/port_platform.h>

typedef enum {

  GRPC_CLIENT_CHANNEL,

  GRPC_CLIENT_SUBCHANNEL,

  GRPC_CLIENT_DYNAMIC,

  GRPC_CLIENT_LAME_CHANNEL,

  GRPC_CLIENT_DIRECT_CHANNEL,

  GRPC_SERVER_CHANNEL,

  GRPC_NUM_CHANNEL_STACK_TYPES
} grpc_channel_stack_type;

bool grpc_channel_stack_type_is_client(grpc_channel_stack_type type);

const char* grpc_channel_stack_type_string(grpc_channel_stack_type type);

#endif
