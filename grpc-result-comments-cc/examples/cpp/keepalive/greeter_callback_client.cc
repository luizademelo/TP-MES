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
#include <thread>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/log/initialize.h"

#ifdef BAZEL_BUILD
#include "examples/protos/helloworld.grpc.pb.h"
#else
#include "helloworld.grpc.pb.h"
#endif

// Define a command line flag for server address with default value "localhost:50051"
ABSL_FLAG(std::string, target, "localhost:50051", "Server address");

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using helloworld::Greeter;
using helloworld::HelloReply;
using helloworld::HelloRequest;

// Client class for interacting with the Greeter service
class GreeterClient {
 public:
  // Constructor that takes a gRPC channel and creates a stub for the Greeter service
  GreeterClient(std::shared_ptr<Channel> channel)
      : stub_(Greeter::NewStub(channel)) {}

  // Method to send a greeting request to the server
  std::string SayHello(const std::string& user) {
    // Create and populate the request message
    HelloRequest request;
    request.set_name(user);

    // Response will be stored here
    HelloReply reply;

    // Context for the client. It could be used to send metadata or adjust RPC settings
    ClientContext context;

    // Synchronization primitives for async call
    std::mutex mu;
    std::condition_variable cv;
    bool done = false;
    Status status;

    // Make the asynchronous call to the SayHello RPC method
    stub_->async()->SayHello(&context, &request, &reply,
                             [&mu, &cv, &done, &status](Status s) {
                               // Callback function that will be called when RPC completes
                               status = std::move(s);
                               std::lock_guard<std::mutex> lock(mu);
                               done = true;
                               cv.notify_one();  // Notify waiting thread that RPC is complete
                             });

    // Wait for the RPC to complete
    std::unique_lock<std::mutex> lock(mu);
    while (!done) {
      cv.wait(lock);
    }

    // Return the response if RPC was successful, otherwise return error message
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
  absl::InitializeLog();

  // Get server address from command line flag
  std::string target_str = absl::GetFlag(FLAGS_target);
  
  // Configure channel arguments for keepalive
  grpc::ChannelArguments args;
  args.SetInt(GRPC_ARG_KEEPALIVE_TIME_MS, 20 * 1000);  // Send keepalive ping every 20 seconds
  args.SetInt(GRPC_ARG_KEEPALIVE_TIMEOUT_MS, 10 * 1000);  // Wait 10 seconds for ping ack
  args.SetInt(GRPC_ARG_KEEPALIVE_PERMIT_WITHOUT_CALLS, 1);  // Allow keepalive pings without active calls

  // Make 10 RPC calls with 10 second intervals between them
  for (auto i = 0; i < 10; ++i) {
    // Create client with custom channel configuration
    GreeterClient greeter(grpc::CreateCustomChannel(
        target_str, grpc::InsecureChannelCredentials(), args));
    
    // Prepare and send request
    std::string user("world");
    std::string reply = greeter.SayHello(user);
    
    // Print server response
    std::cout << "Greeter received: " << reply << std::endl;
    
    // Wait before next call
    std::this_thread::sleep_for(std::chrono::seconds(10));
  }

  return 0;
}
```

Key aspects covered in the comments:
1. Overall purpose of the GreeterClient class
2. Explanation of the async RPC call mechanism with synchronization
3. Purpose of each gRPC component (Channel, ClientContext, Status)
4. Configuration of keepalive parameters
5. Main program flow and loop
6. Error handling
7. Command line flag usage
8. Important implementation details about the callback and waiting mechanism

The comments aim to provide both high-level understanding of the code's purpose and specific details about implementation choices.