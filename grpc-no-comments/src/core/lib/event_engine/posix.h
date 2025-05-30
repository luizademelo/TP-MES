// Copyright 2022 gRPC Authors

#ifndef GRPC_SRC_CORE_LIB_EVENT_ENGINE_POSIX_H
#define GRPC_SRC_CORE_LIB_EVENT_ENGINE_POSIX_H

#include <grpc/event_engine/endpoint_config.h>
#include <grpc/event_engine/event_engine.h>
#include <grpc/event_engine/memory_allocator.h>
#include <grpc/event_engine/slice_buffer.h>
#include <grpc/support/port_platform.h>

#include "src/core/lib/event_engine/extensions/can_track_errors.h"
#include "src/core/lib/event_engine/extensions/chaotic_good_extension.h"
#include "src/core/lib/event_engine/extensions/supports_fd.h"
#include "src/core/lib/event_engine/query_extensions.h"

namespace grpc_event_engine::experimental {

class PosixEndpointWithChaoticGoodSupport
    : public ExtendedType<EventEngine::Endpoint, ChaoticGoodExtension,
                          EndpointSupportsFdExtension,
                          EndpointCanTrackErrorsExtension> {};

class PosixEndpointWithFdSupport
    : public ExtendedType<EventEngine::Endpoint, EndpointSupportsFdExtension,
                          EndpointCanTrackErrorsExtension> {};

class PosixListenerWithFdSupport
    : public ExtendedType<EventEngine::Listener, ListenerSupportsFdExtension> {
};

class PosixEventEngineWithFdSupport
    : public ExtendedType<EventEngine, EventEngineSupportsFdExtension> {};

}

#endif
