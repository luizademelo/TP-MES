
// Copyright 2019 gRPC authors.

#ifndef GRPCPP_IMPL_DELEGATING_CHANNEL_H
#define GRPCPP_IMPL_DELEGATING_CHANNEL_H

#include <grpcpp/impl/channel_interface.h>

#include <memory>

namespace grpc {
namespace experimental {

class DelegatingChannel : public grpc::ChannelInterface {
 public:
  ~DelegatingChannel() override {}

  explicit DelegatingChannel(
      std::shared_ptr<grpc::ChannelInterface> delegate_channel)
      : delegate_channel_(delegate_channel) {}

  grpc_connectivity_state GetState(bool try_to_connect) override {
    return delegate_channel()->GetState(try_to_connect);
  }

  std::shared_ptr<grpc::ChannelInterface> delegate_channel() {
    return delegate_channel_;
  }

 private:
  internal::Call CreateCall(const internal::RpcMethod& method,
                            ClientContext* context,
                            grpc::CompletionQueue* cq) final {
    return delegate_channel()->CreateCall(method, context, cq);
  }

  void PerformOpsOnCall(internal::CallOpSetInterface* ops,
                        internal::Call* call) final {
    delegate_channel()->PerformOpsOnCall(ops, call);
  }

  void* RegisterMethod(const char* method) final {
    return delegate_channel()->RegisterMethod(method);
  }

  void NotifyOnStateChangeImpl(grpc_connectivity_state last_observed,
                               gpr_timespec deadline, grpc::CompletionQueue* cq,
                               void* tag) override {
    delegate_channel()->NotifyOnStateChangeImpl(last_observed, deadline, cq,
                                                tag);
  }

  bool WaitForStateChangeImpl(grpc_connectivity_state last_observed,
                              gpr_timespec deadline) override {
    return delegate_channel()->WaitForStateChangeImpl(last_observed, deadline);
  }

  internal::Call CreateCallInternal(const internal::RpcMethod& method,
                                    ClientContext* context,
                                    grpc::CompletionQueue* cq,
                                    size_t interceptor_pos) final {
    return delegate_channel()->CreateCallInternal(method, context, cq,
                                                  interceptor_pos);
  }

  grpc::CompletionQueue* CallbackCQ() final {
    return delegate_channel()->CallbackCQ();
  }

  std::shared_ptr<grpc::ChannelInterface> delegate_channel_;
};

}
}

#endif
