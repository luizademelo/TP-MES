// Copyright 2022 gRPC authors.

#include <grpc/support/port_platform.h>

#ifdef GPR_WINDOWS
#include <grpc/grpc.h>
#include <grpc/support/log_windows.h>

#include <thread>
#include <variant>

#include "absl/log/log.h"
#include "absl/status/status.h"
#include "absl/time/time.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "src/core/lib/event_engine/common_closures.h"
#include "src/core/lib/event_engine/poller.h"
#include "src/core/lib/event_engine/thread_pool/thread_pool.h"
#include "src/core/lib/event_engine/windows/iocp.h"
#include "src/core/lib/event_engine/windows/win_socket.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/util/notification.h"
#include "test/core/event_engine/windows/create_sockpair.h"

namespace {
using ::grpc_event_engine::experimental::AnyInvocableClosure;
using ::grpc_event_engine::experimental::CreateSockpair;
using ::grpc_event_engine::experimental::EventEngine;
using ::grpc_event_engine::experimental::IOCP;
using ::grpc_event_engine::experimental::Poller;
using ::grpc_event_engine::experimental::SelfDeletingClosure;
using ::grpc_event_engine::experimental::ThreadPool;
using ::grpc_event_engine::experimental::WinSocket;

void LogErrorMessage(int messageid, absl::string_view context) {
  char* utf8_message = gpr_format_message(messageid);
  LOG(ERROR) << "Error in " << context << ": " << utf8_message;
  gpr_free(utf8_message);
}
}

class IOCPTest : public testing::Test {};

TEST_F(IOCPTest, ClientReceivesNotificationOfServerSend) {
  auto thread_pool = grpc_event_engine::experimental::MakeThreadPool(8);
  IOCP iocp(thread_pool.get());
  SOCKET sockpair[2];
  CreateSockpair(sockpair, iocp.GetDefaultSocketFlags());
  auto wrapped_client_socket = iocp.Watch(sockpair[0]);
  auto wrapped_server_socket = iocp.Watch(sockpair[1]);
  grpc_core::Notification read_called;
  grpc_core::Notification write_called;
  DWORD flags = 0;
  AnyInvocableClosure* on_read;
  AnyInvocableClosure* on_write;
  WSABUF read_wsabuf;
  DWORD bytes_rcvd;
  read_wsabuf.len = 2048;
  char read_char_buffer[2048];
  read_wsabuf.buf = read_char_buffer;
  {

    on_read = new AnyInvocableClosure([win_socket = wrapped_client_socket.get(),
                                       &read_called, &read_wsabuf]() {
      VLOG(2) << "Notified on read";
      EXPECT_TRUE(win_socket->read_info()->result().error_status.ok())
          << "Error on read: "
          << win_socket->read_info()->result().error_status;
      EXPECT_GE(win_socket->read_info()->result().bytes_transferred, 10u);
      EXPECT_STREQ(read_wsabuf.buf, "hello!");
      read_called.Notify();
    });
    wrapped_client_socket->NotifyOnRead(on_read);
    int status = WSARecv(
        wrapped_client_socket->raw_socket(), &read_wsabuf, 1, &bytes_rcvd,
        &flags, wrapped_client_socket->read_info()->overlapped(), NULL);

    EXPECT_EQ(status, -1);
    int last_error = WSAGetLastError();
    EXPECT_EQ(last_error, WSA_IO_PENDING);
    if (last_error != WSA_IO_PENDING) {
      LogErrorMessage(last_error, "WSARecv");
    }
  }
  {
    on_write = new AnyInvocableClosure([&write_called] {
      VLOG(2) << "Notified on write";
      write_called.Notify();
    });
    wrapped_server_socket->NotifyOnWrite(on_write);

    WSABUF write_wsabuf;
    char write_char_buffer[2048] = "hello!";
    write_wsabuf.len = 2048;
    write_wsabuf.buf = write_char_buffer;
    DWORD bytes_sent;
    int status = WSASend(
        wrapped_server_socket->raw_socket(), &write_wsabuf, 1, &bytes_sent, 0,
        wrapped_server_socket->write_info()->overlapped(), NULL);
    EXPECT_EQ(status, 0);
    if (status != 0) {
      LogErrorMessage(WSAGetLastError(), "WSASend");
    }
  }

  bool cb_invoked = false;
  auto work_result = iocp.Work(std::chrono::seconds(10),
                               [&cb_invoked]() { cb_invoked = true; });
  ASSERT_TRUE(work_result == Poller::WorkResult::kOk);
  ASSERT_TRUE(cb_invoked);

  cb_invoked = false;
  work_result = iocp.Work(std::chrono::seconds(10),
                          [&cb_invoked]() { cb_invoked = true; });
  ASSERT_TRUE(work_result == Poller::WorkResult::kOk);
  ASSERT_TRUE(cb_invoked);

  read_called.WaitForNotification();
  write_called.WaitForNotification();

  delete on_read;
  delete on_write;
  wrapped_client_socket->Shutdown();
  wrapped_server_socket->Shutdown();
  iocp.Shutdown();
  thread_pool->Quiesce();
}

