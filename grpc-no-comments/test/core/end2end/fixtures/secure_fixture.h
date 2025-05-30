// Copyright 2023 gRPC authors.

#ifndef GRPC_TEST_CORE_END2END_FIXTURES_SECURE_FIXTURE_H
#define GRPC_TEST_CORE_END2END_FIXTURES_SECURE_FIXTURE_H

#include <grpc/credentials.h>
#include <grpc/grpc.h>
#include <grpc/grpc_security.h>

#include <string>
#include <utility>

#include "absl/functional/any_invocable.h"
#include "absl/log/check.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/util/host_port.h"
#include "test/core/end2end/end2end_tests.h"
#include "test/core/test_util/port.h"

class SecureFixture : public grpc_core::CoreTestFixture {
 public:
  explicit SecureFixture(std::string localaddr = grpc_core::JoinHostPort(
                             "localhost", grpc_pick_unused_port_or_die()))
      : localaddr_(std::move(localaddr)) {}

 protected:
  const std::string& localaddr() const { return localaddr_; }

  virtual grpc_core::ChannelArgs MutateClientArgs(grpc_core::ChannelArgs args) {
    return args;
  }
  virtual grpc_core::ChannelArgs MutateServerArgs(grpc_core::ChannelArgs args) {
    return args;
  }

 private:
  virtual grpc_channel_credentials* MakeClientCreds(
      const grpc_core::ChannelArgs& args) = 0;
  virtual grpc_server_credentials* MakeServerCreds(
      const grpc_core::ChannelArgs& args) = 0;
  grpc_server* MakeServer(
      const grpc_core::ChannelArgs& in_args, grpc_completion_queue* cq,
      absl::AnyInvocable<void(grpc_server*)>& pre_server_start) override {
    auto args = MutateServerArgs(in_args);
    auto* creds = MakeServerCreds(args);
    auto* server = grpc_server_create(args.ToC().get(), nullptr);
    grpc_server_register_completion_queue(server, cq, nullptr);
    CHECK(grpc_server_add_http2_port(server, localaddr_.c_str(), creds));
    grpc_server_credentials_release(creds);
    pre_server_start(server);
    grpc_server_start(server);
    return server;
  }
  grpc_channel* MakeClient(const grpc_core::ChannelArgs& in_args,
                           grpc_completion_queue*) override {
    auto args = MutateClientArgs(in_args);
    auto* creds = MakeClientCreds(args);
    auto* client =
        grpc_channel_create(localaddr_.c_str(), creds, args.ToC().get());
    CHECK_NE(client, nullptr);
    grpc_channel_credentials_release(creds);
    return client;
  }

  std::string localaddr_;
};

class InsecureFixture : public SecureFixture {
 public:
  using SecureFixture::SecureFixture;

 private:
  grpc_channel_credentials* MakeClientCreds(
      const grpc_core::ChannelArgs&) override {
    return grpc_insecure_credentials_create();
  }
  grpc_server_credentials* MakeServerCreds(
      const grpc_core::ChannelArgs&) override {
    return grpc_insecure_server_credentials_create();
  }
};

#endif
