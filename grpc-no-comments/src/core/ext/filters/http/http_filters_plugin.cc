
// Copyright 2017 gRPC authors.

#include <grpc/support/port_platform.h>

#include "absl/strings/match.h"
#include "src/core/config/core_configuration.h"
#include "src/core/ext/filters/http/client/http_client_filter.h"
#include "src/core/ext/filters/http/message_compress/compression_filter.h"
#include "src/core/ext/filters/http/server/http_server_filter.h"
#include "src/core/ext/filters/message_size/message_size_filter.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/experiments/experiments.h"
#include "src/core/lib/surface/channel_stack_type.h"
#include "src/core/lib/transport/transport.h"

namespace grpc_core {
namespace {
bool IsBuildingHttpLikeTransport(const ChannelArgs& args) {
  auto* t = args.GetObject<Transport>();
  return t != nullptr && absl::StrContains(t->GetTransportName(), "http");
}
}

void RegisterHttpFilters(CoreConfiguration::Builder* builder) {
  builder->channel_init()
      ->RegisterFilter<ClientCompressionFilter>(GRPC_CLIENT_SUBCHANNEL)
      .If(IsBuildingHttpLikeTransport)
      .After<HttpClientFilter>()
      .After<ClientMessageSizeFilter>();
  builder->channel_init()
      ->RegisterFilter<ClientCompressionFilter>(GRPC_CLIENT_DIRECT_CHANNEL)
      .If(IsBuildingHttpLikeTransport)
      .After<HttpClientFilter>()
      .After<ClientMessageSizeFilter>();
  builder->channel_init()
      ->RegisterFilter<ServerCompressionFilter>(GRPC_SERVER_CHANNEL)
      .If(IsBuildingHttpLikeTransport)
      .After<HttpServerFilter>()
      .After<ServerMessageSizeFilter>();
  builder->channel_init()
      ->RegisterFilter<HttpClientFilter>(GRPC_CLIENT_SUBCHANNEL)
      .If(IsBuildingHttpLikeTransport)
      .After<ClientMessageSizeFilter>();
  builder->channel_init()
      ->RegisterFilter<HttpClientFilter>(GRPC_CLIENT_DIRECT_CHANNEL)
      .If(IsBuildingHttpLikeTransport)
      .After<ClientMessageSizeFilter>();
  builder->channel_init()
      ->RegisterFilter<HttpServerFilter>(GRPC_SERVER_CHANNEL)
      .If(IsBuildingHttpLikeTransport)
      .After<ServerMessageSizeFilter>();
}
}
