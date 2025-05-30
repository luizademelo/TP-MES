
// Copyright 2015 gRPC authors.

#include <grpc/grpc.h>

#include "absl/log/check.h"
#include "src/core/server/server.h"
#include "test/core/bad_client/bad_client.h"
#include "test/core/test_util/test_config.h"

#define PFX_STR                      \
  "PRI * HTTP/2.0\r\n\r\nSM\r\n\r\n" \
  "\x00\x00\x00\x04\x00\x00\x00\x00\x00"

static void verifier(grpc_server* server, grpc_completion_queue* cq,
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

  GRPC_RUN_BAD_CLIENT_TEST(
      verifier, nullptr,
      PFX_STR
      "\x00\x00\xc2\x01\x04\x00\x00\x00\x01"
      "\x10\x05:path\x08/foo/bar"
      "\x10\x07:scheme\x04http"
      "\x10\x07:method\x04POST"
      "\x10\x0a:authority\x09localhost"
      "\x10\x0c"
      "content-type\x09text/html"
      "\x10\x14grpc-accept-encoding\x15identity,deflate,gzip"
      "\x10\x02te\x08trailers"
      "\x10\x0auser-agent\"bad-client grpc-c/0.12.0.0 (linux)",
      GRPC_BAD_CLIENT_DISCONNECT);

  GRPC_RUN_BAD_CLIENT_TEST(
      verifier, nullptr,
      PFX_STR
      "\x00\x00\xcb\x01\x04\x00\x00\x00\x01"
      "\x10\x05:path\x08/foo/bar"
      "\x10\x07:scheme\x04http"
      "\x10\x07:method\x04POST"
      "\x10\x0a:authority\x09localhost"
      "\x10\x0c"
      "content-type\x10"
      "application/grpc"
      "\x10\x14grpc-accept-encoding\x15identity,deflate,gzip"
      "\x10\x02te\x0a"
      "frobnicate"
      "\x10\x0auser-agent\"bad-client grpc-c/0.12.0.0 (linux)",
      GRPC_BAD_CLIENT_DISCONNECT);

  GRPC_RUN_BAD_CLIENT_TEST(
      verifier, nullptr,
      PFX_STR
      "\x00\x00\xd9\x01\x04\x00\x00\x00\x01"
      "\x10\x05:path\x08/foo/bar"
      "\x10\x05:path\x08/foo/bah"
      "\x10\x07:scheme\x04http"
      "\x10\x07:method\x04POST"
      "\x10\x0a:authority\x09localhost"
      "\x10\x0c"
      "content-type\x10"
      "application/grpc"
      "\x10\x14grpc-accept-encoding\x15identity,deflate,gzip"
      "\x10\x02te\x08trailers"
      "\x10\x0auser-agent\"bad-client grpc-c/0.12.0.0 (linux)",
      GRPC_BAD_CLIENT_DISCONNECT);

  GRPC_RUN_BAD_CLIENT_TEST(
      verifier, nullptr,
      PFX_STR
      "\x00\x00\xd2\x01\x04\x00\x00\x00\x01"
      "\x10\x05:path\x08/foo/bar"
      "\x10\x07:scheme\x04http"
      "\x10\x07:method\x04POST"
      "\x10\x0a:authority\x09localhost"
      "\x10\x0c"
      "content-type\x10"
      "application/grpc"
      "\x10\x14grpc-accept-encoding\x1enobody-knows-the-trouble-i-see"
      "\x10\x02te\x08trailers"
      "\x10\x0auser-agent\"bad-client grpc-c/0.12.0.0 (linux)",
      GRPC_BAD_CLIENT_DISCONNECT);

  GRPC_RUN_BAD_CLIENT_TEST(
      verifier, nullptr,
      PFX_STR
      "\x00\x00\xf5\x01\x04\x00\x00\x00\x01"
      "\x10\x05:path\x08/foo/bar"
      "\x10\x07:scheme\x04http"
      "\x10\x07:method\x04POST"
      "\x10\x0a:authority\x09localhost"
      "\x10\x0c"
      "content-type\x10"
      "application/grpc"
      "\x10\x14grpc-accept-encoding\x15identity,deflate,gzip"
      "\x10\x0dgrpc-encoding\x1cyou-dont-know-how-to-do-this"
      "\x10\x02te\x08trailers"
      "\x10\x0auser-agent\"bad-client grpc-c/0.12.0.0 (linux)",
      GRPC_BAD_CLIENT_DISCONNECT);

  grpc_shutdown();
  return 0;
}
