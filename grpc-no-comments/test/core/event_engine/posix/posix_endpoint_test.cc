// Copyright 2022 gRPC Authors

#include "src/core/lib/event_engine/posix_engine/posix_endpoint.h"

#include <grpc/event_engine/event_engine.h>
#include <grpc/grpc.h>
#include <grpc/impl/channel_arg_names.h>

#include <algorithm>
#include <chrono>
#include <list>
#include <memory>
#include <string>
#include <thread>
#include <type_traits>
#include <vector>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/status/statusor.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_split.h"
#include "absl/strings/string_view.h"
#include "gtest/gtest.h"
#include "src/core/config/config_vars.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/event_engine/channel_args_endpoint_config.h"
#include "src/core/lib/event_engine/poller.h"
#include "src/core/lib/event_engine/posix_engine/event_poller.h"
#include "src/core/lib/event_engine/posix_engine/event_poller_posix_default.h"
#include "src/core/lib/event_engine/posix_engine/posix_engine.h"
#include "src/core/lib/event_engine/posix_engine/posix_engine_closure.h"
#include "src/core/lib/event_engine/posix_engine/tcp_socket_utils.h"
#include "src/core/lib/event_engine/tcp_socket_utils.h"
#include "src/core/lib/resource_quota/resource_quota.h"
#include "src/core/util/dual_ref_counted.h"
#include "src/core/util/notification.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/wait_for_single_owner.h"
#include "test/core/event_engine/event_engine_test_utils.h"
#include "test/core/event_engine/posix/posix_engine_test_utils.h"
#include "test/core/event_engine/test_suite/posix/oracle_event_engine_posix.h"
#include "test/core/test_util/port.h"

namespace grpc_event_engine {
namespace experimental {

namespace {

using Endpoint = ::grpc_event_engine::experimental::EventEngine::Endpoint;
using Listener = ::grpc_event_engine::experimental::EventEngine::Listener;
using namespace std::chrono_literals;

constexpr int kMinMessageSize = 1024;
constexpr int kNumConnections = 10;
constexpr int kNumExchangedMessages = 100;
std::atomic<int> g_num_active_connections{0};

struct Connection {
  std::unique_ptr<EventEngine::Endpoint> client_endpoint;
  std::unique_ptr<EventEngine::Endpoint> server_endpoint;
};

std::list<Connection> CreateConnectedEndpoints(
    PosixEventPoller& poller, bool is_zero_copy_enabled, int num_connections,
    std::shared_ptr<EventEngine> posix_ee,
    std::shared_ptr<EventEngine> oracle_ee) {
  std::list<Connection> connections;
  auto memory_quota = std::make_unique<grpc_core::MemoryQuota>("bar");
  std::string target_addr = absl::StrCat(
      "ipv6:[::1]:", std::to_string(grpc_pick_unused_port_or_die()));
  auto resolved_addr = URIToResolvedAddress(target_addr);
  CHECK_OK(resolved_addr);
  std::unique_ptr<EventEngine::Endpoint> server_endpoint;
  grpc_core::Notification* server_signal = new grpc_core::Notification();

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
  if (is_zero_copy_enabled) {
    args = args.Set(GRPC_ARG_TCP_TX_ZEROCOPY_ENABLED, 1);
    args = args.Set(GRPC_ARG_TCP_TX_ZEROCOPY_SEND_BYTES_THRESHOLD,
                    kMinMessageSize);
  }
  ChannelArgsEndpointConfig config(args);
  auto listener = oracle_ee->CreateListener(
      std::move(accept_cb),
      [](absl::Status status) { ASSERT_TRUE(status.ok()); }, config,
      std::make_unique<grpc_core::MemoryQuota>("foo"));
  CHECK_OK(listener);

  EXPECT_TRUE((*listener)->Bind(*resolved_addr).ok());
  EXPECT_TRUE((*listener)->Start().ok());

  for (int i = 0; i < num_connections; ++i) {
    int client_fd = ConnectToServerOrDie(*resolved_addr);
    EventHandle* handle =
        poller.CreateHandle(client_fd, "test", poller.CanTrackErrors());
    EXPECT_NE(handle, nullptr);
    server_signal->WaitForNotification();
    EXPECT_NE(server_endpoint, nullptr);
    ++g_num_active_connections;
    PosixTcpOptions options = TcpOptionsFromEndpointConfig(config);
    connections.push_back(Connection{
        CreatePosixEndpoint(
            handle,
            PosixEngineClosure::TestOnlyToClosure(
                [&poller](absl::Status ) {
                  if (--g_num_active_connections == 0) {
                    poller.Kick();
                  }
                }),
            posix_ee,
            options.resource_quota->memory_quota()->CreateMemoryAllocator(
                "test"),
            options),
        std::move(server_endpoint)});
    delete server_signal;
    server_signal = new grpc_core::Notification();
  }
  delete server_signal;
  return connections;
}

}

std::string TestScenarioName(const ::testing::TestParamInfo<bool>& info) {
  return absl::StrCat("is_zero_copy_enabled_", info.param);
}

class Worker : public grpc_core::DualRefCounted<Worker> {
 public:
  Worker(std::shared_ptr<EventEngine> engine, PosixEventPoller* poller)
      : engine_(std::move(engine)), poller_(poller) {
    WeakRef().release();
  }
  void Orphaned() override { signal.Notify(); }
  void Start() {

    engine_->Run([this]() { Work(); });
  }

