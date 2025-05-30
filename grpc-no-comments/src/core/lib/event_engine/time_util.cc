// Copyright 2022 gRPC authors.

#include "src/core/lib/event_engine/time_util.h"

#include <grpc/event_engine/event_engine.h>
#include <grpc/support/port_platform.h>

#include <chrono>

namespace grpc_event_engine::experimental {

size_t Milliseconds(EventEngine::Duration d) {
  return std::chrono::duration_cast<std::chrono::milliseconds>(d).count();
}

}
