Here's the commented version of the code:

```c++
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

// Include necessary headers
#include <grpcpp/grpcpp.h>  // Main gRPC C++ library

#include <iostream>
#include <memory>
#include <string>

// Abseil libraries for command line flags and logging
#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/log/check.h"
#include "absl/log/initialize.h"

// Include the generated gRPC protobuf headers
// Different paths for Bazel vs non-Bazel builds
#ifdef BAZEL_BUILD
#include "examples/protos/helloworld.grpc.pb.h"
#else
#include "helloworld.grpc.pb.h"
#endif

// Define a command line flag for server address with default value
ABSL_FLAG(std::string, target, "localhost:50051", "Server address");

// Using declarations for gRPC and protobuf types
using grpc::Channel;
using grpc::ClientAsyncResponseReader;
using grpc::ClientContext;
using grpc::CompletionQueue;
using grpc::Status;
using helloworld::Greeter;
using helloworld::HelloReply;
using helloworld::HelloRequest;

// Client class for the Greeter service
class GreeterClient {
 public:
  // Constructor takes a shared channel pointer and creates a stub
  explicit GreeterClient(std::shared_ptr<Channel> channel)
      : stub_(Greeter::NewStub(channel)) {}

  // Method to send a greeting request to the server
  std::string SayHello(const std::string& user) {
    // Create and populate the request protobuf
    HelloRequest request;
    request.set_name(user);

    // Will hold the server's response
    HelloReply reply;

    // Context for the client (can modify timeout, metadata, etc.)
    ClientContext context;

    // Completion queue for async operations
    CompletionQueue cq;

    // Will hold the RPC status
    Status status;

    // Initiate the async RPC call
    std::unique_ptr<ClientAsyncResponseReader<HelloReply> > rpc(
        stub_->AsyncSayHello(&context, request, &cq));

    // Request notification of RPC completion
    rpc->Finish(&reply, &status, (void*)1);
    
    // Variables to receive completion queue event
    void* got_tag;
    bool ok = false;

    // Block waiting for the completion queue to return an event
    CHECK(cq.Next(&got_tag, &ok));

    // Verify the received tag matches our expectation
    CHECK_EQ(got_tag, (void*)1);

    // Verify the operation completed successfully
    CHECK(ok);

    // Return the response message or error string
    if (status.ok()) {
      return reply.message();
    } else {
      return "RPC failed";
    }
  }

 private:
  // The gRPC stub used to make RPC calls
  std::unique_ptr<Greeter::Stub> stub_;
};

int main(int argc, char** argv) {
  // Initialize command line parsing and logging
  absl::ParseCommandLine(argc, argv);
  absl::InitializeLog();

  // Get server address from command line flag
  std::string target_str = absl::GetFlag(FLAGS_target);

  // Create client with insecure channel to server
  GreeterClient greeter(
      grpc::CreateChannel(target_str, grpc::InsecureChannelCredentials()));
  
  // Default user name to greet
  std::string user("world");
  
  // Make RPC call and print response
  std::string reply = greeter.SayHello(user);
  std::cout << "Greeter received: " << reply << std::endl;

  return 0;
}
```

Key additions in the comments:
1. Explained the purpose of each major include
2. Documented the command line flag definition
3. Added detailed comments for the GreeterClient class and its methods
4. Explained the async RPC flow in SayHello()
5. Clarified the purpose of each variable in the RPC call
6. Documented the main function's workflow
7. Added notes about important operations like completion queue handling

The comments aim to help future developers understand:
- The overall structure of the gRPC client
- The asynchronous nature of the RPC calls
- The purpose of each component in the communication flow
- The error checking and validation being performed