// Copyright 2021 The gRPC Authors

#include "src/core/lib/iomgr/resolved_address.h"

#include <grpc/event_engine/event_engine.h>
#include <grpc/support/port_platform.h>
#include <string.h>

#include "absl/log/check.h"
#include "src/core/lib/event_engine/resolved_address_internal.h"

namespace grpc_event_engine::experimental {

EventEngine::ResolvedAddress::ResolvedAddress(const sockaddr* address,
                                              socklen_t size)
    : size_(size) {
  DCHECK_GE(size, 0u);
  CHECK(static_cast<size_t>(size) <= sizeof(address_));
  memcpy(&address_, address, size);
}

const struct sockaddr* EventEngine::ResolvedAddress::address() const {
  return reinterpret_cast<const struct sockaddr*>(address_);
}

socklen_t EventEngine::ResolvedAddress::size() const { return size_; }

EventEngine::ResolvedAddress CreateResolvedAddress(
    const grpc_resolved_address& addr) {
  return EventEngine::ResolvedAddress(
      reinterpret_cast<const sockaddr*>(addr.addr), addr.len);
}

grpc_resolved_address CreateGRPCResolvedAddress(
    const EventEngine::ResolvedAddress& ra) {
  static_assert(
      GRPC_MAX_SOCKADDR_SIZE == EventEngine::ResolvedAddress::MAX_SIZE_BYTES,
      "size should match");
  grpc_resolved_address grpc_addr;
  memset(&grpc_addr, 0, sizeof(grpc_resolved_address));
  memcpy(grpc_addr.addr, ra.address(), ra.size());
  grpc_addr.len = ra.size();
  return grpc_addr;
}

}
