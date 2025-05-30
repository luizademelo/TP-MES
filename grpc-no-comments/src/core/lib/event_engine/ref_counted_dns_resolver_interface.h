// Copyright 2023 The gRPC Authors.

#ifndef GRPC_SRC_CORE_LIB_EVENT_ENGINE_REF_COUNTED_DNS_RESOLVER_INTERFACE_H
#define GRPC_SRC_CORE_LIB_EVENT_ENGINE_REF_COUNTED_DNS_RESOLVER_INTERFACE_H

#include <grpc/event_engine/event_engine.h>
#include <grpc/support/port_platform.h>
#include <stdint.h>

#include "absl/strings/string_view.h"
#include "src/core/util/orphanable.h"

namespace grpc_event_engine::experimental {

class RefCountedDNSResolverInterface
    : public grpc_core::InternallyRefCounted<RefCountedDNSResolverInterface> {
 public:
  explicit RefCountedDNSResolverInterface(const char* trace = nullptr,
                                          intptr_t initial_refcount = 1)
      : grpc_core::InternallyRefCounted<RefCountedDNSResolverInterface>(
            trace, initial_refcount) {}

  virtual void LookupHostname(
      EventEngine::DNSResolver::LookupHostnameCallback on_resolved,
      absl::string_view name, absl::string_view default_port) = 0;

  virtual void LookupSRV(
      EventEngine::DNSResolver::LookupSRVCallback on_resolved,
      absl::string_view name) = 0;

  virtual void LookupTXT(
      EventEngine::DNSResolver::LookupTXTCallback on_resolved,
      absl::string_view name) = 0;
};

}

#endif
