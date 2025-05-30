
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_SURFACE_INIT_H
#define GRPC_SRC_CORE_LIB_SURFACE_INIT_H

#include <grpc/support/port_platform.h>

#include "absl/time/time.h"

void grpc_maybe_wait_for_async_shutdown(void);

bool grpc_wait_for_shutdown_with_timeout(absl::Duration timeout);

#endif
