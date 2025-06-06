
// Copyright 2018 gRPC authors.

#include "src/core/tsi/alts/zero_copy_frame_protector/alts_iovec_record_protocol.h"

#include <grpc/support/alloc.h>
#include <grpc/support/port_platform.h>
#include <stdlib.h>
#include <string.h>

#include "src/core/tsi/alts/frame_protector/alts_counter.h"
#include "src/core/util/crash.h"

struct alts_iovec_record_protocol {
  alts_counter* ctr;
  gsec_aead_crypter* crypter;
  size_t tag_length;
  bool is_integrity_only;
  bool is_protect;
};

static void maybe_copy_error_msg(const char* src, char** dst) {
  if (dst != nullptr && src != nullptr) {
    *dst = static_cast<char*>(gpr_malloc(strlen(src) + 1));
    memcpy(*dst, src, strlen(src) + 1);
  }
}

static void maybe_append_error_msg(const char* appendix, char** dst) {
  if (dst != nullptr && appendix != nullptr) {
    int dst_len = static_cast<int>(strlen(*dst));
    *dst = static_cast<char*>(realloc(*dst, dst_len + strlen(appendix) + 1));
    assert(*dst != nullptr);
    memcpy(*dst + dst_len, appendix, strlen(appendix) + 1);
  }
}

static uint32_t load_32_le(const unsigned char* buffer) {
  return (static_cast<uint32_t>(buffer[3]) << 24) |
         (static_cast<uint32_t>(buffer[2]) << 16) |
         (static_cast<uint32_t>(buffer[1]) << 8) |
         static_cast<uint32_t>(buffer[0]);
}

static void store_32_le(uint32_t value, unsigned char* buffer) {
  buffer[3] = static_cast<unsigned char>(value >> 24) & 0xFF;
  buffer[2] = static_cast<unsigned char>(value >> 16) & 0xFF;
  buffer[1] = static_cast<unsigned char>(value >> 8) & 0xFF;
  buffer[0] = static_cast<unsigned char>(value) & 0xFF;
}

static grpc_status_code ensure_header_and_tag_length(
    const alts_iovec_record_protocol* rp, iovec_t header, iovec_t tag,
    char** error_details) {
  if (rp == nullptr) {
    return GRPC_STATUS_FAILED_PRECONDITION;
  }
  if (header.iov_base == nullptr) {
    maybe_copy_error_msg("Header is nullptr.", error_details);
    return GRPC_STATUS_INVALID_ARGUMENT;
  }
  if (header.iov_len != alts_iovec_record_protocol_get_header_length()) {
    maybe_copy_error_msg("Header length is incorrect.", error_details);
    return GRPC_STATUS_INVALID_ARGUMENT;
  }
  if (tag.iov_base == nullptr) {
    maybe_copy_error_msg("Tag is nullptr.", error_details);
    return GRPC_STATUS_INVALID_ARGUMENT;
  }
  if (tag.iov_len != rp->tag_length) {
    maybe_copy_error_msg("Tag length is incorrect.", error_details);
    return GRPC_STATUS_INVALID_ARGUMENT;
  }
  return GRPC_STATUS_OK;
}

static grpc_status_code increment_counter(alts_counter* counter,
                                          char** error_details) {
  if (counter == nullptr) {
    return GRPC_STATUS_FAILED_PRECONDITION;
  }
  bool is_overflow = false;
  grpc_status_code status =
      alts_counter_increment(counter, &is_overflow, error_details);
  if (status != GRPC_STATUS_OK) {
    return status;
  }
  if (is_overflow) {
    maybe_copy_error_msg("Crypter counter is overflowed.", error_details);
    return GRPC_STATUS_INTERNAL;
  }
  return GRPC_STATUS_OK;
}

static size_t get_total_length(const iovec_t* vec, size_t vec_length) {
  size_t total_length = 0;
  for (size_t i = 0; i < vec_length; ++i) {
    total_length += vec[i].iov_len;
  }
  return total_length;
}

static grpc_status_code write_frame_header(size_t data_length,
                                           unsigned char* header,
                                           char** error_details) {
  if (header == nullptr) {
    maybe_copy_error_msg("Header is nullptr.", error_details);
    return GRPC_STATUS_FAILED_PRECONDITION;
  }
  size_t frame_length = kZeroCopyFrameMessageTypeFieldSize + data_length;
  store_32_le(static_cast<uint32_t>(frame_length), header);
  store_32_le(kZeroCopyFrameMessageType,
              header + kZeroCopyFrameLengthFieldSize);
  return GRPC_STATUS_OK;
}

