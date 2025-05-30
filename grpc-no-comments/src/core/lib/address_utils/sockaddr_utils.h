
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_ADDRESS_UTILS_SOCKADDR_UTILS_H
#define GRPC_SRC_CORE_LIB_ADDRESS_UTILS_SOCKADDR_UTILS_H

#include <grpc/support/port_platform.h>
#include <stdint.h>

#include <string>

#include "absl/status/statusor.h"
#include "src/core/lib/iomgr/resolved_address.h"

int grpc_sockaddr_is_v4mapped(const grpc_resolved_address* addr,
                              grpc_resolved_address* addr4_out);

int grpc_sockaddr_to_v4mapped(const grpc_resolved_address* addr,
                              grpc_resolved_address* addr6_out);

int grpc_sockaddr_is_wildcard(const grpc_resolved_address* addr, int* port_out);

void grpc_sockaddr_make_wildcards(int port, grpc_resolved_address* wild4_out,
                                  grpc_resolved_address* wild6_out);

void grpc_sockaddr_make_wildcard4(int port, grpc_resolved_address* wild_out);

void grpc_sockaddr_make_wildcard6(int port, grpc_resolved_address* wild_out);

int grpc_sockaddr_get_port(const grpc_resolved_address* addr);

int grpc_sockaddr_set_port(grpc_resolved_address* addr, int port);

GRPC_MUST_USE_RESULT absl::StatusOr<std::string> grpc_sockaddr_to_string(
    const grpc_resolved_address* addr, bool normalize);

absl::StatusOr<std::string> grpc_sockaddr_to_uri(
    const grpc_resolved_address* addr);

const char* grpc_sockaddr_get_uri_scheme(const grpc_resolved_address* addr);

int grpc_sockaddr_get_family(const grpc_resolved_address* resolved_addr);

std::string grpc_sockaddr_get_packed_host(
    const grpc_resolved_address* resolved_addr);

void grpc_sockaddr_mask_bits(grpc_resolved_address* address,
                             uint32_t mask_bits);

bool grpc_sockaddr_match_subnet(const grpc_resolved_address* address,
                                const grpc_resolved_address* subnet_address,
                                uint32_t mask_bits);

#endif
