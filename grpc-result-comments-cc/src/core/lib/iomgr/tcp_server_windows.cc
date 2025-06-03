Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

#include <grpc/support/port_platform.h>
#include "src/core/lib/iomgr/port.h"

#ifdef GRPC_WINSOCK_SOCKET

// Windows-specific includes for socket operations and event engine
#include <grpc/event_engine/endpoint_config.h>
#include <grpc/event_engine/event_engine.h>
#include <grpc/event_engine/memory_allocator.h>
#include <grpc/support/alloc.h>
#include <grpc/support/log_windows.h>
#include <grpc/support/string_util.h>
#include <grpc/support/sync.h>
#include <grpc/support/time.h>
#include <inttypes.h>
#include <io.h>

#include <vector>

// Additional includes for logging, checking, and string operations
#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/strings/str_cat.h"
#include "src/core/lib/address_utils/sockaddr_utils.h"
#include "src/core/lib/event_engine/memory_allocator_factory.h"
#include "src/core/lib/event_engine/resolved_address_internal.h"
#include "src/core/lib/event_engine/tcp_socket_utils.h"
#include "src/core/lib/event_engine/windows/windows_engine.h"
#include "src/core/lib/event_engine/windows/windows_listener.h"
#include "src/core/lib/iomgr/closure.h"
#include "src/core/lib/iomgr/event_engine_shims/closure.h"
#include "src/core/lib/iomgr/event_engine_shims/endpoint.h"
#include "src/core/lib/iomgr/iocp_windows.h"
#include "src/core/lib/iomgr/pollset_windows.h"
#include "src/core/lib/iomgr/resolve_address.h"
#include "src/core/lib/iomgr/sockaddr.h"
#include "src/core/lib/iomgr/socket_windows.h"
#include "src/core/lib/iomgr/tcp_server.h"
#include "src/core/lib/iomgr/tcp_windows.h"
#include "src/core/lib/resource_quota/api.h"
#include "src/core/lib/resource_quota/resource_quota.h"
#include "src/core/lib/slice/slice_internal.h"
#include "src/core/util/crash.h"

// Minimum safe size for accept queue
#define MIN_SAFE_ACCEPT_QUEUE_SIZE 100

namespace {
// Using declarations for Event Engine components
using ::grpc_event_engine::experimental::CreateResolvedAddress;
using ::grpc_event_engine::experimental::EndpointConfig;
using ::grpc_event_engine::experimental::EventEngine;
using ::grpc_event_engine::experimental::grpc_event_engine_endpoint_create;
using ::grpc_event_engine::experimental::MemoryAllocator;
using ::grpc_event_engine::experimental::MemoryQuotaBasedMemoryAllocatorFactory;
using ::grpc_event_engine::experimental::ResolvedAddressSetPort;
using ::grpc_event_engine::experimental::RunEventEngineClosure;
}

// Forward declaration of TCP listener structure
typedef struct grpc_tcp_listener grpc_tcp_listener;

// Structure representing a TCP listener
struct grpc_tcp_listener {
#ifdef GRPC_HAVE_UNIX_SOCKET
  // Buffer for Unix domain socket addresses
  uint8_t addresses[(sizeof(sockaddr_un) + 16) * 2] = {};
#else
  // Buffer for IPv6 socket addresses
  uint8_t addresses[(sizeof(grpc_sockaddr_in6) + 16) * 2];
#endif

  SOCKET new_socket;           // Newly accepted socket
  grpc_winsocket* socket;      // Windows socket wrapper
  grpc_resolved_address resolved_addr;  // Resolved address for binding
  int port;                    // Port number
  unsigned port_index;         // Index of this port in server's list
  grpc_tcp_server* server;     // Parent server instance
  LPFN_ACCEPTEX AcceptEx;      // Pointer to AcceptEx function
  int shutting_down;           // Flag indicating shutdown state
  int outstanding_calls;       // Number of outstanding accept calls
  grpc_closure on_accept;     // Closure for accept completion
  struct grpc_tcp_listener* next;  // Next listener in linked list
};

