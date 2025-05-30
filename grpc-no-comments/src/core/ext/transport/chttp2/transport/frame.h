// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_EXT_TRANSPORT_CHTTP2_TRANSPORT_FRAME_H
#define GRPC_SRC_CORE_EXT_TRANSPORT_CHTTP2_TRANSPORT_FRAME_H

#include <grpc/support/port_platform.h>

#include <cstdint>
#include <string>
#include <variant>
#include <vector>

#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"
#include "absl/types/span.h"
#include "src/core/ext/transport/chttp2/transport/http2_status.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/lib/slice/slice_buffer.h"

namespace grpc_core {

constexpr uint8_t kFrameHeaderSize = 9;

struct Http2DataFrame {
  uint32_t stream_id = 0;
  bool end_stream = false;
  SliceBuffer payload;

  bool operator==(const Http2DataFrame& other) const {
    return stream_id == other.stream_id && end_stream == other.end_stream &&
           payload.JoinIntoString() == other.payload.JoinIntoString();
  }
};

struct Http2HeaderFrame {
  uint32_t stream_id = 0;
  bool end_headers = false;
  bool end_stream = false;
  SliceBuffer payload;

  bool operator==(const Http2HeaderFrame& other) const {
    return stream_id == other.stream_id && end_headers == other.end_headers &&
           end_stream == other.end_stream &&
           payload.JoinIntoString() == other.payload.JoinIntoString();
  }
};

struct Http2ContinuationFrame {
  uint32_t stream_id = 0;
  bool end_headers = false;
  SliceBuffer payload;

  bool operator==(const Http2ContinuationFrame& other) const {
    return stream_id == other.stream_id && end_headers == other.end_headers &&
           payload.JoinIntoString() == other.payload.JoinIntoString();
  }
};

struct Http2RstStreamFrame {
  uint32_t stream_id = 0;
  uint32_t error_code = 0;

  bool operator==(const Http2RstStreamFrame& other) const {
    return stream_id == other.stream_id && error_code == other.error_code;
  }
};

struct Http2SettingsFrame {
  struct Setting {
    Setting(uint16_t id, uint32_t value) : id(id), value(value) {}

    uint16_t id;
    uint32_t value;

    bool operator==(const Setting& other) const {
      return id == other.id && value == other.value;
    }
  };
  bool ack = false;
  std::vector<Setting> settings;

  bool operator==(const Http2SettingsFrame& other) const {
    return ack == other.ack && settings == other.settings;
  }
};

struct Http2PingFrame {
  bool ack = false;
  uint64_t opaque = 0;

  bool operator==(const Http2PingFrame& other) const {
    return ack == other.ack && opaque == other.opaque;
  }
};

struct Http2GoawayFrame {
  uint32_t last_stream_id = 0;
  uint32_t error_code = 0;
  Slice debug_data;

  bool operator==(const Http2GoawayFrame& other) const {
    return last_stream_id == other.last_stream_id &&
           error_code == other.error_code &&
           debug_data.as_string_view() == other.debug_data.as_string_view();
  }
};

struct Http2WindowUpdateFrame {
  uint32_t stream_id = 0;
  uint32_t increment = 0;

  bool operator==(const Http2WindowUpdateFrame& other) const {
    return stream_id == other.stream_id && increment == other.increment;
  }
};

struct Http2SecurityFrame {
  SliceBuffer payload;

  bool operator==(const Http2SecurityFrame& other) const {
    return payload.JoinIntoString() == other.payload.JoinIntoString();
  }
};

struct Http2UnknownFrame {
  bool operator==(const Http2UnknownFrame&) const { return true; }
};

struct Http2EmptyFrame {
  bool operator==(const Http2EmptyFrame&) const { return true; }
};

using Http2Frame =
    std::variant<Http2DataFrame, Http2HeaderFrame, Http2ContinuationFrame,
                 Http2RstStreamFrame, Http2SettingsFrame, Http2PingFrame,
                 Http2GoawayFrame, Http2WindowUpdateFrame, Http2SecurityFrame,
                 Http2UnknownFrame, Http2EmptyFrame>;

struct Http2FrameHeader {
  uint32_t length;
  uint8_t type;
  uint8_t flags;
  uint32_t stream_id;

  void Serialize(uint8_t* output) const;

