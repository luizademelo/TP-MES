// Copyright 2022 gRPC Authors

#ifndef GRPC_SRC_CORE_LIB_EVENT_ENGINE_RESOLVED_ADDRESS_INTERNAL_H
#define GRPC_SRC_CORE_LIB_EVENT_ENGINE_RESOLVED_ADDRESS_INTERNAL_H
#include <grpc/event_engine/event_engine.h>
#include <grpc/support/port_platform.h>

#include "src/core/lib/iomgr/resolved_address.h"

namespace grpc_event_engine::experimental {

EventEngine::ResolvedAddress CreateResolvedAddress(
    const grpc_resolved_address& addr);

grpc_resolved_address CreateGRPCResolvedAddress(
    const EventEngine::ResolvedAddress& ra);

}

#endif
