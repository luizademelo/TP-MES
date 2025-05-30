
// Copyright 2020 gRPC authors.

// FIXME: add tests:

#include <grpc/credentials.h>
#include <grpcpp/channel.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/support/channel_arguments.h>

#include <deque>
#include <map>
#include <optional>
#include <thread>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/strings/str_format.h"
#include "absl/strings/str_join.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "src/core/client_channel/backup_poller.h"
#include "src/core/config/config_vars.h"
#include "src/core/credentials/transport/fake/fake_credentials.h"
#include "src/core/lib/address_utils/parse_address.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/iomgr/sockaddr.h"
#include "src/core/load_balancing/rls/rls.h"
#include "src/core/resolver/fake/fake_resolver.h"
#include "src/core/service_config/service_config_impl.h"
#include "src/core/util/env.h"
#include "src/core/util/host_port.h"
#include "src/core/util/time.h"
#include "src/core/util/uri.h"
#include "src/core/util/wait_for_single_owner.h"
#include "src/cpp/server/secure_server_credentials.h"
#include "src/proto/grpc/lookup/v1/rls.grpc.pb.h"
#include "src/proto/grpc/lookup/v1/rls.pb.h"
#include "src/proto/grpc/testing/echo.grpc.pb.h"
#include "test/core/event_engine/event_engine_test_utils.h"
#include "test/core/test_util/fake_stats_plugin.h"
#include "test/core/test_util/port.h"
#include "test/core/test_util/resolve_localhost_ip46.h"
#include "test/core/test_util/test_call_creds.h"
#include "test/core/test_util/test_config.h"
#include "test/core/test_util/test_lb_policies.h"
#include "test/cpp/end2end/counted_service.h"
#include "test/cpp/end2end/rls_server.h"
#include "test/cpp/end2end/test_service_impl.h"
#include "test/cpp/util/credentials.h"
#include "test/cpp/util/test_config.h"

using ::grpc::lookup::v1::RouteLookupRequest;

namespace grpc {
namespace testing {
namespace {

const char* kServerName = "test.google.fr";
const char* kRequestMessage = "Live long and prosper.";
const char* kRlsInstanceUuid = "rls_instance_uuid";

const char* kCallCredsMdKey = "call_cred_name";
const char* kCallCredsMdValue = "call_cred_value";

const char* kTestKey = "test_key";
const char* kTestValue = "test_value";
const char* kHostKey = "host_key";
const char* kServiceKey = "service_key";
const char* kServiceValue = "grpc.testing.EchoTestService";
const char* kMethodKey = "method_key";
const char* kMethodValue = "Echo";
const char* kConstantKey = "constant_key";
const char* kConstantValue = "constant_value";

using BackendService = CountedService<TestServiceImpl>;

class MyTestServiceImpl : public BackendService {
 public:
  Status Echo(ServerContext* context, const EchoRequest* request,
              EchoResponse* response) override {

    EXPECT_THAT(context->client_metadata(),
                ::testing::Contains(
                    ::testing::Pair(kCallCredsMdKey, kCallCredsMdValue)));
    IncreaseRequestCount();
    auto client_metadata = context->client_metadata();
    auto [start, end] = client_metadata.equal_range("x-google-rls-data");
    {
      grpc::internal::MutexLock lock(&mu_);
      for (auto it = start; it != end; ++it) {
        auto& [_, value] = *it;
        rls_header_data_.emplace(value.begin(), value.length());
      }
    }
    IncreaseResponseCount();
    return TestServiceImpl::Echo(context, request, response);
  }

  std::set<std::string> rls_data() {
    grpc::internal::MutexLock lock(&mu_);
    return std::move(rls_header_data_);
  }

  void Start() {}

  void Shutdown() {}

 private:
  grpc::internal::Mutex mu_;
  std::set<std::string> rls_header_data_ ABSL_GUARDED_BY(&mu_);
};

class FakeResolverResponseGeneratorWrapper {
 public:
  FakeResolverResponseGeneratorWrapper()
      : response_generator_(grpc_core::MakeRefCounted<
                            grpc_core::FakeResolverResponseGenerator>()) {}

  void SetNextResolution(absl::string_view service_config_json) {
    grpc_core::ExecCtx exec_ctx;
    response_generator_->SetResponseSynchronously(
        BuildFakeResults(service_config_json));
  }

  grpc_core::FakeResolverResponseGenerator* Get() const {
    return response_generator_.get();
  }

 private:
  static grpc_core::Resolver::Result BuildFakeResults(
      absl::string_view service_config_json) {
    grpc_core::Resolver::Result result;
    result.service_config =
        grpc_core::ServiceConfigImpl::Create(result.args, service_config_json);
    EXPECT_TRUE(result.service_config.ok()) << result.service_config.status();
    return result;
  }

  grpc_core::RefCountedPtr<grpc_core::FakeResolverResponseGenerator>
      response_generator_;
};

class RlsEnd2endTest : public ::testing::Test {
 protected:
  static void SetUpTestSuite() {
    grpc_core::ConfigVars::Overrides overrides;
    overrides.client_channel_backup_poll_interval_ms = 1;
    grpc_core::ConfigVars::SetOverrides(overrides);
    grpc_core::CoreConfiguration::RegisterEphemeralBuilder(
        grpc_core::RegisterFixedAddressLoadBalancingPolicy);
    grpc_init();
  }

  static void TearDownTestSuite() {
    grpc_shutdown_blocking();
    grpc_core::WaitForSingleOwner(
        grpc_event_engine::experimental::GetDefaultEventEngine());
    grpc_core::CoreConfiguration::Reset();
  }

  void SetUp() override {
    rls_server_ = std::make_unique<ServerThread<RlsServiceImpl>>(
        "rls", [](grpc::ServerContext* ctx) {
          EXPECT_THAT(ctx->client_metadata(),
                      ::testing::Contains(
                          ::testing::Pair(kCallCredsMdKey, kCallCredsMdValue)));
          EXPECT_EQ(ctx->ExperimentalGetAuthority(), kServerName);
        });
    rls_server_->Start();
    rls_server_target_ = absl::StrFormat("localhost:%d", rls_server_->port_);

    resolver_response_generator_ =
        std::make_unique<FakeResolverResponseGeneratorWrapper>();
    ChannelArguments args;
    args.SetPointer(GRPC_ARG_FAKE_RESOLVER_RESPONSE_GENERATOR,
                    resolver_response_generator_->Get());
    args.SetString(GRPC_ARG_FAKE_SECURITY_EXPECTED_TARGETS, kServerName);
    args.SetString(GRPC_ARG_TEST_ONLY_RLS_INSTANCE_ID, kRlsInstanceUuid);
    grpc_channel_credentials* channel_creds =
        grpc_fake_transport_security_credentials_create();
    grpc_call_credentials* call_creds = grpc_md_only_test_credentials_create(
        kCallCredsMdKey, kCallCredsMdValue);
    auto creds = std::make_shared<TestCompositeChannelCredentials>(
        channel_creds, call_creds);
    call_creds->Unref();
    channel_creds->Unref();
    target_uri_ = absl::StrCat("fake:///", kServerName);
    channel_ = grpc::CreateCustomChannel(target_uri_, creds, args);
    stub_ = grpc::testing::EchoTestService::NewStub(channel_);
  }

  void TearDown() override {
    ShutdownBackends();
    rls_server_->Shutdown();
  }

  void ShutdownBackends() {
    for (auto& server : backends_) {
      server->Shutdown();
    }
  }

  void StartBackends(size_t num_servers) {
    backends_.clear();
    for (size_t i = 0; i < num_servers; ++i) {
      backends_.push_back(
          std::make_unique<ServerThread<MyTestServiceImpl>>("backend"));
      backends_.back()->Start();
    }
  }

  struct RpcOptions {
    int timeout_ms = 5000;
    bool wait_for_ready = false;
    std::vector<std::pair<std::string, std::string>> metadata;

    RpcOptions() {}

    RpcOptions& set_timeout_ms(int rpc_timeout_ms) {
      timeout_ms = rpc_timeout_ms;
      return *this;
    }

    RpcOptions& set_wait_for_ready(bool rpc_wait_for_ready) {
      wait_for_ready = rpc_wait_for_ready;
      return *this;
    }

    RpcOptions& set_metadata(
        std::vector<std::pair<std::string, std::string>> rpc_metadata) {
      metadata = std::move(rpc_metadata);
      return *this;
    }

    void SetupRpc(ClientContext* context) const {
      for (const auto& [key, value] : metadata) {
        context->AddMetadata(key, value);
      }
      if (timeout_ms != 0) {
        context->set_deadline(
            grpc_timeout_milliseconds_to_deadline(timeout_ms));
      }
      if (wait_for_ready) context->set_wait_for_ready(true);
    }
  };

