// Copyright 2024 The gRPC Authors

#ifndef GRPC_SRC_CORE_LIB_EVENT_ENGINE_WINDOWS_NATIVE_WINDOWS_DNS_RESOLVER_H
#define GRPC_SRC_CORE_LIB_EVENT_ENGINE_WINDOWS_NATIVE_WINDOWS_DNS_RESOLVER_H

#include <grpc/support/port_platform.h>

#ifdef GPR_WINDOWS

#include <grpc/event_engine/event_engine.h>

namespace grpc_event_engine::experimental {

class NativeWindowsDNSResolver : public EventEngine::DNSResolver {
 public:
  explicit NativeWindowsDNSResolver(std::shared_ptr<EventEngine> event_engine);

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
