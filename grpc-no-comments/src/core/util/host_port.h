
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_UTIL_HOST_PORT_H
#define GRPC_SRC_CORE_UTIL_HOST_PORT_H

#include <grpc/support/port_platform.h>

#include <string>

#include "absl/strings/string_view.h"

namespace grpc_core {

std::string JoinHostPort(absl::string_view host, int port);

bool SplitHostPort(absl::string_view name, absl::string_view* host,
                   absl::string_view* port);
bool SplitHostPort(absl::string_view name, std::string* host,
                   std::string* port);

}

#endif
