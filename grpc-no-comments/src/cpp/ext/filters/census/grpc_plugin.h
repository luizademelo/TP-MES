
// Copyright 2018 gRPC authors.

#ifndef GRPC_SRC_CPP_EXT_FILTERS_CENSUS_GRPC_PLUGIN_H
#define GRPC_SRC_CPP_EXT_FILTERS_CENSUS_GRPC_PLUGIN_H

#include <grpc/support/port_platform.h>
#include <grpcpp/opencensus.h>

#include <algorithm>
#include <map>
#include <string>
#include <utility>
#include <vector>

#include "absl/strings/string_view.h"
#include "opencensus/stats/stats.h"
#include "opencensus/tags/tag_key.h"
#include "opencensus/tags/tag_map.h"

namespace grpc {

using experimental::ClientMethodTagKey;
using experimental::ClientStatusTagKey;
using experimental::ServerMethodTagKey;
using experimental::ServerStatusTagKey;

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

using experimental::kRpcServerReceivedBytesPerRpcMeasureName;
using experimental::kRpcServerReceivedMessagesPerRpcMeasureName;
using experimental::kRpcServerSentBytesPerRpcMeasureName;
using experimental::kRpcServerSentMessagesPerRpcMeasureName;
using experimental::kRpcServerServerLatencyMeasureName;
using experimental::kRpcServerStartedRpcsMeasureName;

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

using experimental::ServerCompletedRpcsCumulative;
using experimental::ServerReceivedBytesPerRpcCumulative;
using experimental::ServerReceivedMessagesPerRpcCumulative;
using experimental::ServerSentBytesPerRpcCumulative;
using experimental::ServerSentMessagesPerRpcCumulative;
using experimental::ServerServerLatencyCumulative;
using experimental::ServerStartedRpcsCumulative;

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

using experimental::ServerCompletedRpcsMinute;
using experimental::ServerReceivedBytesPerRpcMinute;
using experimental::ServerReceivedMessagesPerRpcMinute;
using experimental::ServerSentBytesPerRpcMinute;
using experimental::ServerSentMessagesPerRpcMinute;
using experimental::ServerServerLatencyMinute;
using experimental::ServerStartedRpcsMinute;

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

using experimental::ServerCompletedRpcsHour;
using experimental::ServerReceivedBytesPerRpcHour;
using experimental::ServerReceivedMessagesPerRpcHour;
using experimental::ServerSentBytesPerRpcHour;
using experimental::ServerSentMessagesPerRpcHour;
using experimental::ServerServerLatencyHour;
using experimental::ServerStartedRpcsHour;

namespace internal {

extern const absl::string_view kRpcClientApiLatencyMeasureName;

const ::opencensus::stats::ViewDescriptor& ClientApiLatency();

void EnableOpenCensusStats(bool enable);
void EnableOpenCensusTracing(bool enable);

bool OpenCensusStatsEnabled();
bool OpenCensusTracingEnabled();

class OpenCensusRegistry {
 public:
  struct Label {
    std::string key;
    opencensus::tags::TagKey tag_key;
    std::string value;
  };

  struct Attribute {
    std::string key;
    std::string value;
  };

  static OpenCensusRegistry& Get();

  void RegisterConstantLabels(
      const std::map<std::string, std::string>& labels) {
    constant_labels_.reserve(labels.size());
    for (const auto& label : labels) {
      auto tag_key = opencensus::tags::TagKey::Register(label.first);
      constant_labels_.emplace_back(Label{label.first, tag_key, label.second});
    }
  }

  void RegisterConstantAttributes(std::vector<Attribute> attributes) {
    constant_attributes_ = std::move(attributes);
  }

  ::opencensus::tags::TagMap PopulateTagMapWithConstantLabels(
      const ::opencensus::tags::TagMap& tag_map);

  void PopulateCensusContextWithConstantAttributes(
      grpc::experimental::CensusContext* context);

  const std::vector<Label>& ConstantLabels() { return constant_labels_; }

  const std::vector<Attribute>& ConstantAttributes() {
    return constant_attributes_;
  }

 private:
  OpenCensusRegistry() = default;

  std::vector<Label> constant_labels_;
  std::vector<Attribute> constant_attributes_;
};

}

}

#endif
