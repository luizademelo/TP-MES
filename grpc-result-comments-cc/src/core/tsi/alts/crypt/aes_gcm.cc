Here's the commented version of the code:

```c++
// Copyright 2018 gRPC authors.

// Include necessary headers for memory allocation, platform support,
// OpenSSL cryptographic operations, and string manipulation
#include <grpc/support/alloc.h>
#include <grpc/support/port_platform.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/hmac.h>
#include <string.h>

#include <memory>

// Include project-specific headers
#include "absl/types/span.h"
#include "src/core/tsi/alts/crypt/gsec.h"

// Constants for key derivation function parameters
constexpr size_t kKdfKeyLen = 32;
constexpr size_t kKdfCounterLen = 6;
constexpr size_t kKdfCounterOffset = 2;
constexpr size_t kRekeyAeadKeyLen = kAes128GcmKeyLength;

namespace grpc_core {

// GsecKeyFactory implementation
GsecKeyFactory::GsecKeyFactory(absl::Span<const uint8_t> key, bool is_rekey)
    : key_(key.begin(), key.end()), is_rekey_(is_rekey) {}

// Creates a new GsecKeyInterface instance
std::unique_ptr<GsecKeyInterface> GsecKeyFactory::Create() const {
  return std::make_unique<GsecKey>(key_, is_rekey_);
}

// GsecKey implementation
GsecKey::GsecKey(absl::Span<const uint8_t> key, bool is_rekey)
    : is_rekey_(is_rekey) {
  if (is_rekey_) {
    // Initialize buffers for rekey mode
    aead_key_.resize(kRekeyAeadKeyLen);
    kdf_buffer_.resize(EVP_MAX_MD_SIZE);
    nonce_mask_.resize(kAesGcmNonceLength);
    // Copy nonce mask from input key
    memcpy(nonce_mask_.data(), key.data() + kKdfKeyLen, kAesGcmNonceLength);
    // Initialize KDF counter
    kdf_counter_.resize(kKdfCounterLen, 0);
  }
  // Resize and copy the key
  key_.resize(is_rekey_ ? kKdfKeyLen : key.size());
  memcpy(key_.data(), key.data(), key_.size());
}

// Accessor methods
bool GsecKey::IsRekey() { return is_rekey_; }
absl::Span<const uint8_t> GsecKey::key() { return key_; }
absl::Span<const uint8_t> GsecKey::nonce_mask() { return nonce_mask_; }
absl::Span<uint8_t> GsecKey::kdf_counter() { return absl::MakeSpan(kdf_counter_); }
absl::Span<uint8_t> GsecKey::aead_key() { return absl::MakeSpan(aead_key_); }
absl::Span<uint8_t> GsecKey::kdf_buffer() { return absl::MakeSpan(kdf_buffer_); }

}  // namespace grpc_core

// OpenSSL version-specific constants
#if OPENSSL_VERSION_NUMBER >= 0x30000000L
const char kEvpMacAlgorithm[] = "HMAC";
char kEvpDigest[] = "SHA-256";
#endif

// Derives an AEAD key using HMAC-SHA256
static grpc_status_code aes_gcm_derive_aead_key(
    absl::Span<uint8_t> dst, uint8_t* buf, absl::Span<const uint8_t> kdf_key,
    absl::Span<const uint8_t> kdf_counter) {
  unsigned char ctr = 1;
  
  // Implementation for different OpenSSL versions
#if OPENSSL_VERSION_NUMBER < 0x10100000L
  // Legacy OpenSSL (<1.1.0) implementation
  HMAC_CTX hmac;
  HMAC_CTX_init(&hmac);
  if (!HMAC_Init_ex(&hmac, kdf_key.data(), kdf_key.size(), EVP_sha256(),
                    nullptr) ||
      !HMAC_Update(&hmac, kdf_counter.data(), kdf_counter.size()) ||
      !HMAC_Update(&hmac, &ctr, 1) || !HMAC_Final(&hmac, buf, nullptr)) {
    HMAC_CTX_cleanup(&hmac);
    return GRPC_STATUS_INTERNAL;
  }
  HMAC_CTX_cleanup(&hmac);
#elif OPENSSL_VERSION_NUMBER < 0x30000000L
  // OpenSSL 1.1.0+ implementation
  HMAC_CTX* hmac = HMAC_CTX_new();
  if (hmac == nullptr) {
    return GRPC_STATUS_INTERNAL;
  }
  if (!HMAC_Init_ex(hmac, kdf_key.data(), kdf_key.size(), EVP_sha256(),
                    nullptr) ||
      !HMAC_Update(hmac, kdf_counter.data(), kdf_counter.size()) ||
      !HMAC_Update(hmac, &ctr, 1) || !HMAC_Final(hmac, buf, nullptr)) {
    HMAC_CTX_free(hmac);
    return GRPC_STATUS_INTERNAL;
  }
  HMAC_CTX_free(hmac);
#else
  // OpenSSL 3.0+ implementation
  EVP_MAC* mac = EVP_MAC_fetch(nullptr, kEvpMacAlgorithm, nullptr);
  EVP_MAC_CTX* ctx = EVP_MAC_CTX_new(mac);
  if (ctx == nullptr) {
    return GRPC_STATUS_INTERNAL;
  }
  OSSL_PARAM params[2];
  params[0] = OSSL_PARAM_construct_utf8_string("digest", kEvpDigest, 0);
  params[1] = OSSL_PARAM_construct_end();

  if (!EVP_MAC_init(ctx, kdf_key.data(), kdf_key.size(), params) ||
      !EVP_MAC_update(ctx, kdf_counter.data(), kdf_counter.size()) ||
      !EVP_MAC_update(ctx, &ctr, 1) ||
      !EVP_MAC_final(ctx, buf, nullptr, EVP_MAX_MD_SIZE)) {
    EVP_MAC_CTX_free(ctx);
    EVP_MAC_free(mac);
    return GRPC_STATUS_INTERNAL;
  }
  EVP_MAC_CTX_free(ctx);
  EVP_MAC_free(mac);
#endif
  // Copy the derived key to destination
  memcpy(dst.data(), buf, dst.size());
  return GRPC_STATUS_OK;
}

// Structure for AES-GCM AEAD crypter
struct gsec_aes_gcm_aead_crypter {
  gsec_aead_crypter crypter;  // Base crypter interface
  size_t nonce_length;        // Length of nonce
  size_t tag_length;          // Length of authentication tag
  EVP_CIPHER_CTX* ctx;        // OpenSSL cipher context
  grpc_core::GsecKeyInterface* gsec_key;  // Key interface
};

// Gets OpenSSL error messages as a string
static char* aes_gcm_get_openssl_errors() {
  BIO* bio = BIO_new(BIO_s_mem());
  ERR_print_errors(bio);
  BUF_MEM* mem = nullptr;
  char* error_msg = nullptr;
  BIO_get_mem_ptr(bio, &mem);
  if (mem != nullptr) {
    error_msg = static_cast<char*>(gpr_malloc(mem->length + 1));
    memcpy(error_msg, mem->data, mem->length);
    error_msg[mem->length] = '\0';
  }
  BIO_free_all(bio);
  return error_msg;
}

// Formats error messages combining custom message with OpenSSL errors
static void aes_gcm_format_errors(const char* error_msg, char** error_details) {
  if (error_details == nullptr) {
    return;
  }
  unsigned long error = ERR_get_error();
  if (error == 0 && error_msg != nullptr) {
    *error_details = static_cast<char*>(gpr_malloc(strlen(error_msg) + 1));
    memcpy(*error_details, error_msg, strlen(error_msg) + 1);
    return;
  }
  char* openssl_errors = aes_gcm_get_openssl_errors();
  if (openssl_errors != nullptr && error_msg != nullptr) {
    size_t len = strlen(error_msg) + strlen(openssl_errors) + 2;
    *error_details = static_cast<char*>(gpr_malloc(len + 1));
    snprintf(*error_details, len + 1, "%s, %s", error_msg, openssl_errors);
    gpr_free(openssl_errors);
  }
}

// Calculates maximum ciphertext length for given plaintext
static grpc_status_code gsec_aes_gcm_aead_crypter_max_ciphertext_and_tag_length(
    const gsec_aead_crypter* crypter, size_t plaintext_length,
    size_t* max_ciphertext_and_tag_length, char** error_details) {
  if (max_ciphertext_and_tag_length == nullptr) {
    aes_gcm_format_errors("max_ciphertext_and_tag_length is nullptr.",
                          error_details);
    return GRPC_STATUS_INVALID_ARGUMENT;
  }
  gsec_aes_gcm_aead_crypter* aes_gcm_crypter =
      reinterpret_cast<gsec_aes_gcm_aead_crypter*>(
          const_cast<gsec_aead_crypter*>(crypter));
  *max_ciphertext_and_tag_length =
      plaintext_length + aes_gcm_crypter->tag_length;
  return GRPC_STATUS_OK;
}

// Calculates maximum plaintext length for given ciphertext
static grpc_status_code gsec_aes_gcm_aead_crypter_max_plaintext_length(
    const gsec_aead_crypter* crypter, size_t ciphertext_and_tag_length,
    size_t* max_plaintext_length, char** error_details) {
  if (max_plaintext_length == nullptr) {
    aes_gcm_format_errors("max_plaintext_length is nullptr.", error_details);
    return GRPC_STATUS_INVALID_ARGUMENT;
  }
  gsec_aes_gcm_aead_crypter* aes_gcm_crypter =
      reinterpret_cast<gsec_aes_gcm_aead_crypter*>(
          const_cast<gsec_aead_crypter*>(crypter));
  if (ciphertext_and_tag_length < aes_gcm_crypter->tag_length) {
    *max_plaintext_length = 0;
    aes_gcm_format_errors(
        "ciphertext_and_tag_length is smaller than tag_length.", error_details);
    return GRPC_STATUS_INVALID_ARGUMENT;
  }
  *max_plaintext_length =
      ciphertext_and_tag_length - aes_gcm_crypter->tag_length;
  return GRPC_STATUS_OK;
}

// Gets the nonce length
static grpc_status_code gsec_aes_gcm_aead_crypter_nonce_length(
    const gsec_aead_crypter* crypter, size_t* nonce_length,
    char** error_details) {
  if (nonce_length == nullptr) {
    aes_gcm_format_errors("nonce_length is nullptr.", error_details);
    return GRPC_STATUS_INVALID_ARGUMENT;
  }
  gsec_aes_gcm_aead_crypter* aes_gcm_crypter =
      reinterpret_cast<gsec_aes_gcm_aead_crypter*>(
          const_cast<gsec_aead_crypter*>(crypter));
  *nonce_length = aes_gcm_crypter->nonce_length;
  return GRPC_STATUS_OK;
}

// Gets the key length
static grpc_status_code gsec_aes_gcm_aead_crypter_key_length(
    const gsec_aead_crypter* crypter, size_t* key_length,
    char** error_details) {
  if (key_length == nullptr) {
    aes_gcm_format_errors("key_length is nullptr.", error_details);
    return GRPC_STATUS_INVALID_ARGUMENT;
  }
  gsec_aes_gcm_aead_crypter* aes_gcm_crypter =
      reinterpret_cast<gsec_aes_gcm_aead_crypter*>(
          const_cast<gsec_aead_crypter*>(crypter));
  *key_length = aes_gcm_crypter->gsec_key->key().size();
  return GRPC_STATUS_OK;
}

// Gets the tag length
static grpc_status_code gsec_aes_gcm_aead_crypter_tag_length(
    const gsec_aead_crypter* crypter, size_t* tag_length,
    char** error_details) {
  if (tag_length == nullptr) {
    aes_gcm_format_errors("tag_length is nullptr.", error_details);
    return GRPC_STATUS_INVALID_ARGUMENT;
  }
  gsec_aes_gcm_aead_crypter* aes_gcm_crypter =
      reinterpret_cast<gsec_aes_gcm_aead_crypter*>(
          const_cast<gsec_aead_crypter*>(crypter));
  *tag_length = aes_gcm_crypter->tag_length;
  return GRPC_STATUS_OK;
}

// Masks the nonce using XOR operation
static void aes_gcm_mask_nonce(uint8_t* dst, const uint8_t* nonce,
                               const uint8_t* mask) {
  uint64_t mask1;
  uint32_t mask2;
  memcpy(&mask1, mask, sizeof(mask1));
  memcpy(&mask2, mask + sizeof(mask1), sizeof(mask2));
  uint64_t nonce1;
  uint32_t nonce2;
  memcpy(&nonce1, nonce, sizeof(nonce1));
  memcpy(&nonce2, nonce + sizeof(nonce1), sizeof(nonce2));
  nonce1 ^= mask1;
  nonce2 ^= mask2;
  memcpy(dst, &nonce1, sizeof(nonce1));
  memcpy(dst + sizeof(nonce1), &nonce2, sizeof(nonce2));
}

// Performs rekeying if required
static grpc_status_code aes_gcm_rekey_if_required(
    gsec_aes_gcm_aead_crypter* aes_gcm_crypter, const uint8_t* nonce,
    char** error_details) {
  // Check if rekey is needed
  if (!aes_gcm_crypter->gsec_key->IsRekey() ||
      memcmp(aes_gcm_crypter->gsec_key->kdf_counter().data(),
             nonce + kKdfCounterOffset,
             aes_gcm_crypter->gsec_key->kdf_counter().size()) == 0) {
    return GRPC_STATUS_OK;
  }
  
  // Update counter and derive new key
  memcpy(aes_gcm_crypter->gsec_key->kdf_counter().data(),
         nonce + kKdfCounterOffset,
         aes_gcm_crypter->gsec_key->kdf_counter().size());
  if (aes_gcm_derive_aead_key(aes_gcm_crypter->gsec_key->aead_key(),
                              aes_gcm_crypter->gsec_key->kdf_buffer().data(),
                              aes_gcm_crypter->gsec_key->key(),
                              aes_gcm_crypter->gsec_key->kdf_counter()) !=
      GRPC_STATUS_OK) {
    aes_gcm_format_errors("Rekeying failed in key derivation.", error_details);
    return GRPC_STATUS_INTERNAL;
  }
  
  // Update cipher context with new key
  if (!EVP_DecryptInit_ex(aes_gcm_crypter->ctx, nullptr, nullptr,
                          aes_gcm_crypter->gsec_key->aead_key().data(),
                          nullptr)) {
    aes_gcm_format_errors("Rekeying failed in context update.", error_details);
    return GRPC_STATUS_INTERNAL;
  }
  return GRPC_STATUS_OK;
}

// Encrypts plaintext data in iovec format
static grpc_status_code gsec_aes_gcm_aead_crypter_encrypt_iovec(
    gsec_aead_crypter* crypter, const uint8_t* nonce, size_t nonce_length,
    const struct iovec* aad_vec, size_t aad_vec_length,
    const struct iovec* plaintext_vec, size_t plaintext_vec_length,
    struct iovec ciphertext_vec, size_t* ciphertext_bytes_written,
    char** error_details) {
  gsec_aes_gcm_aead_crypter* aes_gcm_crypter =
      reinterpret_cast<gsec_aes_gcm_aead_crypter*>(crypter);

  // Input validation
  if (nonce == nullptr) {
    aes_gcm_format_errors("Nonce buffer is nullptr.", error_details);
    return GRPC_STATUS_INVALID_ARGUMENT;
  }
  if (kAesGcmNonceLength != nonce_length) {
    aes_gcm_format_errors("Nonce buffer has the wrong length.", error_details);
    return GRPC_STATUS_INVALID_ARGUMENT;
  }
  if (aad_vec_length > 0 && aad_vec == nullptr) {
    aes_gcm_format_errors("Non-zero aad_vec_length but aad_vec is nullptr.",
                          error_details);
    return GRPC_STATUS_INVALID_ARGUMENT;
  }
  if (plaintext_vec_length > 0 && plaintext_vec == nullptr) {
    aes_gcm_format_errors(
        "Non-zero plaintext_vec_length but plaintext_vec is nullptr.",
        error_details);
    return GRPC_STATUS_INVALID_ARGUMENT;
  }
  if (ciphertext_bytes_written == nullptr) {
    aes_gcm_format_errors("bytes_written is nullptr.", error_details);
    return GRPC_STATUS_INVALID_ARGUMENT;
  }
  *ciphertext_bytes