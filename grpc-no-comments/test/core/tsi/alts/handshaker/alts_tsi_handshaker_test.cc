
// Copyright 2018 gRPC authors.

#include "src/core/tsi/alts/handshaker/alts_tsi_handshaker.h"

#include <grpc/grpc.h>
#include <grpc/support/sync.h>
#include <stdio.h>
#include <stdlib.h>

#include "gtest/gtest.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/tsi/alts/handshaker/alts_handshaker_client.h"
#include "src/core/tsi/alts/handshaker/alts_shared_resource.h"
#include "src/core/tsi/alts/handshaker/alts_tsi_handshaker_private.h"
#include "src/core/tsi/transport_security_grpc.h"
#include "src/core/util/thd.h"
#include "src/proto/grpc/gcp/altscontext.upb.h"
#include "test/core/test_util/test_config.h"
#include "test/core/tsi/alts/handshaker/alts_handshaker_service_api_test_lib.h"
#include "upb/base/string_view.h"
#include "upb/mem/arena.hpp"
#include "upb/message/internal/map.h"

#define ALTS_TSI_HANDSHAKER_TEST_RECV_BYTES "Hello World"
#define ALTS_TSI_HANDSHAKER_TEST_OUT_FRAME "Hello Google"
#define ALTS_TSI_HANDSHAKER_TEST_CONSUMED_BYTES "Hello "
#define ALTS_TSI_HANDSHAKER_TEST_REMAIN_BYTES "Google"
#define ALTS_TSI_HANDSHAKER_TEST_PEER_IDENTITY "chapi@service.google.com"
#define ALTS_TSI_HANDSHAKER_TEST_SECURITY_LEVEL "TSI_PRIVACY_AND_INTEGRITY"
#define ALTS_TSI_HANDSHAKER_TEST_KEY_DATA \
  "ABCDEFGHIJKLMNOPABCDEFGHIJKLMNOPABCDEFGHIJKL"
#define ALTS_TSI_HANDSHAKER_TEST_BUFFER_SIZE 100
#define ALTS_TSI_HANDSHAKER_TEST_SLEEP_TIME_IN_SECONDS 2
#define ALTS_TSI_HANDSHAKER_TEST_MAX_RPC_VERSION_MAJOR 3
#define ALTS_TSI_HANDSHAKER_TEST_MAX_RPC_VERSION_MINOR 2
#define ALTS_TSI_HANDSHAKER_TEST_MIN_RPC_VERSION_MAJOR 2
#define ALTS_TSI_HANDSHAKER_TEST_MIN_RPC_VERSION_MINOR 1
#define ALTS_TSI_HANDSHAKER_TEST_LOCAL_IDENTITY "chapilocal@service.google.com"
#define ALTS_TSI_HANDSHAKER_TEST_APPLICATION_PROTOCOL \
  "test application protocol"
#define ALTS_TSI_HANDSHAKER_TEST_RECORD_PROTOCOL "test record protocol"
#define ALTS_TSI_HANDSHAKER_TEST_MAX_FRAME_SIZE (2 * 1024 * 1024)
#define ALTS_TSI_HANDSHAKER_TEST_PEER_ATTRIBUTES_KEY "peer"
#define ALTS_TSI_HANDSHAKER_TEST_PEER_ATTRIBUTES_VALUE "attributes"
#define ALTS_TSI_HANDSHAKER_NEGOTIATED_TRANSPORT_PROTOCOL "foo"
#define ALTS_TSI_HANDSHAKER_PREFERRED_TRANSPORT_PROTOCOL "foo,bar,baz"

using grpc_core::internal::alts_handshaker_client_check_fields_for_testing;
using grpc_core::internal::alts_handshaker_client_get_handshaker_for_testing;
using grpc_core::internal::
    alts_handshaker_client_get_recv_buffer_addr_for_testing;
using grpc_core::internal::
    alts_handshaker_client_on_status_received_for_testing;
using grpc_core::internal::alts_handshaker_client_ref_for_testing;
using grpc_core::internal::alts_handshaker_client_set_cb_for_testing;
using grpc_core::internal::alts_handshaker_client_set_fields_for_testing;
using grpc_core::internal::alts_handshaker_client_set_recv_bytes_for_testing;
using grpc_core::internal::alts_tsi_handshaker_get_client_for_testing;
using grpc_core::internal::alts_tsi_handshaker_get_is_client_for_testing;
using grpc_core::internal::alts_tsi_handshaker_set_client_vtable_for_testing;
static bool should_handshaker_client_api_succeed = true;

typedef struct notification {
  gpr_cv cv;
  gpr_mu mu;
  bool notified;
} notification;

typedef enum {
  INVALID,
  FAILED,
  CLIENT_START,
  SERVER_START,
  CLIENT_NEXT,
  SERVER_NEXT,
} alts_handshaker_response_type;

static alts_handshaker_client* cb_event = nullptr;
static notification caller_to_tsi_notification;
static notification tsi_to_caller_notification;

static void notification_init(notification* n) {
  gpr_mu_init(&n->mu);
  gpr_cv_init(&n->cv);
  n->notified = false;
}

static void notification_destroy(notification* n) {
  gpr_mu_destroy(&n->mu);
  gpr_cv_destroy(&n->cv);
}

static void signal(notification* n) {
  gpr_mu_lock(&n->mu);
  n->notified = true;
  gpr_cv_signal(&n->cv);
  gpr_mu_unlock(&n->mu);
}

static void wait(notification* n) {
  gpr_mu_lock(&n->mu);
  while (!n->notified) {
    gpr_cv_wait(&n->cv, &n->mu, gpr_inf_future(GPR_CLOCK_REALTIME));
  }
  n->notified = false;
  gpr_mu_unlock(&n->mu);
}

