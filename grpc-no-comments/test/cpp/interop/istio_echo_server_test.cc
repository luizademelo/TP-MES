
// Copyright 2022 gRPC authors.

#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/support/status.h>

#include <memory>

#include "absl/strings/str_cat.h"
#include "absl/strings/str_format.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "src/core/util/crash.h"
#include "src/core/util/host_port.h"
#include "test/core/test_util/port.h"
#include "test/core/test_util/test_config.h"
#include "test/cpp/interop/istio_echo_server_lib.h"

namespace grpc {
namespace testing {
namespace {

using proto::EchoRequest;
using proto::EchoResponse;
using proto::EchoTestService;
using proto::ForwardEchoRequest;
using proto::ForwardEchoResponse;

class SimpleEchoTestServerImpl : public proto::EchoTestService::Service {
 public:
  explicit SimpleEchoTestServerImpl() {}

  grpc::Status Echo(grpc::ServerContext* ,
                    const proto::EchoRequest* ,
                    proto::EchoResponse* ) override {
    grpc_core::Crash("unreachable");
    return Status(StatusCode::INVALID_ARGUMENT, "Unexpected");
  }

  grpc::Status ForwardEcho(grpc::ServerContext* ,
                           const proto::ForwardEchoRequest* request,
                           proto::ForwardEchoResponse* response) override {
    if (fail_rpc_) {
      return Status(StatusCode::UNAVAILABLE, "fail rpc");
    }
    response->add_output(request->message());
    return Status::OK;
  }

  void set_fail_rpc(bool fail_rpc) { fail_rpc_ = fail_rpc; }

 private:
  std::string hostname_;
  std::string forwarding_address_;
  std::atomic<bool> fail_rpc_{false};

};

class EchoTest : public ::testing::Test {
 protected:
  EchoTest() {

    int forwarding_port = grpc_pick_unused_port_or_die();
    forwarding_address_ = grpc_core::JoinHostPort("localhost", forwarding_port);
    ServerBuilder simple_builder;
    simple_builder.RegisterService(&simple_test_service_impl_);
    simple_builder.AddListeningPort(forwarding_address_,
                                    InsecureServerCredentials());
    simple_server_ = simple_builder.BuildAndStart();

    ServerBuilder builder;
    echo_test_service_impl_ = std::make_unique<EchoTestServiceImpl>(
        "hostname", "v1", forwarding_address_);
    builder.RegisterService(echo_test_service_impl_.get());
    int port = grpc_pick_unused_port_or_die();
    server_address_ = grpc_core::JoinHostPort("localhost", port);
    builder.AddListeningPort(server_address_, InsecureServerCredentials());
    server_ = builder.BuildAndStart();

    auto channel = CreateChannel(server_address_, InsecureChannelCredentials());
    stub_ = EchoTestService::NewStub(channel);
  }

  std::string forwarding_address_;
  SimpleEchoTestServerImpl simple_test_service_impl_;
  std::unique_ptr<EchoTestServiceImpl> echo_test_service_impl_;
  std::string server_address_;
  std::unique_ptr<Server> server_;
  std::unique_ptr<Server> simple_server_;
  std::unique_ptr<EchoTestService::Stub> stub_;
};

TEST_F(EchoTest, SimpleEchoTest) {
  ClientContext context;
  EchoRequest request;
  EchoResponse response;
  request.set_message("hello");
  auto status = stub_->Echo(&context, request, &response);
  ASSERT_TRUE(status.ok());
  EXPECT_THAT(response.message(),
              ::testing::AllOf(::testing::HasSubstr("StatusCode=200\n"),
                               ::testing::HasSubstr("Hostname=hostname\n"),
                               ::testing::HasSubstr("Echo=hello\n"),
                               ::testing::HasSubstr("Host="),
                               ::testing::HasSubstr("IP="),
                               ::testing::HasSubstr("ServiceVersion=v1")));
}

TEST_F(EchoTest, ForwardEchoTest) {
  ClientContext context;
  ForwardEchoRequest request;
  ForwardEchoResponse response;
  request.set_count(3);
  request.set_qps(1);
  request.set_timeout_micros(20 * 1000 * 1000);
  request.set_url(absl::StrCat("grpc://", server_address_));
  request.set_message("hello");
  auto status = stub_->ForwardEcho(&context, request, &response);
  ASSERT_TRUE(status.ok());
  for (int i = 0; i < 3; ++i) {
    EXPECT_THAT(
        response.output()[i],
        ::testing::AllOf(
            ::testing::HasSubstr(
                absl::StrFormat("[%d body] StatusCode=200\n", i)),
            ::testing::HasSubstr(
                absl::StrFormat("[%d body] Hostname=hostname\n", i)),
            ::testing::HasSubstr(absl::StrFormat("[%d body] Echo=hello\n", i)),
            ::testing::HasSubstr(absl::StrFormat("[%d body] Host=", i)),
            ::testing::HasSubstr(
                absl::StrFormat("[%d body] ServiceVersion=v1", i))));
  }
}

TEST_F(EchoTest, ForwardEchoTestUnhandledProtocols) {
  ClientContext context;
  ForwardEchoRequest request;
  ForwardEchoResponse response;
  request.set_count(3);
  request.set_qps(1);
  request.set_timeout_micros(20 * 1000 * 1000);

  request.set_url(absl::StrCat("http://", server_address_));
  request.set_message("hello");
  auto status = stub_->ForwardEcho(&context, request, &response);
  ASSERT_TRUE(status.ok()) << "Code = " << status.error_code()
                           << " Message = " << status.error_message();
  ASSERT_FALSE(response.output().empty());
  EXPECT_EQ(response.output()[0], "hello");
}

TEST_F(EchoTest, ForwardEchoFailure) {
  simple_test_service_impl_.set_fail_rpc(true);
  ClientContext context;
  ForwardEchoRequest request;
  ForwardEchoResponse response;
  request.set_count(3);
  request.set_qps(1);
  request.set_timeout_micros(20 * 1000 * 1000);

  request.set_url(absl::StrCat("http://", server_address_));
  request.set_message("hello");
  auto status = stub_->ForwardEcho(&context, request, &response);
  ASSERT_EQ(status.error_code(), StatusCode::UNAVAILABLE);
}

}
}
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  grpc::testing::TestEnvironment env(&argc, argv);
  grpc_init();
  auto result = RUN_ALL_TESTS();
  grpc_shutdown();
  return result;
}
