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

// Include necessary headers
#include <grpcpp/ext/proto_server_reflection_plugin.h>  // For server reflection
#include <grpcpp/grpcpp.h>                              // Core gRPC functionality
#include <grpcpp/health_check_service_interface.h>      // Health check service

#include <iostream>    // For console output
#include <memory>      // For smart pointers
#include <string>      // For string operations

// Abseil libraries for flags and logging
#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/log/initialize.h"
#include "absl/strings/str_format.h"

// Include generated protobuf headers
#ifdef BAZEL_BUILD
#include "examples/protos/helloworld.grpc.pb.h"  // For Bazel build
#else
#include "helloworld.grpc.pb.h"                  // For non-Bazel build
#endif

// Define a command line flag for server port with default value 50051
ABSL_FLAG(uint16_t, port, 50051, "Server port for the service");

// Using declarations to simplify code
using grpc::CallbackServerContext;
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerUnaryReactor;
using grpc::Status;
using helloworld::Greeter;
using helloworld::HelloReply;
using helloworld::HelloRequest;

// Implementation of the Greeter service
class GreeterServiceImpl final : public Greeter::CallbackService {
  // Implementation of the SayHello RPC method
  ServerUnaryReactor* SayHello(CallbackServerContext* context,
                               const HelloRequest* request,
                               HelloReply* reply) override {
    // Create response message by concatenating "Hello " with the request name
    std::string prefix("Hello ");
    reply->set_message(prefix + request->name());

    // Get the default reactor and finish the RPC call with OK status
    ServerUnaryReactor* reactor = context->DefaultReactor();
    reactor->Finish(Status::OK);
    return reactor;
  }
};

// Function to configure and run the gRPC server
void RunServer(uint16_t port) {
  // Create server address string using the specified port
  std::string server_address = absl::StrFormat("0.0.0.0:%d", port);
  GreeterServiceImpl service;  // Create service instance

  // Enable default health check service
  grpc::EnableDefaultHealthCheckService(true);
  // Initialize server reflection plugin
  grpc::reflection::InitProtoReflectionServerBuilderPlugin();
  
  // Create server builder
  ServerBuilder builder;

  // Add listening port with insecure credentials (no encryption)
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());

  // Register our service implementation
  builder.RegisterService(&service);

  // Configure keepalive and ping settings:
  // - Keepalive ping every 10 minutes
  builder.AddChannelArgument(GRPC_ARG_KEEPALIVE_TIME_MS, 10 * 60 * 1000);
  // - Keepalive timeout after 20 seconds
  builder.AddChannelArgument(GRPC_ARG_KEEPALIVE_TIMEOUT_MS, 20 * 1000);
  // - Allow keepalive pings without active calls
  builder.AddChannelArgument(GRPC_ARG_KEEPALIVE_PERMIT_WITHOUT_CALLS, 1);
  // - Minimum time between ping ACKs without data
  builder.AddChannelArgument(
      GRPC_ARG_HTTP2_MIN_RECV_PING_INTERVAL_WITHOUT_DATA_MS,
      10 * 1000);

  // Build and start the server
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  // Wait for server shutdown
  server->Wait();
}

// Main function
int main(int argc, char** argv) {
  // Parse command line flags
  absl::ParseCommandLine(argc, argv);
  // Initialize logging
  absl::InitializeLog();
  // Run server with port from command line flag
  RunServer(absl::GetFlag(FLAGS_port));
  return 0;
}
```

The comments explain:
1. The purpose of each include statement
2. The command line flag definition
3. The service implementation and its methods
4. The server configuration including keepalive settings
5. The main execution flow
6. Key gRPC concepts like reactors, server builders, and health checks

The comments are concise but provide enough information for a developer to understand the code's functionality and structure without being overly verbose.