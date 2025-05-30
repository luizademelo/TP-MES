// Copyright 2022 gRPC Authors

#include "test/core/event_engine/posix/posix_engine_test_utils.h"

#include <errno.h>
#include <fcntl.h>
#include <poll.h>
#include <stdlib.h>
#include <sys/socket.h>

#include "absl/log/log.h"
#include "absl/strings/str_format.h"
#include "src/core/util/crash.h"

namespace grpc_event_engine {
namespace experimental {

using ResolvedAddress =
    grpc_event_engine::experimental::EventEngine::ResolvedAddress;

int ConnectToServerOrDie(const ResolvedAddress& server_address) {
  int client_fd;
  int one = 1;
  int flags;

  client_fd = socket(AF_INET6, SOCK_STREAM, 0);
  setsockopt(client_fd, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));

  flags = fcntl(client_fd, F_GETFL, 0);
  fcntl(client_fd, F_SETFL, flags | O_NONBLOCK);

  if (connect(client_fd, const_cast<struct sockaddr*>(server_address.address()),
              server_address.size()) == -1) {
    if (errno == EINPROGRESS) {
      struct pollfd pfd;
      pfd.fd = client_fd;
      pfd.events = POLLOUT;
      pfd.revents = 0;
      if (poll(&pfd, 1, -1) == -1) {
        LOG(ERROR) << "poll() failed during connect; errno=" << errno;
        abort();
      }
    } else {
      grpc_core::Crash(
          absl::StrFormat("Failed to connect to the server (errno=%d)", errno));
    }
  }
  return client_fd;
}

}
}
