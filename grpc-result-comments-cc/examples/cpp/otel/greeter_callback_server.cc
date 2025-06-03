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

// Define HAVE_ABSEIL if not already defined to indicate Abseil library availability
#ifndef HAVE_ABSEIL
#define HAVE_ABSEIL
#endif

#include <grpcpp/ext/otel_plugin.h>  // gRPC OpenTelemetry plugin

#include <iostream>
#include <memory>
#include <string>

// Abseil libraries for flags, logging, and string formatting
#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/log/initialize.h"
#include "absl/strings/str_format.h"

// OpenTelemetry libraries for metrics export
#include "opentelemetry/exporters/prometheus/exporter_factory.h"
#include "opentelemetry/exporters/prometheus/exporter_options.h"
#include "opentelemetry/sdk/metrics/meter_provider.h"

// Include path differs between Bazel and non-Bazel builds
#ifdef BAZEL_BUILD
#include "examples/cpp/otel/util.h"
#else
#include "util.h"
#endif

// Define command line flags using Abseil
// Server port flag with default value 50051
ABSL_FLAG(uint16_t, port, 50051, "Server port for the service");
// Prometheus endpoint flag with default value "localhost:9464"
ABSL_FLAG(std::string, prometheus_endpoint, "localhost:9464",
          "Prometheus exporter endpoint");

/**
 * @brief Main function that sets up OpenTelemetry metrics collection and starts gRPC server
 * @param argc Argument count
 * @param argv Argument vector
 * @return int Returns 0 on success, error code on failure
 */
int main(int argc, char** argv) {
  // Parse command line flags
  absl::ParseCommandLine(argc, argv);
  // Initialize Abseil logging
  absl::InitializeLog();

  // Configure Prometheus exporter options
  opentelemetry::exporter::metrics::PrometheusExporterOptions opts;
  opts.url = absl::GetFlag(FLAGS_prometheus_endpoint);  // Set endpoint from flag
  opts.without_otel_scope = false;  // Include OpenTelemetry scope information

  // Create Prometheus exporter and meter provider
  auto prometheus_exporter =
      opentelemetry::exporter::metrics::PrometheusExporterFactory::Create(opts);
  auto meter_provider =
      std::make_shared<opentelemetry::sdk::metrics::MeterProvider>();

  // Add latency view for gRPC server calls (measured in seconds)
  AddLatencyView(meter_provider.get(), "grpc.server.call.duration", "s");
  // Add Prometheus exporter as a metric reader
  meter_provider->AddMetricReader(std::move(prometheus_exporter));

  // Configure and register gRPC OpenTelemetry plugin
  auto status = grpc::OpenTelemetryPluginBuilder()
                    .SetMeterProvider(std::move(meter_provider))
                    .BuildAndRegisterGlobal();
  
  // Check if plugin registration succeeded
  if (!status.ok()) {
    std::cerr << "Failed to register gRPC OpenTelemetry Plugin: "
              << status.ToString() << std::endl;
    return static_cast<int>(status.code());
  }

  // Start the gRPC server with the specified port
  RunServer(absl::GetFlag(FLAGS_port));
  return 0;
}

```