  Status SendRpc(const RpcOptions& rpc_options = RpcOptions(),
                 EchoResponse* response = nullptr) {
    EchoResponse local_response;
    if (response == nullptr) response = &local_response;
    ClientContext context;
    rpc_options.SetupRpc(&context);
    EchoRequest request;
    request.set_message(kRequestMessage);
    return stub_->Echo(&context, request, response);
  }

  void CheckRpcSendOk(const grpc_core::DebugLocation& location,
                      const RpcOptions& rpc_options = RpcOptions()) {
    EchoResponse response;
    Status status = SendRpc(rpc_options, &response);
    ASSERT_TRUE(status.ok()) << location.file() << ":" << location.line()
                             << ": RPC failed: " << status.error_code() << ": "
                             << status.error_message();
    EXPECT_EQ(response.message(), kRequestMessage)
        << location.file() << ":" << location.line();
  }

  void CheckRpcSendFailure(const grpc_core::DebugLocation& location,
                           StatusCode expected_code,
                           absl::string_view expected_message,
                           const RpcOptions& rpc_options = RpcOptions()) {
    Status status = SendRpc(rpc_options);
    ASSERT_FALSE(status.ok()) << location.file() << ":" << location.line();
    EXPECT_EQ(expected_code, status.error_code())
        << location.file() << ":" << location.line();
    EXPECT_EQ(expected_message, status.error_message())
        << location.file() << ":" << location.line();
  }

  class ServiceConfigBuilder {
   public:
    explicit ServiceConfigBuilder(absl::string_view rls_server_target)
        : rls_server_target_(rls_server_target) {}

    ServiceConfigBuilder& set_lookup_service_timeout(
        grpc_core::Duration timeout) {
      lookup_service_timeout_ = timeout * grpc_test_slowdown_factor();
      return *this;
    }

    ServiceConfigBuilder& set_default_target(std::string default_target) {
      default_target_ = std::move(default_target);
      return *this;
    }

    ServiceConfigBuilder& set_max_age(grpc_core::Duration max_age) {
      max_age_ = max_age * grpc_test_slowdown_factor();
      return *this;
    }

    ServiceConfigBuilder& set_stale_age(grpc_core::Duration stale_age) {
      stale_age_ = stale_age * grpc_test_slowdown_factor();
      return *this;
    }

    ServiceConfigBuilder& set_cache_size_bytes(int64_t size) {
      cache_size_bytes_ = size;
      return *this;
    }

    ServiceConfigBuilder& AddKeyBuilder(absl::string_view key_builder) {
      key_builders_.push_back(absl::StrCat("{", key_builder, "}"));
      return *this;
    }

    std::string Build() {

      std::vector<std::string> route_lookup_config_parts;
      route_lookup_config_parts.push_back(absl::StrFormat(
          "        \"lookupService\":\"%s\"", rls_server_target_));
      if (lookup_service_timeout_ > grpc_core::Duration::Zero()) {
        route_lookup_config_parts.push_back(
            absl::StrFormat("        \"lookupServiceTimeout\":\"%fs\"",
                            lookup_service_timeout_.seconds()));
      }
      if (!default_target_.empty()) {
        route_lookup_config_parts.push_back(absl::StrFormat(
            "        \"defaultTarget\":\"%s\"", default_target_));
      }
      route_lookup_config_parts.push_back(absl::StrFormat(
          "        \"cacheSizeBytes\":%" PRId64, cache_size_bytes_));
      if (max_age_ > grpc_core::Duration::Zero()) {
        route_lookup_config_parts.push_back(
            absl::StrFormat("        \"maxAge\":\"%fs\"", max_age_.seconds()));
      }
      if (stale_age_ > grpc_core::Duration::Zero()) {
        route_lookup_config_parts.push_back(absl::StrFormat(
            "        \"staleAge\":\"%fs\"", stale_age_.seconds()));
      }
      if (!key_builders_.empty()) {
        route_lookup_config_parts.push_back(
            absl::StrFormat("        \"grpcKeybuilders\":[%s]",
                            absl::StrJoin(key_builders_, ",")));
      }

      std::vector<std::string> rls_config_parts;
      if (!route_lookup_config_parts.empty()) {
        rls_config_parts.push_back(absl::StrCat(
            "      \"routeLookupConfig\":{",
            absl::StrJoin(route_lookup_config_parts, ","), "      }"));
      }
      rls_config_parts.push_back(
          "      \"childPolicy\":[{"
          "        \"fixed_address_lb\":{}\n"
          "      }],\n"
          "      \"childPolicyConfigTargetFieldName\":\"address\"\n");

      return absl::StrCat(
          "{"
          "  \"loadBalancingConfig\":[{"
          "    \"rls_experimental\":{",
          absl::StrJoin(rls_config_parts, ","),
          "    }"
          "  }]"
          "}");
    }

   private:
    absl::string_view rls_server_target_;
    grpc_core::Duration lookup_service_timeout_;
    std::string default_target_;
    grpc_core::Duration max_age_;
    grpc_core::Duration stale_age_;
    int64_t cache_size_bytes_ = 10485760;
    std::vector<std::string> key_builders_;
  };

  ServiceConfigBuilder MakeServiceConfigBuilder() {
    return ServiceConfigBuilder(rls_server_target_);
  }

  void SetNextResolution(absl::string_view service_config_json) {
    resolver_response_generator_->SetNextResolution(service_config_json);
  }

  template <typename T>
  struct ServerThread {
    template <typename... Args>
    explicit ServerThread(const grpc::string& type, Args&&... args)
        : port_(grpc_pick_unused_port_or_die()),
          type_(type),
          service_(std::forward<Args>(args)...) {}

    void Start() {
      LOG(INFO) << "starting " << type_ << " server on port " << port_;
      CHECK(!running_);
      running_ = true;
      service_.Start();
      grpc::internal::Mutex mu;

      grpc::internal::MutexLock lock(&mu);
      grpc::internal::CondVar cond;
      thread_ = std::make_unique<std::thread>(
          std::bind(&ServerThread::Serve, this, &mu, &cond));
      cond.Wait(&mu);
      LOG(INFO) << type_ << " server startup complete";
    }

    void Serve(grpc::internal::Mutex* mu, grpc::internal::CondVar* cond) {

      grpc::internal::MutexLock lock(mu);
      ServerBuilder builder;
      auto creds = std::make_shared<SecureServerCredentials>(
          grpc_fake_transport_security_server_credentials_create());
      builder.AddListeningPort(absl::StrCat("localhost:", port_),
                               std::move(creds));
      builder.RegisterService(&service_);
      server_ = builder.BuildAndStart();
      cond->Signal();
    }

    void Shutdown() {
      if (!running_) return;
      LOG(INFO) << type_ << " about to shutdown";
      service_.Shutdown();
      server_->Shutdown(grpc_timeout_milliseconds_to_deadline(0));
      thread_->join();
      LOG(INFO) << type_ << " shutdown completed";
      running_ = false;
    }

    const int port_;
    grpc::string type_;
    T service_;
    std::unique_ptr<Server> server_;
    std::unique_ptr<std::thread> thread_;
    bool running_ = false;
  };

