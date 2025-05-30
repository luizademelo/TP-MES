
// Copyright 2019 gRPC authors.

#include <grpc/grpc.h>
#include <grpc/support/alloc.h>
#include <grpc/support/atm.h>
#include <grpc/support/port_platform.h>
#include <grpc/support/string_util.h>
#include <grpc/support/time.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/health_check_service_interface.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>

#include <algorithm>
#include <condition_variable>
#include <memory>
#include <mutex>
#include <random>
#include <thread>

#include "absl/log/log.h"
#include "absl/memory/memory.h"
#include "gtest/gtest.h"
#include "src/core/util/backoff.h"
#include "src/core/util/crash.h"
#include "src/core/util/env.h"
#include "src/proto/grpc/testing/echo.grpc.pb.h"
#include "test/core/test_util/port.h"
#include "test/core/test_util/test_config.h"
#include "test/cpp/end2end/test_service_impl.h"
#include "test/cpp/util/test_credentials_provider.h"

#ifdef GPR_LINUX

namespace grpc {
namespace testing {
namespace {

struct TestScenario {
  TestScenario(const std::string& creds_type, const std::string& content)
      : credentials_type(creds_type), message_content(content) {}
  const std::string credentials_type;
  const std::string message_content;
};

class FlakyNetworkTest : public ::testing::TestWithParam<TestScenario> {
 protected:
  FlakyNetworkTest()
      : server_host_("grpctest"),
        interface_("lo:1"),
        ipv4_address_("10.0.0.1"),
        netmask_("/32") {}

  void InterfaceUp() {
    std::ostringstream cmd;

    cmd << "ip addr add " << ipv4_address_ << netmask_ << " dev " << interface_;
    std::system(cmd.str().c_str());
  }

  void InterfaceDown() {
    std::ostringstream cmd;

    cmd << "ip addr del " << ipv4_address_ << netmask_ << " dev " << interface_;
    std::system(cmd.str().c_str());
  }

  void DNSUp() {
    std::ostringstream cmd;

    cmd << "echo '" << ipv4_address_ << "      " << server_host_
        << "' >> /etc/hosts";
    std::system(cmd.str().c_str());
  }

  void DNSDown() {
    std::ostringstream cmd;

    // NOTE: we can't do this in one step with sed -i because when we are

    cmd << "sed  '/" << server_host_ << "/d' /etc/hosts > /etc/hosts.orig";
    std::system(cmd.str().c_str());

    cmd.str("");

    cmd << "cat /etc/hosts.orig > /etc/hosts";
    std::system(cmd.str().c_str());
  }

  void DropPackets() {
    std::ostringstream cmd;

    cmd << "iptables -A INPUT -s " << ipv4_address_ << " -j DROP";

    std::system(cmd.str().c_str());

    cmd.str("");

    cmd << "iptables -A INPUT -d " << ipv4_address_ << " -j DROP";
  }

  void RestoreNetwork() {
    std::ostringstream cmd;

    cmd << "iptables -D INPUT -s " << ipv4_address_ << " -j DROP";
    std::system(cmd.str().c_str());

    cmd.str("");

    cmd << "iptables -D INPUT -d " << ipv4_address_ << " -j DROP";
  }

  void FlakeNetwork() {
    std::ostringstream cmd;

    cmd << "tc qdisc replace dev " << interface_
        << " root netem delay 100ms 20ms distribution normal loss 0.1% "
           "duplicate "
           "0.1% corrupt 0.01% ";
    std::system(cmd.str().c_str());
  }

  void UnflakeNetwork() {

    std::ostringstream cmd;
    cmd << "tc qdisc del dev " << interface_ << " root netem";
    std::system(cmd.str().c_str());
  }

  void NetworkUp() {
    InterfaceUp();
    DNSUp();
  }

  void NetworkDown() {
    InterfaceDown();
    DNSDown();
  }

  void SetUp() override {
    NetworkUp();
    grpc_init();
    StartServer();
  }

  void TearDown() override {
    NetworkDown();
    StopServer();
    grpc_shutdown();
  }

  void StartServer() {

    port_ = SERVER_PORT;

    server_ = std::make_unique<ServerData>(port_, GetParam().credentials_type);
    server_->Start(server_host_);
  }
  void StopServer() { server_->Shutdown(); }

  std::unique_ptr<grpc::testing::EchoTestService::Stub> BuildStub(
      const std::shared_ptr<Channel>& channel) {
    return grpc::testing::EchoTestService::NewStub(channel);
  }

