
// Copyright 2016 gRPC authors.

#include "test/core/test_util/build.h"
#include "test/core/test_util/test_config.h"
#include "test/cpp/microbenchmarks/fullstack_streaming_ping_pong.h"
#include "test/cpp/util/test_config.h"

namespace grpc {
namespace testing {

static const int kMaxMessageSize = [] {
  if (BuiltUnderMsan() || BuiltUnderTsan() || BuiltUnderUbsan()) {

    return 8 * 1024 * 1024;
  }
  return 128 * 1024 * 1024;
}();

static void StreamingPingPongArgs(benchmark::internal::Benchmark* b) {
  int msg_size = 0;

  b->Args({0, 0});

  for (msg_size = 0; msg_size <= kMaxMessageSize;
       msg_size == 0 ? msg_size++ : msg_size *= 8) {
    b->Args({msg_size, 1});
    b->Args({msg_size, 2});
  }
}

BENCHMARK_TEMPLATE(BM_StreamingPingPong, TCP, NoOpMutator, NoOpMutator)
    ->Apply(StreamingPingPongArgs);
BENCHMARK_TEMPLATE(BM_StreamingPingPong, InProcess, NoOpMutator, NoOpMutator)
    ->Apply(StreamingPingPongArgs);

BENCHMARK_TEMPLATE(BM_StreamingPingPongMsgs, TCP, NoOpMutator, NoOpMutator)
    ->Range(0, kMaxMessageSize);
BENCHMARK_TEMPLATE(BM_StreamingPingPongMsgs, InProcess, NoOpMutator,
                   NoOpMutator)
    ->Range(0, kMaxMessageSize);

BENCHMARK_TEMPLATE(BM_StreamingPingPong, MinTCP, NoOpMutator, NoOpMutator)
    ->Apply(StreamingPingPongArgs);
BENCHMARK_TEMPLATE(BM_StreamingPingPong, MinInProcess, NoOpMutator, NoOpMutator)
    ->Apply(StreamingPingPongArgs);

BENCHMARK_TEMPLATE(BM_StreamingPingPongMsgs, MinTCP, NoOpMutator, NoOpMutator)
    ->Range(0, kMaxMessageSize);
BENCHMARK_TEMPLATE(BM_StreamingPingPongMsgs, MinInProcess, NoOpMutator,
                   NoOpMutator)
    ->Range(0, kMaxMessageSize);

static void StreamingPingPongWithCoalescingApiArgs(
    benchmark::internal::Benchmark* b) {
  int msg_size = 0;

  b->Args(
      {0, 0, 0});
  b->Args(
      {0, 0, 1});

  for (msg_size = 0; msg_size <= kMaxMessageSize;
       msg_size == 0 ? msg_size++ : msg_size *= 8) {
    b->Args({msg_size, 1, 0});
    b->Args({msg_size, 2, 0});
    b->Args({msg_size, 1, 1});
    b->Args({msg_size, 2, 1});
  }
}

BENCHMARK_TEMPLATE(BM_StreamingPingPongWithCoalescingApi, InProcess,
                   NoOpMutator, NoOpMutator)
    ->Apply(StreamingPingPongWithCoalescingApiArgs);
BENCHMARK_TEMPLATE(BM_StreamingPingPongWithCoalescingApi, MinInProcess,
                   NoOpMutator, NoOpMutator)
    ->Apply(StreamingPingPongWithCoalescingApiArgs);

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
