Here's the commented version of the code:

```c++
// Copyright 2022 The gRPC Authors

#include <grpc/support/port_platform.h>

#include <memory>
#include <utility>

#include "absl/strings/str_cat.h"
#include "src/core/lib/iomgr/port.h"
#include "src/core/util/crash.h"

#ifdef GRPC_POSIX_WAKEUP_FD
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#include "src/core/lib/event_engine/posix_engine/wakeup_fd_posix.h"
#endif

#include "src/core/lib/event_engine/posix_engine/wakeup_fd_pipe.h"
#include "src/core/util/strerror.h"

namespace grpc_event_engine::experimental {

#ifdef GRPC_POSIX_WAKEUP_FD

namespace {

// Helper function to set a file descriptor to non-blocking mode
// Args:
//   fd: The file descriptor to modify
// Returns:
//   absl::OkStatus on success, or an error status if fcntl operations fail
absl::Status SetSocketNonBlocking(int fd) {
  int oldflags = fcntl(fd, F_GETFL, 0);
  if (oldflags < 0) {
    return absl::Status(absl::StatusCode::kInternal,
                        absl::StrCat("fcntl: ", grpc_core::StrError(errno)));
  }

  oldflags |= O_NONBLOCK;

  if (fcntl(fd, F_SETFL, oldflags) != 0) {
    return absl::Status(absl::StatusCode::kInternal,
                        absl::StrCat("fcntl: ", grpc_core::StrError(errno)));
  }

  return absl::OkStatus();
}
}

// Initializes a pipe-based wakeup file descriptor
// Creates a pipe and sets both ends to non-blocking mode
// Returns:
//   absl::OkStatus on success, or an error status if pipe creation or
//   non-blocking setup fails
absl::Status PipeWakeupFd::Init() {
  int pipefd[2];
  int r = pipe(pipefd);
  if (0 != r) {
    return absl::Status(absl::StatusCode::kInternal,
                        absl::StrCat("pipe: ", grpc_core::StrError(errno)));
  }
  auto status = SetSocketNonBlocking(pipefd[0]);
  if (!status.ok()) {
    close(pipefd[0]);
    close(pipefd[1]);
    return status;
  }
  status = SetSocketNonBlocking(pipefd[1]);
  if (!status.ok()) {
    close(pipefd[0]);
    close(pipefd[1]);
    return status;
  }
  SetWakeupFds(pipefd[0], pipefd[1]);
  return absl::OkStatus();
}

// Consumes data from the wakeup pipe by reading until empty
// Returns:
//   absl::OkStatus on success or when no data is available (EAGAIN)
//   Error status if read fails for reasons other than EAGAIN or EINTR
absl::Status PipeWakeupFd::ConsumeWakeup() {
  char buf[128];
  ssize_t r;

  for (;;) {
    r = read(ReadFd(), buf, sizeof(buf));
    if (r > 0) continue;  // More data available, keep reading
    if (r == 0) return absl::OkStatus();  // EOF reached
    switch (errno) {
      case EAGAIN:
        return absl::OkStatus();  // No more data available
      case EINTR:
        continue;  // Interrupted, try again
      default:
        return absl::Status(absl::StatusCode::kInternal,
                            absl::StrCat("read: ", grpc_core::StrError(errno)));
    }
  }
}

// Writes a wakeup signal to the pipe
// Returns:
//   absl::OkStatus on success (data written or EINTR handled)
absl::Status PipeWakeupFd::Wakeup() {
  char c = 0;
  while (write(WriteFd(), &c, 1) != 1 && errno == EINTR) {
    // Retry if interrupted by signal
  }
  return absl::OkStatus();
}

// Destructor - closes both ends of the pipe if they're open
PipeWakeupFd::~PipeWakeupFd() {
  if (ReadFd() != 0) {
    close(ReadFd());
  }
  if (WriteFd() != 0) {
    close(WriteFd());
  }
}

// Checks if pipe-based wakeup FDs are supported on this platform
// Returns:
//   true if pipe creation and setup succeeds, false otherwise
bool PipeWakeupFd::IsSupported() {
  PipeWakeupFd pipe_wakeup_fd;
  return pipe_wakeup_fd.Init().ok();
}

// Factory method to create a pipe-based wakeup FD
// Returns:
//   A unique_ptr to a PipeWakeupFd on success
//   An error status if pipe wakeup FDs are not supported or initialization fails
absl::StatusOr<std::unique_ptr<WakeupFd>> PipeWakeupFd::CreatePipeWakeupFd() {
  static bool kIsPipeWakeupFdSupported = PipeWakeupFd::IsSupported();
  if (kIsPipeWakeupFdSupported) {
    auto pipe_wakeup_fd = std::make_unique<PipeWakeupFd>();
    auto status = pipe_wakeup_fd->Init();
    if (status.ok()) {
      return std::unique_ptr<WakeupFd>(std::move(pipe_wakeup_fd));
    }
    return status;
  }
  return absl::NotFoundError("Pipe wakeup fd is not supported");
}

#else

// Stub implementations for non-POSIX platforms

absl::Status PipeWakeupFd::Init() { grpc_core::Crash("unimplemented"); }

absl::Status PipeWakeupFd::ConsumeWakeup() {
  grpc_core::Crash("unimplemented");
}

absl::Status PipeWakeupFd::Wakeup() { grpc_core::Crash("unimplemented"); }

bool PipeWakeupFd::IsSupported() { return false; }

absl::StatusOr<std::unique_ptr<WakeupFd>> PipeWakeupFd::CreatePipeWakeupFd() {
  return absl::NotFoundError("Pipe wakeup fd is not supported");
}

#endif

}  // namespace grpc_event_engine::experimental
```