Here's the commented version of the code:

```c++
// Copyright 2023 The gRPC Authors

// gRPC and Protobuf headers
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>

// Standard library headers
#include <iostream>

// Abseil headers for command line flags and utilities
#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/log/initialize.h"
#include "absl/strings/str_format.h"

// Generated protobuf headers
#include "examples/protos/helloworld.grpc.pb.h"

// Using declarations for gRPC and protobuf namespaces
using grpc::CallbackServerContext;
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerUnaryReactor;
using grpc::Status;
using helloworld::Greeter;
using helloworld::HelloReply;
using helloworld::HelloRequest;

// Define a command line flag for server port with default value 50051
ABSL_FLAG(uint16_t, port, 50051, "Server port for the service");

// Implementation of the Greeter service
class GreeterServiceImpl final : public Greeter::CallbackService {
 public:
  // Callback method for handling SayHello RPC
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
  // Format server address string using the specified port
  std::string server_address = absl::StrFormat("0.0.0.0:%d", port);
  GreeterServiceImpl service;

  // Initialize server reflection plugin for debugging
  grpc::reflection::InitProtoReflectionServerBuilderPlugin();
  
  // Create server builder
  ServerBuilder builder;

  // Add listening port with insecure credentials (no encryption)
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());

  // Register our service implementation
  builder.RegisterService(&service);

  // Build and start the server
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << '\n';

  // Wait for the server to shutdown (blocking call)
  server->Wait();
}

// Main entry point
int main(int argc, char** argv) {
  // Parse command line flags
  absl::ParseCommandLine(argc, argv);
  
  // Run the server with the specified port (or default if not specified)
  RunServer(absl::GetFlag(FLAGS_port));
  
  return 0;
}
```

The comments added explain:
1. The purpose of each include section
2. The command line flag definition
3. The service implementation class and its methods
4. The server setup and configuration process
5. The main program flow
6. Key gRPC concepts like reactors and server builders

The comments are concise but provide enough context for future developers to understand the code's functionality and structure.