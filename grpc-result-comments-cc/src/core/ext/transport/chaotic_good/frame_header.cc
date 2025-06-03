Here's the commented version of the code:

```c++
// Copyright 2022 gRPC authors.

// Header file for frame header functionality in chaotic_good transport
#include "src/core/ext/transport/chaotic_good/frame_header.h"

// Platform-specific support macros
#include <grpc/support/port_platform.h>

// Standard integer types
#include <cstdint>

// ABSL utilities for status and string operations
#include "absl/status/status.h"
#include "absl/strings/str_cat.h"

namespace grpc_core {
namespace chaotic_good {

// Converts FrameHeader object to a human-readable string representation
// Format: [type:<type> stream_id:<id> payload_length:<length>]
std::string FrameHeader::ToString() const {
  return absl::StrCat("[type:", type, " stream_id:", stream_id,
                      " payload_length:", payload_length, "]");
}

// Converts a FrameType enum value to its string representation
// Handles all known frame types and provides a fallback for unknown types
// Unknown types are represented as "Unknown[0x<hex-value>]"
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
  // Default case for unknown frame types
  return absl::StrCat("Unknown[0x", absl::Hex(static_cast<int>(type)), "]");
}

}  // namespace chaotic_good
}  // namespace grpc_core
```

The comments added explain:
1. The purpose of each include file
2. The functionality of the `ToString()` method
3. The behavior of the `FrameTypeString()` function, including how it handles both known and unknown frame types
4. The structure of the namespace hierarchy
5. The format of the output strings

The comments are concise yet informative, providing enough context for future maintainers to understand the code's purpose and behavior without being overly verbose.