// Structure representing a TCP server
struct grpc_tcp_server {
  gpr_refcount refs;           // Reference counting
  grpc_tcp_server_cb on_accept_cb;  // Callback for new connections
  void* on_accept_cb_arg;      // Argument for accept callback
  gpr_mu mu;                  // Mutex for thread safety
  int active_ports;           // Number of active listening ports
  grpc_tcp_listener* head;    // Head of listeners list
  grpc_tcp_listener* tail;    // Tail of listeners list
  grpc_closure_list shutdown_starting;  // Closures to run on shutdown start
  grpc_closure* shutdown_complete;  // Closure to run on shutdown completion
  std::unique_ptr<EventEngine::Listener> ee_listener;  // EventEngine listener
};

// Unlinks a Unix domain socket file if the address is for a Unix socket
void unlink_if_unix_domain_socket(const grpc_resolved_address* resolved_addr) {
#ifdef GRPC_HAVE_UNIX_SOCKET
  const grpc_sockaddr* addr =
      reinterpret_cast<const grpc_sockaddr*>(resolved_addr->addr);
  if (addr->sa_family != AF_UNIX) {
    return;
  }
  struct sockaddr_un* un =
      reinterpret_cast<struct sockaddr_un*>(const_cast<sockaddr*>(addr));

  // Skip abstract namespace sockets
  if (un->sun_path[0] == '\0' && un->sun_path[1] != '\0') {
    return;
  }

  // Convert path to wide char for Windows API
  std::wstring wide_path;
  int needed = MultiByteToWideChar(CP_UTF8, 0, un->sun_path, -1, NULL, 0);
  if (needed <= 0) {
    return;
  }
  wide_path.resize(needed, L'\0');
  if (MultiByteToWideChar(CP_UTF8, 0, un->sun_path, -1, wide_path.data(),
                          needed) == 0) {
    return;
  }

  // Check file attributes before deleting
  DWORD attr = ::GetFileAttributesW(wide_path.data());
  if (attr == INVALID_FILE_ATTRIBUTES) {
    return;
  }
  // Don't delete directories or read-only files
  if (attr & FILE_ATTRIBUTE_DIRECTORY || attr & FILE_ATTRIBUTE_READONLY) {
    return;
  }
  ::DeleteFileW(wide_path.data());
#else
  (void)resolved_addr;  // Silence unused parameter warning
#endif
}

// Creates a new TCP server instance
static grpc_error_handle tcp_server_create(grpc_closure* shutdown_complete,
                                           const EndpointConfig& config,
                                           grpc_tcp_server_cb on_accept_cb,
                                           void* on_accept_cb_arg,
                                           grpc_tcp_server** server) {
  grpc_tcp_server* s = (grpc_tcp_server*)gpr_malloc(sizeof(grpc_tcp_server));
  gpr_ref_init(&s->refs, 1);  // Initialize reference count
  gpr_mu_init(&s->mu);       // Initialize mutex
  s->active_ports = 0;       // No active ports initially
  s->on_accept_cb = on_accept_cb;
  s->on_accept_cb_arg = on_accept_cb_arg;
  s->head = NULL;           // Empty listeners list
  s->tail = NULL;
  s->shutdown_starting.head = NULL;  // Empty shutdown list
  s->shutdown_starting.tail = NULL;
  s->shutdown_complete = shutdown_complete;
  new (&s->ee_listener) std::unique_ptr<EventEngine::Listener>(nullptr);  // Initialize unique_ptr
  *server = s;
  return absl::OkStatus();
}

// Destroys the server instance
static void destroy_server(void* arg, grpc_error_handle error) {
  grpc_tcp_server* s = (grpc_tcp_server*)arg;

  // Clean up all listeners
  while (s->head) {
    grpc_tcp_listener* sp = s->head;
    s->head = sp->next;
    sp->next = NULL;
    grpc_winsocket_destroy(sp->socket);  // Clean up socket
    unlink_if_unix_domain_socket(&sp->resolved_addr);  // Clean up Unix socket if needed
    gpr_free(sp);  // Free listener memory
  }
  std::destroy_at(&s->ee_listener);  // Properly destroy unique_ptr
  gpr_mu_destroy(&s->mu);  // Destroy mutex
  gpr_free(s);  // Free server memory
}

