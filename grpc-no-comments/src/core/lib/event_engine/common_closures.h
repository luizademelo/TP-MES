// Copyright 2022 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_EVENT_ENGINE_COMMON_CLOSURES_H
#define GRPC_SRC_CORE_LIB_EVENT_ENGINE_COMMON_CLOSURES_H

#include <grpc/event_engine/event_engine.h>
#include <grpc/support/port_platform.h>

#include <utility>

#include "absl/functional/any_invocable.h"

namespace grpc_event_engine::experimental {

class AnyInvocableClosure : public EventEngine::Closure {
 public:
  explicit AnyInvocableClosure(absl::AnyInvocable<void()> cb)
      : cb_(std::move(cb)) {}
  void Run() override { cb_(); }

 private:
  absl::AnyInvocable<void()> cb_;
};

class SelfDeletingClosure : public EventEngine::Closure {
 public:

  static Closure* Create(absl::AnyInvocable<void()> cb) {
    return new SelfDeletingClosure(std::move(cb), nullptr);
  }

  static Closure* Create(absl::AnyInvocable<void()> cb,
                         absl::AnyInvocable<void()> dest_cb) {
    return new SelfDeletingClosure(std::move(cb), std::move(dest_cb));
  }
  ~SelfDeletingClosure() override {
    if (dest_cb_) dest_cb_();
  };

  void Run() override {
    cb_();
    delete this;
  }

 private:
  explicit SelfDeletingClosure(absl::AnyInvocable<void()> cb,
                               absl::AnyInvocable<void()> dest_cb)
      : cb_(std::move(cb)), dest_cb_(std::move(dest_cb)) {}
  absl::AnyInvocable<void()> cb_;
  absl::AnyInvocable<void()> dest_cb_;
};

}

#endif
