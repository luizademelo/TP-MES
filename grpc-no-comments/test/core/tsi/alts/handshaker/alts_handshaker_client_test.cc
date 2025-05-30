
// Copyright 2018 gRPC authors.

#include "src/core/tsi/alts/handshaker/alts_handshaker_client.h"

#include <grpc/credentials.h>
#include <grpc/grpc.h>
#include <grpc/grpc_security.h>

#include "gtest/gtest.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/tsi/alts/handshaker/alts_shared_resource.h"
#include "src/core/tsi/alts/handshaker/alts_tsi_handshaker.h"
#include "src/core/tsi/alts/handshaker/alts_tsi_handshaker_private.h"
#include "src/core/tsi/transport_security.h"
#include "src/core/tsi/transport_security_interface.h"
#include "src/core/util/env.h"
#include "test/core/test_util/test_config.h"
#include "test/core/tsi/alts/handshaker/alts_handshaker_service_api_test_lib.h"
#include "upb/mem/arena.hpp"

#define ALTS_HANDSHAKER_CLIENT_TEST_OUT_FRAME "Hello Google"
#define ALTS_HANDSHAKER_CLIENT_TEST_TARGET_NAME "bigtable.google.api.com"
#define ALTS_HANDSHAKER_CLIENT_TEST_TARGET_SERVICE_ACCOUNT1 "A@google.com"
#define ALTS_HANDSHAKER_CLIENT_TEST_TARGET_SERVICE_ACCOUNT2 "B@google.com"
#define ALTS_HANDSHAKER_SERVER_TRANSPORT_PROTOCOL "bar,foo"
#define ALTS_HANDSHAKER_CLIENT_TRANSPORT_PROTOCOL "baz,foo"
#define ALTS_HANDSHAKER_CLIENT_TEST_MAX_FRAME_SIZE (64 * 1024)

const char kMaxConcurrentStreamsEnvironmentVariable[] =
    "GRPC_ALTS_MAX_CONCURRENT_HANDSHAKES";
const size_t kHandshakerClientOpNum = 4;
const size_t kMaxRpcVersionMajor = 3;
const size_t kMaxRpcVersionMinor = 2;
const size_t kMinRpcVersionMajor = 2;
const size_t kMinRpcVersionMinor = 1;

using grpc_core::internal::alts_handshaker_client_get_closure_for_testing;
using grpc_core::internal::
    alts_handshaker_client_get_initial_metadata_for_testing;
using grpc_core::internal::
    alts_handshaker_client_get_recv_buffer_addr_for_testing;
using grpc_core::internal::alts_handshaker_client_get_send_buffer_for_testing;
using grpc_core::internal::
    alts_handshaker_client_on_status_received_for_testing;
using grpc_core::internal::alts_handshaker_client_set_cb_for_testing;
using grpc_core::internal::alts_handshaker_client_set_grpc_caller_for_testing;

