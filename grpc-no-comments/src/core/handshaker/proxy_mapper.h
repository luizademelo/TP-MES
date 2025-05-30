
// Copyright 2017 gRPC authors.

#ifndef GRPC_SRC_CORE_HANDSHAKER_PROXY_MAPPER_H
#define GRPC_SRC_CORE_HANDSHAKER_PROXY_MAPPER_H

#include <grpc/support/port_platform.h>

#include <optional>
#include <string>

#include "absl/strings/string_view.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/iomgr/resolved_address.h"

namespace grpc_core {

class ProxyMapperInterface {
 public:
  virtual ~ProxyMapperInterface() = default;

  virtual std::optional<std::string> MapName(absl::string_view server_uri,
                                             ChannelArgs* args) = 0;

  virtual std::optional<grpc_resolved_address> MapAddress(
      const grpc_resolved_address& address, ChannelArgs* args) = 0;
};

}

#endif
