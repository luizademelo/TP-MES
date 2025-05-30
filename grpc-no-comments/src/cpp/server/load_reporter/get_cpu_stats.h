
// Copyright 2018 gRPC authors.

#ifndef GRPC_SRC_CPP_SERVER_LOAD_REPORTER_GET_CPU_STATS_H
#define GRPC_SRC_CPP_SERVER_LOAD_REPORTER_GET_CPU_STATS_H

#include <grpc/support/port_platform.h>
#include <stdint.h>

#include <utility>

namespace grpc {
namespace load_reporter {

std::pair<uint64_t, uint64_t> GetCpuStatsImpl();

}
}

#endif
