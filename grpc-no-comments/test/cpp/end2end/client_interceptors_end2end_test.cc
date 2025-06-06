
// Copyright 2018 gRPC authors.

#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/create_channel_posix.h>
#include <grpcpp/generic/generic_stub.h>
#include <grpcpp/impl/proto_utils.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>
#include <grpcpp/server_posix.h>
#include <grpcpp/support/client_interceptor.h>

#include <memory>
#include <vector>

#include "absl/log/check.h"
#include "absl/memory/memory.h"
#include "gtest/gtest.h"
#include "src/core/lib/iomgr/port.h"
#include "src/proto/grpc/testing/echo.grpc.pb.h"
#include "test/core/test_util/port.h"
#include "test/core/test_util/test_config.h"
#include "test/cpp/end2end/interceptors_util.h"
#include "test/cpp/end2end/test_service_impl.h"
#include "test/cpp/util/byte_buffer_proto_helper.h"
#include "test/cpp/util/string_ref_helper.h"

#ifdef GRPC_POSIX_SOCKET
#include <fcntl.h>

#include "src/core/lib/iomgr/socket_utils_posix.h"
#endif

namespace grpc {
namespace testing {
namespace {

enum class RPCType {
  kSyncUnary,
  kSyncClientStreaming,
  kSyncServerStreaming,
  kSyncBidiStreaming,
  kAsyncCQUnary,
  kAsyncCQClientStreaming,
  kAsyncCQServerStreaming,
  kAsyncCQBidiStreaming,
};

enum class ChannelType {
  kHttpChannel,
  kFdChannel,
};

class HijackingInterceptor : public experimental::Interceptor {
 public:
  explicit HijackingInterceptor(experimental::ClientRpcInfo* info) {
    info_ = info;

    EXPECT_EQ(strcmp("/grpc.testing.EchoTestService/Echo", info->method()), 0);
    EXPECT_EQ(info->suffix_for_stats(), nullptr);
    EXPECT_EQ(info->type(), experimental::ClientRpcInfo::Type::UNARY);
  }

  void Intercept(experimental::InterceptorBatchMethods* methods) override {
    bool hijack = false;
    if (methods->QueryInterceptionHookPoint(
            experimental::InterceptionHookPoints::PRE_SEND_INITIAL_METADATA)) {
      auto* map = methods->GetSendInitialMetadata();

      ASSERT_EQ(map->size(), 1);
      auto iterator = map->begin();
      EXPECT_EQ("testkey", iterator->first);
      EXPECT_EQ("testvalue", iterator->second);
      hijack = true;
    }
    if (methods->QueryInterceptionHookPoint(
            experimental::InterceptionHookPoints::PRE_SEND_MESSAGE)) {
      EchoRequest req;
      auto* buffer = methods->GetSerializedSendMessage();
      auto copied_buffer = *buffer;
      EXPECT_TRUE(
          SerializationTraits<EchoRequest>::Deserialize(&copied_buffer, &req)
              .ok());
      EXPECT_EQ(req.message(), "Hello");
    }
    if (methods->QueryInterceptionHookPoint(
            experimental::InterceptionHookPoints::PRE_SEND_CLOSE)) {

    }
    if (methods->QueryInterceptionHookPoint(
            experimental::InterceptionHookPoints::POST_RECV_INITIAL_METADATA)) {
      auto* map = methods->GetRecvInitialMetadata();

      EXPECT_EQ(map->size(), 0);
    }
    if (methods->QueryInterceptionHookPoint(
            experimental::InterceptionHookPoints::POST_RECV_MESSAGE)) {
      EchoResponse* resp =
          static_cast<EchoResponse*>(methods->GetRecvMessage());

      EXPECT_EQ(resp->message(), "Hello1");
      resp->set_message("Hello");
    }
    if (methods->QueryInterceptionHookPoint(
            experimental::InterceptionHookPoints::POST_RECV_STATUS)) {
      auto* map = methods->GetRecvTrailingMetadata();
      bool found = false;

      for (const auto& [key, value] : *map) {
        found = key.starts_with("testkey") && value.starts_with("testvalue");
        if (found) break;
      }
      EXPECT_EQ(found, true);
      auto* status = methods->GetRecvStatus();
      EXPECT_EQ(status->ok(), true);
    }
    if (methods->QueryInterceptionHookPoint(
            experimental::InterceptionHookPoints::PRE_RECV_INITIAL_METADATA)) {
      auto* map = methods->GetRecvInitialMetadata();

      EXPECT_EQ(map->size(), 0);
    }
    if (methods->QueryInterceptionHookPoint(
            experimental::InterceptionHookPoints::PRE_RECV_MESSAGE)) {

      EchoResponse* resp =
          static_cast<EchoResponse*>(methods->GetRecvMessage());
      resp->set_message("Hello1");
    }
    if (methods->QueryInterceptionHookPoint(
            experimental::InterceptionHookPoints::PRE_RECV_STATUS)) {
      auto* map = methods->GetRecvTrailingMetadata();

      EXPECT_EQ(map->size(), 0);
      map->insert(std::pair("testkey", "testvalue"));
      auto* status = methods->GetRecvStatus();
      *status = Status(StatusCode::OK, "");
    }
    if (hijack) {
      methods->Hijack();
    } else {
      methods->Proceed();
    }
  }

 private:
  experimental::ClientRpcInfo* info_;
};

class HijackingInterceptorFactory
    : public experimental::ClientInterceptorFactoryInterface {
 public:
  experimental::Interceptor* CreateClientInterceptor(
      experimental::ClientRpcInfo* info) override {
    return new HijackingInterceptor(info);
  }
};

class HijackingInterceptorMakesAnotherCall : public experimental::Interceptor {
 public:
  explicit HijackingInterceptorMakesAnotherCall(
      experimental::ClientRpcInfo* info) {
    info_ = info;

    EXPECT_EQ(strcmp("/grpc.testing.EchoTestService/Echo", info->method()), 0);
    EXPECT_EQ(strcmp("TestSuffixForStats", info->suffix_for_stats()), 0);
  }

