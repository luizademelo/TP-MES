
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_SLICE_SLICE_STRING_HELPERS_H
#define GRPC_SRC_CORE_LIB_SLICE_SLICE_STRING_HELPERS_H

#include <grpc/slice.h>
#include <grpc/support/port_platform.h>
#include <stdint.h>

char* grpc_dump_slice(const grpc_slice& slice, uint32_t flags);

#endif
