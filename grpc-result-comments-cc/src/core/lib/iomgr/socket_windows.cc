Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

// Platform-specific includes and definitions
#include <grpc/support/port_platform.h>
#include "src/core/lib/iomgr/port.h"

// Windows-specific socket implementation
#ifdef GRPC_WINSOCK_SOCKET

#include <winsock2.h>

// GRPC support libraries
#include <grpc/support/alloc.h>
#include <grpc/support/log_windows.h>
#include <mswsock.h>

// Abseil libraries for logging and checking
#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/strings/str_format.h"

// GRPC internal I/O management headers
#include "src/core/lib/iomgr/iocp_windows.h"
#include "src/core/lib/iomgr/iomgr_internal.h"
#include "src/core/lib/iomgr/pollset.h"
#include "src/core/lib/iomgr/pollset_windows.h"
#include "src/core/lib/iomgr/sockaddr_windows.h"
#include "src/core/lib/iomgr/socket_windows.h"
#include "src/core/util/crash.h"

// Static variable for WSA socket flags
static DWORD s_wsa_socket_flags;

// Creates a new grpc_winsocket structure and initializes it
// Parameters:
//   socket - The Windows socket to wrap
//   name - Descriptive name for the socket (used for debugging)
// Returns:
//   A newly allocated and initialized grpc_winsocket
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

// Returns the underlying Windows socket from a grpc_winsocket
SOCKET grpc_winsocket_wrapped_socket(grpc_winsocket* socket) {
  return socket->socket;
}

// Shuts down a winsocket by:
// 1. Cancelling pending operations
// 2. Executing pending closures
// 3. Disconnecting the socket
// 4. Closing the socket
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

  // Handle pending read operations
  if (winsocket->read_info.closure && !winsocket->read_info.has_pending_iocp) {
    winsocket->read_info.bytes_transferred = 0;
    winsocket->read_info.wsa_error = WSA_OPERATION_ABORTED;
    grpc_core::ExecCtx::Run(DEBUG_LOCATION, winsocket->read_info.closure,
                            absl::OkStatus());

    winsocket->read_info.closure_already_executed_at_shutdown = true;
    register_shutdown = true;
  }

  // Handle pending write operations
  if (winsocket->write_info.closure &&
      !winsocket->write_info.has_pending_iocp) {
    winsocket->write_info.bytes_transferred = 0;
    winsocket->write_info.wsa_error = WSA_OPERATION_ABORTED;
    grpc_core::ExecCtx::Run(DEBUG_LOCATION, winsocket->write_info.closure,
                            absl::OkStatus());

    winsocket->write_info.closure_already_executed_at_shutdown = true;
    register_shutdown = true;
  }

  // Register socket shutdown if needed
  if (register_shutdown) {
    grpc_iocp_register_socket_shutdown_socket_locked(winsocket);
  }
  gpr_mu_unlock(&winsocket->state_mu);

  // Attempt to use DisconnectEx for clean shutdown
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

  // Close the socket
  closesocket(winsocket->socket);
}

// Internal function to destroy a winsocket and free its resources
static void destroy(grpc_winsocket* winsocket) {
  grpc_iomgr_unregister_object(&winsocket->iomgr_object);
  gpr_mu_destroy(&winsocket->state_mu);
  gpr_free(winsocket);
}

// Checks if a winsocket is ready to be destroyed
static bool check_destroyable(grpc_winsocket* winsocket) {
  return winsocket->destroy_called == true &&
         winsocket->write_info.closure == NULL &&
         winsocket->read_info.closure == NULL;
}

// Completes the shutdown process and destroys the winsocket
void grpc_winsocket_finish(grpc_winsocket* winsocket) {
  grpc_iocp_finish_socket_shutdown(winsocket);
  destroy(winsocket);
}

// Marks a winsocket for destruction and destroys it if ready
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

// Internal helper to notify on IOCP completion for either read or write
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

// Registers a write completion callback
void grpc_socket_notify_on_write(grpc_winsocket* socket,
                                 grpc_closure* closure) {
  socket_notify_on_iocp(socket, closure, &socket->write_info);
}

// Registers a read completion callback
void grpc_socket_notify_on_read(grpc_winsocket* socket, grpc_closure* closure) {
  socket_notify_on_iocp(socket, closure, &socket->read_info);
}

// Called when a socket operation completes
// Returns true if the socket is ready to be destroyed
bool grpc_socket_become_ready(grpc_winsocket* socket,
                              grpc_winsocket_callback_info* info) {
  CHECK(!info->has_pending_iocp);
  if (info->closure) {
    // Execute the completion callback if not already executed during shutdown
    if (!info->closure_already_executed_at_shutdown) {
      grpc_core::ExecCtx::Run(DEBUG_LOCATION, info->closure, absl::OkStatus());
    }
    info->closure = NULL;
  } else {
    info->has_pending_iocp = 1;
  }
  return check_destroyable(socket);
}

// IPv6 availability detection
static gpr_once g_probe_ipv6_once = GPR_ONCE_INIT;
static bool g_ipv6_loopback_available = false;

// Probes IPv6 support by attempting to create and bind to an IPv6 socket
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

// Returns whether IPv6 loopback is available
int grpc_ipv6_loopback_available(void) {
  gpr_once_init(&g_probe_ipv6_once, probe_ipv6_once);
  return g_ipv6_loopback_available;
}

// Returns the default WSA socket flags
DWORD grpc_get_default_wsa_socket_flags() { return s_wsa_socket_flags; }

// Initializes WSA socket flags, testing for handle inheritance support
void grpc_wsa_socket_flags_init() {
  s_wsa_socket_flags = WSA_FLAG_OVERLAPPED;

  // Test if we can use WSA_FLAG_NO_HANDLE_INHERIT
  SOCKET sock = WSASocket(AF_INET6, SOCK_STREAM, IPPROTO_TCP, NULL, 0,
                          s_wsa_socket_flags | WSA_FLAG_NO_HANDLE_INHERIT);
  if (sock != INVALID_SOCKET) {
    // Flag is supported, enable it by default
    s_wsa_socket_flags |= WSA_FLAG_NO_HANDLE_INHERIT;
    closesocket(sock);
  }
}

#endif
```