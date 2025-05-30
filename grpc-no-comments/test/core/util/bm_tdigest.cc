// Copyright 2024 gRPC authors.

#include <benchmark/benchmark.h>

#include <random>

#include "src/core/util/tdigest.h"

namespace grpc_core {

static void BM_AddWithCompression(benchmark::State& state) {

  const size_t kNumValues = sysconf(_SC_PAGE_SIZE) / sizeof(double);
  std::vector<double> vals;
  vals.reserve(kNumValues);
  std::mt19937 gen(1234);
  std::exponential_distribution<double> exp_dist;

  for (int idx = 0; idx < kNumValues; idx++) {
    vals.push_back(exp_dist(gen));
  }

  TDigest tdigest(state.range(0));

  while (state.KeepRunningBatch(kNumValues)) {
    for (double val : vals) {
      tdigest.Add(val);
    }
  }

  state.SetItemsProcessed(state.iterations());
}
BENCHMARK(BM_AddWithCompression)->Arg(1)->Arg(10)->Arg(100)->Arg(1000);

}

namespace benchmark {
void RunTheBenchmarksNamespaced() { RunSpecifiedBenchmarks(); }
}

int main(int argc, char** argv) {
  ::benchmark::Initialize(&argc, argv);
  benchmark::RunTheBenchmarksNamespaced();
  return 0;
}
