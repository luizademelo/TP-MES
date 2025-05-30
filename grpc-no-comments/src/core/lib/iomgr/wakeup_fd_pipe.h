
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_IOMGR_WAKEUP_FD_PIPE_H
#define GRPC_SRC_CORE_LIB_IOMGR_WAKEUP_FD_PIPE_H

#include <grpc/support/port_platform.h>

#include "src/core/lib/iomgr/wakeup_fd_posix.h"

extern const grpc_wakeup_fd_vtable grpc_pipe_wakeup_fd_vtable;

#endif
