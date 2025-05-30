
// Copyright 2015 gRPC authors.

#ifndef GRPCPP_IMPL_COMPLETION_QUEUE_TAG_H
#define GRPCPP_IMPL_COMPLETION_QUEUE_TAG_H

namespace grpc {

namespace internal {

class CompletionQueueTag {
 public:
  virtual ~CompletionQueueTag() {}

  virtual bool FinalizeResult(void** tag, bool* status) = 0;
};
}

}

#endif
