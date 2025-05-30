
// Copyright 2016 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_IOMGR_TIMER_GENERIC_H
#define GRPC_SRC_CORE_LIB_IOMGR_TIMER_GENERIC_H

#include <grpc/support/port_platform.h>
#include <grpc/support/time.h>

#include "src/core/lib/iomgr/exec_ctx.h"

struct grpc_timer {
  gpr_atm deadline;
  uint32_t heap_index;
  bool pending;
  struct grpc_timer* next;
  struct grpc_timer* prev;
  grpc_closure* closure;
#ifndef NDEBUG
  struct grpc_timer* hash_table_next;
#endif
};

#endif
