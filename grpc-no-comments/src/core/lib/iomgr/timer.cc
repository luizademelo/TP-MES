
// Copyright 2018 gRPC authors.

#include "src/core/lib/iomgr/timer.h"

#include <grpc/support/port_platform.h>

#include "src/core/lib/iomgr/timer_manager.h"

grpc_timer_vtable* grpc_timer_impl;

void grpc_set_timer_impl(grpc_timer_vtable* vtable) {
  grpc_timer_impl = vtable;
}

void grpc_timer_init(grpc_timer* timer, grpc_core::Timestamp deadline,
                     grpc_closure* closure) {
  grpc_timer_impl->init(timer, deadline, closure);
}

void grpc_timer_cancel(grpc_timer* timer) { grpc_timer_impl->cancel(timer); }

grpc_timer_check_result grpc_timer_check(grpc_core::Timestamp* next) {
  return grpc_timer_impl->check(next);
}

void grpc_timer_list_init() { grpc_timer_impl->list_init(); }

void grpc_timer_list_shutdown() { grpc_timer_impl->list_shutdown(); }

void grpc_timer_consume_kick() { grpc_timer_impl->consume_kick(); }
