
/*
 *
 * Copyright 2023 gRPC authors.
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
#include <vector>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/log/initialize.h"

#ifdef BAZEL_BUILD
#include "examples/protos/helloworld.grpc.pb.h"
#include "examples/protos/route_guide.grpc.pb.h"
#else
#include "helloworld.grpc.pb.h"
#include "route_guide.grpc.pb.h"
#endif

ABSL_FLAG(std::string, target, "localhost:50051", "Server address");

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

int main(int argc, char** argv) {
  absl::ParseCommandLine(argc, argv);
  absl::InitializeLog();

  std::string target_str = absl::GetFlag(FLAGS_target);

  auto channel =
      grpc::CreateChannel(target_str, grpc::InsecureChannelCredentials());

  std::mutex mu;
  std::condition_variable cv;
  int done_count = 0;

  std::unique_lock<std::mutex> lock(mu);

  ClientContext hello_context;
  helloworld::HelloRequest hello_request;
  helloworld::HelloReply hello_response;
  Status hello_status;

  ClientContext feature_context;
  routeguide::Point feature_request;
  routeguide::Feature feature_response;
  Status feature_status;

  hello_request.set_name("user");
  helloworld::Greeter::NewStub(channel)->async()->SayHello(
      &hello_context, &hello_request, &hello_response, [&](Status status) {
        std::lock_guard<std::mutex> lock(mu);
        done_count++;
        hello_status = std::move(status);
        cv.notify_all();
      });

  feature_request.set_latitude(50);
  feature_request.set_longitude(100);
  routeguide::RouteGuide::NewStub(channel)->async()->GetFeature(
      &feature_context, &feature_request, &feature_response,
      [&](Status status) {
        std::lock_guard<std::mutex> lock(mu);
        done_count++;
        feature_status = std::move(status);
        cv.notify_all();
      });

  cv.wait(lock, [&]() { return done_count == 2; });
  if (hello_status.ok()) {
    std::cout << "Greeter received: " << hello_response.message() << std::endl;
  } else {
    std::cerr << "Greeter failed: " << hello_status.error_message()
              << std::endl;
  }
  if (feature_status.ok()) {
    std::cout << "Found feature: " << feature_response.name() << std::endl;
  } else {
    std::cerr << "Getting feature failed: " << feature_status.error_message()
              << std::endl;
  }
  return 0;
}
