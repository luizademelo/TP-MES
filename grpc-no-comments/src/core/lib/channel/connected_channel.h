
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_CHANNEL_CONNECTED_CHANNEL_H
#define GRPC_SRC_CORE_LIB_CHANNEL_CONNECTED_CHANNEL_H

#include <grpc/support/port_platform.h>

#include "src/core/lib/channel/channel_fwd.h"
#include "src/core/lib/channel/channel_stack.h"
#include "src/core/lib/channel/channel_stack_builder.h"

extern const grpc_channel_filter grpc_connected_filter;

bool grpc_add_connected_filter(grpc_core::ChannelStackBuilder* builder);

#endif
