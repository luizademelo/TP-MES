
// Copyright 2018 gRPC authors.

#include "src/core/tsi/alts/handshaker/alts_handshaker_client.h"

#include <grpc/byte_buffer.h>
#include <grpc/support/alloc.h>
#include <grpc/support/port_platform.h>

#include <list>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/strings/numbers.h"
#include "absl/strings/str_split.h"
#include "src/core/lib/slice/slice_internal.h"
#include "src/core/lib/surface/call.h"
#include "src/core/lib/surface/channel.h"
#include "src/core/tsi/alts/handshaker/alts_shared_resource.h"
#include "src/core/tsi/alts/handshaker/alts_tsi_handshaker_private.h"
#include "src/core/tsi/alts/handshaker/alts_tsi_utils.h"
#include "src/core/util/crash.h"
#include "src/core/util/env.h"
#include "src/core/util/sync.h"
#include "upb/mem/arena.hpp"

#define TSI_ALTS_INITIAL_BUFFER_SIZE 256

const int kHandshakerClientOpNum = 4;
const char kMaxConcurrentStreamsEnvironmentVariable[] =
    "GRPC_ALTS_MAX_CONCURRENT_HANDSHAKES";

struct alts_handshaker_client {
  const alts_handshaker_client_vtable* vtable;
};

struct recv_message_result {
  tsi_result status;
  const unsigned char* bytes_to_send;
  size_t bytes_to_send_size;
  tsi_handshaker_result* result;
};

typedef struct alts_grpc_handshaker_client {
  alts_handshaker_client base;

  gpr_refcount refs;
  alts_tsi_handshaker* handshaker;
  grpc_call* call;

  alts_grpc_caller grpc_caller;

  grpc_closure on_handshaker_service_resp_recv;

  grpc_byte_buffer* send_buffer = nullptr;
  grpc_byte_buffer* recv_buffer = nullptr;

  bool inject_read_failure = false;

  grpc_metadata_array recv_initial_metadata;

  tsi_handshaker_on_next_done_cb cb;
  void* user_data;

  grpc_alts_credentials_options* options;

  grpc_slice target_name;

  bool is_client;

  grpc_slice recv_bytes;

  unsigned char* buffer;
  size_t buffer_size;

  grpc_closure on_status_received;

  grpc_status_code handshake_status_code = GRPC_STATUS_OK;

  grpc_slice handshake_status_details;

  grpc_core::Mutex mu;

  bool receive_status_finished = false;

  recv_message_result* pending_recv_message_result = nullptr;

  size_t max_frame_size;
  std::vector<std::string> preferred_transport_protocols;

  std::string* error;
} alts_grpc_handshaker_client;

static void handshaker_client_send_buffer_destroy(
    alts_grpc_handshaker_client* client) {
  CHECK_NE(client, nullptr);
  grpc_byte_buffer_destroy(client->send_buffer);
  client->send_buffer = nullptr;
}

static bool is_handshake_finished_properly(grpc_gcp_HandshakerResp* resp) {
  CHECK_NE(resp, nullptr);
  return grpc_gcp_HandshakerResp_result(resp) != nullptr;
}

static void alts_grpc_handshaker_client_unref(
    alts_grpc_handshaker_client* client) {
  if (gpr_unref(&client->refs)) {
    if (client->base.vtable != nullptr &&
        client->base.vtable->destruct != nullptr) {
      client->base.vtable->destruct(&client->base);
    }
    grpc_byte_buffer_destroy(client->send_buffer);
    grpc_byte_buffer_destroy(client->recv_buffer);
    client->send_buffer = nullptr;
    client->recv_buffer = nullptr;
    grpc_metadata_array_destroy(&client->recv_initial_metadata);
    grpc_core::CSliceUnref(client->recv_bytes);
    grpc_core::CSliceUnref(client->target_name);
    grpc_alts_credentials_options_destroy(client->options);
    gpr_free(client->buffer);
    grpc_core::CSliceUnref(client->handshake_status_details);
    delete client;
  }
}

static void maybe_complete_tsi_next(
    alts_grpc_handshaker_client* client, bool receive_status_finished,
    recv_message_result* pending_recv_message_result) {
  recv_message_result* r;
  {
    grpc_core::MutexLock lock(&client->mu);
    client->receive_status_finished |= receive_status_finished;
    if (pending_recv_message_result != nullptr) {
      CHECK_EQ(client->pending_recv_message_result, nullptr);
      client->pending_recv_message_result = pending_recv_message_result;
    }
    if (client->pending_recv_message_result == nullptr) {
      return;
    }
    const bool have_final_result =
        client->pending_recv_message_result->result != nullptr ||
        client->pending_recv_message_result->status != TSI_OK;
    if (have_final_result && !client->receive_status_finished) {

      return;
    }
    r = client->pending_recv_message_result;
    client->pending_recv_message_result = nullptr;
  }
  client->cb(r->status, client->user_data, r->bytes_to_send,
             r->bytes_to_send_size, r->result);
  gpr_free(r);
}

