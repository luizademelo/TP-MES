// Copyright 2016 gRPC authors.

#include <grpc/event_engine/endpoint_config.h>
#include <grpc/grpc.h>
#include <grpc/support/alloc.h>
#include <grpc/support/atm.h>
#include <grpc/support/time.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/ext/call_metric_recorder.h>
#include <grpcpp/ext/orca_service.h>
#include <grpcpp/ext/server_metric_recorder.h>
#include <grpcpp/health_check_service_interface.h>
#include <grpcpp/impl/sync.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>

#include <algorithm>
#include <chrono>
#include <deque>
#include <memory>
#include <mutex>
#include <random>
#include <set>
#include <string>
#include <thread>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/memory/memory.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_format.h"
#include "absl/strings/str_join.h"
#include "absl/strings/string_view.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "src/core/client_channel/backup_poller.h"
#include "src/core/client_channel/config_selector.h"
#include "src/core/client_channel/global_subchannel_pool.h"
#include "src/core/config/config_vars.h"
#include "src/core/credentials/transport/fake/fake_credentials.h"
#include "src/core/lib/address_utils/parse_address.h"
#include "src/core/lib/address_utils/sockaddr_utils.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/iomgr/tcp_client.h"
#include "src/core/lib/transport/connectivity_state.h"
#include "src/core/resolver/endpoint_addresses.h"
#include "src/core/resolver/fake/fake_resolver.h"
#include "src/core/server/server.h"
#include "src/core/service_config/service_config.h"
#include "src/core/service_config/service_config_impl.h"
#include "src/core/util/backoff.h"
#include "src/core/util/crash.h"
#include "src/core/util/debug_location.h"
#include "src/core/util/env.h"
#include "src/core/util/notification.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/time.h"
#include "src/cpp/server/secure_server_credentials.h"
#include "src/proto/grpc/health/v1/health.grpc.pb.h"
#include "src/proto/grpc/testing/echo.grpc.pb.h"
#include "test/core/test_util/port.h"
#include "test/core/test_util/postmortem.h"
#include "test/core/test_util/resolve_localhost_ip46.h"
#include "test/core/test_util/test_config.h"
#include "test/core/test_util/test_lb_policies.h"
#include "test/cpp/end2end/connection_attempt_injector.h"
#include "test/cpp/end2end/test_service_impl.h"
#include "test/cpp/util/credentials.h"
#include "xds/data/orca/v3/orca_load_report.pb.h"

namespace grpc {
namespace testing {
namespace {

using xds::data::orca::v3::OrcaLoadReport;
constexpr char kRequestMessage[] = "Live long and prosper.";

class NoopHealthCheckServiceImpl : public health::v1::Health::Service {
 public:
  ~NoopHealthCheckServiceImpl() override = default;
  Status Check(ServerContext*, const health::v1::HealthCheckRequest*,
               health::v1::HealthCheckResponse*) override {
    return Status::OK;
  }
  Status Watch(ServerContext*, const health::v1::HealthCheckRequest*,
               ServerWriter<health::v1::HealthCheckResponse>*) override {
    grpc_core::MutexLock lock(&mu_);
    request_count_++;
    return Status::OK;
  }
  int request_count() {
    grpc_core::MutexLock lock(&mu_);
    return request_count_;
  }

 private:
  grpc_core::Mutex mu_;
  int request_count_ ABSL_GUARDED_BY(&mu_) = 0;
};

class MyTestServiceImpl : public TestServiceImpl {
 public:
  Status Echo(ServerContext* context, const EchoRequest* request,
              EchoResponse* response) override {
    {
      grpc_core::MutexLock lock(&mu_);
      ++request_count_;
    }
    AddClient(context->peer());
    if (request->has_param() && request->param().has_backend_metrics()) {
      const auto& request_metrics = request->param().backend_metrics();
      auto* recorder = context->ExperimentalGetCallMetricRecorder();
      EXPECT_NE(recorder, nullptr);

      if (request_metrics.application_utilization() > 0) {
        recorder->RecordApplicationUtilizationMetric(
            request_metrics.application_utilization());
      }
      if (request_metrics.cpu_utilization() > 0) {
        recorder->RecordCpuUtilizationMetric(request_metrics.cpu_utilization());
      }
      if (request_metrics.mem_utilization() > 0) {
        recorder->RecordMemoryUtilizationMetric(
            request_metrics.mem_utilization());
      }
      if (request_metrics.rps_fractional() > 0) {
        recorder->RecordQpsMetric(request_metrics.rps_fractional());
      }
      if (request_metrics.eps() > 0) {
        recorder->RecordEpsMetric(request_metrics.eps());
      }
      for (const auto& [key, value] : request_metrics.request_cost()) {
        char* key_copy = static_cast<char*>(
            grpc_call_arena_alloc(context->c_call(), key.size() + 1));
        strncpy(key_copy, key.data(), key.size());
        key_copy[key.size()] = '\0';
        recorder->RecordRequestCostMetric(key_copy, value);
      }
      for (const auto& [key, value] : request_metrics.utilization()) {
        char* key_copy = static_cast<char*>(
            grpc_call_arena_alloc(context->c_call(), key.size() + 1));
        strncpy(key_copy, key.data(), key.size());
        key_copy[key.size()] = '\0';
        recorder->RecordUtilizationMetric(key_copy, value);
      }
      for (const auto& [key, value] : request_metrics.named_metrics()) {
        char* key_copy = static_cast<char*>(
            grpc_call_arena_alloc(context->c_call(), key.size() + 1));
        strncpy(key_copy, key.data(), key.size());
        key_copy[key.size()] = '\0';
        recorder->RecordNamedMetric(key_copy, value);
      }
    }
    return TestServiceImpl::Echo(context, request, response);
  }

  size_t request_count() {
    grpc_core::MutexLock lock(&mu_);
    return request_count_;
  }

  void ResetCounters() {
    grpc_core::MutexLock lock(&mu_);
    request_count_ = 0;
  }

  std::set<std::string> clients() {
    grpc_core::MutexLock lock(&clients_mu_);
    return clients_;
  }

 private:
  void AddClient(const std::string& client) {
    grpc_core::MutexLock lock(&clients_mu_);
    clients_.insert(client);
  }

  grpc_core::Mutex mu_;
  size_t request_count_ ABSL_GUARDED_BY(&mu_) = 0;

  grpc_core::Mutex clients_mu_;
  std::set<std::string> clients_ ABSL_GUARDED_BY(&clients_mu_);
};

class FakeResolverResponseGeneratorWrapper {
 public:
  FakeResolverResponseGeneratorWrapper()
      : response_generator_(grpc_core::MakeRefCounted<
                            grpc_core::FakeResolverResponseGenerator>()) {}

  FakeResolverResponseGeneratorWrapper(
      FakeResolverResponseGeneratorWrapper&& other) noexcept {
    response_generator_ = std::move(other.response_generator_);
  }

  void SetResponse(grpc_core::Resolver::Result result) {
    grpc_core::ExecCtx exec_ctx;
    response_generator_->SetResponseSynchronously(std::move(result));
  }

  void SetNextResolution(const std::vector<int>& ports,
                         const char* service_config_json = nullptr,
                         const grpc_core::ChannelArgs& per_address_args =
                             grpc_core::ChannelArgs()) {
    SetResponse(BuildFakeResults(ports, service_config_json, per_address_args));
  }

  grpc_core::FakeResolverResponseGenerator* Get() const {
    return response_generator_.get();
  }

 private:
  static grpc_core::Resolver::Result BuildFakeResults(
      const std::vector<int>& ports, const char* service_config_json = nullptr,
      const grpc_core::ChannelArgs& per_address_args =
          grpc_core::ChannelArgs()) {
    grpc_core::Resolver::Result result;
    result.addresses = grpc_core::EndpointAddressesList();
    for (const int& port : ports) {
      absl::StatusOr<grpc_core::URI> lb_uri =
          grpc_core::URI::Parse(grpc_core::LocalIpUri(port));
      CHECK_OK(lb_uri);
      grpc_resolved_address address;
      CHECK(grpc_parse_uri(*lb_uri, &address));
      result.addresses->emplace_back(address, per_address_args);
    }
    if (result.addresses->empty()) {
      result.resolution_note = "fake resolver empty address list";
    }
    if (service_config_json != nullptr) {
      result.service_config = grpc_core::ServiceConfigImpl::Create(
          grpc_core::ChannelArgs(), service_config_json);
      EXPECT_TRUE(result.service_config.ok()) << result.service_config.status();
    }
    return result;
  }

  grpc_core::RefCountedPtr<grpc_core::FakeResolverResponseGenerator>
      response_generator_;
};

constexpr absl::string_view kDefaultAuthority = "default.example.com";

class ClientLbEnd2endTest : public ::testing::Test {
 protected:
  void SetUp() override { grpc_init(); }

  void TearDown() override {
    for (size_t i = 0; i < servers_.size(); ++i) {
      servers_[i]->Shutdown();
    }
    servers_.clear();
    grpc_shutdown();
  }

  void CreateServers(
      size_t num_servers, std::vector<int> ports = {},
      std::shared_ptr<ServerCredentials> server_creds = nullptr) {
    servers_.clear();
    for (size_t i = 0; i < num_servers; ++i) {
      int port = 0;
      if (ports.size() == num_servers) port = ports[i];
      servers_.emplace_back(new ServerData(port, server_creds));
    }
  }

  void StartServer(size_t index) { servers_[index]->Start(); }

  void StartServers(size_t num_servers, std::vector<int> ports = {},
                    std::shared_ptr<ServerCredentials> server_creds = nullptr) {
    CreateServers(num_servers, std::move(ports), std::move(server_creds));
    for (size_t i = 0; i < num_servers; ++i) {
      StartServer(i);
    }
  }

  std::vector<int> GetServersPorts(size_t start_index = 0,
                                   size_t stop_index = 0) {
    if (stop_index == 0) stop_index = servers_.size();
    std::vector<int> ports;
    for (size_t i = start_index; i < stop_index; ++i) {
      ports.push_back(servers_[i]->port_);
    }
    return ports;
  }

  std::unique_ptr<grpc::testing::EchoTestService::Stub> BuildStub(
      const std::shared_ptr<Channel>& channel) {
    return grpc::testing::EchoTestService::NewStub(channel);
  }

  std::shared_ptr<Channel> BuildChannel(
      const std::string& lb_policy_name,
      const FakeResolverResponseGeneratorWrapper& response_generator,
      ChannelArguments args = ChannelArguments(),
      std::shared_ptr<ChannelCredentials> channel_creds = nullptr) {
    if (!lb_policy_name.empty()) {
      args.SetLoadBalancingPolicyName(lb_policy_name);
    }
    args.SetPointer(GRPC_ARG_FAKE_RESOLVER_RESPONSE_GENERATOR,
                    response_generator.Get());
    if (channel_creds == nullptr) {
      channel_creds =
          std::make_shared<FakeTransportSecurityChannelCredentials>();
    }
    return grpc::CreateCustomChannel(absl::StrCat("fake:", kDefaultAuthority),
                                     channel_creds, args);
  }

  Status SendRpc(
      const std::unique_ptr<grpc::testing::EchoTestService::Stub>& stub,
      EchoResponse* response = nullptr, int timeout_ms = 1000,
      bool wait_for_ready = false, EchoRequest* request = nullptr,
      std::string authority_override = "") {
    EchoResponse local_response;
    if (response == nullptr) response = &local_response;
    EchoRequest local_request;
    if (request == nullptr) request = &local_request;
    request->set_message(kRequestMessage);
    request->mutable_param()->set_echo_metadata(true);
    ClientContext context;
    context.set_deadline(grpc_timeout_milliseconds_to_deadline(timeout_ms));
    if (!authority_override.empty()) context.set_authority(authority_override);
    if (wait_for_ready) context.set_wait_for_ready(true);
    context.AddMetadata("foo", "1");
    context.AddMetadata("bar", "2");
    context.AddMetadata("baz", "3");
    return stub->Echo(&context, *request, response);
  }

  void CheckRpcSendOk(
      const grpc_core::DebugLocation& location,
      const std::unique_ptr<grpc::testing::EchoTestService::Stub>& stub,
      bool wait_for_ready = false, const OrcaLoadReport* load_report = nullptr,
      int timeout_ms = 2000) {
    EchoResponse response;
    EchoRequest request;
    EchoRequest* request_ptr = nullptr;
    if (load_report != nullptr) {
      request_ptr = &request;
      auto params = request.mutable_param();
      auto backend_metrics = params->mutable_backend_metrics();
      *backend_metrics = *load_report;
    }
    Status status =
        SendRpc(stub, &response, timeout_ms, wait_for_ready, request_ptr);
    ASSERT_TRUE(status.ok())
        << "From " << location.file() << ":" << location.line()
        << "\nError: " << status.error_message() << " "
        << status.error_details();
    ASSERT_EQ(response.message(), kRequestMessage)
        << "From " << location.file() << ":" << location.line();
  }

  void CheckRpcSendFailure(
      const grpc_core::DebugLocation& location,
      const std::unique_ptr<grpc::testing::EchoTestService::Stub>& stub,
      StatusCode expected_status, absl::string_view expected_message_regex) {
    Status status = SendRpc(stub);
    EXPECT_FALSE(status.ok());
    EXPECT_EQ(expected_status, status.error_code())
        << location.file() << ":" << location.line();
    EXPECT_THAT(status.error_message(),
                ::testing::MatchesRegex(expected_message_regex))
        << location.file() << ":" << location.line();
  }

  void SendRpcsUntil(
      const grpc_core::DebugLocation& debug_location,
      const std::unique_ptr<grpc::testing::EchoTestService::Stub>& stub,
      absl::AnyInvocable<bool(const Status&)> continue_predicate,
      EchoRequest* request_ptr = nullptr, int timeout_ms = 15000) {
    absl::Time deadline = absl::InfiniteFuture();
    if (timeout_ms != 0) {
      deadline = absl::Now() +
                 (absl::Milliseconds(timeout_ms) * grpc_test_slowdown_factor());
    }
    while (true) {
      Status status =
          SendRpc(stub, nullptr, 1000,
                  false, request_ptr);
      if (!continue_predicate(status)) return;
      EXPECT_LE(absl::Now(), deadline)
          << debug_location.file() << ":" << debug_location.line();
      if (absl::Now() >= deadline) break;
    }
  }

  struct ServerData {
    const int port_;
    const std::shared_ptr<ServerCredentials> server_creds_;
    std::unique_ptr<Server> server_;
    MyTestServiceImpl service_;
    std::unique_ptr<experimental::ServerMetricRecorder> server_metric_recorder_;
    experimental::OrcaService orca_service_;
    std::unique_ptr<std::thread> thread_;
    bool enable_noop_health_check_service_ = false;
    NoopHealthCheckServiceImpl noop_health_check_service_impl_;

    grpc_core::Mutex mu_;
    grpc_core::CondVar cond_;
    bool server_ready_ ABSL_GUARDED_BY(mu_) = false;
    bool started_ ABSL_GUARDED_BY(mu_) = false;

    explicit ServerData(
        int port = 0, std::shared_ptr<ServerCredentials> server_creds = nullptr)
        : port_(port > 0 ? port : grpc_pick_unused_port_or_die()),
          server_creds_(
              server_creds == nullptr
                  ? std::shared_ptr<
                        ServerCredentials>(new SecureServerCredentials(
                        grpc_fake_transport_security_server_credentials_create()))
                  : std::move(server_creds)),
          server_metric_recorder_(experimental::ServerMetricRecorder::Create()),
          orca_service_(
              server_metric_recorder_.get(),
              experimental::OrcaService::Options().set_min_report_duration(
                  absl::Seconds(0.1))) {}

    void Start() {
      LOG(INFO) << "starting server on port " << port_;
      grpc_core::MutexLock lock(&mu_);
      started_ = true;
      thread_ =
          std::make_unique<std::thread>(std::bind(&ServerData::Serve, this));
      while (!server_ready_) {
        cond_.Wait(&mu_);
      }
      server_ready_ = false;
      LOG(INFO) << "server startup complete";
    }

    void Serve() {
      ServerBuilder builder;
      builder.AddListeningPort(absl::StrCat("localhost:", port_),
                               server_creds_);
      builder.RegisterService(&service_);
      builder.RegisterService(&orca_service_);
      if (enable_noop_health_check_service_) {
        builder.RegisterService(&noop_health_check_service_impl_);
      }
      grpc::ServerBuilder::experimental_type(&builder)
          .EnableCallMetricRecording(server_metric_recorder_.get());
      server_ = builder.BuildAndStart();
      grpc_core::MutexLock lock(&mu_);
      server_ready_ = true;
      cond_.Signal();
    }

