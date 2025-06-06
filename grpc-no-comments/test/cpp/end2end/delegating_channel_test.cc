
// Copyright 2018 gRPC authors.

#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/generic/generic_stub.h>
#include <grpcpp/impl/delegating_channel.h>
#include <grpcpp/impl/proto_utils.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>
#include <grpcpp/support/client_interceptor.h>

#include <memory>
#include <vector>

#include "gtest/gtest.h"
#include "src/proto/grpc/testing/echo.grpc.pb.h"
#include "test/core/test_util/port.h"
#include "test/core/test_util/test_config.h"
#include "test/cpp/end2end/test_service_impl.h"
#include "test/cpp/util/byte_buffer_proto_helper.h"
#include "test/cpp/util/string_ref_helper.h"

namespace grpc {
namespace testing {
namespace {

class TestChannel : public experimental::DelegatingChannel {
 public:
  explicit TestChannel(
      const std::shared_ptr<ChannelInterface>& delegate_channel)
      : experimental::DelegatingChannel(delegate_channel) {}

  grpc_connectivity_state GetState(bool ) override {
    return GRPC_CHANNEL_READY;
  }
};

class DelegatingChannelTest : public ::testing::Test {
 protected:
  DelegatingChannelTest() {
    int port = grpc_pick_unused_port_or_die();
    ServerBuilder builder;
    server_address_ = "localhost:" + std::to_string(port);
    builder.AddListeningPort(server_address_, InsecureServerCredentials());
    builder.RegisterService(&service_);
    server_ = builder.BuildAndStart();
  }

  ~DelegatingChannelTest() override { server_->Shutdown(); }

  std::string server_address_;
  TestServiceImpl service_;
  std::unique_ptr<Server> server_;
};

TEST_F(DelegatingChannelTest, SimpleTest) {
  auto channel = CreateChannel(server_address_, InsecureChannelCredentials());
  std::shared_ptr<TestChannel> test_channel =
      std::make_shared<TestChannel>(channel);

  EXPECT_EQ(channel->GetState(false), GRPC_CHANNEL_IDLE);
  EXPECT_EQ(test_channel->GetState(false), GRPC_CHANNEL_READY);
  auto stub = grpc::testing::EchoTestService::NewStub(test_channel);
  ClientContext ctx;
  EchoRequest req;
  req.set_message("Hello");
  EchoResponse resp;
  Status s = stub->Echo(&ctx, req, &resp);
  EXPECT_EQ(s.ok(), true);
  EXPECT_EQ(resp.message(), "Hello");
}

}
}
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
