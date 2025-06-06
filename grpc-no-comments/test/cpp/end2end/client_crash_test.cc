
// Copyright 2015 gRPC authors.

#include <grpc/grpc.h>
#include <grpc/support/time.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>

#include "absl/log/check.h"
#include "absl/memory/memory.h"
#include "gtest/gtest.h"
#include "src/core/util/crash.h"
#include "src/proto/grpc/testing/duplicate/echo_duplicate.grpc.pb.h"
#include "src/proto/grpc/testing/echo.grpc.pb.h"
#include "test/core/test_util/port.h"
#include "test/core/test_util/test_config.h"
#include "test/cpp/util/subprocess.h"

static std::string g_root;

namespace grpc {
namespace testing {

namespace {

class CrashTest : public ::testing::Test {
 protected:
  CrashTest() {}

  std::unique_ptr<grpc::testing::EchoTestService::Stub> CreateServerAndStub() {
    auto port = grpc_pick_unused_port_or_die();
    std::ostringstream addr_stream;
    addr_stream << "localhost:" << port;
    auto addr = addr_stream.str();
    server_ = std::make_unique<SubProcess>(std::vector<std::string>({
        g_root + "/client_crash_test_server",
        "--address=" + addr,
    }));
    CHECK(server_);
    return grpc::testing::EchoTestService::NewStub(
        grpc::CreateChannel(addr, InsecureChannelCredentials()));
  }

  void KillServer() { server_.reset(); }

 private:
  std::unique_ptr<SubProcess> server_;
};

TEST_F(CrashTest, KillBeforeWrite) {
  auto stub = CreateServerAndStub();

  EchoRequest request;
  EchoResponse response;
  ClientContext context;
  context.set_wait_for_ready(true);

  auto stream = stub->BidiStream(&context);

  request.set_message("Hello");
  EXPECT_TRUE(stream->Write(request));
  EXPECT_TRUE(stream->Read(&response));
  EXPECT_EQ(response.message(), request.message());

  KillServer();

  request.set_message("You should be dead");

  stream->Write(request);

  EXPECT_FALSE(stream->Read(&response));

  EXPECT_FALSE(stream->Finish().ok());
}

TEST_F(CrashTest, KillAfterWrite) {
  auto stub = CreateServerAndStub();

  EchoRequest request;
  EchoResponse response;
  ClientContext context;
  context.set_wait_for_ready(true);

  auto stream = stub->BidiStream(&context);

  request.set_message("Hello");
  EXPECT_TRUE(stream->Write(request));
  EXPECT_TRUE(stream->Read(&response));
  EXPECT_EQ(response.message(), request.message());

  request.set_message("I'm going to kill you");
  EXPECT_TRUE(stream->Write(request));

  KillServer();

  stream->Read(&response);

  EXPECT_FALSE(stream->Finish().ok());
}

}

}
}

int main(int argc, char** argv) {
  std::string me = argv[0];
  auto lslash = me.rfind('/');
  if (lslash != std::string::npos) {
    g_root = me.substr(0, lslash);
  } else {
    g_root = ".";
  }

  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);

  for (int i = 0; i < 3; i++) {
    if (RUN_ALL_TESTS() != 0) {
      return 1;
    }
  }
  return 0;
}
