
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
#include <stdint.h>
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

const std::string kCaCertSubject =
    "CN=testca,O=Internet Widgits Pty Ltd,ST=Some-State,C=AU";

void* tag(intptr_t t) { return reinterpret_cast<void*>(t); }

gpr_timespec five_seconds_time() { return grpc_timeout_seconds_to_deadline(5); }

grpc_server* server_create(grpc_completion_queue* cq, const char* server_addr,
                           grpc_tls_certificate_provider** server_provider,
                           grpc_tls_certificate_verifier** verifier) {
  std::string ca_cert = grpc_core::testing::GetFileContents(CA_CERT_PATH);
  std::string server_cert =
      grpc_core::testing::GetFileContents(SERVER_CERT_PATH);
  std::string server_key = grpc_core::testing::GetFileContents(SERVER_KEY_PATH);

  grpc_tls_credentials_options* options = grpc_tls_credentials_options_create();

  grpc_tls_identity_pairs* server_pairs = grpc_tls_identity_pairs_create();
  grpc_tls_identity_pairs_add_pair(server_pairs, server_key.c_str(),
                                   server_cert.c_str());
  *server_provider = grpc_tls_certificate_provider_static_data_create(
      ca_cert.c_str(), server_pairs);
  grpc_tls_credentials_options_set_certificate_provider(options,
                                                        *server_provider);
  grpc_tls_credentials_options_watch_root_certs(options);
  grpc_tls_credentials_options_watch_identity_key_cert_pairs(options);

  grpc_tls_credentials_options_set_cert_request_type(
      options, GRPC_SSL_REQUEST_AND_REQUIRE_CLIENT_CERTIFICATE_AND_VERIFY);

  auto* server_test_verifier =
      new grpc_core::testing::PeerPropertyExternalVerifier(kCaCertSubject);
  *verifier = grpc_tls_certificate_verifier_external_create(
      server_test_verifier->base());
  grpc_tls_credentials_options_set_certificate_verifier(options, *verifier);
  grpc_server_credentials* creds = grpc_tls_server_credentials_create(options);

  grpc_server* server = grpc_server_create(nullptr, nullptr);
  grpc_server_register_completion_queue(server, cq, nullptr);
  CHECK(grpc_server_add_http2_port(server, server_addr, creds));
  grpc_server_credentials_release(creds);

  grpc_server_start(server);

  return server;
}

grpc_channel* client_create(const char* server_addr,
                            grpc_tls_certificate_provider** client_provider,
                            grpc_tls_certificate_verifier** verifier) {
  std::string ca_cert = grpc_core::testing::GetFileContents(CA_CERT_PATH);
  std::string client_cert =
      grpc_core::testing::GetFileContents(CLIENT_CERT_PATH);
  std::string client_key = grpc_core::testing::GetFileContents(CLIENT_KEY_PATH);

  grpc_tls_credentials_options* options = grpc_tls_credentials_options_create();

  grpc_tls_identity_pairs* client_pairs = grpc_tls_identity_pairs_create();
  grpc_tls_identity_pairs_add_pair(client_pairs, client_key.c_str(),
                                   client_cert.c_str());
  *client_provider = grpc_tls_certificate_provider_static_data_create(
      ca_cert.c_str(), client_pairs);

  grpc_tls_credentials_options_set_certificate_provider(options,
                                                        *client_provider);
  grpc_tls_credentials_options_watch_root_certs(options);
  grpc_tls_credentials_options_watch_identity_key_cert_pairs(options);

  grpc_tls_credentials_options_set_cert_request_type(
      options, GRPC_SSL_REQUEST_AND_REQUIRE_CLIENT_CERTIFICATE_AND_VERIFY);

  auto* client_test_verifier =
      new grpc_core::testing::PeerPropertyExternalVerifier(kCaCertSubject);
  *verifier = grpc_tls_certificate_verifier_external_create(
      client_test_verifier->base());
  grpc_tls_credentials_options_set_certificate_verifier(options, *verifier);
  grpc_channel_credentials* creds = grpc_tls_credentials_create(options);

  grpc_arg args[] = {
      grpc_channel_arg_string_create(
          const_cast<char*>(GRPC_SSL_TARGET_NAME_OVERRIDE_ARG),
          const_cast<char*>("waterzooi.test.google.be")),
  };

  grpc_channel_args* client_args =
      grpc_channel_args_copy_and_add(nullptr, args, GPR_ARRAY_SIZE(args));

  grpc_channel* client = grpc_channel_create(server_addr, creds, client_args);
  CHECK_NE(client, nullptr);
  grpc_channel_credentials_release(creds);

  {
    grpc_core::ExecCtx exec_ctx;
    grpc_channel_args_destroy(client_args);
  }

  return client;
}

