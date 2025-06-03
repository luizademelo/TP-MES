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
#include <iostream>           // For console I/O
#include <memory>             // For smart pointers
#include <mutex>              // For mutex locks
#include <string>             // For string operations

// Include Abseil libraries for command line flags and logging
#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/log/initialize.h"

// Include the generated gRPC protobuf headers
#ifdef BAZEL_BUILD
#include "examples/protos/helloworld.grpc.pb.h"  // Bazel build path
#else
#include "helloworld.grpc.pb.h"                 // Non-Bazel build path
#endif

// Define command line flags using Abseil
ABSL_FLAG(std::string, target, "xds:///helloworld:50051", "Target string");
ABSL_FLAG(bool, xds_creds, true, "Secure mode");

// Using declarations to simplify code
using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using helloworld::Greeter;
using helloworld::HelloReply;
using helloworld::HelloRequest;

/**
 * @class GreeterClient
 * @brief Client for the Greeter service that communicates with the gRPC server.
 */
class GreeterClient {
 public:
  /**
   * @brief Constructor that initializes the gRPC stub.
   * @param channel Shared pointer to the gRPC channel.
   */
  GreeterClient(std::shared_ptr<Channel> channel)
      : stub_(Greeter::NewStub(channel)) {}

  /**
   * @brief Sends a greeting request to the server and returns the response.
   * @param user The name to send in the greeting request.
   * @return The server's response message or an error string if RPC fails.
   */
  std::string SayHello(const std::string& user) {
    // Create and populate the request protobuf
    HelloRequest request;
    request.set_name(user);

    // Response protobuf will be filled in by the server
    HelloReply reply;

    // Client context for the RPC call
    ClientContext context;

    // Synchronization primitives for async call
    std::mutex mu;
    std::condition_variable cv;
    bool done = false;
    Status status;

    // Make the asynchronous call to the SayHello RPC method
    stub_->async()->SayHello(&context, &request, &reply,
                             [&mu, &cv, &done, &status](Status s) {
                               // Callback function that gets executed when RPC completes
                               status = std::move(s);
                               std::lock_guard<std::mutex> lock(mu);
                               done = true;
                               cv.notify_one();  // Notify waiting thread
                             });

    // Wait for the async call to complete
    std::unique_lock<std::mutex> lock(mu);
    while (!done) {
      cv.wait(lock);
    }

    // Check RPC status and return appropriate response
    if (status.ok()) {
      return reply.message();  // Return server's response
    } else {
      // Print error details and return failure message
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return "RPC failed";
    }
  }

 private:
  std::unique_ptr<Greeter::Stub> stub_;  // gRPC stub for making RPC calls
};

/**
 * @brief Main function that creates and runs the Greeter client.
 */
int main(int argc, char** argv) {
  // Parse command line flags
  absl::ParseCommandLine(argc, argv);
  absl::InitializeLog();

  // Create gRPC channel with either XDS credentials or insecure credentials
  GreeterClient greeter(grpc::CreateChannel(
      absl::GetFlag(FLAGS_target),
      absl::GetFlag(FLAGS_xds_creds)
          ? grpc::XdsCredentials(grpc::InsecureChannelCredentials())
          : grpc::InsecureChannelCredentials()));

  // Make RPC call and print response
  std::string user("world");
  std::string reply = greeter.SayHello(user);
  std::cout << "Greeter received: " << reply << std::endl;

  return 0;
}
```

Key improvements in the comments:
1. Added file-level comment explaining the license
2. Added comments for each include statement explaining its purpose
3. Documented the command line flags
4. Added detailed class documentation for GreeterClient
5. Added detailed method documentation for constructor and SayHello
6. Explained the async call mechanism and synchronization
7. Documented the main function flow
8. Added comments for important variables and operations

The comments now provide a clear understanding of:
- The overall structure of the code
- The purpose of each component
- The flow of execution
- The synchronization mechanism for async calls
- The error handling approach
- The command line flag usage