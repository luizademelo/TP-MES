
// Copyright 2015 gRPC authors.

#ifndef GRPCPP_IMPL_PROTO_UTILS_H
#define GRPCPP_IMPL_PROTO_UTILS_H

#include <grpc/byte_buffer_reader.h>
#include <grpc/impl/grpc_types.h>
#include <grpc/slice.h>
#include <grpcpp/impl/codegen/config_protobuf.h>
#include <grpcpp/impl/generic_serialize.h>
#include <grpcpp/impl/serialization_traits.h>
#include <grpcpp/support/byte_buffer.h>
#include <grpcpp/support/proto_buffer_reader.h>
#include <grpcpp/support/proto_buffer_writer.h>
#include <grpcpp/support/slice.h>
#include <grpcpp/support/status.h>

#include <type_traits>

namespace grpc {

template <class T>
class SerializationTraits<
    T, typename std::enable_if<
           std::is_base_of<grpc::protobuf::MessageLite, T>::value>::type> {
 public:
  static Status Serialize(const grpc::protobuf::MessageLite& msg,
                          ByteBuffer* bb, bool* own_buffer) {
    return GenericSerialize<ProtoBufferWriter, T>(msg, bb, own_buffer);
  }

  static Status Deserialize(ByteBuffer* buffer,
                            grpc::protobuf::MessageLite* msg) {
    return GenericDeserialize<ProtoBufferReader, T>(buffer, msg);
  }
};

}

#endif
