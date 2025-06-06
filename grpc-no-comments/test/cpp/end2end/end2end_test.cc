
// Copyright 2015 gRPC authors.

#include <grpc/grpc.h>
#include <grpc/support/alloc.h>
#include <grpc/support/time.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/resource_quota.h>
#include <grpcpp/security/auth_metadata_processor.h>
#include <grpcpp/security/credentials.h>
#include <grpcpp/security/server_credentials.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>
#include <grpcpp/support/string_ref.h>
#include <grpcpp/test/channel_test_peer.h>

#include <mutex>
#include <thread>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/memory/memory.h"
#include "absl/strings/ascii.h"
#include "absl/strings/match.h"
#include "absl/strings/str_format.h"
#include "src/core/client_channel/backup_poller.h"
#include "src/core/config/config_vars.h"
#include "src/core/credentials/call/call_credentials.h"
#include "src/core/lib/experiments/experiments.h"
#include "src/core/lib/iomgr/iomgr.h"
#include "src/core/util/crash.h"
#include "src/core/util/env.h"
#include "src/proto/grpc/testing/duplicate/echo_duplicate.grpc.pb.h"
#include "src/proto/grpc/testing/echo.grpc.pb.h"
#include "test/core/test_util/port.h"
#include "test/core/test_util/test_config.h"
#include "test/cpp/end2end/interceptors_util.h"
#include "test/cpp/end2end/test_service_impl.h"
#include "test/cpp/util/string_ref_helper.h"
#include "test/cpp/util/test_credentials_provider.h"

#ifdef GRPC_POSIX_SOCKET_EV
#include "src/core/lib/iomgr/ev_posix.h"
#endif

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using std::chrono::system_clock;

namespace grpc {
namespace testing {
namespace {

bool CheckIsLocalhost(const std::string& addr) {
  const std::string kIpv6("ipv6:%5B::1%5D:");
  const std::string kIpv4MappedIpv6("ipv6:%5B::ffff:127.0.0.1%5D:");
  const std::string kIpv4("ipv4:127.0.0.1:");
  return addr.substr(0, kIpv4.size()) == kIpv4 ||
         addr.substr(0, kIpv4MappedIpv6.size()) == kIpv4MappedIpv6 ||
         addr.substr(0, kIpv6.size()) == kIpv6;
}

const int kClientChannelBackupPollIntervalMs = 200;

const char kTestCredsPluginErrorMsg[] = "Could not find plugin metadata.";

const char kFakeToken[] = "fake_token";
const char kFakeSelector[] = "fake_selector";
const char kExpectedFakeCredsDebugString[] =
    "CallCredentials{GoogleIAMCredentials{Token:present,"
    "AuthoritySelector:fake_selector}}";

const char kWrongToken[] = "wrong_token";
const char kWrongSelector[] = "wrong_selector";
const char kExpectedWrongCredsDebugString[] =
    "CallCredentials{GoogleIAMCredentials{Token:present,"
    "AuthoritySelector:wrong_selector}}";

const char kFakeToken1[] = "fake_token1";
const char kFakeSelector1[] = "fake_selector1";
const char kExpectedFakeCreds1DebugString[] =
    "CallCredentials{GoogleIAMCredentials{Token:present,"
    "AuthoritySelector:fake_selector1}}";

const char kFakeToken2[] = "fake_token2";
const char kFakeSelector2[] = "fake_selector2";
const char kExpectedFakeCreds2DebugString[] =
    "CallCredentials{GoogleIAMCredentials{Token:present,"
    "AuthoritySelector:fake_selector2}}";

const char kExpectedAuthMetadataPluginKeyFailureCredsDebugString[] =
    "CallCredentials{TestMetadataCredentials{key:TestPluginMetadata,"
    "value:Does not matter, will fail the key is invalid.}}";
const char kExpectedAuthMetadataPluginValueFailureCredsDebugString[] =
    "CallCredentials{TestMetadataCredentials{key:test-plugin-metadata,"
    "value:With illegal \n value.}}";
const char kExpectedAuthMetadataPluginWithDeadlineCredsDebugString[] =
    "CallCredentials{TestMetadataCredentials{key:meta_key,value:Does "
    "not "
    "matter}}";
const char kExpectedNonBlockingAuthMetadataPluginFailureCredsDebugString[] =
    "CallCredentials{TestMetadataCredentials{key:test-plugin-metadata,"
    "value:Does not matter, will fail anyway (see 3rd param)}}";
const char
    kExpectedNonBlockingAuthMetadataPluginAndProcessorSuccessCredsDebugString
        [] = "CallCredentials{TestMetadataCredentials{key:test-plugin-"
             "metadata,value:Dr Jekyll}}";
const char
    kExpectedNonBlockingAuthMetadataPluginAndProcessorFailureCredsDebugString
        [] = "CallCredentials{TestMetadataCredentials{key:test-plugin-"
             "metadata,value:Mr Hyde}}";
const char kExpectedBlockingAuthMetadataPluginFailureCredsDebugString[] =
    "CallCredentials{TestMetadataCredentials{key:test-plugin-metadata,"
    "value:Does not matter, will fail anyway (see 3rd param)}}";
const char kExpectedCompositeCallCredsDebugString[] =
    "CallCredentials{CompositeCallCredentials{TestMetadataCredentials{"
    "key:call-creds-key1,value:call-creds-val1},TestMetadataCredentials{key:"
    "call-creds-key2,value:call-creds-val2}}}";

class TestMetadataCredentialsPlugin : public MetadataCredentialsPlugin {
 public:
  static const char kGoodMetadataKey[];
  static const char kBadMetadataKey[];

  TestMetadataCredentialsPlugin(const grpc::string_ref& metadata_key,
                                const grpc::string_ref& metadata_value,
                                bool is_blocking, bool is_successful,
                                int delay_ms)
      : metadata_key_(metadata_key.data(), metadata_key.length()),
        metadata_value_(metadata_value.data(), metadata_value.length()),
        is_blocking_(is_blocking),
        is_successful_(is_successful),
        delay_ms_(delay_ms) {}

  bool IsBlocking() const override { return is_blocking_; }

  Status GetMetadata(
      grpc::string_ref service_url, grpc::string_ref method_name,
      const grpc::AuthContext& channel_auth_context,
      std::multimap<std::string, std::string>* metadata) override {
    if (delay_ms_ != 0) {
      gpr_sleep_until(
          gpr_time_add(gpr_now(GPR_CLOCK_REALTIME),
                       gpr_time_from_millis(delay_ms_, GPR_TIMESPAN)));
    }
    EXPECT_GT(service_url.length(), 0UL);
    EXPECT_GT(method_name.length(), 0UL);
    EXPECT_TRUE(channel_auth_context.IsPeerAuthenticated());
    EXPECT_TRUE(metadata != nullptr);
    if (is_successful_) {
      metadata->insert(std::pair(metadata_key_, metadata_value_));
      return Status::OK;
    } else {
      return Status(StatusCode::NOT_FOUND, kTestCredsPluginErrorMsg);
    }
  }

  std::string DebugString() override {
    return absl::StrFormat("TestMetadataCredentials{key:%s,value:%s}",
                           metadata_key_.c_str(), metadata_value_.c_str());
  }

 private:
  std::string metadata_key_;
  std::string metadata_value_;
  bool is_blocking_;
  bool is_successful_;
  int delay_ms_;
};

const char TestMetadataCredentialsPlugin::kBadMetadataKey[] =
    "TestPluginMetadata";
const char TestMetadataCredentialsPlugin::kGoodMetadataKey[] =
    "test-plugin-metadata";

class TestAuthMetadataProcessor : public AuthMetadataProcessor {
 public:
  static const char kGoodGuy[];

  explicit TestAuthMetadataProcessor(bool is_blocking)
      : is_blocking_(is_blocking) {}

  std::shared_ptr<CallCredentials> GetCompatibleClientCreds() {
    return grpc::MetadataCredentialsFromPlugin(
        std::unique_ptr<MetadataCredentialsPlugin>(
            new TestMetadataCredentialsPlugin(
                TestMetadataCredentialsPlugin::kGoodMetadataKey, kGoodGuy,
                is_blocking_, true, 0)));
  }

  std::shared_ptr<CallCredentials> GetIncompatibleClientCreds() {
    return grpc::MetadataCredentialsFromPlugin(
        std::unique_ptr<MetadataCredentialsPlugin>(
            new TestMetadataCredentialsPlugin(
                TestMetadataCredentialsPlugin::kGoodMetadataKey, "Mr Hyde",
                is_blocking_, true, 0)));
  }

  bool IsBlocking() const override { return is_blocking_; }

  Status Process(const InputMetadata& auth_metadata, AuthContext* context,
                 OutputMetadata* consumed_auth_metadata,
                 OutputMetadata* response_metadata) override {
    EXPECT_TRUE(consumed_auth_metadata != nullptr);
    EXPECT_TRUE(context != nullptr);
    EXPECT_TRUE(response_metadata != nullptr);
    auto auth_md =
        auth_metadata.find(TestMetadataCredentialsPlugin::kGoodMetadataKey);
    EXPECT_NE(auth_md, auth_metadata.end());
    string_ref auth_md_value = auth_md->second;
    if (auth_md_value == kGoodGuy) {
      context->AddProperty(kIdentityPropName, kGoodGuy);
      context->SetPeerIdentityPropertyName(kIdentityPropName);
      consumed_auth_metadata->insert(
          std::pair(string(auth_md->first.data(), auth_md->first.length()),
                    string(auth_md->second.data(), auth_md->second.length())));
      return Status::OK;
    } else {
      return Status(StatusCode::UNAUTHENTICATED,
                    string("Invalid principal: ") +
                        string(auth_md_value.data(), auth_md_value.length()));
    }
  }

 private:
  static const char kIdentityPropName[];
  bool is_blocking_;
};

const char TestAuthMetadataProcessor::kGoodGuy[] = "Dr Jekyll";
const char TestAuthMetadataProcessor::kIdentityPropName[] = "novel identity";

class Proxy : public grpc::testing::EchoTestService::Service {
 public:
  explicit Proxy(const std::shared_ptr<Channel>& channel)
      : stub_(grpc::testing::EchoTestService::NewStub(channel)) {}

