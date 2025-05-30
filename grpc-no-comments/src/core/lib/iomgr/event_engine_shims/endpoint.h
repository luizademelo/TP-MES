// Copyright 2022 The gRPC Authors

#ifndef GRPC_SRC_CORE_LIB_IOMGR_EVENT_ENGINE_SHIMS_ENDPOINT_H
#define GRPC_SRC_CORE_LIB_IOMGR_EVENT_ENGINE_SHIMS_ENDPOINT_H
#include <grpc/event_engine/event_engine.h>
#include <grpc/support/port_platform.h>

#include <memory>

#include "src/core/lib/iomgr/endpoint.h"

namespace grpc_event_engine {
namespace experimental {

grpc_endpoint* grpc_event_engine_endpoint_create(
    std::unique_ptr<EventEngine::Endpoint> ee_endpoint);

bool grpc_is_event_engine_endpoint(grpc_endpoint* ep);

EventEngine::Endpoint* grpc_get_wrapped_event_engine_endpoint(
    grpc_endpoint* ep);

std::unique_ptr<EventEngine::Endpoint> grpc_take_wrapped_event_engine_endpoint(
    grpc_endpoint* ep);

void grpc_event_engine_endpoint_destroy_and_release_fd(
    grpc_endpoint* ep, int* fd, grpc_closure* on_release_fd);

}
}

#endif
