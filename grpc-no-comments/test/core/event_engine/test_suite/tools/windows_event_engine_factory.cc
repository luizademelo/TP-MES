// Copyright 2022 gRPC authors.

#include <grpc/event_engine/event_engine.h>
#include <grpc/support/port_platform.h>

#include <memory>

#include "absl/functional/any_invocable.h"
#include "absl/log/check.h"

#ifdef GPR_WINDOWS

#include "src/core/lib/event_engine/windows/windows_engine.h"

absl::AnyInvocable<
    std::shared_ptr<grpc_event_engine::experimental::EventEngine>(void)>
CustomEventEngineFactory() {
  return []() {
    return std::make_shared<
        grpc_event_engine::experimental::WindowsEventEngine>();
  };
}

#else

absl::AnyInvocable<
    std::shared_ptr<grpc_event_engine::experimental::EventEngine>(void)>
CustomEventEngineFactory() {
  CHECK(false) << "This tool was not built for Windows.";
}

#endif
