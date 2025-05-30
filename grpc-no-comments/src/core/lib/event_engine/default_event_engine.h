// Copyright 2021 The gRPC Authors

#ifndef GRPC_SRC_CORE_LIB_EVENT_ENGINE_DEFAULT_EVENT_ENGINE_H
#define GRPC_SRC_CORE_LIB_EVENT_ENGINE_DEFAULT_EVENT_ENGINE_H

#include <grpc/event_engine/event_engine.h>
#include <grpc/support/port_platform.h>

#include <memory>

#include "src/core/config/core_configuration.h"
#include "src/core/util/debug_location.h"

namespace grpc_event_engine::experimental {

void RegisterEventEngineChannelArgPreconditioning(
    grpc_core::CoreConfiguration::Builder* builder);

class DefaultEventEngineScope {
 public:
  explicit DefaultEventEngineScope(std::shared_ptr<EventEngine> engine) {
    SetDefaultEventEngine(std::move(engine));
  }
  ~DefaultEventEngineScope() { ShutdownDefaultEventEngine(); }
};

}

#endif
