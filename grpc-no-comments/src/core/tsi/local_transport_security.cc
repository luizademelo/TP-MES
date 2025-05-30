
// Copyright 2018 gRPC authors.

#include "src/core/tsi/local_transport_security.h"

#include <grpc/support/alloc.h>
#include <grpc/support/port_platform.h>
#include <grpc/support/string_util.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "absl/log/log.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/tsi/transport_security_grpc.h"
#include "src/core/util/crash.h"

namespace {

typedef struct local_zero_copy_grpc_protector {
  tsi_zero_copy_grpc_protector base;
} local_zero_copy_grpc_protector;

typedef struct local_tsi_handshaker_result {
  tsi_handshaker_result base;
  unsigned char* unused_bytes;
  size_t unused_bytes_size;
} local_tsi_handshaker_result;

typedef struct local_tsi_handshaker {
  tsi_handshaker base;
} local_tsi_handshaker;

tsi_result handshaker_result_extract_peer(const tsi_handshaker_result* ,
                                          tsi_peer* ) {
  return TSI_OK;
}

tsi_result handshaker_result_get_frame_protector_type(
    const tsi_handshaker_result* ,
    tsi_frame_protector_type* frame_protector_type) {
  *frame_protector_type = TSI_FRAME_PROTECTOR_NONE;
  return TSI_OK;
}

tsi_result handshaker_result_get_unused_bytes(const tsi_handshaker_result* self,
                                              const unsigned char** bytes,
                                              size_t* bytes_size) {
  if (self == nullptr || bytes == nullptr || bytes_size == nullptr) {
    LOG(ERROR) << "Invalid arguments to get_unused_bytes()";
    return TSI_INVALID_ARGUMENT;
  }
  auto* result = reinterpret_cast<local_tsi_handshaker_result*>(
      const_cast<tsi_handshaker_result*>(self));
  *bytes_size = result->unused_bytes_size;
  *bytes = result->unused_bytes;
  return TSI_OK;
}

void handshaker_result_destroy(tsi_handshaker_result* self) {
  if (self == nullptr) {
    return;
  }
  local_tsi_handshaker_result* result =
      reinterpret_cast<local_tsi_handshaker_result*>(
          const_cast<tsi_handshaker_result*>(self));
  gpr_free(result->unused_bytes);
  gpr_free(result);
}

const tsi_handshaker_result_vtable result_vtable = {
    handshaker_result_extract_peer,
    handshaker_result_get_frame_protector_type,
    nullptr,
    nullptr,
    handshaker_result_get_unused_bytes,
    handshaker_result_destroy};

tsi_result create_handshaker_result(const unsigned char* received_bytes,
                                    size_t received_bytes_size,
                                    tsi_handshaker_result** self) {
  if (self == nullptr) {
    LOG(ERROR) << "Invalid arguments to create_handshaker_result()";
    return TSI_INVALID_ARGUMENT;
  }
  local_tsi_handshaker_result* result =
      grpc_core::Zalloc<local_tsi_handshaker_result>();
  if (received_bytes_size > 0) {
    result->unused_bytes =
        static_cast<unsigned char*>(gpr_malloc(received_bytes_size));
    memcpy(result->unused_bytes, received_bytes, received_bytes_size);
  }
  result->unused_bytes_size = received_bytes_size;
  result->base.vtable = &result_vtable;
  *self = &result->base;
  return TSI_OK;
}

tsi_result handshaker_next(tsi_handshaker* self,
                           const unsigned char* received_bytes,
                           size_t received_bytes_size,
                           const unsigned char** ,
                           size_t* bytes_to_send_size,
                           tsi_handshaker_result** result,
                           tsi_handshaker_on_next_done_cb ,
                           void* , std::string* error) {
  if (self == nullptr) {
    LOG(ERROR) << "Invalid arguments to handshaker_next()";
    if (error != nullptr) *error = "invalid argument";
    return TSI_INVALID_ARGUMENT;
  }

  *bytes_to_send_size = 0;
  create_handshaker_result(received_bytes, received_bytes_size, result);
  return TSI_OK;
}

void handshaker_destroy(tsi_handshaker* self) {
  if (self == nullptr) {
    return;
  }
  local_tsi_handshaker* handshaker =
      reinterpret_cast<local_tsi_handshaker*>(self);
  gpr_free(handshaker);
}

const tsi_handshaker_vtable handshaker_vtable = {
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    handshaker_destroy,
    handshaker_next,
    nullptr,
};

}

tsi_result tsi_local_handshaker_create(tsi_handshaker** self) {
  if (self == nullptr) {
    LOG(ERROR) << "Invalid arguments to local_tsi_handshaker_create()";
    return TSI_INVALID_ARGUMENT;
  }
  local_tsi_handshaker* handshaker = grpc_core::Zalloc<local_tsi_handshaker>();
  handshaker->base.vtable = &handshaker_vtable;
  *self = &handshaker->base;
  return TSI_OK;
}
