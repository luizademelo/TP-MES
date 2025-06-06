
// Copyright 2016 gRPC authors.

#include <grpc/grpc.h>
#include <grpc/support/alloc.h>
#include <grpc/support/port_platform.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/ext/channelz_service_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/security/credentials.h>
#include <grpcpp/security/server_credentials.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>
#include <stdlib.h>
#include <unistd.h>

#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <thread>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/strings/str_cat.h"
#include "gtest/gtest.h"
#include "src/core/util/env.h"
#include "src/cpp/server/channelz/channelz_service.h"
#include "src/proto/grpc/testing/test.grpc.pb.h"
#include "test/core/test_util/port.h"
#include "test/core/test_util/test_config.h"
#include "test/cpp/util/subprocess.h"
#include "test/cpp/util/test_credentials_provider.h"

static std::string g_root;

namespace {
using grpc::ClientContext;
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
}

std::string server_address("0.0.0.0:10000");
std::string custom_credentials_type("INSECURE_CREDENTIALS");
std::string sampling_times = "2";
std::string sampling_interval_seconds = "3";
std::string output_json("output.json");

class EchoServerImpl final : public grpc::testing::TestService::Service {
  Status EmptyCall(ServerContext* ,
                   const grpc::testing::Empty* ,
                   grpc::testing::Empty* ) override {
    return Status::OK;
  }
};

void RunClient(const std::string& client_id, gpr_event* done_ev) {
  grpc::ChannelArguments channel_args;
  std::shared_ptr<grpc::ChannelCredentials> channel_creds =
      grpc::testing::GetCredentialsProvider()->GetChannelCredentials(
          custom_credentials_type, &channel_args);
  std::unique_ptr<grpc::testing::TestService::Stub> stub =
      grpc::testing::TestService::NewStub(
          grpc::CreateChannel(server_address, channel_creds));
  LOG(INFO) << "Client " << client_id << " is echoing!";
  while (true) {
    if (gpr_event_wait(done_ev, grpc_timeout_seconds_to_deadline(1)) !=
        nullptr) {
      return;
    }
    grpc::testing::Empty request;
    grpc::testing::Empty response;
    ClientContext context;
    Status status = stub->EmptyCall(&context, request, &response);
    if (!status.ok()) {
      LOG(ERROR) << "Client echo failed.";
      CHECK(0);
    }
  }
}

bool WaitForConnection(int wait_server_seconds) {
  grpc::ChannelArguments channel_args;
  std::shared_ptr<grpc::ChannelCredentials> channel_creds =
      grpc::testing::GetCredentialsProvider()->GetChannelCredentials(
          custom_credentials_type, &channel_args);
  auto channel = grpc::CreateChannel(server_address, channel_creds);
  return channel->WaitForConnected(
      grpc_timeout_seconds_to_deadline(wait_server_seconds));
}

TEST(ChannelzSamplerTest, SimpleTest) {

  grpc::channelz::experimental::InitChannelzService();
  EchoServerImpl service;
  ServerBuilder builder;
  auto server_creds =
      grpc::testing::GetCredentialsProvider()->GetServerCredentials(
          custom_credentials_type);
  builder.AddListeningPort(server_address, server_creds);
  builder.RegisterService(&service);
  std::unique_ptr<Server> server(builder.BuildAndStart());
  LOG(INFO) << "Server listening on " << server_address;
  const int kWaitForServerSeconds = 10;
  ASSERT_TRUE(WaitForConnection(kWaitForServerSeconds));

  gpr_event done_ev1, done_ev2;
  gpr_event_init(&done_ev1);
  gpr_event_init(&done_ev2);
  std::thread client_thread_1(RunClient, "1", &done_ev1);
  std::thread client_thread_2(RunClient, "2", &done_ev2);

  grpc::SubProcess* test_driver = new grpc::SubProcess(
      {g_root + "/channelz_sampler", "--server_address=" + server_address,
       "--custom_credentials_type=" + custom_credentials_type,
       "--sampling_times=" + sampling_times,
       "--sampling_interval_seconds=" + sampling_interval_seconds,
       "--output_json=" + output_json});
  int status = test_driver->Join();
  if (WIFEXITED(status)) {
    if (WEXITSTATUS(status)) {
      LOG(ERROR) << "Channelz sampler test test-runner exited with code "
                 << WEXITSTATUS(status);
      CHECK(0);
    }
  } else if (WIFSIGNALED(status)) {
    LOG(ERROR) << "Channelz sampler test test-runner ended from signal "
               << WTERMSIG(status);
    CHECK(0);
  } else {
    LOG(ERROR) << "Channelz sampler test test-runner ended with unknown status "
               << status;
    CHECK(0);
  }
  delete test_driver;
  gpr_event_set(&done_ev1, reinterpret_cast<void*>(1));
  gpr_event_set(&done_ev2, reinterpret_cast<void*>(1));
  client_thread_1.join();
  client_thread_2.join();
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  std::string me = argv[0];
  auto lslash = me.rfind('/');
  if (lslash != std::string::npos) {
    g_root = me.substr(0, lslash);
  } else {
    g_root = ".";
  }

  server_address = absl::StrCat("0.0.0.0:", grpc_pick_unused_port_or_die());
  int ret = RUN_ALL_TESTS();
  return ret;
}
