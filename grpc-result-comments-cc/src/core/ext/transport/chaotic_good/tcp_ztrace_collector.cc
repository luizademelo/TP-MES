Here's the updated code with comprehensive comments:

```c++
// Copyright 2025 gRPC authors.

#include "src/core/ext/transport/chaotic_good/tcp_ztrace_collector.h"
#include "src/core/ext/transport/chaotic_good/frame_header.h"

namespace grpc_core::chaotic_good::tcp_ztrace_collector_detail {

// Converts TCP frame header information into a JSON object for tracing purposes.
// Args:
//   header: The TCP frame header containing metadata about the frame
//   object: Reference to the JSON object where the header data will be stored
void TcpFrameHeaderToJsonObject(const TcpFrameHeader& header,
                                Json::Object& object) {
  // Add frame type as string representation to JSON object
  object["frame_type"] = Json::FromString(FrameTypeString(header.header.type));
  // Add stream identifier to JSON object
  object["stream_id"] = Json::FromNumber(header.header.stream_id);
  // Add payload length to JSON object
  object["payload_length"] = Json::FromNumber(header.header.payload_length);
  // Conditionally add payload tag if it's non-zero
  if (header.payload_tag != 0) {
    object["payload_tag"] = Json::FromNumber(header.payload_tag);
  }
}

// Converts TCP data frame header information into a JSON object for tracing.
// Args:
//   header: The TCP data frame header containing specific metadata
//   object: Reference to the JSON object where the header data will be stored
void TcpDataFrameHeaderToJsonObject(const TcpDataFrameHeader& header,
                                    Json::Object& object) {
  // Add payload tag to identify the payload
  object["payload_tag"] = Json::FromNumber(header.payload_tag);
  // Add timestamp indicating when the frame was sent
  object["send_time"] = Json::FromNumber(header.send_timestamp);
  // Add length of the payload data
  object["payload_length"] = Json::FromNumber(header.payload_length);
}

// Adds a read status marker to the JSON trace object.
// Args:
//   read: Boolean indicating whether the operation was a read
//   object: Reference to the JSON object to be modified
void MarkRead(bool read, Json::Object& object) {
  object["read"] = Json::FromBool(read);
}

}  // namespace grpc_core::chaotic_good::tcp_ztrace_collector_detail
```

The comments provide:
1. A description of each function's purpose
2. Explanation of parameters
3. Documentation of what each field in the JSON object represents
4. Clear indication of conditional operations
5. Namespace closing comment for better readability

The comments follow a consistent style and provide enough information for future maintainers to understand the tracing functionality without needing to examine the implementation details.