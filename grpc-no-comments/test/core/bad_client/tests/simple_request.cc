// Copyright 2023 gRPC authors.

#include <grpc/grpc.h>
#include <grpc/slice.h>

#include "absl/log/check.h"
#include "src/core/server/server.h"
#include "test/core/bad_client/bad_client.h"
#include "test/core/end2end/cq_verifier.h"
#include "test/core/test_util/test_config.h"

#define PFX_STR                                                            \
  "PRI * HTTP/2.0\r\n\r\nSM\r\n\r\n"                                       \
  "\x00\x00\x00\x04\x00\x00\x00\x00\x00"               \
  "\x00\x00\xc9\x01\x04\x00\x00\x00\x01"

                   \
  "\x10\x05:path\x08/foo/bar"                                              \
  "\x10\x07:scheme\x04http"                                                \
  "\x10\x07:method\x04POST"                                                \
  "\x10\x0a:authority\x09localhost"                                        \
  "\x10\x0c"                                                               \
  "content-type\x10"                                                       \
  "application/grpc"                                                       \
  "\x10\x14grpc-accept-encoding\x15"                                       \
  "deflate,identity,gzip"                                                  \
  "\x10\x02te\x08trailers"                                                 \
  "\x10\x0auser-agent\"bad-client grpc-c/0.12.0.0 (linux)"

#define ONE_SETTING_HDR              \
  "PRI * HTTP/2.0\r\n\r\nSM\r\n\r\n" \
  "\x00\x00\x06\x04\x00\x00\x00\x00\x00"

#define USUAL_HDR                                                          \
  "\x00\x00\xc9\x01\x04\x00\x00\x00\x01"

                   \
  "\x10\x05:path\x08/foo/bar"                                              \
  "\x10\x07:scheme\x04http"                                                \
  "\x10\x07:method\x04POST"                                                \
  "\x10\x0a:authority\x09localhost"                                        \
  "\x10\x0c"                                                               \
  "content-type\x10"                                                       \
  "application/grpc"                                                       \
  "\x10\x14grpc-accept-encoding\x15"                                       \
  "deflate,identity,gzip"                                                  \
  "\x10\x02te\x08trailers"                                                 \
  "\x10\x0auser-agent\"bad-client grpc-c/0.12.0.0 (linux)"

#define PFX_STR_UNUSUAL                                                    \
  "PRI * HTTP/2.0\r\n\r\nSM\r\n\r\n"                                       \
  "\x00\x00\x00\x04\x00\x00\x00\x00\x00"               \
  "\x00\x00\xf4\x01\x04\x00\x00\x00\x01"

           \
  "\x10\x05:path\x08/foo/bar"                                              \
  "\x10\x07:scheme\x04http"                                                \
  "\x10\x07:method\x04POST"                                                \
  "\x10\x04host\x09localhost"                                              \
  "\x10\x0c"                                                               \
  "content-type\x1e"                                                       \
  "application/grpc+this-is-valid"                                         \
  "\x10\x14grpc-accept-encoding\x15identity,deflate,gzip"                  \
  "\x10\x02te\x08trailers"                                                 \
  "\x10\x0auser-agent\"bad-client grpc-c/0.12.0.0 (linux)"                 \
  "\x10\x0cgrpc-timeout\x03"                                               \
  "10S"                                                                    \
  "\x10\x0cgrpc-timeout\x02"                                               \
  "5S"

#define PFX_STR_UNUSUAL2                                                    \
  "PRI * HTTP/2.0\r\n\r\nSM\r\n\r\n"                                        \
  "\x00\x00\x00\x04\x00\x00\x00\x00\x00"                \
  "\x00\x00\xf4\x01\x04\x00\x00\x00\x01"

            \
  "\x10\x05:path\x08/foo/bar"                                               \
  "\x10\x07:scheme\x04http"                                                 \
  "\x10\x07:method\x04POST"                                                 \
  "\x10\x04host\x09localhost"                                               \
  "\x10\x0c"                                                                \
  "content-type\x1e"                                                        \
  "application/grpc;this-is-valid"                                          \
  "\x10\x14grpc-accept-encoding\x15identity,deflate,gzip"                   \
  "\x10\x02te\x08trailers"                                                  \
  "\x10\x0auser-agent\"bad-client grpc-c/0.12.0.0 (linux)"                  \
  "\x10\x0cgrpc-timeout\x03"                                                \
  "10S"                                                                     \
  "\x10\x0cgrpc-timeout\x02"                                                \
  "5S"

#define PFX_STR_TEXT_HTML_CONTENT_TYPE_HEADER                                             \
  "PRI * HTTP/2.0\r\n\r\nSM\r\n\r\n"                                                      \
  "\x00\x00\x00\x04\x00\x00\x00\x00\x00"                              \
  "\x00\x00\xdf\x01\x04\x00\x00\x00\x01"

                          \
  "\x10\x05:path\x08/foo/bar"                                                             \
  "\x10\x07:scheme\x04http"                                                               \
  "\x10\x07:method\x04POST"                                                               \
  "\x10\x04host\x09localhost"                                                             \
  "\x10\x0c"                                                                              \
  "content-type\x09text/html"                                                             \
  "\x10\x14grpc-accept-encoding\x15"                                                      \
  "deflate,identity,gzip"                                                                 \
  "\x10\x02te\x08trailers"                                                                \
  "\x10\x0auser-agent\"bad-client grpc-c/0.12.0.0 (linux)"                                \
  "\x10\x0cgrpc-timeout\x03"                                                              \
  "10S"                                                                                   \
  "\x10\x0cgrpc-timeout\x02"                                                              \
  "5S"

