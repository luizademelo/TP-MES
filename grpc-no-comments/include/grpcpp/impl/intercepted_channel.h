
// Copyright 2018 gRPC authors.

#ifndef GRPCPP_IMPL_INTERCEPTED_CHANNEL_H
#define GRPCPP_IMPL_INTERCEPTED_CHANNEL_H

#include <grpcpp/impl/channel_interface.h>

namespace grpc {
class CompletionQueue;

namespace internal {

class InterceptorBatchMethodsImpl;

class InterceptedChannel : public ChannelInterface {
 public:
  ~InterceptedChannel() override { channel_ = nullptr; }

  grpc_connectivity_state GetState(bool try_to_connect) override {
    return channel_->GetState(try_to_connect);
  }

 private:
  InterceptedChannel(ChannelInterface* channel, size_t pos)
      : channel_(channel), interceptor_pos_(pos) {}

  Call CreateCall(const RpcMethod& method, grpc::ClientContext* context,
                  grpc::CompletionQueue* cq) override {
    return channel_->CreateCallInternal(method, context, cq, interceptor_pos_);
  }

  void PerformOpsOnCall(CallOpSetInterface* ops, Call* call) override {
    return channel_->PerformOpsOnCall(ops, call);
  }
  void* RegisterMethod(const char* method) override {
    return channel_->RegisterMethod(method);
  }

  void NotifyOnStateChangeImpl(grpc_connectivity_state last_observed,
                               gpr_timespec deadline, grpc::CompletionQueue* cq,
                               void* tag) override {
    return channel_->NotifyOnStateChangeImpl(last_observed, deadline, cq, tag);
  }
  bool WaitForStateChangeImpl(grpc_connectivity_state last_observed,
                              gpr_timespec deadline) override {
    return channel_->WaitForStateChangeImpl(last_observed, deadline);
  }

  grpc::CompletionQueue* CallbackCQ() override {
    return channel_->CallbackCQ();
  }

  ChannelInterface* channel_;
  size_t interceptor_pos_;

  friend class InterceptorBatchMethodsImpl;
};
}
}

#endif
