
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

  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr, PFX_STR "\x00",
                           GRPC_BAD_CLIENT_DISCONNECT);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr, PFX_STR "\x00\x00",
                           GRPC_BAD_CLIENT_DISCONNECT);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr, PFX_STR "\x00\x00\x00",
                           GRPC_BAD_CLIENT_DISCONNECT);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr, PFX_STR "\x00\x00\x00\x01",
                           GRPC_BAD_CLIENT_DISCONNECT);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr, PFX_STR "\x00\x00\x00\x01\x00",
                           GRPC_BAD_CLIENT_DISCONNECT);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr, PFX_STR "\x00\x00\x00\x01\x04",
                           GRPC_BAD_CLIENT_DISCONNECT);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr, PFX_STR "\x00\x00\x00\x01\x05",
                           GRPC_BAD_CLIENT_DISCONNECT);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr,
                           PFX_STR "\x00\x00\x00\x01\x04\x00",
                           GRPC_BAD_CLIENT_DISCONNECT);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr,
                           PFX_STR "\x00\x00\x00\x01\x04\x00\x00",
                           GRPC_BAD_CLIENT_DISCONNECT);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr,
                           PFX_STR "\x00\x00\x00\x01\x04\x00\x00\x00",
                           GRPC_BAD_CLIENT_DISCONNECT);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr,
                           PFX_STR "\x00\x00\x00\x01\x04\x00\x00\x00\x00",
                           GRPC_BAD_CLIENT_DISCONNECT);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr,
                           PFX_STR "\x00\x00\x00\x01\x04\x00\x00\x00\x01",
                           GRPC_BAD_CLIENT_DISCONNECT);

  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr,
                           PFX_STR
                           "\x00\x00\x01\x01\x24\x00\x00\x00\x01"
                           "\x00",
                           0);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr,
                           PFX_STR
                           "\x00\x00\x02\x01\x24\x00\x00\x00\x01"
                           "\x00\x00",
                           0);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr,
                           PFX_STR
                           "\x00\x00\x03\x01\x24\x00\x00\x00\x01"
                           "\x00\x00\x00",
                           0);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr,
                           PFX_STR
                           "\x00\x00\x04\x01\x24\x00\x00\x00\x01"
                           "\x00\x00\x00\x00",
                           0);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr,
                           PFX_STR
                           "\x00\x00\x05\x01\x24\x00\x00\x00\x01"
                           "",
                           GRPC_BAD_CLIENT_DISCONNECT);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr,
                           PFX_STR
                           "\x00\x00\x05\x01\x24\x00\x00\x00\x01"
                           "\x00",
                           GRPC_BAD_CLIENT_DISCONNECT);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr,
                           PFX_STR
                           "\x00\x00\x05\x01\x24\x00\x00\x00\x01"
                           "\x00\x00",
                           GRPC_BAD_CLIENT_DISCONNECT);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr,
                           PFX_STR
                           "\x00\x00\x05\x01\x24\x00\x00\x00\x01"
                           "\x00\x00\x00",
                           GRPC_BAD_CLIENT_DISCONNECT);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr,
                           PFX_STR
                           "\x00\x00\x05\x01\x24\x00\x00\x00\x01"
                           "\x00\x00\x00\x00",
                           GRPC_BAD_CLIENT_DISCONNECT);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr,
                           PFX_STR
                           "\x00\x00\x05\x01\x24\x00\x00\x00\x01"
                           "\x00\x00\x00\x00\x00",
                           GRPC_BAD_CLIENT_DISCONNECT);

  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr,
                           PFX_STR
                           "\x00\x00\x01\x01\x04\x00\x00\x00\x01"
                           "\xfe",
                           0);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr,
                           PFX_STR
                           "\x00\x00\x04\x01\x04\x00\x00\x00\x01"
                           "\x7f\x7f\x01"
                           "a",
                           0);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr,
                           PFX_STR
                           "\x00\x00\x04\x01\x04\x00\x00\x00\x01"
                           "\x0f\x7f\x01"
                           "a",
                           0);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr,
                           PFX_STR
                           "\x00\x00\x04\x01\x04\x00\x00\x00\x01"
                           "\x1f\x7f\x01"
                           "a",
                           0);

  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr,
                           PFX_STR
                           "\x00\x00\x03\x01\x04\x00\x00\x00\x01"
                           "\x01\x01"
                           "a",
                           GRPC_BAD_CLIENT_DISCONNECT);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr,
                           PFX_STR
                           "\x00\x00\x03\x01\x04\x00\x00\x00\x01"
                           "\x11\x01"
                           "a",
                           GRPC_BAD_CLIENT_DISCONNECT);

  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr,
                           PFX_STR
                           "\x00\x00\x01\x01\x04\x00\x00\x00\x01"
                           "\x80",
                           0);

  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr,
                           PFX_STR
                           "\x00\x00\x02\x01\x04\x00\x00\x00\x01"
                           "\xff\x00",
                           0);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr,
                           PFX_STR
                           "\x00\x00\x03\x01\x04\x00\x00\x00\x01"
                           "\xff\x80\x00",
                           0);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr,
                           PFX_STR
                           "\x00\x00\x04\x01\x04\x00\x00\x00\x01"
                           "\xff\x80\x80\x00",
                           0);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr,
                           PFX_STR
                           "\x00\x00\x05\x01\x04\x00\x00\x00\x01"
                           "\xff\x80\x80\x80\x00",
                           0);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr,
                           PFX_STR
                           "\x00\x00\x06\x01\x04\x00\x00\x00\x01"
                           "\xff\x80\x80\x80\x80\x00",
                           0);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr,
                           PFX_STR
                           "\x00\x00\x07\x01\x04\x00\x00\x00\x01"
                           "\xff\x80\x80\x80\x80\x80\x00",
                           0);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr,
                           PFX_STR
                           "\x00\x00\x08\x01\x04\x00\x00\x00\x01"
                           "\xff",
                           GRPC_BAD_CLIENT_DISCONNECT);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr,
                           PFX_STR
                           "\x00\x00\x08\x01\x04\x00\x00\x00\x01"
                           "\xff\x80",
                           GRPC_BAD_CLIENT_DISCONNECT);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr,
                           PFX_STR
                           "\x00\x00\x08\x01\x04\x00\x00\x00\x01"
                           "\xff\x80\x80",
                           GRPC_BAD_CLIENT_DISCONNECT);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr,
                           PFX_STR
                           "\x00\x00\x08\x01\x04\x00\x00\x00\x01"
                           "\xff\x80\x80\x80",
                           GRPC_BAD_CLIENT_DISCONNECT);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr,
                           PFX_STR
                           "\x00\x00\x08\x01\x04\x00\x00\x00\x01"
                           "\xff\x80\x80\x80\x80",
                           GRPC_BAD_CLIENT_DISCONNECT);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr,
                           PFX_STR
                           "\x00\x00\x08\x01\x04\x00\x00\x00\x01"
                           "\xff\x80\x80\x80\x80\x80",
                           GRPC_BAD_CLIENT_DISCONNECT);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr,
                           PFX_STR
                           "\x00\x00\x08\x01\x04\x00\x00\x00\x01"
                           "\xff\x80\x80\x80\x80\x80\x80",
                           GRPC_BAD_CLIENT_DISCONNECT);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr,
                           PFX_STR
                           "\x00\x00\x08\x01\x04\x00\x00\x00\x01"
                           "\xff\x80\x80\x80\x80\x80\x80\x00",
                           0);

  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr,
                           PFX_STR
                           "\x00\x00\x06\x01\x04\x00\x00\x00\x01"
                           "\xff\x80\x80\x80\x80\x7f",
                           GRPC_BAD_CLIENT_DISCONNECT);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr,
                           PFX_STR
                           "\x00\x00\x06\x01\x04\x00\x00\x00\x01"
                           "\xff\xff\xff\xff\xff\x0f",
                           GRPC_BAD_CLIENT_DISCONNECT);

  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr,
                           PFX_STR
                           "\x00\x00\x08\x01\x04\x00\x00\x00\x01"
                           "\xff\x80\x80\x80\x80\x80\x80\x02",
                           0);

  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr,
                           PFX_STR
                           "\x00\x00\x01\x01\x04\x00\x00\x00\x01"
                           "\x01",
                           GRPC_BAD_CLIENT_DISCONNECT);

  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr,
                           PFX_STR
                           "\x00\x00\x03\x01\x04\x00\x00\x00\x01"
                           "\x3f\xe1\x1f",
                           GRPC_BAD_CLIENT_DISCONNECT);

  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr,
                           PFX_STR
                           "\x00\x00\x03\x01\x04\x00\x00\x00\x01"
                           "\x3f\xf1\x1f",
                           0);

  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr,
                           PFX_STR
                           "\x00\x00\x04\x01\x04\x00\x00\x00\x01"
                           "\x20\x3f\xe1\x1f",
                           GRPC_BAD_CLIENT_DISCONNECT);

  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr,
                           PFX_STR
                           "\x00\x00\x03\x01\x04\x00\x00\x00\x01"
                           "\x20\x20\x20",
                           0);

  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr,
                           PFX_STR
                           "\x00\x00\x00\x01\x00\x00\x00\x00\x01"
                           "\x00\x00\x00\x09\x04\x00\x00\x00\x01",
                           GRPC_BAD_CLIENT_DISCONNECT);

  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr,
                           PFX_STR
                           "\x00\x00\x00\x01\x00\x00\x00\x00\x01"
                           "\x00\x00\x00\x00\x04\x00\x00\x00\x01",
                           0);

  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr,
                           PFX_STR
                           "\x00\x00\x00\x01\x04\x00\x00\x00\x01"
                           "\x00\x00\x00\x01\x00\x00\x00\x00\x03"
                           "\x00\x00\x00\x09\x04\x00\x00\x00\x01",
                           0);

  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr,
                           PFX_STR "\x00\x00\x00\x09\x04\x00\x00\x00\x01", 0);

  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr,
                           PFX_STR
                           "\x00\x00\x00\x01\x04\x00\x00\x00\x01"
                           "\x00\x00\x00\x01\x04\x00\x00\x00\x01"
                           "\x00\x00\x00\x01\x04\x00\x00\x00\x01",
                           GRPC_BAD_CLIENT_DISCONNECT);

  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr,
                           PFX_STR "\x00\x00\x00\x01\x39\x67\xed\x1d\x64",
                           GRPC_BAD_CLIENT_DISCONNECT);

  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr,
                           PFX_STR
                           "\x00\x00\x19\x01\x04\x00\x00\x00\x01"
                           "\x10\x0cgrpc-timeout\x0a"
                           "15 seconds",
                           GRPC_BAD_CLIENT_DISCONNECT);

  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr,
                           PFX_STR
                           "\x00\x00\x19\x01\x04\x00\x00\x00\x01"
                           "\x10\x0cgrpc-timeout\x0a"
                           "15 seconds"
                           "\x00\x00\x19\x01\x04\x00\x00\x00\x03"
                           "\x10\x0cgrpc-timeout\x0a"
                           "15 seconds",
                           GRPC_BAD_CLIENT_DISCONNECT);

  grpc_shutdown();
  return 0;
}
