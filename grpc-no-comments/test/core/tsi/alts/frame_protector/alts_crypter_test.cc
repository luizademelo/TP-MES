
// Copyright 2018 gRPC authors.

#include "src/core/tsi/alts/frame_protector/alts_crypter.h"

#include <grpc/support/alloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <memory>

#include "absl/types/span.h"
#include "gtest/gtest.h"
#include "test/core/tsi/alts/crypt/gsec_test_util.h"

static void alts_crypter_test_random_seal_unseal(alts_crypter* server_seal,
                                                 alts_crypter* server_unseal,
                                                 alts_crypter* client_seal,
                                                 alts_crypter* client_unseal) {
  size_t data_size = gsec_test_bias_random_uint32(1024) + 1;
  size_t num_overhead_bytes = alts_crypter_num_overhead_bytes(server_seal);
  size_t protected_data_size = data_size + num_overhead_bytes;
  uint8_t* data_buffer = static_cast<uint8_t*>(gpr_malloc(protected_data_size));
  gsec_test_random_bytes(data_buffer, data_size);
  uint8_t* duplicate_buffer = nullptr;
  gsec_test_copy(data_buffer, &duplicate_buffer, data_size);

  size_t size = data_size;
  grpc_status_code status = alts_crypter_process_in_place(
      client_seal, data_buffer, protected_data_size, size, &size, nullptr);
  ASSERT_EQ(status, GRPC_STATUS_OK);
  ASSERT_EQ(size, protected_data_size);
  status = alts_crypter_process_in_place(
      server_unseal, data_buffer, protected_data_size, size, &size, nullptr);
  ASSERT_EQ(status, GRPC_STATUS_OK);
  ASSERT_EQ(memcmp(data_buffer, duplicate_buffer, data_size), 0);
  ASSERT_EQ(size, data_size);

  status = alts_crypter_process_in_place(
      server_seal, data_buffer, protected_data_size, size, &size, nullptr);
  ASSERT_EQ(status, GRPC_STATUS_OK);
  ASSERT_EQ(size, protected_data_size);
  status = alts_crypter_process_in_place(
      client_unseal, data_buffer, protected_data_size, size, &size, nullptr);
  ASSERT_EQ(status, GRPC_STATUS_OK);
  ASSERT_EQ(memcmp(data_buffer, duplicate_buffer, data_size), 0);
  ASSERT_EQ(size, data_size);
  gpr_free(data_buffer);
  gpr_free(duplicate_buffer);
}

