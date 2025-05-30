
// Copyright 2018 gRPC authors.

#include <grpc/support/port_platform.h>

#if !defined(GPR_LINUX) && !defined(GPR_WINDOWS) && !defined(GPR_APPLE)

#include "absl/log/log.h"
#include "src/core/util/crash.h"
#include "src/cpp/server/load_reporter/get_cpu_stats.h"

namespace grpc {
namespace load_reporter {

std::pair<uint64_t, uint64_t> GetCpuStatsImpl() {
  uint64_t busy = 0, total = 0;
  LOG(ERROR)
      << "Platforms other than Linux, Windows, and MacOS are not supported.";
  return std::pair(busy, total);
}

}
}

#endif
