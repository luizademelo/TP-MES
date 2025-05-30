// Copyright 2024 gRPC authors.

#include <benchmark/benchmark.h>
#include <grpc/grpc.h>

#include "src/core/lib/event_engine/default_event_engine.h"
#include "src/core/lib/promise/party.h"
#include "src/core/lib/resource_quota/arena.h"

namespace grpc_core {
namespace {

void BM_PartyCreate(benchmark::State& state) {
  auto arena = SimpleArenaAllocator()->MakeArena();
  arena->SetContext(
      grpc_event_engine::experimental::GetDefaultEventEngine().get());
  for (auto _ : state) {
    Party::Make(arena);
  }
}
BENCHMARK(BM_PartyCreate);

void BM_AddParticipant(benchmark::State& state) {
  auto arena = SimpleArenaAllocator()->MakeArena();
  arena->SetContext(
      grpc_event_engine::experimental::GetDefaultEventEngine().get());
  auto party = Party::Make(arena);
  for (auto _ : state) {
    party->Spawn("participant", []() { return Success{}; }, [](StatusFlag) {});
  }
}
BENCHMARK(BM_AddParticipant);

void BM_WakeupParticipant(benchmark::State& state) {
  auto arena = SimpleArenaAllocator()->MakeArena();
  arena->SetContext(
      grpc_event_engine::experimental::GetDefaultEventEngine().get());
  auto party = Party::Make(arena);
  party->Spawn(
      "driver",
      [&state, w = IntraActivityWaiter()]() mutable -> Poll<StatusFlag> {
        w.pending();
        if (state.KeepRunning()) {
          w.Wake();
          return Pending{};
        }
        return Success{};
      },
      [party](StatusFlag) {});
}
BENCHMARK(BM_WakeupParticipant);

}
}

namespace benchmark {
void RunTheBenchmarksNamespaced() { RunSpecifiedBenchmarks(); }
}

int main(int argc, char** argv) {
  ::benchmark::Initialize(&argc, argv);
  grpc_init();
  {
    auto ee = grpc_event_engine::experimental::GetDefaultEventEngine();
    benchmark::RunTheBenchmarksNamespaced();
  }
  grpc_shutdown();
  return 0;
}
