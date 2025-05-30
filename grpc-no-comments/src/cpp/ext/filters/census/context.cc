
// Copyright 2018 gRPC authors.

#include "src/cpp/ext/filters/census/context.h"

#include <grpc/support/port_platform.h>

#include <new>

#include "opencensus/tags/context_util.h"
#include "opencensus/tags/tag_map.h"
#include "opencensus/trace/context_util.h"
#include "opencensus/trace/propagation/grpc_trace_bin.h"
#include "src/core/lib/transport/transport.h"
#include "src/cpp/ext/filters/census/grpc_plugin.h"
#include "src/cpp/ext/filters/census/rpc_encoding.h"

namespace grpc {

using ::opencensus::tags::TagMap;
using ::opencensus::trace::Span;
using ::opencensus::trace::SpanContext;

void GenerateServerContext(absl::string_view tracing, absl::string_view method,
                           CensusContext* context) {

  context->~CensusContext();
  if (method.empty()) {
    new (context) CensusContext(grpc::internal::OpenCensusRegistry::Get()
                                    .PopulateTagMapWithConstantLabels({}));
    return;
  }
  SpanContext parent_ctx =
      opencensus::trace::propagation::FromGrpcTraceBinHeader(tracing);
  if (parent_ctx.IsValid()) {
    new (context) CensusContext(method, parent_ctx,
                                grpc::internal::OpenCensusRegistry::Get()
                                    .PopulateTagMapWithConstantLabels({}));
  } else {
    new (context)
        CensusContext(method, grpc::internal::OpenCensusRegistry::Get()
                                  .PopulateTagMapWithConstantLabels({}));
  }
  grpc::internal::OpenCensusRegistry::Get()
      .PopulateCensusContextWithConstantAttributes(context);
}

void GenerateClientContext(absl::string_view method, CensusContext* ctxt,
                           CensusContext* parent_ctxt) {

  ctxt->~CensusContext();
  if (method.empty()) {
    new (ctxt) CensusContext(grpc::internal::OpenCensusRegistry::Get()
                                 .PopulateTagMapWithConstantLabels({}));
    return;
  }
  if (parent_ctxt != nullptr) {
    SpanContext span_ctxt = parent_ctxt->Context();
    Span span = parent_ctxt->Span();
    if (span_ctxt.IsValid()) {
      new (ctxt) CensusContext(method, &span,
                               grpc::internal::OpenCensusRegistry::Get()
                                   .PopulateTagMapWithConstantLabels({}));
      grpc::internal::OpenCensusRegistry::Get()
          .PopulateCensusContextWithConstantAttributes(ctxt);
      return;
    }
  }
  const Span& span = opencensus::trace::GetCurrentSpan();
  const TagMap& tags = grpc::internal::OpenCensusRegistry::Get()
                           .PopulateTagMapWithConstantLabels(
                               opencensus::tags::GetCurrentTagMap());
  if (span.context().IsValid()) {

    new (ctxt) CensusContext(method, &span, tags);
  } else {

    new (ctxt) CensusContext(method, tags);
  }
  grpc::internal::OpenCensusRegistry::Get()
      .PopulateCensusContextWithConstantAttributes(ctxt);
}

size_t TraceContextSerialize(const ::opencensus::trace::SpanContext& context,
                             char* tracing_buf, size_t tracing_buf_size) {
  if (tracing_buf_size <
      opencensus::trace::propagation::kGrpcTraceBinHeaderLen) {
    return 0;
  }
  opencensus::trace::propagation::ToGrpcTraceBinHeader(
      context, reinterpret_cast<uint8_t*>(tracing_buf));
  return opencensus::trace::propagation::kGrpcTraceBinHeaderLen;
}

size_t StatsContextSerialize(size_t , grpc_slice* ) {

  return 0;
}

size_t ServerStatsSerialize(uint64_t server_elapsed_time, char* buf,
                            size_t buf_size) {
  return internal::RpcServerStatsEncoding::Encode(server_elapsed_time, buf,
                                                  buf_size);
}

size_t ServerStatsDeserialize(const char* buf, size_t buf_size,
                              uint64_t* server_elapsed_time) {
  return internal::RpcServerStatsEncoding::Decode(
      absl::string_view(buf, buf_size), server_elapsed_time);
}

uint64_t GetIncomingDataSize(const grpc_call_final_info* final_info) {
  return final_info->stats.transport_stream_stats.incoming.data_bytes;
}

uint64_t GetOutgoingDataSize(const grpc_call_final_info* final_info) {
  return final_info->stats.transport_stream_stats.outgoing.data_bytes;
}

SpanContext SpanContextFromCensusContext(const census_context* ctxt) {
  return reinterpret_cast<const CensusContext*>(ctxt)->Context();
}

Span SpanFromCensusContext(const census_context* ctxt) {
  return reinterpret_cast<const CensusContext*>(ctxt)->Span();
}

absl::string_view StatusCodeToString(grpc_status_code code) {
  switch (code) {
    case GRPC_STATUS_OK:
      return "OK";
    case GRPC_STATUS_CANCELLED:
      return "CANCELLED";
    case GRPC_STATUS_UNKNOWN:
      return "UNKNOWN";
    case GRPC_STATUS_INVALID_ARGUMENT:
      return "INVALID_ARGUMENT";
    case GRPC_STATUS_DEADLINE_EXCEEDED:
      return "DEADLINE_EXCEEDED";
    case GRPC_STATUS_NOT_FOUND:
      return "NOT_FOUND";
    case GRPC_STATUS_ALREADY_EXISTS:
      return "ALREADY_EXISTS";
    case GRPC_STATUS_PERMISSION_DENIED:
      return "PERMISSION_DENIED";
    case GRPC_STATUS_UNAUTHENTICATED:
      return "UNAUTHENTICATED";
    case GRPC_STATUS_RESOURCE_EXHAUSTED:
      return "RESOURCE_EXHAUSTED";
    case GRPC_STATUS_FAILED_PRECONDITION:
      return "FAILED_PRECONDITION";
    case GRPC_STATUS_ABORTED:
      return "ABORTED";
    case GRPC_STATUS_OUT_OF_RANGE:
      return "OUT_OF_RANGE";
    case GRPC_STATUS_UNIMPLEMENTED:
      return "UNIMPLEMENTED";
    case GRPC_STATUS_INTERNAL:
      return "INTERNAL";
    case GRPC_STATUS_UNAVAILABLE:
      return "UNAVAILABLE";
    case GRPC_STATUS_DATA_LOSS:
      return "DATA_LOSS";
    default:

      return "UNKNOWN_STATUS";
  }
}

}
