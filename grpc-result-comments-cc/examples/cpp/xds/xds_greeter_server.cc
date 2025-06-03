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
#include <grpcpp/ext/admin_services.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
#include <grpcpp/xds_server_builder.h>

// Standard library includes
#include <iostream>
#include <memory>
#include <string>

// Abseil library includes for flags and logging
#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/log/initialize.h"
#include "absl/log/log.h"
#include "absl/strings/str_cat.h"

// Include generated protobuf headers
#ifdef BAZEL_BUILD
#include "examples/protos/helloworld.grpc.pb.h"
#else
#include "helloworld.grpc.pb.h"
#endif

// Define command line flags using Abseil
ABSL_FLAG(int32_t, port, 50051, "Server port for service.");
ABSL_FLAG(int32_t, maintenance_port, 50052,
          "Server port for maintenance if --secure is used.");
ABSL_FLAG(bool, secure, true, "Secure mode");

// Using declarations for commonly used gRPC types
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
  // Callback method for handling SayHello RPC
  ServerUnaryReactor* SayHello(CallbackServerContext* context,
                               const HelloRequest* request,
                               HelloReply* reply) override {
    // Create response message by concatenating "Hello " with the request name
    std::string prefix("Hello ");
    reply->set_message(prefix + request->name());

    // Get the default reactor and finish the RPC with OK status
    ServerUnaryReactor* reactor = context->DefaultReactor();
    reactor->Finish(Status::OK);
    return reactor;
  }
};

// Function to run the gRPC server
void RunServer() {
  // Enable default health check service
  grpc::EnableDefaultHealthCheckService(true);
  // Initialize server reflection plugin
  grpc::reflection::InitProtoReflectionServerBuilderPlugin();
  
  // Get port numbers from command line flags
  int port = absl::GetFlag(FLAGS_port);
  int maintenance_port = absl::GetFlag(FLAGS_maintenance_port);
  
  // Create server builders
  grpc::XdsServerBuilder xds_builder;
  ServerBuilder builder;
  
  // Server instances
  std::unique_ptr<Server> xds_enabled_server;
  std::unique_ptr<Server> server;
  
  // Service implementation
  GreeterServiceImpl service;

  // Register service with XDS builder
  xds_builder.RegisterService(&service);
  
  // Check if secure mode is enabled
  if (absl::GetFlag(FLAGS_secure)) {
    // Configure XDS-enabled server with secure credentials
    xds_builder.AddListeningPort(
        absl::StrCat("0.0.0.0:", port),
        grpc::XdsServerCredentials(grpc::InsecureServerCredentials()));
    xds_enabled_server = xds_builder.BuildAndStart();
    LOG(INFO) << "Server starting on 0.0.0.0:" << port;
    
    // Add admin services to the maintenance server
    grpc::AddAdminServices(&builder);

    // Start maintenance server
    builder.AddListeningPort(absl::StrCat("0.0.0.0:", maintenance_port),
                             grpc::InsecureServerCredentials());
    server = builder.BuildAndStart();
    LOG(INFO) << "Maintenance server listening on 0.0.0.0:" << maintenance_port;
  } else {
    // Non-secure mode: add admin services directly to XDS builder
    grpc::AddAdminServices(&xds_builder);

    // Start single server
    builder.AddListeningPort(absl::StrCat("0.0.0.0:", port),
                             grpc::InsecureServerCredentials());
    server = xds_builder.BuildAndStart();
    LOG(INFO) << "Server listening on 0.0.0.0:" << port;
  }

  // Wait for server shutdown
  server->Wait();
}

// Main entry point
int main(int argc, char** argv) {
  // Initialize command line parsing and logging
  absl::ParseCommandLine(argc, argv);
  absl::InitializeLog();
  
  // Run the server
  RunServer();
  return 0;
}
```

Key improvements made:
1. Added detailed comments explaining each major section of code
2. Documented the purpose of each include
3. Explained the command line flags
4. Added clear documentation for the service implementation
5. Detailed the server setup logic, including secure vs non-secure modes
6. Explained the flow of server initialization and execution
7. Added context for the main function

The comments now provide a comprehensive understanding of what the code does and why, making it much easier for future developers to maintain and modify.