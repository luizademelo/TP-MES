
// Copyright 2017 gRPC authors.

#include <benchmark/benchmark.h>
#include <grpc/credentials.h>
#include <grpc/grpc.h>
#include <grpc/grpc_security.h>

#include "test/core/test_util/test_config.h"
#include "test/cpp/microbenchmarks/helpers.h"
#include "test/cpp/util/test_config.h"

class ChannelDestroyerFixture {
 public:
  ChannelDestroyerFixture() {}
  virtual ~ChannelDestroyerFixture() {
    if (channel_) {
      grpc_channel_destroy(channel_);
    }
  }
  virtual void Init() = 0;

 protected:
  grpc_channel* channel_ = nullptr;
};

class InsecureChannelFixture : public ChannelDestroyerFixture {
 public:
  InsecureChannelFixture() {}
  void Init() override {
    grpc_channel_credentials* creds = grpc_insecure_credentials_create();
    channel_ = grpc_channel_create("localhost:1234", creds, nullptr);
    grpc_channel_credentials_release(creds);
  }
};

class LameChannelFixture : public ChannelDestroyerFixture {
 public:
  LameChannelFixture() {}
  void Init() override {
    channel_ = grpc_lame_client_channel_create(
        "localhost:1234", GRPC_STATUS_UNAUTHENTICATED, "blah");
  }
};

template <class Fixture>
static void BM_InsecureChannelCreateDestroy(benchmark::State& state) {

  Fixture initial_channels[512];
  for (int i = 0; i < state.range(0); i++) {
    initial_channels[i].Init();
  }
  for (auto _ : state) {
    Fixture channel;
    channel.Init();
  }
}
BENCHMARK_TEMPLATE(BM_InsecureChannelCreateDestroy, InsecureChannelFixture)
    ->Range(0, 512);
;
BENCHMARK_TEMPLATE(BM_InsecureChannelCreateDestroy, LameChannelFixture)
    ->Range(0, 512);
;

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
