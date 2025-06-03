Here's the commented version of the code:

```c++
// Copyright 2018 gRPC authors.

#include "src/core/tsi/alts/zero_copy_frame_protector/alts_grpc_privacy_integrity_record_protocol.h"

#include <grpc/support/alloc.h>
#include <grpc/support/port_platform.h>

#include "absl/log/log.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/lib/slice/slice_internal.h"
#include "src/core/tsi/alts/zero_copy_frame_protector/alts_grpc_record_protocol_common.h"
#include "src/core/tsi/alts/zero_copy_frame_protector/alts_iovec_record_protocol.h"
#include "src/core/util/crash.h"

/**
 * Protects data with both privacy (encryption) and integrity (authentication).
 * 
 * @param rp Pointer to the record protocol instance
 * @param unprotected_slices Buffer containing unprotected data to be protected
 * @param protected_slices Buffer to store the protected data
 * @return tsi_result TSI_OK on success, error code on failure
 */
static tsi_result alts_grpc_privacy_integrity_protect(
    alts_grpc_record_protocol* rp, grpc_slice_buffer* unprotected_slices,
    grpc_slice_buffer* protected_slices) {

  // Validate input parameters
  if (rp == nullptr || unprotected_slices == nullptr ||
      protected_slices == nullptr) {
    LOG(ERROR)
        << "Invalid nullptr arguments to alts_grpc_record_protocol protect.";
    return TSI_INVALID_ARGUMENT;
  }

  // Calculate required protected frame size (original data + header + auth tag)
  size_t protected_frame_size =
      unprotected_slices->length + rp->header_length +
      alts_iovec_record_protocol_get_tag_length(rp->iovec_rp);
  // Allocate memory for protected data
  grpc_slice protected_slice = GRPC_SLICE_MALLOC(protected_frame_size);
  iovec_t protected_iovec = {GRPC_SLICE_START_PTR(protected_slice),
                             GRPC_SLICE_LENGTH(protected_slice)};

  // Convert slice buffer to iovec and perform protection
  char* error_details = nullptr;
  alts_grpc_record_protocol_convert_slice_buffer_to_iovec(rp,
                                                          unprotected_slices);
  grpc_status_code status =
      alts_iovec_record_protocol_privacy_integrity_protect(
          rp->iovec_rp, rp->iovec_buf, unprotected_slices->count,
          protected_iovec, &error_details);
  if (status != GRPC_STATUS_OK) {
    LOG(ERROR) << "Failed to protect, " << error_details;
    gpr_free(error_details);
    grpc_core::CSliceUnref(protected_slice);
    return TSI_INTERNAL_ERROR;
  }
  // Add protected data to output buffer and clean up input buffer
  grpc_slice_buffer_add(protected_slices, protected_slice);
  grpc_slice_buffer_reset_and_unref(unprotected_slices);
  return TSI_OK;
}

/**
 * Unprotects data that was protected with both privacy and integrity.
 * 
 * @param rp Pointer to the record protocol instance
 * @param protected_slices Buffer containing protected data to be unprotected
 * @param unprotected_slices Buffer to store the unprotected data
 * @return tsi_result TSI_OK on success, error code on failure
 */
static tsi_result alts_grpc_privacy_integrity_unprotect(
    alts_grpc_record_protocol* rp, grpc_slice_buffer* protected_slices,
    grpc_slice_buffer* unprotected_slices) {

  // Validate input parameters
  if (rp == nullptr || protected_slices == nullptr ||
      unprotected_slices == nullptr) {
    LOG(ERROR)
        << "Invalid nullptr arguments to alts_grpc_record_protocol unprotect.";
    return TSI_INVALID_ARGUMENT;
  }

  // Check if protected data has sufficient length (header + tag)
  if (protected_slices->length < rp->header_length + rp->tag_length) {
    LOG(ERROR) << "Protected slices do not have sufficient data.";
    return TSI_INVALID_ARGUMENT;
  }
  // Calculate unprotected data size (total - header - tag)
  size_t unprotected_frame_size =
      protected_slices->length - rp->header_length - rp->tag_length;
  grpc_slice unprotected_slice = GRPC_SLICE_MALLOC(unprotected_frame_size);
  iovec_t unprotected_iovec = {GRPC_SLICE_START_PTR(unprotected_slice),
                               GRPC_SLICE_LENGTH(unprotected_slice)};

  // Extract header from protected data
  grpc_slice_buffer_reset_and_unref(&rp->header_sb);
  grpc_slice_buffer_move_first(protected_slices, rp->header_length,
                               &rp->header_sb);
  iovec_t header_iovec = alts_grpc_record_protocol_get_header_iovec(rp);

  // Convert slice buffer to iovec and perform unprotection
  char* error_details = nullptr;
  alts_grpc_record_protocol_convert_slice_buffer_to_iovec(rp, protected_slices);
  grpc_status_code status =
      alts_iovec_record_protocol_privacy_integrity_unprotect(
          rp->iovec_rp, header_iovec, rp->iovec_buf, protected_slices->count,
          unprotected_iovec, &error_details);
  if (status != GRPC_STATUS_OK) {
    LOG(ERROR) << "Failed to unprotect, " << error_details;
    gpr_free(error_details);
    grpc_core::CSliceUnref(unprotected_slice);
    return TSI_INTERNAL_ERROR;
  }
  // Clean up and add unprotected data to output buffer
  grpc_slice_buffer_reset_and_unref(&rp->header_sb);
  grpc_slice_buffer_reset_and_unref(protected_slices);
  grpc_slice_buffer_add(unprotected_slices, unprotected_slice);
  return TSI_OK;
}

// Virtual table for privacy-integrity record protocol operations
static const alts_grpc_record_protocol_vtable
    alts_grpc_privacy_integrity_record_protocol_vtable = {
        alts_grpc_privacy_integrity_protect,
        alts_grpc_privacy_integrity_unprotect, nullptr};

/**
 * Creates a new privacy-integrity record protocol instance.
 * 
 * @param crypter AEAD crypter instance to use for encryption/decryption
 * @param overflow_size Maximum allowed sequence number overflow
 * @param is_client Whether this is for client-side operation
 * @param is_protect Whether this instance will be used for protection
 * @param rp Output parameter for the created record protocol instance
 * @return tsi_result TSI_OK on success, error code on failure
 */
tsi_result alts_grpc_privacy_integrity_record_protocol_create(
    gsec_aead_crypter* crypter, size_t overflow_size, bool is_client,
    bool is_protect, alts_grpc_record_protocol** rp) {
  // Validate input parameters
  if (crypter == nullptr || rp == nullptr) {
    LOG(ERROR)
        << "Invalid nullptr arguments to alts_grpc_record_protocol create.";
    return TSI_INVALID_ARGUMENT;
  }
  // Allocate and initialize new record protocol instance
  auto* impl = static_cast<alts_grpc_record_protocol*>(
      gpr_zalloc(sizeof(alts_grpc_record_protocol)));

  tsi_result result =
      alts_grpc_record_protocol_init(impl, crypter, overflow_size, is_client,
                                     false, is_protect);
  if (result != TSI_OK) {
    gpr_free(impl);
    return result;
  }
  // Set the virtual table for privacy-integrity operations
  impl->vtable = &alts_grpc_privacy_integrity_record_protocol_vtable;
  *rp = impl;
  return TSI_OK;
}
```