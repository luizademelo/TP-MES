
// Copyright 2017 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_IOMGR_SOCKET_FACTORY_POSIX_H
#define GRPC_SRC_CORE_LIB_IOMGR_SOCKET_FACTORY_POSIX_H

#include <grpc/impl/grpc_types.h>
#include <grpc/support/port_platform.h>
#include <grpc/support/sync.h>

#include "src/core/lib/iomgr/resolve_address.h"

struct grpc_socket_factory_vtable {

  int (*socket)(grpc_socket_factory* factory, int domain, int type,
                int protocol);

  int (*bind)(grpc_socket_factory* factory, int sockfd,
              const grpc_resolved_address* addr);

  int (*compare)(grpc_socket_factory* a, grpc_socket_factory* b);

  void (*destroy)(grpc_socket_factory* factory);
};

struct grpc_socket_factory {
  const grpc_socket_factory_vtable* vtable;
  gpr_refcount refcount;
};

void grpc_socket_factory_init(grpc_socket_factory* factory,
                              const grpc_socket_factory_vtable* vtable);

grpc_arg grpc_socket_factory_to_arg(grpc_socket_factory* factory);

int grpc_socket_factory_socket(grpc_socket_factory* factory, int domain,
                               int type, int protocol);

int grpc_socket_factory_bind(grpc_socket_factory* factory, int sockfd,
                             const grpc_resolved_address* addr);

int grpc_socket_factory_compare(grpc_socket_factory* a, grpc_socket_factory* b);

grpc_socket_factory* grpc_socket_factory_ref(grpc_socket_factory* factory);
void grpc_socket_factory_unref(grpc_socket_factory* factory);

#endif
