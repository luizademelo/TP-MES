
// Copyright 2019 gRPC authors.

#ifndef GRPCPP_TEST_DEFAULT_REACTOR_TEST_PEER_H
#define GRPCPP_TEST_DEFAULT_REACTOR_TEST_PEER_H

#include <grpcpp/server_context.h>
#include <grpcpp/support/server_callback.h>

namespace grpc {
namespace testing {

class DefaultReactorTestPeer {
 public:
  explicit DefaultReactorTestPeer(CallbackServerContext* ctx)
      : DefaultReactorTestPeer(ctx, [](Status) {}) {}
  DefaultReactorTestPeer(CallbackServerContext* ctx,
                         std::function<void(Status)> finish_func)
      : ctx_(ctx) {
    ctx->SetupTestDefaultReactor(std::move(finish_func));
  }
  ServerUnaryReactor* reactor() const {
    return reinterpret_cast<ServerUnaryReactor*>(&ctx_->default_reactor_);
  }
  bool test_status_set() const { return ctx_->test_status_set(); }
  Status test_status() const { return ctx_->test_status(); }

 private:
  CallbackServerContext* const ctx_;
};

}
}

#endif
