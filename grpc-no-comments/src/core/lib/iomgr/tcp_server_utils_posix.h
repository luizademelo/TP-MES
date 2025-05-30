
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

typedef struct grpc_tcp_listener {
  int fd;
  grpc_fd* emfd;
  grpc_tcp_server* server;
  grpc_resolved_address addr;
  int port;
  unsigned port_index;
  unsigned fd_index;
  grpc_closure read_closure;
  grpc_closure destroyed_closure;
  struct grpc_tcp_listener* next;

  struct grpc_tcp_listener* sibling;
  int is_sibling;

  grpc_closure retry_closure;
  grpc_timer retry_timer;
  gpr_atm retry_timer_armed;
} grpc_tcp_listener;

struct grpc_tcp_server {
  gpr_refcount refs;

  grpc_tcp_server_cb on_accept_cb = nullptr;
  void* on_accept_cb_arg = nullptr;

  gpr_mu mu;

  size_t active_ports = 0;

  size_t destroyed_ports = 0;

  bool shutdown = false;

  bool shutdown_listeners = false;

  bool so_reuseport = false;

  bool expand_wildcard_addrs = false;

  grpc_tcp_listener* head = nullptr;
  grpc_tcp_listener* tail = nullptr;
  unsigned nports = 0;

  grpc_closure_list shutdown_starting{nullptr, nullptr};

  grpc_closure* shutdown_complete = nullptr;

  const std::vector<grpc_pollset*>* pollsets = nullptr;

  gpr_atm next_pollset_to_assign = 0;

  grpc_core::PosixTcpOptions options;

  grpc_core::TcpServerFdHandler* fd_handler = nullptr;

  grpc_core::MemoryQuotaRefPtr memory_quota;

  int n_bind_ports = 0;
  absl::flat_hash_map<int, std::tuple<int, int>> listen_fd_to_index_map;
  std::unique_ptr<grpc_event_engine::experimental::EventEngine::Listener>
      ee_listener = nullptr;

  int pre_allocated_fd;
};

grpc_error_handle grpc_tcp_server_add_addr(grpc_tcp_server* s,
                                           const grpc_resolved_address* addr,
                                           unsigned port_index,
                                           unsigned fd_index,
                                           grpc_dualstack_mode* dsmode,
                                           grpc_tcp_listener** listener);

grpc_error_handle grpc_tcp_server_add_all_local_addrs(grpc_tcp_server* s,
                                                      unsigned port_index,
                                                      int requested_port,
                                                      int* out_port);

grpc_error_handle grpc_tcp_server_prepare_socket(
    grpc_tcp_server*, int fd, const grpc_resolved_address* addr,
    bool so_reuseport, int* port);

bool grpc_tcp_server_have_ifaddrs(void);

void grpc_tcp_server_listener_initialize_retry_timer(
    grpc_tcp_listener* listener);

#endif
