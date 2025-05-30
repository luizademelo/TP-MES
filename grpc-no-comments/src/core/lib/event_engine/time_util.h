// Copyright 2022 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_EVENT_ENGINE_TIME_UTIL_H
#define GRPC_SRC_CORE_LIB_EVENT_ENGINE_TIME_UTIL_H

#include <grpc/event_engine/event_engine.h>
#include <grpc/support/port_platform.h>
#include <stddef.h>

namespace grpc_event_engine::experimental {

size_t Milliseconds(EventEngine::Duration d);

}

#endif
