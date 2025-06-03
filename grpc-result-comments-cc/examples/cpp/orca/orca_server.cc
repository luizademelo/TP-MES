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

// Include necessary headers
#include <grpcpp/ext/call_metric_recorder.h>  // For call metric recording
#include <grpcpp/ext/orca_service.h>          // For ORCA (Open Request Cost Aggregation) service
#include <grpcpp/grpcpp.h>                    // Core gRPC functionality
#include <grpcpp/health_check_service_interface.h>  // For health check service
#include <grpcpp/support/status.h>                   // For gRPC status codes

#include <cstddef>
#include <iostream>
#include <memory>
#include <string>

// Include ABSL (Abseil) libraries for flags and logging
#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/log/initialize.h"
#include "absl/strings/str_format.h"
#include "examples/protos/helloworld.grpc.pb.h"  // Generated protobuf headers

// Use declarations for cleaner code
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
  // Override the SayHello method for handling unary RPCs
  ServerUnaryReactor* SayHello(CallbackServerContext* context,
                               const HelloRequest* request,
                               HelloReply* reply) override {
    // Get the default reactor for handling the RPC
    ServerUnaryReactor* reactor = context->DefaultReactor();

    // Get the call metric recorder for collecting metrics about this RPC
    auto recorder = context->ExperimentalGetCallMetricRecorder();
    if (recorder == nullptr) {
      // If recorder is not available, finish with an error status
      reactor->Finish({grpc::StatusCode::INTERNAL,
                       "Unable to access metrics recorder. Make sure "
                       "EnableCallMetricRecording had been called."});
      return reactor;
    }

    // Record custom metrics for this RPC call
    recorder->RecordRequestCostMetric("db_queries", 10);  // Record DB queries metric
    recorder->RecordCpuUtilizationMetric(0.5);            // Record CPU utilization metric

    // Prepare the response message
    std::string prefix("Hello ");
    reply->set_message(prefix + request->name());

    // Finish the RPC with OK status
    reactor->Finish(Status::OK);
    return reactor;
  }
};

// Function to start and run the gRPC server
void RunServer(uint16_t port) {
  // Create server address string
  std::string server_address = absl::StrFormat("0.0.0.0:%d", port);
  
  // Initialize server builder
  ServerBuilder builder;
  GreeterServiceImpl service;

  // Create and configure server metric recorder for ORCA service
  auto server_metric_recorder =
      grpc::experimental::ServerMetricRecorder::Create();
  
  // Configure ORCA service with minimum report duration of 0.1 seconds
  grpc::experimental::OrcaService orca_service(
      server_metric_recorder.get(),
      grpc::experimental::OrcaService::Options().set_min_report_duration(
          absl::Seconds(0.1)));
  
  // Register ORCA service with the server
  builder.RegisterService(&orca_service);
  
  // Enable call metric recording for the server
  grpc::ServerBuilder::experimental_type(&builder).EnableCallMetricRecording(
      server_metric_recorder.get());

  // Enable default health check service
  grpc::EnableDefaultHealthCheckService(true);

  // Add listening port with insecure credentials (for demo purposes)
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());

  // Register the Greeter service implementation
  builder.RegisterService(&service);

  // Build and start the server
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;
  
  // Wait for the server to shutdown (blocking call)
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

Key points about the comments added:
1. Added file-level comment explaining the license
2. Added comments for each include statement explaining its purpose
3. Documented the command line flag definition
4. Added detailed comments for the Greeter service implementation
5. Explained the metric recording functionality
6. Documented the server setup and configuration process
7. Added comments for the main function flow
8. Explained the use of experimental features
9. Noted important implementation details

The comments aim to provide both high-level understanding of the code structure and specific details about important implementation choices.