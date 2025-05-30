
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

template <class RequestType, class ResponseType>
class TemplatedGenericStub;
template <class RequestType, class ResponseType>
class TemplatedGenericStubCallback;

namespace internal {

template <class RequestType, class ResponseType>
class TemplatedGenericStubCallbackInternal {
 public:
  explicit TemplatedGenericStubCallbackInternal(
      std::shared_ptr<grpc::ChannelInterface> channel)
      : channel_(channel) {}

  void UnaryCall(ClientContext* context, const std::string& method,
                 StubOptions options, const RequestType* request,
                 ResponseType* response,
                 std::function<void(grpc::Status)> on_completion) {
    UnaryCallInternal(context, method, options, request, response,
                      std::move(on_completion));
  }

  void PrepareUnaryCall(ClientContext* context, const std::string& method,
                        StubOptions options, const RequestType* request,
                        ResponseType* response, ClientUnaryReactor* reactor) {
    PrepareUnaryCallInternal(context, method, options, request, response,
                             reactor);
  }

  void PrepareBidiStreamingCall(
      ClientContext* context, const std::string& method, StubOptions options,
      ClientBidiReactor<RequestType, ResponseType>* reactor) {
    PrepareBidiStreamingCallInternal(context, method, options, reactor);
  }

 private:
  template <class Req, class Resp>
  friend class grpc::TemplatedGenericStub;
  template <class Req, class Resp>
  friend class grpc::TemplatedGenericStubCallback;
  std::shared_ptr<grpc::ChannelInterface> channel_;

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

}
}

#endif
