
// Copyright 2018 gRPC authors.

#ifndef GRPC_SRC_CORE_TSI_ALTS_ZERO_COPY_FRAME_PROTECTOR_ALTS_IOVEC_RECORD_PROTOCOL_H
#define GRPC_SRC_CORE_TSI_ALTS_ZERO_COPY_FRAME_PROTECTOR_ALTS_IOVEC_RECORD_PROTOCOL_H

#include <grpc/support/port_platform.h>
#include <stdbool.h>

#include "src/core/tsi/alts/crypt/gsec.h"

constexpr size_t kZeroCopyFrameMessageType = 0x06;
constexpr size_t kZeroCopyFrameLengthFieldSize = 4;
constexpr size_t kZeroCopyFrameMessageTypeFieldSize = 4;
constexpr size_t kZeroCopyFrameHeaderSize =
    kZeroCopyFrameLengthFieldSize + kZeroCopyFrameMessageTypeFieldSize;

constexpr size_t kAltsRecordProtocolRekeyFrameLimit = 8;
constexpr size_t kAltsRecordProtocolFrameLimit = 5;

typedef struct iovec iovec_t;

typedef struct alts_iovec_record_protocol alts_iovec_record_protocol;

size_t alts_iovec_record_protocol_get_header_length();

size_t alts_iovec_record_protocol_get_tag_length(
    const alts_iovec_record_protocol* rp);

size_t alts_iovec_record_protocol_max_unprotected_data_size(
    const alts_iovec_record_protocol* rp, size_t max_protected_frame_size);

grpc_status_code alts_iovec_record_protocol_integrity_only_protect(
    alts_iovec_record_protocol* rp, const iovec_t* unprotected_vec,
    size_t unprotected_vec_length, iovec_t header, iovec_t tag,
    char** error_details);

grpc_status_code alts_iovec_record_protocol_integrity_only_unprotect(
    alts_iovec_record_protocol* rp, const iovec_t* protected_vec,
    size_t protected_vec_length, iovec_t header, iovec_t tag,
    char** error_details);

grpc_status_code alts_iovec_record_protocol_privacy_integrity_protect(
    alts_iovec_record_protocol* rp, const iovec_t* unprotected_vec,
    size_t unprotected_vec_length, iovec_t protected_frame,
    char** error_details);

grpc_status_code alts_iovec_record_protocol_privacy_integrity_unprotect(
    alts_iovec_record_protocol* rp, iovec_t header,
    const iovec_t* protected_vec, size_t protected_vec_length,
    iovec_t unprotected_data, char** error_details);

grpc_status_code alts_iovec_record_protocol_create(
    gsec_aead_crypter* crypter, size_t overflow_size, bool is_client,
    bool is_integrity_only, bool is_protect, alts_iovec_record_protocol** rp,
    char** error_details);

void alts_iovec_record_protocol_destroy(alts_iovec_record_protocol* rp);

#endif
