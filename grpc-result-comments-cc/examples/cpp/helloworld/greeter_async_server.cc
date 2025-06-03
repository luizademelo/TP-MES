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

// Include necessary headers
#include <grpcpp/grpcpp.h>  // Main gRPC C++ library
#include <iostream>         // For console I/O
#include <memory>           // For smart pointers
#include <string>           // For string operations
#include <thread>           // For threading support

// Include Abseil libraries for flags and logging
#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/log/check.h"
#include "absl/strings/str_format.h"

// Include the generated protobuf headers
#ifdef BAZEL_BUILD
#include "examples/protos/helloworld.grpc.pb.h"
#else
#include "helloworld.grpc.pb.h"
#endif

// Define a command line flag for server port with default value 50051
ABSL_FLAG(uint16_t, port, 50051, "Server port for the service");

// Using declarations to simplify code
using grpc::Server;
using grpc::ServerAsyncResponseWriter;
using grpc::ServerBuilder;
using grpc::ServerCompletionQueue;
using grpc::ServerContext;
using grpc::Status;
using helloworld::Greeter;
using helloworld::HelloReply;
using helloworld::HelloRequest;

// Server implementation class
class ServerImpl final {
 public:
  // Destructor - shuts down server and completion queue
  ~ServerImpl() {
    server_->Shutdown();
    cq_->Shutdown();
  }

  // Main server run method
  void Run(uint16_t port) {
    // Create server address string
    std::string server_address = absl::StrFormat("0.0.0.0:%d", port);

    // Initialize server builder
    ServerBuilder builder;

    // Add listening port with insecure credentials (no encryption)
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());

    // Register the service implementation
    builder.RegisterService(&service_);

    // Get completion queue from builder
    cq_ = builder.AddCompletionQueue();

    // Build and start the server
    server_ = builder.BuildAndStart();
    std::cout << "Server listening on " << server_address << std::endl;

    // Start handling RPCs
    HandleRpcs();
  }

 private:
  // Nested class to handle individual RPC calls
  class CallData {
   public:
    // Constructor - takes service and completion queue
    CallData(Greeter::AsyncService* service, ServerCompletionQueue* cq)
        : service_(service), cq_(cq), responder_(&ctx_), status_(CREATE) {
      // Start processing immediately
      Proceed();
    }

    // Main processing method implementing state machine
    void Proceed() {
      if (status_ == CREATE) {
        // First state: prepare to receive request
        status_ = PROCESS;

        // Request that the system start processing SayHello requests
        service_->RequestSayHello(&ctx_, &request_, &responder_, cq_, cq_,
                                  this);
      } else if (status_ == PROCESS) {
        // Second state: process the request
        // Spawn new CallData instance to handle new requests
        new CallData(service_, cq_);

        // Prepare the response
        std::string prefix("Hello ");
        reply_.set_message(prefix + request_.name());

        // Transition to FINISH state and send response
        status_ = FINISH;
        responder_.Finish(reply_, Status::OK, this);
      } else {
        // Third state: clean up
        CHECK_EQ(status_, FINISH);

        // Delete this instance
        delete this;
      }
    }

   private:
    // Service instance
    Greeter::AsyncService* service_;

    // Completion queue
    ServerCompletionQueue* cq_;

    // Server context
    ServerContext ctx_;

    // Request message
    HelloRequest request_;

    // Response message
    HelloReply reply_;

    // Response writer
    ServerAsyncResponseWriter<HelloReply> responder_;

    // Call state machine states
    enum CallStatus { CREATE, PROCESS, FINISH };
    CallStatus status_;  // Current state of the call
  };

  // Method to handle incoming RPCs
  void HandleRpcs() {
    // Create initial CallData to start processing requests
    new CallData(&service_, cq_.get());
    
    void* tag;  // Receives the operation tag
    bool ok;    // Receives operation success status
    
    // Main processing loop
    while (true) {
      // Block waiting for next event from completion queue
      CHECK(cq_->Next(&tag, &ok));
      CHECK(ok);
      
      // Process the event by calling Proceed() on the CallData instance
      static_cast<CallData*>(tag)->Proceed();
    }
  }

  // Member variables
  std::unique_ptr<ServerCompletionQueue> cq_;  // Completion queue
  Greeter::AsyncService service_;              // Service implementation
  std::unique_ptr<Server> server_;             // Server instance
};

// Main function
int main(int argc, char** argv) {
  // Parse command line flags
  absl::ParseCommandLine(argc, argv);
  
  // Create and run server
  ServerImpl server;
  server.Run(absl::GetFlag(FLAGS_port));

  return 0;
}
```

The comments explain:
1. The overall structure and purpose of each component
2. The asynchronous processing model using completion queues
3. The state machine pattern in CallData
4. The flow of request processing
5. The purpose of each member variable
6. The main server lifecycle

The comments are designed to help future developers understand both the high-level architecture and the detailed implementation choices.