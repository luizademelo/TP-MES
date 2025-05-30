// Copyright 2025 The gRPC Authors

#ifndef GRPC_SRC_CORE_LIB_EVENT_ENGINE_EXTENSIONS_BLOCKING_DNS_H
#define GRPC_SRC_CORE_LIB_EVENT_ENGINE_EXTENSIONS_BLOCKING_DNS_H

#include <grpc/event_engine/event_engine.h>

#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"

namespace grpc_event_engine::experimental {

class ResolverSupportsBlockingLookups {
 public:
  virtual ~ResolverSupportsBlockingLookups() = default;

  static constexpr absl::string_view EndpointExtensionName() {
    return "io.grpc.event_engine.extension.can_track_errors";
  }

  virtual absl::StatusOr<std::vector<EventEngine::ResolvedAddress>>
  LookupHostnameBlocking(absl::string_view name,
                         absl::string_view default_port) = 0;

  virtual absl::StatusOr<std::vector<EventEngine::DNSResolver::SRVRecord>>
  LookupSRVBlocking(absl::string_view name) = 0;

  virtual absl::StatusOr<std::vector<std::string>> LookupTXTBlocking(
      absl::string_view name) = 0;
};

}

#endif