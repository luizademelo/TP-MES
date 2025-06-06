
// Copyright 2015 gRPC authors.

#include "gtest/gtest.h"
#include "src/core/lib/address_utils/parse_address.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/iomgr/port.h"
#include "src/core/util/time.h"
#include "test/core/test_util/port.h"
#include "test/core/test_util/test_config.h"

#ifdef GRPC_POSIX_SOCKET_TCP_CLIENT

#include <errno.h>
#include <fcntl.h>
#include <grpc/grpc.h>
#include <grpc/support/alloc.h>
#include <grpc/support/time.h>
#include <netinet/in.h>
#include <poll.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "absl/log/log.h"
#include "src/core/lib/event_engine/channel_args_endpoint_config.h"
#include "src/core/lib/iomgr/iomgr.h"
#include "src/core/lib/iomgr/pollset_set.h"
#include "src/core/lib/iomgr/socket_utils_posix.h"
#include "src/core/lib/iomgr/tcp_client.h"
#include "src/core/lib/iomgr/timer.h"
#include "src/core/lib/resource_quota/api.h"
#include "src/core/util/crash.h"

static grpc_pollset_set* g_pollset_set;
static gpr_mu* g_mu;
static grpc_pollset* g_pollset;
static int g_connections_complete = 0;
static grpc_endpoint* g_connecting = nullptr;

static grpc_core::Timestamp test_deadline(void) {
  return grpc_core::Timestamp::FromTimespecRoundUp(
      grpc_timeout_seconds_to_deadline(10));
}

static void finish_connection() {
  gpr_mu_lock(g_mu);
  g_connections_complete++;
  grpc_core::ExecCtx exec_ctx;
  ASSERT_TRUE(
      GRPC_LOG_IF_ERROR("pollset_kick", grpc_pollset_kick(g_pollset, nullptr)));

  gpr_mu_unlock(g_mu);
}

static void must_succeed(void* , grpc_error_handle error) {
  ASSERT_NE(g_connecting, nullptr);
  ASSERT_TRUE(error.ok());
  grpc_endpoint_destroy(g_connecting);
  g_connecting = nullptr;
  finish_connection();
}

static void must_fail(void* , grpc_error_handle error) {
  ASSERT_EQ(g_connecting, nullptr);
  ASSERT_FALSE(error.ok());
  finish_connection();
}

void test_succeeds(void) {
  LOG(ERROR) << "---- starting test_succeeds() ----";
  grpc_resolved_address resolved_addr;
  struct sockaddr_in* addr =
      reinterpret_cast<struct sockaddr_in*>(resolved_addr.addr);
  int svr_fd;
  int r;
  int connections_complete_before;
  grpc_closure done;
  grpc_core::ExecCtx exec_ctx;

  memset(&resolved_addr, 0, sizeof(resolved_addr));
  resolved_addr.len = static_cast<socklen_t>(sizeof(struct sockaddr_in));
  addr->sin_family = AF_INET;

  svr_fd = socket(AF_INET, SOCK_STREAM, 0);
  ASSERT_GE(svr_fd, 0);
  ASSERT_EQ(bind(svr_fd, (struct sockaddr*)addr, (socklen_t)resolved_addr.len),
            0);
  ASSERT_EQ(listen(svr_fd, 1), 0);

  gpr_mu_lock(g_mu);
  connections_complete_before = g_connections_complete;
  gpr_mu_unlock(g_mu);

  ASSERT_EQ(getsockname(svr_fd, (struct sockaddr*)addr,
                        (socklen_t*)&resolved_addr.len),
            0);
  GRPC_CLOSURE_INIT(&done, must_succeed, nullptr, grpc_schedule_on_exec_ctx);
  grpc_core::ChannelArgs args = grpc_core::CoreConfiguration::Get()
                                    .channel_args_preconditioning()
                                    .PreconditionChannelArgs(nullptr);
  int64_t connection_handle = grpc_tcp_client_connect(
      &done, &g_connecting, g_pollset_set,
      grpc_event_engine::experimental::ChannelArgsEndpointConfig(args),
      &resolved_addr, grpc_core::Timestamp::InfFuture());

  do {
    resolved_addr.len = static_cast<socklen_t>(sizeof(addr));
    r = accept(svr_fd, reinterpret_cast<struct sockaddr*>(addr),
               reinterpret_cast<socklen_t*>(&resolved_addr.len));
  } while (r == -1 && errno == EINTR);
  ASSERT_GE(r, 0);
  close(r);

  gpr_mu_lock(g_mu);

  while (g_connections_complete == connections_complete_before) {
    grpc_pollset_worker* worker = nullptr;
    ASSERT_TRUE(GRPC_LOG_IF_ERROR(
        "pollset_work",
        grpc_pollset_work(g_pollset, &worker,
                          grpc_core::Timestamp::FromTimespecRoundUp(
                              grpc_timeout_seconds_to_deadline(5)))));
    gpr_mu_unlock(g_mu);
    grpc_core::ExecCtx::Get()->Flush();
    gpr_mu_lock(g_mu);
  }

  gpr_mu_unlock(g_mu);

  ASSERT_EQ(grpc_tcp_client_cancel_connect(connection_handle), false);

  LOG(ERROR) << "---- finished test_succeeds() ----";
}

