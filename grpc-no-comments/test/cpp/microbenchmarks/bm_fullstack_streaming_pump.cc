
// Copyright 2016 gRPC authors.

#include "test/core/test_util/test_config.h"
#include "test/cpp/microbenchmarks/fullstack_streaming_pump.h"
#include "test/cpp/util/test_config.h"

namespace grpc {
namespace testing {

BENCHMARK_TEMPLATE(BM_PumpStreamClientToServer, TCP)
    ->Range(0, 128 * 1024 * 1024);
BENCHMARK_TEMPLATE(BM_PumpStreamClientToServer, UDS)
    ->Range(0, 128 * 1024 * 1024);
BENCHMARK_TEMPLATE(BM_PumpStreamClientToServer, InProcess)
    ->Range(0, 128 * 1024 * 1024);
BENCHMARK_TEMPLATE(BM_PumpStreamServerToClient, TCP)
    ->Range(0, 128 * 1024 * 1024);
BENCHMARK_TEMPLATE(BM_PumpStreamServerToClient, UDS)
    ->Range(0, 128 * 1024 * 1024);
BENCHMARK_TEMPLATE(BM_PumpStreamServerToClient, InProcess)
    ->Range(0, 128 * 1024 * 1024);
BENCHMARK_TEMPLATE(BM_PumpStreamClientToServer, MinTCP)->Arg(0);
BENCHMARK_TEMPLATE(BM_PumpStreamClientToServer, MinUDS)->Arg(0);
BENCHMARK_TEMPLATE(BM_PumpStreamClientToServer, MinInProcess)->Arg(0);
BENCHMARK_TEMPLATE(BM_PumpStreamServerToClient, MinTCP)->Arg(0);
BENCHMARK_TEMPLATE(BM_PumpStreamServerToClient, MinUDS)->Arg(0);
BENCHMARK_TEMPLATE(BM_PumpStreamServerToClient, MinInProcess)->Arg(0);

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