  Status Echo(ServerContext* server_context, const EchoRequest* request,
              EchoResponse* response) override {
    std::unique_ptr<ClientContext> client_context =
        ClientContext::FromServerContext(*server_context);
    return stub_->Echo(client_context.get(), *request, response);
  }

 private:
  std::unique_ptr<grpc::testing::EchoTestService::Stub> stub_;
};

class TestServiceImplDupPkg
    : public grpc::testing::duplicate::EchoTestService::Service {
 public:
  Status Echo(ServerContext* , const EchoRequest* ,
              EchoResponse* response) override {
    response->set_message("no package");
    return Status::OK;
  }
};

class TestScenario {
 public:
  TestScenario(bool use_interceptors, bool use_proxy, bool inproc,
               const std::string& credentials_type, bool callback_server)
      : use_interceptors_(use_interceptors),
        use_proxy_(use_proxy),
        inproc_(inproc),
        credentials_type_(credentials_type),
        callback_server_(callback_server) {}

  bool use_interceptors() const { return use_interceptors_; }
  bool use_proxy() const { return use_proxy_; }
  bool inproc() const { return inproc_; }
  const std::string& credentials_type() const { return credentials_type_; }
  bool callback_server() const { return callback_server_; }

  std::string AsString() const;

  static std::string Name(const ::testing::TestParamInfo<TestScenario>& info) {
    return info.param.AsString();
  }

 private:
  bool use_interceptors_;
  bool use_proxy_;
  bool inproc_;
  const std::string credentials_type_;
  bool callback_server_;
};

std::string TestScenario::AsString() const {
  std::string retval = use_interceptors_ ? "Interceptor" : "";
  if (use_proxy_) retval += "Proxy";
  if (inproc_) retval += "Inproc";
  if (callback_server_) retval += "CallbackServer";
  if (credentials_type_ == kInsecureCredentialsType) {
    retval += "Insecure";
  } else {
    std::string creds_type = absl::AsciiStrToLower(credentials_type_);
    if (!creds_type.empty()) creds_type[0] = absl::ascii_toupper(creds_type[0]);
    retval += creds_type;
  }
  return retval;
}

class End2endTest : public ::testing::TestWithParam<TestScenario> {
 protected:
  static void SetUpTestSuite() { grpc_init(); }
  static void TearDownTestSuite() { grpc_shutdown(); }
  End2endTest()
      : is_server_started_(false),
        kMaxMessageSize_(8192),
        special_service_("special"),
        first_picked_port_(0) {}

  void TearDown() override {
    if (is_server_started_) {
      server_->Shutdown();
      if (proxy_server_) proxy_server_->Shutdown();
    }
    if (first_picked_port_ > 0) {
      grpc_recycle_unused_port(first_picked_port_);
    }
  }

  void StartServer(const std::shared_ptr<AuthMetadataProcessor>& processor) {
    int port = grpc_pick_unused_port_or_die();
    first_picked_port_ = port;
    server_address_ << "localhost:" << port;

    BuildAndStartServer(processor);
  }

  void RestartServer(const std::shared_ptr<AuthMetadataProcessor>& processor) {
    if (is_server_started_) {
      server_->Shutdown();
      BuildAndStartServer(processor);
    }
  }

  void BuildAndStartServer(
      const std::shared_ptr<AuthMetadataProcessor>& processor) {
    ServerBuilder builder;
    ConfigureServerBuilder(&builder);
    auto server_creds = GetCredentialsProvider()->GetServerCredentials(
        GetParam().credentials_type());
    if (GetParam().credentials_type() != kInsecureCredentialsType) {
      server_creds->SetAuthMetadataProcessor(processor);
    }
    if (GetParam().use_interceptors()) {
      std::vector<
          std::unique_ptr<experimental::ServerInterceptorFactoryInterface>>
          creators;

      creators.reserve(20);
      for (auto i = 0; i < 20; i++) {
        creators.push_back(std::make_unique<PhonyInterceptorFactory>());
      }
      builder.experimental().SetInterceptorCreators(std::move(creators));
    }
    builder.AddListeningPort(server_address_.str(), server_creds);
    if (!GetParam().callback_server()) {
      builder.RegisterService(&service_);
    } else {
      builder.RegisterService(&callback_service_);
    }
    builder.RegisterService("foo.test.youtube.com", &special_service_);
    builder.RegisterService(&dup_pkg_service_);

    builder.SetSyncServerOption(ServerBuilder::SyncServerOption::NUM_CQS, 4);
    builder.SetSyncServerOption(
        ServerBuilder::SyncServerOption::CQ_TIMEOUT_MSEC, 10);

    server_ = builder.BuildAndStart();
    is_server_started_ = true;
  }

  virtual void ConfigureServerBuilder(ServerBuilder* builder) {
    builder->SetMaxMessageSize(
        kMaxMessageSize_);
  }

  void ResetChannel(
      std::vector<
          std::unique_ptr<experimental::ClientInterceptorFactoryInterface>>
          interceptor_creators = {}) {
    if (!is_server_started_) {
      StartServer(std::shared_ptr<AuthMetadataProcessor>());
    }
    EXPECT_TRUE(is_server_started_);
    ChannelArguments args;
    auto channel_creds = GetCredentialsProvider()->GetChannelCredentials(
        GetParam().credentials_type(), &args);
    if (!user_agent_prefix_.empty()) {
      args.SetUserAgentPrefix(user_agent_prefix_);
    }
    args.SetString(GRPC_ARG_SECONDARY_USER_AGENT_STRING, "end2end_test");

    if (!GetParam().inproc()) {
      if (!GetParam().use_interceptors()) {
        channel_ = grpc::CreateCustomChannel(server_address_.str(),
                                             channel_creds, args);
      } else {
        channel_ = CreateCustomChannelWithInterceptors(
            server_address_.str(), channel_creds, args,
            interceptor_creators.empty() ? CreatePhonyClientInterceptors()
                                         : std::move(interceptor_creators));
      }
    } else {
      if (!GetParam().use_interceptors()) {
        channel_ = server_->InProcessChannel(args);
      } else {
        channel_ = server_->experimental().InProcessChannelWithInterceptors(
            args, interceptor_creators.empty()
                      ? CreatePhonyClientInterceptors()
                      : std::move(interceptor_creators));
      }
    }
  }

  void ResetStub(
      std::vector<
          std::unique_ptr<experimental::ClientInterceptorFactoryInterface>>
          interceptor_creators = {}) {
    ResetChannel(std::move(interceptor_creators));
    if (GetParam().use_proxy()) {
      proxy_service_ = std::make_unique<Proxy>(channel_);
      int port = grpc_pick_unused_port_or_die();
      std::ostringstream proxyaddr;
      proxyaddr << "localhost:" << port;
      ServerBuilder builder;
      builder.AddListeningPort(proxyaddr.str(), InsecureServerCredentials());
      builder.RegisterService(proxy_service_.get());

      builder.SetSyncServerOption(ServerBuilder::SyncServerOption::NUM_CQS, 4);
      builder.SetSyncServerOption(
          ServerBuilder::SyncServerOption::CQ_TIMEOUT_MSEC, 10);

      proxy_server_ = builder.BuildAndStart();

      channel_ =
          grpc::CreateChannel(proxyaddr.str(), InsecureChannelCredentials());
    }

    stub_ = grpc::testing::EchoTestService::NewStub(channel_);
    PhonyInterceptor::Reset();
  }

  bool is_server_started_;
  std::shared_ptr<Channel> channel_;
  std::unique_ptr<grpc::testing::EchoTestService::Stub> stub_;
  std::unique_ptr<Server> server_;
  std::unique_ptr<Server> proxy_server_;
  std::unique_ptr<Proxy> proxy_service_;
  std::ostringstream server_address_;
  const int kMaxMessageSize_;
  TestServiceImpl service_;
  CallbackTestServiceImpl callback_service_;
  TestServiceImpl special_service_;
  TestServiceImplDupPkg dup_pkg_service_;
  std::string user_agent_prefix_;
  int first_picked_port_;
};

void SendRpc(grpc::testing::EchoTestService::Stub* stub, int num_rpcs,
             bool with_binary_metadata) {
  EchoRequest request;
  EchoResponse response;
  request.set_message("Hello hello hello hello");

  for (int i = 0; i < num_rpcs; ++i) {
    ClientContext context;
    if (with_binary_metadata) {
      char bytes[8] = {'\0', '\1', '\2', '\3',
                       '\4', '\5', '\6', static_cast<char>(i)};
      context.AddMetadata("custom-bin", std::string(bytes, 8));
    }
    context.set_compression_algorithm(GRPC_COMPRESS_GZIP);
    Status s = stub->Echo(&context, request, &response);
    EXPECT_EQ(response.message(), request.message());
    EXPECT_TRUE(s.ok());
  }
}

class End2endServerTryCancelTest : public End2endTest {
 protected:

  // NOTE: Do not call this function with server_try_cancel == DO_NOT_CANCEL.
  void TestRequestStreamServerCancel(
      ServerTryCancelRequestPhase server_try_cancel, int num_msgs_to_send) {
    RestartServer(std::shared_ptr<AuthMetadataProcessor>());
    ResetStub();
    EchoRequest request;
    EchoResponse response;
    ClientContext context;

    context.AddMetadata(kServerTryCancelRequest,
                        std::to_string(server_try_cancel));

    auto stream = stub_->RequestStream(&context, &response);

    int num_msgs_sent = 0;
    while (num_msgs_sent < num_msgs_to_send) {
      request.set_message("hello");
      if (!stream->Write(request)) {
        break;
      }
      num_msgs_sent++;
    }
    LOG(INFO) << "Sent " << num_msgs_sent << " messages";

    stream->WritesDone();
    Status s = stream->Finish();

    switch (server_try_cancel) {
      case CANCEL_BEFORE_PROCESSING:
      case CANCEL_DURING_PROCESSING:

        EXPECT_LE(num_msgs_sent, num_msgs_to_send);
        break;

      case CANCEL_AFTER_PROCESSING:

        EXPECT_EQ(num_msgs_sent, num_msgs_to_send);
        break;

      default:
        LOG(ERROR) << "Invalid server_try_cancel value: " << server_try_cancel;
        EXPECT_TRUE(server_try_cancel > DO_NOT_CANCEL &&
                    server_try_cancel <= CANCEL_AFTER_PROCESSING);
        break;
    }

    EXPECT_FALSE(s.ok());
    EXPECT_EQ(grpc::StatusCode::CANCELLED, s.error_code());

    if (GetParam().use_interceptors()) {
      EXPECT_EQ(20, PhonyInterceptor::GetNumTimesCancel());
    }
  }

