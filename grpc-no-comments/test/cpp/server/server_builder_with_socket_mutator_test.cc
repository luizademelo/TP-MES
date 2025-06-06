
// Copyright 2017 gRPC authors.

#include <grpc/grpc.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/support/config.h>

#include <memory>

#include "gtest/gtest.h"
#include "src/core/lib/iomgr/socket_mutator.h"
#include "src/proto/grpc/testing/echo.grpc.pb.h"
#include "test/core/test_util/port.h"
#include "test/core/test_util/test_config.h"

namespace grpc {
namespace {

bool mock_socket_mutator_mutate_fd(int, grpc_socket_mutator*);
int mock_socket_mutator_compare(grpc_socket_mutator*, grpc_socket_mutator*);
void mock_socket_mutator_destroy(grpc_socket_mutator*);

const grpc_socket_mutator_vtable mock_socket_mutator_vtable = {
    mock_socket_mutator_mutate_fd,
    mock_socket_mutator_compare,
    mock_socket_mutator_destroy,
    nullptr,
};

class MockSocketMutator : public grpc_socket_mutator {
 public:
  MockSocketMutator() : mutate_fd_call_count_(0) {
    grpc_socket_mutator_init(this, &mock_socket_mutator_vtable);
  }
  int mutate_fd_call_count_;
};

bool mock_socket_mutator_mutate_fd(int , grpc_socket_mutator* m) {
  MockSocketMutator* s = reinterpret_cast<MockSocketMutator*>(m);
  s->mutate_fd_call_count_++;
  return true;
}

int mock_socket_mutator_compare(grpc_socket_mutator* a,
                                grpc_socket_mutator* b) {
  return reinterpret_cast<uintptr_t>(a) - reinterpret_cast<uintptr_t>(b);
}

void mock_socket_mutator_destroy(grpc_socket_mutator* m) {
  MockSocketMutator* s = reinterpret_cast<MockSocketMutator*>(m);
  delete s;
}

class MockSocketMutatorServerBuilderOption : public grpc::ServerBuilderOption {
 public:
  explicit MockSocketMutatorServerBuilderOption(
      MockSocketMutator* mock_socket_mutator)
      : mock_socket_mutator_(mock_socket_mutator) {}

  void UpdateArguments(ChannelArguments* args) override {
    args->SetSocketMutator(mock_socket_mutator_);
  }

  void UpdatePlugins(
      std::vector<std::unique_ptr<ServerBuilderPlugin>>*) override {};

  MockSocketMutator* mock_socket_mutator_;
};

class ServerBuilderWithSocketMutatorTest : public ::testing::Test {
 protected:
  static void SetUpTestSuite() { grpc_init(); }

  static void TearDownTestSuite() { grpc_shutdown(); }
};

TEST_F(ServerBuilderWithSocketMutatorTest, CreateServerWithSocketMutator) {
  auto address = "localhost:" + std::to_string(grpc_pick_unused_port_or_die());
  auto mock_socket_mutator = new MockSocketMutator();
  std::unique_ptr<grpc::ServerBuilderOption> mock_socket_mutator_builder_option(
      new MockSocketMutatorServerBuilderOption(mock_socket_mutator));
  testing::EchoTestService::Service echo_service;
  EXPECT_EQ(mock_socket_mutator->mutate_fd_call_count_, 0);
  ServerBuilder builder;
  builder.RegisterService(&echo_service);
  builder.AddListeningPort(address, InsecureServerCredentials());
  builder.SetOption(std::move(mock_socket_mutator_builder_option));
  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
  EXPECT_NE(server, nullptr);

  EXPECT_GE(mock_socket_mutator->mutate_fd_call_count_, 1);
  server->Shutdown();
}

}
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  int ret = RUN_ALL_TESTS();
  return ret;
}
