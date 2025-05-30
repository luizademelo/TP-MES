
// Copyright 2017 gRPC authors.

#include "src/core/handshaker/proxy_mapper_registry.h"

#include <grpc/support/port_platform.h>

#include <algorithm>
#include <memory>
#include <optional>
#include <utility>
#include <vector>

namespace grpc_core {

void ProxyMapperRegistry::Builder::Register(
    bool at_start, std::unique_ptr<ProxyMapperInterface> mapper) {
  if (at_start) {
    mappers_.insert(mappers_.begin(), std::move(mapper));
  } else {
    mappers_.emplace_back(std::move(mapper));
  }
}

ProxyMapperRegistry ProxyMapperRegistry::Builder::Build() {
  ProxyMapperRegistry registry;
  registry.mappers_ = std::move(mappers_);
  return registry;
}

std::optional<std::string> ProxyMapperRegistry::MapName(
    absl::string_view server_uri, ChannelArgs* args) const {
  ChannelArgs args_backup = *args;
  for (const auto& mapper : mappers_) {
    *args = args_backup;
    auto r = mapper->MapName(server_uri, args);
    if (r.has_value()) return r;
  }
  *args = args_backup;
  return std::nullopt;
}

std::optional<grpc_resolved_address> ProxyMapperRegistry::MapAddress(
    const grpc_resolved_address& address, ChannelArgs* args) const {
  ChannelArgs args_backup = *args;
  for (const auto& mapper : mappers_) {
    *args = args_backup;
    auto r = mapper->MapAddress(address, args);
    if (r.has_value()) return r;
  }
  *args = args_backup;
  return std::nullopt;
}

}
