// Copyright 2024 The gRPC Authors.

#ifndef GRPC_SUPPORT_METRICS_H
#define GRPC_SUPPORT_METRICS_H

#include <grpc/event_engine/endpoint_config.h>
#include <grpc/support/port_platform.h>

#include "absl/strings/string_view.h"

namespace grpc_core {
namespace experimental {

class StatsPluginChannelScope {
 public:
  StatsPluginChannelScope(
      absl::string_view target, absl::string_view default_authority,
      const grpc_event_engine::experimental::EndpointConfig& args)
      : target_(target), default_authority_(default_authority), args_(args) {}

  absl::string_view target() const { return target_; }

  absl::string_view default_authority() const { return default_authority_; }

  const grpc_event_engine::experimental::EndpointConfig& experimental_args()
      const {
    return args_;
  }

 private:

  StatsPluginChannelScope(const StatsPluginChannelScope&) = delete;
  StatsPluginChannelScope& operator=(const StatsPluginChannelScope&) = delete;

  absl::string_view target_;
  absl::string_view default_authority_;
  const grpc_event_engine::experimental::EndpointConfig& args_;
};

}
}

#endif
