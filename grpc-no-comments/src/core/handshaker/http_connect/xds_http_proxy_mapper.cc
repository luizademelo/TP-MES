
// Copyright 2024 gRPC authors.

#include "src/core/handshaker/http_connect/xds_http_proxy_mapper.h"

#include <memory>
#include <optional>
#include <string>

#include "absl/log/log.h"
#include "src/core/handshaker/http_connect/http_connect_handshaker.h"
#include "src/core/lib/address_utils/parse_address.h"
#include "src/core/lib/address_utils/sockaddr_utils.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/xds/grpc/xds_endpoint.h"

namespace grpc_core {

std::optional<grpc_resolved_address> XdsHttpProxyMapper::MapAddress(
    const grpc_resolved_address& endpoint_address, ChannelArgs* args) {
  auto proxy_address_str = args->GetString(GRPC_ARG_XDS_HTTP_PROXY);
  if (!proxy_address_str.has_value()) return std::nullopt;
  auto proxy_address = StringToSockaddr(*proxy_address_str);
  if (!proxy_address.ok()) {
    LOG(ERROR) << "error parsing address \"" << *proxy_address_str
               << "\": " << proxy_address.status();
    return std::nullopt;
  }
  auto endpoint_address_str = grpc_sockaddr_to_string(&endpoint_address, true);
  if (!endpoint_address_str.ok()) {
    LOG(ERROR) << "error converting address to string: "
               << endpoint_address_str.status();
    return std::nullopt;
  }
  *args = args->Set(GRPC_ARG_HTTP_CONNECT_SERVER, *endpoint_address_str);
  return *proxy_address;
}

void RegisterXdsHttpProxyMapper(CoreConfiguration::Builder* builder) {
  builder->proxy_mapper_registry()->Register(
      true, std::make_unique<XdsHttpProxyMapper>());
}

}