static grpc_status_code verify_frame_header(size_t data_length,
                                            unsigned char* header,
                                            char** error_details) {
  if (header == nullptr) {
    maybe_copy_error_msg("Header is nullptr.", error_details);
    return GRPC_STATUS_FAILED_PRECONDITION;
  }
  size_t frame_length = load_32_le(header);
  if (frame_length != kZeroCopyFrameMessageTypeFieldSize + data_length) {
    maybe_copy_error_msg("Bad frame length.", error_details);
    return GRPC_STATUS_INTERNAL;
  }
  size_t message_type = load_32_le(header + kZeroCopyFrameLengthFieldSize);
  if (message_type != kZeroCopyFrameMessageType) {
    maybe_copy_error_msg("Unsupported message type.", error_details);
    return GRPC_STATUS_INTERNAL;
  }
  return GRPC_STATUS_OK;
}

size_t alts_iovec_record_protocol_get_header_length() {
  return kZeroCopyFrameHeaderSize;
}

size_t alts_iovec_record_protocol_get_tag_length(
    const alts_iovec_record_protocol* rp) {
  if (rp != nullptr) {
    return rp->tag_length;
  }
  return 0;
}

size_t alts_iovec_record_protocol_max_unprotected_data_size(
    const alts_iovec_record_protocol* rp, size_t max_protected_frame_size) {
  if (rp == nullptr) {
    return 0;
  }
  size_t overhead_bytes_size =
      kZeroCopyFrameMessageTypeFieldSize + rp->tag_length;
  if (max_protected_frame_size <= overhead_bytes_size) return 0;
  return max_protected_frame_size - overhead_bytes_size;
}

grpc_status_code alts_iovec_record_protocol_integrity_only_protect(
    alts_iovec_record_protocol* rp, const iovec_t* unprotected_vec,
    size_t unprotected_vec_length, iovec_t header, iovec_t tag,
    char** error_details) {

  if (rp == nullptr) {
    maybe_copy_error_msg("Input iovec_record_protocol is nullptr.",
                         error_details);
    return GRPC_STATUS_INVALID_ARGUMENT;
  }
  if (!rp->is_integrity_only) {
    maybe_copy_error_msg(
        "Integrity-only operations are not allowed for this object.",
        error_details);
    return GRPC_STATUS_FAILED_PRECONDITION;
  }
  if (!rp->is_protect) {
    maybe_copy_error_msg("Protect operations are not allowed for this object.",
                         error_details);
    return GRPC_STATUS_FAILED_PRECONDITION;
  }
  grpc_status_code status =
      ensure_header_and_tag_length(rp, header, tag, error_details);
  if (status != GRPC_STATUS_OK) {
    return status;
  }

  size_t data_length =
      get_total_length(unprotected_vec, unprotected_vec_length);

  status = write_frame_header(data_length + rp->tag_length,
                              static_cast<unsigned char*>(header.iov_base),
                              error_details);
  if (status != GRPC_STATUS_OK) {
    return status;
  }

  size_t bytes_written = 0;
  status = gsec_aead_crypter_encrypt_iovec(
      rp->crypter, alts_counter_get_counter(rp->ctr),
      alts_counter_get_size(rp->ctr), unprotected_vec, unprotected_vec_length,
       nullptr,  0, tag,
      &bytes_written, error_details);
  if (status != GRPC_STATUS_OK) {
    return status;
  }
  if (bytes_written != rp->tag_length) {
    maybe_copy_error_msg("Bytes written expects to be the same as tag length.",
                         error_details);
    return GRPC_STATUS_INTERNAL;
  }

  return increment_counter(rp->ctr, error_details);
}

