
// Copyright 2022 gRPC authors.

#ifndef GRPC_SRC_CORE_LOAD_BALANCING_HEALTH_CHECK_CLIENT_H
#define GRPC_SRC_CORE_LOAD_BALANCING_HEALTH_CHECK_CLIENT_H

#include <grpc/support/port_platform.h>

#include <memory>

#include "src/core/lib/channel/channel_args.h"
#include "src/core/load_balancing/subchannel_interface.h"
#include "src/core/util/work_serializer.h"

namespace grpc_core {

std::unique_ptr<SubchannelInterface::DataWatcherInterface>
MakeHealthCheckWatcher(
    std::shared_ptr<WorkSerializer> work_serializer, const ChannelArgs& args,
    std::unique_ptr<SubchannelInterface::ConnectivityStateWatcherInterface>
        watcher);

}

#endif
