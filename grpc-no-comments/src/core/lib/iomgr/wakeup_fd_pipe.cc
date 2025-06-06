
// Copyright 2015 gRPC authors.

#include <grpc/support/port_platform.h>

#include "src/core/lib/iomgr/port.h"

#ifdef GRPC_POSIX_WAKEUP_FD

#include <errno.h>
#include <string.h>
#include <unistd.h>

#include "absl/log/log.h"
#include "src/core/lib/iomgr/socket_utils_posix.h"
#include "src/core/lib/iomgr/wakeup_fd_pipe.h"
#include "src/core/lib/iomgr/wakeup_fd_posix.h"
#include "src/core/util/crash.h"
#include "src/core/util/strerror.h"

static grpc_error_handle pipe_init(grpc_wakeup_fd* fd_info) {
  int pipefd[2];
  int r = pipe(pipefd);
  if (0 != r) {
    LOG(ERROR) << "pipe creation failed (" << errno
               << "): " << grpc_core::StrError(errno);
    return GRPC_OS_ERROR(errno, "pipe");
  }
  grpc_error_handle err;
  err = grpc_set_socket_nonblocking(pipefd[0], 1);
  if (!err.ok()) {
    close(pipefd[0]);
    close(pipefd[1]);
    return err;
  }
  err = grpc_set_socket_nonblocking(pipefd[1], 1);
  if (!err.ok()) {
    close(pipefd[0]);
    close(pipefd[1]);
    return err;
  }
  fd_info->read_fd = pipefd[0];
  fd_info->write_fd = pipefd[1];
  return absl::OkStatus();
}

static grpc_error_handle pipe_consume(grpc_wakeup_fd* fd_info) {
  char buf[128];
  ssize_t r;

  for (;;) {
    r = read(fd_info->read_fd, buf, sizeof(buf));
    if (r > 0) continue;
    if (r == 0) return absl::OkStatus();
    switch (errno) {
      case EAGAIN:
        return absl::OkStatus();
      case EINTR:
        continue;
      default:
        return GRPC_OS_ERROR(errno, "read");
    }
  }
}

static grpc_error_handle pipe_wakeup(grpc_wakeup_fd* fd_info) {
  char c = 0;
  while (write(fd_info->write_fd, &c, 1) != 1 && errno == EINTR) {
  }
  return absl::OkStatus();
}

static void pipe_destroy(grpc_wakeup_fd* fd_info) {
  if (fd_info->read_fd != 0) close(fd_info->read_fd);
  if (fd_info->write_fd != 0) close(fd_info->write_fd);
}

static int pipe_check_availability(void) {
  grpc_wakeup_fd fd;
  fd.read_fd = fd.write_fd = -1;

  if (pipe_init(&fd) == absl::OkStatus()) {
    pipe_destroy(&fd);
    return 1;
  } else {
    return 0;
  }
}

const grpc_wakeup_fd_vtable grpc_pipe_wakeup_fd_vtable = {
    pipe_init, pipe_consume, pipe_wakeup, pipe_destroy,
    pipe_check_availability};

#endif
