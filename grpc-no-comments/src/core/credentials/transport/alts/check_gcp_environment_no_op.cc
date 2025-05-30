
// Copyright 2018 gRPC authors.

#include <grpc/support/port_platform.h>

#if !defined(GPR_LINUX) && !defined(GPR_WINDOWS)

#include "absl/log/log.h"
#include "src/core/credentials/transport/alts/check_gcp_environment.h"
#include "src/core/util/crash.h"

bool grpc_alts_is_running_on_gcp() {
  VLOG(2) << "ALTS: Platforms other than Linux and Windows are not supported";
  return false;
}

#endif
