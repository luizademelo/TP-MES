
// Copyright 2015 gRPC authors.

#include <grpc/grpc.h>
#include <grpc/support/cpu.h>
#include <grpc/support/sync.h>
#include <grpc/support/time.h>
#include <grpcpp/completion_queue.h>
#include <grpcpp/impl/completion_queue_tag.h>
#include <grpcpp/impl/grpc_library.h>

#include <vector>

#include "absl/base/thread_annotations.h"
#include "absl/log/check.h"
#include "absl/log/log.h"
#include "src/core/lib/experiments/experiments.h"
#include "src/core/util/crash.h"
#include "src/core/util/sync.h"
#include "src/core/util/thd.h"
#include "src/core/util/useful.h"

namespace grpc {
namespace {

gpr_once g_once_init_callback_alternative = GPR_ONCE_INIT;
grpc_core::Mutex* g_callback_alternative_mu;

struct CallbackAlternativeCQ {
  int refs ABSL_GUARDED_BY(g_callback_alternative_mu) = 0;
  CompletionQueue* cq ABSL_GUARDED_BY(g_callback_alternative_mu);
  std::vector<grpc_core::Thread>* nexting_threads
      ABSL_GUARDED_BY(g_callback_alternative_mu);

  CompletionQueue* Ref() {
    grpc_core::MutexLock lock(&*g_callback_alternative_mu);
    refs++;
    if (refs == 1) {
      cq = new CompletionQueue;
      int num_nexting_threads =
          grpc_core::Clamp(gpr_cpu_num_cores() / 2, 2u, 16u);
      nexting_threads = new std::vector<grpc_core::Thread>;
      for (int i = 0; i < num_nexting_threads; i++) {
        nexting_threads->emplace_back(
            "nexting_thread",
            [](void* arg) {
              grpc_completion_queue* cq =
                  static_cast<CompletionQueue*>(arg)->cq();
              while (true) {

                auto ev = grpc_completion_queue_next(
                    cq,
                    gpr_time_add(gpr_now(GPR_CLOCK_REALTIME),
                                 gpr_time_from_millis(1000, GPR_TIMESPAN)),
                    nullptr);
                if (ev.type == GRPC_QUEUE_SHUTDOWN) {
                  return;
                }
                if (ev.type == GRPC_QUEUE_TIMEOUT) {
                  gpr_sleep_until(
                      gpr_time_add(gpr_now(GPR_CLOCK_REALTIME),
                                   gpr_time_from_millis(100, GPR_TIMESPAN)));
                  continue;
                }
                DCHECK(ev.type == GRPC_OP_COMPLETE);

                auto* functor =
                    static_cast<grpc_completion_queue_functor*>(ev.tag);
                functor->functor_run(functor, ev.success);
              }
            },
            cq);
      }
      for (auto& th : *nexting_threads) {
        th.Start();
      }
    }
    return cq;
  }

  void Unref() {
    grpc_core::MutexLock lock(g_callback_alternative_mu);
    refs--;
    if (refs == 0) {
      cq->Shutdown();
      for (auto& th : *nexting_threads) {
        th.Join();
      }
      delete nexting_threads;
      delete cq;
    }
  }
};

CallbackAlternativeCQ g_callback_alternative_cq;

}

CompletionQueue::CompletionQueue(grpc_completion_queue* take)
    : GrpcLibrary(false), cq_(take) {
  InitialAvalanching();
}

void CompletionQueue::Shutdown() {
#ifndef NDEBUG
  if (!ServerListEmpty()) {
    LOG(ERROR) << "CompletionQueue shutdown being shutdown before its server.";
  }
#endif
  CompleteAvalanching();
}

CompletionQueue::NextStatus CompletionQueue::AsyncNextInternal(
    void** tag, bool* ok, gpr_timespec deadline) {
  for (;;) {
    auto ev = grpc_completion_queue_next(cq_, deadline, nullptr);
    switch (ev.type) {
      case GRPC_QUEUE_TIMEOUT:
        return TIMEOUT;
      case GRPC_QUEUE_SHUTDOWN:
        return SHUTDOWN;
      case GRPC_OP_COMPLETE:
        auto core_cq_tag =
            static_cast<grpc::internal::CompletionQueueTag*>(ev.tag);
        *ok = ev.success != 0;
        *tag = core_cq_tag;
        if (core_cq_tag->FinalizeResult(tag, ok)) {
          return GOT_EVENT;
        }
        break;
    }
  }
}

CompletionQueue::CompletionQueueTLSCache::CompletionQueueTLSCache(
    CompletionQueue* cq)
    : cq_(cq), flushed_(false) {
  grpc_completion_queue_thread_local_cache_init(cq_->cq_);
}

CompletionQueue::CompletionQueueTLSCache::~CompletionQueueTLSCache() {
  CHECK(flushed_);
}

bool CompletionQueue::CompletionQueueTLSCache::Flush(void** tag, bool* ok) {
  int res = 0;
  void* res_tag;
  flushed_ = true;
  if (grpc_completion_queue_thread_local_cache_flush(cq_->cq_, &res_tag,
                                                     &res)) {
    auto core_cq_tag =
        static_cast<grpc::internal::CompletionQueueTag*>(res_tag);
    *ok = res == 1;
    if (core_cq_tag->FinalizeResult(tag, ok)) {
      return true;
    }
  }
  return false;
}

CompletionQueue* CompletionQueue::CallbackAlternativeCQ() {
  if (grpc_core::IsEventEngineCallbackCqEnabled()) {
    grpc_core::Crash("CallbackAlternativeCQ should not be instantiated");
  }
  gpr_once_init(&g_once_init_callback_alternative,
                [] { g_callback_alternative_mu = new grpc_core::Mutex(); });
  return g_callback_alternative_cq.Ref();
}

void CompletionQueue::ReleaseCallbackAlternativeCQ(CompletionQueue* cq)
    ABSL_NO_THREAD_SAFETY_ANALYSIS {
  (void)cq;

  DCHECK(cq == g_callback_alternative_cq.cq);
  g_callback_alternative_cq.Unref();
}

}
