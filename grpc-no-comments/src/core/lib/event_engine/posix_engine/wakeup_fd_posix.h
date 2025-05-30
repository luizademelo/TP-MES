// Copyright 2022 The gRPC Authors

#ifndef GRPC_SRC_CORE_LIB_EVENT_ENGINE_POSIX_ENGINE_WAKEUP_FD_POSIX_H
#define GRPC_SRC_CORE_LIB_EVENT_ENGINE_POSIX_ENGINE_WAKEUP_FD_POSIX_H

#include <grpc/support/port_platform.h>

#include "absl/status/status.h"

namespace grpc_event_engine::experimental {

class WakeupFd {
 public:
  virtual absl::Status ConsumeWakeup() = 0;
  virtual absl::Status Wakeup() = 0;
  virtual ~WakeupFd() = default;

  int ReadFd() { return read_fd_; }
  int WriteFd() { return write_fd_; }

 protected:
  WakeupFd() : read_fd_(0), write_fd_(0) {}
  void SetWakeupFds(int read_fd, int write_fd) {
    read_fd_ = read_fd;
    write_fd_ = write_fd;
  }

 private:
  int read_fd_;
  int write_fd_;
};

}

#endif