  std::shared_ptr<Channel> BuildChannel(
      const std::string& lb_policy_name,
      ChannelArguments args = ChannelArguments()) {
    if (!lb_policy_name.empty()) {
      args.SetLoadBalancingPolicyName(lb_policy_name);
    }
    auto channel_creds = GetCredentialsProvider()->GetChannelCredentials(
        GetParam().credentials_type, &args);
    std::ostringstream server_address;
    server_address << server_host_ << ":" << port_;
    return CreateCustomChannel(server_address.str(), channel_creds, args);
  }

  bool SendRpc(
      const std::unique_ptr<grpc::testing::EchoTestService::Stub>& stub,
      int timeout_ms = 0, bool wait_for_ready = false) {
    auto response = std::make_unique<EchoResponse>();
    EchoRequest request;
    auto& msg = GetParam().message_content;
    request.set_message(msg);
    ClientContext context;
    if (timeout_ms > 0) {
      context.set_deadline(grpc_timeout_milliseconds_to_deadline(timeout_ms));

      request.mutable_param()->set_skip_cancelled_check(true);
    }

    if (wait_for_ready) {
      context.set_wait_for_ready(true);
    }
    Status status = stub->Echo(&context, request, response.get());
    auto ok = status.ok();
    if (ok) {
      VLOG(2) << "RPC succeeded";
    } else {
      VLOG(2) << "RPC failed: " << status.error_message();
    }
    return ok;
  }

  struct ServerData {
    int port_;
    const std::string creds_;
    std::unique_ptr<Server> server_;
    TestServiceImpl service_;
    std::unique_ptr<std::thread> thread_;
    bool server_ready_ = false;

    ServerData(int port, const std::string& creds)
        : port_(port), creds_(creds) {}

    void Start(const std::string& server_host) {
      LOG(INFO) << "starting server on port " << port_;
      std::mutex mu;
      std::unique_lock<std::mutex> lock(mu);
      std::condition_variable cond;
      thread_ = std::make_unique<std::thread>(
          std::bind(&ServerData::Serve, this, server_host, &mu, &cond));
      cond.wait(lock, [this] { return server_ready_; });
      server_ready_ = false;
      LOG(INFO) << "server startup complete";
    }

    void Serve(const std::string& server_host, std::mutex* mu,
               std::condition_variable* cond) {
      std::ostringstream server_address;
      server_address << server_host << ":" << port_;
      ServerBuilder builder;
      auto server_creds =
          GetCredentialsProvider()->GetServerCredentials(creds_);
      builder.AddListeningPort(server_address.str(), server_creds);
      builder.RegisterService(&service_);
      server_ = builder.BuildAndStart();
      std::lock_guard<std::mutex> lock(*mu);
      server_ready_ = true;
      cond->notify_one();
    }

    void Shutdown() {
      server_->Shutdown(grpc_timeout_milliseconds_to_deadline(0));
      thread_->join();
    }
  };

  bool WaitForChannelNotReady(Channel* channel, int timeout_seconds = 5) {
    const gpr_timespec deadline =
        grpc_timeout_seconds_to_deadline(timeout_seconds);
    grpc_connectivity_state state;
    while ((state = channel->GetState(false )) ==
           GRPC_CHANNEL_READY) {
      if (!channel->WaitForStateChange(state, deadline)) return false;
    }
    return true;
  }

  bool WaitForChannelReady(Channel* channel, int timeout_seconds = 5) {
    const gpr_timespec deadline =
        grpc_timeout_seconds_to_deadline(timeout_seconds);
    grpc_connectivity_state state;
    while ((state = channel->GetState(true )) !=
           GRPC_CHANNEL_READY) {
      if (!channel->WaitForStateChange(state, deadline)) return false;
    }
    return true;
  }

