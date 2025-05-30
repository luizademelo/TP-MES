// Copyright 2023 The gRPC Authors.

#include <grpc/support/port_platform.h>

#include "src/core/lib/iomgr/port.h"

#ifdef GRPC_POSIX_SOCKET_RESOLVE_ADDRESS

#include <netdb.h>
#include <string.h>
#include <sys/socket.h>

#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#include "absl/functional/any_invocable.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_format.h"
#include "src/core/lib/event_engine/posix_engine/native_posix_dns_resolver.h"
#include "src/core/util/host_port.h"
#include "src/core/util/useful.h"

namespace grpc_event_engine::experimental {

absl::StatusOr<std::vector<EventEngine::ResolvedAddress>>
LookupHostnameBlocking(absl::string_view name, absl::string_view default_port) {
  struct addrinfo hints;
  struct addrinfo *result = nullptr, *resp;
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

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;
  int s = getaddrinfo(host.c_str(), port.c_str(), &hints, &result);
  if (s != 0) {

    const char* svc[][2] = {{"http", "80"}, {"https", "443"}};
    for (size_t i = 0; i < GPR_ARRAY_SIZE(svc); i++) {
      if (port == svc[i][0]) {
        s = getaddrinfo(host.c_str(), svc[i][1], &hints, &result);
        break;
      }
    }
  }
  if (s != 0) {
    return absl::UnknownError(absl::StrFormat(
        "Address lookup failed for %s os_error: %s syscall: getaddrinfo", name,
        gai_strerror(s)));
  }

  std::vector<EventEngine::ResolvedAddress> addresses;
  for (resp = result; resp != nullptr; resp = resp->ai_next) {
    addresses.emplace_back(resp->ai_addr, resp->ai_addrlen);
  }
  if (result) {
    freeaddrinfo(result);
  }
  return addresses;
}

NativePosixDNSResolver::NativePosixDNSResolver(
    std::shared_ptr<EventEngine> event_engine)
    : event_engine_(std::move(event_engine)) {}

void NativePosixDNSResolver::LookupHostname(
    EventEngine::DNSResolver::LookupHostnameCallback on_resolved,
    absl::string_view name, absl::string_view default_port) {
  event_engine_->Run([name = std::string(name), default_port,
                      on_resolved = std::move(on_resolved)]() mutable {
    on_resolved(LookupHostnameBlocking(name, default_port));
  });
}

void NativePosixDNSResolver::LookupSRV(
    EventEngine::DNSResolver::LookupSRVCallback on_resolved,
    absl::string_view ) {

  event_engine_->Run([on_resolved = std::move(on_resolved)]() mutable {
    on_resolved(absl::UnimplementedError(
        "The Native resolver does not support looking up SRV records"));
  });
}

void NativePosixDNSResolver::LookupTXT(
    EventEngine::DNSResolver::LookupTXTCallback on_resolved,
    absl::string_view ) {

  event_engine_->Run([on_resolved = std::move(on_resolved)]() mutable {
    on_resolved(absl::UnimplementedError(
        "The Native resolver does not support looking up TXT records"));
  });
}

}

#endif
