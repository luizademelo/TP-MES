
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_IOMGR_TCP_WINDOWS_H
#define GRPC_SRC_CORE_LIB_IOMGR_TCP_WINDOWS_H

#include <grpc/support/port_platform.h>

#include "src/core/lib/iomgr/port.h"

#ifdef GRPC_WINSOCK_SOCKET
#include "src/core/lib/iomgr/endpoint.h"
#include "src/core/lib/iomgr/socket_windows.h"

grpc_endpoint* grpc_tcp_create(grpc_winsocket* socket,
                               absl::string_view peer_string);

grpc_error_handle grpc_tcp_prepare_socket(SOCKET sock);

grpc_error_handle grpc_tcp_set_non_block(SOCKET sock);

#endif

#endif
