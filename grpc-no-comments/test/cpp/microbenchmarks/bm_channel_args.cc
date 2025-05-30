// Copyright 2017 gRPC authors.

#include <benchmark/benchmark.h>
#include <grpcpp/support/channel_arguments.h>

#include <random>

#include "absl/container/btree_map.h"
#include "src/core/lib/channel/channel_args.h"

const char kKey[] = "a very long key";
const char kValue[] = "a very long value";

void BM_ChannelArgs(benchmark::State& state) {
  grpc_core::ChannelArgs arg1, arg2;
  arg1 = arg1.Set(kKey, kValue);
  arg2 = arg2.Set(kKey, kValue);
  for (auto s : state) {
    benchmark::DoNotOptimize(arg1 < arg2);
  }
}
BENCHMARK(BM_ChannelArgs);

void BM_grpc_channel_args(benchmark::State& state) {
  grpc_channel_args arg1, arg2;
  grpc::ChannelArguments xargs;
  xargs.SetString(kKey, kValue);
  xargs.SetChannelArgs(&arg1);
  xargs.SetChannelArgs(&arg2);
  for (auto s : state) {
    benchmark::DoNotOptimize(grpc_channel_args_compare(&arg1, &arg2));
  }
}
BENCHMARK(BM_grpc_channel_args);

void BM_ChannelArgsAsKeyIntoMap(benchmark::State& state) {
  std::map<grpc_core::ChannelArgs, int> m;
  std::vector<grpc_core::ChannelArgs> v;
  for (int i = 0; i < 10000; i++) {
    const auto& a = grpc_core::ChannelArgs().Set(kKey, i);
    m[a] = i;
    v.push_back(a);
  }
  std::shuffle(v.begin(), v.end(), std::mt19937(std::random_device()()));
  size_t n = 0;
  for (auto s : state) {
    benchmark::DoNotOptimize(m.find(v[n++ % v.size()]));
  }
}
BENCHMARK(BM_ChannelArgsAsKeyIntoMap);

void BM_ChannelArgsAsKeyIntoBTree(benchmark::State& state) {
  absl::btree_map<grpc_core::ChannelArgs, int> m;
  std::vector<grpc_core::ChannelArgs> v;
  for (int i = 0; i < 10000; i++) {
    const auto& a = grpc_core::ChannelArgs().Set(kKey, i);
    m[a] = i;
    v.push_back(a);
  }
  std::shuffle(v.begin(), v.end(), std::mt19937(std::random_device()()));
  size_t n = 0;
  for (auto s : state) {
    benchmark::DoNotOptimize(m.find(v[n++ % v.size()]));
  }
}
BENCHMARK(BM_ChannelArgsAsKeyIntoBTree);

namespace benchmark {
void RunTheBenchmarksNamespaced() { RunSpecifiedBenchmarks(); }
}

int main(int argc, char** argv) {
  ::benchmark::Initialize(&argc, argv);
  benchmark::RunTheBenchmarksNamespaced();
  return 0;
}
