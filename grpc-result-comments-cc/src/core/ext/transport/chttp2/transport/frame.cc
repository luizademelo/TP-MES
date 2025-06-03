Here's the commented version of the code:

```c++
// Copyright 2023 gRPC authors.

#include "src/core/ext/transport/chttp2/transport/frame.h"

#include <grpc/support/port_platform.h>
#include <stddef.h>

#include <cstdint>
#include <string>
#include <utility>

#include "absl/log/check.h"
#include "absl/status/status.h"
#include "absl/strings/str_cat.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/lib/slice/slice_buffer.h"
#include "src/core/util/crash.h"

using grpc_core::http2::Http2ErrorCode;
using grpc_core::http2::Http2Status;
using grpc_core::http2::ValueOrHttp2Status;

namespace grpc_core {

namespace {

// Enum defining HTTP/2 frame types as per RFC 9113
enum class FrameType : uint8_t {
  kData = 0,           // DATA frame
  kHeader = 1,         // HEADERS frame
  kRstStream = 3,      // RST_STREAM frame
  kSettings = 4,       // SETTINGS frame
  kPushPromise = 5,    // PUSH_PROMISE frame
  kPing = 6,           // PING frame
  kGoaway = 7,         // GOAWAY frame
  kWindowUpdate = 8,    // WINDOW_UPDATE frame
  kContinuation = 9,    // CONTINUATION frame
  kCustomSecurity = 200 // Custom security frame (non-standard)
};

// HTTP/2 frame flag definitions
constexpr uint8_t kFlagEndStream = 1;    // END_STREAM flag
constexpr uint8_t kFlagAck = 1;          // ACK flag (used in PING and SETTINGS)
constexpr uint8_t kFlagEndHeaders = 4;   // END_HEADERS flag
constexpr uint8_t kFlagPadded = 8;       // PADDED flag
constexpr uint8_t kFlagPriority = 0x20;  // PRIORITY flag

// Writes a 16-bit value to output buffer in network byte order (big-endian)
void Write2b(uint16_t x, uint8_t* output) {
  output[0] = static_cast<uint8_t>(x >> 8);
  output[1] = static_cast<uint8_t>(x);
}

// Reads a 16-bit value from input buffer in network byte order (big-endian)
uint16_t Read2b(const uint8_t* input) {
  return static_cast<uint16_t>(input[0]) << 8 | static_cast<uint16_t>(input[1]);
}

// Writes a 24-bit value to output buffer in network byte order (big-endian)
void Write3b(uint32_t x, uint8_t* output) {
  CHECK_LT(x, 16777216u); // Ensure value fits in 24 bits
  output[0] = static_cast<uint8_t>(x >> 16);
  output[1] = static_cast<uint8_t>(x >> 8);
  output[2] = static_cast<uint8_t>(x);
}

// Reads a 24-bit value from input buffer in network byte order (big-endian)
uint32_t Read3b(const uint8_t* input) {
  return static_cast<uint32_t>(input[0]) << 16 |
         static_cast<uint32_t>(input[1]) << 8 | static_cast<uint32_t>(input[2]);
}

// Mask for 7-bit values (used for 31-bit values where MSB is reserved)
constexpr uint32_t k8BitMask = 0x7f;

// Writes a 31-bit value (with MSB masked out) to output buffer
void Write31bits(uint32_t x, uint8_t* output) {
  output[0] = static_cast<uint8_t>(k8BitMask & (x >> 24));
  output[1] = static_cast<uint8_t>(x >> 16);
  output[2] = static_cast<uint8_t>(x >> 8);
  output[3] = static_cast<uint8_t>(x);
}

// Reads a 31-bit value (with MSB masked out) from input buffer
uint32_t Read31bits(const uint8_t* input) {
  return (k8BitMask & static_cast<uint32_t>(input[0])) << 24 |
         static_cast<uint32_t>(input[1]) << 16 |
         static_cast<uint32_t>(input[2]) << 8 | static_cast<uint32_t>(input[3]);
}

// Writes a 32-bit value to output buffer in network byte order (big-endian)
void Write4b(uint32_t x, uint8_t* output) {
  output[0] = static_cast<uint8_t>(x >> 24);
  output[1] = static_cast<uint8_t>(x >> 16);
  output[2] = static_cast<uint8_t>(x >> 8);
  output[3] = static_cast<uint8_t>(x);
}

// Reads a 32-bit value from input buffer in network byte order (big-endian)
uint32_t Read4b(const uint8_t* input) {
  return static_cast<uint32_t>(input[0]) << 24 |
         static_cast<uint32_t>(input[1]) << 16 |
         static_cast<uint32_t>(input[2]) << 8 | static_cast<uint32_t>(input[3]);
}

// Writes a 64-bit value to output buffer in network byte order (big-endian)
void Write8b(uint64_t x, uint8_t* output) {
  output[0] = static_cast<uint8_t>(x >> 56);
  output[1] = static_cast<uint8_t>(x >> 48);
  output[2] = static_cast<uint8_t>(x >> 40);
  output[3] = static_cast<uint8_t>(x >> 32);
  output[4] = static_cast<uint8_t>(x >> 24);
  output[5] = static_cast<uint8_t>(x >> 16);
  output[6] = static_cast<uint8_t>(x >> 8);
  output[7] = static_cast<uint8_t>(x);
}

// Reads a 64-bit value from input buffer in network byte order (big-endian)
uint64_t Read8b(const uint8_t* input) {
  return static_cast<uint64_t>(input[0]) << 56 |
         static_cast<uint64_t>(input[1]) << 48 |
         static_cast<uint64_t>(input[2]) << 40 |
         static_cast<uint64_t>(input[3]) << 32 |
         static_cast<uint64_t>(input[4]) << 24 |
         static_cast<uint64_t>(input[5]) << 16 |
         static_cast<uint64_t>(input[6]) << 8 | static_cast<uint64_t>(input[7]);
}

// Helper function to conditionally apply a flag
uint8_t MaybeFlag(bool condition, uint8_t flag_mask) {
  return condition ? flag_mask : 0;
}

// Helper function to check if a flag is set
bool ExtractFlag(uint8_t flags, uint8_t flag_mask) {
  return (flags & flag_mask) != 0;
}

// Visitor class to calculate additional bytes needed for frame serialization
class SerializeExtraBytesRequired {
 public:
  size_t operator()(const Http2DataFrame&) { return 0; }
  size_t operator()(const Http2HeaderFrame&) { return 0; }
  size_t operator()(const Http2ContinuationFrame&) { return 0; }
  size_t operator()(const Http2RstStreamFrame&) { return 4; } // 4 bytes for error code
  size_t operator()(const Http2SettingsFrame& f) {
    return 6 * f.settings.size(); // 6 bytes per setting (2 for ID, 4 for value)
  }
  size_t operator()(const Http2PingFrame&) { return 8; } // 8 bytes for opaque data
  size_t operator()(const Http2GoawayFrame&) { return 8; } // 8 bytes for fixed fields
  size_t operator()(const Http2WindowUpdateFrame&) { return 4; } // 4 bytes for increment
  size_t operator()(const Http2SecurityFrame&) { return 0; }
  size_t operator()(const Http2UnknownFrame&) { Crash("unreachable"); }
  size_t operator()(const Http2EmptyFrame&) { return 0; }
};

// Visitor class to serialize HTTP/2 frames
class SerializeHeaderAndPayload {
 public:
  SerializeHeaderAndPayload(size_t extra_bytes, SliceBuffer& out)
      : out_(out),
        extra_bytes_(MutableSlice::CreateUninitialized(extra_bytes)) {}

  // Serialize DATA frame
  void operator()(Http2DataFrame& frame) {
    auto hdr = extra_bytes_.TakeFirst(kFrameHeaderSize);
    Http2FrameHeader{static_cast<uint32_t>(frame.payload.Length()),
                     static_cast<uint8_t>(FrameType::kData),
                     MaybeFlag(frame.end_stream, kFlagEndStream),
                     frame.stream_id}
        .Serialize(hdr.begin());
    out_.AppendIndexed(Slice(std::move(hdr)));
    out_.TakeAndAppend(frame.payload);
  }

  // Serialize HEADERS frame
  void operator()(Http2HeaderFrame& frame) {
    auto hdr = extra_bytes_.TakeFirst(kFrameHeaderSize);
    Http2FrameHeader{
        static_cast<uint32_t>(frame.payload.Length()),
        static_cast<uint8_t>(FrameType::kHeader),
        static_cast<uint8_t>(MaybeFlag(frame.end_headers, kFlagEndHeaders) |
                             MaybeFlag(frame.end_stream, kFlagEndStream)),
        frame.stream_id}
        .Serialize(hdr.begin());
    out_.AppendIndexed(Slice(std::move(hdr)));
    out_.TakeAndAppend(frame.payload);
  }

  // Serialize CONTINUATION frame
  void operator()(Http2ContinuationFrame& frame) {
    auto hdr = extra_bytes_.TakeFirst(kFrameHeaderSize);
    Http2FrameHeader{
        static_cast<uint32_t>(frame.payload.Length()),
        static_cast<uint8_t>(FrameType::kContinuation),
        static_cast<uint8_t>(MaybeFlag(frame.end_headers, kFlagEndHeaders)),
        frame.stream_id}
        .Serialize(hdr.begin());
    out_.AppendIndexed(Slice(std::move(hdr)));
    out_.TakeAndAppend(frame.payload);
  }

  // Serialize RST_STREAM frame
  void operator()(Http2RstStreamFrame& frame) {
    auto hdr_and_payload = extra_bytes_.TakeFirst(kFrameHeaderSize + 4);
    Http2FrameHeader{4, static_cast<uint8_t>(FrameType::kRstStream), 0,
                     frame.stream_id}
        .Serialize(hdr_and_payload.begin());
    Write4b(frame.error_code, hdr_and_payload.begin() + kFrameHeaderSize);
    out_.AppendIndexed(Slice(std::move(hdr_and_payload)));
  }

  // Serialize SETTINGS frame
  void operator()(Http2SettingsFrame& frame) {
    const size_t payload_size = 6 * frame.settings.size();
    auto hdr_and_payload =
        extra_bytes_.TakeFirst(kFrameHeaderSize + payload_size);
    Http2FrameHeader{static_cast<uint32_t>(payload_size),
                     static_cast<uint8_t>(FrameType::kSettings),
                     MaybeFlag(frame.ack, kFlagAck), 0}
        .Serialize(hdr_and_payload.begin());
    size_t offset = kFrameHeaderSize;
    for (auto& setting : frame.settings) {
      Write2b(setting.id, hdr_and_payload.begin() + offset);
      Write4b(setting.value, hdr_and_payload.begin() + offset + 2);
      offset += 6;
    }
    out_.AppendIndexed(Slice(std::move(hdr_and_payload)));
  }

  // Serialize PING frame
  void operator()(Http2PingFrame& frame) {
    auto hdr_and_payload = extra_bytes_.TakeFirst(kFrameHeaderSize + 8);
    Http2FrameHeader{8, static_cast<uint8_t>(FrameType::kPing),
                     MaybeFlag(frame.ack, kFlagAck), 0}
        .Serialize(hdr_and_payload.begin());
    Write8b(frame.opaque, hdr_and_payload.begin() + kFrameHeaderSize);
    out_.AppendIndexed(Slice(std::move(hdr_and_payload)));
  }

  // Serialize GOAWAY frame
  void operator()(Http2GoawayFrame& frame) {
    auto hdr_and_fixed_payload = extra_bytes_.TakeFirst(kFrameHeaderSize + 8);
    Http2FrameHeader{static_cast<uint32_t>(8 + frame.debug_data.length()),
                     static_cast<uint8_t>(FrameType::kGoaway), 0, 0}
        .Serialize(hdr_and_fixed_payload.begin());
    if (GPR_UNLIKELY(frame.last_stream_id > RFC9113::kMaxStreamId31Bit)) {
      LOG(ERROR) << "Stream ID will be truncated. The MSB will be set to 0 "
                 << frame.last_stream_id;
    }
    Write31bits(frame.last_stream_id,
                hdr_and_fixed_payload.begin() + kFrameHeaderSize);
    Write4b(frame.error_code,
            hdr_and_fixed_payload.begin() + kFrameHeaderSize + 4);
    out_.AppendIndexed(Slice(std::move(hdr_and_fixed_payload)));
    out_.AppendIndexed(std::move(frame.debug_data));
  }

  // Serialize WINDOW_UPDATE frame
  void operator()(Http2WindowUpdateFrame& frame) {
    auto hdr_and_payload = extra_bytes_.TakeFirst(kFrameHeaderSize + 4);
    Http2FrameHeader{4, static_cast<uint8_t>(FrameType::kWindowUpdate), 0,
                     frame.stream_id}
        .Serialize(hdr_and_payload.begin());
    if (GPR_UNLIKELY(frame.increment > RFC9113::kMaxStreamId31Bit)) {
      LOG(ERROR) << "Http2WindowUpdateFrame increment will be truncated to 31 "
                    "bits. The MSB will be set to 0 "
                 << frame.increment;
    }
    Write31bits(frame.increment, hdr_and_payload.begin() + kFrameHeaderSize);
    out_.AppendIndexed(Slice(std::move(hdr_and_payload)));
  }

  // Serialize custom SECURITY frame
  void operator()(Http2SecurityFrame& frame) {
    auto hdr = extra_bytes_.TakeFirst(kFrameHeaderSize);
    Http2FrameHeader{static_cast<uint32_t>(frame.payload.Length()),
                     static_cast<uint8_t>(FrameType::kCustomSecurity), 0, 0}
        .Serialize(hdr.begin());
    out_.AppendIndexed(Slice(std::move(hdr)));
    out_.TakeAndAppend(frame.payload);
  }

  void operator()(Http2UnknownFrame&) { Crash("unreachable"); }
  void operator()(Http2EmptyFrame&) {}

 private:
  SliceBuffer& out_;
  MutableSlice extra_bytes_;
};

// Helper function to strip padding from frame payload
Http2Status StripPadding(const Http2FrameHeader& hdr, SliceBuffer& payload) {
  if (GPR_UNLIKELY(payload.Length() < 1)) {
    return Http2Status::Http2ConnectionError(
        Http2ErrorCode::kProtocolError,
        absl::StrCat(RFC9113::kFrameParserIncorrectPadding, hdr.ToString()));
  }
  const size_t payload_size = payload.Length();
  uint8_t padding_bytes;
  payload.MoveFirstNBytesIntoBuffer(1, &padding_bytes);

  if (GPR_UNLIKELY(payload_size <= padding_bytes)) {
    return Http2Status::Http2ConnectionError(
        Http2ErrorCode::kProtocolError,
        absl::StrCat(RFC9113::kPaddingLengthLargerThanFrameLength,
                     hdr.ToString()));
  }

  payload.RemoveLastNBytes(padding_bytes);
  return Http2Status::Ok();
}

// Parse DATA frame
ValueOrHttp2Status<Http2Frame> ParseDataFrame(const Http2FrameHeader& hdr,
                                              SliceBuffer& payload) {
  if (GPR_UNLIKELY((hdr.stream_id % 2) == 0)) {
    if ((hdr.stream_id == 0)) {
      return Http2Status::Http2ConnectionError(
          Http2ErrorCode::kProtocolError,
          absl::StrCat(RFC9113::kDataStreamIdMustBeNonZero, hdr.ToString()));
    } else {
      return Http2Status::Http2ConnectionError(
          Http2ErrorCode::kProtocolError,
          absl::StrCat(RFC9113::kStreamIdMustBeOdd, hdr.ToString()));
    }
  }

  if (hdr.flags & kFlagPadded) {
    Http2Status s = StripPadding(hdr, payload);
    if (GPR_UNLIKELY(!s.IsOk())) {
      return ValueOrHttp2Status<Http2Frame>(std::move(s));
    }
  }

  return ValueOrHttp2Status<Http2Frame>(
      Http2DataFrame{hdr.stream_id, ExtractFlag(hdr.flags, kFlagEndStream),
                     std::move(payload)});
}

// Parse HEADERS frame
ValueOrHttp2Status<Http2Frame> ParseHeaderFrame(const Http2FrameHeader& hdr,
                                                SliceBuffer& payload) {
  if (GPR_UNLIKELY((hdr.stream_id % 2) == 0)) {
    if (hdr.stream_id == 0) {
      return Http2Status::Http2ConnectionError(
          Http2ErrorCode::kProtocolError,
          absl::StrCat(RFC9113::kHeaderStreamIdMustBeNonZero, hdr.ToString()));
    } else {
      return Http2Status::Http2ConnectionError(
          Http2ErrorCode::kProtocolError,
          absl::StrCat(RFC9113::kStreamIdMustBeOdd, hdr.ToString()));
    }
  }

  if (hdr.flags & kFlagPadded) {
    Http2Status s = StripPadding(hdr, payload);
    if (GPR_UNLIKELY(!s.IsOk())) {
      return ValueOrHttp2Status<Http2