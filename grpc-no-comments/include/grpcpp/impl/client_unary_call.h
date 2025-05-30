
// Copyright 2015 gRPC authors.

#ifndef GRPCPP_IMPL_CLIENT_UNARY_CALL_H
#define GRPCPP_IMPL_CLIENT_UNARY_CALL_H

#include <grpcpp/impl/call.h>
#include <grpcpp/impl/call_op_set.h>
#include <grpcpp/impl/channel_interface.h>
#include <grpcpp/support/config.h>
#include <grpcpp/support/status.h>

namespace grpc {

class ClientContext;
namespace internal {
class RpcMethod;

template <class InputMessage, class OutputMessage,
          class BaseInputMessage = InputMessage,
          class BaseOutputMessage = OutputMessage>
Status BlockingUnaryCall(ChannelInterface* channel, const RpcMethod& method,
                         grpc::ClientContext* context,
                         const InputMessage& request, OutputMessage* result) {
  static_assert(std::is_base_of<BaseInputMessage, InputMessage>::value,
                "Invalid input message specification");
  static_assert(std::is_base_of<BaseOutputMessage, OutputMessage>::value,
                "Invalid output message specification");
  return BlockingUnaryCallImpl<BaseInputMessage, BaseOutputMessage>(
             channel, method, context, request, result)
      .status();
}

template <class InputMessage, class OutputMessage>
class BlockingUnaryCallImpl {
 public:
  BlockingUnaryCallImpl(ChannelInterface* channel, const RpcMethod& method,
                        grpc::ClientContext* context,
                        const InputMessage& request, OutputMessage* result) {
    grpc::CompletionQueue cq(grpc_completion_queue_attributes{
        GRPC_CQ_CURRENT_VERSION, GRPC_CQ_PLUCK, GRPC_CQ_DEFAULT_POLLING,
        nullptr});
    grpc::internal::Call call(channel->CreateCall(method, context, &cq));
    CallOpSet<CallOpSendInitialMetadata, CallOpSendMessage,
              CallOpRecvInitialMetadata, CallOpRecvMessage<OutputMessage>,
              CallOpClientSendClose, CallOpClientRecvStatus>
        ops;
    status_ = ops.SendMessagePtr(&request);
    if (!status_.ok()) {
      return;
    }
    ops.SendInitialMetadata(&context->send_initial_metadata_,
                            context->initial_metadata_flags());
    ops.RecvInitialMetadata(context);
    ops.RecvMessage(result);
    ops.AllowNoMessage();
    ops.ClientSendClose();
    ops.ClientRecvStatus(context, &status_);
    call.PerformOps(&ops);
    cq.Pluck(&ops);

    if (!ops.got_message && status_.ok()) {
      status_ = Status(StatusCode::UNIMPLEMENTED,
                       "No message returned for unary request");
    }
  }
  Status status() { return status_; }

 private:
  Status status_;
};

}
}

#endif
