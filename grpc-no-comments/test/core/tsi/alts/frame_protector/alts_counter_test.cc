
// Copyright 2018 gRPC authors.

#include "src/core/tsi/alts/frame_protector/alts_counter.h"

#include <grpc/support/alloc.h>

#include "gtest/gtest.h"
#include "src/core/util/crash.h"
#include "test/core/tsi/alts/crypt/gsec_test_util.h"

const size_t kSmallCounterSize = 4;
const size_t kSmallOverflowSize = 1;
const size_t kGcmCounterSize = 12;
const size_t kGcmOverflowSize = 5;

static bool do_bytes_represent_client(alts_counter* ctr,
                                      unsigned char* , size_t size) {
  return (ctr->counter[size - 1] & 0x80) == 0x80;
}

static void alts_counter_test_input_sanity_check(size_t counter_size,
                                                 size_t overflow_size) {
  alts_counter* ctr = nullptr;
  char* error_details = nullptr;

  grpc_status_code status =
      alts_counter_create(true, 0, overflow_size, &ctr, &error_details);
  ASSERT_TRUE(gsec_test_expect_compare_code_and_substr(
      status, GRPC_STATUS_INVALID_ARGUMENT, error_details,
      "counter_size is invalid."));
  gpr_free(error_details);

  status = alts_counter_create(true, counter_size, 0, &ctr, &error_details);
  ASSERT_TRUE(gsec_test_expect_compare_code_and_substr(
      status, GRPC_STATUS_INVALID_ARGUMENT, error_details,
      "overflow_size is invalid."));
  gpr_free(error_details);

  status = alts_counter_create(true, counter_size, overflow_size, nullptr,
                               &error_details);
  ASSERT_TRUE(gsec_test_expect_compare_code_and_substr(
      status, GRPC_STATUS_INVALID_ARGUMENT, error_details,
      "crypter_counter is nullptr."));
  gpr_free(error_details);

  status = alts_counter_create(true, counter_size, overflow_size, &ctr,
                               &error_details);
  ASSERT_EQ(status, GRPC_STATUS_OK);

  bool is_overflow = false;
  status = alts_counter_increment(nullptr, &is_overflow, &error_details);
  ASSERT_TRUE(gsec_test_expect_compare_code_and_substr(
      status, GRPC_STATUS_INVALID_ARGUMENT, error_details,
      "crypter_counter is nullptr."));
  gpr_free(error_details);

  status = alts_counter_increment(ctr, nullptr, &error_details);
  ASSERT_TRUE(gsec_test_expect_compare_code_and_substr(
      status, GRPC_STATUS_INVALID_ARGUMENT, error_details,
      "is_overflow is nullptr."));
  gpr_free(error_details);
  alts_counter_destroy(ctr);
}

static void alts_counter_test_overflow_full_range(bool is_client,
                                                  size_t counter_size,
                                                  size_t overflow_size) {
  alts_counter* ctr = nullptr;
  char* error_details = nullptr;
  grpc_status_code status = alts_counter_create(
      is_client, counter_size, overflow_size, &ctr, &error_details);
  ASSERT_EQ(status, GRPC_STATUS_OK);
  unsigned char* expected =
      static_cast<unsigned char*>(gpr_zalloc(counter_size));
  if (is_client) {
    expected[counter_size - 1] = 0x80;
  }

  ASSERT_EQ(do_bytes_represent_client(ctr, alts_counter_get_counter(ctr),
                                      counter_size),
            is_client);
  ASSERT_EQ(memcmp(alts_counter_get_counter(ctr), expected, counter_size), 0);
  bool is_overflow = false;
  ASSERT_EQ(alts_counter_increment(ctr, &is_overflow, &error_details),
            GRPC_STATUS_OK);
  ASSERT_FALSE(is_overflow);

  int iterations = 1 << (overflow_size * 8);
  int ind = 1;
  for (ind = 1; ind < iterations - 1; ind++) {
    ASSERT_EQ(do_bytes_represent_client(ctr, alts_counter_get_counter(ctr),
                                        counter_size),
              is_client);
    ASSERT_EQ(alts_counter_increment(ctr, &is_overflow, &error_details),
              GRPC_STATUS_OK);
    ASSERT_FALSE(is_overflow);
  }
  ASSERT_EQ(do_bytes_represent_client(ctr, alts_counter_get_counter(ctr),
                                      counter_size),
            is_client);
  ASSERT_EQ(alts_counter_increment(ctr, &is_overflow, &error_details),
            GRPC_STATUS_FAILED_PRECONDITION);
  ASSERT_TRUE(is_overflow);
  gpr_free(expected);
  alts_counter_destroy(ctr);
}

static void alts_counter_test_overflow_single_increment(bool is_client,
                                                        size_t counter_size,
                                                        size_t overflow_size) {
  alts_counter* ctr = nullptr;
  char* error_details = nullptr;
  grpc_status_code status = alts_counter_create(
      is_client, counter_size, overflow_size, &ctr, &error_details);
  ASSERT_EQ(status, GRPC_STATUS_OK);
  unsigned char* expected =
      static_cast<unsigned char*>(gpr_zalloc(counter_size));
  memset(expected, 0xFF, overflow_size);
  expected[0] = 0xFE;

  if (is_client) {
    expected[counter_size - 1] = 0x80;
  }
  memcpy(ctr->counter, expected, counter_size);
  ASSERT_EQ(do_bytes_represent_client(ctr, alts_counter_get_counter(ctr),
                                      counter_size),
            is_client);
  ASSERT_EQ(memcmp(expected, alts_counter_get_counter(ctr), counter_size), 0);
  bool is_overflow = false;
  ASSERT_EQ(alts_counter_increment(ctr, &is_overflow, &error_details),
            GRPC_STATUS_OK);
  ASSERT_FALSE(is_overflow);
  ASSERT_EQ(do_bytes_represent_client(ctr, alts_counter_get_counter(ctr),
                                      counter_size),
            is_client);
  expected[0] = static_cast<unsigned char>(expected[0] + 1);
  ASSERT_EQ(memcmp(expected, alts_counter_get_counter(ctr), counter_size), 0);
  ASSERT_EQ(alts_counter_increment(ctr, &is_overflow, &error_details),
            GRPC_STATUS_FAILED_PRECONDITION);
  ASSERT_TRUE(is_overflow);
  gpr_free(expected);
  alts_counter_destroy(ctr);
}

TEST(AltsCounterTest, MainTest) {
  alts_counter_test_input_sanity_check(kGcmCounterSize, kGcmOverflowSize);
  alts_counter_test_overflow_full_range(true, kSmallCounterSize,
                                        kSmallOverflowSize);
  alts_counter_test_overflow_full_range(false, kSmallCounterSize,
                                        kSmallOverflowSize);
  alts_counter_test_overflow_single_increment(true, kGcmCounterSize,
                                              kGcmOverflowSize);
  alts_counter_test_overflow_single_increment(false, kGcmCounterSize,
                                              kGcmOverflowSize);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
