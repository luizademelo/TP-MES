// Copyright 2023 gRPC authors.

#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

#include <iostream>
#include <memory>
#include <string>
#include <unordered_set>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/log/initialize.h"
#include "absl/strings/str_format.h"
#include "absl/synchronization/mutex.h"

#ifdef BAZEL_BUILD
#include "examples/protos/helloworld.grpc.pb.h"
#include "google/rpc/error_details.pb.h"
#include "src/proto/grpc/status/status.pb.h"
#else
#include "error_details.pb.h"
#include "helloworld.grpc.pb.h"
#include "status.pb.h"
#endif

ABSL_FLAG(uint16_t, port, 50051, "Server port for the service");

using grpc::CallbackServerContext;
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerUnaryReactor;
using grpc::Status;
using grpc::StatusCode;
using helloworld::Greeter;
using helloworld::HelloReply;
using helloworld::HelloRequest;

class GreeterServiceImpl final : public Greeter::CallbackService {
  ServerUnaryReactor* SayHello(CallbackServerContext* context,
                               const HelloRequest* request,
                               HelloReply* reply) override {
    ServerUnaryReactor* reactor = context->DefaultReactor();
    Status status;

    if (CheckRequestDuplicate(request->name())) {

      google::rpc::QuotaFailure quota_failure;
      auto violation = quota_failure.add_violations();
      violation->set_subject("name: " + request->name());
      violation->set_description("Limit one greeting per person");
      google::rpc::Status s;
      s.set_code(static_cast<int>(StatusCode::RESOURCE_EXHAUSTED));
      s.set_message("Request limit exceeded");
      s.add_details()->PackFrom(quota_failure);
      status = Status(StatusCode::RESOURCE_EXHAUSTED, "Request limit exceeded",
                      s.SerializeAsString());
    } else {
      reply->set_message(absl::StrFormat("Hello %s", request->name()));
      status = Status::OK;
    }
    reactor->Finish(status);
    return reactor;
  }

 private:
  bool CheckRequestDuplicate(const std::string& name) {
    absl::MutexLock lock(&mu_);
    return !request_name_set_.insert(name).second;
  }

  absl::Mutex mu_;
  std::unordered_set<std::string> request_name_set_;
};

void RunServer(uint16_t port) {
  std::string server_address = absl::StrFormat("0.0.0.0:%d", port);
  GreeterServiceImpl service;

  grpc::EnableDefaultHealthCheckService(true);
  grpc::reflection::InitProtoReflectionServerBuilderPlugin();
  ServerBuilder builder;

  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());

  builder.RegisterService(&service);

  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  server->Wait();
}

int main(int argc, char** argv) {
  absl::ParseCommandLine(argc, argv);
  absl::InitializeLog();
  RunServer(absl::GetFlag(FLAGS_port));
  return 0;
}