    void Shutdown() {
      grpc_core::MutexLock lock(&mu_);
      if (!started_) return;
      server_->Shutdown(grpc_timeout_milliseconds_to_deadline(0));
      thread_->join();
      started_ = false;
    }

    void StopListeningAndSendGoaways() {
      grpc_core::ExecCtx exec_ctx;
      auto* server = grpc_core::Server::FromC(server_->c_server());
      server->StopListening();
      server->SendGoaways();
    }

    void SetServingStatus(const std::string& service, bool serving) {
      server_->GetHealthCheckService()->SetServingStatus(service, serving);
    }
  };

  void ResetCounters() {
    for (const auto& server : servers_) server->service_.ResetCounters();
  }

  bool SeenAllServers(size_t start_index = 0, size_t stop_index = 0) {
    if (stop_index == 0) stop_index = servers_.size();
    for (size_t i = start_index; i < stop_index; ++i) {
      if (servers_[i]->service_.request_count() == 0) return false;
    }
    return true;
  }

  void WaitForServers(
      const grpc_core::DebugLocation& location,
      const std::unique_ptr<grpc::testing::EchoTestService::Stub>& stub,
      size_t start_index = 0, size_t stop_index = 0,
      absl::AnyInvocable<void(const Status&)> status_check = nullptr,
      absl::Duration timeout = absl::Seconds(30)) {
    if (stop_index == 0) stop_index = servers_.size();
    auto deadline = absl::Now() + (timeout * grpc_test_slowdown_factor());
    LOG(INFO) << "========= WAITING FOR BACKENDS [" << start_index << ", "
              << stop_index << ") ==========";
    while (!SeenAllServers(start_index, stop_index)) {
      Status status = SendRpc(stub);
      if (status_check != nullptr) {
        if (!status.ok()) status_check(status);
      } else {
        EXPECT_TRUE(status.ok())
            << " code=" << status.error_code() << " message=\""
            << status.error_message() << "\" at " << location.file() << ":"
            << location.line();
      }
      EXPECT_LE(absl::Now(), deadline)
          << " at " << location.file() << ":" << location.line();
      if (absl::Now() >= deadline) break;
    }
    ResetCounters();
  }

  void WaitForServer(
      const grpc_core::DebugLocation& location,
      const std::unique_ptr<grpc::testing::EchoTestService::Stub>& stub,
      size_t server_index,
      absl::AnyInvocable<void(const Status&)> status_check = nullptr) {
    WaitForServers(location, stub, server_index, server_index + 1,
                   std::move(status_check));
  }

  bool WaitForChannelState(
      Channel* channel,
      absl::AnyInvocable<bool(grpc_connectivity_state)> predicate,
      bool try_to_connect = false, int timeout_seconds = 5) {
    const gpr_timespec deadline =
        grpc_timeout_seconds_to_deadline(timeout_seconds);
    while (true) {
      grpc_connectivity_state state = channel->GetState(try_to_connect);
      if (predicate(state)) break;
      if (!channel->WaitForStateChange(state, deadline)) return false;
    }
    return true;
  }

  bool WaitForChannelNotReady(Channel* channel, int timeout_seconds = 5) {
    auto predicate = [](grpc_connectivity_state state) {
      return state != GRPC_CHANNEL_READY;
    };
    return WaitForChannelState(channel, predicate, false, timeout_seconds);
  }

  bool WaitForChannelReady(Channel* channel, int timeout_seconds = 5) {
    auto predicate = [](grpc_connectivity_state state) {
      return state == GRPC_CHANNEL_READY;
    };
    return WaitForChannelState(channel, predicate, true, timeout_seconds);
  }

  void UpdateConnectionOrder(
      const std::vector<std::unique_ptr<ServerData>>& servers,
      std::vector<int>* connection_order) {
    for (size_t i = 0; i < servers.size(); ++i) {
      if (servers[i]->service_.request_count() == 1) {

        const auto it =
            std::find(connection_order->begin(), connection_order->end(), i);
        if (it == connection_order->end()) {
          connection_order->push_back(i);
          return;
        }
      }
    }
  }

  void EnableNoopHealthCheckService() {
    for (auto& server : servers_) {
      server->enable_noop_health_check_service_ = true;
    }
  }

  static std::string MakeConnectionFailureRegex(absl::string_view prefix) {
    return absl::StrCat(
        prefix,
        "; last error: (UNKNOWN|UNAVAILABLE): "

        "(ipv6:%5B::1%5D|ipv4:127.0.0.1):[0-9]+: "

        "(Failed to connect to remote host: )?"
        "(Timeout occurred: )?"

        "( ?\\(*("
        "Secure read failed|"
        "Handshake (read|write) failed|"
        "Delayed close due to in-progress write|"

        "((connect|sendmsg|recvmsg|getsockopt\\(SO\\_ERROR\\)): ?)?"

        "(Connection refused"
        "|Connection reset by peer"
        "|Socket closed"
        "|FD shutdown"
        "|Endpoint closing)"

        "( \\([0-9]+\\))?"

        ")\\)*)+");
  }

  std::vector<std::unique_ptr<ServerData>> servers_;
  grpc_core::PostMortem port_mortem_;
};

TEST_F(ClientLbEnd2endTest, ChannelStateConnectingWhenResolving) {
  const int kNumServers = 3;
  StartServers(kNumServers);
  FakeResolverResponseGeneratorWrapper response_generator;
  auto channel = BuildChannel("", response_generator);
  auto stub = BuildStub(channel);

  EXPECT_EQ(channel->GetState(false ), GRPC_CHANNEL_IDLE);

  EXPECT_EQ(channel->GetState(true ), GRPC_CHANNEL_IDLE);

  ASSERT_TRUE(
      WaitForChannelState(channel.get(), [&](grpc_connectivity_state state) {
        if (state == GRPC_CHANNEL_IDLE) return false;
        EXPECT_EQ(state, GRPC_CHANNEL_CONNECTING);
        return true;
      }));

  response_generator.SetNextResolution(GetServersPorts());

  EXPECT_TRUE(WaitForChannelReady(channel.get()));
}

TEST_F(ClientLbEnd2endTest, ChannelIdleness) {

  const int kNumServers = 1;
  StartServers(kNumServers);

  ChannelArguments args;
  args.SetInt(GRPC_ARG_CLIENT_IDLE_TIMEOUT_MS,
              1000 * grpc_test_slowdown_factor());
  FakeResolverResponseGeneratorWrapper response_generator;
  auto channel = BuildChannel("", response_generator, args);
  auto stub = BuildStub(channel);

  EXPECT_EQ(channel->GetState(false), GRPC_CHANNEL_IDLE);

  LOG(INFO) << "*** SENDING RPC, CHANNEL SHOULD CONNECT ***";
  response_generator.SetNextResolution(GetServersPorts());
  CheckRpcSendOk(DEBUG_LOCATION, stub);
  EXPECT_EQ(channel->GetState(false), GRPC_CHANNEL_READY);

  LOG(INFO) << "*** WAITING FOR CHANNEL TO GO IDLE ***";
  gpr_sleep_until(grpc_timeout_milliseconds_to_deadline(1200));
  EXPECT_EQ(channel->GetState(false), GRPC_CHANNEL_IDLE);

  LOG(INFO) << "*** SENDING ANOTHER RPC, CHANNEL SHOULD RECONNECT ***";
  response_generator.SetNextResolution(GetServersPorts());
  CheckRpcSendOk(DEBUG_LOCATION, stub);
  EXPECT_EQ(channel->GetState(false), GRPC_CHANNEL_READY);
}

class AuthorityOverrideTest : public ClientLbEnd2endTest {
 protected:
  static void SetUpTestSuite() {
    grpc_core::CoreConfiguration::Reset();
    grpc_core::CoreConfiguration::RegisterEphemeralBuilder(
        [](grpc_core::CoreConfiguration::Builder* builder) {
          grpc_core::RegisterAuthorityOverrideLoadBalancingPolicy(builder);
        });
    grpc_init();
  }

