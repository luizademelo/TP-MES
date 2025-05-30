
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_IOMGR_TIMER_H
#define GRPC_SRC_CORE_LIB_IOMGR_TIMER_H

#include <grpc/event_engine/event_engine.h>
#include <grpc/support/port_platform.h>
#include <grpc/support/time.h>

#include <cstdint>

#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/iomgr/iomgr.h"
#include "src/core/lib/iomgr/port.h"

typedef struct grpc_timer {
  int64_t deadline;

  uint32_t heap_index;
  bool pending;
  struct grpc_timer* next;
  struct grpc_timer* prev;
  grpc_closure* closure;
#ifndef NDEBUG
  struct grpc_timer* hash_table_next;
#endif

  union {
    void* custom_timer;
    grpc_event_engine::experimental::EventEngine::TaskHandle ee_task_handle;
  };
} grpc_timer;

static_assert(std::is_trivial<grpc_timer>::value,
              "grpc_timer is expected to be a trivial type");

typedef enum {
  GRPC_TIMERS_NOT_CHECKED,
  GRPC_TIMERS_CHECKED_AND_EMPTY,
  GRPC_TIMERS_FIRED,
} grpc_timer_check_result;

typedef struct grpc_timer_vtable {
  void (*init)(grpc_timer* timer, grpc_core::Timestamp, grpc_closure* closure);
  void (*cancel)(grpc_timer* timer);

  grpc_timer_check_result (*check)(grpc_core::Timestamp* next);
  void (*list_init)();
  void (*list_shutdown)(void);
  void (*consume_kick)(void);
} grpc_timer_vtable;

void grpc_timer_init(grpc_timer* timer, grpc_core::Timestamp deadline,
                     grpc_closure* closure);

void grpc_timer_init_unset(grpc_timer* timer);

void grpc_timer_cancel(grpc_timer* timer);

grpc_timer_check_result grpc_timer_check(grpc_core::Timestamp* next);
void grpc_timer_list_init();
void grpc_timer_list_shutdown();

void grpc_timer_consume_kick(void);

void grpc_kick_poller(void);

void grpc_set_timer_impl(grpc_timer_vtable* vtable);

#endif