grpc_status_code alts_iovec_record_protocol_integrity_only_unprotect(
    alts_iovec_record_protocol* rp, const iovec_t* protected_vec,
    size_t protected_vec_length, iovec_t header, iovec_t tag,
    char** error_details) {

  if (rp == nullptr) {
    maybe_copy_error_msg("Input iovec_record_protocol is nullptr.",
                         error_details);
    return GRPC_STATUS_INVALID_ARGUMENT;
  }
  if (!rp->is_integrity_only) {
    maybe_copy_error_msg(
        "Integrity-only operations are not allowed for this object.",
        error_details);
    return GRPC_STATUS_FAILED_PRECONDITION;
  }
  if (rp->is_protect) {
    maybe_copy_error_msg(
        "Unprotect operations are not allowed for this object.", error_details);
    return GRPC_STATUS_FAILED_PRECONDITION;
  }
  grpc_status_code status =
      ensure_header_and_tag_length(rp, header, tag, error_details);
  if (status != GRPC_STATUS_OK) return status;

  size_t data_length = get_total_length(protected_vec, protected_vec_length);

  status = verify_frame_header(data_length + rp->tag_length,
                               static_cast<unsigned char*>(header.iov_base),
                               error_details);
  if (status != GRPC_STATUS_OK) {
    return status;
  }

  iovec_t plaintext = {nullptr, 0};
  size_t bytes_written = 0;
  status = gsec_aead_crypter_decrypt_iovec(
      rp->crypter, alts_counter_get_counter(rp->ctr),
      alts_counter_get_size(rp->ctr), protected_vec, protected_vec_length, &tag,
      1, plaintext, &bytes_written, error_details);
  if (status != GRPC_STATUS_OK || bytes_written != 0) {
    maybe_append_error_msg(" Frame tag verification failed.", error_details);
    return GRPC_STATUS_INTERNAL;
  }

  return increment_counter(rp->ctr, error_details);
}

grpc_status_code alts_iovec_record_protocol_privacy_integrity_protect(
    alts_iovec_record_protocol* rp, const iovec_t* unprotected_vec,
    size_t unprotected_vec_length, iovec_t protected_frame,
    char** error_details) {

  if (rp == nullptr) {
    maybe_copy_error_msg("Input iovec_record_protocol is nullptr.",
                         error_details);
    return GRPC_STATUS_INVALID_ARGUMENT;
  }
  if (rp->is_integrity_only) {
    maybe_copy_error_msg(
        "Privacy-integrity operations are not allowed for this object.",
        error_details);
    return GRPC_STATUS_FAILED_PRECONDITION;
  }
  if (!rp->is_protect) {
    maybe_copy_error_msg("Protect operations are not allowed for this object.",
                         error_details);
    return GRPC_STATUS_FAILED_PRECONDITION;
  }

  size_t data_length =
      get_total_length(unprotected_vec, unprotected_vec_length);

  if (protected_frame.iov_base == nullptr) {
    maybe_copy_error_msg("Protected frame is nullptr.", error_details);
    return GRPC_STATUS_INVALID_ARGUMENT;
  }
  if (protected_frame.iov_len !=
      alts_iovec_record_protocol_get_header_length() + data_length +
          rp->tag_length) {
    maybe_copy_error_msg("Protected frame size is incorrect.", error_details);
    return GRPC_STATUS_INVALID_ARGUMENT;
  }

  grpc_status_code status = write_frame_header(
      data_length + rp->tag_length,
      static_cast<unsigned char*>(protected_frame.iov_base), error_details);
  if (status != GRPC_STATUS_OK) {
    return status;
  }

  unsigned char* ciphertext_buffer =
      static_cast<unsigned char*>(protected_frame.iov_base) +
      alts_iovec_record_protocol_get_header_length();
  iovec_t ciphertext = {ciphertext_buffer, data_length + rp->tag_length};
  size_t bytes_written = 0;
  status = gsec_aead_crypter_encrypt_iovec(
      rp->crypter, alts_counter_get_counter(rp->ctr),
      alts_counter_get_size(rp->ctr),  nullptr,
       0, unprotected_vec, unprotected_vec_length,
      ciphertext, &bytes_written, error_details);
  if (status != GRPC_STATUS_OK) {
    return status;
  }
  if (bytes_written != data_length + rp->tag_length) {
    maybe_copy_error_msg(
        "Bytes written expects to be data length plus tag length.",
        error_details);
    return GRPC_STATUS_INTERNAL;
  }

  return increment_counter(rp->ctr, error_details);
}