// Completes server shutdown
static void finish_shutdown_locked(grpc_tcp_server* s) {
  if (s->shutdown_complete != NULL) {
    grpc_core::ExecCtx::Run(DEBUG_LOCATION, s->shutdown_complete,
                            absl::OkStatus());
  }

  // Schedule server destruction
  grpc_core::ExecCtx::Run(
      DEBUG_LOCATION,
      GRPC_CLOSURE_CREATE(destroy_server, s, grpc_schedule_on_exec_ctx),
      absl::OkStatus());
}

// Increments server reference count
static grpc_tcp_server* tcp_server_ref(grpc_tcp_server* s) {
  gpr_ref_non_zero(&s->refs);
  return s;
}

// Adds a closure to be run when shutdown starts
static void tcp_server_shutdown_starting_add(grpc_tcp_server* s,
                                             grpc_closure* shutdown_starting) {
  gpr_mu_lock(&s->mu);
  grpc_closure_list_append(&s->shutdown_starting, shutdown_starting,
                           absl::OkStatus());
  gpr_mu_unlock(&s->mu);
}

// Initiates server shutdown
static void tcp_server_destroy(grpc_tcp_server* s) {
  grpc_tcp_listener* sp;
  gpr_mu_lock(&s->mu);

  if (s->active_ports == 0) {
    // No active ports, shutdown immediately
    finish_shutdown_locked(s);
  } else {
    // Shutdown all listeners
    for (sp = s->head; sp; sp = sp->next) {
      sp->shutting_down = 1;
      grpc_winsocket_shutdown(sp->socket);
    }
  }
  gpr_mu_unlock(&s->mu);
}

// Decrements server reference count and destroys if last reference
static void tcp_server_unref(grpc_tcp_server* s) {
  if (gpr_unref(&s->refs)) {
    grpc_tcp_server_shutdown_listeners(s);
    gpr_mu_lock(&s->mu);
    grpc_core::ExecCtx::RunList(DEBUG_LOCATION, &s->shutdown_starting);
    gpr_mu_unlock(&s->mu);
    tcp_server_destroy(s);
  }
}

// Prepares a socket for server operations (bind, listen)
static grpc_error_handle prepare_socket(SOCKET sock,
                                        const grpc_resolved_address* addr,
                                        int* port) {
  grpc_resolved_address sockname_temp;
  grpc_error_handle error;
  int sockname_temp_len;
  
  // Configure socket based on address family
  if (grpc_sockaddr_get_family(addr) == AF_UNIX) {
    error = grpc_tcp_set_non_block(sock);
  } else {
    error = grpc_tcp_prepare_socket(sock);
  }
  if (!error.ok()) {
    goto failure;
  }
  
  // Clean up any existing Unix domain socket file
  unlink_if_unix_domain_socket(addr);
  
  // Bind socket to address
  if (bind(sock, (const grpc_sockaddr*)addr->addr, (int)addr->len) ==
      SOCKET_ERROR) {
    error = GRPC_WSA_ERROR(WSAGetLastError(), "bind");
    goto failure;
  }

  // Start listening on socket
  if (listen(sock, SOMAXCONN) == SOCKET_ERROR) {
    error = GRPC_WSA_ERROR(WSAGetLastError(), "listen");
    goto failure;
  }

  // Get the actual bound port number
  sockname_temp_len = sizeof(struct sockaddr_storage);
  if (getsockname(sock, (grpc_sockaddr*)sockname_temp.addr,
                  &sockname_temp_len) == SOCKET_ERROR) {
    error = GRPC_WSA_ERROR(WSAGetLastError(), "getsockname");
    goto failure;
  }
  sockname_temp.len = (size_t)sockname_temp_len;

  *port = grpc_sockaddr_get_port(&sockname_temp);
  return absl::OkStatus();

failure:
  CHECK(!error.ok());
  error = GRPC_ERROR_CREATE_REFERENCING("Failed to prepare server socket",
                                        &error, 1);
  if (sock != INVALID_SOCKET) closesocket(sock);
  return error;
}

