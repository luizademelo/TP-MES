
// Copyright 2015 gRPC authors.

#include <grpc/support/port_platform.h>

#include "src/core/lib/iomgr/port.h"

#ifdef GRPC_WINSOCK_SOCKET

#include <winsock2.h>

#include <grpc/support/alloc.h>
#include <grpc/support/log_windows.h>
#include <mswsock.h>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/strings/str_format.h"
#include "src/core/lib/iomgr/iocp_windows.h"
#include "src/core/lib/iomgr/iomgr_internal.h"
#include "src/core/lib/iomgr/pollset.h"
#include "src/core/lib/iomgr/pollset_windows.h"
#include "src/core/lib/iomgr/sockaddr_windows.h"
#include "src/core/lib/iomgr/socket_windows.h"
#include "src/core/util/crash.h"

static DWORD s_wsa_socket_flags;

grpc_winsocket* grpc_winsocket_create(SOCKET socket, const char* name) {
  grpc_winsocket* r = (grpc_winsocket*)gpr_malloc(sizeof(grpc_winsocket));
  memset(r, 0, sizeof(grpc_winsocket));
  r->socket = socket;
  gpr_mu_init(&r->state_mu);
  grpc_iomgr_register_object(
      &r->iomgr_object, absl::StrFormat("%s:socket=0x%p", name, r).c_str());
  grpc_iocp_add_socket(r);
  return r;
}

SOCKET grpc_winsocket_wrapped_socket(grpc_winsocket* socket) {
  return socket->socket;
}

void grpc_winsocket_shutdown(grpc_winsocket* winsocket) {

  int status;
  GUID guid = WSAID_DISCONNECTEX;
  LPFN_DISCONNECTEX DisconnectEx;
  DWORD ioctl_num_bytes;

  gpr_mu_lock(&winsocket->state_mu);
  if (winsocket->shutdown_called) {
    gpr_mu_unlock(&winsocket->state_mu);
    return;
  }
  winsocket->shutdown_called = true;
  bool register_shutdown = false;

  if (winsocket->read_info.closure && !winsocket->read_info.has_pending_iocp) {
    winsocket->read_info.bytes_transferred = 0;
    winsocket->read_info.wsa_error = WSA_OPERATION_ABORTED;
    grpc_core::ExecCtx::Run(DEBUG_LOCATION, winsocket->read_info.closure,
                            absl::OkStatus());

    winsocket->read_info.closure_already_executed_at_shutdown = true;
    register_shutdown = true;
  }

  if (winsocket->write_info.closure &&
      !winsocket->write_info.has_pending_iocp) {
    winsocket->write_info.bytes_transferred = 0;
    winsocket->write_info.wsa_error = WSA_OPERATION_ABORTED;
    grpc_core::ExecCtx::Run(DEBUG_LOCATION, winsocket->write_info.closure,
                            absl::OkStatus());

    winsocket->write_info.closure_already_executed_at_shutdown = true;
    register_shutdown = true;
  }

  if (register_shutdown) {

    grpc_iocp_register_socket_shutdown_socket_locked(winsocket);
  }
  gpr_mu_unlock(&winsocket->state_mu);

  status = WSAIoctl(winsocket->socket, SIO_GET_EXTENSION_FUNCTION_POINTER,
                    &guid, sizeof(guid), &DisconnectEx, sizeof(DisconnectEx),
                    &ioctl_num_bytes, NULL, NULL);

  if (status == 0) {
    DisconnectEx(winsocket->socket, NULL, 0, 0);
  } else {
    char* utf8_message = gpr_format_message(WSAGetLastError());
    VLOG(2) << "Unable to retrieve DisconnectEx pointer : " << utf8_message;
    gpr_free(utf8_message);
  }

  closesocket(winsocket->socket);
}

static void destroy(grpc_winsocket* winsocket) {
  grpc_iomgr_unregister_object(&winsocket->iomgr_object);
  gpr_mu_destroy(&winsocket->state_mu);
  gpr_free(winsocket);
}

