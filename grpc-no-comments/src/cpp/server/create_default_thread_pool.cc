
// Copyright 2015 gRPC authors.

#include "src/cpp/server/dynamic_thread_pool.h"
#include "src/cpp/server/thread_pool_interface.h"

#ifndef GRPC_CUSTOM_DEFAULT_THREAD_POOL

namespace grpc {
namespace {

ThreadPoolInterface* CreateDefaultThreadPoolImpl() {
  return new DynamicThreadPool();
}

CreateThreadPoolFunc g_ctp_impl = CreateDefaultThreadPoolImpl;

}

ThreadPoolInterface* CreateDefaultThreadPool() { return g_ctp_impl(); }

void SetCreateThreadPool(CreateThreadPoolFunc func) { g_ctp_impl = func; }

}

#endif
