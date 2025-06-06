
// Copyright 2015 gRPC authors.

#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>

#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#include "absl/flags/flag.h"
#include "absl/log/check.h"
#include "absl/log/log.h"
#include "src/core/util/crash.h"
#include "src/proto/grpc/testing/echo.grpc.pb.h"
#include "test/cpp/util/test_config.h"

ABSL_FLAG(std::string, address, "", "Address to connect to");
ABSL_FLAG(std::string, mode, "", "Test mode to use");

using grpc::testing::EchoRequest;
using grpc::testing::EchoResponse;

int main(int argc, char** argv) {
  grpc::testing::InitTest(&argc, &argv, true);
  auto stub = grpc::testing::EchoTestService::NewStub(grpc::CreateChannel(
      absl::GetFlag(FLAGS_address), grpc::InsecureChannelCredentials()));

  EchoRequest request;
  EchoResponse response;
  grpc::ClientContext context;
  context.set_wait_for_ready(true);

  if (absl::GetFlag(FLAGS_mode) == "bidi") {
    auto stream = stub->BidiStream(&context);
    for (int i = 0;; i++) {
      std::ostringstream msg;
      msg << "Hello " << i;
      request.set_message(msg.str());
      CHECK(stream->Write(request));
      CHECK(stream->Read(&response));
      CHECK(response.message() == request.message());
    }
  } else if (absl::GetFlag(FLAGS_mode) == "response") {
    EchoRequest request;
    request.set_message("Hello");
    auto stream = stub->ResponseStream(&context, request);
    for (;;) {
      CHECK(stream->Read(&response));
    }
  } else {
    LOG(ERROR) << "invalid test mode '" << absl::GetFlag(FLAGS_mode) << "'";
    return 1;
  }
}
