
// Copyright 2015 gRPC authors.

#include "gtest/gtest.h"
#include "src/core/lib/iomgr/port.h"
#include "test/core/test_util/test_config.h"

#ifdef GRPC_POSIX_SOCKET_EV

#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <grpc/grpc.h>
#include <grpc/support/alloc.h>
#include <grpc/support/sync.h>
#include <grpc/support/time.h>
#include <netinet/in.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>

#include "absl/log/log.h"
#include "src/core/lib/event_engine/shim.h"
#include "src/core/lib/experiments/experiments.h"
#include "src/core/lib/iomgr/ev_posix.h"
#include "src/core/lib/iomgr/socket_utils_posix.h"
#include "src/core/util/strerror.h"

static gpr_mu* g_mu;
static grpc_pollset* g_pollset;

#define BUF_SIZE 1024

static void create_test_socket(int port, int* socket_fd,
                               struct sockaddr_in* sin) {
  int fd;
  int one = 1;
  int buffer_size_bytes = BUF_SIZE;
  int flags;

  fd = socket(AF_INET, SOCK_STREAM, 0);
  setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));

  ASSERT_EQ(grpc_set_socket_sndbuf(fd, buffer_size_bytes), absl::OkStatus());
  ASSERT_EQ(grpc_set_socket_rcvbuf(fd, buffer_size_bytes), absl::OkStatus());

  flags = fcntl(fd, F_GETFL, 0);
  ASSERT_EQ(fcntl(fd, F_SETFL, flags | O_NONBLOCK), 0);
  *socket_fd = fd;

  sin->sin_family = AF_INET;
  sin->sin_addr.s_addr = htonl(0x7f000001);
  ASSERT_GE(port, 0);
  ASSERT_LT(port, 65536);
  sin->sin_port = htons(static_cast<uint16_t>(port));
}

void no_op_cb(void* , int ) {}

typedef struct {
  grpc_fd* em_fd;
  ssize_t read_bytes_total;
  int done;
  grpc_closure listen_closure;
} server;

static void server_init(server* sv) {
  sv->read_bytes_total = 0;
  sv->done = 0;
}

typedef struct {
  server* sv;
  grpc_fd* em_fd;
  char read_buf[BUF_SIZE];
  grpc_closure session_read_closure;
} session;

static void session_shutdown_cb(void* arg,
                                bool ) {
  session* se = static_cast<session*>(arg);
  server* sv = se->sv;
  grpc_fd_orphan(se->em_fd, nullptr, nullptr, "a");
  gpr_free(se);

  grpc_fd_shutdown(sv->em_fd, GRPC_ERROR_CREATE("session_shutdown_cb"));
}

static void session_read_cb(void* arg,
                            grpc_error_handle error) {
  session* se = static_cast<session*>(arg);
  int fd = grpc_fd_wrapped_fd(se->em_fd);

  ssize_t read_once = 0;
  ssize_t read_total = 0;

  if (!error.ok()) {
    session_shutdown_cb(arg, true);
    return;
  }

  do {
    read_once = read(fd, se->read_buf, BUF_SIZE);
    if (read_once > 0) read_total += read_once;
  } while (read_once > 0);
  se->sv->read_bytes_total += read_total;

  if (read_once == 0) {
    session_shutdown_cb(arg, true);
  } else if (read_once == -1) {
    if (errno == EAGAIN) {

      grpc_fd_notify_on_read(se->em_fd, &se->session_read_closure);
    } else {
      LOG(FATAL) << "Unhandled read error " << grpc_core::StrError(errno);
    }
  }
}

static void listen_shutdown_cb(void* arg , int ) {
  server* sv = static_cast<server*>(arg);

  grpc_fd_orphan(sv->em_fd, nullptr, nullptr, "b");

  gpr_mu_lock(g_mu);
  sv->done = 1;
  ASSERT_TRUE(
      GRPC_LOG_IF_ERROR("pollset_kick", grpc_pollset_kick(g_pollset, nullptr)));
  gpr_mu_unlock(g_mu);
}

