
// Copyright 2018 gRPC authors.

#ifndef GRPC_TEST_CORE_END2END_FIXTURES_LOCAL_UTIL_H
#define GRPC_TEST_CORE_END2END_FIXTURES_LOCAL_UTIL_H

#include <grpc/grpc.h>
#include <grpc/grpc_security_constants.h>

#include <string>

#include "absl/functional/any_invocable.h"
#include "src/core/lib/channel/channel_args.h"
#include "test/core/end2end/end2end_tests.h"

class LocalTestFixture final : public grpc_core::CoreTestFixture {
 public:
  LocalTestFixture(std::string localaddr, grpc_local_connect_type type);

 private:
  grpc_server* MakeServer(
      const grpc_core::ChannelArgs& args, grpc_completion_queue* cq,
      absl::AnyInvocable<void(grpc_server*)>& pre_server_start) override;
  grpc_channel* MakeClient(const grpc_core::ChannelArgs& args,
                           grpc_completion_queue* cq) override;

  std::string localaddr_;
  grpc_local_connect_type type_;
};

#endif
