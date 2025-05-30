
// Copyright 2018 gRPC authors.

#ifndef GRPC_SRC_CORE_TSI_ALTS_HANDSHAKER_ALTS_HANDSHAKER_CLIENT_H
#define GRPC_SRC_CORE_TSI_ALTS_HANDSHAKER_ALTS_HANDSHAKER_CLIENT_H

#include <grpc/byte_buffer.h>
#include <grpc/byte_buffer_reader.h>
#include <grpc/grpc.h>
#include <grpc/support/port_platform.h>

#include "src/core/lib/iomgr/closure.h"
#include "src/core/lib/iomgr/pollset_set.h"
#include "src/core/tsi/alts/handshaker/alts_tsi_handshaker.h"
#include "src/core/tsi/transport_security_interface.h"

#define ALTS_SERVICE_METHOD "/grpc.gcp.HandshakerService/DoHandshake"
#define ALTS_APPLICATION_PROTOCOL "grpc"
#define ALTS_RECORD_PROTOCOL "ALTSRP_GCM_AES128_REKEY"
#define ALTS_HANDSHAKER_SERVICE_URL_FOR_TESTING "lame"

const size_t kAltsAes128GcmRekeyKeyLength = 44;

typedef struct alts_tsi_handshaker alts_tsi_handshaker;

typedef struct alts_handshaker_client alts_handshaker_client;

typedef grpc_call_error (*alts_grpc_caller)(grpc_call* call, const grpc_op* ops,
                                            size_t nops, grpc_closure* tag);

typedef struct alts_handshaker_client_vtable {
  tsi_result (*client_start)(alts_handshaker_client* client);
  tsi_result (*server_start)(alts_handshaker_client* client,
                             grpc_slice* bytes_received);
  tsi_result (*next)(alts_handshaker_client* client,
                     grpc_slice* bytes_received);
  void (*shutdown)(alts_handshaker_client* client);
  void (*destruct)(alts_handshaker_client* client);
} alts_handshaker_client_vtable;

tsi_result alts_handshaker_client_start_client(alts_handshaker_client* client);

tsi_result alts_handshaker_client_start_server(alts_handshaker_client* client,
                                               grpc_slice* bytes_received);

tsi_result alts_handshaker_client_next(alts_handshaker_client* client,
                                       grpc_slice* bytes_received);

void alts_handshaker_client_shutdown(alts_handshaker_client* client);

void alts_handshaker_client_destroy(alts_handshaker_client* client);

alts_handshaker_client* alts_grpc_handshaker_client_create(
    alts_tsi_handshaker* handshaker, grpc_channel* channel,
    const char* handshaker_service_url, grpc_pollset_set* interested_parties,
    grpc_alts_credentials_options* options, const grpc_slice& target_name,
    grpc_iomgr_cb_func grpc_cb, tsi_handshaker_on_next_done_cb cb,
    void* user_data, alts_handshaker_client_vtable* vtable_for_testing,
    bool is_client, size_t max_frame_size,
    std::optional<absl::string_view> preferred_transport_protocol,
    std::string* error);

void alts_handshaker_client_handle_response(alts_handshaker_client* client,
                                            bool is_ok);

size_t MaxNumberOfConcurrentHandshakes();

#endif
