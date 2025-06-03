Here's the commented version of the code:

```c++
// Copyright 2018 gRPC authors.

// Includes necessary headers for ALTS zero-copy frame protector implementation
#include "src/core/tsi/alts/zero_copy_frame_protector/alts_zero_copy_grpc_protector.h"

#include <grpc/support/alloc.h>
#include <grpc/support/port_platform.h>
#include <string.h>

#include <memory>
#include <utility>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "src/core/tsi/alts/crypt/gsec.h"
#include "src/core/tsi/alts/zero_copy_frame_protector/alts_grpc_integrity_only_record_protocol.h"
#include "src/core/tsi/alts/zero_copy_frame_protector/alts_grpc_privacy_integrity_record_protocol.h"
#include "src/core/tsi/alts/zero_copy_frame_protector/alts_grpc_record_protocol.h"
#include "src/core/tsi/alts/zero_copy_frame_protector/alts_iovec_record_protocol.h"
#include "src/core/tsi/transport_security_grpc.h"

// Frame length constants
constexpr size_t kMinFrameLength = 1024;        // Minimum allowed frame length
constexpr size_t kDefaultFrameLength = 16 * 1024;  // Default frame length
constexpr size_t kMaxFrameLength = 16 * 1024 * 1024;  // Maximum allowed frame length

// Structure representing ALTS zero-copy protector
typedef struct alts_zero_copy_grpc_protector {
  tsi_zero_copy_grpc_protector base;  // Base protector structure
  alts_grpc_record_protocol* record_protocol;  // Protocol for protecting data
  alts_grpc_record_protocol* unrecord_protocol;  // Protocol for unprotecting data
  size_t max_protected_frame_size;  // Maximum size of protected frames
  size_t max_unprotected_data_size;  // Maximum size of unprotected data
  grpc_slice_buffer unprotected_staging_sb;  // Buffer for staging unprotected data
  grpc_slice_buffer protected_sb;  // Buffer for protected data
  grpc_slice_buffer protected_staging_sb;  // Buffer for staging protected data
  uint32_t parsed_frame_size;  // Size of the current frame being parsed
} alts_zero_copy_grpc_protector;

/**
 * Reads the frame size from the slice buffer.
 * @param sb The slice buffer containing the frame
 * @param total_frame_size Output parameter for the total frame size
 * @return true if frame size was successfully read, false otherwise
 */
static bool read_frame_size(const grpc_slice_buffer* sb,
                            uint32_t* total_frame_size) {
  // Check for invalid input or insufficient data
  if (sb == nullptr || sb->length < kZeroCopyFrameLengthFieldSize) {
    return false;
  }
  uint8_t frame_size_buffer[kZeroCopyFrameLengthFieldSize];
  uint8_t* buf = frame_size_buffer;

  // Copy frame size bytes from slice buffer
  size_t remaining = kZeroCopyFrameLengthFieldSize;
  for (size_t i = 0; i < sb->count; i++) {
    size_t slice_length = GRPC_SLICE_LENGTH(sb->slices[i]);
    if (remaining <= slice_length) {
      memcpy(buf, GRPC_SLICE_START_PTR(sb->slices[i]), remaining);
      remaining = 0;
      break;
    } else {
      memcpy(buf, GRPC_SLICE_START_PTR(sb->slices[i]), slice_length);
      buf += slice_length;
      remaining -= slice_length;
    }
  }
  CHECK_EQ(remaining, 0u);

  // Combine bytes into frame size (little-endian)
  uint32_t frame_size = (static_cast<uint32_t>(frame_size_buffer[3]) << 24) |
                        (static_cast<uint32_t>(frame_size_buffer[2]) << 16) |
                        (static_cast<uint32_t>(frame_size_buffer[1]) << 8) |
                        static_cast<uint32_t>(frame_size_buffer[0]);
  // Validate frame size
  if (frame_size > kMaxFrameLength) {
    LOG(ERROR) << "Frame size is larger than maximum frame size";
    return false;
  }

  // Return total frame size including length field
  *total_frame_size =
      static_cast<uint32_t>(frame_size + kZeroCopyFrameLengthFieldSize);
  return true;
}

/**
 * Creates an ALTS GRPC record protocol instance.
 * @param key The key interface for encryption
 * @param is_client Whether this is for client-side protection
 * @param is_integrity_only Whether to use integrity-only protection
 * @param is_protect Whether this is for protecting data
 * @param enable_extra_copy Whether to enable extra copying
 * @param record_protocol Output parameter for created protocol
 * @return tsi_result indicating success or failure
 */
static tsi_result create_alts_grpc_record_protocol(
    std::unique_ptr<grpc_core::GsecKeyInterface> key, bool is_client,
    bool is_integrity_only, bool is_protect, bool enable_extra_copy,
    alts_grpc_record_protocol** record_protocol) {
  // Validate input parameters
  if (key == nullptr || record_protocol == nullptr) {
    return TSI_INVALID_ARGUMENT;
  }
  grpc_status_code status;
  gsec_aead_crypter* crypter = nullptr;
  char* error_details = nullptr;
  bool is_rekey = key->IsRekey();
  
  // Create AEAD crypter
  status = gsec_aes_gcm_aead_crypter_create(std::move(key), kAesGcmNonceLength,
                                            kAesGcmTagLength, &crypter,
                                            &error_details);
  if (status != GRPC_STATUS_OK) {
    LOG(ERROR) << "Failed to create AEAD crypter, " << error_details;
    gpr_free(error_details);
    return TSI_INTERNAL_ERROR;
  }
  
  // Set overflow limit based on whether this is a rekey
  size_t overflow_limit = is_rekey ? kAltsRecordProtocolRekeyFrameLimit
                                   : kAltsRecordProtocolFrameLimit;

  // Create appropriate record protocol based on parameters
  tsi_result result = is_integrity_only
                          ? alts_grpc_integrity_only_record_protocol_create(
                                crypter, overflow_limit, is_client, is_protect,
                                enable_extra_copy, record_protocol)
                          : alts_grpc_privacy_integrity_record_protocol_create(
                                crypter, overflow_limit, is_client, is_protect,
                                record_protocol);
  if (result != TSI_OK) {
    gsec_aead_crypter_destroy(crypter);
    return result;
  }
  return TSI_OK;
}

/**
 * Protects data using the zero-copy protector.
 * @param self The protector instance
 * @param unprotected_slices Input unprotected data
 * @param protected_slices Output protected data
 * @return tsi_result indicating success or failure
 */
static tsi_result alts_zero_copy_grpc_protector_protect(
    tsi_zero_copy_grpc_protector* self, grpc_slice_buffer* unprotected_slices,
    grpc_slice_buffer* protected_slices) {
  // Validate input parameters
  if (self == nullptr || unprotected_slices == nullptr ||
      protected_slices == nullptr) {
    LOG(ERROR) << "Invalid nullptr arguments to zero-copy grpc protect.";
    return TSI_INVALID_ARGUMENT;
  }
  alts_zero_copy_grpc_protector* protector =
      reinterpret_cast<alts_zero_copy_grpc_protector*>(self);

  // Process data in chunks if it exceeds maximum unprotected data size
  while (unprotected_slices->length > protector->max_unprotected_data_size) {
    grpc_slice_buffer_move_first(unprotected_slices,
                                 protector->max_unprotected_data_size,
                                 &protector->unprotected_staging_sb);
    tsi_result status = alts_grpc_record_protocol_protect(
        protector->record_protocol, &protector->unprotected_staging_sb,
        protected_slices);
    if (status != TSI_OK) {
      return status;
    }
  }
  // Protect remaining data
  return alts_grpc_record_protocol_protect(
      protector->record_protocol, unprotected_slices, protected_slices);
}

/**
 * Unprotects data using the zero-copy protector.
 * @param self The protector instance
 * @param protected_slices Input protected data
 * @param unprotected_slices Output unprotected data
 * @param min_progress_size Output parameter for minimum progress size
 * @return tsi_result indicating success or failure
 */
static tsi_result alts_zero_copy_grpc_protector_unprotect(
    tsi_zero_copy_grpc_protector* self, grpc_slice_buffer* protected_slices,
    grpc_slice_buffer* unprotected_slices, int* min_progress_size) {
  // Validate input parameters
  if (self == nullptr || unprotected_slices == nullptr ||
      protected_slices == nullptr) {
    LOG(ERROR) << "Invalid nullptr arguments to zero-copy grpc unprotect.";
    return TSI_INVALID_ARGUMENT;
  }
  alts_zero_copy_grpc_protector* protector =
      reinterpret_cast<alts_zero_copy_grpc_protector*>(self);
  
  // Move protected data to internal buffer
  grpc_slice_buffer_move_into(protected_slices, &protector->protected_sb);

  // Process complete frames
  while (protector->protected_sb.length >= kZeroCopyFrameLengthFieldSize) {
    // Parse frame size if not already done
    if (protector->parsed_frame_size == 0) {
      if (!read_frame_size(&protector->protected_sb,
                           &protector->parsed_frame_size)) {
        grpc_slice_buffer_reset_and_unref(&protector->protected_sb);
        return TSI_DATA_CORRUPTED;
      }
    }
    // Wait for complete frame if not enough data
    if (protector->protected_sb.length < protector->parsed_frame_size) break;

    // Unprotect the frame
    tsi_result status;
    if (protector->protected_sb.length == protector->parsed_frame_size) {
      status = alts_grpc_record_protocol_unprotect(protector->unrecord_protocol,
                                                   &protector->protected_sb,
                                                   unprotected_slices);
    } else {
      // For partial frames, move to staging buffer first
      grpc_slice_buffer_move_first(&protector->protected_sb,
                                   protector->parsed_frame_size,
                                   &protector->protected_staging_sb);
      status = alts_grpc_record_protocol_unprotect(
          protector->unrecord_protocol, &protector->protected_staging_sb,
          unprotected_slices);
    }
    protector->parsed_frame_size = 0;
    if (status != TSI_OK) {
      grpc_slice_buffer_reset_and_unref(&protector->protected_sb);
      return status;
    }
  }
  
  // Calculate minimum progress size if requested
  if (min_progress_size != nullptr) {
    if (protector->parsed_frame_size > kZeroCopyFrameLengthFieldSize) {
      *min_progress_size =
          protector->parsed_frame_size - protector->protected_sb.length;
    } else {
      *min_progress_size = 1;
    }
  }
  return TSI_OK;
}

/**
 * Destroys the zero-copy protector instance.
 * @param self The protector instance to destroy
 */
static void alts_zero_copy_grpc_protector_destroy(
    tsi_zero_copy_grpc_protector* self) {
  if (self == nullptr) {
    return;
  }
  alts_zero_copy_grpc_protector* protector =
      reinterpret_cast<alts_zero_copy_grpc_protector*>(self);
  // Clean up all resources
  alts_grpc_record_protocol_destroy(protector->record_protocol);
  alts_grpc_record_protocol_destroy(protector->unrecord_protocol);
  grpc_slice_buffer_destroy(&protector->unprotected_staging_sb);
  grpc_slice_buffer_destroy(&protector->protected_sb);
  grpc_slice_buffer_destroy(&protector->protected_staging_sb);
  gpr_free(protector);
}

/**
 * Gets the maximum frame size supported by the protector.
 * @param self The protector instance
 * @param max_frame_size Output parameter for maximum frame size
 * @return tsi_result indicating success or failure
 */
static tsi_result alts_zero_copy_grpc_protector_max_frame_size(
    tsi_zero_copy_grpc_protector* self, size_t* max_frame_size) {
  if (self == nullptr || max_frame_size == nullptr) return TSI_INVALID_ARGUMENT;
  alts_zero_copy_grpc_protector* protector =
      reinterpret_cast<alts_zero_copy_grpc_protector*>(self);
  *max_frame_size = protector->max_protected_frame_size;
  return TSI_OK;
}

// Virtual table for zero-copy protector operations
static const tsi_zero_copy_grpc_protector_vtable
    alts_zero_copy_grpc_protector_vtable = {
        alts_zero_copy_grpc_protector_protect,
        alts_zero_copy_grpc_protector_unprotect,
        alts_zero_copy_grpc_protector_destroy,
        alts_zero_copy_grpc_protector_max_frame_size};

/**
 * Creates a new ALTS zero-copy GRPC protector instance.
 * @param key_factory Factory for creating cryptographic keys
 * @param is_client Whether this is for client-side protection
 * @param is_integrity_only Whether to use integrity-only protection
 * @param enable_extra_copy Whether to enable extra copying
 * @param max_protected_frame_size Maximum frame size for protected data
 * @param protector Output parameter for created protector
 * @return tsi_result indicating success or failure
 */
tsi_result alts_zero_copy_grpc_protector_create(
    const grpc_core::GsecKeyFactoryInterface& key_factory, bool is_client,
    bool is_integrity_only, bool enable_extra_copy,
    size_t* max_protected_frame_size,
    tsi_zero_copy_grpc_protector** protector) {
  // Validate input parameters
  if (protector == nullptr) {
    LOG(ERROR)
        << "Invalid nullptr arguments to alts_zero_copy_grpc_protector create.";
    return TSI_INVALID_ARGUMENT;
  }

  // Allocate and initialize protector structure
  alts_zero_copy_grpc_protector* impl =
      static_cast<alts_zero_copy_grpc_protector*>(
          gpr_zalloc(sizeof(alts_zero_copy_grpc_protector)));

  // Create record protocols for protection and unprotection
  tsi_result status = create_alts_grpc_record_protocol(
      key_factory.Create(), is_client, is_integrity_only,
      true, enable_extra_copy, &impl->record_protocol);
  if (status == TSI_OK) {
    status = create_alts_grpc_record_protocol(
        key_factory.Create(), is_client, is_integrity_only,
        false, enable_extra_copy, &impl->unrecord_protocol);
    if (status == TSI_OK) {
      // Configure frame size limits
      size_t max_protected_frame_size_to_set = kDefaultFrameLength;
      if (max_protected_frame_size != nullptr) {
        *max_protected_frame_size =
            std::min(*max_protected_frame_size, kMaxFrameLength);
        *max_protected_frame_size =
            std::max(*max_protected_frame_size, kMinFrameLength);
        max_protected_frame_size_to_set = *max_protected_frame_size;
      }
      impl->max_protected_frame_size = max_protected_frame_size_to_set;
      impl->max_unprotected_data_size =
          alts_grpc_record_protocol_max_unprotected_data_size(
              impl->record_protocol, max_protected_frame_size_to_set);
      CHECK_GT(impl->max_unprotected_data_size, 0u);

      // Initialize buffers
      grpc_slice_buffer_init(&impl->unprotected_staging_sb);
      grpc_slice_buffer_init(&impl->protected_sb);
      grpc_slice_buffer_init(&impl->protected_staging_sb);
      impl->parsed_frame_size = 0;
      impl->base.vtable = &alts_zero_copy_grpc_protector_vtable;
      *protector = &impl->base;
      return TSI_OK;
    }
  }

  // Clean up on failure
  alts_grpc_record_protocol_destroy(impl->record_protocol);
  alts_grpc_record_protocol_destroy(impl->unrecord_protocol);
  gpr_free(impl);
  return TSI_INTERNAL_ERROR;
}
```