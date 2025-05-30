// Copyright 2021 gRPC authors.

#ifndef GRPC_TEST_CORE_PROMISE_TEST_WAKEUP_SCHEDULERS_H
#define GRPC_TEST_CORE_PROMISE_TEST_WAKEUP_SCHEDULERS_H

#include <stdlib.h>

#include <functional>

#include "gmock/gmock.h"

namespace grpc_core {

struct NoWakeupScheduler {
  template <typename ActivityType>
  class BoundScheduler {
   public:
    explicit BoundScheduler(NoWakeupScheduler) {}
    void ScheduleWakeup() { abort(); }
  };
};

struct InlineWakeupScheduler {
  template <typename ActivityType>
  class BoundScheduler {
   public:
    explicit BoundScheduler(InlineWakeupScheduler) {}
    void ScheduleWakeup() {
      static_cast<ActivityType*>(this)->RunScheduledWakeup();
    }
  };
};

class MockCallbackScheduler {
 public:
  MOCK_METHOD(void, Schedule, (std::function<void()>));
};

struct UseMockCallbackScheduler {
  MockCallbackScheduler* scheduler;
  template <typename ActivityType>
  class BoundScheduler {
   public:
    explicit BoundScheduler(UseMockCallbackScheduler use_scheduler)
        : scheduler(use_scheduler.scheduler) {}
    void ScheduleWakeup() {
      scheduler->Schedule(
          [this] { static_cast<ActivityType*>(this)->RunScheduledWakeup(); });
    }

   private:
    MockCallbackScheduler* scheduler;
  };
};

}

#endif
