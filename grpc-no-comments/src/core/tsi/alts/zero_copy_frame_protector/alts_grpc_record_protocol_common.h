
// Copyright 2018 gRPC authors.

#ifndef GRPC_SRC_CORE_TSI_ALTS_ZERO_COPY_FRAME_PROTECTOR_ALTS_GRPC_RECORD_PROTOCOL_COMMON_H
#define GRPC_SRC_CORE_TSI_ALTS_ZERO_COPY_FRAME_PROTECTOR_ALTS_GRPC_RECORD_PROTOCOL_COMMON_H

#include <grpc/support/port_platform.h>

#include "src/core/tsi/alts/zero_copy_frame_protector/alts_grpc_record_protocol.h"
#include "src/core/tsi/alts/zero_copy_frame_protector/alts_iovec_record_protocol.h"

struct alts_grpc_record_protocol_vtable {
  tsi_result (*protect)(alts_grpc_record_protocol* self,
                        grpc_slice_buffer* unprotected_slices,
                        grpc_slice_buffer* protected_slices);
  tsi_result (*unprotect)(alts_grpc_record_protocol* self,
                          grpc_slice_buffer* protected_slices,
                          grpc_slice_buffer* unprotected_slices);
  void (*destruct)(alts_grpc_record_protocol* self);
};

struct alts_grpc_record_protocol {
  const alts_grpc_record_protocol_vtable* vtable;
  alts_iovec_record_protocol* iovec_rp;
  grpc_slice_buffer header_sb;
  unsigned char* header_buf;
  size_t header_length;
  size_t tag_length;
  iovec_t* iovec_buf;
  size_t iovec_buf_length;
};

void alts_grpc_record_protocol_convert_slice_buffer_to_iovec(
    alts_grpc_record_protocol* rp, const grpc_slice_buffer* sb);

void alts_grpc_record_protocol_copy_slice_buffer(const grpc_slice_buffer* src,
                                                 unsigned char* dst);

iovec_t alts_grpc_record_protocol_get_header_iovec(
    alts_grpc_record_protocol* rp);

tsi_result alts_grpc_record_protocol_init(alts_grpc_record_protocol* rp,
                                          gsec_aead_crypter* crypter,
                                          size_t overflow_size, bool is_client,
                                          bool is_integrity_only,
                                          bool is_protect);

#endif
