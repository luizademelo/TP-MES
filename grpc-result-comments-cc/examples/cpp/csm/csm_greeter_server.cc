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
#include <grpcpp/ext/admin_services.h>
#include <grpcpp/ext/csm_observability.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
#include <grpcpp/xds_server_builder.h>

#include <iostream>
#include <memory>
#include <string>

// Abseil headers for flags, logging and string operations
#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/log/initialize.h"
#include "absl/log/log.h"
#include "absl/strings/str_cat.h"

// OpenTelemetry headers for metrics collection
#include "opentelemetry/exporters/prometheus/exporter_factory.h"
#include "opentelemetry/exporters/prometheus/exporter_options.h"
#include "opentelemetry/sdk/metrics/meter_provider.h"

// gRPC utility for getting hostname
#include "src/core/util/gethostname.h"

// Include the generated protobuf headers
#ifdef BAZEL_BUILD
#include "examples/protos/helloworld.grpc.pb.h"
#else
#include "helloworld.grpc.pb.h"
#endif

// Define a command line flag for server port with default value 50051
ABSL_FLAG(int32_t, port, 50051, "Server port for service.");

// Using declarations for gRPC and protobuf classes
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
  // Implementation of the SayHello RPC method
  ServerUnaryReactor* SayHello(CallbackServerContext* context,
                               const HelloRequest* request,
                               HelloReply* reply) override {
    // Create a response message with hostname prefix
    std::string prefix("Hello from ");
    prefix += my_name + " ";
    reply->set_message(prefix + request->name());

    // Get the default reactor and finish the RPC with OK status
    ServerUnaryReactor* reactor = context->DefaultReactor();
    reactor->Finish(Status::OK);
    return reactor;
  }

 public:
  // Constructor that takes hostname as parameter
  GreeterServiceImpl(const std::string& my_hostname) : my_name(my_hostname) {}

 private:
  const std::string my_name;  // Stores the hostname
};

// Function to run the gRPC server
void RunServer(const char* hostname) {
  // Enable default health check service
  grpc::EnableDefaultHealthCheckService(true);
  // Initialize server reflection plugin
  grpc::reflection::InitProtoReflectionServerBuilderPlugin();
  
  // Get port from command line flag
  int port = absl::GetFlag(FLAGS_port);
  
  // Create XDS server builder
  grpc::XdsServerBuilder xds_builder;
  std::unique_ptr<Server> xds_enabled_server;

  // Create service instance with hostname
  std::string my_hostname(hostname);
  GreeterServiceImpl service(my_hostname);

  // Register service with the server
  xds_builder.RegisterService(&service);

  // Add listening port with insecure credentials
  xds_builder.AddListeningPort(absl::StrCat("0.0.0.0:", port),
                               grpc::InsecureServerCredentials());
  // Build and start the server
  xds_enabled_server = xds_builder.BuildAndStart();
  LOG(INFO) << "Server starting on 0.0.0.0:" << port;

  // Wait for server shutdown
  xds_enabled_server->Wait();
}

int main(int argc, char** argv) {
  // Parse command line flags
  absl::ParseCommandLine(argc, argv);
  // Initialize logging
  absl::InitializeLog();
  
  // Configure Prometheus exporter for metrics collection
  opentelemetry::exporter::metrics::PrometheusExporterOptions opts;
  opts.url = "0.0.0.0:9464";
  opts.without_otel_scope = false;
  
  // Create Prometheus exporter and meter provider
  auto prometheus_exporter =
      opentelemetry::exporter::metrics::PrometheusExporterFactory::Create(opts);
  auto meter_provider =
      std::make_shared<opentelemetry::sdk::metrics::MeterProvider>();
  meter_provider->AddMetricReader(std::move(prometheus_exporter));
  
  // Initialize CSM (Cloud Service Mesh) observability
  auto observability = grpc::CsmObservabilityBuilder()
                           .SetMeterProvider(std::move(meter_provider))
                           .BuildAndRegister();
  if (!observability.ok()) {
    std::cerr << "CsmObservability::Init() failed: "
              << observability.status().ToString() << std::endl;
    return static_cast<int>(observability.status().code());
  }
  
  // Get hostname for the server
  const char* hostname = grpc_gethostname();
  if (hostname == nullptr) {
    std::cout << "Failed to get hostname, terminating" << std::endl;
    return 1;
  }
  
  // Run the server with the obtained hostname
  RunServer(hostname);
  return 0;
}
```