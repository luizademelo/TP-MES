
// Copyright 2020 gRPC authors.

#include <grpc/grpc.h>
#include <grpcpp/ext/csm_observability.h>
#include <grpcpp/health_check_service_interface.h>

#include <iostream>

#include "absl/flags/flag.h"
#include "absl/log/log.h"
#include "opentelemetry/exporters/prometheus/exporter_factory.h"
#include "opentelemetry/exporters/prometheus/exporter_options.h"
#include "opentelemetry/sdk/metrics/meter_provider.h"
#include "src/core/util/gethostname.h"
#include "test/core/test_util/test_config.h"
#include "test/cpp/interop/xds_interop_server_lib.h"
#include "test/cpp/util/test_config.h"

ABSL_FLAG(int32_t, port, 8080, "Server port for service.");
ABSL_FLAG(int32_t, maintenance_port, 8081,
          "Server port for maintenance if --security is \"secure\".");
ABSL_FLAG(std::string, server_id, "cpp_server",
          "Server ID to include in responses.");
ABSL_FLAG(bool, secure_mode, false,
          "If true, XdsServerCredentials are used, InsecureServerCredentials "
          "otherwise");
ABSL_FLAG(bool, enable_csm_observability, false,
          "Whether to enable CSM Observability");

grpc::CsmObservability EnableCsmObservability() {
  VLOG(2) << "Registering Prometheus exporter";
  opentelemetry::exporter::metrics::PrometheusExporterOptions opts;

  opts.url = "0.0.0.0:9464";
  opts.without_otel_scope = false;
  auto prometheus_exporter =
      opentelemetry::exporter::metrics::PrometheusExporterFactory::Create(opts);
  auto meter_provider =
      std::make_shared<opentelemetry::sdk::metrics::MeterProvider>();
  meter_provider->AddMetricReader(std::move(prometheus_exporter));
  auto observability = grpc::CsmObservabilityBuilder()
                           .SetMeterProvider(std::move(meter_provider))
                           .BuildAndRegister();
  assert(observability.ok());
  return *std::move(observability);
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  grpc::testing::InitTest(&argc, &argv, true);
  char* hostname = grpc_gethostname();
  if (hostname == nullptr) {
    std::cout << "Failed to get hostname, terminating" << std::endl;
    return 1;
  }
  int port = absl::GetFlag(FLAGS_port);
  if (port == 0) {
    std::cout << "Invalid port, terminating" << std::endl;
    return 1;
  }
  int maintenance_port = absl::GetFlag(FLAGS_maintenance_port);
  if (maintenance_port == 0) {
    std::cout << "Invalid maintenance port, terminating" << std::endl;
    return 1;
  }
  grpc::EnableDefaultHealthCheckService(false);
  bool enable_csm_observability = absl::GetFlag(FLAGS_enable_csm_observability);
  grpc::CsmObservability observability;
  if (enable_csm_observability) {
    observability = EnableCsmObservability();
  }
  grpc::testing::RunServer(
      absl::GetFlag(FLAGS_secure_mode), port, maintenance_port, hostname,
      absl::GetFlag(FLAGS_server_id), [](grpc::Server* ) {});

  return 0;
}
