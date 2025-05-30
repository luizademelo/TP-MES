// Copyright 2022 The gRPC Authors

#include <grpc/support/port_platform.h>

#ifndef GRPC_ENABLE_FORK_SUPPORT

int main(int , char** ) { return 0; }
#else

#include <grpc/fork.h>
#include <grpc/grpc.h>
#include <grpc/support/time.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>
#include <signal.h>

#include "absl/log/log.h"
#include "absl/strings/str_cat.h"
#include "gtest/gtest.h"
#include "src/core/util/fork.h"
#include "src/proto/grpc/testing/echo.grpc.pb.h"
#include "test/core/test_util/port.h"
#include "test/core/test_util/test_config.h"
#include "test/cpp/util/test_config.h"

namespace grpc {
namespace testing {
namespace {

class ServiceImpl final : public EchoTestService::Service {
  Status BidiStream(
      ServerContext* ,
      ServerReaderWriter<EchoResponse, EchoRequest>* stream) override {
    EchoRequest request;
    EchoResponse response;
    while (stream->Read(&request)) {
      LOG(INFO) << "recv msg " << request.message();
      response.set_message(request.message());
      stream->Write(response);
      LOG(INFO) << "wrote msg " << response.message();
    }
    return Status::OK;
  }
};

std::unique_ptr<EchoTestService::Stub> MakeStub(const std::string& addr) {
  return EchoTestService::NewStub(
      grpc::CreateChannel(addr, InsecureChannelCredentials()));
}

TEST(ClientForkTest, ClientCallsBeforeAndAfterForkSucceed) {
  grpc_core::Fork::Enable(true);

  int port = grpc_pick_unused_port_or_die();
  std::string addr = absl::StrCat("localhost:", port);

  pid_t server_pid = fork();
  switch (server_pid) {
    case -1:
      GTEST_FAIL() << "failure forking";
    case 0:
    {
      ServiceImpl impl;
      grpc::ServerBuilder builder;
      builder.AddListeningPort(addr, grpc::InsecureServerCredentials());
      builder.RegisterService(&impl);
      std::unique_ptr<Server> server(builder.BuildAndStart());
      server->Wait();
      return;
    }
    default:
      break;
  }

  // NOTE: without this scope, test running with the epoll1 poller will fail.
  {
    std::unique_ptr<EchoTestService::Stub> stub = MakeStub(addr);
    EchoRequest request;
    EchoResponse response;
    ClientContext context;
    context.set_wait_for_ready(true);

    auto stream = stub->BidiStream(&context);

    request.set_message("Hello");
    ASSERT_TRUE(stream->Write(request));
    ASSERT_TRUE(stream->Read(&response));
    ASSERT_EQ(response.message(), request.message());
  }

  pid_t child_client_pid = fork();
  switch (child_client_pid) {
    case -1:
      GTEST_FAIL() << "fork failed";
    case 0:
    {
      VLOG(2) << "In post-fork child";
      EchoRequest request;
      EchoResponse response;
      ClientContext context;
      context.set_wait_for_ready(true);

      std::unique_ptr<EchoTestService::Stub> stub = MakeStub(addr);
      auto stream = stub->BidiStream(&context);

      request.set_message("Hello again from child");
      ASSERT_TRUE(stream->Write(request));
      ASSERT_TRUE(stream->Read(&response));
      ASSERT_EQ(response.message(), request.message());
      exit(0);
    }
    default:
    {
      VLOG(2) << "In post-fork parent";
      EchoRequest request;
      EchoResponse response;
      ClientContext context;
      context.set_wait_for_ready(true);

      std::unique_ptr<EchoTestService::Stub> stub = MakeStub(addr);
      auto stream = stub->BidiStream(&context);

      request.set_message("Hello again from parent");
      EXPECT_TRUE(stream->Write(request));
      EXPECT_TRUE(stream->Read(&response));
      EXPECT_EQ(response.message(), request.message());

      int child_status;
      ASSERT_EQ(waitpid(child_client_pid, &child_status, 0), child_client_pid)
          << "failed to get status of child client";
      ASSERT_EQ(WEXITSTATUS(child_status), 0) << "child did not exit cleanly";
    }
  }

  kill(server_pid, SIGINT);
}

}
}
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  grpc::testing::InitTest(&argc, &argv, true);
  grpc::testing::TestEnvironment env(&argc, argv);
  grpc_init();
  int res = RUN_ALL_TESTS();
  grpc_shutdown();
  return res;
}
#endif
