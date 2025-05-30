
// Copyright 2022 gRPC authors.

#include <grpc++/grpc++.h>
#include <grpcpp/ext/gcp_observability.h>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "src/core/config/core_configuration.h"
#include "src/proto/grpc/testing/echo.grpc.pb.h"
#include "src/proto/grpc/testing/echo_messages.pb.h"
#include "test/core/test_util/port.h"
#include "test/core/test_util/test_config.h"
#include "test/cpp/end2end/test_service_impl.h"

namespace grpc {
namespace testing {
namespace {

TEST(GcpObservabilityTest, Basic) {
  auto observability = grpc::GcpObservability::Init();
  EXPECT_EQ(observability.status(),
            absl::FailedPreconditionError(
                "Environment variables GRPC_GCP_OBSERVABILITY_CONFIG_FILE or "
                "GRPC_GCP_OBSERVABILITY_CONFIG "
                "not defined"));
  grpc_core::CoreConfiguration::Reset();
}

TEST(GcpObservabilityTest, ContinuesWorkingAfterFailure) {
  auto observability = grpc::GcpObservability::Init();
  EXPECT_FALSE(observability.ok());

  grpc::ServerBuilder builder;
  TestServiceImpl service;
  int port = grpc_pick_unused_port_or_die();
  auto server_address = absl::StrCat("localhost:", port);

  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials(),
                           &port);
  builder.RegisterService(&service);
  auto server = builder.BuildAndStart();
  ASSERT_NE(nullptr, server);
  auto server_thread = std::thread([&]() { server->Wait(); });

  auto stub = EchoTestService::NewStub(
      grpc::CreateChannel(server_address, grpc::InsecureChannelCredentials()));
  EchoRequest request;
  request.set_message("foo");
  EchoResponse response;
  grpc::ClientContext context;
  grpc::Status status = stub->Echo(&context, request, &response);
  EXPECT_TRUE(status.ok());
  EXPECT_EQ(response.message(), "foo");
  server->Shutdown();
  server_thread.join();
}

}
}
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
