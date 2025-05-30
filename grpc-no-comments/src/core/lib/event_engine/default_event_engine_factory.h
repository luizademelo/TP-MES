// Copyright 2021 The gRPC Authors

#ifndef GRPC_SRC_CORE_LIB_EVENT_ENGINE_DEFAULT_EVENT_ENGINE_FACTORY_H
#define GRPC_SRC_CORE_LIB_EVENT_ENGINE_DEFAULT_EVENT_ENGINE_FACTORY_H

#include <grpc/event_engine/event_engine.h>
#include <grpc/support/port_platform.h>

#include <memory>

namespace grpc_event_engine::experimental {

std::shared_ptr<EventEngine> DefaultEventEngineFactory();

}

#endif