namespace {

typedef struct alts_handshaker_client_test_config {
  grpc_channel* channel;
  grpc_completion_queue* cq;
  alts_handshaker_client* client;
  alts_handshaker_client* server;
  grpc_slice out_frame;
} alts_handshaker_client_test_config;

void ValidateRpcProtocolVersions(const grpc_gcp_RpcProtocolVersions* versions) {
  ASSERT_NE(versions, nullptr);
  const grpc_gcp_RpcProtocolVersions_Version* max_version =
      grpc_gcp_RpcProtocolVersions_max_rpc_version(versions);
  const grpc_gcp_RpcProtocolVersions_Version* min_version =
      grpc_gcp_RpcProtocolVersions_min_rpc_version(versions);
  ASSERT_EQ(grpc_gcp_RpcProtocolVersions_Version_major(max_version),
            kMaxRpcVersionMajor);
  ASSERT_EQ(grpc_gcp_RpcProtocolVersions_Version_minor(max_version),
            kMaxRpcVersionMinor);
  ASSERT_EQ(grpc_gcp_RpcProtocolVersions_Version_major(min_version),
            kMinRpcVersionMajor);
  ASSERT_EQ(grpc_gcp_RpcProtocolVersions_Version_minor(min_version),
            kMinRpcVersionMinor);
}

void ValidateTargetIdentities(const grpc_gcp_Identity* const* target_identities,
                              size_t target_identities_count) {
  ASSERT_EQ(target_identities_count, 2);
  const grpc_gcp_Identity* identity1 = target_identities[1];
  const grpc_gcp_Identity* identity2 = target_identities[0];
  ASSERT_TRUE(upb_StringView_IsEqual(
      grpc_gcp_Identity_service_account(identity1),
      upb_StringView_FromString(
          ALTS_HANDSHAKER_CLIENT_TEST_TARGET_SERVICE_ACCOUNT1)));
  ASSERT_TRUE(upb_StringView_IsEqual(
      grpc_gcp_Identity_service_account(identity2),
      upb_StringView_FromString(
          ALTS_HANDSHAKER_CLIENT_TEST_TARGET_SERVICE_ACCOUNT2)));
}

bool ValidateOp(alts_handshaker_client* c, const grpc_op* op, size_t nops,
                bool is_start) {
  EXPECT_TRUE(c != nullptr && op != nullptr && nops != 0);
  bool ok = true;
  grpc_op* start_op = const_cast<grpc_op*>(op);
  if (is_start) {
    ok &= (op->op == GRPC_OP_SEND_INITIAL_METADATA);
    ok &= (op->data.send_initial_metadata.count == 0);
    op++;
    EXPECT_LE((size_t)(op - start_op), kHandshakerClientOpNum);
    ok &= (op->op == GRPC_OP_RECV_INITIAL_METADATA);
    ok &= (op->data.recv_initial_metadata.recv_initial_metadata ==
           alts_handshaker_client_get_initial_metadata_for_testing(c));
    op++;
    EXPECT_LE((size_t)(op - start_op), kHandshakerClientOpNum);
  }
  ok &= (op->op == GRPC_OP_SEND_MESSAGE);
  ok &= (op->data.send_message.send_message ==
         alts_handshaker_client_get_send_buffer_for_testing(c));
  op++;
  EXPECT_LE((size_t)(op - start_op), kHandshakerClientOpNum);
  ok &= (op->op == GRPC_OP_RECV_MESSAGE);
  ok &= (op->data.recv_message.recv_message ==
         alts_handshaker_client_get_recv_buffer_addr_for_testing(c));
  op++;
  EXPECT_LE((size_t)(op - start_op), kHandshakerClientOpNum);
  return ok;
}

grpc_gcp_HandshakerReq* DeserializeHandshakerReq(grpc_byte_buffer* buffer,
                                                 upb_Arena* arena) {
  EXPECT_NE(buffer, nullptr);
  grpc_byte_buffer_reader bbr;
  EXPECT_TRUE(grpc_byte_buffer_reader_init(&bbr, buffer));
  grpc_slice slice = grpc_byte_buffer_reader_readall(&bbr);
  grpc_gcp_HandshakerReq* req = grpc_gcp_handshaker_req_decode(slice, arena);
  EXPECT_NE(req, nullptr);
  grpc_slice_unref(slice);
  grpc_byte_buffer_reader_destroy(&bbr);
  return req;
}

bool IsRecvStatusOp(const grpc_op* op, size_t nops) {
  return nops == 1 && op->op == GRPC_OP_RECV_STATUS_ON_CLIENT;
}

grpc_call_error CheckMustNotBeCalled(grpc_call* ,
                                     const grpc_op* , size_t ,
                                     grpc_closure* ) {
  abort();
}

grpc_call_error CheckClientStartSuccess(grpc_call* , const grpc_op* op,
                                        size_t nops, grpc_closure* closure) {

  if (IsRecvStatusOp(op, nops)) {
    return GRPC_CALL_OK;
  }
  upb::Arena arena;
  alts_handshaker_client* client =
      static_cast<alts_handshaker_client*>(closure->cb_arg);
  EXPECT_EQ(alts_handshaker_client_get_closure_for_testing(client), closure);
  grpc_gcp_HandshakerReq* req = DeserializeHandshakerReq(
      alts_handshaker_client_get_send_buffer_for_testing(client), arena.ptr());
  const grpc_gcp_StartClientHandshakeReq* client_start =
      grpc_gcp_HandshakerReq_client_start(req);
  EXPECT_EQ(grpc_gcp_StartClientHandshakeReq_handshake_security_protocol(
                client_start),
            grpc_gcp_ALTS);
  upb_StringView const* application_protocols =
      grpc_gcp_StartClientHandshakeReq_application_protocols(client_start,
                                                             nullptr);
  EXPECT_TRUE(upb_StringView_IsEqual(
      application_protocols[0],
      upb_StringView_FromString(ALTS_APPLICATION_PROTOCOL)));
  upb_StringView const* record_protocols =
      grpc_gcp_StartClientHandshakeReq_record_protocols(client_start, nullptr);
  EXPECT_TRUE(upb_StringView_IsEqual(
      record_protocols[0], upb_StringView_FromString(ALTS_RECORD_PROTOCOL)));
  const grpc_gcp_RpcProtocolVersions* rpc_protocol_versions =
      grpc_gcp_StartClientHandshakeReq_rpc_versions(client_start);
  ValidateRpcProtocolVersions(rpc_protocol_versions);
  size_t target_identities_count;
  const grpc_gcp_Identity* const* target_identities =
      grpc_gcp_StartClientHandshakeReq_target_identities(
          client_start, &target_identities_count);
  ValidateTargetIdentities(target_identities, target_identities_count);
  EXPECT_TRUE(upb_StringView_IsEqual(
      grpc_gcp_StartClientHandshakeReq_target_name(client_start),
      upb_StringView_FromString(ALTS_HANDSHAKER_CLIENT_TEST_TARGET_NAME)));
  EXPECT_EQ(grpc_gcp_StartClientHandshakeReq_max_frame_size(client_start),
            ALTS_HANDSHAKER_CLIENT_TEST_MAX_FRAME_SIZE);
  EXPECT_TRUE(ValidateOp(client, op, nops, true ));
  return GRPC_CALL_OK;
}

void VerifyTransportProtocolPreferences(
    const grpc_gcp_TransportProtocolPreferences* protocol_preferences,
    bool is_server) {
  ASSERT_NE(protocol_preferences, nullptr);
  size_t transport_protocol_count;
  const upb_StringView* transport_protocols =
      grpc_gcp_TransportProtocolPreferences_transport_protocol(
          protocol_preferences, &transport_protocol_count);

  ASSERT_EQ(transport_protocol_count, 2);

  if (is_server) {
    ASSERT_TRUE(upb_StringView_IsEqual(transport_protocols[0],
                                       upb_StringView_FromString("bar")));
  } else {
    ASSERT_TRUE(upb_StringView_IsEqual(transport_protocols[0],
                                       upb_StringView_FromString("baz")));
  }
  ASSERT_TRUE(upb_StringView_IsEqual(transport_protocols[1],
                                     upb_StringView_FromString("foo")));
}

grpc_call_error VerifyClientSuccessWithProtocolNegotiation(
    grpc_call* , const grpc_op* op, size_t nops,
    grpc_closure* closure) {

  if (IsRecvStatusOp(op, nops)) {
    return GRPC_CALL_OK;
  }
  upb::Arena arena;
  alts_handshaker_client* client =
      static_cast<alts_handshaker_client*>(closure->cb_arg);
  EXPECT_EQ(alts_handshaker_client_get_closure_for_testing(client), closure);
  grpc_gcp_HandshakerReq* req = DeserializeHandshakerReq(
      alts_handshaker_client_get_send_buffer_for_testing(client), arena.ptr());
  const grpc_gcp_StartClientHandshakeReq* client_start =
      grpc_gcp_HandshakerReq_client_start(req);
  VerifyTransportProtocolPreferences(
      grpc_gcp_StartClientHandshakeReq_transport_protocol_preferences(
          client_start),
      false);
  return CheckClientStartSuccess(nullptr, op, nops, closure);
}

grpc_call_error CheckServerStartSuccess(grpc_call* , const grpc_op* op,
                                        size_t nops, grpc_closure* closure) {

  if (IsRecvStatusOp(op, nops)) {
    return GRPC_CALL_OK;
  }
  upb::Arena arena;
  alts_handshaker_client* client =
      static_cast<alts_handshaker_client*>(closure->cb_arg);
  EXPECT_EQ(alts_handshaker_client_get_closure_for_testing(client), closure);
  grpc_gcp_HandshakerReq* req = DeserializeHandshakerReq(
      alts_handshaker_client_get_send_buffer_for_testing(client), arena.ptr());
  const grpc_gcp_StartServerHandshakeReq* server_start =
      grpc_gcp_HandshakerReq_server_start(req);
  upb_StringView const* application_protocols =
      grpc_gcp_StartServerHandshakeReq_application_protocols(server_start,
                                                             nullptr);
  EXPECT_TRUE(upb_StringView_IsEqual(
      application_protocols[0],
      upb_StringView_FromString(ALTS_APPLICATION_PROTOCOL)));
  EXPECT_EQ(
      grpc_gcp_StartServerHandshakeReq_handshake_parameters_size(server_start),
      1);
  grpc_gcp_ServerHandshakeParameters* value;
  EXPECT_TRUE(grpc_gcp_StartServerHandshakeReq_handshake_parameters_get(
      server_start, grpc_gcp_ALTS, &value));
  upb_StringView const* record_protocols =
      grpc_gcp_ServerHandshakeParameters_record_protocols(value, nullptr);
  EXPECT_TRUE(upb_StringView_IsEqual(
      record_protocols[0], upb_StringView_FromString(ALTS_RECORD_PROTOCOL)));
  ValidateRpcProtocolVersions(
      grpc_gcp_StartServerHandshakeReq_rpc_versions(server_start));
  EXPECT_EQ(grpc_gcp_StartServerHandshakeReq_max_frame_size(server_start),
            ALTS_HANDSHAKER_CLIENT_TEST_MAX_FRAME_SIZE);
  EXPECT_TRUE(ValidateOp(client, op, nops, true ));
  return GRPC_CALL_OK;
}

grpc_call_error CheckServerStartSuccessWithNegotiation(grpc_call* ,
                                                       const grpc_op* op,
                                                       size_t nops,
                                                       grpc_closure* closure) {

  if (IsRecvStatusOp(op, nops)) {
    return GRPC_CALL_OK;
  }
  upb::Arena arena;
  alts_handshaker_client* client =
      static_cast<alts_handshaker_client*>(closure->cb_arg);
  EXPECT_EQ(alts_handshaker_client_get_closure_for_testing(client), closure);
  grpc_gcp_HandshakerReq* req = DeserializeHandshakerReq(
      alts_handshaker_client_get_send_buffer_for_testing(client), arena.ptr());
  const grpc_gcp_StartServerHandshakeReq* server_start =
      grpc_gcp_HandshakerReq_server_start(req);
  VerifyTransportProtocolPreferences(
      grpc_gcp_StartServerHandshakeReq_transport_protocol_preferences(
          server_start),
      true);
  return CheckServerStartSuccess(nullptr, op, nops, closure);
}

grpc_call_error CheckNextSuccess(grpc_call* , const grpc_op* op,
                                 size_t nops, grpc_closure* closure) {
  upb::Arena arena;
  alts_handshaker_client* client =
      static_cast<alts_handshaker_client*>(closure->cb_arg);
  EXPECT_EQ(alts_handshaker_client_get_closure_for_testing(client), closure);
  grpc_gcp_HandshakerReq* req = DeserializeHandshakerReq(
      alts_handshaker_client_get_send_buffer_for_testing(client), arena.ptr());
  const grpc_gcp_NextHandshakeMessageReq* next =
      grpc_gcp_HandshakerReq_next(req);
  EXPECT_TRUE(upb_StringView_IsEqual(
      grpc_gcp_NextHandshakeMessageReq_in_bytes(next),
      upb_StringView_FromString(ALTS_HANDSHAKER_CLIENT_TEST_OUT_FRAME)));
  EXPECT_TRUE(ValidateOp(client, op, nops, false ));
  return GRPC_CALL_OK;
}

grpc_call_error CheckGrpcCallFailure(grpc_call* , const grpc_op* op,
                                     size_t nops, grpc_closure* ) {

  if (IsRecvStatusOp(op, nops)) {
    return GRPC_CALL_OK;
  }
  return GRPC_CALL_ERROR;
}

grpc_alts_credentials_options* CreateCredentialsOptions(bool is_client) {
  grpc_alts_credentials_options* options =
      is_client ? grpc_alts_credentials_client_options_create()
                : grpc_alts_credentials_server_options_create();
  if (is_client) {
    grpc_alts_credentials_client_options_add_target_service_account(
        options, ALTS_HANDSHAKER_CLIENT_TEST_TARGET_SERVICE_ACCOUNT1);
    grpc_alts_credentials_client_options_add_target_service_account(
        options, ALTS_HANDSHAKER_CLIENT_TEST_TARGET_SERVICE_ACCOUNT2);
  }
  grpc_gcp_rpc_protocol_versions* versions = &options->rpc_versions;
  EXPECT_TRUE(grpc_gcp_rpc_protocol_versions_set_max(
      versions, kMaxRpcVersionMajor, kMaxRpcVersionMinor));
  EXPECT_TRUE(grpc_gcp_rpc_protocol_versions_set_min(
      versions, kMinRpcVersionMajor, kMinRpcVersionMinor));
  return options;
}

alts_handshaker_client_test_config* CreateConfig() {
  alts_handshaker_client_test_config* config =
      static_cast<alts_handshaker_client_test_config*>(
          gpr_zalloc(sizeof(*config)));
  grpc_channel_credentials* creds = grpc_insecure_credentials_create();
  config->channel = grpc_channel_create(ALTS_HANDSHAKER_SERVICE_URL_FOR_TESTING,
                                        creds, nullptr);
  grpc_channel_credentials_release(creds);
  config->cq = grpc_completion_queue_create_for_next(nullptr);
  grpc_alts_credentials_options* client_options =
      CreateCredentialsOptions(true );
  grpc_alts_credentials_options* server_options =
      CreateCredentialsOptions(false );
  config->server = alts_grpc_handshaker_client_create(
      nullptr, config->channel, ALTS_HANDSHAKER_SERVICE_URL_FOR_TESTING,
      nullptr, server_options,
      grpc_slice_from_static_string(ALTS_HANDSHAKER_CLIENT_TEST_TARGET_NAME),
      nullptr, nullptr, nullptr, nullptr, false,
      ALTS_HANDSHAKER_CLIENT_TEST_MAX_FRAME_SIZE,
      ALTS_HANDSHAKER_SERVER_TRANSPORT_PROTOCOL, nullptr);
  config->client = alts_grpc_handshaker_client_create(
      nullptr, config->channel, ALTS_HANDSHAKER_SERVICE_URL_FOR_TESTING,
      nullptr, client_options,
      grpc_slice_from_static_string(ALTS_HANDSHAKER_CLIENT_TEST_TARGET_NAME),
      nullptr, nullptr, nullptr, nullptr, true,
      ALTS_HANDSHAKER_CLIENT_TEST_MAX_FRAME_SIZE,
      ALTS_HANDSHAKER_CLIENT_TRANSPORT_PROTOCOL, nullptr);
  EXPECT_NE(config->client, nullptr);
  EXPECT_NE(config->server, nullptr);
  grpc_alts_credentials_options_destroy(client_options);
  grpc_alts_credentials_options_destroy(server_options);
  config->out_frame =
      grpc_slice_from_static_string(ALTS_HANDSHAKER_CLIENT_TEST_OUT_FRAME);
  return config;
}

void DestroyConfig(alts_handshaker_client_test_config* config) {
  if (config == nullptr) {
    return;
  }
  grpc_completion_queue_destroy(config->cq);
  grpc_channel_destroy(config->channel);
  alts_handshaker_client_destroy(config->client);
  alts_handshaker_client_destroy(config->server);
  grpc_slice_unref(config->out_frame);
  gpr_free(config);
}

}

