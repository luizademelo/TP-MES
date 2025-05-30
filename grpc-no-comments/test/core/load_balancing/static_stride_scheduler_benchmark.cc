
// Copyright 2022 gRPC authors.

#include <benchmark/benchmark.h>

#include <algorithm>
#include <atomic>
#include <cstdint>
#include <optional>
#include <vector>

#include "absl/algorithm/container.h"
#include "absl/log/check.h"
#include "absl/random/random.h"
#include "absl/types/span.h"
#include "src/core/load_balancing/weighted_round_robin/static_stride_scheduler.h"
#include "src/core/util/no_destruct.h"

namespace grpc_core {
namespace {

const int kNumWeightsLow = 10;
const int kNumWeightsHigh = 10000;
const int kRangeMultiplier = 10;

const std::vector<float>& Weights() {
  static const NoDestruct<std::vector<float>> kWeights([] {
    static NoDestruct<absl::BitGen> bit_gen;
    std::vector<float> weights;
    weights.reserve(kNumWeightsHigh);
    for (int i = 0; i < 40; ++i) {
      for (int j = 0; j < kNumWeightsHigh / 40; ++j) {
        weights.push_back(0.6 + (0.01 * i));
      }
    }
    absl::c_shuffle(weights, *bit_gen);
    return weights;
  }());
  return *kWeights;
}

void BM_StaticStrideSchedulerPickNonAtomic(benchmark::State& state) {
  uint32_t sequence = 0;
  const std::optional<StaticStrideScheduler> scheduler =
      StaticStrideScheduler::Make(
          absl::MakeSpan(Weights()).subspan(0, state.range(0)),
          [&] { return sequence++; });
  CHECK(scheduler.has_value());
  for (auto s : state) {
    benchmark::DoNotOptimize(scheduler->Pick());
  }
}
BENCHMARK(BM_StaticStrideSchedulerPickNonAtomic)
    ->RangeMultiplier(kRangeMultiplier)
    ->Range(kNumWeightsLow, kNumWeightsHigh);

void BM_StaticStrideSchedulerPickAtomic(benchmark::State& state) {
  std::atomic<uint32_t> sequence{0};
  const std::optional<StaticStrideScheduler> scheduler =
      StaticStrideScheduler::Make(
          absl::MakeSpan(Weights()).subspan(0, state.range(0)),
          [&] { return sequence.fetch_add(1, std::memory_order_relaxed); });
  CHECK(scheduler.has_value());
  for (auto s : state) {
    benchmark::DoNotOptimize(scheduler->Pick());
  }
}
BENCHMARK(BM_StaticStrideSchedulerPickAtomic)
    ->RangeMultiplier(kRangeMultiplier)
    ->Range(kNumWeightsLow, kNumWeightsHigh);

void BM_StaticStrideSchedulerMake(benchmark::State& state) {
  uint32_t sequence = 0;
  for (auto s : state) {
    const std::optional<StaticStrideScheduler> scheduler =
        StaticStrideScheduler::Make(
            absl::MakeSpan(Weights()).subspan(0, state.range(0)),
            [&] { return sequence++; });
    CHECK(scheduler.has_value());
  }
}
BENCHMARK(BM_StaticStrideSchedulerMake)
    ->RangeMultiplier(kRangeMultiplier)
    ->Range(kNumWeightsLow, kNumWeightsHigh);

}
}

namespace benchmark {
void RunTheBenchmarksNamespaced() { RunSpecifiedBenchmarks(); }
}

int main(int argc, char** argv) {
  benchmark::Initialize(&argc, argv);
  benchmark::RunTheBenchmarksNamespaced();
  return 0;
}
