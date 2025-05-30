
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_IOMGR_SOCKET_MUTATOR_H
#define GRPC_SRC_CORE_LIB_IOMGR_SOCKET_MUTATOR_H

#include <grpc/impl/grpc_types.h>
#include <grpc/support/port_platform.h>
#include <grpc/support/sync.h>
#include <stdbool.h>

typedef enum {

  GRPC_FD_CLIENT_CONNECTION_USAGE,

  GRPC_FD_SERVER_LISTENER_USAGE,

  GRPC_FD_SERVER_CONNECTION_USAGE,
} grpc_fd_usage;

typedef struct {

  int fd;

  grpc_fd_usage usage;
} grpc_mutate_socket_info;

struct grpc_socket_mutator_vtable {

  bool (*mutate_fd)(int fd, grpc_socket_mutator* mutator);

  int (*compare)(grpc_socket_mutator* a, grpc_socket_mutator* b);

  void (*destroy)(grpc_socket_mutator* mutator);

  bool (*mutate_fd_2)(const grpc_mutate_socket_info* info,
                      grpc_socket_mutator* mutator);
};

struct grpc_socket_mutator {
  const grpc_socket_mutator_vtable* vtable;
  gpr_refcount refcount;
};

void grpc_socket_mutator_init(grpc_socket_mutator* mutator,
                              const grpc_socket_mutator_vtable* vtable);

grpc_arg grpc_socket_mutator_to_arg(grpc_socket_mutator* mutator);

bool grpc_socket_mutator_mutate_fd(grpc_socket_mutator* mutator, int fd,
                                   grpc_fd_usage usage);

int grpc_socket_mutator_compare(grpc_socket_mutator* a, grpc_socket_mutator* b);

grpc_socket_mutator* grpc_socket_mutator_ref(grpc_socket_mutator* mutator);
void grpc_socket_mutator_unref(grpc_socket_mutator* mutator);

#endif
