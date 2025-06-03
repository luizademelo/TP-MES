Here's the commented version of the code:

```c++
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

// Performs DNS resolution for a given hostname and port using Apple's DNSService API
// Arguments:
//   on_resolve - Callback to be invoked with the resolution result or error
//   name - The hostname and optional port to resolve (format: "host:port")
//   default_port - Default port to use if not specified in the name
void DNSServiceResolverImpl::LookupHostname(
    EventEngine::DNSResolver::LookupHostnameCallback on_resolve,
    absl::string_view name, absl::string_view default_port) {
  GRPC_TRACE_LOG(event_engine_dns, INFO)
      << "DNSServiceResolverImpl::LookupHostname: name: " << name
      << ", default_port: " << default_port << ", this: " << this;

  // Split input name into host and port components
  absl::string_view host;
  absl::string_view port_string;
  if (!grpc_core::SplitHostPort(name, &host, &port_string)) {
    // If parsing fails, return an error via callback
    engine_->Run([on_resolve = std::move(on_resolve),
                  status = absl::InvalidArgumentError(
                      absl::StrCat("Unparsable name: ", name))]() mutable {
      on_resolve(status);
    });
    return;
  }
  if (host.empty()) {
    // If host is empty, return an error via callback
    engine_->Run([on_resolve = std::move(on_resolve),
                  status = absl::InvalidArgumentError(absl::StrCat(
                      "host must not be empty in name: ", name))]() mutable {
      on_resolve(status);
    });
    return;
  }
  if (port_string.empty()) {
    if (default_port.empty()) {
      // If no port is specified and no default is provided, return an error
      engine_->Run([on_resolve = std::move(on_resolve),
                    status = absl::InvalidArgumentError(absl::StrFormat(
                        "No port in name %s or default_port argument",
                        name))]() mutable { on_resolve(std::move(status)); });
      return;
    }
    port_string = default_port;
  }

  // Convert port string to numeric value
  int port = 0;
  if (port_string == "http") {
    port = 80;
  } else if (port_string == "https") {
    port = 443;
  } else if (!absl::SimpleAtoi(port_string, &port)) {
    // If port parsing fails, return an error
    engine_->Run([on_resolve = std::move(on_resolve),
                  status = absl::InvalidArgumentError(absl::StrCat(
                      "Failed to parse port in name: ", name))]() mutable {
      on_resolve(std::move(status));
    });
    return;
  }

  // First try to parse as a direct IP address (IPv4 or IPv6)
  grpc_resolved_address addr;
  const std::string hostport = grpc_core::JoinHostPort(host, port);
  if (grpc_parse_ipv4_hostport(hostport.c_str(), &addr, false) ||
      grpc_parse_ipv6_hostport(hostport.c_str(), &addr, false)) {
    // If successful, return the parsed address immediately
    std::vector<EventEngine::ResolvedAddress> result;
    result.emplace_back(reinterpret_cast<sockaddr*>(addr.addr), addr.len);
    engine_->Run([on_resolve = std::move(on_resolve),
                  result = std::move(result)]() mutable {
      on_resolve(std::move(result));
    });
    return;
  }

  // If not an IP address, perform DNS resolution using Apple's API
  DNSServiceRef sdRef;
  auto host_string = std::string{host};
  auto error = DNSServiceGetAddrInfo(
      &sdRef, kDNSServiceFlagsTimeout | kDNSServiceFlagsReturnIntermediates, 0,
      kDNSServiceProtocol_IPv4 | kDNSServiceProtocol_IPv6, host_string.c_str(),
      &DNSServiceResolverImpl::ResolveCallback, this);

  if (error != kDNSServiceErr_NoError) {
    // If DNS resolution initiation fails, return an error
    engine_->Run([on_resolve = std::move(on_resolve),
                  status = absl::UnknownError(absl::StrFormat(
                      "DNSServiceGetAddrInfo failed with error:%d",
                      error))]() mutable { on_resolve(std::move(status)); });
    return;
  }

  // Associate the DNS service with our dispatch queue
  grpc_core::ReleasableMutexLock lock(&request_mu_);
  error = DNSServiceSetDispatchQueue(sdRef, queue_);
  if (error != kDNSServiceErr_NoError) {
    engine_->Run([on_resolve = std::move(on_resolve),
                  status = absl::UnknownError(absl::StrFormat(
                      "DNSServiceSetDispatchQueue failed with error:%d",
                      error))]() mutable { on_resolve(std::move(status)); });
    return;
  }

  // Store the request information for later processing
  requests_.try_emplace(
      sdRef, DNSServiceRequest{
                 std::move(on_resolve), static_cast<uint16_t>(port), {}});
}

// Callback function invoked by DNSServiceGetAddrInfo for each resolution result
// Arguments:
//   sdRef - Reference to the DNS service
//   flags - DNS service flags
//   interfaceIndex - Network interface index
//   errorCode - Error code if resolution failed
//   hostname - The hostname being resolved
//   address - Resolved address (if successful)
//   ttl - Time-to-live for the record
//   context - User context (pointer to DNSServiceResolverImpl instance)
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
    // If there's a fatal error, clean up and return the error
    auto request_node = that->requests_.extract(request_it);
    lock.Release();

    auto& request = request_node.mapped();
    request.on_resolve(absl::UnknownError(absl::StrFormat(
        "address lookup failed for %s: errorCode: %d", hostname, errorCode)));
    DNSServiceRefDeallocate(sdRef);
    return;
  }

  auto& request = request_it->second;

  // Track which address families we've received responses for
  if (address->sa_family == AF_INET) {
    request.has_ipv4_response = true;
  } else if (address->sa_family == AF_INET6) {
    request.has_ipv6_response = true;
  }

  if (errorCode == kDNSServiceErr_NoError) {
    // Add the resolved address to our results
    request.result.emplace_back(address, address->sa_len);
    auto& resolved_address = request.result.back();
    
    // Set the port number in the resolved address
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

  // Check if we've received all expected responses
  if (!(flags & kDNSServiceFlagsMoreComing) && request.has_ipv4_response &&
      request.has_ipv6_response) {
    // If resolution is complete, return results or error
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

// Shuts down the resolver, canceling all pending requests
void DNSServiceResolverImpl::Shutdown() {
  dispatch_async_f(queue_, Ref().release(), [](void* thatPtr) {
    grpc_core::RefCountedPtr<DNSServiceResolverImpl> that{
        static_cast<DNSServiceResolverImpl*>(thatPtr)};

    // Extract all pending requests while holding the lock
    grpc_core::ReleasableMutexLock lock(&that->request_mu_);
    auto requests = std::exchange(that->requests_, {});
    lock.Release();

    // Cancel all pending requests and clean up resources
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

}  // namespace grpc_event_engine::experimental

#endif  // AVAILABLE_MAC_OS_X_VERSION_10_12_AND_LATER
#endif  // GPR_APPLE
```