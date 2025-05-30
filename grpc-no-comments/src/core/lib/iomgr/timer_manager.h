
// Copyright 2017 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_IOMGR_TIMER_MANAGER_H
#define GRPC_SRC_CORE_LIB_IOMGR_TIMER_MANAGER_H

#include <grpc/support/port_platform.h>
#include <stdbool.h>

void grpc_timer_manager_init(void);
void grpc_timer_manager_shutdown(void);

void grpc_timer_manager_set_threading(bool enabled);

void grpc_timer_manager_set_start_threaded(bool enabled);

void grpc_timer_manager_tick(void);

uint64_t grpc_timer_manager_get_wakeups_testonly(void);

#endif
