
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_IOMGR_TCP_CLIENT_H
#define GRPC_SRC_CORE_LIB_IOMGR_TCP_CLIENT_H

#include <grpc/event_engine/endpoint_config.h>
#include <grpc/impl/grpc_types.h>
#include <grpc/support/port_platform.h>
#include <grpc/support/time.h>

#include "src/core/lib/iomgr/endpoint.h"
#include "src/core/lib/iomgr/pollset_set.h"
#include "src/core/lib/iomgr/resolve_address.h"
#include "src/core/lib/resource_quota/memory_quota.h"

typedef struct grpc_tcp_client_vtable {
  int64_t (*connect)(
      grpc_closure* on_connect, grpc_endpoint** endpoint,
      grpc_pollset_set* interested_parties,
      const grpc_event_engine::experimental::EndpointConfig& config,
      const grpc_resolved_address* addr, grpc_core::Timestamp deadline);
  bool (*cancel_connect)(int64_t connection_handle);
} grpc_tcp_client_vtable;

int64_t grpc_tcp_client_connect(
    grpc_closure* on_connect, grpc_endpoint** endpoint,
    grpc_pollset_set* interested_parties,
    const grpc_event_engine::experimental::EndpointConfig& config,
    const grpc_resolved_address* addr, grpc_core::Timestamp deadline);

bool grpc_tcp_client_cancel_connect(int64_t connection_handle);

extern void grpc_tcp_client_global_init();

void grpc_set_tcp_client_impl(grpc_tcp_client_vtable* impl);

#endif