  static void TearDownTestSuite() {
    grpc_shutdown();
    grpc_core::CoreConfiguration::Reset();
  }
};

TEST_F(AuthorityOverrideTest, NoOverride) {
  StartServers(1);
  FakeResolverResponseGeneratorWrapper response_generator;
  auto channel = BuildChannel("", response_generator);
  auto stub = BuildStub(channel);
  response_generator.SetNextResolution(GetServersPorts());

  EchoRequest request;
  request.mutable_param()->set_echo_host_from_authority_header(true);
  EchoResponse response;
  Status status = SendRpc(stub, &response, 1000,
                          false, &request);
  EXPECT_TRUE(status.ok()) << "code=" << status.error_code()
                           << " message=" << status.error_message();

  EXPECT_EQ(kDefaultAuthority, response.param().host());
}

TEST_F(AuthorityOverrideTest, OverrideFromResolver) {
  StartServers(1);
  FakeResolverResponseGeneratorWrapper response_generator;
  auto channel = BuildChannel("", response_generator);
  auto stub = BuildStub(channel);

  response_generator.SetNextResolution(
      GetServersPorts(), nullptr,
      grpc_core::ChannelArgs().Set(GRPC_ARG_DEFAULT_AUTHORITY,
                                   "from-resolver.example.com"));

  EchoRequest request;
  request.mutable_param()->set_echo_host_from_authority_header(true);
  EchoResponse response;
  Status status = SendRpc(stub, &response, 1000,
                          false, &request);
  EXPECT_TRUE(status.ok()) << "code=" << status.error_code()
                           << " message=" << status.error_message();

  EXPECT_EQ("from-resolver.example.com", response.param().host());
}

TEST_F(AuthorityOverrideTest, OverrideOnChannel) {
  StartServers(1);

  FakeResolverResponseGeneratorWrapper response_generator;
  ChannelArguments args;
  args.SetString(GRPC_ARG_DEFAULT_AUTHORITY, "from-channel.example.com");
  auto channel = BuildChannel("", response_generator, args);
  auto stub = BuildStub(channel);
  response_generator.SetNextResolution(GetServersPorts());

  EchoRequest request;
  request.mutable_param()->set_echo_host_from_authority_header(true);
  EchoResponse response;
  Status status = SendRpc(stub, &response, 1000,
                          false, &request);
  EXPECT_TRUE(status.ok()) << "code=" << status.error_code()
                           << " message=" << status.error_message();

  EXPECT_EQ("from-channel.example.com", response.param().host());
}

TEST_F(AuthorityOverrideTest, OverrideFromLbPolicy) {

  StartServers(1, {}, InsecureServerCredentials());
  FakeResolverResponseGeneratorWrapper response_generator;
  ChannelArguments args;
  args.SetString(GRPC_ARG_TEST_LB_AUTHORITY_OVERRIDE, "from-lb.example.com");
  auto channel = BuildChannel("authority_override_lb", response_generator, args,
                              InsecureChannelCredentials());
  auto stub = BuildStub(channel);
  response_generator.SetNextResolution(GetServersPorts());

  EchoRequest request;
  request.mutable_param()->set_echo_host_from_authority_header(true);
  EchoResponse response;
  Status status = SendRpc(stub, &response, 1000,
                          false, &request);
  EXPECT_TRUE(status.ok()) << "code=" << status.error_code()
                           << " message=" << status.error_message();

  EXPECT_EQ("from-lb.example.com", response.param().host());
}

TEST_F(AuthorityOverrideTest, PerRpcOverride) {

  StartServers(1, {}, InsecureServerCredentials());
  FakeResolverResponseGeneratorWrapper response_generator;
  auto channel = BuildChannel("", response_generator, ChannelArguments(),
                              InsecureChannelCredentials());
  auto stub = BuildStub(channel);
  response_generator.SetNextResolution(GetServersPorts());

  EchoRequest request;
  request.mutable_param()->set_echo_host_from_authority_header(true);
  EchoResponse response;
  Status status = SendRpc(stub, &response, 1000,
                          false, &request,
                          "per-rpc.example.com");
  EXPECT_TRUE(status.ok()) << "code=" << status.error_code()
                           << " message=" << status.error_message();

  EXPECT_EQ("per-rpc.example.com", response.param().host());
}

TEST_F(AuthorityOverrideTest,
       ChannelOverrideTakesPrecedenceOverResolverOverride) {
  StartServers(1);

  FakeResolverResponseGeneratorWrapper response_generator;
  ChannelArguments args;
  args.SetString(GRPC_ARG_DEFAULT_AUTHORITY, "from-channel.example.com");
  auto channel = BuildChannel("", response_generator, args);
  auto stub = BuildStub(channel);

  response_generator.SetNextResolution(
      GetServersPorts(), nullptr,
      grpc_core::ChannelArgs().Set(GRPC_ARG_DEFAULT_AUTHORITY,
                                   "from-resolver.example.com"));

  EchoRequest request;
  request.mutable_param()->set_echo_host_from_authority_header(true);
  EchoResponse response;
  Status status = SendRpc(stub, &response, 1000,
                          false, &request);
  EXPECT_TRUE(status.ok()) << "code=" << status.error_code()
                           << " message=" << status.error_message();

  EXPECT_EQ("from-channel.example.com", response.param().host());
}

TEST_F(AuthorityOverrideTest,
       LbPolicyOverrideTakesPrecedenceOverChannelOverride) {

  StartServers(1, {}, InsecureServerCredentials());
  FakeResolverResponseGeneratorWrapper response_generator;
  ChannelArguments args;
  args.SetString(GRPC_ARG_DEFAULT_AUTHORITY, "from-channel.example.com");
  args.SetString(GRPC_ARG_TEST_LB_AUTHORITY_OVERRIDE, "from-lb.example.com");
  auto channel = BuildChannel("authority_override_lb", response_generator, args,
                              InsecureChannelCredentials());
  auto stub = BuildStub(channel);
  response_generator.SetNextResolution(GetServersPorts());

  EchoRequest request;
  request.mutable_param()->set_echo_host_from_authority_header(true);
  EchoResponse response;
  Status status = SendRpc(stub, &response, 1000,
                          false, &request);
  EXPECT_TRUE(status.ok()) << "code=" << status.error_code()
                           << " message=" << status.error_message();

  EXPECT_EQ("from-lb.example.com", response.param().host());
}

TEST_F(AuthorityOverrideTest,
       PerRpcOverrideTakesPrecedenceOverLbPolicyOverride) {

  StartServers(1, {}, InsecureServerCredentials());
  FakeResolverResponseGeneratorWrapper response_generator;
  ChannelArguments args;
  args.SetString(GRPC_ARG_TEST_LB_AUTHORITY_OVERRIDE, "from-lb.example.com");
  auto channel = BuildChannel("authority_override_lb", response_generator, args,
                              InsecureChannelCredentials());
  auto stub = BuildStub(channel);
  response_generator.SetNextResolution(GetServersPorts());

  EchoRequest request;
  request.mutable_param()->set_echo_host_from_authority_header(true);
  EchoResponse response;
  Status status = SendRpc(stub, &response, 1000,
                          false, &request,
                          "per-rpc.example.com");
  EXPECT_TRUE(status.ok()) << "code=" << status.error_code()
                           << " message=" << status.error_message();

  EXPECT_EQ("per-rpc.example.com", response.param().host());
}

using PickFirstTest = ClientLbEnd2endTest;

TEST_F(PickFirstTest, Basic) {

  const int kNumServers = 3;
  StartServers(kNumServers);
  FakeResolverResponseGeneratorWrapper response_generator;
  auto channel = BuildChannel(
      "", response_generator);
  auto stub = BuildStub(channel);
  response_generator.SetNextResolution(GetServersPorts());
  for (size_t i = 0; i < servers_.size(); ++i) {
    CheckRpcSendOk(DEBUG_LOCATION, stub);
  }

  bool found = false;
  for (size_t i = 0; i < servers_.size(); ++i) {
    const int request_count = servers_[i]->service_.request_count();
    if (request_count == kNumServers) {
      found = true;
    } else {
      EXPECT_EQ(0, request_count);
    }
  }
  EXPECT_TRUE(found);

  EXPECT_EQ("pick_first", channel->GetLoadBalancingPolicyName());
}

TEST_F(PickFirstTest, ProcessPending) {
  StartServers(1);
  FakeResolverResponseGeneratorWrapper response_generator;
  auto channel = BuildChannel(
      "", response_generator);
  auto stub = BuildStub(channel);
  response_generator.SetNextResolution({servers_[0]->port_});
  WaitForServer(DEBUG_LOCATION, stub, 0);

  FakeResolverResponseGeneratorWrapper second_response_generator;
  auto second_channel = BuildChannel("", second_response_generator);
  auto second_stub = BuildStub(second_channel);
  second_response_generator.SetNextResolution({servers_[0]->port_});
  CheckRpcSendOk(DEBUG_LOCATION, second_stub);
}

TEST_F(PickFirstTest, SelectsReadyAtStartup) {
  ChannelArguments args;
  constexpr int kInitialBackOffMs = 5000;
  args.SetInt(GRPC_ARG_INITIAL_RECONNECT_BACKOFF_MS,
              kInitialBackOffMs * grpc_test_slowdown_factor());

  std::vector<int> ports = {grpc_pick_unused_port_or_die(),
                            grpc_pick_unused_port_or_die()};
  CreateServers(2, ports);
  StartServer(1);
  FakeResolverResponseGeneratorWrapper response_generator1;
  auto channel1 = BuildChannel("pick_first", response_generator1, args);
  auto stub1 = BuildStub(channel1);
  response_generator1.SetNextResolution(ports);

  WaitForServer(DEBUG_LOCATION, stub1, 1);

  FakeResolverResponseGeneratorWrapper response_generator2;
  auto channel2 = BuildChannel("pick_first", response_generator2, args);
  response_generator2.SetNextResolution(ports);

  EXPECT_TRUE(WaitForChannelReady(channel2.get(), 1 ));
}

TEST_F(PickFirstTest, BackOffInitialReconnect) {
  StartServers(1);
  ChannelArguments args;
  constexpr int kInitialBackOffMs = 100;
  args.SetInt(GRPC_ARG_INITIAL_RECONNECT_BACKOFF_MS,
              kInitialBackOffMs * grpc_test_slowdown_factor());
  FakeResolverResponseGeneratorWrapper response_generator;
  auto channel = BuildChannel("pick_first", response_generator, args);
  auto stub = BuildStub(channel);
  response_generator.SetNextResolution({servers_[0]->port_});

  ConnectionAttemptInjector injector;
  auto hold1 = injector.AddHold(servers_[0]->port_);
  auto hold2 = injector.AddHold(servers_[0]->port_);

  EXPECT_EQ(channel->GetState(true), GRPC_CHANNEL_IDLE);

  hold1->Wait();
  const grpc_core::Timestamp first_attempt_time = grpc_core::Timestamp::Now();
  hold1->Fail(absl::UnavailableError("nope"));

  hold2->Wait();
  const grpc_core::Duration waited =
      grpc_core::Timestamp::Now() - first_attempt_time;

  EXPECT_TRUE(
      WaitForChannelState(channel.get(), [&](grpc_connectivity_state state) {
        if (state == GRPC_CHANNEL_TRANSIENT_FAILURE) return true;
        EXPECT_THAT(state, ::testing::AnyOf(GRPC_CHANNEL_IDLE,
                                            GRPC_CHANNEL_CONNECTING));
        return false;
      }));

  hold2->Resume();

  EXPECT_TRUE(WaitForChannelReady(channel.get()));

  VLOG(2) << "Waited " << waited.millis() << " milliseconds";

  EXPECT_GE(waited.millis(),
            (kInitialBackOffMs * grpc_test_slowdown_factor()) * 0.7);
  EXPECT_LE(waited.millis(),
            (kInitialBackOffMs * grpc_test_slowdown_factor()) * 1.5);
}

TEST_F(PickFirstTest, BackOffMinReconnect) {
  ChannelArguments args;
  constexpr int kMinReconnectBackOffMs = 1000;
  args.SetInt(GRPC_ARG_MIN_RECONNECT_BACKOFF_MS,
              kMinReconnectBackOffMs * grpc_test_slowdown_factor());
  const std::vector<int> ports = {grpc_pick_unused_port_or_die()};
  FakeResolverResponseGeneratorWrapper response_generator;
  auto channel = BuildChannel("pick_first", response_generator, args);
  auto stub = BuildStub(channel);
  response_generator.SetNextResolution(ports);

  ConnectionAttemptInjector injector;
  injector.SetDelay(grpc_core::Duration::Milliseconds(
      kMinReconnectBackOffMs * grpc_test_slowdown_factor() * 1.10));
  const gpr_timespec t0 = gpr_now(GPR_CLOCK_MONOTONIC);
  channel->WaitForConnected(
      grpc_timeout_milliseconds_to_deadline(kMinReconnectBackOffMs * 2));
  const gpr_timespec t1 = gpr_now(GPR_CLOCK_MONOTONIC);
  const grpc_core::Duration waited =
      grpc_core::Duration::FromTimespec(gpr_time_sub(t1, t0));
  VLOG(2) << "Waited " << waited.millis() << " milliseconds";

  EXPECT_GE(waited.millis(),
            (kMinReconnectBackOffMs * grpc_test_slowdown_factor()) - 1);
}

TEST_F(PickFirstTest, ResetConnectionBackoff) {
  ChannelArguments args;
  constexpr int kInitialBackOffMs = 1000;
  args.SetInt(GRPC_ARG_INITIAL_RECONNECT_BACKOFF_MS,
              kInitialBackOffMs * grpc_test_slowdown_factor());
  const std::vector<int> ports = {grpc_pick_unused_port_or_die()};
  FakeResolverResponseGeneratorWrapper response_generator;
  auto channel = BuildChannel("pick_first", response_generator, args);
  auto stub = BuildStub(channel);
  response_generator.SetNextResolution(ports);

  EXPECT_FALSE(
      channel->WaitForConnected(grpc_timeout_milliseconds_to_deadline(10)));

  StartServers(1, ports);
  const gpr_timespec t0 = gpr_now(GPR_CLOCK_MONOTONIC);

  EXPECT_FALSE(
      channel->WaitForConnected(grpc_timeout_milliseconds_to_deadline(10)));

  experimental::ChannelResetConnectionBackoff(channel.get());

  EXPECT_TRUE(channel->WaitForConnected(
      grpc_timeout_milliseconds_to_deadline(kInitialBackOffMs)));
  const gpr_timespec t1 = gpr_now(GPR_CLOCK_MONOTONIC);
  const grpc_core::Duration waited =
      grpc_core::Duration::FromTimespec(gpr_time_sub(t1, t0));
  VLOG(2) << "Waited " << waited.millis() << " milliseconds";

  EXPECT_LT(waited.millis(), kInitialBackOffMs * grpc_test_slowdown_factor());
}

TEST_F(ClientLbEnd2endTest,
       ResetConnectionBackoffNextAttemptStartsImmediately) {

  ConnectionAttemptInjector injector;

  const int port = grpc_pick_unused_port_or_die();
  ChannelArguments args;
  const int kInitialBackOffMs = 5000;
  args.SetInt(GRPC_ARG_INITIAL_RECONNECT_BACKOFF_MS,
              kInitialBackOffMs * grpc_test_slowdown_factor());
  FakeResolverResponseGeneratorWrapper response_generator;
  auto channel = BuildChannel("pick_first", response_generator, args);
  auto stub = BuildStub(channel);
  response_generator.SetNextResolution({port});

  auto hold1 = injector.AddHold(port);
  LOG(INFO) << "=== TRIGGERING INITIAL CONNECTION ATTEMPT";
  EXPECT_EQ(GRPC_CHANNEL_IDLE, channel->GetState(true));
  hold1->Wait();
  EXPECT_EQ(GRPC_CHANNEL_CONNECTING,
            channel->GetState(false));

  LOG(INFO) << "=== RESETTING BACKOFF";
  experimental::ChannelResetConnectionBackoff(channel.get());

  auto hold2 = injector.AddHold(port);

  LOG(INFO) << "=== RESUMING INITIAL ATTEMPT";
  const gpr_timespec t0 = gpr_now(GPR_CLOCK_MONOTONIC);
  hold1->Resume();
  LOG(INFO) << "=== WAITING FOR SECOND ATTEMPT";

  EXPECT_TRUE(channel->WaitForStateChange(GRPC_CHANNEL_CONNECTING,
                                          grpc_timeout_seconds_to_deadline(1)));
  hold2->Wait();
  const gpr_timespec t1 = gpr_now(GPR_CLOCK_MONOTONIC);
  LOG(INFO) << "=== RESUMING SECOND ATTEMPT";
  hold2->Resume();

  const grpc_core::Duration waited =
      grpc_core::Duration::FromTimespec(gpr_time_sub(t1, t0));
  VLOG(2) << "Waited " << waited.millis() << " milliseconds";
  EXPECT_LT(waited.millis(), 1000 * grpc_test_slowdown_factor());
}

TEST_F(PickFirstTest, Updates) {

  const int kNumServers = 3;
  StartServers(kNumServers);
  FakeResolverResponseGeneratorWrapper response_generator;
  auto channel = BuildChannel("pick_first", response_generator);
  auto stub = BuildStub(channel);

  response_generator.SetNextResolution(GetServersPorts(0, 1));
  LOG(INFO) << "****** SET [0] *******";
  CheckRpcSendOk(DEBUG_LOCATION, stub);
  EXPECT_EQ(servers_[0]->service_.request_count(), 1);

  response_generator.SetNextResolution({});
  LOG(INFO) << "****** SET none *******";
  WaitForChannelNotReady(channel.get());

  response_generator.SetNextResolution(GetServersPorts(1, 2));
  LOG(INFO) << "****** SET [1] *******";
  WaitForChannelReady(channel.get());
  WaitForServer(DEBUG_LOCATION, stub, 1);

  response_generator.SetNextResolution(GetServersPorts(2, 3));
  LOG(INFO) << "****** SET [2] *******";
  WaitForServer(DEBUG_LOCATION, stub, 2);

  EXPECT_EQ("pick_first", channel->GetLoadBalancingPolicyName());
}

TEST_F(PickFirstTest, UpdateSuperset) {

  const int kNumServers = 3;
  StartServers(kNumServers);
  FakeResolverResponseGeneratorWrapper response_generator;
  auto channel = BuildChannel("pick_first", response_generator);
  auto stub = BuildStub(channel);

  std::vector<int> ports;

  ports.emplace_back(servers_[0]->port_);
  response_generator.SetNextResolution(ports);
  LOG(INFO) << "****** SET [0] *******";
  CheckRpcSendOk(DEBUG_LOCATION, stub);
  EXPECT_EQ(servers_[0]->service_.request_count(), 1);
  servers_[0]->service_.ResetCounters();

  ports.clear();
  ports.emplace_back(servers_[1]->port_);
  ports.emplace_back(servers_[0]->port_);
  response_generator.SetNextResolution(ports);
  LOG(INFO) << "****** SET superset *******";
  CheckRpcSendOk(DEBUG_LOCATION, stub);

  WaitForServer(DEBUG_LOCATION, stub, 0);
  EXPECT_EQ(0, servers_[1]->service_.request_count());

  EXPECT_EQ("pick_first", channel->GetLoadBalancingPolicyName());
}

TEST_F(PickFirstTest, UpdateToUnconnected) {
  const int kNumServers = 2;
  CreateServers(kNumServers);
  StartServer(0);
  FakeResolverResponseGeneratorWrapper response_generator;
  auto channel = BuildChannel("pick_first", response_generator);
  auto stub = BuildStub(channel);

  std::vector<int> ports;

  ports.emplace_back(servers_[0]->port_);
  response_generator.SetNextResolution(ports);
  LOG(INFO) << "****** SET [0] *******";
  CheckRpcSendOk(DEBUG_LOCATION, stub);

  ports.clear();
  ports.emplace_back(grpc_pick_unused_port_or_die());
  ports.emplace_back(servers_[1]->port_);
  response_generator.SetNextResolution(ports);
  LOG(INFO) << "****** SET [unavailable] *******";
  EXPECT_TRUE(WaitForChannelNotReady(channel.get()));

  LOG(INFO) << "****** StartServer(1) *******";
  StartServer(1);
  EXPECT_TRUE(WaitForChannelReady(channel.get()));
}

TEST_F(PickFirstTest, GlobalSubchannelPool) {

  const int kNumServers = 1;
  StartServers(kNumServers);
  std::vector<int> ports = GetServersPorts();

  auto channel_creds =
      std::make_shared<FakeTransportSecurityChannelCredentials>();
  FakeResolverResponseGeneratorWrapper response_generator1;
  auto channel1 = BuildChannel("pick_first", response_generator1,
                               ChannelArguments(), channel_creds);
  auto stub1 = BuildStub(channel1);
  response_generator1.SetNextResolution(ports);
  FakeResolverResponseGeneratorWrapper response_generator2;
  auto channel2 = BuildChannel("pick_first", response_generator2,
                               ChannelArguments(), channel_creds);
  auto stub2 = BuildStub(channel2);
  response_generator2.SetNextResolution(ports);
  WaitForServer(DEBUG_LOCATION, stub1, 0);

  CheckRpcSendOk(DEBUG_LOCATION, stub1);
  CheckRpcSendOk(DEBUG_LOCATION, stub2);

  EXPECT_EQ(2, servers_[0]->service_.request_count());

  EXPECT_EQ(1UL, servers_[0]->service_.clients().size());
}

TEST_F(PickFirstTest, LocalSubchannelPool) {

  const int kNumServers = 1;
  StartServers(kNumServers);
  std::vector<int> ports = GetServersPorts();

  ChannelArguments args;
  args.SetInt(GRPC_ARG_USE_LOCAL_SUBCHANNEL_POOL, 1);
  FakeResolverResponseGeneratorWrapper response_generator1;
  auto channel1 = BuildChannel("pick_first", response_generator1, args);
  auto stub1 = BuildStub(channel1);
  response_generator1.SetNextResolution(ports);
  FakeResolverResponseGeneratorWrapper response_generator2;
  auto channel2 = BuildChannel("pick_first", response_generator2, args);
  auto stub2 = BuildStub(channel2);
  response_generator2.SetNextResolution(ports);
  WaitForServer(DEBUG_LOCATION, stub1, 0);

  CheckRpcSendOk(DEBUG_LOCATION, stub1);
  CheckRpcSendOk(DEBUG_LOCATION, stub2);

  EXPECT_EQ(2, servers_[0]->service_.request_count());

  EXPECT_EQ(2UL, servers_[0]->service_.clients().size());
}

TEST_F(PickFirstTest, ManyUpdates) {
  const int kNumUpdates = 1000;
  const int kNumServers = 3;
  StartServers(kNumServers);
  FakeResolverResponseGeneratorWrapper response_generator;
  auto channel = BuildChannel("pick_first", response_generator);
  auto stub = BuildStub(channel);
  std::vector<int> ports = GetServersPorts();
  for (size_t i = 0; i < kNumUpdates; ++i) {
    std::shuffle(ports.begin(), ports.end(),
                 std::mt19937(std::random_device()()));
    response_generator.SetNextResolution(ports);

    if ((i + 1) % 10 == 0) CheckRpcSendOk(DEBUG_LOCATION, stub);
  }

  EXPECT_EQ("pick_first", channel->GetLoadBalancingPolicyName());
}

TEST_F(PickFirstTest, ReresolutionNoSelected) {

  const int kNumServers = 3;
  const int kNumAliveServers = 1;
  StartServers(kNumAliveServers);
  std::vector<int> alive_ports, dead_ports;
  for (size_t i = 0; i < kNumServers; ++i) {
    if (i < kNumAliveServers) {
      alive_ports.emplace_back(servers_[i]->port_);
    } else {
      dead_ports.emplace_back(grpc_pick_unused_port_or_die());
    }
  }
  FakeResolverResponseGeneratorWrapper response_generator;
  auto channel = BuildChannel("pick_first", response_generator);
  auto stub = BuildStub(channel);

  response_generator.SetNextResolution(dead_ports);
  LOG(INFO) << "****** INITIAL RESOLUTION SET *******";
  for (size_t i = 0; i < 10; ++i) {
    CheckRpcSendFailure(
        DEBUG_LOCATION, stub, StatusCode::UNAVAILABLE,
        MakeConnectionFailureRegex("failed to connect to all addresses"));
  }

  LOG(INFO) << "****** WAITING FOR RE-RESOLUTION *******";
  EXPECT_TRUE(response_generator.Get()->WaitForReresolutionRequest(
      absl::Seconds(5 * grpc_test_slowdown_factor())));
  LOG(INFO) << "****** RE-RESOLUTION SEEN *******";

  response_generator.SetNextResolution(alive_ports);
  LOG(INFO) << "****** RE-RESOLUTION SENT *******";
  WaitForServer(DEBUG_LOCATION, stub, 0, [](const Status& status) {
    EXPECT_EQ(StatusCode::UNAVAILABLE, status.error_code());
    EXPECT_THAT(status.error_message(),
                ::testing::ContainsRegex(MakeConnectionFailureRegex(
                    "failed to connect to all addresses")));
  });
  CheckRpcSendOk(DEBUG_LOCATION, stub);
  EXPECT_EQ(servers_[0]->service_.request_count(), 1);

  EXPECT_EQ("pick_first", channel->GetLoadBalancingPolicyName());
}

TEST_F(PickFirstTest, ReconnectWithoutNewResolverResult) {
  std::vector<int> ports = {grpc_pick_unused_port_or_die()};
  StartServers(1, ports);
  FakeResolverResponseGeneratorWrapper response_generator;
  auto channel = BuildChannel("pick_first", response_generator);
  auto stub = BuildStub(channel);
  response_generator.SetNextResolution(ports);
  LOG(INFO) << "****** INITIAL CONNECTION *******";
  WaitForServer(DEBUG_LOCATION, stub, 0);
  LOG(INFO) << "****** STOPPING SERVER ******";
  servers_[0]->Shutdown();
  EXPECT_TRUE(WaitForChannelNotReady(channel.get()));
  LOG(INFO) << "****** RESTARTING SERVER ******";
  StartServers(1, ports);
  WaitForServer(DEBUG_LOCATION, stub, 0);
}

TEST_F(PickFirstTest, ReconnectWithoutNewResolverResultStartsFromTopOfList) {
  std::vector<int> ports = {grpc_pick_unused_port_or_die(),
                            grpc_pick_unused_port_or_die()};
  CreateServers(2, ports);
  StartServer(1);
  FakeResolverResponseGeneratorWrapper response_generator;
  auto channel = BuildChannel("pick_first", response_generator);
  auto stub = BuildStub(channel);
  response_generator.SetNextResolution(ports);
  LOG(INFO) << "****** INITIAL CONNECTION *******";
  WaitForServer(DEBUG_LOCATION, stub, 1);
  LOG(INFO) << "****** STOPPING SERVER ******";
  servers_[1]->Shutdown();
  EXPECT_TRUE(WaitForChannelNotReady(channel.get()));
  LOG(INFO) << "****** STARTING BOTH SERVERS ******";
  StartServers(2, ports);
  WaitForServer(DEBUG_LOCATION, stub, 0);
}

TEST_F(PickFirstTest, FailsEmptyResolverUpdate) {
  FakeResolverResponseGeneratorWrapper response_generator;
  auto channel = BuildChannel("pick_first", response_generator);
  auto stub = BuildStub(channel);
  LOG(INFO) << "****** SENDING INITIAL RESOLVER RESULT *******";

  grpc_core::Notification notification;
  grpc_core::Resolver::Result result;
  result.addresses.emplace();
  result.result_health_callback = [&](absl::Status status) {
    LOG(INFO) << "****** RESULT HEALTH CALLBACK *******";
    EXPECT_EQ(absl::StatusCode::kUnavailable, status.code());
    EXPECT_EQ("address list must not be empty", status.message()) << status;
    notification.Notify();
  };
  response_generator.SetResponse(std::move(result));

  LOG(INFO) << "****** TELLING CHANNEL TO CONNECT *******";
  auto predicate = [](grpc_connectivity_state state) {
    return state == GRPC_CHANNEL_TRANSIENT_FAILURE;
  };
  EXPECT_TRUE(
      WaitForChannelState(channel.get(), predicate, true));

  notification.WaitForNotification();

  LOG(INFO) << "****** SENDING NEXT RESOLVER RESULT *******";
  StartServers(1);
  response_generator.SetNextResolution(GetServersPorts());
  LOG(INFO) << "****** SENDING WAIT_FOR_READY RPC *******";
  CheckRpcSendOk(DEBUG_LOCATION, stub, true);
}

TEST_F(PickFirstTest, CheckStateBeforeStartWatch) {
  std::vector<int> ports = {grpc_pick_unused_port_or_die()};
  StartServers(1, ports);
  FakeResolverResponseGeneratorWrapper response_generator;
  auto channel_1 = BuildChannel("pick_first", response_generator);
  auto stub_1 = BuildStub(channel_1);
  response_generator.SetNextResolution(ports);
  LOG(INFO) << "****** RESOLUTION SET FOR CHANNEL 1 *******";
  WaitForServer(DEBUG_LOCATION, stub_1, 0);
  LOG(INFO) << "****** CHANNEL 1 CONNECTED *******";
  servers_[0]->Shutdown();
  EXPECT_TRUE(WaitForChannelNotReady(channel_1.get()));

  StartServers(1, ports);
  LOG(INFO) << "****** SERVER RESTARTED *******";
  FakeResolverResponseGeneratorWrapper response_generator_2;
  auto channel_2 = BuildChannel("pick_first", response_generator_2);
  auto stub_2 = BuildStub(channel_2);
  response_generator_2.SetNextResolution(ports);
  LOG(INFO) << "****** RESOLUTION SET FOR CHANNEL 2 *******";
  WaitForServer(DEBUG_LOCATION, stub_2, 0);
  LOG(INFO) << "****** CHANNEL 2 CONNECTED *******";
  servers_[0]->Shutdown();

  EXPECT_TRUE(WaitForChannelNotReady(channel_2.get()));

  StartServers(1, ports);
  LOG(INFO) << "****** SERVER RESTARTED AGAIN *******";
  LOG(INFO) << "****** CHANNEL 2 STARTING A CALL *******";

  CheckRpcSendOk(DEBUG_LOCATION, stub_2);
  LOG(INFO) << "****** CHANNEL 2 FINISHED A CALL *******";

  EXPECT_EQ("pick_first", channel_1->GetLoadBalancingPolicyName());

  EXPECT_EQ("pick_first", channel_2->GetLoadBalancingPolicyName());
}

TEST_F(PickFirstTest, IdleOnDisconnect) {

  const int kNumServers = 1;
  StartServers(kNumServers);
  FakeResolverResponseGeneratorWrapper response_generator;
  auto channel =
      BuildChannel("", response_generator);
  auto stub = BuildStub(channel);
  response_generator.SetNextResolution(GetServersPorts());
  CheckRpcSendOk(DEBUG_LOCATION, stub);
  EXPECT_EQ(channel->GetState(false), GRPC_CHANNEL_READY);

  servers_[0]->Shutdown();
  EXPECT_TRUE(WaitForChannelNotReady(channel.get()));
  EXPECT_EQ(channel->GetState(false), GRPC_CHANNEL_IDLE);
  servers_.clear();
}

TEST_F(PickFirstTest, StaysIdleUponEmptyUpdate) {

  const int kNumServers = 1;
  StartServers(kNumServers);
  FakeResolverResponseGeneratorWrapper response_generator;
  auto channel =
      BuildChannel("", response_generator);
  auto stub = BuildStub(channel);
  response_generator.SetNextResolution(GetServersPorts());
  CheckRpcSendOk(DEBUG_LOCATION, stub);
  EXPECT_EQ(channel->GetState(false), GRPC_CHANNEL_READY);

  servers_[0]->Shutdown();
  EXPECT_TRUE(WaitForChannelNotReady(channel.get()));
  EXPECT_EQ(channel->GetState(false), GRPC_CHANNEL_IDLE);

  response_generator.SetNextResolution({});
  EXPECT_FALSE(channel->WaitForStateChange(
      GRPC_CHANNEL_IDLE, grpc_timeout_seconds_to_deadline(3)));

  StartServer(0);
  response_generator.SetNextResolution(GetServersPorts());
  CheckRpcSendOk(DEBUG_LOCATION, stub);
  EXPECT_EQ(channel->GetState(false), GRPC_CHANNEL_READY);
}

TEST_F(PickFirstTest,
       StaysTransientFailureOnFailedConnectionAttemptUntilReady) {

  std::vector<int> ports = {grpc_pick_unused_port_or_die(),
                            grpc_pick_unused_port_or_die(),
                            grpc_pick_unused_port_or_die()};

  ChannelArguments args;
  args.SetInt(GRPC_ARG_INITIAL_RECONNECT_BACKOFF_MS,
              1000 * grpc_test_slowdown_factor());
  FakeResolverResponseGeneratorWrapper response_generator;
  auto channel = BuildChannel("", response_generator, args);
  auto stub = BuildStub(channel);
  response_generator.SetNextResolution(ports);
  EXPECT_EQ(GRPC_CHANNEL_IDLE, channel->GetState(false));

  CheckRpcSendFailure(
      DEBUG_LOCATION, stub, StatusCode::UNAVAILABLE,
      MakeConnectionFailureRegex("failed to connect to all addresses"));

  EXPECT_EQ(GRPC_CHANNEL_TRANSIENT_FAILURE, channel->GetState(false));

  StartServers(1, {ports.back()});

  EXPECT_TRUE(channel->WaitForStateChange(GRPC_CHANNEL_TRANSIENT_FAILURE,
                                          grpc_timeout_seconds_to_deadline(4)));
  EXPECT_EQ(GRPC_CHANNEL_READY, channel->GetState(false));
  CheckRpcSendOk(DEBUG_LOCATION, stub);
}

using RoundRobinTest = ClientLbEnd2endTest;

TEST_F(RoundRobinTest, Basic) {

  const int kNumServers = 3;
  StartServers(kNumServers);
  FakeResolverResponseGeneratorWrapper response_generator;
  auto channel = BuildChannel("round_robin", response_generator);
  auto stub = BuildStub(channel);
  response_generator.SetNextResolution(GetServersPorts());

  do {
    CheckRpcSendOk(DEBUG_LOCATION, stub);
  } while (!SeenAllServers());
  ResetCounters();

  WaitForServer(DEBUG_LOCATION, stub, servers_.size() - 1);
  std::vector<int> connection_order;
  for (size_t i = 0; i < servers_.size(); ++i) {
    CheckRpcSendOk(DEBUG_LOCATION, stub);
    UpdateConnectionOrder(servers_, &connection_order);
  }

  const auto expected = std::vector<int>{0, 1, 2};
  EXPECT_EQ(expected, connection_order);

  EXPECT_EQ("round_robin", channel->GetLoadBalancingPolicyName());
}

TEST_F(RoundRobinTest, ProcessPending) {
  StartServers(1);
  FakeResolverResponseGeneratorWrapper response_generator;
  auto channel = BuildChannel("round_robin", response_generator);
  auto stub = BuildStub(channel);
  response_generator.SetNextResolution({servers_[0]->port_});
  WaitForServer(DEBUG_LOCATION, stub, 0);

  FakeResolverResponseGeneratorWrapper second_response_generator;
  auto second_channel = BuildChannel("round_robin", second_response_generator);
  auto second_stub = BuildStub(second_channel);
  second_response_generator.SetNextResolution({servers_[0]->port_});
  CheckRpcSendOk(DEBUG_LOCATION, second_stub);
}

TEST_F(RoundRobinTest, Updates) {

  const int kNumServers = 3;
  StartServers(kNumServers);
  FakeResolverResponseGeneratorWrapper response_generator;
  auto channel = BuildChannel("round_robin", response_generator);
  auto stub = BuildStub(channel);

  LOG(INFO) << "*** FIRST BACKEND ***";
  std::vector<int> ports = {servers_[0]->port_};
  response_generator.SetNextResolution(ports);
  WaitForServer(DEBUG_LOCATION, stub, 0);

  for (size_t i = 0; i < 10; ++i) CheckRpcSendOk(DEBUG_LOCATION, stub);
  EXPECT_EQ(10, servers_[0]->service_.request_count());
  EXPECT_EQ(0, servers_[1]->service_.request_count());
  EXPECT_EQ(0, servers_[2]->service_.request_count());
  ResetCounters();

  LOG(INFO) << "*** SECOND BACKEND ***";
  ports.clear();
  ports.emplace_back(servers_[1]->port_);
  response_generator.SetNextResolution(ports);

  EXPECT_EQ(0, servers_[1]->service_.request_count());
  WaitForServer(DEBUG_LOCATION, stub, 1);
  for (size_t i = 0; i < 10; ++i) CheckRpcSendOk(DEBUG_LOCATION, stub);
  EXPECT_EQ(0, servers_[0]->service_.request_count());
  EXPECT_EQ(10, servers_[1]->service_.request_count());
  EXPECT_EQ(0, servers_[2]->service_.request_count());
  ResetCounters();

  LOG(INFO) << "*** THIRD BACKEND ***";
  ports.clear();
  ports.emplace_back(servers_[2]->port_);
  response_generator.SetNextResolution(ports);
  WaitForServer(DEBUG_LOCATION, stub, 2);
  for (size_t i = 0; i < 10; ++i) CheckRpcSendOk(DEBUG_LOCATION, stub);
  EXPECT_EQ(0, servers_[0]->service_.request_count());
  EXPECT_EQ(0, servers_[1]->service_.request_count());
  EXPECT_EQ(10, servers_[2]->service_.request_count());
  ResetCounters();

  LOG(INFO) << "*** ALL BACKENDS ***";
  ports.clear();
  ports.emplace_back(servers_[0]->port_);
  ports.emplace_back(servers_[1]->port_);
  ports.emplace_back(servers_[2]->port_);
  response_generator.SetNextResolution(ports);
  WaitForServers(DEBUG_LOCATION, stub);

  for (size_t i = 0; i < 3; ++i) CheckRpcSendOk(DEBUG_LOCATION, stub);
  EXPECT_EQ(1, servers_[0]->service_.request_count());
  EXPECT_EQ(1, servers_[1]->service_.request_count());
  EXPECT_EQ(1, servers_[2]->service_.request_count());
  ResetCounters();

  LOG(INFO) << "*** NO BACKENDS ***";
  ports.clear();
  response_generator.SetNextResolution(ports);
  WaitForChannelNotReady(channel.get());
  CheckRpcSendFailure(
      DEBUG_LOCATION, stub, StatusCode::UNAVAILABLE,
      "empty address list \\(fake resolver empty address list\\)");
  servers_[0]->service_.ResetCounters();

  LOG(INFO) << "*** BACK TO SECOND BACKEND ***";
  ports.clear();
  ports.emplace_back(servers_[1]->port_);
  response_generator.SetNextResolution(ports);
  WaitForChannelReady(channel.get());
  WaitForServer(DEBUG_LOCATION, stub, 1);
  EXPECT_EQ(GRPC_CHANNEL_READY, channel->GetState(false));

  EXPECT_EQ("round_robin", channel->GetLoadBalancingPolicyName());
}

TEST_F(RoundRobinTest, UpdateInError) {
  StartServers(2);
  FakeResolverResponseGeneratorWrapper response_generator;
  auto channel = BuildChannel("round_robin", response_generator);
  auto stub = BuildStub(channel);

  response_generator.SetNextResolution(GetServersPorts(0, 1));

  for (size_t i = 0; i < 10; ++i) {
    CheckRpcSendOk(DEBUG_LOCATION, stub, false,
                   nullptr, 4000);
  }
  EXPECT_EQ(10, servers_[0]->service_.request_count());
  EXPECT_EQ(0, servers_[1]->service_.request_count());
  servers_[0]->service_.ResetCounters();

  std::vector<int> ports = {servers_[0]->port_, grpc_pick_unused_port_or_die(),
                            servers_[1]->port_};
  response_generator.SetNextResolution(ports);
  WaitForServers(DEBUG_LOCATION, stub, 0, 2, nullptr,
                 absl::Seconds(60));

  // Note: The split may be slightly uneven because of an extra picker

  for (size_t i = 0; i < 10; ++i) {
    CheckRpcSendOk(DEBUG_LOCATION, stub, false,
                   nullptr, 4000);
  }
  EXPECT_THAT(servers_[0]->service_.request_count(),
              ::testing::AllOf(::testing::Ge(4), ::testing::Le(6)));
  EXPECT_THAT(servers_[1]->service_.request_count(),
              ::testing::AllOf(::testing::Ge(4), ::testing::Le(6)));
  EXPECT_EQ(10, servers_[0]->service_.request_count() +
                    servers_[1]->service_.request_count());
}

TEST_F(RoundRobinTest, ManyUpdates) {

  const int kNumServers = 3;
  StartServers(kNumServers);
  FakeResolverResponseGeneratorWrapper response_generator;
  auto channel = BuildChannel("round_robin", response_generator);
  auto stub = BuildStub(channel);
  std::vector<int> ports = GetServersPorts();
  for (size_t i = 0; i < 1000; ++i) {
    std::shuffle(ports.begin(), ports.end(),
                 std::mt19937(std::random_device()()));
    response_generator.SetNextResolution(ports);
    if (i % 10 == 0) CheckRpcSendOk(DEBUG_LOCATION, stub);
  }

  EXPECT_EQ("round_robin", channel->GetLoadBalancingPolicyName());
}

TEST_F(RoundRobinTest, ReresolveOnSubchannelConnectionFailure) {

  StartServers(3);

  FakeResolverResponseGeneratorWrapper response_generator;
  auto channel = BuildChannel("round_robin", response_generator);
  auto stub = BuildStub(channel);

  std::vector<int> ports = {servers_[0]->port_, servers_[1]->port_};
  response_generator.SetNextResolution(ports);

  WaitForServers(DEBUG_LOCATION, stub, 0, 2);

  LOG(INFO) << "****** SENDING GOAWAY FROM SERVER 0 *******";
  {
    grpc_core::ExecCtx exec_ctx;
    grpc_core::Server::FromC(servers_[0]->server_->c_server())->SendGoaways();
  }
  LOG(INFO) << "****** WAITING FOR RE-RESOLUTION REQUEST *******";
  EXPECT_TRUE(response_generator.Get()->WaitForReresolutionRequest(
      absl::Seconds(5 * grpc_test_slowdown_factor())));
  LOG(INFO) << "****** RE-RESOLUTION REQUEST SEEN *******";

  ports.push_back(servers_[2]->port_);
  response_generator.SetNextResolution(ports);

  WaitForServer(DEBUG_LOCATION, stub, 2);
}

TEST_F(RoundRobinTest, FailsEmptyResolverUpdate) {
  FakeResolverResponseGeneratorWrapper response_generator;
  auto channel = BuildChannel("round_robin", response_generator);
  auto stub = BuildStub(channel);
  LOG(INFO) << "****** SENDING INITIAL RESOLVER RESULT *******";

  grpc_core::Notification notification;
  grpc_core::Resolver::Result result;
  result.addresses.emplace();
  result.resolution_note = "injected error";
  result.result_health_callback = [&](absl::Status status) {
    EXPECT_EQ(status, absl::UnavailableError("empty address list"));
    notification.Notify();
  };
  response_generator.SetResponse(std::move(result));

  LOG(INFO) << "****** TELLING CHANNEL TO CONNECT *******";
  auto predicate = [](grpc_connectivity_state state) {
    return state == GRPC_CHANNEL_TRANSIENT_FAILURE;
  };
  EXPECT_TRUE(
      WaitForChannelState(channel.get(), predicate, true));

  notification.WaitForNotification();

  CheckRpcSendFailure(DEBUG_LOCATION, stub, StatusCode::UNAVAILABLE,
                      "empty address list \\(injected error\\)");

  LOG(INFO) << "****** SENDING NEXT RESOLVER RESULT *******";
  StartServers(1);
  response_generator.SetNextResolution(GetServersPorts());
  LOG(INFO) << "****** SENDING WAIT_FOR_READY RPC *******";
  CheckRpcSendOk(DEBUG_LOCATION, stub, true);
}

TEST_F(RoundRobinTest, TransientFailure) {

  const int kNumServers = 3;
  StartServers(kNumServers);
  FakeResolverResponseGeneratorWrapper response_generator;
  auto channel = BuildChannel("round_robin", response_generator);
  auto stub = BuildStub(channel);
  response_generator.SetNextResolution(GetServersPorts());
  EXPECT_TRUE(WaitForChannelReady(channel.get()));

  for (size_t i = 0; i < servers_.size(); ++i) {
    servers_[i]->Shutdown();
  }
  auto predicate = [](grpc_connectivity_state state) {
    return state == GRPC_CHANNEL_TRANSIENT_FAILURE;
  };
  EXPECT_TRUE(WaitForChannelState(channel.get(), predicate));
  CheckRpcSendFailure(
      DEBUG_LOCATION, stub, StatusCode::UNAVAILABLE,
      MakeConnectionFailureRegex("connections to all backends failing"));
}

TEST_F(RoundRobinTest, TransientFailureAtStartup) {

  FakeResolverResponseGeneratorWrapper response_generator;
  auto channel = BuildChannel("round_robin", response_generator);
  auto stub = BuildStub(channel);
  response_generator.SetNextResolution({
      grpc_pick_unused_port_or_die(),
      grpc_pick_unused_port_or_die(),
      grpc_pick_unused_port_or_die(),
  });
  for (size_t i = 0; i < servers_.size(); ++i) {
    servers_[i]->Shutdown();
  }
  auto predicate = [](grpc_connectivity_state state) {
    return state == GRPC_CHANNEL_TRANSIENT_FAILURE;
  };
  EXPECT_TRUE(WaitForChannelState(channel.get(), predicate, true));
  CheckRpcSendFailure(
      DEBUG_LOCATION, stub, StatusCode::UNAVAILABLE,
      MakeConnectionFailureRegex("connections to all backends failing"));
}

TEST_F(RoundRobinTest, StaysInTransientFailureInSubsequentConnecting) {

  ConnectionAttemptInjector injector;

  const int port = grpc_pick_unused_port_or_die();

  FakeResolverResponseGeneratorWrapper response_generator;
  auto channel = BuildChannel("round_robin", response_generator);
  auto stub = BuildStub(channel);
  response_generator.SetNextResolution({port});

  LOG(INFO) << "=== WAITING FOR CHANNEL TO REPORT TF ===";
  auto predicate = [](grpc_connectivity_state state) {
    return state == GRPC_CHANNEL_TRANSIENT_FAILURE;
  };
  EXPECT_TRUE(
      WaitForChannelState(channel.get(), predicate, true));

  auto hold = injector.AddHold(port);
  hold->Wait();

  EXPECT_EQ(GRPC_CHANNEL_TRANSIENT_FAILURE, channel->GetState(false));

  LOG(INFO) << "=== EXPECTING RPCs TO FAIL ===";
  for (size_t i = 0; i < 5; ++i) {
    CheckRpcSendFailure(
        DEBUG_LOCATION, stub, StatusCode::UNAVAILABLE,
        MakeConnectionFailureRegex("connections to all backends failing"));
  }

  hold->Resume();
}

TEST_F(RoundRobinTest, ReportsLatestStatusInTransientFailure) {

  ConnectionAttemptInjector injector;

  const std::vector<int> ports = {grpc_pick_unused_port_or_die(),
                                  grpc_pick_unused_port_or_die()};

  FakeResolverResponseGeneratorWrapper response_generator;
  auto channel = BuildChannel("round_robin", response_generator);
  auto stub = BuildStub(channel);
  response_generator.SetNextResolution(ports);

  CheckRpcSendFailure(
      DEBUG_LOCATION, stub, StatusCode::UNAVAILABLE,
      MakeConnectionFailureRegex("connections to all backends failing"));

  auto hold1 = injector.AddHold(ports[0]);
  auto hold2 = injector.AddHold(ports[1]);
  hold1->Wait();
  hold2->Wait();

  hold1->Fail(GRPC_ERROR_CREATE("Survey says... Bzzzzt!"));

  absl::Time deadline =
      absl::Now() + (absl::Seconds(5) * grpc_test_slowdown_factor());
  while (true) {
    Status status = SendRpc(stub);
    EXPECT_EQ(StatusCode::UNAVAILABLE, status.error_code());
    if (::testing::Matches(::testing::MatchesRegex(
            "connections to all backends failing; last error: "
            "UNKNOWN: (ipv6:%5B::1%5D|ipv4:127.0.0.1):[0-9]+: "
            "Survey says... Bzzzzt!"))(status.error_message())) {
      break;
    }
    LOG(INFO) << "STATUS MESSAGE: " << status.error_message();
    EXPECT_THAT(status.error_message(),
                ::testing::MatchesRegex(MakeConnectionFailureRegex(
                    "connections to all backends failing")));
    EXPECT_LT(absl::Now(), deadline);
    if (absl::Now() >= deadline) break;
  }

  hold2->Resume();
}

TEST_F(RoundRobinTest, DoesNotFailRpcsUponDisconnection) {

  ConnectionAttemptInjector injector;

  StartServers(1);

  FakeResolverResponseGeneratorWrapper response_generator;
  auto channel = BuildChannel("round_robin", response_generator);
  auto stub = BuildStub(channel);
  response_generator.SetNextResolution(GetServersPorts());

  LOG(INFO) << "=== STARTING CLIENT THREAD ===";
  std::atomic<bool> shutdown{false};
  gpr_event ev;
  gpr_event_init(&ev);
  std::thread thd([&]() {
    LOG(INFO) << "sending first RPC";
    CheckRpcSendOk(DEBUG_LOCATION, stub);
    gpr_event_set(&ev, reinterpret_cast<void*>(1));
    while (!shutdown.load()) {
      LOG(INFO) << "sending RPC";
      CheckRpcSendOk(DEBUG_LOCATION, stub);
    }
  });

  LOG(INFO) << "=== WAITING FOR FIRST RPC TO COMPLETE ===";
  ASSERT_EQ(reinterpret_cast<void*>(1),
            gpr_event_wait(&ev, grpc_timeout_seconds_to_deadline(1)));

  ASSERT_EQ(GRPC_CHANNEL_READY, channel->GetState(false));

  auto hold1 =
      injector.AddHold(servers_[0]->port_, true);

  LOG(INFO) << "=== SHUTTING DOWN SERVER ===";
  {
    grpc_core::ExecCtx exec_ctx;
    grpc_core::Server::FromC(servers_[0]->server_->c_server())->SendGoaways();
  }
  gpr_sleep_until(grpc_timeout_seconds_to_deadline(1));
  servers_[0]->Shutdown();

  LOG(INFO) << "=== WAITING FOR RECONNECTION ATTEMPT ===";
  hold1->Wait();

  LOG(INFO) << "=== RESTARTING SERVER ===";
  StartServer(0);
  hold1->Resume();

  LOG(INFO) << "=== WAITING FOR RECONNECTION ATTEMPT TO COMPLETE ===";
  hold1->WaitForCompletion();

  LOG(INFO) << "=== SHUTTING DOWN CLIENT THREAD ===";
  shutdown.store(true);
  thd.join();
}

TEST_F(RoundRobinTest, SingleReconnect) {
  const int kNumServers = 3;
  StartServers(kNumServers);
  const auto ports = GetServersPorts();
  FakeResolverResponseGeneratorWrapper response_generator;
  auto channel = BuildChannel("round_robin", response_generator);
  auto stub = BuildStub(channel);
  response_generator.SetNextResolution(ports);
  WaitForServers(DEBUG_LOCATION, stub);

  WaitForServer(DEBUG_LOCATION, stub, servers_.size() - 1);
  for (size_t i = 0; i < servers_.size(); ++i) {
    CheckRpcSendOk(DEBUG_LOCATION, stub);
    EXPECT_EQ(1, servers_[i]->service_.request_count()) << "for backend #" << i;
  }

  for (size_t i = 0; i < servers_.size(); ++i) {
    EXPECT_EQ(1, servers_[i]->service_.request_count());
  }

  servers_[0]->StopListeningAndSendGoaways();

  ResetCounters();
  SendRpcsUntil(
      DEBUG_LOCATION, stub,
      [&, num_rpcs_not_on_backend_0 = 0](const Status& status) mutable {
        EXPECT_TRUE(status.ok()) << "code=" << status.error_code()
                                 << " message=" << status.error_message();
        if (servers_[0]->service_.request_count() == 1) {
          num_rpcs_not_on_backend_0 = 0;
        } else {
          ++num_rpcs_not_on_backend_0;
        }
        ResetCounters();
        return num_rpcs_not_on_backend_0 < kNumServers;
      });

  for (int i = 0; i < 10 * kNumServers; ++i) {
    CheckRpcSendOk(DEBUG_LOCATION, stub);
  }

  EXPECT_EQ(0UL, servers_[0]->service_.request_count());

  servers_[0]->Shutdown();
  StartServer(0);

  WaitForServer(DEBUG_LOCATION, stub, 0);
}

TEST_F(RoundRobinTest, ServersHealthCheckingUnimplementedTreatedAsHealthy) {
  StartServers(1);
  ChannelArguments args;
  args.SetServiceConfigJSON(
      "{\"healthCheckConfig\": "
      "{\"serviceName\": \"health_check_service_name\"}}");
  FakeResolverResponseGeneratorWrapper response_generator;
  auto channel = BuildChannel("round_robin", response_generator, args);
  auto stub = BuildStub(channel);
  response_generator.SetNextResolution({servers_[0]->port_});
  EXPECT_TRUE(WaitForChannelReady(channel.get()));
  CheckRpcSendOk(DEBUG_LOCATION, stub);
}

TEST_F(RoundRobinTest, HealthChecking) {
  EnableDefaultHealthCheckService(true);

  const int kNumServers = 3;
  StartServers(kNumServers);
  ChannelArguments args;
  args.SetServiceConfigJSON(
      "{\"healthCheckConfig\": "
      "{\"serviceName\": \"health_check_service_name\"}}");
  FakeResolverResponseGeneratorWrapper response_generator;
  auto channel = BuildChannel("round_robin", response_generator, args);
  auto stub = BuildStub(channel);
  response_generator.SetNextResolution(GetServersPorts());

  LOG(INFO)
      << "*** initial state: unknown health check service name for all servers";
  EXPECT_FALSE(WaitForChannelReady(channel.get(), 1));

  LOG(INFO) << "*** server 0 healthy";
  servers_[0]->SetServingStatus("health_check_service_name", true);
  EXPECT_TRUE(WaitForChannelReady(channel.get()));

  WaitForServer(DEBUG_LOCATION, stub, 0);
  for (int i = 0; i < 10; ++i) {
    CheckRpcSendOk(DEBUG_LOCATION, stub);
  }
  EXPECT_EQ(10, servers_[0]->service_.request_count());
  EXPECT_EQ(0, servers_[1]->service_.request_count());
  EXPECT_EQ(0, servers_[2]->service_.request_count());

  LOG(INFO) << "*** server 2 healthy";
  servers_[2]->SetServingStatus("health_check_service_name", true);
  WaitForServer(DEBUG_LOCATION, stub, 2);
  for (int i = 0; i < 10; ++i) {
    CheckRpcSendOk(DEBUG_LOCATION, stub);
  }
  EXPECT_EQ(5, servers_[0]->service_.request_count());
  EXPECT_EQ(0, servers_[1]->service_.request_count());
  EXPECT_EQ(5, servers_[2]->service_.request_count());

  LOG(INFO) << "*** server 1 healthy";
  servers_[1]->SetServingStatus("health_check_service_name", true);
  WaitForServer(DEBUG_LOCATION, stub, 1);
  for (int i = 0; i < 9; ++i) {
    CheckRpcSendOk(DEBUG_LOCATION, stub);
  }
  EXPECT_EQ(3, servers_[0]->service_.request_count());
  EXPECT_EQ(3, servers_[1]->service_.request_count());
  EXPECT_EQ(3, servers_[2]->service_.request_count());

  LOG(INFO) << "*** server 0 unhealthy";
  servers_[0]->SetServingStatus("health_check_service_name", false);
  do {
    ResetCounters();
    for (int i = 0; i < kNumServers; ++i) {
      CheckRpcSendOk(DEBUG_LOCATION, stub);
    }
  } while (servers_[1]->service_.request_count() != 2 &&
           servers_[2]->service_.request_count() != 2);

  LOG(INFO) << "*** all servers unhealthy";
  servers_[1]->SetServingStatus("health_check_service_name", false);
  servers_[2]->SetServingStatus("health_check_service_name", false);
  EXPECT_TRUE(WaitForChannelNotReady(channel.get()));

  SendRpcsUntil(DEBUG_LOCATION, stub, [&](const Status& status) {
    if (status.ok()) return true;
    EXPECT_EQ(status.error_code(), StatusCode::UNAVAILABLE);
    EXPECT_THAT(
        status.error_message(),
        ::testing::MatchesRegex(
            "connections to all backends failing; last error: "
            "(ipv6:%5B::1%5D|ipv4:127.0.0.1):[0-9]+: backend unhealthy"));
    return false;
  });

  EnableDefaultHealthCheckService(false);
}

TEST_F(RoundRobinTest, HealthCheckingHandlesSubchannelFailure) {
  EnableDefaultHealthCheckService(true);

  const int kNumServers = 3;
  StartServers(kNumServers);
  servers_[0]->SetServingStatus("health_check_service_name", true);
  servers_[1]->SetServingStatus("health_check_service_name", true);
  servers_[2]->SetServingStatus("health_check_service_name", true);
  ChannelArguments args;
  args.SetServiceConfigJSON(
      "{\"healthCheckConfig\": "
      "{\"serviceName\": \"health_check_service_name\"}}");
  FakeResolverResponseGeneratorWrapper response_generator;
  auto channel = BuildChannel("round_robin", response_generator, args);
  auto stub = BuildStub(channel);
  response_generator.SetNextResolution(GetServersPorts());
  WaitForServer(DEBUG_LOCATION, stub, 0);

  servers_[0]->StopListeningAndSendGoaways();
  response_generator.SetNextResolution(GetServersPorts());

  for (size_t i = 0; i < 100; i++) {
    CheckRpcSendOk(DEBUG_LOCATION, stub);
  }
}

TEST_F(RoundRobinTest, WithHealthCheckingInhibitPerChannel) {
  EnableDefaultHealthCheckService(true);

  const int kNumServers = 1;
  StartServers(kNumServers);

  auto channel_creds =
      std::make_shared<FakeTransportSecurityChannelCredentials>();

  ChannelArguments args;
  args.SetServiceConfigJSON(
      "{\"healthCheckConfig\": "
      "{\"serviceName\": \"health_check_service_name\"}}");
  FakeResolverResponseGeneratorWrapper response_generator1;
  auto channel1 =
      BuildChannel("round_robin", response_generator1, args, channel_creds);
  auto stub1 = BuildStub(channel1);
  std::vector<int> ports = GetServersPorts();
  response_generator1.SetNextResolution(ports);

  args.SetInt(GRPC_ARG_INHIBIT_HEALTH_CHECKING, 1);
  FakeResolverResponseGeneratorWrapper response_generator2;
  auto channel2 =
      BuildChannel("round_robin", response_generator2, args, channel_creds);
  auto stub2 = BuildStub(channel2);
  response_generator2.SetNextResolution(ports);

  EXPECT_FALSE(WaitForChannelReady(channel1.get(), 1));
  CheckRpcSendFailure(
      DEBUG_LOCATION, stub1, StatusCode::UNAVAILABLE,
      "connections to all backends failing; last error: "
      "(ipv6:%5B::1%5D|ipv4:127.0.0.1):[0-9]+: backend unhealthy");

  EXPECT_TRUE(WaitForChannelReady(channel2.get(), 1));
  CheckRpcSendOk(DEBUG_LOCATION, stub2);

  servers_[0]->SetServingStatus("health_check_service_name", true);
  CheckRpcSendOk(DEBUG_LOCATION, stub1, true );

  EXPECT_EQ(1UL, servers_[0]->service_.clients().size());

  EnableDefaultHealthCheckService(false);
}

TEST_F(RoundRobinTest, HealthCheckingServiceNamePerChannel) {
  EnableDefaultHealthCheckService(true);

  const int kNumServers = 1;
  StartServers(kNumServers);

  auto channel_creds =
      std::make_shared<FakeTransportSecurityChannelCredentials>();

  ChannelArguments args;
  args.SetServiceConfigJSON(
      "{\"healthCheckConfig\": "
      "{\"serviceName\": \"health_check_service_name\"}}");
  FakeResolverResponseGeneratorWrapper response_generator1;
  auto channel1 =
      BuildChannel("round_robin", response_generator1, args, channel_creds);
  auto stub1 = BuildStub(channel1);
  std::vector<int> ports = GetServersPorts();
  response_generator1.SetNextResolution(ports);

  ChannelArguments args2;
  args2.SetServiceConfigJSON(
      "{\"healthCheckConfig\": "
      "{\"serviceName\": \"health_check_service_name2\"}}");
  FakeResolverResponseGeneratorWrapper response_generator2;
  auto channel2 =
      BuildChannel("round_robin", response_generator2, args2, channel_creds);
  auto stub2 = BuildStub(channel2);
  response_generator2.SetNextResolution(ports);

  servers_[0]->SetServingStatus("health_check_service_name2", true);

  EXPECT_FALSE(WaitForChannelReady(channel1.get(), 1));
  CheckRpcSendFailure(
      DEBUG_LOCATION, stub1, StatusCode::UNAVAILABLE,
      "connections to all backends failing; last error: "
      "(ipv6:%5B::1%5D|ipv4:127.0.0.1):[0-9]+: backend unhealthy");

  EXPECT_TRUE(WaitForChannelReady(channel2.get(), 1));
  CheckRpcSendOk(DEBUG_LOCATION, stub2);

  servers_[0]->SetServingStatus("health_check_service_name", true);
  CheckRpcSendOk(DEBUG_LOCATION, stub1, true );

  EXPECT_EQ(1UL, servers_[0]->service_.clients().size());

  EnableDefaultHealthCheckService(false);
}

TEST_F(RoundRobinTest,
       HealthCheckingServiceNameChangesAfterSubchannelsCreated) {
  EnableDefaultHealthCheckService(true);

  const int kNumServers = 1;
  StartServers(kNumServers);

  const char* kServiceConfigJson =
      "{\"healthCheckConfig\": "
      "{\"serviceName\": \"health_check_service_name\"}}";
  FakeResolverResponseGeneratorWrapper response_generator;
  auto channel = BuildChannel("round_robin", response_generator);
  auto stub = BuildStub(channel);
  std::vector<int> ports = GetServersPorts();
  response_generator.SetNextResolution(ports, kServiceConfigJson);
  servers_[0]->SetServingStatus("health_check_service_name", true);
  EXPECT_TRUE(WaitForChannelReady(channel.get(), 1 ));

  const char* kServiceConfigJson2 =
      "{\"healthCheckConfig\": "
      "{\"serviceName\": \"health_check_service_name2\"}}";
  response_generator.SetNextResolution(ports, kServiceConfigJson2);
  EXPECT_TRUE(WaitForChannelNotReady(channel.get()));

  EnableDefaultHealthCheckService(false);
}

TEST_F(RoundRobinTest, HealthCheckingRetryOnStreamEnd) {

  const int kNumServers = 2;
  CreateServers(kNumServers);
  EnableNoopHealthCheckService();
  StartServer(0);
  StartServer(1);
  ChannelArguments args;

  args.SetServiceConfigJSON(
      "{\"healthCheckConfig\": "
      "{\"serviceName\": \"health_check_service_name\"}}");
  FakeResolverResponseGeneratorWrapper response_generator;
  auto channel = BuildChannel("round_robin", response_generator, args);
  response_generator.SetNextResolution(GetServersPorts());
  EXPECT_FALSE(WaitForChannelReady(channel.get()));
  EXPECT_GT(servers_[0]->noop_health_check_service_impl_.request_count(), 1);
  EXPECT_GT(servers_[1]->noop_health_check_service_impl_.request_count(), 1);
}

class ClientLbPickArgsTest : public ClientLbEnd2endTest {
 protected:
  void SetUp() override {
    ClientLbEnd2endTest::SetUp();
    current_test_instance_ = this;
  }

