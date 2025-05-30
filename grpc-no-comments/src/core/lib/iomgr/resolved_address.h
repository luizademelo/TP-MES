// Copyright 2021 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_IOMGR_RESOLVED_ADDRESS_H
#define GRPC_SRC_CORE_LIB_IOMGR_RESOLVED_ADDRESS_H

#include <grpc/support/port_platform.h>
#include <stddef.h>

#include "src/core/lib/iomgr/port.h"

#ifdef GRPC_WINSOCK_SOCKET
#include <ws2tcpip.h>
#endif

#if defined(GRPC_POSIX_SOCKET) || defined(GRPC_CFSTREAM)
#include <sys/socket.h>
#endif

#define GRPC_MAX_SOCKADDR_SIZE 128

struct grpc_resolved_address {
  char addr[GRPC_MAX_SOCKADDR_SIZE];
  socklen_t len;
};

#endif