static void alts_crypter_test_multiple_random_seal_unseal(
    alts_crypter* server_seal, alts_crypter* server_unseal,
    alts_crypter* client_seal, alts_crypter* client_unseal) {
  size_t data_size = gsec_test_bias_random_uint32(1024) + 1;
  size_t num_overhead_bytes = alts_crypter_num_overhead_bytes(server_seal);
  size_t protected_data_size = data_size + num_overhead_bytes;

  uint8_t* data_buffer1 =
      static_cast<uint8_t*>(gpr_malloc(protected_data_size));
  uint8_t* data_buffer2 =
      static_cast<uint8_t*>(gpr_malloc(protected_data_size));
  uint8_t* duplicate_buffer1 = nullptr;
  uint8_t* duplicate_buffer2 = nullptr;
  gsec_test_random_bytes(data_buffer1, data_size);
  gsec_test_random_bytes(data_buffer2, data_size);
  gsec_test_copy(data_buffer1, &duplicate_buffer1, data_size);
  gsec_test_copy(data_buffer2, &duplicate_buffer2, data_size);

  size_t size1 = data_size, size2 = data_size;
  grpc_status_code status = alts_crypter_process_in_place(
      client_seal, data_buffer1, protected_data_size, size1, &size1, nullptr);
  ASSERT_EQ(status, GRPC_STATUS_OK);
  ASSERT_EQ(size1, protected_data_size);
  status = alts_crypter_process_in_place(
      client_seal, data_buffer2, protected_data_size, size2, &size2, nullptr);
  ASSERT_EQ(status, GRPC_STATUS_OK);
  ASSERT_EQ(size2, protected_data_size);
  status = alts_crypter_process_in_place(
      server_unseal, data_buffer1, protected_data_size, size1, &size1, nullptr);
  ASSERT_EQ(status, GRPC_STATUS_OK);
  ASSERT_EQ(memcmp(data_buffer1, duplicate_buffer1, data_size), 0);
  ASSERT_EQ(size1, data_size);
  status = alts_crypter_process_in_place(
      server_unseal, data_buffer2, protected_data_size, size2, &size2, nullptr);
  ASSERT_EQ(status, GRPC_STATUS_OK);
  ASSERT_EQ(memcmp(data_buffer2, duplicate_buffer2, data_size), 0);
  ASSERT_EQ(size2, data_size);

  status = alts_crypter_process_in_place(
      server_seal, data_buffer1, protected_data_size, size1, &size1, nullptr);
  ASSERT_EQ(status, GRPC_STATUS_OK);
  ASSERT_EQ(size1, protected_data_size);
  status = alts_crypter_process_in_place(
      server_seal, data_buffer2, protected_data_size, size2, &size2, nullptr);
  ASSERT_EQ(status, GRPC_STATUS_OK);
  ASSERT_EQ(size2, protected_data_size);
  status = alts_crypter_process_in_place(
      client_unseal, data_buffer1, protected_data_size, size1, &size1, nullptr);
  ASSERT_EQ(status, GRPC_STATUS_OK);
  ASSERT_EQ(memcmp(data_buffer1, duplicate_buffer1, data_size), 0);
  ASSERT_EQ(size1, data_size);
  status = alts_crypter_process_in_place(
      client_unseal, data_buffer2, protected_data_size, size2, &size2, nullptr);
  ASSERT_EQ(status, GRPC_STATUS_OK);
  ASSERT_EQ(memcmp(data_buffer2, duplicate_buffer2, data_size), 0);
  ASSERT_EQ(size2, data_size);

  gpr_free(data_buffer1);
  gpr_free(data_buffer2);
  gpr_free(duplicate_buffer1);
  gpr_free(duplicate_buffer2);
}

static void alts_crypter_test_corrupted_unseal(
    alts_crypter* server_seal, alts_crypter* server_unseal,
    alts_crypter* client_seal, alts_crypter* ) {
  size_t data_size = gsec_test_bias_random_uint32(1024) + 1;
  size_t num_overhead_bytes = alts_crypter_num_overhead_bytes(server_seal);
  size_t protected_data_size = data_size + num_overhead_bytes;
  auto* data_buffer = static_cast<uint8_t*>(gpr_malloc(protected_data_size));
  auto* zero_buffer = static_cast<uint8_t*>(gpr_zalloc(data_size));

  size_t size = data_size;
  gsec_test_random_bytes(data_buffer, data_size);
  grpc_status_code status = alts_crypter_process_in_place(
      client_seal, data_buffer, protected_data_size, size, &size, nullptr);
  ASSERT_EQ(status, GRPC_STATUS_OK);
  ASSERT_EQ(size, protected_data_size);
  uint8_t* corrupted_data_buffer;
  char* error_message = nullptr;
  gsec_test_copy_and_alter_random_byte(data_buffer, &corrupted_data_buffer,
                                       protected_data_size);
  status = alts_crypter_process_in_place(server_unseal, corrupted_data_buffer,
                                         protected_data_size, size, &size,
                                         &error_message);
  ASSERT_TRUE(gsec_test_expect_compare_code_and_substr(
      status, GRPC_STATUS_FAILED_PRECONDITION, error_message,
      "Checking tag failed"));
  ASSERT_EQ(memcmp(corrupted_data_buffer, zero_buffer, data_size), 0);
  gpr_free(corrupted_data_buffer);
  gpr_free(error_message);

  size = data_size;
  gsec_test_random_bytes(data_buffer, data_size);
  status = alts_crypter_process_in_place(
      client_seal, data_buffer, protected_data_size, size, &size, nullptr);
  ASSERT_EQ(status, GRPC_STATUS_OK);
  ASSERT_EQ(size, protected_data_size);
  gsec_test_copy(data_buffer, &corrupted_data_buffer, protected_data_size);
  (*corrupted_data_buffer)++;
  status = alts_crypter_process_in_place(server_unseal, corrupted_data_buffer,
                                         protected_data_size, size, &size,
                                         &error_message);
  ASSERT_TRUE(gsec_test_expect_compare_code_and_substr(
      status, GRPC_STATUS_FAILED_PRECONDITION, error_message,
      "Checking tag failed"));
  ASSERT_EQ(memcmp(corrupted_data_buffer, zero_buffer, data_size), 0);
  gpr_free(corrupted_data_buffer);
  gpr_free(error_message);

  size = data_size;
  gsec_test_random_bytes(data_buffer, data_size);
  status = alts_crypter_process_in_place(
      client_seal, data_buffer, protected_data_size, size, &size, nullptr);
  ASSERT_EQ(status, GRPC_STATUS_OK);
  ASSERT_EQ(size, protected_data_size);
  gsec_test_copy(data_buffer, &corrupted_data_buffer, protected_data_size);
  (*(corrupted_data_buffer + protected_data_size - 1))++;
  status = alts_crypter_process_in_place(server_unseal, corrupted_data_buffer,
                                         protected_data_size, size, &size,
                                         &error_message);
  ASSERT_TRUE(gsec_test_expect_compare_code_and_substr(
      status, GRPC_STATUS_FAILED_PRECONDITION, error_message,
      "Checking tag failed"));
  ASSERT_EQ(memcmp(corrupted_data_buffer, zero_buffer, data_size), 0);
  gpr_free(corrupted_data_buffer);
  gpr_free(error_message);

  gpr_free(data_buffer);
  gpr_free(zero_buffer);
}

