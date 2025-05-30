// Copyright 2023 The gRPC Authors

#ifndef GRPC_SRC_CORE_LIB_EVENT_ENGINE_THREAD_POOL_THREAD_POOL_H
#define GRPC_SRC_CORE_LIB_EVENT_ENGINE_THREAD_POOL_THREAD_POOL_H
#include <grpc/event_engine/event_engine.h>
#include <grpc/support/port_platform.h>
#include <stddef.h>

#include <memory>

#include "absl/functional/any_invocable.h"
#include "src/core/lib/event_engine/forkable.h"

namespace grpc_event_engine::experimental {

class ThreadPool : public Forkable {
 public:

  ~ThreadPool() override = default;

  virtual void Quiesce() = 0;

  virtual void Run(absl::AnyInvocable<void()> callback) = 0;
  virtual void Run(EventEngine::Closure* closure) = 0;
};

std::shared_ptr<ThreadPool> MakeThreadPool(size_t reserve_threads);

}

#endif
