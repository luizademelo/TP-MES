
// Copyright 2016 gRPC authors.

#ifndef GRPC_SRC_CORE_HANDSHAKER_HTTP_CONNECT_HTTP_PROXY_MAPPER_H
#define GRPC_SRC_CORE_HANDSHAKER_HTTP_CONNECT_HTTP_PROXY_MAPPER_H

#include <grpc/support/port_platform.h>

#include <optional>
#include <string>

#include "absl/strings/string_view.h"
#include "src/core/config/core_configuration.h"
#include "src/core/handshaker/proxy_mapper.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/iomgr/resolved_address.h"

namespace grpc_core {

class HttpProxyMapper final : public ProxyMapperInterface {
 public:
  static constexpr char const* kAddressProxyEnvVar = "GRPC_ADDRESS_HTTP_PROXY";
  static constexpr char const* kAddressProxyEnabledAddressesEnvVar =
      "GRPC_ADDRESS_HTTP_PROXY_ENABLED_ADDRESSES";

  std::optional<std::string> MapName(absl::string_view server_uri,
                                     ChannelArgs* args) override;

  std::optional<grpc_resolved_address> MapAddress(
      const grpc_resolved_address& address, ChannelArgs* args) override;
};

void RegisterHttpProxyMapper(CoreConfiguration::Builder* builder);

}

#endif
