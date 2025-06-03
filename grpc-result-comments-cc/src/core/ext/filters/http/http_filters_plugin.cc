Here's the commented version of the code:

```c++
// Copyright 2017 gRPC authors.

// Includes platform-specific configuration and various gRPC core headers
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
// Helper function to determine if the transport is HTTP-like
// Args:
//   args: Channel arguments containing transport configuration
// Returns:
//   bool: true if transport is HTTP-like, false otherwise
bool IsBuildingHttpLikeTransport(const ChannelArgs& args) {
  auto* t = args.GetObject<Transport>();
  // Check if transport exists and its name contains "http"
  return t != nullptr && absl::StrContains(t->GetTransportName(), "http");
}
}  // namespace

// Registers HTTP-related filters with the core configuration builder
// Args:
//   builder: Pointer to CoreConfiguration builder that will register the filters
void RegisterHttpFilters(CoreConfiguration::Builder* builder) {
  // Register client compression filter for subchannels with conditions:
  // - Only for HTTP-like transports
  // - Must be registered after HttpClientFilter and ClientMessageSizeFilter
  builder->channel_init()
      ->RegisterFilter<ClientCompressionFilter>(GRPC_CLIENT_SUBCHANNEL)
      .If(IsBuildingHttpLikeTransport)
      .After<HttpClientFilter>()
      .After<ClientMessageSizeFilter>();

  // Register client compression filter for direct channels with same conditions
  builder->channel_init()
      ->RegisterFilter<ClientCompressionFilter>(GRPC_CLIENT_DIRECT_CHANNEL)
      .If(IsBuildingHttpLikeTransport)
      .After<HttpClientFilter>()
      .After<ClientMessageSizeFilter>();

  // Register server compression filter with conditions:
  // - Only for HTTP-like transports
  // - Must be registered after HttpServerFilter and ServerMessageSizeFilter
  builder->channel_init()
      ->RegisterFilter<ServerCompressionFilter>(GRPC_SERVER_CHANNEL)
      .If(IsBuildingHttpLikeTransport)
      .After<HttpServerFilter>()
      .After<ServerMessageSizeFilter>();

  // Register HTTP client filter for subchannels with conditions:
  // - Only for HTTP-like transports
  // - Must be registered after ClientMessageSizeFilter
  builder->channel_init()
      ->RegisterFilter<HttpClientFilter>(GRPC_CLIENT_SUBCHANNEL)
      .If(IsBuildingHttpLikeTransport)
      .After<ClientMessageSizeFilter>();

  // Register HTTP client filter for direct channels with same conditions
  builder->channel_init()
      ->RegisterFilter<HttpClientFilter>(GRPC_CLIENT_DIRECT_CHANNEL)
      .If(IsBuildingHttpLikeTransport)
      .After<ClientMessageSizeFilter>();

  // Register HTTP server filter with conditions:
  // - Only for HTTP-like transports
  // - Must be registered after ServerMessageSizeFilter
  builder->channel_init()
      ->RegisterFilter<HttpServerFilter>(GRPC_SERVER_CHANNEL)
      .If(IsBuildingHttpLikeTransport)
      .After<ServerMessageSizeFilter>();
}
}  // namespace grpc_core
```

The comments explain:
1. The purpose of each include statement
2. The helper function's role and implementation
3. The overall purpose of RegisterHttpFilters
4. Each filter registration's specific conditions and ordering requirements
5. The different channel types being configured (subchannel, direct channel, server channel)

The comments maintain a consistent style and provide enough detail to understand the code's functionality without being overly verbose.