// Copyright 2022 The gRPC Authors

#ifndef GRPC_SRC_CORE_LIB_EVENT_ENGINE_POSIX_ENGINE_WAKEUP_FD_POSIX_DEFAULT_H
#define GRPC_SRC_CORE_LIB_EVENT_ENGINE_POSIX_ENGINE_WAKEUP_FD_POSIX_DEFAULT_H
#include <grpc/support/port_platform.h>

#include <memory>

#include "absl/status/statusor.h"

namespace grpc_event_engine::experimental {

class WakeupFd;

bool SupportsWakeupFd();

absl::StatusOr<std::unique_ptr<WakeupFd>> CreateWakeupFd();

}

#endif
