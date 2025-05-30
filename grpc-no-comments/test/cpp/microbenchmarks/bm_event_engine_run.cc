// Copyright 2022 The gRPC Authors

#include <benchmark/benchmark.h>
#include <grpc/event_engine/event_engine.h>
#include <grpcpp/impl/grpc_library.h>

#include <atomic>
#include <cmath>
#include <memory>
#include <vector>

#include "absl/debugging/leak_check.h"
#include "absl/functional/any_invocable.h"
#include "absl/log/check.h"
#include "absl/strings/str_format.h"
#include "src/core/lib/event_engine/common_closures.h"
#include "src/core/lib/event_engine/default_event_engine.h"
#include "src/core/util/crash.h"
#include "src/core/util/notification.h"
#include "test/core/test_util/test_config.h"
#include "test/cpp/microbenchmarks/helpers.h"
#include "test/cpp/util/test_config.h"

namespace {

using ::grpc_event_engine::experimental::AnyInvocableClosure;
using ::grpc_event_engine::experimental::EventEngine;
using ::grpc_event_engine::experimental::GetDefaultEventEngine;

struct FanoutParameters {
  int depth;
  int fanout;
  int limit;
};

void BM_EventEngine_RunSmallLambda(benchmark::State& state) {
  auto engine = GetDefaultEventEngine();
  const int cb_count = state.range(0);
  std::atomic_int count{0};
  for (auto _ : state) {
    state.PauseTiming();
    grpc_core::Notification signal;
    auto cb = [&signal, &count, cb_count]() {
      if (++count == cb_count) signal.Notify();
    };
    state.ResumeTiming();
    for (int i = 0; i < cb_count; i++) {
      engine->Run(cb);
    }
    signal.WaitForNotification();
    count.store(0);
  }
  state.SetItemsProcessed(cb_count * state.iterations());
}
BENCHMARK(BM_EventEngine_RunSmallLambda)
    ->Range(100, 4096)
    ->MeasureProcessCPUTime()
    ->UseRealTime();

void BM_EventEngine_RunLargeLambda(benchmark::State& state) {
  int cb_count = state.range(0);

  std::string extra = "12345678";
  auto engine = GetDefaultEventEngine();
  std::atomic_int count{0};
  for (auto _ : state) {
    state.PauseTiming();
    grpc_core::Notification signal;
    auto cb = [&signal, &count, cb_count, extra]() {
      (void)extra;
      if (++count == cb_count) signal.Notify();
    };
    state.ResumeTiming();
    for (int i = 0; i < cb_count; i++) {
      engine->Run(cb);
    }
    signal.WaitForNotification();
    count.store(0);
  }
  state.SetItemsProcessed(cb_count * state.iterations());
}
BENCHMARK(BM_EventEngine_RunLargeLambda)
    ->Range(100, 4096)
    ->MeasureProcessCPUTime()
    ->UseRealTime();

void BM_EventEngine_RunClosure(benchmark::State& state) {
  int cb_count = state.range(0);
  grpc_core::Notification* signal = new grpc_core::Notification();
  std::atomic_int count{0};

  AnyInvocableClosure* closure = absl::IgnoreLeak(
      new AnyInvocableClosure([signal_holder = &signal, cb_count, &count]() {
        if (++count == cb_count) {
          (*signal_holder)->Notify();
        }
      }));
  auto engine = GetDefaultEventEngine();
  for (auto _ : state) {
    for (int i = 0; i < cb_count; i++) {
      engine->Run(closure);
    }
    signal->WaitForNotification();
    state.PauseTiming();
    delete signal;
    signal = new grpc_core::Notification();
    count.store(0);
    state.ResumeTiming();
  }
  delete signal;
  state.SetItemsProcessed(cb_count * state.iterations());
}
BENCHMARK(BM_EventEngine_RunClosure)
    ->Range(100, 4096)
    ->MeasureProcessCPUTime()
    ->UseRealTime();

void FanoutTestArguments(benchmark::internal::Benchmark* b) {

  b->Args({1000, 1})
      ->Args({100, 1})
      ->Args({1, 1000})
      ->Args({1, 100})
      ->Args({2, 70})
      ->Args({4, 8})
      ->UseRealTime()
      ->MeasureProcessCPUTime();
}

FanoutParameters GetFanoutParameters(benchmark::State& state) {
  FanoutParameters params;
  params.depth = state.range(0);
  params.fanout = state.range(1);
  if (params.depth == 1 || params.fanout == 1) {
    params.limit = std::max(params.depth, params.fanout) + 1;
  } else {

    params.limit =
        (1 - std::pow(params.fanout, params.depth + 1)) / (1 - params.fanout);
  }

  CHECK(params.limit >= params.fanout * params.depth);
  return params;
}

void FanOutCallback(std::shared_ptr<EventEngine> engine,
                    const FanoutParameters params,
                    grpc_core::Notification& signal, std::atomic_int& count,
                    int processing_layer) {
  int local_cnt = count.fetch_add(1, std::memory_order_acq_rel) + 1;
  if (local_cnt == params.limit) {
    signal.Notify();
    return;
  }
  DCHECK_LT(local_cnt, params.limit);
  if (params.depth == processing_layer) return;
  for (int i = 0; i < params.fanout; i++) {
    engine->Run([engine, params, processing_layer, &count, &signal]() {
      FanOutCallback(engine, params, signal, count, processing_layer + 1);
    });
  }
}

void BM_EventEngine_Lambda_FanOut(benchmark::State& state) {
  auto params = GetFanoutParameters(state);
  auto engine = GetDefaultEventEngine();
  for (auto _ : state) {
    std::atomic_int count{0};
    grpc_core::Notification signal;
    FanOutCallback(engine, params, signal, count, 0);
    do {
      signal.WaitForNotification();
    } while (count.load() != params.limit);
  }
  state.SetItemsProcessed(params.limit * state.iterations());
}
BENCHMARK(BM_EventEngine_Lambda_FanOut)->Apply(FanoutTestArguments);

void ClosureFanOutCallback(EventEngine::Closure* child_closure,
                           std::shared_ptr<EventEngine> engine,
                           grpc_core::Notification** signal_holder,
                           std::atomic_int& count,
                           const FanoutParameters params) {
  int local_cnt = count.fetch_add(1, std::memory_order_acq_rel) + 1;
  if (local_cnt == params.limit) {
    (*signal_holder)->Notify();
    return;
  }
  if (local_cnt > params.limit) {
    grpc_core::Crash(absl::StrFormat("Ran too many closures: %d/%d", local_cnt,
                                     params.limit));
  }
  if (child_closure == nullptr) return;
  for (int i = 0; i < params.fanout; i++) {
    engine->Run(child_closure);
  }
}

void BM_EventEngine_Closure_FanOut(benchmark::State& state) {
  auto params = GetFanoutParameters(state);
  auto engine = GetDefaultEventEngine();
  std::vector<EventEngine::Closure*> closures;
  closures.reserve(params.depth + 2);
  closures.push_back(nullptr);
  grpc_core::Notification* signal = new grpc_core::Notification();
  std::atomic_int count{0};

  for (int i = 0; i <= params.depth; i++) {

    closures.push_back(new AnyInvocableClosure(
        [i, engine, &closures, params, signal_holder = &signal, &count]() {
          ClosureFanOutCallback(closures[i], engine, signal_holder, count,
                                params);
        }));
  }
  for (auto _ : state) {
    DCHECK_EQ(count.load(std::memory_order_relaxed), 0);
    engine->Run(closures[params.depth + 1]);
    do {
      signal->WaitForNotification();
    } while (count.load() != params.limit);

    state.PauseTiming();
    delete signal;
    signal = new grpc_core::Notification();
    count.store(0);
    state.ResumeTiming();
  }
  delete signal;
  state.SetItemsProcessed(params.limit * state.iterations());
  for (auto i : closures) delete i;
}
BENCHMARK(BM_EventEngine_Closure_FanOut)->Apply(FanoutTestArguments);

}

namespace benchmark {
void RunTheBenchmarksNamespaced() { RunSpecifiedBenchmarks(); }
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  LibraryInitializer libInit;
  benchmark::Initialize(&argc, argv);
  grpc::testing::InitTest(&argc, &argv, false);

  benchmark::RunTheBenchmarksNamespaced();
  return 0;
}
