
// Copyright 2015 gRPC authors.

#include <benchmark/benchmark.h>

#include "test/core/test_util/test_config.h"

static void BM_NoOp(benchmark::State& state) {
  for (auto _ : state) {
  }
}
BENCHMARK(BM_NoOp);

namespace benchmark {
void RunTheBenchmarksNamespaced() { RunSpecifiedBenchmarks(); }
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  benchmark::Initialize(&argc, argv);
  benchmark::RunTheBenchmarksNamespaced();
  return 0;
}