  static void SetUpTestSuite() {
    grpc_core::CoreConfiguration::Reset();
    grpc_core::CoreConfiguration::RegisterEphemeralBuilder(
        [](grpc_core::CoreConfiguration::Builder* builder) {
          grpc_core::RegisterTestPickArgsLoadBalancingPolicy(builder,
                                                             SavePickArgs);
        });
    grpc_init();
  }

  static void TearDownTestSuite() {
    grpc_shutdown();
    grpc_core::CoreConfiguration::Reset();
  }

  std::vector<grpc_core::PickArgsSeen> args_seen_list() {
    grpc_core::MutexLock lock(&mu_);
    return args_seen_list_;
  }

  static std::string ArgsSeenListString(
      const std::vector<grpc_core::PickArgsSeen>& args_seen_list) {
    std::vector<std::string> entries;
    for (const auto& args_seen : args_seen_list) {
      std::vector<std::string> metadata;
      for (const auto& [key, value] : args_seen.metadata) {
        metadata.push_back(absl::StrCat(key, "=", value));
      }
      entries.push_back(absl::StrFormat("{path=\"%s\", metadata=[%s]}",
                                        args_seen.path,
                                        absl::StrJoin(metadata, ", ")));
    }
    return absl::StrCat("[", absl::StrJoin(entries, ", "), "]");
  }

