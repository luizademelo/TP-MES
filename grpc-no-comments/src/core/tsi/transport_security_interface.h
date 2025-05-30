
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_TSI_TRANSPORT_SECURITY_INTERFACE_H
#define GRPC_SRC_CORE_TSI_TRANSPORT_SECURITY_INTERFACE_H

#include <grpc/support/port_platform.h>
#include <stdint.h>
#include <stdlib.h>

#include <string>

#include "src/core/lib/debug/trace.h"

typedef enum {
  TSI_OK = 0,
  TSI_UNKNOWN_ERROR = 1,
  TSI_INVALID_ARGUMENT = 2,
  TSI_PERMISSION_DENIED = 3,
  TSI_INCOMPLETE_DATA = 4,
  TSI_FAILED_PRECONDITION = 5,
  TSI_UNIMPLEMENTED = 6,
  TSI_INTERNAL_ERROR = 7,
  TSI_DATA_CORRUPTED = 8,
  TSI_NOT_FOUND = 9,
  TSI_PROTOCOL_FAILURE = 10,
  TSI_HANDSHAKE_IN_PROGRESS = 11,
  TSI_OUT_OF_RESOURCES = 12,
  TSI_ASYNC = 13,
  TSI_HANDSHAKE_SHUTDOWN = 14,
  TSI_CLOSE_NOTIFY = 15,
  TSI_DRAIN_BUFFER = 16,

} tsi_result;

typedef enum {
  TSI_SECURITY_MIN,
  TSI_SECURITY_NONE = TSI_SECURITY_MIN,
  TSI_INTEGRITY_ONLY,
  TSI_PRIVACY_AND_INTEGRITY,
  TSI_SECURITY_MAX = TSI_PRIVACY_AND_INTEGRITY,
} tsi_security_level;

typedef enum {

  TSI_DONT_REQUEST_CLIENT_CERTIFICATE,
  TSI_REQUEST_CLIENT_CERTIFICATE_BUT_DONT_VERIFY,
  TSI_REQUEST_CLIENT_CERTIFICATE_AND_VERIFY,
  TSI_REQUEST_AND_REQUIRE_CLIENT_CERTIFICATE_BUT_DONT_VERIFY,
  TSI_REQUEST_AND_REQUIRE_CLIENT_CERTIFICATE_AND_VERIFY,
} tsi_client_certificate_request_type;

typedef enum {

  TSI_FRAME_PROTECTOR_NORMAL,

  TSI_FRAME_PROTECTOR_ZERO_COPY,

  TSI_FRAME_PROTECTOR_NORMAL_OR_ZERO_COPY,

  TSI_FRAME_PROTECTOR_NONE,
} tsi_frame_protector_type;

typedef enum {
  TSI_TLS1_2,
  TSI_TLS1_3,
} tsi_tls_version;

const char* tsi_result_to_string(tsi_result result);
const char* tsi_security_level_to_string(tsi_security_level security_level);

typedef struct tsi_zero_copy_grpc_protector tsi_zero_copy_grpc_protector;

typedef struct tsi_frame_protector tsi_frame_protector;

tsi_result tsi_frame_protector_protect(tsi_frame_protector* self,
                                       const unsigned char* unprotected_bytes,
                                       size_t* unprotected_bytes_size,
                                       unsigned char* protected_output_frames,
                                       size_t* protected_output_frames_size);

tsi_result tsi_frame_protector_protect_flush(
    tsi_frame_protector* self, unsigned char* protected_output_frames,
    size_t* protected_output_frames_size, size_t* still_pending_size);

tsi_result tsi_frame_protector_unprotect(
    tsi_frame_protector* self, const unsigned char* protected_frames_bytes,
    size_t* protected_frames_bytes_size, unsigned char* unprotected_bytes,
    size_t* unprotected_bytes_size);

void tsi_frame_protector_destroy(tsi_frame_protector* self);

#define TSI_CERTIFICATE_TYPE_PEER_PROPERTY "certificate_type"

#define TSI_SECURITY_LEVEL_PEER_PROPERTY "security_level"

typedef struct tsi_peer_property {
  char* name;
  struct {
    char* data;
    size_t length;
  } value;
} tsi_peer_property;

struct tsi_peer {
  tsi_peer_property* properties;
  size_t property_count;
};

void tsi_peer_destruct(tsi_peer* self);

typedef struct tsi_handshaker_result tsi_handshaker_result;

tsi_result tsi_handshaker_result_extract_peer(const tsi_handshaker_result* self,
                                              tsi_peer* peer);

tsi_result tsi_handshaker_result_get_frame_protector_type(
    const tsi_handshaker_result* self,
    tsi_frame_protector_type* frame_protector_type);

tsi_result tsi_handshaker_result_create_frame_protector(
    const tsi_handshaker_result* self, size_t* max_output_protected_frame_size,
    tsi_frame_protector** protector);

tsi_result tsi_handshaker_result_get_unused_bytes(
    const tsi_handshaker_result* self, const unsigned char** bytes,
    size_t* bytes_size);

void tsi_handshaker_result_destroy(tsi_handshaker_result* self);

typedef struct tsi_handshaker tsi_handshaker;

tsi_result tsi_handshaker_get_bytes_to_send_to_peer(tsi_handshaker* self,
                                                    unsigned char* bytes,
                                                    size_t* bytes_size);

tsi_result tsi_handshaker_process_bytes_from_peer(tsi_handshaker* self,
                                                  const unsigned char* bytes,
                                                  size_t* bytes_size);

tsi_result tsi_handshaker_get_result(tsi_handshaker* self);

#define tsi_handshaker_is_in_progress(h) \
  (tsi_handshaker_get_result((h)) == TSI_HANDSHAKE_IN_PROGRESS)

tsi_result tsi_handshaker_extract_peer(tsi_handshaker* self, tsi_peer* peer);

tsi_result tsi_handshaker_create_frame_protector(
    tsi_handshaker* self, size_t* max_output_protected_frame_size,
    tsi_frame_protector** protector);

typedef void (*tsi_handshaker_on_next_done_cb)(
    tsi_result status, void* user_data, const unsigned char* bytes_to_send,
    size_t bytes_to_send_size, tsi_handshaker_result* handshaker_result);

tsi_result tsi_handshaker_next(tsi_handshaker* self,
                               const unsigned char* received_bytes,
                               size_t received_bytes_size,
                               const unsigned char** bytes_to_send,
                               size_t* bytes_to_send_size,
                               tsi_handshaker_result** handshaker_result,
                               tsi_handshaker_on_next_done_cb cb,
                               void* user_data, std::string* error = nullptr);

void tsi_handshaker_shutdown(tsi_handshaker* self);

void tsi_handshaker_destroy(tsi_handshaker* self);

void tsi_init();

void tsi_destroy();

#endif
