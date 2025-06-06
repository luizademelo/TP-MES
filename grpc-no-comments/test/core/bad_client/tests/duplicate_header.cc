
// Copyright 2018 gRPC authors.

#include <grpc/grpc.h>
#include <grpc/slice.h>
#include <grpc/status.h>
#include <string.h>

#include "absl/log/check.h"
#include "src/core/util/time.h"
#include "test/core/bad_client/bad_client.h"
#include "test/core/end2end/cq_verifier.h"
#include "test/core/test_util/test_config.h"

#define PFX_STR                      \
  "PRI * HTTP/2.0\r\n\r\nSM\r\n\r\n" \
  "\x00\x00\x00\x04\x00\x00\x00\x00\x00"

#define HEADER_STR                                                         \
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

#define PAYLOAD_STR                      \
  "\x00\x00\x20\x00\x00\x00\x00\x00\x01" \
  "\x00\x00\x00\x00"

static void verifier(grpc_server* server, grpc_completion_queue* cq,
                     void* ) {
  grpc_call_error error;
  grpc_call* s;
  grpc_call_details call_details;
  grpc_byte_buffer* request_payload_recv = nullptr;
  grpc_op* op;
  grpc_op ops[6];
  grpc_core::CqVerifier cqv(cq);
  grpc_metadata_array request_metadata_recv;
  int was_cancelled = 2;

  grpc_call_details_init(&call_details);
  grpc_metadata_array_init(&request_metadata_recv);

  error = grpc_server_request_call(server, &s, &call_details,
                                   &request_metadata_recv, cq, cq,
                                   grpc_core::CqVerifier::tag(101));
  CHECK_EQ(error, GRPC_CALL_OK);
  bool got = false;
  cqv.Expect(grpc_core::CqVerifier::tag(101),
             grpc_core::CqVerifier::Maybe{&got});
  cqv.Verify(grpc_core::Duration::Seconds(1));

  if (!got) {
    grpc_server_shutdown_and_notify(server, cq, grpc_core::CqVerifier::tag(99));
    cqv.Expect(grpc_core::CqVerifier::tag(101), false);
    cqv.Expect(grpc_core::CqVerifier::tag(99), true);
    cqv.Verify();
    return;
  }

  CHECK_EQ(grpc_slice_str_cmp(call_details.host, "localhost"), 0);
  CHECK_EQ(grpc_slice_str_cmp(call_details.method, "/foo/bar"), 0);

  memset(ops, 0, sizeof(ops));
  op = ops;
  op->op = GRPC_OP_SEND_INITIAL_METADATA;
  op->data.send_initial_metadata.count = 0;
  op->flags = 0;
  op->reserved = nullptr;
  op++;
  op->op = GRPC_OP_RECV_MESSAGE;
  op->data.recv_message.recv_message = &request_payload_recv;
  op->flags = 0;
  op->reserved = nullptr;
  op++;
  error = grpc_call_start_batch(s, ops, static_cast<size_t>(op - ops),
                                grpc_core::CqVerifier::tag(102), nullptr);
  CHECK_EQ(error, GRPC_CALL_OK);

  cqv.Expect(grpc_core::CqVerifier::tag(102),
             grpc_core::CqVerifier::AnyStatus());
  cqv.Verify();

  memset(ops, 0, sizeof(ops));
  op = ops;
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

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  grpc_init();

  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr,
                           PFX_STR HEADER_STR HEADER_STR PAYLOAD_STR, 0);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr,
                           PFX_STR HEADER_STR HEADER_STR HEADER_STR PAYLOAD_STR,
                           0);
  grpc_shutdown();
  return 0;
}
