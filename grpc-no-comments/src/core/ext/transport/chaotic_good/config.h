// Copyright 2024 gRPC authors.

#ifndef GRPC_SRC_CORE_EXT_TRANSPORT_CHAOTIC_GOOD_CONFIG_H
#define GRPC_SRC_CORE_EXT_TRANSPORT_CHAOTIC_GOOD_CONFIG_H

#include <vector>

#include "absl/container/flat_hash_set.h"
#include "src/core/ext/transport/chaotic_good/chaotic_good_frame.pb.h"
#include "src/core/ext/transport/chaotic_good/message_chunker.h"
#include "src/core/ext/transport/chaotic_good/pending_connection.h"
#include "src/core/ext/transport/chaotic_good/tcp_frame_transport.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/event_engine/extensions/tcp_trace.h"

namespace grpc_core {
namespace chaotic_good {

#define GRPC_ARG_CHAOTIC_GOOD_ALIGNMENT "grpc.chaotic_good.alignment"
#define GRPC_ARG_CHAOTIC_GOOD_MAX_RECV_CHUNK_SIZE \
  "grpc.chaotic_good.max_recv_chunk_size"
#define GRPC_ARG_CHAOTIC_GOOD_MAX_SEND_CHUNK_SIZE \
  "grpc.chaotic_good.max_send_chunk_size"
#define GRPC_ARG_CHAOTIC_GOOD_INLINED_PAYLOAD_SIZE_THRESHOLD \
  "grpc.chaotic_good.inlined_payload_size_threshold"

class Config {
 public:
  explicit Config(
      const ChannelArgs& channel_args,
      std::initializer_list<chaotic_good_frame::Settings::Features>
          supported_features = {chaotic_good_frame::Settings::CHUNKING})
      : supported_features_(supported_features) {
    decode_alignment_ =
        std::max(1, channel_args.GetInt(GRPC_ARG_CHAOTIC_GOOD_ALIGNMENT)
                        .value_or(decode_alignment_));
    max_recv_chunk_size_ = std::max(
        0, channel_args.GetInt(GRPC_ARG_CHAOTIC_GOOD_MAX_RECV_CHUNK_SIZE)
               .value_or(max_recv_chunk_size_));
    max_send_chunk_size_ = std::max(
        0, channel_args.GetInt(GRPC_ARG_CHAOTIC_GOOD_MAX_SEND_CHUNK_SIZE)
               .value_or(max_send_chunk_size_));
    if (max_recv_chunk_size_ == 0 || max_send_chunk_size_ == 0) {
      max_recv_chunk_size_ = 0;
      max_send_chunk_size_ = 0;
    }
    inline_payload_size_threshold_ = std::max(
        0, channel_args
               .GetInt(GRPC_ARG_CHAOTIC_GOOD_INLINED_PAYLOAD_SIZE_THRESHOLD)
               .value_or(inline_payload_size_threshold_));
    tracing_enabled_ =
        channel_args.GetBool(GRPC_ARG_TCP_TRACING_ENABLED).value_or(false);
  }

  Config(const Config&) = delete;
  Config& operator=(const Config&) = delete;
  Config(Config&&) = default;
  Config& operator=(Config&&) = default;

  ~Config() = default;

  void ServerAddPendingDataEndpoint(PendingConnection endpoint) {
    pending_data_endpoints_.emplace_back(std::move(endpoint));
  }

  std::vector<PendingConnection> TakePendingDataEndpoints() {
    return std::move(pending_data_endpoints_);
  }

  void PrepareServerOutgoingSettings(chaotic_good_frame::Settings& settings) {
    for (const auto& pending_data_endpoint : pending_data_endpoints_) {
      settings.add_connection_id(pending_data_endpoint.id());
    }
    PrepareOutgoingSettings(settings);
  }

  void PrepareClientOutgoingSettings(chaotic_good_frame::Settings& settings) {
    CHECK_EQ(pending_data_endpoints_.size(), 0u);
    PrepareOutgoingSettings(settings);
  }

