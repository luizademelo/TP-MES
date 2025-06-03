Here's the commented version of the code:

```c++
// Copyright 2017 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_IOMGR_TCP_SERVER_UTILS_POSIX_H
#define GRPC_SRC_CORE_LIB_IOMGR_TCP_SERVER_UTILS_POSIX_H

#include <grpc/support/port_platform.h>

#include <memory>

#include "absl/container/flat_hash_map.h"
#include "src/core/lib/event_engine/posix.h"
#include "src/core/lib/iomgr/ev_posix.h"
#include "src/core/lib/iomgr/resolve_address.h"
#include "src/core/lib/iomgr/socket_utils_posix.h"
#include "src/core/lib/iomgr/tcp_server.h"
#include "src/core/lib/iomgr/timer.h"
#include "src/core/lib/resource_quota/memory_quota.h"

// Structure representing a TCP listener in gRPC
typedef struct grpc_tcp_listener {
  int fd;                      // File descriptor for the listening socket
  grpc_fd* emfd;               // Event manager file descriptor wrapper
  grpc_tcp_server* server;     // Parent TCP server
  grpc_resolved_address addr;  // Resolved address this listener is bound to
  int port;                    // Port number this listener is bound to
  unsigned port_index;         // Index of this port in the server's port list
  unsigned fd_index;           // Index of this file descriptor
  grpc_closure read_closure;   // Closure for read operations
  grpc_closure destroyed_closure; // Closure for destruction notification
  struct grpc_tcp_listener* next; // Pointer to next listener in the list

  struct grpc_tcp_listener* sibling; // Pointer to sibling listener (for SO_REUSEPORT)
  int is_sibling;                    // Flag indicating if this is a sibling listener

  grpc_closure retry_closure;        // Closure for retry operations
  grpc_timer retry_timer;            // Timer for retry operations
  gpr_atm retry_timer_armed;         // Atomic flag indicating if retry timer is armed
} grpc_tcp_listener;

// Structure representing a TCP server in gRPC
struct grpc_tcp_server {
  gpr_refcount refs;  // Reference count for the server

  // Callback and argument for when a connection is accepted
  grpc_tcp_server_cb on_accept_cb = nullptr;
  void* on_accept_cb_arg = nullptr;

  gpr_mu mu;  // Mutex for thread synchronization

  size_t active_ports = 0;    // Number of currently active listening ports
  size_t destroyed_ports = 0; // Number of destroyed ports

  bool shutdown = false;            // Flag indicating if server is shutting down
  bool shutdown_listeners = false;  // Flag indicating if listeners should be shut down
  bool so_reuseport = false;        // Flag indicating if SO_REUSEPORT is enabled
  bool expand_wildcard_addrs = false; // Flag for wildcard address expansion

  // Linked list of listeners
  grpc_tcp_listener* head = nullptr;
  grpc_tcp_listener* tail = nullptr;
  unsigned nports = 0;  // Total number of ports

  grpc_closure_list shutdown_starting{nullptr, nullptr}; // Closures to run when shutdown starts
  grpc_closure* shutdown_complete = nullptr;             // Closure to run when shutdown completes

  const std::vector<grpc_pollset*>* pollsets = nullptr; // Pollsets for event handling
  gpr_atm next_pollset_to_assign = 0; // Atomic counter for round-robin pollset assignment

  grpc_core::PosixTcpOptions options; // TCP server options
  grpc_core::TcpServerFdHandler* fd_handler = nullptr; // Handler for file descriptors
  grpc_core::MemoryQuotaRefPtr memory_quota; // Memory quota for the server

  int n_bind_ports = 0; // Number of ports to bind
  // Mapping of file descriptors to their index and port index
  absl::flat_hash_map<int, std::tuple<int, int>> listen_fd_to_index_map;
  // Event engine listener for handling connections
  std::unique_ptr<grpc_event_engine::experimental::EventEngine::Listener>
      ee_listener = nullptr;

  int pre_allocated_fd; // Pre-allocated file descriptor
};

// Adds a specific address to the TCP server
grpc_error_handle grpc_tcp_server_add_addr(grpc_tcp_server* s,
                                           const grpc_resolved_address* addr,
                                           unsigned port_index,
                                           unsigned fd_index,
                                           grpc_dualstack_mode* dsmode,
                                           grpc_tcp_listener** listener);

// Adds all local addresses to the TCP server
grpc_error_handle grpc_tcp_server_add_all_local_addrs(grpc_tcp_server* s,
                                                      unsigned port_index,
                                                      int requested_port,
                                                      int* out_port);

// Prepares a socket for the TCP server
grpc_error_handle grpc_tcp_server_prepare_socket(
    grpc_tcp_server*, int fd, const grpc_resolved_address* addr,
    bool so_reuseport, int* port);

// Checks if the system has network interfaces available
bool grpc_tcp_server_have_ifaddrs(void);

// Initializes the retry timer for a TCP listener
void grpc_tcp_server_listener_initialize_retry_timer(
    grpc_tcp_listener* listener);

#endif
```