// Copyright 2023 gRPC authors.

#include "src/core/util/per_cpu.h"

#include <grpc/support/cpu.h>
#include <grpc/support/port_platform.h>

#include "src/core/util/useful.h"

namespace grpc_core {

thread_local PerCpuShardingHelper::State PerCpuShardingHelper::state_;

size_t PerCpuOptions::Shards() {
  return ShardsForCpuCount(gpr_cpu_num_cores());
}

size_t PerCpuOptions::ShardsForCpuCount(size_t cpu_count) {
  return Clamp<size_t>(cpu_count / cpus_per_shard_, 1, max_shards_);
}

}
