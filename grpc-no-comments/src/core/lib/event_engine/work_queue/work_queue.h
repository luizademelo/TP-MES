// Copyright 2022 The gRPC Authors

#ifndef GRPC_SRC_CORE_LIB_EVENT_ENGINE_WORK_QUEUE_WORK_QUEUE_H
#define GRPC_SRC_CORE_LIB_EVENT_ENGINE_WORK_QUEUE_WORK_QUEUE_H

#include <grpc/event_engine/event_engine.h>
#include <grpc/support/port_platform.h>
#include <stddef.h>

#include "absl/functional/any_invocable.h"

namespace grpc_event_engine::experimental {

class WorkQueue {
 public:
  virtual ~WorkQueue() = default;

  virtual bool Empty() const = 0;

  virtual size_t Size() const = 0;

  virtual EventEngine::Closure* PopMostRecent() = 0;

  virtual EventEngine::Closure* PopOldest() = 0;

  virtual void Add(EventEngine::Closure* closure) = 0;

  virtual void Add(absl::AnyInvocable<void()> invocable) = 0;

  virtual const void* owner() = 0;
};

}

#endif