TEST(AltsHandshakerClientTest, ScheduleRequestInvalidArgTest) {

  alts_handshaker_client_test_config* config = CreateConfig();

  alts_handshaker_client_set_grpc_caller_for_testing(config->client,
                                                     CheckMustNotBeCalled);

  {
    grpc_core::ExecCtx exec_ctx;
    ASSERT_EQ(alts_handshaker_client_start_client(nullptr),
              TSI_INVALID_ARGUMENT);
  }

  {
    grpc_core::ExecCtx exec_ctx;
    ASSERT_EQ(alts_handshaker_client_start_server(config->server, nullptr),
              TSI_INVALID_ARGUMENT);
  }
  {
    grpc_core::ExecCtx exec_ctx;
    ASSERT_EQ(alts_handshaker_client_start_server(nullptr, &config->out_frame),
              TSI_INVALID_ARGUMENT);
  }

  {
    grpc_core::ExecCtx exec_ctx;
    ASSERT_EQ(alts_handshaker_client_next(config->client, nullptr),
              TSI_INVALID_ARGUMENT);
  }
  {
    grpc_core::ExecCtx exec_ctx;
    ASSERT_EQ(alts_handshaker_client_next(nullptr, &config->out_frame),
              TSI_INVALID_ARGUMENT);
  }

  alts_handshaker_client_shutdown(nullptr);

  DestroyConfig(config);
}

