
// Copyright 2016 gRPC authors.

#include "test/cpp/util/byte_buffer_proto_helper.h"

#include "absl/memory/memory.h"

namespace grpc {
namespace testing {

bool ParseFromByteBuffer(ByteBuffer* buffer, grpc::protobuf::Message* message) {
  std::vector<Slice> slices;
  (void)buffer->Dump(&slices);
  std::string buf;
  buf.reserve(buffer->Length());
  for (auto s = slices.begin(); s != slices.end(); s++) {
    buf.append(reinterpret_cast<const char*>(s->begin()), s->size());
  }
  return message->ParseFromString(buf);
}

std::unique_ptr<ByteBuffer> SerializeToByteBuffer(
    grpc::protobuf::Message* message) {
  std::string buf;
  message->SerializeToString(&buf);
  Slice slice(buf);
  return std::make_unique<ByteBuffer>(&slice, 1);
}

bool SerializeToByteBufferInPlace(grpc::protobuf::Message* message,
                                  ByteBuffer* buffer) {
  std::string buf;
  if (!message->SerializeToString(&buf)) {
    return false;
  }
  buffer->Clear();
  Slice slice(buf);
  ByteBuffer tmp(&slice, 1);
  buffer->Swap(&tmp);
  return true;
}

}
}
