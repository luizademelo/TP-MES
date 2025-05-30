// Copyright 2021 gRPC Authors

#include "src/core/lib/iomgr/event_engine_shims/closure.h"

#include <grpc/event_engine/event_engine.h>
#include <grpc/support/port_platform.h>

#include "absl/functional/any_invocable.h"
#include "absl/log/log.h"
#include "absl/status/status.h"
#include "src/core/lib/iomgr/closure.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/transport/error_utils.h"

namespace grpc_event_engine {
namespace experimental {

void RunEventEngineClosure(grpc_closure* closure, grpc_error_handle error) {
  if (closure == nullptr) {
    return;
  }
  grpc_core::ExecCtx exec_ctx;
#ifndef NDEBUG
  closure->scheduled = false;
  GRPC_TRACE_VLOG(closure, 2)
      << "EventEngine: running closure " << closure << ": created ["
      << closure->file_created << ":" << closure->line_created
      << "]: " << (closure->run ? "run" : "scheduled") << " ["
      << closure->file_initiated << ":" << closure->line_initiated << "]";
#endif
  closure->cb(closure->cb_arg, error);
#ifndef NDEBUG
  GRPC_TRACE_VLOG(closure, 2)
      << "EventEngine: closure " << closure << " finished";
#endif
}

absl::AnyInvocable<void(absl::Status)> GrpcClosureToStatusCallback(
    grpc_closure* closure) {
  return [closure](absl::Status status) {
    RunEventEngineClosure(closure, absl_status_to_grpc_error(status));
  };
}

}
}
