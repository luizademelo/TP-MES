Here's the commented version of the code snippet:

```c++
// Copyright 2023 gRPC authors.

// Include necessary headers for CPU utilities and platform-specific support
#include "src/core/util/per_cpu.h"

#include <grpc/support/cpu.h>        // For CPU core count functionality
#include <grpc/support/port_platform.h>  // For platform-specific definitions

#include "src/core/util/useful.h"    // For utility functions like Clamp

namespace grpc_core {

// Thread-local storage for per-CPU sharding state
// Each thread maintains its own instance of State
thread_local PerCpuShardingHelper::State PerCpuShardingHelper::state_;

// Returns the number of shards based on the current CPU count
// Uses the system's actual CPU count to determine appropriate sharding
size_t PerCpuOptions::Shards() {
  return ShardsForCpuCount(gpr_cpu_num_cores());
}

// Calculates the optimal number of shards for a given CPU count
// Ensures the result is within configured bounds (1 <= shards <= max_shards_)
// The calculation divides CPU count by configured CPUs per shard (cpus_per_shard_)
size_t PerCpuOptions::ShardsForCpuCount(size_t cpu_count) {
  return Clamp<size_t>(cpu_count / cpus_per_shard_, 1, max_shards_);
}

}  // namespace grpc_core
```

The comments explain:
1. The purpose of each include directive
2. The thread-local storage mechanism for per-CPU state
3. The functionality of both Shards() and ShardsForCpuCount() methods
4. The bounds checking and calculation logic in ShardsForCpuCount()
5. The namespace closure

The comments are designed to help future developers understand:
- The overall purpose of this CPU sharding utility
- How thread-safety is maintained
- The configuration constraints (minimum 1 shard, maximum max_shards_)
- The relationship between CPU count and shard count