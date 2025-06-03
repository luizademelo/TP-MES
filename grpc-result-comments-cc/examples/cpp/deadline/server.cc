Here's the commented version of the code:

```c++
// Copyright 2023 gRPC authors.

// Include necessary headers
#include <grpcpp/grpcpp.h>

#include <chrono>
#include <condition_variable>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>

// Include Abseil libraries for flags, logging, and string utilities
#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/log/initialize.h"
#include "absl/strings/match.h"
#include "absl/strings/str_format.h"

// Include the generated gRPC protobuf headers
#ifdef BAZEL_BUILD
#include "examples/protos/helloworld.grpc.pb.h"
#else
#include "helloworld.grpc.pb.h"
#endif

// Define a command line flag for server port with default value 50051
ABSL_FLAG(uint16_t, port, 50051, "Server port for the service");

// Using declarations for gRPC and protobuf namespaces
using grpc::CallbackServerContext;
using grpc::Channel;
using grpc::ClientContext;
using grpc::Server;
using grpc::ServerBidiReactor;
using grpc::ServerBuilder;
using grpc::ServerUnaryReactor;
using grpc::Status;
using helloworld::Greeter;
using helloworld::HelloReply;
using helloworld::HelloRequest;

// Implementation of the Greeter service
class GreeterServiceImpl final : public Greeter::CallbackService {
 public:
  // Constructor that creates a channel to itself for request propagation
  GreeterServiceImpl(const std::string& self_address) {
    self_channel_ =
        grpc::CreateChannel(self_address, grpc::InsecureChannelCredentials());
  }

 private:
  // Implementation of the SayHello RPC method
  ServerUnaryReactor* SayHello(CallbackServerContext* context,
                               const HelloRequest* request,
                               HelloReply* reply) override {
    // Check if the request should be propagated
    if (absl::StartsWith(request->name(), "[propagate me]")) {
      // Create a stub for self-communication
      std::unique_ptr<Greeter::Stub> stub = Greeter::NewStub(self_channel_);
      
      // Artificial delay to simulate processing
      std::this_thread::sleep_for(std::chrono::milliseconds(800));

      // Prepare new request by removing the propagation prefix
      HelloRequest new_request;
      new_request.set_name(request->name().substr(14));
      
      // Create new context from the incoming one
      std::unique_ptr<ClientContext> new_context =
          ClientContext::FromCallbackServerContext(*context);
      
      // Synchronization primitives for async call
      std::mutex mu;
      std::condition_variable cv;
      bool done = false;
      Status status;
      
      // Make asynchronous call to self
      stub->async()->SayHello(new_context.get(), &new_request, reply,
                              [&mu, &cv, &done, &status](Status s) {
                                status = std::move(s);
                                std::lock_guard<std::mutex> lock(mu);
                                done = true;
                                cv.notify_one();
                              });
      
      // Wait for the async call to complete
      std::unique_lock<std::mutex> lock(mu);
      while (!done) {
        cv.wait(lock);
      }
      
      // Return reactor with the final status
      ServerUnaryReactor* reactor = context->DefaultReactor();
      reactor->Finish(status);
      return reactor;
    }

    // Special case for delayed response
    if (request->name() == "delay") {
      std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    }

    // Normal response - echo back the request name
    reply->set_message(request->name());

    // Return reactor with OK status
    ServerUnaryReactor* reactor = context->DefaultReactor();
    reactor->Finish(Status::OK);
    return reactor;
  }

  // Channel for communicating with self
  std::shared_ptr<Channel> self_channel_;
};

// Function to start and run the gRPC server
void RunServer(uint16_t port) {
  // Create server address string
  std::string server_address = absl::StrFormat("0.0.0.0:%d", port);
  
  // Create service instance
  GreeterServiceImpl service(server_address);

  // Build server
  ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);

  // Start server
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  // Wait for server shutdown
  server->Wait();
}

// Main function
int main(int argc, char** argv) {
  // Initialize command line parsing and logging
  absl::ParseCommandLine(argc, argv);
  absl::InitializeLog();
  
  // Run server with the specified port
  RunServer(absl::GetFlag(FLAGS_port));
  return 0;
}
```

The comments explain:
1. The overall structure and purpose of each component
2. The special handling of "[propagate me]" requests
3. The self-referential channel usage
4. The asynchronous call pattern with synchronization
5. The command line flag handling
6. The server setup and lifecycle

The comments are designed to help future developers understand both the high-level architecture and the detailed implementation choices.