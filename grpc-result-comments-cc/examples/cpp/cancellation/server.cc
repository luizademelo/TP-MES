Here's the commented version of the code:

```c++
// Copyright 2023 gRPC authors.

// Include necessary headers
#include <grpcpp/grpcpp.h>  // Main gRPC C++ library

#include <iostream>
#include <memory>
#include <string>
#include <vector>

// Abseil libraries for flags, logging and string formatting
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

// Define a command line flag for server port with default value 50051
ABSL_FLAG(uint16_t, port, 50051, "Server port for the service");

// Using declarations to simplify code
using grpc::CallbackServerContext;
using grpc::Server;
using grpc::ServerBidiReactor;
using grpc::ServerBuilder;
using grpc::Status;
using helloworld::Greeter;
using helloworld::HelloReply;
using helloworld::HelloRequest;

// Implementation of the gRPC service
class KeyValueStoreServiceImpl final : public Greeter::CallbackService {
  // Override the bidirectional streaming RPC method
  ServerBidiReactor<HelloRequest, HelloReply>* SayHelloBidiStream(
      CallbackServerContext* context) override {
    // Inner Reactor class to handle the stream events
    class Reactor : public ServerBidiReactor<HelloRequest, HelloReply> {
     public:
      explicit Reactor() { StartRead(&request_); }  // Start reading immediately

      // Called when a read operation completes
      void OnReadDone(bool ok) override {
        if (!ok) {
          // Stream was cancelled or failed
          std::cout << "OnReadDone Cancelled!" << std::endl;
          return Finish(grpc::Status::CANCELLED);
        }
        // Create response by appending " Ack" to the received name
        response_.set_message(absl::StrCat(request_.name(), " Ack"));
        StartWrite(&response_);  // Send the response back
      }

      // Called when a write operation completes
      void OnWriteDone(bool ok) override {
        if (!ok) {
          // Write failed
          std::cout << "OnWriteDone Cancelled!" << std::endl;
          return Finish(grpc::Status::CANCELLED);
        }
        StartRead(&request_);  // Read next message from client
      }

      // Called when the stream is done
      void OnDone() override { delete this; }  // Clean up the reactor

     private:
      HelloRequest request_;  // Stores the incoming request
      HelloReply response_;   // Stores the outgoing response
    };

    // Create and return a new reactor instance for this stream
    return new Reactor();
  }
};

// Function to start and run the gRPC server
void RunServer(uint16_t port) {
  // Create server address string
  std::string server_address = absl::StrFormat("0.0.0.0:%d", port);
  KeyValueStoreServiceImpl service;  // Our service implementation

  ServerBuilder builder;  // gRPC server builder

  // Add listening port with insecure credentials (for demo purposes)
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());

  // Register our service implementation
  builder.RegisterService(&service);

  // Build and start the server
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  // Wait for server shutdown
  server->Wait();
}

// Main entry point
int main(int argc, char** argv) {
  // Initialize command line parsing and logging
  absl::ParseCommandLine(argc, argv);
  absl::InitializeLog();
  
  // Run the server with the port from command line or default
  RunServer(absl::GetFlag(FLAGS_port));
  return 0;
}
```

The comments explain:
1. The overall structure and purpose of each component
2. The bidirectional streaming RPC implementation details
3. The flow of requests and responses
4. Error handling cases
5. Memory management (especially the Reactor lifecycle)
6. Command line flag usage
7. Server setup and configuration

The comments are designed to help future developers understand both the high-level architecture and the implementation details of this gRPC service.