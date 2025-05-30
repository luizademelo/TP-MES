
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_SURFACE_CALL_TEST_ONLY_H
#define GRPC_SRC_CORE_LIB_SURFACE_CALL_TEST_ONLY_H

#include <grpc/grpc.h>
#include <grpc/impl/compression_types.h>
#include <grpc/support/port_platform.h>
#include <stdint.h>

grpc_compression_algorithm grpc_call_test_only_get_compression_algorithm(
    grpc_call* call);

uint32_t grpc_call_test_only_get_message_flags(grpc_call* call);

uint32_t grpc_call_test_only_get_encodings_accepted_by_peer(grpc_call* call);

#endif
