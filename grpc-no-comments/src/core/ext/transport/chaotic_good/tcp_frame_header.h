
// Copyright 2025 gRPC authors.

#ifndef GRPC_SRC_CORE_EXT_TRANSPORT_CHAOTIC_GOOD_TCP_FRAME_HEADER_H
#define GRPC_SRC_CORE_EXT_TRANSPORT_CHAOTIC_GOOD_TCP_FRAME_HEADER_H

#include "absl/strings/str_cat.h"
#include "src/core/ext/transport/chaotic_good/frame_header.h"

namespace grpc_core::chaotic_good {

inline uint32_t DataConnectionPadding(uint32_t payload_length,
                                      uint32_t alignment) {
  if (payload_length % alignment == 0) return 0;
  return alignment - (payload_length % alignment);
}

struct TcpFrameHeader {

  enum { kFrameHeaderSize = 16 };

  FrameHeader header;

  uint64_t payload_tag = 0;

  static absl::StatusOr<TcpFrameHeader> Parse(const uint8_t* data);

  void Serialize(uint8_t* data) const;

  std::string ToString() const;

  bool operator==(const TcpFrameHeader& h) const {
    return header == h.header && payload_tag == h.payload_tag;
  }

  uint32_t Padding(uint32_t alignment) const;
};

struct TcpDataFrameHeader {
  enum { kFrameHeaderSize = 20 };
  uint64_t payload_tag;
  uint64_t send_timestamp;
  uint32_t payload_length;

  static absl::StatusOr<TcpDataFrameHeader> Parse(const uint8_t* data);

  void Serialize(uint8_t* data) const;

  template <typename Sink>
  friend void AbslStringify(Sink& sink, const TcpDataFrameHeader& frame) {
    sink.Append(absl::StrCat("DataFrameHeader{payload_tag:", frame.payload_tag,
                             ",send_timestamp:", frame.send_timestamp,
                             ",payload_length:", frame.payload_length, "}"));
  }
};

}

#endif
