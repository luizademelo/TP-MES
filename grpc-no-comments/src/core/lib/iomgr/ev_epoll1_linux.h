
// Copyright 2017 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_IOMGR_EV_EPOLL1_LINUX_H
#define GRPC_SRC_CORE_LIB_IOMGR_EV_EPOLL1_LINUX_H

#include <grpc/support/port_platform.h>

#include "src/core/lib/iomgr/ev_posix.h"
#include "src/core/lib/iomgr/port.h"

extern const grpc_event_engine_vtable grpc_ev_epoll1_posix;

#endif
