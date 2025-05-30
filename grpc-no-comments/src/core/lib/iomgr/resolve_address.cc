
// Copyright 2018 gRPC authors.

#include "src/core/lib/iomgr/resolve_address.h"

#include <grpc/event_engine/event_engine.h>
#include <grpc/support/alloc.h>
#include <grpc/support/port_platform.h>

#include "absl/strings/str_cat.h"
#include "src/core/util/crash.h"
#include "src/core/util/no_destruct.h"

namespace grpc_core {
const char* kDefaultSecurePort = "https";

namespace {
NoDestruct<std::shared_ptr<DNSResolver>> g_dns_resolver;
}

const DNSResolver::LookupTaskHandle DNSResolver::LookupTaskHandle::kInvalid = {
    -1, -1};
const DNSResolver::TaskHandle DNSResolver::kNullHandle = {0, 0};

void ResetDNSResolver(std::shared_ptr<DNSResolver> resolver) {
  *g_dns_resolver = std::move(resolver);
}

std::shared_ptr<DNSResolver> GetDNSResolver() { return *g_dns_resolver; }

bool operator==(const DNSResolver::LookupTaskHandle& lhs,
                const DNSResolver::LookupTaskHandle& rhs) {
  return lhs.keys[0] == rhs.keys[0] && lhs.keys[1] == rhs.keys[1];
}

bool operator!=(const DNSResolver::LookupTaskHandle& lhs,
                const DNSResolver::LookupTaskHandle& rhs) {
  return !(lhs == rhs);
}

std::string DNSResolver::HandleToString(TaskHandle handle) {
  return absl::StrCat("{", handle.keys[0], ",", handle.keys[1], "}");
}

}
