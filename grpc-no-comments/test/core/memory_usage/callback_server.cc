
// Copyright 2022 gRPC authors.

#include <grpcpp/grpcpp.h>
#include <grpcpp/security/server_credentials.h>
#include <grpcpp/support/server_callback.h>
#include <grpcpp/support/status.h>
#include <grpcpp/xds_server_builder.h>
#include <signal.h>
#include <unistd.h>

#include <memory>
#include <string>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/log/check.h"
#include "absl/log/log.h"
#include "src/core/ext/transport/chaotic_good/chaotic_good.h"
#include "src/core/transport/endpoint_transport.h"
#include "src/proto/grpc/testing/benchmark_service.grpc.pb.h"
#include "src/proto/grpc/testing/messages.pb.h"
#include "test/core/memory_usage/memstats.h"
#include "test/core/test_util/test_config.h"

ABSL_FLAG(std::string, bind, "", "Bind host:port");
ABSL_FLAG(bool, secure, false, "Use SSL Credentials");
ABSL_FLAG(bool, use_xds, false, "Use xDS");
ABSL_FLAG(bool, chaotic_good, false, "Use chaotic good");

class ServerCallbackImpl final
    : public grpc::testing::BenchmarkService::CallbackService {
 public:
  explicit ServerCallbackImpl(long before_server_memory)
      : before_server_create(before_server_memory) {}

  grpc::ServerUnaryReactor* UnaryCall(
      grpc::CallbackServerContext* context,
      const grpc::testing::SimpleRequest* ,
      grpc::testing::SimpleResponse* ) override {
    auto* reactor = context->DefaultReactor();
    reactor->Finish(grpc::Status::OK);
    return reactor;
  }
  grpc::ServerUnaryReactor* GetBeforeSnapshot(
      grpc::CallbackServerContext* context,
      const grpc::testing::SimpleRequest* ,
      grpc::testing::MemorySize* response) override {
    LOG(INFO) << "BeforeSnapshot RPC CALL RECEIVED";
    response->set_rss(before_server_create);
    auto* reactor = context->DefaultReactor();
    reactor->Finish(grpc::Status::OK);
    return reactor;
  }

 private:
  long before_server_create;
};

static void sigint_handler(int ) { _exit(0); }

int main(int argc, char** argv) {
  absl::ParseCommandLine(argc, argv);
  char* fake_argv[1];
  CHECK_GE(argc, 1);
  fake_argv[0] = argv[0];
  grpc::testing::TestEnvironment env(&argc, argv);
  grpc_init();
  signal(SIGINT, sigint_handler);
  std::string server_address = absl::GetFlag(FLAGS_bind);
  if (server_address.empty()) {
    LOG(ERROR) << "Server: No port entered";
    return 1;
  }
  LOG(INFO) << "Server port: " << server_address;

  long before_server_create = GetMemUsage();
  ServerCallbackImpl callback_server(before_server_create);

  grpc::XdsServerBuilder xds_builder;
  grpc::ServerBuilder normal_builder;
  grpc::ServerBuilder* builder =
      absl::GetFlag(FLAGS_use_xds) ? &xds_builder : &normal_builder;

  if (absl::GetFlag(FLAGS_chaotic_good)) {
    builder->AddChannelArgument(
        GRPC_ARG_PREFERRED_TRANSPORT_PROTOCOLS,
        std::string(grpc_core::chaotic_good::WireFormatPreferences()));
  }

  std::shared_ptr<grpc::ServerCredentials> creds =
      grpc::InsecureServerCredentials();
  if (absl::GetFlag(FLAGS_secure)) {
    LOG(INFO) << "Supposed to be secure, is not yet";

  }
  builder->AddListeningPort(server_address, creds);
  builder->RegisterService(&callback_server);

  std::shared_ptr<grpc::Server> server(builder->BuildAndStart());
  LOG(INFO) << "Server listening on " << server_address;

  server->Wait();
  return 0;
}
