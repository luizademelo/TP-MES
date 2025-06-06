
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
#include "absl/log/log.h"
#include "absl/memory/memory.h"
#include "gtest/gtest.h"
#include "src/core/util/crash.h"
#include "src/proto/grpc/testing/duplicate/echo_duplicate.grpc.pb.h"
#include "src/proto/grpc/testing/echo.grpc.pb.h"
#include "test/core/test_util/port.h"
#include "test/core/test_util/test_config.h"
#include "test/cpp/util/subprocess.h"

using grpc::testing::EchoRequest;
using grpc::testing::EchoResponse;

static std::string g_root;

namespace grpc {
namespace testing {

namespace {

class ServiceImpl final : public grpc::testing::EchoTestService::Service {
 public:
  ServiceImpl() : bidi_stream_count_(0), response_stream_count_(0) {}

  Status BidiStream(
      ServerContext* ,
      ServerReaderWriter<EchoResponse, EchoRequest>* stream) override {
    bidi_stream_count_++;
    EchoRequest request;
    EchoResponse response;
    while (stream->Read(&request)) {
      LOG(INFO) << "recv msg " << request.message();
      response.set_message(request.message());
      stream->Write(response);
      gpr_sleep_until(gpr_time_add(gpr_now(GPR_CLOCK_REALTIME),
                                   gpr_time_from_seconds(1, GPR_TIMESPAN)));
    }
    return Status::OK;
  }

  Status ResponseStream(ServerContext* ,
                        const EchoRequest* ,
                        ServerWriter<EchoResponse>* writer) override {
    EchoResponse response;
    response_stream_count_++;
    for (int i = 0;; i++) {
      std::ostringstream msg;
      msg << "Hello " << i;
      response.set_message(msg.str());
      if (!writer->Write(response)) break;
      gpr_sleep_until(gpr_time_add(gpr_now(GPR_CLOCK_REALTIME),
                                   gpr_time_from_seconds(1, GPR_TIMESPAN)));
    }
    return Status::OK;
  }

  int bidi_stream_count() { return bidi_stream_count_; }

  int response_stream_count() { return response_stream_count_; }

 private:
  int bidi_stream_count_;
  int response_stream_count_;
};

class CrashTest : public ::testing::Test {
 protected:
  CrashTest() {}

  std::unique_ptr<Server> CreateServerAndClient(const std::string& mode) {
    auto port = grpc_pick_unused_port_or_die();
    std::ostringstream addr_stream;
    addr_stream << "localhost:" << port;
    auto addr = addr_stream.str();
    client_ = std::make_unique<SubProcess>(
        std::vector<std::string>({g_root + "/server_crash_test_client",
                                  "--address=" + addr, "--mode=" + mode}));
    CHECK(client_);

    ServerBuilder builder;
    builder.AddListeningPort(addr, grpc::InsecureServerCredentials());
    builder.RegisterService(&service_);
    return builder.BuildAndStart();
  }

  void KillClient() { client_.reset(); }

  bool HadOneBidiStream() { return service_.bidi_stream_count() == 1; }

  bool HadOneResponseStream() { return service_.response_stream_count() == 1; }

 private:
  std::unique_ptr<SubProcess> client_;
  ServiceImpl service_;
};

TEST_F(CrashTest, ResponseStream) {
  auto server = CreateServerAndClient("response");

  gpr_sleep_until(gpr_time_add(gpr_now(GPR_CLOCK_REALTIME),
                               gpr_time_from_seconds(60, GPR_TIMESPAN)));
  KillClient();
  server->Shutdown();
  CHECK(HadOneResponseStream());
}

TEST_F(CrashTest, BidiStream) {
  auto server = CreateServerAndClient("bidi");

  gpr_sleep_until(gpr_time_add(gpr_now(GPR_CLOCK_REALTIME),
                               gpr_time_from_seconds(60, GPR_TIMESPAN)));
  KillClient();
  server->Shutdown();
  CHECK(HadOneBidiStream());
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
  return RUN_ALL_TESTS();
}
