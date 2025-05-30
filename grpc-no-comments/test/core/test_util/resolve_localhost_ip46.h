
// Copyright 2020 gRPC authors.

#ifndef GRPC_TEST_CORE_TEST_UTIL_RESOLVE_LOCALHOST_IP46_H
#define GRPC_TEST_CORE_TEST_UTIL_RESOLVE_LOCALHOST_IP46_H

#include <string>

#include "absl/strings/string_view.h"

namespace grpc_core {

void LocalhostResolves(bool* ipv4, bool* ipv6);

bool RunningWithIPv6Only();

absl::string_view LocalIp();

std::string LocalIpAndPort(int port);

std::string LocalIpUri(int port);

}

#endif
