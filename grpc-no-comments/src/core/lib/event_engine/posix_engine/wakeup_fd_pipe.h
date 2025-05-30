// Copyright 2022 The gRPC Authors

#ifndef GRPC_SRC_CORE_LIB_EVENT_ENGINE_POSIX_ENGINE_WAKEUP_FD_PIPE_H
#define GRPC_SRC_CORE_LIB_EVENT_ENGINE_POSIX_ENGINE_WAKEUP_FD_PIPE_H

#include <grpc/support/port_platform.h>

#include <memory>

#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "src/core/lib/event_engine/posix_engine/wakeup_fd_posix.h"

namespace grpc_event_engine::experimental {

class PipeWakeupFd : public WakeupFd {
 public:
  PipeWakeupFd() : WakeupFd() {}
  ~PipeWakeupFd() override;
  absl::Status ConsumeWakeup() override;
  absl::Status Wakeup() override;
  static absl::StatusOr<std::unique_ptr<WakeupFd>> CreatePipeWakeupFd();
  static bool IsSupported();

 private:
  absl::Status Init();
};

}

#endif
