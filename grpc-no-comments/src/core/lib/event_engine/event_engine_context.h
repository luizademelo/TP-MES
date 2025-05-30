// Copyright 2024 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_EVENT_ENGINE_EVENT_ENGINE_CONTEXT_H
#define GRPC_SRC_CORE_LIB_EVENT_ENGINE_EVENT_ENGINE_CONTEXT_H

#include <grpc/event_engine/event_engine.h>
#include <grpc/support/port_platform.h>

#include "src/core/lib/resource_quota/arena.h"

namespace grpc_core {

template <>
struct ArenaContextType<grpc_event_engine::experimental::EventEngine> {
  static void Destroy(grpc_event_engine::experimental::EventEngine*) {}
};

}

#endif
