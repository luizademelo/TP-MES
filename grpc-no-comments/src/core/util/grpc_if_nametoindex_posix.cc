
// Copyright 2016 gRPC authors.

#include <grpc/support/port_platform.h>

#include "src/core/lib/iomgr/port.h"

#if GRPC_IF_NAMETOINDEX == 1 && defined(GRPC_POSIX_SOCKET_IF_NAMETOINDEX)

#include <errno.h>
#include <net/if.h>

#include "absl/log/log.h"
#include "src/core/util/crash.h"
#include "src/core/util/grpc_if_nametoindex.h"

uint32_t grpc_if_nametoindex(char* name) {
  uint32_t out = if_nametoindex(name);
  if (out == 0) {
    VLOG(2) << "if_nametoindex failed for name " << name << ". errno " << errno;
  }
  return out;
}

#endif
