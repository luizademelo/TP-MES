
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_IOMGR_RESOLVE_ADDRESS_IMPL_H
#define GRPC_SRC_CORE_LIB_IOMGR_RESOLVE_ADDRESS_IMPL_H

#include <grpc/support/port_platform.h>
#include <stddef.h>

#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/iomgr/port.h"
#include "src/core/lib/iomgr/resolve_address.h"

namespace grpc_core {

class DNSCallbackExecCtxScheduler {
 public:
  DNSCallbackExecCtxScheduler(
      std::function<void(absl::StatusOr<std::vector<grpc_resolved_address>>)>
          on_done,
      absl::StatusOr<std::vector<grpc_resolved_address>> param)
      : on_done_(std::move(on_done)), param_(std::move(param)) {
    GRPC_CLOSURE_INIT(&closure_, RunCallback, this, grpc_schedule_on_exec_ctx);
    ExecCtx::Run(DEBUG_LOCATION, &closure_, absl::OkStatus());
  }

 private:
  static void RunCallback(void* arg, grpc_error_handle ) {
    DNSCallbackExecCtxScheduler* self =
        static_cast<DNSCallbackExecCtxScheduler*>(arg);
    self->on_done_(std::move(self->param_));
    delete self;
  }

  const std::function<void(absl::StatusOr<std::vector<grpc_resolved_address>>)>
      on_done_;
  absl::StatusOr<std::vector<grpc_resolved_address>> param_;
  grpc_closure closure_;
};

}

#endif
