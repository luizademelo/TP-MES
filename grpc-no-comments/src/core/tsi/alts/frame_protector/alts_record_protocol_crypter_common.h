
// Copyright 2018 gRPC authors.

#ifndef GRPC_SRC_CORE_TSI_ALTS_FRAME_PROTECTOR_ALTS_RECORD_PROTOCOL_CRYPTER_COMMON_H
#define GRPC_SRC_CORE_TSI_ALTS_FRAME_PROTECTOR_ALTS_RECORD_PROTOCOL_CRYPTER_COMMON_H

#include <grpc/grpc.h>
#include <grpc/support/port_platform.h>

#include "src/core/tsi/alts/frame_protector/alts_counter.h"
#include "src/core/tsi/alts/frame_protector/alts_crypter.h"

typedef struct alts_record_protocol_crypter {
  alts_crypter base;
  gsec_aead_crypter* crypter;
  alts_counter* ctr;
} alts_record_protocol_crypter;

grpc_status_code input_sanity_check(
    const alts_record_protocol_crypter* rp_crypter, const unsigned char* data,
    size_t* output_size, char** error_details);

grpc_status_code increment_counter(alts_record_protocol_crypter* rp_crypter,
                                   char** error_details);

alts_record_protocol_crypter* alts_crypter_create_common(
    gsec_aead_crypter* crypter, bool is_client, size_t overflow_size,
    char** error_details);

size_t alts_record_protocol_crypter_num_overhead_bytes(const alts_crypter* c);

void alts_record_protocol_crypter_destruct(alts_crypter* c);

#endif
