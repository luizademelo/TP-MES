
// Copyright 2019 gRPC authors.

#include <arpa/inet.h>
#include <fcntl.h>
#include <grpc/support/alloc.h>
#include <grpc/support/port_platform.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/support/channel_arguments.h>
#include <inttypes.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/wait.h>
#include <unistd.h>

#include <chrono>
#include <cstdlib>
#include <memory>
#include <string>
#include <thread>

#include "absl/flags/flag.h"
#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/strings/str_format.h"
#include "absl/time/time.h"
#include "src/core/lib/iomgr/port.h"
#include "src/core/lib/iomgr/socket_mutator.h"
#include "src/core/util/crash.h"
#include "src/core/util/string.h"
#include "src/proto/grpc/testing/empty.pb.h"
#include "src/proto/grpc/testing/messages.pb.h"
#include "src/proto/grpc/testing/test.grpc.pb.h"
#include "src/proto/grpc/testing/test.pb.h"
#include "test/cpp/util/test_config.h"
#include "test/cpp/util/test_credentials_provider.h"

ABSL_FLAG(std::string, custom_credentials_type, "",
          "User provided credentials type.");
ABSL_FLAG(std::string, server_uri, "localhost:1000", "Server URI target");
ABSL_FLAG(std::string, induce_fallback_cmd, "exit 1",
          "Shell command to induce fallback, e.g. by unrouting addresses");
ABSL_FLAG(int, fallback_deadline_seconds, 1,
          "Number of seconds to wait for fallback to occur after inducing it");
ABSL_FLAG(std::string, test_case, "",
          "Test case to run. Valid options are:\n\n"
          "fallback_before_startup : fallback before making RPCs to backends"
          "fallback_after_startup : fallback after making RPCs to backends");

#ifdef LINUX_VERSION_CODE
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 37)
#define SOCKET_SUPPORTS_TCP_USER_TIMEOUT
#endif
#endif

#ifdef SOCKET_SUPPORTS_TCP_USER_TIMEOUT
using grpc::testing::GrpclbRouteType;
using grpc::testing::SimpleRequest;
using grpc::testing::SimpleResponse;
using grpc::testing::TestService;