  void Intercept(experimental::InterceptorBatchMethods* methods) override {
    if (methods->QueryInterceptionHookPoint(
            experimental::InterceptionHookPoints::PRE_SEND_INITIAL_METADATA)) {
      auto* map = methods->GetSendInitialMetadata();

      ASSERT_EQ(map->size(), 1);
      auto iterator = map->begin();
      EXPECT_EQ("testkey", iterator->first);
      EXPECT_EQ("testvalue", iterator->second);

      metadata_map_ = *map;
    }
    if (methods->QueryInterceptionHookPoint(
            experimental::InterceptionHookPoints::PRE_SEND_MESSAGE)) {
      EchoRequest req;
      auto* buffer = methods->GetSerializedSendMessage();
      auto copied_buffer = *buffer;
      EXPECT_TRUE(
          SerializationTraits<EchoRequest>::Deserialize(&copied_buffer, &req)
              .ok());
      EXPECT_EQ(req.message(), "Hello");
      req_ = req;
      stub_ = grpc::testing::EchoTestService::NewStub(
          methods->GetInterceptedChannel());
      ctx_.AddMetadata(metadata_map_.begin()->first,
                       metadata_map_.begin()->second);
      stub_->async()->Echo(&ctx_, &req_, &resp_, [this, methods](Status s) {
        EXPECT_EQ(s.ok(), true);
        EXPECT_EQ(resp_.message(), "Hello");
        methods->Hijack();
      });

      return;
    }
    if (methods->QueryInterceptionHookPoint(
            experimental::InterceptionHookPoints::PRE_SEND_CLOSE)) {

    }
    if (methods->QueryInterceptionHookPoint(
            experimental::InterceptionHookPoints::POST_RECV_INITIAL_METADATA)) {
      auto* map = methods->GetRecvInitialMetadata();

      EXPECT_EQ(map->size(), 0);
    }
    if (methods->QueryInterceptionHookPoint(
            experimental::InterceptionHookPoints::POST_RECV_MESSAGE)) {
      EchoResponse* resp =
          static_cast<EchoResponse*>(methods->GetRecvMessage());

      EXPECT_EQ(resp->message(), "Hello");
    }
    if (methods->QueryInterceptionHookPoint(
            experimental::InterceptionHookPoints::POST_RECV_STATUS)) {
      auto* map = methods->GetRecvTrailingMetadata();
      bool found = false;

      for (const auto& [key, value] : *map) {
        found = key.starts_with("testkey") && value.starts_with("testvalue");
        if (found) break;
      }
      EXPECT_EQ(found, true);
      auto* status = methods->GetRecvStatus();
      EXPECT_EQ(status->ok(), true);
    }
    if (methods->QueryInterceptionHookPoint(
            experimental::InterceptionHookPoints::PRE_RECV_INITIAL_METADATA)) {
      auto* map = methods->GetRecvInitialMetadata();

      EXPECT_EQ(map->size(), 0);
    }
    if (methods->QueryInterceptionHookPoint(
            experimental::InterceptionHookPoints::PRE_RECV_MESSAGE)) {

      EchoResponse* resp =
          static_cast<EchoResponse*>(methods->GetRecvMessage());
      resp->set_message(resp_.message());
    }
    if (methods->QueryInterceptionHookPoint(
            experimental::InterceptionHookPoints::PRE_RECV_STATUS)) {
      auto* map = methods->GetRecvTrailingMetadata();

      EXPECT_EQ(map->size(), 0);
      map->insert(std::pair("testkey", "testvalue"));
      auto* status = methods->GetRecvStatus();
      *status = Status(StatusCode::OK, "");
    }

    methods->Proceed();
  }

 private:
  experimental::ClientRpcInfo* info_;
  std::multimap<std::string, std::string> metadata_map_;
  ClientContext ctx_;
  EchoRequest req_;
  EchoResponse resp_;
  std::unique_ptr<grpc::testing::EchoTestService::Stub> stub_;
};

class HijackingInterceptorMakesAnotherCallFactory
    : public experimental::ClientInterceptorFactoryInterface {
 public:
  experimental::Interceptor* CreateClientInterceptor(
      experimental::ClientRpcInfo* info) override {
    return new HijackingInterceptorMakesAnotherCall(info);
  }
};

class BidiStreamingRpcHijackingInterceptor : public experimental::Interceptor {
 public:
  explicit BidiStreamingRpcHijackingInterceptor(
      experimental::ClientRpcInfo* info) {
    info_ = info;
    EXPECT_EQ(info->suffix_for_stats(), nullptr);
  }

  void Intercept(experimental::InterceptorBatchMethods* methods) override {
    bool hijack = false;
    if (methods->QueryInterceptionHookPoint(
            experimental::InterceptionHookPoints::PRE_SEND_INITIAL_METADATA)) {
      CheckMetadata(*methods->GetSendInitialMetadata(), "testkey", "testvalue");
      hijack = true;
    }
    if (methods->QueryInterceptionHookPoint(
            experimental::InterceptionHookPoints::PRE_SEND_MESSAGE)) {
      EchoRequest req;
      auto* buffer = methods->GetSerializedSendMessage();
      auto copied_buffer = *buffer;
      EXPECT_TRUE(
          SerializationTraits<EchoRequest>::Deserialize(&copied_buffer, &req)
              .ok());
      EXPECT_EQ(req.message().find("Hello"), 0u);
      msg = req.message();
    }
    if (methods->QueryInterceptionHookPoint(
            experimental::InterceptionHookPoints::PRE_SEND_CLOSE)) {

    }
    if (methods->QueryInterceptionHookPoint(
            experimental::InterceptionHookPoints::POST_RECV_STATUS)) {
      CheckMetadata(*methods->GetRecvTrailingMetadata(), "testkey",
                    "testvalue");
      auto* status = methods->GetRecvStatus();
      EXPECT_EQ(status->ok(), true);
    }
    if (methods->QueryInterceptionHookPoint(
            experimental::InterceptionHookPoints::PRE_RECV_MESSAGE)) {
      EchoResponse* resp =
          static_cast<EchoResponse*>(methods->GetRecvMessage());
      resp->set_message(msg);
    }
    if (methods->QueryInterceptionHookPoint(
            experimental::InterceptionHookPoints::POST_RECV_MESSAGE)) {
      EXPECT_EQ(static_cast<EchoResponse*>(methods->GetRecvMessage())
                    ->message()
                    .find("Hello"),
                0u);
    }
    if (methods->QueryInterceptionHookPoint(
            experimental::InterceptionHookPoints::PRE_RECV_STATUS)) {
      auto* map = methods->GetRecvTrailingMetadata();

      EXPECT_EQ(map->size(), 0);
      map->insert(std::pair("testkey", "testvalue"));
      auto* status = methods->GetRecvStatus();
      *status = Status(StatusCode::OK, "");
    }
    if (hijack) {
      methods->Hijack();
    } else {
      methods->Proceed();
    }
  }

