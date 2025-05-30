
// Copyright 2018 gRPC authors.

#ifndef GRPC_SRC_CORE_TSI_ALTS_CRYPT_GSEC_H
#define GRPC_SRC_CORE_TSI_ALTS_CRYPT_GSEC_H

#include <assert.h>
#include <grpc/event_engine/port.h>
#include <grpc/grpc.h>
#include <grpc/support/port_platform.h>
#include <stdint.h>
#include <stdlib.h>

#include <memory>
#include <vector>

#include "absl/types/span.h"

namespace grpc_core {

class GsecKeyInterface {
 public:
  virtual ~GsecKeyInterface() = default;

  virtual bool IsRekey() = 0;
  virtual absl::Span<const uint8_t> key() = 0;

  virtual absl::Span<uint8_t> aead_key() = 0;
  virtual absl::Span<const uint8_t> nonce_mask() = 0;
  virtual absl::Span<uint8_t> kdf_counter() = 0;
  virtual absl::Span<uint8_t> kdf_buffer() = 0;
};

class GsecKeyFactoryInterface {
 public:
  virtual ~GsecKeyFactoryInterface() = default;

  virtual std::unique_ptr<GsecKeyInterface> Create() const = 0;
};

class GsecKeyFactory : public GsecKeyFactoryInterface {
 public:

  GsecKeyFactory(absl::Span<const uint8_t> key, bool is_rekey);
  ~GsecKeyFactory() override = default;

  std::unique_ptr<GsecKeyInterface> Create() const override;

 private:
  std::vector<uint8_t> key_;
  bool is_rekey_;
};

class GsecKey : public GsecKeyInterface {
 public:

  GsecKey(absl::Span<const uint8_t> key, bool is_rekey);
  ~GsecKey() override = default;

  bool IsRekey() override;
  absl::Span<const uint8_t> key() override;
  absl::Span<uint8_t> aead_key() override;
  absl::Span<const uint8_t> nonce_mask() override;
  absl::Span<uint8_t> kdf_counter() override;
  absl::Span<uint8_t> kdf_buffer() override;

 private:
  bool is_rekey_;
  std::vector<uint8_t> key_;
  std::vector<uint8_t> aead_key_;
  std::vector<uint8_t> kdf_buffer_;
  std::vector<uint8_t> nonce_mask_;
  std::vector<uint8_t> kdf_counter_;
};

}

#ifndef _STRUCT_IOVEC
#if !defined(GRPC_EVENT_ENGINE_POSIX)
struct iovec {
  void* iov_base;
  size_t iov_len;
};
#endif
#endif

const size_t kAesGcmNonceLength = 12;
const size_t kAesGcmTagLength = 16;
const size_t kAes128GcmKeyLength = 16;
const size_t kAes256GcmKeyLength = 32;

const size_t kAes128GcmRekeyKeyLength = 44;

typedef struct gsec_aead_crypter gsec_aead_crypter;

typedef struct gsec_aead_crypter_vtable {
  grpc_status_code (*encrypt_iovec)(
      gsec_aead_crypter* crypter, const uint8_t* nonce, size_t nonce_length,
      const struct iovec* aad_vec, size_t aad_vec_length,
      const struct iovec* plaintext_vec, size_t plaintext_vec_length,
      struct iovec ciphertext_vec, size_t* ciphertext_bytes_written,
      char** error_details);
  grpc_status_code (*decrypt_iovec)(
      gsec_aead_crypter* crypter, const uint8_t* nonce, size_t nonce_length,
      const struct iovec* aad_vec, size_t aad_vec_length,
      const struct iovec* ciphertext_vec, size_t ciphertext_vec_length,
      struct iovec plaintext_vec, size_t* plaintext_bytes_written,
      char** error_details);
  grpc_status_code (*max_ciphertext_and_tag_length)(
      const gsec_aead_crypter* crypter, size_t plaintext_length,
      size_t* max_ciphertext_and_tag_length_to_return, char** error_details);
  grpc_status_code (*max_plaintext_length)(
      const gsec_aead_crypter* crypter, size_t ciphertext_and_tag_length,
      size_t* max_plaintext_length_to_return, char** error_details);
  grpc_status_code (*nonce_length)(const gsec_aead_crypter* crypter,
                                   size_t* nonce_length_to_return,
                                   char** error_details);
  grpc_status_code (*key_length)(const gsec_aead_crypter* crypter,
                                 size_t* key_length_to_return,
                                 char** error_details);
  grpc_status_code (*tag_length)(const gsec_aead_crypter* crypter,
                                 size_t* tag_length_to_return,
                                 char** error_details);
  void (*destruct)(gsec_aead_crypter* crypter);
} gsec_aead_crypter_vtable;

struct gsec_aead_crypter {
  const struct gsec_aead_crypter_vtable* vtable;
};

grpc_status_code gsec_aead_crypter_encrypt(
    gsec_aead_crypter* crypter, const uint8_t* nonce, size_t nonce_length,
    const uint8_t* aad, size_t aad_length, const uint8_t* plaintext,
    size_t plaintext_length, uint8_t* ciphertext_and_tag,
    size_t ciphertext_and_tag_length, size_t* bytes_written,
    char** error_details);

grpc_status_code gsec_aead_crypter_encrypt_iovec(
    gsec_aead_crypter* crypter, const uint8_t* nonce, size_t nonce_length,
    const struct iovec* aad_vec, size_t aad_vec_length,
    const struct iovec* plaintext_vec, size_t plaintext_vec_length,
    struct iovec ciphertext_vec, size_t* ciphertext_bytes_written,
    char** error_details);

grpc_status_code gsec_aead_crypter_decrypt(
    gsec_aead_crypter* crypter, const uint8_t* nonce, size_t nonce_length,
    const uint8_t* aad, size_t aad_length, const uint8_t* ciphertext_and_tag,
    size_t ciphertext_and_tag_length, uint8_t* plaintext,
    size_t plaintext_length, size_t* bytes_written, char** error_details);

grpc_status_code gsec_aead_crypter_decrypt_iovec(
    gsec_aead_crypter* crypter, const uint8_t* nonce, size_t nonce_length,
    const struct iovec* aad_vec, size_t aad_vec_length,
    const struct iovec* ciphertext_vec, size_t ciphertext_vec_length,
    struct iovec plaintext_vec, size_t* plaintext_bytes_written,
    char** error_details);

grpc_status_code gsec_aead_crypter_max_ciphertext_and_tag_length(
    const gsec_aead_crypter* crypter, size_t plaintext_length,
    size_t* max_ciphertext_and_tag_length_to_return, char** error_details);

grpc_status_code gsec_aead_crypter_max_plaintext_length(
    const gsec_aead_crypter* crypter, size_t ciphertext_and_tag_length,
    size_t* max_plaintext_length_to_return, char** error_details);

grpc_status_code gsec_aead_crypter_nonce_length(
    const gsec_aead_crypter* crypter, size_t* nonce_length_to_return,
    char** error_details);

grpc_status_code gsec_aead_crypter_key_length(const gsec_aead_crypter* crypter,
                                              size_t* key_length_to_return,
                                              char** error_details);

grpc_status_code gsec_aead_crypter_tag_length(const gsec_aead_crypter* crypter,
                                              size_t* tag_length_to_return,
                                              char** error_details);

void gsec_aead_crypter_destroy(gsec_aead_crypter* crypter);

grpc_status_code gsec_aes_gcm_aead_crypter_create(
    std::unique_ptr<grpc_core::GsecKeyInterface> key, size_t nonce_length,
    size_t tag_length, gsec_aead_crypter** crypter, char** error_details);

#endif
