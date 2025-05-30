// Copyright 2022 The gRPC Authors

#include <benchmark/benchmark.h>
#include <grpc/event_engine/event_engine.h>
#include <grpc/support/port_platform.h>

#include <deque>

#include "absl/log/check.h"
#include "src/core/lib/event_engine/common_closures.h"
#include "src/core/lib/event_engine/work_queue/basic_work_queue.h"
#include "src/core/util/sync.h"
#include "test/core/test_util/test_config.h"

namespace {

using ::grpc_event_engine::experimental::AnyInvocableClosure;
using ::grpc_event_engine::experimental::BasicWorkQueue;
using ::grpc_event_engine::experimental::EventEngine;

grpc_core::Mutex globalMu;
BasicWorkQueue globalWorkQueue;
std::deque<EventEngine::Closure*> globalDeque;

void MultithreadedTestArguments(benchmark::internal::Benchmark* b) {
  b->Range(1, 512)
      ->UseRealTime()
      ->MeasureProcessCPUTime()
      ->Threads(1)
      ->Threads(4)
      ->ThreadPerCpu();
}

void BM_MultithreadedWorkQueuePopOldest(benchmark::State& state) {
  AnyInvocableClosure closure([] {});
  int element_count = state.range(0);
  double pop_attempts = 0;
  for (auto _ : state) {
    for (int i = 0; i < element_count; i++) globalWorkQueue.Add(&closure);
    int cnt = 0;
    do {
      if (++pop_attempts && globalWorkQueue.PopOldest() != nullptr) ++cnt;
    } while (cnt < element_count);
  }
  state.counters["added"] = element_count * state.iterations();
  state.counters["pop_rate"] = benchmark::Counter(
      element_count * state.iterations(), benchmark::Counter::kIsRate);
  state.counters["pop_attempts"] = pop_attempts;

  state.counters["hit_rate"] =
      benchmark::Counter(element_count * state.iterations() / pop_attempts,
                         benchmark::Counter::kAvgThreads);
  if (state.thread_index() == 0) {
    CHECK(globalWorkQueue.Empty());
  }
}
BENCHMARK(BM_MultithreadedWorkQueuePopOldest)
    ->Apply(MultithreadedTestArguments);

void BM_MultithreadedWorkQueuePopMostRecent(benchmark::State& state) {
  AnyInvocableClosure closure([] {});
  int element_count = state.range(0);
  double pop_attempts = 0;
  for (auto _ : state) {
    for (int i = 0; i < element_count; i++) globalWorkQueue.Add(&closure);
    int cnt = 0;
    do {
      if (++pop_attempts && globalWorkQueue.PopMostRecent() != nullptr) ++cnt;
    } while (cnt < element_count);
  }
  state.counters["added"] = element_count * state.iterations();
  state.counters["pop_rate"] = benchmark::Counter(
      element_count * state.iterations(), benchmark::Counter::kIsRate);
  state.counters["pop_attempts"] = pop_attempts;
  state.counters["hit_rate"] =
      benchmark::Counter(element_count * state.iterations() / pop_attempts,
                         benchmark::Counter::kAvgThreads);
  if (state.thread_index() == 0) {
    CHECK(globalWorkQueue.Empty());
  }
}
BENCHMARK(BM_MultithreadedWorkQueuePopMostRecent)
    ->Apply(MultithreadedTestArguments);

void BM_MultithreadedStdDequeLIFO(benchmark::State& state) {
  int element_count = state.range(0);
  AnyInvocableClosure closure([] {});
  for (auto _ : state) {
    for (int i = 0; i < element_count; i++) {
      grpc_core::MutexLock lock(&globalMu);
      globalDeque.push_back(&closure);
    }
    for (int i = 0; i < element_count; i++) {
      grpc_core::MutexLock lock(&globalMu);
      EventEngine::Closure* popped = globalDeque.back();
      globalDeque.pop_back();
      CHECK_NE(popped, nullptr);
    }
  }
  state.counters["added"] = element_count * state.iterations();
  state.counters["pop_attempts"] = state.counters["added"];
  state.counters["pop_rate"] = benchmark::Counter(
      element_count * state.iterations(), benchmark::Counter::kIsRate);
  state.counters["hit_rate"] =
      benchmark::Counter(1, benchmark::Counter::kAvgThreads);
}
BENCHMARK(BM_MultithreadedStdDequeLIFO)->Apply(MultithreadedTestArguments);

void BM_WorkQueueIntptrPopMostRecent(benchmark::State& state) {
  BasicWorkQueue queue;
  grpc_event_engine::experimental::AnyInvocableClosure closure([] {});
  int element_count = state.range(0);
  for (auto _ : state) {
    int cnt = 0;
    for (int i = 0; i < element_count; i++) queue.Add(&closure);
    do {
      if (queue.PopMostRecent() != nullptr) ++cnt;
    } while (cnt < element_count);
  }
  state.counters["Added"] = element_count * state.iterations();
  state.counters["Popped"] = state.counters["Added"];
  state.counters["Pop Rate"] =
      benchmark::Counter(state.counters["Popped"], benchmark::Counter::kIsRate);
}
BENCHMARK(BM_WorkQueueIntptrPopMostRecent)
    ->Range(1, 512)
    ->UseRealTime()
    ->MeasureProcessCPUTime();

void BM_WorkQueueClosureExecution(benchmark::State& state) {
  BasicWorkQueue queue;
  int element_count = state.range(0);
  int run_count = 0;
  grpc_event_engine::experimental::AnyInvocableClosure closure(
      [&run_count] { ++run_count; });
  for (auto _ : state) {
    for (int i = 0; i < element_count; i++) queue.Add(&closure);
    do {
      queue.PopMostRecent()->Run();
    } while (run_count < element_count);
    run_count = 0;
  }
  state.counters["Added"] = element_count * state.iterations();
  state.counters["Popped"] = state.counters["Added"];
  state.counters["Pop Rate"] =
      benchmark::Counter(state.counters["Popped"], benchmark::Counter::kIsRate);
}
BENCHMARK(BM_WorkQueueClosureExecution)
    ->Range(8, 128)
    ->UseRealTime()
    ->MeasureProcessCPUTime();

void BM_WorkQueueAnyInvocableExecution(benchmark::State& state) {
  BasicWorkQueue queue;
  int element_count = state.range(0);
  int run_count = 0;
  for (auto _ : state) {
    for (int i = 0; i < element_count; i++) {
      queue.Add([&run_count] { ++run_count; });
    }
    do {
      queue.PopMostRecent()->Run();
    } while (run_count < element_count);
    run_count = 0;
  }
  state.counters["Added"] = element_count * state.iterations();
  state.counters["Popped"] = state.counters["Added"];
  state.counters["Pop Rate"] =
      benchmark::Counter(state.counters["Popped"], benchmark::Counter::kIsRate);
}
BENCHMARK(BM_WorkQueueAnyInvocableExecution)
    ->Range(8, 128)
    ->UseRealTime()
    ->MeasureProcessCPUTime();

}

namespace benchmark {
void RunTheBenchmarksNamespaced() { RunSpecifiedBenchmarks(); }
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::benchmark::Initialize(&argc, argv);
  benchmark::RunTheBenchmarksNamespaced();
  return 0;
}
