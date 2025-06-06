
// Copyright 2015 gRPC authors.

#include <benchmark/benchmark.h>
#include <grpc/grpc.h>
#include <grpcpp/completion_queue.h>
#include <grpcpp/impl/grpc_library.h>

#include "absl/log/check.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/surface/completion_queue.h"
#include "src/core/util/crash.h"
#include "test/core/test_util/test_config.h"
#include "test/cpp/microbenchmarks/helpers.h"
#include "test/cpp/util/test_config.h"

namespace grpc {
namespace testing {

static void BM_CreateDestroyCpp(benchmark::State& state) {
  for (auto _ : state) {
    CompletionQueue cq;
  }
}
BENCHMARK(BM_CreateDestroyCpp);

static void BM_CreateDestroyCpp2(benchmark::State& state) {
  for (auto _ : state) {
    grpc_completion_queue* core_cq =
        grpc_completion_queue_create_for_next(nullptr);
    CompletionQueue cq(core_cq);
  }
}
BENCHMARK(BM_CreateDestroyCpp2);

static void BM_CreateDestroyCore(benchmark::State& state) {
  for (auto _ : state) {

    grpc_completion_queue_destroy(
        grpc_completion_queue_create_for_next(nullptr));
  }
}
BENCHMARK(BM_CreateDestroyCore);

static void DoneWithCompletionOnStack(void* ,
                                      grpc_cq_completion* ) {}

static void DoneWithCompletionOnHeap(void* ,
                                     grpc_cq_completion* completion) {
  delete completion;
}

class PhonyTag final : public internal::CompletionQueueTag {
 public:
  bool FinalizeResult(void** , bool* ) override {
    return true;
  }
};

static void BM_Pass1Cpp(benchmark::State& state) {
  CompletionQueue cq;
  grpc_completion_queue* c_cq = cq.cq();
  for (auto _ : state) {
    grpc_cq_completion completion;
    PhonyTag phony_tag;
    grpc_core::ExecCtx exec_ctx;
    CHECK(grpc_cq_begin_op(c_cq, &phony_tag));
    grpc_cq_end_op(c_cq, &phony_tag, absl::OkStatus(),
                   DoneWithCompletionOnStack, nullptr, &completion);

    void* tag;
    bool ok;
    cq.Next(&tag, &ok);
  }
}
BENCHMARK(BM_Pass1Cpp);

static void BM_Pass1Core(benchmark::State& state) {

  grpc_completion_queue* cq = grpc_completion_queue_create_for_next(nullptr);
  gpr_timespec deadline = gpr_inf_future(GPR_CLOCK_MONOTONIC);
  for (auto _ : state) {
    grpc_cq_completion completion;
    grpc_core::ExecCtx exec_ctx;
    CHECK(grpc_cq_begin_op(cq, nullptr));
    grpc_cq_end_op(cq, nullptr, absl::OkStatus(), DoneWithCompletionOnStack,
                   nullptr, &completion);

    grpc_completion_queue_next(cq, deadline, nullptr);
  }
  grpc_completion_queue_destroy(cq);
}
BENCHMARK(BM_Pass1Core);

static void BM_Pluck1Core(benchmark::State& state) {

  grpc_completion_queue* cq = grpc_completion_queue_create_for_pluck(nullptr);
  gpr_timespec deadline = gpr_inf_future(GPR_CLOCK_MONOTONIC);
  for (auto _ : state) {
    grpc_cq_completion completion;
    grpc_core::ExecCtx exec_ctx;
    CHECK(grpc_cq_begin_op(cq, nullptr));
    grpc_cq_end_op(cq, nullptr, absl::OkStatus(), DoneWithCompletionOnStack,
                   nullptr, &completion);

    grpc_completion_queue_pluck(cq, nullptr, deadline, nullptr);
  }
  grpc_completion_queue_destroy(cq);
}
BENCHMARK(BM_Pluck1Core);

static void BM_EmptyCore(benchmark::State& state) {

  grpc_completion_queue* cq = grpc_completion_queue_create_for_next(nullptr);
  gpr_timespec deadline = gpr_inf_past(GPR_CLOCK_MONOTONIC);
  for (auto _ : state) {
    grpc_completion_queue_next(cq, deadline, nullptr);
  }
  grpc_completion_queue_destroy(cq);
}
BENCHMARK(BM_EmptyCore);

static void shutdown_and_destroy(grpc_completion_queue* cc) {
  grpc_completion_queue_shutdown(cc);
  grpc_completion_queue_destroy(cc);
}

static gpr_mu shutdown_mu, mu;
static gpr_cv shutdown_cv, cv;

class TagCallback : public grpc_completion_queue_functor {
 public:
  explicit TagCallback(int* iter) : iter_(iter) {
    functor_run = &TagCallback::Run;
    inlineable = false;
  }
  ~TagCallback() {}
  static void Run(grpc_completion_queue_functor* cb, int ok) {
    gpr_mu_lock(&mu);
    CHECK(static_cast<bool>(ok));
    *static_cast<TagCallback*>(cb)->iter_ += 1;
    gpr_cv_signal(&cv);
    gpr_mu_unlock(&mu);
  };

