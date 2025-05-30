// Copyright 2022 gRPC Authors

#include <errno.h>
#include <fcntl.h>
#include <grpc/event_engine/event_engine.h>
#include <grpc/grpc.h>
#include <grpc/impl/channel_arg_names.h>
#include <poll.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

#include <algorithm>
#include <chrono>
#include <cstring>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/memory/memory.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_format.h"
#include "gtest/gtest.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/event_engine/channel_args_endpoint_config.h"
#include "src/core/lib/event_engine/posix_engine/posix_engine.h"
#include "src/core/lib/event_engine/tcp_socket_utils.h"
#include "src/core/lib/resource_quota/memory_quota.h"
#include "src/core/lib/resource_quota/resource_quota.h"
#include "src/core/util/crash.h"
#include "src/core/util/notification.h"
#include "src/core/util/wait_for_single_owner.h"
#include "test/core/event_engine/event_engine_test_utils.h"
#include "test/core/test_util/port.h"
#include "test/core/test_util/test_config.h"

namespace grpc_event_engine {
namespace experimental {

using namespace std::chrono_literals;

namespace {

std::vector<int> CreateConnectedSockets(
    EventEngine::ResolvedAddress resolved_addr) {
  int server_socket;
  int opt = -1;
  int client_socket;
  int one = 1;
  int flags;
  std::vector<int> ret_sockets;

  if ((server_socket = socket(AF_INET6, SOCK_STREAM, 0)) <= 0) {
    grpc_core::Crash(
        absl::StrFormat("Error creating socket: %s", std::strerror(errno)));
  }

  if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
    grpc_core::Crash(absl::StrFormat("Error setsockopt(SO_REUSEADDR): %s",
                                     std::strerror(errno)));
  }
  if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt))) {
    grpc_core::Crash(absl::StrFormat("Error setsockopt(SO_REUSEPORT): %s",
                                     std::strerror(errno)));
  }

  if (bind(server_socket, resolved_addr.address(), resolved_addr.size()) < 0) {
    grpc_core::Crash(absl::StrFormat("Error bind: %s", std::strerror(errno)));
  }

  if (listen(server_socket, 1) < 0) {
    grpc_core::Crash(absl::StrFormat("Error listen: %s", std::strerror(errno)));
  }
  ret_sockets.push_back(server_socket);

  while (true) {
    client_socket = socket(AF_INET6, SOCK_STREAM, 0);
    setsockopt(client_socket, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));

    flags = fcntl(client_socket, F_GETFL, 0);
    EXPECT_EQ(fcntl(client_socket, F_SETFL, flags | O_NONBLOCK), 0);

    if (connect(client_socket,
                const_cast<struct sockaddr*>(resolved_addr.address()),
                resolved_addr.size()) == -1) {
      if (errno == EINPROGRESS) {
        struct pollfd pfd;
        pfd.fd = client_socket;
        pfd.events = POLLOUT;
        pfd.revents = 0;
        int ret = poll(&pfd, 1, 1000);
        if (ret == -1) {
          LOG(ERROR) << "poll() failed during connect; errno=" << errno;
          abort();
        } else if (ret == 0) {

          ret_sockets.push_back(client_socket);
          return ret_sockets;
        }
      } else {
        grpc_core::Crash(absl::StrFormat(
            "Failed to connect to the server (errno=%d)", errno));
      }
    }
    ret_sockets.push_back(client_socket);
  }
  return ret_sockets;
}

}

TEST(PosixEventEngineTest, IndefiniteConnectTimeoutOrRstTest) {
  std::string target_addr = absl::StrCat(
      "ipv6:[::1]:", std::to_string(grpc_pick_unused_port_or_die()));
  auto resolved_addr = URIToResolvedAddress(target_addr);
  CHECK_OK(resolved_addr);
  std::shared_ptr<EventEngine> posix_ee =
      PosixEventEngine::MakePosixEventEngine();
  std::string resolved_addr_str =
      ResolvedAddressToNormalizedString(*resolved_addr).value();
  auto sockets = CreateConnectedSockets(*resolved_addr);
  grpc_core::Notification signal;
  grpc_core::ChannelArgs args;
  auto quota = grpc_core::ResourceQuota::Default();
  args = args.Set(GRPC_ARG_RESOURCE_QUOTA, quota);
  ChannelArgsEndpointConfig config(args);
  auto memory_quota = absl::make_unique<grpc_core::MemoryQuota>("bar");
  posix_ee->Connect(
      [&signal](absl::StatusOr<std::unique_ptr<EventEngine::Endpoint>> status) {
        EXPECT_EQ(status.status().code(), absl::StatusCode::kUnknown);
        signal.Notify();
      },
      *resolved_addr, config, memory_quota->CreateMemoryAllocator("conn-1"),
      3s);
  signal.WaitForNotification();
  for (auto sock : sockets) {
    close(sock);
  }
  grpc_core::WaitForSingleOwner(std::move(posix_ee));
}

TEST(PosixEventEngineTest, IndefiniteConnectCancellationTest) {
  std::string target_addr = absl::StrCat(
      "ipv6:[::1]:", std::to_string(grpc_pick_unused_port_or_die()));
  auto resolved_addr = URIToResolvedAddress(target_addr);
  CHECK_OK(resolved_addr);
  std::shared_ptr<EventEngine> posix_ee =
      PosixEventEngine::MakePosixEventEngine();
  std::string resolved_addr_str =
      ResolvedAddressToNormalizedString(*resolved_addr).value();
  auto sockets = CreateConnectedSockets(*resolved_addr);
  grpc_core::ChannelArgs args;
  auto quota = grpc_core::ResourceQuota::Default();
  args = args.Set(GRPC_ARG_RESOURCE_QUOTA, quota);
  ChannelArgsEndpointConfig config(args);
  auto memory_quota = absl::make_unique<grpc_core::MemoryQuota>("bar");
  auto connection_handle = posix_ee->Connect(
      [](absl::StatusOr<std::unique_ptr<EventEngine::Endpoint>> ) {
        FAIL() << "The on_connect callback should not have run since the "
                  "connection attempt was cancelled.";
      },
      *resolved_addr, config, memory_quota->CreateMemoryAllocator("conn-2"),
      3s);
  if (connection_handle.keys[0] > 0) {
    ASSERT_TRUE(posix_ee->CancelConnect(connection_handle));
  }
  for (auto sock : sockets) {
    close(sock);
  }
  grpc_core::WaitForSingleOwner(std::move(posix_ee));
}

}
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  grpc_init();
  int ret = RUN_ALL_TESTS();
  grpc_shutdown();
  return ret;
}