TEST_F(IOCPTest, IocpWorkTimeoutDueToNoNotificationRegistered) {
  auto thread_pool = grpc_event_engine::experimental::MakeThreadPool(8);
  IOCP iocp(thread_pool.get());
  SOCKET sockpair[2];
  CreateSockpair(sockpair, iocp.GetDefaultSocketFlags());
  auto wrapped_client_socket = iocp.Watch(sockpair[0]);
  grpc_core::Notification read_called;
  DWORD flags = 0;
  WSABUF read_wsabuf;
  DWORD bytes_rcvd;
  read_wsabuf.len = 2048;
  char read_char_buffer[2048];
  read_wsabuf.buf = read_char_buffer;
  {

    wrapped_client_socket->NotifyOnRead(
        SelfDeletingClosure::Create([win_socket = wrapped_client_socket.get(),
                                     &read_called, &read_wsabuf]() {
          VLOG(2) << "Notified on read";
          EXPECT_TRUE(win_socket->read_info()->result().error_status.ok())
              << "Error on read: "
              << win_socket->read_info()->result().error_status;
          EXPECT_GE(win_socket->read_info()->result().bytes_transferred, 10u);
          EXPECT_STREQ(read_wsabuf.buf, "hello!");
          read_called.Notify();
        }));
    int status = WSARecv(
        wrapped_client_socket->raw_socket(), &read_wsabuf, 1, &bytes_rcvd,
        &flags, wrapped_client_socket->read_info()->overlapped(), NULL);

    EXPECT_EQ(status, -1);
    int last_error = WSAGetLastError();
    EXPECT_EQ(last_error, WSA_IO_PENDING);
    if (last_error != WSA_IO_PENDING) {
      LogErrorMessage(last_error, "WSARecv");
    }
  }
  {

    WSABUF write_wsabuf;
    char write_char_buffer[2048] = "hello!";
    write_wsabuf.len = 2048;
    write_wsabuf.buf = write_char_buffer;
    DWORD bytes_sent;
    OVERLAPPED write_overlapped;
    memset(&write_overlapped, 0, sizeof(OVERLAPPED));
    int status = WSASend(sockpair[1], &write_wsabuf, 1, &bytes_sent, 0,
                         &write_overlapped, NULL);
    EXPECT_EQ(status, 0);
    if (status != 0) {
      LogErrorMessage(WSAGetLastError(), "WSASend");
    }
  }

  bool cb_invoked = false;
  auto work_result = iocp.Work(std::chrono::seconds(2),
                               [&cb_invoked]() { cb_invoked = true; });
  ASSERT_TRUE(work_result == Poller::WorkResult::kOk);
  ASSERT_TRUE(cb_invoked);

  read_called.WaitForNotification();
  wrapped_client_socket->Shutdown();
  iocp.Shutdown();
  thread_pool->Quiesce();
}

TEST_F(IOCPTest, KickWorks) {
  auto thread_pool = grpc_event_engine::experimental::MakeThreadPool(8);
  IOCP iocp(thread_pool.get());
  grpc_core::Notification kicked;
  thread_pool->Run([&iocp, &kicked] {
    bool cb_invoked = false;
    Poller::WorkResult result = iocp.Work(
        std::chrono::seconds(30), [&cb_invoked]() { cb_invoked = true; });
    ASSERT_TRUE(result == Poller::WorkResult::kKicked);
    ASSERT_FALSE(cb_invoked);
    kicked.Notify();
  });
  thread_pool->Run([&iocp] {

    absl::SleepFor(absl::Milliseconds(42));
    iocp.Kick();
  });

  kicked.WaitForNotification();
  thread_pool->Quiesce();
}

