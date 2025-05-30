
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_IOMGR_IOCP_WINDOWS_H
#define GRPC_SRC_CORE_LIB_IOMGR_IOCP_WINDOWS_H

#include <grpc/support/port_platform.h>
#include <grpc/support/sync.h>

#include "src/core/lib/iomgr/port.h"

#ifdef GRPC_WINSOCK_SOCKET

#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/iomgr/socket_windows.h"

typedef enum {
  GRPC_IOCP_WORK_WORK,
  GRPC_IOCP_WORK_TIMEOUT,
  GRPC_IOCP_WORK_KICK
} grpc_iocp_work_status;

grpc_iocp_work_status grpc_iocp_work(grpc_core::Timestamp deadline);
void grpc_iocp_init(void);
void grpc_iocp_kick(void);
void grpc_iocp_flush(void);
void grpc_iocp_shutdown(void);
void grpc_iocp_add_socket(grpc_winsocket*);

void grpc_iocp_register_socket_shutdown_socket_locked(grpc_winsocket* socket);

void grpc_iocp_finish_socket_shutdown(grpc_winsocket* socket);

#endif

#endif
