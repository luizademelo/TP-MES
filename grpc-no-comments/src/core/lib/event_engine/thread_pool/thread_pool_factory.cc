// Copyright 2023 The gRPC Authors

#include <grpc/support/port_platform.h>
#include <stddef.h>

#include <memory>

#include "src/core/lib/event_engine/forkable.h"
#include "src/core/lib/event_engine/thread_pool/thread_pool.h"
#include "src/core/lib/event_engine/thread_pool/work_stealing_thread_pool.h"
#include "src/core/util/no_destruct.h"

namespace grpc_event_engine::experimental {

namespace {
grpc_core::NoDestruct<ObjectGroupForkHandler> g_thread_pool_fork_manager;

class ThreadPoolForkCallbackMethods {
 public:
  static void Prefork() { g_thread_pool_fork_manager->Prefork(); }
  static void PostforkParent() { g_thread_pool_fork_manager->PostforkParent(); }
  static void PostforkChild() { g_thread_pool_fork_manager->PostforkChild(); }
};
}

std::shared_ptr<ThreadPool> MakeThreadPool(size_t reserve_threads) {
  auto thread_pool = std::make_shared<WorkStealingThreadPool>(reserve_threads);
  g_thread_pool_fork_manager->RegisterForkable(
      thread_pool, ThreadPoolForkCallbackMethods::Prefork,
      ThreadPoolForkCallbackMethods::PostforkParent,
      ThreadPoolForkCallbackMethods::PostforkChild);
  return thread_pool;
}

}
