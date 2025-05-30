
// Copyright 2018 gRPC authors.

#ifndef GRPC_SRC_CORE_TELEMETRY_CONTEXT_LIST_ENTRY_H
#define GRPC_SRC_CORE_TELEMETRY_CONTEXT_LIST_ENTRY_H

#include <grpc/support/port_platform.h>
#include <stddef.h>
#include <stdint.h>

#include <memory>
#include <utility>
#include <vector>

#include "src/core/telemetry/tcp_tracer.h"

namespace grpc_core {

class ContextListEntry {
 public:
  ContextListEntry(void* context, int64_t outbuf_offset,
                   int64_t num_traced_bytes, size_t byte_offset,
                   size_t stream_index,
                   std::shared_ptr<TcpCallTracer> tcp_tracer)
      : trace_context_(context),
        outbuf_offset_(outbuf_offset),
        num_traced_bytes_in_chunk_(num_traced_bytes),
        byte_offset_in_stream_(byte_offset),
        stream_index_(stream_index),
        tcp_tracer_(std::move(tcp_tracer)) {}

  ContextListEntry() = delete;

  void* TraceContext() { return trace_context_; }
  int64_t OutbufOffset() { return outbuf_offset_; }
  int64_t NumTracedBytesInChunk() { return num_traced_bytes_in_chunk_; }
  size_t ByteOffsetInStream() { return byte_offset_in_stream_; }
  size_t StreamIndex() { return stream_index_; }
  std::shared_ptr<TcpCallTracer> ReleaseTcpTracer() {
    return std::move(tcp_tracer_);
  }

 private:
  void* trace_context_;

  int64_t outbuf_offset_;

  int64_t num_traced_bytes_in_chunk_;

  size_t byte_offset_in_stream_;

  size_t stream_index_;
  std::shared_ptr<TcpCallTracer> tcp_tracer_;
};

typedef std::vector<ContextListEntry> ContextList;
}

#endif