  void Wait() {
    signal.WaitForNotification();
    WeakUnref();
  }

 private:
  void Work() {
    auto result = poller_->Work(24h, [this]() {

      Ref().release();
      engine_->Run([this]() { Work(); });
    });
    ASSERT_TRUE(result == Poller::WorkResult::kOk ||
                result == Poller::WorkResult::kKicked);

    Unref();
  }
  std::shared_ptr<EventEngine> engine_;

  PosixEventPoller* poller_;
  grpc_core::Notification signal;
};

class PosixEndpointTest : public ::testing::TestWithParam<bool> {
  void SetUp() override {
    oracle_ee_ = std::make_shared<PosixOracleEventEngine>();
    scheduler_ =
        std::make_unique<grpc_event_engine::experimental::TestScheduler>(
            posix_ee_.get());
    EXPECT_NE(scheduler_, nullptr);
    poller_ = MakeDefaultPoller(scheduler_.get());
    posix_ee_ = PosixEventEngine::MakeTestOnlyPosixEventEngine(poller_);
    EXPECT_NE(posix_ee_, nullptr);
    scheduler_->ChangeCurrentEventEngine(posix_ee_.get());
    if (poller_ != nullptr) {
      LOG(INFO) << "Using poller: " << poller_->Name();
    }
  }

  void TearDown() override {
    if (poller_ != nullptr) {
      poller_->Shutdown();
    }
    grpc_core::WaitForSingleOwner(std::move(posix_ee_));
    grpc_core::WaitForSingleOwner(std::move(oracle_ee_));
  }

 public:
  TestScheduler* Scheduler() { return scheduler_.get(); }

  std::shared_ptr<EventEngine> GetPosixEE() { return posix_ee_; }

  std::shared_ptr<EventEngine> GetOracleEE() { return oracle_ee_; }

  PosixEventPoller* PosixPoller() { return poller_.get(); }

 private:
  std::shared_ptr<PosixEventPoller> poller_;
  std::unique_ptr<TestScheduler> scheduler_;
  std::shared_ptr<EventEngine> posix_ee_;
  std::shared_ptr<EventEngine> oracle_ee_;
};

TEST_P(PosixEndpointTest, ConnectExchangeBidiDataTransferTest) {
  if (PosixPoller() == nullptr) {
    return;
  }
  Worker* worker = new Worker(GetPosixEE(), PosixPoller());
  worker->Start();
  {
    auto connections = CreateConnectedEndpoints(*PosixPoller(), GetParam(), 1,
                                                GetPosixEE(), GetOracleEE());
    auto it = connections.begin();
    auto client_endpoint = std::move((*it).client_endpoint);
    auto server_endpoint = std::move((*it).server_endpoint);
    EXPECT_NE(client_endpoint, nullptr);
    EXPECT_NE(server_endpoint, nullptr);
    connections.erase(it);

    for (int i = 0; i < kNumExchangedMessages; i++) {

      ASSERT_TRUE(SendValidatePayload(GetNextSendMessage(),
                                      client_endpoint.get(),
                                      server_endpoint.get())
                      .ok());

      ASSERT_TRUE(SendValidatePayload(GetNextSendMessage(),
                                      server_endpoint.get(),
                                      client_endpoint.get())
                      .ok());
    }
  }
  worker->Wait();
}

TEST_P(PosixEndpointTest, MultipleIPv6ConnectionsToOneOracleListenerTest) {
  if (PosixPoller() == nullptr) {
    return;
  }
  Worker* worker = new Worker(GetPosixEE(), PosixPoller());
  worker->Start();
  auto connections = CreateConnectedEndpoints(
      *PosixPoller(), GetParam(), kNumConnections, GetPosixEE(), GetOracleEE());
  std::vector<std::thread> threads;

  threads.reserve(kNumConnections);
  for (int i = 0; i < kNumConnections; i++) {

    auto it = connections.begin();
    auto client_endpoint = std::move((*it).client_endpoint);
    auto server_endpoint = std::move((*it).server_endpoint);
    EXPECT_NE(client_endpoint, nullptr);
    EXPECT_NE(server_endpoint, nullptr);
    connections.erase(it);
    threads.emplace_back([client_endpoint = std::move(client_endpoint),
                          server_endpoint = std::move(server_endpoint)]() {
      std::vector<std::thread> workers;
      workers.reserve(2);
      auto worker = [client_endpoint = client_endpoint.get(),
                     server_endpoint =
                         server_endpoint.get()](bool client_to_server) {
        for (int i = 0; i < kNumExchangedMessages; i++) {

          if (client_to_server) {
            EXPECT_TRUE(SendValidatePayload(GetNextSendMessage(),
                                            client_endpoint, server_endpoint)
                            .ok());
          } else {
            EXPECT_TRUE(SendValidatePayload(GetNextSendMessage(),
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
  worker->Wait();
}

INSTANTIATE_TEST_SUITE_P(PosixEndpoint, PosixEndpointTest,
                         ::testing::ValuesIn({false, true}), &TestScenarioName);

}
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
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