  // NOTE: Do not call this function with server_try_cancel == DO_NOT_CANCEL.
  void TestResponseStreamServerCancel(
      ServerTryCancelRequestPhase server_try_cancel) {
    RestartServer(std::shared_ptr<AuthMetadataProcessor>());
    ResetStub();
    EchoRequest request;
    EchoResponse response;
    ClientContext context;

    context.AddMetadata(kServerTryCancelRequest,
                        std::to_string(server_try_cancel));

    request.set_message("hello");
    auto stream = stub_->ResponseStream(&context, request);

    int num_msgs_read = 0;
    while (num_msgs_read < kServerDefaultResponseStreamsToSend) {
      if (!stream->Read(&response)) {
        break;
      }
      EXPECT_EQ(response.message(),
                request.message() + std::to_string(num_msgs_read));
      num_msgs_read++;
    }
    LOG(INFO) << "Read " << num_msgs_read << " messages";

    Status s = stream->Finish();

    switch (server_try_cancel) {
      case CANCEL_BEFORE_PROCESSING:

        EXPECT_EQ(num_msgs_read, 0);
        break;

      case CANCEL_DURING_PROCESSING:

        EXPECT_LE(num_msgs_read, kServerDefaultResponseStreamsToSend);
        break;

      case CANCEL_AFTER_PROCESSING:

        EXPECT_LE(num_msgs_read, kServerDefaultResponseStreamsToSend);
        break;

      default: {
        LOG(ERROR) << "Invalid server_try_cancel value: " << server_try_cancel;
        EXPECT_TRUE(server_try_cancel > DO_NOT_CANCEL &&
                    server_try_cancel <= CANCEL_AFTER_PROCESSING);
        break;
      }
    }

    EXPECT_FALSE(s.ok());

    if (GetParam().use_interceptors()) {
      EXPECT_EQ(20, PhonyInterceptor::GetNumTimesCancel());
    }
  }

