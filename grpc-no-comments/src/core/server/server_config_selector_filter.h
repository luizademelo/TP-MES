
// Copyright 2021 gRPC authors.

#ifndef GRPC_SRC_CORE_SERVER_SERVER_CONFIG_SELECTOR_FILTER_H
#define GRPC_SRC_CORE_SERVER_SERVER_CONFIG_SELECTOR_FILTER_H

#include <grpc/support/port_platform.h>

#include "src/core/lib/channel/channel_fwd.h"
#include "src/core/lib/channel/channel_stack.h"

namespace grpc_core {

extern const grpc_channel_filter kServerConfigSelectorFilter;

}

#endif
