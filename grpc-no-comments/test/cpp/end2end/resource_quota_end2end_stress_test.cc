// Copyright 2023 gRPC authors.

#include <grpc/grpc.h>
#include <grpc/support/time.h>
#include <grpcpp/client_context.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/support/server_callback.h>

#include <memory>
#include <string>
#include <thread>
#include <utility>
#include <vector>

#include "absl/status/statusor.h"
#include "absl/strings/str_cat.h"
#include "absl/time/time.h"
#include "gtest/gtest.h"
#include "src/core/credentials/transport/fake/fake_credentials.h"
#include "src/core/lib/event_engine/tcp_socket_utils.h"
#include "src/core/lib/experiments/config.h"
#include "src/core/util/notification.h"
#include "src/cpp/server/secure_server_credentials.h"
#include "src/proto/grpc/testing/echo.grpc.pb.h"
#include "test/core/test_util/port.h"
#include "test/core/test_util/test_config.h"
#include "test/cpp/util/credentials.h"

namespace grpc {
namespace testing {
namespace {
constexpr int kResourceQuotaSizeBytes = 1024 * 1024;
constexpr int kPayloadSizeBytes = 1024 * 1024;
constexpr int kNumParallelChannels = 10;
}

class EchoClientUnaryReactor : public grpc::ClientUnaryReactor {
 public:
  EchoClientUnaryReactor(ClientContext* ctx, EchoTestService::Stub* stub,
                         const std::string payload, Status* status)
      : ctx_(ctx), payload_(payload), status_(status) {
    request_.set_message(payload);
    stub->async()->Echo(ctx_, &request_, &response_, this);
    StartCall();
  }

  void Await() { notification_.WaitForNotification(); }

 protected:
  void OnReadInitialMetadataDone(bool ) override {}

  void OnDone(const Status& s) override {
    *status_ = s;
    notification_.Notify();
  }

 private:
  ClientContext* const ctx_;
  EchoRequest request_;
  EchoResponse response_;
  const std::string payload_;
  grpc_core::Notification notification_;
  Status* const status_;
};

class EchoServerUnaryReactor : public ServerUnaryReactor {
 public:
  EchoServerUnaryReactor(CallbackServerContext* ,
                         const EchoRequest* request, EchoResponse* response) {
    response->set_message(request->message());
    Finish(grpc::Status::OK);
  }

 private:
  void OnDone() override { delete this; }
};

class GrpcCallbackServiceImpl : public EchoTestService::CallbackService {
 public:
  ServerUnaryReactor* Echo(CallbackServerContext* context,
                           const EchoRequest* request,
                           EchoResponse* response) override {
    return new EchoServerUnaryReactor(context, request, response);
  }
};

class End2EndResourceQuotaUnaryTest : public ::testing::Test {
 protected:
  End2EndResourceQuotaUnaryTest() {
    int port = grpc_pick_unused_port_or_die();
    server_address_ = absl::StrCat("localhost:", port);
    payload_ = std::string(kPayloadSizeBytes, 'a');
    ServerBuilder builder;
    builder.AddListeningPort(server_address_, InsecureServerCredentials());
    builder.SetResourceQuota(
        grpc::ResourceQuota("TestService").Resize(kResourceQuotaSizeBytes));
    builder.RegisterService(&grpc_service_);
    server_ = builder.BuildAndStart();
  }

  ~End2EndResourceQuotaUnaryTest() override { server_->Shutdown(); }

  void MakeGrpcCall() {
    ClientContext ctx;
    Status status;
    auto stub = EchoTestService::NewStub(
        CreateChannel(server_address_, grpc::InsecureChannelCredentials()));
    ctx.set_wait_for_ready(false);
    EchoClientUnaryReactor reactor(&ctx, stub.get(), payload_, &status);
    reactor.Await();
  }

  void MakeGrpcCalls() {
    std::vector<std::thread> workers;
    workers.reserve(kNumParallelChannels);

    for (int i = 0; i < kNumParallelChannels; ++i) {
      workers.emplace_back([this]() { MakeGrpcCall(); });
    }
    for (int i = 0; i < kNumParallelChannels; ++i) {
      workers[i].join();
    }
  }

