
// Copyright 2022 gRPC authors.

#include <grpc/grpc.h>
#include <grpcpp/grpcpp.h>

#include <thread>

#include "absl/strings/str_format.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "src/core/util/sync.h"
#include "src/proto/grpc/testing/empty.pb.h"
#include "src/proto/grpc/testing/test.grpc.pb.h"
#include "test/core/test_util/port.h"
#include "test/core/test_util/test_config.h"
#include "test/cpp/interop/xds_interop_server_lib.h"

namespace grpc {
namespace testing {
namespace {

void ServerLoop(int port, grpc_core::Mutex* mutex,
                grpc_core::CondVar* condition, Server** server) {
  RunServer(false, port,  -1, "127.0.0.1",
            "test_server", [&](Server* s) {
              grpc_core::MutexLock lock(mutex);
              *server = s;
              condition->Signal();
            });
}

TEST(GetRpcBehaviorMetadataTest, ErrorCodeNoFilter) {
  auto status = GetStatusForRpcBehaviorMetadata("error-code-16", "hostname");
  ASSERT_TRUE(status.has_value());
  ASSERT_EQ(status->error_code(), 16) << status->error_message();
}

TEST(GetRpcBehaviorMetadataTest, ErrorCodeThisHost) {
  auto status = GetStatusForRpcBehaviorMetadata(
      "hostname=hostname error-code-16", "hostname");
  ASSERT_TRUE(status.has_value());
  ASSERT_EQ(status->error_code(), 16) << status->error_message();
}

TEST(GetRpcBehaviorMetadataTest, ErrorCodeOtherHost) {
  auto status = GetStatusForRpcBehaviorMetadata(
      "hostname=hostname2 error-code-16", "hostname");
  ASSERT_FALSE(status.has_value());
}

TEST(GetRpcBehaviorMetadataTest, MalformedErrorCode) {
  auto status = GetStatusForRpcBehaviorMetadata("error-code-", "hostname");
  ASSERT_TRUE(status.has_value());
  ASSERT_EQ(status->error_code(), grpc::StatusCode::INVALID_ARGUMENT)
      << status->error_message();
}

TEST(GetRpcBehaviorMetadataTest, MalformedHostName) {
  auto status =
      GetStatusForRpcBehaviorMetadata("hostname= error-code-16", "hostname");
  ASSERT_TRUE(status.has_value());
  ASSERT_EQ(status->error_code(), grpc::StatusCode::INVALID_ARGUMENT)
      << status->error_message();
}

TEST(GetRpcBehaviorMetadataTest, ErrorWhenUnsupported) {
  auto status = GetStatusForRpcBehaviorMetadata("unsupported", "hostname");
  ASSERT_TRUE(status.has_value());
  ASSERT_EQ(status->error_code(), grpc::StatusCode::INVALID_ARGUMENT)
      << status->error_message();
}

TEST(MaintenanceServerHookServiceTest, HookServiceInstalled) {
  int port = grpc_pick_unused_port_or_die();
  grpc_core::Mutex mutex;
  grpc_core::CondVar condition;
  Server* server = nullptr;
  std::thread thread(ServerLoop, port, &mutex, &condition, &server);
  {
    grpc_core::MutexLock lock(&mutex);
    while (server == nullptr) {
      condition.Wait(&mutex);
    }
  }
  HookService::Stub stub(CreateChannel(absl::StrFormat("127.0.0.1:%d", port),
                                       InsecureChannelCredentials()));
  ClientContext ctx;
  Empty req, res;
  auto status = stub.ClearReturnStatus(&ctx, req, &res);
  EXPECT_EQ(status.error_code(), StatusCode::OK);
  server->Shutdown();
  thread.join();
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
