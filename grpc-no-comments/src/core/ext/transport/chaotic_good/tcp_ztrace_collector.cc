
// Copyright 2025 gRPC authors.

#include "src/core/ext/transport/chaotic_good/tcp_ztrace_collector.h"

#include "src/core/ext/transport/chaotic_good/frame_header.h"

namespace grpc_core::chaotic_good::tcp_ztrace_collector_detail {

void TcpFrameHeaderToJsonObject(const TcpFrameHeader& header,
                                Json::Object& object) {
  object["frame_type"] = Json::FromString(FrameTypeString(header.header.type));
  object["stream_id"] = Json::FromNumber(header.header.stream_id);
  object["payload_length"] = Json::FromNumber(header.header.payload_length);
  if (header.payload_tag != 0) {
    object["payload_tag"] = Json::FromNumber(header.payload_tag);
  }
}

void TcpDataFrameHeaderToJsonObject(const TcpDataFrameHeader& header,
                                    Json::Object& object) {
  object["payload_tag"] = Json::FromNumber(header.payload_tag);
  object["send_time"] = Json::FromNumber(header.send_timestamp);
  object["payload_length"] = Json::FromNumber(header.payload_length);
}

void MarkRead(bool read, Json::Object& object) {
  object["read"] = Json::FromBool(read);
}

}
