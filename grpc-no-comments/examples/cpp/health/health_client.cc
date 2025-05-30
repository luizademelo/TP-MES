
/*
 *
 * Copyright 2024 gRPC authors.
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

#include <condition_variable>
#include <iostream>
#include <memory>
#include <mutex>
#include <string>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/log/initialize.h"

#ifdef BAZEL_BUILD
#include "examples/protos/helloworld.grpc.pb.h"
#include "src/proto/grpc/health/v1/health.grpc.pb.h"
#else
#include "health.grpc.pb.h"
#include "helloworld.grpc.pb.h"
#endif

ABSL_FLAG(std::string, target, "localhost:50051", "Server address");

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using grpc::health::v1::Health;
using grpc::health::v1::HealthCheckRequest;
using grpc::health::v1::HealthCheckResponse;
using helloworld::Greeter;
using helloworld::HelloReply;
using helloworld::HelloRequest;

class GreeterClient {
 public:
  GreeterClient(std::shared_ptr<Channel> channel)
      : stub_(Greeter::NewStub(channel)),
        health_stub_(Health::NewStub(channel)) {}

  std::string SayHello(const std::string& user) {

    HelloRequest request;
    request.set_name(user);

    HelloReply reply;

    ClientContext context;

    std::mutex mu;
    std::condition_variable cv;
    bool done = false;
    Status status;
    stub_->async()->SayHello(&context, &request, &reply,
                             [&mu, &cv, &done, &status](Status s) {
                               status = std::move(s);
                               std::lock_guard<std::mutex> lock(mu);
                               done = true;
                               cv.notify_one();
                             });

    std::unique_lock<std::mutex> lock(mu);
    while (!done) {
      cv.wait(lock);
    }

    if (status.ok()) {
      return reply.message();
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return "RPC failed";
    }
  }

  void CheckHealth(const std::string& message) {
    ClientContext context;
    HealthCheckResponse response;
    Status status = health_stub_->Check(
        &context, HealthCheckRequest::default_instance(), &response);
    if (!status.ok()) {
      std::cerr << "Failed to check service health: " << status.error_code()
                << ": " << status.error_message() << "\n";
      return;
    }
    std::cout << message << ": status: "
              << HealthCheckResponse::ServingStatus_Name(response.status())
              << "\n";
  }

 private:
  std::unique_ptr<Greeter::Stub> stub_;
  std::unique_ptr<Health::Stub> health_stub_;
};

int main(int argc, char** argv) {
  absl::ParseCommandLine(argc, argv);
  absl::InitializeLog();

  std::string target_str = absl::GetFlag(FLAGS_target);

  grpc::ChannelArguments args;
  args.SetServiceConfigJSON(
      "{\"healthCheckConfig\": "
      "{\"serviceName\": \"\"}}");
  GreeterClient greeter(grpc::CreateCustomChannel(
      target_str, grpc::InsecureChannelCredentials(), args));
  std::string user = "world";
  greeter.CheckHealth("Before call");
  std::string reply = greeter.SayHello(user);
  std::cout << "Greeter received: " << reply << std::endl;
  greeter.CheckHealth("After call");
  reply = greeter.SayHello(user);
  std::cout << "Greeter received: " << reply << std::endl;
  greeter.CheckHealth("After second call");
  return 0;
}