static bool check_destroyable(grpc_winsocket* winsocket) {
  return winsocket->destroy_called == true &&
         winsocket->write_info.closure == NULL &&
         winsocket->read_info.closure == NULL;
}

void grpc_winsocket_finish(grpc_winsocket* winsocket) {
  grpc_iocp_finish_socket_shutdown(winsocket);
  destroy(winsocket);
}

void grpc_winsocket_destroy(grpc_winsocket* winsocket) {
  gpr_mu_lock(&winsocket->state_mu);
  CHECK(!winsocket->destroy_called);
  winsocket->destroy_called = true;
  bool should_destroy = check_destroyable(winsocket);
  gpr_mu_unlock(&winsocket->state_mu);
  if (should_destroy) {
    grpc_winsocket_finish(winsocket);
  }
}

static void socket_notify_on_iocp(grpc_winsocket* socket, grpc_closure* closure,
                                  grpc_winsocket_callback_info* info) {
  CHECK(info->closure == NULL);
  gpr_mu_lock(&socket->state_mu);
  if (info->has_pending_iocp) {
    info->has_pending_iocp = 0;
    grpc_core::ExecCtx::Run(DEBUG_LOCATION, closure, absl::OkStatus());
  } else {
    info->closure = closure;
  }
  gpr_mu_unlock(&socket->state_mu);
}

void grpc_socket_notify_on_write(grpc_winsocket* socket,
                                 grpc_closure* closure) {
  socket_notify_on_iocp(socket, closure, &socket->write_info);
}

void grpc_socket_notify_on_read(grpc_winsocket* socket, grpc_closure* closure) {
  socket_notify_on_iocp(socket, closure, &socket->read_info);
}

bool grpc_socket_become_ready(grpc_winsocket* socket,
                              grpc_winsocket_callback_info* info) {
  CHECK(!info->has_pending_iocp);
  if (info->closure) {

    if (!info->closure_already_executed_at_shutdown) {
      grpc_core::ExecCtx::Run(DEBUG_LOCATION, info->closure, absl::OkStatus());
    }
    info->closure = NULL;
  } else {
    info->has_pending_iocp = 1;
  }
  return check_destroyable(socket);
}

static gpr_once g_probe_ipv6_once = GPR_ONCE_INIT;
static bool g_ipv6_loopback_available = false;

static void probe_ipv6_once(void) {
  SOCKET s = socket(AF_INET6, SOCK_STREAM, 0);
  g_ipv6_loopback_available = 0;
  if (s == INVALID_SOCKET) {
    VLOG(2) << "Disabling AF_INET6 sockets because socket() failed.";
  } else {
    grpc_sockaddr_in6 addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin6_family = AF_INET6;
    addr.sin6_addr.s6_addr[15] = 1;
    if (bind(s, reinterpret_cast<grpc_sockaddr*>(&addr), sizeof(addr)) == 0) {
      g_ipv6_loopback_available = 1;
    } else {
      VLOG(2) << "Disabling AF_INET6 sockets because ::1 is not available.";
    }
    closesocket(s);
  }
}

int grpc_ipv6_loopback_available(void) {
  gpr_once_init(&g_probe_ipv6_once, probe_ipv6_once);
  return g_ipv6_loopback_available;
}

DWORD grpc_get_default_wsa_socket_flags() { return s_wsa_socket_flags; }

void grpc_wsa_socket_flags_init() {
  s_wsa_socket_flags = WSA_FLAG_OVERLAPPED;

  SOCKET sock = WSASocket(AF_INET6, SOCK_STREAM, IPPROTO_TCP, NULL, 0,
                          s_wsa_socket_flags | WSA_FLAG_NO_HANDLE_INHERIT);
  if (sock != INVALID_SOCKET) {

    s_wsa_socket_flags |= WSA_FLAG_NO_HANDLE_INHERIT;
    closesocket(sock);
  }
}

#endif
