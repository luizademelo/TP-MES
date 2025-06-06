// Copyright 2022 The gRPC Authors

#include <grpc/grpc.h>
#include <stdint.h>
#include <sys/select.h>

#include <algorithm>
#include <atomic>
#include <chrono>
#include <cstring>
#include <memory>
#include <vector>

#include "absl/status/statusor.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_format.h"
#include "absl/strings/str_split.h"
#include "absl/strings/string_view.h"
#include "gtest/gtest.h"
#include "src/core/config/config_vars.h"
#include "src/core/lib/event_engine/poller.h"
#include "src/core/lib/event_engine/posix_engine/wakeup_fd_pipe.h"
#include "src/core/lib/event_engine/posix_engine/wakeup_fd_posix.h"
#include "src/core/lib/iomgr/port.h"
#include "src/core/util/ref_counted_ptr.h"

#ifdef GRPC_POSIX_SOCKET_EV

#include <errno.h>
#include <fcntl.h>
#include <grpc/support/alloc.h>
#include <grpc/support/sync.h>
#include <netinet/in.h>
#include <poll.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

#include "absl/log/log.h"
#include "absl/status/status.h"
#include "src/core/lib/event_engine/common_closures.h"
#include "src/core/lib/event_engine/posix_engine/event_poller.h"
#include "src/core/lib/event_engine/posix_engine/event_poller_posix_default.h"
#include "src/core/lib/event_engine/posix_engine/posix_engine.h"
#include "src/core/lib/event_engine/posix_engine/posix_engine_closure.h"
#include "src/core/util/crash.h"
#include "src/core/util/dual_ref_counted.h"
#include "src/core/util/notification.h"
#include "src/core/util/strerror.h"
#include "test/core/event_engine/posix/posix_engine_test_utils.h"
#include "test/core/test_util/port.h"

static gpr_mu g_mu;
static std::shared_ptr<grpc_event_engine::experimental::PosixEventPoller>
    g_event_poller;

#define BUF_SIZE 1024

#define MAX_NUM_FD 1024

#define CLIENT_WRITE_BUF_SIZE 10

#define CLIENT_TOTAL_WRITE_CNT 3

namespace grpc_event_engine {
namespace experimental {

using namespace std::chrono_literals;

namespace {

absl::Status SetSocketSendBuf(int fd, int buffer_size_bytes) {
  return 0 == setsockopt(fd, SOL_SOCKET, SO_SNDBUF, &buffer_size_bytes,
                         sizeof(buffer_size_bytes))
             ? absl::OkStatus()
             : absl::Status(absl::StatusCode::kInternal,
                            grpc_core::StrError(errno).c_str());
}

void CreateTestSocket(int port, int* socket_fd, struct sockaddr_in6* sin) {
  int fd;
  int one = 1;
  int buffer_size_bytes = BUF_SIZE;
  int flags;

  fd = socket(AF_INET6, SOCK_STREAM, 0);
  setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));

  EXPECT_TRUE(SetSocketSendBuf(fd, buffer_size_bytes).ok());
  EXPECT_TRUE(SetSocketSendBuf(fd, buffer_size_bytes).ok());

  flags = fcntl(fd, F_GETFL, 0);
  EXPECT_EQ(fcntl(fd, F_SETFL, flags | O_NONBLOCK), 0);
  *socket_fd = fd;

