
// Copyright 2018 gRPC authors.

#ifndef GRPCPP_IMPL_CALL_OP_SET_INTERFACE_H
#define GRPCPP_IMPL_CALL_OP_SET_INTERFACE_H

#include <grpcpp/impl/completion_queue_tag.h>

namespace grpc {
namespace internal {

class Call;

class CallOpSetInterface : public CompletionQueueTag {
 public:

  virtual void FillOps(internal::Call* call) = 0;

  virtual void* core_cq_tag() = 0;

  virtual void SetHijackingState() = 0;

  virtual void ContinueFillOpsAfterInterception() = 0;

  virtual void ContinueFinalizeResultAfterInterception() = 0;
};
}
}

#endif