  int port_;
  std::unique_ptr<Server> server_;
  string server_address_;
  GrpcCallbackServiceImpl grpc_service_;
  std::string payload_;
};

TEST_F(End2EndResourceQuotaUnaryTest, MultipleUnaryRPCTest) { MakeGrpcCalls(); }

class End2EndConnectionQuotaTest : public ::testing::TestWithParam<int> {
 protected:
  End2EndConnectionQuotaTest() {
    port_ = grpc_pick_unused_port_or_die();
    server_address_ = absl::StrCat("[::]:", port_);
    connect_address_ = absl::StrCat("ipv6:[::1]:", port_);
    payload_ = std::string(kPayloadSizeBytes, 'a');
    ServerBuilder builder;
    builder.AddListeningPort(
        server_address_,
        std::make_shared<SecureServerCredentials>(
            grpc_fake_transport_security_server_credentials_create()));
    builder.AddChannelArgument(GRPC_ARG_SERVER_HANDSHAKE_TIMEOUT_MS, 1000);
    builder.AddChannelArgument(GRPC_ARG_MAX_ALLOWED_INCOMING_CONNECTIONS,
                               GetParam());
    builder.AddChannelArgument(
        GRPC_ARG_HTTP2_MIN_RECV_PING_INTERVAL_WITHOUT_DATA_MS, 10000);
    builder.RegisterService(&grpc_service_);
    server_ = builder.BuildAndStart();
  }

  ~End2EndConnectionQuotaTest() override { server_->Shutdown(); }

  std::unique_ptr<EchoTestService::Stub> CreateGrpcChannelStub() {
    grpc::ChannelArguments args;
    args.SetInt(GRPC_ARG_USE_LOCAL_SUBCHANNEL_POOL, 1);
    args.SetInt(GRPC_ARG_ENABLE_RETRIES, 0);
    args.SetInt(GRPC_ARG_KEEPALIVE_TIME_MS, 20000);
    args.SetInt(GRPC_ARG_KEEPALIVE_TIMEOUT_MS, 10000);
    args.SetInt(GRPC_ARG_HTTP2_MIN_SENT_PING_INTERVAL_WITHOUT_DATA_MS, 15000);
    args.SetInt(GRPC_ARG_KEEPALIVE_PERMIT_WITHOUT_CALLS, 1);

    return EchoTestService::NewStub(CreateCustomChannel(
        connect_address_,
        std::make_shared<FakeTransportSecurityChannelCredentials>(), args));
  }

  void TestExceedingConnectionQuota() {
    const int kNumConnections = 2 * GetParam();
#ifdef GPR_LINUX

    auto connect_address_resolved =
        grpc_event_engine::experimental::URIToResolvedAddress(connect_address_);
    std::vector<std::thread> workers;
    workers.reserve(kNumConnections);
    for (int i = 0; i < kNumConnections; ++i) {
      workers.emplace_back([connect_address_resolved]() {
        int client_fd;
        int one = 1;
        char buf[1024];
        client_fd = socket(AF_INET6, SOCK_STREAM, 0);
        setsockopt(client_fd, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));

        EXPECT_EQ(connect(client_fd,
                          const_cast<struct sockaddr*>(
                              connect_address_resolved->address()),
                          connect_address_resolved->size()),
                  0);

        while (recv(client_fd, buf, 1024, 0) > 0) {
        }
        close(client_fd);
      });
    }
    for (int i = 0; i < kNumConnections; ++i) {
      workers[i].join();
    }
#endif

    std::vector<std::unique_ptr<EchoTestService::Stub>> stubs;
    stubs.reserve(kNumConnections);
    for (int i = 0; i < kNumConnections; i++) {
      stubs.push_back(CreateGrpcChannelStub());
    }
    for (int i = 0; i < kNumConnections; ++i) {
      ClientContext ctx;
      Status status;
      ctx.set_wait_for_ready(false);
      EchoClientUnaryReactor reactor(&ctx, stubs[i].get(), payload_, &status);
      reactor.Await();

      if (i < kNumConnections / 2) {
        EXPECT_TRUE(status.ok());

      } else {

        EXPECT_FALSE(status.ok());
      }
    }
  }

  int port_;
  std::unique_ptr<Server> server_;
  string server_address_;
  string connect_address_;
  GrpcCallbackServiceImpl grpc_service_;
  std::string payload_;
};

TEST_P(End2EndConnectionQuotaTest, ConnectionQuotaTest) {
  TestExceedingConnectionQuota();
}

INSTANTIATE_TEST_SUITE_P(ConnectionQuotaParamTest, End2EndConnectionQuotaTest,
                         ::testing::ValuesIn<int>({10, 100}));

}
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
