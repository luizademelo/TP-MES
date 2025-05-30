
// Copyright 2017 gRPC authors.

#include <grpc/support/port_platform.h>

#include "src/core/lib/iomgr/port.h"
#include "src/core/util/gethostname.h"

#ifdef GRPC_POSIX_HOST_NAME_MAX

#include <grpc/support/alloc.h>
#include <limits.h>
#include <unistd.h>

char* grpc_gethostname() {
  char* hostname = static_cast<char*>(gpr_malloc(HOST_NAME_MAX));
  if (gethostname(hostname, HOST_NAME_MAX) != 0) {
    gpr_free(hostname);
    return nullptr;
  }
  return hostname;
}

#endif
