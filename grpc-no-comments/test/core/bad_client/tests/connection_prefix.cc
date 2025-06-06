
// Copyright 2015 gRPC authors.

#include <grpc/grpc.h>

#include "absl/log/check.h"
#include "src/core/server/server.h"
#include "test/core/bad_client/bad_client.h"
#include "test/core/test_util/test_config.h"

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

  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr, "X", 0);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr, "PX", 0);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr, "PRX", 0);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr, "PRIX", 0);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr, "PRI X", 0);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr, "PRI *X", 0);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr, "PRI * X", 0);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr, "PRI * HX", 0);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr, "PRI * HTX", 0);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr, "PRI * HTTX", 0);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr, "PRI * HTTPX", 0);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr, "PRI * HTTP/X", 0);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr, "PRI * HTTP/2X", 0);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr, "PRI * HTTP/2.X", 0);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr, "PRI * HTTP/2.0X", 0);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr, "PRI * HTTP/2.0\rX", 0);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr, "PRI * HTTP/2.0\r\nX", 0);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr, "PRI * HTTP/2.0\r\n\rX", 0);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr, "PRI * HTTP/2.0\r\n\r\nX", 0);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr, "PRI * HTTP/2.0\r\n\r\nSX", 0);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr, "PRI * HTTP/2.0\r\n\r\nSMX", 0);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr, "PRI * HTTP/2.0\r\n\r\nSM\rX", 0);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr, "PRI * HTTP/2.0\r\n\r\nSM\r\nX",
                           0);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr, "PRI * HTTP/2.0\r\n\r\nSM\r\n\rX",
                           0);

  grpc_shutdown();
  return 0;
}