 private:
  experimental::ClientRpcInfo* info_;
  std::string msg;
};

class ClientStreamingRpcHijackingInterceptor
    : public experimental::Interceptor {
 public:
  explicit ClientStreamingRpcHijackingInterceptor(
      experimental::ClientRpcInfo* info) {
    info_ = info;
    EXPECT_EQ(
        strcmp("/grpc.testing.EchoTestService/RequestStream", info->method()),
        0);
    EXPECT_EQ(strcmp("TestSuffixForStats", info->suffix_for_stats()), 0);
  }
  void Intercept(experimental::InterceptorBatchMethods* methods) override {
    bool hijack = false;
    if (methods->QueryInterceptionHookPoint(
            experimental::InterceptionHookPoints::PRE_SEND_INITIAL_METADATA)) {
      hijack = true;
    }
    if (methods->QueryInterceptionHookPoint(
            experimental::InterceptionHookPoints::PRE_SEND_MESSAGE)) {
      if (++count_ > 10) {
        methods->FailHijackedSendMessage();
      }
    }
    if (methods->QueryInterceptionHookPoint(
            experimental::InterceptionHookPoints::POST_SEND_MESSAGE)) {
      EXPECT_FALSE(got_failed_send_);
      got_failed_send_ = !methods->GetSendMessageStatus();
    }
    if (methods->QueryInterceptionHookPoint(
            experimental::InterceptionHookPoints::PRE_RECV_STATUS)) {
      auto* status = methods->GetRecvStatus();
      *status = Status(StatusCode::UNAVAILABLE, "Done sending 10 messages");
    }
    if (hijack) {
      methods->Hijack();
    } else {
      methods->Proceed();
    }
  }

  static bool GotFailedSend() { return got_failed_send_; }

 private:
  experimental::ClientRpcInfo* info_;
  int count_ = 0;
  static bool got_failed_send_;
};

bool ClientStreamingRpcHijackingInterceptor::got_failed_send_ = false;

class ClientStreamingRpcHijackingInterceptorFactory
    : public experimental::ClientInterceptorFactoryInterface {
 public:
  experimental::Interceptor* CreateClientInterceptor(
      experimental::ClientRpcInfo* info) override {
    return new ClientStreamingRpcHijackingInterceptor(info);
  }
};

class ServerStreamingRpcHijackingInterceptor
    : public experimental::Interceptor {
 public:
  explicit ServerStreamingRpcHijackingInterceptor(
      experimental::ClientRpcInfo* info) {
    info_ = info;
    got_failed_message_ = false;
    EXPECT_EQ(info->suffix_for_stats(), nullptr);
  }

  void Intercept(experimental::InterceptorBatchMethods* methods) override {
    bool hijack = false;
    if (methods->QueryInterceptionHookPoint(
            experimental::InterceptionHookPoints::PRE_SEND_INITIAL_METADATA)) {
      auto* map = methods->GetSendInitialMetadata();

      ASSERT_EQ(map->size(), 1);
      auto iterator = map->begin();
      EXPECT_EQ("testkey", iterator->first);
      EXPECT_EQ("testvalue", iterator->second);
      hijack = true;
    }
    if (methods->QueryInterceptionHookPoint(
            experimental::InterceptionHookPoints::PRE_SEND_MESSAGE)) {
      EchoRequest req;
      auto* buffer = methods->GetSerializedSendMessage();
      auto copied_buffer = *buffer;
      EXPECT_TRUE(
          SerializationTraits<EchoRequest>::Deserialize(&copied_buffer, &req)
              .ok());
      EXPECT_EQ(req.message(), "Hello");
    }
    if (methods->QueryInterceptionHookPoint(
            experimental::InterceptionHookPoints::PRE_SEND_CLOSE)) {

    }
    if (methods->QueryInterceptionHookPoint(
            experimental::InterceptionHookPoints::POST_RECV_STATUS)) {
      auto* map = methods->GetRecvTrailingMetadata();
      bool found = false;

      for (const auto& [key, value] : *map) {
        found = key.starts_with("testkey") && value.starts_with("testvalue");
        if (found) break;
      }
      EXPECT_EQ(found, true);
      auto* status = methods->GetRecvStatus();
      EXPECT_EQ(status->ok(), true);
    }
    if (methods->QueryInterceptionHookPoint(
            experimental::InterceptionHookPoints::PRE_RECV_MESSAGE)) {
      if (++count_ > 10) {
        methods->FailHijackedRecvMessage();
      }
      EchoResponse* resp =
          static_cast<EchoResponse*>(methods->GetRecvMessage());
      resp->set_message("Hello");
    }
    if (methods->QueryInterceptionHookPoint(
            experimental::InterceptionHookPoints::POST_RECV_MESSAGE)) {

      EXPECT_FALSE(got_failed_message_);
      got_failed_message_ = methods->GetRecvMessage() == nullptr;
    }
    if (methods->QueryInterceptionHookPoint(
            experimental::InterceptionHookPoints::PRE_RECV_STATUS)) {
      auto* map = methods->GetRecvTrailingMetadata();

      EXPECT_EQ(map->size(), 0);
      map->insert(std::pair("testkey", "testvalue"));
      auto* status = methods->GetRecvStatus();
      *status = Status(StatusCode::OK, "");
    }
    if (hijack) {
      methods->Hijack();
    } else {
      methods->Proceed();
    }
  }

  static bool GotFailedMessage() { return got_failed_message_; }

 private:
  experimental::ClientRpcInfo* info_;
  static bool got_failed_message_;
  int count_ = 0;
};

bool ServerStreamingRpcHijackingInterceptor::got_failed_message_ = false;

class ServerStreamingRpcHijackingInterceptorFactory
    : public experimental::ClientInterceptorFactoryInterface {
 public:
  experimental::Interceptor* CreateClientInterceptor(
      experimental::ClientRpcInfo* info) override {
    return new ServerStreamingRpcHijackingInterceptor(info);
  }
};

class BidiStreamingRpcHijackingInterceptorFactory
    : public experimental::ClientInterceptorFactoryInterface {
 public:
  experimental::Interceptor* CreateClientInterceptor(
      experimental::ClientRpcInfo* info) override {
    return new BidiStreamingRpcHijackingInterceptor(info);
  }
};

class LoggingInterceptor : public experimental::Interceptor {
 public:
  explicit LoggingInterceptor(experimental::ClientRpcInfo* ) {
    pre_send_initial_metadata_ = false;
    pre_send_message_count_ = 0;
    pre_send_close_ = false;
    post_recv_initial_metadata_ = false;
    post_recv_message_count_ = 0;
    post_recv_status_ = false;
  }

