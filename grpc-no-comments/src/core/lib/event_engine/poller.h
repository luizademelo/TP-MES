// Copyright 2022 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_EVENT_ENGINE_POLLER_H
#define GRPC_SRC_CORE_LIB_EVENT_ENGINE_POLLER_H

#include <grpc/event_engine/event_engine.h>
#include <grpc/support/port_platform.h>

#include "absl/functional/function_ref.h"

namespace grpc_event_engine::experimental {

class Poller {
 public:
  enum class WorkResult { kOk, kDeadlineExceeded, kKicked };

  virtual ~Poller() = default;

  virtual WorkResult Work(EventEngine::Duration timeout,
                          absl::FunctionRef<void()> schedule_poll_again) = 0;

  virtual void Kick() = 0;
};

}

#endif
