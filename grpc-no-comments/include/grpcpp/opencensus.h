
// Copyright 2019 gRPC authors.

#ifndef GRPCPP_OPENCENSUS_H
#define GRPCPP_OPENCENSUS_H

#include <grpc/support/port_platform.h>

#include "opencensus/stats/view_descriptor.h"
#include "opencensus/tags/tag_map.h"
#include "opencensus/trace/span.h"
#include "opencensus/trace/span_context.h"

#define GRPC_OPENCENSUS_DEPRECATION_REASON                   \
  "OpenCensus has been sunsetted in favor of OpenTelemetry " \
  "https://opentelemetry.io/blog/2023/sunsetting-opencensus/"

namespace grpc {
class ServerContext;

GRPC_DEPRECATED(GRPC_OPENCENSUS_DEPRECATION_REASON)
void RegisterOpenCensusPlugin();

GRPC_DEPRECATED(GRPC_OPENCENSUS_DEPRECATION_REASON)
void RegisterOpenCensusViewsForExport();

GRPC_DEPRECATED(GRPC_OPENCENSUS_DEPRECATION_REASON)
::opencensus::trace::Span GetSpanFromServerContext(ServerContext* context);

namespace experimental {

::opencensus::tags::TagKey ClientMethodTagKey();
::opencensus::tags::TagKey ClientStatusTagKey();
::opencensus::tags::TagKey ServerMethodTagKey();
::opencensus::tags::TagKey ServerStatusTagKey();

extern const absl::string_view kRpcClientSentMessagesPerRpcMeasureName;
extern const absl::string_view kRpcClientSentBytesPerRpcMeasureName;
extern const absl::string_view kRpcClientReceivedMessagesPerRpcMeasureName;
extern const absl::string_view kRpcClientReceivedBytesPerRpcMeasureName;
extern const absl::string_view kRpcClientRoundtripLatencyMeasureName;
extern const absl::string_view kRpcClientServerLatencyMeasureName;
extern const absl::string_view kRpcClientStartedRpcsMeasureName;
extern const absl::string_view kRpcClientRetriesPerCallMeasureName;
extern const absl::string_view kRpcClientTransparentRetriesPerCallMeasureName;
extern const absl::string_view kRpcClientRetryDelayPerCallMeasureName;
extern const absl::string_view kRpcClientTransportLatencyMeasureName;

extern const absl::string_view kRpcServerSentMessagesPerRpcMeasureName;
extern const absl::string_view kRpcServerSentBytesPerRpcMeasureName;
extern const absl::string_view kRpcServerReceivedMessagesPerRpcMeasureName;
extern const absl::string_view kRpcServerReceivedBytesPerRpcMeasureName;
extern const absl::string_view kRpcServerServerLatencyMeasureName;
extern const absl::string_view kRpcServerStartedRpcsMeasureName;

const ::opencensus::stats::ViewDescriptor& ClientStartedRpcs();
const ::opencensus::stats::ViewDescriptor& ClientCompletedRpcs();
const ::opencensus::stats::ViewDescriptor& ClientRoundtripLatency();
const ::opencensus::stats::ViewDescriptor&
ClientSentCompressedMessageBytesPerRpc();
const ::opencensus::stats::ViewDescriptor&
ClientReceivedCompressedMessageBytesPerRpc();
const ::opencensus::stats::ViewDescriptor& ClientTransportLatency();

const ::opencensus::stats::ViewDescriptor& ServerStartedRpcs();
const ::opencensus::stats::ViewDescriptor& ServerCompletedRpcs();
const ::opencensus::stats::ViewDescriptor&
ServerSentCompressedMessageBytesPerRpc();
const ::opencensus::stats::ViewDescriptor&
ServerReceivedCompressedMessageBytesPerRpc();
const ::opencensus::stats::ViewDescriptor& ServerServerLatency();

const ::opencensus::stats::ViewDescriptor& ClientSentMessagesPerRpcCumulative();
const ::opencensus::stats::ViewDescriptor& ClientSentBytesPerRpcCumulative();
const ::opencensus::stats::ViewDescriptor&
ClientReceivedMessagesPerRpcCumulative();
const ::opencensus::stats::ViewDescriptor&
ClientReceivedBytesPerRpcCumulative();
const ::opencensus::stats::ViewDescriptor& ClientRoundtripLatencyCumulative();
const ::opencensus::stats::ViewDescriptor& ClientServerLatencyCumulative();
const ::opencensus::stats::ViewDescriptor& ClientStartedRpcsCumulative();
const ::opencensus::stats::ViewDescriptor& ClientCompletedRpcsCumulative();
const ::opencensus::stats::ViewDescriptor& ClientRetriesPerCallCumulative();
const ::opencensus::stats::ViewDescriptor& ClientRetriesCumulative();
const ::opencensus::stats::ViewDescriptor&
ClientTransparentRetriesPerCallCumulative();
const ::opencensus::stats::ViewDescriptor& ClientTransparentRetriesCumulative();
const ::opencensus::stats::ViewDescriptor& ClientRetryDelayPerCallCumulative();

const ::opencensus::stats::ViewDescriptor& ServerSentBytesPerRpcCumulative();
const ::opencensus::stats::ViewDescriptor&
ServerReceivedBytesPerRpcCumulative();
const ::opencensus::stats::ViewDescriptor& ServerServerLatencyCumulative();
const ::opencensus::stats::ViewDescriptor& ServerStartedRpcsCumulative();
const ::opencensus::stats::ViewDescriptor& ServerCompletedRpcsCumulative();
const ::opencensus::stats::ViewDescriptor& ServerSentMessagesPerRpcCumulative();
const ::opencensus::stats::ViewDescriptor&
ServerReceivedMessagesPerRpcCumulative();

const ::opencensus::stats::ViewDescriptor& ClientSentMessagesPerRpcMinute();
const ::opencensus::stats::ViewDescriptor& ClientSentBytesPerRpcMinute();
const ::opencensus::stats::ViewDescriptor& ClientReceivedMessagesPerRpcMinute();
const ::opencensus::stats::ViewDescriptor& ClientReceivedBytesPerRpcMinute();
const ::opencensus::stats::ViewDescriptor& ClientRoundtripLatencyMinute();
const ::opencensus::stats::ViewDescriptor& ClientServerLatencyMinute();
const ::opencensus::stats::ViewDescriptor& ClientStartedRpcsMinute();
const ::opencensus::stats::ViewDescriptor& ClientCompletedRpcsMinute();
const ::opencensus::stats::ViewDescriptor& ClientRetriesPerCallMinute();
const ::opencensus::stats::ViewDescriptor& ClientRetriesMinute();
const ::opencensus::stats::ViewDescriptor&
ClientTransparentRetriesPerCallMinute();
const ::opencensus::stats::ViewDescriptor& ClientTransparentRetriesMinute();
const ::opencensus::stats::ViewDescriptor& ClientRetryDelayPerCallMinute();

const ::opencensus::stats::ViewDescriptor& ServerSentMessagesPerRpcMinute();
const ::opencensus::stats::ViewDescriptor& ServerSentBytesPerRpcMinute();
const ::opencensus::stats::ViewDescriptor& ServerReceivedMessagesPerRpcMinute();
const ::opencensus::stats::ViewDescriptor& ServerReceivedBytesPerRpcMinute();
const ::opencensus::stats::ViewDescriptor& ServerServerLatencyMinute();
const ::opencensus::stats::ViewDescriptor& ServerStartedRpcsMinute();
const ::opencensus::stats::ViewDescriptor& ServerCompletedRpcsMinute();

const ::opencensus::stats::ViewDescriptor& ClientSentMessagesPerRpcHour();
const ::opencensus::stats::ViewDescriptor& ClientSentBytesPerRpcHour();
const ::opencensus::stats::ViewDescriptor& ClientReceivedMessagesPerRpcHour();
const ::opencensus::stats::ViewDescriptor& ClientReceivedBytesPerRpcHour();
const ::opencensus::stats::ViewDescriptor& ClientRoundtripLatencyHour();
const ::opencensus::stats::ViewDescriptor& ClientServerLatencyHour();
const ::opencensus::stats::ViewDescriptor& ClientStartedRpcsHour();
const ::opencensus::stats::ViewDescriptor& ClientCompletedRpcsHour();
const ::opencensus::stats::ViewDescriptor& ClientRetriesPerCallHour();
const ::opencensus::stats::ViewDescriptor& ClientRetriesHour();
const ::opencensus::stats::ViewDescriptor&
ClientTransparentRetriesPerCallHour();
const ::opencensus::stats::ViewDescriptor& ClientTransparentRetriesHour();
const ::opencensus::stats::ViewDescriptor& ClientRetryDelayPerCallHour();

const ::opencensus::stats::ViewDescriptor& ServerSentMessagesPerRpcHour();
const ::opencensus::stats::ViewDescriptor& ServerSentBytesPerRpcHour();
const ::opencensus::stats::ViewDescriptor& ServerReceivedMessagesPerRpcHour();
const ::opencensus::stats::ViewDescriptor& ServerReceivedBytesPerRpcHour();
const ::opencensus::stats::ViewDescriptor& ServerServerLatencyHour();
const ::opencensus::stats::ViewDescriptor& ServerStartedRpcsHour();
const ::opencensus::stats::ViewDescriptor& ServerCompletedRpcsHour();

class GRPC_DEPRECATED(GRPC_OPENCENSUS_DEPRECATION_REASON) CensusContext {
 public:
  CensusContext() : span_(::opencensus::trace::Span::BlankSpan()), tags_({}) {}

