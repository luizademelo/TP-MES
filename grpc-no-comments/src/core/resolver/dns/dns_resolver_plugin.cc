// Copyright 2022 The gRPC Authors

#include "src/core/resolver/dns/dns_resolver_plugin.h"

#include <grpc/support/port_platform.h>

#include <memory>

#include "absl/log/log.h"
#include "absl/strings/match.h"
#include "src/core/config/config_vars.h"
#include "src/core/lib/experiments/experiments.h"
#include "src/core/resolver/dns/c_ares/dns_resolver_ares.h"
#include "src/core/resolver/dns/event_engine/event_engine_client_channel_resolver.h"
#include "src/core/resolver/dns/native/dns_resolver.h"
#include "src/core/resolver/resolver_factory.h"
#include "src/core/util/crash.h"

namespace grpc_core {

void RegisterDnsResolver(CoreConfiguration::Builder* builder) {
#if GRPC_IOS_EVENT_ENGINE_CLIENT
  VLOG(2) << "Using EventEngine dns resolver";
  builder->resolver_registry()->RegisterResolverFactory(
      std::make_unique<EventEngineClientChannelDNSResolverFactory>());
  return;
#endif
#ifndef GRPC_DO_NOT_INSTANTIATE_POSIX_POLLER
  if (IsEventEngineDnsEnabled()) {
    VLOG(2) << "Using EventEngine dns resolver";
    builder->resolver_registry()->RegisterResolverFactory(
        std::make_unique<EventEngineClientChannelDNSResolverFactory>());
    return;
  }
#endif
  auto resolver = ConfigVars::Get().DnsResolver();

  if (ShouldUseAresDnsResolver(resolver)) {
    VLOG(2) << "Using ares dns resolver";
    RegisterAresDnsResolver(builder);
    return;
  }

  if (absl::EqualsIgnoreCase(resolver, "native") ||
      !builder->resolver_registry()->HasResolverFactory("dns")) {
    VLOG(2) << "Using native dns resolver";
    RegisterNativeDnsResolver(builder);
    return;
  }
  Crash(
      "Unable to set DNS resolver! Likely a logic error in gRPC-core, "
      "please file a bug.");
}

}
