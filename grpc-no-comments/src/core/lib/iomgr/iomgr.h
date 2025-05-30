
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_IOMGR_IOMGR_H
#define GRPC_SRC_CORE_LIB_IOMGR_IOMGR_H

#include <grpc/support/port_platform.h>
#include <stdlib.h>

#include "src/core/lib/iomgr/closure.h"
#include "src/core/lib/iomgr/port.h"

void grpc_iomgr_init();

void grpc_iomgr_start();

void grpc_iomgr_shutdown();

void grpc_iomgr_shutdown_background_closure();

bool grpc_iomgr_run_in_background();

bool grpc_iomgr_is_any_background_poller_thread();

bool grpc_iomgr_add_closure_to_background_poller(grpc_closure* closure,
                                                 grpc_error_handle error);

size_t grpc_iomgr_count_objects_for_testing();

#endif
