
// Copyright 2017 gRPC authors.

#include <benchmark/benchmark.h>

#include "src/core/call/metadata.h"

namespace grpc_core {
namespace {

void BM_MetadataMapCreateDestroy(benchmark::State& state) {
  for (auto _ : state) {
    auto md = Arena::MakePooledForOverwrite<ServerMetadata>();
  }
}
BENCHMARK(BM_MetadataMapCreateDestroy);

void BM_MetadataMapCreateDestroyOnStack(benchmark::State& state) {
  for (auto _ : state) {
    ServerMetadata md;
  }
}
BENCHMARK(BM_MetadataMapCreateDestroyOnStack);

void BM_MetadataMapCreateDestroySetStatus(benchmark::State& state) {
  auto message = Slice::FromExternalString("message");
  for (auto _ : state) {
    auto md = Arena::MakePooledForOverwrite<ServerMetadata>();
    md->Set(GrpcStatusMetadata(), GRPC_STATUS_UNKNOWN);
    md->Set(GrpcMessageMetadata(), message.Copy());
  }
}
BENCHMARK(BM_MetadataMapCreateDestroySetStatus);

void BM_MetadataMapCreateDestroySetStatusCancelled(benchmark::State& state) {
  auto message = Slice::FromExternalString("message");
  for (auto _ : state) {
    auto md = Arena::MakePooledForOverwrite<ServerMetadata>();
    md->Set(GrpcStatusMetadata(), GRPC_STATUS_CANCELLED);
  }
}
BENCHMARK(BM_MetadataMapCreateDestroySetStatusCancelled);

void BM_MetadataMapFromAbslStatusCancelled(benchmark::State& state) {
  for (auto _ : state) {
    ServerMetadataFromStatus(absl::CancelledError());
  }
}
BENCHMARK(BM_MetadataMapFromAbslStatusCancelled);

void BM_MetadataMapFromAbslStatusOk(benchmark::State& state) {
  for (auto _ : state) {
    ServerMetadataFromStatus(absl::OkStatus());
  }
}
BENCHMARK(BM_MetadataMapFromAbslStatusOk);

}
}

namespace benchmark {
void RunTheBenchmarksNamespaced() { RunSpecifiedBenchmarks(); }
}

int main(int argc, char** argv) {
  ::benchmark::Initialize(&argc, argv);
  benchmark::RunTheBenchmarksNamespaced();
  return 0;
}
