Here's the commented version of the code:

```c++
// Copyright 2021 the gRPC authors.

// Include necessary gRPC headers for server functionality
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

// Standard C++ headers
#include <iostream>
#include <memory>
#include <string>

// Abseil headers for command line parsing and logging
#include "absl/flags/parse.h"
#include "absl/log/initialize.h"
// Generated protobuf headers for the helloworld service
#include "examples/protos/helloworld.grpc.pb.h"

// Using declarations to simplify code
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using helloworld::Greeter;
using helloworld::HelloReply;
using helloworld::HelloRequest;

// Implementation of the Greeter service
class GreeterServiceImpl final : public Greeter::Service {
  // Override the SayHello RPC method
  Status SayHello(ServerContext* context, const HelloRequest* request,
                  HelloReply* reply) override {
    // Set the reply message to be the same as the request name (echo service)
    reply->set_message(request->name());
    // Log the echoed name to console
    std::cout << "Echoing: " << request->name() << std::endl;
    // Return OK status indicating successful RPC completion
    return Status::OK;
  }
};

// Function to configure and start the gRPC server
void RunServer() {
  // Define server address using Unix abstract socket
  std::string server_address("unix-abstract:grpc%00abstract");
  GreeterServiceImpl service;
  
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
  
  // Build and start the server
  std::unique_ptr<Server> server(builder.BuildAndStart());
  // Log server startup information
  std::cout << "Server listening on " << server_address << " ... ";
  // Wait for server shutdown
  server->Wait();
}

// Main entry point
int main(int argc, char** argv) {
  // Parse command line arguments using Abseil
  absl::ParseCommandLine(argc, argv);
  // Initialize Abseil logging
  absl::InitializeLog();
  // Start the gRPC server
  RunServer();

  return 0;
}
```

Key aspects documented:
1. Header file purposes
2. Service implementation details
3. RPC method functionality
4. Server configuration steps
5. Important gRPC features being used (reflection, health checks)
6. Main program flow
7. Security note about insecure credentials
8. Logging behavior

The comments are designed to help future developers understand:
- What the code does at each step
- Why certain choices were made (like using Unix abstract sockets)
- How the gRPC components fit together
- Where to look for more information about specific features