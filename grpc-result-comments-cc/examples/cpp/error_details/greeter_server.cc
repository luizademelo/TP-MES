Here's the commented version of the code:

```c++
// Copyright 2023 gRPC authors.

// Include necessary gRPC headers
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

// Standard C++ headers
#include <iostream>
#include <memory>
#include <string>
#include <unordered_set>

// Abseil headers for flags, logging, and string formatting
#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/log/initialize.h"
#include "absl/strings/str_format.h"
#include "absl/synchronization/mutex.h"

// Conditional includes for different build environments
#ifdef BAZEL_BUILD
#include "examples/protos/helloworld.grpc.pb.h"
#include "google/rpc/error_details.pb.h"
#include "src/proto/grpc/status/status.pb.h"
#else
#include "error_details.pb.h"
#include "helloworld.grpc.pb.h"
#include "status.pb.h"
#endif

// Define a command line flag for server port with default value 50051
ABSL_FLAG(uint16_t, port, 50051, "Server port for the service");

// Using declarations for gRPC and protocol buffer namespaces
using grpc::CallbackServerContext;
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerUnaryReactor;
using grpc::Status;
using grpc::StatusCode;
using helloworld::Greeter;
using helloworld::HelloReply;
using helloworld::HelloRequest;

// Implementation of the Greeter service
class GreeterServiceImpl final : public Greeter::CallbackService {
  // Handles SayHello RPC requests
  ServerUnaryReactor* SayHello(CallbackServerContext* context,
                               const HelloRequest* request,
                               HelloReply* reply) override {
    // Get the default reactor for handling the response
    ServerUnaryReactor* reactor = context->DefaultReactor();
    Status status;

    // Check if this is a duplicate request for the same name
    if (CheckRequestDuplicate(request->name())) {
      // Create a detailed error response for duplicate requests
      google::rpc::QuotaFailure quota_failure;
      auto violation = quota_failure.add_violations();
      violation->set_subject("name: " + request->name());
      violation->set_description("Limit one greeting per person");
      
      // Set up gRPC status with quota failure details
      google::rpc::Status s;
      s.set_code(static_cast<int>(StatusCode::RESOURCE_EXHAUSTED));
      s.set_message("Request limit exceeded");
      s.add_details()->PackFrom(quota_failure);
      
      // Create final status with error details
      status = Status(StatusCode::RESOURCE_EXHAUSTED, "Request limit exceeded",
                      s.SerializeAsString());
    } else {
      // For valid requests, format the greeting message
      reply->set_message(absl::StrFormat("Hello %s", request->name()));
      status = Status::OK;
    }
    
    // Send the response
    reactor->Finish(status);
    return reactor;
  }

 private:
  // Checks if a name has been seen before (thread-safe)
  bool CheckRequestDuplicate(const std::string& name) {
    absl::MutexLock lock(&mu_);  // Lock for thread safety
    // Returns false if insertion succeeded (name wasn't in set)
    return !request_name_set_.insert(name).second;
  }

  absl::Mutex mu_;  // Mutex for protecting request_name_set_
  std::unordered_set<std::string> request_name_set_;  // Tracks seen names
};

// Starts the gRPC server on the specified port
void RunServer(uint16_t port) {
  // Format server address string
  std::string server_address = absl::StrFormat("0.0.0.0:%d", port);
  GreeterServiceImpl service;

  // Enable default health check service and reflection
  grpc::EnableDefaultHealthCheckService(true);
  grpc::reflection::InitProtoReflectionServerBuilderPlugin();
  
  // Configure and build the server
  ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);

  // Start the server
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  // Wait for server shutdown
  server->Wait();
}

// Entry point for the application
int main(int argc, char** argv) {
  // Initialize command line parsing and logging
  absl::ParseCommandLine(argc, argv);
  absl::InitializeLog();
  
  // Start the server with the specified port
  RunServer(absl::GetFlag(FLAGS_port));
  return 0;
}
```

Key aspects covered in the comments:
1. File header and copyright notice
2. Purpose of each include group
3. Command line flag definition
4. Service implementation details
5. Thread safety mechanisms
6. Error handling and response generation
7. Server setup and configuration
8. Main application flow

The comments aim to explain both the high-level architecture and important implementation details while maintaining readability.