 private:
  const std::string server_host_;
  const std::string interface_;
  const std::string ipv4_address_;
  const std::string netmask_;
  std::unique_ptr<grpc::testing::EchoTestService::Stub> stub_;
  std::unique_ptr<ServerData> server_;
  const int SERVER_PORT = 32750;
  int port_;
};

std::vector<TestScenario> CreateTestScenarios() {
  std::vector<TestScenario> scenarios;
  std::vector<std::string> credentials_types;
  std::vector<std::string> messages;

  credentials_types.push_back(kInsecureCredentialsType);
  auto sec_list = GetCredentialsProvider()->GetSecureCredentialsTypeList();
  for (auto sec = sec_list.begin(); sec != sec_list.end(); sec++) {
    credentials_types.push_back(*sec);
  }

  messages.push_back("🖖");
  for (size_t k = 1; k < GRPC_DEFAULT_MAX_RECV_MESSAGE_LENGTH / 1024; k *= 32) {
    std::string big_msg;
    for (size_t i = 0; i < k * 1024; ++i) {
      char c = 'a' + (i % 26);
      big_msg += c;
    }
    messages.push_back(big_msg);
  }
  for (auto cred = credentials_types.begin(); cred != credentials_types.end();
       ++cred) {
    for (auto msg = messages.begin(); msg != messages.end(); msg++) {
      scenarios.emplace_back(*cred, *msg);
    }
  }

  return scenarios;
}

INSTANTIATE_TEST_SUITE_P(FlakyNetworkTest, FlakyNetworkTest,
                         ::testing::ValuesIn(CreateTestScenarios()));

TEST_P(FlakyNetworkTest, NetworkTransition) {
  const int kKeepAliveTimeMs = 1000;
  const int kKeepAliveTimeoutMs = 1000;
  ChannelArguments args;
  args.SetInt(GRPC_ARG_KEEPALIVE_TIME_MS, kKeepAliveTimeMs);
  args.SetInt(GRPC_ARG_KEEPALIVE_TIMEOUT_MS, kKeepAliveTimeoutMs);
  args.SetInt(GRPC_ARG_KEEPALIVE_PERMIT_WITHOUT_CALLS, 1);
  args.SetInt(GRPC_ARG_HTTP2_MAX_PINGS_WITHOUT_DATA, 0);

  auto channel = BuildChannel("pick_first", args);
  auto stub = BuildStub(channel);

  EXPECT_TRUE(SendRpc(stub));
  EXPECT_EQ(channel->GetState(false), GRPC_CHANNEL_READY);

  std::atomic_bool shutdown{false};
  std::thread sender = std::thread([this, &stub, &shutdown]() {
    while (true) {
      if (shutdown.load()) {
        return;
      }
      SendRpc(stub);
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
  });

  NetworkDown();
  EXPECT_TRUE(WaitForChannelNotReady(channel.get()));

  InterfaceUp();
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));

