
// Copyright 2016 gRPC authors.

#ifndef GRPC_TEST_CPP_UTIL_BYTE_BUFFER_PROTO_HELPER_H
#define GRPC_TEST_CPP_UTIL_BYTE_BUFFER_PROTO_HELPER_H

#include <grpcpp/impl/codegen/config_protobuf.h>
#include <grpcpp/support/byte_buffer.h>

#include <memory>

namespace grpc {
namespace testing {

bool ParseFromByteBuffer(ByteBuffer* buffer, grpc::protobuf::Message* message);

std::unique_ptr<ByteBuffer> SerializeToByteBuffer(
    grpc::protobuf::Message* message);

bool SerializeToByteBufferInPlace(grpc::protobuf::Message* message,
                                  ByteBuffer* buffer);

}
}

#endif