TEST(AltsHandshakerClientTest, ScheduleRequestSuccessTest) {

  alts_handshaker_client_test_config* config = CreateConfig();

  alts_handshaker_client_set_grpc_caller_for_testing(config->client,
                                                     CheckClientStartSuccess);
  {
    grpc_core::ExecCtx exec_ctx;
    ASSERT_EQ(alts_handshaker_client_start_client(config->client), TSI_OK);
  }
  {
    grpc_core::ExecCtx exec_ctx;
    ASSERT_EQ(alts_handshaker_client_next(nullptr, &config->out_frame),
              TSI_INVALID_ARGUMENT);
  }

  alts_handshaker_client_set_grpc_caller_for_testing(config->server,
                                                     CheckServerStartSuccess);
  {
    grpc_core::ExecCtx exec_ctx;
    ASSERT_EQ(
        alts_handshaker_client_start_server(config->server, &config->out_frame),
        TSI_OK);
  }

  alts_handshaker_client_set_grpc_caller_for_testing(config->client,
                                                     CheckNextSuccess);
  {
    grpc_core::ExecCtx exec_ctx;
    ASSERT_EQ(alts_handshaker_client_next(config->client, &config->out_frame),
              TSI_OK);
  }

  alts_handshaker_client_set_grpc_caller_for_testing(config->server,
                                                     CheckNextSuccess);
  {
    grpc_core::ExecCtx exec_ctx;
    ASSERT_EQ(alts_handshaker_client_next(config->server, &config->out_frame),
              TSI_OK);
  }

  {
    grpc_core::ExecCtx exec_ctx;
    alts_handshaker_client_on_status_received_for_testing(
        config->client, GRPC_STATUS_OK, absl::OkStatus());
    alts_handshaker_client_on_status_received_for_testing(
        config->server, GRPC_STATUS_OK, absl::OkStatus());
  }
  DestroyConfig(config);
}