  memset(sin, 0, sizeof(struct sockaddr_in6));
  sin->sin6_family = AF_INET6;
  (reinterpret_cast<char*>(&sin->sin6_addr))[15] = 1;
  EXPECT_TRUE(port >= 0 && port < 65536);
  sin->sin6_port = htons(static_cast<uint16_t>(port));
}

typedef struct {
  EventHandle* em_fd;
  ssize_t read_bytes_total;
  int done;
  PosixEngineClosure* listen_closure;
} server;

void ServerInit(server* sv) {
  sv->read_bytes_total = 0;
  sv->done = 0;
}

typedef struct {
  server* sv;
  EventHandle* em_fd;
  char read_buf[BUF_SIZE];
  PosixEngineClosure* session_read_closure;
} session;

void SessionShutdownCb(session* se, bool ) {
  server* sv = se->sv;
  se->em_fd->OrphanHandle(nullptr, nullptr, "a");
  gpr_free(se);

  sv->em_fd->ShutdownHandle(
      absl::Status(absl::StatusCode::kUnknown, "SessionShutdownCb"));
}

void SessionReadCb(session* se, absl::Status status) {
  int fd = se->em_fd->WrappedFd();

  ssize_t read_once = 0;
  ssize_t read_total = 0;

  if (!status.ok()) {
    SessionShutdownCb(se, true);
    return;
  }

  do {
    read_once = read(fd, se->read_buf, BUF_SIZE);
    if (read_once > 0) read_total += read_once;
  } while (read_once > 0);
  se->sv->read_bytes_total += read_total;

  if (read_once == 0) {
    SessionShutdownCb(se, true);
  } else if (read_once == -1) {
    EXPECT_EQ(errno, EAGAIN);

    se->session_read_closure = PosixEngineClosure::TestOnlyToClosure(
        [se](absl::Status status) { SessionReadCb(se, status); });
    se->em_fd->NotifyOnRead(se->session_read_closure);
  }
}

void ListenShutdownCb(server* sv) {
  sv->em_fd->OrphanHandle(nullptr, nullptr, "b");
  gpr_mu_lock(&g_mu);
  sv->done = 1;
  g_event_poller->Kick();
  gpr_mu_unlock(&g_mu);
}

void ListenCb(server* sv, absl::Status status) {
  int fd;
  int flags;
  session* se;
  struct sockaddr_storage ss;
  socklen_t slen = sizeof(ss);
  EventHandle* listen_em_fd = sv->em_fd;

  if (!status.ok()) {
    ListenShutdownCb(sv);
    return;
  }

  do {
    fd = accept(listen_em_fd->WrappedFd(),
                reinterpret_cast<struct sockaddr*>(&ss), &slen);
  } while (fd < 0 && errno == EINTR);
  if (fd < 0 && errno == EAGAIN) {
    sv->listen_closure = PosixEngineClosure::TestOnlyToClosure(
        [sv](absl::Status status) { ListenCb(sv, status); });
    listen_em_fd->NotifyOnRead(sv->listen_closure);
    return;
  } else if (fd < 0) {
    LOG(ERROR) << "Failed to accept a connection, returned error: "
               << grpc_core::StrError(errno);
  }
  EXPECT_GE(fd, 0);
  EXPECT_LT(fd, FD_SETSIZE);
  flags = fcntl(fd, F_GETFL, 0);
  fcntl(fd, F_SETFL, flags | O_NONBLOCK);
  se = static_cast<session*>(gpr_malloc(sizeof(*se)));
  se->sv = sv;
  se->em_fd = g_event_poller->CreateHandle(fd, "listener", false);
  se->session_read_closure = PosixEngineClosure::TestOnlyToClosure(
      [se](absl::Status status) { SessionReadCb(se, status); });
  se->em_fd->NotifyOnRead(se->session_read_closure);
  sv->listen_closure = PosixEngineClosure::TestOnlyToClosure(
      [sv](absl::Status status) { ListenCb(sv, status); });
  listen_em_fd->NotifyOnRead(sv->listen_closure);
}

int ServerStart(server* sv) {
  int port = grpc_pick_unused_port_or_die();
  int fd;
  struct sockaddr_in6 sin;
  socklen_t addr_len;

  CreateTestSocket(port, &fd, &sin);
  addr_len = sizeof(sin);
  EXPECT_EQ(bind(fd, (struct sockaddr*)&sin, addr_len), 0);
  EXPECT_EQ(getsockname(fd, (struct sockaddr*)&sin, &addr_len), 0);
  port = ntohs(sin.sin6_port);
  EXPECT_EQ(listen(fd, MAX_NUM_FD), 0);

  sv->em_fd = g_event_poller->CreateHandle(fd, "server", false);
  sv->listen_closure = PosixEngineClosure::TestOnlyToClosure(
      [sv](absl::Status status) { ListenCb(sv, status); });
  sv->em_fd->NotifyOnRead(sv->listen_closure);
  return port;
}

typedef struct {
  EventHandle* em_fd;
  char write_buf[CLIENT_WRITE_BUF_SIZE];
  ssize_t write_bytes_total;

  int client_write_cnt;
  int done;
  PosixEngineClosure* write_closure;
} client;

void ClientInit(client* cl) {
  memset(cl->write_buf, 0, sizeof(cl->write_buf));
  cl->write_bytes_total = 0;
  cl->client_write_cnt = 0;
  cl->done = 0;
}

void ClientSessionShutdownCb(client* cl) {
  cl->em_fd->OrphanHandle(nullptr, nullptr, "c");
  gpr_mu_lock(&g_mu);
  cl->done = 1;
  g_event_poller->Kick();
  gpr_mu_unlock(&g_mu);
}

void ClientSessionWrite(client* cl, absl::Status status) {
  int fd = cl->em_fd->WrappedFd();
  ssize_t write_once = 0;

  if (!status.ok()) {
    ClientSessionShutdownCb(cl);
    return;
  }

  do {
    write_once = write(fd, cl->write_buf, CLIENT_WRITE_BUF_SIZE);
    if (write_once > 0) cl->write_bytes_total += write_once;
  } while (write_once > 0);

  EXPECT_EQ(errno, EAGAIN);
  gpr_mu_lock(&g_mu);
  if (cl->client_write_cnt < CLIENT_TOTAL_WRITE_CNT) {
    cl->write_closure = PosixEngineClosure::TestOnlyToClosure(
        [cl](absl::Status status) { ClientSessionWrite(cl, status); });
    cl->client_write_cnt++;
    gpr_mu_unlock(&g_mu);
    cl->em_fd->NotifyOnWrite(cl->write_closure);
  } else {
    gpr_mu_unlock(&g_mu);
    ClientSessionShutdownCb(cl);
  }
}

void ClientStart(client* cl, int port) {
  int fd;
  struct sockaddr_in6 sin;
  CreateTestSocket(port, &fd, &sin);
  if (connect(fd, reinterpret_cast<struct sockaddr*>(&sin), sizeof(sin)) ==
      -1) {
    if (errno == EINPROGRESS) {
      struct pollfd pfd;
      pfd.fd = fd;
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

  cl->em_fd = g_event_poller->CreateHandle(fd, "client", false);
  ClientSessionWrite(cl, absl::OkStatus());
}

void WaitAndShutdown(server* sv, client* cl) {
  Poller::WorkResult result;
  gpr_mu_lock(&g_mu);
  while (!sv->done || !cl->done) {
    gpr_mu_unlock(&g_mu);
    result = g_event_poller->Work(24h, []() {});
    ASSERT_FALSE(result == Poller::WorkResult::kDeadlineExceeded);
    gpr_mu_lock(&g_mu);
  }
  gpr_mu_unlock(&g_mu);
}

class EventPollerTest : public ::testing::Test {
  void SetUp() override {
    engine_ = PosixEventEngine::MakePosixEventEngine();
    EXPECT_NE(engine_, nullptr);
    scheduler_ = std::make_unique<TestScheduler>(engine_.get());
    EXPECT_NE(scheduler_, nullptr);
    g_event_poller = MakeDefaultPoller(scheduler_.get());
    engine_ = PosixEventEngine::MakeTestOnlyPosixEventEngine(g_event_poller);
    EXPECT_NE(engine_, nullptr);
    scheduler_->ChangeCurrentEventEngine(engine_.get());
    if (g_event_poller != nullptr) {
      LOG(INFO) << "Using poller: " << g_event_poller->Name();
    }
  }

  void TearDown() override {
    if (g_event_poller != nullptr) {
      g_event_poller->Shutdown();
    }
  }

 public:
  TestScheduler* Scheduler() { return scheduler_.get(); }

 private:
  std::shared_ptr<PosixEventEngine> engine_;
  std::unique_ptr<TestScheduler> scheduler_;
};

TEST_F(EventPollerTest, TestEventPollerHandle) {
  server sv;
  client cl;
  int port;
  if (g_event_poller == nullptr) {
    return;
  }
  ServerInit(&sv);
  port = ServerStart(&sv);
  ClientInit(&cl);
  ClientStart(&cl, port);

  WaitAndShutdown(&sv, &cl);
  EXPECT_EQ(sv.read_bytes_total, cl.write_bytes_total);
}

typedef struct FdChangeData {
  void (*cb_that_ran)(struct FdChangeData*, absl::Status);
} FdChangeData;

void InitChangeData(FdChangeData* fdc) { fdc->cb_that_ran = nullptr; }

void DestroyChangeData(FdChangeData* ) {}

void FirstReadCallback(FdChangeData* fdc, absl::Status ) {
  gpr_mu_lock(&g_mu);
  fdc->cb_that_ran = FirstReadCallback;
  g_event_poller->Kick();
  gpr_mu_unlock(&g_mu);
}

void SecondReadCallback(FdChangeData* fdc, absl::Status ) {
  gpr_mu_lock(&g_mu);
  fdc->cb_that_ran = SecondReadCallback;
  g_event_poller->Kick();
  gpr_mu_unlock(&g_mu);
}

TEST_F(EventPollerTest, TestEventPollerHandleChange) {
  EventHandle* em_fd;
  FdChangeData a, b;
  int flags;
  int sv[2];
  char data;
  ssize_t result;
  if (g_event_poller == nullptr) {
    return;
  }
  PosixEngineClosure* first_closure = PosixEngineClosure::TestOnlyToClosure(
      [a = &a](absl::Status status) { FirstReadCallback(a, status); });
  PosixEngineClosure* second_closure = PosixEngineClosure::TestOnlyToClosure(
      [b = &b](absl::Status status) { SecondReadCallback(b, status); });
  InitChangeData(&a);
  InitChangeData(&b);

  EXPECT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, sv), 0);
  flags = fcntl(sv[0], F_GETFL, 0);
  EXPECT_EQ(fcntl(sv[0], F_SETFL, flags | O_NONBLOCK), 0);
  flags = fcntl(sv[1], F_GETFL, 0);
  EXPECT_EQ(fcntl(sv[1], F_SETFL, flags | O_NONBLOCK), 0);

  em_fd =
      g_event_poller->CreateHandle(sv[0], "TestEventPollerHandleChange", false);
  EXPECT_NE(em_fd, nullptr);

  em_fd->NotifyOnRead(first_closure);
  data = 0;
  result = write(sv[1], &data, 1);
  EXPECT_EQ(result, 1);

  auto poller_work = [](FdChangeData* fdc) {
    Poller::WorkResult result;
    gpr_mu_lock(&g_mu);
    while (fdc->cb_that_ran == nullptr) {
      gpr_mu_unlock(&g_mu);
      result = g_event_poller->Work(24h, []() {});
      ASSERT_FALSE(result == Poller::WorkResult::kDeadlineExceeded);
      gpr_mu_lock(&g_mu);
    }
  };
  poller_work(&a);
  EXPECT_EQ(a.cb_that_ran, FirstReadCallback);
  gpr_mu_unlock(&g_mu);

  result = read(sv[0], &data, 1);
  EXPECT_EQ(result, 1);

  em_fd->NotifyOnRead(second_closure);
  data = 0;
  result = write(sv[1], &data, 1);
  EXPECT_EQ(result, 1);

  poller_work(&b);

  EXPECT_EQ(b.cb_that_ran, SecondReadCallback);
  gpr_mu_unlock(&g_mu);

  em_fd->OrphanHandle(nullptr, nullptr, "d");
  DestroyChangeData(&a);
  DestroyChangeData(&b);
  close(sv[1]);
}

std::atomic<int> kTotalActiveWakeupFdHandles{0};

class WakeupFdHandle : public grpc_core::DualRefCounted<WakeupFdHandle> {
 public:
  WakeupFdHandle(int num_wakeups, Scheduler* scheduler,
                 PosixEventPoller* poller)
      : num_wakeups_(num_wakeups),
        scheduler_(scheduler),
        poller_(poller),
        on_read_(
            PosixEngineClosure::ToPermanentClosure([this](absl::Status status) {
              EXPECT_TRUE(status.ok());
              status = ReadPipe();
              if (!status.ok()) {

                EXPECT_EQ(status, absl::InternalError("Spurious Wakeup"));
                handle_->NotifyOnRead(on_read_);
                return;
              }
              if (--num_wakeups_ == 0) {

                handle_->ShutdownHandle(absl::InternalError("Shutting down"));
                Unref();
              } else {
                handle_->NotifyOnRead(on_read_);
                Ref().release();

                scheduler_->Run(SelfDeletingClosure::Create([this]() {

                  EXPECT_TRUE(wakeup_fd_->Wakeup().ok());
                  Unref();
                }));
              }
            })) {
    WeakRef().release();
    ++kTotalActiveWakeupFdHandles;
    EXPECT_GT(num_wakeups_, 0);
    EXPECT_NE(scheduler_, nullptr);
    EXPECT_NE(poller_, nullptr);
    wakeup_fd_ = *PipeWakeupFd::CreatePipeWakeupFd();
    handle_ = poller_->CreateHandle(wakeup_fd_->ReadFd(), "test", false);
    EXPECT_NE(handle_, nullptr);
    handle_->NotifyOnRead(on_read_);

    EXPECT_TRUE(wakeup_fd_->Wakeup().ok());
  }

