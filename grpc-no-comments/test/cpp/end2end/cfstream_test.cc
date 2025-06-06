
// Copyright 2019 The gRPC Authors

#include <grpc/grpc.h>
#include <grpc/support/alloc.h>
#include <grpc/support/atm.h>
#include <grpc/support/string_util.h>
#include <grpc/support/time.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/health_check_service_interface.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>

#include <algorithm>
#include <memory>
#include <mutex>
#include <random>
#include <thread>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "gtest/gtest.h"
#include "src/core/lib/iomgr/port.h"
#include "src/core/util/backoff.h"
#include "src/core/util/crash.h"
#include "src/core/util/env.h"
#include "src/proto/grpc/testing/echo.grpc.pb.h"
#include "test/core/test_util/port.h"
#include "test/core/test_util/test_config.h"
#include "test/cpp/end2end/test_service_impl.h"
#include "test/cpp/util/test_credentials_provider.h"

#ifdef GRPC_CFSTREAM
using grpc::ClientAsyncResponseReader;
using grpc::testing::EchoRequest;
using grpc::testing::EchoResponse;
using grpc::testing::RequestParams;
using std::chrono::system_clock;

namespace grpc {
namespace testing {
namespace {

struct TestScenario {
  TestScenario(const std::string& creds_type, const std::string& content)
      : credentials_type(creds_type), message_content(content) {}
  const std::string credentials_type;
  const std::string message_content;
};

class CFStreamTest : public ::testing::TestWithParam<TestScenario> {
 protected:
  CFStreamTest()
      : server_host_("grpctest"),
        interface_("lo0"),
        ipv4_address_("10.0.0.1") {}

  void DNSUp() {
    std::ostringstream cmd;

    cmd << "echo '" << ipv4_address_ << "      " << server_host_
        << "  ' | sudo tee -a /etc/hosts";
    std::system(cmd.str().c_str());
  }

  void DNSDown() {
    std::ostringstream cmd;

    cmd << "sudo sed -i '.bak' '/" << server_host_ << "/d' /etc/hosts";
    std::system(cmd.str().c_str());
  }

  void InterfaceUp() {
    std::ostringstream cmd;
    cmd << "sudo /sbin/ifconfig " << interface_ << " alias " << ipv4_address_;
    std::system(cmd.str().c_str());
  }

  void InterfaceDown() {
    std::ostringstream cmd;
    cmd << "sudo /sbin/ifconfig " << interface_ << " -alias " << ipv4_address_;
    std::system(cmd.str().c_str());
  }

  void NetworkUp() {
    VLOG(2) << "Bringing network up";
    InterfaceUp();
    DNSUp();
  }

  void NetworkDown() {
    VLOG(2) << "Bringing network down";
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
    port_ = grpc_pick_unused_port_or_die();
    server_.reset(new ServerData(port_, GetParam().credentials_type));
    server_->Start(server_host_);
  }
  void StopServer() { server_->Shutdown(); }

  std::unique_ptr<grpc::testing::EchoTestService::Stub> BuildStub(
      const std::shared_ptr<Channel>& channel) {
    return grpc::testing::EchoTestService::NewStub(channel);
  }

  std::shared_ptr<Channel> BuildChannel() {
    std::ostringstream server_address;
    server_address << server_host_ << ":" << port_;
    ChannelArguments args;
    auto channel_creds = GetCredentialsProvider()->GetChannelCredentials(
        GetParam().credentials_type, &args);
    return CreateCustomChannel(server_address.str(), channel_creds, args);
  }

  void SendRpc(
      const std::unique_ptr<grpc::testing::EchoTestService::Stub>& stub,
      bool expect_success = false) {
    auto response = std::unique_ptr<EchoResponse>(new EchoResponse());
    EchoRequest request;
    auto& msg = GetParam().message_content;
    request.set_message(msg);
    ClientContext context;
    Status status = stub->Echo(&context, request, response.get());
    if (status.ok()) {
      VLOG(2) << "RPC with succeeded";
      EXPECT_EQ(msg, response->message());
    } else {
      VLOG(2) << "RPC failed: " << status.error_message();
    }
    if (expect_success) {
      EXPECT_TRUE(status.ok());
    }
  }
  void SendAsyncRpc(
      const std::unique_ptr<grpc::testing::EchoTestService::Stub>& stub,
      RequestParams param = RequestParams()) {
    EchoRequest request;
    request.set_message(GetParam().message_content);
    *request.mutable_param() = std::move(param);
    AsyncClientCall* call = new AsyncClientCall;

    call->response_reader =
        stub->PrepareAsyncEcho(&call->context, request, &cq_);

    call->response_reader->StartCall();
    call->response_reader->Finish(&call->reply, &call->status, (void*)call);
  }

  void ShutdownCQ() { cq_.Shutdown(); }

  bool CQNext(void** tag, bool* ok) {
    auto deadline = std::chrono::system_clock::now() + std::chrono::seconds(10);
    auto ret = cq_.AsyncNext(tag, ok, deadline);
    if (ret == grpc::CompletionQueue::GOT_EVENT) {
      return true;
    } else if (ret == grpc::CompletionQueue::SHUTDOWN) {
      return false;
    } else {
      CHECK(ret == grpc::CompletionQueue::TIMEOUT);

      return false;
    }
  }

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

