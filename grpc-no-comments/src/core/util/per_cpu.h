// Copyright 2022 gRPC authors.

#ifndef GRPC_SRC_CORE_UTIL_PER_CPU_H
#define GRPC_SRC_CORE_UTIL_PER_CPU_H

#include <grpc/support/cpu.h>
#include <grpc/support/port_platform.h>
#include <stdint.h>

#include <algorithm>
#include <cstddef>
#include <limits>
#include <memory>

namespace grpc_core {

class PerCpuOptions {
 public:

  PerCpuOptions SetCpusPerShard(size_t cpus_per_shard) {
    cpus_per_shard_ = std::max<size_t>(1, cpus_per_shard);
    return *this;
  }

  PerCpuOptions SetMaxShards(size_t max_shards) {
    max_shards_ = std::max<size_t>(1, max_shards);
    return *this;
  }

  size_t cpus_per_shard() const { return cpus_per_shard_; }
  size_t max_shards() const { return max_shards_; }

  size_t Shards();
  size_t ShardsForCpuCount(size_t cpu_count);

 private:
  size_t cpus_per_shard_ = 1;
  size_t max_shards_ = std::numeric_limits<size_t>::max();
};

class PerCpuShardingHelper {
 public:
  size_t GetShardingBits() {

    if (GPR_UNLIKELY(state_.uses_until_refresh == 0)) state_ = State();
    --state_.uses_until_refresh;
    return state_.last_seen_cpu;
  }

 private:
  struct State {
    uint16_t last_seen_cpu = gpr_cpu_current_cpu();
    uint16_t uses_until_refresh = 65535;
  };
  static thread_local State state_;
};

template <typename T>
class PerCpu {
 public:

  explicit PerCpu(PerCpuOptions options) : shards_(options.Shards()) {}

  T& this_cpu() { return data_[sharding_helper_.GetShardingBits() % shards_]; }

  T* begin() { return data_.get(); }
  T* end() { return data_.get() + shards_; }
  const T* begin() const { return data_.get(); }
  const T* end() const { return data_.get() + shards_; }

 private:
  PerCpuShardingHelper sharding_helper_;
  const size_t shards_;
  std::unique_ptr<T[]> data_{new T[shards_]};
};

}

#endif