static void verifier(grpc_server* server, grpc_completion_queue* cq,
                     void* ) {
  grpc_call_error error;
  grpc_call* s;
  grpc_call_details call_details;
  grpc_core::CqVerifier cqv(cq);
  grpc_metadata_array request_metadata_recv;

  grpc_call_details_init(&call_details);
  grpc_metadata_array_init(&request_metadata_recv);

  error = grpc_server_request_call(server, &s, &call_details,
                                   &request_metadata_recv, cq, cq,
                                   grpc_core::CqVerifier::tag(101));
  CHECK_EQ(error, GRPC_CALL_OK);
  cqv.Expect(grpc_core::CqVerifier::tag(101), true);
  cqv.Verify();

  CHECK_EQ(grpc_slice_str_cmp(call_details.host, "localhost"), 0);
  CHECK_EQ(grpc_slice_str_cmp(call_details.method, "/foo/bar"), 0);

  grpc_metadata_array_destroy(&request_metadata_recv);
  grpc_call_details_destroy(&call_details);
  grpc_call_unref(s);
}

static void VerifyRpcDoesNotGetCanceled(grpc_server* server,
                                        grpc_completion_queue* cq,
                                        void* ) {
  grpc_call_error error;
  grpc_call* s;
  grpc_call_details call_details;
  grpc_core::CqVerifier cqv(cq);
  grpc_metadata_array request_metadata_recv;
  int was_cancelled = 2;

  grpc_call_details_init(&call_details);
  grpc_metadata_array_init(&request_metadata_recv);

  error = grpc_server_request_call(server, &s, &call_details,
                                   &request_metadata_recv, cq, cq,
                                   grpc_core::CqVerifier::tag(101));
  CHECK_EQ(error, GRPC_CALL_OK);
  cqv.Expect(grpc_core::CqVerifier::tag(101), true);
  cqv.Verify();

  CHECK_EQ(grpc_slice_str_cmp(call_details.host, "localhost"), 0);
  CHECK_EQ(grpc_slice_str_cmp(call_details.method, "/foo/bar"), 0);

  grpc_op* op;
  grpc_op ops[6];

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
  op->data.send_status_from_server.status = GRPC_STATUS_UNIMPLEMENTED;
  grpc_slice status_details = grpc_slice_from_static_string("xyz");
  op->data.send_status_from_server.status_details = &status_details;
  op->flags = 0;
  op->reserved = nullptr;
  op++;
  error = grpc_call_start_batch(s, ops, static_cast<size_t>(op - ops),
                                grpc_core::CqVerifier::tag(103), nullptr);
  CHECK_EQ(error, GRPC_CALL_OK);

  cqv.Expect(grpc_core::CqVerifier::tag(103), true);
  cqv.Verify();

  grpc_metadata_array_destroy(&request_metadata_recv);
  grpc_call_details_destroy(&call_details);
  grpc_call_unref(s);
}

static void failure_verifier(grpc_server* server, grpc_completion_queue* cq,
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

  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr, PFX_STR, 0);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr, PFX_STR_UNUSUAL, 0);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr, PFX_STR_UNUSUAL2, 0);

  GRPC_RUN_BAD_CLIENT_TEST(VerifyRpcDoesNotGetCanceled, nullptr,
                           PFX_STR_TEXT_HTML_CONTENT_TYPE_HEADER, 0);

  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr,
                           PFX_STR
                           "\x00\x00\x05\x00\x00\x00\x00\x00\x01"
                           "\x34\x00\x00\x00\x00",
                           0);

  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr,
                           PFX_STR "\x00\x00\x00\x00\x02\x00\x00\x00\x01", 0);

  GRPC_RUN_BAD_CLIENT_TEST(failure_verifier, nullptr,
                           PFX_STR "\x00\x00\x01\x08\x00\x00\x00\x00\x01", 0);

  GRPC_RUN_BAD_CLIENT_TEST(failure_verifier, nullptr,
                           PFX_STR "\x00\x00\x00\x08\x10\x00\x00\x00\x01", 0);

  GRPC_RUN_BAD_CLIENT_TEST(failure_verifier, nullptr,
                           PFX_STR
                           "\x00\x00\x04\x08\x00\x00\x00\x00\x01"
                           "\x00\x00\x00\x00",
                           0);

  GRPC_RUN_BAD_CLIENT_TEST(
      verifier, nullptr,
      ONE_SETTING_HDR
      "\xFE\x05\x00\x00\x00\x01" USUAL_HDR
      "\x00\x00\x05\xC8\x00\x00\x00\x00\x00\x68\x65\x6C\x6C\x6F",
      0);

  GRPC_RUN_BAD_CLIENT_TEST(
      VerifyRpcDoesNotGetCanceled, nullptr,
      ONE_SETTING_HDR
      "\xFE\x05\x00\x00\x00\x00" USUAL_HDR
      "\x00\x00\x05\xC8\x00\x00\x00\x00\x00\x68\x65\x6C\x6C\x6F",
      0);

  GRPC_RUN_BAD_CLIENT_TEST(failure_verifier, nullptr,
                           PFX_STR "\x00\x00\x04\x07\x00\x00\x00\x00\x00", 0);

  GRPC_RUN_BAD_CLIENT_TEST(failure_verifier, nullptr,
                           PFX_STR "\x00\x01\x12\x07\x00\x00\x00\x00\x00",
                           GRPC_BAD_CLIENT_DISCONNECT);

  GRPC_RUN_BAD_CLIENT_TEST(failure_verifier, nullptr,
                           PFX_STR "\x00\x00\x01\x03\x00\x00\x00\x00\x01", 0);

  GRPC_RUN_BAD_CLIENT_TEST(failure_verifier, nullptr,
                           PFX_STR "\x00\x00\x00\x03\x10\x00\x00\x00\x01", 0);

  grpc_shutdown();
  return 0;
}
