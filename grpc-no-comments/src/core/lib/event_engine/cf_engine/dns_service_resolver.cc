// Copyright 2023 The gRPC Authors

#include <grpc/support/port_platform.h>

#ifdef GPR_APPLE
#include <AvailabilityMacros.h>
#ifdef AVAILABLE_MAC_OS_X_VERSION_10_12_AND_LATER

#include "absl/log/check.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_format.h"
#include "src/core/lib/address_utils/parse_address.h"
#include "src/core/lib/event_engine/cf_engine/dns_service_resolver.h"
#include "src/core/lib/event_engine/posix_engine/lockfree_event.h"
#include "src/core/lib/event_engine/tcp_socket_utils.h"
#include "src/core/util/host_port.h"

namespace grpc_event_engine::experimental {

void DNSServiceResolverImpl::LookupHostname(
    EventEngine::DNSResolver::LookupHostnameCallback on_resolve,
    absl::string_view name, absl::string_view default_port) {
  GRPC_TRACE_LOG(event_engine_dns, INFO)
      << "DNSServiceResolverImpl::LookupHostname: name: " << name
      << ", default_port: " << default_port << ", this: " << this;

  absl::string_view host;
  absl::string_view port_string;
  if (!grpc_core::SplitHostPort(name, &host, &port_string)) {
    engine_->Run([on_resolve = std::move(on_resolve),
                  status = absl::InvalidArgumentError(
                      absl::StrCat("Unparsable name: ", name))]() mutable {
      on_resolve(status);
    });
    return;
  }
  if (host.empty()) {
    engine_->Run([on_resolve = std::move(on_resolve),
                  status = absl::InvalidArgumentError(absl::StrCat(
                      "host must not be empty in name: ", name))]() mutable {
      on_resolve(status);
    });
    return;
  }
  if (port_string.empty()) {
    if (default_port.empty()) {
      engine_->Run([on_resolve = std::move(on_resolve),
                    status = absl::InvalidArgumentError(absl::StrFormat(
                        "No port in name %s or default_port argument",
                        name))]() mutable { on_resolve(std::move(status)); });
      return;
    }
    port_string = default_port;
  }

  int port = 0;
  if (port_string == "http") {
    port = 80;
  } else if (port_string == "https") {
    port = 443;
  } else if (!absl::SimpleAtoi(port_string, &port)) {
    engine_->Run([on_resolve = std::move(on_resolve),
                  status = absl::InvalidArgumentError(absl::StrCat(
                      "Failed to parse port in name: ", name))]() mutable {
      on_resolve(std::move(status));
    });
    return;
  }

  grpc_resolved_address addr;
  const std::string hostport = grpc_core::JoinHostPort(host, port);
  if (grpc_parse_ipv4_hostport(hostport.c_str(), &addr,
                               false) ||
      grpc_parse_ipv6_hostport(hostport.c_str(), &addr,
                               false)) {

    std::vector<EventEngine::ResolvedAddress> result;
    result.emplace_back(reinterpret_cast<sockaddr*>(addr.addr), addr.len);
    engine_->Run([on_resolve = std::move(on_resolve),
                  result = std::move(result)]() mutable {
      on_resolve(std::move(result));
    });
    return;
  }

  DNSServiceRef sdRef;
  auto host_string = std::string{host};
  auto error = DNSServiceGetAddrInfo(
      &sdRef, kDNSServiceFlagsTimeout | kDNSServiceFlagsReturnIntermediates, 0,
      kDNSServiceProtocol_IPv4 | kDNSServiceProtocol_IPv6, host_string.c_str(),
      &DNSServiceResolverImpl::ResolveCallback, this );

  if (error != kDNSServiceErr_NoError) {
    engine_->Run([on_resolve = std::move(on_resolve),
                  status = absl::UnknownError(absl::StrFormat(
                      "DNSServiceGetAddrInfo failed with error:%d",
                      error))]() mutable { on_resolve(std::move(status)); });
    return;
  }

  grpc_core::ReleasableMutexLock lock(&request_mu_);

  error = DNSServiceSetDispatchQueue(sdRef, queue_);
  if (error != kDNSServiceErr_NoError) {
    engine_->Run([on_resolve = std::move(on_resolve),
                  status = absl::UnknownError(absl::StrFormat(
                      "DNSServiceSetDispatchQueue failed with error:%d",
                      error))]() mutable { on_resolve(std::move(status)); });
    return;
  }

  requests_.try_emplace(
      sdRef, DNSServiceRequest{
                 std::move(on_resolve), static_cast<uint16_t>(port), {}});
}

void DNSServiceResolverImpl::ResolveCallback(
    DNSServiceRef sdRef, DNSServiceFlags flags, uint32_t interfaceIndex,
    DNSServiceErrorType errorCode, const char* hostname,
    const struct sockaddr* address, uint32_t ttl, void* context) {
  GRPC_TRACE_LOG(event_engine_dns, INFO)
      << "DNSServiceResolverImpl::ResolveCallback: sdRef: " << sdRef
      << ", flags: " << flags << ", interface: " << interfaceIndex
      << ", errorCode: " << errorCode << ", hostname: " << hostname
      << ", addressFamily: " << address->sa_family << ", ttl: " << ttl
      << ", this: " << context;

  auto that = static_cast<DNSServiceResolverImpl*>(context);

  grpc_core::ReleasableMutexLock lock(&that->request_mu_);
  auto request_it = that->requests_.find(sdRef);
  CHECK(request_it != that->requests_.end());

  if (errorCode != kDNSServiceErr_NoError &&
      errorCode != kDNSServiceErr_NoSuchRecord) {

    auto request_node = that->requests_.extract(request_it);
    lock.Release();

    auto& request = request_node.mapped();
    request.on_resolve(absl::UnknownError(absl::StrFormat(
        "address lookup failed for %s: errorCode: %d", hostname, errorCode)));
    DNSServiceRefDeallocate(sdRef);
    return;
  }

  auto& request = request_it->second;

  if (address->sa_family == AF_INET) {
    request.has_ipv4_response = true;
  } else if (address->sa_family == AF_INET6) {
    request.has_ipv6_response = true;
  }

  if (errorCode == kDNSServiceErr_NoError) {
    request.result.emplace_back(address, address->sa_len);
    auto& resolved_address = request.result.back();
    if (address->sa_family == AF_INET) {
      (const_cast<sockaddr_in*>(
           reinterpret_cast<const sockaddr_in*>(resolved_address.address())))
          ->sin_port = htons(request.port);
    } else if (address->sa_family == AF_INET6) {
      (const_cast<sockaddr_in6*>(
           reinterpret_cast<const sockaddr_in6*>(resolved_address.address())))
          ->sin6_port = htons(request.port);
    }

    GRPC_TRACE_LOG(event_engine_dns, INFO)
        << "DNSServiceResolverImpl::ResolveCallback: sdRef: " << sdRef
        << ", hostname: " << hostname << ", addressPort: "
        << ResolvedAddressToString(resolved_address).value_or("ERROR")
        << ", this: " << context;
  }

  if (!(flags & kDNSServiceFlagsMoreComing) && request.has_ipv4_response &&
      request.has_ipv6_response) {

    auto request_node = that->requests_.extract(request_it);
    lock.Release();

    auto& request = request_node.mapped();
    if (request.result.empty()) {
      request.on_resolve(absl::NotFoundError(absl::StrFormat(
          "address lookup failed for %s: Domain name not found", hostname)));
    } else {
      request.on_resolve(std::move(request.result));
    }
    DNSServiceRefDeallocate(sdRef);
  }
}

void DNSServiceResolverImpl::Shutdown() {
  dispatch_async_f(queue_, Ref().release(), [](void* thatPtr) {
    grpc_core::RefCountedPtr<DNSServiceResolverImpl> that{
        static_cast<DNSServiceResolverImpl*>(thatPtr)};

    grpc_core::ReleasableMutexLock lock(&that->request_mu_);
    auto requests = std::exchange(that->requests_, {});
    lock.Release();

    for (auto& [sdRef, request] : requests) {
      GRPC_TRACE_LOG(event_engine_dns, INFO)
          << "DNSServiceResolverImpl::Shutdown sdRef: " << sdRef
          << ", this: " << thatPtr;
      request.on_resolve(
          absl::CancelledError("DNSServiceResolverImpl::Shutdown"));
      DNSServiceRefDeallocate(static_cast<DNSServiceRef>(sdRef));
    }
  });
}

}

#endif
#endif
