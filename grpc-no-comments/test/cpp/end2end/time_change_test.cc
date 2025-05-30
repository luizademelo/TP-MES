
// Copyright 2019 gRPC authors.

#include <grpc/grpc.h>
#include <grpc/support/time.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>
#include <sys/time.h>

#include <thread>

#include "absl/log/check.h"
#include "absl/memory/memory.h"
#include "gtest/gtest.h"
#include "src/core/lib/iomgr/timer.h"
#include "src/core/util/crash.h"
#include "src/proto/grpc/testing/echo.grpc.pb.h"
#include "test/core/test_util/port.h"
#include "test/core/test_util/test_config.h"
#include "test/cpp/end2end/test_service_impl.h"
#include "test/cpp/util/subprocess.h"

static std::string g_root;

static gpr_mu g_mu;
extern gpr_timespec (*gpr_now_impl)(gpr_clock_type clock_type);
gpr_timespec (*gpr_now_impl_orig)(gpr_clock_type clock_type) = gpr_now_impl;
static int g_time_shift_sec = 0;
static int g_time_shift_nsec = 0;
static gpr_timespec now_impl(gpr_clock_type clock) {
  auto ts = gpr_now_impl_orig(clock);

  if (clock != GPR_CLOCK_REALTIME) {
    return ts;
  }
  CHECK_GE(ts.tv_nsec, 0);
  CHECK_LT(ts.tv_nsec, GPR_NS_PER_SEC);
  gpr_mu_lock(&g_mu);
  ts.tv_sec += g_time_shift_sec;
  ts.tv_nsec += g_time_shift_nsec;
  gpr_mu_unlock(&g_mu);
  if (ts.tv_nsec >= GPR_NS_PER_SEC) {
    ts.tv_nsec -= GPR_NS_PER_SEC;
    ++ts.tv_sec;
  } else if (ts.tv_nsec < 0) {
    --ts.tv_sec;
    ts.tv_nsec = GPR_NS_PER_SEC + ts.tv_nsec;
  }
  return ts;
}

static void set_now_offset(int msecs) {
  gpr_mu_lock(&g_mu);
  g_time_shift_sec = msecs / 1000;
  g_time_shift_nsec = (msecs % 1000) * 1e6;
  gpr_mu_unlock(&g_mu);
}

static void reset_now_offset() {
  gpr_mu_lock(&g_mu);
  g_time_shift_sec = 0;
  g_time_shift_nsec = 0;
  gpr_mu_unlock(&g_mu);
}

namespace grpc {
namespace testing {

namespace {

TEST(TimespecTest, GprNowInvalidClockType) {

  gpr_clock_type invalid_clock_type = static_cast<gpr_clock_type>(32641);
  EXPECT_DEATH(gpr_now(invalid_clock_type), ".*");
}

TEST(TimespecTest, GprTimeAddNegativeNs) {
  gpr_timespec now = gpr_now(GPR_CLOCK_MONOTONIC);
  gpr_timespec bad_ts = {1, -1000, GPR_TIMESPAN};
  EXPECT_DEATH(gpr_time_add(now, bad_ts), ".*");
}

TEST(TimespecTest, GprTimeSubNegativeNs) {

  gpr_timespec now = gpr_now(GPR_CLOCK_MONOTONIC);
  gpr_timespec bad_ts = {1, -1000, GPR_TIMESPAN};
  EXPECT_DEATH(gpr_time_sub(now, bad_ts), ".*");
}

TEST(TimespecTest, GrpcNegativeMillisToTimespec) {

  gpr_timespec ts =
      grpc_core::Timestamp::FromMillisecondsAfterProcessEpoch(-1500)
          .as_timespec(GPR_CLOCK_MONOTONIC);
  CHECK(ts.tv_sec = -2);
  CHECK(ts.tv_nsec = 5e8);
  CHECK_EQ(ts.clock_type, GPR_CLOCK_MONOTONIC);
}

class TimeChangeTest : public ::testing::Test {
 protected:
  TimeChangeTest() {}

  static void SetUpTestSuite() {
    auto port = grpc_pick_unused_port_or_die();
    std::ostringstream addr_stream;
    addr_stream << "localhost:" << port;
    server_address_ = addr_stream.str();
    server_ = std::make_unique<SubProcess>(std::vector<std::string>({
        g_root + "/client_crash_test_server",
        "--address=" + server_address_,
    }));
    CHECK(server_);

    auto channel =
        grpc::CreateChannel(server_address_, InsecureChannelCredentials());
    CHECK(channel);
    EXPECT_TRUE(channel->WaitForConnected(
        grpc_timeout_milliseconds_to_deadline(30000)));
  }

  static void TearDownTestSuite() { server_.reset(); }

  void SetUp() override {
    channel_ =
        grpc::CreateChannel(server_address_, InsecureChannelCredentials());
    CHECK(channel_);
    stub_ = grpc::testing::EchoTestService::NewStub(channel_);
  }

  void TearDown() override { reset_now_offset(); }

  std::unique_ptr<grpc::testing::EchoTestService::Stub> CreateStub() {
    return grpc::testing::EchoTestService::NewStub(channel_);
  }

  std::shared_ptr<Channel> GetChannel() { return channel_; }

  const int TIME_OFFSET1 = 20123;
  const int TIME_OFFSET2 = 5678;

