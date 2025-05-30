
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_IOMGR_TCP_POSIX_H
#define GRPC_SRC_CORE_LIB_IOMGR_TCP_POSIX_H

#include <grpc/event_engine/endpoint_config.h>
#include <grpc/support/port_platform.h>

#include "src/core/lib/debug/trace.h"
#include "src/core/lib/iomgr/buffer_list.h"
#include "src/core/lib/iomgr/endpoint.h"
#include "src/core/lib/iomgr/ev_posix.h"
#include "src/core/lib/iomgr/port.h"
#include "src/core/lib/iomgr/socket_utils_posix.h"

grpc_endpoint* grpc_tcp_create(grpc_fd* fd,
                               const grpc_core::PosixTcpOptions& options,
                               absl::string_view peer_string);

grpc_endpoint* grpc_tcp_create(
    grpc_fd* fd, const grpc_event_engine::experimental::EndpointConfig& config,
    absl::string_view peer_string);

int grpc_tcp_fd(grpc_endpoint* ep);

void grpc_tcp_destroy_and_release_fd(grpc_endpoint* ep, int* fd,
                                     grpc_closure* done);

#ifdef GRPC_POSIX_SOCKET_TCP

void grpc_tcp_posix_init();

void grpc_tcp_posix_shutdown();

#endif

#endif
