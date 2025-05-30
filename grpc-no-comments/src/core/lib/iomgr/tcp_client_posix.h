
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_IOMGR_TCP_CLIENT_POSIX_H
#define GRPC_SRC_CORE_LIB_IOMGR_TCP_CLIENT_POSIX_H

#include <grpc/support/port_platform.h>

#include "src/core/lib/iomgr/endpoint.h"
#include "src/core/lib/iomgr/ev_posix.h"
#include "src/core/lib/iomgr/socket_utils_posix.h"
#include "src/core/lib/iomgr/tcp_client.h"

grpc_endpoint* grpc_tcp_create_from_fd(
    grpc_fd* fd, const grpc_event_engine::experimental::EndpointConfig& config,
    absl::string_view addr_str);

grpc_error_handle grpc_tcp_client_prepare_fd(
    const grpc_core::PosixTcpOptions& options,
    const grpc_resolved_address* addr, grpc_resolved_address* mapped_addr,
    int* fd);

int64_t grpc_tcp_client_create_from_prepared_fd(
    grpc_pollset_set* interested_parties, grpc_closure* closure, const int fd,
    const grpc_event_engine::experimental::EndpointConfig& config,
    const grpc_resolved_address* addr, grpc_core::Timestamp deadline,
    grpc_endpoint** ep);

#endif
