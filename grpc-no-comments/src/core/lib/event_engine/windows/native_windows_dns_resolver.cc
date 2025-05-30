// Copyright 2024 The gRPC Authors

#include <grpc/support/port_platform.h>

#ifdef GPR_WINDOWS
#include <grpc/event_engine/event_engine.h>
#include <inttypes.h>
#include <string.h>
#include <sys/types.h>

#include <string>

#include "absl/strings/str_cat.h"
#include "absl/strings/str_format.h"
#include "src/core/lib/event_engine/windows/native_windows_dns_resolver.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/util/host_port.h"
#include "src/core/util/status_helper.h"

namespace grpc_event_engine::experimental {

namespace {
absl::StatusOr<std::vector<EventEngine::ResolvedAddress>>
LookupHostnameBlocking(absl::string_view name, absl::string_view default_port) {
  std::vector<EventEngine::ResolvedAddress> addresses;

  std::string host;
  std::string port;
  grpc_core::SplitHostPort(name, &host, &port);
  if (host.empty()) {
    return absl::InvalidArgumentError(absl::StrCat("Unparsable name: ", name));
  }
  if (port.empty()) {
    if (default_port.empty()) {
      return absl::InvalidArgumentError(
          absl::StrFormat("No port in name %s or default_port argument", name));
    }
    port = std::string(default_port);
  }

  struct addrinfo hints;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;
  struct addrinfo* result = nullptr;
  int getaddrinfo_error =
      getaddrinfo(host.c_str(), port.c_str(), &hints, &result);
  if (getaddrinfo_error != 0) {
    return absl::UnknownError(
        absl::StrFormat("Address lookup failed for %s os_error: %s", name,
                        grpc_core::StatusToString(
                            GRPC_WSA_ERROR(WSAGetLastError(), "getaddrinfo"))
                            .c_str()));
  }

  for (auto* resp = result; resp != nullptr; resp = resp->ai_next) {
    addresses.emplace_back(resp->ai_addr, resp->ai_addrlen);
  }
  if (result) freeaddrinfo(result);
  return addresses;
}

}
NativeWindowsDNSResolver::NativeWindowsDNSResolver(
    std::shared_ptr<EventEngine> event_engine)
    : event_engine_(std::move(event_engine)) {}

void NativeWindowsDNSResolver::LookupHostname(
    EventEngine::DNSResolver::LookupHostnameCallback on_resolved,
    absl::string_view name, absl::string_view default_port) {
  event_engine_->Run(
      [name, default_port, on_resolved = std::move(on_resolved)]() mutable {
        on_resolved(LookupHostnameBlocking(name, default_port));
      });
}

void NativeWindowsDNSResolver::LookupSRV(
    EventEngine::DNSResolver::LookupSRVCallback on_resolved,
    absl::string_view ) {

  event_engine_->Run([on_resolved = std::move(on_resolved)]() mutable {
    on_resolved(absl::UnimplementedError(
        "The Native resolver does not support looking up SRV records"));
  });
}

void NativeWindowsDNSResolver::LookupTXT(
    EventEngine::DNSResolver::LookupTXTCallback on_resolved,
    absl::string_view ) {

  event_engine_->Run([on_resolved = std::move(on_resolved)]() mutable {
    on_resolved(absl::UnimplementedError(
        "The Native resolver does not support looking up TXT records"));
  });
}

}

#endif
