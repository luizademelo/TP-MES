
// Copyright 2018 gRPC authors.

#ifndef GRPC_SRC_CORE_TSI_ALTS_ZERO_COPY_FRAME_PROTECTOR_ALTS_GRPC_RECORD_PROTOCOL_H
#define GRPC_SRC_CORE_TSI_ALTS_ZERO_COPY_FRAME_PROTECTOR_ALTS_GRPC_RECORD_PROTOCOL_H

#include <grpc/slice_buffer.h>
#include <grpc/support/port_platform.h>

#include "src/core/tsi/transport_security_interface.h"

typedef struct alts_grpc_record_protocol alts_grpc_record_protocol;

tsi_result alts_grpc_record_protocol_protect(
    alts_grpc_record_protocol* self, grpc_slice_buffer* unprotected_slices,
    grpc_slice_buffer* protected_slices);

tsi_result alts_grpc_record_protocol_unprotect(
    alts_grpc_record_protocol* self, grpc_slice_buffer* protected_slices,
    grpc_slice_buffer* unprotected_slices);

size_t alts_grpc_record_protocol_max_unprotected_data_size(
    const alts_grpc_record_protocol* self, size_t max_protected_frame_size);

void alts_grpc_record_protocol_destroy(alts_grpc_record_protocol* self);

#endif