 private:
  int* iter_;
};

class ShutdownCallback : public grpc_completion_queue_functor {
 public:
  explicit ShutdownCallback(bool* done) : done_(done) {
    functor_run = &ShutdownCallback::Run;
    inlineable = false;
  }
  ~ShutdownCallback() {}
  static void Run(grpc_completion_queue_functor* cb, int ok) {
    gpr_mu_lock(&shutdown_mu);
    *static_cast<ShutdownCallback*>(cb)->done_ = static_cast<bool>(ok);
    gpr_cv_signal(&shutdown_cv);
    gpr_mu_unlock(&shutdown_mu);
  }

 private:
  bool* done_;
};

static void BM_Callback_CQ_Pass1Core(benchmark::State& state) {
  int iteration = 0, current_iterations = 0;
  TagCallback tag_cb(&iteration);
  gpr_mu_init(&mu);
  gpr_cv_init(&cv);
  gpr_mu_init(&shutdown_mu);
  gpr_cv_init(&shutdown_cv);
  bool got_shutdown = false;
  ShutdownCallback shutdown_cb(&got_shutdown);

  grpc_completion_queue_attributes attr;
  attr.version = 2;
  attr.cq_completion_type = GRPC_CQ_CALLBACK;
  attr.cq_polling_type = GRPC_CQ_NON_POLLING;
  attr.cq_shutdown_cb = &shutdown_cb;
  grpc_completion_queue* cc = grpc_completion_queue_create(
      grpc_completion_queue_factory_lookup(&attr), &attr, nullptr);
  for (auto _ : state) {
    grpc_core::ExecCtx exec_ctx;
    grpc_cq_completion completion;
    CHECK(grpc_cq_begin_op(cc, &tag_cb));
    grpc_cq_end_op(cc, &tag_cb, absl::OkStatus(), DoneWithCompletionOnStack,
                   nullptr, &completion);
  }
  shutdown_and_destroy(cc);

  gpr_mu_lock(&mu);
  current_iterations = static_cast<int>(state.iterations());
  while (current_iterations != iteration) {

    gpr_cv_wait(&cv, &mu, gpr_inf_future(GPR_CLOCK_REALTIME));
  }
  gpr_mu_unlock(&mu);

  gpr_mu_lock(&shutdown_mu);
  while (!got_shutdown) {

    gpr_cv_wait(&shutdown_cv, &shutdown_mu, gpr_inf_future(GPR_CLOCK_REALTIME));
  }
  gpr_mu_unlock(&shutdown_mu);

  CHECK(got_shutdown);
  CHECK(iteration == static_cast<int>(state.iterations()));
  gpr_cv_destroy(&cv);
  gpr_mu_destroy(&mu);
  gpr_cv_destroy(&shutdown_cv);
  gpr_mu_destroy(&shutdown_mu);
}
static void BM_Callback_CQ_Pass1CoreHeapCompletion(benchmark::State& state) {
  int iteration = 0, current_iterations = 0;
  TagCallback tag_cb(&iteration);
  gpr_mu_init(&mu);
  gpr_cv_init(&cv);
  gpr_mu_init(&shutdown_mu);
  gpr_cv_init(&shutdown_cv);
  bool got_shutdown = false;
  ShutdownCallback shutdown_cb(&got_shutdown);
  grpc_completion_queue* cc =
      grpc_completion_queue_create_for_callback(&shutdown_cb, nullptr);
  for (auto _ : state) {
    grpc_core::ExecCtx exec_ctx;
    grpc_cq_completion* completion = new grpc_cq_completion;
    CHECK(grpc_cq_begin_op(cc, &tag_cb));
    grpc_cq_end_op(cc, &tag_cb, absl::OkStatus(), DoneWithCompletionOnHeap,
                   nullptr, completion);
  }
  shutdown_and_destroy(cc);

  gpr_mu_lock(&mu);
  current_iterations = static_cast<int>(state.iterations());
  while (current_iterations != iteration) {

    gpr_cv_wait(&cv, &mu, gpr_inf_future(GPR_CLOCK_REALTIME));
  }
  gpr_mu_unlock(&mu);

  gpr_mu_lock(&shutdown_mu);
  while (!got_shutdown) {

    gpr_cv_wait(&shutdown_cv, &shutdown_mu, gpr_inf_future(GPR_CLOCK_REALTIME));
  }
  gpr_mu_unlock(&shutdown_mu);

  CHECK(got_shutdown);
  CHECK(iteration == static_cast<int>(state.iterations()));
  gpr_cv_destroy(&cv);
  gpr_mu_destroy(&mu);
  gpr_cv_destroy(&shutdown_cv);
  gpr_mu_destroy(&shutdown_mu);
}
BENCHMARK(BM_Callback_CQ_Pass1Core);
BENCHMARK(BM_Callback_CQ_Pass1CoreHeapCompletion);

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
