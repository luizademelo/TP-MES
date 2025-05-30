// Copyright 2022 The gRPC Authors

#include <grpc/support/port_platform.h>

#include <utility>

#include "absl/strings/str_cat.h"
#include "src/core/lib/iomgr/port.h"
#include "src/core/util/crash.h"

#ifdef GRPC_LINUX_EVENTFD

#include <errno.h>
#include <sys/eventfd.h>
#include <unistd.h>

#include "src/core/lib/event_engine/posix_engine/wakeup_fd_posix.h"
#endif

#include "src/core/lib/event_engine/posix_engine/wakeup_fd_eventfd.h"
#include "src/core/util/strerror.h"

namespace grpc_event_engine::experimental {

#ifdef GRPC_LINUX_EVENTFD

absl::Status EventFdWakeupFd::Init() {
  int read_fd = eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
  int write_fd = -1;
  if (read_fd < 0) {
    return absl::Status(absl::StatusCode::kInternal,
                        absl::StrCat("eventfd: ", grpc_core::StrError(errno)));
  }
  SetWakeupFds(read_fd, write_fd);
  return absl::OkStatus();
}

absl::Status EventFdWakeupFd::ConsumeWakeup() {
  eventfd_t value;
  int err;
  do {
    err = eventfd_read(ReadFd(), &value);
  } while (err < 0 && errno == EINTR);
  if (err < 0 && errno != EAGAIN) {
    return absl::Status(
        absl::StatusCode::kInternal,
        absl::StrCat("eventfd_read: ", grpc_core::StrError(errno)));
  }
  return absl::OkStatus();
}

absl::Status EventFdWakeupFd::Wakeup() {
  int err;
  do {
    err = eventfd_write(ReadFd(), 1);
  } while (err < 0 && errno == EINTR);
  if (err < 0) {
    return absl::Status(
        absl::StatusCode::kInternal,
        absl::StrCat("eventfd_write: ", grpc_core::StrError(errno)));
  }
  return absl::OkStatus();
}

EventFdWakeupFd::~EventFdWakeupFd() {
  if (ReadFd() != 0) {
    close(ReadFd());
  }
}

bool EventFdWakeupFd::IsSupported() {
  EventFdWakeupFd event_fd_wakeup_fd;
  return event_fd_wakeup_fd.Init().ok();
}

absl::StatusOr<std::unique_ptr<WakeupFd>>
EventFdWakeupFd::CreateEventFdWakeupFd() {
  static bool kIsEventFdWakeupFdSupported = EventFdWakeupFd::IsSupported();
  if (kIsEventFdWakeupFdSupported) {
    auto event_fd_wakeup_fd = std::make_unique<EventFdWakeupFd>();
    auto status = event_fd_wakeup_fd->Init();
    if (status.ok()) {
      return std::unique_ptr<WakeupFd>(std::move(event_fd_wakeup_fd));
    }
    return status;
  }
  return absl::NotFoundError("Eventfd wakeup fd is not supported");
}

#else

#include "src/core/util/crash.h"

absl::Status EventFdWakeupFd::Init() { grpc_core::Crash("unimplemented"); }

absl::Status EventFdWakeupFd::ConsumeWakeup() {
  grpc_core::Crash("unimplemented");
}

absl::Status EventFdWakeupFd::Wakeup() { grpc_core::Crash("unimplemented"); }

bool EventFdWakeupFd::IsSupported() { return false; }

absl::StatusOr<std::unique_ptr<WakeupFd>>
EventFdWakeupFd::CreateEventFdWakeupFd() {
  return absl::NotFoundError("Eventfd wakeup fd is not supported");
}

#endif

}
