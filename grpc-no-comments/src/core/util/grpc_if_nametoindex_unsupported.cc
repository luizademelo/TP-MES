
// Copyright 2016 gRPC authors.

#include <grpc/support/port_platform.h>

#include "src/core/lib/iomgr/port.h"

#if GRPC_IF_NAMETOINDEX == 0 || !defined(GRPC_POSIX_SOCKET_IF_NAMETOINDEX)

#include "absl/log/log.h"
#include "src/core/util/crash.h"
#include "src/core/util/grpc_if_nametoindex.h"

uint32_t grpc_if_nametoindex(char* name) {
  VLOG(2) << "Not attempting to convert interface name " << name
          << " to index for current platform.";
  return 0;
}

#endif