  std::vector<std::unique_ptr<ServerThread<MyTestServiceImpl>>> backends_;
  std::string rls_server_target_;
  std::unique_ptr<ServerThread<RlsServiceImpl>> rls_server_;
  std::unique_ptr<FakeResolverResponseGeneratorWrapper>
      resolver_response_generator_;
  std::string target_uri_;
  std::shared_ptr<grpc::Channel> channel_;
  std::unique_ptr<grpc::testing::EchoTestService::Stub> stub_;
};

TEST_F(RlsEnd2endTest, Basic) {
  StartBackends(1);
  SetNextResolution(
      MakeServiceConfigBuilder()
          .AddKeyBuilder(absl::StrFormat("\"names\":[{"
                                         "  \"service\":\"%s\","
                                         "  \"method\":\"%s\""
                                         "}],"
                                         "\"headers\":["
                                         "  {"
                                         "    \"key\":\"%s\","
                                         "    \"names\":["
                                         "      \"key1\""
                                         "    ]"
                                         "  }"
                                         "]",
                                         kServiceValue, kMethodValue, kTestKey))
          .Build());
  rls_server_->service_.SetResponse(
      BuildRlsRequest({{kTestKey, kTestValue}}),
      BuildRlsResponse({grpc_core::LocalIpUri(backends_[0]->port_)}));
  CheckRpcSendOk(DEBUG_LOCATION,
                 RpcOptions().set_metadata({{"key1", kTestValue}}));
  EXPECT_EQ(rls_server_->service_.request_count(), 1);
  EXPECT_EQ(rls_server_->service_.response_count(), 1);
  EXPECT_EQ(backends_[0]->service_.request_count(), 1);

  EXPECT_THAT(backends_[0]->service_.rls_data(), ::testing::ElementsAre());
}

TEST_F(RlsEnd2endTest, DuplicateHeadersAreMerged) {
  const char* kTestValue2 = "test_value_2";
  StartBackends(1);
  SetNextResolution(
      MakeServiceConfigBuilder()
          .AddKeyBuilder(absl::StrFormat("\"names\":[{"
                                         "  \"service\":\"%s\","
                                         "  \"method\":\"%s\""
                                         "}],"
                                         "\"headers\":["
                                         "  {"
                                         "    \"key\":\"%s\","
                                         "    \"names\":["
                                         "      \"key1\""
                                         "    ]"
                                         "  }"
                                         "]",
                                         kServiceValue, kMethodValue, kTestKey))
          .Build());
  rls_server_->service_.SetResponse(
      BuildRlsRequest({{kTestKey, absl::StrCat(kTestValue, ",", kTestValue2)}}),
      BuildRlsResponse({grpc_core::LocalIpUri(backends_[0]->port_)}));

  CheckRpcSendOk(
      DEBUG_LOCATION,
      RpcOptions().set_metadata({{"key1", kTestValue}, {"key1", kTestValue2}}));
  EXPECT_EQ(rls_server_->service_.request_count(), 1);
  EXPECT_EQ(rls_server_->service_.response_count(), 1);
  EXPECT_EQ(backends_[0]->service_.request_count(), 1);
}

TEST_F(RlsEnd2endTest, SecondHeaderUsed) {
  StartBackends(1);
  SetNextResolution(
      MakeServiceConfigBuilder()
          .AddKeyBuilder(absl::StrFormat("\"names\":[{"
                                         "  \"service\":\"%s\","
                                         "  \"method\":\"%s\""
                                         "}],"
                                         "\"headers\":["
                                         "  {"
                                         "    \"key\":\"%s\","
                                         "    \"names\":["
                                         "      \"key1\", \"key2\""
                                         "    ]"
                                         "  }"
                                         "]",
                                         kServiceValue, kMethodValue, kTestKey))
          .Build());
  rls_server_->service_.SetResponse(
      BuildRlsRequest({{kTestKey, kTestValue}}),
      BuildRlsResponse({grpc_core::LocalIpUri(backends_[0]->port_)}));
  CheckRpcSendOk(DEBUG_LOCATION,
                 RpcOptions().set_metadata({{"key2", kTestValue}}));
  EXPECT_EQ(rls_server_->service_.request_count(), 1);
  EXPECT_EQ(rls_server_->service_.response_count(), 1);
  EXPECT_EQ(backends_[0]->service_.request_count(), 1);
}

TEST_F(RlsEnd2endTest, MultipleHeaderKeys) {
  const char* kTestKey2 = "test_key_2";
  const char* kTestValue2 = "test_value_2";
  StartBackends(1);
  SetNextResolution(MakeServiceConfigBuilder()
                        .AddKeyBuilder(absl::StrFormat(
                            "\"names\":[{"
                            "  \"service\":\"%s\","
                            "  \"method\":\"%s\""
                            "}],"
                            "\"headers\":["
                            "  {"
                            "    \"key\":\"%s\","
                            "    \"names\":["
                            "      \"key1\""
                            "    ]"
                            "  },"
                            "  {"
                            "    \"key\":\"%s\","
                            "    \"names\":["
                            "      \"key2\""
                            "    ]"
                            "  }"
                            "]",
                            kServiceValue, kMethodValue, kTestKey, kTestKey2))
                        .Build());
  rls_server_->service_.SetResponse(
      BuildRlsRequest({
          {kTestKey, kTestValue},
          {kTestKey2, kTestValue2},
      }),
      BuildRlsResponse({grpc_core::LocalIpUri(backends_[0]->port_)}));
  CheckRpcSendOk(
      DEBUG_LOCATION,
      RpcOptions().set_metadata({{"key1", kTestValue}, {"key2", kTestValue2}}));
  EXPECT_EQ(rls_server_->service_.request_count(), 1);
  EXPECT_EQ(rls_server_->service_.response_count(), 1);
  EXPECT_EQ(backends_[0]->service_.request_count(), 1);

  EXPECT_THAT(backends_[0]->service_.rls_data(), ::testing::ElementsAre());
}

TEST_F(RlsEnd2endTest, NoHeaderMatch) {
  StartBackends(1);
  SetNextResolution(
      MakeServiceConfigBuilder()
          .AddKeyBuilder(absl::StrFormat("\"names\":[{"
                                         "  \"service\":\"%s\","
                                         "  \"method\":\"%s\""
                                         "}],"
                                         "\"headers\":["
                                         "  {"
                                         "    \"key\":\"%s\","
                                         "    \"names\":["
                                         "      \"key1\""
                                         "    ]"
                                         "  }"
                                         "]",
                                         kServiceValue, kMethodValue, kTestKey))
          .Build());
  rls_server_->service_.SetResponse(
      BuildRlsRequest({}),
      BuildRlsResponse({grpc_core::LocalIpUri(backends_[0]->port_)}));

  CheckRpcSendOk(DEBUG_LOCATION);
  EXPECT_EQ(rls_server_->service_.request_count(), 1);
  EXPECT_EQ(rls_server_->service_.response_count(), 1);
  EXPECT_EQ(backends_[0]->service_.request_count(), 1);
}

TEST_F(RlsEnd2endTest, WildcardMethod) {
  StartBackends(1);
  SetNextResolution(MakeServiceConfigBuilder()
                        .AddKeyBuilder(absl::StrFormat("\"names\":[{"
                                                       "  \"service\":\"%s\""
                                                       "}],"
                                                       "\"headers\":["
                                                       "  {"
                                                       "    \"key\":\"%s\","
                                                       "    \"names\":["
                                                       "      \"key1\""
                                                       "    ]"
                                                       "  }"
                                                       "]",
                                                       kServiceValue, kTestKey))
                        .Build());
  rls_server_->service_.SetResponse(
      BuildRlsRequest({{kTestKey, kTestValue}}),
      BuildRlsResponse({grpc_core::LocalIpUri(backends_[0]->port_)}));
  CheckRpcSendOk(DEBUG_LOCATION,
                 RpcOptions().set_metadata({{"key1", kTestValue}}));
  EXPECT_EQ(rls_server_->service_.request_count(), 1);
  EXPECT_EQ(rls_server_->service_.response_count(), 1);
  EXPECT_EQ(backends_[0]->service_.request_count(), 1);
}

TEST_F(RlsEnd2endTest, NoKeyBuilderForMethod) {
  StartBackends(1);
  SetNextResolution(
      MakeServiceConfigBuilder()
          .AddKeyBuilder(absl::StrFormat("\"names\":[{"
                                         "  \"service\":\"%s\","
                                         "  \"method\":\"some_other_method\""
                                         "}],"
                                         "\"headers\":["
                                         "  {"
                                         "    \"key\":\"%s\","
                                         "    \"names\":["
                                         "      \"key1\""
                                         "    ]"
                                         "  }"
                                         "]",
                                         kServiceValue, kTestKey))
          .Build());
  rls_server_->service_.SetResponse(
      BuildRlsRequest({}),
      BuildRlsResponse({grpc_core::LocalIpUri(backends_[0]->port_)}));
  CheckRpcSendOk(DEBUG_LOCATION);
  EXPECT_EQ(rls_server_->service_.request_count(), 1);
  EXPECT_EQ(rls_server_->service_.response_count(), 1);
  EXPECT_EQ(backends_[0]->service_.request_count(), 1);
}

TEST_F(RlsEnd2endTest, HeaderData) {
  const char* kHeaderData = "header_data";
  StartBackends(1);
  SetNextResolution(
      MakeServiceConfigBuilder()
          .AddKeyBuilder(absl::StrFormat("\"names\":[{"
                                         "  \"service\":\"%s\","
                                         "  \"method\":\"%s\""
                                         "}],"
                                         "\"headers\":["
                                         "  {"
                                         "    \"key\":\"%s\","
                                         "    \"names\":["
                                         "      \"key1\""
                                         "    ]"
                                         "  }"
                                         "]",
                                         kServiceValue, kMethodValue, kTestKey))
          .Build());
  rls_server_->service_.SetResponse(
      BuildRlsRequest({{kTestKey, kTestValue}}),
      BuildRlsResponse({grpc_core::LocalIpUri(backends_[0]->port_)},
                       kHeaderData));
  CheckRpcSendOk(DEBUG_LOCATION,
                 RpcOptions().set_metadata({{"key1", kTestValue}}));
  EXPECT_EQ(rls_server_->service_.request_count(), 1);
  EXPECT_EQ(rls_server_->service_.response_count(), 1);
  EXPECT_EQ(backends_[0]->service_.request_count(), 1);
  EXPECT_THAT(backends_[0]->service_.rls_data(),
              ::testing::ElementsAre(kHeaderData));
}

TEST_F(RlsEnd2endTest, ExtraKeysAndConstantKeys) {
  StartBackends(1);
  SetNextResolution(
      MakeServiceConfigBuilder()
          .AddKeyBuilder(absl::StrFormat("\"names\":[{"
                                         "  \"service\":\"%s\","
                                         "  \"method\":\"%s\""
                                         "}],"
                                         "\"headers\":["
                                         "  {"
                                         "    \"key\":\"%s\","
                                         "    \"names\":["
                                         "      \"key1\",\"key2\",\"key3\""
                                         "    ]"
                                         "  }"
                                         "],"
                                         "\"extraKeys\":{"
                                         "  \"host\":\"%s\","
                                         "  \"service\":\"%s\","
                                         "  \"method\":\"%s\""
                                         "},"
                                         "\"constantKeys\":{"
                                         "  \"%s\":\"%s\""
                                         "}",
                                         kServiceValue, kMethodValue, kTestKey,
                                         kHostKey, kServiceKey, kMethodKey,
                                         kConstantKey, kConstantValue))
          .Build());
  rls_server_->service_.SetResponse(
      BuildRlsRequest({
          {kTestKey, kTestValue},
          {kHostKey, kServerName},
          {kServiceKey, kServiceValue},
          {kMethodKey, kMethodValue},
          {kConstantKey, kConstantValue},
      }),
      BuildRlsResponse({grpc_core::LocalIpUri(backends_[0]->port_)}));
  CheckRpcSendOk(DEBUG_LOCATION,
                 RpcOptions().set_metadata({{"key1", kTestValue}}));
  EXPECT_EQ(rls_server_->service_.request_count(), 1);
  EXPECT_EQ(rls_server_->service_.response_count(), 1);
  EXPECT_EQ(backends_[0]->service_.request_count(), 1);
}

TEST_F(RlsEnd2endTest, TwoCacheEntriesWithSameTarget) {
  const char* kTestValue2 = "test_value2";
  StartBackends(1);
  SetNextResolution(
      MakeServiceConfigBuilder()
          .AddKeyBuilder(absl::StrFormat("\"names\":[{"
                                         "  \"service\":\"%s\","
                                         "  \"method\":\"%s\""
                                         "}],"
                                         "\"headers\":["
                                         "  {"
                                         "    \"key\":\"%s\","
                                         "    \"names\":["
                                         "      \"key1\""
                                         "    ]"
                                         "  }"
                                         "]",
                                         kServiceValue, kMethodValue, kTestKey))
          .Build());
  rls_server_->service_.SetResponse(
      BuildRlsRequest({{kTestKey, kTestValue}}),
      BuildRlsResponse({grpc_core::LocalIpUri(backends_[0]->port_)}));
  rls_server_->service_.SetResponse(
      BuildRlsRequest({{kTestKey, kTestValue2}}),
      BuildRlsResponse({grpc_core::LocalIpUri(backends_[0]->port_)}));
  CheckRpcSendOk(DEBUG_LOCATION,
                 RpcOptions().set_metadata({{"key1", kTestValue}}));
  EXPECT_EQ(rls_server_->service_.request_count(), 1);
  EXPECT_EQ(rls_server_->service_.response_count(), 1);
  EXPECT_EQ(backends_[0]->service_.request_count(), 1);
  CheckRpcSendOk(DEBUG_LOCATION,
                 RpcOptions().set_metadata({{"key1", kTestValue2}}));
  EXPECT_EQ(rls_server_->service_.request_count(), 2);
  EXPECT_EQ(rls_server_->service_.response_count(), 2);
  EXPECT_EQ(backends_[0]->service_.request_count(), 2);
}

TEST_F(RlsEnd2endTest, FailedRlsRequestWithoutDefaultTarget) {
  StartBackends(1);
  SetNextResolution(
      MakeServiceConfigBuilder()
          .AddKeyBuilder(absl::StrFormat("\"names\":[{"
                                         "  \"service\":\"%s\","
                                         "  \"method\":\"%s\""
                                         "}],"
                                         "\"headers\":["
                                         "  {"
                                         "    \"key\":\"%s\","
                                         "    \"names\":["
                                         "      \"key1\""
                                         "    ]"
                                         "  }"
                                         "]",
                                         kServiceValue, kMethodValue, kTestKey))
          .Build());

  const char* kTestValue2 = "test_value_2";
  const char* kTestValue3 = "test_value_3";
  rls_server_->service_.SetResponse(
      BuildRlsRequest({{kTestKey, kTestValue2}}),
      BuildRlsResponse({grpc_core::LocalIpUri(backends_[0]->port_)}));
  rls_server_->service_.SetResponse(
      BuildRlsRequest({{kTestKey, kTestValue3}}),
      BuildRlsResponse({grpc_core::LocalIpUri(backends_[0]->port_)}));
  CheckRpcSendOk(DEBUG_LOCATION,
                 RpcOptions().set_metadata({{"key1", kTestValue2}}));
  CheckRpcSendOk(DEBUG_LOCATION,
                 RpcOptions().set_metadata({{"key1", kTestValue3}}));

  CheckRpcSendFailure(DEBUG_LOCATION, StatusCode::UNAVAILABLE,
                      "RLS request failed: INTERNAL: no response entry",
                      RpcOptions().set_metadata({{"key1", kTestValue}}));
  EXPECT_THAT(
      rls_server_->service_.GetUnmatchedRequests(),
      ::testing::ElementsAre(

          ::testing::Property(
              &RouteLookupRequest::DebugString,
              BuildRlsRequest({{kTestKey, kTestValue}}).DebugString())));

  rls_server_->service_.SetResponse(
      BuildRlsRequest({{kTestKey, kTestValue}}),
      BuildRlsResponse({grpc_core::LocalIpUri(backends_[0]->port_)}));

  gpr_sleep_until(grpc_timeout_seconds_to_deadline(3));
  CheckRpcSendOk(DEBUG_LOCATION,
                 RpcOptions().set_metadata({{"key1", kTestValue}}));
  EXPECT_EQ(rls_server_->service_.request_count(), 4);
  EXPECT_EQ(rls_server_->service_.response_count(), 3);
  EXPECT_EQ(backends_[0]->service_.request_count(), 3);
}

TEST_F(RlsEnd2endTest, FailedRlsRequestWithDefaultTarget) {
  StartBackends(1);
  SetNextResolution(
      MakeServiceConfigBuilder()
          .AddKeyBuilder(absl::StrFormat("\"names\":[{"
                                         "  \"service\":\"%s\","
                                         "  \"method\":\"%s\""
                                         "}],"
                                         "\"headers\":["
                                         "  {"
                                         "    \"key\":\"%s\","
                                         "    \"names\":["
                                         "      \"key1\""
                                         "    ]"
                                         "  }"
                                         "]",
                                         kServiceValue, kMethodValue, kTestKey))
          .set_default_target(grpc_core::LocalIpUri(backends_[0]->port_))
          .Build());

  CheckRpcSendOk(DEBUG_LOCATION,
                 RpcOptions().set_metadata({{"key1", kTestValue}}));
  EXPECT_THAT(
      rls_server_->service_.GetUnmatchedRequests(),
      ::testing::ElementsAre(

          ::testing::Property(
              &RouteLookupRequest::DebugString,
              BuildRlsRequest({{kTestKey, kTestValue}}).DebugString())));
  EXPECT_EQ(rls_server_->service_.request_count(), 1);
  EXPECT_EQ(rls_server_->service_.response_count(), 0);
  EXPECT_EQ(backends_[0]->service_.request_count(), 1);
}

TEST_F(RlsEnd2endTest, RlsRequestTimeout) {
  StartBackends(2);
  SetNextResolution(
      MakeServiceConfigBuilder()
          .AddKeyBuilder(absl::StrFormat("\"names\":[{"
                                         "  \"service\":\"%s\","
                                         "  \"method\":\"%s\""
                                         "}],"
                                         "\"headers\":["
                                         "  {"
                                         "    \"key\":\"%s\","
                                         "    \"names\":["
                                         "      \"key1\""
                                         "    ]"
                                         "  }"
                                         "]",
                                         kServiceValue, kMethodValue, kTestKey))
          .set_default_target(grpc_core::LocalIpUri(backends_[1]->port_))
          .set_lookup_service_timeout(grpc_core::Duration::Seconds(2))
          .Build());

  rls_server_->service_.SetResponse(
      BuildRlsRequest({{kTestKey, kTestValue}}),
      BuildRlsResponse({grpc_core::LocalIpUri(backends_[0]->port_)}),
      grpc_core::Duration::Seconds(3));

  CheckRpcSendOk(DEBUG_LOCATION,
                 RpcOptions().set_metadata({{"key1", kTestValue}}));
  EXPECT_EQ(rls_server_->service_.request_count(), 1);
  EXPECT_EQ(backends_[0]->service_.request_count(), 0);
  EXPECT_EQ(backends_[1]->service_.request_count(), 1);
}

TEST_F(RlsEnd2endTest, UpdateConfig) {
  StartBackends(2);
  auto service_config_builder =
      MakeServiceConfigBuilder()
          .AddKeyBuilder(absl::StrFormat("\"names\":[{"
                                         "  \"service\":\"%s\","
                                         "  \"method\":\"%s\""
                                         "}],"
                                         "\"headers\":["
                                         "  {"
                                         "    \"key\":\"%s\","
                                         "    \"names\":["
                                         "      \"key1\""
                                         "    ]"
                                         "  }"
                                         "]",
                                         kServiceValue, kMethodValue, kTestKey))
          .set_default_target(grpc_core::LocalIpUri(backends_[0]->port_));
  SetNextResolution(service_config_builder.Build());

  CheckRpcSendOk(DEBUG_LOCATION,
                 RpcOptions().set_metadata({{"key1", kTestValue}}));
  EXPECT_THAT(
      rls_server_->service_.GetUnmatchedRequests(),
      ::testing::ElementsAre(

          ::testing::Property(
              &RouteLookupRequest::DebugString,
              BuildRlsRequest({{kTestKey, kTestValue}}).DebugString())));
  EXPECT_EQ(rls_server_->service_.request_count(), 1);
  EXPECT_EQ(rls_server_->service_.response_count(), 0);
  EXPECT_EQ(backends_[0]->service_.request_count(), 1);
  EXPECT_EQ(backends_[1]->service_.request_count(), 0);

  service_config_builder.set_default_target(
      grpc_core::LocalIpUri(backends_[1]->port_));
  SetNextResolution(service_config_builder.Build());

  CheckRpcSendOk(DEBUG_LOCATION,
                 RpcOptions().set_metadata({{"key1", kTestValue}}));
  EXPECT_EQ(rls_server_->service_.request_count(), 1);
  EXPECT_EQ(rls_server_->service_.response_count(), 0);
  EXPECT_EQ(backends_[0]->service_.request_count(), 1);
  EXPECT_EQ(backends_[1]->service_.request_count(), 1);
}

TEST_F(RlsEnd2endTest, CachedResponse) {
  StartBackends(1);
  SetNextResolution(
      MakeServiceConfigBuilder()
          .AddKeyBuilder(absl::StrFormat("\"names\":[{"
                                         "  \"service\":\"%s\","
                                         "  \"method\":\"%s\""
                                         "}],"
                                         "\"headers\":["
                                         "  {"
                                         "    \"key\":\"%s\","
                                         "    \"names\":["
                                         "      \"key1\""
                                         "    ]"
                                         "  }"
                                         "]",
                                         kServiceValue, kMethodValue, kTestKey))
          .Build());
  rls_server_->service_.SetResponse(
      BuildRlsRequest({{kTestKey, kTestValue}}),
      BuildRlsResponse({grpc_core::LocalIpUri(backends_[0]->port_)}));

  CheckRpcSendOk(DEBUG_LOCATION,
                 RpcOptions().set_metadata({{"key1", kTestValue}}));
  CheckRpcSendOk(DEBUG_LOCATION,
                 RpcOptions().set_metadata({{"key1", kTestValue}}));

  EXPECT_EQ(rls_server_->service_.request_count(), 1);
  EXPECT_EQ(rls_server_->service_.response_count(), 1);
  EXPECT_EQ(backends_[0]->service_.request_count(), 2);
}

TEST_F(RlsEnd2endTest, StaleCacheEntry) {
  StartBackends(1);
  SetNextResolution(
      MakeServiceConfigBuilder()
          .AddKeyBuilder(absl::StrFormat("\"names\":[{"
                                         "  \"service\":\"%s\","
                                         "  \"method\":\"%s\""
                                         "}],"
                                         "\"headers\":["
                                         "  {"
                                         "    \"key\":\"%s\","
                                         "    \"names\":["
                                         "      \"key1\""
                                         "    ]"
                                         "  }"
                                         "]",
                                         kServiceValue, kMethodValue, kTestKey))
          .set_max_age(grpc_core::Duration::Seconds(5))
          .set_stale_age(grpc_core::Duration::Seconds(1))
          .Build());
  rls_server_->service_.SetResponse(
      BuildRlsRequest({{kTestKey, kTestValue}}),
      BuildRlsResponse({grpc_core::LocalIpUri(backends_[0]->port_)}));

  CheckRpcSendOk(DEBUG_LOCATION,
                 RpcOptions().set_metadata({{"key1", kTestValue}}));
  EXPECT_EQ(rls_server_->service_.request_count(), 1);
  EXPECT_EQ(rls_server_->service_.response_count(), 1);
  EXPECT_EQ(backends_[0]->service_.request_count(), 1);

  rls_server_->service_.RemoveResponse(
      BuildRlsRequest({{kTestKey, kTestValue}}));
  rls_server_->service_.SetResponse(
      BuildRlsRequest({{kTestKey, kTestValue}},
                      RouteLookupRequest::REASON_STALE),
      BuildRlsResponse({grpc_core::LocalIpUri(backends_[0]->port_)}));

  gpr_sleep_until(grpc_timeout_seconds_to_deadline(2));

  CheckRpcSendOk(DEBUG_LOCATION,
                 RpcOptions().set_metadata({{"key1", kTestValue}}));
  EXPECT_EQ(backends_[0]->service_.request_count(), 2);

  gpr_sleep_until(grpc_timeout_seconds_to_deadline(2));
  EXPECT_EQ(rls_server_->service_.request_count(), 2);
  EXPECT_EQ(rls_server_->service_.response_count(), 2);
}

TEST_F(RlsEnd2endTest, StaleCacheEntryWithHeaderData) {
  const char* kHeaderData = "header_data";
  StartBackends(1);
  SetNextResolution(
      MakeServiceConfigBuilder()
          .AddKeyBuilder(absl::StrFormat("\"names\":[{"
                                         "  \"service\":\"%s\","
                                         "  \"method\":\"%s\""
                                         "}],"
                                         "\"headers\":["
                                         "  {"
                                         "    \"key\":\"%s\","
                                         "    \"names\":["
                                         "      \"key1\""
                                         "    ]"
                                         "  }"
                                         "]",
                                         kServiceValue, kMethodValue, kTestKey))
          .set_max_age(grpc_core::Duration::Seconds(5))
          .set_stale_age(grpc_core::Duration::Seconds(1))
          .Build());
  rls_server_->service_.SetResponse(
      BuildRlsRequest({{kTestKey, kTestValue}}),
      BuildRlsResponse({grpc_core::LocalIpUri(backends_[0]->port_)},
                       kHeaderData));

  CheckRpcSendOk(DEBUG_LOCATION,
                 RpcOptions().set_metadata({{"key1", kTestValue}}));
  EXPECT_EQ(rls_server_->service_.request_count(), 1);
  EXPECT_EQ(rls_server_->service_.response_count(), 1);
  EXPECT_EQ(backends_[0]->service_.request_count(), 1);

  rls_server_->service_.RemoveResponse(
      BuildRlsRequest({{kTestKey, kTestValue}}));
  rls_server_->service_.SetResponse(
      BuildRlsRequest({{kTestKey, kTestValue}},
                      RouteLookupRequest::REASON_STALE, kHeaderData),
      BuildRlsResponse({grpc_core::LocalIpUri(backends_[0]->port_)},
                       kHeaderData));

  gpr_sleep_until(grpc_timeout_seconds_to_deadline(2));

  CheckRpcSendOk(DEBUG_LOCATION,
                 RpcOptions().set_metadata({{"key1", kTestValue}}));
  EXPECT_EQ(backends_[0]->service_.request_count(), 2);

  gpr_sleep_until(grpc_timeout_seconds_to_deadline(2));
  EXPECT_EQ(rls_server_->service_.request_count(), 2);
  EXPECT_EQ(rls_server_->service_.response_count(), 2);
}

TEST_F(RlsEnd2endTest, ExpiredCacheEntry) {
  StartBackends(1);
  SetNextResolution(
      MakeServiceConfigBuilder()
          .AddKeyBuilder(absl::StrFormat("\"names\":[{"
                                         "  \"service\":\"%s\","
                                         "  \"method\":\"%s\""
                                         "}],"
                                         "\"headers\":["
                                         "  {"
                                         "    \"key\":\"%s\","
                                         "    \"names\":["
                                         "      \"key1\""
                                         "    ]"
                                         "  }"
                                         "]",
                                         kServiceValue, kMethodValue, kTestKey))
          .set_max_age(grpc_core::Duration::Seconds(1))
          .set_lookup_service_timeout(grpc_core::Duration::Seconds(1))
          .Build());
  rls_server_->service_.SetResponse(
      BuildRlsRequest({{kTestKey, kTestValue}}),
      BuildRlsResponse({grpc_core::LocalIpUri(backends_[0]->port_)}));

  CheckRpcSendOk(DEBUG_LOCATION,
                 RpcOptions().set_metadata({{"key1", kTestValue}}));
  EXPECT_EQ(rls_server_->service_.request_count(), 1);
  EXPECT_EQ(rls_server_->service_.response_count(), 1);
  EXPECT_EQ(backends_[0]->service_.request_count(), 1);

  rls_server_->service_.RemoveResponse(
      BuildRlsRequest({{kTestKey, kTestValue}}));

  gpr_sleep_until(grpc_timeout_seconds_to_deadline(2));

  CheckRpcSendFailure(DEBUG_LOCATION, StatusCode::UNAVAILABLE,
                      "RLS request failed: INTERNAL: no response entry",
                      RpcOptions().set_metadata({{"key1", kTestValue}}));
  EXPECT_EQ(rls_server_->service_.request_count(), 2);
  EXPECT_EQ(rls_server_->service_.response_count(), 1);
  EXPECT_EQ(backends_[0]->service_.request_count(), 1);
}

TEST_F(RlsEnd2endTest, CacheSizeLimit) {
  const char* kTestValue2 = "test_value_2";
  StartBackends(2);
  SetNextResolution(
      MakeServiceConfigBuilder()
          .AddKeyBuilder(absl::StrFormat("\"names\":[{"
                                         "  \"service\":\"%s\","
                                         "  \"method\":\"%s\""
                                         "}],"
                                         "\"headers\":["
                                         "  {"
                                         "    \"key\":\"%s\","
                                         "    \"names\":["
                                         "      \"key1\""
                                         "    ]"
                                         "  }"
                                         "]",
                                         kServiceValue, kMethodValue,
                                         kTestKey))
          .set_cache_size_bytes(1)
          .Build());

  rls_server_->service_.SetResponse(
      BuildRlsRequest({{kTestKey, kTestValue}}),
      BuildRlsResponse({grpc_core::LocalIpUri(backends_[0]->port_)}));
  rls_server_->service_.SetResponse(
      BuildRlsRequest({{kTestKey, kTestValue2}}),
      BuildRlsResponse({grpc_core::LocalIpUri(backends_[1]->port_)}));

  CheckRpcSendOk(DEBUG_LOCATION,
                 RpcOptions().set_metadata({{"key1", kTestValue}}));
  EXPECT_EQ(rls_server_->service_.request_count(), 1);
  EXPECT_EQ(rls_server_->service_.response_count(), 1);
  EXPECT_EQ(backends_[0]->service_.request_count(), 1);
  EXPECT_EQ(backends_[1]->service_.request_count(), 0);

  CheckRpcSendOk(DEBUG_LOCATION,
                 RpcOptions().set_metadata({{"key1", kTestValue}}));
  EXPECT_EQ(rls_server_->service_.request_count(), 1);
  EXPECT_EQ(rls_server_->service_.response_count(), 1);
  EXPECT_EQ(backends_[0]->service_.request_count(), 2);
  EXPECT_EQ(backends_[1]->service_.request_count(), 0);

  gpr_sleep_until(grpc_timeout_seconds_to_deadline(6));

  CheckRpcSendOk(DEBUG_LOCATION,
                 RpcOptions().set_metadata({{"key1", kTestValue2}}));
  EXPECT_EQ(rls_server_->service_.request_count(), 2);
  EXPECT_EQ(rls_server_->service_.response_count(), 2);
  EXPECT_EQ(backends_[0]->service_.request_count(), 2);
  EXPECT_EQ(backends_[1]->service_.request_count(), 1);

  CheckRpcSendOk(DEBUG_LOCATION,
                 RpcOptions().set_metadata({{"key1", kTestValue}}));
  EXPECT_EQ(rls_server_->service_.request_count(), 3);
  EXPECT_EQ(rls_server_->service_.response_count(), 3);
  EXPECT_EQ(backends_[0]->service_.request_count(), 3);
  EXPECT_EQ(backends_[1]->service_.request_count(), 1);

  CheckRpcSendOk(DEBUG_LOCATION,
                 RpcOptions().set_metadata({{"key1", kTestValue2}}));
  EXPECT_EQ(rls_server_->service_.request_count(), 3);
  EXPECT_EQ(rls_server_->service_.response_count(), 3);
  EXPECT_EQ(backends_[0]->service_.request_count(), 3);
  EXPECT_EQ(backends_[1]->service_.request_count(), 2);
}

TEST_F(RlsEnd2endTest, MultipleTargets) {
  StartBackends(1);
  SetNextResolution(
      MakeServiceConfigBuilder()
          .AddKeyBuilder(absl::StrFormat("\"names\":[{"
                                         "  \"service\":\"%s\","
                                         "  \"method\":\"%s\""
                                         "}],"
                                         "\"headers\":["
                                         "  {"
                                         "    \"key\":\"%s\","
                                         "    \"names\":["
                                         "      \"key1\""
                                         "    ]"
                                         "  }"
                                         "]",
                                         kServiceValue, kMethodValue, kTestKey))
          .Build());
  rls_server_->service_.SetResponse(
      BuildRlsRequest({{kTestKey, kTestValue}}),
      BuildRlsResponse(

          {grpc_core::LocalIpUri(backends_[0]->port_), "invalid_target"}));
  CheckRpcSendOk(DEBUG_LOCATION,
                 RpcOptions().set_metadata({{"key1", kTestValue}}));
  EXPECT_EQ(rls_server_->service_.request_count(), 1);
  EXPECT_EQ(rls_server_->service_.response_count(), 1);
  EXPECT_EQ(backends_[0]->service_.request_count(), 1);
}

TEST_F(RlsEnd2endTest, MultipleTargetsFirstInTransientFailure) {
  StartBackends(1);
  SetNextResolution(
      MakeServiceConfigBuilder()
          .AddKeyBuilder(absl::StrFormat("\"names\":[{"
                                         "  \"service\":\"%s\","
                                         "  \"method\":\"%s\""
                                         "}],"
                                         "\"headers\":["
                                         "  {"
                                         "    \"key\":\"%s\","
                                         "    \"names\":["
                                         "      \"key1\""
                                         "    ]"
                                         "  }"
                                         "]",
                                         kServiceValue, kMethodValue, kTestKey))
          .Build());
  rls_server_->service_.SetResponse(
      BuildRlsRequest({{kTestKey, kTestValue}}),
      BuildRlsResponse(

          {"invalid_target", grpc_core::LocalIpUri(backends_[0]->port_)}));
  CheckRpcSendOk(DEBUG_LOCATION,
                 RpcOptions().set_metadata({{"key1", kTestValue}}));
  EXPECT_EQ(rls_server_->service_.request_count(), 1);
  EXPECT_EQ(rls_server_->service_.response_count(), 1);
  EXPECT_EQ(backends_[0]->service_.request_count(), 1);
}

TEST_F(RlsEnd2endTest, ConnectivityStateReady) {
  StartBackends(1);
  SetNextResolution(
      MakeServiceConfigBuilder()
          .AddKeyBuilder(absl::StrFormat("\"names\":[{"
                                         "  \"service\":\"%s\","
                                         "  \"method\":\"%s\""
                                         "}],"
                                         "\"headers\":["
                                         "  {"
                                         "    \"key\":\"%s\","
                                         "    \"names\":["
                                         "      \"key1\""
                                         "    ]"
                                         "  }"
                                         "]",
                                         kServiceValue, kMethodValue, kTestKey))
          .Build());
  EXPECT_EQ(GRPC_CHANNEL_IDLE, channel_->GetState(false));
  rls_server_->service_.SetResponse(
      BuildRlsRequest({{kTestKey, kTestValue}}),
      BuildRlsResponse(

          {"invalid_target", grpc_core::LocalIpUri(backends_[0]->port_)}));
  CheckRpcSendOk(DEBUG_LOCATION,
                 RpcOptions().set_metadata({{"key1", kTestValue}}));
  EXPECT_EQ(rls_server_->service_.request_count(), 1);
  EXPECT_EQ(rls_server_->service_.response_count(), 1);
  EXPECT_EQ(backends_[0]->service_.request_count(), 1);
  EXPECT_EQ(GRPC_CHANNEL_READY, channel_->GetState(false));
}

TEST_F(RlsEnd2endTest, ConnectivityStateIdle) {
  SetNextResolution(
      MakeServiceConfigBuilder()
          .AddKeyBuilder(absl::StrFormat("\"names\":[{"
                                         "  \"service\":\"%s\","
                                         "  \"method\":\"%s\""
                                         "}],"
                                         "\"headers\":["
                                         "  {"
                                         "    \"key\":\"%s\","
                                         "    \"names\":["
                                         "      \"key1\""
                                         "    ]"
                                         "  }"
                                         "]",
                                         kServiceValue, kMethodValue, kTestKey))
          .Build());
  EXPECT_EQ(GRPC_CHANNEL_IDLE, channel_->GetState(false));

  CheckRpcSendFailure(DEBUG_LOCATION, StatusCode::UNAVAILABLE,
                      "RLS request failed: INTERNAL: no response entry");

  EXPECT_EQ(GRPC_CHANNEL_IDLE, channel_->GetState(false));
}

TEST_F(RlsEnd2endTest, ConnectivityStateTransientFailure) {
  SetNextResolution(
      MakeServiceConfigBuilder()
          .AddKeyBuilder(absl::StrFormat("\"names\":[{"
                                         "  \"service\":\"%s\","
                                         "  \"method\":\"%s\""
                                         "}],"
                                         "\"headers\":["
                                         "  {"
                                         "    \"key\":\"%s\","
                                         "    \"names\":["
                                         "      \"key1\""
                                         "    ]"
                                         "  }"
                                         "]",
                                         kServiceValue, kMethodValue, kTestKey))
          .Build());
  EXPECT_EQ(GRPC_CHANNEL_IDLE, channel_->GetState(false));
  rls_server_->service_.SetResponse(BuildRlsRequest({{kTestKey, kTestValue}}),
                                    BuildRlsResponse({"invalid_target"}));
  CheckRpcSendFailure(
      DEBUG_LOCATION, StatusCode::UNAVAILABLE,
      "empty address list (no address in fixed_address_lb policy)",
      RpcOptions().set_metadata({{"key1", kTestValue}}));
  EXPECT_EQ(rls_server_->service_.request_count(), 1);
  EXPECT_EQ(rls_server_->service_.response_count(), 1);
  EXPECT_EQ(GRPC_CHANNEL_TRANSIENT_FAILURE,
            channel_->GetState(false));
}

class RlsMetricsEnd2endTest : public RlsEnd2endTest {
 protected:
  void SetUp() override {

    stats_plugin_ = grpc_core::FakeStatsPluginBuilder()
                        .UseDisabledByDefaultMetrics(true)
                        .BuildAndRegister();
    RlsEnd2endTest::SetUp();
  }

