Here's the commented version of the code:

```c++
// Copyright 2023 The gRPC Authors

// Include necessary gRPC and other library headers
#include <grpcpp/grpcpp.h>

#include <iostream>
#include <memory>
#include <string>

// Include Abseil flags and logging utilities
#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/log/initialize.h"

// Handle different include paths for Bazel vs non-Bazel builds
#ifdef BAZEL_BUILD
#include "examples/protos/helloworld.grpc.pb.h"
#else
#include "helloworld.grpc.pb.h"
#endif

// Define command line flags using Abseil
ABSL_FLAG(bool, crash_on_errors, false,
          "Crash the application on client errors");
ABSL_FLAG(std::string, target, "localhost:50051", "Server address");

// Using declarations for gRPC and protobuf types
using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using helloworld::Greeter;
using helloworld::HelloReply;
using helloworld::HelloRequest;

// Client class for the Greeter service
class GreeterClient {
 public:
  // Constructor takes a gRPC channel and creates a stub for the Greeter service
  GreeterClient(std::shared_ptr<Channel> channel)
      : stub_(Greeter::NewStub(channel)) {}

  // Sends a greeting request to the server and returns the response
  std::string SayHello(const std::string& user) {
    // Create and populate the request protobuf
    HelloRequest request;
    request.set_name(user);

    // Will hold the server's response
    HelloReply reply;

    // Context for the client call
    ClientContext context;

    // Make the actual RPC call
    Status status = stub_->SayHello(&context, request, &reply);

    // Handle response based on flags and status
    if (absl::GetFlag(FLAGS_crash_on_errors)) {
      assert(status.ok());  // Crash if enabled and RPC failed
    }
    if (status.ok()) {
      return reply.message();  // Return server's response
    } else {
      return "RPC failed";  // Return error message
    }
  }

 private:
  // The gRPC service stub
  std::unique_ptr<Greeter::Stub> stub_;
};

// Main function - entry point of the application
int main(int argc, char** argv) {
  // Initialize command line parsing and logging
  absl::ParseCommandLine(argc, argv);
  absl::InitializeLog();

  // Create client with insecure channel to the target server
  GreeterClient greeter(grpc::CreateChannel(
      absl::GetFlag(FLAGS_target), grpc::InsecureChannelCredentials()));
  
  // Default user name and greeting request
  std::string user("world");
  std::string reply = greeter.SayHello(user);
  
  // Print the server's response
  std::cout << "Greeter received: " << reply << std::endl;

  return 0;
}
```

The comments explain:
1. Header inclusions and their purposes
2. Command line flag definitions
3. Class structure and purpose
4. Method functionality and flow
5. RPC call handling and error management
6. Main program flow and initialization
7. Important implementation details like the insecure channel

The comments are placed to help future developers understand:
- The overall architecture
- Key decision points
- Error handling strategy
- Important implementation details
- The flow of data through the system