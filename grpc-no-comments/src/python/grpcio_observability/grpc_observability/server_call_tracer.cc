// Copyright 2023 gRPC authors.

#include "server_call_tracer.h"

#include <grpc/support/port_platform.h>
#include <stdint.h>
#include <string.h>

#include <algorithm>
#include <initializer_list>
#include <string>
#include <utility>
#include <vector>

#include "absl/strings/escaping.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_format.h"
#include "absl/strings/string_view.h"
#include "absl/time/clock.h"
#include "absl/time/time.h"
#include "constants.h"
#include "observability_util.h"
#include "python_observability_context.h"
#include "src/core/call/metadata_batch.h"
#include "src/core/lib/channel/channel_stack.h"
#include "src/core/lib/experiments/experiments.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/resource_quota/arena.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/lib/slice/slice_buffer.h"
#include "src/core/telemetry/call_tracer.h"

namespace grpc_observability {

namespace {

struct ServerO11yMetadata {
  grpc_core::Slice path;
  grpc_core::Slice tracing_slice;
  grpc_core::Slice census_proto;
};

void GetO11yMetadata(const grpc_metadata_batch* b, ServerO11yMetadata* som) {
  const auto* path = b->get_pointer(grpc_core::HttpPathMetadata());
  if (path != nullptr) {
    som->path = path->Ref();
  }
  if (PythonCensusTracingEnabled()) {
    const auto* grpc_trace_bin =
        b->get_pointer(grpc_core::GrpcTraceBinMetadata());
    if (grpc_trace_bin != nullptr) {
      som->tracing_slice = grpc_trace_bin->Ref();
    }
  }
  if (PythonCensusStatsEnabled()) {
    const auto* grpc_tags_bin =
        b->get_pointer(grpc_core::GrpcTagsBinMetadata());
    if (grpc_tags_bin != nullptr) {
      som->census_proto = grpc_tags_bin->Ref();
    }
  }
}

bool KeyInLabels(std::string key, const std::vector<Label>& labels) {
  const auto it = std::find_if(labels.begin(), labels.end(),
                               [&key](const Label& l) { return l.key == key; });

  if (it == labels.end()) {
    return false;
  }
  return true;
}

}

void PythonOpenCensusServerCallTracer::RecordSendInitialMetadata(
    grpc_metadata_batch* send_initial_metadata) {

  for (const auto& key : MetadataExchangeKeyNames) {
    if (KeyInLabels(key, labels_from_peer_)) {
      labels_injector_.AddExchangeLabelsToMetadata(send_initial_metadata);
    }
  }
}

void PythonOpenCensusServerCallTracer::RecordReceivedInitialMetadata(
    grpc_metadata_batch* recv_initial_metadata) {
  ServerO11yMetadata som;
  GetO11yMetadata(recv_initial_metadata, &som);
  path_ = std::move(som.path);
  method_ = GetMethod(path_);
  auto tracing_enabled = PythonCensusTracingEnabled();
  GenerateServerContext(
      tracing_enabled ? som.tracing_slice.as_string_view() : "",
      absl::StrCat("Recv.", method_), &context_);
  registered_method_ =
      recv_initial_metadata->get(grpc_core::GrpcRegisteredMethod())
          .value_or(nullptr) != nullptr;
  if (PythonCensusStatsEnabled()) {
    context_.Labels().emplace_back(kServerMethod, std::string(method_));
    RecordIntMetric(kRpcServerStartedRpcsMeasureName, 1, context_.Labels(),
                    identifier_, registered_method_,
                    false);
  }

  labels_from_peer_ = labels_injector_.GetExchangeLabels(recv_initial_metadata);
}

void PythonOpenCensusServerCallTracer::RecordSendTrailingMetadata(
    grpc_metadata_batch* send_trailing_metadata) {

  elapsed_time_ = absl::Now() - start_time_;
  if (PythonCensusStatsEnabled() && send_trailing_metadata != nullptr) {
    size_t len = ServerStatsSerialize(absl::ToInt64Nanoseconds(elapsed_time_),
                                      stats_buf_, kMaxServerStatsLen);
    if (len > 0) {
      send_trailing_metadata->Set(
          grpc_core::GrpcServerStatsBinMetadata(),
          grpc_core::Slice::FromCopiedBuffer(stats_buf_, len));
    }
  }
}

void PythonOpenCensusServerCallTracer::RecordSendMessage(
    const grpc_core::Message& send_message) {
  RecordAnnotation(absl::StrFormat("Send message: %ld bytes",
                                   send_message.payload()->Length()));
  ++sent_message_count_;
}

void PythonOpenCensusServerCallTracer::RecordSendCompressedMessage(
    const grpc_core::Message& send_compressed_message) {
  RecordAnnotation(
      absl::StrFormat("Send compressed message: %ld bytes",
                      send_compressed_message.payload()->Length()));
}

void PythonOpenCensusServerCallTracer::RecordReceivedMessage(
    const grpc_core::Message& recv_message) {
  RecordAnnotation(absl::StrFormat("Received message: %ld bytes",
                                   recv_message.payload()->Length()));
  ++recv_message_count_;
}

void PythonOpenCensusServerCallTracer::RecordReceivedDecompressedMessage(
    const grpc_core::Message& recv_decompressed_message) {
  RecordAnnotation(
      absl::StrFormat("Received decompressed message: %ld bytes",
                      recv_decompressed_message.payload()->Length()));
}

void PythonOpenCensusServerCallTracer::RecordCancel(
    grpc_error_handle ) {
  elapsed_time_ = absl::Now() - start_time_;
}

void PythonOpenCensusServerCallTracer::RecordEnd(
    const grpc_call_final_info* final_info) {
  if (PythonCensusStatsEnabled()) {
    uint64_t outgoing_bytes;
    uint64_t incoming_bytes;
    if (grpc_core::IsCallTracerInTransportEnabled()) {
      outgoing_bytes = outgoing_bytes_.load();
      incoming_bytes = incoming_bytes_.load();
    } else {
      outgoing_bytes = GetOutgoingDataSize(final_info);
      incoming_bytes = GetIncomingDataSize(final_info);
    }
    double elapsed_time_s = absl::ToDoubleSeconds(elapsed_time_);
    context_.Labels().emplace_back(kServerMethod, std::string(method_));
    context_.Labels().emplace_back(
        kServerStatus,
        std::string(StatusCodeToString(final_info->final_status)));
    for (const auto& label : labels_from_peer_) {
      context_.Labels().emplace_back(label);
    }
    RecordDoubleMetric(kRpcServerSentBytesPerRpcMeasureName,
                       static_cast<double>(outgoing_bytes), context_.Labels(),
                       identifier_, registered_method_,
                       true);
    RecordDoubleMetric(kRpcServerReceivedBytesPerRpcMeasureName,
                       static_cast<double>(incoming_bytes), context_.Labels(),
                       identifier_, registered_method_,
                       true);
    RecordDoubleMetric(kRpcServerServerLatencyMeasureName, elapsed_time_s,
                       context_.Labels(), identifier_, registered_method_,
                       true);
    RecordIntMetric(kRpcServerCompletedRpcMeasureName, 1, context_.Labels(),
                    identifier_, registered_method_,
                    true);
    RecordIntMetric(kRpcServerSentMessagesPerRpcMeasureName,
                    sent_message_count_, context_.Labels(), identifier_,
                    registered_method_, true);
    RecordIntMetric(kRpcServerReceivedMessagesPerRpcMeasureName,
                    recv_message_count_, context_.Labels(), identifier_,
                    registered_method_, true);
  }
  if (PythonCensusTracingEnabled()) {
    context_.EndSpan();
    if (IsSampled()) {
      RecordSpan(context_.GetSpan().ToCensusData());
    }
  }

  delete this;
}

void PythonOpenCensusServerCallTracer::RecordIncomingBytes(
    const TransportByteSize& transport_byte_size) {
  incoming_bytes_.fetch_add(transport_byte_size.data_bytes);
}

void PythonOpenCensusServerCallTracer::RecordOutgoingBytes(
    const TransportByteSize& transport_byte_size) {
  outgoing_bytes_.fetch_add(transport_byte_size.data_bytes);
}

void PythonOpenCensusServerCallTracer::RecordAnnotation(
    absl::string_view annotation) {
  if (!context_.GetSpanContext().IsSampled()) {
    return;
  }
  context_.AddSpanAnnotation(annotation);
}

void PythonOpenCensusServerCallTracer::RecordAnnotation(
    const Annotation& annotation) {
  if (!context_.GetSpanContext().IsSampled()) {
    return;
  }

  switch (annotation.type()) {

    default:
      if (IsSampled()) {
        context_.AddSpanAnnotation(annotation.ToString());
      }
      break;
  }
}

std::shared_ptr<grpc_core::TcpCallTracer>
PythonOpenCensusServerCallTracer::StartNewTcpTrace() {
  return nullptr;
}

std::string PythonOpenCensusServerCallTracer::TraceId() {
  return absl::BytesToHexString(
      absl::string_view(context_.GetSpanContext().TraceId()));
}

std::string PythonOpenCensusServerCallTracer::SpanId() {
  return absl::BytesToHexString(
      absl::string_view(context_.GetSpanContext().SpanId()));
}

bool PythonOpenCensusServerCallTracer::IsSampled() {
  return context_.GetSpanContext().IsSampled();
}

grpc_core::ServerCallTracer*
PythonOpenCensusServerCallTracerFactory::CreateNewServerCallTracer(
    grpc_core::Arena* arena, const grpc_core::ChannelArgs& channel_args) {

  (void)arena;
  (void)channel_args;
  return new PythonOpenCensusServerCallTracer(exchange_labels_, identifier_);
}

bool PythonOpenCensusServerCallTracerFactory::IsServerTraced(
    const grpc_core::ChannelArgs& args) {

  return true;
}

PythonOpenCensusServerCallTracerFactory::
    PythonOpenCensusServerCallTracerFactory(
        const std::vector<Label>& exchange_labels, const char* identifier)
    : exchange_labels_(exchange_labels), identifier_(identifier) {}

}
