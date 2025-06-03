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

// Using declarations to simplify usage of gRPC and protocol buffer classes
using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using helloworld::Greeter;
using helloworld::HelloReply;
using helloworld::HelloRequest;

// Client class that demonstrates custom metadata handling with gRPC
class CustomHeaderClient {
 public:
  // Constructor that takes a gRPC channel and creates a stub for the Greeter service
  CustomHeaderClient(std::shared_ptr<Channel> channel)
      : stub_(Greeter::NewStub(channel)) {}

  // Method to send a greeting request to the server with custom metadata
  std::string SayHello(const std::string& user) {
    // Create and populate the request protocol buffer
    HelloRequest request;
    request.set_name(user);

    // Will hold the server's response
    HelloReply reply;

    // Client context for this RPC call
    ClientContext context;

    // Add custom text metadata to the request
    context.AddMetadata("custom-header", "Custom Value");

    // Add custom binary metadata to the request (8 bytes)
    char bytes[8] = {'\0', '\1', '\2', '\3', '\4', '\5', '\6', '\7'};
    context.AddMetadata("custom-bin", std::string(bytes, 8));

    // Make the actual RPC call
    Status status = stub_->SayHello(&context, request, &reply);

    if (status.ok()) {
      // If successful, print server metadata from response
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
      // If failed, print error information
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return "RPC failed";
    }
  }

 private:
  // The gRPC stub for making RPC calls to the Greeter service
  std::unique_ptr<Greeter::Stub> stub_;
};

int main(int argc, char** argv) {
  // Initialize command line parsing and logging
  absl::ParseCommandLine(argc, argv);
  absl::InitializeLog();

  // Create client instance connected to local server on port 50051
  // Note: Using insecure credentials (no encryption)
  CustomHeaderClient greeter(grpc::CreateChannel(
      "localhost:50051", grpc::InsecureChannelCredentials()));
  
  // Default user name for the greeting
  std::string user("world");
  
  // Make the RPC call and print the response
  std::string reply = greeter.SayHello(user);
  std::cout << "Client received message: " << reply << std::endl;
  
  return 0;
}
```

Key additions in the comments:
1. Explained the purpose of each major component (class, methods)
2. Detailed the custom metadata handling (both text and binary)
3. Noted the RPC call flow and error handling
4. Explained the main function's initialization and execution flow
5. Added warnings about insecure channel credentials
6. Clarified the purpose of protocol buffer objects
7. Explained the metadata retrieval from server response

The comments are designed to help future developers understand:
- The overall structure of the gRPC client
- How custom metadata is added and processed
- The RPC call lifecycle
- Error handling patterns
- Important security considerations