void test_fails(void) {
  LOG(ERROR) << "---- starting test_fails() ----";
  grpc_resolved_address resolved_addr;
  struct sockaddr_in* addr =
      reinterpret_cast<struct sockaddr_in*>(resolved_addr.addr);
  int connections_complete_before;
  grpc_closure done;
  grpc_core::ExecCtx exec_ctx;

  memset(&resolved_addr, 0, sizeof(resolved_addr));
  resolved_addr.len = static_cast<socklen_t>(sizeof(struct sockaddr_in));
  addr->sin_family = AF_INET;

  gpr_mu_lock(g_mu);
  connections_complete_before = g_connections_complete;
  gpr_mu_unlock(g_mu);

  GRPC_CLOSURE_INIT(&done, must_fail, nullptr, grpc_schedule_on_exec_ctx);
  int64_t connection_handle = grpc_tcp_client_connect(
      &done, &g_connecting, g_pollset_set,
      grpc_event_engine::experimental::ChannelArgsEndpointConfig(),
      &resolved_addr, grpc_core::Timestamp::InfFuture());
  gpr_mu_lock(g_mu);

  while (g_connections_complete == connections_complete_before) {
    grpc_pollset_worker* worker = nullptr;
    grpc_core::Timestamp polling_deadline = test_deadline();
    switch (grpc_timer_check(&polling_deadline)) {
      case GRPC_TIMERS_FIRED:
        break;
      case GRPC_TIMERS_NOT_CHECKED:
        polling_deadline = grpc_core::Timestamp::ProcessEpoch();
        [[fallthrough]];
      case GRPC_TIMERS_CHECKED_AND_EMPTY:
        ASSERT_TRUE(GRPC_LOG_IF_ERROR(
            "pollset_work",
            grpc_pollset_work(g_pollset, &worker, polling_deadline)));
        break;
    }
    gpr_mu_unlock(g_mu);
    grpc_core::ExecCtx::Get()->Flush();
    gpr_mu_lock(g_mu);
  }

  gpr_mu_unlock(g_mu);

  ASSERT_EQ(grpc_tcp_client_cancel_connect(connection_handle), false);

  LOG(ERROR) << "---- finished test_fails() ----";
}

void test_connect_cancellation_succeeds(void) {
  LOG(ERROR) << "---- starting test_connect_cancellation_succeeds() ----";
  auto target_ipv6_addr_uri = *grpc_core::URI::Parse(absl::StrCat(
      "ipv6:[::1]:", std::to_string(grpc_pick_unused_port_or_die())));
  auto target_ipv4_addr_uri = *grpc_core::URI::Parse(absl::StrCat(
      "ipv4:127.0.0.1:", std::to_string(grpc_pick_unused_port_or_die())));
  grpc_resolved_address resolved_addr;
  int svr_fd;
  grpc_closure done;
  grpc_core::ExecCtx exec_ctx;
  bool tried_ipv4 = false;
  ASSERT_TRUE(grpc_parse_uri(target_ipv6_addr_uri, &resolved_addr));
  auto try_bind = [&](int sock) {
    return (sock >= 0 &&
            bind(sock, reinterpret_cast<sockaddr*>(resolved_addr.addr),
                 resolved_addr.len) == 0);
  };

  svr_fd = socket(AF_INET6, SOCK_STREAM, 0);

  if (!try_bind(svr_fd)) {
    if (svr_fd >= 0) {
      close(svr_fd);
    }

    ASSERT_TRUE(grpc_parse_uri(target_ipv4_addr_uri, &resolved_addr));
    svr_fd = socket(AF_INET, SOCK_STREAM, 0);
    tried_ipv4 = true;
    if (!try_bind(svr_fd)) {
      if (svr_fd >= 0) {
        close(svr_fd);
      }
      LOG(ERROR) << "Skipping test. Failed to create a phony server bound to "
                    "ipv6 or ipv4 address";
      return;
    }
  }

  ASSERT_EQ(listen(svr_fd, 1), 0);

  std::vector<int> client_sockets;
  bool create_more_client_connections = true;

  while (create_more_client_connections) {
    const int kOne = 1;
    int client_socket = socket(tried_ipv4 ? AF_INET : AF_INET6, SOCK_STREAM, 0);
    ASSERT_GE(client_socket, 0);
    setsockopt(client_socket, SOL_SOCKET, SO_REUSEADDR, &kOne, sizeof(kOne));

    int flags = fcntl(client_socket, F_GETFL, 0);
    ASSERT_EQ(fcntl(client_socket, F_SETFL, flags | O_NONBLOCK), 0);

    if (connect(client_socket, reinterpret_cast<sockaddr*>(resolved_addr.addr),
                resolved_addr.len) == -1) {
      if (errno == EINPROGRESS) {
        struct pollfd pfd;
        pfd.fd = client_socket;
        pfd.events = POLLOUT;
        pfd.revents = 0;
        int ret = poll(&pfd, 1, 1000);
        if (ret == -1) {
          FAIL() << "poll() failed during connect; errno=" << errno;
        } else if (ret == 0) {

          create_more_client_connections = false;
        }
      } else {
        FAIL() << "Failed to connect to the server. errno=%d" << errno;
      }
    }
    client_sockets.push_back(client_socket);
  }

  ASSERT_EQ(getsockname(svr_fd, reinterpret_cast<sockaddr*>(resolved_addr.addr),
                        (socklen_t*)&resolved_addr.len),
            0);
  GRPC_CLOSURE_INIT(&done, must_succeed, nullptr, grpc_schedule_on_exec_ctx);
  grpc_core::ChannelArgs args = grpc_core::CoreConfiguration::Get()
                                    .channel_args_preconditioning()
                                    .PreconditionChannelArgs(nullptr);
  int64_t connection_handle = grpc_tcp_client_connect(
      &done, &g_connecting, g_pollset_set,
      grpc_event_engine::experimental::ChannelArgsEndpointConfig(args),
      &resolved_addr, grpc_core::Timestamp::InfFuture());
  ASSERT_GT(connection_handle, 0);
  ASSERT_EQ(grpc_tcp_client_cancel_connect(connection_handle), true);
  for (auto sock : client_sockets) {
    close(sock);
  }
  close(svr_fd);
  LOG(ERROR) << "---- finished test_connect_cancellation_succeeds() ----";
}