grpc_status_code alts_iovec_record_protocol_privacy_integrity_unprotect(
    alts_iovec_record_protocol* rp, iovec_t header,
    const iovec_t* protected_vec, size_t protected_vec_length,
    iovec_t unprotected_data, char** error_details) {

  if (rp == nullptr) {
    maybe_copy_error_msg("Input iovec_record_protocol is nullptr.",
                         error_details);
    return GRPC_STATUS_INVALID_ARGUMENT;
  }
  if (rp->is_integrity_only) {
    maybe_copy_error_msg(
        "Privacy-integrity operations are not allowed for this object.",
        error_details);
    return GRPC_STATUS_FAILED_PRECONDITION;
  }
  if (rp->is_protect) {
    maybe_copy_error_msg(
        "Unprotect operations are not allowed for this object.", error_details);
    return GRPC_STATUS_FAILED_PRECONDITION;
  }

  size_t protected_data_length =
      get_total_length(protected_vec, protected_vec_length);
  if (protected_data_length < rp->tag_length) {
    maybe_copy_error_msg(
        "Protected data length should be more than the tag length.",
        error_details);
    return GRPC_STATUS_INVALID_ARGUMENT;
  }

  if (header.iov_base == nullptr) {
    maybe_copy_error_msg("Header is nullptr.", error_details);
    return GRPC_STATUS_INVALID_ARGUMENT;
  }
  if (header.iov_len != alts_iovec_record_protocol_get_header_length()) {
    maybe_copy_error_msg("Header length is incorrect.", error_details);
    return GRPC_STATUS_INVALID_ARGUMENT;
  }

  if (unprotected_data.iov_len != protected_data_length - rp->tag_length) {
    maybe_copy_error_msg("Unprotected data size is incorrect.", error_details);
    return GRPC_STATUS_INVALID_ARGUMENT;
  }

  grpc_status_code status = verify_frame_header(
      protected_data_length, static_cast<unsigned char*>(header.iov_base),
      error_details);
  if (status != GRPC_STATUS_OK) {
    return status;
  }

  size_t bytes_written = 0;
  status = gsec_aead_crypter_decrypt_iovec(
      rp->crypter, alts_counter_get_counter(rp->ctr),
      alts_counter_get_size(rp->ctr),  nullptr,
       0, protected_vec, protected_vec_length,
      unprotected_data, &bytes_written, error_details);
  if (status != GRPC_STATUS_OK) {
    maybe_append_error_msg(" Frame decryption failed.", error_details);
    return GRPC_STATUS_INTERNAL;
  }
  if (bytes_written != protected_data_length - rp->tag_length) {
    maybe_copy_error_msg(
        "Bytes written expects to be protected data length minus tag length.",
        error_details);
    return GRPC_STATUS_INTERNAL;
  }

  return increment_counter(rp->ctr, error_details);
}

grpc_status_code alts_iovec_record_protocol_create(
    gsec_aead_crypter* crypter, size_t overflow_size, bool is_client,
    bool is_integrity_only, bool is_protect, alts_iovec_record_protocol** rp,
    char** error_details) {
  if (crypter == nullptr || rp == nullptr) {
    maybe_copy_error_msg(
        "Invalid nullptr arguments to alts_iovec_record_protocol create.",
        error_details);
    return GRPC_STATUS_INVALID_ARGUMENT;
  }
  alts_iovec_record_protocol* impl = static_cast<alts_iovec_record_protocol*>(
      gpr_zalloc(sizeof(alts_iovec_record_protocol)));

  size_t counter_length = 0;
  grpc_status_code status =
      gsec_aead_crypter_nonce_length(crypter, &counter_length, error_details);
  if (status != GRPC_STATUS_OK) {
    goto cleanup;
  }

  status =
      alts_counter_create(is_protect ? !is_client : is_client, counter_length,
                          overflow_size, &impl->ctr, error_details);
  if (status != GRPC_STATUS_OK) {
    goto cleanup;
  }

  status =
      gsec_aead_crypter_tag_length(crypter, &impl->tag_length, error_details);
  if (status != GRPC_STATUS_OK) {
    goto cleanup;
  }
  impl->crypter = crypter;
  impl->is_integrity_only = is_integrity_only;
  impl->is_protect = is_protect;
  *rp = impl;
  return GRPC_STATUS_OK;
cleanup:
  alts_counter_destroy(impl->ctr);
  gpr_free(impl);
  return GRPC_STATUS_FAILED_PRECONDITION;
}

void alts_iovec_record_protocol_destroy(alts_iovec_record_protocol* rp) {
  if (rp != nullptr) {
    alts_counter_destroy(rp->ctr);
    gsec_aead_crypter_destroy(rp->crypter);
    gpr_free(rp);
  }
}
