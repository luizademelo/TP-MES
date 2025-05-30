// Copyright 2022 gRPC authors.

#ifndef GRPC_TEST_CORE_MEMORY_USAGE_MEMSTATS_H
#define GRPC_TEST_CORE_MEMORY_USAGE_MEMSTATS_H

#include <optional>

long GetMemUsage(std::optional<int> pid = std::nullopt);

struct MemStats {
  long rss;
  static MemStats Snapshot() { return MemStats{GetMemUsage()}; }
};

#endif
