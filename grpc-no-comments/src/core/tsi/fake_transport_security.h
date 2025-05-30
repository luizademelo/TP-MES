
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_TSI_FAKE_TRANSPORT_SECURITY_H
#define GRPC_SRC_CORE_TSI_FAKE_TRANSPORT_SECURITY_H

#include <grpc/support/port_platform.h>

#include "src/core/lib/slice/slice_internal.h"
#include "src/core/tsi/transport_security_interface.h"

#define TSI_FAKE_CERTIFICATE_TYPE "FAKE"

#define TSI_FAKE_SECURITY_LEVEL "TSI_SECURITY_NONE"

tsi_handshaker* tsi_create_fake_handshaker(int is_client);

tsi_frame_protector* tsi_create_fake_frame_protector(
    size_t* max_protected_frame_size);

tsi_zero_copy_grpc_protector* tsi_create_fake_zero_copy_grpc_protector(
    size_t* max_protected_frame_size);

uint32_t tsi_fake_zero_copy_grpc_protector_next_frame_size(
    const grpc_slice_buffer* protected_slices);
#endif