 private:
  static void SavePickArgs(const grpc_core::PickArgsSeen& args_seen) {
    ClientLbPickArgsTest* self = current_test_instance_;
    grpc_core::MutexLock lock(&self->mu_);
    self->args_seen_list_.emplace_back(args_seen);
  }

  static ClientLbPickArgsTest* current_test_instance_;
  grpc_core::Mutex mu_;
  std::vector<grpc_core::PickArgsSeen> args_seen_list_;
};

ClientLbPickArgsTest* ClientLbPickArgsTest::current_test_instance_ = nullptr;

TEST_F(ClientLbPickArgsTest, Basic) {
  const int kNumServers = 1;
  StartServers(kNumServers);
  FakeResolverResponseGeneratorWrapper response_generator;
  auto channel = BuildChannel("test_pick_args_lb", response_generator);
  auto stub = BuildStub(channel);
  response_generator.SetNextResolution(GetServersPorts());

  ASSERT_TRUE(channel->WaitForConnected(gpr_inf_future(GPR_CLOCK_MONOTONIC)));

  EXPECT_EQ("test_pick_args_lb", channel->GetLoadBalancingPolicyName());

  CheckRpcSendOk(DEBUG_LOCATION, stub, true);
  auto pick_args_seen_list = args_seen_list();
  EXPECT_THAT(pick_args_seen_list,
              ::testing::ElementsAre(::testing::AllOf(
                  ::testing::Field(&grpc_core::PickArgsSeen::path,
                                   "/grpc.testing.EchoTestService/Echo"),
                  ::testing::Field(&grpc_core::PickArgsSeen::metadata,
                                   ::testing::UnorderedElementsAre(
                                       ::testing::Pair("foo", "1"),
                                       ::testing::Pair("bar", "2"),
                                       ::testing::Pair("baz", "3"))))))
      << ArgsSeenListString(pick_args_seen_list);
}

class OrcaLoadReportBuilder {
 public:
  OrcaLoadReportBuilder() = default;
  explicit OrcaLoadReportBuilder(const OrcaLoadReport& report)
      : report_(report) {}
  OrcaLoadReportBuilder& SetApplicationUtilization(double v) {
    report_.set_application_utilization(v);
    return *this;
  }
  OrcaLoadReportBuilder& SetCpuUtilization(double v) {
    report_.set_cpu_utilization(v);
    return *this;
  }
  OrcaLoadReportBuilder& SetMemUtilization(double v) {
    report_.set_mem_utilization(v);
    return *this;
  }
  OrcaLoadReportBuilder& SetQps(double v) {
    report_.set_rps_fractional(v);
    return *this;
  }
  OrcaLoadReportBuilder& SetEps(double v) {
    report_.set_eps(v);
    return *this;
  }
  OrcaLoadReportBuilder& SetRequestCost(absl::string_view n, double v) {
    (*report_.mutable_request_cost())[n] = v;
    return *this;
  }
  OrcaLoadReportBuilder& SetUtilization(absl::string_view n, double v) {
    (*report_.mutable_utilization())[n] = v;
    return *this;
  }
  OrcaLoadReportBuilder& SetNamedMetrics(absl::string_view n, double v) {
    (*report_.mutable_named_metrics())[n] = v;
    return *this;
  }
  OrcaLoadReport Build() { return std::move(report_); }

