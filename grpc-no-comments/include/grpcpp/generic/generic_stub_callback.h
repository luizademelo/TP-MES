
// Copyright 2024 gRPC authors.

#ifndef GRPCPP_GENERIC_GENERIC_STUB_CALLBACK_H
#define GRPCPP_GENERIC_GENERIC_STUB_CALLBACK_H

#include <grpcpp/impl/generic_stub_internal.h>
#include <grpcpp/support/byte_buffer.h>

namespace grpc {

template <class RequestType, class ResponseType>
class TemplatedGenericStubCallback final
    : public internal::TemplatedGenericStubCallbackInternal<RequestType,
                                                            ResponseType> {
 public:
  using internal::TemplatedGenericStubCallbackInternal<
      RequestType, ResponseType>::TemplatedGenericStubCallbackInternal;
};

typedef TemplatedGenericStubCallback<grpc::ByteBuffer, grpc::ByteBuffer>
    GenericStubCallback;

}

#endif