static grpc_byte_buffer* generate_handshaker_response(
    alts_handshaker_response_type type) {
  upb::Arena arena;
  grpc_gcp_HandshakerResult* result;
  grpc_gcp_Identity* peer_identity;
  grpc_gcp_HandshakerResp* resp = grpc_gcp_HandshakerResp_new(arena.ptr());
  grpc_gcp_HandshakerStatus* status =
      grpc_gcp_HandshakerResp_mutable_status(resp, arena.ptr());
  grpc_gcp_HandshakerStatus_set_code(status, 0);
  grpc_gcp_Identity* local_identity;
  grpc_gcp_NegotiatedTransportProtocol* protocol;
  switch (type) {
    case INVALID:
      break;
    case CLIENT_START:
    case SERVER_START:
      grpc_gcp_HandshakerResp_set_out_frames(
          resp, upb_StringView_FromString(ALTS_TSI_HANDSHAKER_TEST_OUT_FRAME));
      break;
    case CLIENT_NEXT:
      grpc_gcp_HandshakerResp_set_out_frames(
          resp, upb_StringView_FromString(ALTS_TSI_HANDSHAKER_TEST_OUT_FRAME));
      grpc_gcp_HandshakerResp_set_bytes_consumed(
          resp, strlen(ALTS_TSI_HANDSHAKER_TEST_CONSUMED_BYTES));
      result = grpc_gcp_HandshakerResp_mutable_result(resp, arena.ptr());
      peer_identity =
          grpc_gcp_HandshakerResult_mutable_peer_identity(result, arena.ptr());
      grpc_gcp_Identity_attributes_set(
          peer_identity,
          upb_StringView_FromString(
              ALTS_TSI_HANDSHAKER_TEST_PEER_ATTRIBUTES_KEY),
          upb_StringView_FromString(
              ALTS_TSI_HANDSHAKER_TEST_PEER_ATTRIBUTES_VALUE),
          arena.ptr());
      grpc_gcp_Identity_set_service_account(
          peer_identity,
          upb_StringView_FromString(ALTS_TSI_HANDSHAKER_TEST_PEER_IDENTITY));
      grpc_gcp_HandshakerResult_set_key_data(
          result, upb_StringView_FromString(ALTS_TSI_HANDSHAKER_TEST_KEY_DATA));
      EXPECT_TRUE(grpc_gcp_handshaker_resp_set_peer_rpc_versions(
          resp, arena.ptr(), ALTS_TSI_HANDSHAKER_TEST_MAX_RPC_VERSION_MAJOR,
          ALTS_TSI_HANDSHAKER_TEST_MAX_RPC_VERSION_MINOR,
          ALTS_TSI_HANDSHAKER_TEST_MIN_RPC_VERSION_MAJOR,
          ALTS_TSI_HANDSHAKER_TEST_MIN_RPC_VERSION_MINOR));
      local_identity =
          grpc_gcp_HandshakerResult_mutable_local_identity(result, arena.ptr());
      grpc_gcp_Identity_set_service_account(
          local_identity,
          upb_StringView_FromString(ALTS_TSI_HANDSHAKER_TEST_LOCAL_IDENTITY));
      grpc_gcp_HandshakerResult_set_application_protocol(
          result, upb_StringView_FromString(
                      ALTS_TSI_HANDSHAKER_TEST_APPLICATION_PROTOCOL));
      grpc_gcp_HandshakerResult_set_record_protocol(
          result,
          upb_StringView_FromString(ALTS_TSI_HANDSHAKER_TEST_RECORD_PROTOCOL));
      grpc_gcp_HandshakerResult_set_max_frame_size(
          result, ALTS_TSI_HANDSHAKER_TEST_MAX_FRAME_SIZE);
      protocol = grpc_gcp_HandshakerResult_mutable_transport_protocol(
          result, arena.ptr());
      grpc_gcp_NegotiatedTransportProtocol_set_transport_protocol(
          protocol, upb_StringView_FromString(
                        ALTS_TSI_HANDSHAKER_NEGOTIATED_TRANSPORT_PROTOCOL));
      break;
    case SERVER_NEXT:
      grpc_gcp_HandshakerResp_set_bytes_consumed(
          resp, strlen(ALTS_TSI_HANDSHAKER_TEST_OUT_FRAME));
      result = grpc_gcp_HandshakerResp_mutable_result(resp, arena.ptr());
      peer_identity =
          grpc_gcp_HandshakerResult_mutable_peer_identity(result, arena.ptr());
      grpc_gcp_Identity_attributes_set(
          peer_identity,
          upb_StringView_FromString(
              ALTS_TSI_HANDSHAKER_TEST_PEER_ATTRIBUTES_KEY),
          upb_StringView_FromString(
              ALTS_TSI_HANDSHAKER_TEST_PEER_ATTRIBUTES_VALUE),
          arena.ptr());
      grpc_gcp_Identity_set_service_account(
          peer_identity,
          upb_StringView_FromString(ALTS_TSI_HANDSHAKER_TEST_PEER_IDENTITY));
      grpc_gcp_HandshakerResult_set_key_data(
          result, upb_StringView_FromString(ALTS_TSI_HANDSHAKER_TEST_KEY_DATA));
      EXPECT_TRUE(grpc_gcp_handshaker_resp_set_peer_rpc_versions(
          resp, arena.ptr(), ALTS_TSI_HANDSHAKER_TEST_MAX_RPC_VERSION_MAJOR,
          ALTS_TSI_HANDSHAKER_TEST_MAX_RPC_VERSION_MINOR,
          ALTS_TSI_HANDSHAKER_TEST_MIN_RPC_VERSION_MAJOR,
          ALTS_TSI_HANDSHAKER_TEST_MIN_RPC_VERSION_MINOR));
      local_identity =
          grpc_gcp_HandshakerResult_mutable_local_identity(result, arena.ptr());
      grpc_gcp_Identity_set_service_account(
          local_identity,
          upb_StringView_FromString(ALTS_TSI_HANDSHAKER_TEST_LOCAL_IDENTITY));
      grpc_gcp_HandshakerResult_set_application_protocol(
          result, upb_StringView_FromString(
                      ALTS_TSI_HANDSHAKER_TEST_APPLICATION_PROTOCOL));
      grpc_gcp_HandshakerResult_set_record_protocol(
          result,
          upb_StringView_FromString(ALTS_TSI_HANDSHAKER_TEST_RECORD_PROTOCOL));
      protocol = grpc_gcp_HandshakerResult_mutable_transport_protocol(
          result, arena.ptr());
      grpc_gcp_NegotiatedTransportProtocol_set_transport_protocol(
          protocol, upb_StringView_FromString(
                        ALTS_TSI_HANDSHAKER_NEGOTIATED_TRANSPORT_PROTOCOL));
      break;
    case FAILED:
      grpc_gcp_HandshakerStatus_set_code(status, 3 );
      break;
  }
  size_t buf_len;
  char* buf = grpc_gcp_HandshakerResp_serialize(resp, arena.ptr(), &buf_len);
  grpc_slice slice = grpc_slice_from_copied_buffer(buf, buf_len);
  if (type == INVALID) {
    grpc_slice bad_slice =
        grpc_slice_split_head(&slice, GRPC_SLICE_LENGTH(slice) - 1);
    grpc_slice_unref(slice);
    slice = grpc_slice_ref(bad_slice);
    grpc_slice_unref(bad_slice);
  }
  grpc_byte_buffer* buffer =
      grpc_raw_byte_buffer_create(&slice, 1 );
  grpc_slice_unref(slice);
  return buffer;
}

