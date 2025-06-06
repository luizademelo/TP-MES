
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_IOMGR_TIMER_HEAP_H
#define GRPC_SRC_CORE_LIB_IOMGR_TIMER_HEAP_H

#include <grpc/support/port_platform.h>

#include "src/core/lib/iomgr/timer.h"

struct grpc_timer_heap {
  grpc_timer** timers;
  uint32_t timer_count;
  uint32_t timer_capacity;
};

bool grpc_timer_heap_add(grpc_timer_heap* heap, grpc_timer* timer);

void grpc_timer_heap_init(grpc_timer_heap* heap);
void grpc_timer_heap_destroy(grpc_timer_heap* heap);

void grpc_timer_heap_remove(grpc_timer_heap* heap, grpc_timer* timer);
grpc_timer* grpc_timer_heap_top(grpc_timer_heap* heap);
void grpc_timer_heap_pop(grpc_timer_heap* heap);

bool grpc_timer_heap_is_empty(grpc_timer_heap* heap);

#endif
