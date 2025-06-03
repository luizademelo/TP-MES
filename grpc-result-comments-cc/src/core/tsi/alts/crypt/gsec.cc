Here's the commented version of the code:

```c++
// Copyright 2018 gRPC authors.

#include "src/core/tsi/alts/crypt/gsec.h"

#include <grpc/support/alloc.h>
#include <grpc/support/port_platform.h>
#include <stdio.h>
#include <string.h>

// Error message for uninitialized crypter or vtable
static const char vtable_error_msg[] =
    "crypter or crypter->vtable has not been initialized properly";

// Helper function to copy error messages to the provided destination
// Args:
//   src: Source error message to copy
//   dst: Destination pointer where the error message will be copied
static void maybe_copy_error_msg(const char* src, char** dst) {
  if (dst != nullptr && src != nullptr) {
    *dst = static_cast<char*>(gpr_malloc(strlen(src) + 1));
    memcpy(*dst, src, strlen(src) + 1);
  }
}

// Encrypts plaintext using AEAD (Authenticated Encryption with Additional Data)
// Args:
//   crypter: AEAD crypter instance
//   nonce: Nonce/IV for encryption
//   nonce_length: Length of nonce
//   aad: Additional authenticated data
//   aad_length: Length of AAD
//   plaintext: Data to encrypt
//   plaintext_length: Length of plaintext
//   ciphertext_and_tag: Output buffer for ciphertext + authentication tag
//   ciphertext_and_tag_length: Length of output buffer
//   bytes_written: Output parameter for actual bytes written
//   error_details: Output parameter for error details
// Returns:
//   GRPC status code indicating success or failure
grpc_status_code gsec_aead_crypter_encrypt(
    gsec_aead_crypter* crypter, const uint8_t* nonce, size_t nonce_length,
    const uint8_t* aad, size_t aad_length, const uint8_t* plaintext,
    size_t plaintext_length, uint8_t* ciphertext_and_tag,
    size_t ciphertext_and_tag_length, size_t* bytes_written,
    char** error_details) {
  if (crypter != nullptr && crypter->vtable != nullptr &&
      crypter->vtable->encrypt_iovec != nullptr) {
    // Prepare I/O vectors for AAD, plaintext, and ciphertext
    struct iovec aad_vec = {const_cast<uint8_t*>(aad), aad_length};
    struct iovec plaintext_vec = {const_cast<uint8_t*>(plaintext),
                                  plaintext_length};
    struct iovec ciphertext_vec = {ciphertext_and_tag,
                                   ciphertext_and_tag_length};
    // Delegate to vtable implementation
    return crypter->vtable->encrypt_iovec(
        crypter, nonce, nonce_length, &aad_vec, 1, &plaintext_vec, 1,
        ciphertext_vec, bytes_written, error_details);
  }

  maybe_copy_error_msg(vtable_error_msg, error_details);
  return GRPC_STATUS_INVALID_ARGUMENT;
}

// Encrypts plaintext using AEAD with I/O vector interface
// Args:
//   crypter: AEAD crypter instance
//   nonce: Nonce/IV for encryption
//   nonce_length: Length of nonce
//   aad_vec: Array of I/O vectors for additional authenticated data
//   aad_vec_length: Number of AAD I/O vectors
//   plaintext_vec: Array of I/O vectors for plaintext
//   plaintext_vec_length: Number of plaintext I/O vectors
//   ciphertext_vec: I/O vector for ciphertext output
//   ciphertext_bytes_written: Output parameter for bytes written
//   error_details: Output parameter for error details
// Returns:
//   GRPC status code indicating success or failure
grpc_status_code gsec_aead_crypter_encrypt_iovec(
    gsec_aead_crypter* crypter, const uint8_t* nonce, size_t nonce_length,
    const struct iovec* aad_vec, size_t aad_vec_length,
    const struct iovec* plaintext_vec, size_t plaintext_vec_length,
    struct iovec ciphertext_vec, size_t* ciphertext_bytes_written,
    char** error_details) {
  if (crypter != nullptr && crypter->vtable != nullptr &&
      crypter->vtable->encrypt_iovec != nullptr) {
    return crypter->vtable->encrypt_iovec(
        crypter, nonce, nonce_length, aad_vec, aad_vec_length, plaintext_vec,
        plaintext_vec_length, ciphertext_vec, ciphertext_bytes_written,
        error_details);
  }

  maybe_copy_error_msg(vtable_error_msg, error_details);
  return GRPC_STATUS_INVALID_ARGUMENT;
}

// Decrypts ciphertext using AEAD (Authenticated Encryption with Additional Data)
// Args:
//   crypter: AEAD crypter instance
//   nonce: Nonce/IV used for encryption
//   nonce_length: Length of nonce
//   aad: Additional authenticated data
//   aad_length: Length of AAD
//   ciphertext_and_tag: Ciphertext + authentication tag to decrypt
//   ciphertext_and_tag_length: Length of ciphertext + tag
//   plaintext: Output buffer for decrypted data
//   plaintext_length: Length of plaintext buffer
//   bytes_written: Output parameter for actual bytes written
//   error_details: Output parameter for error details
// Returns:
//   GRPC status code indicating success or failure
grpc_status_code gsec_aead_crypter_decrypt(
    gsec_aead_crypter* crypter, const uint8_t* nonce, size_t nonce_length,
    const uint8_t* aad, size_t aad_length, const uint8_t* ciphertext_and_tag,
    size_t ciphertext_and_tag_length, uint8_t* plaintext,
    size_t plaintext_length, size_t* bytes_written, char** error_details) {
  if (crypter != nullptr && crypter->vtable != nullptr &&
      crypter->vtable->decrypt_iovec != nullptr) {
    // Prepare I/O vectors for AAD, ciphertext, and plaintext
    struct iovec aad_vec = {const_cast<uint8_t*>(aad), aad_length};
    struct iovec ciphertext_vec = {const_cast<uint8_t*>(ciphertext_and_tag),
                                   ciphertext_and_tag_length};
    struct iovec plaintext_vec = {plaintext, plaintext_length};
    // Delegate to vtable implementation
    return crypter->vtable->decrypt_iovec(
        crypter, nonce, nonce_length, &aad_vec, 1, &ciphertext_vec, 1,
        plaintext_vec, bytes_written, error_details);
  }

  maybe_copy_error_msg(vtable_error_msg, error_details);
  return GRPC_STATUS_INVALID_ARGUMENT;
}

// Decrypts ciphertext using AEAD with I/O vector interface
// Args:
//   crypter: AEAD crypter instance
//   nonce: Nonce/IV used for encryption
//   nonce_length: Length of nonce
//   aad_vec: Array of I/O vectors for additional authenticated data
//   aad_vec_length: Number of AAD I/O vectors
//   ciphertext_vec: Array of I/O vectors for ciphertext + tag
//   ciphertext_vec_length: Number of ciphertext I/O vectors
//   plaintext_vec: I/O vector for plaintext output
//   plaintext_bytes_written: Output parameter for bytes written
//   error_details: Output parameter for error details
// Returns:
//   GRPC status code indicating success or failure
grpc_status_code gsec_aead_crypter_decrypt_iovec(
    gsec_aead_crypter* crypter, const uint8_t* nonce, size_t nonce_length,
    const struct iovec* aad_vec, size_t aad_vec_length,
    const struct iovec* ciphertext_vec, size_t ciphertext_vec_length,
    struct iovec plaintext_vec, size_t* plaintext_bytes_written,
    char** error_details) {
  if (crypter != nullptr && crypter->vtable != nullptr &&
      crypter->vtable->encrypt_iovec != nullptr) {
    return crypter->vtable->decrypt_iovec(
        crypter, nonce, nonce_length, aad_vec, aad_vec_length, ciphertext_vec,
        ciphertext_vec_length, plaintext_vec, plaintext_bytes_written,
        error_details);
  }

  maybe_copy_error_msg(vtable_error_msg, error_details);
  return GRPC_STATUS_INVALID_ARGUMENT;
}

// Gets maximum ciphertext length (including tag) for given plaintext length
// Args:
//   crypter: AEAD crypter instance
//   plaintext_length: Length of plaintext
//   max_ciphertext_and_tag_length_to_return: Output parameter for max length
//   error_details: Output parameter for error details
// Returns:
//   GRPC status code indicating success or failure
grpc_status_code gsec_aead_crypter_max_ciphertext_and_tag_length(
    const gsec_aead_crypter* crypter, size_t plaintext_length,
    size_t* max_ciphertext_and_tag_length_to_return, char** error_details) {
  if (crypter != nullptr && crypter->vtable != nullptr &&
      crypter->vtable->max_ciphertext_and_tag_length != nullptr) {
    return crypter->vtable->max_ciphertext_and_tag_length(
        crypter, plaintext_length, max_ciphertext_and_tag_length_to_return,
        error_details);
  }

  maybe_copy_error_msg(vtable_error_msg, error_details);
  return GRPC_STATUS_INVALID_ARGUMENT;
}

// Gets maximum plaintext length for given ciphertext length (including tag)
// Args:
//   crypter: AEAD crypter instance
//   ciphertext_and_tag_length: Length of ciphertext + tag
//   max_plaintext_length_to_return: Output parameter for max length
//   error_details: Output parameter for error details
// Returns:
//   GRPC status code indicating success or failure
grpc_status_code gsec_aead_crypter_max_plaintext_length(
    const gsec_aead_crypter* crypter, size_t ciphertext_and_tag_length,
    size_t* max_plaintext_length_to_return, char** error_details) {
  if (crypter != nullptr && crypter->vtable != nullptr &&
      crypter->vtable->max_plaintext_length != nullptr) {
    return crypter->vtable->max_plaintext_length(
        crypter, ciphertext_and_tag_length, max_plaintext_length_to_return,
        error_details);
  }

  maybe_copy_error_msg(vtable_error_msg, error_details);
  return GRPC_STATUS_INVALID_ARGUMENT;
}

// Gets the nonce length required by the crypter
// Args:
//   crypter: AEAD crypter instance
//   nonce_length_to_return: Output parameter for nonce length
//   error_details: Output parameter for error details
// Returns:
//   GRPC status code indicating success or failure
grpc_status_code gsec_aead_crypter_nonce_length(
    const gsec_aead_crypter* crypter, size_t* nonce_length_to_return,
    char** error_details) {
  if (crypter != nullptr && crypter->vtable != nullptr &&
      crypter->vtable->nonce_length != nullptr) {
    return crypter->vtable->nonce_length(crypter, nonce_length_to_return,
                                         error_details);
  }

  maybe_copy_error_msg(vtable_error_msg, error_details);
  return GRPC_STATUS_INVALID_ARGUMENT;
}

// Gets the key length required by the crypter
// Args:
//   crypter: AEAD crypter instance
//   key_length_to_return: Output parameter for key length
//   error_details: Output parameter for error details
// Returns:
//   GRPC status code indicating success or failure
grpc_status_code gsec_aead_crypter_key_length(const gsec_aead_crypter* crypter,
                                              size_t* key_length_to_return,
                                              char** error_details) {
  if (crypter != nullptr && crypter->vtable != nullptr &&
      crypter->vtable->key_length != nullptr) {
    return crypter->vtable->key_length(crypter, key_length_to_return,
                                       error_details);
  }

  maybe_copy_error_msg(vtable_error_msg, error_details);
  return GRPC_STATUS_INVALID_ARGUMENT;
}

// Gets the authentication tag length used by the crypter
// Args:
//   crypter: AEAD crypter instance
//   tag_length_to_return: Output parameter for tag length
//   error_details: Output parameter for error details
// Returns:
//   GRPC status code indicating success or failure
grpc_status_code gsec_aead_crypter_tag_length(const gsec_aead_crypter* crypter,
                                              size_t* tag_length_to_return,
                                              char** error_details) {
  if (crypter != nullptr && crypter->vtable != nullptr &&
      crypter->vtable->tag_length != nullptr) {
    return crypter->vtable->tag_length(crypter, tag_length_to_return,
                                       error_details);
  }

  maybe_copy_error_msg(vtable_error_msg, error_details);
  return GRPC_STATUS_INVALID_ARGUMENT;
}

// Destroys and deallocates the AEAD crypter instance
// Args:
//   crypter: AEAD crypter instance to destroy
void gsec_aead_crypter_destroy(gsec_aead_crypter* crypter) {
  if (crypter != nullptr) {
    if (crypter->vtable != nullptr && crypter->vtable->destruct != nullptr) {
      crypter->vtable->destruct(crypter);
    }
    gpr_free(crypter);
  }
}
```