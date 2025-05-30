
// Copyright 2017 gRPC authors.

#ifndef GRPC_SRC_CORE_HANDSHAKER_PROXY_MAPPER_REGISTRY_H
#define GRPC_SRC_CORE_HANDSHAKER_PROXY_MAPPER_REGISTRY_H

#include <grpc/support/port_platform.h>

#include <algorithm>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "absl/strings/string_view.h"
#include "src/core/handshaker/proxy_mapper.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/iomgr/resolved_address.h"

namespace grpc_core {

class ProxyMapperRegistry {
  using ProxyMapperList = std::vector<std::unique_ptr<ProxyMapperInterface>>;

 public:
  class Builder {
   public:

    void Register(bool at_start, std::unique_ptr<ProxyMapperInterface> mapper);

    ProxyMapperRegistry Build();

   private:
    ProxyMapperList mappers_;
  };

  ~ProxyMapperRegistry() = default;
  ProxyMapperRegistry(const ProxyMapperRegistry&) = delete;
  ProxyMapperRegistry& operator=(const ProxyMapperRegistry&) = delete;
  ProxyMapperRegistry(ProxyMapperRegistry&&) = default;
  ProxyMapperRegistry& operator=(ProxyMapperRegistry&&) = default;

  std::optional<std::string> MapName(absl::string_view server_uri,
                                     ChannelArgs* args) const;

  std::optional<grpc_resolved_address> MapAddress(
      const grpc_resolved_address& address, ChannelArgs* args) const;

 private:
  ProxyMapperRegistry() = default;

  ProxyMapperList mappers_;
};

}

#endif
