// Copyright 2022 gRPC authors.

#include <grpc/event_engine/event_engine.h>
#include <grpc/event_engine/memory_allocator.h>
#include <grpc/impl/channel_arg_names.h>

#include <algorithm>
#include <chrono>
#include <memory>
#include <string>
#include <thread>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>

#include "absl/log/check.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/str_cat.h"
#include "absl/time/clock.h"
#include "absl/time/time.h"
#include "gtest/gtest.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/event_engine/channel_args_endpoint_config.h"
#include "src/core/lib/event_engine/tcp_socket_utils.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/resource_quota/memory_quota.h"
#include "src/core/lib/resource_quota/resource_quota.h"
#include "src/core/util/notification.h"
#include "test/core/event_engine/event_engine_test_utils.h"
#include "test/core/event_engine/test_suite/event_engine_test_framework.h"
#include "test/core/test_util/port.h"

namespace grpc_event_engine {
namespace experimental {

void InitServerTests() {}

}
}

class EventEngineServerTest : public EventEngineTest {};

using namespace std::chrono_literals;

namespace {

using ::grpc_event_engine::experimental::ChannelArgsEndpointConfig;
using ::grpc_event_engine::experimental::EventEngine;
using ::grpc_event_engine::experimental::URIToResolvedAddress;
using Endpoint = ::grpc_event_engine::experimental::EventEngine::Endpoint;
using Listener = ::grpc_event_engine::experimental::EventEngine::Listener;
using ::grpc_event_engine::experimental::GetNextSendMessage;

constexpr int kNumExchangedMessages = 100;

}

TEST_F(EventEngineServerTest, CannotBindAfterStarted) {
  std::shared_ptr<EventEngine> engine(this->NewEventEngine());
  ChannelArgsEndpointConfig config;
  auto listener = engine->CreateListener(
      [](std::unique_ptr<Endpoint>, grpc_core::MemoryAllocator) {},
      [](absl::Status) {}, config,
      std::make_unique<grpc_core::MemoryQuota>("foo"));

  auto resolved_addr = URIToResolvedAddress(absl::StrCat(
      "ipv6:[::1]:", std::to_string(grpc_pick_unused_port_or_die())));
  ASSERT_TRUE(resolved_addr.ok()) << resolved_addr.status();
  auto bind_result = (*listener)->Bind(*resolved_addr);
  ASSERT_TRUE(bind_result.ok()) << bind_result.status();
  auto listen_result = (*listener)->Start();
  ASSERT_TRUE(listen_result.ok()) << listen_result;

  auto resolved_addr2 = URIToResolvedAddress(absl::StrCat(
      "ipv6:[::1]:", std::to_string(grpc_pick_unused_port_or_die())));
  ASSERT_TRUE(resolved_addr2.ok());
  ASSERT_FALSE((*listener)->Bind(*resolved_addr2).ok());
}

TEST_F(EventEngineServerTest, ServerConnectExchangeBidiDataTransferTest) {
  grpc_core::ExecCtx ctx;
  std::shared_ptr<EventEngine> oracle_ee(this->NewOracleEventEngine());
  std::shared_ptr<EventEngine> test_ee(this->NewEventEngine());
  auto memory_quota = std::make_unique<grpc_core::MemoryQuota>("bar");
  std::string target_addr = absl::StrCat(
      "ipv6:[::1]:", std::to_string(grpc_pick_unused_port_or_die()));
  auto resolved_addr = URIToResolvedAddress(target_addr);
  CHECK_OK(resolved_addr);
  std::unique_ptr<EventEngine::Endpoint> client_endpoint;
  std::unique_ptr<EventEngine::Endpoint> server_endpoint;
  grpc_core::Notification client_signal;
  grpc_core::Notification server_signal;

  Listener::AcceptCallback accept_cb =
      [&server_endpoint, &server_signal](
          std::unique_ptr<Endpoint> ep,
          grpc_core::MemoryAllocator ) {
        server_endpoint = std::move(ep);
        server_signal.Notify();
      };

  grpc_core::ChannelArgs args;
  auto quota = grpc_core::ResourceQuota::Default();
  args = args.Set(GRPC_ARG_RESOURCE_QUOTA, quota);
  ChannelArgsEndpointConfig config(args);
  auto listener = *test_ee->CreateListener(
      std::move(accept_cb),
      [](absl::Status status) {
        ASSERT_TRUE(status.ok()) << status.ToString();
      },
      config, std::make_unique<grpc_core::MemoryQuota>("foo"));

  ASSERT_TRUE(listener->Bind(*resolved_addr).ok());
  ASSERT_TRUE(listener->Start().ok());

  oracle_ee->Connect(
      [&client_endpoint,
       &client_signal](absl::StatusOr<std::unique_ptr<Endpoint>> endpoint) {
        ASSERT_TRUE(endpoint.ok()) << endpoint.status();
        client_endpoint = std::move(*endpoint);
        client_signal.Notify();
      },
      *resolved_addr, config, memory_quota->CreateMemoryAllocator("conn-1"),
      24h);

  client_signal.WaitForNotification();
  server_signal.WaitForNotification();
  ASSERT_NE(client_endpoint.get(), nullptr);
  ASSERT_NE(server_endpoint.get(), nullptr);

  for (int i = 0; i < kNumExchangedMessages; i++) {

    ASSERT_TRUE(SendValidatePayload(GetNextSendMessage(), client_endpoint.get(),
                                    server_endpoint.get())
                    .ok());

    ASSERT_TRUE(SendValidatePayload(GetNextSendMessage(), server_endpoint.get(),
                                    client_endpoint.get())
                    .ok());
  }
  client_endpoint.reset();
  server_endpoint.reset();
  listener.reset();
}

