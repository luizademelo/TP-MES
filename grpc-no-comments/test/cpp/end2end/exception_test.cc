
// Copyright 2017 gRPC authors.

#include <grpc/support/port_platform.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>

#include <exception>
#include <memory>

#include "gtest/gtest.h"
#include "src/proto/grpc/testing/echo.grpc.pb.h"
#include "test/core/test_util/test_config.h"

namespace grpc {
namespace testing {

const char* kErrorMessage = "This service caused an exception";

#if GRPC_ALLOW_EXCEPTIONS
class ExceptingServiceImpl : public grpc::testing::EchoTestService::Service {
 public:
  Status Echo(ServerContext* , const EchoRequest* ,
              EchoResponse* ) override {
    throw -1;
  }
  Status RequestStream(ServerContext* ,
                       ServerReader<EchoRequest>* ,
                       EchoResponse* ) override {
    throw ServiceException();
  }

 private:
  class ServiceException final : public std::exception {
   public:
    ServiceException() {}

   private:
    const char* what() const noexcept override { return kErrorMessage; }
  };
};

class ExceptionTest : public ::testing::Test {
 protected:
  ExceptionTest() {}

  void SetUp() override {
    ServerBuilder builder;
    builder.RegisterService(&service_);
    server_ = builder.BuildAndStart();
  }

  void TearDown() override { server_->Shutdown(); }

  void ResetStub() {
    channel_ = server_->InProcessChannel(ChannelArguments());
    stub_ = grpc::testing::EchoTestService::NewStub(channel_);
  }

  std::shared_ptr<Channel> channel_;
  std::unique_ptr<grpc::testing::EchoTestService::Stub> stub_;
  std::unique_ptr<Server> server_;
  ExceptingServiceImpl service_;
};

TEST_F(ExceptionTest, Unary) {
  ResetStub();
  EchoRequest request;
  EchoResponse response;
  request.set_message("test");

  for (int i = 0; i < 10; i++) {
    ClientContext context;
    Status s = stub_->Echo(&context, request, &response);
    EXPECT_FALSE(s.ok());
    EXPECT_EQ(s.error_code(), StatusCode::UNKNOWN);
  }
}

TEST_F(ExceptionTest, RequestStream) {
  ResetStub();
  EchoResponse response;

  for (int i = 0; i < 10; i++) {
    ClientContext context;
    auto stream = stub_->RequestStream(&context, &response);
    stream->WritesDone();
    Status s = stream->Finish();

    EXPECT_FALSE(s.ok());
    EXPECT_EQ(s.error_code(), StatusCode::UNKNOWN);
  }
}

#endif

}
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
