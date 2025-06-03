Here's the commented version of the code:

```c++
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

// Include necessary headers
#include <grpcpp/grpcpp.h>  // Main gRPC C++ library
#include <condition_variable>  // For thread synchronization
#include <iostream>  // For console I/O
#include <memory>    // For smart pointers
#include <mutex>     // For mutex locks
#include <string>    // For string handling
#include <vector>    // For vector container

// Include ABSL (Abseil) libraries for command line parsing and logging
#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/log/initialize.h"

// Include protocol buffer generated files
// Different paths for Bazel build vs regular build
#ifdef BAZEL_BUILD
#include "examples/protos/helloworld.grpc.pb.h"
#include "examples/protos/route_guide.grpc.pb.h"
#else
#include "helloworld.grpc.pb.h"
#include "route_guide.grpc.pb.h"
#endif

// Define a command line flag for server address with default value
ABSL_FLAG(std::string, target, "localhost:50051", "Server address");

// Using declarations for gRPC components
using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

int main(int argc, char** argv) {
  // Initialize command line parsing and logging
  absl::ParseCommandLine(argc, argv);
  absl::InitializeLog();

  // Get server address from command line flag
  std::string target_str = absl::GetFlag(FLAGS_target);

  // Create insecure gRPC channel to the server
  auto channel =
      grpc::CreateChannel(target_str, grpc::InsecureChannelCredentials());

  // Synchronization primitives for async callbacks
  std::mutex mu;  // Mutex for protecting shared data
  std::condition_variable cv;  // Condition variable for signaling completion
  int done_count = 0;  // Counter for completed async calls

  // Lock the mutex before waiting for async operations
  std::unique_lock<std::mutex> lock(mu);

  // Context and request/response objects for HelloWorld service
  ClientContext hello_context;
  helloworld::HelloRequest hello_request;
  helloworld::HelloReply hello_response;
  Status hello_status;

  // Context and request/response objects for RouteGuide service
  ClientContext feature_context;
  routeguide::Point feature_request;
  routeguide::Feature feature_response;
  Status feature_status;

  // Set up and make async call to HelloWorld service
  hello_request.set_name("user");
  helloworld::Greeter::NewStub(channel)->async()->SayHello(
      &hello_context, &hello_request, &hello_response, [&](Status status) {
        // Callback for HelloWorld service response
        std::lock_guard<std::mutex> lock(mu);
        done_count++;
        hello_status = std::move(status);
        cv.notify_all();  // Notify waiting thread
      });

  // Set up and make async call to RouteGuide service
  feature_request.set_latitude(50);
  feature_request.set_longitude(100);
  routeguide::RouteGuide::NewStub(channel)->async()->GetFeature(
      &feature_context, &feature_request, &feature_response,
      [&](Status status) {
        // Callback for RouteGuide service response
        std::lock_guard<std::mutex> lock(mu);
        done_count++;
        feature_status = std::move(status);
        cv.notify_all();  // Notify waiting thread
      });

  // Wait until both async calls complete (done_count == 2)
  cv.wait(lock, [&]() { return done_count == 2; });

  // Process HelloWorld service response
  if (hello_status.ok()) {
    std::cout << "Greeter received: " << hello_response.message() << std::endl;
  } else {
    std::cerr << "Greeter failed: " << hello_status.error_message()
              << std::endl;
  }

  // Process RouteGuide service response
  if (feature_status.ok()) {
    std::cout << "Found feature: " << feature_response.name() << std::endl;
  } else {
    std::cerr << "Getting feature failed: " << feature_status.error_message()
              << std::endl;
  }

  return 0;
}
```

Key aspects covered in the comments:
1. Header file purposes
2. Command line flag definition
3. Synchronization primitives explanation
4. Async call setup and callback handling
5. Response processing logic
6. Overall flow of the program
7. Error handling paths

The comments explain both the high-level structure and the detailed implementation choices, making it easier for future developers to understand and maintain the code.