
// Copyright 2020 gRPC authors.

#ifndef GRPC_SRC_CORE_EXT_FILTERS_HTTP_MESSAGE_COMPRESS_COMPRESSION_FILTER_H
#define GRPC_SRC_CORE_EXT_FILTERS_HTTP_MESSAGE_COMPRESS_COMPRESSION_FILTER_H

#include <grpc/impl/compression_types.h>
#include <grpc/support/port_platform.h>
#include <stddef.h>
#include <stdint.h>

#include <cstddef>
#include <optional>

#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"
#include "src/core/call/metadata_batch.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/channel/channel_fwd.h"
#include "src/core/lib/channel/promise_based_filter.h"
#include "src/core/lib/compression/compression_internal.h"
#include "src/core/lib/promise/arena_promise.h"
#include "src/core/lib/transport/transport.h"

namespace grpc_core {

class ChannelCompression {
 public:
  explicit ChannelCompression(const ChannelArgs& args);

  struct DecompressArgs {
    grpc_compression_algorithm algorithm;
    std::optional<uint32_t> max_recv_message_length;
  };

  grpc_compression_algorithm default_compression_algorithm() const {
    return default_compression_algorithm_;
  }

  CompressionAlgorithmSet enabled_compression_algorithms() const {
    return enabled_compression_algorithms_;
  }

  grpc_compression_algorithm HandleOutgoingMetadata(
      grpc_metadata_batch& outgoing_metadata);
  DecompressArgs HandleIncomingMetadata(
      const grpc_metadata_batch& incoming_metadata);

  MessageHandle CompressMessage(MessageHandle message,
                                grpc_compression_algorithm algorithm,
                                CallTracerInterface* call_tracer) const;

  absl::StatusOr<MessageHandle> DecompressMessage(
      bool is_client, MessageHandle message, DecompressArgs args,
      CallTracerInterface* call_tracer) const;

  Json::Object ToJsonObject() const {
    Json::Object object;
    if (max_recv_size_.has_value()) {
      object["maxRecvSize"] = Json::FromNumber(*max_recv_size_);
    }
    const char* algorithm =
        CompressionAlgorithmAsString(default_compression_algorithm_);
    if (algorithm != nullptr) {
      object["defaultCompressionAlgorithm"] = Json::FromString(algorithm);
    }
    object["enabledCompressionAlgorithms"] = Json::FromString(
        std::string(enabled_compression_algorithms_.ToString()));
    object["enableCompression"] = Json::FromBool(enable_compression_);
    object["enableDecompression"] = Json::FromBool(enable_decompression_);
    return object;
  }

 private:

  std::optional<uint32_t> max_recv_size_;
  size_t message_size_service_config_parser_index_;

  grpc_compression_algorithm default_compression_algorithm_;

  CompressionAlgorithmSet enabled_compression_algorithms_;

  bool enable_compression_;

  bool enable_decompression_;
};

class ClientCompressionFilter final
    : public ImplementChannelFilter<ClientCompressionFilter>,
      public channelz::DataSource {
 public:
  static const grpc_channel_filter kFilter;

  static absl::string_view TypeName() { return "compression"; }

  static absl::StatusOr<std::unique_ptr<ClientCompressionFilter>> Create(
      const ChannelArgs& args, ChannelFilter::Args filter_args);

  explicit ClientCompressionFilter(const ChannelArgs& args)
      : channelz::DataSource(args.GetObjectRef<channelz::BaseNode>()),
        compression_engine_(args) {}
  ~ClientCompressionFilter() override { ResetDataSource(); }

  void AddData(channelz::DataSink sink) override {
    sink.AddAdditionalInfo("clientCompressionFilter",
                           compression_engine_.ToJsonObject());
  }

  class Call {
   public:
    void OnClientInitialMetadata(ClientMetadata& md,
                                 ClientCompressionFilter* filter);
    MessageHandle OnClientToServerMessage(MessageHandle message,
                                          ClientCompressionFilter* filter);

    void OnServerInitialMetadata(ServerMetadata& md,
                                 ClientCompressionFilter* filter);
    absl::StatusOr<MessageHandle> OnServerToClientMessage(
        MessageHandle message, ClientCompressionFilter* filter);

    static inline const NoInterceptor OnClientToServerHalfClose;
    static inline const NoInterceptor OnServerTrailingMetadata;
    static inline const NoInterceptor OnFinalize;

   private:
    grpc_compression_algorithm compression_algorithm_;
    ChannelCompression::DecompressArgs decompress_args_;

    CallTracerInterface* call_tracer_ = nullptr;
  };

 private:
  ChannelCompression compression_engine_;
};

class ServerCompressionFilter final
    : public ImplementChannelFilter<ServerCompressionFilter>,
      public channelz::DataSource {
 public:
  static const grpc_channel_filter kFilter;

  static absl::string_view TypeName() { return "compression"; }

  static absl::StatusOr<std::unique_ptr<ServerCompressionFilter>> Create(
      const ChannelArgs& args, ChannelFilter::Args filter_args);

  explicit ServerCompressionFilter(const ChannelArgs& args)
      : channelz::DataSource(args.GetObjectRef<channelz::BaseNode>()),
        compression_engine_(args) {}
  ~ServerCompressionFilter() override { ResetDataSource(); }

  void AddData(channelz::DataSink sink) override {
    sink.AddAdditionalInfo("serverCompressionFilter",
                           compression_engine_.ToJsonObject());
  }

  class Call {
   public:
    void OnClientInitialMetadata(ClientMetadata& md,
                                 ServerCompressionFilter* filter);
    absl::StatusOr<MessageHandle> OnClientToServerMessage(
        MessageHandle message, ServerCompressionFilter* filter);

    void OnServerInitialMetadata(ServerMetadata& md,
                                 ServerCompressionFilter* filter);
    MessageHandle OnServerToClientMessage(MessageHandle message,
                                          ServerCompressionFilter* filter);

    static inline const NoInterceptor OnClientToServerHalfClose;
    static inline const NoInterceptor OnServerTrailingMetadata;
    static inline const NoInterceptor OnFinalize;

   private:
    ChannelCompression::DecompressArgs decompress_args_;
    grpc_compression_algorithm compression_algorithm_;
  };

 private:
  ChannelCompression compression_engine_;
};

}

#endif
