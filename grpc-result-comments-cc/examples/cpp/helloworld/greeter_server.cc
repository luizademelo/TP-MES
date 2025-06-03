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

// Include necessary headers for gRPC functionality
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

// Standard C++ headers
#include <iostream>
#include <memory>
#include <string>

// Abseil headers for command line flags and logging
#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/log/initialize.h"
#include "absl/strings/str_format.h"

// Include the generated protobuf headers
// Different paths for Bazel vs non-Bazel builds
#ifdef BAZEL_BUILD
#include "examples/protos/helloworld.grpc.pb.h"
#else
#include "helloworld.grpc.pb.h"
#endif

// Using declarations to simplify code
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using helloworld::Greeter;
using helloworld::HelloReply;
using helloworld::HelloRequest;

// Define a command line flag for server port with default value 50051
ABSL_FLAG(uint16_t, port, 50051, "Server port for the service");

// Implementation of the Greeter service
class GreeterServiceImpl final : public Greeter::Service {
  // Override the SayHello method from the service definition
  Status SayHello(ServerContext* context, const HelloRequest* request,
                  HelloReply* reply) override {
    // Create a response message by concatenating "Hello " with the request name
    std::string prefix("Hello ");
    reply->set_message(prefix + request->name());
    // Return OK status to indicate successful processing
    return Status::OK;
  }
};

// Function to configure and run the gRPC server
void RunServer(uint16_t port) {
  // Create server address string using the specified port
  std::string server_address = absl::StrFormat("0.0.0.0:%d", port);
  GreeterServiceImpl service;  // Create an instance of our service implementation

  // Enable default health check service for server monitoring
  grpc::EnableDefaultHealthCheckService(true);
  // Initialize server reflection plugin (for debugging/testing)
  grpc::reflection::InitProtoReflectionServerBuilderPlugin();
  
  // Create server builder to configure the server
  ServerBuilder builder;

  // Add listening port with insecure credentials (for development only)
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());

  // Register our service implementation with the server
  builder.RegisterService(&service);

  // Build and start the server
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  // Block until the server shuts down
  server->Wait();
}

// Main entry point for the application
int main(int argc, char** argv) {
  // Parse command line flags
  absl::ParseCommandLine(argc, argv);
  // Initialize logging system
  absl::InitializeLog();
  // Run the server with the port specified in command line flags (or default)
  RunServer(absl::GetFlag(FLAGS_port));
  return 0;
}
```

The comments explain:
1. The purpose of each include statement
2. The command line flag definition
3. The service implementation details
4. The server setup and configuration process
5. The main program flow
6. Important notes about security (insecure credentials warning)
7. The purpose of health checks and server reflection

The comments are concise but provide enough context for a developer to understand the code's functionality and structure.