  ~WakeupFdHandle() override { delete on_read_; }

  void Orphaned() override {

    handle_->OrphanHandle(
        PosixEngineClosure::TestOnlyToClosure(
            [poller = poller_, wakeupfd_handle = this](absl::Status status) {
              EXPECT_TRUE(status.ok());
              if (--kTotalActiveWakeupFdHandles == 0) {
                poller->Kick();
              }
              wakeupfd_handle->WeakUnref();
            }),
        nullptr, "");
  }

 private:
  absl::Status ReadPipe() {
    char buf[128];
    ssize_t r;
    int total_bytes_read = 0;
    for (;;) {
      r = read(wakeup_fd_->ReadFd(), buf, sizeof(buf));
      if (r > 0) {
        total_bytes_read += r;
        continue;
      }
      if (r == 0) return absl::OkStatus();
      switch (errno) {
        case EAGAIN:
          return total_bytes_read > 0 ? absl::OkStatus()
                                      : absl::InternalError("Spurious Wakeup");
        case EINTR:
          continue;
        default:
          return absl::Status(
              absl::StatusCode::kInternal,
              absl::StrCat("read: ", grpc_core::StrError(errno)));
      }
    }
  }
  int num_wakeups_;
  Scheduler* scheduler_;
  PosixEventPoller* poller_;
  PosixEngineClosure* on_read_;
  std::unique_ptr<WakeupFd> wakeup_fd_;
  EventHandle* handle_;
};

class Worker : public grpc_core::DualRefCounted<Worker> {
 public:
  Worker(Scheduler* scheduler, PosixEventPoller* poller, int num_handles,
         int num_wakeups_per_handle)
      : scheduler_(scheduler), poller_(poller) {
    handles_.reserve(num_handles);
    for (int i = 0; i < num_handles; i++) {
      handles_.push_back(
          new WakeupFdHandle(num_wakeups_per_handle, scheduler_, poller_));
    }
    WeakRef().release();
  }
  void Orphaned() override { signal.Notify(); }
  void Start() {

    scheduler_->Run([this]() { Work(); });
  }