  bool WaitForChannelReady(Channel* channel, int timeout_seconds = 10) {
    const gpr_timespec deadline =
        grpc_timeout_seconds_to_deadline(timeout_seconds);
    grpc_connectivity_state state;
    while ((state = channel->GetState(true )) !=
           GRPC_CHANNEL_READY) {
      if (!channel->WaitForStateChange(state, deadline)) return false;
    }
    return true;
  }

  struct AsyncClientCall {
    EchoResponse reply;
    ClientContext context;
    Status status;
    std::unique_ptr<ClientAsyncResponseReader<EchoResponse>> response_reader;
  };

 private:
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
      thread_.reset(new std::thread(
          std::bind(&ServerData::Serve, this, server_host, &mu, &cond)));
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

    void Shutdown(bool join = true) {
      server_->Shutdown(grpc_timeout_milliseconds_to_deadline(0));
      if (join) thread_->join();
    }
  };

  CompletionQueue cq_;
  const std::string server_host_;
  const std::string interface_;
  const std::string ipv4_address_;
  std::unique_ptr<ServerData> server_;
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

INSTANTIATE_TEST_SUITE_P(CFStreamTest, CFStreamTest,
                         ::testing::ValuesIn(CreateTestScenarios()));

TEST_P(CFStreamTest, NetworkTransition) {
  auto channel = BuildChannel();
  auto stub = BuildStub(channel);

  SendRpc(stub, true);
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

  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  NetworkUp();

  EXPECT_TRUE(WaitForChannelReady(channel.get()));
  EXPECT_EQ(channel->GetState(false), GRPC_CHANNEL_READY);
  shutdown.store(true);
  sender.join();
}

TEST_P(CFStreamTest, NetworkFlapRpcsInFlight) {
  auto channel = BuildChannel();
  auto stub = BuildStub(channel);
  std::atomic_int rpcs_sent{0};

  for (int i = 0; i < 10; ++i) {
    RequestParams param;
    param.set_skip_cancelled_check(true);
    SendAsyncRpc(stub, param);
    ++rpcs_sent;
  }
  EXPECT_TRUE(WaitForChannelReady(channel.get()));

  NetworkDown();

  std::thread thd = std::thread([this, &rpcs_sent]() {
    void* got_tag;
    bool ok = false;
    bool network_down = true;
    int total_completions = 0;

    while (CQNext(&got_tag, &ok)) {
      ++total_completions;
      CHECK(ok);
      AsyncClientCall* call = static_cast<AsyncClientCall*>(got_tag);
      if (!call->status.ok()) {
        VLOG(2) << "RPC failed with error: " << call->status.error_message();

        if (network_down) {
          NetworkUp();
          network_down = false;
        }
      } else {
        VLOG(2) << "RPC succeeded";
      }
      delete call;
    }

    (void)rpcs_sent;

  });

  for (int i = 0; i < 100; ++i) {
    RequestParams param;
    param.set_skip_cancelled_check(true);
    SendAsyncRpc(stub, param);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    ++rpcs_sent;
  }

  ShutdownCQ();

  thd.join();
}

TEST_P(CFStreamTest, ConcurrentRpc) {
  auto channel = BuildChannel();
  auto stub = BuildStub(channel);
  std::atomic_int rpcs_sent{0};
  std::thread thd = std::thread([this, &rpcs_sent]() {
    void* got_tag;
    bool ok = false;
    int total_completions = 0;

    while (CQNext(&got_tag, &ok)) {
      ++total_completions;
      CHECK(ok);
      AsyncClientCall* call = static_cast<AsyncClientCall*>(got_tag);
      if (!call->status.ok()) {
        VLOG(2) << "RPC failed with error: " << call->status.error_message();

      } else {
        VLOG(2) << "RPC succeeded";
      }
      delete call;
    }

    (void)rpcs_sent;

  });

  for (int i = 0; i < 10; ++i) {
    if (i % 3 == 0) {
      RequestParams param;
      ErrorStatus* error = param.mutable_expected_error();
      error->set_code(StatusCode::INTERNAL);
      error->set_error_message("internal error");
      SendAsyncRpc(stub, param);
    } else if (i % 5 == 0) {
      RequestParams param;
      param.set_echo_metadata(true);
      DebugInfo* info = param.mutable_debug_info();
      info->add_stack_entries("stack_entry1");
      info->add_stack_entries("stack_entry2");
      info->set_detail("detailed debug info");
      SendAsyncRpc(stub, param);
    } else {
      SendAsyncRpc(stub);
    }
    ++rpcs_sent;
  }

  ShutdownCQ();

  thd.join();
}

}
}
}
#endif

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  grpc::testing::TestEnvironment env(&argc, argv);
  grpc_core::SetEnv("grpc_cfstream", "1");
  const auto result = RUN_ALL_TESTS();
  return result;
}
