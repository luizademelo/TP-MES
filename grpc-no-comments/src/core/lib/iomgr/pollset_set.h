
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_IOMGR_POLLSET_SET_H
#define GRPC_SRC_CORE_LIB_IOMGR_POLLSET_SET_H

#include <grpc/support/port_platform.h>

#include "src/core/lib/iomgr/iomgr_fwd.h"

typedef struct grpc_pollset_set_vtable {
  grpc_pollset_set* (*create)(void);
  void (*destroy)(grpc_pollset_set* pollset_set);
  void (*add_pollset)(grpc_pollset_set* pollset_set, grpc_pollset* pollset);
  void (*del_pollset)(grpc_pollset_set* pollset_set, grpc_pollset* pollset);
  void (*add_pollset_set)(grpc_pollset_set* bag, grpc_pollset_set* item);
  void (*del_pollset_set)(grpc_pollset_set* bag, grpc_pollset_set* item);
} grpc_pollset_set_vtable;

void grpc_set_pollset_set_vtable(grpc_pollset_set_vtable* vtable);

grpc_pollset_set* grpc_pollset_set_create(void);
void grpc_pollset_set_destroy(grpc_pollset_set* pollset_set);
void grpc_pollset_set_add_pollset(grpc_pollset_set* pollset_set,
                                  grpc_pollset* pollset);
void grpc_pollset_set_del_pollset(grpc_pollset_set* pollset_set,
                                  grpc_pollset* pollset);
void grpc_pollset_set_add_pollset_set(grpc_pollset_set* bag,
                                      grpc_pollset_set* item);
void grpc_pollset_set_del_pollset_set(grpc_pollset_set* bag,
                                      grpc_pollset_set* item);

#endif