  static Http2FrameHeader Parse(const uint8_t* input);
  std::string ToString() const;

  bool operator==(const Http2FrameHeader& other) const {
    return length == other.length && type == other.type &&
           flags == other.flags && stream_id == other.stream_id;
  }
};

http2::ValueOrHttp2Status<Http2Frame> ParseFramePayload(
    const Http2FrameHeader& hdr, SliceBuffer payload);

void Serialize(absl::Span<Http2Frame> frames, SliceBuffer& out);

constexpr uint8_t kGrpcHeaderSizeInBytes = 5;

struct GrpcMessageHeader {
  uint8_t flags = 0;
  uint32_t length = 0;
};

GrpcMessageHeader ExtractGrpcHeader(SliceBuffer& payload);

void AppendGrpcHeaderToSliceBuffer(SliceBuffer& payload, const uint8_t flags,
                                   const uint32_t length);

namespace RFC9113 {

inline constexpr absl::string_view kStreamIdMustBeOdd =
    "RFC9113: Streams initiated by a client MUST use odd-numbered stream "
    "identifiers";

inline constexpr absl::string_view kDataStreamIdMustBeNonZero =
    "RFC9113: DATA frames MUST be associated with a stream";
inline constexpr absl::string_view kHeaderStreamIdMustBeNonZero =
    "RFC9113: HEADERS frames MUST be associated with a stream";
inline constexpr absl::string_view kContinuationStreamIdMustBeNonZero =
    "RFC9113: CONTINUATION frames MUST be associated with a stream";
inline constexpr absl::string_view kRstStreamStreamIdMustBeNonZero =
    "RFC9113: RST_STREAM frames frames MUST be associated with a stream";

inline constexpr absl::string_view kPingStreamIdMustBeZero =
    "RFC9113: If a PING frame is received with a Stream Identifier field "
    "value other than 0x00, the recipient MUST respond with a connection error";
inline constexpr absl::string_view kGoAwayStreamIdMustBeZero =
    "RFC9113: An endpoint MUST treat a GOAWAY frame with a stream identifier "
    "other than 0x00 as a connection error";
inline constexpr absl::string_view kSettingsStreamIdMustBeZero =
    "RFC9113: If an endpoint receives a SETTINGS frame whose Stream "
    "Identifier field is anything other than 0x00, the endpoint MUST respond "
    "with a connection error";

inline constexpr absl::string_view kRstStreamLength4 =
    "RFC9113: A RST_STREAM frame with a length other than 4 octets MUST be "
    "treated as a connection error";
inline constexpr absl::string_view kSettingsLength0 =
    "RFC9113: Receipt of a SETTINGS frame with the ACK flag set and a length "
    "field value other than 0 MUST be treated as a connection error";
inline constexpr absl::string_view kSettingsLength6x =
    "RFC9113: SETTINGS frame with a length other than a multiple of 6 octets "
    "MUST be treated as a connection error";
inline constexpr absl::string_view kPingLength8 =
    "RFC9113: Receipt of a PING frame with a length field value other than 8 "
    "MUST be treated as a connection error";
inline constexpr absl::string_view kWindowUpdateLength4 =
    "RFC9113: A WINDOW_UPDATE frame with a length other than 4 octets MUST be "
    "treated as a connection error";
inline constexpr absl::string_view kWindowSizeIncrement =
    "RFC9113: The legal range for the increment to the flow-control window is "
    "1 to (2^31)-1";
inline constexpr absl::string_view kPaddingLengthLargerThanFrameLength =
    "RFC9113: If the length of the padding is the length of the frame payload "
    "or greater, the recipient MUST treat this as a connection error";

inline constexpr absl::string_view kNoPushPromise =
    "RFC9113: PUSH_PROMISE MUST NOT be sent if the SETTINGS_ENABLE_PUSH "
    "setting of the "
    "peer endpoint is set to 0";

inline constexpr absl::string_view kFrameParserIncorrectPadding =
    "Incorrect length of padding in frame";
inline constexpr absl::string_view kIncorrectFrame = "Incorrect Frame";
inline constexpr absl::string_view kGoAwayLength8 =
    "GOAWAY frame should have a Last-Stream-ID and Error Code making the "
    "minimum length 8 octets";

inline constexpr uint32_t kMaxStreamId31Bit = 0x7fffffffu;

}
}

#endif