void do_round_trip(grpc_completion_queue* cq, grpc_server* server,
                   const char* server_addr) {
  grpc_tls_certificate_provider* provider = nullptr;
  grpc_tls_certificate_verifier* verifier = nullptr;
  grpc_channel* client = client_create(server_addr, &provider, &verifier);

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
  error = grpc_call_start_batch(c, ops, static_cast<size_t>(op - ops), tag(1),
                                nullptr);
  CHECK_EQ(error, GRPC_CALL_OK);

  grpc_call* s;
  error = grpc_server_request_call(server, &s, &call_details,
                                   &request_metadata_recv, cq, cq, tag(101));
  CHECK_EQ(error, GRPC_CALL_OK);
  cqv.Expect(tag(101), true);
  cqv.Verify();

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
  error = grpc_call_start_batch(s, ops, static_cast<size_t>(op - ops), tag(103),
                                nullptr);
  CHECK_EQ(error, GRPC_CALL_OK);

  cqv.Expect(tag(103), true);
  cqv.Expect(tag(1), true);
  cqv.Verify();

  grpc_metadata_array_destroy(&initial_metadata_recv);
  grpc_metadata_array_destroy(&trailing_metadata_recv);
  grpc_metadata_array_destroy(&request_metadata_recv);
  grpc_call_details_destroy(&call_details);

  grpc_call_unref(c);
  grpc_call_unref(s);

  grpc_channel_destroy(client);
  grpc_tls_certificate_provider_release(provider);
  grpc_tls_certificate_verifier_release(verifier);
}

void drain_cq(grpc_completion_queue* cq) {
  grpc_event ev;
  do {
    ev = grpc_completion_queue_next(cq, five_seconds_time(), nullptr);
  } while (ev.type != GRPC_QUEUE_SHUTDOWN);
}

TEST(H2TlsPeerPropertyExternalVerifier, PeerPropertyExternalVerifierTest) {
  int port = grpc_pick_unused_port_or_die();

  std::string server_addr = grpc_core::JoinHostPort("localhost", port);

  grpc_completion_queue* cq = grpc_completion_queue_create_for_next(nullptr);

  grpc_tls_certificate_provider* provider = nullptr;
  grpc_tls_certificate_verifier* verifier = nullptr;
  grpc_server* server =
      server_create(cq, server_addr.c_str(), &provider, &verifier);

  do_round_trip(cq, server, server_addr.c_str());

  CHECK(grpc_completion_queue_next(
            cq, grpc_timeout_milliseconds_to_deadline(100), nullptr)
            .type == GRPC_QUEUE_TIMEOUT);

  grpc_server_shutdown_and_notify(server, cq, tag(1000));
  grpc_event ev;
  do {
    ev = grpc_completion_queue_next(cq, grpc_timeout_seconds_to_deadline(5),
                                    nullptr);
  } while (ev.type != GRPC_OP_COMPLETE || ev.tag != tag(1000));
  grpc_server_destroy(server);
  grpc_tls_certificate_provider_release(provider);
  grpc_tls_certificate_verifier_release(verifier);

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
