
// Copyright 2017 gRPC authors.

#include <grpc/support/port_platform.h>

#include "src/core/lib/iomgr/port.h"
#include "src/core/util/gethostname.h"

#ifdef GRPC_POSIX_SYSCONF

#include <grpc/support/alloc.h>
#include <unistd.h>

char* grpc_gethostname() {
  size_t host_name_max = (size_t)sysconf(_SC_HOST_NAME_MAX);
  char* hostname = (char*)gpr_malloc(host_name_max);
  if (gethostname(hostname, host_name_max) != 0) {
    gpr_free(hostname);
    return nullptr;
  }
  return hostname;
}

#endif