  void Wait() {
    signal.WaitForNotification();
    WeakUnref();
  }

 private:
  void Work() {
    auto result = g_event_poller->Work(24h, [this]() {

      Ref().release();
      scheduler_->Run([this]() { Work(); });
    });
    ASSERT_TRUE(result == Poller::WorkResult::kOk ||
                result == Poller::WorkResult::kKicked);

    Unref();
  }
  Scheduler* scheduler_;
  PosixEventPoller* poller_;
  grpc_core::Notification signal;
  std::vector<WakeupFdHandle*> handles_;
};

TEST_F(EventPollerTest, TestMultipleHandles) {
  static constexpr int kNumHandles = 100;
  static constexpr int kNumWakeupsPerHandle = 100;
  if (g_event_poller == nullptr) {
    return;
  }
  Worker* worker = new Worker(Scheduler(), g_event_poller.get(), kNumHandles,
                              kNumWakeupsPerHandle);
  worker->Start();
  worker->Wait();
}

}
}
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  gpr_mu_init(&g_mu);
  auto poll_strategy = grpc_core::ConfigVars::Get().PollStrategy();
  auto strings = absl::StrSplit(poll_strategy, ',');
  if (std::find(strings.begin(), strings.end(), "none") != strings.end()) {

    return 0;
  }

  grpc_init();
  int r = RUN_ALL_TESTS();
  grpc_shutdown();
  return r;
}

#else

int main(int argc, char** argv) { return 1; }

#endif
