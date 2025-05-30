
// Copyright 2017 gRPC authors.

#ifndef GRPC_SRC_CORE_TSI_TRANSPORT_SECURITY_GRPC_H
#define GRPC_SRC_CORE_TSI_TRANSPORT_SECURITY_GRPC_H

#include <grpc/slice_buffer.h>
#include <grpc/support/port_platform.h>

#include "src/core/tsi/transport_security.h"

tsi_result tsi_handshaker_result_create_zero_copy_grpc_protector(
    const tsi_handshaker_result* self, size_t* max_output_protected_frame_size,
    tsi_zero_copy_grpc_protector** protector);

tsi_result tsi_zero_copy_grpc_protector_protect(
    tsi_zero_copy_grpc_protector* self, grpc_slice_buffer* unprotected_slices,
    grpc_slice_buffer* protected_slices);

tsi_result tsi_zero_copy_grpc_protector_unprotect(
    tsi_zero_copy_grpc_protector* self, grpc_slice_buffer* protected_slices,
    grpc_slice_buffer* unprotected_slices, int* min_progress_size);

void tsi_zero_copy_grpc_protector_destroy(tsi_zero_copy_grpc_protector* self);

tsi_result tsi_zero_copy_grpc_protector_max_frame_size(
    tsi_zero_copy_grpc_protector* self, size_t* max_frame_size);

struct tsi_zero_copy_grpc_protector_vtable {
  tsi_result (*protect)(tsi_zero_copy_grpc_protector* self,
                        grpc_slice_buffer* unprotected_slices,
                        grpc_slice_buffer* protected_slices);
  tsi_result (*unprotect)(tsi_zero_copy_grpc_protector* self,
                          grpc_slice_buffer* protected_slices,
                          grpc_slice_buffer* unprotected_slices,
                          int* min_progress_size);
  void (*destroy)(tsi_zero_copy_grpc_protector* self);
  tsi_result (*max_frame_size)(tsi_zero_copy_grpc_protector* self,
                               size_t* max_frame_size);
};
struct tsi_zero_copy_grpc_protector {
  const tsi_zero_copy_grpc_protector_vtable* vtable;
};

#endif
