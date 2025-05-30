// Copyright 2022 gRPC authors.

#ifndef GRPC_SRC_CORE_EXT_TRANSPORT_CHAOTIC_GOOD_FRAME_HEADER_H
#define GRPC_SRC_CORE_EXT_TRANSPORT_CHAOTIC_GOOD_FRAME_HEADER_H

#include <grpc/support/port_platform.h>
#include <stddef.h>

#include <cstdint>

#include "absl/status/statusor.h"
#include "src/core/util/bitset.h"

namespace grpc_core {
namespace chaotic_good {

enum class FrameType : uint8_t {
  kSettings = 0x00,
  kTcpSecurityFrame = 0x01,
  kClientInitialMetadata = 0x80,
  kClientEndOfStream = 0x81,
  kServerInitialMetadata = 0x91,
  kServerTrailingMetadata = 0x92,
  kMessage = 0xa0,
  kBeginMessage = 0xa1,
  kMessageChunk = 0xa2,
  kCancel = 0xff,
};

std::string FrameTypeString(FrameType type);

inline std::ostream& operator<<(std::ostream& out, FrameType type) {
  return out << FrameTypeString(type);
}

template <typename Sink>
void AbslStringify(Sink& sink, FrameType type) {
  sink.Append(FrameTypeString(type));
}

struct FrameHeader {
  FrameType type = FrameType::kCancel;
  uint32_t stream_id = 0;
  uint32_t payload_length = 0;

  std::string ToString() const;

  bool operator==(const FrameHeader& h) const {
    return type == h.type && stream_id == h.stream_id &&
           payload_length == h.payload_length;
  }
};

inline std::ostream& operator<<(std::ostream& out, const FrameHeader& h) {
  return out << h.ToString();
}

}
}

#endif