// Decrements active port count and notifies if server should shutdown
static void decrement_active_ports_and_notify_locked(grpc_tcp_listener* sp) {
  sp->shutting_down = 0;
  CHECK_GT(sp->server->active_ports, 0u);
  if (0 == --sp->server->active_ports) {
    finish_shutdown_locked(sp->server);
  }
}

// Starts an asynchronous accept operation on a listener
static grpc_error_handle start_accept_locked(grpc_tcp_listener* port) {
  SOCKET sock = INVALID_SOCKET;
  BOOL success;
  const DWORD addrlen = sizeof(port->addresses) / 2;
  DWORD bytes_received = 0;
  grpc_error_handle error;

  if (port->shutting_down) {
    return absl::OkStatus();
  }
  
  // Create new socket for accepting connection
  const int addr_family =
      grpc_sockaddr_get_family(&port->resolved_addr) == AF_UNIX ? AF_UNIX
                                                                : AF_INET6;
  const int protocol = addr_family == AF_UNIX ? 0 : IPPROTO_TCP;
  sock = WSASocket(addr_family, SOCK_STREAM, protocol, NULL, 0,
                   grpc_get_default_wsa_socket_flags());
  if (sock == INVALID_SOCKET) {
    error = GRPC_WSA_ERROR(WSAGetLastError(), "WSASocket");
    goto failure;
  }
  
  // Prepare the new socket
  if (addr_family == AF_UNIX) {
    error = grpc_tcp_set_non_block(sock);
  } else {
    error = grpc_tcp_prepare_socket(sock);
  }
  if (!error.ok()) goto failure;

  // Start AcceptEx operation
  success = port->AcceptEx(port->socket->socket, sock, port->addresses, 0,
                           addrlen, addrlen, &bytes_received,
                           &port->socket->read_info.overlapped);

  if (!success) {
    int last_error = WSAGetLastError();
    if (last_error != ERROR_IO_PENDING) {
      error = GRPC_WSA_ERROR(last_error, "AcceptEx");
      goto failure;
    }
  }

  // Store new socket and set up completion notification
  port->new_socket = sock;
  grpc_socket_notify_on_read(port->socket, &port->on_accept);
  port->outstanding_calls++;
  return error;

failure:
  CHECK(!error.ok());
  if (sock != INVALID_SOCKET) closesocket(sock);
  return error;
}

// Callback for when an accept operation completes
static void on_accept(void* arg, grpc_error_handle error) {
  grpc_tcp_listener* sp = (grpc_tcp_listener*)arg;
  SOCKET sock = sp->new_socket;
  grpc_winsocket_callback_info* info = &sp->socket->read_info;
  grpc_endpoint* ep = NULL;
  grpc_resolved_address peer_name;
  DWORD transferred_bytes;
  DWORD flags;
  BOOL wsa_success;
  int err;

  gpr_mu_lock(&sp->server->mu);

  peer_name.len = sizeof(struct sockaddr_storage);

  if (!error.ok()) {
    VLOG(2) << "Skipping on_accept due to error: "
            << grpc_core::StatusToString(error);

    gpr_mu_unlock(&sp->server->mu);
    return;
  }

  // Get results of AcceptEx operation
  transferred_bytes = 0;
  wsa_success = WSAGetOverlappedResult(sock, &info->overlapped,
                                       &transferred_bytes, FALSE, &flags);
  if (!wsa_success) {
    if (!sp->shutting_down) {
      char* utf8_message = gpr_format_message(WSAGetLastError());
      LOG(ERROR) << "on_accept error: " << utf8_message;
      gpr_free(utf8_message);
    }
    closesocket(sock);
  } else {
    if (!sp->shutting_down) {
      // Update socket context
      err = setsockopt(sock, SOL_SOCKET, SO_UPDATE_ACCEPT_CONTEXT,
                       (char*)&sp->socket->socket, sizeof(sp->socket->socket));
      if (err) {
        char* utf8_message = gpr_format_message(WSAGetLastError());
        LOG(ERROR) << "setsockopt error: " << utf8_message;
        gpr_free(utf8_message);
      }
      
      // Get peer name for logging
      int peer_name_len = (int)peer_name.len;
      err = getpeername(s