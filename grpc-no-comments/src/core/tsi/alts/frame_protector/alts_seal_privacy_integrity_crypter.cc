
// Copyright 2018 gRPC authors.

#include <grpc/support/alloc.h>
#include <grpc/support/port_platform.h>

#include "src/core/tsi/alts/frame_protector/alts_counter.h"
#include "src/core/tsi/alts/frame_protector/alts_crypter.h"
#include "src/core/tsi/alts/frame_protector/alts_record_protocol_crypter_common.h"

static void maybe_copy_error_msg(const char* src, char** dst) {
  if (dst != nullptr && src != nullptr) {
    *dst = static_cast<char*>(gpr_malloc(strlen(src) + 1));
    memcpy(*dst, src, strlen(src) + 1);
  }
}

static grpc_status_code seal_check(alts_crypter* c, const unsigned char* data,
                                   size_t data_allocated_size, size_t data_size,
                                   size_t* output_size, char** error_details) {

  grpc_status_code status = input_sanity_check(
      reinterpret_cast<const alts_record_protocol_crypter*>(c), data,
      output_size, error_details);
  if (status != GRPC_STATUS_OK) return status;

  size_t num_overhead_bytes =
      alts_crypter_num_overhead_bytes(reinterpret_cast<const alts_crypter*>(c));
  if (data_size == 0) {
    const char error_msg[] = "data_size is zero.";
    maybe_copy_error_msg(error_msg, error_details);
    return GRPC_STATUS_INVALID_ARGUMENT;
  }
  if (data_size + num_overhead_bytes > data_allocated_size) {
    const char error_msg[] =
        "data_allocated_size is smaller than sum of data_size and "
        "num_overhead_bytes.";
    maybe_copy_error_msg(error_msg, error_details);
    return GRPC_STATUS_INVALID_ARGUMENT;
  }
  return GRPC_STATUS_OK;
}

static grpc_status_code alts_seal_crypter_process_in_place(
    alts_crypter* c, unsigned char* data, size_t data_allocated_size,
    size_t data_size, size_t* output_size, char** error_details) {
  grpc_status_code status = seal_check(c, data, data_allocated_size, data_size,
                                       output_size, error_details);
  if (status != GRPC_STATUS_OK) {
    return status;
  }

  alts_record_protocol_crypter* rp_crypter =
      reinterpret_cast<alts_record_protocol_crypter*>(c);
  status = gsec_aead_crypter_encrypt(
      rp_crypter->crypter, alts_counter_get_counter(rp_crypter->ctr),
      alts_counter_get_size(rp_crypter->ctr), nullptr ,
      0 , data, data_size, data, data_allocated_size,
      output_size, error_details);
  if (status != GRPC_STATUS_OK) {
    return status;
  }

  return increment_counter(rp_crypter, error_details);
}

static const alts_crypter_vtable vtable = {
    alts_record_protocol_crypter_num_overhead_bytes,
    alts_seal_crypter_process_in_place, alts_record_protocol_crypter_destruct};

grpc_status_code alts_seal_crypter_create(gsec_aead_crypter* gc, bool is_client,
                                          size_t overflow_size,
                                          alts_crypter** crypter,
                                          char** error_details) {
  if (crypter == nullptr) {
    const char error_msg[] = "crypter is nullptr.";
    maybe_copy_error_msg(error_msg, error_details);
    return GRPC_STATUS_FAILED_PRECONDITION;
  }
  alts_record_protocol_crypter* rp_crypter =
      alts_crypter_create_common(gc, !is_client, overflow_size, error_details);
  if (rp_crypter == nullptr) {
    return GRPC_STATUS_FAILED_PRECONDITION;
  }
  rp_crypter->base.vtable = &vtable;
  *crypter = &rp_crypter->base;
  return GRPC_STATUS_OK;
}
