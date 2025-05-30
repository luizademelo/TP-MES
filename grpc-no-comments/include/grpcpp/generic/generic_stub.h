
// Copyright 2015 gRPC authors.

#ifndef GRPCPP_GENERIC_GENERIC_STUB_H
#define GRPCPP_GENERIC_GENERIC_STUB_H

#include <grpcpp/client_context.h>
#include <grpcpp/impl/generic_stub_internal.h>
#include <grpcpp/impl/rpc_method.h>
#include <grpcpp/support/async_stream.h>
#include <grpcpp/support/async_unary_call.h>
#include <grpcpp/support/byte_buffer.h>
#include <grpcpp/support/stub_options.h>

namespace grpc {

class CompletionQueue;

typedef ClientAsyncReaderWriter<ByteBuffer, ByteBuffer>
    GenericClientAsyncReaderWriter;
typedef ClientAsyncResponseReader<ByteBuffer> GenericClientAsyncResponseReader;

template <class RequestType, class ResponseType>
class TemplatedGenericStub final
    : public internal::TemplatedGenericStubCallbackInternal<RequestType,
                                                            ResponseType> {
 public:
  using internal::TemplatedGenericStubCallbackInternal<
      RequestType, ResponseType>::TemplatedGenericStubCallbackInternal;

  std::unique_ptr<ClientAsyncReaderWriter<RequestType, ResponseType>>
  PrepareCall(ClientContext* context, const std::string& method,
              grpc::CompletionQueue* cq) {
    return CallInternal(channel_.get(), context, method, {}, cq,
                        false, nullptr);
  }

  std::unique_ptr<ClientAsyncResponseReader<ResponseType>> PrepareUnaryCall(
      ClientContext* context, const std::string& method,
      const RequestType& request, grpc::CompletionQueue* cq) {
    return std::unique_ptr<ClientAsyncResponseReader<ResponseType>>(
        internal::ClientAsyncResponseReaderHelper::Create<ResponseType>(
            channel_.get(), cq,
            grpc::internal::RpcMethod(method.c_str(),
                                      nullptr,
                                      grpc::internal::RpcMethod::NORMAL_RPC),
            context, request));
  }

  using internal::TemplatedGenericStubCallbackInternal<
      RequestType, ResponseType>::PrepareUnaryCall;

  std::unique_ptr<ClientAsyncReaderWriter<RequestType, ResponseType>> Call(
      ClientContext* context, const std::string& method,
      grpc::CompletionQueue* cq, void* tag) {
    return CallInternal(channel_.get(), context, method, {}, cq,
                        true, tag);
  }

 private:
  using internal::TemplatedGenericStubCallbackInternal<RequestType,
                                                       ResponseType>::channel_;

  std::unique_ptr<ClientAsyncReaderWriter<RequestType, ResponseType>>
  CallInternal(grpc::ChannelInterface* channel, ClientContext* context,
               const std::string& method, StubOptions options,
               grpc::CompletionQueue* cq, bool start, void* tag) {
    return std::unique_ptr<ClientAsyncReaderWriter<RequestType, ResponseType>>(
        internal::ClientAsyncReaderWriterFactory<RequestType, ResponseType>::
            Create(channel, cq,
                   grpc::internal::RpcMethod(
                       method.c_str(), options.suffix_for_stats(),
                       grpc::internal::RpcMethod::BIDI_STREAMING),
                   context, start, tag));
  }
};

typedef TemplatedGenericStub<grpc::ByteBuffer, grpc::ByteBuffer> GenericStub;

}

#endif
