Here's the commented version of the code:

```c++
// Copyright 2018 gRPC authors.

// Header includes for OpenCensus and gRPC functionality
#include "src/cpp/ext/filters/census/grpc_plugin.h"

#include <grpc/support/port_platform.h>
#include <grpcpp/opencensus.h>
#include <grpcpp/server_context.h>

#include <atomic>

#include "absl/base/attributes.h"
#include "absl/strings/string_view.h"
#include "opencensus/tags/tag_key.h"
#include "opencensus/trace/span.h"
#include "src/core/config/core_configuration.h"
#include "src/core/ext/filters/logging/logging_filter.h"
#include "src/core/lib/surface/channel_stack_type.h"
#include "src/core/telemetry/call_tracer.h"
#include "src/cpp/ext/filters/census/client_filter.h"
#include "src/cpp/ext/filters/census/measures.h"
#include "src/cpp/ext/filters/census/server_call_tracer.h"

namespace grpc {

// Registers the OpenCensus plugin with gRPC
// This sets up both server-side and client-side tracing and monitoring
void RegisterOpenCensusPlugin() {
  // Register server call tracer factory for OpenCensus
  grpc_core::ServerCallTracerFactory::RegisterGlobal(
      new grpc::internal::OpenCensusServerCallTracerFactory);
  
  // Configure client-side OpenCensus filter to be inserted into the channel stack
  grpc_core::CoreConfiguration::RegisterEphemeralBuilder(
      [](grpc_core::CoreConfiguration::Builder* builder) {
        builder->channel_init()
            ->RegisterFilter(GRPC_CLIENT_CHANNEL,
                             &grpc::internal::OpenCensusClientFilter::kFilter)
            .Before<grpc_core::ClientLoggingFilter>();
      });

  // Initialize client-side metrics
  RpcClientSentBytesPerRpc();
  RpcClientReceivedBytesPerRpc();
  RpcClientRoundtripLatency();
  RpcClientServerLatency();
  RpcClientStartedRpcs();
  RpcClientSentMessagesPerRpc();
  RpcClientReceivedMessagesPerRpc();
  RpcClientRetriesPerCall();
  RpcClientTransparentRetriesPerCall();
  RpcClientRetryDelayPerCall();
  RpcClientTransportLatency();
  internal::RpcClientApiLatency();

  // Initialize server-side metrics
  RpcServerSentBytesPerRpc();
  RpcServerReceivedBytesPerRpc();
  RpcServerServerLatency();
  RpcServerStartedRpcs();
  RpcServerSentMessagesPerRpc();
  RpcServerReceivedMessagesPerRpc();
}

// Retrieves the OpenCensus Span from a gRPC ServerContext
// Returns a blank span if context is null or invalid
::opencensus::trace::Span GetSpanFromServerContext(
    grpc::ServerContext* context) {
  if (context == nullptr) return opencensus::trace::Span::BlankSpan();

  return reinterpret_cast<const grpc::experimental::CensusContext*>(
             context->census_context())
      ->Span();
}

namespace experimental {

// Returns a TagKey for client method name in OpenCensus metrics
::opencensus::tags::TagKey ClientMethodTagKey() {
  static const auto method_tag_key =
      ::opencensus::tags::TagKey::Register("grpc_client_method");
  return method_tag_key;
}

// Returns a TagKey for client status code in OpenCensus metrics
::opencensus::tags::TagKey ClientStatusTagKey() {
  static const auto status_tag_key =
      ::opencensus::tags::TagKey::Register("grpc_client_status");
  return status_tag_key;
}

// Returns a TagKey for server method name in OpenCensus metrics
::opencensus::tags::TagKey ServerMethodTagKey() {
  static const auto method_tag_key =
      ::opencensus::tags::TagKey::Register("grpc_server_method");
  return method_tag_key;
}

// Returns a TagKey for server status code in OpenCensus metrics
::opencensus::tags::TagKey ServerStatusTagKey() {
  static const auto status_tag_key =
      ::opencensus::tags::TagKey::Register("grpc_server_status");
  return status_tag_key;
}

// Constants defining OpenCensus measure names for client-side metrics
ABSL_CONST_INIT const absl::string_view
    kRpcClientSentMessagesPerRpcMeasureName =
        "grpc.io/client/sent_messages_per_rpc";

ABSL_CONST_INIT const absl::string_view kRpcClientSentBytesPerRpcMeasureName =
    "grpc.io/client/sent_bytes_per_rpc";

ABSL_CONST_INIT const absl::string_view
    kRpcClientReceivedMessagesPerRpcMeasureName =
        "grpc.io/client/received_messages_per_rpc";

ABSL_CONST_INIT const absl::string_view
    kRpcClientReceivedBytesPerRpcMeasureName =
        "grpc.io/client/received_bytes_per_rpc";

ABSL_CONST_INIT const absl::string_view kRpcClientRoundtripLatencyMeasureName =
    "grpc.io/client/roundtrip_latency";

ABSL_CONST_INIT const absl::string_view kRpcClientServerLatencyMeasureName =
    "grpc.io/client/server_latency";

ABSL_CONST_INIT const absl::string_view kRpcClientStartedRpcsMeasureName =
    "grpc.io/client/started_rpcs";

ABSL_CONST_INIT const absl::string_view kRpcClientRetriesPerCallMeasureName =
    "grpc.io/client/retries_per_call";

ABSL_CONST_INIT const absl::string_view
    kRpcClientTransparentRetriesPerCallMeasureName =
        "grpc.io/client/transparent_retries_per_call";

ABSL_CONST_INIT const absl::string_view kRpcClientRetryDelayPerCallMeasureName =
    "grpc.io/client/retry_delay_per_call";

ABSL_CONST_INIT const absl::string_view kRpcClientTransportLatencyMeasureName =
    "grpc.io/client/transport_latency";

// Constants defining OpenCensus measure names for server-side metrics
ABSL_CONST_INIT const absl::string_view
    kRpcServerSentMessagesPerRpcMeasureName =
        "grpc.io/server/sent_messages_per_rpc";

ABSL_CONST_INIT const absl::string_view kRpcServerSentBytesPerRpcMeasureName =
    "grpc.io/server/sent_bytes_per_rpc";

ABSL_CONST_INIT const absl::string_view
    kRpcServerReceivedMessagesPerRpcMeasureName =
        "grpc.io/server/received_messages_per_rpc";

ABSL_CONST_INIT const absl::string_view
    kRpcServerReceivedBytesPerRpcMeasureName =
        "grpc.io/server/received_bytes_per_rpc";

ABSL_CONST_INIT const absl::string_view kRpcServerServerLatencyMeasureName =
    "grpc.io/server/server_latency";

ABSL_CONST_INIT const absl::string_view kRpcServerStartedRpcsMeasureName =
    "grpc.io/server/started_rpcs";

}

namespace internal {

// Constant for client API latency measure name
ABSL_CONST_INIT const absl::string_view kRpcClientApiLatencyMeasureName =
    "grpc.io/client/api_latency";

namespace {
// Atomic flags controlling OpenCensus features
std::atomic<bool> g_open_census_stats_enabled(true);
std::atomic<bool> g_open_census_tracing_enabled(true);
}

// Singleton accessor for OpenCensusRegistry
OpenCensusRegistry& OpenCensusRegistry::Get() {
  static OpenCensusRegistry* registry = new OpenCensusRegistry;
  return *registry;
}

// Adds constant labels to a TagMap for OpenCensus metrics
::opencensus::tags::TagMap OpenCensusRegistry::PopulateTagMapWithConstantLabels(
    const ::opencensus::tags::TagMap& tag_map) {
  std::vector<std::pair<::opencensus::tags::TagKey, std::string>> tags =
      tag_map.tags();
  for (const auto& label : ConstantLabels()) {
    tags.emplace_back(label.tag_key, label.value);
  }
  return ::opencensus::tags::TagMap(std::move(tags));
}

// Adds constant attributes to a CensusContext span
void OpenCensusRegistry::PopulateCensusContextWithConstantAttributes(
    grpc::experimental::CensusContext* context) {
  for (const auto& attribute : ConstantAttributes()) {
    context->AddSpanAttribute(attribute.key, attribute.value);
  }
}

// Enables/disables OpenCensus stats collection
void EnableOpenCensusStats(bool enable) {
  g_open_census_stats_enabled = enable;
}

// Enables/disables OpenCensus tracing
void EnableOpenCensusTracing(bool enable) {
  g_open_census_tracing_enabled = enable;
}

// Returns whether OpenCensus stats collection is enabled
bool OpenCensusStatsEnabled() {
  return g_open_census_stats_enabled.load(std::memory_order_relaxed);
}

// Returns whether OpenCensus tracing is enabled
bool OpenCensusTracingEnabled() {
  return g_open_census_tracing_enabled.load(std::memory_order_relaxed);
}

}

}
```