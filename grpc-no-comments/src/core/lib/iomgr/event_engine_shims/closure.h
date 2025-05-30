// Copyright 2022 gRPC Authors

#ifndef GRPC_SRC_CORE_LIB_IOMGR_EVENT_ENGINE_SHIMS_CLOSURE_H
#define GRPC_SRC_CORE_LIB_IOMGR_EVENT_ENGINE_SHIMS_CLOSURE_H

#include <grpc/event_engine/event_engine.h>
#include <grpc/support/port_platform.h>

#include "absl/functional/any_invocable.h"
#include "src/core/lib/iomgr/closure.h"
#include "src/core/lib/iomgr/error.h"

namespace grpc_event_engine {
namespace experimental {

void RunEventEngineClosure(grpc_closure* closure, grpc_error_handle error);

absl::AnyInvocable<void(absl::Status)> GrpcClosureToStatusCallback(
    grpc_closure* closure);

}
}

#endif
