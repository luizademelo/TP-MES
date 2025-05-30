// Copyright 2022 gRPC authors.

#include <grpc/support/port_platform.h>

#ifdef GPR_WINDOWS

#include <grpc/event_engine/event_engine.h>
#include <grpc/grpc.h>

#include "absl/status/status.h"
#include "gtest/gtest.h"
#include "src/core/lib/event_engine/channel_args_endpoint_config.h"
#include "src/core/lib/event_engine/thread_pool/thread_pool.h"
#include "src/core/lib/event_engine/windows/iocp.h"
#include "src/core/lib/event_engine/windows/windows_endpoint.h"
#include "src/core/lib/event_engine/windows/windows_engine.h"
#include "src/core/lib/resource_quota/memory_quota.h"
#include "src/core/util/notification.h"
#include "test/core/event_engine/windows/create_sockpair.h"

namespace grpc_event_engine {
namespace experimental {

using namespace std::chrono_literals;

class WindowsEndpointTest : public testing::Test {};

TEST_F(WindowsEndpointTest, BasicCommunication) {

  auto thread_pool = MakeThreadPool(8);
  IOCP iocp(thread_pool.get());
  grpc_core::MemoryQuota quota("endpoint_test");
  SOCKET sockpair[2];
  CreateSockpair(sockpair, IOCP::GetDefaultSocketFlags());
  auto wrapped_client_socket = iocp.Watch(sockpair[0]);
  auto wrapped_server_socket = iocp.Watch(sockpair[1]);
  sockaddr_in loopback_addr = GetSomeIpv4LoopbackAddress();
  auto engine = std::make_shared<WindowsEventEngine>();
  EventEngine::ResolvedAddress addr((sockaddr*)&loopback_addr,
                                    sizeof(loopback_addr));
  WindowsEndpoint client(addr, std::move(wrapped_client_socket),
                         quota.CreateMemoryAllocator("client"),
                         ChannelArgsEndpointConfig(), thread_pool.get(),
                         engine);
  WindowsEndpoint server(addr, std::move(wrapped_server_socket),
                         quota.CreateMemoryAllocator("server"),
                         ChannelArgsEndpointConfig(), thread_pool.get(),
                         engine);

  std::string message = "0xDEADBEEF";
  grpc_core::Notification read_done;
  SliceBuffer read_buffer;
  EXPECT_FALSE(server.Read(
      [&read_done, &message, &read_buffer](absl::Status) {
        ASSERT_EQ(read_buffer.Count(), 1u);
        auto slice = read_buffer.TakeFirst();
        EXPECT_EQ(slice.as_string_view(), message);
        read_done.Notify();
      },
      &read_buffer, EventEngine::Endpoint::ReadArgs()));
  grpc_core::Notification write_done;
  SliceBuffer write_buffer;
  write_buffer.Append(Slice::FromCopiedString(message));
  EXPECT_FALSE(
      client.Write([&write_done](absl::Status) { write_done.Notify(); },
                   &write_buffer, EventEngine::Endpoint::WriteArgs()));
  iocp.Work(5s, []() {});

  write_done.WaitForNotification();
  read_done.WaitForNotification();
  thread_pool->Quiesce();
}

TEST_F(WindowsEndpointTest, Conversation) {

  auto thread_pool = MakeThreadPool(8);
  IOCP iocp(thread_pool.get());
  grpc_core::MemoryQuota quota("endpoint_test");
  SOCKET sockpair[2];
  CreateSockpair(sockpair, IOCP::GetDefaultSocketFlags());
  sockaddr_in loopback_addr = GetSomeIpv4LoopbackAddress();
  EventEngine::ResolvedAddress addr((sockaddr*)&loopback_addr,
                                    sizeof(loopback_addr));

  struct AppState {
    AppState(const EventEngine::ResolvedAddress& addr,
             std::unique_ptr<WinSocket> client,
             std::unique_ptr<WinSocket> server, grpc_core::MemoryQuota& quota,
             ThreadPool* thread_pool, std::shared_ptr<EventEngine> engine)
        : client(addr, std::move(client), quota.CreateMemoryAllocator("client"),
                 ChannelArgsEndpointConfig(), thread_pool, engine),
          server(addr, std::move(server), quota.CreateMemoryAllocator("server"),
                 ChannelArgsEndpointConfig(), thread_pool, engine) {}
    grpc_core::Notification done;
    WindowsEndpoint client;
    WindowsEndpoint server;
    SliceBuffer read_buffer;
    SliceBuffer write_buffer;
    const std::vector<std::string> messages{
        "Java is to Javascript what car is to carpet. -Heilmann",
        "Make it work, make it right, make it fast. -Beck",
        "First, solve the problem. Then write the code. -Johnson",
        "It works on my machine."};

    std::atomic<size_t> exchange{0};

    void WriteAndQueueReader(WindowsEndpoint* writer, WindowsEndpoint* reader) {
      write_buffer.Clear();
      write_buffer.Append(Slice::FromCopiedString(messages[exchange]));
      EXPECT_FALSE(writer->Write([](absl::Status) {}, &write_buffer,
                                 EventEngine::Endpoint::WriteArgs()));
      auto cb = [this](absl::Status status) { ReadCB(status); };
      read_buffer.Clear();
      EXPECT_FALSE(
          reader->Read(cb, &read_buffer, EventEngine::Endpoint::ReadArgs()));
    }

    void ReadCB(absl::Status) {
      ASSERT_EQ(read_buffer.Count(), 1u);
      ASSERT_EQ(read_buffer.TakeFirst().as_string_view(), messages[exchange]);
      if (++exchange == messages.size()) {
        done.Notify();
        return;
      }
      if (exchange % 2 == 0) {
        WriteAndQueueReader(&client, &server);
      } else {
        WriteAndQueueReader(&server, &client);
      }
    }
  };
  auto engine = std::make_shared<WindowsEventEngine>();
  AppState state(addr, iocp.Watch(sockpair[0]),
                 iocp.Watch(sockpair[1]), quota, thread_pool.get(),
                 engine);
  state.WriteAndQueueReader(&state.client, &state.server);
  while (iocp.Work(100ms, []() {}) == Poller::WorkResult::kOk ||
         !state.done.HasBeenNotified()) {
  }

  state.done.WaitForNotification();
  thread_pool->Quiesce();
}

}
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