TEST_F(EventEngineServerTest,
       ServerMultipleIPv6ConnectionsToOneOracleListenerTest) {
  grpc_core::ExecCtx ctx;
  static constexpr int kNumListenerAddresses = 10;
  static constexpr int kNumConnections = 10;
  std::shared_ptr<EventEngine> oracle_ee(this->NewOracleEventEngine());
  std::shared_ptr<EventEngine> test_ee(this->NewEventEngine());
  auto memory_quota = std::make_unique<grpc_core::MemoryQuota>("bar");
  std::unique_ptr<EventEngine::Endpoint> server_endpoint;

  grpc_core::Notification* server_signal = new grpc_core::Notification();
  std::vector<std::string> target_addrs;
  std::vector<std::tuple<std::unique_ptr<Endpoint>, std::unique_ptr<Endpoint>>>
      connections;

  Listener::AcceptCallback accept_cb =
      [&server_endpoint, &server_signal](
          std::unique_ptr<Endpoint> ep,
          grpc_core::MemoryAllocator ) {
        server_endpoint = std::move(ep);
        server_signal->Notify();
      };
  grpc_core::ChannelArgs args;
  auto quota = grpc_core::ResourceQuota::Default();
  args = args.Set(GRPC_ARG_RESOURCE_QUOTA, quota);
  ChannelArgsEndpointConfig config(args);
  auto listener = *test_ee->CreateListener(
      std::move(accept_cb),
      [](absl::Status status) {
        ASSERT_TRUE(status.ok()) << status.ToString();
      },
      config, std::make_unique<grpc_core::MemoryQuota>("foo"));

  target_addrs.reserve(kNumListenerAddresses);
  for (int i = 0; i < kNumListenerAddresses; i++) {
    std::string target_addr = absl::StrCat(
        "ipv6:[::1]:", std::to_string(grpc_pick_unused_port_or_die()));
    ASSERT_TRUE(listener->Bind(*URIToResolvedAddress(target_addr)).ok());
    target_addrs.push_back(target_addr);
  }
  ASSERT_TRUE(listener->Start().ok());
  absl::SleepFor(absl::Milliseconds(500));
  for (int i = 0; i < kNumConnections; i++) {
    std::unique_ptr<EventEngine::Endpoint> client_endpoint;
    grpc_core::Notification client_signal;

    grpc_core::ChannelArgs client_args;
    auto client_quota = grpc_core::ResourceQuota::Default();
    client_args = client_args.Set(GRPC_ARG_RESOURCE_QUOTA, client_quota);
    ChannelArgsEndpointConfig client_config(client_args);
    oracle_ee->Connect(
        [&client_endpoint,
         &client_signal](absl::StatusOr<std::unique_ptr<Endpoint>> endpoint) {
          ASSERT_TRUE(endpoint.ok());
          client_endpoint = std::move(*endpoint);
          client_signal.Notify();
        },
        *URIToResolvedAddress(target_addrs[i % kNumListenerAddresses]),
        client_config,
        memory_quota->CreateMemoryAllocator(
            absl::StrCat("conn-", std::to_string(i))),
        24h);

    client_signal.WaitForNotification();
    server_signal->WaitForNotification();
    ASSERT_NE(client_endpoint.get(), nullptr);
    ASSERT_NE(server_endpoint.get(), nullptr);
    connections.push_back(
        std::tuple(std::move(client_endpoint), std::move(server_endpoint)));
    delete server_signal;
    server_signal = new grpc_core::Notification();
  }
  delete server_signal;

  std::vector<std::thread> threads;

  threads.reserve(kNumConnections);
  for (int i = 0; i < kNumConnections; i++) {

    threads.emplace_back([client_endpoint =
                              std::move(std::get<0>(connections[i])),
                          server_endpoint =
                              std::move(std::get<1>(connections[i]))]() {
      std::vector<std::thread> workers;
      workers.reserve(2);
      auto worker = [client_endpoint = client_endpoint.get(),
                     server_endpoint =
                         server_endpoint.get()](bool client_to_server) {
        grpc_core::ExecCtx ctx;
        for (int i = 0; i < kNumExchangedMessages; i++) {

          if (client_to_server) {
            ASSERT_TRUE(SendValidatePayload(GetNextSendMessage(),
                                            client_endpoint, server_endpoint)
                            .ok());
          } else {
            ASSERT_TRUE(SendValidatePayload(GetNextSendMessage(),
                                            server_endpoint, client_endpoint)
                            .ok());
          }
        }
      };

      workers.emplace_back([&worker]() { worker(true); });

      workers.emplace_back([&worker]() { worker(false); });
      workers[0].join();
      workers[1].join();
    });
  }
  for (auto& t : threads) {
    t.join();
  }
  server_endpoint.reset();
  listener.reset();
}
