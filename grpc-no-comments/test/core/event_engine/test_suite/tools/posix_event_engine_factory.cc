// Copyright 2023 gRPC authors.

#include <grpc/event_engine/event_engine.h>
#include <grpc/support/port_platform.h>

#include <memory>

#include "absl/functional/any_invocable.h"
#include "absl/log/check.h"
#include "src/core/lib/iomgr/port.h"

#ifdef GRPC_POSIX_SOCKET_TCP

#include "src/core/lib/event_engine/posix_engine/posix_engine.h"

absl::AnyInvocable<
    std::shared_ptr<grpc_event_engine::experimental::EventEngine>(void)>
CustomEventEngineFactory() {
  return []() {
    return grpc_event_engine::experimental::PosixEventEngine::
        MakePosixEventEngine();
  };
}

#else

absl::AnyInvocable<
    std::unique_ptr<grpc_event_engine::experimental::EventEngine>(void)>
CustomEventEngineFactory() {
  CHECK(false) <<  "This tool was not built for Posix environments.");
}

#endif