static void handle_response_done(alts_grpc_handshaker_client* client,
                                 tsi_result status, std::string error,
                                 const unsigned char* bytes_to_send,
                                 size_t bytes_to_send_size,
                                 tsi_handshaker_result* result) {
  if (client->error != nullptr) *client->error = std::move(error);
  recv_message_result* p = grpc_core::Zalloc<recv_message_result>();
  p->status = status;
  p->bytes_to_send = bytes_to_send;
  p->bytes_to_send_size = bytes_to_send_size;
  p->result = result;
  maybe_complete_tsi_next(client, false ,
                          p );
}

void alts_handshaker_client_handle_response(alts_handshaker_client* c,
                                            bool is_ok) {
  CHECK_NE(c, nullptr);
  alts_grpc_handshaker_client* client =
      reinterpret_cast<alts_grpc_handshaker_client*>(c);
  grpc_byte_buffer* recv_buffer = client->recv_buffer;
  alts_tsi_handshaker* handshaker = client->handshaker;

  if (client->cb == nullptr) {
    LOG(ERROR)
        << "client->cb is nullptr in alts_tsi_handshaker_handle_response()";
    return;
  }
  if (handshaker == nullptr) {
    LOG(ERROR)
        << "handshaker is nullptr in alts_tsi_handshaker_handle_response()";
    handle_response_done(
        client, TSI_INTERNAL_ERROR,
        "handshaker is nullptr in alts_tsi_handshaker_handle_response()",
        nullptr, 0, nullptr);
    return;
  }

  if (alts_tsi_handshaker_has_shutdown(handshaker)) {
    VLOG(2) << "TSI handshake shutdown";
    handle_response_done(client, TSI_HANDSHAKE_SHUTDOWN,
                         "TSI handshake shutdown", nullptr, 0, nullptr);
    return;
  }

  if (!is_ok || client->inject_read_failure) {
    VLOG(2) << "read failed on grpc call to handshaker service";
    handle_response_done(client, TSI_INTERNAL_ERROR,
                         "read failed on grpc call to handshaker service",
                         nullptr, 0, nullptr);
    return;
  }
  if (recv_buffer == nullptr) {
    VLOG(2)
        << "recv_buffer is nullptr in alts_tsi_handshaker_handle_response()";
    handle_response_done(
        client, TSI_INTERNAL_ERROR,
        "recv_buffer is nullptr in alts_tsi_handshaker_handle_response()",
        nullptr, 0, nullptr);
    return;
  }
  upb::Arena arena;
  grpc_gcp_HandshakerResp* resp =
      alts_tsi_utils_deserialize_response(recv_buffer, arena.ptr());
  grpc_byte_buffer_destroy(client->recv_buffer);
  client->recv_buffer = nullptr;

  if (resp == nullptr) {
    LOG(ERROR) << "alts_tsi_utils_deserialize_response() failed";
    handle_response_done(client, TSI_DATA_CORRUPTED,
                         "alts_tsi_utils_deserialize_response() failed",
                         nullptr, 0, nullptr);
    return;
  }
  const grpc_gcp_HandshakerStatus* resp_status =
      grpc_gcp_HandshakerResp_status(resp);
  if (resp_status == nullptr) {
    LOG(ERROR) << "No status in HandshakerResp";
    handle_response_done(client, TSI_DATA_CORRUPTED,
                         "No status in HandshakerResp", nullptr, 0, nullptr);
    return;
  }
  upb_StringView out_frames = grpc_gcp_HandshakerResp_out_frames(resp);
  unsigned char* bytes_to_send = nullptr;
  size_t bytes_to_send_size = 0;
  if (out_frames.size > 0) {
    bytes_to_send_size = out_frames.size;
    while (bytes_to_send_size > client->buffer_size) {
      client->buffer_size *= 2;
      client->buffer = static_cast<unsigned char*>(
          gpr_realloc(client->buffer, client->buffer_size));
    }
    memcpy(client->buffer, out_frames.data, bytes_to_send_size);
    bytes_to_send = client->buffer;
  }
  tsi_handshaker_result* result = nullptr;
  if (is_handshake_finished_properly(resp)) {
    tsi_result status =
        alts_tsi_handshaker_result_create(resp, client->is_client, &result);
    if (status != TSI_OK) {
      LOG(ERROR) << "alts_tsi_handshaker_result_create() failed";
      handle_response_done(client, status,
                           "alts_tsi_handshaker_result_create() failed",
                           nullptr, 0, nullptr);
      return;
    }
    alts_tsi_handshaker_result_set_unused_bytes(
        result, &client->recv_bytes,
        grpc_gcp_HandshakerResp_bytes_consumed(resp));
  }
  grpc_status_code code = static_cast<grpc_status_code>(
      grpc_gcp_HandshakerStatus_code(resp_status));
  std::string error;
  if (code != GRPC_STATUS_OK) {
    upb_StringView details = grpc_gcp_HandshakerStatus_details(resp_status);
    if (details.size > 0) {
      error = absl::StrCat("Status ", code, " from handshaker service: ",
                           absl::string_view(details.data, details.size));
      LOG_EVERY_N_SEC(INFO, 1) << error;
    }
  }

  handle_response_done(client, alts_tsi_utils_convert_to_tsi_result(code),
                       std::move(error), bytes_to_send, bytes_to_send_size,
                       result);
}

