
// Copyright 2018 gRPC authors.

#ifndef GRPC_TEST_CORE_TSI_ALTS_CRYPT_GSEC_TEST_UTIL_H
#define GRPC_TEST_CORE_TSI_ALTS_CRYPT_GSEC_TEST_UTIL_H

#include <grpc/grpc.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void gsec_test_random_bytes(uint8_t* bytes, size_t length);

void gsec_test_random_array(uint8_t** bytes, size_t length);

uint32_t gsec_test_bias_random_uint32(uint32_t max_length);

void gsec_test_copy(const uint8_t* src, uint8_t** des, size_t source_len);

void gsec_test_copy_and_alter_random_byte(const uint8_t* src, uint8_t** des,
                                          size_t source_len);

int gsec_test_expect_compare_code_and_substr(grpc_status_code status1,
                                             grpc_status_code status2,
                                             const char* msg1,
                                             const char* msg2);

#endif
