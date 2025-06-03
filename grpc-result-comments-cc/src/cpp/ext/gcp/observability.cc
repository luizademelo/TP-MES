Here's the commented version of the code:

```c++
// Copyright 2022 gRPC authors.

// Include necessary gRPC and related headers
#include <grpc/grpc.h>
#include <grpc/support/port_platform.h>
#include <grpcpp/channel.h>
#include <grpcpp/ext/gcp_observability.h>
#include <grpcpp/opencensus.h>
#include <grpcpp/security/credentials.h>
#include <grpcpp/support/channel_arguments.h>
#include <stdint.h>

// Standard C++ includes
#include <algorithm>
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>

// ABSL includes for status handling and string operations
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/str_cat.h"
#include "absl/time/clock.h"
#include "absl/time/time.h"

// Google Cloud API protobuf includes
#include "google/api/monitored_resource.pb.h"
#include "google/devtools/cloudtrace/v2/tracing.grpc.pb.h"
#include "google/monitoring/v3/metric_service.grpc.pb.h"

// OpenCensus includes for metrics and tracing
#include "opencensus/exporters/stats/stackdriver/stackdriver_exporter.h"
#include "opencensus/exporters/trace/stackdriver/stackdriver_exporter.h"
#include "opencensus/stats/stats.h"
#include "opencensus/trace/sampler.h"
#include "opencensus/trace/trace_config.h"

// gRPC internal includes
#include "src/core/ext/filters/logging/logging_filter.h"
#include "src/core/util/crash.h"
#include "src/core/util/notification.h"
#include "src/cpp/client/client_stats_interceptor.h"
#include "src/cpp/ext/filters/census/client_filter.h"
#include "src/cpp/ext/filters/census/grpc_plugin.h"
#include "src/cpp/ext/filters/census/open_census_call_tracer.h"
#include "src/cpp/ext/gcp/environment_autodetect.h"
#include "src/cpp/ext/gcp/observability_config.h"
#include "src/cpp/ext/gcp/observability_logging_sink.h"

namespace grpc {

namespace internal {
namespace {

// Global logging sink for observability data
grpc::internal::ObservabilityLoggingSink* g_logging_sink = nullptr;

// Flag to track if GCP observability has been initialized
bool g_gcp_observability_initialized = false;

// Constants for OpenCensus trace configuration
constexpr uint32_t kMaxAttributes = 128;
constexpr uint32_t kMaxAnnotations = 128;
constexpr uint32_t kMaxMessageEvents = 128;
constexpr uint32_t kMaxLinks = 128;

// Stackdriver service addresses
constexpr char kGoogleStackdriverTraceAddress[] = "cloudtrace.googleapis.com";
constexpr char kGoogleStackdriverStatsAddress[] = "monitoring.googleapis.com";

// Registers OpenCensus views for GCP observability metrics
void RegisterOpenCensusViewsForGcpObservability() {
  // Client-side metrics
  experimental::ClientStartedRpcs().RegisterForExport();
  experimental::ClientCompletedRpcs().RegisterForExport();
  experimental::ClientRoundtripLatency().RegisterForExport();
  internal::ClientApiLatency().RegisterForExport();
  experimental::ClientSentCompressedMessageBytesPerRpc().RegisterForExport();
  experimental::ClientReceivedCompressedMessageBytesPerRpc()
      .RegisterForExport();

  // Server-side metrics
  experimental::ServerStartedRpcs().RegisterForExport();
  experimental::ServerCompletedRpcs().RegisterForExport();
  experimental::ServerSentCompressedMessageBytesPerRpc().RegisterForExport();
  experimental::ServerReceivedCompressedMessageBytesPerRpc()
      .RegisterForExport();
  experimental::ServerServerLatency().RegisterForExport();
}

}  // namespace

// Initializes GCP observability for gRPC
absl::Status GcpObservabilityInit() {
  // Read configuration from environment variables
  auto config = grpc::internal::GcpObservabilityConfig::ReadFromEnv();
  if (!config.ok()) {
    return config.status();
  }
  
  // Early return if no observability features are configured
  if (!config->cloud_trace.has_value() &&
      !config->cloud_monitoring.has_value() &&
      !config->cloud_logging.has_value()) {
    return absl::OkStatus();
  }
  
  // Prevent double initialization
  if (g_gcp_observability_initialized) {
    grpc_core::Crash("GCP Observability for gRPC was already initialized.");
  }
  g_gcp_observability_initialized = true;
  
  // Auto-detect GCP environment
  grpc::internal::EnvironmentAutoDetect::Create(config->project_id);
  
  // Configure tracing if enabled
  if (!config->cloud_trace.has_value()) {
    grpc::internal::EnableOpenCensusTracing(false);
  }
  
  // Configure monitoring if enabled
  if (!config->cloud_monitoring.has_value()) {
    grpc::internal::EnableOpenCensusStats(false);
  } else {
    // Register client interceptor for monitoring
    grpc::internal::RegisterGlobalClientStatsInterceptorFactory(
        new grpc::internal::OpenCensusClientInterceptorFactory);
  }
  
  // Configure logging if enabled
  if (config->cloud_logging.has_value()) {
    g_logging_sink = new grpc::internal::ObservabilityLoggingSink(
        config->cloud_logging.value(), config->project_id, config->labels);
    grpc_core::RegisterLoggingFilter(g_logging_sink);
  }

  // Register OpenCensus plugin if either tracing or monitoring is enabled
  if (config->cloud_trace.has_value() || config->cloud_monitoring.has_value()) {
    grpc::RegisterOpenCensusPlugin();
  }

  // Set up Stackdriver exporters if needed
  if (config->cloud_trace.has_value() || config->cloud_monitoring.has_value()) {
    grpc_init();
    grpc_core::Notification notification;
    grpc::internal::EnvironmentAutoDetect::Get().NotifyOnDone(
        [&]() { notification.Notify(); });
    notification.WaitForNotification();
    
    auto* resource = grpc::internal::EnvironmentAutoDetect::Get().resource();
    
    // Configure tracing attributes if enabled
    if (config->cloud_trace.has_value()) {
      std::vector<internal::OpenCensusRegistry::Attribute> attributes;
      attributes.reserve(resource->labels.size() + config->labels.size());

      // Add resource labels as attributes
      for (const auto& resource_label : resource->labels) {
        attributes.push_back(internal::OpenCensusRegistry::Attribute{
            absl::StrCat(resource->resource_type, ".", resource_label.first),
            resource_label.second});
      }

      // Add constant labels as attributes
      for (const auto& constant_label : config->labels) {
        attributes.push_back(internal::OpenCensusRegistry::Attribute{
            constant_label.first, constant_label.second});
      }
      grpc::internal::OpenCensusRegistry::Get().RegisterConstantAttributes(
          std::move(attributes));
    }
    
    // Configure monitoring if enabled
    if (config->cloud_monitoring.has_value()) {
      grpc::internal::OpenCensusRegistry::Get().RegisterConstantLabels(
          config->labels);
      RegisterOpenCensusViewsForGcpObservability();
    }

    // Set up Stackdriver trace exporter if enabled
    if (config->cloud_trace.has_value()) {
      // Configure trace parameters
      opencensus::trace::TraceConfig::SetCurrentTraceParams(
          {kMaxAttributes, kMaxAnnotations, kMaxMessageEvents, kMaxLinks,
           opencensus::trace::ProbabilitySampler(
               config->cloud_trace->sampling_rate)});
      
      // Set up Stackdriver trace exporter
      opencensus::exporters::trace::StackdriverOptions trace_opts;
      trace_opts.project_id = config->project_id;
      ChannelArguments args;
      args.SetInt(GRPC_ARG_ENABLE_OBSERVABILITY, 0);
      trace_opts.trace_service_stub =
          ::google::devtools::cloudtrace::v2::TraceService::NewStub(
              CreateCustomChannel(kGoogleStackdriverTraceAddress,
                                  GoogleDefaultCredentials(), args));
      opencensus::exporters::trace::StackdriverExporter::Register(
          std::move(trace_opts));
    }
    
    // Set up Stackdriver stats exporter if enabled
    if (config->cloud_monitoring.has_value()) {
      opencensus::exporters::stats::StackdriverOptions stats_opts;
      stats_opts.project_id = config->project_id;
      stats_opts.monitored_resource.set_type(resource->resource_type);
      stats_opts.monitored_resource.mutable_labels()->insert(
          resource->labels.begin(), resource->labels.end());
      ChannelArguments args;
      args.SetInt(GRPC_ARG_ENABLE_OBSERVABILITY, 0);
      stats_opts.metric_service_stub =
          google::monitoring::v3::MetricService::NewStub(
              CreateCustomChannel(kGoogleStackdriverStatsAddress,
                                  GoogleDefaultCredentials(), args));
      opencensus::exporters::stats::StackdriverExporter::Register(
          std::move(stats_opts));
    }
    grpc_shutdown();
  }
  return absl::OkStatus();
}

// Shuts down GCP observability
void GcpObservabilityClose() {
  // Flush and close logging sink if it exists
  if (g_logging_sink != nullptr) {
    g_logging_sink->FlushAndClose();
  }

  // Wait for any pending operations to complete
  absl::SleepFor(absl::Seconds(25));
}

}  // namespace internal

namespace experimental {

// Public interface for initializing GCP observability
absl::Status GcpObservabilityInit() {
  return grpc::internal::GcpObservabilityInit();
}

// Public interface for closing GCP observability
void GcpObservabilityClose() { return grpc::internal::GcpObservabilityClose(); }

}  // namespace experimental

// Implementation of GcpObservability class
absl::StatusOr<GcpObservability> GcpObservability::Init() {
  absl::Status status = grpc::internal::GcpObservabilityInit();
  if (!status.ok()) {
    return status;
  }
  GcpObservability obj;
  obj.impl_ = std::make_unique<GcpObservabilityImpl>();
  return obj;
}

// Move constructor
GcpObservability::GcpObservability(GcpObservability&& other) noexcept
    : impl_(std::move(other.impl_)) {}

// Move assignment operator
GcpObservability& GcpObservability::operator=(
    GcpObservability&& other) noexcept {
  if (this != &other) {
    impl_ = std::move(other.impl_);
  }
  return *this;
}

// Destructor that ensures observability is properly closed
GcpObservability::GcpObservabilityImpl::~GcpObservabilityImpl() {
  grpc::internal::GcpObservabilityClose();
}

}  // namespace grpc
```