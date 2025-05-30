
// Copyright 2024 gRPC authors.

#ifndef GRPC_SRC_CORE_HANDSHAKER_HTTP_CONNECT_XDS_HTTP_PROXY_MAPPER_H
#define GRPC_SRC_CORE_HANDSHAKER_HTTP_CONNECT_XDS_HTTP_PROXY_MAPPER_H

#include <optional>
#include <string>

#include "absl/strings/string_view.h"
#include "src/core/config/core_configuration.h"
#include "src/core/handshaker/proxy_mapper.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/iomgr/resolved_address.h"

namespace grpc_core {

class XdsHttpProxyMapper final : public ProxyMapperInterface {
 public:
  std::optional<std::string> MapName(absl::string_view ,
                                     ChannelArgs* ) override {
    return std::nullopt;
  }

  std::optional<grpc_resolved_address> MapAddress(
      const grpc_resolved_address& address, ChannelArgs* args) override;
};

void RegisterXdsHttpProxyMapper(CoreConfiguration::Builder* builder);

}

#endif
