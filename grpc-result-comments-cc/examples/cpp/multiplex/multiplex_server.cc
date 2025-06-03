Here's the commented version of the code:

```c++
/*
 *
 * Copyright 2023 gRPC authors.
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
#include <map>
#include <memory>
#include <string>

// Abseil headers for flags and logging
#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/log/initialize.h"
#include "absl/strings/str_format.h"

// Include protocol buffer generated headers
// Different paths for Bazel vs non-Bazel builds
#ifdef BAZEL_BUILD
#include "examples/protos/helloworld.grpc.pb.h"
#include "examples/protos/route_guide.grpc.pb.h"
#else
#include "helloworld.grpc.pb.h"
#include "route_guide.grpc.pb.h"
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
using routeguide::RouteGuide;

// Implementation of the Greeter service
class GreeterServiceImpl final : public Greeter::CallbackService {
  // Callback method for handling SayHello requests
  ServerUnaryReactor* SayHello(CallbackServerContext* context,
                               const HelloRequest* request,
                               HelloReply* reply) override {
    // Create response message by concatenating "Hello " with the request name
    std::string prefix("Hello ");
    reply->set_message(prefix + request->name());

    // Get the default reactor and finish the call with OK status
    ServerUnaryReactor* reactor = context->DefaultReactor();
    reactor->Finish(Status::OK);
    return reactor;
  }
};

// Implementation of the RouteGuide service
class RouteGuideImpl final : public RouteGuide::CallbackService {
 public:
  // Callback method for handling GetFeature requests
  ServerUnaryReactor* GetFeature(CallbackServerContext* context,
                                 const routeguide::Point* request,
                                 routeguide::Feature* response) override {
    // Create a key from latitude and longitude
    std::string key =
        absl::StrFormat("%d:%d", request->latitude(), request->longitude());
    
    // Set feature name with location information
    response->set_name(absl::StrFormat("Feature: latitude: %d, longitude: %d",
                                       request->latitude(),
                                       request->longitude()));
    // Set the feature's location
    *response->mutable_location() = *request;
    
    // Get the default reactor and finish the call with OK status
    ServerUnaryReactor* reactor = context->DefaultReactor();
    reactor->Finish(Status::OK);
    return reactor;
  }

 private:
  // Database of features (currently unused in this implementation)
  std::map<std::string, routeguide::Feature> features_db_;
};

// Function to start and run the gRPC server
void RunServer(uint16_t port) {
  // Create server address string
  std::string server_address = absl::StrFormat("0.0.0.0:%d", port);
  
  // Create service implementations
  GreeterServiceImpl greeter;
  RouteGuideImpl route_guide;

  // Enable default health check service
  grpc::EnableDefaultHealthCheckService(true);
  
  // Initialize server reflection plugin
  grpc::reflection::InitProtoReflectionServerBuilderPlugin();
  
  // Create server builder
  ServerBuilder builder;

  // Add listening port with insecure credentials (no encryption)
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());

  // Register services with the server
  builder.RegisterService(&greeter);
  builder.RegisterService(&route_guide);

  // Build and start the server
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  // Wait for server shutdown
  server->Wait();
}

// Main entry point
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
3. The service implementations and their methods
4. The server setup and configuration
5. The main program flow
6. Key operations within each method

The comments are designed to help future developers understand:
- What the code does at a high level
- The purpose of each component
- The flow of execution
- Important implementation details
- Where to look for specific functionality