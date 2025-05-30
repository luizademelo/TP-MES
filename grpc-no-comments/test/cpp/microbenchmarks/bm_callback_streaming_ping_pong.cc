
// Copyright 2019 gRPC authors.

#include "test/core/test_util/build.h"
#include "test/core/test_util/test_config.h"
#include "test/cpp/microbenchmarks/callback_streaming_ping_pong.h"
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
    b->MeasureProcessCPUTime()->UseRealTime();
  }
}

BENCHMARK_TEMPLATE(BM_CallbackBidiStreaming, InProcess, NoOpMutator,
                   NoOpMutator)
    ->Apply(StreamingPingPongArgs);
BENCHMARK_TEMPLATE(BM_CallbackBidiStreaming, MinInProcess, NoOpMutator,
                   NoOpMutator)
    ->Apply(StreamingPingPongArgs);

BENCHMARK_TEMPLATE(BM_CallbackBidiStreaming, InProcess,
                   Client_AddMetadata<RandomBinaryMetadata<10>, 1>, NoOpMutator)
    ->Args({0, 1});
BENCHMARK_TEMPLATE(BM_CallbackBidiStreaming, InProcess,
                   Client_AddMetadata<RandomBinaryMetadata<31>, 1>, NoOpMutator)
    ->Args({0, 1});
BENCHMARK_TEMPLATE(BM_CallbackBidiStreaming, InProcess,
                   Client_AddMetadata<RandomBinaryMetadata<100>, 1>,
                   NoOpMutator)
    ->Args({0, 1});
BENCHMARK_TEMPLATE(BM_CallbackBidiStreaming, InProcess,
                   Client_AddMetadata<RandomBinaryMetadata<10>, 2>, NoOpMutator)
    ->Args({0, 1});
BENCHMARK_TEMPLATE(BM_CallbackBidiStreaming, InProcess,
                   Client_AddMetadata<RandomBinaryMetadata<31>, 2>, NoOpMutator)
    ->Args({0, 1});
BENCHMARK_TEMPLATE(BM_CallbackBidiStreaming, InProcess,
                   Client_AddMetadata<RandomBinaryMetadata<100>, 2>,
                   NoOpMutator)
    ->Args({0, 1});
BENCHMARK_TEMPLATE(BM_CallbackBidiStreaming, InProcess,
                   Client_AddMetadata<RandomAsciiMetadata<10>, 1>, NoOpMutator)
    ->Args({0, 1});
BENCHMARK_TEMPLATE(BM_CallbackBidiStreaming, InProcess,
                   Client_AddMetadata<RandomAsciiMetadata<31>, 1>, NoOpMutator)
    ->Args({0, 1});
BENCHMARK_TEMPLATE(BM_CallbackBidiStreaming, InProcess,
                   Client_AddMetadata<RandomAsciiMetadata<100>, 1>, NoOpMutator)
    ->Args({0, 1});

BENCHMARK_TEMPLATE(BM_CallbackBidiStreaming, InProcess, NoOpMutator,
                   Server_AddInitialMetadata<RandomBinaryMetadata<10>, 1>)
    ->Args({0, 1});
BENCHMARK_TEMPLATE(BM_CallbackBidiStreaming, InProcess, NoOpMutator,
                   Server_AddInitialMetadata<RandomBinaryMetadata<31>, 1>)
    ->Args({0, 1});
BENCHMARK_TEMPLATE(BM_CallbackBidiStreaming, InProcess, NoOpMutator,
                   Server_AddInitialMetadata<RandomBinaryMetadata<100>, 1>)
    ->Args({0, 1});
BENCHMARK_TEMPLATE(BM_CallbackBidiStreaming, InProcess, NoOpMutator,
                   Server_AddInitialMetadata<RandomAsciiMetadata<10>, 1>)
    ->Args({0, 1});
BENCHMARK_TEMPLATE(BM_CallbackBidiStreaming, InProcess, NoOpMutator,
                   Server_AddInitialMetadata<RandomAsciiMetadata<31>, 1>)
    ->Args({0, 1});
BENCHMARK_TEMPLATE(BM_CallbackBidiStreaming, InProcess, NoOpMutator,
                   Server_AddInitialMetadata<RandomAsciiMetadata<100>, 1>)
    ->Args({0, 1});
BENCHMARK_TEMPLATE(BM_CallbackBidiStreaming, InProcess, NoOpMutator,
                   Server_AddInitialMetadata<RandomAsciiMetadata<10>, 100>)
    ->Args({0, 1});

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
