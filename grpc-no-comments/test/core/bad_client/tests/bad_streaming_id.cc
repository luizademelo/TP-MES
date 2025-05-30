
// Copyright 2019 gRPC authors.

#include <grpc/grpc.h>

#include <memory>

#include "absl/log/check.h"
#include "gtest/gtest.h"
#include "src/core/server/server.h"
#include "test/core/bad_client/bad_client.h"
#include "test/core/test_util/test_config.h"

#define HEADER_FRAME_ID_1                                                  \
  "\x00\x00\xc9\x01\x05\x00\x00\x00\x01"

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

#define HEADER_FRAME_ID_2                                                  \
  "\x00\x00\xc9\x01\x05\x00\x00\x00\x02"

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

#define HEADER_FRAME_ID_3                                                  \
  "\x00\x00\xc9\x01\x05\x00\x00\x00\x03"

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

namespace {

void verifier(grpc_server* server, grpc_completion_queue* cq,
              void* ) {
  while (grpc_core::Server::FromC(server)->HasOpenConnections()) {
    CHECK(grpc_completion_queue_next(
              cq, grpc_timeout_milliseconds_to_deadline(20), nullptr)
              .type == GRPC_QUEUE_TIMEOUT);
  }
}

TEST(BadStreamingId, RegularHeader) {
  grpc_bad_client_arg args[2];
  args[0] = connection_preface_arg;
  args[1].client_validator = nullptr;
  args[1].client_payload = HEADER_FRAME_ID_1;
  args[1].client_payload_length = sizeof(HEADER_FRAME_ID_1) - 1;
  grpc_run_bad_client_test(verifier, args, 2, GRPC_BAD_CLIENT_DISCONNECT);
}

TEST(BadStreamingId, NonClientStreamId) {
  grpc_bad_client_arg args[2];
  args[0] = connection_preface_arg;

  args[1].client_validator = nullptr;
  args[1].client_payload = HEADER_FRAME_ID_2;
  args[1].client_payload_length = sizeof(HEADER_FRAME_ID_2) - 1;
  grpc_run_bad_client_test(verifier, args, 2, GRPC_BAD_CLIENT_DISCONNECT);
}

TEST(BadStreamingId, ClosedStreamId) {
  grpc_bad_client_arg args[4];
  args[0] = connection_preface_arg;

  args[1].client_validator = nullptr;
  args[1].client_payload = HEADER_FRAME_ID_1;
  args[1].client_payload_length = sizeof(HEADER_FRAME_ID_1) - 1;

  args[2].client_validator = nullptr;
  args[2].client_payload = HEADER_FRAME_ID_3;
  args[2].client_payload_length = sizeof(HEADER_FRAME_ID_3) - 1;

  args[3].client_validator = nullptr;
  args[3].client_payload = HEADER_FRAME_ID_1;
  args[3].client_payload_length = sizeof(HEADER_FRAME_ID_1) - 1;
  grpc_run_bad_client_test(verifier, args, 4, GRPC_BAD_CLIENT_DISCONNECT);
}

}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  grpc_init();
  int retval = RUN_ALL_TESTS();
  grpc_shutdown();
  return retval;
}