  // NOTE: Do not call this function with server_try_cancel == DO_NOT_CANCEL.
  void TestBidiStreamServerCancel(ServerTryCancelRequestPhase server_try_cancel,
                                  int num_messages) {
    RestartServer(std::shared_ptr<AuthMetadataProcessor>());
    ResetStub();
    EchoRequest request;
    EchoResponse response;
    ClientContext context;

    context.AddMetadata(kServerTryCancelRequest,
                        std::to_string(server_try_cancel));

    auto stream = stub_->BidiStream(&context);

    int num_msgs_read = 0;
    int num_msgs_sent = 0;
    while (num_msgs_sent < num_messages) {
      request.set_message("hello " + std::to_string(num_msgs_sent));
      if (!stream->Write(request)) {
        break;
      }
      num_msgs_sent++;

      if (!stream->Read(&response)) {
        break;
      }
      num_msgs_read++;

      EXPECT_EQ(response.message(), request.message());
    }
    LOG(INFO) << "Sent " << num_msgs_sent << " messages";
    LOG(INFO) << "Read " << num_msgs_read << " messages";

    stream->WritesDone();
    Status s = stream->Finish();

    switch (server_try_cancel) {
      case CANCEL_BEFORE_PROCESSING:
        EXPECT_EQ(num_msgs_read, 0);
        break;

      case CANCEL_DURING_PROCESSING:
        EXPECT_LE(num_msgs_sent, num_messages);
        EXPECT_LE(num_msgs_read, num_msgs_sent);
        break;

      case CANCEL_AFTER_PROCESSING:
        EXPECT_EQ(num_msgs_sent, num_messages);

        EXPECT_LE(num_msgs_read, num_msgs_sent);
        break;

      default:
        LOG(ERROR) << "Invalid server_try_cancel value: " << server_try_cancel;
        EXPECT_TRUE(server_try_cancel > DO_NOT_CANCEL &&
                    server_try_cancel <= CANCEL_AFTER_PROCESSING);
        break;
    }

    EXPECT_FALSE(s.ok());
    EXPECT_EQ(grpc::StatusCode::CANCELLED, s.error_code());

    if (GetParam().use_interceptors()) {
      EXPECT_EQ(20, PhonyInterceptor::GetNumTimesCancel());
    }
  }
};

TEST_P(End2endServerTryCancelTest, RequestEchoServerCancel) {
  ResetStub();
  EchoRequest request;
  EchoResponse response;
  ClientContext context;

  context.AddMetadata(kServerTryCancelRequest,
                      std::to_string(CANCEL_BEFORE_PROCESSING));
  Status s = stub_->Echo(&context, request, &response);
  EXPECT_FALSE(s.ok());
  EXPECT_EQ(grpc::StatusCode::CANCELLED, s.error_code());
}

TEST_P(End2endServerTryCancelTest, RequestStreamServerCancelBeforeReads) {
  TestRequestStreamServerCancel(CANCEL_BEFORE_PROCESSING, 1);
}

TEST_P(End2endServerTryCancelTest, RequestStreamServerCancelDuringRead) {
  TestRequestStreamServerCancel(CANCEL_DURING_PROCESSING, 10);
}

TEST_P(End2endServerTryCancelTest, RequestStreamServerCancelAfterReads) {
  TestRequestStreamServerCancel(CANCEL_AFTER_PROCESSING, 4);
}

TEST_P(End2endServerTryCancelTest, ResponseStreamServerCancelBefore) {
  TestResponseStreamServerCancel(CANCEL_BEFORE_PROCESSING);
}

TEST_P(End2endServerTryCancelTest, ResponseStreamServerCancelDuring) {
  TestResponseStreamServerCancel(CANCEL_DURING_PROCESSING);
}

TEST_P(End2endServerTryCancelTest, ResponseStreamServerCancelAfter) {
  TestResponseStreamServerCancel(CANCEL_AFTER_PROCESSING);
}

TEST_P(End2endServerTryCancelTest, BidiStreamServerCancelBefore) {
  TestBidiStreamServerCancel(CANCEL_BEFORE_PROCESSING, 2);
}

TEST_P(End2endServerTryCancelTest, BidiStreamServerCancelDuring) {
  TestBidiStreamServerCancel(CANCEL_DURING_PROCESSING, 10);
}

TEST_P(End2endServerTryCancelTest, BidiStreamServerCancelAfter) {
  TestBidiStreamServerCancel(CANCEL_AFTER_PROCESSING, 5);
}

TEST_P(End2endTest, SimpleRpcWithCustomUserAgentPrefix) {

  if (GetParam().inproc()) {
    return;
  }
  user_agent_prefix_ = "custom_prefix";
  ResetStub();
  EchoRequest request;
  EchoResponse response;
  request.set_message("Hello hello hello hello");
  request.mutable_param()->set_echo_metadata(true);

  ClientContext context;
  Status s = stub_->Echo(&context, request, &response);
  EXPECT_EQ(response.message(), request.message());
  EXPECT_TRUE(s.ok());
  const auto& trailing_metadata = context.GetServerTrailingMetadata();
  auto iter = trailing_metadata.find("user-agent");
  EXPECT_TRUE(iter != trailing_metadata.end());
  std::string expected_prefix = user_agent_prefix_ + " grpc-c++/";
  EXPECT_TRUE(iter->second.starts_with(expected_prefix)) << iter->second;
}

TEST_P(End2endTest, MultipleRpcsWithVariedBinaryMetadataValue) {
  ResetStub();
  std::vector<std::thread> threads;
  threads.reserve(10);
  for (int i = 0; i < 10; ++i) {
    threads.emplace_back(SendRpc, stub_.get(), 10, true);
  }
  for (int i = 0; i < 10; ++i) {
    threads[i].join();
  }
}

TEST_P(End2endTest, MultipleRpcs) {
  ResetStub();
  std::vector<std::thread> threads;
  threads.reserve(10);
  for (int i = 0; i < 10; ++i) {
    threads.emplace_back(SendRpc, stub_.get(), 10, false);
  }
  for (int i = 0; i < 10; ++i) {
    threads[i].join();
  }
}

TEST_P(End2endTest, ManyStubs) {
  ResetStub();
  ChannelTestPeer peer(channel_.get());
  int registered_calls_pre = peer.registered_calls();
  for (int i = 0; i < 1000; ++i) {
    grpc::testing::EchoTestService::NewStub(channel_);
  }
  EXPECT_EQ(peer.registered_calls(), registered_calls_pre);
}

TEST_P(End2endTest, EmptyBinaryMetadata) {
  ResetStub();
  EchoRequest request;
  EchoResponse response;
  request.set_message("Hello hello hello hello");
  ClientContext context;
  context.AddMetadata("custom-bin", "");
  Status s = stub_->Echo(&context, request, &response);
  EXPECT_EQ(response.message(), request.message());
  EXPECT_TRUE(s.ok());
}

TEST_P(End2endTest, AuthoritySeenOnServerSide) {
  ResetStub();
  EchoRequest request;
  request.mutable_param()->set_echo_host_from_authority_header(true);
  EchoResponse response;
  request.set_message("Live long and prosper.");
  ClientContext context;
  Status s = stub_->Echo(&context, request, &response);
  EXPECT_EQ(response.message(), request.message());
  if (GetParam().credentials_type() == kTlsCredentialsType) {

    EXPECT_EQ("foo.test.google.fr", response.param().host());
  } else if (GetParam().inproc()) {
    EXPECT_EQ("inproc", response.param().host());
  } else {
    EXPECT_EQ(server_address_.str(), response.param().host());
  }
  EXPECT_TRUE(s.ok());
}

TEST_P(End2endTest, ReconnectChannel) {
  if (GetParam().inproc()) {
    return;
  }
  int poller_slowdown_factor = 1;

#ifdef GRPC_POSIX_SOCKET_EV
  if (grpc_core::ConfigVars::Get().PollStrategy() == "poll") {
    poller_slowdown_factor = 2;
  }
#endif
  ResetStub();
  SendRpc(stub_.get(), 1, false);
  RestartServer(std::shared_ptr<AuthMetadataProcessor>());

  gpr_sleep_until(
      gpr_time_add(gpr_now(GPR_CLOCK_REALTIME),
                   gpr_time_from_millis(kClientChannelBackupPollIntervalMs * 5 *
                                            poller_slowdown_factor *
                                            grpc_test_slowdown_factor(),
                                        GPR_TIMESPAN)));
  SendRpc(stub_.get(), 1, false);
}

TEST_P(End2endTest, RequestStreamOneRequest) {
  ResetStub();
  EchoRequest request;
  EchoResponse response;
  ClientContext context;

  auto stream = stub_->RequestStream(&context, &response);
  request.set_message("hello");
  EXPECT_TRUE(stream->Write(request));
  stream->WritesDone();
  Status s = stream->Finish();
  EXPECT_EQ(response.message(), request.message());
  EXPECT_TRUE(s.ok());
  EXPECT_TRUE(context.debug_error_string().empty());
}

TEST_P(End2endTest, RequestStreamOneRequestWithCoalescingApi) {
  ResetStub();
  EchoRequest request;
  EchoResponse response;
  ClientContext context;

  context.set_initial_metadata_corked(true);
  auto stream = stub_->RequestStream(&context, &response);
  request.set_message("hello");
  stream->WriteLast(request, WriteOptions());
  Status s = stream->Finish();
  EXPECT_EQ(response.message(), request.message());
  EXPECT_TRUE(s.ok());
}

TEST_P(End2endTest, RequestStreamTwoRequests) {
  ResetStub();
  EchoRequest request;
  EchoResponse response;
  ClientContext context;

  auto stream = stub_->RequestStream(&context, &response);
  request.set_message("hello");
  EXPECT_TRUE(stream->Write(request));
  EXPECT_TRUE(stream->Write(request));
  stream->WritesDone();
  Status s = stream->Finish();
  EXPECT_EQ(response.message(), "hellohello");
  EXPECT_TRUE(s.ok());
}

TEST_P(End2endTest, RequestStreamTwoRequestsWithWriteThrough) {
  ResetStub();
  EchoRequest request;
  EchoResponse response;
  ClientContext context;

  auto stream = stub_->RequestStream(&context, &response);
  request.set_message("hello");
  EXPECT_TRUE(stream->Write(request, WriteOptions().set_write_through()));
  EXPECT_TRUE(stream->Write(request, WriteOptions().set_write_through()));
  stream->WritesDone();
  Status s = stream->Finish();
  EXPECT_EQ(response.message(), "hellohello");
  EXPECT_TRUE(s.ok());
}

TEST_P(End2endTest, RequestStreamTwoRequestsWithCoalescingApi) {
  ResetStub();
  EchoRequest request;
  EchoResponse response;
  ClientContext context;

  context.set_initial_metadata_corked(true);
  auto stream = stub_->RequestStream(&context, &response);
  request.set_message("hello");
  EXPECT_TRUE(stream->Write(request));
  stream->WriteLast(request, WriteOptions());
  Status s = stream->Finish();
  EXPECT_EQ(response.message(), "hellohello");
  EXPECT_TRUE(s.ok());
}

TEST_P(End2endTest, ResponseStream) {
  ResetStub();
  EchoRequest request;
  EchoResponse response;
  ClientContext context;
  request.set_message("hello");

  auto stream = stub_->ResponseStream(&context, request);
  for (int i = 0; i < kServerDefaultResponseStreamsToSend; ++i) {
    EXPECT_TRUE(stream->Read(&response));
    EXPECT_EQ(response.message(), request.message() + std::to_string(i));
  }
  EXPECT_FALSE(stream->Read(&response));

  Status s = stream->Finish();
  EXPECT_TRUE(s.ok());
}

TEST_P(End2endTest, ResponseStreamWithCoalescingApi) {
  ResetStub();
  EchoRequest request;
  EchoResponse response;
  ClientContext context;
  request.set_message("hello");
  context.AddMetadata(kServerUseCoalescingApi, "1");

  auto stream = stub_->ResponseStream(&context, request);
  for (int i = 0; i < kServerDefaultResponseStreamsToSend; ++i) {
    EXPECT_TRUE(stream->Read(&response));
    EXPECT_EQ(response.message(), request.message() + std::to_string(i));
  }
  EXPECT_FALSE(stream->Read(&response));

  Status s = stream->Finish();
  EXPECT_TRUE(s.ok());
}

TEST_P(End2endTest, ResponseStreamWithEverythingCoalesced) {
  ResetStub();
  EchoRequest request;
  EchoResponse response;
  ClientContext context;
  request.set_message("hello");
  context.AddMetadata(kServerUseCoalescingApi, "1");

  context.AddMetadata(kServerResponseStreamsToSend, "1");

  auto stream = stub_->ResponseStream(&context, request);
  EXPECT_TRUE(stream->Read(&response));
  EXPECT_EQ(response.message(), request.message() + "0");

  EXPECT_FALSE(stream->Read(&response));

  Status s = stream->Finish();
  EXPECT_TRUE(s.ok());
}

TEST_P(End2endTest, BidiStream) {
  ResetStub();
  EchoRequest request;
  EchoResponse response;
  ClientContext context;
  std::string msg("hello");

  auto stream = stub_->BidiStream(&context);

  for (int i = 0; i < kServerDefaultResponseStreamsToSend; ++i) {
    request.set_message(msg + std::to_string(i));
    EXPECT_TRUE(stream->Write(request));
    EXPECT_TRUE(stream->Read(&response));
    EXPECT_EQ(response.message(), request.message());
  }

  stream->WritesDone();
  EXPECT_FALSE(stream->Read(&response));
  EXPECT_FALSE(stream->Read(&response));

  Status s = stream->Finish();
  EXPECT_TRUE(s.ok());
}

TEST_P(End2endTest, BidiStreamWithCoalescingApi) {
  ResetStub();
  EchoRequest request;
  EchoResponse response;
  ClientContext context;
  context.AddMetadata(kServerFinishAfterNReads, "3");
  context.set_initial_metadata_corked(true);
  std::string msg("hello");

  auto stream = stub_->BidiStream(&context);

  request.set_message(msg + "0");
  EXPECT_TRUE(stream->Write(request));
  EXPECT_TRUE(stream->Read(&response));
  EXPECT_EQ(response.message(), request.message());

  request.set_message(msg + "1");
  EXPECT_TRUE(stream->Write(request));
  EXPECT_TRUE(stream->Read(&response));
  EXPECT_EQ(response.message(), request.message());

  request.set_message(msg + "2");
  stream->WriteLast(request, WriteOptions());
  EXPECT_TRUE(stream->Read(&response));
  EXPECT_EQ(response.message(), request.message());

  EXPECT_FALSE(stream->Read(&response));
  EXPECT_FALSE(stream->Read(&response));

  Status s = stream->Finish();
  EXPECT_TRUE(s.ok());
}

TEST_P(End2endTest, BidiStreamWithEverythingCoalesced) {
  ResetStub();
  EchoRequest request;
  EchoResponse response;
  ClientContext context;
  context.AddMetadata(kServerFinishAfterNReads, "1");
  context.set_initial_metadata_corked(true);
  std::string msg("hello");

  auto stream = stub_->BidiStream(&context);

  request.set_message(msg + "0");
  stream->WriteLast(request, WriteOptions());
  EXPECT_TRUE(stream->Read(&response));
  EXPECT_EQ(response.message(), request.message());

  EXPECT_FALSE(stream->Read(&response));
  EXPECT_FALSE(stream->Read(&response));

  Status s = stream->Finish();
  EXPECT_TRUE(s.ok());
}

TEST_P(End2endTest, DiffPackageServices) {
  ResetStub();
  EchoRequest request;
  EchoResponse response;
  request.set_message("Hello");

  ClientContext context;
  Status s = stub_->Echo(&context, request, &response);
  EXPECT_EQ(response.message(), request.message());
  EXPECT_TRUE(s.ok());

  std::unique_ptr<grpc::testing::duplicate::EchoTestService::Stub> dup_pkg_stub(
      grpc::testing::duplicate::EchoTestService::NewStub(channel_));
  ClientContext context2;
  s = dup_pkg_stub->Echo(&context2, request, &response);
  EXPECT_EQ("no package", response.message());
  EXPECT_TRUE(s.ok());
}

template <class ServiceType>
void CancelRpc(ClientContext* context, int delay_us, ServiceType* service) {
  gpr_sleep_until(gpr_time_add(gpr_now(GPR_CLOCK_REALTIME),
                               gpr_time_from_micros(delay_us, GPR_TIMESPAN)));
  while (!service->signal_client()) {
  }
  context->TryCancel();
}

TEST_P(End2endTest, CancelRpcBeforeStart) {
  ResetStub();
  EchoRequest request;
  EchoResponse response;
  ClientContext context;
  request.set_message("hello");
  context.TryCancel();
  Status s = stub_->Echo(&context, request, &response);
  EXPECT_EQ("", response.message());
  EXPECT_EQ(grpc::StatusCode::CANCELLED, s.error_code());
  if (GetParam().use_interceptors()) {
    EXPECT_EQ(20, PhonyInterceptor::GetNumTimesCancel());
  }
}

TEST_P(End2endTest, CancelRpcAfterStart) {
  for (int i = 0; i < 10; i++) {
    ResetStub();
    EchoRequest request;
    EchoResponse response;
    ClientContext context;
    request.set_message("hello");
    request.mutable_param()->set_server_notify_client_when_started(true);
    request.mutable_param()->set_skip_cancelled_check(true);
    Status s;
    std::thread echo_thread([this, &s, &context, &request, &response] {
      s = stub_->Echo(&context, request, &response);
    });
    if (!GetParam().callback_server()) {
      EXPECT_EQ(service_.ClientWaitUntilNRpcsStarted(1), 1);
    } else {
      EXPECT_EQ(callback_service_.ClientWaitUntilNRpcsStarted(1), 1);
    }

    context.TryCancel();

    if (!GetParam().callback_server()) {
      service_.SignalServerToContinue();
    } else {
      callback_service_.SignalServerToContinue();
    }

    echo_thread.join();

    if (s.ok()) continue;
    EXPECT_EQ("", response.message());
    EXPECT_EQ(grpc::StatusCode::CANCELLED, s.error_code());
    if (GetParam().use_interceptors()) {
      EXPECT_EQ(20, PhonyInterceptor::GetNumTimesCancel());
    }
    return;
  }
  GTEST_FAIL() << "Failed to get cancellation";
}

TEST_P(End2endTest, ClientCancelsRequestStream) {
  ResetStub();
  EchoRequest request;
  EchoResponse response;
  ClientContext context;
  request.set_message("hello");

  auto stream = stub_->RequestStream(&context, &response);
  EXPECT_TRUE(stream->Write(request));
  EXPECT_TRUE(stream->Write(request));

  context.TryCancel();

  Status s = stream->Finish();
  EXPECT_EQ(grpc::StatusCode::CANCELLED, s.error_code());

  EXPECT_EQ(response.message(), "");
  if (GetParam().use_interceptors()) {
    EXPECT_EQ(20, PhonyInterceptor::GetNumTimesCancel());
  }
}

TEST_P(End2endTest, ClientCancelsResponseStream) {
  ResetStub();
  EchoRequest request;
  EchoResponse response;
  ClientContext context;
  request.set_message("hello");

  auto stream = stub_->ResponseStream(&context, request);

  EXPECT_TRUE(stream->Read(&response));
  EXPECT_EQ(response.message(), request.message() + "0");
  EXPECT_TRUE(stream->Read(&response));
  EXPECT_EQ(response.message(), request.message() + "1");

  context.TryCancel();

  if (stream->Read(&response)) {
    EXPECT_EQ(response.message(), request.message() + "2");

    EXPECT_FALSE(stream->Read(&response));
  }

  Status s = stream->Finish();

  EXPECT_GE(grpc::StatusCode::CANCELLED, s.error_code());
  if (GetParam().use_interceptors()) {
    EXPECT_EQ(20, PhonyInterceptor::GetNumTimesCancel());
  }
}

TEST_P(End2endTest, ClientCancelsBidi) {
  ResetStub();
  EchoRequest request;
  EchoResponse response;
  ClientContext context;
  std::string msg("hello");

  context.AddMetadata(kClientTryCancelRequest, std::to_string(1));

  auto stream = stub_->BidiStream(&context);

  request.set_message(msg + "0");
  EXPECT_TRUE(stream->Write(request));
  EXPECT_TRUE(stream->Read(&response));
  EXPECT_EQ(response.message(), request.message());

  request.set_message(msg + "1");
  EXPECT_TRUE(stream->Write(request));

  context.TryCancel();

  if (stream->Read(&response)) {
    EXPECT_EQ(response.message(), request.message());

    EXPECT_FALSE(stream->Read(&response));
  }

  Status s = stream->Finish();
  EXPECT_EQ(grpc::StatusCode::CANCELLED, s.error_code());
  if (GetParam().use_interceptors()) {
    EXPECT_EQ(20, PhonyInterceptor::GetNumTimesCancel());
  }
}

TEST_P(End2endTest, RpcMaxMessageSize) {
  ResetStub();
  EchoRequest request;
  EchoResponse response;
  request.set_message(string(kMaxMessageSize_ * 2, 'a'));
  request.mutable_param()->set_server_die(true);

  ClientContext context;
  Status s = stub_->Echo(&context, request, &response);
  EXPECT_FALSE(s.ok());
}

void ReaderThreadFunc(ClientReaderWriter<EchoRequest, EchoResponse>* stream,
                      gpr_event* ev) {
  EchoResponse resp;
  gpr_event_set(ev, reinterpret_cast<void*>(1));
  while (stream->Read(&resp)) {
    LOG(INFO) << "Read message";
  }
}

TEST_P(End2endTest, SimultaneousReadWritesDone) {
  ResetStub();
  ClientContext context;
  gpr_event ev;
  gpr_event_init(&ev);
  auto stream = stub_->BidiStream(&context);
  std::thread reader_thread(ReaderThreadFunc, stream.get(), &ev);
  gpr_event_wait(&ev, gpr_inf_future(GPR_CLOCK_REALTIME));
  stream->WritesDone();
  reader_thread.join();
  Status s = stream->Finish();
  EXPECT_TRUE(s.ok());
}

TEST_P(End2endTest, ChannelState) {
  if (GetParam().inproc()) {
    return;
  }

  ResetStub();

  EXPECT_EQ(GRPC_CHANNEL_IDLE, channel_->GetState(false));

  CompletionQueue cq;
  std::chrono::system_clock::time_point deadline =
      std::chrono::system_clock::now() + std::chrono::milliseconds(10);
  channel_->NotifyOnStateChange(GRPC_CHANNEL_IDLE, deadline, &cq, nullptr);
  void* tag;
  bool ok = true;
  cq.Next(&tag, &ok);
  EXPECT_FALSE(ok);

  EXPECT_EQ(GRPC_CHANNEL_IDLE, channel_->GetState(true));
  EXPECT_TRUE(channel_->WaitForStateChange(GRPC_CHANNEL_IDLE,
                                           gpr_inf_future(GPR_CLOCK_REALTIME)));
  auto state = channel_->GetState(false);
  EXPECT_TRUE(state == GRPC_CHANNEL_CONNECTING || state == GRPC_CHANNEL_READY);
}

TEST_P(End2endTest, ChannelStateTimeout) {
  if ((GetParam().credentials_type() != kInsecureCredentialsType) ||
      GetParam().inproc()) {
    return;
  }
  int port = grpc_pick_unused_port_or_die();
  std::ostringstream server_address;
  server_address << "localhost:" << port;

  auto channel =
      grpc::CreateChannel(server_address.str(), InsecureChannelCredentials());

  EXPECT_EQ(GRPC_CHANNEL_IDLE, channel->GetState(true));

  auto state = GRPC_CHANNEL_IDLE;
  for (int i = 0; i < 10; i++) {
    channel->WaitForStateChange(
        state, std::chrono::system_clock::now() + std::chrono::seconds(1));
    state = channel->GetState(false);
  }
}

TEST_P(End2endTest, ChannelStateOnLameChannel) {
  if ((GetParam().credentials_type() != kInsecureCredentialsType) ||
      GetParam().inproc()) {
    return;
  }

  auto channel = grpc::CreateChannel("dns:///", InsecureChannelCredentials());

  EXPECT_EQ(GRPC_CHANNEL_TRANSIENT_FAILURE, channel->GetState(true));

  auto state = GRPC_CHANNEL_TRANSIENT_FAILURE;
  for (int i = 0; i < 10; ++i) {
    channel->WaitForStateChange(
        state, std::chrono::system_clock::now() + std::chrono::seconds(1));
    state = channel->GetState(false);
  }
}

TEST_P(End2endTest, NonExistingService) {
  ResetChannel();
  std::unique_ptr<grpc::testing::UnimplementedEchoService::Stub> stub;
  stub = grpc::testing::UnimplementedEchoService::NewStub(channel_);

  EchoRequest request;
  EchoResponse response;
  request.set_message("Hello");

  ClientContext context;
  Status s = stub->Unimplemented(&context, request, &response);
  EXPECT_EQ(StatusCode::UNIMPLEMENTED, s.error_code());
  EXPECT_EQ("", s.error_message());
}

TEST_P(End2endTest, BinaryTrailerTest) {
  ResetStub();
  EchoRequest request;
  EchoResponse response;
  ClientContext context;

  request.mutable_param()->set_echo_metadata(true);
  DebugInfo* info = request.mutable_param()->mutable_debug_info();
  info->add_stack_entries("stack_entry_1");
  info->add_stack_entries("stack_entry_2");
  info->add_stack_entries("stack_entry_3");
  info->set_detail("detailed debug info");
  std::string expected_string = info->SerializeAsString();
  request.set_message("Hello");

  Status s = stub_->Echo(&context, request, &response);
  EXPECT_FALSE(s.ok());
  auto trailers = context.GetServerTrailingMetadata();
  EXPECT_EQ(1u, trailers.count(kDebugInfoTrailerKey));
  auto iter = trailers.find(kDebugInfoTrailerKey);
  EXPECT_EQ(expected_string, iter->second);

  DebugInfo returned_info;
  EXPECT_TRUE(returned_info.ParseFromString(ToString(iter->second)));
}

TEST_P(End2endTest, ExpectErrorTest) {
  ResetStub();

  std::vector<ErrorStatus> expected_status;
  expected_status.emplace_back();
  expected_status.back().set_code(13);

  expected_status.emplace_back();
  expected_status.back().set_code(13);
  expected_status.back().set_error_message("text error message");
  expected_status.back().set_binary_error_details("text error details");

  expected_status.emplace_back();
  expected_status.back().set_code(13);
  expected_status.back().set_error_message("text error message");
  expected_status.back().set_binary_error_details(
      "\x0\x1\x2\x3\x4\x5\x6\x8\x9\xA\xB");

  for (auto iter = expected_status.begin(); iter != expected_status.end();
       ++iter) {
    EchoRequest request;
    EchoResponse response;
    ClientContext context;
    request.set_message("Hello");
    auto* error = request.mutable_param()->mutable_expected_error();
    error->set_code(iter->code());
    error->set_error_message(iter->error_message());
    error->set_binary_error_details(iter->binary_error_details());

    Status s = stub_->Echo(&context, request, &response);
    EXPECT_FALSE(s.ok());
    EXPECT_EQ(iter->code(), s.error_code());
    EXPECT_EQ(iter->error_message(), s.error_message());
    EXPECT_EQ(iter->binary_error_details(), s.error_details());
    if (grpc_core::IsErrorFlattenEnabled()) {
      EXPECT_THAT(context.debug_error_string(),
                  ::testing::HasSubstr("INTERNAL"));
    } else {
      EXPECT_TRUE(absl::StrContains(context.debug_error_string(), "status"));
      EXPECT_TRUE(absl::StrContains(context.debug_error_string(), "13"));
    }
  }
}

class ProxyEnd2endTest : public End2endTest {
 protected:
};

TEST_P(ProxyEnd2endTest, SimpleRpc) {
  ResetStub();
  SendRpc(stub_.get(), 1, false);
}

TEST_P(ProxyEnd2endTest, SimpleRpcWithEmptyMessages) {
  ResetStub();
  EchoRequest request;
  EchoResponse response;

  ClientContext context;
  Status s = stub_->Echo(&context, request, &response);
  EXPECT_TRUE(s.ok());
}

TEST_P(ProxyEnd2endTest, MultipleRpcs) {
  ResetStub();
  std::vector<std::thread> threads;
  threads.reserve(10);
  for (int i = 0; i < 10; ++i) {
    threads.emplace_back(SendRpc, stub_.get(), 10, false);
  }
  for (int i = 0; i < 10; ++i) {
    threads[i].join();
  }
}

TEST_P(ProxyEnd2endTest, RpcDeadlineExpires) {
  ResetStub();
  EchoRequest request;
  EchoResponse response;
  request.set_message("Hello");
  request.mutable_param()->set_skip_cancelled_check(true);

  request.mutable_param()->set_server_sleep_us(4 * 1000 * 1000);

  ClientContext context;
  std::chrono::system_clock::time_point deadline =
      std::chrono::system_clock::now() + std::chrono::milliseconds(1);
  context.set_deadline(deadline);
  Status s = stub_->Echo(&context, request, &response);
  EXPECT_EQ(StatusCode::DEADLINE_EXCEEDED, s.error_code());
}

TEST_P(ProxyEnd2endTest, RpcLongDeadline) {
  ResetStub();
  EchoRequest request;
  EchoResponse response;
  request.set_message("Hello");

  ClientContext context;
  std::chrono::system_clock::time_point deadline =
      std::chrono::system_clock::now() + std::chrono::hours(1);
  context.set_deadline(deadline);
  Status s = stub_->Echo(&context, request, &response);
  EXPECT_EQ(response.message(), request.message());
  EXPECT_TRUE(s.ok());
}

TEST_P(ProxyEnd2endTest, EchoDeadline) {
  ResetStub();
  EchoRequest request;
  EchoResponse response;
  request.set_message("Hello");
  request.mutable_param()->set_echo_deadline(true);

  ClientContext context;
  std::chrono::system_clock::time_point deadline =
      std::chrono::system_clock::now() + std::chrono::seconds(100);
  context.set_deadline(deadline);
  Status s = stub_->Echo(&context, request, &response);
  EXPECT_EQ(response.message(), request.message());
  EXPECT_TRUE(s.ok());
  gpr_timespec sent_deadline;
  Timepoint2Timespec(deadline, &sent_deadline);

  EXPECT_LE(response.param().request_deadline() - sent_deadline.tv_sec, 2);
  EXPECT_GE(response.param().request_deadline() - sent_deadline.tv_sec, -1);
}

TEST_P(ProxyEnd2endTest, EchoDeadlineForNoDeadlineRpc) {
  ResetStub();
  EchoRequest request;
  EchoResponse response;
  request.set_message("Hello");
  request.mutable_param()->set_echo_deadline(true);

  ClientContext context;
  Status s = stub_->Echo(&context, request, &response);
  EXPECT_EQ(response.message(), request.message());
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(response.param().request_deadline(),
            gpr_inf_future(GPR_CLOCK_REALTIME).tv_sec);
}

TEST_P(ProxyEnd2endTest, UnimplementedRpc) {
  ResetStub();
  EchoRequest request;
  EchoResponse response;
  request.set_message("Hello");

  ClientContext context;
  Status s = stub_->Unimplemented(&context, request, &response);
  EXPECT_FALSE(s.ok());
  EXPECT_EQ(s.error_code(), grpc::StatusCode::UNIMPLEMENTED);
  EXPECT_EQ(s.error_message(), "");
  EXPECT_EQ(response.message(), "");
}

TEST_P(ProxyEnd2endTest, ClientCancelsRpc) {
  ResetStub();
  EchoRequest request;
  EchoResponse response;
  request.set_message("Hello");
  const int kCancelDelayUs = 10 * 1000;
  request.mutable_param()->set_client_cancel_after_us(kCancelDelayUs);

  ClientContext context;
  std::thread cancel_thread;
  if (!GetParam().callback_server()) {
    cancel_thread = std::thread(
        [&context, this](int delay) { CancelRpc(&context, delay, &service_); },
        kCancelDelayUs);
    // Note: the unusual pattern above (and below) is caused by a conflict

  } else {
    cancel_thread = std::thread(
        [&context, this](int delay) {
          CancelRpc(&context, delay, &callback_service_);
        },
        kCancelDelayUs);
  }
  Status s = stub_->Echo(&context, request, &response);
  cancel_thread.join();
  EXPECT_EQ(StatusCode::CANCELLED, s.error_code());
  EXPECT_THAT(s.error_message(), ::testing::HasSubstr("CANCELLED"));
}

TEST_P(ProxyEnd2endTest, ServerCancelsRpc) {
  ResetStub();
  EchoRequest request;
  EchoResponse response;
  request.set_message("Hello");
  request.mutable_param()->set_server_cancel_after_us(1000);

  ClientContext context;
  Status s = stub_->Echo(&context, request, &response);
  EXPECT_EQ(StatusCode::CANCELLED, s.error_code());
  EXPECT_EQ(s.error_message(), "");
}

TEST_P(ProxyEnd2endTest, HugeResponse) {
  ResetStub();
  EchoRequest request;
  EchoResponse response;
  request.set_message("huge response");
  const size_t kResponseSize = 1024 * (1024 + 10);
  request.mutable_param()->set_response_message_length(kResponseSize);

  ClientContext context;
  std::chrono::system_clock::time_point deadline =
      std::chrono::system_clock::now() + std::chrono::seconds(20);
  context.set_deadline(deadline);
  Status s = stub_->Echo(&context, request, &response);
  EXPECT_EQ(kResponseSize, response.message().size());
  EXPECT_TRUE(s.ok());
}

TEST_P(ProxyEnd2endTest, Peer) {

  if (GetParam().inproc()) {
    return;
  }
  ResetStub();
  EchoRequest request;
  EchoResponse response;
  request.set_message("hello");
  request.mutable_param()->set_echo_peer(true);

  ClientContext context;
  Status s = stub_->Echo(&context, request, &response);
  EXPECT_EQ(response.message(), request.message());
  EXPECT_TRUE(s.ok());
  EXPECT_TRUE(CheckIsLocalhost(response.param().peer()));
  EXPECT_TRUE(CheckIsLocalhost(context.peer()));
}

class SecureEnd2endTest : public End2endTest {
 protected:
  SecureEnd2endTest() {
    CHECK(!GetParam().use_proxy());
    CHECK(GetParam().credentials_type() != kInsecureCredentialsType);
  }
};

TEST_P(SecureEnd2endTest, SimpleRpcWithHost) {
  ResetStub();

  EchoRequest request;
  EchoResponse response;
  request.set_message("Hello");

  ClientContext context;
  context.set_authority("foo.test.youtube.com");
  Status s = stub_->Echo(&context, request, &response);
  EXPECT_EQ(response.message(), request.message());
  EXPECT_TRUE(response.has_param());
  EXPECT_EQ("special", response.param().host());
  EXPECT_TRUE(s.ok());
}

bool MetadataContains(
    const std::multimap<grpc::string_ref, grpc::string_ref>& metadata,
    const std::string& key, const std::string& value) {
  int count = 0;

  for (std::multimap<grpc::string_ref, grpc::string_ref>::const_iterator iter =
           metadata.begin();
       iter != metadata.end(); ++iter) {
    if (ToString(iter->first) == key && ToString(iter->second) == value) {
      count++;
    }
  }
  return count == 1;
}

TEST_P(SecureEnd2endTest, BlockingAuthMetadataPluginAndProcessorSuccess) {
  auto* processor = new TestAuthMetadataProcessor(true);
  StartServer(std::shared_ptr<AuthMetadataProcessor>(processor));
  ResetStub();
  EchoRequest request;
  EchoResponse response;
  ClientContext context;
  context.set_credentials(processor->GetCompatibleClientCreds());
  request.set_message("Hello");
  request.mutable_param()->set_echo_metadata(true);
  request.mutable_param()->set_expected_client_identity(
      TestAuthMetadataProcessor::kGoodGuy);
  request.mutable_param()->set_expected_transport_security_type(
      GetParam().credentials_type());

  Status s = stub_->Echo(&context, request, &response);
  EXPECT_EQ(request.message(), response.message());
  EXPECT_TRUE(s.ok());

  EXPECT_FALSE(MetadataContains(
      context.GetServerTrailingMetadata(), GRPC_AUTHORIZATION_METADATA_KEY,
      std::string("Bearer ") + TestAuthMetadataProcessor::kGoodGuy));
}

TEST_P(SecureEnd2endTest, BlockingAuthMetadataPluginAndProcessorFailure) {
  auto* processor = new TestAuthMetadataProcessor(true);
  StartServer(std::shared_ptr<AuthMetadataProcessor>(processor));
  ResetStub();
  EchoRequest request;
  EchoResponse response;
  ClientContext context;
  context.set_credentials(processor->GetIncompatibleClientCreds());
  request.set_message("Hello");

  Status s = stub_->Echo(&context, request, &response);
  EXPECT_FALSE(s.ok());
  EXPECT_EQ(s.error_code(), StatusCode::UNAUTHENTICATED);
}

TEST_P(SecureEnd2endTest, SetPerCallCredentials) {
  ResetStub();
  EchoRequest request;
  EchoResponse response;
  ClientContext context;
  std::shared_ptr<CallCredentials> creds =
      GoogleIAMCredentials(kFakeToken, kFakeSelector);
  context.set_credentials(creds);
  request.set_message("Hello");
  request.mutable_param()->set_echo_metadata(true);

  Status s = stub_->Echo(&context, request, &response);
  EXPECT_EQ(request.message(), response.message());
  EXPECT_TRUE(s.ok());
  EXPECT_TRUE(MetadataContains(context.GetServerTrailingMetadata(),
                               GRPC_IAM_AUTHORIZATION_TOKEN_METADATA_KEY,
                               kFakeToken));
  EXPECT_TRUE(MetadataContains(context.GetServerTrailingMetadata(),
                               GRPC_IAM_AUTHORITY_SELECTOR_METADATA_KEY,
                               kFakeSelector));
  EXPECT_EQ(context.credentials()->DebugString(),
            kExpectedFakeCredsDebugString);
}

class CredentialsInterceptor : public experimental::Interceptor {
 public:
  explicit CredentialsInterceptor(experimental::ClientRpcInfo* info)
      : info_(info) {}

