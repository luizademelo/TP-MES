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
#include <grpcpp/ext/proto_server_reflection_plugin.h>  // For gRPC reflection
#include <grpcpp/grpcpp.h>  // Core gRPC library
#include <grpcpp/health_check_service_interface.h>  // Health check service

#include <iostream>
#include <memory>
#include <string>

// Abseil libraries for flags and logging
#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/log/initialize.h"
#include "absl/strings/str_format.h"

// Include the generated protobuf headers
#ifdef BAZEL_BUILD
#include "examples/protos/helloworld.grpc.pb.h"
#else
#include "helloworld.grpc.pb.h"
#endif

// Define a command line flag for server port with default value 50051
ABSL_FLAG(uint16_t, port, 50051, "Server port for the service");

// Using declarations for commonly used gRPC and protobuf types
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

// Function to start and run the gRPC server
void RunServer(uint16_t port) {
  // Create server address string using the specified port
  std::string server_address = absl::StrFormat("0.0.0.0:%d", port);
  GreeterServiceImpl service;  // Create service instance

  // Enable default health check service and reflection service
  grpc::EnableDefaultHealthCheckService(true);
  grpc::reflection::InitProtoReflectionServerBuilderPlugin();

  // Create server builder
  ServerBuilder builder;

  // Add listening port with insecure credentials (for development only)
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());

  // Register our service implementation
  builder.RegisterService(&service);

  // Build and start the server
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  // Wait for the server to shutdown (blocking call)
  server->Wait();
}

int main(int argc, char** argv) {
  // Parse command line flags and initialize logging
  absl::ParseCommandLine(argc, argv);
  absl::InitializeLog();

  // Start the server with the specified port from command line flags
  RunServer(absl::GetFlag(FLAGS_port));
  return 0;
}
```

Key comments added:
1. Explained the purpose of each include header
2. Documented the command line flag definition
3. Added explanation for the service implementation class
4. Detailed the SayHello RPC method implementation
5. Documented the server setup and configuration in RunServer()
6. Added comments for main() function flow
7. Noted important details like insecure credentials being for development only

The comments follow a consistent style and provide clear explanations of both the high-level flow and important implementation details while avoiding redundancy with the code itself.