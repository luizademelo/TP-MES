
/*
 *
 * Copyright 2015 gRPC authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <grpcpp/grpcpp.h>

#include <iostream>
#include <memory>
#include <string>

#ifdef BAZEL_BUILD
#include "examples/protos/helloworld.grpc.pb.h"
#else
#include "helloworld.grpc.pb.h"
#endif
#include "absl/flags/parse.h"
#include "absl/log/initialize.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using helloworld::Greeter;
using helloworld::HelloReply;
using helloworld::HelloRequest;

class CustomHeaderClient {
 public:
  CustomHeaderClient(std::shared_ptr<Channel> channel)
      : stub_(Greeter::NewStub(channel)) {}

  std::string SayHello(const std::string& user) {

    HelloRequest request;
    request.set_name(user);

    HelloReply reply;

    ClientContext context;

    context.AddMetadata("custom-header", "Custom Value");

    char bytes[8] = {'\0', '\1', '\2', '\3', '\4', '\5', '\6', '\7'};
    context.AddMetadata("custom-bin", std::string(bytes, 8));

    Status status = stub_->SayHello(&context, request, &reply);

    if (status.ok()) {
      std::cout << "Client received initial metadata from server: "
                << context.GetServerInitialMetadata()
                       .find("custom-server-metadata")
                       ->second
                << std::endl;
      std::cout << "Client received trailing metadata from server: "
                << context.GetServerTrailingMetadata()
                       .find("custom-trailing-metadata")
                       ->second
                << std::endl;
      return reply.message();
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return "RPC failed";
    }
  }

 private:
  std::unique_ptr<Greeter::Stub> stub_;
};

int main(int argc, char** argv) {
  absl::ParseCommandLine(argc, argv);
  absl::InitializeLog();

  CustomHeaderClient greeter(grpc::CreateChannel(
      "localhost:50051", grpc::InsecureChannelCredentials()));
  std::string user("world");
  std::string reply = greeter.SayHello(user);
  std::cout << "Client received message: " << reply << std::endl;
  return 0;
}
