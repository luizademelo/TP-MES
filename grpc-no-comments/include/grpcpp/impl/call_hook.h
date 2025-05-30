
// Copyright 2015 gRPC authors.

#ifndef GRPCPP_IMPL_CALL_HOOK_H
#define GRPCPP_IMPL_CALL_HOOK_H

namespace grpc {

namespace internal {
class CallOpSetInterface;
class Call;

class CallHook {
 public:
  virtual ~CallHook() {}
  virtual void PerformOpsOnCall(CallOpSetInterface* ops, Call* call) = 0;
};
}

}

#endif