  void Intercept(experimental::InterceptorBatchMethods* methods) override {
    if (methods->QueryInterceptionHookPoint(
            experimental::InterceptionHookPoints::PRE_SEND_INITIAL_METADATA)) {
      auto* map = methods->GetSendInitialMetadata();

      ASSERT_EQ(map->size(), 1);
      auto iterator = map->begin();
      EXPECT_EQ("testkey", iterator->first);
      EXPECT_EQ("testvalue", iterator->second);
      ASSERT_FALSE(pre_send_initial_metadata_);
      pre_send_initial_metadata_ = true;
    }
    if (methods->QueryInterceptionHookPoint(
            experimental::InterceptionHookPoints::PRE_SEND_MESSAGE)) {
      EchoRequest req;
      auto* send_msg = methods->GetSendMessage();
      if (send_msg == nullptr) {

        auto* buffer = methods->GetSerializedSendMessage();
        auto copied_buffer = *buffer;
        EchoRequest req;
        EXPECT_TRUE(
            SerializationTraits<EchoRequest>::Deserialize(&copied_buffer, &req)
                .ok());
        EXPECT_EQ(req.message(), "Hello");
      } else {
        EXPECT_EQ(
            static_cast<const EchoRequest*>(send_msg)->message().find("Hello"),
            0u);
      }
      auto* buffer = methods->GetSerializedSendMessage();
      auto copied_buffer = *buffer;
      EXPECT_TRUE(
          SerializationTraits<EchoRequest>::Deserialize(&copied_buffer, &req)
              .ok());
      EXPECT_TRUE(req.message().find("Hello") == 0u);
      pre_send_message_count_++;
    }
    if (methods->QueryInterceptionHookPoint(
            experimental::InterceptionHookPoints::PRE_SEND_CLOSE)) {

      pre_send_close_ = true;
    }
    if (methods->QueryInterceptionHookPoint(
            experimental::InterceptionHookPoints::POST_RECV_INITIAL_METADATA)) {
      auto* map = methods->GetRecvInitialMetadata();

      EXPECT_EQ(map->size(), 0);
      post_recv_initial_metadata_ = true;
    }
    if (methods->QueryInterceptionHookPoint(
            experimental::InterceptionHookPoints::POST_RECV_MESSAGE)) {
      EchoResponse* resp =
          static_cast<EchoResponse*>(methods->GetRecvMessage());
      if (resp != nullptr) {
        EXPECT_TRUE(resp->message().find("Hello") == 0u);
        post_recv_message_count_++;
      }
    }
    if (methods->QueryInterceptionHookPoint(
            experimental::InterceptionHookPoints::POST_RECV_STATUS)) {
      auto* map = methods->GetRecvTrailingMetadata();
      bool found = false;

      for (const auto& [key, value] : *map) {
        found = key.starts_with("testkey") && value.starts_with("testvalue");
        if (found) break;
      }
      EXPECT_EQ(found, true);
      auto* status = methods->GetRecvStatus();
      EXPECT_EQ(status->ok(), true);
      post_recv_status_ = true;
    }
    methods->Proceed();
  }

  static void VerifyCall(RPCType type) {
    switch (type) {
      case RPCType::kSyncUnary:
      case RPCType::kAsyncCQUnary:
        VerifyUnaryCall();
        break;
      case RPCType::kSyncClientStreaming:
      case RPCType::kAsyncCQClientStreaming:
        VerifyClientStreamingCall();
        break;
      case RPCType::kSyncServerStreaming:
      case RPCType::kAsyncCQServerStreaming:
        VerifyServerStreamingCall();
        break;
      case RPCType::kSyncBidiStreaming:
      case RPCType::kAsyncCQBidiStreaming:
        VerifyBidiStreamingCall();
        break;
    }
  }

  static void VerifyCallCommon() {
    EXPECT_TRUE(pre_send_initial_metadata_);
    EXPECT_TRUE(pre_send_close_);
    EXPECT_TRUE(post_recv_initial_metadata_);
    EXPECT_TRUE(post_recv_status_);
  }

  static void VerifyUnaryCall() {
    VerifyCallCommon();
    EXPECT_EQ(pre_send_message_count_, 1);
    EXPECT_EQ(post_recv_message_count_, 1);
  }

