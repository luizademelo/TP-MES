
// Copyright 2018 gRPC authors.

#include <grpc/support/port_platform.h>

#ifdef GPR_WINDOWS

#include <windows.h>

#include <cstdint>

#include "src/cpp/server/load_reporter/get_cpu_stats.h"

namespace grpc {
namespace load_reporter {

namespace {

uint64_t FiletimeToInt(const FILETIME& ft) {
  ULARGE_INTEGER i;
  i.LowPart = ft.dwLowDateTime;
  i.HighPart = ft.dwHighDateTime;
  return i.QuadPart;
}

}

std::pair<uint64_t, uint64_t> GetCpuStatsImpl() {
  uint64_t busy = 0, total = 0;
  FILETIME idle, kernel, user;
  if (GetSystemTimes(&idle, &kernel, &user) != 0) {
    total = FiletimeToInt(kernel) + FiletimeToInt(user);
    busy = total - FiletimeToInt(idle);
  }
  return std::pair(busy, total);
}

}
}

#endif
