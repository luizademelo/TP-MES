
// Copyright 2015 gRPC authors.

#include <grpc/support/port_platform.h>

#include "src/core/lib/iomgr/port.h"

#ifdef GRPC_POSIX_NO_SPECIAL_WAKEUP_FD

#include <stddef.h>

#include "src/core/lib/iomgr/wakeup_fd_posix.h"

static int check_availability_invalid(void) { return 0; }

const grpc_wakeup_fd_vtable grpc_specialized_wakeup_fd_vtable = {
    nullptr, nullptr, nullptr, nullptr, check_availability_invalid};

#endif