static tsi_result continue_make_grpc_call(alts_grpc_handshaker_client* client,
                                          bool is_start) {
  CHECK_NE(client, nullptr);
  grpc_op ops[kHandshakerClientOpNum];
  memset(ops, 0, sizeof(ops));
  grpc_op* op = ops;
  if (is_start) {
    op->op = GRPC_OP_RECV_STATUS_ON_CLIENT;
    op->data.recv_status_on_client.trailing_metadata = nullptr;
    op->data.recv_status_on_client.status = &client->handshake_status_code;
    op->data.recv_status_on_client.status_details =
        &client->handshake_status_details;
    op->flags = 0;
    op->reserved = nullptr;
    op++;
    CHECK(op - ops <= kHandshakerClientOpNum);
    gpr_ref(&client->refs);
    grpc_call_error call_error =
        client->grpc_caller(client->call, ops, static_cast<size_t>(op - ops),
                            &client->on_status_received);

    CHECK_EQ(call_error, GRPC_CALL_OK);
    memset(ops, 0, sizeof(ops));
    op = ops;
    op->op = GRPC_OP_SEND_INITIAL_METADATA;
    op->data.send_initial_metadata.count = 0;
    op++;
    CHECK(op - ops <= kHandshakerClientOpNum);
    op->op = GRPC_OP_RECV_INITIAL_METADATA;
    op->data.recv_initial_metadata.recv_initial_metadata =
        &client->recv_initial_metadata;
    op++;
    CHECK(op - ops <= kHandshakerClientOpNum);
  }
  op->op = GRPC_OP_SEND_MESSAGE;
  op->data.send_message.send_message = client->send_buffer;
  op++;
  CHECK(op - ops <= kHandshakerClientOpNum);
  op->op = GRPC_OP_RECV_MESSAGE;
  op->data.recv_message.recv_message = &client->recv_buffer;
  op++;
  CHECK(op - ops <= kHandshakerClientOpNum);
  CHECK_NE(client->grpc_caller, nullptr);
  if (client->grpc_caller(client->call, ops, static_cast<size_t>(op - ops),
                          &client->on_handshaker_service_resp_recv) !=
      GRPC_CALL_OK) {
    LOG(ERROR) << "Start batch operation failed";
    return TSI_INTERNAL_ERROR;
  }
  return TSI_OK;
}

namespace {

class HandshakeQueue {
 public:
  explicit HandshakeQueue(size_t max_outstanding_handshakes)
      : max_outstanding_handshakes_(max_outstanding_handshakes) {}

  void RequestHandshake(alts_grpc_handshaker_client* client) {
    {
      grpc_core::MutexLock lock(&mu_);
      if (outstanding_handshakes_ == max_outstanding_handshakes_) {

        queued_handshakes_.push_back(client);
        return;
      }

      ++outstanding_handshakes_;
    }
    continue_make_grpc_call(client, true );
  }

  void HandshakeDone() {
    alts_grpc_handshaker_client* client = nullptr;
    {
      grpc_core::MutexLock lock(&mu_);
      if (queued_handshakes_.empty()) {

        --outstanding_handshakes_;
        return;
      }

      client = queued_handshakes_.front();
      queued_handshakes_.pop_front();
    }
    continue_make_grpc_call(client, true );
  }