static void check_must_not_be_called(tsi_result , void* ,
                                     const unsigned char* ,
                                     size_t ,
                                     tsi_handshaker_result* ) {
  ASSERT_TRUE(0);
}

static void on_client_start_success_cb(tsi_result status, void* user_data,
                                       const unsigned char* bytes_to_send,
                                       size_t bytes_to_send_size,
                                       tsi_handshaker_result* result) {
  ASSERT_EQ(status, TSI_OK);
  ASSERT_EQ(user_data, nullptr);
  ASSERT_EQ(bytes_to_send_size, strlen(ALTS_TSI_HANDSHAKER_TEST_OUT_FRAME));
  ASSERT_EQ(memcmp(bytes_to_send, ALTS_TSI_HANDSHAKER_TEST_OUT_FRAME,
                   bytes_to_send_size),
            0);
  ASSERT_EQ(result, nullptr);

  tsi_peer peer;
  ASSERT_EQ(tsi_handshaker_result_extract_peer(result, &peer),
            TSI_INVALID_ARGUMENT);

  tsi_frame_protector* protector = nullptr;
  ASSERT_EQ(
      tsi_handshaker_result_create_frame_protector(result, nullptr, &protector),
      TSI_INVALID_ARGUMENT);

  const unsigned char* unused_bytes = nullptr;
  size_t unused_bytes_size = 0;
  ASSERT_EQ(tsi_handshaker_result_get_unused_bytes(result, &unused_bytes,
                                                   &unused_bytes_size),
            TSI_INVALID_ARGUMENT);
  signal(&tsi_to_caller_notification);
}

static void on_server_start_success_cb(tsi_result status, void* user_data,
                                       const unsigned char* bytes_to_send,
                                       size_t bytes_to_send_size,
                                       tsi_handshaker_result* result) {
  ASSERT_EQ(status, TSI_OK);
  ASSERT_EQ(user_data, nullptr);
  ASSERT_EQ(bytes_to_send_size, strlen(ALTS_TSI_HANDSHAKER_TEST_OUT_FRAME));
  ASSERT_EQ(memcmp(bytes_to_send, ALTS_TSI_HANDSHAKER_TEST_OUT_FRAME,
                   bytes_to_send_size),
            0);
  ASSERT_EQ(result, nullptr);

  tsi_peer peer;
  ASSERT_EQ(tsi_handshaker_result_extract_peer(result, &peer),
            TSI_INVALID_ARGUMENT);

  tsi_frame_protector* protector = nullptr;
  ASSERT_EQ(
      tsi_handshaker_result_create_frame_protector(result, nullptr, &protector),
      TSI_INVALID_ARGUMENT);

  const unsigned char* unused_bytes = nullptr;
  size_t unused_bytes_size = 0;
  ASSERT_EQ(tsi_handshaker_result_get_unused_bytes(result, &unused_bytes,
                                                   &unused_bytes_size),
            TSI_INVALID_ARGUMENT);
  signal(&tsi_to_caller_notification);
}

static void on_client_next_success_cb(tsi_result status, void* user_data,
                                      const unsigned char* bytes_to_send,
                                      size_t bytes_to_send_size,
                                      tsi_handshaker_result* result) {
  ASSERT_EQ(status, TSI_OK);
  ASSERT_EQ(user_data, nullptr);
  ASSERT_EQ(bytes_to_send_size, strlen(ALTS_TSI_HANDSHAKER_TEST_OUT_FRAME));
  ASSERT_EQ(memcmp(bytes_to_send, ALTS_TSI_HANDSHAKER_TEST_OUT_FRAME,
                   bytes_to_send_size),
            0);
  ASSERT_NE(result, nullptr);

  tsi_zero_copy_grpc_protector* zero_copy_protector = nullptr;
  ASSERT_EQ(tsi_handshaker_result_create_zero_copy_grpc_protector(
                result, nullptr, &zero_copy_protector),
            TSI_OK);
  size_t actual_max_frame_size;
  tsi_zero_copy_grpc_protector_max_frame_size(zero_copy_protector,
                                              &actual_max_frame_size);
  ASSERT_EQ(actual_max_frame_size, kTsiAltsMaxFrameSize);
  tsi_zero_copy_grpc_protector_destroy(zero_copy_protector);

  tsi_peer peer;
  ASSERT_EQ(tsi_handshaker_result_extract_peer(result, &peer), TSI_OK);
  ASSERT_EQ(peer.property_count, kTsiAltsMinNumOfPeerProperties + 1);
  ASSERT_EQ(memcmp(TSI_ALTS_CERTIFICATE_TYPE, peer.properties[0].value.data,
                   peer.properties[0].value.length),
            0);
  ASSERT_EQ(
      memcmp(ALTS_TSI_HANDSHAKER_TEST_PEER_IDENTITY,
             peer.properties[1].value.data, peer.properties[1].value.length),
      0);

  upb::Arena context_arena;
  grpc_gcp_AltsContext* ctx = grpc_gcp_AltsContext_parse(
      peer.properties[3].value.data, peer.properties[3].value.length,
      context_arena.ptr());
  ASSERT_NE(ctx, nullptr);
  upb_StringView application_protocol =
      grpc_gcp_AltsContext_application_protocol(ctx);
  upb_StringView record_protocol = grpc_gcp_AltsContext_record_protocol(ctx);
  upb_StringView peer_account = grpc_gcp_AltsContext_peer_service_account(ctx);
  upb_StringView local_account =
      grpc_gcp_AltsContext_local_service_account(ctx);
  ASSERT_EQ(memcmp(ALTS_TSI_HANDSHAKER_TEST_APPLICATION_PROTOCOL,
                   application_protocol.data, application_protocol.size),
            0);
  ASSERT_EQ(memcmp(ALTS_TSI_HANDSHAKER_TEST_RECORD_PROTOCOL,
                   record_protocol.data, record_protocol.size),
            0);
  ASSERT_EQ(memcmp(ALTS_TSI_HANDSHAKER_TEST_PEER_IDENTITY, peer_account.data,
                   peer_account.size),
            0);
  ASSERT_EQ(memcmp(ALTS_TSI_HANDSHAKER_TEST_LOCAL_IDENTITY, local_account.data,
                   local_account.size),
            0);
  size_t iter = kUpb_Map_Begin;
  upb_StringView key;
  upb_StringView val;
  while (grpc_gcp_AltsContext_peer_attributes_next(ctx, &key, &val, &iter)) {
    ASSERT_TRUE(upb_StringView_IsEqual(
        key, upb_StringView_FromString(
                 ALTS_TSI_HANDSHAKER_TEST_PEER_ATTRIBUTES_KEY)));
    ASSERT_TRUE(upb_StringView_IsEqual(
        val, upb_StringView_FromString(
                 ALTS_TSI_HANDSHAKER_TEST_PEER_ATTRIBUTES_VALUE)));
  }

  ASSERT_EQ(
      memcmp(ALTS_TSI_HANDSHAKER_TEST_SECURITY_LEVEL,
             peer.properties[4].value.data, peer.properties[4].value.length),
      0);
  tsi_peer_destruct(&peer);

  const unsigned char* bytes = nullptr;
  size_t bytes_size = 0;
  ASSERT_EQ(tsi_handshaker_result_get_unused_bytes(result, &bytes, &bytes_size),
            TSI_OK);
  ASSERT_EQ(bytes_size, strlen(ALTS_TSI_HANDSHAKER_TEST_REMAIN_BYTES));
  ASSERT_EQ(memcmp(bytes, ALTS_TSI_HANDSHAKER_TEST_REMAIN_BYTES, bytes_size),
            0);

  tsi_frame_protector* protector = nullptr;
  ASSERT_EQ(
      tsi_handshaker_result_create_frame_protector(result, nullptr, &protector),
      TSI_OK);
  ASSERT_NE(protector, nullptr);
  tsi_frame_protector_destroy(protector);
  tsi_handshaker_result_destroy(result);
  signal(&tsi_to_caller_notification);
}

