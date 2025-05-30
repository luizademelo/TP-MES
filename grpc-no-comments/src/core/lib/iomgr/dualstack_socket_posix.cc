
// Copyright 2020 gRPC authors.

#include <grpc/support/port_platform.h>

#include "src/core/lib/iomgr/port.h"

#ifdef GRPC_POSIX_SOCKET_UTILS_COMMON

#include <netinet/in.h>

#include "src/core/lib/iomgr/socket_utils_posix.h"

#ifndef GRPC_SET_SOCKET_DUALSTACK_CUSTOM

int grpc_forbid_dualstack_sockets_for_testing = 0;

int grpc_set_socket_dualstack(int fd) {
  if (!grpc_forbid_dualstack_sockets_for_testing) {
    const int off = 0;
    return 0 == setsockopt(fd, IPPROTO_IPV6, IPV6_V6ONLY, &off, sizeof(off));
  } else {

    const int on = 1;
    setsockopt(fd, IPPROTO_IPV6, IPV6_V6ONLY, &on, sizeof(on));
    return 0;
  }
}
#endif
#endif
