// Copyright 2021 The gRPC Authors

#ifndef GRPC_EVENT_ENGINE_ENDPOINT_CONFIG_H
#define GRPC_EVENT_ENGINE_ENDPOINT_CONFIG_H

#include <grpc/support/port_platform.h>

#include <optional>
#include <string>

#include "absl/strings/string_view.h"

namespace grpc_event_engine {
namespace experimental {

class EndpointConfig {
 public:
  virtual ~EndpointConfig() = default;

  virtual std::optional<int> GetInt(absl::string_view key) const = 0;

  virtual std::optional<absl::string_view> GetString(
      absl::string_view key) const = 0;

  virtual void* GetVoidPointer(absl::string_view key) const = 0;
};

}
}

#endif
