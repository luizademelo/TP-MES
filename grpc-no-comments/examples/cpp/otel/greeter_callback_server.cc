
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

#include <grpcpp/ext/otel_plugin.h>

#include <iostream>
#include <memory>
#include <string>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/log/initialize.h"
#include "absl/strings/str_format.h"
#include "opentelemetry/exporters/prometheus/exporter_factory.h"
#include "opentelemetry/exporters/prometheus/exporter_options.h"
#include "opentelemetry/sdk/metrics/meter_provider.h"

#ifdef BAZEL_BUILD
#include "examples/cpp/otel/util.h"
#else
#include "util.h"
#endif

ABSL_FLAG(uint16_t, port, 50051, "Server port for the service");
ABSL_FLAG(std::string, prometheus_endpoint, "localhost:9464",
          "Prometheus exporter endpoint");

int main(int argc, char** argv) {
  absl::ParseCommandLine(argc, argv);
  absl::InitializeLog();

  opentelemetry::exporter::metrics::PrometheusExporterOptions opts;
  opts.url = absl::GetFlag(FLAGS_prometheus_endpoint);
  opts.without_otel_scope = false;
  auto prometheus_exporter =
      opentelemetry::exporter::metrics::PrometheusExporterFactory::Create(opts);
  auto meter_provider =
      std::make_shared<opentelemetry::sdk::metrics::MeterProvider>();

  AddLatencyView(meter_provider.get(), "grpc.server.call.duration", "s");
  meter_provider->AddMetricReader(std::move(prometheus_exporter));
  auto status = grpc::OpenTelemetryPluginBuilder()
                    .SetMeterProvider(std::move(meter_provider))
                    .BuildAndRegisterGlobal();
  if (!status.ok()) {
    std::cerr << "Failed to register gRPC OpenTelemetry Plugin: "
              << status.ToString() << std::endl;
    return static_cast<int>(status.code());
  }
  RunServer(absl::GetFlag(FLAGS_port));
  return 0;
}
