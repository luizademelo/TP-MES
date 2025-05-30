
// Copyright 2015 gRPC authors.

#include <benchmark/benchmark.h>
#include <grpc/grpc.h>
#include <grpcpp/alarm.h>
#include <grpcpp/completion_queue.h>
#include <grpcpp/impl/grpc_library.h>

#include "test/core/test_util/test_config.h"
#include "test/cpp/microbenchmarks/helpers.h"
#include "test/cpp/util/test_config.h"

namespace grpc {
namespace testing {

static void BM_Alarm_Tag_Immediate(benchmark::State& state) {
  CompletionQueue cq;
  Alarm alarm;
  void* output_tag;
  bool ok;
  auto deadline = grpc_timeout_seconds_to_deadline(0);
  for (auto _ : state) {
    alarm.Set(&cq, deadline, nullptr);
    cq.Next(&output_tag, &ok);
  }
}
BENCHMARK(BM_Alarm_Tag_Immediate);

}
}

namespace benchmark {
void RunTheBenchmarksNamespaced() { RunSpecifiedBenchmarks(); }
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  LibraryInitializer libInit;
  ::benchmark::Initialize(&argc, argv);
  grpc::testing::InitTest(&argc, &argv, false);
  benchmark::RunTheBenchmarksNamespaced();
  return 0;
}
