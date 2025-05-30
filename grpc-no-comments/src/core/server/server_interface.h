
// Copyright 2024 gRPC authors.

#ifndef GRPC_SRC_CORE_SERVER_SERVER_INTERFACE_H
#define GRPC_SRC_CORE_SERVER_SERVER_INTERFACE_H

#include <grpc/impl/compression_types.h>
#include <grpc/support/port_platform.h>

#include "src/core/channelz/channelz.h"
#include "src/core/lib/channel/channel_args.h"

namespace grpc_core {

class ServerCallTracerFactory;

class ServerInterface {
 public:
  virtual ~ServerInterface() = default;

  virtual const ChannelArgs& channel_args() const = 0;
  virtual channelz::ServerNode* channelz_node() const = 0;
  virtual ServerCallTracerFactory* server_call_tracer_factory() const = 0;
  virtual grpc_compression_options compression_options() const = 0;
};

}

#endif
