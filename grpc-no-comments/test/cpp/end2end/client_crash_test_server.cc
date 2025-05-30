
// Copyright 2015 gRPC authors.

#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>

#include <iostream>
#include <memory>
#include <string>

#include "absl/flags/flag.h"
#include "absl/log/log.h"
#include "src/core/util/crash.h"
#include "src/proto/grpc/testing/echo.grpc.pb.h"
#include "test/cpp/util/test_config.h"

ABSL_FLAG(std::string, address, "", "Address to bind to");

using grpc::testing::EchoRequest;
using grpc::testing::EchoResponse;

namespace grpc {
namespace testing {

class ServiceImpl final : public grpc::testing::EchoTestService::Service {
  Status BidiStream(
      ServerContext* ,
      ServerReaderWriter<EchoResponse, EchoRequest>* stream) override {
    EchoRequest request;
    EchoResponse response;
    while (stream->Read(&request)) {
      LOG(INFO) << "recv msg " << request.message();
      response.set_message(request.message());
      stream->Write(response);
    }
    return Status::OK;
  }
};

void RunServer() {
  ServiceImpl service;

  ServerBuilder builder;
  builder.AddListeningPort(absl::GetFlag(FLAGS_address),
                           grpc::InsecureServerCredentials());
  builder.RegisterService(&service);
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << absl::GetFlag(FLAGS_address)
            << std::endl;
  server->Wait();
}
}
}

int main(int argc, char** argv) {
  grpc::testing::InitTest(&argc, &argv, true);
  grpc::testing::RunServer();

  return 0;
}