  absl::Status ReceiveServerIncomingSettings(
      const chaotic_good_frame::Settings& settings,
      ClientConnectionFactory& connector) {
    absl::flat_hash_set<chaotic_good_frame::Settings::Features>
        supported_features;
    for (const auto feature : settings.supported_features()) {
      if (chaotic_good_frame::Settings::Features_IsValid(feature)) {
        const auto valid_feature =
            static_cast<chaotic_good_frame::Settings::Features>(feature);
        if (supported_features_.contains(valid_feature)) {
          supported_features.insert(valid_feature);
        }
      }
    }
    supported_features_.swap(supported_features);
    for (const auto& connection_id : settings.connection_id()) {
      pending_data_endpoints_.emplace_back(connector.Connect(connection_id));
    }
    return ReceiveIncomingSettings(settings);
  }

  absl::Status ReceiveClientIncomingSettings(
      const chaotic_good_frame::Settings& settings) {
    absl::flat_hash_set<chaotic_good_frame::Settings::Features>
        supported_features;
    for (const auto feature : settings.supported_features()) {
      if (!chaotic_good_frame::Settings::Features_IsValid(feature)) {
        return absl::InternalError(absl::StrCat(
            "Unsupported feature present in chaotic-good handshake: ",
            feature));
      }
      const auto valid_feature =
          static_cast<chaotic_good_frame::Settings::Features>(feature);
      if (!supported_features_.contains(valid_feature)) {
        return absl::InternalError(absl::StrCat(
            "Unsupported feature present in chaotic-good handshake: ",
            chaotic_good_frame::Settings::Features_Name(valid_feature)));
      }
      supported_features.insert(valid_feature);
    }
    supported_features_.swap(supported_features);
    if (settings.connection_id_size() != 0) {
      return absl::InternalError("Client cannot specify connection ids");
    }
    return ReceiveIncomingSettings(settings);
  }

  TcpFrameTransport::Options MakeTcpFrameTransportOptions() const {
    TcpFrameTransport::Options options;
    options.encode_alignment = encode_alignment_;
    options.decode_alignment = decode_alignment_;
    options.inlined_payload_size_threshold = inline_payload_size_threshold_;
    return options;
  }

  MessageChunker MakeMessageChunker() const {
    return MessageChunker(max_send_chunk_size_, encode_alignment_);
  }

  bool tracing_enabled() const { return tracing_enabled_; }

  void TestOnlySetChunkSizes(uint32_t size) {
    max_send_chunk_size_ = size;
    max_recv_chunk_size_ = size;
  }

  uint32_t encode_alignment() const { return encode_alignment_; }
  uint32_t decode_alignment() const { return decode_alignment_; }
  uint32_t max_send_chunk_size() const { return max_send_chunk_size_; }

  uint32_t max_recv_chunk_size() const { return max_recv_chunk_size_; }
  uint32_t inline_payload_size_threshold() const {
    return inline_payload_size_threshold_;
  }

  std::string ToString() const {
    return absl::StrCat(GRPC_DUMP_ARGS(tracing_enabled_, encode_alignment_,
                                       decode_alignment_, max_send_chunk_size_,
                                       max_recv_chunk_size_,
                                       inline_payload_size_threshold_));
  }

  template <typename Sink>
  friend void AbslStringify(Sink& sink, const Config& config) {
    sink.Append(config.ToString());
  }

  bool supports_chunking() const {
    return supported_features_.contains(chaotic_good_frame::Settings::CHUNKING);
  }

 private:

  void PrepareOutgoingSettings(chaotic_good_frame::Settings& settings) const {
    settings.set_alignment(decode_alignment_);
    settings.set_max_chunk_size(max_recv_chunk_size_);
  }

  absl::Status ReceiveIncomingSettings(
      const chaotic_good_frame::Settings& settings) {
    if (settings.alignment() != 0) encode_alignment_ = settings.alignment();
    max_send_chunk_size_ =
        std::min(max_send_chunk_size_, settings.max_chunk_size());
    if (!supports_chunking() || settings.max_chunk_size() == 0) {
      max_recv_chunk_size_ = 0;
      max_send_chunk_size_ = 0;
    }
    return absl::OkStatus();
  }

  bool tracing_enabled_ = false;
  uint32_t encode_alignment_ = 64;
  uint32_t decode_alignment_ = 64;
  uint32_t max_send_chunk_size_ = 1024 * 1024;
  uint32_t max_recv_chunk_size_ = 1024 * 1024;
  uint32_t inline_payload_size_threshold_ = 8 * 1024;
  std::vector<PendingConnection> pending_data_endpoints_;
  absl::flat_hash_set<chaotic_good_frame::Settings::Features>
      supported_features_;
};

}
}

#endif
