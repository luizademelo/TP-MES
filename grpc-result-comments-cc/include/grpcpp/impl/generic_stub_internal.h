Here's the commented version of the code:

```c++
// Copyright 2024 gRPC authors.

#ifndef GRPCPP_IMPL_GENERIC_STUB_INTERNAL_H
#define GRPCPP_IMPL_GENERIC_STUB_INTERNAL_H

#include <grpcpp/client_context.h>
#include <grpcpp/impl/rpc_method.h>
#include <grpcpp/support/byte_buffer.h>
#include <grpcpp/support/client_callback.h>
#include <grpcpp/support/status.h>
#include <grpcpp/support/stub_options.h>

#include <functional>

namespace grpc {

// Forward declarations of templated classes for generic stubs
template <class RequestType, class ResponseType>
class TemplatedGenericStub;
template <class RequestType, class ResponseType>
class TemplatedGenericStubCallback;

namespace internal {

// Internal implementation class for templated generic stub callbacks
// Provides functionality for making various types of RPC calls
template <class RequestType, class ResponseType>
class TemplatedGenericStubCallbackInternal {
 public:
  // Constructor that takes a shared pointer to a channel interface
  explicit TemplatedGenericStubCallbackInternal(
      std::shared_ptr<grpc::ChannelInterface> channel)
      : channel_(channel) {}

  // Makes a unary RPC call with completion callback
  // context: Client context for the call
  // method: Name of the method to call
  // options: Stub options including stats suffix
  // request: Pointer to request message
  // response: Pointer to response message
  // on_completion: Callback to be invoked when call completes
  void UnaryCall(ClientContext* context, const std::string& method,
                 StubOptions options, const RequestType* request,
                 ResponseType* response,
                 std::function<void(grpc::Status)> on_completion) {
    UnaryCallInternal(context, method, options, request, response,
                      std::move(on_completion));
  }

  // Prepares a unary RPC call with reactor pattern
  // reactor: ClientUnaryReactor that will handle call events
  void PrepareUnaryCall(ClientContext* context, const std::string& method,
                        StubOptions options, const RequestType* request,
                        ResponseType* response, ClientUnaryReactor* reactor) {
    PrepareUnaryCallInternal(context, method, options, request, response,
                             reactor);
  }

  // Prepares a bidirectional streaming RPC call
  // reactor: ClientBidiReactor that will handle stream events
  void PrepareBidiStreamingCall(
      ClientContext* context, const std::string& method, StubOptions options,
      ClientBidiReactor<RequestType, ResponseType>* reactor) {
    PrepareBidiStreamingCallInternal(context, method, options, reactor);
  }

 private:
  // Grant access to related template classes
  template <class Req, class Resp>
  friend class grpc::TemplatedGenericStub;
  template <class Req, class Resp>
  friend class grpc::TemplatedGenericStubCallback;
  
  // Shared pointer to the channel interface
  std::shared_ptr<grpc::ChannelInterface> channel_;

  // Internal implementation of unary call with completion callback
  void UnaryCallInternal(ClientContext* context, const std::string& method,
                         StubOptions options, const RequestType* request,
                         ResponseType* response,
                         std::function<void(grpc::Status)> on_completion) {
    internal::CallbackUnaryCall(
        channel_.get(),
        grpc::internal::RpcMethod(method.c_str(), options.suffix_for_stats(),
                                  grpc::internal::RpcMethod::NORMAL_RPC),
        context, request, response, std::move(on_completion));
  }

  // Internal implementation of unary call preparation with reactor
  void PrepareUnaryCallInternal(ClientContext* context,
                                const std::string& method, StubOptions options,
                                const RequestType* request,
                                ResponseType* response,
                                ClientUnaryReactor* reactor) {
    internal::ClientCallbackUnaryFactory::Create<RequestType, ResponseType>(
        channel_.get(),
        grpc::internal::RpcMethod(method.c_str(), options.suffix_for_stats(),
                                  grpc::internal::RpcMethod::NORMAL_RPC),
        context, request, response, reactor);
  }

  // Internal implementation of bidirectional streaming call preparation
  void PrepareBidiStreamingCallInternal(
      ClientContext* context, const std::string& method, StubOptions options,
      ClientBidiReactor<RequestType, ResponseType>* reactor) {
    internal::ClientCallbackReaderWriterFactory<RequestType, ResponseType>::
        Create(channel_.get(),
               grpc::internal::RpcMethod(
                   method.c_str(), options.suffix_for_stats(),
                   grpc::internal::RpcMethod::BIDI_STREAMING),
               context, reactor);
  }
};

}  // namespace internal
}  // namespace grpc

#endif  // GRPCPP_IMPL_GENERIC_STUB_INTERNAL_H
```