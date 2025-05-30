// Copyright 2021 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_PROMISE_EXEC_CTX_WAKEUP_SCHEDULER_H
#define GRPC_SRC_CORE_LIB_PROMISE_EXEC_CTX_WAKEUP_SCHEDULER_H

#include <grpc/support/port_platform.h>

#include "absl/status/status.h"
#include "src/core/lib/iomgr/closure.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/util/debug_location.h"

namespace grpc_core {

class ExecCtxWakeupScheduler {
 public:
  template <typename ActivityType>
  class BoundScheduler {
   protected:
    explicit BoundScheduler(ExecCtxWakeupScheduler) {}
    BoundScheduler(const BoundScheduler&) = delete;
    BoundScheduler& operator=(const BoundScheduler&) = delete;
    void ScheduleWakeup() {
      GRPC_CLOSURE_INIT(
          &closure_,
          [](void* arg, grpc_error_handle) {
            static_cast<ActivityType*>(arg)->RunScheduledWakeup();
          },
          static_cast<ActivityType*>(this), nullptr);
      ExecCtx::Run(DEBUG_LOCATION, &closure_, absl::OkStatus());
    }

   private:
    grpc_closure closure_;
  };
};

}

#endif
