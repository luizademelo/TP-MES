
// Copyright 2018 gRPC authors.

#include "src/core/tsi/alts/zero_copy_frame_protector/alts_grpc_integrity_only_record_protocol.h"

#include <grpc/support/alloc.h>
#include <grpc/support/port_platform.h>
#include <string.h>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/lib/slice/slice_internal.h"
#include "src/core/tsi/alts/zero_copy_frame_protector/alts_grpc_record_protocol_common.h"
#include "src/core/tsi/alts/zero_copy_frame_protector/alts_iovec_record_protocol.h"
#include "src/core/util/crash.h"

typedef struct alts_grpc_integrity_only_record_protocol {
  alts_grpc_record_protocol base;
  bool enable_extra_copy;
  grpc_slice_buffer data_sb;
  unsigned char* tag_buf;
} alts_grpc_integrity_only_record_protocol;

static tsi_result alts_grpc_integrity_only_extra_copy_protect(
    alts_grpc_record_protocol* rp, grpc_slice_buffer* unprotected_slices,
    grpc_slice_buffer* protected_slices) {

  size_t data_length = unprotected_slices->length;
  size_t protected_frame_size =
      unprotected_slices->length + rp->header_length + rp->tag_length;
  grpc_slice protected_slice = GRPC_SLICE_MALLOC(protected_frame_size);
  uint8_t* data = GRPC_SLICE_START_PTR(protected_slice) + rp->header_length;
  for (size_t i = 0; i < unprotected_slices->count; i++) {
    memcpy(data, GRPC_SLICE_START_PTR(unprotected_slices->slices[i]),
           GRPC_SLICE_LENGTH(unprotected_slices->slices[i]));
    data += GRPC_SLICE_LENGTH(unprotected_slices->slices[i]);
  }

  char* error_details = nullptr;
  iovec_t header_iovec = {GRPC_SLICE_START_PTR(protected_slice),
                          rp->header_length};
  iovec_t tag_iovec = {
      GRPC_SLICE_START_PTR(protected_slice) + rp->header_length + data_length,
      rp->tag_length};
  rp->iovec_buf[0].iov_base =
      GRPC_SLICE_START_PTR(protected_slice) + rp->header_length;
  rp->iovec_buf[0].iov_len = data_length;
  grpc_status_code status = alts_iovec_record_protocol_integrity_only_protect(
      rp->iovec_rp, rp->iovec_buf, 1, header_iovec, tag_iovec, &error_details);
  if (status != GRPC_STATUS_OK) {
    LOG(ERROR) << "Failed to protect, " << error_details;
    gpr_free(error_details);
    return TSI_INTERNAL_ERROR;
  }
  grpc_slice_buffer_add(protected_slices, protected_slice);
  grpc_slice_buffer_reset_and_unref(unprotected_slices);
  return TSI_OK;
}

static tsi_result alts_grpc_integrity_only_protect(
    alts_grpc_record_protocol* rp, grpc_slice_buffer* unprotected_slices,
    grpc_slice_buffer* protected_slices) {

  if (rp == nullptr || unprotected_slices == nullptr ||
      protected_slices == nullptr) {
    LOG(ERROR)
        << "Invalid nullptr arguments to alts_grpc_record_protocol protect.";
    return TSI_INVALID_ARGUMENT;
  }
  alts_grpc_integrity_only_record_protocol* integrity_only_record_protocol =
      reinterpret_cast<alts_grpc_integrity_only_record_protocol*>(rp);
  if (integrity_only_record_protocol->enable_extra_copy) {
    return alts_grpc_integrity_only_extra_copy_protect(rp, unprotected_slices,
                                                       protected_slices);
  }

  grpc_slice header_slice = GRPC_SLICE_MALLOC(rp->header_length);
  grpc_slice tag_slice = GRPC_SLICE_MALLOC(rp->tag_length);

  char* error_details = nullptr;
  iovec_t header_iovec = {GRPC_SLICE_START_PTR(header_slice),
                          GRPC_SLICE_LENGTH(header_slice)};
  iovec_t tag_iovec = {GRPC_SLICE_START_PTR(tag_slice),
                       GRPC_SLICE_LENGTH(tag_slice)};
  alts_grpc_record_protocol_convert_slice_buffer_to_iovec(rp,
                                                          unprotected_slices);
  grpc_status_code status = alts_iovec_record_protocol_integrity_only_protect(
      rp->iovec_rp, rp->iovec_buf, unprotected_slices->count, header_iovec,
      tag_iovec, &error_details);
  if (status != GRPC_STATUS_OK) {
    LOG(ERROR) << "Failed to protect, " << error_details;
    gpr_free(error_details);
    return TSI_INTERNAL_ERROR;
  }

  grpc_slice_buffer_add(protected_slices, header_slice);
  grpc_slice_buffer_move_into(unprotected_slices, protected_slices);
  grpc_slice_buffer_add(protected_slices, tag_slice);
  return TSI_OK;
}

