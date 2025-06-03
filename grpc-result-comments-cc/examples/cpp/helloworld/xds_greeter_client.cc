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

#include <iostream>
#include <memory>
#include <string>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"

// Include the generated gRPC protobuf headers
// Different paths are used depending on whether this is a Bazel build
#ifdef BAZEL_BUILD
#include "examples/protos/helloworld.grpc.pb.h"
#else
#include "helloworld.grpc.pb.h"
#endif

// Define command line flags using Abseil
// Default target is an xDS-enabled gRPC server
ABSL_FLAG(std::string, target, "xds:///helloworld:50051", "Target string");
// Default security mode is secure (using xDS credentials)
ABSL_FLAG(bool, secure, true, "Secure mode");

// Import commonly used gRPC and protobuf types into current namespace
using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using helloworld::Greeter;
using helloworld::HelloReply;
using helloworld::HelloRequest;

/**
 * @brief Client for the Greeter service that communicates with a gRPC server.
 */
class GreeterClient {
 public:
  /**
   * @brief Construct a new Greeter Client object
   * @param channel Shared pointer to the gRPC communication channel
   */
  GreeterClient(std::shared_ptr<Channel> channel)
      : stub_(Greeter::NewStub(channel)) {}

  /**
   * @brief Sends a greeting request to the server
   * @param user The name to include in the greeting request
   * @return std::string The greeting response from server or error message
   */
  std::string SayHello(const std::string& user) {
    // Create and populate the request protobuf
    HelloRequest request;
    request.set_name(user);

    // Response protobuf will be filled in by the RPC call
    HelloReply reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC call to the server
    Status status = stub_->SayHello(&context, request, &reply);

    // Process the response
    if (status.ok()) {
      return reply.message();
    } else {
      // Print error details if the RPC failed
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return "RPC failed";
    }
  }

 private:
  // The gRPC stub used to make RPC calls
  std::unique_ptr<Greeter::Stub> stub_;
};

/**
 * @brief Main function that creates a client and makes a greeting RPC call
 */
int main(int argc, char** argv) {
  // Parse command line flags
  absl::ParseCommandLine(argc, argv);
  
  // Create a gRPC channel with either secure (xDS) or insecure credentials
  // based on the command line flag
  GreeterClient greeter(grpc::CreateChannel(
      absl::GetFlag(FLAGS_target),
      absl::GetFlag(FLAGS_secure)
          ? grpc::XdsCredentials(grpc::InsecureChannelCredentials())
          : grpc::InsecureChannelCredentials()));
  
  // Default user name for the greeting
  std::string user("world");
  
  // Make the RPC call and print the response
  std::string reply = greeter.SayHello(user);
  std::cout << "Greeter received: " << reply << std::endl;

  return 0;
}
```

Key improvements in the comments:
1. Added detailed class and method documentation
2. Explained the purpose of each major code block
3. Clarified the use of command line flags
4. Documented the RPC call flow and error handling
5. Added notes about the channel creation and security options
6. Explained the conditional includes for different build systems
7. Added context about the protobuf message usage

The comments are designed to help future developers understand:
- The overall purpose of each component
- How the gRPC communication works
- The significance of the security options
- The flow of data through the system
- Error handling mechanisms