  std::shared_ptr<grpc_core::FakeStatsPlugin> stats_plugin_;
};

TEST_F(RlsMetricsEnd2endTest, MetricDefinitionDefaultTargetPicks) {
  const auto* descriptor =
      grpc_core::GlobalInstrumentsRegistryTestPeer::FindMetricDescriptorByName(
          "grpc.lb.rls.default_target_picks");
  ASSERT_NE(descriptor, nullptr);
  EXPECT_EQ(descriptor->value_type,
            grpc_core::GlobalInstrumentsRegistry::ValueType::kUInt64);
  EXPECT_EQ(descriptor->instrument_type,
            grpc_core::GlobalInstrumentsRegistry::InstrumentType::kCounter);
  EXPECT_EQ(descriptor->enable_by_default, false);
  EXPECT_EQ(descriptor->name, "grpc.lb.rls.default_target_picks");
  EXPECT_EQ(descriptor->unit, "{pick}");
  EXPECT_THAT(descriptor->label_keys,
              ::testing::ElementsAre("grpc.target", "grpc.lb.rls.server_target",
                                     "grpc.lb.rls.data_plane_target",
                                     "grpc.lb.pick_result"));
  EXPECT_THAT(descriptor->optional_label_keys, ::testing::ElementsAre());
}

TEST_F(RlsMetricsEnd2endTest, MetricDefinitionTargetPicks) {
  const auto* descriptor =
      grpc_core::GlobalInstrumentsRegistryTestPeer::FindMetricDescriptorByName(
          "grpc.lb.rls.target_picks");
  ASSERT_NE(descriptor, nullptr);
  EXPECT_EQ(descriptor->value_type,
            grpc_core::GlobalInstrumentsRegistry::ValueType::kUInt64);
  EXPECT_EQ(descriptor->instrument_type,
            grpc_core::GlobalInstrumentsRegistry::InstrumentType::kCounter);
  EXPECT_EQ(descriptor->enable_by_default, false);
  EXPECT_EQ(descriptor->name, "grpc.lb.rls.target_picks");
  EXPECT_EQ(descriptor->unit, "{pick}");
  EXPECT_THAT(descriptor->label_keys,
              ::testing::ElementsAre("grpc.target", "grpc.lb.rls.server_target",
                                     "grpc.lb.rls.data_plane_target",
                                     "grpc.lb.pick_result"));
  EXPECT_THAT(descriptor->optional_label_keys, ::testing::ElementsAre());
}

TEST_F(RlsMetricsEnd2endTest, MetricDefinitionFailedPicks) {
  const auto* descriptor =
      grpc_core::GlobalInstrumentsRegistryTestPeer::FindMetricDescriptorByName(
          "grpc.lb.rls.failed_picks");
  ASSERT_NE(descriptor, nullptr);
  EXPECT_EQ(descriptor->value_type,
            grpc_core::GlobalInstrumentsRegistry::ValueType::kUInt64);
  EXPECT_EQ(descriptor->instrument_type,
            grpc_core::GlobalInstrumentsRegistry::InstrumentType::kCounter);
  EXPECT_EQ(descriptor->enable_by_default, false);
  EXPECT_EQ(descriptor->name, "grpc.lb.rls.failed_picks");
  EXPECT_EQ(descriptor->unit, "{pick}");
  EXPECT_THAT(
      descriptor->label_keys,
      ::testing::ElementsAre("grpc.target", "grpc.lb.rls.server_target"));
  EXPECT_THAT(descriptor->optional_label_keys, ::testing::ElementsAre());
}

TEST_F(RlsMetricsEnd2endTest, MetricDefinitionCacheEntries) {
  const auto* descriptor =
      grpc_core::GlobalInstrumentsRegistryTestPeer::FindMetricDescriptorByName(
          "grpc.lb.rls.cache_entries");
  ASSERT_NE(descriptor, nullptr);
  EXPECT_EQ(descriptor->value_type,
            grpc_core::GlobalInstrumentsRegistry::ValueType::kInt64);
  EXPECT_EQ(
      descriptor->instrument_type,
      grpc_core::GlobalInstrumentsRegistry::InstrumentType::kCallbackGauge);
  EXPECT_EQ(descriptor->enable_by_default, false);
  EXPECT_EQ(descriptor->name, "grpc.lb.rls.cache_entries");
  EXPECT_EQ(descriptor->unit, "{entry}");
  EXPECT_THAT(descriptor->label_keys,
              ::testing::ElementsAre("grpc.target", "grpc.lb.rls.server_target",
                                     "grpc.lb.rls.instance_uuid"));
  EXPECT_THAT(descriptor->optional_label_keys, ::testing::ElementsAre());
}

TEST_F(RlsMetricsEnd2endTest, MetricDefinitionCacheSize) {
  const auto* descriptor =
      grpc_core::GlobalInstrumentsRegistryTestPeer::FindMetricDescriptorByName(
          "grpc.lb.rls.cache_size");
  ASSERT_NE(descriptor, nullptr);
  EXPECT_EQ(descriptor->value_type,
            grpc_core::GlobalInstrumentsRegistry::ValueType::kInt64);
  EXPECT_EQ(
      descriptor->instrument_type,
      grpc_core::GlobalInstrumentsRegistry::InstrumentType::kCallbackGauge);
  EXPECT_EQ(descriptor->enable_by_default, false);
  EXPECT_EQ(descriptor->name, "grpc.lb.rls.cache_size");
  EXPECT_EQ(descriptor->unit, "By");
  EXPECT_THAT(descriptor->label_keys,
              ::testing::ElementsAre("grpc.target", "grpc.lb.rls.server_target",
                                     "grpc.lb.rls.instance_uuid"));
  EXPECT_THAT(descriptor->optional_label_keys, ::testing::ElementsAre());
}

TEST_F(RlsMetricsEnd2endTest, MetricValues) {
  auto kMetricTargetPicks =
      grpc_core::GlobalInstrumentsRegistryTestPeer::
          FindUInt64CounterHandleByName("grpc.lb.rls.target_picks")
              .value();
  auto kMetricFailedPicks =
      grpc_core::GlobalInstrumentsRegistryTestPeer::
          FindUInt64CounterHandleByName("grpc.lb.rls.failed_picks")
              .value();
  auto kMetricCacheEntries =
      grpc_core::GlobalInstrumentsRegistryTestPeer::
          FindCallbackInt64GaugeHandleByName("grpc.lb.rls.cache_entries")
              .value();
  auto kMetricCacheSize =
      grpc_core::GlobalInstrumentsRegistryTestPeer::
          FindCallbackInt64GaugeHandleByName("grpc.lb.rls.cache_size")
              .value();
  StartBackends(2);
  SetNextResolution(
      MakeServiceConfigBuilder()
          .AddKeyBuilder(absl::StrFormat("\"names\":[{"
                                         "  \"service\":\"%s\","
                                         "  \"method\":\"%s\""
                                         "}],"
                                         "\"headers\":["
                                         "  {"
                                         "    \"key\":\"%s\","
                                         "    \"names\":["
                                         "      \"key1\""
                                         "    ]"
                                         "  }"
                                         "]",
                                         kServiceValue, kMethodValue, kTestKey))
          .Build());
  const std::string rls_target0 = grpc_core::LocalIpUri(backends_[0]->port_);
  const std::string rls_target1 = grpc_core::LocalIpUri(backends_[1]->port_);

  rls_server_->service_.SetResponse(BuildRlsRequest({{kTestKey, rls_target0}}),
                                    BuildRlsResponse({rls_target0}));
  CheckRpcSendOk(DEBUG_LOCATION,
                 RpcOptions().set_metadata({{"key1", rls_target0}}));
  EXPECT_EQ(rls_server_->service_.request_count(), 1);
  EXPECT_EQ(rls_server_->service_.response_count(), 1);
  EXPECT_EQ(backends_[0]->service_.request_count(), 1);
  EXPECT_EQ(backends_[1]->service_.request_count(), 0);

  EXPECT_THAT(
      stats_plugin_->GetUInt64CounterValue(
          kMetricTargetPicks,
          {target_uri_, rls_server_target_, rls_target0, "complete"}, {}),
      ::testing::Optional(1));
  EXPECT_THAT(
      stats_plugin_->GetUInt64CounterValue(
          kMetricTargetPicks,
          {target_uri_, rls_server_target_, rls_target1, "complete"}, {}),
      std::nullopt);
  EXPECT_EQ(stats_plugin_->GetUInt64CounterValue(
                kMetricFailedPicks, {target_uri_, rls_server_target_}, {}),
            std::nullopt);
  stats_plugin_->TriggerCallbacks();
  EXPECT_THAT(stats_plugin_->GetInt64CallbackGaugeValue(
                  kMetricCacheEntries,
                  {target_uri_, rls_server_target_, kRlsInstanceUuid}, {}),
              ::testing::Optional(1));
  auto cache_size = stats_plugin_->GetInt64CallbackGaugeValue(
      kMetricCacheSize, {target_uri_, rls_server_target_, kRlsInstanceUuid},
      {});
  EXPECT_THAT(cache_size, ::testing::Optional(::testing::Ge(1)));

  rls_server_->service_.SetResponse(BuildRlsRequest({{kTestKey, rls_target1}}),
                                    BuildRlsResponse({rls_target1}));
  CheckRpcSendOk(DEBUG_LOCATION,
                 RpcOptions().set_metadata({{"key1", rls_target1}}));
  EXPECT_EQ(rls_server_->service_.request_count(), 2);
  EXPECT_EQ(rls_server_->service_.response_count(), 2);
  EXPECT_EQ(backends_[0]->service_.request_count(), 1);
  EXPECT_EQ(backends_[1]->service_.request_count(), 1);

  EXPECT_THAT(
      stats_plugin_->GetUInt64CounterValue(
          kMetricTargetPicks,
          {target_uri_, rls_server_target_, rls_target0, "complete"}, {}),
      ::testing::Optional(1));
  EXPECT_THAT(
      stats_plugin_->GetUInt64CounterValue(
          kMetricTargetPicks,
          {target_uri_, rls_server_target_, rls_target1, "complete"}, {}),
      ::testing::Optional(1));
  EXPECT_EQ(stats_plugin_->GetUInt64CounterValue(
                kMetricFailedPicks, {target_uri_, rls_server_target_}, {}),
            std::nullopt);
  stats_plugin_->TriggerCallbacks();
  EXPECT_THAT(stats_plugin_->GetInt64CallbackGaugeValue(
                  kMetricCacheEntries,
                  {target_uri_, rls_server_target_, kRlsInstanceUuid}, {}),
              ::testing::Optional(2));
  auto cache_size2 = stats_plugin_->GetInt64CallbackGaugeValue(
      kMetricCacheSize, {target_uri_, rls_server_target_, kRlsInstanceUuid},
      {});
  EXPECT_THAT(cache_size2, ::testing::Optional(::testing::Ge(2)));
  if (cache_size.has_value() && cache_size2.has_value()) {
    EXPECT_GT(*cache_size2, *cache_size);
  }

  CheckRpcSendFailure(DEBUG_LOCATION, StatusCode::UNAVAILABLE,
                      "RLS request failed: INTERNAL: no response entry",
                      RpcOptions().set_metadata({{"key1", kTestValue}}));
  EXPECT_THAT(
      rls_server_->service_.GetUnmatchedRequests(),
      ::testing::ElementsAre(

          ::testing::Property(
              &RouteLookupRequest::DebugString,
              BuildRlsRequest({{kTestKey, kTestValue}}).DebugString())));
  EXPECT_EQ(rls_server_->service_.request_count(), 3);
  EXPECT_EQ(rls_server_->service_.response_count(), 2);
  EXPECT_EQ(backends_[0]->service_.request_count(), 1);
  EXPECT_EQ(backends_[1]->service_.request_count(), 1);

  EXPECT_THAT(
      stats_plugin_->GetUInt64CounterValue(
          kMetricTargetPicks,
          {target_uri_, rls_server_target_, rls_target0, "complete"}, {}),
      ::testing::Optional(1));
  EXPECT_THAT(
      stats_plugin_->GetUInt64CounterValue(
          kMetricTargetPicks,
          {target_uri_, rls_server_target_, rls_target1, "complete"}, {}),
      ::testing::Optional(1));
  EXPECT_THAT(stats_plugin_->GetUInt64CounterValue(
                  kMetricFailedPicks, {target_uri_, rls_server_target_}, {}),
              ::testing::Optional(1));
  stats_plugin_->TriggerCallbacks();
  EXPECT_THAT(stats_plugin_->GetInt64CallbackGaugeValue(
                  kMetricCacheEntries,
                  {target_uri_, rls_server_target_, kRlsInstanceUuid}, {}),
              ::testing::Optional(3));
  auto cache_size3 = stats_plugin_->GetInt64CallbackGaugeValue(
      kMetricCacheSize, {target_uri_, rls_server_target_, kRlsInstanceUuid},
      {});
  EXPECT_THAT(cache_size3, ::testing::Optional(::testing::Ge(3)));
  if (cache_size.has_value() && cache_size3.has_value()) {
    EXPECT_GT(*cache_size3, *cache_size);
  }
}

TEST_F(RlsMetricsEnd2endTest, MetricValuesDefaultTargetRpcs) {
  auto kMetricDefaultTargetPicks =
      grpc_core::GlobalInstrumentsRegistryTestPeer::
          FindUInt64CounterHandleByName("grpc.lb.rls.default_target_picks")
              .value();
  StartBackends(1);
  const std::string default_target = grpc_core::LocalIpUri(backends_[0]->port_);
  SetNextResolution(
      MakeServiceConfigBuilder()
          .AddKeyBuilder(absl::StrFormat("\"names\":[{"
                                         "  \"service\":\"%s\","
                                         "  \"method\":\"%s\""
                                         "}],"
                                         "\"headers\":["
                                         "  {"
                                         "    \"key\":\"%s\","
                                         "    \"names\":["
                                         "      \"key1\""
                                         "    ]"
                                         "  }"
                                         "]",
                                         kServiceValue, kMethodValue, kTestKey))
          .set_default_target(default_target)
          .Build());

  CheckRpcSendOk(DEBUG_LOCATION,
                 RpcOptions().set_metadata({{"key1", kTestValue}}));
  EXPECT_THAT(
      rls_server_->service_.GetUnmatchedRequests(),
      ::testing::ElementsAre(

          ::testing::Property(
              &RouteLookupRequest::DebugString,
              BuildRlsRequest({{kTestKey, kTestValue}}).DebugString())));
  EXPECT_EQ(rls_server_->service_.request_count(), 1);
  EXPECT_EQ(rls_server_->service_.response_count(), 0);
  EXPECT_EQ(backends_[0]->service_.request_count(), 1);

  EXPECT_THAT(
      stats_plugin_->GetUInt64CounterValue(
          kMetricDefaultTargetPicks,
          {target_uri_, rls_server_target_, default_target, "complete"}, {}),
      ::testing::Optional(1));
}

}
}
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  grpc::testing::TestEnvironment env(&argc, argv);
  return RUN_ALL_TESTS();
}