static tsi_result alts_grpc_integrity_only_unprotect(
    alts_grpc_record_protocol* rp, grpc_slice_buffer* protected_slices,
    grpc_slice_buffer* unprotected_slices) {

  if (rp == nullptr || protected_slices == nullptr ||
      unprotected_slices == nullptr) {
    LOG(ERROR)
        << "Invalid nullptr arguments to alts_grpc_record_protocol unprotect.";
    return TSI_INVALID_ARGUMENT;
  }
  if (protected_slices->length < rp->header_length + rp->tag_length) {
    LOG(ERROR) << "Protected slices do not have sufficient data.";
    return TSI_INVALID_ARGUMENT;
  }

  alts_grpc_integrity_only_record_protocol* integrity_only_record_protocol =
      reinterpret_cast<alts_grpc_integrity_only_record_protocol*>(rp);

  grpc_slice_buffer_reset_and_unref(&rp->header_sb);
  grpc_slice_buffer_move_first(protected_slices, rp->header_length,
                               &rp->header_sb);
  CHECK(rp->header_sb.length == rp->header_length);
  iovec_t header_iovec = alts_grpc_record_protocol_get_header_iovec(rp);

  grpc_slice_buffer_reset_and_unref(&integrity_only_record_protocol->data_sb);
  grpc_slice_buffer_move_first(protected_slices,
                               protected_slices->length - rp->tag_length,
                               &integrity_only_record_protocol->data_sb);
  CHECK(protected_slices->length == rp->tag_length);
  iovec_t tag_iovec = {nullptr, rp->tag_length};
  if (protected_slices->count == 1) {
    tag_iovec.iov_base = GRPC_SLICE_START_PTR(protected_slices->slices[0]);
  } else {

    alts_grpc_record_protocol_copy_slice_buffer(
        protected_slices, integrity_only_record_protocol->tag_buf);
    tag_iovec.iov_base = integrity_only_record_protocol->tag_buf;
  }

  char* error_details = nullptr;
  alts_grpc_record_protocol_convert_slice_buffer_to_iovec(
      rp, &integrity_only_record_protocol->data_sb);
  grpc_status_code status = alts_iovec_record_protocol_integrity_only_unprotect(
      rp->iovec_rp, rp->iovec_buf,
      integrity_only_record_protocol->data_sb.count, header_iovec, tag_iovec,
      &error_details);
  if (status != GRPC_STATUS_OK) {
    LOG(ERROR) << "Failed to unprotect, " << error_details;
    gpr_free(error_details);
    return TSI_INTERNAL_ERROR;
  }
  grpc_slice_buffer_reset_and_unref(&rp->header_sb);
  grpc_slice_buffer_reset_and_unref(protected_slices);
  grpc_slice_buffer_move_into(&integrity_only_record_protocol->data_sb,
                              unprotected_slices);
  return TSI_OK;
}

static void alts_grpc_integrity_only_destruct(alts_grpc_record_protocol* rp) {
  if (rp == nullptr) {
    return;
  }
  alts_grpc_integrity_only_record_protocol* integrity_only_rp =
      reinterpret_cast<alts_grpc_integrity_only_record_protocol*>(rp);
  grpc_slice_buffer_destroy(&integrity_only_rp->data_sb);
  gpr_free(integrity_only_rp->tag_buf);
}

static const alts_grpc_record_protocol_vtable
    alts_grpc_integrity_only_record_protocol_vtable = {
        alts_grpc_integrity_only_protect, alts_grpc_integrity_only_unprotect,
        alts_grpc_integrity_only_destruct};

tsi_result alts_grpc_integrity_only_record_protocol_create(
    gsec_aead_crypter* crypter, size_t overflow_size, bool is_client,
    bool is_protect, bool enable_extra_copy, alts_grpc_record_protocol** rp) {
  if (crypter == nullptr || rp == nullptr) {
    LOG(ERROR)
        << "Invalid nullptr arguments to alts_grpc_record_protocol create.";
    return TSI_INVALID_ARGUMENT;
  }
  alts_grpc_integrity_only_record_protocol* impl =
      static_cast<alts_grpc_integrity_only_record_protocol*>(
          gpr_zalloc(sizeof(alts_grpc_integrity_only_record_protocol)));

  tsi_result result = alts_grpc_record_protocol_init(
      &impl->base, crypter, overflow_size, is_client,
      true, is_protect);
  if (result != TSI_OK) {
    gpr_free(impl);
    return result;
  }
  impl->enable_extra_copy = enable_extra_copy;

  grpc_slice_buffer_init(&impl->data_sb);

  impl->tag_buf =
      static_cast<unsigned char*>(gpr_malloc(impl->base.tag_length));
  impl->base.vtable = &alts_grpc_integrity_only_record_protocol_vtable;
  *rp = &impl->base;
  return TSI_OK;
}