TEST(AltsHandshakerClientTest,
     ScheduleRequestSuccessWithProtocolNegotiationTest) {

  alts_handshaker_client_test_config* config = CreateConfig();

  alts_handshaker_client_set_grpc_caller_for_testing(
      config->client, VerifyClientSuccessWithProtocolNegotiation);
  {
    grpc_core::ExecCtx exec_ctx;
    ASSERT_EQ(alts_handshaker_client_start_client(config->client), TSI_OK);
  }
  {
    grpc_core::ExecCtx exec_ctx;
    ASSERT_EQ(alts_handshaker_client_next(nullptr, &config->out_frame),
              TSI_INVALID_ARGUMENT);
  }

  alts_handshaker_client_set_grpc_caller_for_testing(
      config->server, CheckServerStartSuccessWithNegotiation);
  {
    grpc_core::ExecCtx exec_ctx;
    ASSERT_EQ(
        alts_handshaker_client_start_server(config->server, &config->out_frame),
        TSI_OK);
  }

  alts_handshaker_client_set_grpc_caller_for_testing(config->client,
                                                     CheckNextSuccess);
  {
    grpc_core::ExecCtx exec_ctx;
    ASSERT_EQ(alts_handshaker_client_next(config->client, &config->out_frame),
              TSI_OK);
  }

  alts_handshaker_client_set_grpc_caller_for_testing(config->server,
                                                     CheckNextSuccess);
  {
    grpc_core::ExecCtx exec_ctx;
    ASSERT_EQ(alts_handshaker_client_next(config->server, &config->out_frame),
              TSI_OK);
  }

  {
    grpc_core::ExecCtx exec_ctx;
    alts_handshaker_client_on_status_received_for_testing(
        config->client, GRPC_STATUS_OK, absl::OkStatus());
    alts_handshaker_client_on_status_received_for_testing(
        config->server, GRPC_STATUS_OK, absl::OkStatus());
  }
  DestroyConfig(config);
}