  static void VerifyClientStreamingCall() {
    VerifyCallCommon();
    EXPECT_EQ(pre_send_message_count_, kNumStreamingMessages);
    EXPECT_EQ(post_recv_message_count_, 1);
  }

  static void VerifyServerStreamingCall() {
    VerifyCallCommon();
    EXPECT_EQ(pre_send_message_count_, 1);
    EXPECT_EQ(post_recv_message_count_, kNumStreamingMessages);
  }

  static void VerifyBidiStreamingCall() {
    VerifyCallCommon();
    EXPECT_EQ(pre_send_message_count_, kNumStreamingMessages);
    EXPECT_EQ(post_recv_message_count_, kNumStreamingMessages);
  }

 private:
  static bool pre_send_initial_metadata_;
  static int pre_send_message_count_;
  static bool pre_send_close_;
  static bool post_recv_initial_metadata_;
  static int post_recv_message_count_;
  static bool post_recv_status_;
};

bool LoggingInterceptor::pre_send_initial_metadata_;
int LoggingInterceptor::pre_send_message_count_;
bool LoggingInterceptor::pre_send_close_;
bool LoggingInterceptor::post_recv_initial_metadata_;
int LoggingInterceptor::post_recv_message_count_;
bool LoggingInterceptor::post_recv_status_;

class LoggingInterceptorFactory
    : public experimental::ClientInterceptorFactoryInterface {
 public:
  experimental::Interceptor* CreateClientInterceptor(
      experimental::ClientRpcInfo* info) override {
    return new LoggingInterceptor(info);
  }
};

class TestScenario {
 public:
  explicit TestScenario(const ChannelType& channel_type,
                        const RPCType& rpc_type)
      : channel_type_(channel_type), rpc_type_(rpc_type) {}

  ChannelType channel_type() const { return channel_type_; }

  RPCType rpc_type() const { return rpc_type_; }

 private:
  const ChannelType channel_type_;
  const RPCType rpc_type_;
};

std::vector<TestScenario> CreateTestScenarios() {
  std::vector<TestScenario> scenarios;
  std::vector<RPCType> rpc_types;
  rpc_types.emplace_back(RPCType::kSyncUnary);
  rpc_types.emplace_back(RPCType::kSyncClientStreaming);
  rpc_types.emplace_back(RPCType::kSyncServerStreaming);
  rpc_types.emplace_back(RPCType::kSyncBidiStreaming);
  rpc_types.emplace_back(RPCType::kAsyncCQUnary);
  rpc_types.emplace_back(RPCType::kAsyncCQServerStreaming);
  for (const auto& rpc_type : rpc_types) {
    scenarios.emplace_back(ChannelType::kHttpChannel, rpc_type);

#ifdef GRPC_POSIX_SOCKET
    scenarios.emplace_back(ChannelType::kFdChannel, rpc_type);
#endif
  }
  return scenarios;
}

class ParameterizedClientInterceptorsEnd2endTest
    : public ::testing::TestWithParam<TestScenario> {
 protected:
  ParameterizedClientInterceptorsEnd2endTest() {
    ServerBuilder builder;
    builder.RegisterService(&service_);
    if (GetParam().channel_type() == ChannelType::kHttpChannel) {
      int port = grpc_pick_unused_port_or_die();
      server_address_ = "localhost:" + std::to_string(port);
      builder.AddListeningPort(server_address_, InsecureServerCredentials());
      server_ = builder.BuildAndStart();
    }
#ifdef GRPC_POSIX_SOCKET
    else if (GetParam().channel_type() == ChannelType::kFdChannel) {
      int flags;
      CHECK_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, sv_), 0);
      flags = fcntl(sv_[0], F_GETFL, 0);
      CHECK_EQ(fcntl(sv_[0], F_SETFL, flags | O_NONBLOCK), 0);
      flags = fcntl(sv_[1], F_GETFL, 0);
      CHECK_EQ(fcntl(sv_[1], F_SETFL, flags | O_NONBLOCK), 0);
      CHECK(grpc_set_socket_no_sigpipe_if_possible(sv_[0]) == absl::OkStatus());
      CHECK(grpc_set_socket_no_sigpipe_if_possible(sv_[1]) == absl::OkStatus());
      server_ = builder.BuildAndStart();
      AddInsecureChannelFromFd(server_.get(), sv_[1]);
    }
#endif
  }

  ~ParameterizedClientInterceptorsEnd2endTest() override {
    server_->Shutdown(grpc_timeout_milliseconds_to_deadline(0));
  }

  std::shared_ptr<grpc::Channel> CreateClientChannel(
      std::vector<std::unique_ptr<
          grpc::experimental::ClientInterceptorFactoryInterface>>
          creators) {
    if (GetParam().channel_type() == ChannelType::kHttpChannel) {
      return experimental::CreateCustomChannelWithInterceptors(
          server_address_, InsecureChannelCredentials(), ChannelArguments(),
          std::move(creators));
    }
#ifdef GRPC_POSIX_SOCKET
    else if (GetParam().channel_type() == ChannelType::kFdChannel) {
      return experimental::CreateCustomInsecureChannelWithInterceptorsFromFd(
          "", sv_[0], ChannelArguments(), std::move(creators));
    }
#endif
    return nullptr;
  }

  void SendRPC(const std::shared_ptr<Channel>& channel) {
    switch (GetParam().rpc_type()) {
      case RPCType::kSyncUnary:
        MakeCall(channel);
        break;
      case RPCType::kSyncClientStreaming:
        MakeClientStreamingCall(channel);
        break;
      case RPCType::kSyncServerStreaming:
        MakeServerStreamingCall(channel);
        break;
      case RPCType::kSyncBidiStreaming:
        MakeBidiStreamingCall(channel);
        break;
      case RPCType::kAsyncCQUnary:
        MakeAsyncCQCall(channel);
        break;
      case RPCType::kAsyncCQClientStreaming:

        break;
      case RPCType::kAsyncCQServerStreaming:
        MakeAsyncCQServerStreamingCall(channel);
        break;
      case RPCType::kAsyncCQBidiStreaming:

        break;
    }
  }

