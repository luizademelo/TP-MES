// Copyright 2022 The gRPC Authors

#ifndef GRPC_SRC_CORE_LIB_IOMGR_EVENT_ENGINE_SHIMS_TCP_CLIENT_H
#define GRPC_SRC_CORE_LIB_IOMGR_EVENT_ENGINE_SHIMS_TCP_CLIENT_H
#include <grpc/event_engine/event_engine.h>
#include <grpc/support/port_platform.h>

#include "src/core/lib/iomgr/endpoint.h"
#include "src/core/lib/iomgr/resolved_address.h"

namespace grpc_event_engine {
namespace experimental {

int64_t event_engine_tcp_client_connect(grpc_closure* on_connect,
                                        grpc_endpoint** endpoint,
                                        const EndpointConfig& config,
                                        const grpc_resolved_address* addr,
                                        grpc_core::Timestamp deadline);

bool event_engine_tcp_client_cancel_connect(int64_t connection_handle);

}
}

#endif
