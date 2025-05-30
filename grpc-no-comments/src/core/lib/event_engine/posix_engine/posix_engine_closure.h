// Copyright 2022 The gRPC Authors

#ifndef GRPC_SRC_CORE_LIB_EVENT_ENGINE_POSIX_ENGINE_POSIX_ENGINE_CLOSURE_H
#define GRPC_SRC_CORE_LIB_EVENT_ENGINE_POSIX_ENGINE_POSIX_ENGINE_CLOSURE_H
#include <grpc/event_engine/event_engine.h>
#include <grpc/support/port_platform.h>

#include <utility>

#include "absl/functional/any_invocable.h"
#include "absl/status/status.h"

namespace grpc_event_engine::experimental {

class PosixEngineClosure final
    : public grpc_event_engine::experimental::EventEngine::Closure {
 public:
  PosixEngineClosure() = default;
  PosixEngineClosure(absl::AnyInvocable<void(absl::Status)> cb,
                     bool is_permanent)
      : cb_(std::move(cb)),
        is_permanent_(is_permanent),
        status_(absl::OkStatus()) {}
  ~PosixEngineClosure() final = default;
  void SetStatus(absl::Status status) { status_ = status; }
  void Run() override {

    if (!is_permanent_) {
      cb_(std::exchange(status_, absl::OkStatus()));
      delete this;
    } else {
      cb_(std::exchange(status_, absl::OkStatus()));
    }
  }

  static PosixEngineClosure* ToPermanentClosure(
      absl::AnyInvocable<void(absl::Status)> cb) {
    return new PosixEngineClosure(std::move(cb), true);
  }

  static PosixEngineClosure* TestOnlyToClosure(
      absl::AnyInvocable<void(absl::Status)> cb) {
    return new PosixEngineClosure(std::move(cb), false);
  }

 private:
  absl::AnyInvocable<void(absl::Status)> cb_;
  bool is_permanent_ = false;
  absl::Status status_;
};

}

#endif
