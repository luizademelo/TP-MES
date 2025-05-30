// Copyright 2023 The gRPC Authors.

#ifndef GRPC_SRC_CORE_LIB_EVENT_ENGINE_POSIX_ENGINE_NATIVE_POSIX_DNS_RESOLVER_H
#define GRPC_SRC_CORE_LIB_EVENT_ENGINE_POSIX_ENGINE_NATIVE_POSIX_DNS_RESOLVER_H

#include <grpc/support/port_platform.h>

#include <memory>

#include "absl/strings/string_view.h"
#include "src/core/lib/iomgr/port.h"

#ifdef GRPC_POSIX_SOCKET_RESOLVE_ADDRESS

#include <grpc/event_engine/event_engine.h>

namespace grpc_event_engine::experimental {

absl::StatusOr<std::vector<EventEngine::ResolvedAddress>>
LookupHostnameBlocking(absl::string_view name, absl::string_view default_port);

class NativePosixDNSResolver : public EventEngine::DNSResolver {
 public:
  explicit NativePosixDNSResolver(std::shared_ptr<EventEngine> event_engine);

  void LookupHostname(
      EventEngine::DNSResolver::LookupHostnameCallback on_resolved,
      absl::string_view name, absl::string_view default_port) override;

  void LookupSRV(EventEngine::DNSResolver::LookupSRVCallback on_resolved,
                 absl::string_view name) override;

  void LookupTXT(EventEngine::DNSResolver::LookupTXTCallback on_resolved,
                 absl::string_view name) override;

 private:
  std::shared_ptr<EventEngine> event_engine_;
};

}

#endif
#endif