static void alts_crypter_test_unsync_seal_unseal(alts_crypter* server_seal,
                                                 alts_crypter* server_unseal,
                                                 alts_crypter* client_seal,
                                                 alts_crypter* client_unseal) {
  size_t data_size = gsec_test_bias_random_uint32(1024) + 1;
  size_t num_overhead_bytes = alts_crypter_num_overhead_bytes(server_seal);
  size_t protected_data_size = data_size + num_overhead_bytes;
  auto* data_buffer = static_cast<uint8_t*>(gpr_malloc(protected_data_size));
  auto* zero_buffer = static_cast<uint8_t*>(gpr_zalloc(data_size));

  size_t size = data_size;
  gsec_test_random_bytes(data_buffer, data_size);
  grpc_status_code status = alts_crypter_process_in_place(
      client_seal, data_buffer, protected_data_size, size, &size, nullptr);
  ASSERT_EQ(status, GRPC_STATUS_OK);
  ASSERT_EQ(size, protected_data_size);

  size = data_size;
  gsec_test_random_bytes(data_buffer, data_size);
  status = alts_crypter_process_in_place(
      client_seal, data_buffer, protected_data_size, size, &size, nullptr);
  ASSERT_EQ(status, GRPC_STATUS_OK);
  ASSERT_EQ(size, protected_data_size);

  char* error_message = nullptr;
  status = alts_crypter_process_in_place(server_unseal, data_buffer,
                                         protected_data_size, size, &size,
                                         &error_message);
  ASSERT_TRUE(gsec_test_expect_compare_code_and_substr(
      status, GRPC_STATUS_FAILED_PRECONDITION, error_message,
      "Checking tag failed"));
  ASSERT_EQ(memcmp(data_buffer, zero_buffer, data_size), 0);
  gpr_free(error_message);

  size = data_size;
  gsec_test_random_bytes(data_buffer, data_size);
  status = alts_crypter_process_in_place(
      server_seal, data_buffer, protected_data_size, size, &size, nullptr);
  ASSERT_EQ(status, GRPC_STATUS_OK);
  ASSERT_EQ(size, protected_data_size);

  size = data_size;
  gsec_test_random_bytes(data_buffer, data_size);
  status = alts_crypter_process_in_place(
      server_seal, data_buffer, protected_data_size, size, &size, nullptr);
  ASSERT_EQ(status, GRPC_STATUS_OK);
  ASSERT_EQ(size, protected_data_size);

  status = alts_crypter_process_in_place(client_unseal, data_buffer,
                                         protected_data_size, size, &size,
                                         &error_message);
  ASSERT_TRUE(gsec_test_expect_compare_code_and_substr(
      status, GRPC_STATUS_FAILED_PRECONDITION, error_message,
      "Checking tag failed"));
  ASSERT_EQ(memcmp(data_buffer, zero_buffer, data_size), 0);
  gpr_free(error_message);
  gpr_free(data_buffer);
  gpr_free(zero_buffer);
}