  DNSUp();
  EXPECT_TRUE(WaitForChannelReady(channel.get()));
  EXPECT_EQ(channel->GetState(false), GRPC_CHANNEL_READY);
  shutdown.store(true);
  sender.join();
}

TEST_P(FlakyNetworkTest, ServerUnreachableWithKeepalive) {
  const int kKeepAliveTimeMs = 1000;
  const int kKeepAliveTimeoutMs = 1000;
  const int kReconnectBackoffMs = 1000;
  ChannelArguments args;
  args.SetInt(GRPC_ARG_KEEPALIVE_TIME_MS, kKeepAliveTimeMs);
  args.SetInt(GRPC_ARG_KEEPALIVE_TIMEOUT_MS, kKeepAliveTimeoutMs);
  args.SetInt(GRPC_ARG_KEEPALIVE_PERMIT_WITHOUT_CALLS, 1);
  args.SetInt(GRPC_ARG_HTTP2_MAX_PINGS_WITHOUT_DATA, 0);

  args.SetInt(GRPC_ARG_MIN_RECONNECT_BACKOFF_MS, kReconnectBackoffMs);

  args.SetInt(GRPC_ARG_MAX_RECONNECT_BACKOFF_MS, kReconnectBackoffMs);

  VLOG(2) << "FlakyNetworkTest.ServerUnreachableWithKeepalive start";
  auto channel = BuildChannel("pick_first", args);
  auto stub = BuildStub(channel);

  EXPECT_TRUE(SendRpc(stub));
  EXPECT_EQ(channel->GetState(false), GRPC_CHANNEL_READY);

  std::atomic_bool shutdown{false};
  std::thread sender = std::thread([this, &stub, &shutdown]() {
    while (true) {
      if (shutdown.load()) {
        return;
      }
      SendRpc(stub);
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
  });

  VLOG(2) << "Adding iptables rule to drop packets";
  DropPackets();
  std::this_thread::sleep_for(std::chrono::milliseconds(10000));
  EXPECT_TRUE(WaitForChannelNotReady(channel.get()));

  RestoreNetwork();
  VLOG(2) << "Removed iptables rule to drop packets";
  EXPECT_TRUE(WaitForChannelReady(channel.get()));
  EXPECT_EQ(channel->GetState(false), GRPC_CHANNEL_READY);
  shutdown.store(true);
  sender.join();
  VLOG(2) << "FlakyNetworkTest.ServerUnreachableWithKeepalive end";
}

TEST_P(FlakyNetworkTest, ServerUnreachableNoKeepalive) {
  auto channel = BuildChannel("pick_first", ChannelArguments());
  auto stub = BuildStub(channel);

  EXPECT_TRUE(SendRpc(stub));
  EXPECT_EQ(channel->GetState(false), GRPC_CHANNEL_READY);

  DropPackets();

  std::thread sender = std::thread([this, &stub]() {

    EXPECT_FALSE(SendRpc(stub, 500, true));

    EXPECT_TRUE(SendRpc(stub, 0, true));
  });

  std::this_thread::sleep_for(std::chrono::milliseconds(2000));

  RestoreNetwork();

  sender.join();
}

TEST_P(FlakyNetworkTest, FlakyNetwork) {
  const int kKeepAliveTimeMs = 1000;
  const int kKeepAliveTimeoutMs = 1000;
  const int kMessageCount = 100;
  ChannelArguments args;
  args.SetInt(GRPC_ARG_KEEPALIVE_TIME_MS, kKeepAliveTimeMs);
  args.SetInt(GRPC_ARG_KEEPALIVE_TIMEOUT_MS, kKeepAliveTimeoutMs);
  args.SetInt(GRPC_ARG_KEEPALIVE_PERMIT_WITHOUT_CALLS, 1);
  args.SetInt(GRPC_ARG_HTTP2_MAX_PINGS_WITHOUT_DATA, 0);

  auto channel = BuildChannel("pick_first", args);
  auto stub = BuildStub(channel);

  EXPECT_TRUE(SendRpc(stub));
  EXPECT_EQ(channel->GetState(false), GRPC_CHANNEL_READY);

  FlakeNetwork();
  for (int i = 0; i < kMessageCount; ++i) {
    SendRpc(stub);
  }

  UnflakeNetwork();
  EXPECT_EQ(channel->GetState(false), GRPC_CHANNEL_READY);
}

TEST_P(FlakyNetworkTest, ServerRestartKeepaliveEnabled) {
  const int kKeepAliveTimeMs = 1000;
  const int kKeepAliveTimeoutMs = 1000;
  ChannelArguments args;
  args.SetInt(GRPC_ARG_KEEPALIVE_TIME_MS, kKeepAliveTimeMs);
  args.SetInt(GRPC_ARG_KEEPALIVE_TIMEOUT_MS, kKeepAliveTimeoutMs);
  args.SetInt(GRPC_ARG_KEEPALIVE_PERMIT_WITHOUT_CALLS, 1);
  args.SetInt(GRPC_ARG_HTTP2_MAX_PINGS_WITHOUT_DATA, 0);

  auto channel = BuildChannel("pick_first", args);
  auto stub = BuildStub(channel);

  EXPECT_TRUE(SendRpc(stub));
  EXPECT_EQ(channel->GetState(false), GRPC_CHANNEL_READY);

  StopServer();
  EXPECT_TRUE(WaitForChannelNotReady(channel.get()));
  EXPECT_FALSE(SendRpc(stub));

  std::this_thread::sleep_for(std::chrono::milliseconds(1000));

  StartServer();
  EXPECT_TRUE(WaitForChannelReady(channel.get()));

}

TEST_P(FlakyNetworkTest, ServerRestartKeepaliveDisabled) {
  auto channel = BuildChannel("pick_first", ChannelArguments());
  auto stub = BuildStub(channel);

  EXPECT_TRUE(SendRpc(stub));
  EXPECT_EQ(channel->GetState(false), GRPC_CHANNEL_READY);

  StopServer();
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));

  EXPECT_TRUE(WaitForChannelNotReady(channel.get()));

  std::this_thread::sleep_for(std::chrono::milliseconds(1000));

  StartServer();
  EXPECT_TRUE(WaitForChannelReady(channel.get()));
}

}
}
}
#endif

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  grpc::testing::TestEnvironment env(&argc, argv);
  auto result = RUN_ALL_TESTS();
  return result;
}
