
// Copyright 2015-2016 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_IOMGR_EV_POLL_POSIX_H
#define GRPC_SRC_CORE_LIB_IOMGR_EV_POLL_POSIX_H

#include <grpc/support/port_platform.h>

#include "src/core/lib/iomgr/ev_posix.h"

extern const grpc_event_engine_vtable grpc_ev_poll_posix;
extern const grpc_event_engine_vtable grpc_ev_none_posix;

#endif
