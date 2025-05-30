
// Copyright 2017 gRPC authors.

#include <grpc/support/port_platform.h>

#include "src/core/lib/iomgr/port.h"

#if defined(GRPC_POSIX_SOCKET) && !defined(GRPC_HAVE_IFADDRS)

#include "src/core/lib/iomgr/tcp_server_utils_posix.h"

grpc_error_handle grpc_tcp_server_add_all_local_addrs(grpc_tcp_server* ,
                                                      unsigned ,
                                                      int ,
                                                      int* ) {
  return GRPC_ERROR_CREATE("no ifaddrs available");
}

bool grpc_tcp_server_have_ifaddrs(void) { return false; }

#endif
