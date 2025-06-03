Here's the commented version of the code:

```c++
/*
 *
 * Copyright 2024 gRPC authors.
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

// Abseil flags and logging headers
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

// Define a command line flag for the server port with default value 50051
ABSL_FLAG(uint16_t, port, 50051, "Server port for the service");

// Using declarations for gRPC and protobuf types
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
 public:
  // Sets the health check service for this service implementation
  void set_health_check_service(
      grpc::HealthCheckServiceInterface* health_check_service) {
    health_check_service_ = health_check_service;
  }

 private:
  // Implementation of the SayHello RPC method
  ServerUnaryReactor* SayHello(CallbackServerContext* context,
                               const HelloRequest* request,
                               HelloReply* reply) override {
    // Create response message by prepending "Hello " to the request name
    std::string prefix("Hello ");
    reply->set_message(prefix + request->name());
    
    // Get the default reactor and finish the RPC call with OK status
    ServerUnaryReactor* reactor = context->DefaultReactor();
    reactor->Finish(Status::OK);

    // Toggle serving status and update health check service
    is_serving_ = !is_serving_;
    health_check_service_->SetServingStatus(is_serving_);
    
    return reactor;
  }

  // Pointer to health check service interface
  grpc::HealthCheckServiceInterface* health_check_service_ = nullptr;
  // Current serving status (toggled on each request)
  bool is_serving_ = true;
};

// Function to run the gRPC server
void RunServer(uint16_t port) {
  // Create server address string
  std::string server_address = absl::StrFormat("0.0.0.0:%d", port);
  GreeterServiceImpl service;

  // Enable default health check service
  grpc::EnableDefaultHealthCheckService(true);
  // Initialize server reflection plugin
  grpc::reflection::InitProtoReflectionServerBuilderPlugin();
  
  // Create server builder
  ServerBuilder builder;

  // Add listening port with insecure credentials
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());

  // Register the service implementation
  builder.RegisterService(&service);

  // Build and start the server
  std::unique_ptr<Server> server(builder.BuildAndStart());
  // Set health check service for our implementation
  service.set_health_check_service(server->GetHealthCheckService());
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
  // Run the server with the specified port
  RunServer(absl::GetFlag(FLAGS_port));
  return 0;
}
```