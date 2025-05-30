
// Copyright 2016 gRPC authors.

#include "src/core/lib/surface/channel_stack_type.h"

#include <grpc/support/port_platform.h>

bool grpc_channel_stack_type_is_client(grpc_channel_stack_type type) {
  switch (type) {
    case GRPC_CLIENT_CHANNEL:
      return true;
    case GRPC_CLIENT_SUBCHANNEL:
      return true;
    case GRPC_CLIENT_LAME_CHANNEL:
      return true;
    case GRPC_CLIENT_DIRECT_CHANNEL:
      return true;
    case GRPC_CLIENT_DYNAMIC:
      return true;
    case GRPC_SERVER_CHANNEL:
      return false;
    case GRPC_NUM_CHANNEL_STACK_TYPES:
      break;
  }
  GPR_UNREACHABLE_CODE(return true;);
}

const char* grpc_channel_stack_type_string(grpc_channel_stack_type type) {
  switch (type) {
    case GRPC_CLIENT_CHANNEL:
      return "CLIENT_CHANNEL";
    case GRPC_CLIENT_SUBCHANNEL:
      return "CLIENT_SUBCHANNEL";
    case GRPC_SERVER_CHANNEL:
      return "SERVER_CHANNEL";
    case GRPC_CLIENT_LAME_CHANNEL:
      return "CLIENT_LAME_CHANNEL";
    case GRPC_CLIENT_DIRECT_CHANNEL:
      return "CLIENT_DIRECT_CHANNEL";
    case GRPC_CLIENT_DYNAMIC:
      return "CLIENT_DYNAMIC_CHANNEL";
    case GRPC_NUM_CHANNEL_STACK_TYPES:
      break;
  }
  GPR_UNREACHABLE_CODE(return "UNKNOWN");
}
