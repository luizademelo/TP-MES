
// Copyright 2018 gRPC authors.

#ifndef GRPC_SRC_CORE_TSI_ALTS_FRAME_PROTECTOR_ALTS_CRYPTER_H
#define GRPC_SRC_CORE_TSI_ALTS_FRAME_PROTECTOR_ALTS_CRYPTER_H

#include <grpc/grpc.h>
#include <grpc/support/port_platform.h>
#include <stdbool.h>
#include <string.h>

#include "src/core/tsi/alts/crypt/gsec.h"

typedef struct alts_crypter alts_crypter;

typedef struct alts_crypter_vtable {
  size_t (*num_overhead_bytes)(const alts_crypter* crypter);
  grpc_status_code (*process_in_place)(alts_crypter* crypter,
                                       unsigned char* data,
                                       size_t data_allocated_size,
                                       size_t data_size, size_t* output_size,
                                       char** error_details);
  void (*destruct)(alts_crypter* crypter);
} alts_crypter_vtable;

struct alts_crypter {
  const alts_crypter_vtable* vtable;
};

size_t alts_crypter_num_overhead_bytes(const alts_crypter* crypter);

grpc_status_code alts_crypter_process_in_place(
    alts_crypter* crypter, unsigned char* data, size_t data_allocated_size,
    size_t data_size, size_t* output_size, char** error_details);

grpc_status_code alts_seal_crypter_create(gsec_aead_crypter* gc, bool is_client,
                                          size_t overflow_size,
                                          alts_crypter** crypter,
                                          char** error_details);

grpc_status_code alts_unseal_crypter_create(gsec_aead_crypter* gc,
                                            bool is_client,
                                            size_t overflow_size,
                                            alts_crypter** crypter,
                                            char** error_details);

void alts_crypter_destroy(alts_crypter* crypter);

#endif
