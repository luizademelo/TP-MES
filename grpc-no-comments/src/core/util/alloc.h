
// Copyright 2018 gRPC authors.

#ifndef GRPC_SRC_CORE_UTIL_ALLOC_H
#define GRPC_SRC_CORE_UTIL_ALLOC_H

#include <grpc/support/port_platform.h>

#define GPR_ROUND_UP_TO_ALIGNMENT_SIZE(x) \
  (((x) + GPR_MAX_ALIGNMENT - 1u) & ~(GPR_MAX_ALIGNMENT - 1u))

#endif
