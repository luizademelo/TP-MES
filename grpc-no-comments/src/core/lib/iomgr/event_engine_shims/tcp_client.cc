// Copyright 2022 The gRPC Authors

#include "src/core/lib/iomgr/event_engine_shims/tcp_client.h"

#include <grpc/event_engine/event_engine.h>
#include <grpc/support/port_platform.h>
#include <grpc/support/time.h>

#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "src/core/lib/address_utils/sockaddr_utils.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/event_engine/default_event_engine.h"
#include "src/core/lib/event_engine/resolved_address_internal.h"
#include "src/core/lib/iomgr/closure.h"
#include "src/core/lib/iomgr/endpoint.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/iomgr/event_engine_shims/endpoint.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/resource_quota/resource_quota.h"
#include "src/core/lib/transport/error_utils.h"

namespace grpc_event_engine {
namespace experimental {

int64_t event_engine_tcp_client_connect(
    grpc_closure* on_connect, grpc_endpoint** endpoint,
    const grpc_event_engine::experimental::EndpointConfig& config,
    const grpc_resolved_address* addr, grpc_core::Timestamp deadline) {
  auto resource_quota = reinterpret_cast<grpc_core::ResourceQuota*>(
      config.GetVoidPointer(GRPC_ARG_RESOURCE_QUOTA));
  auto addr_uri = grpc_sockaddr_to_uri(addr);
  EventEngine* engine_ptr = reinterpret_cast<EventEngine*>(
      config.GetVoidPointer(GRPC_INTERNAL_ARG_EVENT_ENGINE));

  std::shared_ptr<EventEngine> keeper;
  if (engine_ptr == nullptr) {
    keeper = GetDefaultEventEngine();
    engine_ptr = keeper.get();
  }
  EventEngine::ConnectionHandle handle = engine_ptr->Connect(
      [on_connect,
       endpoint](absl::StatusOr<std::unique_ptr<EventEngine::Endpoint>> ep) {
        grpc_core::ExecCtx exec_ctx;
        absl::Status conn_status = ep.ok() ? absl::OkStatus() : ep.status();
        if (ep.ok()) {
          *endpoint = grpc_event_engine_endpoint_create(std::move(*ep));
        } else {
          *endpoint = nullptr;
        }
        GRPC_TRACE_LOG(event_engine, INFO)
            << "EventEngine::Connect Status: " << ep.status();
        grpc_core::ExecCtx::Run(DEBUG_LOCATION, on_connect,
                                absl_status_to_grpc_error(conn_status));
      },
      CreateResolvedAddress(*addr), config,
      resource_quota != nullptr
          ? resource_quota->memory_quota()->CreateMemoryOwner()
          : grpc_event_engine::experimental::MemoryAllocator(),
      std::max(grpc_core::Duration::Milliseconds(1),
               deadline - grpc_core::Timestamp::Now()));
  GRPC_TRACE_LOG(event_engine, INFO)
      << "EventEngine::Connect Peer: " << *addr_uri << ", handle: " << handle;
  return handle.keys[0];
}

bool event_engine_tcp_client_cancel_connect(int64_t connection_handle) {
  GRPC_TRACE_LOG(event_engine, INFO)
      << "EventEngine::CancelConnect handle: " << connection_handle;
  return GetDefaultEventEngine()->CancelConnect(
      {static_cast<intptr_t>(connection_handle), 0});
}
}
}