 private:
  grpc_core::Mutex mu_;
  std::list<alts_grpc_handshaker_client*> queued_handshakes_;
  size_t outstanding_handshakes_ = 0;
  const size_t max_outstanding_handshakes_;
};

gpr_once g_queued_handshakes_init = GPR_ONCE_INIT;

HandshakeQueue* g_client_handshake_queue;
HandshakeQueue* g_server_handshake_queue;

void DoHandshakeQueuesInit(void) {
  const size_t per_queue_max_outstanding_handshakes =
      MaxNumberOfConcurrentHandshakes();
  g_client_handshake_queue =
      new HandshakeQueue(per_queue_max_outstanding_handshakes);
  g_server_handshake_queue =
      new HandshakeQueue(per_queue_max_outstanding_handshakes);
}

void RequestHandshake(alts_grpc_handshaker_client* client, bool is_client) {
  gpr_once_init(&g_queued_handshakes_init, DoHandshakeQueuesInit);
  HandshakeQueue* queue =
      is_client ? g_client_handshake_queue : g_server_handshake_queue;
  queue->RequestHandshake(client);
}

void HandshakeDone(bool is_client) {
  HandshakeQueue* queue =
      is_client ? g_client_handshake_queue : g_server_handshake_queue;
  queue->HandshakeDone();
}

};

static tsi_result make_grpc_call(alts_handshaker_client* c, bool is_start) {
  CHECK_NE(c, nullptr);
  alts_grpc_handshaker_client* client =
      reinterpret_cast<alts_grpc_handshaker_client*>(c);
  if (is_start) {
    RequestHandshake(client, client->is_client);
    return TSI_OK;
  } else {
    return continue_make_grpc_call(client, is_start);
  }
}

static void on_status_received(void* arg, grpc_error_handle error) {
  alts_grpc_handshaker_client* client =
      static_cast<alts_grpc_handshaker_client*>(arg);
  if (client->handshake_status_code != GRPC_STATUS_OK) {

    char* status_details =
        grpc_slice_to_c_string(client->handshake_status_details);
    VLOG(2) << "alts_grpc_handshaker_client:" << client
            << " on_status_received status:" << client->handshake_status_code
            << " details:|" << status_details << "| error:|"
            << grpc_core::StatusToString(error) << "|";
    gpr_free(status_details);
  }
  maybe_complete_tsi_next(client, true ,
                          nullptr );
  HandshakeDone(client->is_client);
  alts_grpc_handshaker_client_unref(client);
}

static grpc_byte_buffer* get_serialized_handshaker_req(
    grpc_gcp_HandshakerReq* req, upb_Arena* arena) {
  size_t buf_length;
  char* buf = grpc_gcp_HandshakerReq_serialize(req, arena, &buf_length);
  if (buf == nullptr) {
    return nullptr;
  }
  grpc_slice slice = grpc_slice_from_copied_buffer(buf, buf_length);
  grpc_byte_buffer* byte_buffer = grpc_raw_byte_buffer_create(&slice, 1);
  grpc_core::CSliceUnref(slice);
  return byte_buffer;
}

static grpc_byte_buffer* get_serialized_start_client(
    alts_handshaker_client* c) {
  CHECK_NE(c, nullptr);
  alts_grpc_handshaker_client* client =
      reinterpret_cast<alts_grpc_handshaker_client*>(c);
  upb::Arena arena;
  grpc_gcp_HandshakerReq* req = grpc_gcp_HandshakerReq_new(arena.ptr());
  grpc_gcp_StartClientHandshakeReq* start_client =
      grpc_gcp_HandshakerReq_mutable_client_start(req, arena.ptr());
  grpc_gcp_StartClientHandshakeReq_set_handshake_security_protocol(
      start_client, grpc_gcp_ALTS);
  grpc_gcp_StartClientHandshakeReq_add_application_protocols(
      start_client, upb_StringView_FromString(ALTS_APPLICATION_PROTOCOL),
      arena.ptr());
  grpc_gcp_StartClientHandshakeReq_add_record_protocols(
      start_client, upb_StringView_FromString(ALTS_RECORD_PROTOCOL),
      arena.ptr());
  grpc_gcp_RpcProtocolVersions* client_version =
      grpc_gcp_StartClientHandshakeReq_mutable_rpc_versions(start_client,
                                                            arena.ptr());
  grpc_gcp_RpcProtocolVersions_assign_from_struct(
      client_version, arena.ptr(), &client->options->rpc_versions);
  grpc_gcp_StartClientHandshakeReq_set_target_name(
      start_client, upb_StringView_FromDataAndSize(
                        reinterpret_cast<const char*>(
                            GRPC_SLICE_START_PTR(client->target_name)),
                        GRPC_SLICE_LENGTH(client->target_name)));
  target_service_account* ptr =
      (reinterpret_cast<grpc_alts_credentials_client_options*>(client->options))
          ->target_account_list_head;
  while (ptr != nullptr) {
    grpc_gcp_Identity* target_identity =
        grpc_gcp_StartClientHandshakeReq_add_target_identities(start_client,
                                                               arena.ptr());
    grpc_gcp_Identity_set_service_account(target_identity,
                                          upb_StringView_FromString(ptr->data));
    ptr = ptr->next;
  }
  grpc_gcp_StartClientHandshakeReq_set_max_frame_size(
      start_client, static_cast<uint32_t>(client->max_frame_size));
  if (!client->preferred_transport_protocols.empty()) {
    grpc_gcp_TransportProtocolPreferences* preferences =
        grpc_gcp_StartClientHandshakeReq_mutable_transport_protocol_preferences(
            start_client, arena.ptr());
    for (const auto& transport_protocol :
         client->preferred_transport_protocols) {
      grpc_gcp_TransportProtocolPreferences_add_transport_protocol(
          preferences, upb_StringView_FromString(transport_protocol.c_str()),
          arena.ptr());
    }
  }
  return get_serialized_handshaker_req(req, arena.ptr());
}

