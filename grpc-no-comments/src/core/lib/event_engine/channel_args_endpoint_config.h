// Copyright 2021 The gRPC Authors

#ifndef GRPC_SRC_CORE_LIB_EVENT_ENGINE_CHANNEL_ARGS_ENDPOINT_CONFIG_H
#define GRPC_SRC_CORE_LIB_EVENT_ENGINE_CHANNEL_ARGS_ENDPOINT_CONFIG_H

#include <grpc/event_engine/endpoint_config.h>
#include <grpc/support/port_platform.h>

#include <optional>

#include "absl/strings/string_view.h"
#include "src/core/lib/channel/channel_args.h"

namespace grpc_event_engine::experimental {

class ChannelArgsEndpointConfig : public EndpointConfig {
 public:
  ChannelArgsEndpointConfig() = default;
  explicit ChannelArgsEndpointConfig(const grpc_core::ChannelArgs& args)
      : args_(args) {}
  ChannelArgsEndpointConfig(const ChannelArgsEndpointConfig& config) = default;
  ChannelArgsEndpointConfig& operator=(const ChannelArgsEndpointConfig& other) =
      default;
  std::optional<int> GetInt(absl::string_view key) const override;
  std::optional<absl::string_view> GetString(
      absl::string_view key) const override;
  void* GetVoidPointer(absl::string_view key) const override;

 private:
  grpc_core::ChannelArgs args_;
};

}

#endif
