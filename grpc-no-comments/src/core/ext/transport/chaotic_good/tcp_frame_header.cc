// Copyright 2025 gRPC authors.

#include "src/core/ext/transport/chaotic_good/tcp_frame_header.h"

#include "src/core/ext/transport/chaotic_good/serialize_little_endian.h"

namespace grpc_core::chaotic_good {

void TcpFrameHeader::Serialize(uint8_t* data) const {
  DCHECK_EQ(payload_tag >> 56, 0u) << payload_tag;
  WriteLittleEndianUint64(
      static_cast<uint64_t>(header.type) | (payload_tag << 8), data);
  WriteLittleEndianUint32(header.stream_id, data + 8);
  WriteLittleEndianUint32(header.payload_length, data + 12);
}

absl::StatusOr<TcpFrameHeader> TcpFrameHeader::Parse(const uint8_t* data) {
  TcpFrameHeader tcp_header;
  const uint64_t type_and_tag = ReadLittleEndianUint64(data);
  tcp_header.header.type = static_cast<FrameType>(type_and_tag & 0xff);
  tcp_header.payload_tag = type_and_tag >> 8;
  tcp_header.header.stream_id = ReadLittleEndianUint32(data + 8);
  tcp_header.header.payload_length = ReadLittleEndianUint32(data + 12);
  return tcp_header;
}

uint32_t TcpFrameHeader::Padding(uint32_t alignment) const {
  if (payload_tag == 0) return 0;
  return DataConnectionPadding(kFrameHeaderSize + header.payload_length,
                               alignment);
}

std::string TcpFrameHeader::ToString() const {
  return absl::StrCat(header.ToString(), "@", payload_tag);
}

void TcpDataFrameHeader::Serialize(uint8_t* data) const {
  WriteLittleEndianUint64(payload_tag, data);
  WriteLittleEndianUint64(send_timestamp, data + 8);
  WriteLittleEndianUint32(payload_length, data + 16);
}

absl::StatusOr<TcpDataFrameHeader> TcpDataFrameHeader::Parse(
    const uint8_t* data) {
  TcpDataFrameHeader header;
  header.payload_tag = ReadLittleEndianUint64(data);
  header.send_timestamp = ReadLittleEndianUint64(data + 8);
  header.payload_length = ReadLittleEndianUint32(data + 16);
  return header;
}

}