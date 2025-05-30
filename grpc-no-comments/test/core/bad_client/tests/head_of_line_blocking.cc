
// Copyright 2015 gRPC authors.

#include <grpc/byte_buffer.h>
#include <grpc/grpc.h>
#include <grpc/support/alloc.h>
#include <grpc/support/time.h>
#include <stdint.h>
#include <string.h>

#include <algorithm>

#include "absl/log/check.h"
#include "test/core/bad_client/bad_client.h"
#include "test/core/end2end/cq_verifier.h"
#include "test/core/test_util/test_config.h"

static const char prefix[] =
    "PRI * HTTP/2.0\r\n\r\nSM\r\n\r\n"

    "\x00\x00\x00\x04\x00\x00\x00\x00\x00"

    "\x00\x00\xd0\x01\x04\x00\x00\x00\x01"
    "\x10\x05:path\x0f/registered/bar"
    "\x10\x07:scheme\x04http"
    "\x10\x07:method\x04POST"
    "\x10\x0a:authority\x09localhost"
    "\x10\x0c"
    "content-type\x10"
    "application/grpc"
    "\x10\x14grpc-accept-encoding\x15identity,deflate,gzip"
    "\x10\x02te\x08trailers"
    "\x10\x0auser-agent\"bad-client grpc-c/0.12.0.0 (linux)"

    "\x00\x00\x05\x00\x00\x00\x00\x00\x01"
    "\x01\x00\x00\x27\x10"

    "\x00\x00\xd0\x01\x04\x00\x00\x00\x03"
    "\x10\x05:path\x0f/registered/bar"
    "\x10\x07:scheme\x04http"
    "\x10\x07:method\x04POST"
    "\x10\x0a:authority\x09localhost"
    "\x10\x0c"
    "content-type\x10"
    "application/grpc"
    "\x10\x14grpc-accept-encoding\x15identity,deflate,gzip"
    "\x10\x02te\x08trailers"
    "\x10\x0auser-agent\"bad-client grpc-c/0.12.0.0 (linux)"

    "\x00\x00\x05\x00\x00\x00\x00\x00\x03"
    "\x01\x00\x00\x27\x10"
    "";

static void verifier(grpc_server* server, grpc_completion_queue* cq,
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

char* g_buffer;
size_t g_cap = 0;
size_t g_count = 0;

static void addbuf(const void* data, size_t len) {
  if (g_count + len > g_cap) {
    g_cap = std::max(g_count + len, g_cap * 2);
    g_buffer = static_cast<char*>(gpr_realloc(g_buffer, g_cap));
  }
  memcpy(g_buffer + g_count, data, len);
  g_count += len;
}

int main(int argc, char** argv) {
  int i;
  grpc::testing::TestEnvironment env(&argc, argv);
  grpc_init();

#define NUM_FRAMES 10
#define FRAME_SIZE 1000

  addbuf(prefix, sizeof(prefix) - 1);
  for (i = 0; i < NUM_FRAMES; i++) {
    uint8_t hdr[9] = {static_cast<uint8_t>(FRAME_SIZE >> 16),
                      static_cast<uint8_t>(FRAME_SIZE >> 8),
                      static_cast<uint8_t>(FRAME_SIZE),
                      0,
                      0,
                      0,
                      0,
                      0,
                      3};
    uint8_t msg[FRAME_SIZE];
    memset(msg, 'a', sizeof(msg));
    addbuf(hdr, sizeof(hdr));
    addbuf(msg, FRAME_SIZE);
  }
  grpc_bad_client_arg bca = {nullptr, nullptr, g_buffer, g_count};
  grpc_run_bad_client_test(verifier, &bca, 1, 0);
  gpr_free(g_buffer);
  grpc_shutdown();

  return 0;
}