static void listen_cb(void* arg,
                      grpc_error_handle error) {
  server* sv = static_cast<server*>(arg);
  int fd;
  int flags;
  session* se;
  struct sockaddr_storage ss;
  socklen_t slen = sizeof(ss);
  grpc_fd* listen_em_fd = sv->em_fd;

  if (!error.ok()) {
    listen_shutdown_cb(arg, 1);
    return;
  }

  fd = accept(grpc_fd_wrapped_fd(listen_em_fd),
              reinterpret_cast<struct sockaddr*>(&ss), &slen);
  ASSERT_GE(fd, 0);
  ASSERT_LT(fd, FD_SETSIZE);
  flags = fcntl(fd, F_GETFL, 0);
  fcntl(fd, F_SETFL, flags | O_NONBLOCK);
  se = static_cast<session*>(gpr_malloc(sizeof(*se)));
  se->sv = sv;
  se->em_fd = grpc_fd_create(fd, "listener", false);
  grpc_pollset_add_fd(g_pollset, se->em_fd);
  GRPC_CLOSURE_INIT(&se->session_read_closure, session_read_cb, se,
                    grpc_schedule_on_exec_ctx);
  grpc_fd_notify_on_read(se->em_fd, &se->session_read_closure);

  grpc_fd_notify_on_read(listen_em_fd, &sv->listen_closure);
}

#define MAX_NUM_FD 1024

static int server_start(server* sv) {
  int port = 0;
  int fd;
  struct sockaddr_in sin;
  socklen_t addr_len;

  create_test_socket(port, &fd, &sin);
  addr_len = sizeof(sin);
  EXPECT_EQ(bind(fd, (struct sockaddr*)&sin, addr_len), 0);
  EXPECT_EQ(getsockname(fd, (struct sockaddr*)&sin, &addr_len), 0);
  port = ntohs(sin.sin_port);
  EXPECT_EQ(listen(fd, MAX_NUM_FD), 0);

  sv->em_fd = grpc_fd_create(fd, "server", false);
  grpc_pollset_add_fd(g_pollset, sv->em_fd);

  GRPC_CLOSURE_INIT(&sv->listen_closure, listen_cb, sv,
                    grpc_schedule_on_exec_ctx);
  grpc_fd_notify_on_read(sv->em_fd, &sv->listen_closure);

  return port;
}

static void server_wait_and_shutdown(server* sv) {
  gpr_mu_lock(g_mu);
  while (!sv->done) {
    grpc_core::ExecCtx exec_ctx;
    grpc_pollset_worker* worker = nullptr;
    ASSERT_TRUE(GRPC_LOG_IF_ERROR(
        "pollset_work", grpc_pollset_work(g_pollset, &worker,
                                          grpc_core::Timestamp::InfFuture())));
    gpr_mu_unlock(g_mu);

    gpr_mu_lock(g_mu);
  }
  gpr_mu_unlock(g_mu);
}

#define CLIENT_WRITE_BUF_SIZE 10

#define CLIENT_TOTAL_WRITE_CNT 3

typedef struct {
  grpc_fd* em_fd;
  char write_buf[CLIENT_WRITE_BUF_SIZE];
  ssize_t write_bytes_total;

  int client_write_cnt;

  int done;
  grpc_closure write_closure;
} client;

static void client_init(client* cl) {
  memset(cl->write_buf, 0, sizeof(cl->write_buf));
  cl->write_bytes_total = 0;
  cl->client_write_cnt = 0;
  cl->done = 0;
}

static void client_session_shutdown_cb(void* arg , int ) {
  client* cl = static_cast<client*>(arg);
  grpc_fd_orphan(cl->em_fd, nullptr, nullptr, "c");
  cl->done = 1;
  ASSERT_TRUE(
      GRPC_LOG_IF_ERROR("pollset_kick", grpc_pollset_kick(g_pollset, nullptr)));
}