static void alts_crypter_test_input_sanity_check(alts_crypter* crypter_seal,
                                                 alts_crypter* crypter_unseal) {
  size_t data_size = gsec_test_bias_random_uint32(1024) + 1;
  size_t num_overhead_bytes = alts_crypter_num_overhead_bytes(crypter_seal);
  size_t protected_data_size = data_size + num_overhead_bytes;
  auto* data_buffer = static_cast<uint8_t*>(gpr_malloc(protected_data_size));
  gsec_test_random_bytes(data_buffer, data_size);
  char* error_message = nullptr;
  size_t size = data_size;

  grpc_status_code status = alts_crypter_process_in_place(
      nullptr, data_buffer, protected_data_size, size, &size, &error_message);
  ASSERT_TRUE(gsec_test_expect_compare_code_and_substr(
      status, GRPC_STATUS_INVALID_ARGUMENT, error_message,
      "crypter or crypter->vtable has not been initialized properly."));
  gpr_free(error_message);

  size = data_size;
  status = alts_crypter_process_in_place(
      crypter_seal, nullptr, protected_data_size, size, &size, &error_message);
  ASSERT_TRUE(gsec_test_expect_compare_code_and_substr(
      status, GRPC_STATUS_INVALID_ARGUMENT, error_message, "data is nullptr."));
  gpr_free(error_message);

  size = 0;
  status = alts_crypter_process_in_place(crypter_seal, data_buffer,
                                         protected_data_size, size, &size,
                                         &error_message);
  ASSERT_TRUE(gsec_test_expect_compare_code_and_substr(
      status, GRPC_STATUS_INVALID_ARGUMENT, error_message,
      "data_size is zero."));
  gpr_free(error_message);

  size = data_size;
  status = alts_crypter_process_in_place(crypter_seal, data_buffer,
                                         protected_data_size - 1, size, &size,
                                         &error_message);
  ASSERT_TRUE(gsec_test_expect_compare_code_and_substr(
      status, GRPC_STATUS_INVALID_ARGUMENT, error_message,
      "data_allocated_size is smaller than sum of data_size and "
      "num_overhead_bytes."));
  gpr_free(error_message);

  size = data_size;
  status = alts_crypter_process_in_place(crypter_unseal, nullptr,
                                         protected_data_size, size, &size,
                                         &error_message);
  ASSERT_TRUE(gsec_test_expect_compare_code_and_substr(
      status, GRPC_STATUS_INVALID_ARGUMENT, error_message, "data is nullptr."));
  gpr_free(error_message);

  size = 0;
  status = alts_crypter_process_in_place(crypter_unseal, data_buffer,
                                         protected_data_size, size, &size,
                                         &error_message);
  ASSERT_TRUE(gsec_test_expect_compare_code_and_substr(
      status, GRPC_STATUS_INVALID_ARGUMENT, error_message,
      "data_size is smaller than num_overhead_bytes."));
  gpr_free(error_message);

  size = num_overhead_bytes - 1;
  status = alts_crypter_process_in_place(crypter_unseal, data_buffer,
                                         protected_data_size, size, &size,
                                         &error_message);
  ASSERT_TRUE(gsec_test_expect_compare_code_and_substr(
      status, GRPC_STATUS_INVALID_ARGUMENT, error_message,
      "data_size is smaller than num_overhead_bytes."));
  gpr_free(error_message);
  gpr_free(data_buffer);
}

