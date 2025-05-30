
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_IOMGR_POLLSET_H
#define GRPC_SRC_CORE_LIB_IOMGR_POLLSET_H

#include <grpc/support/port_platform.h>
#include <grpc/support/sync.h>
#include <grpc/support/time.h>

#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/iomgr/iomgr_fwd.h"

typedef struct grpc_pollset_worker grpc_pollset_worker;

typedef struct grpc_pollset_vtable {
  void (*global_init)(void);
  void (*global_shutdown)(void);
  void (*init)(grpc_pollset* pollset, gpr_mu** mu);
  void (*shutdown)(grpc_pollset* pollset, grpc_closure* closure);
  void (*destroy)(grpc_pollset* pollset);
  grpc_error_handle (*work)(grpc_pollset* pollset, grpc_pollset_worker** worker,
                            grpc_core::Timestamp deadline);
  grpc_error_handle (*kick)(grpc_pollset* pollset,
                            grpc_pollset_worker* specific_worker);
  size_t (*pollset_size)(void);
} grpc_pollset_vtable;

void grpc_set_pollset_vtable(grpc_pollset_vtable* vtable);

void grpc_pollset_global_init(void);
void grpc_pollset_global_shutdown(void);

size_t grpc_pollset_size(void);

void grpc_pollset_init(grpc_pollset* pollset, gpr_mu** mu);

void grpc_pollset_shutdown(grpc_pollset* pollset, grpc_closure* closure);
void grpc_pollset_destroy(grpc_pollset* pollset);

grpc_error_handle grpc_pollset_work(grpc_pollset* pollset,
                                    grpc_pollset_worker** worker,
                                    grpc_core::Timestamp deadline);

grpc_error_handle grpc_pollset_kick(grpc_pollset* pollset,
                                    grpc_pollset_worker* specific_worker);

#endif
