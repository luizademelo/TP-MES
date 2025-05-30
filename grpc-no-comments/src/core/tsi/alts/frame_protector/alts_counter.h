
// Copyright 2018 gRPC authors.

#ifndef GRPC_SRC_CORE_TSI_ALTS_FRAME_PROTECTOR_ALTS_COUNTER_H
#define GRPC_SRC_CORE_TSI_ALTS_FRAME_PROTECTOR_ALTS_COUNTER_H

#include <grpc/grpc.h>
#include <grpc/support/port_platform.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct alts_counter {
  size_t size;
  size_t overflow_size;
  unsigned char* counter;
} alts_counter;

grpc_status_code alts_counter_create(bool is_client, size_t counter_size,
                                     size_t overflow_size,
                                     alts_counter** crypter_counter,
                                     char** error_details);

grpc_status_code alts_counter_increment(alts_counter* crypter_counter,
                                        bool* is_overflow,
                                        char** error_details);

size_t alts_counter_get_size(alts_counter* crypter_counter);

unsigned char* alts_counter_get_counter(alts_counter* crypter_counter);

void alts_counter_destroy(alts_counter* crypter_counter);

#endif
