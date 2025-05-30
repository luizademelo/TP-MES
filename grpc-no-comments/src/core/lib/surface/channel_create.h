
// Copyright 2024 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_SURFACE_CHANNEL_CREATE_H
#define GRPC_SRC_CORE_LIB_SURFACE_CHANNEL_CREATE_H

#include <grpc/support/port_platform.h>

#include <string>

#include "absl/status/statusor.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/surface/channel.h"
#include "src/core/lib/surface/channel_stack_type.h"

#define GRPC_ARG_USE_V3_STACK "grpc.internal.use_v3_stack"

namespace grpc_core {

class Transport;

absl::StatusOr<RefCountedPtr<Channel>> ChannelCreate(
    std::string target, ChannelArgs args,
    grpc_channel_stack_type channel_stack_type, Transport* optional_transport);

}

#endif