static void tsi_cb_assert_tsi_internal_error(
    tsi_result status, void* ,
    const unsigned char* , size_t ,
    tsi_handshaker_result* ) {
  ASSERT_EQ(status, TSI_INTERNAL_ERROR);
}

TEST(AltsHandshakerClientTest, ScheduleRequestGrpcCallFailureTest) {

  alts_handshaker_client_test_config* config = CreateConfig();

  alts_handshaker_client_set_grpc_caller_for_testing(config->client,
                                                     CheckGrpcCallFailure);
  {
    grpc_core::ExecCtx exec_ctx;

    alts_handshaker_client_set_cb_for_testing(config->client,
                                              tsi_cb_assert_tsi_internal_error);
    alts_handshaker_client_start_client(config->client);
  }

  alts_handshaker_client_set_grpc_caller_for_testing(config->server,
                                                     CheckGrpcCallFailure);
  {
    grpc_core::ExecCtx exec_ctx;

    alts_handshaker_client_set_cb_for_testing(config->server,
                                              tsi_cb_assert_tsi_internal_error);
    alts_handshaker_client_start_server(config->server, &config->out_frame);
  }
  {
    grpc_core::ExecCtx exec_ctx;

    ASSERT_EQ(alts_handshaker_client_next(config->client, &config->out_frame),
              TSI_INTERNAL_ERROR);
  }
  {
    grpc_core::ExecCtx exec_ctx;

    ASSERT_EQ(alts_handshaker_client_next(config->server, &config->out_frame),
              TSI_INTERNAL_ERROR);
  }

  {
    grpc_core::ExecCtx exec_ctx;
    alts_handshaker_client_on_status_received_for_testing(
        config->client, GRPC_STATUS_OK, absl::OkStatus());
    alts_handshaker_client_on_status_received_for_testing(
        config->server, GRPC_STATUS_OK, absl::OkStatus());
  }
  DestroyConfig(config);
}

TEST(MaxNumberOfConcurrentHandshakesTest, Default) {
  grpc_core::UnsetEnv(kMaxConcurrentStreamsEnvironmentVariable);
  EXPECT_EQ(MaxNumberOfConcurrentHandshakes(), 100);
}

TEST(MaxNumberOfConcurrentHandshakesTest, EnvVarNotInt) {
  grpc_core::SetEnv(kMaxConcurrentStreamsEnvironmentVariable, "not-a-number");
  EXPECT_EQ(MaxNumberOfConcurrentHandshakes(), 100);
}

TEST(MaxNumberOfConcurrentHandshakesTest, EnvVarNegative) {
  grpc_core::SetEnv(kMaxConcurrentStreamsEnvironmentVariable, "-10");
  EXPECT_EQ(MaxNumberOfConcurrentHandshakes(), 100);
}

TEST(MaxNumberOfConcurrentHandshakesTest, EnvVarSuccess) {
  grpc_core::SetEnv(kMaxConcurrentStreamsEnvironmentVariable, "10");
  EXPECT_EQ(MaxNumberOfConcurrentHandshakes(), 10);
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
