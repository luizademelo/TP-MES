
// Copyright 2022 gRPC authors.

#ifndef GRPC_SRC_CORE_EXT_FILTERS_LOGGING_LOGGING_FILTER_H
#define GRPC_SRC_CORE_EXT_FILTERS_LOGGING_LOGGING_FILTER_H

#include <grpc/support/port_platform.h>

#include <string>
#include <utility>

#include "absl/status/statusor.h"
#include "src/core/ext/filters/logging/logging_sink.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/channel/channel_fwd.h"
#include "src/core/lib/channel/promise_based_filter.h"
#include "src/core/lib/promise/arena_promise.h"
#include "src/core/lib/transport/transport.h"

namespace grpc_core {

namespace logging_filter_detail {

class CallData {
 public:
  CallData(bool is_client, const ClientMetadata& client_initial_metadata,
           const std::string& authority);

  bool ShouldLog() { return config_.ShouldLog(); }

  void LogClientHeader(bool is_client, CallTracerAnnotationInterface* tracer,
                       const ClientMetadata& metadata);
  void LogClientHalfClose(bool is_client,
                          CallTracerAnnotationInterface* tracer);
  void LogServerHeader(bool is_client, CallTracerAnnotationInterface* tracer,
                       const ServerMetadata* metadata);
  void LogServerTrailer(bool is_client, CallTracerAnnotationInterface* tracer,
                        const ServerMetadata* metadata);
  void LogClientMessage(bool is_client, CallTracerAnnotationInterface* tracer,
                        const SliceBuffer* message);
  void LogServerMessage(bool is_client, CallTracerAnnotationInterface* tracer,
                        const SliceBuffer* message);
  void LogCancel(bool is_client, CallTracerAnnotationInterface* tracer);

 private:
  void SetCommonEntryFields(LoggingSink::Entry* entry, bool is_client,
                            CallTracerAnnotationInterface* tracer,
                            LoggingSink::Entry::EventType event_type);
  absl::uint128 call_id_;
  uint32_t sequence_id_ = 0;
  std::string service_name_;
  std::string method_name_;
  std::string authority_;
  LoggingSink::Entry::Address peer_;
  LoggingSink::Config config_;
};

}

class ClientLoggingFilter final
    : public ImplementChannelFilter<ClientLoggingFilter> {
 public:
  static const grpc_channel_filter kFilter;

  static absl::string_view TypeName() { return "logging"; }

  static absl::StatusOr<std::unique_ptr<ClientLoggingFilter>> Create(
      const ChannelArgs& args, ChannelFilter::Args );

  explicit ClientLoggingFilter(std::string default_authority)
      : default_authority_(std::move(default_authority)) {}

  class Call {
   public:
    void OnClientInitialMetadata(ClientMetadata& md,
                                 ClientLoggingFilter* filter);
    void OnServerInitialMetadata(ServerMetadata& md);
    void OnServerTrailingMetadata(ServerMetadata& md);
    void OnClientToServerMessage(const Message& message);
    void OnClientToServerHalfClose();
    void OnServerToClientMessage(const Message& message);
    static inline const NoInterceptor OnFinalize;

   private:
    std::optional<logging_filter_detail::CallData> call_data_;
  };

 private:
  const std::string default_authority_;
};

class ServerLoggingFilter final
    : public ImplementChannelFilter<ServerLoggingFilter> {
 public:
  static const grpc_channel_filter kFilter;

  static absl::string_view TypeName() { return "logging"; }

  static absl::StatusOr<std::unique_ptr<ServerLoggingFilter>> Create(
      const ChannelArgs& args, ChannelFilter::Args );

  class Call {
   public:
    void OnClientInitialMetadata(ClientMetadata& md);
    void OnServerInitialMetadata(ServerMetadata& md);
    void OnServerTrailingMetadata(ServerMetadata& md);
    void OnClientToServerMessage(const Message& message);
    void OnClientToServerHalfClose();
    void OnServerToClientMessage(const Message& message);
    static inline const NoInterceptor OnFinalize;

   private:
    std::optional<logging_filter_detail::CallData> call_data_;
  };
};

void RegisterLoggingFilter(LoggingSink* sink);

}

#endif
