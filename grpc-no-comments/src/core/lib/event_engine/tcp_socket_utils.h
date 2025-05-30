// Copyright 2022 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_EVENT_ENGINE_TCP_SOCKET_UTILS_H
#define GRPC_SRC_CORE_LIB_EVENT_ENGINE_TCP_SOCKET_UTILS_H

#include <grpc/event_engine/event_engine.h>
#include <grpc/support/port_platform.h>

#include <optional>
#include <string>

#include "absl/status/statusor.h"

namespace grpc_event_engine::experimental {

bool ResolvedAddressIsV4Mapped(
    const EventEngine::ResolvedAddress& resolved_addr,
    EventEngine::ResolvedAddress* resolved_addr4_out);

bool ResolvedAddressToV4Mapped(
    const EventEngine::ResolvedAddress& resolved_addr,
    EventEngine::ResolvedAddress* resolved_addr6_out);

EventEngine::ResolvedAddress ResolvedAddressMakeWild6(int port);

EventEngine::ResolvedAddress ResolvedAddressMakeWild4(int port);

int ResolvedAddressGetPort(const EventEngine::ResolvedAddress& resolved_addr);

void ResolvedAddressSetPort(EventEngine::ResolvedAddress& resolved_addr,
                            int port);

std::optional<int> MaybeGetWildcardPortFromAddress(
    const EventEngine::ResolvedAddress& addr);

bool ResolvedAddressIsVSock(const EventEngine::ResolvedAddress& resolved_addr);

absl::StatusOr<std::string> ResolvedAddressToString(
    const EventEngine::ResolvedAddress& resolved_addr);

absl::StatusOr<std::string> ResolvedAddressToNormalizedString(
    const EventEngine::ResolvedAddress& resolved_addr);

absl::StatusOr<std::string> ResolvedAddressToURI(
    const EventEngine::ResolvedAddress& resolved_address);

absl::StatusOr<EventEngine::ResolvedAddress> URIToResolvedAddress(
    std::string address_str);

}

#endif
