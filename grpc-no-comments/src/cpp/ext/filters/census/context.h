
// Copyright 2018 gRPC authors.

#ifndef GRPC_SRC_CPP_EXT_FILTERS_CENSUS_CONTEXT_H
#define GRPC_SRC_CPP_EXT_FILTERS_CENSUS_CONTEXT_H

#include <grpc/grpc.h>
#include <grpc/slice.h>
#include <grpc/status.h>
#include <grpc/support/port_platform.h>
#include <grpcpp/opencensus.h>
#include <stddef.h>
#include <stdint.h>

#include "absl/strings/string_view.h"
#include "absl/strings/strip.h"
#include "opencensus/trace/span.h"
#include "opencensus/trace/span_context.h"
#include "src/core/lib/channel/channel_stack.h"
#include "src/core/lib/slice/slice.h"

namespace grpc {

using experimental::CensusContext;

size_t TraceContextSerialize(const ::opencensus::trace::SpanContext& context,
                             char* tracing_buf, size_t tracing_buf_size);

size_t StatsContextSerialize(size_t max_tags_len, grpc_slice* tags);

size_t ServerStatsSerialize(uint64_t server_elapsed_time, char* buf,
                            size_t buf_size);

size_t ServerStatsDeserialize(const char* buf, size_t buf_size,
                              uint64_t* server_elapsed_time);

void GenerateServerContext(absl::string_view tracing, absl::string_view method,
                           CensusContext* context);

void GenerateClientContext(absl::string_view method, CensusContext* ctxt,
                           CensusContext* parent_ctx);

uint64_t GetIncomingDataSize(const grpc_call_final_info* final_info);

uint64_t GetOutgoingDataSize(const grpc_call_final_info* final_info);

::opencensus::trace::SpanContext SpanContextFromCensusContext(
    const census_context* ctxt);
::opencensus::trace::Span SpanFromCensusContext(const census_context* ctxt);

absl::string_view StatusCodeToString(grpc_status_code code);

inline absl::string_view GetMethod(const grpc_core::Slice& path) {
  if (path.empty()) {
    return "";
  }

  return absl::StripPrefix(path.as_string_view(), "/");
}

}

#endif
