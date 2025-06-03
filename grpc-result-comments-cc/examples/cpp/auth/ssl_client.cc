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
#include "helper.h"

#ifdef BAZEL_BUILD
#include "examples/protos/helloworld.grpc.pb.h"
#else
#include "helloworld.grpc.pb.h"
#endif

// Define a command line flag for the server port with default value 50051
ABSL_FLAG(uint16_t, port, 50051, "Server port for the service");

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using helloworld::Greeter;
using helloworld::HelloReply;
using helloworld::HelloRequest;

// GreeterClient class for making RPC calls to the Greeter service
class GreeterClient {
 public:
  // Constructor that takes a gRPC channel and creates a stub for the Greeter service
  GreeterClient(std::shared_ptr<Channel> channel)
      : stub_(Greeter::NewStub(channel)) {}

  // Sends a SayHello RPC to the server with the given user name
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

    // Make the asynchronous SayHello RPC call
    stub_->async()->SayHello(&context, &request, &reply,
                             [&mu, &cv, &done, &status](Status s) {
                               // Callback function that gets called when RPC completes
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

    // Return the response message if RPC was successful
    if (status.ok()) {
      return reply.message();
    } else {
      // Print error details if RPC failed
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return "RPC failed";
    }
  }

 private:
  // The gRPC stub for making RPC calls to the Greeter service
  std::unique_ptr<Greeter::Stub> stub_;
};

// Path to root certificate file, differs between Bazel and non-Bazel builds
#ifdef BAZEL_BUILD
constexpr char kRootCertificate[] = "examples/cpp/auth/credentials/root.crt";
#else
constexpr char kRootCertificate[] = "credentials/root.crt";
#endif

int main(int argc, char** argv) {
  // Parse command line flags
  absl::ParseCommandLine(argc, argv);
  absl::InitializeLog();

  // Create the target address string using the port from command line flags
  std::string target_str =
      absl::StrFormat("localhost:%d", absl::GetFlag(FLAGS_port));

  // Set up SSL credentials using the root certificate
  grpc::SslCredentialsOptions ssl_options;
  ssl_options.pem_root_certs = LoadStringFromFile(kRootCertificate);

  // Create GreeterClient instance with SSL credentials
  GreeterClient greeter(
      grpc::CreateChannel(target_str, grpc::SslCredentials(ssl_options)));
  
  // Make the RPC call with a default user name
  std::string user("world");
  std::string reply = greeter.SayHello(user);
  
  // Print the response from the server
  std::cout << "Greeter received: " << reply << std::endl;

  return 0;
}
```

Key improvements in the comments:
1. Added class-level documentation for GreeterClient
2. Explained the purpose of each major section of code
3. Documented the async RPC call mechanism and synchronization
4. Explained the command line flag usage
5. Clarified the SSL credentials setup
6. Added comments for the different build scenarios (Bazel vs non-Bazel)
7. Explained the main program flow

The comments are concise but provide enough context for future developers to understand both the high-level operation and important implementation details.