  std::string server_address_;
  int sv_[2];
  EchoTestServiceStreamingImpl service_;
  std::unique_ptr<Server> server_;
};

TEST_P(ParameterizedClientInterceptorsEnd2endTest,
       ClientInterceptorLoggingTest) {
  ChannelArguments args;
  PhonyInterceptor::Reset();
  std::vector<std::unique_ptr<experimental::ClientInterceptorFactoryInterface>>
      creators;
  creators.push_back(std::make_unique<LoggingInterceptorFactory>());

  for (auto i = 0; i < 20; i++) {
    creators.push_back(std::make_unique<PhonyInterceptorFactory>());
  }
  auto channel = CreateClientChannel(std::move(creators));
  SendRPC(channel);
  LoggingInterceptor::VerifyCall(GetParam().rpc_type());

  EXPECT_EQ(PhonyInterceptor::GetNumTimesRun(), 20);
}

INSTANTIATE_TEST_SUITE_P(ParameterizedClientInterceptorsEnd2end,
                         ParameterizedClientInterceptorsEnd2endTest,
                         ::testing::ValuesIn(CreateTestScenarios()));

class ClientInterceptorsEnd2endTest
    : public ::testing::TestWithParam<TestScenario> {
 protected:
  ClientInterceptorsEnd2endTest() {
    int port = grpc_pick_unused_port_or_die();

    ServerBuilder builder;
    server_address_ = "localhost:" + std::to_string(port);
    builder.AddListeningPort(server_address_, InsecureServerCredentials());
    builder.RegisterService(&service_);
    server_ = builder.BuildAndStart();
  }

  ~ClientInterceptorsEnd2endTest() override { server_->Shutdown(); }

  std::string server_address_;
  TestServiceImpl service_;
  std::unique_ptr<Server> server_;
};

TEST_F(ClientInterceptorsEnd2endTest,
       LameChannelClientInterceptorHijackingTest) {
  ChannelArguments args;
  std::vector<std::unique_ptr<experimental::ClientInterceptorFactoryInterface>>
      creators;
  creators.push_back(std::make_unique<HijackingInterceptorFactory>());
  auto channel = experimental::CreateCustomChannelWithInterceptors(
      server_address_, nullptr, args, std::move(creators));
  MakeCall(channel);
}

TEST_F(ClientInterceptorsEnd2endTest, ClientInterceptorHijackingTest) {
  ChannelArguments args;
  PhonyInterceptor::Reset();
  std::vector<std::unique_ptr<experimental::ClientInterceptorFactoryInterface>>
      creators;

  creators.reserve(20);
  for (auto i = 0; i < 20; i++) {
    creators.push_back(std::make_unique<PhonyInterceptorFactory>());
  }
  creators.push_back(std::make_unique<HijackingInterceptorFactory>());

  for (auto i = 0; i < 20; i++) {
    creators.push_back(std::make_unique<PhonyInterceptorFactory>());
  }
  auto channel = experimental::CreateCustomChannelWithInterceptors(
      server_address_, InsecureChannelCredentials(), args, std::move(creators));
  MakeCall(channel);

  EXPECT_EQ(PhonyInterceptor::GetNumTimesRun(), 20);
}

TEST_F(ClientInterceptorsEnd2endTest, ClientInterceptorLogThenHijackTest) {
  ChannelArguments args;
  std::vector<std::unique_ptr<experimental::ClientInterceptorFactoryInterface>>
      creators;
  creators.push_back(std::make_unique<LoggingInterceptorFactory>());
  creators.push_back(std::make_unique<HijackingInterceptorFactory>());
  auto channel = experimental::CreateCustomChannelWithInterceptors(
      server_address_, InsecureChannelCredentials(), args, std::move(creators));
  MakeCall(channel);
  LoggingInterceptor::VerifyUnaryCall();
}

TEST_F(ClientInterceptorsEnd2endTest,
       ClientInterceptorHijackingMakesAnotherCallTest) {
  ChannelArguments args;
  PhonyInterceptor::Reset();
  std::vector<std::unique_ptr<experimental::ClientInterceptorFactoryInterface>>
      creators;

  creators.reserve(5);
  for (auto i = 0; i < 5; i++) {
    creators.push_back(std::make_unique<PhonyInterceptorFactory>());
  }
  creators.push_back(
      std::unique_ptr<experimental::ClientInterceptorFactoryInterface>(
          new HijackingInterceptorMakesAnotherCallFactory()));

  for (auto i = 0; i < 7; i++) {
    creators.push_back(std::make_unique<PhonyInterceptorFactory>());
  }
  auto channel = server_->experimental().InProcessChannelWithInterceptors(
      args, std::move(creators));

  MakeCall(channel, StubOptions("TestSuffixForStats"));

  EXPECT_EQ(PhonyInterceptor::GetNumTimesRun(), 12);
}

class ClientInterceptorsCallbackEnd2endTest : public ::testing::Test {
 protected:
  ClientInterceptorsCallbackEnd2endTest() {
    int port = grpc_pick_unused_port_or_die();

    ServerBuilder builder;
    server_address_ = "localhost:" + std::to_string(port);
    builder.AddListeningPort(server_address_, InsecureServerCredentials());
    builder.RegisterService(&service_);
    server_ = builder.BuildAndStart();
  }

  ~ClientInterceptorsCallbackEnd2endTest() override { server_->Shutdown(); }

