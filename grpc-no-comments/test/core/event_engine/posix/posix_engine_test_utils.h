// Copyright 2022 gRPC Authors

#ifndef GRPC_TEST_CORE_EVENT_ENGINE_POSIX_POSIX_ENGINE_TEST_UTILS_H
#define GRPC_TEST_CORE_EVENT_ENGINE_POSIX_POSIX_ENGINE_TEST_UTILS_H

#include <grpc/event_engine/event_engine.h>

#include <utility>

#include "absl/functional/any_invocable.h"
#include "src/core/lib/event_engine/posix_engine/event_poller.h"

namespace grpc_event_engine {
namespace experimental {

class TestScheduler : public Scheduler {
 public:
  explicit TestScheduler(grpc_event_engine::experimental::EventEngine* engine)
      : engine_(engine) {}
  TestScheduler() : engine_(nullptr) {};
  void ChangeCurrentEventEngine(
      grpc_event_engine::experimental::EventEngine* engine) {
    engine_ = engine;
  }
  void Run(experimental::EventEngine::Closure* closure) override {
    if (engine_ != nullptr) {
      engine_->Run(closure);
    } else {
      closure->Run();
    }
  }

  void Run(absl::AnyInvocable<void()> cb) override {
    if (engine_ != nullptr) {
      engine_->Run(std::move(cb));
    } else {
      cb();
    }
  }

 private:
  grpc_event_engine::experimental::EventEngine* engine_;
};

int ConnectToServerOrDie(
    const grpc_event_engine::experimental::EventEngine::ResolvedAddress&
        server_address);

}
}

#endif
