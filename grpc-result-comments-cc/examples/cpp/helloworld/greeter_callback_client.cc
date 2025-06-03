Here's the commented version of the code:

```c++
/*
 *
 * Copyright 2021 gRPC authors.
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

#ifdef BAZEL_BUILD
#include "examples/protos/helloworld.grpc.pb.h"
#else
#include "helloworld.grpc.pb.h"
#endif

// Define a command line flag for server address with default value "localhost:50051"
ABSL_FLAG(std::string, target, "localhost:50051", "Server address");

// Import necessary gRPC and protobuf namespaces
using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using helloworld::Greeter;
using helloworld::HelloReply;
using helloworld::HelloRequest;

// Client class for the Greeter service
class GreeterClient {
 public:
  // Constructor that takes a gRPC channel and creates a stub for the Greeter service
  GreeterClient(std::shared_ptr<Channel> channel)
      : stub_(Greeter::NewStub(channel)) {}

  // Method to send a greeting to the server and receive a response
  std::string SayHello(const std::string& user) {
    // Create and populate the request message
    HelloRequest request;
    request.set_name(user);

    // Will store the server's response
    HelloReply reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // Synchronization primitives for handling the async call
    std::mutex mu;
    std::condition_variable cv;
    bool done = false;
    Status status;

    // Make the asynchronous call to the SayHello RPC
    stub_->async()->SayHello(&context, &request, &reply,
                             [&mu, &cv, &done, &status](Status s) {
                               // Callback function that gets called when RPC completes
                               status = std::move(s);
                               std::lock_guard<std::mutex> lock(mu);
                               done = true;
                               cv.notify_one();  // Notify the waiting thread
                             });

    // Wait for the RPC to complete
    std::unique_lock<std::mutex> lock(mu);
    while (!done) {
      cv.wait(lock);
    }

    // Return the response if RPC was successful, otherwise return error
    if (status.ok()) {
      return reply.message();
    } else {
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
  // Parse command line flags
  absl::ParseCommandLine(argc, argv);

  // Get the server address from command line flags
  std::string target_str = absl::GetFlag(FLAGS_target);

  // Create a GreeterClient connected to the specified server
  GreeterClient greeter(
      grpc::CreateChannel(target_str, grpc::InsecureChannelCredentials()));
  
  // Default user name to greet
  std::string user("world");
  
  // Make the RPC call and print the response
  std::string reply = greeter.SayHello(user);
  std::cout << "Greeter received: " << reply << std::endl;

  return 0;
}
```

Key improvements in the comments:
1. Added explanation for the ABSL_FLAG macro
2. Documented the purpose of the GreeterClient class
3. Explained the constructor and its parameters
4. Detailed the SayHello method's functionality including:
   - Request/response message handling
   - ClientContext usage
   - Async call mechanics with synchronization
   - Error handling
5. Explained the main function's flow
6. Added comments for important variables and their purposes
7. Maintained all existing license and copyright information

The comments now provide a clear understanding of:
- The overall structure of the gRPC client
- How the asynchronous call is implemented
- The synchronization mechanism used
- The flow of data through the system
- Error handling approach