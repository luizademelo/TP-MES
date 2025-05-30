
// Copyright 2015 gRPC authors.

#ifndef GRPC_TEST_CORE_BAD_CLIENT_BAD_CLIENT_H
#define GRPC_TEST_CORE_BAD_CLIENT_BAD_CLIENT_H

#include <grpc/grpc.h>
#include <grpc/slice.h>
#include <stddef.h>
#include <stdint.h>

#define GRPC_BAD_CLIENT_REGISTERED_METHOD "/registered/bar"
#define GRPC_BAD_CLIENT_REGISTERED_HOST "localhost"

typedef void (*grpc_bad_client_server_side_validator)(grpc_server* server,
                                                      grpc_completion_queue* cq,
                                                      void* registered_method);

typedef bool (*grpc_bad_client_client_stream_validator)(
    grpc_slice_buffer* incoming, void* arg);

struct grpc_bad_client_arg {
  grpc_bad_client_client_stream_validator client_validator;
  void* client_validator_arg;
  const char* client_payload;
  size_t client_payload_length;
};

#define GRPC_BAD_CLIENT_DISCONNECT 1
#define GRPC_BAD_CLIENT_LARGE_REQUEST 2
#define GRPC_BAD_CLIENT_MAX_CONCURRENT_REQUESTS_OF_ONE 4

void grpc_run_bad_client_test(
    grpc_bad_client_server_side_validator server_validator,
    grpc_bad_client_arg args[], int num_args, uint32_t flags);

#define COMBINE1(X, Y) X##Y
#define COMBINE(X, Y) COMBINE1(X, Y)

#define GRPC_RUN_BAD_CLIENT_TEST(server_validator, client_validator, payload,  \
                                 flags)                                        \
  grpc_bad_client_arg COMBINE(bca, __LINE__) = {client_validator, nullptr,     \
                                                payload, sizeof(payload) - 1}; \
  grpc_run_bad_client_test(server_validator, &COMBINE(bca, __LINE__), 1, flags)

bool client_connection_preface_validator(grpc_slice_buffer* incoming,
                                         void* arg);

bool rst_stream_client_validator(grpc_slice_buffer* incoming, void* arg);

extern grpc_bad_client_arg connection_preface_arg;

void server_verifier_request_call(grpc_server* server,
                                  grpc_completion_queue* cq,
                                  void* registered_method);
#endif
