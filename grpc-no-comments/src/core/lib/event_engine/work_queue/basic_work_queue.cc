// Copyright 2023 The gRPC Authors

#include "src/core/lib/event_engine/work_queue/basic_work_queue.h"

#include <grpc/support/port_platform.h>

#include <utility>

#include "src/core/lib/event_engine/common_closures.h"
#include "src/core/util/sync.h"

namespace grpc_event_engine::experimental {

BasicWorkQueue::BasicWorkQueue(void* owner) : owner_(owner) {}

bool BasicWorkQueue::Empty() const {
  grpc_core::MutexLock lock(&mu_);
  return q_.empty();
}

size_t BasicWorkQueue::Size() const {
  grpc_core::MutexLock lock(&mu_);
  return q_.size();
}

EventEngine::Closure* BasicWorkQueue::PopMostRecent() {
  grpc_core::MutexLock lock(&mu_);
  if (q_.empty()) return nullptr;
  auto tmp = q_.back();
  q_.pop_back();
  return tmp;
}

EventEngine::Closure* BasicWorkQueue::PopOldest() {
  grpc_core::MutexLock lock(&mu_);
  if (q_.empty()) return nullptr;
  auto tmp = q_.front();
  q_.pop_front();
  return tmp;
}

void BasicWorkQueue::Add(EventEngine::Closure* closure) {
  grpc_core::MutexLock lock(&mu_);
  q_.push_back(closure);
}

void BasicWorkQueue::Add(absl::AnyInvocable<void()> invocable) {
  grpc_core::MutexLock lock(&mu_);
  q_.push_back(SelfDeletingClosure::Create(std::move(invocable)));
}

}