static void on_server_next_success_cb(tsi_result status, void* user_data,
                                      const unsigned char* bytes_to_send,
                                      size_t bytes_to_send_size,
                                      tsi_handshaker_result* result) {
  ASSERT_EQ(status, TSI_OK);
  ASSERT_EQ(user_data, nullptr);
  ASSERT_EQ(bytes_to_send_size, 0);
  ASSERT_EQ(bytes_to_send, nullptr);
  ASSERT_NE(result, nullptr);

  tsi_zero_copy_grpc_protector* zero_copy_protector = nullptr;
  size_t user_specified_max_frame_size =
      ALTS_TSI_HANDSHAKER_TEST_MAX_FRAME_SIZE;
  ASSERT_EQ(tsi_handshaker_result_create_zero_copy_grpc_protector(
                result, &user_specified_max_frame_size, &zero_copy_protector),
            TSI_OK);
  size_t actual_max_frame_size;
  tsi_zero_copy_grpc_protector_max_frame_size(zero_copy_protector,
                                              &actual_max_frame_size);
  ASSERT_EQ(actual_max_frame_size, kTsiAltsMinFrameSize);
  tsi_zero_copy_grpc_protector_destroy(zero_copy_protector);

  tsi_peer peer;
  ASSERT_EQ(tsi_handshaker_result_extract_peer(result, &peer), TSI_OK);
  ASSERT_EQ(peer.property_count, kTsiAltsMinNumOfPeerProperties + 1);
  ASSERT_EQ(memcmp(TSI_ALTS_CERTIFICATE_TYPE, peer.properties[0].value.data,
                   peer.properties[0].value.length),
            0);
  ASSERT_EQ(
      memcmp(ALTS_TSI_HANDSHAKER_TEST_PEER_IDENTITY,
             peer.properties[1].value.data, peer.properties[1].value.length),
      0);

  upb::Arena context_arena;
  grpc_gcp_AltsContext* ctx = grpc_gcp_AltsContext_parse(
      peer.properties[3].value.data, peer.properties[3].value.length,
      context_arena.ptr());
  ASSERT_NE(ctx, nullptr);
  upb_StringView application_protocol =
      grpc_gcp_AltsContext_application_protocol(ctx);
  upb_StringView record_protocol = grpc_gcp_AltsContext_record_protocol(ctx);
  upb_StringView peer_account = grpc_gcp_AltsContext_peer_service_account(ctx);
  upb_StringView local_account =
      grpc_gcp_AltsContext_local_service_account(ctx);
  ASSERT_EQ(memcmp(ALTS_TSI_HANDSHAKER_TEST_APPLICATION_PROTOCOL,
                   application_protocol.data, application_protocol.size),
            0);
  ASSERT_EQ(memcmp(ALTS_TSI_HANDSHAKER_TEST_RECORD_PROTOCOL,
                   record_protocol.data, record_protocol.size),
            0);
  ASSERT_EQ(memcmp(ALTS_TSI_HANDSHAKER_TEST_PEER_IDENTITY, peer_account.data,
                   peer_account.size),
            0);
  ASSERT_EQ(memcmp(ALTS_TSI_HANDSHAKER_TEST_LOCAL_IDENTITY, local_account.data,
                   local_account.size),
            0);
  size_t iter = kUpb_Map_Begin;
  upb_StringView key;
  upb_StringView val;
  while (grpc_gcp_AltsContext_peer_attributes_next(ctx, &key, &val, &iter)) {
    ASSERT_TRUE(upb_StringView_IsEqual(
        key, upb_StringView_FromString(
                 ALTS_TSI_HANDSHAKER_TEST_PEER_ATTRIBUTES_KEY)));
    ASSERT_TRUE(upb_StringView_IsEqual(
        val, upb_StringView_FromString(
                 ALTS_TSI_HANDSHAKER_TEST_PEER_ATTRIBUTES_VALUE)));
  }

  ASSERT_EQ(
      memcmp(ALTS_TSI_HANDSHAKER_TEST_SECURITY_LEVEL,
             peer.properties[4].value.data, peer.properties[4].value.length),
      0);

  tsi_peer_destruct(&peer);

  const unsigned char* bytes = nullptr;
  size_t bytes_size = 0;
  ASSERT_EQ(tsi_handshaker_result_get_unused_bytes(result, &bytes, &bytes_size),
            TSI_OK);
  ASSERT_EQ(bytes_size, 0);
  ASSERT_EQ(bytes, nullptr);

  tsi_frame_protector* protector = nullptr;
  ASSERT_EQ(
      tsi_handshaker_result_create_frame_protector(result, nullptr, &protector),
      TSI_OK);
  ASSERT_NE(protector, nullptr);
  tsi_frame_protector_destroy(protector);
  tsi_handshaker_result_destroy(result);
  signal(&tsi_to_caller_notification);
}

