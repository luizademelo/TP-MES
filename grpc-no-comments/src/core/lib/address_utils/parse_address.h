
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_ADDRESS_UTILS_PARSE_ADDRESS_H
#define GRPC_SRC_CORE_LIB_ADDRESS_UTILS_PARSE_ADDRESS_H

#include <grpc/support/port_platform.h>
#include <stdint.h>

#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/iomgr/resolved_address.h"
#include "src/core/util/uri.h"

bool grpc_parse_unix(const grpc_core::URI& uri,
                     grpc_resolved_address* resolved_addr);

bool grpc_parse_unix_abstract(const grpc_core::URI& uri,
                              grpc_resolved_address* resolved_addr);

bool grpc_parse_vsock(const grpc_core::URI& uri,
                      grpc_resolved_address* resolved_addr);

bool grpc_parse_ipv4(const grpc_core::URI& uri,
                     grpc_resolved_address* resolved_addr);

bool grpc_parse_ipv6(const grpc_core::URI& uri,
                     grpc_resolved_address* resolved_addr);

bool grpc_parse_uri(const grpc_core::URI& uri,
                    grpc_resolved_address* resolved_addr);

bool grpc_parse_ipv4_hostport(absl::string_view hostport,
                              grpc_resolved_address* addr, bool log_errors);
bool grpc_parse_ipv6_hostport(absl::string_view hostport,
                              grpc_resolved_address* addr, bool log_errors);

uint16_t grpc_strhtons(const char* port);

namespace grpc_core {

absl::StatusOr<grpc_resolved_address> StringToSockaddr(
    absl::string_view address_and_port);
absl::StatusOr<grpc_resolved_address> StringToSockaddr(
    absl::string_view address, int port);

grpc_error_handle UnixSockaddrPopulate(absl::string_view path,
                                       grpc_resolved_address* resolved_addr);

grpc_error_handle UnixAbstractSockaddrPopulate(
    absl::string_view path, grpc_resolved_address* resolved_addr);

grpc_error_handle VSockaddrPopulate(absl::string_view path,
                                    grpc_resolved_address* resolved_addr);
}

#endif
