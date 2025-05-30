
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_IOMGR_TCP_SERVER_H
#define GRPC_SRC_CORE_LIB_IOMGR_TCP_SERVER_H

#include <grpc/event_engine/endpoint_config.h>
#include <grpc/grpc.h>
#include <grpc/impl/grpc_types.h>
#include <grpc/support/port_platform.h>

#include <vector>

#include "src/core/lib/iomgr/closure.h"
#include "src/core/lib/iomgr/endpoint.h"
#include "src/core/lib/iomgr/resolve_address.h"

typedef struct grpc_tcp_server grpc_tcp_server;

typedef struct grpc_tcp_server_acceptor {

  grpc_tcp_server* from_server;

  unsigned port_index;
  unsigned fd_index;

  bool external_connection;
  int listener_fd;
  grpc_byte_buffer* pending_data;
} grpc_tcp_server_acceptor;

typedef void (*grpc_tcp_server_cb)(void* arg, grpc_endpoint* ep,
                                   grpc_pollset* accepting_pollset,
                                   grpc_tcp_server_acceptor* acceptor);
namespace grpc_core {

class TcpServerFdHandler {
 public:
  virtual ~TcpServerFdHandler() = default;
  virtual void Handle(int listener_fd, int fd,
                      grpc_byte_buffer* pending_read) = 0;
};
}

typedef struct grpc_tcp_server_vtable {
  grpc_error_handle (*create)(
      grpc_closure* shutdown_complete,
      const grpc_event_engine::experimental::EndpointConfig& config,
      grpc_tcp_server_cb on_accept_cb, void* cb_arg, grpc_tcp_server** server);
  void (*start)(grpc_tcp_server* server,
                const std::vector<grpc_pollset*>* pollsets);
  grpc_error_handle (*add_port)(grpc_tcp_server* s,
                                const grpc_resolved_address* addr,
                                int* out_port);
  grpc_core::TcpServerFdHandler* (*create_fd_handler)(grpc_tcp_server* s);
  unsigned (*port_fd_count)(grpc_tcp_server* s, unsigned port_index);
  int (*port_fd)(grpc_tcp_server* s, unsigned port_index, unsigned fd_index);
  grpc_tcp_server* (*ref)(grpc_tcp_server* s);
  void (*shutdown_starting_add)(grpc_tcp_server* s,
                                grpc_closure* shutdown_starting);
  void (*unref)(grpc_tcp_server* s);
  void (*shutdown_listeners)(grpc_tcp_server* s);
  int (*pre_allocated_fd)(grpc_tcp_server* s);
  void (*set_pre_allocated_fd)(grpc_tcp_server* s, int fd);
} grpc_tcp_server_vtable;

grpc_error_handle grpc_tcp_server_create(
    grpc_closure* shutdown_complete,
    const grpc_event_engine::experimental::EndpointConfig& config,
    grpc_tcp_server_cb on_accept_cb, void* cb_arg, grpc_tcp_server** server);

void grpc_tcp_server_start(grpc_tcp_server* server,
                           const std::vector<grpc_pollset*>* pollsets);

grpc_error_handle grpc_tcp_server_add_port(grpc_tcp_server* s,
                                           const grpc_resolved_address* addr,
                                           int* out_port);

grpc_core::TcpServerFdHandler* grpc_tcp_server_create_fd_handler(
    grpc_tcp_server* s);

unsigned grpc_tcp_server_port_fd_count(grpc_tcp_server* s, unsigned port_index);

int grpc_tcp_server_port_fd(grpc_tcp_server* s, unsigned port_index,
                            unsigned fd_index);

grpc_tcp_server* grpc_tcp_server_ref(grpc_tcp_server* s);

void grpc_tcp_server_shutdown_starting_add(grpc_tcp_server* s,
                                           grpc_closure* shutdown_starting);

void grpc_tcp_server_unref(grpc_tcp_server* s);

void grpc_tcp_server_shutdown_listeners(grpc_tcp_server* s);

int grpc_tcp_server_pre_allocated_fd(grpc_tcp_server* s);

void grpc_tcp_server_set_pre_allocated_fd(grpc_tcp_server* s, int fd);

void grpc_tcp_server_global_init();

void grpc_set_tcp_server_impl(grpc_tcp_server_vtable* impl);

#endif