 private:
  OrcaLoadReport report_;
};

OrcaLoadReport BackendMetricDataToOrcaLoadReport(
    const grpc_core::BackendMetricData& backend_metric_data) {
  auto builder = OrcaLoadReportBuilder()
                     .SetApplicationUtilization(
                         backend_metric_data.application_utilization)
                     .SetCpuUtilization(backend_metric_data.cpu_utilization)
                     .SetMemUtilization(backend_metric_data.mem_utilization)
                     .SetQps(backend_metric_data.qps)
                     .SetEps(backend_metric_data.eps);
  for (const auto& [key, value] : backend_metric_data.request_cost) {
    builder.SetRequestCost(std::string(key), value);
  }
  for (const auto& [key, value] : backend_metric_data.utilization) {
    builder.SetUtilization(std::string(key), value);
  }
  for (const auto& [key, value] : backend_metric_data.named_metrics) {
    builder.SetNamedMetrics(std::string(key), value);
  }
  return builder.Build();
}

void CheckLoadReportAsExpected(const OrcaLoadReport& actual,
                               const OrcaLoadReport& expected) {
  EXPECT_EQ(actual.application_utilization(),
            expected.application_utilization());
  EXPECT_EQ(actual.cpu_utilization(), expected.cpu_utilization());
  EXPECT_EQ(actual.mem_utilization(), expected.mem_utilization());
  EXPECT_EQ(actual.rps_fractional(), expected.rps_fractional());
  EXPECT_EQ(actual.eps(), expected.eps());
  EXPECT_EQ(actual.request_cost().size(), expected.request_cost().size());
  for (const auto& [key, value] : actual.request_cost()) {
    auto it = expected.request_cost().find(key);
    ASSERT_NE(it, expected.request_cost().end());
    EXPECT_EQ(it->second, value);
  }
  EXPECT_EQ(actual.utilization().size(), expected.utilization().size());
  for (const auto& [key, value] : actual.utilization()) {
    auto it = expected.utilization().find(key);
    ASSERT_NE(it, expected.utilization().end());
    EXPECT_EQ(it->second, value);
  }
  EXPECT_EQ(actual.named_metrics().size(), expected.named_metrics().size());
  for (const auto& [key, value] : actual.named_metrics()) {
    auto it = expected.named_metrics().find(key);
    ASSERT_NE(it, expected.named_metrics().end());
    EXPECT_EQ(it->second, value);
  }
}

class ClientLbInterceptTrailingMetadataTest : public ClientLbEnd2endTest {
 protected:
  void SetUp() override {
    ClientLbEnd2endTest::SetUp();
    current_test_instance_ = this;
  }

  static void SetUpTestSuite() {
    grpc_core::CoreConfiguration::Reset();
    grpc_core::CoreConfiguration::RegisterEphemeralBuilder(
        [](grpc_core::CoreConfiguration::Builder* builder) {
          grpc_core::RegisterInterceptRecvTrailingMetadataLoadBalancingPolicy(
              builder, ReportTrailerIntercepted);
        });
    grpc_init();
  }

  static void TearDownTestSuite() {
    grpc_shutdown();
    grpc_core::CoreConfiguration::Reset();
  }

  int num_trailers_intercepted() {
    grpc_core::MutexLock lock(&mu_);
    return num_trailers_intercepted_;
  }

  absl::Status last_status() {
    grpc_core::MutexLock lock(&mu_);
    return last_status_;
  }

  grpc_core::MetadataVector trailing_metadata() {
    grpc_core::MutexLock lock(&mu_);
    return std::move(trailing_metadata_);
  }

  std::optional<OrcaLoadReport> backend_load_report() {
    grpc_core::MutexLock lock(&mu_);
    return std::move(load_report_);
  }

  bool WaitForLbCallback() {
    grpc_core::MutexLock lock(&mu_);
    while (!trailer_intercepted_) {
      if (cond_.WaitWithTimeout(&mu_, absl::Seconds(3))) return false;
    }
    trailer_intercepted_ = false;
    return true;
  }

  void RunPerRpcMetricReportingTest(const OrcaLoadReport& reported,
                                    const OrcaLoadReport& expected) {
    const int kNumServers = 1;
    const int kNumRpcs = 10;
    StartServers(kNumServers);
    FakeResolverResponseGeneratorWrapper response_generator;
    auto channel =
        BuildChannel("intercept_trailing_metadata_lb", response_generator);
    auto stub = BuildStub(channel);
    response_generator.SetNextResolution(GetServersPorts());
    for (size_t i = 0; i < kNumRpcs; ++i) {
      CheckRpcSendOk(DEBUG_LOCATION, stub, false, &reported);
      auto actual = backend_load_report();
      ASSERT_TRUE(actual.has_value());
      CheckLoadReportAsExpected(*actual, expected);
    }

    EXPECT_EQ("intercept_trailing_metadata_lb",
              channel->GetLoadBalancingPolicyName());
    EXPECT_EQ(kNumRpcs, num_trailers_intercepted());
  }

