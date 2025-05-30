// Copyright 2022 gRPC authors.

#include "src/core/util/strerror.h"

#include <grpc/support/port_platform.h>
#include <string.h>

#include "absl/strings/str_format.h"

namespace grpc_core {

#ifdef GPR_WINDOWS
std::string StrError(int err) { return strerror(err); }
#else
std::string StrError(int err) {
  struct Finish {
    static std::string Run(char* buf, int err, int r) {
      if (r == 0) return buf;
      return absl::StrFormat("strerror_r(%d) failed: %d", err, r);
    }
    static std::string Run(char*, int, const char* r) { return r; }
  };
  char buf[256];
  return Finish::Run(buf, err, strerror_r(err, buf, sizeof(buf)));
}
#endif

}
