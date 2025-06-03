Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

#include <grpc/support/port_platform.h>

#include "src/core/lib/iomgr/port.h"

#ifdef GRPC_POSIX_WAKEUP_FD  // Only compile this code if POSIX wakeup FD is supported

#include <errno.h>
#include <string.h>
#include <unistd.h>

#include "absl/log/log.h"
#include "src/core/lib/iomgr/socket_utils_posix.h"
#include "src/core/lib/iomgr/wakeup_fd_pipe.h"
#include "src/core/lib/iomgr/wakeup_fd_posix.h"
#include "src/core/util/crash.h"
#include "src/core/util/strerror.h"

// Initializes a pipe-based wakeup file descriptor
// Args:
//   fd_info: Pointer to the wakeup file descriptor structure to initialize
// Returns:
//   grpc_error_handle: OK on success, or error status if initialization fails
static grpc_error_handle pipe_init(grpc_wakeup_fd* fd_info) {
  int pipefd[2];
  int r = pipe(pipefd);
  if (0 != r) {
    LOG(ERROR) << "pipe creation failed (" << errno
               << "): " << grpc_core::StrError(errno);
    return GRPC_OS_ERROR(errno, "pipe");
  }
  
  grpc_error_handle err;
  // Set read end of pipe to non-blocking mode
  err = grpc_set_socket_nonblocking(pipefd[0], 1);
  if (!err.ok()) {
    close(pipefd[0]);
    close(pipefd[1]);
    return err;
  }
  
  // Set write end of pipe to non-blocking mode
  err = grpc_set_socket_nonblocking(pipefd[1], 1);
  if (!err.ok()) {
    close(pipefd[0]);
    close(pipefd[1]);
    return err;
  }
  
  // Store pipe file descriptors in wakeup fd structure
  fd_info->read_fd = pipefd[0];
  fd_info->write_fd = pipefd[1];
  return absl::OkStatus();
}

// Consumes data from the wakeup pipe (reads until empty)
// Args:
//   fd_info: Pointer to the wakeup file descriptor structure
// Returns:
//   grpc_error_handle: OK on success, or error status if read fails
static grpc_error_handle pipe_consume(grpc_wakeup_fd* fd_info) {
  char buf[128];
  ssize_t r;

  for (;;) {
    r = read(fd_info->read_fd, buf, sizeof(buf));
    if (r > 0) continue;  // More data available, keep reading
    if (r == 0) return absl::OkStatus();  // Pipe closed, return OK
    switch (errno) {
      case EAGAIN:  // No more data available
        return absl::OkStatus();
      case EINTR:   // Interrupted by signal, try again
        continue;
      default:      // Actual error occurred
        return GRPC_OS_ERROR(errno, "read");
    }
  }
}

// Writes to the wakeup pipe to trigger a wakeup
// Args:
//   fd_info: Pointer to the wakeup file descriptor structure
// Returns:
//   grpc_error_handle: Always returns OK (but may block on write)
static grpc_error_handle pipe_wakeup(grpc_wakeup_fd* fd_info) {
  char c = 0;
  // Keep trying to write if interrupted by signal
  while (write(fd_info->write_fd, &c, 1) != 1 && errno == EINTR) {
  }
  return absl::OkStatus();
}

// Cleans up and closes the pipe file descriptors
// Args:
//   fd_info: Pointer to the wakeup file descriptor structure to destroy
static void pipe_destroy(grpc_wakeup_fd* fd_info) {
  if (fd_info->read_fd != 0) close(fd_info->read_fd);
  if (fd_info->write_fd != 0) close(fd_info->write_fd);
}

// Checks if pipe-based wakeup is available on this system
// Returns:
//   int: 1 if available, 0 if not
static int pipe_check_availability(void) {
  grpc_wakeup_fd fd;
  fd.read_fd = fd.write_fd = -1;

  // Try to create and initialize a pipe
  if (pipe_init(&fd) == absl::OkStatus()) {
    pipe_destroy(&fd);
    return 1;  // Pipe wakeup is available
  } else {
    return 0;  // Pipe wakeup is not available
  }
}

// Vtable containing pipe-based wakeup fd operations
const grpc_wakeup_fd_vtable grpc_pipe_wakeup_fd_vtable = {
    pipe_init,              // Initialization function
    pipe_consume,           // Consume function
    pipe_wakeup,            // Wakeup function
    pipe_destroy,           // Cleanup function
    pipe_check_availability // Availability check function
};

#endif  // GRPC_POSIX_WAKEUP_FD
```