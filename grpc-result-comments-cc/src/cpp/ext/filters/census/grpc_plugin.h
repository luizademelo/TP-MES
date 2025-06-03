Here's the commented version of the code:

```c++
// Copyright 2018 gRPC authors.

#ifndef GRPC_SRC_CPP_EXT_FILTERS_CENSUS_GRPC_PLUGIN_H
#define GRPC_SRC_CPP_EXT_FILTERS_CENSUS_GRPC_PLUGIN_H

// Include necessary headers for platform support, OpenCensus integration,
// and standard library components
#include <grpc/support/port_platform.h>
#include <grpcpp/opencensus.h>

#include <algorithm>
#include <map>
#include <string>
#include <utility>
#include <vector>

// Include OpenCensus and Abseil headers for metrics and tags functionality
#include "absl/strings/string_view.h"
#include "opencensus/stats/stats.h"
#include "opencensus/tags/tag_key.h"
#include "opencensus/tags/tag_map.h"

namespace grpc {

// Import tag keys for client and server method/status from experimental namespace
using experimental::ClientMethodTagKey;
using experimental::ClientStatusTagKey;
using experimental::ServerMethodTagKey;
using experimental::ServerStatusTagKey;

// Import measure names for client-side RPC metrics
using experimental::kRpcClientReceivedBytesPerRpcMeasureName;
using experimental::kRpcClientReceivedMessagesPerRpcMeasureName;
using experimental::kRpcClientRetriesPerCallMeasureName;
using experimental::kRpcClientRetryDelayPerCallMeasureName;
using experimental::kRpcClientRoundtripLatencyMeasureName;
using experimental::kRpcClientSentBytesPerRpcMeasureName;
using experimental::kRpcClientSentMessagesPerRpcMeasureName;
using experimental::kRpcClientServerLatencyMeasureName;
using experimental::kRpcClientStartedRpcsMeasureName;
using experimental::kRpcClientTransparentRetriesPerCallMeasureName;

// Import measure names for server-side RPC metrics
using experimental::kRpcServerReceivedBytesPerRpcMeasureName;
using experimental::kRpcServerReceivedMessagesPerRpcMeasureName;
using experimental::kRpcServerSentBytesPerRpcMeasureName;
using experimental::kRpcServerSentMessagesPerRpcMeasureName;
using experimental::kRpcServerServerLatencyMeasureName;
using experimental::kRpcServerStartedRpcsMeasureName;

// Import cumulative view descriptors for client-side metrics
using experimental::ClientCompletedRpcsCumulative;
using experimental::ClientReceivedBytesPerRpcCumulative;
using experimental::ClientReceivedMessagesPerRpcCumulative;
using experimental::ClientRetriesCumulative;
using experimental::ClientRetriesPerCallCumulative;
using experimental::ClientRetryDelayPerCallCumulative;
using experimental::ClientRoundtripLatencyCumulative;
using experimental::ClientSentBytesPerRpcCumulative;
using experimental::ClientSentMessagesPerRpcCumulative;
using experimental::ClientServerLatencyCumulative;
using experimental::ClientStartedRpcsCumulative;
using experimental::ClientTransparentRetriesCumulative;
using experimental::ClientTransparentRetriesPerCallCumulative;

// Import cumulative view descriptors for server-side metrics
using experimental::ServerCompletedRpcsCumulative;
using experimental::ServerReceivedBytesPerRpcCumulative;
using experimental::ServerReceivedMessagesPerRpcCumulative;
using experimental::ServerSentBytesPerRpcCumulative;
using experimental::ServerSentMessagesPerRpcCumulative;
using experimental::ServerServerLatencyCumulative;
using experimental::ServerStartedRpcsCumulative;

// Import minute-interval view descriptors for client-side metrics
using experimental::ClientCompletedRpcsMinute;
using experimental::ClientReceivedBytesPerRpcMinute;
using experimental::ClientReceivedMessagesPerRpcMinute;
using experimental::ClientRetriesMinute;
using experimental::ClientRetriesPerCallMinute;
using experimental::ClientRetryDelayPerCallMinute;
using experimental::ClientRoundtripLatencyMinute;
using experimental::ClientSentBytesPerRpcMinute;
using experimental::ClientSentMessagesPerRpcMinute;
using experimental::ClientServerLatencyMinute;
using experimental::ClientStartedRpcsMinute;
using experimental::ClientTransparentRetriesMinute;
using experimental::ClientTransparentRetriesPerCallMinute;

// Import minute-interval view descriptors for server-side metrics
using experimental::ServerCompletedRpcsMinute;
using experimental::ServerReceivedBytesPerRpcMinute;
using experimental::ServerReceivedMessagesPerRpcMinute;
using experimental::ServerSentBytesPerRpcMinute;
using experimental::ServerSentMessagesPerRpcMinute;
using experimental::ServerServerLatencyMinute;
using experimental::ServerStartedRpcsMinute;

// Import hour-interval view descriptors for client-side metrics
using experimental::ClientCompletedRpcsHour;
using experimental::ClientReceivedBytesPerRpcHour;
using experimental::ClientReceivedMessagesPerRpcHour;
using experimental::ClientRetriesHour;
using experimental::ClientRetriesPerCallHour;
using experimental::ClientRetryDelayPerCallHour;
using experimental::ClientRoundtripLatencyHour;
using experimental::ClientSentBytesPerRpcHour;
using experimental::ClientSentMessagesPerRpcHour;
using experimental::ClientServerLatencyHour;
using experimental::ClientStartedRpcsHour;
using experimental::ClientTransparentRetriesHour;
using experimental::ClientTransparentRetriesPerCallHour;

// Import hour-interval view descriptors for server-side metrics
using experimental::ServerCompletedRpcsHour;
using experimental::ServerReceivedBytesPerRpcHour;
using experimental::ServerReceivedMessagesPerRpcHour;
using experimental::ServerSentBytesPerRpcHour;
using experimental::ServerSentMessagesPerRpcHour;
using experimental::ServerServerLatencyHour;
using experimental::ServerStartedRpcsHour;

namespace internal {

// External declaration for client API latency measure name
extern const absl::string_view kRpcClientApiLatencyMeasureName;

// Returns the view descriptor for client API latency
const ::opencensus::stats::ViewDescriptor& ClientApiLatency();

// Functions to enable/disable OpenCensus stats and tracing
void EnableOpenCensusStats(bool enable);
void EnableOpenCensusTracing(bool enable);

// Functions to check if OpenCensus stats and tracing are enabled
bool OpenCensusStatsEnabled();
bool OpenCensusTracingEnabled();

// Registry class for managing OpenCensus-related configurations
class OpenCensusRegistry {
 public:
  // Nested struct for label information (key, tag key, and value)
  struct Label {
    std::string key;
    opencensus::tags::TagKey tag_key;
    std::string value;
  };

  // Nested struct for attribute information (key-value pair)
  struct Attribute {
    std::string key;
    std::string value;
  };

  // Singleton accessor method
  static OpenCensusRegistry& Get();

  // Registers constant labels that will be applied to all metrics
  void RegisterConstantLabels(
      const std::map<std::string, std::string>& labels) {
    constant_labels_.reserve(labels.size());
    for (const auto& label : labels) {
      auto tag_key = opencensus::tags::TagKey::Register(label.first);
      constant_labels_.emplace_back(Label{label.first, tag_key, label.second});
    }
  }

  // Registers constant attributes that will be applied to all traces
  void RegisterConstantAttributes(std::vector<Attribute> attributes) {
    constant_attributes_ = std::move(attributes);
  }

  // Combines the provided tag map with the registered constant labels
  ::opencensus::tags::TagMap PopulateTagMapWithConstantLabels(
      const ::opencensus::tags::TagMap& tag_map);

  // Adds registered constant attributes to the CensusContext
  void PopulateCensusContextWithConstantAttributes(
      grpc::experimental::CensusContext* context);

  // Accessors for constant labels and attributes
  const std::vector<Label>& ConstantLabels() { return constant_labels_; }
  const std::vector<Attribute>& ConstantAttributes() {
    return constant_attributes_;
  }

 private:
  // Private constructor for singleton pattern
  OpenCensusRegistry() = default;

  // Storage for constant labels and attributes
  std::vector<Label> constant_labels_;
  std::vector<Attribute> constant_attributes_;
};

}  // namespace internal

}  // namespace grpc

#endif  // GRPC_SRC_CPP_EXT_FILTERS_CENSUS_GRPC_PLUGIN_H
```