static void create_random_alts_seal_crypter(
    alts_crypter** server_seal, alts_crypter** server_unseal,
    alts_crypter** client_seal, alts_crypter** client_unseal,
    gsec_aead_crypter** server_crypter_seal,
    gsec_aead_crypter** server_crypter_unseal,
    gsec_aead_crypter** client_crypter_seal,
    gsec_aead_crypter** client_crypter_unseal, bool rekey) {
  size_t key_length = rekey ? kAes128GcmRekeyKeyLength : kAes128GcmKeyLength;
  uint8_t* key;
  gsec_test_random_array(&key, key_length);
  ASSERT_EQ(gsec_aes_gcm_aead_crypter_create(
                std::make_unique<grpc_core::GsecKey>(
                    absl::MakeConstSpan(key, key_length), rekey),
                kAesGcmNonceLength, kAesGcmTagLength, server_crypter_seal,
                nullptr),
            GRPC_STATUS_OK);
  ASSERT_EQ(gsec_aes_gcm_aead_crypter_create(
                std::make_unique<grpc_core::GsecKey>(
                    absl::MakeConstSpan(key, key_length), rekey),
                kAesGcmNonceLength, kAesGcmTagLength, server_crypter_unseal,
                nullptr),
            GRPC_STATUS_OK);
  ASSERT_EQ(gsec_aes_gcm_aead_crypter_create(
                std::make_unique<grpc_core::GsecKey>(
                    absl::MakeConstSpan(key, key_length), rekey),
                kAesGcmNonceLength, kAesGcmTagLength, client_crypter_seal,
                nullptr),
            GRPC_STATUS_OK);
  ASSERT_EQ(gsec_aes_gcm_aead_crypter_create(
                std::make_unique<grpc_core::GsecKey>(
                    absl::MakeConstSpan(key, key_length), rekey),
                kAesGcmNonceLength, kAesGcmTagLength, client_crypter_unseal,
                nullptr),
            GRPC_STATUS_OK);

  size_t overflow_size = rekey ? 8 : 5;
  ASSERT_EQ(alts_seal_crypter_create(*client_crypter_seal, true,
                                     overflow_size, client_seal,
                                     nullptr),
            GRPC_STATUS_OK);
  ASSERT_EQ(alts_unseal_crypter_create(
                *client_crypter_unseal, true, overflow_size,
                client_unseal, nullptr),
            GRPC_STATUS_OK);
  ASSERT_EQ(alts_seal_crypter_create(*server_crypter_seal, false,
                                     overflow_size, server_seal,
                                     nullptr),
            GRPC_STATUS_OK);
  ASSERT_EQ(alts_unseal_crypter_create(
                *server_crypter_unseal, false, overflow_size,
                server_unseal, nullptr),
            GRPC_STATUS_OK);
  gpr_free(key);
}

static void destroy_random_alts_seal_crypter(alts_crypter* server_seal,
                                             alts_crypter* server_unseal,
                                             alts_crypter* client_seal,
                                             alts_crypter* client_unseal) {
  alts_crypter_destroy(server_seal);
  alts_crypter_destroy(server_unseal);
  alts_crypter_destroy(client_seal);
  alts_crypter_destroy(client_unseal);
}

