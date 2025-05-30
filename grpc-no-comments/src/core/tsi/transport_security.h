
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_TSI_TRANSPORT_SECURITY_H
#define GRPC_SRC_CORE_TSI_TRANSPORT_SECURITY_H

#include <grpc/support/port_platform.h>
#include <stdbool.h>

#include "src/core/lib/debug/trace.h"
#include "src/core/tsi/transport_security_interface.h"

struct tsi_frame_protector_vtable {
  tsi_result (*protect)(tsi_frame_protector* self,
                        const unsigned char* unprotected_bytes,
                        size_t* unprotected_bytes_size,
                        unsigned char* protected_output_frames,
                        size_t* protected_output_frames_size);
  tsi_result (*protect_flush)(tsi_frame_protector* self,
                              unsigned char* protected_output_frames,
                              size_t* protected_output_frames_size,
                              size_t* still_pending_size);
  tsi_result (*unprotect)(tsi_frame_protector* self,
                          const unsigned char* protected_frames_bytes,
                          size_t* protected_frames_bytes_size,
                          unsigned char* unprotected_bytes,
                          size_t* unprotected_bytes_size);
  void (*destroy)(tsi_frame_protector* self);
};
struct tsi_frame_protector {
  const tsi_frame_protector_vtable* vtable;
};

struct tsi_handshaker_vtable {

  tsi_result (*get_bytes_to_send_to_peer)(tsi_handshaker* self,
                                          unsigned char* bytes,
                                          size_t* bytes_size);
  tsi_result (*process_bytes_from_peer)(tsi_handshaker* self,
                                        const unsigned char* bytes,
                                        size_t* bytes_size);
  tsi_result (*get_result)(tsi_handshaker* self);
  tsi_result (*extract_peer)(tsi_handshaker* self, tsi_peer* peer);
  tsi_result (*create_frame_protector)(tsi_handshaker* self,
                                       size_t* max_protected_frame_size,
                                       tsi_frame_protector** protector);

  void (*destroy)(tsi_handshaker* self);

  tsi_result (*next)(tsi_handshaker* self, const unsigned char* received_bytes,
                     size_t received_bytes_size,
                     const unsigned char** bytes_to_send,
                     size_t* bytes_to_send_size,
                     tsi_handshaker_result** handshaker_result,
                     tsi_handshaker_on_next_done_cb cb, void* user_data,
                     std::string* error);
  void (*shutdown)(tsi_handshaker* self);
};
struct tsi_handshaker {
  const tsi_handshaker_vtable* vtable;
  bool frame_protector_created;
  bool handshaker_result_created;
  bool handshake_shutdown;
};

struct tsi_handshaker_result_vtable {
  tsi_result (*extract_peer)(const tsi_handshaker_result* self, tsi_peer* peer);
  tsi_result (*get_frame_protector_type)(
      const tsi_handshaker_result* self,
      tsi_frame_protector_type* frame_protector_type);

  tsi_result (*create_zero_copy_grpc_protector)(
      const tsi_handshaker_result* self,
      size_t* max_output_protected_frame_size,
      tsi_zero_copy_grpc_protector** protector);

  tsi_result (*create_frame_protector)(const tsi_handshaker_result* self,
                                       size_t* max_output_protected_frame_size,
                                       tsi_frame_protector** protector);
  tsi_result (*get_unused_bytes)(const tsi_handshaker_result* self,
                                 const unsigned char** bytes,
                                 size_t* bytes_size);
  void (*destroy)(tsi_handshaker_result* self);
};
struct tsi_handshaker_result {
  const tsi_handshaker_result_vtable* vtable;
};

tsi_result tsi_construct_peer(size_t property_count, tsi_peer* peer);
tsi_peer_property tsi_init_peer_property(void);
void tsi_peer_property_destruct(tsi_peer_property* property);
tsi_result tsi_construct_string_peer_property(const char* name,
                                              const char* value,
                                              size_t value_length,
                                              tsi_peer_property* property);
tsi_result tsi_construct_allocated_string_peer_property(
    const char* name, size_t value_length, tsi_peer_property* property);
tsi_result tsi_construct_string_peer_property_from_cstring(
    const char* name, const char* value, tsi_peer_property* property);
const tsi_peer_property* tsi_peer_get_property_by_name(const tsi_peer* peer,
                                                       const char* name);

char* tsi_strdup(const char* src);

#endif