 private:
  static std::string server_address_;
  static std::unique_ptr<SubProcess> server_;
  std::shared_ptr<Channel> channel_;
  std::unique_ptr<grpc::testing::EchoTestService::Stub> stub_;
};
std::string TimeChangeTest::server_address_;
std::unique_ptr<SubProcess> TimeChangeTest::server_;

TEST_F(TimeChangeTest, TimeJumpForwardBeforeStreamCreated) {
  EchoRequest request;
  EchoResponse response;
  ClientContext context;
  context.set_deadline(grpc_timeout_milliseconds_to_deadline(5000));
  context.AddMetadata(kServerResponseStreamsToSend, "1");

  auto channel = GetChannel();
  CHECK(channel);
  EXPECT_TRUE(
      channel->WaitForConnected(grpc_timeout_milliseconds_to_deadline(5000)));
  auto stub = CreateStub();

  set_now_offset(TIME_OFFSET1);
  auto stream = stub->BidiStream(&context);
  request.set_message("Hello");
  EXPECT_TRUE(stream->Write(request));

  EXPECT_TRUE(stream->WritesDone());
  EXPECT_TRUE(stream->Read(&response));

  auto status = stream->Finish();
  EXPECT_TRUE(status.ok());
}

TEST_F(TimeChangeTest, TimeJumpBackBeforeStreamCreated) {
  EchoRequest request;
  EchoResponse response;
  ClientContext context;
  context.set_deadline(grpc_timeout_milliseconds_to_deadline(5000));
  context.AddMetadata(kServerResponseStreamsToSend, "1");

  auto channel = GetChannel();
  CHECK(channel);
  EXPECT_TRUE(
      channel->WaitForConnected(grpc_timeout_milliseconds_to_deadline(5000)));
  auto stub = CreateStub();

  set_now_offset(-TIME_OFFSET1);
  auto stream = stub->BidiStream(&context);
  request.set_message("Hello");
  EXPECT_TRUE(stream->Write(request));

  EXPECT_TRUE(stream->WritesDone());
  EXPECT_TRUE(stream->Read(&response));
  EXPECT_EQ(request.message(), response.message());

  auto status = stream->Finish();
  EXPECT_TRUE(status.ok());
}

TEST_F(TimeChangeTest, TimeJumpForwardAfterStreamCreated) {
  EchoRequest request;
  EchoResponse response;
  ClientContext context;
  context.set_deadline(grpc_timeout_milliseconds_to_deadline(5000));
  context.AddMetadata(kServerResponseStreamsToSend, "2");

  auto channel = GetChannel();
  CHECK(channel);
  EXPECT_TRUE(
      channel->WaitForConnected(grpc_timeout_milliseconds_to_deadline(5000)));
  auto stub = CreateStub();

  auto stream = stub->BidiStream(&context);

  request.set_message("Hello");
  EXPECT_TRUE(stream->Write(request));
  EXPECT_TRUE(stream->Read(&response));

  set_now_offset(TIME_OFFSET1);

  request.set_message("World");
  EXPECT_TRUE(stream->Write(request));
  EXPECT_TRUE(stream->WritesDone());
  EXPECT_TRUE(stream->Read(&response));

  auto status = stream->Finish();
  EXPECT_TRUE(status.ok());
}

TEST_F(TimeChangeTest, TimeJumpBackAfterStreamCreated) {
  EchoRequest request;
  EchoResponse response;
  ClientContext context;
  context.set_deadline(grpc_timeout_milliseconds_to_deadline(5000));
  context.AddMetadata(kServerResponseStreamsToSend, "2");

  auto channel = GetChannel();
  CHECK(channel);
  EXPECT_TRUE(
      channel->WaitForConnected(grpc_timeout_milliseconds_to_deadline(5000)));
  auto stub = CreateStub();

  auto stream = stub->BidiStream(&context);

  request.set_message("Hello");
  EXPECT_TRUE(stream->Write(request));
  EXPECT_TRUE(stream->Read(&response));

  set_now_offset(-TIME_OFFSET1);

  request.set_message("World");
  EXPECT_TRUE(stream->Write(request));
  EXPECT_TRUE(stream->WritesDone());
  EXPECT_TRUE(stream->Read(&response));

  auto status = stream->Finish();
  EXPECT_TRUE(status.ok());
}

TEST_F(TimeChangeTest, TimeJumpForwardAndBackDuringCall) {
  EchoRequest request;
  EchoResponse response;
  ClientContext context;
  context.set_deadline(grpc_timeout_milliseconds_to_deadline(5000));
  context.AddMetadata(kServerResponseStreamsToSend, "2");

  auto channel = GetChannel();
  CHECK(channel);

  EXPECT_TRUE(
      channel->WaitForConnected(grpc_timeout_milliseconds_to_deadline(5000)));
  auto stub = CreateStub();
  auto stream = stub->BidiStream(&context);

  request.set_message("Hello");
  EXPECT_TRUE(stream->Write(request));

  set_now_offset(-TIME_OFFSET2);

  EXPECT_TRUE(stream->Read(&response));
  request.set_message("World");

  set_now_offset(TIME_OFFSET1);

  EXPECT_TRUE(stream->Write(request));

  set_now_offset(-TIME_OFFSET2);

  EXPECT_TRUE(stream->WritesDone());

  set_now_offset(-TIME_OFFSET2);

  EXPECT_TRUE(stream->Read(&response));

  set_now_offset(-TIME_OFFSET2);

  auto status = stream->Finish();
  EXPECT_TRUE(status.ok());
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

  gpr_mu_init(&g_mu);
  gpr_now_impl = now_impl;

  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  auto ret = RUN_ALL_TESTS();
  return ret;
}