static tsi_result handshaker_client_start_client(alts_handshaker_client* c) {
  if (c == nullptr) {
    LOG(ERROR) << "client is nullptr in handshaker_client_start_client()";
    return TSI_INVALID_ARGUMENT;
  }
  grpc_byte_buffer* buffer = get_serialized_start_client(c);
  alts_grpc_handshaker_client* client =
      reinterpret_cast<alts_grpc_handshaker_client*>(c);
  if (buffer == nullptr) {
    LOG(ERROR) << "get_serialized_start_client() failed";
    return TSI_INTERNAL_ERROR;
  }
  handshaker_client_send_buffer_destroy(client);
  client->send_buffer = buffer;
  tsi_result result = make_grpc_call(&client->base, true );
  if (result != TSI_OK) {
    LOG(ERROR) << "make_grpc_call() failed";
  }
  return result;
}

static grpc_byte_buffer* get_serialized_start_server(
    alts_handshaker_client* c, grpc_slice* bytes_received) {
  CHECK_NE(c, nullptr);
  CHECK_NE(bytes_received, nullptr);
  alts_grpc_handshaker_client* client =
      reinterpret_cast<alts_grpc_handshaker_client*>(c);

  upb::Arena arena;
  grpc_gcp_HandshakerReq* req = grpc_gcp_HandshakerReq_new(arena.ptr());

  grpc_gcp_StartServerHandshakeReq* start_server =
      grpc_gcp_HandshakerReq_mutable_server_start(req, arena.ptr());
  grpc_gcp_StartServerHandshakeReq_add_application_protocols(
      start_server, upb_StringView_FromString(ALTS_APPLICATION_PROTOCOL),
      arena.ptr());
  grpc_gcp_ServerHandshakeParameters* value =
      grpc_gcp_ServerHandshakeParameters_new(arena.ptr());
  grpc_gcp_ServerHandshakeParameters_add_record_protocols(
      value, upb_StringView_FromString(ALTS_RECORD_PROTOCOL), arena.ptr());
  grpc_gcp_StartServerHandshakeReq_handshake_parameters_set(
      start_server, grpc_gcp_ALTS, value, arena.ptr());
  grpc_gcp_StartServerHandshakeReq_set_in_bytes(
      start_server,
      upb_StringView_FromDataAndSize(
          reinterpret_cast<const char*>(GRPC_SLICE_START_PTR(*bytes_received)),
          GRPC_SLICE_LENGTH(*bytes_received)));
  grpc_gcp_RpcProtocolVersions* server_version =
      grpc_gcp_StartServerHandshakeReq_mutable_rpc_versions(start_server,
                                                            arena.ptr());
  grpc_gcp_RpcProtocolVersions_assign_from_struct(
      server_version, arena.ptr(), &client->options->rpc_versions);
  grpc_gcp_StartServerHandshakeReq_set_max_frame_size(
      start_server, static_cast<uint32_t>(client->max_frame_size));
  if (!client->preferred_transport_protocols.empty()) {
    grpc_gcp_TransportProtocolPreferences* preferences =
        grpc_gcp_StartServerHandshakeReq_mutable_transport_protocol_preferences(
            start_server, arena.ptr());
    for (const auto& transport_protocol :
         client->preferred_transport_protocols) {
      grpc_gcp_TransportProtocolPreferences_add_transport_protocol(
          preferences, upb_StringView_FromString(transport_protocol.c_str()),
          arena.ptr());
    }
  }
  return get_serialized_handshaker_req(req, arena.ptr());
}

static tsi_result handshaker_client_start_server(alts_handshaker_client* c,
                                                 grpc_slice* bytes_received) {
  if (c == nullptr || bytes_received == nullptr) {
    LOG(ERROR) << "Invalid arguments to handshaker_client_start_server()";
    return TSI_INVALID_ARGUMENT;
  }
  alts_grpc_handshaker_client* client =
      reinterpret_cast<alts_grpc_handshaker_client*>(c);
  grpc_byte_buffer* buffer = get_serialized_start_server(c, bytes_received);
  if (buffer == nullptr) {
    LOG(ERROR) << "get_serialized_start_server() failed";
    return TSI_INTERNAL_ERROR;
  }
  handshaker_client_send_buffer_destroy(client);
  client->send_buffer = buffer;
  tsi_result result = make_grpc_call(&client->base, true );
  if (result != TSI_OK) {
    LOG(ERROR) << "make_grpc_call() failed";
  }
  return result;
}

