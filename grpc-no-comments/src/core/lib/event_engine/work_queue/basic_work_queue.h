// Copyright 2023 The gRPC Authors

#ifndef GRPC_SRC_CORE_LIB_EVENT_ENGINE_WORK_QUEUE_BASIC_WORK_QUEUE_H
#define GRPC_SRC_CORE_LIB_EVENT_ENGINE_WORK_QUEUE_BASIC_WORK_QUEUE_H
#include <grpc/event_engine/event_engine.h>
#include <grpc/support/port_platform.h>
#include <stddef.h>

#include <deque>

#include "absl/base/thread_annotations.h"
#include "absl/functional/any_invocable.h"
#include "src/core/lib/event_engine/work_queue/work_queue.h"
#include "src/core/util/sync.h"

namespace grpc_event_engine::experimental {

class BasicWorkQueue : public WorkQueue {
 public:
  BasicWorkQueue() : owner_(nullptr) {}
  explicit BasicWorkQueue(void* owner);

  bool Empty() const override ABSL_LOCKS_EXCLUDED(mu_);

  size_t Size() const override ABSL_LOCKS_EXCLUDED(mu_);

  EventEngine::Closure* PopMostRecent() override ABSL_LOCKS_EXCLUDED(mu_);

  EventEngine::Closure* PopOldest() override ABSL_LOCKS_EXCLUDED(mu_);

  void Add(EventEngine::Closure* closure) override ABSL_LOCKS_EXCLUDED(mu_);

  void Add(absl::AnyInvocable<void()> invocable) override
      ABSL_LOCKS_EXCLUDED(mu_);
  const void* owner() override { return owner_; }

 private:
  mutable grpc_core::Mutex mu_;
  std::deque<EventEngine::Closure*> q_ ABSL_GUARDED_BY(mu_);
  const void* const owner_ = nullptr;
};

}

#endif
