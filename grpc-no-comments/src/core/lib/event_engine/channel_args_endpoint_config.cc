// Copyright 2021 The gRPC Authors

#include "src/core/lib/event_engine/channel_args_endpoint_config.h"

#include <grpc/event_engine/event_engine.h>
#include <grpc/support/port_platform.h>

#include <optional>
#include <string>

#include "src/core/lib/channel/channel_args.h"

namespace grpc_event_engine::experimental {

std::optional<int> ChannelArgsEndpointConfig::GetInt(
    absl::string_view key) const {
  return args_.GetInt(key);
}

std::optional<absl::string_view> ChannelArgsEndpointConfig::GetString(
    absl::string_view key) const {
  return args_.GetString(key);
}

void* ChannelArgsEndpointConfig::GetVoidPointer(absl::string_view key) const {
  if (key == GRPC_INTERNAL_ARG_EVENT_ENGINE) {
    return args_.GetObject<EventEngine>();
  }
  return args_.GetVoidPointer(key);
}

}