  void Intercept(experimental::InterceptorBatchMethods* methods) override {
    if (methods->QueryInterceptionHookPoint(
            experimental::InterceptionHookPoints::PRE_SEND_INITIAL_METADATA)) {
      std::shared_ptr<CallCredentials> creds =
          GoogleIAMCredentials(kFakeToken, kFakeSelector);
      info_->client_context()->set_credentials(creds);
    }
    methods->Proceed();
  }

 private:
  experimental::ClientRpcInfo* info_ = nullptr;
};

class CredentialsInterceptorFactory
    : public experimental::ClientInterceptorFactoryInterface {
  CredentialsInterceptor* CreateClientInterceptor(
      experimental::ClientRpcInfo* info) override {
    return new CredentialsInterceptor(info);
  }
};

TEST_P(SecureEnd2endTest, CallCredentialsInterception) {
  if (!GetParam().use_interceptors()) {
    return;
  }
  std::vector<std::unique_ptr<experimental::ClientInterceptorFactoryInterface>>
      interceptor_creators;
  interceptor_creators.push_back(
      std::make_unique<CredentialsInterceptorFactory>());
  ResetStub(std::move(interceptor_creators));
  EchoRequest request;
  EchoResponse response;
  ClientContext context;

  request.set_message("Hello");
  request.mutable_param()->set_echo_metadata(true);

  Status s = stub_->Echo(&context, request, &response);
  EXPECT_EQ(request.message(), response.message());
  EXPECT_TRUE(s.ok());
  EXPECT_TRUE(MetadataContains(context.GetServerTrailingMetadata(),
                               GRPC_IAM_AUTHORIZATION_TOKEN_METADATA_KEY,
                               kFakeToken));
  EXPECT_TRUE(MetadataContains(context.GetServerTrailingMetadata(),
                               GRPC_IAM_AUTHORITY_SELECTOR_METADATA_KEY,
                               kFakeSelector));
  EXPECT_EQ(context.credentials()->DebugString(),
            kExpectedFakeCredsDebugString);
}

TEST_P(SecureEnd2endTest, CallCredentialsInterceptionWithSetCredentials) {
  if (!GetParam().use_interceptors()) {
    return;
  }
  std::vector<std::unique_ptr<experimental::ClientInterceptorFactoryInterface>>
      interceptor_creators;
  interceptor_creators.push_back(
      std::make_unique<CredentialsInterceptorFactory>());
  ResetStub(std::move(interceptor_creators));
  EchoRequest request;
  EchoResponse response;
  ClientContext context;
  std::shared_ptr<CallCredentials> creds1 =
      GoogleIAMCredentials(kWrongToken, kWrongSelector);
  context.set_credentials(creds1);
  EXPECT_EQ(context.credentials(), creds1);
  EXPECT_EQ(context.credentials()->DebugString(),
            kExpectedWrongCredsDebugString);
  request.set_message("Hello");
  request.mutable_param()->set_echo_metadata(true);

  Status s = stub_->Echo(&context, request, &response);
  EXPECT_EQ(request.message(), response.message());
  EXPECT_TRUE(s.ok());
  EXPECT_TRUE(MetadataContains(context.GetServerTrailingMetadata(),
                               GRPC_IAM_AUTHORIZATION_TOKEN_METADATA_KEY,
                               kFakeToken));
  EXPECT_TRUE(MetadataContains(context.GetServerTrailingMetadata(),
                               GRPC_IAM_AUTHORITY_SELECTOR_METADATA_KEY,
                               kFakeSelector));
  EXPECT_EQ(context.credentials()->DebugString(),
            kExpectedFakeCredsDebugString);
}

TEST_P(SecureEnd2endTest, OverridePerCallCredentials) {
  ResetStub();
  EchoRequest request;
  EchoResponse response;
  ClientContext context;
  std::shared_ptr<CallCredentials> creds1 =
      GoogleIAMCredentials(kFakeToken1, kFakeSelector1);
  context.set_credentials(creds1);
  EXPECT_EQ(context.credentials(), creds1);
  EXPECT_EQ(context.credentials()->DebugString(),
            kExpectedFakeCreds1DebugString);
  std::shared_ptr<CallCredentials> creds2 =
      GoogleIAMCredentials(kFakeToken2, kFakeSelector2);
  context.set_credentials(creds2);
  EXPECT_EQ(context.credentials(), creds2);
  request.set_message("Hello");
  request.mutable_param()->set_echo_metadata(true);

  Status s = stub_->Echo(&context, request, &response);
  EXPECT_TRUE(MetadataContains(context.GetServerTrailingMetadata(),
                               GRPC_IAM_AUTHORIZATION_TOKEN_METADATA_KEY,
                               kFakeToken2));
  EXPECT_TRUE(MetadataContains(context.GetServerTrailingMetadata(),
                               GRPC_IAM_AUTHORITY_SELECTOR_METADATA_KEY,
                               kFakeSelector2));
  EXPECT_FALSE(MetadataContains(context.GetServerTrailingMetadata(),
                                GRPC_IAM_AUTHORIZATION_TOKEN_METADATA_KEY,
                                kFakeToken1));
  EXPECT_FALSE(MetadataContains(context.GetServerTrailingMetadata(),
                                GRPC_IAM_AUTHORITY_SELECTOR_METADATA_KEY,
                                kFakeSelector1));
  EXPECT_EQ(context.credentials()->DebugString(),
            kExpectedFakeCreds2DebugString);
  EXPECT_EQ(request.message(), response.message());
  EXPECT_TRUE(s.ok());
}

TEST_P(SecureEnd2endTest, AuthMetadataPluginKeyFailure) {
  ResetStub();
  EchoRequest request;
  EchoResponse response;
  ClientContext context;
  context.set_credentials(grpc::MetadataCredentialsFromPlugin(
      std::unique_ptr<MetadataCredentialsPlugin>(
          new TestMetadataCredentialsPlugin(
              TestMetadataCredentialsPlugin::kBadMetadataKey,
              "Does not matter, will fail the key is invalid.", false, true,
              0))));
  request.set_message("Hello");

  Status s = stub_->Echo(&context, request, &response);
  EXPECT_FALSE(s.ok());
  EXPECT_EQ(s.error_code(), StatusCode::UNAVAILABLE);
  EXPECT_EQ(context.credentials()->DebugString(),
            kExpectedAuthMetadataPluginKeyFailureCredsDebugString);
}

TEST_P(SecureEnd2endTest, AuthMetadataPluginValueFailure) {
  ResetStub();
  EchoRequest request;
  EchoResponse response;
  ClientContext context;
  context.set_credentials(grpc::MetadataCredentialsFromPlugin(
      std::unique_ptr<MetadataCredentialsPlugin>(
          new TestMetadataCredentialsPlugin(
              TestMetadataCredentialsPlugin::kGoodMetadataKey,
              "With illegal \n value.", false, true, 0))));
  request.set_message("Hello");

  Status s = stub_->Echo(&context, request, &response);
  EXPECT_FALSE(s.ok());
  EXPECT_EQ(s.error_code(), StatusCode::UNAVAILABLE);
  EXPECT_EQ(context.credentials()->DebugString(),
            kExpectedAuthMetadataPluginValueFailureCredsDebugString);
}

TEST_P(SecureEnd2endTest, AuthMetadataPluginWithDeadline) {
  ResetStub();
  EchoRequest request;
  request.mutable_param()->set_skip_cancelled_check(true);
  EchoResponse response;
  ClientContext context;
  const int delay = 100;
  std::chrono::system_clock::time_point deadline =
      std::chrono::system_clock::now() + std::chrono::milliseconds(delay);
  context.set_deadline(deadline);
  context.set_credentials(grpc::MetadataCredentialsFromPlugin(
      std::unique_ptr<MetadataCredentialsPlugin>(
          new TestMetadataCredentialsPlugin("meta_key", "Does not matter", true,
                                            true, delay))));
  request.set_message("Hello");

  Status s = stub_->Echo(&context, request, &response);
  if (!s.ok()) {
    EXPECT_TRUE(s.error_code() == StatusCode::DEADLINE_EXCEEDED ||
                s.error_code() == StatusCode::UNAVAILABLE);
  }
  EXPECT_EQ(context.credentials()->DebugString(),
            kExpectedAuthMetadataPluginWithDeadlineCredsDebugString);
}

TEST_P(SecureEnd2endTest, AuthMetadataPluginWithCancel) {
  ResetStub();
  EchoRequest request;
  request.mutable_param()->set_skip_cancelled_check(true);
  EchoResponse response;
  ClientContext context;
  const int delay = 100;
  context.set_credentials(grpc::MetadataCredentialsFromPlugin(
      std::unique_ptr<MetadataCredentialsPlugin>(
          new TestMetadataCredentialsPlugin("meta_key", "Does not matter", true,
                                            true, delay))));
  request.set_message("Hello");

  std::thread cancel_thread([&] {
    gpr_sleep_until(gpr_time_add(gpr_now(GPR_CLOCK_REALTIME),
                                 gpr_time_from_millis(delay, GPR_TIMESPAN)));
    context.TryCancel();
  });
  Status s = stub_->Echo(&context, request, &response);
  if (!s.ok()) {
    EXPECT_TRUE(s.error_code() == StatusCode::CANCELLED ||
                s.error_code() == StatusCode::UNAVAILABLE);
  }
  cancel_thread.join();
  EXPECT_EQ(context.credentials()->DebugString(),
            kExpectedAuthMetadataPluginWithDeadlineCredsDebugString);
}

TEST_P(SecureEnd2endTest, NonBlockingAuthMetadataPluginFailure) {
  ResetStub();
  EchoRequest request;
  EchoResponse response;
  ClientContext context;
  context.set_credentials(grpc::MetadataCredentialsFromPlugin(
      std::unique_ptr<MetadataCredentialsPlugin>(
          new TestMetadataCredentialsPlugin(
              TestMetadataCredentialsPlugin::kGoodMetadataKey,
              "Does not matter, will fail anyway (see 3rd param)", false, false,
              0))));
  request.set_message("Hello");

  Status s = stub_->Echo(&context, request, &response);
  EXPECT_FALSE(s.ok());
  EXPECT_EQ(s.error_code(), StatusCode::UNAVAILABLE);
  EXPECT_EQ(s.error_message(),
            std::string("Getting metadata from plugin failed with error: ") +
                kTestCredsPluginErrorMsg);
  EXPECT_EQ(context.credentials()->DebugString(),
            kExpectedNonBlockingAuthMetadataPluginFailureCredsDebugString);
}

TEST_P(SecureEnd2endTest, NonBlockingAuthMetadataPluginAndProcessorSuccess) {
  auto* processor = new TestAuthMetadataProcessor(false);
  StartServer(std::shared_ptr<AuthMetadataProcessor>(processor));
  ResetStub();
  EchoRequest request;
  EchoResponse response;
  ClientContext context;
  context.set_credentials(processor->GetCompatibleClientCreds());
  request.set_message("Hello");
  request.mutable_param()->set_echo_metadata(true);
  request.mutable_param()->set_expected_client_identity(
      TestAuthMetadataProcessor::kGoodGuy);
  request.mutable_param()->set_expected_transport_security_type(
      GetParam().credentials_type());

  Status s = stub_->Echo(&context, request, &response);
  EXPECT_EQ(request.message(), response.message());
  EXPECT_TRUE(s.ok());

  EXPECT_FALSE(MetadataContains(
      context.GetServerTrailingMetadata(), GRPC_AUTHORIZATION_METADATA_KEY,
      std::string("Bearer ") + TestAuthMetadataProcessor::kGoodGuy));
  EXPECT_EQ(
      context.credentials()->DebugString(),
      kExpectedNonBlockingAuthMetadataPluginAndProcessorSuccessCredsDebugString);
}

TEST_P(SecureEnd2endTest, NonBlockingAuthMetadataPluginAndProcessorFailure) {
  auto* processor = new TestAuthMetadataProcessor(false);
  StartServer(std::shared_ptr<AuthMetadataProcessor>(processor));
  ResetStub();
  EchoRequest request;
  EchoResponse response;
  ClientContext context;
  context.set_credentials(processor->GetIncompatibleClientCreds());
  request.set_message("Hello");

  Status s = stub_->Echo(&context, request, &response);
  EXPECT_FALSE(s.ok());
  EXPECT_EQ(s.error_code(), StatusCode::UNAUTHENTICATED);
  EXPECT_EQ(
      context.credentials()->DebugString(),
      kExpectedNonBlockingAuthMetadataPluginAndProcessorFailureCredsDebugString);
}

TEST_P(SecureEnd2endTest, BlockingAuthMetadataPluginFailure) {
  ResetStub();
  EchoRequest request;
  EchoResponse response;
  ClientContext context;
  context.set_credentials(grpc::MetadataCredentialsFromPlugin(
      std::unique_ptr<MetadataCredentialsPlugin>(
          new TestMetadataCredentialsPlugin(
              TestMetadataCredentialsPlugin::kGoodMetadataKey,
              "Does not matter, will fail anyway (see 3rd param)", true, false,
              0))));
  request.set_message("Hello");

  Status s = stub_->Echo(&context, request, &response);
  EXPECT_FALSE(s.ok());
  EXPECT_EQ(s.error_code(), StatusCode::UNAVAILABLE);
  EXPECT_EQ(s.error_message(),
            std::string("Getting metadata from plugin failed with error: ") +
                kTestCredsPluginErrorMsg);
  EXPECT_EQ(context.credentials()->DebugString(),
            kExpectedBlockingAuthMetadataPluginFailureCredsDebugString);
}

TEST_P(SecureEnd2endTest, CompositeCallCreds) {
  ResetStub();
  EchoRequest request;
  EchoResponse response;
  ClientContext context;
  const char kMetadataKey1[] = "call-creds-key1";
  const char kMetadataKey2[] = "call-creds-key2";
  const char kMetadataVal1[] = "call-creds-val1";
  const char kMetadataVal2[] = "call-creds-val2";

  context.set_credentials(grpc::CompositeCallCredentials(
      grpc::MetadataCredentialsFromPlugin(
          std::unique_ptr<MetadataCredentialsPlugin>(
              new TestMetadataCredentialsPlugin(kMetadataKey1, kMetadataVal1,
                                                true, true, 0))),
      grpc::MetadataCredentialsFromPlugin(
          std::unique_ptr<MetadataCredentialsPlugin>(
              new TestMetadataCredentialsPlugin(kMetadataKey2, kMetadataVal2,
                                                true, true, 0)))));
  request.set_message("Hello");
  request.mutable_param()->set_echo_metadata(true);

  Status s = stub_->Echo(&context, request, &response);
  EXPECT_TRUE(s.ok());
  EXPECT_TRUE(MetadataContains(context.GetServerTrailingMetadata(),
                               kMetadataKey1, kMetadataVal1));
  EXPECT_TRUE(MetadataContains(context.GetServerTrailingMetadata(),
                               kMetadataKey2, kMetadataVal2));
  EXPECT_EQ(context.credentials()->DebugString(),
            kExpectedCompositeCallCredsDebugString);
}

TEST_P(SecureEnd2endTest, ClientAuthContext) {
  ResetStub();
  EchoRequest request;
  EchoResponse response;
  request.set_message("Hello");
  request.mutable_param()->set_check_auth_context(
      GetParam().credentials_type() == kTlsCredentialsType);
  request.mutable_param()->set_expected_transport_security_type(
      GetParam().credentials_type());
  ClientContext context;
  Status s = stub_->Echo(&context, request, &response);
  EXPECT_EQ(response.message(), request.message());
  EXPECT_TRUE(s.ok());

  std::shared_ptr<const AuthContext> auth_ctx = context.auth_context();
  std::vector<grpc::string_ref> tst =
      auth_ctx->FindPropertyValues("transport_security_type");
  ASSERT_EQ(1u, tst.size());
  EXPECT_EQ(GetParam().credentials_type(), ToString(tst[0]));
  if (GetParam().credentials_type() == kTlsCredentialsType) {
    EXPECT_EQ("x509_subject_alternative_name",
              auth_ctx->GetPeerIdentityPropertyName());
    EXPECT_EQ(4u, auth_ctx->GetPeerIdentity().size());
    EXPECT_EQ("*.test.google.fr", ToString(auth_ctx->GetPeerIdentity()[0]));
    EXPECT_EQ("waterzooi.test.google.be",
              ToString(auth_ctx->GetPeerIdentity()[1]));
    EXPECT_EQ("*.test.youtube.com", ToString(auth_ctx->GetPeerIdentity()[2]));
    EXPECT_EQ("192.168.1.3", ToString(auth_ctx->GetPeerIdentity()[3]));
  }
}

class ResourceQuotaEnd2endTest : public End2endTest {
 public:
  ResourceQuotaEnd2endTest()
      : server_resource_quota_("server_resource_quota") {}

