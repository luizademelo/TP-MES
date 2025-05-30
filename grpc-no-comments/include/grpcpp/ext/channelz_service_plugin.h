
// Copyright 2018 gRPC authors.

#ifndef GRPCPP_EXT_CHANNELZ_SERVICE_PLUGIN_H
#define GRPCPP_EXT_CHANNELZ_SERVICE_PLUGIN_H

#include <grpc/support/port_platform.h>
#include <grpcpp/impl/server_builder_plugin.h>
#include <grpcpp/impl/server_initializer.h>
#include <grpcpp/support/config.h>

namespace grpc {
namespace channelz {
namespace experimental {

void InitChannelzService();

}
}
}

#endif