static tsi_result mock_client_start(alts_handshaker_client* client) {
  if (!should_handshaker_client_api_succeed) {
    return TSI_INTERNAL_ERROR;
  }

  alts_handshaker_client_check_fields_for_testing(
      client, on_client_start_success_cb, nullptr, true, nullptr);

  grpc_byte_buffer** recv_buffer_ptr =
      alts_handshaker_client_get_recv_buffer_addr_for_testing(client);
  *recv_buffer_ptr = generate_handshaker_response(CLIENT_START);
  cb_event = client;
  signal(&caller_to_tsi_notification);
  return TSI_OK;
}

static void mock_shutdown(alts_handshaker_client* ) {}

static tsi_result mock_server_start(alts_handshaker_client* client,
                                    grpc_slice* bytes_received) {
  if (!should_handshaker_client_api_succeed) {
    return TSI_INTERNAL_ERROR;
  }
  alts_handshaker_client_check_fields_for_testing(
      client, on_server_start_success_cb, nullptr, true, nullptr);
  EXPECT_EQ(memcmp(GRPC_SLICE_START_PTR(*bytes_received),
                   ALTS_TSI_HANDSHAKER_TEST_RECV_BYTES,
                   GRPC_SLICE_LENGTH(*bytes_received)),
            0);

  grpc_byte_buffer** recv_buffer_ptr =
      alts_handshaker_client_get_recv_buffer_addr_for_testing(client);
  *recv_buffer_ptr = generate_handshaker_response(SERVER_START);
  cb_event = client;
  signal(&caller_to_tsi_notification);
  return TSI_OK;
}

static tsi_result mock_next(alts_handshaker_client* client,
                            grpc_slice* bytes_received) {
  if (!should_handshaker_client_api_succeed) {
    return TSI_INTERNAL_ERROR;
  }
  alts_tsi_handshaker* handshaker =
      alts_handshaker_client_get_handshaker_for_testing(client);
  bool is_client = alts_tsi_handshaker_get_is_client_for_testing(handshaker);
  tsi_handshaker_on_next_done_cb cb =
      is_client ? on_client_next_success_cb : on_server_next_success_cb;
  alts_handshaker_client_set_cb_for_testing(client, cb);
  alts_handshaker_client_set_recv_bytes_for_testing(client, bytes_received);
  alts_handshaker_client_check_fields_for_testing(client, cb, nullptr, true,
                                                  bytes_received);
  EXPECT_NE(bytes_received, nullptr);
  EXPECT_EQ(memcmp(GRPC_SLICE_START_PTR(*bytes_received),
                   ALTS_TSI_HANDSHAKER_TEST_RECV_BYTES,
                   GRPC_SLICE_LENGTH(*bytes_received)),
            0);

  grpc_slice out_frame =
      grpc_slice_from_static_string(ALTS_TSI_HANDSHAKER_TEST_OUT_FRAME);
  grpc_byte_buffer** recv_buffer_ptr =
      alts_handshaker_client_get_recv_buffer_addr_for_testing(client);
  *recv_buffer_ptr = is_client ? generate_handshaker_response(CLIENT_NEXT)
                               : generate_handshaker_response(SERVER_NEXT);
  alts_handshaker_client_set_recv_bytes_for_testing(client, &out_frame);
  cb_event = client;
  signal(&caller_to_tsi_notification);
  grpc_slice_unref(out_frame);
  return TSI_OK;
}

static void mock_destruct(alts_handshaker_client* ) {}

static alts_handshaker_client_vtable vtable = {mock_client_start,
                                               mock_server_start, mock_next,
                                               mock_shutdown, mock_destruct};

static tsi_handshaker* create_test_handshaker(bool is_client) {
  tsi_handshaker* handshaker = nullptr;
  grpc_alts_credentials_options* options =
      grpc_alts_credentials_client_options_create();
  alts_tsi_handshaker_create(options, "target_name",
                             ALTS_HANDSHAKER_SERVICE_URL_FOR_TESTING, is_client,
                             nullptr, &handshaker, 0,
                             ALTS_TSI_HANDSHAKER_PREFERRED_TRANSPORT_PROTOCOL);
  alts_tsi_handshaker* alts_handshaker =
      reinterpret_cast<alts_tsi_handshaker*>(handshaker);
  alts_tsi_handshaker_set_client_vtable_for_testing(alts_handshaker, &vtable);
  grpc_alts_credentials_options_destroy(options);
  return handshaker;
}

static void run_tsi_handshaker_destroy_with_exec_ctx(
    tsi_handshaker* handshaker) {
  grpc_core::ExecCtx exec_ctx;
  tsi_handshaker_destroy(handshaker);
}

TEST(AltsTsiHandshakerTest, CheckHandshakerNextInvalidInput) {
  should_handshaker_client_api_succeed = true;

  tsi_handshaker* handshaker = create_test_handshaker(true);

  ASSERT_EQ(tsi_handshaker_next(nullptr, nullptr, 0, nullptr, nullptr, nullptr,
                                check_must_not_be_called, nullptr),
            TSI_INVALID_ARGUMENT);

  ASSERT_EQ(tsi_handshaker_next(handshaker, nullptr, 0, nullptr, nullptr,
                                nullptr, nullptr, nullptr),
            TSI_INVALID_ARGUMENT);

  run_tsi_handshaker_destroy_with_exec_ctx(handshaker);
}

TEST(AltsTsiHandshakerTest, CheckHandshakerShutdownInvalidInput) {
  should_handshaker_client_api_succeed = false;

  tsi_handshaker* handshaker = create_test_handshaker(true );

  tsi_handshaker_shutdown(nullptr);

  run_tsi_handshaker_destroy_with_exec_ctx(handshaker);
}

static void check_handshaker_next_success() {

  tsi_handshaker* client_handshaker =
      create_test_handshaker(true );
  tsi_handshaker* server_handshaker =
      create_test_handshaker(false );

  ASSERT_EQ(tsi_handshaker_next(client_handshaker, nullptr, 0, nullptr, nullptr,
                                nullptr, on_client_start_success_cb, nullptr),
            TSI_ASYNC);
  wait(&tsi_to_caller_notification);

  ASSERT_EQ(tsi_handshaker_next(
                client_handshaker,
                (const unsigned char*)ALTS_TSI_HANDSHAKER_TEST_RECV_BYTES,
                strlen(ALTS_TSI_HANDSHAKER_TEST_RECV_BYTES), nullptr, nullptr,
                nullptr, on_client_next_success_cb, nullptr),
            TSI_ASYNC);
  wait(&tsi_to_caller_notification);

  ASSERT_EQ(tsi_handshaker_next(
                server_handshaker,
                (const unsigned char*)ALTS_TSI_HANDSHAKER_TEST_RECV_BYTES,
                strlen(ALTS_TSI_HANDSHAKER_TEST_RECV_BYTES), nullptr, nullptr,
                nullptr, on_server_start_success_cb, nullptr),
            TSI_ASYNC);
  wait(&tsi_to_caller_notification);

  ASSERT_EQ(tsi_handshaker_next(
                server_handshaker,
                (const unsigned char*)ALTS_TSI_HANDSHAKER_TEST_RECV_BYTES,
                strlen(ALTS_TSI_HANDSHAKER_TEST_RECV_BYTES), nullptr, nullptr,
                nullptr, on_server_next_success_cb, nullptr),
            TSI_ASYNC);
  wait(&tsi_to_caller_notification);

  run_tsi_handshaker_destroy_with_exec_ctx(server_handshaker);
  run_tsi_handshaker_destroy_with_exec_ctx(client_handshaker);
}

