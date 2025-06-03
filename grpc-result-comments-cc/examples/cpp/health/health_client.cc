Here's the commented version of the code:

```c++
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

// Define a command line flag for server address with default value "localhost:50051"
ABSL_FLAG(std::string, target, "localhost:50051", "Server address");

// Using declarations to simplify code
using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using grpc::health::v1::Health;
using grpc::health::v1::HealthCheckRequest;
using grpc::health::v1::HealthCheckResponse;
using helloworld::Greeter;
using helloworld::HelloReply;
using helloworld::HelloRequest;

// Client class for interacting with Greeter and Health services
class GreeterClient {
 public:
  // Constructor initializes stubs for both Greeter and Health services
  GreeterClient(std::shared_ptr<Channel> channel)
      : stub_(Greeter::NewStub(channel)),
        health_stub_(Health::NewStub(channel)) {}

  // Sends a greeting to the server and returns the response
  std::string SayHello(const std::string& user) {
    // Prepare the request with user name
    HelloRequest request;
    request.set_name(user);

    HelloReply reply;
    ClientContext context;

    // Synchronization primitives for async call
    std::mutex mu;
    std::condition_variable cv;
    bool done = false;
    Status status;

    // Make asynchronous call to SayHello
    stub_->async()->SayHello(&context, &request, &reply,
                             [&mu, &cv, &done, &status](Status s) {
                               // Callback function for async call
                               status = std::move(s);
                               std::lock_guard<std::mutex> lock(mu);
                               done = true;
                               cv.notify_one();
                             });

    // Wait for the async call to complete
    std::unique_lock<std::mutex> lock(mu);
    while (!done) {
      cv.wait(lock);
    }

    // Return response or error message
    if (status.ok()) {
      return reply.message();
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return "RPC failed";
    }
  }

  // Checks the health status of the server
  void CheckHealth(const std::string& message) {
    ClientContext context;
    HealthCheckResponse response;
    // Make synchronous health check call
    Status status = health_stub_->Check(
        &context, HealthCheckRequest::default_instance(), &response);
    
    if (!status.ok()) {
      std::cerr << "Failed to check service health: " << status.error_code()
                << ": " << status.error_message() << "\n";
      return;
    }
    // Print health status
    std::cout << message << ": status: "
              << HealthCheckResponse::ServingStatus_Name(response.status())
              << "\n";
  }

 private:
  std::unique_ptr<Greeter::Stub> stub_;        // Stub for Greeter service
  std::unique_ptr<Health::Stub> health_stub_;  // Stub for Health service
};

int main(int argc, char** argv) {
  // Initialize command line parsing and logging
  absl::ParseCommandLine(argc, argv);
  absl::InitializeLog();

  // Get server address from command line flag
  std::string target_str = absl::GetFlag(FLAGS_target);

  // Configure channel with health check service
  grpc::ChannelArguments args;
  args.SetServiceConfigJSON(
      "{\"healthCheckConfig\": "
      "{\"serviceName\": \"\"}}");
  
  // Create client with insecure channel (for demo purposes)
  GreeterClient greeter(grpc::CreateCustomChannel(
      target_str, grpc::InsecureChannelCredentials(), args));
  
  std::string user = "world";
  // Perform health checks and RPC calls to demonstrate functionality
  greeter.CheckHealth("Before call");
  std::string reply = greeter.SayHello(user);
  std::cout << "Greeter received: " << reply << std::endl;
  greeter.CheckHealth("After call");
  reply = greeter.SayHello(user);
  std::cout << "Greeter received: " << reply << std::endl;
  greeter.CheckHealth("After second call");
  
  return 0;
}
```

Key additions in the comments:
1. Explained the purpose of the command line flag
2. Documented the class and its methods
3. Added detailed comments about the async call mechanism in SayHello
4. Explained the health check functionality
5. Documented the main program flow
6. Noted important implementation details like the use of insecure channel
7. Added comments about synchronization primitives
8. Explained the purpose of each section in the main function

The comments are designed to help future developers understand:
- The overall architecture
- Important implementation details
- The flow of execution
- Key design decisions
- Potential areas of concern (like insecure channel usage)