static void client_session_write(void* arg,
                                 grpc_error_handle error) {
  client* cl = static_cast<client*>(arg);
  int fd = grpc_fd_wrapped_fd(cl->em_fd);
  ssize_t write_once = 0;

  if (!error.ok()) {
    gpr_mu_lock(g_mu);
    client_session_shutdown_cb(arg, 1);
    gpr_mu_unlock(g_mu);
    return;
  }

  do {
    write_once = write(fd, cl->write_buf, CLIENT_WRITE_BUF_SIZE);
    if (write_once > 0) cl->write_bytes_total += write_once;
  } while (write_once > 0);

  if (errno == EAGAIN) {
    gpr_mu_lock(g_mu);
    if (cl->client_write_cnt < CLIENT_TOTAL_WRITE_CNT) {
      GRPC_CLOSURE_INIT(&cl->write_closure, client_session_write, cl,
                        grpc_schedule_on_exec_ctx);
      grpc_fd_notify_on_write(cl->em_fd, &cl->write_closure);
      cl->client_write_cnt++;
    } else {
      client_session_shutdown_cb(arg, 1);
    }
    gpr_mu_unlock(g_mu);
  } else {
    LOG(FATAL) << "unknown errno " << grpc_core::StrError(errno).c_str();
  }
}

static void client_start(client* cl, int port) {
  int fd;
  struct sockaddr_in sin;
  create_test_socket(port, &fd, &sin);
  if (connect(fd, reinterpret_cast<struct sockaddr*>(&sin), sizeof(sin)) ==
      -1) {
    if (errno == EINPROGRESS) {
      struct pollfd pfd;
      pfd.fd = fd;
      pfd.events = POLLOUT;
      pfd.revents = 0;
      if (poll(&pfd, 1, -1) == -1) {
        LOG(FATAL) << "poll() failed during connect; errno=" << errno;
      }
    } else {
      LOG(FATAL) << "Failed to connect to the server (errno=" << errno << ")";
    }
  }

  cl->em_fd = grpc_fd_create(fd, "client", false);
  grpc_pollset_add_fd(g_pollset, cl->em_fd);

  client_session_write(cl, absl::OkStatus());
}

static void client_wait_and_shutdown(client* cl) {
  gpr_mu_lock(g_mu);
  while (!cl->done) {
    grpc_pollset_worker* worker = nullptr;
    grpc_core::ExecCtx exec_ctx;
    ASSERT_TRUE(GRPC_LOG_IF_ERROR(
        "pollset_work", grpc_pollset_work(g_pollset, &worker,
                                          grpc_core::Timestamp::InfFuture())));
    gpr_mu_unlock(g_mu);

    gpr_mu_lock(g_mu);
  }
  gpr_mu_unlock(g_mu);
}

static void test_grpc_fd(void) {
  server sv;
  client cl;
  int port;
  grpc_core::ExecCtx exec_ctx;

  server_init(&sv);
  port = server_start(&sv);
  client_init(&cl);
  client_start(&cl, port);

  client_wait_and_shutdown(&cl);
  server_wait_and_shutdown(&sv);
  ASSERT_EQ(sv.read_bytes_total, cl.write_bytes_total);
  LOG(INFO) << "Total read bytes " << sv.read_bytes_total;
}

typedef struct fd_change_data {
  grpc_iomgr_cb_func cb_that_ran;
} fd_change_data;

void init_change_data(fd_change_data* fdc) { fdc->cb_that_ran = nullptr; }

void destroy_change_data(fd_change_data* ) {}

static void first_read_callback(void* arg ,
                                grpc_error_handle ) {
  fd_change_data* fdc = static_cast<fd_change_data*>(arg);

  gpr_mu_lock(g_mu);
  fdc->cb_that_ran = first_read_callback;
  ASSERT_TRUE(
      GRPC_LOG_IF_ERROR("pollset_kick", grpc_pollset_kick(g_pollset, nullptr)));
  gpr_mu_unlock(g_mu);
}

static void second_read_callback(void* arg ,
                                 grpc_error_handle ) {
  fd_change_data* fdc = static_cast<fd_change_data*>(arg);

  gpr_mu_lock(g_mu);
  fdc->cb_that_ran = second_read_callback;
  ASSERT_TRUE(
      GRPC_LOG_IF_ERROR("pollset_kick", grpc_pollset_kick(g_pollset, nullptr)));
  gpr_mu_unlock(g_mu);
}