static void check_handshaker_next_with_shutdown() {
  tsi_handshaker* handshaker = create_test_handshaker(true );

  ASSERT_EQ(tsi_handshaker_next(handshaker, nullptr, 0, nullptr, nullptr,
                                nullptr, on_client_start_success_cb, nullptr),
            TSI_ASYNC);
  wait(&tsi_to_caller_notification);
  tsi_handshaker_shutdown(handshaker);
  ASSERT_EQ(
      tsi_handshaker_next(
          handshaker, (const unsigned char*)ALTS_TSI_HANDSHAKER_TEST_RECV_BYTES,
          strlen(ALTS_TSI_HANDSHAKER_TEST_RECV_BYTES), nullptr, nullptr,
          nullptr, on_client_next_success_cb, nullptr),
      TSI_HANDSHAKE_SHUTDOWN);

  run_tsi_handshaker_destroy_with_exec_ctx(handshaker);
}

static void check_handle_response_with_shutdown(void* ) {
  wait(&caller_to_tsi_notification);
  alts_handshaker_client_handle_response(cb_event, true );
}

TEST(AltsTsiHandshakerTest, CheckHandshakerNextFailure) {
  should_handshaker_client_api_succeed = false;

  tsi_handshaker* client_handshaker =
      create_test_handshaker(true );
  tsi_handshaker* server_handshaker =
      create_test_handshaker(false );

  ASSERT_EQ(tsi_handshaker_next(client_handshaker, nullptr, 0, nullptr, nullptr,
                                nullptr, check_must_not_be_called, nullptr),
            TSI_INTERNAL_ERROR);

  ASSERT_EQ(tsi_handshaker_next(
                server_handshaker,
                (const unsigned char*)ALTS_TSI_HANDSHAKER_TEST_RECV_BYTES,
                strlen(ALTS_TSI_HANDSHAKER_TEST_RECV_BYTES), nullptr, nullptr,
                nullptr, check_must_not_be_called, nullptr),
            TSI_INTERNAL_ERROR);

  ASSERT_EQ(tsi_handshaker_next(
                server_handshaker,
                (const unsigned char*)ALTS_TSI_HANDSHAKER_TEST_RECV_BYTES,
                strlen(ALTS_TSI_HANDSHAKER_TEST_RECV_BYTES), nullptr, nullptr,
                nullptr, check_must_not_be_called, nullptr),
            TSI_INTERNAL_ERROR);

  ASSERT_EQ(tsi_handshaker_next(
                client_handshaker,
                (const unsigned char*)ALTS_TSI_HANDSHAKER_TEST_RECV_BYTES,
                strlen(ALTS_TSI_HANDSHAKER_TEST_RECV_BYTES), nullptr, nullptr,
                nullptr, check_must_not_be_called, nullptr),
            TSI_INTERNAL_ERROR);

  run_tsi_handshaker_destroy_with_exec_ctx(server_handshaker);
  run_tsi_handshaker_destroy_with_exec_ctx(client_handshaker);
}

TEST(AltsTsiHandshakerTest, CheckHandshakerNextIncomplete) {
  should_handshaker_client_api_succeed = false;
  tsi_handshaker* server_handshaker =
      create_test_handshaker(false );

  ASSERT_EQ(tsi_handshaker_next(server_handshaker, nullptr, 0, nullptr, nullptr,
                                nullptr, check_must_not_be_called, nullptr),
            TSI_INCOMPLETE_DATA);

  run_tsi_handshaker_destroy_with_exec_ctx(server_handshaker);
}

static void on_invalid_input_cb(tsi_result status, void* user_data,
                                const unsigned char* bytes_to_send,
                                size_t bytes_to_send_size,
                                tsi_handshaker_result* result) {
  ASSERT_EQ(status, TSI_INTERNAL_ERROR);
  ASSERT_EQ(user_data, nullptr);
  ASSERT_EQ(bytes_to_send, nullptr);
  ASSERT_EQ(bytes_to_send_size, 0);
  ASSERT_EQ(result, nullptr);
}

static void on_failed_grpc_call_cb(tsi_result status, void* user_data,
                                   const unsigned char* bytes_to_send,
                                   size_t bytes_to_send_size,
                                   tsi_handshaker_result* result) {
  ASSERT_EQ(status, TSI_INTERNAL_ERROR);
  ASSERT_EQ(user_data, nullptr);
  ASSERT_EQ(bytes_to_send, nullptr);
  ASSERT_EQ(bytes_to_send_size, 0);
  ASSERT_EQ(result, nullptr);
}

TEST(AltsTsiHandshakerTest, CheckHandleResponseNullptrHandshaker) {
  should_handshaker_client_api_succeed = false;

  notification_init(&caller_to_tsi_notification);
  notification_init(&tsi_to_caller_notification);

  tsi_handshaker* handshaker = create_test_handshaker(true );
  tsi_handshaker_next(handshaker, nullptr, 0, nullptr, nullptr, nullptr,
                      on_client_start_success_cb, nullptr);
  alts_tsi_handshaker* alts_handshaker =
      reinterpret_cast<alts_tsi_handshaker*>(handshaker);
  grpc_slice slice = grpc_empty_slice();
  grpc_byte_buffer* recv_buffer = grpc_raw_byte_buffer_create(&slice, 1);
  alts_handshaker_client* client =
      alts_tsi_handshaker_get_client_for_testing(alts_handshaker);

  alts_handshaker_client_set_fields_for_testing(
      client, nullptr, on_invalid_input_cb, nullptr, recv_buffer,
      false);
  alts_handshaker_client_handle_response(client, true);
  // Note: here and elsewhere in this test, we first ref the handshaker in order

  alts_handshaker_client_ref_for_testing(client);
  {
    grpc_core::ExecCtx exec_ctx;
    alts_handshaker_client_on_status_received_for_testing(
        client, GRPC_STATUS_OK, absl::OkStatus());
  }

  grpc_slice_unref(slice);
  run_tsi_handshaker_destroy_with_exec_ctx(handshaker);
  notification_destroy(&caller_to_tsi_notification);
  notification_destroy(&tsi_to_caller_notification);
}