  std::string server_address_;
  TestServiceImpl service_;
  std::unique_ptr<Server> server_;
};

TEST_F(ClientInterceptorsCallbackEnd2endTest,
       ClientInterceptorLoggingTestWithCallback) {
  ChannelArguments args;
  PhonyInterceptor::Reset();
  std::vector<std::unique_ptr<experimental::ClientInterceptorFactoryInterface>>
      creators;
  creators.push_back(std::make_unique<LoggingInterceptorFactory>());

  for (auto i = 0; i < 20; i++) {
    creators.push_back(std::make_unique<PhonyInterceptorFactory>());
  }
  auto channel = server_->experimental().InProcessChannelWithInterceptors(
      args, std::move(creators));
  MakeCallbackCall(channel);
  LoggingInterceptor::VerifyUnaryCall();

  EXPECT_EQ(PhonyInterceptor::GetNumTimesRun(), 20);
}

TEST_F(ClientInterceptorsCallbackEnd2endTest,
       ClientInterceptorHijackingTestWithCallback) {
  ChannelArguments args;
  PhonyInterceptor::Reset();
  std::vector<std::unique_ptr<experimental::ClientInterceptorFactoryInterface>>
      creators;
  creators.push_back(std::make_unique<LoggingInterceptorFactory>());

  for (auto i = 0; i < 20; i++) {
    creators.push_back(std::make_unique<PhonyInterceptorFactory>());
  }
  creators.push_back(std::make_unique<HijackingInterceptorFactory>());
  auto channel = server_->experimental().InProcessChannelWithInterceptors(
      args, std::move(creators));
  MakeCallbackCall(channel);
  LoggingInterceptor::VerifyUnaryCall();

  EXPECT_EQ(PhonyInterceptor::GetNumTimesRun(), 20);
}

TEST_F(ClientInterceptorsCallbackEnd2endTest,
       ClientInterceptorFactoryAllowsNullptrReturn) {
  ChannelArguments args;
  PhonyInterceptor::Reset();
  std::vector<std::unique_ptr<experimental::ClientInterceptorFactoryInterface>>
      creators;
  creators.push_back(std::make_unique<LoggingInterceptorFactory>());

  for (auto i = 0; i < 20; i++) {
    creators.push_back(std::make_unique<PhonyInterceptorFactory>());
    creators.push_back(std::make_unique<NullInterceptorFactory>());
  }
  auto channel = server_->experimental().InProcessChannelWithInterceptors(
      args, std::move(creators));
  MakeCallbackCall(channel);
  LoggingInterceptor::VerifyUnaryCall();

  EXPECT_EQ(PhonyInterceptor::GetNumTimesRun(), 20);
}

class ClientInterceptorsStreamingEnd2endTest : public ::testing::Test {
 protected:
  ClientInterceptorsStreamingEnd2endTest() {
    int port = grpc_pick_unused_port_or_die();

    ServerBuilder builder;
    server_address_ = "localhost:" + std::to_string(port);
    builder.AddListeningPort(server_address_, InsecureServerCredentials());
    builder.RegisterService(&service_);
    server_ = builder.BuildAndStart();
  }

  ~ClientInterceptorsStreamingEnd2endTest() override { server_->Shutdown(); }

  std::string server_address_;
  EchoTestServiceStreamingImpl service_;
  std::unique_ptr<Server> server_;
};

TEST_F(ClientInterceptorsStreamingEnd2endTest, ClientStreamingTest) {
  ChannelArguments args;
  PhonyInterceptor::Reset();
  std::vector<std::unique_ptr<experimental::ClientInterceptorFactoryInterface>>
      creators;
  creators.push_back(std::make_unique<LoggingInterceptorFactory>());

  for (auto i = 0; i < 20; i++) {
    creators.push_back(std::make_unique<PhonyInterceptorFactory>());
  }
  auto channel = experimental::CreateCustomChannelWithInterceptors(
      server_address_, InsecureChannelCredentials(), args, std::move(creators));
  MakeClientStreamingCall(channel);
  LoggingInterceptor::VerifyClientStreamingCall();

  EXPECT_EQ(PhonyInterceptor::GetNumTimesRun(), 20);
}

TEST_F(ClientInterceptorsStreamingEnd2endTest, ServerStreamingTest) {
  ChannelArguments args;
  PhonyInterceptor::Reset();
  std::vector<std::unique_ptr<experimental::ClientInterceptorFactoryInterface>>
      creators;
  creators.push_back(std::make_unique<LoggingInterceptorFactory>());

  for (auto i = 0; i < 20; i++) {
    creators.push_back(std::make_unique<PhonyInterceptorFactory>());
  }
  auto channel = experimental::CreateCustomChannelWithInterceptors(
      server_address_, InsecureChannelCredentials(), args, std::move(creators));
  MakeServerStreamingCall(channel);
  LoggingInterceptor::VerifyServerStreamingCall();

  EXPECT_EQ(PhonyInterceptor::GetNumTimesRun(), 20);
}

TEST_F(ClientInterceptorsStreamingEnd2endTest, ClientStreamingHijackingTest) {
  ChannelArguments args;
  std::vector<std::unique_ptr<experimental::ClientInterceptorFactoryInterface>>
      creators;
  creators.push_back(
      std::make_unique<ClientStreamingRpcHijackingInterceptorFactory>());
  auto channel = experimental::CreateCustomChannelWithInterceptors(
      server_address_, InsecureChannelCredentials(), args, std::move(creators));

  auto stub = grpc::testing::EchoTestService::NewStub(
      channel, StubOptions("TestSuffixForStats"));
  ClientContext ctx;
  EchoRequest req;
  EchoResponse resp;
  req.mutable_param()->set_echo_metadata(true);
  req.set_message("Hello");
  string expected_resp;
  auto writer = stub->RequestStream(&ctx, &resp);
  for (int i = 0; i < 10; i++) {
    EXPECT_TRUE(writer->Write(req));
    expected_resp += "Hello";
  }

  writer->Write(req);
  Status s = writer->Finish();
  EXPECT_EQ(s.ok(), false);
  EXPECT_TRUE(ClientStreamingRpcHijackingInterceptor::GotFailedSend());
}

TEST_F(ClientInterceptorsStreamingEnd2endTest, ServerStreamingHijackingTest) {
  ChannelArguments args;
  PhonyInterceptor::Reset();
  std::vector<std::unique_ptr<experimental::ClientInterceptorFactoryInterface>>
      creators;
  creators.push_back(
      std::make_unique<ServerStreamingRpcHijackingInterceptorFactory>());
  auto channel = experimental::CreateCustomChannelWithInterceptors(
      server_address_, InsecureChannelCredentials(), args, std::move(creators));
  MakeServerStreamingCall(channel);
  EXPECT_TRUE(ServerStreamingRpcHijackingInterceptor::GotFailedMessage());
}

TEST_F(ClientInterceptorsStreamingEnd2endTest,
       AsyncCQServerStreamingHijackingTest) {
  ChannelArguments args;
  PhonyInterceptor::Reset();
  std::vector<std::unique_ptr<experimental::ClientInterceptorFactoryInterface>>
      creators;
  creators.push_back(
      std::make_unique<ServerStreamingRpcHijackingInterceptorFactory>());
  auto channel = experimental::CreateCustomChannelWithInterceptors(
      server_address_, InsecureChannelCredentials(), args, std::move(creators));
  MakeAsyncCQServerStreamingCall(channel);
  EXPECT_TRUE(ServerStreamingRpcHijackingInterceptor::GotFailedMessage());
}

TEST_F(ClientInterceptorsStreamingEnd2endTest, BidiStreamingHijackingTest) {
  ChannelArguments args;
  PhonyInterceptor::Reset();
  std::vector<std::unique_ptr<experimental::ClientInterceptorFactoryInterface>>
      creators;
  creators.push_back(
      std::make_unique<BidiStreamingRpcHijackingInterceptorFactory>());
  auto channel = experimental::CreateCustomChannelWithInterceptors(
      server_address_, InsecureChannelCredentials(), args, std::move(creators));
  MakeBidiStreamingCall(channel);
}

TEST_F(ClientInterceptorsStreamingEnd2endTest, BidiStreamingTest) {
  ChannelArguments args;
  PhonyInterceptor::Reset();
  std::vector<std::unique_ptr<experimental::ClientInterceptorFactoryInterface>>
      creators;
  creators.push_back(std::make_unique<LoggingInterceptorFactory>());

  for (auto i = 0; i < 20; i++) {
    creators.push_back(std::make_unique<PhonyInterceptorFactory>());
  }
  auto channel = experimental::CreateCustomChannelWithInterceptors(
      server_address_, InsecureChannelCredentials(), args, std::move(creators));
  MakeBidiStreamingCall(channel);
  LoggingInterceptor::VerifyBidiStreamingCall();

  EXPECT_EQ(PhonyInterceptor::GetNumTimesRun(), 20);
}

class ClientGlobalInterceptorEnd2endTest : public ::testing::Test {
 protected:
  ClientGlobalInterceptorEnd2endTest() {
    int port = grpc_pick_unused_port_or_die();

    ServerBuilder builder;
    server_address_ = "localhost:" + std::to_string(port);
    builder.AddListeningPort(server_address_, InsecureServerCredentials());
    builder.RegisterService(&service_);
    server_ = builder.BuildAndStart();
  }

