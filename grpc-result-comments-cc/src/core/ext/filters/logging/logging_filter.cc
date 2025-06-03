Here's the commented version of the code:

```c++
// Copyright 2022 gRPC authors.

// Include necessary headers for the logging filter implementation
#include "src/core/ext/filters/logging/logging_filter.h"

#include <grpc/impl/channel_arg_names.h>
#include <grpc/slice.h>
#include <grpc/status.h>
#include <grpc/support/port_platform.h>
#include <inttypes.h>

#include <algorithm>
#include <cstddef>
#include <functional>
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>

// Include ABSL (Abseil) libraries for logging, random number generation, etc.
#include "absl/log/log.h"
#include "absl/numeric/int128.h"
#include "absl/random/random.h"
#include "absl/random/uniform_int_distribution.h"
#include "absl/status/statusor.h"
#include "absl/strings/numbers.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_split.h"
#include "absl/strings/string_view.h"
#include "absl/strings/strip.h"

// Include core gRPC headers
#include "src/core/call/metadata_batch.h"
#include "src/core/client_channel/client_channel_filter.h"
#include "src/core/config/core_configuration.h"
#include "src/core/ext/filters/logging/logging_sink.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/channel/channel_fwd.h"
#include "src/core/lib/channel/channel_stack.h"
#include "src/core/lib/promise/arena_promise.h"
#include "src/core/lib/promise/cancel_callback.h"
#include "src/core/lib/promise/context.h"
#include "src/core/lib/promise/map.h"
#include "src/core/lib/promise/pipe.h"
#include "src/core/lib/resource_quota/arena.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/lib/slice/slice_buffer.h"
#include "src/core/lib/surface/channel_stack_type.h"
#include "src/core/lib/transport/transport.h"
#include "src/core/resolver/resolver_registry.h"
#include "src/core/telemetry/call_tracer.h"
#include "src/core/util/host_port.h"
#include "src/core/util/latent_see.h"
#include "src/core/util/time.h"
#include "src/core/util/uri.h"

namespace grpc_core {

namespace {

// Global logging sink pointer
LoggingSink* g_logging_sink = nullptr;

// Generates a unique call ID using thread-local random number generation
absl::uint128 GetCallId() {
  thread_local absl::InsecureBitGen gen;
  return absl::uniform_int_distribution<absl::uint128>()(gen);
}

// Helper class for encoding metadata into logging payload
class MetadataEncoder {
 public:
  MetadataEncoder(LoggingSink::Entry::Payload* payload,
                  std::string* status_details_bin, uint64_t log_len)
      : payload_(payload),
        status_details_bin_(status_details_bin),
        log_len_(log_len) {}

  // Encodes a key-value pair from metadata
  void Encode(const Slice& key_slice, const Slice& value_slice) {
    auto key = key_slice.as_string_view();
    auto value = value_slice.as_string_view();
    // Special handling for status details binary
    if (status_details_bin_ != nullptr && key == "grpc-status-details-bin") {
      *status_details_bin_ = std::string(value);
      return;
    }
    // Skip grpc- prefixed metadata
    if (absl::ConsumePrefix(&key, "grpc-")) {
      return;
    }
    // Check if metadata exceeds maximum logging size
    uint64_t mdentry_len = key.length() + value.length();
    if (mdentry_len > log_len_) {
      VLOG(2) << "Skipped metadata key because of max metadata logging bytes "
              << mdentry_len << " (current) vs " << log_len_
              << " (max less already accounted metadata)";
      truncated_ = true;
      return;
    }

    // Add metadata to payload
    payload_->metadata.emplace(std::string(key), std::string(value));
    log_len_ -= mdentry_len;
  }

  // Template for encoding metadata types we don't specifically handle
  template <typename Which>
  void Encode(Which, const typename Which::ValueType&) {}

  // Special handling for gRPC status code
  void Encode(GrpcStatusMetadata, grpc_status_code status) {
    payload_->status_code = status;
  }

  // Special handling for gRPC status message
  void Encode(GrpcMessageMetadata, const Slice& status_message) {
    payload_->status_message = std::string(status_message.as_string_view());
  }

  // Returns whether any metadata was truncated due to size limits
  bool truncated() const { return truncated_; }

 private:
  LoggingSink::Entry::Payload* const payload_;  // Payload to populate
  std::string* const status_details_bin_;      // Status details binary storage
  uint64_t log_len_;                           // Remaining log capacity
  bool truncated_ = false;                     // Whether truncation occurred
};

// Helper function to parse IP and port from a string
void SetIpPort(absl::string_view s, LoggingSink::Entry::Address* peer) {
  absl::string_view host;
  absl::string_view port;
  if (SplitHostPort(absl::string_view(s.data(), s.length()), &host, &port) ==
      1) {
    if (!host.empty()) {
      peer->address = std::string(host);
    }
    if (!port.empty()) {
      if (!absl::SimpleAtoi(absl::string_view(port.data(), port.size()),
                            &peer->ip_port)) {
        peer->ip_port = 0;
      }
    }
  }
}

// Converts a peer string to a structured Address object
LoggingSink::Entry::Address PeerStringToAddress(const Slice& peer_string) {
  LoggingSink::Entry::Address address;
  absl::StatusOr<URI> uri = URI::Parse(peer_string.as_string_view());
  if (!uri.ok()) {
    VLOG(2) << "peer_string is in invalid format and cannot be logged";
    return address;
  }

  // Handle different URI schemes
  if (uri->scheme() == "ipv4") {
    address.type = LoggingSink::Entry::Address::Type::kIpv4;
    SetIpPort(uri->path(), &address);
  } else if (uri->scheme() == "ipv6") {
    address.type = LoggingSink::Entry::Address::Type::kIpv6;
    SetIpPort(uri->path(), &address);
  } else if (uri->scheme() == "unix") {
    address.type = LoggingSink::Entry::Address::Type::kUnix;
    address.address = uri->path();
  }
  return address;
}

// Encodes a message into the logging payload with size limits
void EncodeMessageToPayload(const SliceBuffer* message, uint32_t log_len,
                            LoggingSink::Entry* entry) {
  auto* sb = message->c_slice_buffer();
  entry->payload.message_length = sb->length;

  // Process each slice in the message
  for (size_t i = 0; i < sb->count; i++) {
    absl::StrAppend(
        &entry->payload.message,
        absl::string_view(
            reinterpret_cast<const char*>(GRPC_SLICE_START_PTR(sb->slices[i])),
            std::min(static_cast<size_t>(GRPC_SLICE_LENGTH(sb->slices[i])),
                     static_cast<size_t>(log_len))));
    if (log_len < GRPC_SLICE_LENGTH(sb->slices[i])) {
      entry->payload_truncated = true;
      break;
    }
    log_len -= GRPC_SLICE_LENGTH(sb->slices[i]);
  }
}

}  // namespace

namespace logging_filter_detail {

// CallData implementation for logging filter
CallData::CallData(bool is_client,
                   const ClientMetadata& client_initial_metadata,
                   const std::string& authority)
    : call_id_(GetCallId()) {
  // Extract service and method names from path
  absl::string_view path;
  if (auto* value = client_initial_metadata.get_pointer(HttpPathMetadata())) {
    path = value->as_string_view();
  }
  std::vector<std::string> parts = absl::StrSplit(path, '/', absl::SkipEmpty());
  if (parts.size() == 2) {
    service_name_ = std::move(parts[0]);
    method_name_ = std::move(parts[1]);
  }
  // Find matching logging configuration
  config_ = g_logging_sink->FindMatch(is_client, service_name_, method_name_);
  if (config_.ShouldLog()) {
    // Store authority for logging
    if (auto* value =
            client_initial_metadata.get_pointer(HttpAuthorityMetadata())) {
      authority_ = std::string(value->as_string_view());
    } else {
      authority_ = authority;
    }
  }
}

// Log client header metadata
void CallData::LogClientHeader(bool is_client,
                               CallTracerAnnotationInterface* tracer,
                               const ClientMetadata& metadata) {
  LoggingSink::Entry entry;
  if (!is_client) {
    // For server-side, capture peer information
    if (auto* value = metadata.get_pointer(PeerString())) {
      peer_ = PeerStringToAddress(*value);
    }
  }
  SetCommonEntryFields(&entry, is_client, tracer,
                       LoggingSink::Entry::EventType::kClientHeader);
  MetadataEncoder encoder(&entry.payload, nullptr,
                          config_.max_metadata_bytes());
  metadata.Encode(&encoder);
  entry.payload_truncated = encoder.truncated();
  g_logging_sink->LogEntry(std::move(entry));
}

// Log client half-close event
void CallData::LogClientHalfClose(bool is_client,
                                  CallTracerAnnotationInterface* tracer) {
  LoggingSink::Entry entry;
  SetCommonEntryFields(&entry, is_client, tracer,
                       LoggingSink::Entry::EventType::kClientHalfClose);
  g_logging_sink->LogEntry(std::move(entry));
}

// Log server header metadata
void CallData::LogServerHeader(bool is_client,
                               CallTracerAnnotationInterface* tracer,
                               const ServerMetadata* metadata) {
  LoggingSink::Entry entry;
  if (metadata != nullptr) {
    entry.is_trailer_only = metadata->get(GrpcTrailersOnly()).value_or(false);
    if (is_client) {
      // For client-side, capture peer information
      if (auto* value = metadata->get_pointer(PeerString())) {
        peer_ = PeerStringToAddress(*value);
      }
    }
  }
  SetCommonEntryFields(&entry, is_client, tracer,
                       LoggingSink::Entry::EventType::kServerHeader);
  if (metadata != nullptr) {
    MetadataEncoder encoder(&entry.payload, nullptr,
                            config_.max_metadata_bytes());
    metadata->Encode(&encoder);
    entry.payload_truncated = encoder.truncated();
  }
  g_logging_sink->LogEntry(std::move(entry));
}

// Log server trailer metadata
void CallData::LogServerTrailer(bool is_client,
                                CallTracerAnnotationInterface* tracer,
                                const ServerMetadata* metadata) {
  LoggingSink::Entry entry;
  SetCommonEntryFields(&entry, is_client, tracer,
                       LoggingSink::Entry::EventType::kServerTrailer);
  if (metadata != nullptr) {
    entry.is_trailer_only = metadata->get(GrpcTrailersOnly()).value_or(false);
    MetadataEncoder encoder(&entry.payload, &entry.payload.status_details,
                            config_.max_metadata_bytes());
    metadata->Encode(&encoder);
    entry.payload_truncated = encoder.truncated();
  }
  g_logging_sink->LogEntry(std::move(entry));
}

// Log client message
void CallData::LogClientMessage(bool is_client,
                                CallTracerAnnotationInterface* tracer,
                                const SliceBuffer* message) {
  LoggingSink::Entry entry;
  SetCommonEntryFields(&entry, is_client, tracer,
                       LoggingSink::Entry::EventType::kClientMessage);
  EncodeMessageToPayload(message, config_.max_message_bytes(), &entry);
  g_logging_sink->LogEntry(std::move(entry));
}

// Log server message
void CallData::LogServerMessage(bool is_client,
                                CallTracerAnnotationInterface* tracer,
                                const SliceBuffer* message) {
  LoggingSink::Entry entry;
  SetCommonEntryFields(&entry, is_client, tracer,
                       LoggingSink::Entry::EventType::kServerMessage);
  EncodeMessageToPayload(message, config_.max_message_bytes(), &entry);
  g_logging_sink->LogEntry(std::move(entry));
}

// Log call cancellation
void CallData::LogCancel(bool is_client,
                         CallTracerAnnotationInterface* tracer) {
  LoggingSink::Entry entry;
  SetCommonEntryFields(&entry, is_client, tracer,
                       LoggingSink::Entry::EventType::kCancel);
  g_logging_sink->LogEntry(std::move(entry));
}

// Sets common fields for all log entries
void CallData::SetCommonEntryFields(LoggingSink::Entry* entry, bool is_client,
                                    CallTracerAnnotationInterface* tracer,
                                    LoggingSink::Entry::EventType event_type) {
  entry->call_id = call_id_;
  entry->sequence_id = sequence_id_++;
  entry->type = event_type;
  entry->logger = is_client ? LoggingSink::Entry::Logger::kClient
                            : LoggingSink::Entry::Logger::kServer;
  entry->authority = authority_;
  entry->peer = peer_;
  entry->service_name = service_name_;
  entry->method_name = method_name_;
  entry->timestamp = Timestamp::Now();
  // Add tracing information if available
  if (tracer != nullptr) {
    entry->trace_id = tracer->TraceId();
    entry->span_id = tracer->SpanId();
    entry->is_sampled = tracer->IsSampled();
  }
}

}  // namespace logging_filter_detail

// ClientLoggingFilter implementation

// Creates a new ClientLoggingFilter instance
absl::StatusOr<std::unique_ptr<ClientLoggingFilter>>
ClientLoggingFilter::Create(const ChannelArgs& args,
                            ChannelFilter::Args ) {
  // Try to get default authority from channel args
  std::optional<absl::string_view> default_authority =
      args.GetString(GRPC_ARG_DEFAULT_AUTHORITY);
  if (default_authority.has_value()) {
    return std::make_unique<ClientLoggingFilter>(
        std::string(default_authority.value()));
  }
  // Fall back to server URI if default authority not available
  std::optional<std::string> server_uri =
      args.GetOwnedString(GRPC_ARG_SERVER_URI);
  if (server_uri.has_value()) {
    return std::make_unique<ClientLoggingFilter>(
        CoreConfiguration::Get().resolver_registry().GetDefaultAuthority(
            *server_uri));
  }
  // Use empty string as last resort
  return std::make_unique<ClientLoggingFilter>("");
}

// Handles client initial metadata
void ClientLoggingFilter::Call::OnClientInitialMetadata(
    ClientMetadata& md, ClientLoggingFilter* filter) {
  GRPC_LATENT_SEE_INNER_SCOPE(
      "ClientLoggingFilter::Call::OnClientInitialMetadata");
  call_data_.emplace(true, md, filter->default_authority_);
  if (!call_data_->ShouldLog()) {
    call_data_.reset();
    return;
  }
  call_data_->LogClientHeader(
      true, MaybeGetContext<CallTracerAnnotationInterface>(), md);
}

// Handles server initial metadata
void ClientLoggingFilter::Call::OnServerInitialMetadata(ServerMetadata& md) {
  GRPC_LATENT_SEE_INNER_SCOPE(
      "ClientLoggingFilter::Call::OnServerInitialMetadata");
  if (!call_data_.has_value()) return;
  call_data_->LogServerHeader(
      true, MaybeGetContext<CallTracerAnnotationInterface>(),
      &md);
}

// Handles server trailing metadata
void ClientLoggingFilter::Call::OnServerTrailingMetadata(ServerMetadata& md) {
  GRPC_LATENT_SEE_INNER_SCOPE(
      "ClientLoggingFilter::Call::OnServerTrailingMetadata");
  if (!call_data_.has_value()) return;
  if (md.get(GrpcCallWasCancelled()).value_or(false) &&
      md.get(GrpcStatusMetadata()) == GRPC_STATUS_CANCELLED) {
    call_data_->LogCancel(
        true, MaybeGetContext<CallTracerAnnotationInterface>());
    return;
  }
  call_data_->LogServerTrailer(
      true, MaybeGetContext<CallTracerAnnotationInterface>(),
      &md);
}

// Handles client-to-server message
void ClientLoggingFilter::Call::OnClientToServerMessage(
    const Message& message) {
  GRPC_LATENT_SEE_INNER_SCOPE(
      "ClientLoggingFilter::Call::OnClientToServerMessage");
  if (!call_data_.has_value()) return;
  call_data_->LogClientMessage(
      true, MaybeGetContext<CallTracerAnnotationInterface>(),
      message.payload());
}

// Handles client half-close
void ClientLoggingFilter::Call::OnClientToServerHalfClose() {
  GRPC_LATENT_SEE_INNER_SCOPE(
      "ClientLoggingFilter::Call::OnClientToServerHalfClose");
  if (!call_data_.has_value()) return;
  call_data_->LogClientHalfClose(
      true, MaybeGetContext<CallTracerAnnotationInterface>());
}

// Handles server-to-client message
void ClientLoggingFilter::Call::OnServerToClientMessage(
    const Message& message) {
  GRPC_LATENT_SEE_INNER_SCOPE(
      "ClientLoggingFilter::Call::OnServerToClientMessage");
  if (!call_data_.has_value()) return;
  call_data_->LogServerMessage(
      true, MaybeGetContext<CallTracerAnnotationInterface>(),