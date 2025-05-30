
// Copyright 2022 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_IOMGR_SYSTEMD_UTILS_H
#define GRPC_SRC_CORE_LIB_IOMGR_SYSTEMD_UTILS_H

#include <grpc/support/port_platform.h>

#include "src/core/lib/iomgr/tcp_server_utils_posix.h"

void set_matching_sd_fds(grpc_tcp_server* s, const grpc_resolved_address* addr,
                         int requested_port);

#endif
