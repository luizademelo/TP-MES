// Copyright 2018 gRPC authors.

#include "src/core/lib/iomgr/internal_errqueue.h"

#include <grpc/support/port_platform.h>

#include "absl/log/log.h"
#include "src/core/lib/iomgr/port.h"

#ifdef GRPC_POSIX_SOCKET_TCP

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>

#include "src/core/util/strerror.h"

namespace grpc_core {

bool KernelSupportsErrqueue() {
  static const bool errqueue_supported = []() {
#ifdef GRPC_LINUX_ERRQUEUE

    struct utsname buffer;
    if (uname(&buffer) != 0) {
      LOG(ERROR) << "uname: " << StrError(errno);
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
