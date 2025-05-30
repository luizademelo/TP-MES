// Copyright 2023 gRPC authors.

#include "test/core/transport/chaotic_good_legacy/transport_test.h"

namespace grpc_core {
namespace chaotic_good_legacy {
namespace testing {

grpc_event_engine::experimental::Slice SerializedFrameHeader(
    FrameType type, uint16_t payload_connection_id, uint32_t stream_id,
    uint32_t payload_length) {
  uint8_t buffer[FrameHeader::kFrameHeaderSize] = {
      static_cast<uint8_t>(payload_connection_id),
      static_cast<uint8_t>(payload_connection_id >> 16),
      static_cast<uint8_t>(type),
      0,
      static_cast<uint8_t>(stream_id),
      static_cast<uint8_t>(stream_id >> 8),
      static_cast<uint8_t>(stream_id >> 16),
      static_cast<uint8_t>(stream_id >> 24),
      static_cast<uint8_t>(payload_length),
      static_cast<uint8_t>(payload_length >> 8),
      static_cast<uint8_t>(payload_length >> 16),
      static_cast<uint8_t>(payload_length >> 24),
  };
  return grpc_event_engine::experimental::Slice::FromCopiedBuffer(
      buffer, sizeof(buffer));
}

grpc_event_engine::experimental::Slice Zeros(uint32_t length) {
  std::string zeros(length, 0);
  return grpc_event_engine::experimental::Slice::FromCopiedBuffer(zeros.data(),
                                                                  length);
}

}
}
}
