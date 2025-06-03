Here's the commented version of the code:

```c++
// Copyright 2023 gRPC authors.

// Include necessary headers
#include <grpcpp/grpcpp.h>  // Main gRPC C++ library
#include <condition_variable>  // For thread synchronization
#include <iostream>  // For console I/O
#include <memory>  // For smart pointers
#include <mutex>  // For mutex locks
#include <string>  // For string operations
#include <thread>  // For thread operations

// Include ABSL (Abseil) libraries for flags and logging
#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/log/initialize.h"

// Include the generated protobuf headers
// Different paths depending on whether this is a Bazel build or not
#ifdef BAZEL_BUILD
#include "examples/protos/helloworld.grpc.pb.h"
#else
#include "helloworld.grpc.pb.h"
#endif

// Define a command line flag for server address with default value
ABSL_FLAG(std::string, target, "localhost:50051", "Server address");

// Using declarations to simplify code
using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using helloworld::Greeter;
using helloworld::HelloReply;
using helloworld::HelloRequest;

// GreeterClient class for making RPC calls to the Greeter service
class GreeterClient {
 public:
  // Constructor takes a shared channel and creates a stub
  GreeterClient(std::shared_ptr<Channel> channel)
      : stub_(Greeter::NewStub(channel)) {}

  // Method to send a HelloRequest and receive a HelloReply
  std::string SayHello(const std::string& user, bool wait_for_ready) {
    // Prepare the request with the user's name
    HelloRequest request;
    request.set_name(user);
    
    // Response and context objects
    HelloReply reply;
    ClientContext context;
    
    // Set whether to wait for server to be ready
    context.set_wait_for_ready(wait_for_ready);
    
    // Synchronization primitives for async call
    std::mutex mu;
    std::condition_variable cv;
    bool done = false;
    Status status;
    
    // Make the asynchronous RPC call
    stub_->async()->SayHello(&context, &request, &reply,
                             [&mu, &cv, &done, &status](Status s) {
                               // Callback when RPC completes
                               status = std::move(s);
                               std::lock_guard<std::mutex> lock(mu);
                               done = true;
                               cv.notify_one();  // Notify waiting thread
                             });

    // Wait for the RPC to complete
    std::unique_lock<std::mutex> lock(mu);
    while (!done) {
      cv.wait(lock);
    }
    
    // Return response or error message
    if (status.ok()) {
      return reply.message();
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << "\n";
      return "RPC failed";
    }
  }

 private:
  std::unique_ptr<Greeter::Stub> stub_;  // gRPC service stub
};

int main(int argc, char** argv) {
  // Initialize command line parsing and logging
  absl::ParseCommandLine(argc, argv);
  absl::InitializeLog();
  
  // Get server address from command line flag
  std::string target_str = absl::GetFlag(FLAGS_target);
  
  // Create client with insecure channel credentials
  GreeterClient greeter(
      grpc::CreateChannel(target_str, grpc::InsecureChannelCredentials()));
  
  // Default user name
  std::string user("world");

  // First call without waiting for server to be ready
  std::cout << "Greeter received: "
            << greeter.SayHello(user, false) << "\n";
  
  // Prompt user to start server if not running
  std::cout << "\nWe will now send RPCs with wait_for_ready set. If the "
               "server is not running already, please start it now.\n";

  // Second call with waiting for server to be ready
  std::cout << "Greeter received: "
            << greeter.SayHello(user, true) << "\n";

  return 0;
}
```

Key aspects covered in the comments:
1. File header and copyright notice
2. Purpose of each include directive
3. Command line flag definition
4. Class and method documentation
5. Explanation of the asynchronous RPC flow
6. Synchronization mechanism details
7. Main program flow and user prompts
8. Important implementation details like insecure channel credentials

The comments aim to provide both high-level understanding of the code's purpose and specific details about implementation choices, making it easier for future developers to maintain and modify the code.