
// Copyright 2015 gRPC authors.

#include <grpc/grpc.h>
#include <grpc/slice.h>

#include "absl/log/check.h"
#include "absl/strings/str_cat.h"
#include "src/core/lib/experiments/experiments.h"
#include "src/core/server/server.h"
#include "test/core/bad_client/bad_client.h"
#include "test/core/end2end/cq_verifier.h"
#include "test/core/test_util/test_config.h"

#define PFX_STR "PRI * HTTP/2.0\r\n\r\nSM\r\n\r\n"
#define ONE_SETTING_HDR "\x00\x00\x06\x04\x00\x00\x00\x00\x00"
#define ZERO_SETTING_HDR "\x00\x00\x00\x04\x00\x00\x00\x00\x00"
#define SETTING_ACK "\x00\x00\x00\x04\x01\x00\x00\x00\x00"

#define RST_STREAM_1 "\x00\x00\x04\x03\x00\x00\x00\x00\x01\x00\x00\x00\x00"
#define RST_STREAM_3 "\x00\x00\x04\x03\x00\x00\x00\x00\x03\x00\x00\x00\x00"

#define FOOBAR_0                                                           \
  "\x00\x00\xca\x01\x04\x00\x00\x00\x01"

                   \
  "\x10\x05:path\x09/foo/bar0"                                             \
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

#define FOOBAR_1                                                           \
  "\x00\x00\xca\x01\x04\x00\x00\x00\x05"

                   \
  "\x10\x05:path\x09/foo/bar1"                                             \
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

#define FOOBAR_2                                                           \
  "\x00\x00\xca\x01\x04\x00\x00\x00\x03"

                   \
  "\x10\x05:path\x09/foo/bar2"                                             \
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

static void verifier(grpc_server* server, grpc_completion_queue* cq,
                     void* ) {
  while (grpc_core::Server::FromC(server)->HasOpenConnections()) {
    CHECK(grpc_completion_queue_next(
              cq, grpc_timeout_milliseconds_to_deadline(20), nullptr)
              .type == GRPC_QUEUE_TIMEOUT);
  }
}

static void single_request_verifier(grpc_server* server,
                                    grpc_completion_queue* cq,
                                    void* ) {
  grpc_call_error error;
  grpc_call* s;
  grpc_call_details call_details;
  grpc_core::CqVerifier cqv(cq);
  grpc_metadata_array request_metadata_recv;

  for (int i = 0; i < 2; i++) {
    grpc_call_details_init(&call_details);
    grpc_metadata_array_init(&request_metadata_recv);

    error = grpc_server_request_call(server, &s, &call_details,
                                     &request_metadata_recv, cq, cq,
                                     grpc_core::CqVerifier::tag(101));
    CHECK_EQ(error, GRPC_CALL_OK);
    cqv.Expect(grpc_core::CqVerifier::tag(101), true);
    cqv.Verify();

    CHECK_EQ(grpc_slice_str_cmp(call_details.host, "localhost"), 0);
    CHECK_EQ(grpc_slice_str_cmp(call_details.method,
                                absl::StrCat("/foo/bar", i).c_str()),
             0);

    grpc_metadata_array_destroy(&request_metadata_recv);
    grpc_call_details_destroy(&call_details);
    grpc_call_unref(s);
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
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr, PFX_STR "\x06",
                           GRPC_BAD_CLIENT_DISCONNECT);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr, PFX_STR "\x00\x06",
                           GRPC_BAD_CLIENT_DISCONNECT);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr, PFX_STR "\x00\x00\x06",
                           GRPC_BAD_CLIENT_DISCONNECT);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr, PFX_STR "\x00\x00\x00\x04",
                           GRPC_BAD_CLIENT_DISCONNECT);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr, PFX_STR "\x00\x00\x00\x04\x00",
                           GRPC_BAD_CLIENT_DISCONNECT);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr, PFX_STR "\x00\x00\x00\x04\x01",
                           GRPC_BAD_CLIENT_DISCONNECT);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr, PFX_STR "\x00\x00\x00\x04\xff",
                           GRPC_BAD_CLIENT_DISCONNECT);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr,
                           PFX_STR "\x00\x00\x00\x04\x00\x00",
                           GRPC_BAD_CLIENT_DISCONNECT);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr,
                           PFX_STR "\x00\x00\x00\x04\x00\x00\x00",
                           GRPC_BAD_CLIENT_DISCONNECT);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr,
                           PFX_STR "\x00\x00\x00\x04\x00\x00\x00\x00",
                           GRPC_BAD_CLIENT_DISCONNECT);

  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr,
                           PFX_STR "\x00\x00\x00\x04\x00\x00\x00\x00\x01", 0);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr,
                           PFX_STR "\x00\x00\x00\x04\x00\x40\x00\x00\x00", 0);

  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr,
                           PFX_STR "\x00\x00\x01\x04\x00\x00\x00\x00\x00", 0);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr,
                           PFX_STR "\x00\x00\x02\x04\x00\x00\x00\x00\x00", 0);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr,
                           PFX_STR "\x00\x00\x03\x04\x00\x00\x00\x00\x00", 0);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr,
                           PFX_STR "\x00\x00\x04\x04\x00\x00\x00\x00\x00", 0);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr,
                           PFX_STR "\x00\x00\x05\x04\x00\x00\x00\x00\x00", 0);

  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr,
                           PFX_STR ONE_SETTING_HDR "\x00\x05\x00\x00\x00\x00",
                           GRPC_BAD_CLIENT_DISCONNECT);
  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr,
                           PFX_STR ONE_SETTING_HDR "\x00\x06\xff\xff\xff\xff",
                           GRPC_BAD_CLIENT_DISCONNECT);

  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr,
                           PFX_STR ONE_SETTING_HDR "\x00\x04\x00\x01\x00\x00",
                           GRPC_BAD_CLIENT_DISCONNECT);

  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr,
                           PFX_STR
                           "\x00\x00\x00\x04\x00\x00\x00\x00\x00"
                           "\x00\x00\x01\x04\x01\x00\x00\x00\x00",
                           0);

  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr,
                           PFX_STR "\x00\x00\x00\x04\x10\x00\x00\x00\x00", 0);

  GRPC_RUN_BAD_CLIENT_TEST(verifier, nullptr,
                           PFX_STR ONE_SETTING_HDR "\x00\x99\x00\x00\x00\x00",
                           GRPC_BAD_CLIENT_DISCONNECT);

  GRPC_RUN_BAD_CLIENT_TEST(single_request_verifier, nullptr,
                           PFX_STR ZERO_SETTING_HDR FOOBAR_0 FOOBAR_2
                               SETTING_ACK RST_STREAM_1 RST_STREAM_3 FOOBAR_1,
                           GRPC_BAD_CLIENT_MAX_CONCURRENT_REQUESTS_OF_ONE);

  grpc_shutdown();
  return 0;
}
