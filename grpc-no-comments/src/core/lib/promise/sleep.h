// Copyright 2022 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_PROMISE_SLEEP_H
#define GRPC_SRC_CORE_LIB_PROMISE_SLEEP_H

#include <grpc/event_engine/event_engine.h>
#include <grpc/support/port_platform.h>

#include <atomic>
#include <utility>

#include "absl/status/status.h"
#include "src/core/lib/promise/activity.h"
#include "src/core/lib/promise/poll.h"
#include "src/core/util/time.h"

namespace grpc_core {

class Sleep final {
 public:
  explicit Sleep(Timestamp deadline);
  explicit Sleep(Duration timeout) : Sleep(Timestamp::Now() + timeout) {}
  ~Sleep();

  Sleep(const Sleep&) = delete;
  Sleep& operator=(const Sleep&) = delete;
  Sleep(Sleep&& other) noexcept
      : deadline_(other.deadline_),
        closure_(std::exchange(other.closure_, nullptr)) {}
  Sleep& operator=(Sleep&& other) noexcept {
    deadline_ = other.deadline_;
    std::swap(closure_, other.closure_);
    return *this;
  };

  Poll<absl::Status> operator()();

 private:
  class ActiveClosure final
      : public grpc_event_engine::experimental::EventEngine::Closure {
   public:
    explicit ActiveClosure(Timestamp deadline);

    void Run() override;

    void Cancel();

    bool HasRun() const;

   private:
    bool Unref();

    Waker waker_;

    std::atomic<int> refs_{2};
    std::shared_ptr<grpc_event_engine::experimental::EventEngine> event_engine_;
    grpc_event_engine::experimental::EventEngine::TaskHandle timer_handle_;
  };

  Timestamp deadline_;
  ActiveClosure* closure_{nullptr};
};

}

#endif
