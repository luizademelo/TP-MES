// Copyright 2022 gRPC authors.

#include "src/core/ext/transport/chaotic_good/frame_header.h"

#include <grpc/support/port_platform.h>

#include <cstdint>

#include "absl/status/status.h"
#include "absl/strings/str_cat.h"

namespace grpc_core {
namespace chaotic_good {

std::string FrameHeader::ToString() const {
  return absl::StrCat("[type:", type, " stream_id:", stream_id,
                      " payload_length:", payload_length, "]");
}

std::string FrameTypeString(FrameType type) {
  switch (type) {
    case FrameType::kSettings:
      return "Settings";
    case FrameType::kClientInitialMetadata:
      return "ClientInitialMetadata";
    case FrameType::kClientEndOfStream:
      return "ClientEndOfStream";
    case FrameType::kMessage:
      return "Message";
    case FrameType::kServerInitialMetadata:
      return "ServerInitialMetadata";
    case FrameType::kServerTrailingMetadata:
      return "ServerTrailingMetadata";
    case FrameType::kCancel:
      return "Cancel";
    case FrameType::kBeginMessage:
      return "BeginMessage";
    case FrameType::kMessageChunk:
      return "MessageChunk";
    case FrameType::kTcpSecurityFrame:
      return "TcpSecurityFrame";
  }
  return absl::StrCat("Unknown[0x", absl::Hex(static_cast<int>(type)), "]");
}

}
}