 private:
  static void ReportTrailerIntercepted(
      const grpc_core::TrailingMetadataArgsSeen& args_seen) {
    const auto* backend_metric_data = args_seen.backend_metric_data;
    ClientLbInterceptTrailingMetadataTest* self = current_test_instance_;
    grpc_core::MutexLock lock(&self->mu_);
    self->last_status_ = args_seen.status;
    self->num_trailers_intercepted_++;
    self->trailer_intercepted_ = true;
    self->trailing_metadata_ = args_seen.metadata;
    if (backend_metric_data != nullptr) {
      self->load_report_ =
          BackendMetricDataToOrcaLoadReport(*backend_metric_data);
    }
    self->cond_.Signal();
  }

  static ClientLbInterceptTrailingMetadataTest* current_test_instance_;
  int num_trailers_intercepted_ = 0;
  bool trailer_intercepted_ = false;
  grpc_core::Mutex mu_;
  grpc_core::CondVar cond_;
  absl::Status last_status_;
  grpc_core::MetadataVector trailing_metadata_;
  std::optional<OrcaLoadReport> load_report_;
};

ClientLbInterceptTrailingMetadataTest*
    ClientLbInterceptTrailingMetadataTest::current_test_instance_ = nullptr;

TEST_F(ClientLbInterceptTrailingMetadataTest, StatusOk) {
  StartServers(1);
  FakeResolverResponseGeneratorWrapper response_generator;
  auto channel =
      BuildChannel("intercept_trailing_metadata_lb", response_generator);
  auto stub = BuildStub(channel);
  response_generator.SetNextResolution(GetServersPorts());

  CheckRpcSendOk(DEBUG_LOCATION, stub);

  EXPECT_EQ("intercept_trailing_metadata_lb",
            channel->GetLoadBalancingPolicyName());
  EXPECT_EQ(1, num_trailers_intercepted());
  EXPECT_EQ(absl::OkStatus(), last_status());
}

TEST_F(ClientLbInterceptTrailingMetadataTest, StatusFailed) {
  StartServers(1);
  FakeResolverResponseGeneratorWrapper response_generator;
  auto channel =
      BuildChannel("intercept_trailing_metadata_lb", response_generator);
  auto stub = BuildStub(channel);
  response_generator.SetNextResolution(GetServersPorts());
  EchoRequest request;
  auto* expected_error = request.mutable_param()->mutable_expected_error();
  expected_error->set_code(GRPC_STATUS_PERMISSION_DENIED);
  expected_error->set_error_message("bummer, man");
  Status status = SendRpc(stub, nullptr, 1000,
                          false, &request);
  EXPECT_EQ(status.error_code(), StatusCode::PERMISSION_DENIED);
  EXPECT_EQ(status.error_message(), "bummer, man");
  absl::Status status_seen_by_lb = last_status();
  EXPECT_EQ(status_seen_by_lb.code(), absl::StatusCode::kPermissionDenied);
  EXPECT_EQ(status_seen_by_lb.message(), "bummer, man");
}

TEST_F(ClientLbInterceptTrailingMetadataTest,
       StatusCancelledWithoutStartingRecvTrailingMetadata) {
  StartServers(1);
  FakeResolverResponseGeneratorWrapper response_generator;
  auto channel =
      BuildChannel("intercept_trailing_metadata_lb", response_generator);
  response_generator.SetNextResolution(GetServersPorts());
  auto stub = BuildStub(channel);
  {

    ClientContext ctx;
    auto stream = stub->BidiStream(&ctx);
    ctx.TryCancel();
  }

  ASSERT_TRUE(WaitForLbCallback());

  EXPECT_EQ(1, num_trailers_intercepted());
  absl::Status status_seen_by_lb = last_status();
  EXPECT_EQ(status_seen_by_lb.code(), absl::StatusCode::kCancelled);
  EXPECT_EQ(status_seen_by_lb.message(), "call cancelled");
}

TEST_F(ClientLbInterceptTrailingMetadataTest, InterceptsRetriesDisabled) {
  const int kNumServers = 1;
  const int kNumRpcs = 10;
  StartServers(kNumServers);
  FakeResolverResponseGeneratorWrapper response_generator;
  ChannelArguments channel_args;
  channel_args.SetInt(GRPC_ARG_ENABLE_RETRIES, 0);
  auto channel = BuildChannel("intercept_trailing_metadata_lb",
                              response_generator, channel_args);
  auto stub = BuildStub(channel);
  response_generator.SetNextResolution(GetServersPorts());
  for (size_t i = 0; i < kNumRpcs; ++i) {
    CheckRpcSendOk(DEBUG_LOCATION, stub);
  }

  EXPECT_EQ("intercept_trailing_metadata_lb",
            channel->GetLoadBalancingPolicyName());
  EXPECT_EQ(kNumRpcs, num_trailers_intercepted());
  EXPECT_THAT(trailing_metadata(),
              ::testing::UnorderedElementsAre(

                  ::testing::Pair("grpc-status", "0"),
                  ::testing::Pair("user-agent", ::testing::_),
                  ::testing::Pair("foo", "1"), ::testing::Pair("bar", "2"),
                  ::testing::Pair("baz", "3")));
  EXPECT_FALSE(backend_load_report().has_value());
}

TEST_F(ClientLbInterceptTrailingMetadataTest, InterceptsRetriesEnabled) {
  const int kNumServers = 1;
  const int kNumRpcs = 10;
  StartServers(kNumServers);
  ChannelArguments args;
  args.SetServiceConfigJSON(
      "{\n"
      "  \"methodConfig\": [ {\n"
      "    \"name\": [\n"
      "      { \"service\": \"grpc.testing.EchoTestService\" }\n"
      "    ],\n"
      "    \"retryPolicy\": {\n"
      "      \"maxAttempts\": 3,\n"
      "      \"initialBackoff\": \"1s\",\n"
      "      \"maxBackoff\": \"120s\",\n"
      "      \"backoffMultiplier\": 1.6,\n"
      "      \"retryableStatusCodes\": [ \"ABORTED\" ]\n"
      "    }\n"
      "  } ]\n"
      "}");
  FakeResolverResponseGeneratorWrapper response_generator;
  auto channel =
      BuildChannel("intercept_trailing_metadata_lb", response_generator, args);
  auto stub = BuildStub(channel);
  response_generator.SetNextResolution(GetServersPorts());
  for (size_t i = 0; i < kNumRpcs; ++i) {
    CheckRpcSendOk(DEBUG_LOCATION, stub);
  }

  EXPECT_EQ("intercept_trailing_metadata_lb",
            channel->GetLoadBalancingPolicyName());
  EXPECT_EQ(kNumRpcs, num_trailers_intercepted());
  EXPECT_THAT(trailing_metadata(),
              ::testing::UnorderedElementsAre(

                  ::testing::Pair("grpc-status", "0"),
                  ::testing::Pair("user-agent", ::testing::_),
                  ::testing::Pair("foo", "1"), ::testing::Pair("bar", "2"),
                  ::testing::Pair("baz", "3")));
  EXPECT_FALSE(backend_load_report().has_value());
}

TEST_F(ClientLbInterceptTrailingMetadataTest, Valid) {
  RunPerRpcMetricReportingTest(OrcaLoadReportBuilder()
                                   .SetApplicationUtilization(0.25)
                                   .SetCpuUtilization(0.5)
                                   .SetMemUtilization(0.75)
                                   .SetQps(0.25)
                                   .SetEps(0.1)
                                   .SetRequestCost("foo", -0.8)
                                   .SetRequestCost("bar", 1.4)
                                   .SetUtilization("baz", 1.0)
                                   .SetUtilization("quux", 0.9)
                                   .SetNamedMetrics("metric0", 3.0)
                                   .SetNamedMetrics("metric1", -1.0)
                                   .Build(),
                               OrcaLoadReportBuilder()
                                   .SetApplicationUtilization(0.25)
                                   .SetCpuUtilization(0.5)
                                   .SetMemUtilization(0.75)
                                   .SetQps(0.25)
                                   .SetEps(0.1)
                                   .SetRequestCost("foo", -0.8)
                                   .SetRequestCost("bar", 1.4)
                                   .SetUtilization("baz", 1.0)
                                   .SetUtilization("quux", 0.9)
                                   .SetNamedMetrics("metric0", 3.0)
                                   .SetNamedMetrics("metric1", -1.0)
                                   .Build());
}

TEST_F(ClientLbInterceptTrailingMetadataTest, NegativeValues) {
  RunPerRpcMetricReportingTest(OrcaLoadReportBuilder()
                                   .SetApplicationUtilization(-0.3)
                                   .SetCpuUtilization(-0.1)
                                   .SetMemUtilization(-0.2)
                                   .SetQps(-3)
                                   .SetEps(-4)
                                   .SetRequestCost("foo", -5)
                                   .SetUtilization("bar", -0.6)
                                   .SetNamedMetrics("baz", -0.7)
                                   .Build(),
                               OrcaLoadReportBuilder()
                                   .SetRequestCost("foo", -5)
                                   .SetNamedMetrics("baz", -0.7)
                                   .Build());
}

TEST_F(ClientLbInterceptTrailingMetadataTest, AboveOneUtilization) {
  RunPerRpcMetricReportingTest(OrcaLoadReportBuilder()
                                   .SetApplicationUtilization(1.9)
                                   .SetCpuUtilization(1.1)
                                   .SetMemUtilization(2)
                                   .SetQps(3)
                                   .SetEps(4)
                                   .SetUtilization("foo", 5)
                                   .Build(),
                               OrcaLoadReportBuilder()
                                   .SetApplicationUtilization(1.9)
                                   .SetCpuUtilization(1.1)
                                   .SetQps(3)
                                   .SetEps(4)
                                   .Build());
}

TEST_F(ClientLbInterceptTrailingMetadataTest, BackendMetricDataMerge) {
  const int kNumServers = 1;
  const int kNumRpcs = 10;
  StartServers(kNumServers);
  servers_[0]->server_metric_recorder_->SetApplicationUtilization(0.99);
  servers_[0]->server_metric_recorder_->SetCpuUtilization(0.99);
  servers_[0]->server_metric_recorder_->SetMemoryUtilization(0.99);
  servers_[0]->server_metric_recorder_->SetQps(0.99);
  servers_[0]->server_metric_recorder_->SetEps(0.99);
  servers_[0]->server_metric_recorder_->SetNamedUtilization("foo", 0.99);
  servers_[0]->server_metric_recorder_->SetNamedUtilization("bar", 0.1);
  OrcaLoadReport per_server_load = OrcaLoadReportBuilder()
                                       .SetApplicationUtilization(0.99)
                                       .SetCpuUtilization(0.99)
                                       .SetMemUtilization(0.99)
                                       .SetQps(0.99)
                                       .SetEps(0.99)
                                       .SetUtilization("foo", 0.99)
                                       .SetUtilization("bar", 0.1)
                                       .Build();
  FakeResolverResponseGeneratorWrapper response_generator;
  auto channel =
      BuildChannel("intercept_trailing_metadata_lb", response_generator);
  auto stub = BuildStub(channel);
  response_generator.SetNextResolution(GetServersPorts());
  size_t total_num_rpcs = 0;
  {
    OrcaLoadReport load_report =
        OrcaLoadReportBuilder().SetApplicationUtilization(0.5).Build();
    OrcaLoadReport expected = OrcaLoadReportBuilder(per_server_load)
                                  .SetApplicationUtilization(0.5)
                                  .Build();
    for (size_t i = 0; i < kNumRpcs; ++i) {
      CheckRpcSendOk(DEBUG_LOCATION, stub, false, &load_report);
      auto actual = backend_load_report();
      ASSERT_TRUE(actual.has_value());
      CheckLoadReportAsExpected(*actual, expected);
      ++total_num_rpcs;
    }
  }
  {
    OrcaLoadReport load_report =
        OrcaLoadReportBuilder().SetMemUtilization(0.5).Build();
    OrcaLoadReport expected =
        OrcaLoadReportBuilder(per_server_load).SetMemUtilization(0.5).Build();
    for (size_t i = 0; i < kNumRpcs; ++i) {
      CheckRpcSendOk(DEBUG_LOCATION, stub, false, &load_report);
      auto actual = backend_load_report();
      ASSERT_TRUE(actual.has_value());
      CheckLoadReportAsExpected(*actual, expected);
      ++total_num_rpcs;
    }
  }
  {
    OrcaLoadReport load_report = OrcaLoadReportBuilder().SetQps(0.5).Build();
    OrcaLoadReport expected =
        OrcaLoadReportBuilder(per_server_load).SetQps(0.5).Build();
    for (size_t i = 0; i < kNumRpcs; ++i) {
      CheckRpcSendOk(DEBUG_LOCATION, stub, false, &load_report);
      auto actual = backend_load_report();
      ASSERT_TRUE(actual.has_value());
      CheckLoadReportAsExpected(*actual, expected);
      ++total_num_rpcs;
    }
  }
  {
    OrcaLoadReport load_report = OrcaLoadReportBuilder().SetEps(0.5).Build();
    OrcaLoadReport expected =
        OrcaLoadReportBuilder(per_server_load).SetEps(0.5).Build();
    for (size_t i = 0; i < kNumRpcs; ++i) {
      CheckRpcSendOk(DEBUG_LOCATION, stub, false, &load_report);
      auto actual = backend_load_report();
      ASSERT_TRUE(actual.has_value());
      CheckLoadReportAsExpected(*actual, expected);
      ++total_num_rpcs;
    }
  }
  {
    OrcaLoadReport load_report =
        OrcaLoadReportBuilder()
            .SetUtilization("foo", 0.5)
            .SetUtilization("bar", 1.1)
            .SetUtilization("baz", 1.0)
            .Build();
    auto expected = OrcaLoadReportBuilder(per_server_load)
                        .SetUtilization("foo", 0.5)
                        .SetUtilization("baz", 1.0)
                        .Build();
    for (size_t i = 0; i < kNumRpcs; ++i) {
      CheckRpcSendOk(DEBUG_LOCATION, stub, false, &load_report);
      auto actual = backend_load_report();
      ASSERT_TRUE(actual.has_value());
      CheckLoadReportAsExpected(*actual, expected);
      ++total_num_rpcs;
    }
  }

  EXPECT_EQ("intercept_trailing_metadata_lb",
            channel->GetLoadBalancingPolicyName());
  EXPECT_EQ(total_num_rpcs, num_trailers_intercepted());
}

class ClientLbAddressTest : public ClientLbEnd2endTest {
 protected:
  void SetUp() override {
    ClientLbEnd2endTest::SetUp();
    current_test_instance_ = this;
  }

  static void SetUpTestSuite() {
    grpc_core::CoreConfiguration::Reset();
    grpc_core::CoreConfiguration::RegisterEphemeralBuilder(
        [](grpc_core::CoreConfiguration::Builder* builder) {
          grpc_core::RegisterAddressTestLoadBalancingPolicy(builder,
                                                            SaveAddress);
        });
    grpc_init();
  }

  static void TearDownTestSuite() {
    grpc_shutdown();
    grpc_core::CoreConfiguration::Reset();
  }

  std::vector<std::string> addresses_seen() {
    grpc_core::MutexLock lock(&mu_);
    return addresses_seen_;
  }

 private:
  static void SaveAddress(const grpc_core::EndpointAddresses& address) {
    ClientLbAddressTest* self = current_test_instance_;
    grpc_core::MutexLock lock(&self->mu_);
    self->addresses_seen_.emplace_back(address.ToString());
  }

  static ClientLbAddressTest* current_test_instance_;
  grpc_core::Mutex mu_;
  std::vector<std::string> addresses_seen_ ABSL_GUARDED_BY(&mu_);
};

ClientLbAddressTest* ClientLbAddressTest::current_test_instance_ = nullptr;

TEST_F(ClientLbAddressTest, Basic) {
  const int kNumServers = 1;
  StartServers(kNumServers);
  FakeResolverResponseGeneratorWrapper response_generator;
  auto channel = BuildChannel("address_test_lb", response_generator);
  auto stub = BuildStub(channel);

  response_generator.SetNextResolution(
      GetServersPorts(), nullptr,
      grpc_core::ChannelArgs().Set("test_key", "test_value"));
  CheckRpcSendOk(DEBUG_LOCATION, stub);

  EXPECT_EQ("address_test_lb", channel->GetLoadBalancingPolicyName());

  std::vector<std::string> expected;
  for (const int port : GetServersPorts()) {
    expected.emplace_back(absl::StrCat("addrs=[", grpc_core::LocalIp(), ":",
                                       port, "] args={test_key=test_value}"));
  }
  EXPECT_EQ(addresses_seen(), expected);
}

class OobBackendMetricTest : public ClientLbEnd2endTest {
 protected:
  using BackendMetricReport = std::pair<int , OrcaLoadReport>;

