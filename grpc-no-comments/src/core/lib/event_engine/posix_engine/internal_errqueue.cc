// Copyright 2022 gRPC authors.

#include "src/core/lib/event_engine/posix_engine/internal_errqueue.h"

#include <grpc/support/port_platform.h>

#include "absl/log/log.h"
#include "src/core/lib/iomgr/port.h"

#ifdef GRPC_POSIX_SOCKET_TCP

#include <errno.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>

#include <cstddef>

#include "src/core/util/strerror.h"

namespace grpc_event_engine::experimental {

#ifdef GRPC_LINUX_ERRQUEUE
int GetSocketTcpInfo(struct tcp_info* info, int fd) {
  memset(info, 0, sizeof(*info));
  info->length = offsetof(tcp_info, length);
  return getsockopt(fd, IPPROTO_TCP, TCP_INFO, info, &(info->length));
}
#endif

bool KernelSupportsErrqueue() {
  static const bool errqueue_supported = []() {
#ifdef GRPC_LINUX_ERRQUEUE

    struct utsname buffer;
    if (uname(&buffer) != 0) {
      LOG(ERROR) << "uname: " << grpc_core::StrError(errno);
      return false;
    }
    char* release = buffer.release;
    if (release == nullptr) {
      return false;
    }

    if (strtol(release, nullptr, 10) >= 4) {
      return true;
    } else {
      VLOG(2) << "ERRQUEUE support not enabled";
    }
#endif
    return false;
  }();
  return errqueue_supported;
}

}

#endif
