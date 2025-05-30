
// Copyright 2015 gRPC authors.

#ifndef GRPCPP_IMPL_CALL_H
#define GRPCPP_IMPL_CALL_H

#include <grpc/impl/grpc_types.h>
#include <grpcpp/impl/call_hook.h>

namespace grpc {
class CompletionQueue;
namespace experimental {
class ClientRpcInfo;
class ServerRpcInfo;
}
namespace internal {
class CallHook;
class CallOpSetInterface;

class Call final {
 public:
  Call()
      : call_hook_(nullptr),
        cq_(nullptr),
        call_(nullptr),
        max_receive_message_size_(-1) {}

  Call(grpc_call* call, CallHook* call_hook, grpc::CompletionQueue* cq)
      : call_hook_(call_hook),
        cq_(cq),
        call_(call),
        max_receive_message_size_(-1) {}

  Call(grpc_call* call, CallHook* call_hook, grpc::CompletionQueue* cq,
       experimental::ClientRpcInfo* rpc_info)
      : call_hook_(call_hook),
        cq_(cq),
        call_(call),
        max_receive_message_size_(-1),
        client_rpc_info_(rpc_info) {}

  Call(grpc_call* call, CallHook* call_hook, grpc::CompletionQueue* cq,
       int max_receive_message_size, experimental::ServerRpcInfo* rpc_info)
      : call_hook_(call_hook),
        cq_(cq),
        call_(call),
        max_receive_message_size_(max_receive_message_size),
        server_rpc_info_(rpc_info) {}

  void PerformOps(CallOpSetInterface* ops) {
    call_hook_->PerformOpsOnCall(ops, this);
  }

  grpc_call* call() const { return call_; }
  grpc::CompletionQueue* cq() const { return cq_; }

  int max_receive_message_size() const { return max_receive_message_size_; }

  experimental::ClientRpcInfo* client_rpc_info() const {
    return client_rpc_info_;
  }

  experimental::ServerRpcInfo* server_rpc_info() const {
    return server_rpc_info_;
  }

 private:
  CallHook* call_hook_;
  grpc::CompletionQueue* cq_;
  grpc_call* call_;
  int max_receive_message_size_;
  experimental::ClientRpcInfo* client_rpc_info_ = nullptr;
  experimental::ServerRpcInfo* server_rpc_info_ = nullptr;
};
}
}

#endif
