
// Copyright 2017 gRPC authors.

#include <benchmark/benchmark.h>

#include "absl/random/random.h"
#include "src/core/util/sync.h"

static void BM_OneRngFromFreshBitSet(benchmark::State& state) {
  for (auto _ : state) {
    benchmark::DoNotOptimize(absl::Uniform(absl::BitGen(), 0.0, 1.0));
  }
}
BENCHMARK(BM_OneRngFromFreshBitSet);

static void BM_OneRngFromReusedBitSet(benchmark::State& state) {
  absl::BitGen bitgen;
  for (auto _ : state) {
    benchmark::DoNotOptimize(absl::Uniform(bitgen, 0.0, 1.0));
  }
}
BENCHMARK(BM_OneRngFromReusedBitSet);

static void BM_OneRngFromReusedBitSetWithMutex(benchmark::State& state) {
  struct Data {
    grpc_core::Mutex mu;
    absl::BitGen bitgen ABSL_GUARDED_BY(mu);
  };
  Data data;
  for (auto _ : state) {
    grpc_core::MutexLock lock(&data.mu);
    benchmark::DoNotOptimize(absl::Uniform(data.bitgen, 0.0, 1.0));
  }
}
BENCHMARK(BM_OneRngFromReusedBitSetWithMutex);

namespace benchmark {
void RunTheBenchmarksNamespaced() { RunSpecifiedBenchmarks(); }
}

int main(int argc, char** argv) {
  ::benchmark::Initialize(&argc, argv);
  benchmark::RunTheBenchmarksNamespaced();
  return 0;
}