  void ConfigureServerBuilder(ServerBuilder* builder) override {
    builder->SetResourceQuota(server_resource_quota_);
  }

 private:
  ResourceQuota server_resource_quota_;
};

TEST_P(ResourceQuotaEnd2endTest, SimpleRequest) {
  ResetStub();

  EchoRequest request;
  EchoResponse response;
  request.set_message("Hello");

  ClientContext context;
  Status s = stub_->Echo(&context, request, &response);
  EXPECT_EQ(response.message(), request.message());
  EXPECT_TRUE(s.ok());
}

std::vector<TestScenario> CreateTestScenarios(bool use_proxy,
                                              bool test_insecure,
                                              bool test_secure,
                                              bool test_inproc,
                                              bool test_callback_server) {
  std::vector<TestScenario> scenarios;
  std::vector<std::string> credentials_types;

  grpc_core::ConfigVars::Overrides overrides;
  overrides.client_channel_backup_poll_interval_ms =
      kClientChannelBackupPollIntervalMs;
  grpc_core::ConfigVars::SetOverrides(overrides);
#if TARGET_OS_IPHONE

  grpc_core::SetEnv("grpc_cfstream", "0");
#endif

  if (test_secure) {
    credentials_types =
        GetCredentialsProvider()->GetSecureCredentialsTypeList();
  }
  auto insec_ok = [] {

    return GetCredentialsProvider()->GetChannelCredentials(
               kInsecureCredentialsType, nullptr) != nullptr;
  };
  if (test_insecure && insec_ok()) {
    credentials_types.push_back(kInsecureCredentialsType);
  }

  CHECK(!credentials_types.empty());
  for (const auto& cred : credentials_types) {
    scenarios.emplace_back(false, false, false, cred, false);
    scenarios.emplace_back(true, false, false, cred, false);
    if (test_callback_server) {

      scenarios.emplace_back(false, false, false, cred, true);
      scenarios.emplace_back(true, false, false, cred, true);
    }
    if (use_proxy) {
      scenarios.emplace_back(false, true, false, cred, false);
      scenarios.emplace_back(true, true, false, cred, false);
    }
  }
  if (test_inproc && insec_ok()) {
    scenarios.emplace_back(false, false, true, kInsecureCredentialsType, false);
    scenarios.emplace_back(true, false, true, kInsecureCredentialsType, false);
    if (test_callback_server) {
      scenarios.emplace_back(false, false, true, kInsecureCredentialsType,
                             true);
      scenarios.emplace_back(true, false, true, kInsecureCredentialsType, true);
    }
  }
  return scenarios;
}

INSTANTIATE_TEST_SUITE_P(
    End2end, End2endTest,
    ::testing::ValuesIn(CreateTestScenarios(false, true, true, true, true)),
    &TestScenario::Name);

INSTANTIATE_TEST_SUITE_P(
    End2endServerTryCancel, End2endServerTryCancelTest,
    ::testing::ValuesIn(CreateTestScenarios(false, true, true, true, true)),
    &TestScenario::Name);

INSTANTIATE_TEST_SUITE_P(
    ProxyEnd2end, ProxyEnd2endTest,
    ::testing::ValuesIn(CreateTestScenarios(true, true, true, true, true)),
    &TestScenario::Name);

INSTANTIATE_TEST_SUITE_P(
    SecureEnd2end, SecureEnd2endTest,
    ::testing::ValuesIn(CreateTestScenarios(false, false, true, false, true)),
    &TestScenario::Name);

INSTANTIATE_TEST_SUITE_P(
    ResourceQuotaEnd2end, ResourceQuotaEnd2endTest,
    ::testing::ValuesIn(CreateTestScenarios(false, true, true, true, true)),
    &TestScenario::Name);

}
}
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  int ret = RUN_ALL_TESTS();
  return ret;
}
