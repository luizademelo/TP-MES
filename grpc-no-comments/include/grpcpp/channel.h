
// Copyright 2015 gRPC authors.

#ifndef GRPCPP_CHANNEL_H
#define GRPCPP_CHANNEL_H

#include <grpc/grpc.h>
#include <grpcpp/completion_queue.h>
#include <grpcpp/impl/call.h>
#include <grpcpp/impl/channel_interface.h>
#include <grpcpp/impl/grpc_library.h>
#include <grpcpp/impl/sync.h>
#include <grpcpp/support/client_interceptor.h>
#include <grpcpp/support/config.h>

#include <memory>

struct grpc_channel;

namespace grpc {
namespace testing {
class ChannelTestPeer;
}

std::shared_ptr<Channel> CreateChannelInternal(
    const std::string& host, grpc_channel* c_channel,
    std::vector<
        std::unique_ptr<experimental::ClientInterceptorFactoryInterface>>
        interceptor_creators);

namespace experimental {

void ChannelResetConnectionBackoff(Channel* channel);
}

class Channel final : public grpc::ChannelInterface,
                      public grpc::internal::CallHook,
                      public std::enable_shared_from_this<Channel>,
                      private grpc::internal::GrpcLibrary {
 public:
  ~Channel() override;

  grpc_connectivity_state GetState(bool try_to_connect) override;

  std::string GetLoadBalancingPolicyName() const;

  std::string GetServiceConfigJSON() const;

 private:
  template <class InputMessage, class OutputMessage>
  friend class grpc::internal::BlockingUnaryCallImpl;
  friend class grpc::testing::ChannelTestPeer;
  friend void experimental::ChannelResetConnectionBackoff(Channel* channel);
  friend std::shared_ptr<Channel> grpc::CreateChannelInternal(
      const std::string& host, grpc_channel* c_channel,
      std::vector<std::unique_ptr<
          grpc::experimental::ClientInterceptorFactoryInterface>>
          interceptor_creators);
  friend class grpc::internal::InterceptedChannel;
  Channel(const std::string& host, grpc_channel* c_channel,
          std::vector<std::unique_ptr<
              grpc::experimental::ClientInterceptorFactoryInterface>>
              interceptor_creators);

  grpc::internal::Call CreateCall(const grpc::internal::RpcMethod& method,
                                  grpc::ClientContext* context,
                                  grpc::CompletionQueue* cq) override;
  void PerformOpsOnCall(grpc::internal::CallOpSetInterface* ops,
                        grpc::internal::Call* call) override;
  void* RegisterMethod(const char* method) override;

  void NotifyOnStateChangeImpl(grpc_connectivity_state last_observed,
                               gpr_timespec deadline, grpc::CompletionQueue* cq,
                               void* tag) override;
  bool WaitForStateChangeImpl(grpc_connectivity_state last_observed,
                              gpr_timespec deadline) override;

  grpc::CompletionQueue* CallbackCQ() override;

  grpc::internal::Call CreateCallInternal(
      const grpc::internal::RpcMethod& method, grpc::ClientContext* context,
      grpc::CompletionQueue* cq, size_t interceptor_pos) override;

  const std::string host_;
  grpc_channel* const c_channel_;

  grpc::internal::Mutex mu_;

  std::atomic<CompletionQueue*> callback_cq_{nullptr};

  std::vector<
      std::unique_ptr<grpc::experimental::ClientInterceptorFactoryInterface>>
      interceptor_creators_;
};

}

#endif