static void test_grpc_fd_change(void) {
  grpc_fd* em_fd;
  fd_change_data a, b;
  int flags;
  int sv[2];
  char data;
  ssize_t result;
  grpc_closure first_closure;
  grpc_closure second_closure;
  grpc_core::ExecCtx exec_ctx;

  GRPC_CLOSURE_INIT(&first_closure, first_read_callback, &a,
                    grpc_schedule_on_exec_ctx);
  GRPC_CLOSURE_INIT(&second_closure, second_read_callback, &b,
                    grpc_schedule_on_exec_ctx);

  init_change_data(&a);
  init_change_data(&b);

  ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, sv), 0);
  flags = fcntl(sv[0], F_GETFL, 0);
  ASSERT_EQ(fcntl(sv[0], F_SETFL, flags | O_NONBLOCK), 0);
  flags = fcntl(sv[1], F_GETFL, 0);
  ASSERT_EQ(fcntl(sv[1], F_SETFL, flags | O_NONBLOCK), 0);

  em_fd = grpc_fd_create(sv[0], "test_grpc_fd_change", false);
  grpc_pollset_add_fd(g_pollset, em_fd);

  grpc_fd_notify_on_read(em_fd, &first_closure);
  data = 0;
  result = write(sv[1], &data, 1);
  ASSERT_EQ(result, 1);

  gpr_mu_lock(g_mu);
  while (a.cb_that_ran == nullptr) {
    grpc_pollset_worker* worker = nullptr;
    ASSERT_TRUE(GRPC_LOG_IF_ERROR(
        "pollset_work", grpc_pollset_work(g_pollset, &worker,
                                          grpc_core::Timestamp::InfFuture())));
    gpr_mu_unlock(g_mu);

    gpr_mu_lock(g_mu);
  }
  ASSERT_EQ(a.cb_that_ran, first_read_callback);
  gpr_mu_unlock(g_mu);

  result = read(sv[0], &data, 1);
  ASSERT_EQ(result, 1);

  grpc_fd_notify_on_read(em_fd, &second_closure);
  data = 0;
  result = write(sv[1], &data, 1);
  ASSERT_EQ(result, 1);

  gpr_mu_lock(g_mu);
  while (b.cb_that_ran == nullptr) {
    grpc_pollset_worker* worker = nullptr;
    ASSERT_TRUE(GRPC_LOG_IF_ERROR(
        "pollset_work", grpc_pollset_work(g_pollset, &worker,
                                          grpc_core::Timestamp::InfFuture())));
    gpr_mu_unlock(g_mu);

    gpr_mu_lock(g_mu);
  }

  ASSERT_EQ(b.cb_that_ran, second_read_callback);
  gpr_mu_unlock(g_mu);

  grpc_fd_orphan(em_fd, nullptr, nullptr, "d");

  destroy_change_data(&a);
  destroy_change_data(&b);
  close(sv[1]);
}

static void destroy_pollset(void* p, grpc_error_handle ) {
  grpc_pollset_destroy(static_cast<grpc_pollset*>(p));
}

TEST(FdPosixTest, MainTest) {
  if (grpc_core::IsEventEngineForAllOtherEndpointsEnabled() &&
      !grpc_event_engine::experimental::
          EventEngineExperimentDisabledForPython()) {
    GTEST_SKIP() << "The event_engine_for_all_other_endpoints experiment is "
                    "enabled, which replaces iomgr grpc_fds with minimal "
                    "implementations. The full iomgr API is not supported, so "
                    "this test needs to be disabled.";
  }
  grpc_closure destroyed;
  grpc_init();
  if (grpc_core::IsPollsetAlternativeEnabled()) {
    GTEST_SKIP() << "Skipping test since we're using pollset alternative";
  }
  {
    grpc_core::ExecCtx exec_ctx;
    g_pollset = static_cast<grpc_pollset*>(gpr_zalloc(grpc_pollset_size()));
    grpc_pollset_init(g_pollset, &g_mu);
    test_grpc_fd();
    test_grpc_fd_change();
    GRPC_CLOSURE_INIT(&destroyed, destroy_pollset, g_pollset,
                      grpc_schedule_on_exec_ctx);
    grpc_pollset_shutdown(g_pollset, &destroyed);
    grpc_core::ExecCtx::Get()->Flush();
    gpr_free(g_pollset);
  }
  grpc_shutdown();
}

#endif

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