static grpc_byte_buffer* get_serialized_next(grpc_slice* bytes_received) {
  CHECK_NE(bytes_received, nullptr);
  upb::Arena arena;
  grpc_gcp_HandshakerReq* req = grpc_gcp_HandshakerReq_new(arena.ptr());
  grpc_gcp_NextHandshakeMessageReq* next =
      grpc_gcp_HandshakerReq_mutable_next(req, arena.ptr());
  grpc_gcp_NextHandshakeMessageReq_set_in_bytes(
      next,
      upb_StringView_FromDataAndSize(
          reinterpret_cast<const char*> GRPC_SLICE_START_PTR(*bytes_received),
          GRPC_SLICE_LENGTH(*bytes_received)));
  return get_serialized_handshaker_req(req, arena.ptr());
}

static tsi_result handshaker_client_next(alts_handshaker_client* c,
                                         grpc_slice* bytes_received) {
  if (c == nullptr || bytes_received == nullptr) {
    LOG(ERROR) << "Invalid arguments to handshaker_client_next()";
    return TSI_INVALID_ARGUMENT;
  }
  alts_grpc_handshaker_client* client =
      reinterpret_cast<alts_grpc_handshaker_client*>(c);
  grpc_core::CSliceUnref(client->recv_bytes);
  client->recv_bytes = grpc_core::CSliceRef(*bytes_received);
  grpc_byte_buffer* buffer = get_serialized_next(bytes_received);
  if (buffer == nullptr) {
    LOG(ERROR) << "get_serialized_next() failed";
    return TSI_INTERNAL_ERROR;
  }
  handshaker_client_send_buffer_destroy(client);
  client->send_buffer = buffer;
  tsi_result result = make_grpc_call(&client->base, false );
  if (result != TSI_OK) {
    LOG(ERROR) << "make_grpc_call() failed";
  }
  return result;
}

static void handshaker_client_shutdown(alts_handshaker_client* c) {
  CHECK_NE(c, nullptr);
  alts_grpc_handshaker_client* client =
      reinterpret_cast<alts_grpc_handshaker_client*>(c);
  if (client->call != nullptr) {
    grpc_call_cancel_internal(client->call);
  }
}

static void handshaker_call_unref(void* arg, grpc_error_handle ) {
  grpc_call* call = static_cast<grpc_call*>(arg);
  grpc_call_unref(call);
}

static void handshaker_client_destruct(alts_handshaker_client* c) {
  if (c == nullptr) {
    return;
  }
  alts_grpc_handshaker_client* client =
      reinterpret_cast<alts_grpc_handshaker_client*>(c);
  if (client->call != nullptr) {

    if (grpc_core::ExecCtx::Get() == nullptr) {

      grpc_call_unref(client->call);
    } else {

      grpc_core::ExecCtx::Run(
          DEBUG_LOCATION,
          GRPC_CLOSURE_CREATE(handshaker_call_unref, client->call,
                              grpc_schedule_on_exec_ctx),
          absl::OkStatus());
    }
  }
}

static const alts_handshaker_client_vtable vtable = {
    handshaker_client_start_client, handshaker_client_start_server,
    handshaker_client_next, handshaker_client_shutdown,
    handshaker_client_destruct};