namespace {

enum RpcMode {
  FailFast,
  WaitForReady,
};

GrpclbRouteType DoRPCAndGetPath(TestService::Stub* stub, int deadline_seconds,
                                RpcMode rpc_mode) {
  LOG(INFO) << "DoRPCAndGetPath deadline_seconds:" << deadline_seconds
            << " rpc_mode:" << rpc_mode;
  SimpleRequest request;
  SimpleResponse response;
  grpc::ClientContext context;
  if (rpc_mode == WaitForReady) {
    context.set_wait_for_ready(true);
  }
  request.set_fill_grpclb_route_type(true);
  std::chrono::system_clock::time_point deadline =
      std::chrono::system_clock::now() + std::chrono::seconds(deadline_seconds);
  context.set_deadline(deadline);
  grpc::Status s = stub->UnaryCall(&context, request, &response);
  if (!s.ok()) {
    LOG(INFO) << "DoRPCAndGetPath failed. status-message: "
              << s.error_message();
    return GrpclbRouteType::GRPCLB_ROUTE_TYPE_UNKNOWN;
  }
  CHECK(response.grpclb_route_type() ==
            GrpclbRouteType::GRPCLB_ROUTE_TYPE_BACKEND ||
        response.grpclb_route_type() ==
            GrpclbRouteType::GRPCLB_ROUTE_TYPE_FALLBACK);
  LOG(INFO) << "DoRPCAndGetPath done. grpclb_route_type:"
            << response.grpclb_route_type();
  return response.grpclb_route_type();
}

GrpclbRouteType DoRPCAndGetPath(TestService::Stub* stub, int deadline_seconds) {
  return DoRPCAndGetPath(stub, deadline_seconds, FailFast);
}

bool TcpUserTimeoutMutateFd(int fd, grpc_socket_mutator* ) {
  int timeout = 20000;
  LOG(INFO) << "Setting socket option TCP_USER_TIMEOUT on fd: " << fd;
  if (0 != setsockopt(fd, IPPROTO_TCP, TCP_USER_TIMEOUT, &timeout,
                      sizeof(timeout))) {
    grpc_core::Crash("Failed to set socket option TCP_USER_TIMEOUT");
  }
  int newval;
  socklen_t len = sizeof(newval);
  if (0 != getsockopt(fd, IPPROTO_TCP, TCP_USER_TIMEOUT, &newval, &len) ||
      newval != timeout) {
    grpc_core::Crash("Failed to get expected socket option TCP_USER_TIMEOUT");
  }
  return true;
}

int TcpUserTimeoutCompare(grpc_socket_mutator* ,
                          grpc_socket_mutator* ) {
  return 0;
}

void TcpUserTimeoutDestroy(grpc_socket_mutator* mutator) { delete mutator; }

const grpc_socket_mutator_vtable kTcpUserTimeoutMutatorVtable =
    grpc_socket_mutator_vtable{TcpUserTimeoutMutateFd, TcpUserTimeoutCompare,
                               TcpUserTimeoutDestroy, nullptr};

std::unique_ptr<TestService::Stub> CreateFallbackTestStub() {
  grpc::ChannelArguments channel_args;
  grpc_socket_mutator* tcp_user_timeout_mutator = new grpc_socket_mutator();
  grpc_socket_mutator_init(tcp_user_timeout_mutator,
                           &kTcpUserTimeoutMutatorVtable);
  channel_args.SetSocketMutator(tcp_user_timeout_mutator);

  channel_args.SetInt(GRPC_ARG_SERVICE_CONFIG_DISABLE_RESOLUTION, 0);
  std::shared_ptr<grpc::ChannelCredentials> channel_creds =
      grpc::testing::GetCredentialsProvider()->GetChannelCredentials(
          absl::GetFlag(FLAGS_custom_credentials_type), &channel_args);
  return TestService::NewStub(grpc::CreateCustomChannel(
      absl::GetFlag(FLAGS_server_uri), channel_creds, channel_args));
}

void RunCommand(const std::string& command) {
  LOG(INFO) << "RunCommand: |" << command << "|";
  int out = std::system(command.c_str());
  if (WIFEXITED(out)) {
    int code = WEXITSTATUS(out);
    if (code != 0) {
      grpc_core::Crash(
          absl::StrFormat("RunCommand failed exit code:%d command:|%s|", code,
                          command.c_str()));
    }
  } else {
    grpc_core::Crash(
        absl::StrFormat("RunCommand failed command:|%s|", command.c_str()));
  }
}

void WaitForFallbackAndDoRPCs(TestService::Stub* stub) {
  int fallback_retry_count = 0;
  bool fallback = false;
  absl::Time fallback_deadline =
      absl::Now() +
      absl::Seconds(absl::GetFlag(FLAGS_fallback_deadline_seconds));
  while (absl::Now() < fallback_deadline) {
    GrpclbRouteType grpclb_route_type = DoRPCAndGetPath(stub, 1);
    if (grpclb_route_type == GrpclbRouteType::GRPCLB_ROUTE_TYPE_BACKEND) {
      LOG(ERROR) << "Got grpclb route type backend. Backends are "
                    "supposed to be unreachable, so this test is broken";
      CHECK(0);
    }
    if (grpclb_route_type == GrpclbRouteType::GRPCLB_ROUTE_TYPE_FALLBACK) {
      LOG(INFO) << "Made one successful RPC to a fallback. Now expect the same "
                   "for the rest.";
      fallback = true;
      break;
    } else {
      LOG(ERROR) << "Retryable RPC failure on iteration: "
                 << fallback_retry_count;
    }
    fallback_retry_count++;
  }
  if (!fallback) {
    LOG(ERROR) << "Didn't fall back within deadline";
    CHECK(0);
  }
  for (int i = 0; i < 30; i++) {
    GrpclbRouteType grpclb_route_type = DoRPCAndGetPath(stub, 20);
    CHECK(grpclb_route_type == GrpclbRouteType::GRPCLB_ROUTE_TYPE_FALLBACK);
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}

void DoFallbackBeforeStartupTest() {
  std::unique_ptr<TestService::Stub> stub = CreateFallbackTestStub();
  RunCommand(absl::GetFlag(FLAGS_induce_fallback_cmd));
  WaitForFallbackAndDoRPCs(stub.get());
}

void DoFallbackAfterStartupTest() {
  std::unique_ptr<TestService::Stub> stub = CreateFallbackTestStub();
  GrpclbRouteType grpclb_route_type = DoRPCAndGetPath(stub.get(), 20);
  CHECK(grpclb_route_type == GrpclbRouteType::GRPCLB_ROUTE_TYPE_BACKEND);
  RunCommand(absl::GetFlag(FLAGS_induce_fallback_cmd));
  WaitForFallbackAndDoRPCs(stub.get());
}

}

int main(int argc, char** argv) {
  grpc::testing::InitTest(&argc, &argv, true);
  LOG(INFO) << "Testing: " << absl::GetFlag(FLAGS_test_case);
  if (absl::GetFlag(FLAGS_test_case) == "fallback_before_startup") {
    DoFallbackBeforeStartupTest();
    LOG(INFO) << "DoFallbackBeforeStartup done!";
  } else if (absl::GetFlag(FLAGS_test_case) == "fallback_after_startup") {
    DoFallbackAfterStartupTest();
    LOG(INFO) << "DoFallbackBeforeStartup done!";
  } else {
    grpc_core::Crash(absl::StrFormat("Invalid test case: %s",
                                     absl::GetFlag(FLAGS_test_case).c_str()));
  }
}

#else

int main(int argc, char** argv) {
  grpc::testing::InitTest(&argc, &argv, true);
  grpc_core::Crash(
      "This test requires TCP_USER_TIMEOUT, which isn't available");
}

#endif
