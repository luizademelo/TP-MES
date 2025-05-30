// Copyright 2017 gRPC authors.

#ifndef GRPC_SRC_CORE_EXT_TRANSPORT_INPROC_INPROC_TRANSPORT_H
#define GRPC_SRC_CORE_EXT_TRANSPORT_INPROC_INPROC_TRANSPORT_H

#include <grpc/grpc.h>
#include <grpc/support/port_platform.h>

#include "src/core/lib/debug/trace.h"
#include "src/core/lib/transport/transport.h"

grpc_channel* grpc_inproc_channel_create(grpc_server* server,
                                         const grpc_channel_args* args,
                                         void* reserved);

namespace grpc_core {

std::pair<OrphanablePtr<Transport>, OrphanablePtr<Transport>>
MakeInProcessTransportPair(const ChannelArgs& server_channel_args);

}

#endif
