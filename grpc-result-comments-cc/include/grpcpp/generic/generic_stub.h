Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

// Header guard to prevent multiple inclusions
#ifndef GRPCPP_GENERIC_GENERIC_STUB_H
#define GRPCPP_GENERIC_GENERIC_STUB_H

// Include necessary headers
#include <grpcpp/client_context.h>
#include <grpcpp/impl/generic_stub_internal.h>
#include <grpcpp/impl/rpc_method.h>
#include <grpcpp/support/async_stream.h>
#include <grpcpp/support/async_unary_call.h>
#include <grpcpp/support/byte_buffer.h>
#include <grpcpp/support/stub_options.h>

namespace grpc {

// Forward declaration
class CompletionQueue;

// Type aliases for generic async reader/writer and response reader
typedef ClientAsyncReaderWriter<ByteBuffer, ByteBuffer>
    GenericClientAsyncReaderWriter;
typedef ClientAsyncResponseReader<ByteBuffer> GenericClientAsyncResponseReader;

// Template class for generic stub supporting both request and response types
template <class RequestType, class ResponseType>
class TemplatedGenericStub final
    : public internal::TemplatedGenericStubCallbackInternal<RequestType,
                                                            ResponseType> {
 public:
  // Inherit constructor from base class
  using internal::TemplatedGenericStubCallbackInternal<
      RequestType, ResponseType>::TemplatedGenericStubCallbackInternal;

  // Prepares a bidirectional streaming call
  // context: Client context for the call
  // method: Name of the method to call
  // cq: Completion queue to use for async operations
  // Returns: Unique pointer to async reader/writer
  std::unique_ptr<ClientAsyncReaderWriter<RequestType, ResponseType>>
  PrepareCall(ClientContext* context, const std::string& method,
              grpc::CompletionQueue* cq) {
    return CallInternal(channel_.get(), context, method, {}, cq,
                        false, nullptr);
  }

  // Prepares a unary call
  // context: Client context for the call
  // method: Name of the method to call
  // request: Request message to send
  // cq: Completion queue to use for async operations
  // Returns: Unique pointer to async response reader
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

  // Inherit PrepareUnaryCall from base class
  using internal::TemplatedGenericStubCallbackInternal<
      RequestType, ResponseType>::PrepareUnaryCall;

  // Initiates a bidirectional streaming call
  // context: Client context for the call
  // method: Name of the method to call
  // cq: Completion queue to use for async operations
  // tag: Tag to associate with the operation
  // Returns: Unique pointer to async reader/writer
  std::unique_ptr<ClientAsyncReaderWriter<RequestType, ResponseType>> Call(
      ClientContext* context, const std::string& method,
      grpc::CompletionQueue* cq, void* tag) {
    return CallInternal(channel_.get(), context, method, {}, cq,
                        true, tag);
  }

 private:
  // Inherit channel_ member from base class
  using internal::TemplatedGenericStubCallbackInternal<RequestType,
                                                       ResponseType>::channel_;

  // Internal method to create async reader/writer
  // channel: gRPC channel to use
  // context: Client context for the call
  // method: Name of the method to call
  // options: Stub options
  // cq: Completion queue to use for async operations
  // start: Whether to start the call immediately
  // tag: Tag to associate with the operation
  // Returns: Unique pointer to async reader/writer
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

// Type alias for byte buffer based generic stub
typedef TemplatedGenericStub<grpc::ByteBuffer, grpc::ByteBuffer> GenericStub;

}  // namespace grpc

#endif  // GRPCPP_GENERIC_GENERIC_STUB_H
```

The comments explain:
1. The purpose of each section and component
2. The parameters for each method
3. The return values
4. The inheritance relationships
5. The template parameters
6. The internal implementation details
7. The type aliases used

The comments are designed to help future developers understand:
- How to use the class and its methods
- What each method does
- The flow of data through the class
- The relationship between different components
- The purpose of template parameters