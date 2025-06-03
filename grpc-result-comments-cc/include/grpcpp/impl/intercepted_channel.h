Here's the commented version of the code:

```c++
// Copyright 2018 gRPC authors.

#ifndef GRPCPP_IMPL_INTERCEPTED_CHANNEL_H
#define GRPCPP_IMPL_INTERCEPTED_CHANNEL_H

#include <grpcpp/impl/channel_interface.h>

namespace grpc {
class CompletionQueue;

namespace internal {

class InterceptorBatchMethodsImpl;

// InterceptedChannel is a decorator class that wraps a ChannelInterface
// and provides interception capabilities for gRPC calls.
// It forwards most operations to the underlying channel while maintaining
// interceptor position information.
class InterceptedChannel : public ChannelInterface {
 public:
  // Destructor that clears the underlying channel pointer
  ~InterceptedChannel() override { channel_ = nullptr; }

  // Gets the connectivity state of the underlying channel
  // @param try_to_connect If true, will try to connect if not connected
  // @return Current connectivity state of the channel
  grpc_connectivity_state GetState(bool try_to_connect) override {
    return channel_->GetState(try_to_connect);
  }

 private:
  // Private constructor only accessible by friend classes
  // @param channel The underlying channel to intercept
  // @param pos The position of this interceptor in the interceptor chain
  InterceptedChannel(ChannelInterface* channel, size_t pos)
      : channel_(channel), interceptor_pos_(pos) {}

  // Creates a call on the underlying channel with interceptor handling
  // @param method The RPC method to call
  // @param context The client context for the call
  // @param cq The completion queue to use
  // @return A Call object representing the RPC
  Call CreateCall(const RpcMethod& method, grpc::ClientContext* context,
                  grpc::CompletionQueue* cq) override {
    return channel_->CreateCallInternal(method, context, cq, interceptor_pos_);
  }

  // Performs operations on a call through the underlying channel
  // @param ops The operations to perform
  // @param call The call to perform operations on
  void PerformOpsOnCall(CallOpSetInterface* ops, Call* call) override {
    return channel_->PerformOpsOnCall(ops, call);
  }

  // Registers a method with the underlying channel
  // @param method The method name to register
  // @return An opaque pointer representing the registered method
  void* RegisterMethod(const char* method) override {
    return channel_->RegisterMethod(method);
  }

  // Notifies when the channel's connectivity state changes
  // @param last_observed The last observed state
  // @param deadline The deadline for the notification
  // @param cq The completion queue to notify
  // @param tag The tag associated with the notification
  void NotifyOnStateChangeImpl(grpc_connectivity_state last_observed,
                               gpr_timespec deadline, grpc::CompletionQueue* cq,
                               void* tag) override {
    return channel_->NotifyOnStateChangeImpl(last_observed, deadline, cq, tag);
  }

  // Waits for a channel state change
  // @param last_observed The last observed state
  // @param deadline The deadline for the wait
  // @return true if state changed, false if deadline expired
  bool WaitForStateChangeImpl(grpc_connectivity_state last_observed,
                              gpr_timespec deadline) override {
    return channel_->WaitForStateChangeImpl(last_observed, deadline);
  }

  // Gets the callback completion queue from the underlying channel
  // @return Pointer to the callback completion queue
  grpc::CompletionQueue* CallbackCQ() override {
    return channel_->CallbackCQ();
  }

  ChannelInterface* channel_;      // The underlying channel being intercepted
  size_t interceptor_pos_;         // Position in the interceptor chain

  friend class InterceptorBatchMethodsImpl;  // Allow access to private constructor
};
}
}

#endif
```

The comments explain:
1. The overall purpose of the InterceptedChannel class
2. Each method's functionality and parameters
3. The private constructor's purpose and accessibility
4. The role of member variables
5. The friend class relationship
6. The forwarding nature of most method implementations

The comments are written in a clear, professional style that would help future maintainers understand the code's purpose and behavior without being overly verbose.