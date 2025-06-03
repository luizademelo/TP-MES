Here's the commented version of the code:

```c++
/*
 *
 * Copyright 2021 gRPC authors.
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

#ifndef HAVE_ABSEIL
#define HAVE_ABSEIL
#endif

// Include necessary gRPC headers
#include <grpcpp/ext/otel_plugin.h>           // OpenTelemetry plugin
#include <grpcpp/ext/proto_server_reflection_plugin.h>  // Server reflection
#include <grpcpp/grpcpp.h>                    // Core gRPP functionality
#include <grpcpp/health_check_service_interface.h>  // Health check service

// Standard C++ headers
#include <iostream>
#include <memory>
#include <string>

// Abseil headers for flags and logging
#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/log/initialize.h"
#include "absl/strings/str_format.h"

// OpenTelemetry headers for metrics
#include "opentelemetry/exporters/prometheus/exporter_factory.h"
#include "opentelemetry/exporters/prometheus/exporter_options.h"
#include "opentelemetry/sdk/metrics/meter_provider.h"

// Include project-specific headers with different paths for Bazel vs non-Bazel builds
#ifdef BAZEL_BUILD
#include "examples/cpp/otel/codelab/util.h"
#include "examples/protos/helloworld.grpc.pb.h"
#else
#include "helloworld.grpc.pb.h"
#include "util.h"
#endif

// Define command line flags using Abseil
ABSL_FLAG(uint16_t, port, 50051, "Server port for the service");
ABSL_FLAG(std::string, prometheus_endpoint, "localhost:9464",
          "Prometheus exporter endpoint");

namespace {

// Import commonly used types into the namespace
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
  // Callback method for handling SayHello RPCs
  ServerUnaryReactor* SayHello(CallbackServerContext* context,
                               const HelloRequest* request,
                               HelloReply* reply) override {
    // Create response message by combining prefix with client's name
    std::string prefix("Hello ");
    reply->set_message(prefix + request->name());

    // Simulate processing delay (5 seconds)
    std::this_thread::sleep_for(std::chrono::seconds(5));

    // Get default reactor and finish the RPC with OK status
    ServerUnaryReactor* reactor = context->DefaultReactor();
    reactor->Finish(Status::OK);
    return reactor;
  }
};

// Function to start and run the gRPC server
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

}  // namespace

// Main entry point
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

Key additions in the comments:
1. Explained the purpose of each major include group
2. Documented the command line flags
3. Added detailed comments for the Greeter service implementation
4. Explained the server setup and configuration process
5. Noted important details like the insecure credentials (which should be changed for production)
6. Explained the artificial delay in the SayHello method
7. Documented the main function flow
8. Added notes about the namespace usage and type imports

The comments provide context for future maintainers while avoiding over-commenting obvious constructs. They focus on explaining the why rather than the what, except where the implementation might be non-obvious.