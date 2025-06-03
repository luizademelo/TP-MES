Here's the commented version of the code:

```c++
// Copyright 2022 the gRPC authors.

// Include necessary gRPC headers
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
// Generated protobuf headers for our service
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
    // Create a response message by concatenating "Hello " with the request name
    std::string prefix("Hello ");
    reply->set_message(prefix + request->name());
    // Return OK status to indicate successful processing
    return Status::OK;
  }
};

// Function to configure and start the gRPC server
void RunServer() {
  // Server will listen on Unix domain socket
  std::string server_address("unix:/tmp/server");
  // Create an instance of our service implementation
  GreeterServiceImpl service;

  // Enable default health check service (used for load balancing and health checking)
  grpc::EnableDefaultHealthCheckService(true);
  // Enable server reflection (useful for debugging and command-line tools)
  grpc::reflection::InitProtoReflectionServerBuilderPlugin();
  
  // Create server builder to configure the server
  ServerBuilder builder;

  // Add listening port with insecure credentials (no encryption)
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());

  // Register our service implementation with the server
  builder.RegisterService(&service);

  // Build and start the server
  std::unique_ptr<Server> server(builder.BuildAndStart());
  // Print server information
  std::cout << "Server listening on " << server_address << std::endl;

  // Block until the server shuts down
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

The comments explain:
1. The purpose of each include statement
2. The service implementation class and its method
3. The server setup and configuration process
4. The main program flow
5. Key gRPC features being used (health checks, reflection)
6. The communication channel being used (Unix domain socket)

The comments are concise but provide enough information for a developer to understand what each part of the code does without being overly verbose.