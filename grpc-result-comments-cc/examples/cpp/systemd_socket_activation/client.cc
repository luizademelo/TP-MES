Here's the commented version of the code:

```c++
// Copyright 2022 the gRPC authors.

// Include necessary headers
#include <grpcpp/grpcpp.h>  // Main gRPC C++ library
#include <iostream>          // For console I/O
#include <memory>            // For smart pointers
#include <string>            // For string operations

// Include ABSL and protobuf generated headers
#include "absl/flags/parse.h"       // For command line parsing
#include "absl/log/initialize.h"    // For logging initialization
#include "examples/protos/helloworld.grpc.pb.h"  // Generated gRPC service definitions

// Using declarations to simplify code
using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using helloworld::Greeter;
using helloworld::HelloReply;
using helloworld::HelloRequest;

// Client class for the Greeter service
class GreeterClient {
 public:
  // Constructor takes a shared_ptr to a Channel (connection to server)
  GreeterClient(std::shared_ptr<Channel> channel)
      : stub_(Greeter::NewStub(channel)) {}  // Creates a new stub for the Greeter service

  // Sends a greeting to the server and returns the response
  std::string SayHello(const std::string& user) {
    // Create and populate the request message
    HelloRequest request;
    request.set_name(user);  // Set the name field in the request

    // Will store the server's response
    HelloReply reply;
    
    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC call to the server
    Status status = stub_->SayHello(&context, request, &reply);

    // Check if the RPC was successful
    if (status.ok()) {
      return reply.message();  // Return the server's response message
    } else {
      // Print error details if the RPC failed
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return "RPC failed";
    }
  }

 private:
  // The gRPC stub used to make RPC calls to the server
  std::unique_ptr<Greeter::Stub> stub_;
};

int main(int argc, char** argv) {
  // Initialize command line parsing and logging
  absl::ParseCommandLine(argc, argv);
  absl::InitializeLog();

  // Default target string if no arguments are provided
  std::string target_str;
  std::string arg_str("--target");
  
  // Parse command line arguments
  if (argc > 1) {
    std::string arg_val = argv[1];
    size_t start_pos = arg_val.find(arg_str);
    if (start_pos != std::string::npos) {
      start_pos += arg_str.size();
      if (arg_val[start_pos] == '=') {
        target_str = arg_val.substr(start_pos + 1);  // Extract target address
      } else {
        std::cout << "The only correct argument syntax is --target="
                  << std::endl;
        return 0;
      }
    } else {
      std::cout << "The only acceptable argument is --target=" << std::endl;
      return 0;
    }
  } else {
    // Default target if no arguments provided
    target_str = "unix:/tmp/server";
  }
  
  // Create a client instance with insecure channel credentials
  GreeterClient greeter(
      grpc::CreateChannel(target_str, grpc::InsecureChannelCredentials()));
  
  // Send a greeting to the server and print the response
  std::string user("world");
  std::string reply(greeter.SayHello(user));
  std::cout << "Greeter received: " << reply << std::endl;

  return 0;
}
```

Key improvements in the comments:
1. Added file-level comment about the copyright
2. Explained each major include and its purpose
3. Documented the class purpose and its methods
4. Added detailed comments about the RPC call flow
5. Explained the command line argument parsing logic
6. Clarified the default behavior when no arguments are provided
7. Added comments about important objects like ClientContext and Status
8. Explained the stub's role in the client class

The comments now provide a clear understanding of:
- The overall architecture (client-server RPC)
- The flow of execution
- Error handling
- Important gRPC concepts used
- Command line argument processing
- Default values and behaviors