  void SetUp() override {
    ClientLbEnd2endTest::SetUp();
    current_test_instance_ = this;
  }

  static void SetUpTestSuite() {
    grpc_core::CoreConfiguration::Reset();
    grpc_core::CoreConfiguration::RegisterEphemeralBuilder(
        [](grpc_core::CoreConfiguration::Builder* builder) {
          grpc_core::RegisterOobBackendMetricTestLoadBalancingPolicy(
              builder, BackendMetricCallback);
        });
    grpc_init();
  }

  static void TearDownTestSuite() {
    grpc_shutdown();
    grpc_core::CoreConfiguration::Reset();
  }

  std::optional<BackendMetricReport> GetBackendMetricReport() {
    grpc_core::MutexLock lock(&mu_);
    if (backend_metric_reports_.empty()) return std::nullopt;
    auto result = std::move(backend_metric_reports_.front());
    backend_metric_reports_.pop_front();
    return result;
  }

 private:
  static void BackendMetricCallback(
      const grpc_core::EndpointAddresses& address,
      const grpc_core::BackendMetricData& backend_metric_data) {
    auto load_report = BackendMetricDataToOrcaLoadReport(backend_metric_data);
    int port = grpc_sockaddr_get_port(&address.address());
    grpc_core::MutexLock lock(&current_test_instance_->mu_);
    current_test_instance_->backend_metric_reports_.push_back(
        {port, std::move(load_report)});
  }

  static OobBackendMetricTest* current_test_instance_;
  grpc_core::Mutex mu_;
  std::deque<BackendMetricReport> backend_metric_reports_ ABSL_GUARDED_BY(&mu_);
};

OobBackendMetricTest* OobBackendMetricTest::current_test_instance_ = nullptr;

TEST_F(OobBackendMetricTest, Basic) {
  StartServers(1);

  constexpr char kMetricName[] = "foo";
  servers_[0]->server_metric_recorder_->SetApplicationUtilization(0.5);
  servers_[0]->server_metric_recorder_->SetCpuUtilization(0.1);
  servers_[0]->server_metric_recorder_->SetMemoryUtilization(0.2);
  servers_[0]->server_metric_recorder_->SetEps(0.3);
  servers_[0]->server_metric_recorder_->SetQps(0.4);
  servers_[0]->server_metric_recorder_->SetNamedUtilization(kMetricName, 0.4);

  FakeResolverResponseGeneratorWrapper response_generator;
  auto channel = BuildChannel("oob_backend_metric_test_lb", response_generator);
  auto stub = BuildStub(channel);
  response_generator.SetNextResolution(GetServersPorts());

  CheckRpcSendOk(DEBUG_LOCATION, stub);

  EXPECT_EQ("oob_backend_metric_test_lb",
            channel->GetLoadBalancingPolicyName());

  bool report_seen = false;
  for (size_t i = 0; i < 5; ++i) {
    auto report = GetBackendMetricReport();
    if (report.has_value()) {
      EXPECT_EQ(report->first, servers_[0]->port_);
      EXPECT_EQ(report->second.application_utilization(), 0.5);
      EXPECT_EQ(report->second.cpu_utilization(), 0.1);
      EXPECT_EQ(report->second.mem_utilization(), 0.2);
      EXPECT_EQ(report->second.eps(), 0.3);
      EXPECT_EQ(report->second.rps_fractional(), 0.4);
      EXPECT_THAT(
          report->second.utilization(),
          ::testing::UnorderedElementsAre(::testing::Pair(kMetricName, 0.4)));
      report_seen = true;
      break;
    }
    gpr_sleep_until(grpc_timeout_seconds_to_deadline(1));
  }
  ASSERT_TRUE(report_seen);

  servers_[0]->server_metric_recorder_->SetNamedUtilization(kMetricName, 0.7);
  servers_[0]->server_metric_recorder_->SetQps(0.8);
  servers_[0]->server_metric_recorder_->SetEps(0.6);
  servers_[0]->server_metric_recorder_->SetMemoryUtilization(0.5);
  servers_[0]->server_metric_recorder_->SetCpuUtilization(2.4);
  servers_[0]->server_metric_recorder_->SetApplicationUtilization(1.2);

  report_seen = false;
  for (size_t i = 0; i < 5; ++i) {
    auto report = GetBackendMetricReport();
    if (report.has_value()) {
      EXPECT_EQ(report->first, servers_[0]->port_);
      if (report->second.application_utilization() != 0.5) {
        EXPECT_EQ(report->second.application_utilization(), 1.2);
        EXPECT_EQ(report->second.cpu_utilization(), 2.4);
        EXPECT_EQ(report->second.mem_utilization(), 0.5);
        EXPECT_EQ(report->second.eps(), 0.6);
        EXPECT_EQ(report->second.rps_fractional(), 0.8);
        EXPECT_THAT(
            report->second.utilization(),
            ::testing::UnorderedElementsAre(::testing::Pair(kMetricName, 0.7)));
        report_seen = true;
        break;
      }
    }
    gpr_sleep_until(grpc_timeout_seconds_to_deadline(1));
  }
  ASSERT_TRUE(report_seen);
}

class ControlPlaneStatusRewritingTest : public ClientLbEnd2endTest {
 protected:
  static void SetUpTestSuite() {
    grpc_core::CoreConfiguration::Reset();
    grpc_core::CoreConfiguration::RegisterEphemeralBuilder(
        [](grpc_core::CoreConfiguration::Builder* builder) {
          grpc_core::RegisterFailLoadBalancingPolicy(
              builder, absl::AbortedError("nope"));
        });
    grpc_init();
  }

  static void TearDownTestSuite() {
    grpc_shutdown();
    grpc_core::CoreConfiguration::Reset();
  }
};

TEST_F(ControlPlaneStatusRewritingTest, RewritesFromLb) {

  FakeResolverResponseGeneratorWrapper response_generator;
  auto channel = BuildChannel("fail_lb", response_generator);
  auto stub = BuildStub(channel);
  response_generator.SetNextResolution(GetServersPorts());

  CheckRpcSendFailure(
      DEBUG_LOCATION, stub, StatusCode::INTERNAL,
      "Illegal status code from LB pick; original status: ABORTED: nope");
}

TEST_F(ControlPlaneStatusRewritingTest, RewritesFromResolver) {

  FakeResolverResponseGeneratorWrapper response_generator;
  auto channel = BuildChannel("pick_first", response_generator);
  auto stub = BuildStub(channel);
  grpc_core::Resolver::Result result;
  result.service_config = absl::AbortedError("nope");
  result.addresses.emplace();
  response_generator.SetResponse(std::move(result));

  CheckRpcSendFailure(
      DEBUG_LOCATION, stub, StatusCode::INTERNAL,
      "Illegal status code from resolver; original status: ABORTED: nope");
}

TEST_F(ControlPlaneStatusRewritingTest, RewritesFromConfigSelector) {
  class FailConfigSelector : public grpc_core::ConfigSelector {
   public:
    explicit FailConfigSelector(absl::Status status)
        : status_(std::move(status)) {}
    grpc_core::UniqueTypeName name() const override {
      static grpc_core::UniqueTypeName::Factory kFactory("FailConfigSelector");
      return kFactory.Create();
    }
    bool Equals(const ConfigSelector* other) const override {
      return status_ == static_cast<const FailConfigSelector*>(other)->status_;
    }
    absl::Status GetCallConfig(GetCallConfigArgs ) override {
      return status_;
    }

   private:
    absl::Status status_;
  };

  FakeResolverResponseGeneratorWrapper response_generator;
  auto channel = BuildChannel("pick_first", response_generator);
  auto stub = BuildStub(channel);
  auto config_selector =
      grpc_core::MakeRefCounted<FailConfigSelector>(absl::AbortedError("nope"));
  grpc_core::Resolver::Result result;
  result.addresses.emplace();
  result.service_config =
      grpc_core::ServiceConfigImpl::Create(grpc_core::ChannelArgs(), "{}");
  ASSERT_TRUE(result.service_config.ok()) << result.service_config.status();
  result.args = grpc_core::ChannelArgs().SetObject(config_selector);
  response_generator.SetResponse(std::move(result));

  CheckRpcSendFailure(
      DEBUG_LOCATION, stub, StatusCode::INTERNAL,
      "Illegal status code from ConfigSelector; original status: "
      "ABORTED: nope");
}

const char kServiceConfigPerCall[] =
    "{\n"
    "  \"loadBalancingConfig\": [\n"
    "    {\"weighted_round_robin\": {\n"
    "      \"blackoutPeriod\": \"0s\",\n"
    "      \"weightUpdatePeriod\": \"0.1s\"\n"
    "    }}\n"
    "  ]\n"
    "}";

const char kServiceConfigOob[] =
    "{\n"
    "  \"loadBalancingConfig\": [\n"
    "    {\"weighted_round_robin\": {\n"
    "      \"blackoutPeriod\": \"0s\",\n"
    "      \"weightUpdatePeriod\": \"0.1s\",\n"
    "      \"enableOobLoadReport\": true\n"
    "    }}\n"
    "  ]\n"
    "}";

const char kServiceConfigWithOutlierDetection[] =
    "{\n"
    "  \"loadBalancingConfig\": [\n"
    "    {\"outlier_detection_experimental\": {\n"
    "      \"childPolicy\": [\n"
    "        {\"weighted_round_robin\": {\n"
    "          \"blackoutPeriod\": \"%ds\",\n"
    "          \"weightUpdatePeriod\": \"0.1s\"\n"
    "        }}\n"
    "      ]\n"
    "    }}\n"
    "  ]\n"
    "}";

class WeightedRoundRobinTest : public ClientLbEnd2endTest {
 protected:
  void ExpectWeightedRoundRobinPicks(
      const grpc_core::DebugLocation& location,
      const std::unique_ptr<grpc::testing::EchoTestService::Stub>& stub,
      const std::vector<size_t>& expected_weights, size_t total_passes = 3,
      EchoRequest* request_ptr = nullptr, int timeout_ms = 15000) {
    CHECK_EQ(expected_weights.size(), servers_.size());
    size_t total_picks_per_pass = 0;
    for (size_t picks : expected_weights) {
      total_picks_per_pass += picks;
    }
    size_t num_picks = 0;
    size_t num_passes = 0;
    SendRpcsUntil(
        location, stub,
        [&](const Status&) {
          if (++num_picks == total_picks_per_pass) {
            bool match = true;
            for (size_t i = 0; i < expected_weights.size(); ++i) {
              if (servers_[i]->service_.request_count() !=
                  expected_weights[i]) {
                match = false;
                break;
              }
            }
            if (match) {
              if (++num_passes == total_passes) return false;
            } else {
              num_passes = 0;
            }
            num_picks = 0;
            ResetCounters();
          }
          return true;
        },
        request_ptr, timeout_ms);
  }
};

TEST_F(WeightedRoundRobinTest, CallAndServerMetric) {
  const int kNumServers = 3;
  StartServers(kNumServers);

  servers_[0]->server_metric_recorder_->SetApplicationUtilization(0.2);
  servers_[0]->server_metric_recorder_->SetEps(20);
  servers_[0]->server_metric_recorder_->SetQps(100);
  servers_[1]->server_metric_recorder_->SetApplicationUtilization(0.3);
  servers_[1]->server_metric_recorder_->SetEps(30);
  servers_[1]->server_metric_recorder_->SetQps(100);
  servers_[2]->server_metric_recorder_->SetApplicationUtilization(1.5);
  servers_[2]->server_metric_recorder_->SetEps(20);
  servers_[2]->server_metric_recorder_->SetQps(200);

  FakeResolverResponseGeneratorWrapper response_generator;
  auto channel = BuildChannel("", response_generator);
  auto stub = BuildStub(channel);
  response_generator.SetNextResolution(GetServersPorts(),
                                       kServiceConfigPerCall);

  EchoRequest request;

  request.mutable_param()->mutable_backend_metrics()->set_eps(
      std::numeric_limits<double>::min());
  request.mutable_param()->mutable_backend_metrics()->set_rps_fractional(100);
  ExpectWeightedRoundRobinPicks(DEBUG_LOCATION, stub,
                                {15, 10, 2},
                                3, &request);

  ExpectWeightedRoundRobinPicks(DEBUG_LOCATION, stub,
                                {6, 4, 3});

  EXPECT_EQ("weighted_round_robin", channel->GetLoadBalancingPolicyName());
}

TEST_F(WeightedRoundRobinTest, WithOutlierDetection) {
  const int kBlackoutPeriodSeconds = 10;
  const int kNumServers = 3;
  StartServers(kNumServers);

  servers_[0]->server_metric_recorder_->SetApplicationUtilization(0.2);
  servers_[0]->server_metric_recorder_->SetEps(20);
  servers_[0]->server_metric_recorder_->SetQps(100);
  servers_[1]->server_metric_recorder_->SetApplicationUtilization(0.3);
  servers_[1]->server_metric_recorder_->SetEps(30);
  servers_[1]->server_metric_recorder_->SetQps(100);
  servers_[2]->server_metric_recorder_->SetApplicationUtilization(1.5);
  servers_[2]->server_metric_recorder_->SetEps(20);
  servers_[2]->server_metric_recorder_->SetQps(200);

  FakeResolverResponseGeneratorWrapper response_generator;
  auto channel = BuildChannel("", response_generator);
  auto stub = BuildStub(channel);
  response_generator.SetNextResolution(
      GetServersPorts(),
      absl::StrFormat(kServiceConfigWithOutlierDetection, 0).c_str());

  absl::Time deadline =
      absl::Now() +
      absl::Seconds(kBlackoutPeriodSeconds * grpc_test_slowdown_factor());
  EchoRequest request;

  request.mutable_param()->mutable_backend_metrics()->set_eps(
      std::numeric_limits<double>::min());
  request.mutable_param()->mutable_backend_metrics()->set_rps_fractional(100);
  do {
    ExpectWeightedRoundRobinPicks(DEBUG_LOCATION, stub,
                                  {15, 10, 2},
                                  3, &request);
  } while (absl::Now() < deadline);

  response_generator.SetNextResolution(
      GetServersPorts(),
      absl::StrFormat(kServiceConfigWithOutlierDetection,
                      kBlackoutPeriodSeconds * grpc_test_slowdown_factor())
          .c_str());

  ExpectWeightedRoundRobinPicks(
      DEBUG_LOCATION, stub, {15, 10, 2},
      3, &request,
      (kBlackoutPeriodSeconds - 1) * 1000);
}

class WeightedRoundRobinParamTest
    : public WeightedRoundRobinTest,
      public ::testing::WithParamInterface<const char*> {};

INSTANTIATE_TEST_SUITE_P(WeightedRoundRobin, WeightedRoundRobinParamTest,
                         ::testing::Values(kServiceConfigPerCall,
                                           kServiceConfigOob));

TEST_P(WeightedRoundRobinParamTest, Basic) {
  const int kNumServers = 3;
  StartServers(kNumServers);

  servers_[0]->server_metric_recorder_->SetApplicationUtilization(0.4);
  servers_[0]->server_metric_recorder_->SetEps(40);
  servers_[0]->server_metric_recorder_->SetQps(100);
  servers_[1]->server_metric_recorder_->SetApplicationUtilization(0.2);
  servers_[1]->server_metric_recorder_->SetEps(20);
  servers_[1]->server_metric_recorder_->SetQps(100);
  servers_[2]->server_metric_recorder_->SetApplicationUtilization(0.3);
  servers_[2]->server_metric_recorder_->SetEps(5);
  servers_[2]->server_metric_recorder_->SetQps(200);

  FakeResolverResponseGeneratorWrapper response_generator;
  auto channel = BuildChannel("", response_generator);
  auto stub = BuildStub(channel);
  response_generator.SetNextResolution(GetServersPorts(), GetParam());

  ExpectWeightedRoundRobinPicks(DEBUG_LOCATION, stub,
                                {1, 2, 4});

  EXPECT_EQ("weighted_round_robin", channel->GetLoadBalancingPolicyName());
}

}
}
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  grpc::testing::TestEnvironment env(&argc, argv);

  grpc_core::ConfigVars::Overrides overrides;
  overrides.client_channel_backup_poll_interval_ms = 1;
  grpc_core::ConfigVars::SetOverrides(overrides);
#if TARGET_OS_IPHONE

  grpc_core::SetEnv("grpc_cfstream", "0");
#endif
  grpc_init();
  grpc::testing::ConnectionAttemptInjector::Init();
  const auto result = RUN_ALL_TESTS();
  grpc_shutdown();
  return result;
}
