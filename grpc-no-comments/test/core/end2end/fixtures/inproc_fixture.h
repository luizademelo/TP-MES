// Copyright 2023 gRPC authors.

#ifndef GRPC_TEST_CORE_END2END_FIXTURES_INPROC_FIXTURE_H
#define GRPC_TEST_CORE_END2END_FIXTURES_INPROC_FIXTURE_H

#include <grpc/grpc.h>

#include "absl/functional/any_invocable.h"
#include "src/core/ext/transport/inproc/inproc_transport.h"
#include "src/core/lib/channel/channel_args.h"
#include "test/core/end2end/end2end_tests.h"

class InprocFixture : public grpc_core::CoreTestFixture {
 public:
  explicit InprocFixture(bool promise_based) : promise_based_(promise_based) {}

 private:
  grpc_server* MakeServer(
      const grpc_core::ChannelArgs& args, grpc_completion_queue* cq,
      absl::AnyInvocable<void(grpc_server*)>& pre_server_start) override {
    if (made_server_ != nullptr) return made_server_;
    made_server_ = grpc_server_create(
        args.Set("grpc.experimental.promise_based_inproc_transport",
                 promise_based_)
            .ToC()
            .get(),
        nullptr);
    grpc_server_register_completion_queue(made_server_, cq, nullptr);
    pre_server_start(made_server_);
    grpc_server_start(made_server_);
    return made_server_;
  }
  grpc_channel* MakeClient(const grpc_core::ChannelArgs& args,
                           grpc_completion_queue* cq) override {

    absl::AnyInvocable<void(grpc_server*)>
        not_sure_what_to_do_but_this_works_for_now = [](grpc_server*) {};
    return grpc_inproc_channel_create(
        MakeServer(args, cq, not_sure_what_to_do_but_this_works_for_now),
        args.Set("grpc.experimental.promise_based_inproc_transport",
                 promise_based_)
            .ToC()
            .get(),
        nullptr);
  }

  grpc_server* made_server_ = nullptr;
  const bool promise_based_;
};

#endif
