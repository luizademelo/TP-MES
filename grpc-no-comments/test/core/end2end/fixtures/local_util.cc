
// Copyright 2018 gRPC authors.

#include "test/core/end2end/fixtures/local_util.h"

#include <grpc/credentials.h>
#include <grpc/grpc_security.h>
#include <grpc/status.h>
#include <string.h>

#include <utility>

#include "absl/log/check.h"

static void process_auth_failure(void* state, grpc_auth_context* ,
                                 const grpc_metadata* ,
                                 size_t ,
                                 grpc_process_auth_metadata_done_cb cb,
                                 void* user_data) {
  CHECK_EQ(state, nullptr);
  cb(user_data, nullptr, 0, nullptr, 0, GRPC_STATUS_UNAUTHENTICATED, nullptr);
}

LocalTestFixture::LocalTestFixture(std::string localaddr,
                                   grpc_local_connect_type type)
    : localaddr_(std::move(localaddr)), type_(type) {}

grpc_server* LocalTestFixture::MakeServer(
    const grpc_core::ChannelArgs& args, grpc_completion_queue* cq,
    absl::AnyInvocable<void(grpc_server*)>& pre_server_start) {
  grpc_server_credentials* server_creds =
      grpc_local_server_credentials_create(type_);
  auto* server = grpc_server_create(args.ToC().get(), nullptr);
  grpc_server_register_completion_queue(server, cq, nullptr);
  if (args.Contains(FAIL_AUTH_CHECK_SERVER_ARG_NAME)) {
    grpc_auth_metadata_processor processor = {process_auth_failure, nullptr,
                                              nullptr};
    grpc_server_credentials_set_auth_metadata_processor(server_creds,
                                                        processor);
  }
  CHECK(grpc_server_add_http2_port(server, localaddr_.c_str(), server_creds));
  grpc_server_credentials_release(server_creds);
  pre_server_start(server);
  grpc_server_start(server);
  return server;
}

grpc_channel* LocalTestFixture::MakeClient(const grpc_core::ChannelArgs& args,
                                           grpc_completion_queue*) {
  grpc_channel_credentials* creds = grpc_local_credentials_create(type_);
  auto* client =
      grpc_channel_create(localaddr_.c_str(), creds, args.ToC().get());
  CHECK_NE(client, nullptr);
  grpc_channel_credentials_release(creds);
  return client;
}
