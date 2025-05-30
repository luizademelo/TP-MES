// Copyright 2023 The gRPC Authors

#ifndef GRPC_SRC_CORE_RESOLVER_DNS_EVENT_ENGINE_EVENT_ENGINE_CLIENT_CHANNEL_RESOLVER_H
#define GRPC_SRC_CORE_RESOLVER_DNS_EVENT_ENGINE_EVENT_ENGINE_CLIENT_CHANNEL_RESOLVER_H
#include <grpc/support/port_platform.h>

#include "absl/strings/string_view.h"
#include "src/core/resolver/resolver.h"
#include "src/core/resolver/resolver_factory.h"
#include "src/core/util/orphanable.h"
#include "src/core/util/uri.h"

namespace grpc_core {

class EventEngineClientChannelDNSResolverFactory final
    : public ResolverFactory {
 public:
  absl::string_view scheme() const override { return "dns"; }
  bool IsValidUri(const URI& uri) const override;
  OrphanablePtr<Resolver> CreateResolver(ResolverArgs args) const override;
};

}

#endif
