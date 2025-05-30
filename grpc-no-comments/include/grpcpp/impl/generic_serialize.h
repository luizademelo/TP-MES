// Copyright 2024 gRPC authors.

#ifndef GRPCPP_IMPL_GENERIC_SERIALIZE_H
#define GRPCPP_IMPL_GENERIC_SERIALIZE_H

#include <grpc/byte_buffer_reader.h>
#include <grpc/impl/grpc_types.h>
#include <grpc/slice.h>
#include <grpcpp/impl/codegen/config_protobuf.h>
#include <grpcpp/impl/serialization_traits.h>
#include <grpcpp/support/byte_buffer.h>
#include <grpcpp/support/proto_buffer_reader.h>
#include <grpcpp/support/proto_buffer_writer.h>
#include <grpcpp/support/slice.h>
#include <grpcpp/support/status.h>

#include <type_traits>

#include "absl/log/absl_check.h"

namespace grpc {

template <class ProtoBufferWriter, class T>
Status GenericSerialize(const grpc::protobuf::MessageLite& msg, ByteBuffer* bb,
                        bool* own_buffer) {
  static_assert(std::is_base_of<protobuf::io::ZeroCopyOutputStream,
                                ProtoBufferWriter>::value,
                "ProtoBufferWriter must be a subclass of "
                "::protobuf::io::ZeroCopyOutputStream");
  *own_buffer = true;
  int byte_size = static_cast<int>(msg.ByteSizeLong());
  if (static_cast<size_t>(byte_size) <= GRPC_SLICE_INLINED_SIZE) {
    Slice slice(byte_size);

    ABSL_CHECK(slice.end() == msg.SerializeWithCachedSizesToArray(
                                  const_cast<uint8_t*>(slice.begin())));
    ByteBuffer tmp(&slice, 1);
    bb->Swap(&tmp);

    return grpc::Status::OK;
  }
  ProtoBufferWriter writer(bb, kProtoBufferWriterMaxBufferLength, byte_size);
  protobuf::io::CodedOutputStream cs(&writer);
  msg.SerializeWithCachedSizes(&cs);
  return !cs.HadError()
             ? grpc::Status::OK
             : Status(StatusCode::INTERNAL, "Failed to serialize message");
}

template <class ProtoBufferReader, class T>
Status GenericDeserialize(ByteBuffer* buffer,
                          grpc::protobuf::MessageLite* msg) {
  static_assert(std::is_base_of<protobuf::io::ZeroCopyInputStream,
                                ProtoBufferReader>::value,
                "ProtoBufferReader must be a subclass of "
                "::protobuf::io::ZeroCopyInputStream");
  if (buffer == nullptr) {
    return Status(StatusCode::INTERNAL, "No payload");
  }
  Status result = grpc::Status::OK;
  {
    ProtoBufferReader reader(buffer);
    if (!reader.status().ok()) {
      return reader.status();
    }
    if (!msg->ParseFromZeroCopyStream(&reader)) {
      result = Status(StatusCode::INTERNAL, msg->InitializationErrorString());
    }
  }
  buffer->Clear();
  return result;
}

}

#endif
