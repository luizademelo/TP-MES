// Copyright 2024 gRPC authors.

#include <grpcpp/grpcpp.h>

#include <iostream>
#include <memory>
#include <string>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/log/initialize.h"
#include "absl/strings/str_format.h"
#include "helper.h"

#ifdef BAZEL_BUILD
#include "examples/protos/helloworld.grpc.pb.h"
#else
#include "helloworld.grpc.pb.h"
#endif

ABSL_FLAG(uint16_t, port, 50051, "Server port for the service");

using grpc::CallbackServerContext;
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerUnaryReactor;
using grpc::Status;
using helloworld::Greeter;
using helloworld::HelloReply;
using helloworld::HelloRequest;

class GreeterServiceImpl final : public Greeter::CallbackService {
  ServerUnaryReactor* SayHello(CallbackServerContext* context,
                               const HelloRequest* request,
                               HelloReply* reply) override {
    std::string prefix("Hello ");
    reply->set_message(prefix + request->name());

    ServerUnaryReactor* reactor = context->DefaultReactor();
    reactor->Finish(Status::OK);
    return reactor;
  }
};

#ifdef BAZEL_BUILD
constexpr char kServerCertPath[] =
    "examples/cpp/auth/credentials/localhost.crt";
constexpr char kServerKeyPath[] = "examples/cpp/auth/credentials/localhost.key";
#else
constexpr char kServerCertPath[] = "credentials/localhost.crt";
constexpr char kServerKeyPath[] = "credentials/localhost.key";
#endif

void RunServer(uint16_t port) {
  std::string server_address = absl::StrFormat("0.0.0.0:%d", port);
  GreeterServiceImpl service;
  ServerBuilder builder;

  grpc::SslServerCredentialsOptions::PemKeyCertPair key_cert_pair = {
      LoadStringFromFile(kServerKeyPath), LoadStringFromFile(kServerCertPath)};
  grpc::SslServerCredentialsOptions ssl_options;
  ssl_options.pem_key_cert_pairs.emplace_back(key_cert_pair);

  builder.AddListeningPort(server_address,
                           grpc::SslServerCredentials(ssl_options));

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
