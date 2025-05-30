// Copyright 2022 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_EVENT_ENGINE_UTILS_H
#define GRPC_SRC_CORE_LIB_EVENT_ENGINE_UTILS_H

#include <grpc/event_engine/event_engine.h>
#include <grpc/support/port_platform.h>
#include <stdint.h>

#include <string>
#include <vector>

#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"
#include "src/core/util/time.h"

namespace grpc_event_engine::experimental {

std::string HandleToStringInternal(uintptr_t a, uintptr_t b);

template <typename Handle>
std::string HandleToString(const Handle& handle) {
  return HandleToStringInternal(handle.keys[0], handle.keys[1]);
}

grpc_core::Timestamp ToTimestamp(grpc_core::Timestamp now,
                                 EventEngine::Duration delta);

absl::StatusOr<std::vector<EventEngine::ResolvedAddress>>
LookupHostnameBlocking(EventEngine::DNSResolver* dns_resolver,
                       absl::string_view name, absl::string_view default_port);

absl::string_view WriteEventToString(
    grpc_event_engine::experimental::internal::WriteEvent event);

}

#endif
