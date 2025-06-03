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

// Include necessary headers
#include <grpcpp/ext/otel_plugin.h>  // For OpenTelemetry plugin support
#include <grpcpp/grpcpp.h>           // Core gRPC functionality

#include <condition_variable>  // For thread synchronization
#include <mutex>              // For mutual exclusion
#include <string>             // For string operations

// Abseil and OpenTelemetry headers
#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/log/initialize.h"
#include "opentelemetry/exporters/prometheus/exporter_factory.h"
#include "opentelemetry/exporters/prometheus/exporter_options.h"
#include "opentelemetry/sdk/metrics/meter_provider.h"

// Include paths differ between Bazel and non-Bazel builds
#ifdef BAZEL_BUILD
#include "examples/cpp/otel/codelab/util.h"
#include "examples/protos/helloworld.grpc.pb.h"
#else
#include "helloworld.grpc.pb.h"
#include "util.h"
#endif

// Define command line flags using Abseil
ABSL_FLAG(std::string, target, "localhost:50051", "Server address");
ABSL_FLAG(std::string, prometheus_endpoint, "localhost:9465",
          "Prometheus exporter endpoint");

namespace {

// Import commonly used types into the namespace
using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using helloworld::Greeter;
using helloworld::HelloReply;
using helloworld::HelloRequest;

// Client class for the Greeter service
class GreeterClient {
 public:
  // Constructor takes a shared channel and creates a stub
  GreeterClient(std::shared_ptr<Channel> channel)
      : stub_(Greeter::NewStub(channel)) {}

  // Sends a greeting to the server and returns the response
  std::string SayHello(const std::string& user) {
    // Prepare the request
    HelloRequest request;
    request.set_name(user);

    // Will store the server's response
    HelloReply reply;

    // Context for the client
    ClientContext context;

    // Synchronization primitives for async call
    std::mutex mu;
    std::condition_variable cv;
    bool done = false;
    Status status;

    // Make an asynchronous call to the SayHello RPC
    stub_->async()->SayHello(&context, &request, &reply,
                             [&mu, &cv, &done, &status](Status s) {
                               // Callback when RPC completes
                               status = std::move(s);
                               std::lock_guard<std::mutex> lock(mu);
                               done = true;
                               cv.notify_one();
                             });

    // Wait for the RPC to complete
    std::unique_lock<std::mutex> lock(mu);
    while (!done) {
      cv.wait(lock);
    }

    // Process the response
    if (status.ok()) {
      return reply.message();
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return "RPC failed";
    }
  }

 private:
  std::unique_ptr<Greeter::Stub> stub_;  // gRPC stub for making RPC calls
};

// Main client execution function
void RunClient(const std::string& target_str) {
  // Channel arguments (empty in this case)
  grpc::ChannelArguments args;

  // Continuous loop making RPC calls
  while (true) {
    // Create client with insecure channel (no encryption)
    GreeterClient greeter(grpc::CreateCustomChannel(
        target_str, grpc::InsecureChannelCredentials(), args));
    
    // Make RPC call and print response
    std::string user("world");
    std::string reply = greeter.SayHello(user);
    std::cout << "Greeter received: " << reply << std::endl;
    
    // Wait before next call
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}

}  // namespace

// Main entry point
int main(int argc, char** argv) {
  // Initialize command line parsing and logging
  absl::ParseCommandLine(argc, argv);
  absl::InitializeLog();

  // Set up Prometheus metrics exporter
  opentelemetry::exporter::metrics::PrometheusExporterOptions opts;
  opts.url = absl::GetFlag(FLAGS_prometheus_endpoint);
  auto prometheus_exporter =
      opentelemetry::exporter::metrics::PrometheusExporterFactory::Create(opts);
  auto meter_provider =
      std::make_shared<opentelemetry::sdk::metrics::MeterProvider>();

  // Add latency view for gRPC client attempts
  AddLatencyView(meter_provider.get(), "grpc.client.attempt.duration", "s");
  
  // Configure metrics collection
  meter_provider->AddMetricReader(std::move(prometheus_exporter));
  
  // Register gRPC OpenTelemetry plugin
  auto status = grpc::OpenTelemetryPluginBuilder()
                    .SetMeterProvider(std::move(meter_provider))
                    .BuildAndRegisterGlobal();
  
  // Check for plugin registration errors
  if (!status.ok()) {
    std::cerr << "Failed to register gRPC OpenTelemetry Plugin: "
              << status.ToString() << std::endl;
    return static_cast<int>(status.code());
  }

  // Run the client with the specified target
  RunClient(absl::GetFlag(FLAGS_target));

  return 0;
}
```