
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_IOMGR_SOCKET_UTILS_H
#define GRPC_SRC_CORE_LIB_IOMGR_SOCKET_UTILS_H

#include <grpc/support/port_platform.h>
#include <stddef.h>

uint16_t grpc_htons(uint16_t hostshort);

uint16_t grpc_ntohs(uint16_t netshort);

uint32_t grpc_htonl(uint32_t hostlong);

uint32_t grpc_ntohl(uint32_t netlong);

int grpc_inet_pton(int af, const char* src, void* dst);

const char* grpc_inet_ntop(int af, const void* src, char* dst, size_t size);

#endif
