
// Copyright 2015 gRPC authors.

#include "test/cpp/util/cli_call.h"

#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>

#include "gtest/gtest.h"
#include "src/proto/grpc/testing/echo.grpc.pb.h"
#include "test/core/test_util/port.h"
#include "test/core/test_util/test_config.h"
#include "test/cpp/util/string_ref_helper.h"

namespace grpc {
namespace testing {

class TestServiceImpl : public grpc::testing::EchoTestService::Service {
 public:
  Status Echo(ServerContext* context, const EchoRequest* request,
              EchoResponse* response) override {
    if (!context->client_metadata().empty()) {
      for (std::multimap<grpc::string_ref, grpc::string_ref>::const_iterator
               iter = context->client_metadata().begin();
           iter != context->client_metadata().end(); ++iter) {
        context->AddInitialMetadata(ToString(iter->first),
                                    ToString(iter->second));
      }
    }
    context->AddTrailingMetadata("trailing_key", "trailing_value");
    response->set_message(request->message());
    return Status::OK;
  }
};

class CliCallTest : public ::testing::Test {
 protected:
  CliCallTest() {}

  void SetUp() override {
    int port = grpc_pick_unused_port_or_die();
    server_address_ << "localhost:" << port;

    ServerBuilder builder;
    builder.AddListeningPort(server_address_.str(),
                             InsecureServerCredentials());
    builder.RegisterService(&service_);
    server_ = builder.BuildAndStart();
  }

  void TearDown() override { server_->Shutdown(); }

  void ResetStub() {
    channel_ = grpc::CreateChannel(server_address_.str(),
                                   InsecureChannelCredentials());
    stub_ = grpc::testing::EchoTestService::NewStub(channel_);
  }

  std::shared_ptr<Channel> channel_;
  std::unique_ptr<grpc::testing::EchoTestService::Stub> stub_;
  std::unique_ptr<Server> server_;
  std::ostringstream server_address_;
  TestServiceImpl service_;
};

TEST_F(CliCallTest, SimpleRpc) {
  ResetStub();

  EchoRequest request;
  EchoResponse response;
  request.set_message("Hello");

  ClientContext context;
  context.AddMetadata("key1", "val1");
  Status s = stub_->Echo(&context, request, &response);
  EXPECT_EQ(response.message(), request.message());
  EXPECT_TRUE(s.ok());

  const std::string kMethod("/grpc.testing.EchoTestService/Echo");
  std::string request_bin, response_bin, expected_response_bin;
  EXPECT_TRUE(request.SerializeToString(&request_bin));
  EXPECT_TRUE(response.SerializeToString(&expected_response_bin));
  std::multimap<std::string, std::string> client_metadata;
  std::multimap<grpc::string_ref, grpc::string_ref> server_initial_metadata,
      server_trailing_metadata;
  client_metadata.insert(std::pair<std::string, std::string>("key1", "val1"));
  CliCall call(channel_, kMethod, client_metadata);
  Status s2 = call.Call(request_bin, &response_bin, &server_initial_metadata,
                        &server_trailing_metadata);
  EXPECT_TRUE(s2.ok());

  EXPECT_EQ(expected_response_bin, response_bin);
  EXPECT_EQ(context.GetServerInitialMetadata(), server_initial_metadata);
  EXPECT_EQ(context.GetServerTrailingMetadata(), server_trailing_metadata);
}

}
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
