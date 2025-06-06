
// Copyright 2018 gRPC authors.

#include <grpc/credentials.h>
#include <grpc/grpc.h>
#include <grpc/grpc_security.h>
#include <grpc/grpc_security_constants.h>
#include <grpc/impl/channel_arg_names.h>
#include <grpc/impl/propagation_bits.h>
#include <grpc/slice.h>
#include <grpc/status.h>
#include <grpc/support/time.h>
#include <string.h>

#include <optional>
#include <string>

#include "absl/log/check.h"
#include "gtest/gtest.h"
#include "src/core/config/config_vars.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/util/host_port.h"
#include "src/core/util/useful.h"
#include "test/core/end2end/cq_verifier.h"
#include "test/core/test_util/port.h"
#include "test/core/test_util/test_config.h"
#include "test/core/test_util/tls_utils.h"

#define CA_CERT_PATH "src/core/tsi/test_creds/ca.pem"
#define CLIENT_CERT_PATH "src/core/tsi/test_creds/client.pem"
#define CLIENT_KEY_PATH "src/core/tsi/test_creds/client.key"
#define SERVER_CERT_PATH "src/core/tsi/test_creds/server1.pem"
#define SERVER_KEY_PATH "src/core/tsi/test_creds/server1.key"

namespace grpc {
namespace testing {
namespace {

gpr_timespec five_seconds_time() { return grpc_timeout_seconds_to_deadline(5); }

grpc_server* server_create(grpc_completion_queue* cq, const char* server_addr) {
  std::string ca_cert = grpc_core::testing::GetFileContents(CA_CERT_PATH);
  std::string server_cert =
      grpc_core::testing::GetFileContents(SERVER_CERT_PATH);
  std::string server_key = grpc_core::testing::GetFileContents(SERVER_KEY_PATH);
  grpc_ssl_pem_key_cert_pair pem_cert_key_pair = {server_key.c_str(),
                                                  server_cert.c_str()};
  grpc_server_credentials* server_creds = grpc_ssl_server_credentials_create_ex(
      ca_cert.c_str(), &pem_cert_key_pair, 1,
      GRPC_SSL_REQUEST_CLIENT_CERTIFICATE_AND_VERIFY, nullptr);

  grpc_server* server = grpc_server_create(nullptr, nullptr);
  grpc_server_register_completion_queue(server, cq, nullptr);
  CHECK(grpc_server_add_http2_port(server, server_addr, server_creds));
  grpc_server_credentials_release(server_creds);
  grpc_server_start(server);
  return server;
}

grpc_channel* client_create(const char* server_addr,
                            grpc_ssl_session_cache* cache) {
  std::string ca_cert = grpc_core::testing::GetFileContents(CA_CERT_PATH);
  std::string client_cert =
      grpc_core::testing::GetFileContents(CLIENT_CERT_PATH);
  std::string client_key = grpc_core::testing::GetFileContents(CLIENT_KEY_PATH);
  grpc_ssl_pem_key_cert_pair signed_client_key_cert_pair = {
      client_key.c_str(), client_cert.c_str()};
  grpc_channel_credentials* client_creds = grpc_ssl_credentials_create(
      ca_cert.c_str(), &signed_client_key_cert_pair, nullptr, nullptr);

  grpc_arg args[] = {
      grpc_channel_arg_string_create(
          const_cast<char*>(GRPC_SSL_TARGET_NAME_OVERRIDE_ARG),
          const_cast<char*>("waterzooi.test.google.be")),
      grpc_ssl_session_cache_create_channel_arg(cache),
  };

  grpc_channel_args* client_args =
      grpc_channel_args_copy_and_add(nullptr, args, GPR_ARRAY_SIZE(args));

  grpc_channel* client =
      grpc_channel_create(server_addr, client_creds, client_args);
  CHECK_NE(client, nullptr);
  grpc_channel_credentials_release(client_creds);

  {
    grpc_core::ExecCtx exec_ctx;
    grpc_channel_args_destroy(client_args);
  }

  return client;
}

void do_round_trip(grpc_completion_queue* cq, grpc_server* server,
                   const char* server_addr, grpc_ssl_session_cache* cache,
                   bool expect_session_reuse) {
  grpc_channel* client = client_create(server_addr, cache);

  grpc_core::CqVerifier cqv(cq);
  grpc_op ops[6];
  grpc_op* op;
  grpc_metadata_array initial_metadata_recv;
  grpc_metadata_array trailing_metadata_recv;
  grpc_metadata_array request_metadata_recv;
  grpc_call_details call_details;
  grpc_status_code status;
  grpc_call_error error;
  grpc_slice details;
  int was_cancelled = 2;

  gpr_timespec deadline = grpc_timeout_seconds_to_deadline(60);
  grpc_call* c = grpc_channel_create_call(
      client, nullptr, GRPC_PROPAGATE_DEFAULTS, cq,
      grpc_slice_from_static_string("/foo"), nullptr, deadline, nullptr);
  CHECK(c);

  grpc_metadata_array_init(&initial_metadata_recv);
  grpc_metadata_array_init(&trailing_metadata_recv);
  grpc_metadata_array_init(&request_metadata_recv);
  grpc_call_details_init(&call_details);

  memset(ops, 0, sizeof(ops));
  op = ops;
  op->op = GRPC_OP_SEND_INITIAL_METADATA;
  op->data.send_initial_metadata.count = 0;
  op->flags = 0;
  op->reserved = nullptr;
  op++;
  op->op = GRPC_OP_SEND_CLOSE_FROM_CLIENT;
  op->flags = 0;
  op->reserved = nullptr;
  op++;
  op->op = GRPC_OP_RECV_INITIAL_METADATA;
  op->data.recv_initial_metadata.recv_initial_metadata = &initial_metadata_recv;
  op->flags = 0;
  op->reserved = nullptr;
  op++;
  op->op = GRPC_OP_RECV_STATUS_ON_CLIENT;
  op->data.recv_status_on_client.trailing_metadata = &trailing_metadata_recv;
  op->data.recv_status_on_client.status = &status;
  op->data.recv_status_on_client.status_details = &details;
  op->flags = 0;
  op->reserved = nullptr;
  op++;
  error = grpc_call_start_batch(c, ops, static_cast<size_t>(op - ops),
                                grpc_core::CqVerifier::tag(1), nullptr);
  CHECK_EQ(error, GRPC_CALL_OK);

  grpc_call* s;
  error = grpc_server_request_call(server, &s, &call_details,
                                   &request_metadata_recv, cq, cq,
                                   grpc_core::CqVerifier::tag(101));
  CHECK_EQ(error, GRPC_CALL_OK);
  cqv.Expect(grpc_core::CqVerifier::tag(101), true);
  cqv.Verify();

  grpc_auth_context* auth = grpc_call_auth_context(s);
  grpc_auth_property_iterator it = grpc_auth_context_find_properties_by_name(
      auth, GRPC_SSL_SESSION_REUSED_PROPERTY);
  const grpc_auth_property* property = grpc_auth_property_iterator_next(&it);
  CHECK_NE(property, nullptr);
  if (expect_session_reuse) {
    CHECK_EQ(strcmp(property->value, "true"), 0);
  } else {
    CHECK_EQ(strcmp(property->value, "false"), 0);
  }
  grpc_auth_context_release(auth);

  memset(ops, 0, sizeof(ops));
  op = ops;
  op->op = GRPC_OP_SEND_INITIAL_METADATA;
  op->data.send_initial_metadata.count = 0;
  op->flags = 0;
  op->reserved = nullptr;
  op++;
  op->op = GRPC_OP_RECV_CLOSE_ON_SERVER;
  op->data.recv_close_on_server.cancelled = &was_cancelled;
  op->flags = 0;
  op->reserved = nullptr;
  op++;
  op->op = GRPC_OP_SEND_STATUS_FROM_SERVER;
  op->data.send_status_from_server.trailing_metadata_count = 0;
  op->data.send_status_from_server.status = GRPC_STATUS_OK;
  op->flags = 0;
  op->reserved = nullptr;
  op++;
  error = grpc_call_start_batch(s, ops, static_cast<size_t>(op - ops),
                                grpc_core::CqVerifier::tag(103), nullptr);
  CHECK_EQ(error, GRPC_CALL_OK);

  cqv.Expect(grpc_core::CqVerifier::tag(103), true);
  cqv.Expect(grpc_core::CqVerifier::tag(1), true);
  cqv.Verify();

  grpc_metadata_array_destroy(&initial_metadata_recv);
  grpc_metadata_array_destroy(&trailing_metadata_recv);
  grpc_metadata_array_destroy(&request_metadata_recv);
  grpc_call_details_destroy(&call_details);

  grpc_call_unref(c);
  grpc_call_unref(s);

  grpc_channel_destroy(client);
}

void drain_cq(grpc_completion_queue* cq) {
  grpc_event ev;
  do {
    ev = grpc_completion_queue_next(cq, five_seconds_time(), nullptr);
  } while (ev.type != GRPC_QUEUE_SHUTDOWN);
}

TEST(H2SessionReuseTest, SingleReuse) {
  int port = grpc_pick_unused_port_or_die();

  std::string server_addr = grpc_core::JoinHostPort("localhost", port);

  grpc_completion_queue* cq = grpc_completion_queue_create_for_next(nullptr);
  grpc_ssl_session_cache* cache = grpc_ssl_session_cache_create_lru(16);

  grpc_server* server = server_create(cq, server_addr.c_str());

  do_round_trip(cq, server, server_addr.c_str(), cache, false);
  do_round_trip(cq, server, server_addr.c_str(), cache, true);
  do_round_trip(cq, server, server_addr.c_str(), cache, true);

  grpc_ssl_session_cache_destroy(cache);

  CHECK(grpc_completion_queue_next(
            cq, grpc_timeout_milliseconds_to_deadline(100), nullptr)
            .type == GRPC_QUEUE_TIMEOUT);

  grpc_server_shutdown_and_notify(server, cq, grpc_core::CqVerifier::tag(1000));
  grpc_event ev;
  do {
    ev = grpc_completion_queue_next(cq, grpc_timeout_seconds_to_deadline(5),
                                    nullptr);
  } while (ev.type != GRPC_OP_COMPLETE ||
           ev.tag != grpc_core::CqVerifier::tag(1000));
  grpc_server_destroy(server);

  grpc_completion_queue_shutdown(cq);
  drain_cq(cq);
  grpc_completion_queue_destroy(cq);
}

}
}
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  grpc_core::ConfigVars::Overrides overrides;
  overrides.default_ssl_roots_file_path = CA_CERT_PATH;
  grpc_core::ConfigVars::SetOverrides(overrides);

  grpc_init();
  ::testing::InitGoogleTest(&argc, argv);
  int ret = RUN_ALL_TESTS();
  grpc_shutdown();

  return ret;
}