void test_fails_bad_addr_no_leak(void) {
  LOG(ERROR) << "---- starting test_fails_bad_addr_no_leak() ----";
  grpc_resolved_address resolved_addr;
  struct sockaddr_in* addr =
      reinterpret_cast<struct sockaddr_in*>(resolved_addr.addr);
  int connections_complete_before;
  grpc_closure done;
  grpc_core::ExecCtx exec_ctx;
  memset(&resolved_addr, 0, sizeof(resolved_addr));
  resolved_addr.len = static_cast<socklen_t>(sizeof(struct sockaddr_in));

  addr->sin_family = AF_IPX;
  gpr_mu_lock(g_mu);
  connections_complete_before = g_connections_complete;
  gpr_mu_unlock(g_mu);

  GRPC_CLOSURE_INIT(&done, must_fail, nullptr, grpc_schedule_on_exec_ctx);
  grpc_tcp_client_connect(
      &done, &g_connecting, g_pollset_set,
      grpc_event_engine::experimental::ChannelArgsEndpointConfig(),
      &resolved_addr, grpc_core::Timestamp::InfFuture());
  gpr_mu_lock(g_mu);
  while (g_connections_complete == connections_complete_before) {
    grpc_pollset_worker* worker = nullptr;
    grpc_core::Timestamp polling_deadline = test_deadline();
    switch (grpc_timer_check(&polling_deadline)) {
      case GRPC_TIMERS_FIRED:
        break;
      case GRPC_TIMERS_NOT_CHECKED:
        polling_deadline = grpc_core::Timestamp::ProcessEpoch();
        [[fallthrough]];
      case GRPC_TIMERS_CHECKED_AND_EMPTY:
        ASSERT_TRUE(GRPC_LOG_IF_ERROR(
            "pollset_work",
            grpc_pollset_work(g_pollset, &worker, polling_deadline)));
        break;
    }
    gpr_mu_unlock(g_mu);
    grpc_core::ExecCtx::Get()->Flush();
    gpr_mu_lock(g_mu);
  }
  gpr_mu_unlock(g_mu);
  LOG(ERROR) << "---- finished test_fails_bad_addr_no_leak() ----";
}

static void destroy_pollset(void* p, grpc_error_handle ) {
  grpc_pollset_destroy(static_cast<grpc_pollset*>(p));
}

TEST(TcpClientPosixTest, MainTest) {
  grpc_closure destroyed;
  grpc_init();

  {
    grpc_core::ExecCtx exec_ctx;
    g_pollset_set = grpc_pollset_set_create();
    g_pollset = static_cast<grpc_pollset*>(gpr_zalloc(grpc_pollset_size()));
    grpc_pollset_init(g_pollset, &g_mu);
    grpc_pollset_set_add_pollset(g_pollset_set, g_pollset);

    test_succeeds();
    test_connect_cancellation_succeeds();
    test_fails();
    test_fails_bad_addr_no_leak();
    grpc_pollset_set_destroy(g_pollset_set);
    GRPC_CLOSURE_INIT(&destroyed, destroy_pollset, g_pollset,
                      grpc_schedule_on_exec_ctx);
    grpc_pollset_shutdown(g_pollset, &destroyed);
  }

  grpc_shutdown();
  gpr_free(g_pollset);
}

#endif

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
