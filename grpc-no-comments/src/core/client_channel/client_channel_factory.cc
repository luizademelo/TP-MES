
// Copyright 2015 gRPC authors.

#include "src/core/client_channel/client_channel_factory.h"

#include <grpc/support/port_platform.h>

#define GRPC_ARG_CLIENT_CHANNEL_FACTORY "grpc.client_channel_factory"

namespace grpc_core {

absl::string_view ClientChannelFactory::ChannelArgName() {
  return GRPC_ARG_CLIENT_CHANNEL_FACTORY;
}

}
