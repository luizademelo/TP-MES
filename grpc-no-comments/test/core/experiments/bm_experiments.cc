// Copyright 2017 gRPC authors.

#include <benchmark/benchmark.h>

#include "src/core/lib/experiments/experiments.h"

static void BM_IsExperimentEnabled(benchmark::State& state) {
  for (auto _ : state) {
    benchmark::DoNotOptimize(grpc_core::IsMonitoringExperimentEnabled());
  }
}
BENCHMARK(BM_IsExperimentEnabled);

namespace benchmark {
void RunTheBenchmarksNamespaced() { RunSpecifiedBenchmarks(); }
}

int main(int argc, char** argv) {
  ::benchmark::Initialize(&argc, argv);
  benchmark::RunTheBenchmarksNamespaced();
  return 0;
}