TEST(AltsTsiHandshakerTest, CheckHandleResponseNullptrRecvBytes) {
  should_handshaker_client_api_succeed = false;

  notification_init(&caller_to_tsi_notification);
  notification_init(&tsi_to_caller_notification);

  tsi_handshaker* handshaker = create_test_handshaker(true );
  tsi_handshaker_next(handshaker, nullptr, 0, nullptr, nullptr, nullptr,
                      on_client_start_success_cb, nullptr);
  alts_tsi_handshaker* alts_handshaker =
      reinterpret_cast<alts_tsi_handshaker*>(handshaker);
  alts_handshaker_client* client =
      alts_tsi_handshaker_get_client_for_testing(alts_handshaker);

  alts_handshaker_client_set_fields_for_testing(
      client, alts_handshaker, on_invalid_input_cb, nullptr, nullptr,
      false);
  alts_handshaker_client_handle_response(client, true);
  alts_handshaker_client_ref_for_testing(client);
  {
    grpc_core::ExecCtx exec_ctx;
    alts_handshaker_client_on_status_received_for_testing(
        client, GRPC_STATUS_OK, absl::OkStatus());
  }

  run_tsi_handshaker_destroy_with_exec_ctx(handshaker);
  notification_destroy(&caller_to_tsi_notification);
  notification_destroy(&tsi_to_caller_notification);
}

TEST(AltsTsiHandshakerTest,
     CheckHandleResponseFailedGrpcCallToHandshakerService) {
  should_handshaker_client_api_succeed = false;

  notification_init(&caller_to_tsi_notification);
  notification_init(&tsi_to_caller_notification);

  tsi_handshaker* handshaker = create_test_handshaker(true );
  tsi_handshaker_next(handshaker, nullptr, 0, nullptr, nullptr, nullptr,
                      on_client_start_success_cb, nullptr);
  alts_tsi_handshaker* alts_handshaker =
      reinterpret_cast<alts_tsi_handshaker*>(handshaker);
  grpc_slice slice = grpc_empty_slice();
  grpc_byte_buffer* recv_buffer = grpc_raw_byte_buffer_create(&slice, 1);
  alts_handshaker_client* client =
      alts_tsi_handshaker_get_client_for_testing(alts_handshaker);

  alts_handshaker_client_set_fields_for_testing(
      client, alts_handshaker, on_failed_grpc_call_cb, nullptr, recv_buffer,
      true);
  alts_handshaker_client_handle_response(client, true);
  alts_handshaker_client_ref_for_testing(client);
  {
    grpc_core::ExecCtx exec_ctx;
    alts_handshaker_client_on_status_received_for_testing(
        client, GRPC_STATUS_UNKNOWN, absl::OkStatus());
  }

  grpc_slice_unref(slice);
  run_tsi_handshaker_destroy_with_exec_ctx(handshaker);
  notification_destroy(&caller_to_tsi_notification);
  notification_destroy(&tsi_to_caller_notification);
}

TEST(AltsTsiHandshakerTest,
     CheckHandleResponseFailedRecvMessageFromHandshakerService) {
  should_handshaker_client_api_succeed = false;

  notification_init(&caller_to_tsi_notification);
  notification_init(&tsi_to_caller_notification);

  tsi_handshaker* handshaker = create_test_handshaker(true );
  tsi_handshaker_next(handshaker, nullptr, 0, nullptr, nullptr, nullptr,
                      on_client_start_success_cb, nullptr);
  alts_tsi_handshaker* alts_handshaker =
      reinterpret_cast<alts_tsi_handshaker*>(handshaker);
  grpc_slice slice = grpc_empty_slice();
  grpc_byte_buffer* recv_buffer = grpc_raw_byte_buffer_create(&slice, 1);
  alts_handshaker_client* client =
      alts_tsi_handshaker_get_client_for_testing(alts_handshaker);

  alts_handshaker_client_set_fields_for_testing(
      client, alts_handshaker, on_failed_grpc_call_cb, nullptr, recv_buffer,
      false);
  alts_handshaker_client_handle_response(client, false);
  alts_handshaker_client_ref_for_testing(client);
  {
    grpc_core::ExecCtx exec_ctx;
    alts_handshaker_client_on_status_received_for_testing(
        client, GRPC_STATUS_OK, absl::OkStatus());
  }

  grpc_slice_unref(slice);
  run_tsi_handshaker_destroy_with_exec_ctx(handshaker);
  notification_destroy(&caller_to_tsi_notification);
  notification_destroy(&tsi_to_caller_notification);
}

static void on_invalid_resp_cb(tsi_result status, void* user_data,
                               const unsigned char* bytes_to_send,
                               size_t bytes_to_send_size,
                               tsi_handshaker_result* result) {
  ASSERT_EQ(status, TSI_DATA_CORRUPTED);
  ASSERT_EQ(user_data, nullptr);
  ASSERT_EQ(bytes_to_send, nullptr);
  ASSERT_EQ(bytes_to_send_size, 0);
  ASSERT_EQ(result, nullptr);
}

TEST(AltsTsiHandshakerTest, CheckHandleResponseInvalidResp) {
  should_handshaker_client_api_succeed = false;

  notification_init(&caller_to_tsi_notification);
  notification_init(&tsi_to_caller_notification);

  tsi_handshaker* handshaker = create_test_handshaker(true );
  tsi_handshaker_next(handshaker, nullptr, 0, nullptr, nullptr, nullptr,
                      on_client_start_success_cb, nullptr);
  alts_tsi_handshaker* alts_handshaker =
      reinterpret_cast<alts_tsi_handshaker*>(handshaker);
  alts_handshaker_client* client =
      alts_tsi_handshaker_get_client_for_testing(alts_handshaker);

  grpc_byte_buffer* recv_buffer = generate_handshaker_response(INVALID);
  alts_handshaker_client_set_fields_for_testing(
      client, alts_handshaker, on_invalid_resp_cb, nullptr, recv_buffer,
      false);
  alts_handshaker_client_handle_response(client, true);
  alts_handshaker_client_ref_for_testing(client);
  {
    grpc_core::ExecCtx exec_ctx;
    alts_handshaker_client_on_status_received_for_testing(
        client, GRPC_STATUS_OK, absl::OkStatus());
  }

  run_tsi_handshaker_destroy_with_exec_ctx(handshaker);
  notification_destroy(&caller_to_tsi_notification);
  notification_destroy(&tsi_to_caller_notification);
}

