Here's the commented version of the code:

```c++
// Copyright 2025 gRPC authors.

#include "src/core/ext/transport/chaotic_good/tcp_frame_header.h"
#include "src/core/ext/transport/chaotic_good/serialize_little_endian.h"

namespace grpc_core::chaotic_good {

// Serializes the TcpFrameHeader into a byte array in little-endian format.
// The header consists of:
// - Frame type (8 bits) combined with payload tag (56 bits) into 64 bits
// - Stream ID (32 bits)
// - Payload length (32 bits)
void TcpFrameHeader::Serialize(uint8_t* data) const {
  // Verify that payload_tag doesn't exceed 56 bits
  DCHECK_EQ(payload_tag >> 56, 0u) << payload_tag;
  // Combine frame type (lower 8 bits) and payload tag (upper 56 bits)
  WriteLittleEndianUint64(
      static_cast<uint64_t>(header.type) | (payload_tag << 8), data);
  // Write stream ID at offset 8
  WriteLittleEndianUint32(header.stream_id, data + 8);
  // Write payload length at offset 12
  WriteLittleEndianUint32(header.payload_length, data + 12);
}

// Parses a byte array into a TcpFrameHeader object.
// Returns the parsed header or an error status if parsing fails.
absl::StatusOr<TcpFrameHeader> TcpFrameHeader::Parse(const uint8_t* data) {
  TcpFrameHeader tcp_header;
  // Read combined type and payload tag (64 bits)
  const uint64_t type_and_tag = ReadLittleEndianUint64(data);
  // Extract frame type from lower 8 bits
  tcp_header.header.type = static_cast<FrameType>(type_and_tag & 0xff);
  // Extract payload tag from upper 56 bits
  tcp_header.payload_tag = type_and_tag >> 8;
  // Read stream ID from offset 8
  tcp_header.header.stream_id = ReadLittleEndianUint32(data + 8);
  // Read payload length from offset 12
  tcp_header.header.payload_length = ReadLittleEndianUint32(data + 12);
  return tcp_header;
}

// Calculates required padding for alignment of the frame.
// Returns 0 if payload_tag is 0 (no padding needed).
// Otherwise calculates padding needed after header and payload.
uint32_t TcpFrameHeader::Padding(uint32_t alignment) const {
  if (payload_tag == 0) return 0;
  return DataConnectionPadding(kFrameHeaderSize + header.payload_length,
                               alignment);
}

// Returns a string representation of the frame header in format:
// "header.ToString()@payload_tag"
std::string TcpFrameHeader::ToString() const {
  return absl::StrCat(header.ToString(), "@", payload_tag);
}

// Serializes the TcpDataFrameHeader into a byte array in little-endian format.
// The header consists of:
// - Payload tag (64 bits)
// - Send timestamp (64 bits)
// - Payload length (32 bits)
void TcpDataFrameHeader::Serialize(uint8_t* data) const {
  WriteLittleEndianUint64(payload_tag, data);  // Write payload tag at offset 0
  WriteLittleEndianUint64(send_timestamp, data + 8);  // Write timestamp at offset 8
  WriteLittleEndianUint32(payload_length, data + 16);  // Write length at offset 16
}

// Parses a byte array into a TcpDataFrameHeader object.
// Returns the parsed header or an error status if parsing fails.
absl::StatusOr<TcpDataFrameHeader> TcpDataFrameHeader::Parse(
    const uint8_t* data) {
  TcpDataFrameHeader header;
  header.payload_tag = ReadLittleEndianUint64(data);  // Read payload tag from offset 0
  header.send_timestamp = ReadLittleEndianUint64(data + 8);  // Read timestamp from offset 8
  header.payload_length = ReadLittleEndianUint32(data + 16);  // Read length from offset 16
  return header;
}

}  // namespace grpc_core::chaotic_good
```