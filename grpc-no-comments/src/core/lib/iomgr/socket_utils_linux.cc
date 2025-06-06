
// Copyright 2015 gRPC authors.

#include <grpc/support/port_platform.h>

#include "src/core/lib/iomgr/port.h"

#ifdef GRPC_LINUX_SOCKETUTILS

#include <sys/socket.h>
#include <sys/types.h>

#include "src/core/lib/iomgr/sockaddr.h"
#include "src/core/lib/iomgr/socket_utils_posix.h"
#include "src/core/util/crash.h"

int grpc_accept4(int sockfd, grpc_resolved_address* resolved_addr, int nonblock,
                 int cloexec) {
  int flags = 0;
  flags |= nonblock ? SOCK_NONBLOCK : 0;
  flags |= cloexec ? SOCK_CLOEXEC : 0;
  return accept4(sockfd, reinterpret_cast<grpc_sockaddr*>(resolved_addr->addr),
                 &resolved_addr->len, flags);
}

#endif
