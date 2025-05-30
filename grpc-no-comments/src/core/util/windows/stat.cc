
// Copyright 2020 gRPC authors.

#include <grpc/support/port_platform.h>

#ifdef GPR_WINDOWS_STAT

#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "src/core/util/crash.h"
#include "src/core/util/stat.h"
#include "src/core/util/strerror.h"

namespace grpc_core {

absl::Status GetFileModificationTime(const char* filename, time_t* timestamp) {
  CHECK_NE(filename, nullptr);
  CHECK_NE(timestamp, nullptr);
  struct _stat buf;
  if (_stat(filename, &buf) != 0) {
    std::string error_msg = StrError(errno);
    LOG(ERROR) << "_stat failed for filename " << filename << " with error "
               << error_msg;
    return absl::Status(absl::StatusCode::kInternal, error_msg);
  }

  *timestamp = buf.st_mtime;
  return absl::OkStatus();
}

}

#endif
