
// Copyright 2018 gRPC authors.

#include <grpc/support/port_platform.h>

#include <utility>

#ifdef GPR_LINUX

#include <inttypes.h>

#include <cstdio>

#include "src/cpp/server/load_reporter/get_cpu_stats.h"

namespace grpc {
namespace load_reporter {

std::pair<uint64_t, uint64_t> GetCpuStatsImpl() {
  uint64_t busy = 0, total = 0;
  FILE* fp;
  fp = fopen("/proc/stat", "r");
  uint64_t user, nice, system, idle;
  if (fscanf(fp, "cpu %" PRIu64 " %" PRIu64 " %" PRIu64 " %" PRIu64, &user,
             &nice, &system, &idle) != 4) {

    user = nice = system = idle = 0;
  }
  fclose(fp);
  busy = user + nice + system;
  total = busy + idle;
  return std::pair(busy, total);
}

}
}

#endif