TEST(AltsCrypterTest, AltsCrypterDoGenericTests) {
  alts_crypter *server_seal = nullptr, *server_unseal = nullptr,
               *client_seal = nullptr, *client_unseal = nullptr;
  gsec_aead_crypter *server_crypter_seal = nullptr,
                    *server_crypter_unseal = nullptr,
                    *client_crypter_seal = nullptr,
                    *client_crypter_unseal = nullptr;

  create_random_alts_seal_crypter(&server_seal, &server_unseal, &client_seal,
                                  &client_unseal, &server_crypter_seal,
                                  &server_crypter_unseal, &client_crypter_seal,
                                  &client_crypter_unseal, false);
  alts_crypter_test_random_seal_unseal(server_seal, server_unseal, client_seal,
                                       client_unseal);
  destroy_random_alts_seal_crypter(server_seal, server_unseal, client_seal,
                                   client_unseal);

  create_random_alts_seal_crypter(&server_seal, &server_unseal, &client_seal,
                                  &client_unseal, &server_crypter_seal,
                                  &server_crypter_unseal, &client_crypter_seal,
                                  &client_crypter_unseal, true);
  alts_crypter_test_random_seal_unseal(server_seal, server_unseal, client_seal,
                                       client_unseal);
  destroy_random_alts_seal_crypter(server_seal, server_unseal, client_seal,
                                   client_unseal);

  create_random_alts_seal_crypter(&server_seal, &server_unseal, &client_seal,
                                  &client_unseal, &server_crypter_seal,
                                  &server_crypter_unseal, &client_crypter_seal,
                                  &client_crypter_unseal, false);
  alts_crypter_test_multiple_random_seal_unseal(server_seal, server_unseal,
                                                client_seal, client_unseal);
  destroy_random_alts_seal_crypter(server_seal, server_unseal, client_seal,
                                   client_unseal);

  create_random_alts_seal_crypter(&server_seal, &server_unseal, &client_seal,
                                  &client_unseal, &server_crypter_seal,
                                  &server_crypter_unseal, &client_crypter_seal,
                                  &client_crypter_unseal, true);
  alts_crypter_test_multiple_random_seal_unseal(server_seal, server_unseal,
                                                client_seal, client_unseal);
  destroy_random_alts_seal_crypter(server_seal, server_unseal, client_seal,
                                   client_unseal);

  create_random_alts_seal_crypter(&server_seal, &server_unseal, &client_seal,
                                  &client_unseal, &server_crypter_seal,
                                  &server_crypter_unseal, &client_crypter_seal,
                                  &client_crypter_unseal, false);
  alts_crypter_test_corrupted_unseal(server_seal, server_unseal, client_seal,
                                     client_unseal);
  destroy_random_alts_seal_crypter(server_seal, server_unseal, client_seal,
                                   client_unseal);

  create_random_alts_seal_crypter(&server_seal, &server_unseal, &client_seal,
                                  &client_unseal, &server_crypter_seal,
                                  &server_crypter_unseal, &client_crypter_seal,
                                  &client_crypter_unseal, true);
  alts_crypter_test_corrupted_unseal(server_seal, server_unseal, client_seal,
                                     client_unseal);
  destroy_random_alts_seal_crypter(server_seal, server_unseal, client_seal,
                                   client_unseal);

  create_random_alts_seal_crypter(&server_seal, &server_unseal, &client_seal,
                                  &client_unseal, &server_crypter_seal,
                                  &server_crypter_unseal, &client_crypter_seal,
                                  &client_crypter_unseal, false);
  alts_crypter_test_unsync_seal_unseal(server_seal, server_unseal, client_seal,
                                       client_unseal);
  destroy_random_alts_seal_crypter(server_seal, server_unseal, client_seal,
                                   client_unseal);

  create_random_alts_seal_crypter(&server_seal, &server_unseal, &client_seal,
                                  &client_unseal, &server_crypter_seal,
                                  &server_crypter_unseal, &client_crypter_seal,
                                  &client_crypter_unseal, true);
  alts_crypter_test_unsync_seal_unseal(server_seal, server_unseal, client_seal,
                                       client_unseal);
  destroy_random_alts_seal_crypter(server_seal, server_unseal, client_seal,
                                   client_unseal);

  create_random_alts_seal_crypter(&server_seal, &server_unseal, &client_seal,
                                  &client_unseal, &server_crypter_seal,
                                  &server_crypter_unseal, &client_crypter_seal,
                                  &client_crypter_unseal, false);
  alts_crypter_test_input_sanity_check(server_seal, server_unseal);
  destroy_random_alts_seal_crypter(server_seal, server_unseal, client_seal,
                                   client_unseal);

  create_random_alts_seal_crypter(&server_seal, &server_unseal, &client_seal,
                                  &client_unseal, &server_crypter_seal,
                                  &server_crypter_unseal, &client_crypter_seal,
                                  &client_crypter_unseal, true);
  alts_crypter_test_input_sanity_check(server_seal, server_unseal);
  destroy_random_alts_seal_crypter(server_seal, server_unseal, client_seal,
                                   client_unseal);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
