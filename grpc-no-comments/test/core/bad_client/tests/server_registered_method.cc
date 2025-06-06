
// Copyright 2015 gRPC authors.

#include <grpc/byte_buffer.h>
#include <grpc/grpc.h>
#include <grpc/support/time.h>

#include "absl/log/check.h"
#include "src/core/server/server.h"
#include "test/core/bad_client/bad_client.h"
#include "test/core/end2end/cq_verifier.h"
#include "test/core/test_util/test_config.h"

#define PFX_STR                                               \
  "PRI * HTTP/2.0\r\n\r\nSM\r\n\r\n"                          \
  "\x00\x00\x00\x04\x00\x00\x00\x00\x00"  \
  "\x00\x00\xd0\x01\x04\x00\x00\x00\x01"                      \
  "\x10\x05:path\x0f/registered/bar"                          \
  "\x10\x07:scheme\x04http"                                   \
  "\x10\x07:method\x04POST"                                   \
  "\x10\x0a:authority\x09localhost"                           \
  "\x10\x0c"                                                  \
  "content-type\x10"                                          \
  "application/grpc"                                          \
  "\x10\x14grpc-accept-encoding\x15identity,deflate,gzip"     \
  "\x10\x02te\x08trailers"                                    \
  "\x10\x0auser-agent\"bad-client grpc-c/0.12.0.0 (linux)"

static void verifier_succeeds(grpc_server* server, grpc_completion_queue* cq,
                              void* registered_method) {
  grpc_call_error error;
  grpc_call* s;
  grpc_core::CqVerifier cqv(cq);
  grpc_metadata_array request_metadata_recv;
  gpr_timespec deadline;
  grpc_byte_buffer* payload = nullptr;

  grpc_metadata_array_init(&request_metadata_recv);

  error = grpc_server_request_registered_call(
      server, registered_method, &s, &deadline, &request_metadata_recv,
      &payload, cq, cq, grpc_core::CqVerifier::tag(101));
  CHECK_EQ(error, GRPC_CALL_OK);
  cqv.Expect(grpc_core::CqVerifier::tag(101), true);
  cqv.Verify();

  CHECK_NE(payload, nullptr);

  grpc_metadata_array_destroy(&request_metadata_recv);
  grpc_call_unref(s);
  grpc_byte_buffer_destroy(payload);
}

static void verifier_fails(grpc_server* server, grpc_completion_queue* cq,
                           void* ) {
  while (grpc_core::Server::FromC(server)->HasOpenConnections()) {
    CHECK(grpc_completion_queue_next(
              cq, grpc_timeout_milliseconds_to_deadline(20), nullptr)
              .type == GRPC_QUEUE_TIMEOUT);
  }
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  grpc_init();

  GRPC_RUN_BAD_CLIENT_TEST(verifier_fails, nullptr,
                           PFX_STR "\x00\x00\x00\x00\x00\x00\x00\x00\x01",
                           GRPC_BAD_CLIENT_DISCONNECT);
  GRPC_RUN_BAD_CLIENT_TEST(verifier_fails, nullptr,
                           PFX_STR "\x00\x00\x01\x00\x00\x00\x00\x00\x01\x00",
                           GRPC_BAD_CLIENT_DISCONNECT);
  GRPC_RUN_BAD_CLIENT_TEST(verifier_fails, nullptr,
                           PFX_STR
                           "\x00\x00\x02\x00\x00\x00\x00\x00\x01\x00\x00",
                           GRPC_BAD_CLIENT_DISCONNECT);
  GRPC_RUN_BAD_CLIENT_TEST(verifier_fails, nullptr,
                           PFX_STR
                           "\x00\x00\x03\x00\x00\x00\x00\x00\x01\x00\x00\x00",
                           GRPC_BAD_CLIENT_DISCONNECT);
  GRPC_RUN_BAD_CLIENT_TEST(
      verifier_fails, nullptr,
      PFX_STR "\x00\x00\x04\x00\x00\x00\x00\x00\x01\x00\x00\x00\x00",
      GRPC_BAD_CLIENT_DISCONNECT);
  GRPC_RUN_BAD_CLIENT_TEST(
      verifier_succeeds, nullptr,
      PFX_STR "\x00\x00\x05\x00\x01\x00\x00\x00\x01\x00\x00\x00\x00\x00", 0);
  GRPC_RUN_BAD_CLIENT_TEST(
      verifier_fails, nullptr,
      PFX_STR "\x00\x00\x05\x00\x00\x00\x00\x00\x01\x00\x00\x00\x00\x01",
      GRPC_BAD_CLIENT_DISCONNECT);
  GRPC_RUN_BAD_CLIENT_TEST(
      verifier_succeeds, nullptr,
      PFX_STR "\x00\x00\x06\x00\x01\x00\x00\x00\x01\x00\x00\x00\x00\x01\x00",
      0);
  GRPC_RUN_BAD_CLIENT_TEST(
      verifier_fails, nullptr,
      PFX_STR "\x00\x00\x05\x00\x00\x00\x00\x00\x01\x00\x00\x00\x00\x02",
      GRPC_BAD_CLIENT_DISCONNECT);
  GRPC_RUN_BAD_CLIENT_TEST(
      verifier_fails, nullptr,
      PFX_STR "\x00\x00\x06\x00\x00\x00\x00\x00\x01\x00\x00\x00\x00\x02\x00",
      GRPC_BAD_CLIENT_DISCONNECT);
  GRPC_RUN_BAD_CLIENT_TEST(
      verifier_succeeds, nullptr,
      PFX_STR
      "\x00\x00\x07\x00\x01\x00\x00\x00\x01\x00\x00\x00\x00\x02\x00\x00",
      0);

  grpc_shutdown();
  return 0;
}
