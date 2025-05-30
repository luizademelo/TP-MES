
// Copyright 2018 gRPC authors.

#include "src/core/lib/iomgr/tcp_client.h"

#include <grpc/support/port_platform.h>

grpc_tcp_client_vtable* grpc_tcp_client_impl;

int64_t grpc_tcp_client_connect(
    grpc_closure* on_connect, grpc_endpoint** endpoint,
    grpc_pollset_set* interested_parties,
    const grpc_event_engine::experimental::EndpointConfig& config,
    const grpc_resolved_address* addr, grpc_core::Timestamp deadline) {
  return grpc_tcp_client_impl->connect(on_connect, endpoint, interested_parties,
                                       config, addr, deadline);
}

bool grpc_tcp_client_cancel_connect(int64_t connection_handle) {
  return grpc_tcp_client_impl->cancel_connect(connection_handle);
}

void grpc_set_tcp_client_impl(grpc_tcp_client_vtable* impl) {
  grpc_tcp_client_impl = impl;
}
