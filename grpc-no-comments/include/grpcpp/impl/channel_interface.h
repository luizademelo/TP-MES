
// Copyright 2016 gRPC authors.

#ifndef GRPCPP_IMPL_CHANNEL_INTERFACE_H
#define GRPCPP_IMPL_CHANNEL_INTERFACE_H

#include <grpc/impl/connectivity_state.h>
#include <grpcpp/impl/call.h>
#include <grpcpp/support/status.h>
#include <grpcpp/support/time.h>

namespace grpc {
template <class R>
class ClientReader;
template <class W>
class ClientWriter;
template <class W, class R>
class ClientReaderWriter;
namespace internal {
template <class InputMessage, class OutputMessage>
class CallbackUnaryCallImpl;
template <class R>
class ClientAsyncReaderFactory;
template <class W>
class ClientAsyncWriterFactory;
template <class W, class R>
class ClientAsyncReaderWriterFactory;
class ClientAsyncResponseReaderHelper;
template <class W, class R>
class ClientCallbackReaderWriterFactory;
template <class R>
class ClientCallbackReaderFactory;
template <class W>
class ClientCallbackWriterFactory;
class ClientCallbackUnaryFactory;
}

class ChannelInterface;
class ClientContext;
class CompletionQueue;

namespace experimental {
class DelegatingChannel;
}

namespace internal {
class Call;
class CallOpSetInterface;
class RpcMethod;
class InterceptedChannel;
template <class InputMessage, class OutputMessage>
class BlockingUnaryCallImpl;
}

class ChannelInterface {
 public:
  virtual ~ChannelInterface() {}

  virtual grpc_connectivity_state GetState(bool try_to_connect) = 0;

  template <typename T>
  void NotifyOnStateChange(grpc_connectivity_state last_observed, T deadline,
                           grpc::CompletionQueue* cq, void* tag) {
    TimePoint<T> deadline_tp(deadline);
    NotifyOnStateChangeImpl(last_observed, deadline_tp.raw_time(), cq, tag);
  }

  template <typename T>
  bool WaitForStateChange(grpc_connectivity_state last_observed, T deadline) {
    TimePoint<T> deadline_tp(deadline);
    return WaitForStateChangeImpl(last_observed, deadline_tp.raw_time());
  }

  template <typename T>
  bool WaitForConnected(T deadline) {
    grpc_connectivity_state state;
    while ((state = GetState(true)) != GRPC_CHANNEL_READY) {
      if (!WaitForStateChange(state, deadline)) return false;
    }
    return true;
  }

 private:
  template <class R>
  friend class grpc::ClientReader;
  template <class W>
  friend class grpc::ClientWriter;
  template <class W, class R>
  friend class grpc::ClientReaderWriter;
  template <class R>
  friend class grpc::internal::ClientAsyncReaderFactory;
  template <class W>
  friend class grpc::internal::ClientAsyncWriterFactory;
  template <class W, class R>
  friend class grpc::internal::ClientAsyncReaderWriterFactory;
  friend class grpc::internal::ClientAsyncResponseReaderHelper;
  template <class W, class R>
  friend class grpc::internal::ClientCallbackReaderWriterFactory;
  template <class R>
  friend class grpc::internal::ClientCallbackReaderFactory;
  template <class W>
  friend class grpc::internal::ClientCallbackWriterFactory;
  friend class grpc::internal::ClientCallbackUnaryFactory;
  template <class InputMessage, class OutputMessage>
  friend class grpc::internal::BlockingUnaryCallImpl;
  template <class InputMessage, class OutputMessage>
  friend class grpc::internal::CallbackUnaryCallImpl;
  friend class grpc::internal::RpcMethod;
  friend class grpc::experimental::DelegatingChannel;
  friend class grpc::internal::InterceptedChannel;
  virtual internal::Call CreateCall(const internal::RpcMethod& method,
                                    grpc::ClientContext* context,
                                    grpc::CompletionQueue* cq) = 0;
  virtual void PerformOpsOnCall(internal::CallOpSetInterface* ops,
                                internal::Call* call) = 0;
  virtual void* RegisterMethod(const char* method) = 0;
  virtual void NotifyOnStateChangeImpl(grpc_connectivity_state last_observed,
                                       gpr_timespec deadline,
                                       grpc::CompletionQueue* cq,
                                       void* tag) = 0;
  virtual bool WaitForStateChangeImpl(grpc_connectivity_state last_observed,
                                      gpr_timespec deadline) = 0;

  virtual internal::Call CreateCallInternal(
      const internal::RpcMethod& , grpc::ClientContext* ,
      grpc::CompletionQueue* , size_t ) {
    return internal::Call();
  }

  virtual grpc::CompletionQueue* CallbackCQ() { return nullptr; }
};
}

#endif
