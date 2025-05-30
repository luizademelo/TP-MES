
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_IOMGR_SOCKET_WINDOWS_H
#define GRPC_SRC_CORE_LIB_IOMGR_SOCKET_WINDOWS_H

#include <grpc/support/port_platform.h>

#include "src/core/lib/iomgr/port.h"

#ifdef GRPC_WINSOCK_SOCKET
#include <grpc/support/atm.h>
#include <grpc/support/sync.h>
#include <winsock2.h>

#include "src/core/lib/iomgr/closure.h"
#include "src/core/lib/iomgr/iomgr_internal.h"

#ifndef WSA_FLAG_NO_HANDLE_INHERIT
#define WSA_FLAG_NO_HANDLE_INHERIT 0x80
#endif

typedef struct grpc_winsocket_callback_info {

  OVERLAPPED overlapped;

  grpc_closure* closure;

  int has_pending_iocp;

  DWORD bytes_transferred;
  int wsa_error;

  bool closure_already_executed_at_shutdown = false;
} grpc_winsocket_callback_info;

typedef struct grpc_winsocket {
  SOCKET socket;
  bool destroy_called;

  grpc_winsocket_callback_info write_info;
  grpc_winsocket_callback_info read_info;

  gpr_mu state_mu;
  bool shutdown_called;
  bool shutdown_registered;

  int added_to_iocp;

  grpc_iomgr_object iomgr_object;
} grpc_winsocket;

grpc_winsocket* grpc_winsocket_create(SOCKET socket, const char* name);

SOCKET grpc_winsocket_wrapped_socket(grpc_winsocket* socket);

void grpc_winsocket_shutdown(grpc_winsocket* socket);

void grpc_winsocket_destroy(grpc_winsocket* socket);

void grpc_socket_notify_on_write(grpc_winsocket* winsocket,
                                 grpc_closure* closure);

void grpc_socket_notify_on_read(grpc_winsocket* winsocket,
                                grpc_closure* closure);

bool grpc_socket_become_ready(grpc_winsocket* socket,
                              grpc_winsocket_callback_info* info);

int grpc_ipv6_loopback_available(void);

void grpc_wsa_socket_flags_init();

DWORD grpc_get_default_wsa_socket_flags();

void grpc_winsocket_finish(grpc_winsocket*);

#endif

#endif