static void check_handle_response_success(void* ) {

  wait(&caller_to_tsi_notification);
  alts_handshaker_client_handle_response(cb_event, true );

  wait(&caller_to_tsi_notification);
  alts_handshaker_client_handle_response(cb_event, true );
  alts_handshaker_client_ref_for_testing(cb_event);
  {
    grpc_core::ExecCtx exec_ctx;
    alts_handshaker_client_on_status_received_for_testing(
        cb_event, GRPC_STATUS_OK, absl::OkStatus());
  }

  wait(&caller_to_tsi_notification);
  alts_handshaker_client_handle_response(cb_event, true );

  wait(&caller_to_tsi_notification);
  alts_handshaker_client_handle_response(cb_event, true );
  alts_handshaker_client_ref_for_testing(cb_event);
  {
    grpc_core::ExecCtx exec_ctx;
    alts_handshaker_client_on_status_received_for_testing(
        cb_event, GRPC_STATUS_OK, absl::OkStatus());
  }
}

static void on_failed_resp_cb(tsi_result status, void* user_data,
                              const unsigned char* bytes_to_send,
                              size_t bytes_to_send_size,
                              tsi_handshaker_result* result) {
  ASSERT_EQ(status, TSI_INVALID_ARGUMENT);
  ASSERT_EQ(user_data, nullptr);
  ASSERT_EQ(bytes_to_send, nullptr);
  ASSERT_EQ(bytes_to_send_size, 0);
  ASSERT_EQ(result, nullptr);
}

TEST(AltsTsiHandshakerTest, CheckHandleResponseFailure) {
  should_handshaker_client_api_succeed = false;

  notification_init(&caller_to_tsi_notification);
  notification_init(&tsi_to_caller_notification);

  tsi_handshaker* handshaker = create_test_handshaker(true );
  tsi_handshaker_next(handshaker, nullptr, 0, nullptr, nullptr, nullptr,
                      on_client_start_success_cb, nullptr);
  alts_tsi_handshaker* alts_handshaker =
      reinterpret_cast<alts_tsi_handshaker*>(handshaker);
  alts_handshaker_client* client =
      alts_tsi_handshaker_get_client_for_testing(alts_handshaker);

  grpc_byte_buffer* recv_buffer = generate_handshaker_response(FAILED);
  alts_handshaker_client_set_fields_for_testing(
      client, alts_handshaker, on_failed_resp_cb, nullptr, recv_buffer,
      false);
  alts_handshaker_client_handle_response(client, true );
  alts_handshaker_client_ref_for_testing(client);
  {
    grpc_core::ExecCtx exec_ctx;
    alts_handshaker_client_on_status_received_for_testing(
        client, GRPC_STATUS_OK, absl::OkStatus());
  }

  run_tsi_handshaker_destroy_with_exec_ctx(handshaker);
  notification_destroy(&caller_to_tsi_notification);
  notification_destroy(&tsi_to_caller_notification);
}

static void on_shutdown_resp_cb(tsi_result status, void* user_data,
                                const unsigned char* bytes_to_send,
                                size_t bytes_to_send_size,
                                tsi_handshaker_result* result) {
  ASSERT_EQ(status, TSI_HANDSHAKE_SHUTDOWN);
  ASSERT_EQ(user_data, nullptr);
  ASSERT_EQ(bytes_to_send, nullptr);
  ASSERT_EQ(bytes_to_send_size, 0);
  ASSERT_EQ(result, nullptr);
}

TEST(AltsTsiHandshakerTest, CheckHandleResponseAfterShutdown) {
  should_handshaker_client_api_succeed = true;

  notification_init(&caller_to_tsi_notification);
  notification_init(&tsi_to_caller_notification);
  tsi_handshaker* handshaker = create_test_handshaker(true );
  tsi_handshaker_next(handshaker, nullptr, 0, nullptr, nullptr, nullptr,
                      on_client_start_success_cb, nullptr);
  alts_tsi_handshaker* alts_handshaker =
      reinterpret_cast<alts_tsi_handshaker*>(handshaker);
  alts_handshaker_client* client =
      alts_tsi_handshaker_get_client_for_testing(alts_handshaker);
  grpc_byte_buffer** recv_buffer_ptr =
      alts_handshaker_client_get_recv_buffer_addr_for_testing(client);
  grpc_byte_buffer_destroy(*recv_buffer_ptr);

  tsi_handshaker_shutdown(handshaker);
  grpc_byte_buffer* recv_buffer = generate_handshaker_response(CLIENT_START);
  alts_handshaker_client_set_fields_for_testing(
      client, alts_handshaker, on_shutdown_resp_cb, nullptr, recv_buffer,
      false);
  alts_handshaker_client_handle_response(client, true);
  alts_handshaker_client_ref_for_testing(client);
  {
    grpc_core::ExecCtx exec_ctx;
    alts_handshaker_client_on_status_received_for_testing(
        client, GRPC_STATUS_OK, absl::OkStatus());
  }

  run_tsi_handshaker_destroy_with_exec_ctx(handshaker);
  notification_destroy(&caller_to_tsi_notification);
  notification_destroy(&tsi_to_caller_notification);
}

TEST(AltsTsiHandshakerTest, CheckHandshakerNextFailsAfterShutdown) {
  should_handshaker_client_api_succeed = true;

  notification_init(&caller_to_tsi_notification);
  notification_init(&tsi_to_caller_notification);
  cb_event = nullptr;

  grpc_core::Thread thd("alts_tsi_handshaker_test",
                        &check_handle_response_with_shutdown, nullptr);
  thd.Start();
  check_handshaker_next_with_shutdown();
  thd.Join();

  notification_destroy(&caller_to_tsi_notification);
  notification_destroy(&tsi_to_caller_notification);
}

TEST(AltsTsiHandshakerTest, CheckHandshakerSuccess) {
  should_handshaker_client_api_succeed = true;

  notification_init(&caller_to_tsi_notification);
  notification_init(&tsi_to_caller_notification);

  grpc_core::Thread thd("alts_tsi_handshaker_test",
                        &check_handle_response_success, nullptr);
  thd.Start();
  check_handshaker_next_success();
  thd.Join();

  notification_destroy(&caller_to_tsi_notification);
  notification_destroy(&tsi_to_caller_notification);
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  grpc::testing::TestGrpcScope grpc_scope;
  grpc_alts_shared_resource_dedicated_init();
  int ret = RUN_ALL_TESTS();
  grpc_alts_shared_resource_dedicated_shutdown();
  return ret;
}