TEST_F(IOCPTest, KickThenShutdownCasusesNextWorkerToBeKicked) {

  auto thread_pool = grpc_event_engine::experimental::MakeThreadPool(8);
  IOCP iocp(thread_pool.get());

  iocp.Kick();
  iocp.Kick();
  bool cb_invoked = false;

  auto result = iocp.Work(std::chrono::milliseconds(1),
                          [&cb_invoked]() { cb_invoked = true; });
  ASSERT_TRUE(result == Poller::WorkResult::kKicked);
  ASSERT_FALSE(cb_invoked);
  result = iocp.Work(std::chrono::milliseconds(1),
                     [&cb_invoked]() { cb_invoked = true; });
  ASSERT_TRUE(result == Poller::WorkResult::kKicked);
  ASSERT_FALSE(cb_invoked);

  result = iocp.Work(std::chrono::milliseconds(1),
                     [&cb_invoked]() { cb_invoked = true; });
  ASSERT_TRUE(result == Poller::WorkResult::kDeadlineExceeded);
  ASSERT_FALSE(cb_invoked);
  thread_pool->Quiesce();
}

TEST_F(IOCPTest, StressTestThousandsOfSockets) {

  int thread_count = 10;
  int sockets_per_thread = 50;
  std::atomic<int> read_count{0};
  std::atomic<int> write_count{0};
  std::vector<std::thread> threads;
  threads.reserve(thread_count);
  for (int thread_n = 0; thread_n < thread_count; thread_n++) {
    threads.emplace_back([sockets_per_thread, &read_count, &write_count] {
      auto thread_pool = grpc_event_engine::experimental::MakeThreadPool(8);
      IOCP iocp(thread_pool.get());

      std::thread iocp_worker([&iocp] {
        Poller::WorkResult result;
        do {
          result = iocp.Work(std::chrono::seconds(1), []() {});
        } while (result != Poller::WorkResult::kDeadlineExceeded);
      });
      for (int i = 0; i < sockets_per_thread; i++) {
        SOCKET sockpair[2];
        CreateSockpair(sockpair, iocp.GetDefaultSocketFlags());
        auto wrapped_client_socket = iocp.Watch(sockpair[0]);
        auto wrapped_server_socket = iocp.Watch(sockpair[1]);
        auto* pclient = wrapped_client_socket.get();
        pclient->NotifyOnRead(SelfDeletingClosure::Create(
            [&read_count,
             win_socket = std::move(wrapped_client_socket)]() mutable {
              read_count.fetch_add(1);
              win_socket->Shutdown();
            }));
        auto* pserver = wrapped_server_socket.get();
        pserver->NotifyOnWrite(SelfDeletingClosure::Create(
            [&write_count,
             win_socket = std::move(wrapped_server_socket)]() mutable {
              write_count.fetch_add(1);
              win_socket->Shutdown();
            }));
        {

          WSABUF read_wsabuf;
          read_wsabuf.len = 20;
          char read_char_buffer[20];
          read_wsabuf.buf = read_char_buffer;
          DWORD bytes_rcvd;
          DWORD flags = 0;
          int status =
              WSARecv(pclient->raw_socket(), &read_wsabuf, 1, &bytes_rcvd,
                      &flags, pclient->read_info()->overlapped(), NULL);

          EXPECT_EQ(status, -1);
          int last_error = WSAGetLastError();
          EXPECT_EQ(last_error, WSA_IO_PENDING);
          if (last_error != WSA_IO_PENDING) {
            LogErrorMessage(last_error, "WSARecv");
          }
        }
        {

          WSABUF write_wsabuf;
          char write_char_buffer[20] = "hello!";
          write_wsabuf.len = 20;
          write_wsabuf.buf = write_char_buffer;
          DWORD bytes_sent;
          int status =
              WSASend(pserver->raw_socket(), &write_wsabuf, 1, &bytes_sent, 0,
                      pserver->write_info()->overlapped(), NULL);
          if (status != 0) {
            int wsa_error = WSAGetLastError();
            if (wsa_error != WSA_IO_PENDING) {
              LogErrorMessage(wsa_error, "WSASend");
              FAIL() << "Error in WSASend. See logs";
            }
          }
        }
      }
      iocp_worker.join();
      thread_pool->Quiesce();
    });
  }
  for (auto& t : threads) {
    t.join();
  }
  absl::Time deadline = absl::Now() + absl::Seconds(30);
  while (read_count.load() != thread_count * sockets_per_thread ||
         write_count.load() != thread_count * sockets_per_thread) {
    absl::SleepFor(absl::Milliseconds(50));
    if (deadline < absl::Now()) {
      FAIL() << "Deadline exceeded with " << read_count.load() << " reads and "
             << write_count.load() << " writes";
    }
  }
  ASSERT_EQ(read_count.load(), thread_count * sockets_per_thread);
  ASSERT_EQ(write_count.load(), thread_count * sockets_per_thread);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  grpc_init();
  int status = RUN_ALL_TESTS();
  grpc_shutdown();
  return status;
}
#else
int main(int , char** ) { return 0; }
#endif