alts_handshaker_client* alts_grpc_handshaker_client_create(
    alts_tsi_handshaker* handshaker, grpc_channel* channel,
    const char* handshaker_service_url, grpc_pollset_set* interested_parties,
    grpc_alts_credentials_options* options, const grpc_slice& target_name,
    grpc_iomgr_cb_func grpc_cb, tsi_handshaker_on_next_done_cb cb,
    void* user_data, alts_handshaker_client_vtable* vtable_for_testing,
    bool is_client, size_t max_frame_size,
    std::optional<absl::string_view> preferred_transport_protocols,
    std::string* error) {
  if (channel == nullptr || handshaker_service_url == nullptr) {
    LOG(ERROR) << "Invalid arguments to alts_handshaker_client_create()";
    return nullptr;
  }
  alts_grpc_handshaker_client* client = new alts_grpc_handshaker_client();
  memset(&client->base, 0, sizeof(client->base));
  client->base.vtable =
      vtable_for_testing == nullptr ? &vtable : vtable_for_testing;
  gpr_ref_init(&client->refs, 1);
  client->handshaker = handshaker;
  client->grpc_caller = grpc_call_start_batch_and_execute;
  grpc_metadata_array_init(&client->recv_initial_metadata);
  client->cb = cb;
  client->user_data = user_data;
  client->options = grpc_alts_credentials_options_copy(options);
  client->target_name = grpc_slice_copy(target_name);
  client->is_client = is_client;
  client->recv_bytes = grpc_empty_slice();
  client->buffer_size = TSI_ALTS_INITIAL_BUFFER_SIZE;
  client->buffer = static_cast<unsigned char*>(gpr_zalloc(client->buffer_size));
  client->handshake_status_details = grpc_empty_slice();
  client->max_frame_size = max_frame_size;
  std::vector<std::string> transport_protocols;
  if (preferred_transport_protocols.has_value()) {
    transport_protocols = absl::StrSplit(preferred_transport_protocols.value(),
                                         ',', absl::SkipWhitespace());
  }
  client->preferred_transport_protocols = transport_protocols;
  client->error = error;
  client->call =
      strcmp(handshaker_service_url, ALTS_HANDSHAKER_SERVICE_URL_FOR_TESTING) ==
              0
          ? nullptr
          : grpc_core::Channel::FromC(channel)->CreateCall(
                nullptr, GRPC_PROPAGATE_DEFAULTS,
                nullptr, interested_parties,
                grpc_core::Slice::FromStaticString(ALTS_SERVICE_METHOD),
                std::nullopt, grpc_core::Timestamp::InfFuture(),
                true);
  GRPC_CLOSURE_INIT(&client->on_handshaker_service_resp_recv, grpc_cb, client,
                    grpc_schedule_on_exec_ctx);
  GRPC_CLOSURE_INIT(&client->on_status_received, on_status_received, client,
                    grpc_schedule_on_exec_ctx);
  return &client->base;
}

namespace grpc_core {
namespace internal {

void alts_handshaker_client_set_grpc_caller_for_testing(
    alts_handshaker_client* c, alts_grpc_caller caller) {
  CHECK(c != nullptr);
  CHECK_NE(caller, nullptr);
  alts_grpc_handshaker_client* client =
      reinterpret_cast<alts_grpc_handshaker_client*>(c);
  client->grpc_caller = caller;
}

grpc_byte_buffer* alts_handshaker_client_get_send_buffer_for_testing(
    alts_handshaker_client* c) {
  CHECK_NE(c, nullptr);
  alts_grpc_handshaker_client* client =
      reinterpret_cast<alts_grpc_handshaker_client*>(c);
  return client->send_buffer;
}

grpc_byte_buffer** alts_handshaker_client_get_recv_buffer_addr_for_testing(
    alts_handshaker_client* c) {
  CHECK_NE(c, nullptr);
  alts_grpc_handshaker_client* client =
      reinterpret_cast<alts_grpc_handshaker_client*>(c);
  return &client->recv_buffer;
}

grpc_metadata_array* alts_handshaker_client_get_initial_metadata_for_testing(
    alts_handshaker_client* c) {
  CHECK_NE(c, nullptr);
  alts_grpc_handshaker_client* client =
      reinterpret_cast<alts_grpc_handshaker_client*>(c);
  return &client->recv_initial_metadata;
}

void alts_handshaker_client_set_recv_bytes_for_testing(
    alts_handshaker_client* c, grpc_slice* recv_bytes) {
  CHECK_NE(c, nullptr);
  alts_grpc_handshaker_client* client =
      reinterpret_cast<alts_grpc_handshaker_client*>(c);
  client->recv_bytes = CSliceRef(*recv_bytes);
}

void alts_handshaker_client_set_fields_for_testing(
    alts_handshaker_client* c, alts_tsi_handshaker* handshaker,
    tsi_handshaker_on_next_done_cb cb, void* user_data,
    grpc_byte_buffer* recv_buffer, bool inject_read_failure) {
  CHECK_NE(c, nullptr);
  alts_grpc_handshaker_client* client =
      reinterpret_cast<alts_grpc_handshaker_client*>(c);
  client->handshaker = handshaker;
  client->cb = cb;
  client->user_data = user_data;
  client->recv_buffer = recv_buffer;
  client->inject_read_failure = inject_read_failure;
}

void alts_handshaker_client_check_fields_for_testing(
    alts_handshaker_client* c, tsi_handshaker_on_next_done_cb cb,
    void* user_data, bool has_sent_start_message, grpc_slice* recv_bytes) {
  CHECK_NE(c, nullptr);
  alts_grpc_handshaker_client* client =
      reinterpret_cast<alts_grpc_handshaker_client*>(c);
  CHECK(client->cb == cb);
  CHECK(client->user_data == user_data);
  if (recv_bytes != nullptr) {
    CHECK_EQ(grpc_slice_cmp(client->recv_bytes, *recv_bytes), 0);
  }
  CHECK(alts_tsi_handshaker_get_has_sent_start_message_for_testing(
            client->handshaker) == has_sent_start_message);
}

void alts_handshaker_client_set_vtable_for_testing(
    alts_handshaker_client* c, alts_handshaker_client_vtable* vtable) {
  CHECK_NE(c, nullptr);
  CHECK_NE(vtable, nullptr);
  alts_grpc_handshaker_client* client =
      reinterpret_cast<alts_grpc_handshaker_client*>(c);
  client->base.vtable = vtable;
}

alts_tsi_handshaker* alts_handshaker_client_get_handshaker_for_testing(
    alts_handshaker_client* c) {
  CHECK_NE(c, nullptr);
  alts_grpc_handshaker_client* client =
      reinterpret_cast<alts_grpc_handshaker_client*>(c);
  return client->handshaker;
}

void alts_handshaker_client_set_cb_for_testing(
    alts_handshaker_client* c, tsi_handshaker_on_next_done_cb cb) {
  CHECK_NE(c, nullptr);
  alts_grpc_handshaker_client* client =
      reinterpret_cast<alts_grpc_handshaker_client*>(c);
  client->cb = cb;
}

grpc_closure* alts_handshaker_client_get_closure_for_testing(
    alts_handshaker_client* c) {
  CHECK_NE(c, nullptr);
  alts_grpc_handshaker_client* client =
      reinterpret_cast<alts_grpc_handshaker_client*>(c);
  return &client->on_handshaker_service_resp_recv;
}

void alts_handshaker_client_ref_for_testing(alts_handshaker_client* c) {
  alts_grpc_handshaker_client* client =
      reinterpret_cast<alts_grpc_handshaker_client*>(c);
  gpr_ref(&client->refs);
}

void alts_handshaker_client_on_status_received_for_testing(
    alts_handshaker_client* c, grpc_status_code status,
    grpc_error_handle error) {

  gpr_once_init(&g_queued_handshakes_init, DoHandshakeQueuesInit);
  alts_grpc_handshaker_client* client =
      reinterpret_cast<alts_grpc_handshaker_client*>(c);
  client->handshake_status_code = status;
  client->handshake_status_details = grpc_empty_slice();
  Closure::Run(DEBUG_LOCATION, &client->on_status_received, error);
}

}
}