  ~ClientGlobalInterceptorEnd2endTest() override { server_->Shutdown(); }

  std::string server_address_;
  TestServiceImpl service_;
  std::unique_ptr<Server> server_;
};

TEST_F(ClientGlobalInterceptorEnd2endTest, PhonyGlobalInterceptor) {

  PhonyInterceptorFactory global_factory;
  experimental::RegisterGlobalClientInterceptorFactory(&global_factory);
  ChannelArguments args;
  PhonyInterceptor::Reset();
  std::vector<std::unique_ptr<experimental::ClientInterceptorFactoryInterface>>
      creators;

  creators.reserve(20);
  for (auto i = 0; i < 20; i++) {
    creators.push_back(std::make_unique<PhonyInterceptorFactory>());
  }
  auto channel = experimental::CreateCustomChannelWithInterceptors(
      server_address_, InsecureChannelCredentials(), args, std::move(creators));
  MakeCall(channel);

  EXPECT_EQ(PhonyInterceptor::GetNumTimesRun(), 21);
  experimental::TestOnlyResetGlobalClientInterceptorFactory();
}

TEST_F(ClientGlobalInterceptorEnd2endTest, LoggingGlobalInterceptor) {

  LoggingInterceptorFactory global_factory;
  experimental::RegisterGlobalClientInterceptorFactory(&global_factory);
  ChannelArguments args;
  PhonyInterceptor::Reset();
  std::vector<std::unique_ptr<experimental::ClientInterceptorFactoryInterface>>
      creators;

  creators.reserve(20);
  for (auto i = 0; i < 20; i++) {
    creators.push_back(std::make_unique<PhonyInterceptorFactory>());
  }
  auto channel = experimental::CreateCustomChannelWithInterceptors(
      server_address_, InsecureChannelCredentials(), args, std::move(creators));
  MakeCall(channel);
  LoggingInterceptor::VerifyUnaryCall();

  EXPECT_EQ(PhonyInterceptor::GetNumTimesRun(), 20);
  experimental::TestOnlyResetGlobalClientInterceptorFactory();
}

TEST_F(ClientGlobalInterceptorEnd2endTest, HijackingGlobalInterceptor) {

  HijackingInterceptorFactory global_factory;
  experimental::RegisterGlobalClientInterceptorFactory(&global_factory);
  ChannelArguments args;
  PhonyInterceptor::Reset();
  std::vector<std::unique_ptr<experimental::ClientInterceptorFactoryInterface>>
      creators;

  creators.reserve(20);
  for (auto i = 0; i < 20; i++) {
    creators.push_back(std::make_unique<PhonyInterceptorFactory>());
  }
  auto channel = experimental::CreateCustomChannelWithInterceptors(
      server_address_, InsecureChannelCredentials(), args, std::move(creators));
  MakeCall(channel);

  EXPECT_EQ(PhonyInterceptor::GetNumTimesRun(), 20);
  experimental::TestOnlyResetGlobalClientInterceptorFactory();
}

}
}
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  int ret = RUN_ALL_TESTS();

  CHECK(grpc_wait_until_shutdown(10));
  return ret;
}