  explicit CensusContext(absl::string_view name,
                         const ::opencensus::tags::TagMap& tags)
      : span_(::opencensus::trace::Span::StartSpan(name)), tags_(tags) {}

  explicit CensusContext(const ::opencensus::tags::TagMap& tags)
      : span_(::opencensus::trace::Span::BlankSpan()), tags_(tags) {}

  CensusContext(absl::string_view name, const ::opencensus::trace::Span* parent,
                const ::opencensus::tags::TagMap& tags)
      : span_(::opencensus::trace::Span::StartSpan(name, parent)),
        tags_(tags) {}

  CensusContext(absl::string_view name,
                const ::opencensus::trace::SpanContext& parent_ctxt)
      : span_(::opencensus::trace::Span::StartSpanWithRemoteParent(
            name, parent_ctxt)),
        tags_({}) {}

  CensusContext(absl::string_view name,
                const ::opencensus::trace::SpanContext& parent_ctxt,
                const ::opencensus::tags::TagMap& tags)
      : span_(::opencensus::trace::Span::StartSpanWithRemoteParent(
            name, parent_ctxt)),
        tags_(tags) {}

  void AddSpanAttribute(absl::string_view key,
                        opencensus::trace::AttributeValueRef attribute) {
    span_.AddAttribute(key, attribute);
  }

  void AddSpanAnnotation(absl::string_view description,
                         opencensus::trace::AttributesRef attributes) {
    span_.AddAnnotation(description, attributes);
  }

  const ::opencensus::trace::Span& Span() const { return span_; }
  const ::opencensus::tags::TagMap& tags() const { return tags_; }

  ::opencensus::trace::SpanContext Context() const { return Span().context(); }
  void EndSpan() { Span().End(); }

 private:
  ::opencensus::trace::Span span_;
  ::opencensus::tags::TagMap tags_;
};

}

}

#endif