tsi_result alts_handshaker_client_start_client(alts_handshaker_client* client) {
  if (client != nullptr && client->vtable != nullptr &&
      client->vtable->client_start != nullptr) {
    return client->vtable->client_start(client);
  }
  LOG(ERROR) << "client or client->vtable has not been initialized properly";
  return TSI_INVALID_ARGUMENT;
}

tsi_result alts_handshaker_client_start_server(alts_handshaker_client* client,
                                               grpc_slice* bytes_received) {
  if (client != nullptr && client->vtable != nullptr &&
      client->vtable->server_start != nullptr) {
    return client->vtable->server_start(client, bytes_received);
  }
  LOG(ERROR) << "client or client->vtable has not been initialized properly";
  return TSI_INVALID_ARGUMENT;
}

tsi_result alts_handshaker_client_next(alts_handshaker_client* client,
                                       grpc_slice* bytes_received) {
  if (client != nullptr && client->vtable != nullptr &&
      client->vtable->next != nullptr) {
    return client->vtable->next(client, bytes_received);
  }
  LOG(ERROR) << "client or client->vtable has not been initialized properly";
  return TSI_INVALID_ARGUMENT;
}

void alts_handshaker_client_shutdown(alts_handshaker_client* client) {
  if (client != nullptr && client->vtable != nullptr &&
      client->vtable->shutdown != nullptr) {
    client->vtable->shutdown(client);
  }
}

void alts_handshaker_client_destroy(alts_handshaker_client* c) {
  if (c != nullptr) {
    alts_grpc_handshaker_client* client =
        reinterpret_cast<alts_grpc_handshaker_client*>(c);
    alts_grpc_handshaker_client_unref(client);
  }
}

size_t MaxNumberOfConcurrentHandshakes() {
  size_t max_concurrent_handshakes = 100;
  std::optional<std::string> env_var_max_concurrent_handshakes =
      grpc_core::GetEnv(kMaxConcurrentStreamsEnvironmentVariable);
  if (env_var_max_concurrent_handshakes.has_value()) {
    size_t effective_max_concurrent_handshakes = 100;
    if (absl::SimpleAtoi(*env_var_max_concurrent_handshakes,
                         &effective_max_concurrent_handshakes)) {
      max_concurrent_handshakes = effective_max_concurrent_handshakes;
    }
  }
  return max_concurrent_handshakes;
}
