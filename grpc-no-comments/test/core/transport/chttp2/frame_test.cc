// Copyright 2023 gRPC authors.

#include "src/core/ext/transport/chttp2/transport/frame.h"

#include <algorithm>
#include <initializer_list>
#include <utility>

#include "absl/status/status.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "src/core/ext/transport/chttp2/transport/http2_status.h"
#include "src/core/lib/slice/slice_buffer.h"

namespace grpc_core {
namespace {

using http2::Http2ErrorCode;
using http2::Http2Status;
using http2::ValueOrHttp2Status;

MATCHER_P3(Http2StatusIs, error_type, code, message, "") {
  if (arg.GetType() != error_type) {
    return false;
  }
  if (error_type == Http2Status::Http2ErrorType::kStreamError) {
    return arg.GetStreamErrorCode() == code &&
           arg.GetAbslStreamError().message() == message;
  } else {
    return arg.GetConnectionErrorCode() == code &&
           arg.GetAbslConnectionError().message() == message;
  }
}

void DoTheseThings(std::initializer_list<int>) {}

template <typename... Frames>
std::vector<uint8_t> Serialize(Frames... f) {
  std::vector<Http2Frame> frames;
  DoTheseThings({(frames.emplace_back(std::move(f)), 1)...});
  SliceBuffer temp;
  Serialize(absl::Span<Http2Frame>(frames), temp);
  auto slice = temp.JoinIntoSlice();
  return std::vector<uint8_t>(slice.begin(), slice.end());
}

template <typename... I>
std::vector<uint8_t> ByteVec(I... i) {
  return std::vector<uint8_t>{static_cast<uint8_t>(i)...};
}

SliceBuffer SliceBufferFromString(absl::string_view s) {
  SliceBuffer temp;
  temp.Append(Slice::FromCopiedString(s));
  return temp;
}

std::vector<uint8_t> Serialize(const Http2FrameHeader& header) {
  uint8_t temp[9];
  header.Serialize(temp);
  return std::vector<uint8_t>(temp, temp + 9);
}

Http2FrameHeader ParseHeader(uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3,
                             uint8_t b4, uint8_t b5, uint8_t b6, uint8_t b7,
                             uint8_t b8) {
  uint8_t temp[9] = {b0, b1, b2, b3, b4, b5, b6, b7, b8};
  return Http2FrameHeader::Parse(temp);
}

template <typename... I>
Http2Frame ParseFrame(I... i) {
  SliceBuffer buffer;
  buffer.Append(Slice::FromCopiedBuffer(ByteVec(i...)));
  uint8_t hdr[9];
  buffer.MoveFirstNBytesIntoBuffer(9, hdr);
  auto frame_hdr = Http2FrameHeader::Parse(hdr);
  EXPECT_EQ(frame_hdr.length, buffer.Length())
      << "frame_hdr=" << frame_hdr.ToString();
  auto r = ParseFramePayload(frame_hdr, std::move(buffer));
  EXPECT_TRUE(r.IsOk()) << r.DebugString();
  return std::move(r.value());
}

template <typename... I>
Http2Status ValidateFrame(I... i) {
  SliceBuffer buffer;
  buffer.Append(Slice::FromCopiedBuffer(ByteVec(i...)));
  uint8_t hdr[9];
  buffer.MoveFirstNBytesIntoBuffer(9, hdr);
  auto frame_hdr = Http2FrameHeader::Parse(hdr);
  EXPECT_EQ(frame_hdr.length, buffer.Length())
      << "frame_hdr=" << frame_hdr.ToString();

  auto frame = ParseFramePayload(frame_hdr, std::move(buffer));
  return (frame.IsOk()
              ? Http2Status::Ok()
              : ValueOrHttp2Status<Http2Frame>::TakeStatus(std::move(frame)));
}

TEST(Header, Serialization) {
  EXPECT_EQ(Serialize(Http2FrameHeader{0, 0, 0, 0}),
            ByteVec(0, 0, 0, 0, 0, 0, 0, 0, 0));
  EXPECT_EQ(Serialize(Http2FrameHeader{0x123456, 0x9a, 0xbc, 0x12345678}),
            ByteVec(0x12, 0x34, 0x56, 0x9a, 0xbc, 0x12, 0x34, 0x56, 0x78));
}

TEST(Header, Parse) {
  EXPECT_EQ(ParseHeader(0, 0, 0, 0, 0, 0, 0, 0, 0),
            (Http2FrameHeader{0, 0, 0, 0}));
  EXPECT_EQ(ParseHeader(0x12, 0x34, 0x56, 0x9a, 0xbc, 0x12, 0x34, 0x56, 0x78),
            (Http2FrameHeader{0x123456, 0x9a, 0xbc, 0x12345678}));
}

TEST(Header, ToString) {
  EXPECT_EQ((Http2FrameHeader{0, 0, 0, 0}).ToString(),
            "{DATA: flags=0, stream_id=0, length=0}");
  EXPECT_EQ((Http2FrameHeader{0x123456, 0x9a, 0xbc, 0x12345678}).ToString(),
            "{UNKNOWN(154): flags=188, stream_id=305419896, length=1193046}");
}

TEST(Frame, Http2DataFrameSerialization) {
  EXPECT_EQ(Serialize(Http2DataFrame{1, false, SliceBufferFromString("hello")}),
            ByteVec(0, 0, 5, 0, 0, 0, 0, 0, 1, 'h', 'e', 'l', 'l', 'o'));
  EXPECT_EQ(Serialize(Http2DataFrame{0x78381821, true,
                                     SliceBufferFromString("kids")}),
            ByteVec(0, 0, 4, 0, 1, 0x78, 0x38, 0x18, 0x21, 'k', 'i', 'd', 's'));
}

TEST(Frame, Http2HeaderFrameSerialization) {
  EXPECT_EQ(Serialize(Http2HeaderFrame{1, false, false,
                                       SliceBufferFromString("hello")}),
            ByteVec(0, 0, 5, 1, 0, 0, 0, 0, 1, 'h', 'e', 'l', 'l', 'o'));
  EXPECT_EQ(Serialize(Http2HeaderFrame{1, true, false,
                                       SliceBufferFromString("hello")}),
            ByteVec(0, 0, 5, 1, 4, 0, 0, 0, 1, 'h', 'e', 'l', 'l', 'o'));
  EXPECT_EQ(Serialize(Http2HeaderFrame{1, false, true,
                                       SliceBufferFromString("hello")}),
            ByteVec(0, 0, 5, 1, 1, 0, 0, 0, 1, 'h', 'e', 'l', 'l', 'o'));
  EXPECT_EQ(Serialize(Http2HeaderFrame{1, true, true,
                                       SliceBufferFromString("hello")}),
            ByteVec(0, 0, 5, 1, 5, 0, 0, 0, 1, 'h', 'e', 'l', 'l', 'o'));
}

TEST(Frame, Http2ContinuationFrameSerialization) {
  EXPECT_EQ(Serialize(Http2ContinuationFrame{1, false,
                                             SliceBufferFromString("hello")}),
            ByteVec(0, 0, 5, 9, 0, 0, 0, 0, 1, 'h', 'e', 'l', 'l', 'o'));
  EXPECT_EQ(Serialize(Http2ContinuationFrame{1, true,
                                             SliceBufferFromString("hello")}),
            ByteVec(0, 0, 5, 9, 4, 0, 0, 0, 1, 'h', 'e', 'l', 'l', 'o'));
}

TEST(Frame, Http2RstStreamFrameSerialization) {
  EXPECT_EQ(Serialize(Http2RstStreamFrame{
                1, static_cast<uint32_t>(Http2ErrorCode::kConnectError)}),
            ByteVec(0, 0, 4, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0x0a));
}

TEST(Frame, Http2SettingsFrameSerialization) {
  EXPECT_EQ(Serialize(Http2SettingsFrame{}),
            ByteVec(0, 0, 0, 4, 0, 0, 0, 0, 0));
  EXPECT_EQ(
      Serialize(Http2SettingsFrame{false, {{0x1234, 0x9abcdef0}}}),
      ByteVec(0, 0, 6, 4, 0, 0, 0, 0, 0, 0x12, 0x34, 0x9a, 0xbc, 0xde, 0xf0));
  EXPECT_EQ(Serialize(Http2SettingsFrame{
                false, {{0x1234, 0x9abcdef0}, {0x4321, 0x12345678}}}),
            ByteVec(0, 0, 12, 4, 0, 0, 0, 0, 0, 0x12, 0x34, 0x9a, 0xbc, 0xde,
                    0xf0, 0x43, 0x21, 0x12, 0x34, 0x56, 0x78));
  EXPECT_EQ(Serialize(Http2SettingsFrame{true, {}}),
            ByteVec(0, 0, 0, 4, 1, 0, 0, 0, 0));
}

TEST(Frame, Http2PingFrameSerialization) {
  EXPECT_EQ(Serialize(Http2PingFrame{false, 0x123456789abcdef0}),
            ByteVec(0, 0, 8, 6, 0, 0, 0, 0, 0, 0x12, 0x34, 0x56, 0x78, 0x9a,
                    0xbc, 0xde, 0xf0));
  EXPECT_EQ(Serialize(Http2PingFrame{true, 0x123456789abcdef0}),
            ByteVec(0, 0, 8, 6, 1, 0, 0, 0, 0, 0x12, 0x34, 0x56, 0x78, 0x9a,
                    0xbc, 0xde, 0xf0));
}

TEST(Frame, Http2GoawayFrameSerialization) {
  EXPECT_EQ(
      Serialize(Http2GoawayFrame{
          0x12345678, static_cast<uint32_t>(Http2ErrorCode::kEnhanceYourCalm),
          Slice::FromCopiedString("hello")}),
      ByteVec( 0, 0, 13,
               7,
               0,
               0, 0, 0, 0,
               0x12, 0x34, 0x56, 0x78,
               0, 0, 0, 0x0b,
               'h', 'e', 'l', 'l', 'o'));

  EXPECT_EQ(
      Serialize(Http2GoawayFrame{0xffffffff, static_cast<uint32_t>(0xffffffff),
                                 Slice::FromCopiedString("hello")}),
      ByteVec( 0, 0, 13,
               7,
               0,
               0, 0, 0, 0,
               0x7f, 0xff, 0xff, 0xff,
               0xff, 0xff, 0xff, 0xff,
               'h', 'e', 'l', 'l', 'o'));
}

TEST(Frame, Http2WindowUpdateFrameSerialization) {
  EXPECT_EQ(Serialize(Http2WindowUpdateFrame{1, 0x12345678}),
            ByteVec( 0, 0, 4,
                     8,
                     0,
                     0, 0, 0, 1,
                     0x12, 0x34,
                    0x56, 0x78));

  EXPECT_EQ(Serialize(Http2WindowUpdateFrame{1, 0xffffffff}),
            ByteVec( 0, 0, 4,
                     8,
                     0,
                     0, 0, 0, 1,
                     0x7f, 0xff,
                    0xff, 0xff));
}

TEST(Frame, Http2SecurityFrameSerialization) {
  EXPECT_EQ(Serialize(Http2SecurityFrame{SliceBufferFromString("hello")}),
            ByteVec(0, 0, 5, 200, 0, 0, 0, 0, 0, 'h', 'e', 'l', 'l', 'o'));
}

constexpr uint8_t kFlagPadded = 8;
constexpr uint8_t kFlagPriority = 0x20;
constexpr uint8_t kAllOnes = 0xffu;

TEST(Frame, ParseHttp2DataFrame) {
  EXPECT_EQ(
      ParseFrame( 0, 0, 5,
                  0,

                 0,
                  0, 0, 0, 1,
                  'h', 'e', 'l', 'l', 'o'),
      Http2Frame(Http2DataFrame{1, false, SliceBufferFromString("hello")}));
  EXPECT_EQ(ParseFrame( 0, 0, 4,
                        0,

                       1,
                        0x18,
                       0x38, 0x18, 0x21,
                        'k', 'i', 'd', 's'),
            Http2Frame(Http2DataFrame{0x18381821, true,
                                      SliceBufferFromString("kids")}));

  EXPECT_EQ(ParseFrame( 0, 0, 4,
                        0,

                       (kAllOnes - kFlagPadded),

                        0xff, 0x38, 0x18, 0x21,
                        'k', 'i', 'd', 's'),
            Http2Frame(Http2DataFrame{0x7f381821, true,
                                      SliceBufferFromString("kids")}));
}

TEST(Frame, ParseHttp2HeaderFrame) {
  EXPECT_EQ(
      ParseFrame(
           0, 0, 5,
           1,

          0,
           0, 0, 0, 1,
           'h', 'e', 'l', 'l', 'o'),
      Http2Frame(Http2HeaderFrame{1, false,
                                  false,
                                  SliceBufferFromString("hello")}));
  EXPECT_EQ(
      ParseFrame(
           0, 0, 4,
           1,

          4,
           0x78, 0x38, 0x18, 0x21,
           'k', 'i', 'd', 's'),
      Http2Frame(Http2HeaderFrame{0x78381821, true,
                                  false,
                                  SliceBufferFromString("kids")}));
  EXPECT_EQ(
      ParseFrame(
           0, 0, 4,
           1,

          1,
           0x78, 0x38, 0x18, 0x21,
           'k', 'i', 'd', 's'),
      Http2Frame(Http2HeaderFrame{0x78381821, false,
                                  true,
                                  SliceBufferFromString("kids")}));
  EXPECT_EQ(
      ParseFrame(
           0, 0, 4,
           1,

          5,
           0x78, 0x38, 0x18, 0x21,
           'k', 'i', 'd', 's'),
      Http2Frame(Http2HeaderFrame{0x78381821, true,
                                  true,
                                  SliceBufferFromString("kids")}));

  EXPECT_EQ(
      ParseFrame(
           0, 0, 5,
           1,

          (kAllOnes - kFlagPriority - kFlagPadded),
           0xff, 0xff, 0xff,
          0xff,
           'h', 'e', 'l', 'l', 'o'),
      Http2Frame(Http2HeaderFrame{0x7fffffff, true,
                                  true,
                                  SliceBufferFromString("hello")}));
}

TEST(Frame, ParseHttp2ContinuationFrame) {
  EXPECT_EQ(
      ParseFrame(
           0, 0, 5,
           9,
           0,
           0, 0, 0, 1,
           'h', 'e', 'l', 'l', 'o'),
      Http2Frame(Http2ContinuationFrame{1, false,
                                        SliceBufferFromString("hello")}));
  EXPECT_EQ(
      ParseFrame(
           0, 0, 5,
           9,
           4,
           0x78, 0x38, 0x18, 0x21,
           'h', 'e', 'l', 'l', 'o'),
      Http2Frame(Http2ContinuationFrame{0x78381821, true,
                                        SliceBufferFromString("hello")}));

  EXPECT_EQ(
      ParseFrame(
           0, 0, 5,
           9,
           0xff,
           0xff, 0xff, 0xff, 0xff,
           'h', 'e', 'l', 'l', 'o'),
      Http2Frame(Http2ContinuationFrame{0x7fffffff, true,
                                        SliceBufferFromString("hello")}));
}

TEST(Frame, ParseHttp2RstStreamFrame) {
  EXPECT_EQ(ParseFrame( 0, 0, 4,
                        3,
                        0,
                        0, 0, 0, 1,
                        0, 0, 0, 0x0a),
            Http2Frame(Http2RstStreamFrame{
                1, static_cast<uint32_t>(Http2ErrorCode::kConnectError)}));

  EXPECT_EQ(ParseFrame( 0, 0, 4,
                        3,
                        0xff,
                        0xff, 0xff, 0xff, 0xff,
                        0xff, 0xff, 0xff, 0xff),
            Http2Frame(Http2RstStreamFrame{0x7fffffff, 0xffffffff}));
}

TEST(Frame, ParseHttp2SettingsFrame) {

  EXPECT_EQ(ParseFrame( 0, 0, 0,
                        4,
                        0,
                        0, 0, 0, 0),
            Http2Frame(Http2SettingsFrame{}));

  EXPECT_EQ(ParseFrame( 0, 0, 6,
                        4,
                        0,
                        0, 0, 0, 0,
                        0x12, 0x34, 0x9a, 0xbc,
                       0xde, 0xf0),
            Http2Frame(Http2SettingsFrame{false, {{0x1234, 0x9abcdef0}}}));
  EXPECT_EQ(ParseFrame( 0, 0, 12,
                        4,
                        0,
                        0, 0, 0, 0,
                        0x12, 0x34, 0x9a, 0xbc,
                       0xde, 0xf0,
                        0x43, 0x21, 0x12, 0x34,
                       0x56, 0x78),
            Http2Frame(Http2SettingsFrame{
                false, {{0x1234, 0x9abcdef0}, {0x4321, 0x12345678}}}));
  EXPECT_EQ(ParseFrame( 0, 0, 0,
                        4,
                        1,
                        0, 0, 0, 0),
            Http2Frame(Http2SettingsFrame{true, {}}));

  EXPECT_EQ(ParseFrame( 0, 0, 0,
                        4,
                        0xff,
                        0x80, 0, 0, 0),
            Http2Frame(Http2SettingsFrame{true}));
}

TEST(Frame, ParseHttp2PingFrame) {
  EXPECT_EQ(ParseFrame( 0, 0, 8,
                        6,
                        0,
                        0, 0, 0, 0,
                        0x12, 0x34, 0x56, 0x78,
                       0x9a, 0xbc, 0xde, 0xf0),
            Http2Frame(Http2PingFrame{false, 0x123456789abcdef0}));
  EXPECT_EQ(ParseFrame( 0, 0, 8,
                        6,
                        1,
                        0, 0, 0, 0,
                        0x12, 0x34, 0x56, 0x78,
                       0x9a, 0xbc, 0xde, 0xf0),
            Http2Frame(Http2PingFrame{true, 0x123456789abcdef0}));

  EXPECT_EQ(ParseFrame( 0, 0, 8,
                        6,
                        0xff,
                        0x80, 0, 0, 0,
                        0xff, 0xff, 0xff, 0xff,
                       0xff, 0xff, 0xff, 0xff),
            Http2Frame(Http2PingFrame{true, 0xffffffffffffffff}));
}

TEST(Frame, ParseHttp2GoawayFrame) {
  EXPECT_EQ(ParseFrame( 0, 0, 8,
                        7,
                        0,
                        0, 0, 0, 0,

                       0x12, 0x34, 0x56, 0x78,
                        0, 0, 0, 0x0b
                       ),
            Http2Frame(Http2GoawayFrame{
                0x12345678,
                static_cast<uint32_t>(Http2ErrorCode::kEnhanceYourCalm)}));
  EXPECT_EQ(
      ParseFrame( 0, 0, 13,
                  7,
                  0,
                  0, 0, 0, 0,

                 0x12, 0x34, 0x56, 0x78,
                  0, 0, 0, 0x0b,
                  'h', 'e', 'l', 'l', 'o'),
      Http2Frame(Http2GoawayFrame{
          0x12345678, static_cast<uint32_t>(Http2ErrorCode::kEnhanceYourCalm),
          Slice::FromCopiedString("hello")}));

  EXPECT_EQ(
      ParseFrame( 0, 0, 13,
                  7,
                  0xff,
                  0x80, 0, 0, 0,

                 0xff, 0xff, 0xff, 0xff,
                  0, 0, 0, 0x0b,
                  'h', 'e', 'l', 'l', 'o'),
      Http2Frame(Http2GoawayFrame{
          0x7fffffff, static_cast<uint32_t>(Http2ErrorCode::kEnhanceYourCalm),
          Slice::FromCopiedString("hello")}));
}

TEST(Frame, ParseHttp2WindowUpdateFrame) {
  EXPECT_EQ(ParseFrame( 0, 0, 4,
                        8,
                        0,
                        0, 0, 0, 1,

                       0x12, 0x34, 0x56, 0x78),
            Http2Frame(Http2WindowUpdateFrame{1, 0x12345678}));

  EXPECT_EQ(ParseFrame( 0, 0, 4,
                        8,
                        0xff,
                        0xff, 0xff, 0xff, 0xff,

                       0xff, 0xff, 0xff, 0xff),
            Http2Frame(Http2WindowUpdateFrame{0x7fffffff, 0x7fffffff}));
}

TEST(Frame, ParseHttp2SecurityFrame) {
  EXPECT_EQ(ParseFrame( 0, 0, 5,
                        200,
                        0,
                        0, 0, 0, 0,
                        'h', 'e', 'l', 'l', 'o'),
            Http2Frame(Http2SecurityFrame{SliceBufferFromString("hello")}));
  EXPECT_EQ(ParseFrame( 0, 0, 5,
                        200,
                        0xff,
                        0xff, 0xff, 0xff, 0xff,
                        'h', 'e', 'l', 'l', 'o'),
            Http2Frame(Http2SecurityFrame{SliceBufferFromString("hello")}));
}

TEST(Frame, ParseHttp2DataFramePadded) {
  EXPECT_EQ(
      ParseFrame( 0, 0, 9,
                  0,

                 8,
                  0, 0, 0, 1,
                  3,
                  'h', 'e', 'l', 'l', 'o',
                  0, 0, 0),
      Http2Frame(Http2DataFrame{1, false, SliceBufferFromString("hello")}));
}

TEST(Frame, ParseHttp2HeaderFramePadded) {

  EXPECT_EQ(
      ParseFrame(
           0, 0, 8,
           1,

          8,
           0, 0, 0, 1,
           2,
           'h', 'e', 'l', 'l', 'o',
           0, 0),
      Http2Frame(
          Http2HeaderFrame{1, false, false, SliceBufferFromString("hello")}));
  EXPECT_EQ(
      ParseFrame(
           0, 0, 10,
           1,

          32,
           0, 0, 0, 1,
           1, 2, 3, 4, 5,
           'h', 'e', 'l', 'l', 'o'),
      Http2Frame(
          Http2HeaderFrame{1, false, false, SliceBufferFromString("hello")}));
  EXPECT_EQ(
      ParseFrame(
           0, 0, 13,
           1,

          40,
           0, 0, 0, 1,
           2, 1, 2, 3, 4, 5,
           'h', 'e', 'l', 'l', 'o',
           1, 2),
      Http2Frame(
          Http2HeaderFrame{1, false, false, SliceBufferFromString("hello")}));
}

TEST(Frame, UnknownIgnored) {

  EXPECT_EQ(ParseFrame( 0, 0, 10,
                        77,
                        0,
                        0, 0, 0, 1,
                        1, 2, 3, 4, 5, 6, 7, 8, 9, 10),
            Http2Frame(Http2UnknownFrame{}));

  EXPECT_EQ(ParseFrame( 0, 0, 10,
                        2,
                        0xff,
                        0, 0, 0, 1,
                        1, 2, 3, 4, 5, 6, 7, 8, 9, 10),
            Http2Frame(Http2UnknownFrame{}));
}

TEST(Frame, ParseRejectsPushPromise) {
  EXPECT_THAT(
      ValidateFrame( 0, 0, 10,
                     5,
                     0,
                     0, 0, 0, 1,
                     1, 2, 3, 4, 5, 6, 7, 8, 9, 10),
      Http2StatusIs(
          Http2Status::Http2ErrorType::kConnectionError,
          Http2ErrorCode::kProtocolError,
          absl::StrCat(RFC9113::kNoPushPromise,
                       "{PUSH_PROMISE: flags=0, stream_id=1, length=10}")));
}

TEST(Frame, ParseRejectsDataFrame) {
  EXPECT_THAT(
      ValidateFrame( 0, 0, 0,
                     0,

                    0,
                     0, 0, 0, 0),
      Http2StatusIs(Http2Status::Http2ErrorType::kConnectionError,
                    Http2ErrorCode::kProtocolError,
                    absl::StrCat(RFC9113::kDataStreamIdMustBeNonZero,
                                 "{DATA: flags=0, stream_id=0, length=0}")));
  EXPECT_THAT(
      ValidateFrame( 0, 0, 0,
                     0,

                    0,
                     0, 0, 0, 2),
      Http2StatusIs(Http2Status::Http2ErrorType::kConnectionError,
                    Http2ErrorCode::kProtocolError,
                    absl::StrCat(RFC9113::kStreamIdMustBeOdd,
                                 "{DATA: flags=0, stream_id=2, length=0}")));

  EXPECT_THAT(
      ValidateFrame( 0, 0, 9,
                     0,

                    9,
                     0, 0, 0, 1,
                     0xff,
                     'h', 'e', 'l', 'l', 'o',
                     0, 0, 0),
      Http2StatusIs(Http2Status::Http2ErrorType::kConnectionError,
                    Http2ErrorCode::kProtocolError,
                    absl::StrCat(RFC9113::kPaddingLengthLargerThanFrameLength,
                                 "{DATA: flags=9, stream_id=1, length=9}")));
}

TEST(Frame, ParseRejectsHeaderFrame) {
  EXPECT_THAT(
      ValidateFrame( 0, 0, 0,
                     1,

                    0,
                     0, 0, 0, 0),
      Http2StatusIs(Http2Status::Http2ErrorType::kConnectionError,
                    Http2ErrorCode::kProtocolError,
                    absl::StrCat(RFC9113::kHeaderStreamIdMustBeNonZero,
                                 "{HEADER: flags=0, stream_id=0, length=0}")));
  EXPECT_THAT(
      ValidateFrame( 0, 0, 0,
                     1,

                    0,
                     0, 0, 0, 2),
      Http2StatusIs(Http2Status::Http2ErrorType::kConnectionError,
                    Http2ErrorCode::kProtocolError,
                    absl::StrCat(RFC9113::kStreamIdMustBeOdd,
                                 "{HEADER: flags=0, stream_id=2, length=0}")));

}

TEST(Frame, ParseRejectsContinuationFrame) {
  EXPECT_THAT(
      ValidateFrame(
           0, 0, 0,
           9,
           0,
           0, 0, 0, 0),
      Http2StatusIs(
          Http2Status::Http2ErrorType::kConnectionError,
          Http2ErrorCode::kProtocolError,
          absl::StrCat(RFC9113::kContinuationStreamIdMustBeNonZero,
                       "{CONTINUATION: flags=0, stream_id=0, length=0}")));
  EXPECT_THAT(
      ValidateFrame(
           0, 0, 0,
           9,
           0,
           0, 0, 0, 2),
      Http2StatusIs(
          Http2Status::Http2ErrorType::kConnectionError,
          Http2ErrorCode::kProtocolError,
          absl::StrCat(RFC9113::kStreamIdMustBeOdd,
                       "{CONTINUATION: flags=0, stream_id=2, length=0}")));
}

TEST(Frame, ParseRejectsRstStreamFrame) {
  EXPECT_THAT(
      ValidateFrame( 0, 0, 3,
                     3,
                     0,
                     0, 0, 0, 1,
                     100, 100, 100),
      Http2StatusIs(
          Http2Status::Http2ErrorType::kConnectionError,
          Http2ErrorCode::kFrameSizeError,
          absl::StrCat(RFC9113::kRstStreamLength4,
                       "{RST_STREAM: flags=0, stream_id=1, length=3}")));
  EXPECT_THAT(
      ValidateFrame( 0, 0, 4,
                     3,
                     0,
                     0, 0, 0, 0,
                     100, 100, 100, 100),
      Http2StatusIs(
          Http2Status::Http2ErrorType::kConnectionError,
          Http2ErrorCode::kProtocolError,
          absl::StrCat(RFC9113::kRstStreamStreamIdMustBeNonZero,
                       "{RST_STREAM: flags=0, stream_id=0, length=4}")));
  EXPECT_THAT(
      ValidateFrame( 0, 0, 4,
                     3,
                     0,
                     0, 0, 0, 2,
                     100, 100, 100, 100),
      Http2StatusIs(
          Http2Status::Http2ErrorType::kConnectionError,
          Http2ErrorCode::kProtocolError,
          absl::StrCat(RFC9113::kStreamIdMustBeOdd,
                       "{RST_STREAM: flags=0, stream_id=2, length=4}")));
}

TEST(Frame, ParseRejectsSettingsFrame) {
  EXPECT_THAT(ValidateFrame( 0, 0, 1,
                             4,
                             1,
                             0, 0, 0, 0,
                             1),
              Http2StatusIs(
                  Http2Status::Http2ErrorType::kConnectionError,
                  Http2ErrorCode::kFrameSizeError,
                  absl::StrCat(RFC9113::kSettingsLength0,
                               "{SETTINGS: flags=1, stream_id=0, length=1}")));
  EXPECT_THAT(ValidateFrame( 0, 0, 1,
                             4,
                             0,
                             0, 0, 0, 0,
                             1),
              Http2StatusIs(
                  Http2Status::Http2ErrorType::kConnectionError,
                  Http2ErrorCode::kFrameSizeError,
                  absl::StrCat(RFC9113::kSettingsLength6x,
                               "{SETTINGS: flags=0, stream_id=0, length=1}")));
  EXPECT_THAT(ValidateFrame( 0, 0, 2,
                             4,
                             0,
                             0, 0, 0, 0,
                             1, 1),
              Http2StatusIs(
                  Http2Status::Http2ErrorType::kConnectionError,
                  Http2ErrorCode::kFrameSizeError,
                  absl::StrCat(RFC9113::kSettingsLength6x,
                               "{SETTINGS: flags=0, stream_id=0, length=2}")));
  EXPECT_THAT(ValidateFrame( 0, 0, 3,
                             4,
                             0,
                             0, 0, 0, 0,
                             1, 1, 1),
              Http2StatusIs(
                  Http2Status::Http2ErrorType::kConnectionError,
                  Http2ErrorCode::kFrameSizeError,
                  absl::StrCat(RFC9113::kSettingsLength6x,
                               "{SETTINGS: flags=0, stream_id=0, length=3}")));
  EXPECT_THAT(ValidateFrame( 0, 0, 4,
                             4,
                             0,
                             0, 0, 0, 0,
                             1, 1, 1, 1),
              Http2StatusIs(
                  Http2Status::Http2ErrorType::kConnectionError,
                  Http2ErrorCode::kFrameSizeError,
                  absl::StrCat(RFC9113::kSettingsLength6x,
                               "{SETTINGS: flags=0, stream_id=0, length=4}")));
  EXPECT_THAT(ValidateFrame( 0, 0, 5,
                             4,
                             0,
                             0, 0, 0, 0,
                             1, 1, 1, 1, 1),
              Http2StatusIs(
                  Http2Status::Http2ErrorType::kConnectionError,
                  Http2ErrorCode::kFrameSizeError,
                  absl::StrCat(RFC9113::kSettingsLength6x,
                               "{SETTINGS: flags=0, stream_id=0, length=5}")));
  EXPECT_THAT(ValidateFrame( 0, 0, 7,
                             4,
                             0,
                             0, 0, 0, 0,
                             1, 1, 1, 1, 1, 1, 1),
              Http2StatusIs(
                  Http2Status::Http2ErrorType::kConnectionError,
                  Http2ErrorCode::kFrameSizeError,
                  absl::StrCat(RFC9113::kSettingsLength6x,
                               "{SETTINGS: flags=0, stream_id=0, length=7}")));
  EXPECT_THAT(ValidateFrame( 0, 0, 0,
                             4,
                             0,
                             0, 0, 0, 1),
              Http2StatusIs(
                  Http2Status::Http2ErrorType::kConnectionError,
                  Http2ErrorCode::kProtocolError,
                  absl::StrCat(RFC9113::kSettingsStreamIdMustBeZero,
                               "{SETTINGS: flags=0, stream_id=1, length=0}")));
}

TEST(Frame, ParseRejectsPingFrame) {
  EXPECT_THAT(
      ValidateFrame( 0, 0, 0,
                     6,
                     0,
                     0, 0, 0, 0),
      Http2StatusIs(Http2Status::Http2ErrorType::kConnectionError,
                    Http2ErrorCode::kFrameSizeError,
                    absl::StrCat(RFC9113::kPingLength8,
                                 "{PING: flags=0, stream_id=0, length=0}")));
  EXPECT_THAT(
      ValidateFrame( 0, 0, 8,
                     6,
                     0,
                     0, 0, 0, 1,
                     1, 2, 3, 4, 5, 6, 7, 8),
      Http2StatusIs(Http2Status::Http2ErrorType::kConnectionError,
                    Http2ErrorCode::kProtocolError,
                    absl::StrCat(RFC9113::kPingStreamIdMustBeZero,
                                 "{PING: flags=0, stream_id=1, length=8}")));
}

TEST(Frame, ParseRejectsGoawayFrame) {
  EXPECT_THAT(
      ValidateFrame( 0, 0, 0,
                     7,
                     0,
                     0, 0, 0, 0),
      Http2StatusIs(Http2Status::Http2ErrorType::kConnectionError,
                    Http2ErrorCode::kFrameSizeError,
                    absl::StrCat(RFC9113::kGoAwayLength8,
                                 "{GOAWAY: flags=0, stream_id=0, length=0}")));
  EXPECT_THAT(
      ValidateFrame( 0, 0, 1,
                     7,
                     0,
                     0, 0, 0, 0,
                     1),
      Http2StatusIs(Http2Status::Http2ErrorType::kConnectionError,
                    Http2ErrorCode::kFrameSizeError,
                    absl::StrCat(RFC9113::kGoAwayLength8,
                                 "{GOAWAY: flags=0, stream_id=0, length=1}")));
  EXPECT_THAT(
      ValidateFrame( 0, 0, 2,
                     7,
                     0,
                     0, 0, 0, 0,
                     1, 1),
      Http2StatusIs(Http2Status::Http2ErrorType::kConnectionError,
                    Http2ErrorCode::kFrameSizeError,
                    absl::StrCat(RFC9113::kGoAwayLength8,
                                 "{GOAWAY: flags=0, stream_id=0, length=2}")));
  EXPECT_THAT(
      ValidateFrame( 0, 0, 3,
                     7,
                     0,
                     0, 0, 0, 0,
                     1, 1, 1),
      Http2StatusIs(Http2Status::Http2ErrorType::kConnectionError,
                    Http2ErrorCode::kFrameSizeError,
                    absl::StrCat(RFC9113::kGoAwayLength8,
                                 "{GOAWAY: flags=0, stream_id=0, length=3}")));
  EXPECT_THAT(
      ValidateFrame( 0, 0, 4,
                     7,
                     0,
                     0, 0, 0, 0,
                     1, 1, 1, 1),
      Http2StatusIs(Http2Status::Http2ErrorType::kConnectionError,
                    Http2ErrorCode::kFrameSizeError,
                    absl::StrCat(RFC9113::kGoAwayLength8,
                                 "{GOAWAY: flags=0, stream_id=0, length=4}")));
  EXPECT_THAT(
      ValidateFrame( 0, 0, 5,
                     7,
                     0,
                     0, 0, 0, 0,
                     1, 1, 1, 1, 1),
      Http2StatusIs(Http2Status::Http2ErrorType::kConnectionError,
                    Http2ErrorCode::kFrameSizeError,
                    absl::StrCat(RFC9113::kGoAwayLength8,
                                 "{GOAWAY: flags=0, stream_id=0, length=5}")));
  EXPECT_THAT(
      ValidateFrame( 0, 0, 6,
                     7,
                     0,
                     0, 0, 0, 0,
                     1, 1, 1, 1, 1, 1),
      Http2StatusIs(Http2Status::Http2ErrorType::kConnectionError,
                    Http2ErrorCode::kFrameSizeError,
                    absl::StrCat(RFC9113::kGoAwayLength8,
                                 "{GOAWAY: flags=0, stream_id=0, length=6}")));
  EXPECT_THAT(
      ValidateFrame( 0, 0, 7,
                     7,
                     0,
                     0, 0, 0, 0,
                     1, 1, 1, 1, 1, 1, 1),
      Http2StatusIs(Http2Status::Http2ErrorType::kConnectionError,
                    Http2ErrorCode::kFrameSizeError,
                    absl::StrCat(RFC9113::kGoAwayLength8,
                                 "{GOAWAY: flags=0, stream_id=0, length=7}")));
  EXPECT_THAT(
      ValidateFrame( 0, 0, 8,
                     7,
                     0,
                     0, 0, 0, 1,
                     1, 2, 3, 4, 5, 6, 7, 8),
      Http2StatusIs(Http2Status::Http2ErrorType::kConnectionError,
                    Http2ErrorCode::kProtocolError,
                    absl::StrCat(RFC9113::kGoAwayStreamIdMustBeZero,
                                 "{GOAWAY: flags=0, stream_id=1, length=8}")));
}

TEST(Frame, ParseRejectsWindowUpdateFrame) {
  EXPECT_THAT(
      ValidateFrame( 0, 0, 0,
                     8,
                     0,
                     0, 0, 0, 0),
      Http2StatusIs(
          Http2Status::Http2ErrorType::kConnectionError,
          Http2ErrorCode::kFrameSizeError,
          absl::StrCat(RFC9113::kWindowUpdateLength4,
                       "{WINDOW_UPDATE: flags=0, stream_id=0, length=0}")));
  EXPECT_THAT(
      ValidateFrame( 0, 0, 1,
                     8,
                     0,
                     0, 0, 0, 0,
                     1),
      Http2StatusIs(
          Http2Status::Http2ErrorType::kConnectionError,
          Http2ErrorCode::kFrameSizeError,
          absl::StrCat(RFC9113::kWindowUpdateLength4,
                       "{WINDOW_UPDATE: flags=0, stream_id=0, length=1}")));
  EXPECT_THAT(
      ValidateFrame( 0, 0, 2,
                     8,
                     0,
                     0, 0, 0, 0,
                     1, 1),
      Http2StatusIs(
          Http2Status::Http2ErrorType::kConnectionError,
          Http2ErrorCode::kFrameSizeError,
          absl::StrCat(RFC9113::kWindowUpdateLength4,
                       "{WINDOW_UPDATE: flags=0, stream_id=0, length=2}")));
  EXPECT_THAT(
      ValidateFrame( 0, 0, 3,
                     8,
                     0,
                     0, 0, 0, 0,
                     1, 1, 1),
      Http2StatusIs(
          Http2Status::Http2ErrorType::kConnectionError,
          Http2ErrorCode::kFrameSizeError,
          absl::StrCat(RFC9113::kWindowUpdateLength4,
                       "{WINDOW_UPDATE: flags=0, stream_id=0, length=3}")));
  EXPECT_THAT(
      ValidateFrame( 0, 0, 5,
                     8,
                     0,
                     0, 0, 0, 0,
                     1, 1, 1, 1, 1),
      Http2StatusIs(
          Http2Status::Http2ErrorType::kConnectionError,
          Http2ErrorCode::kFrameSizeError,
          absl::StrCat(RFC9113::kWindowUpdateLength4,
                       "{WINDOW_UPDATE: flags=0, stream_id=0, length=5}")));
  EXPECT_THAT(
      ValidateFrame( 0, 0, 4,
                     8,
                     1,
                     0, 0, 0, 4,
                     1, 1, 1, 1),
      Http2StatusIs(
          Http2Status::Http2ErrorType::kConnectionError,
          Http2ErrorCode::kProtocolError,
          absl::StrCat(RFC9113::kStreamIdMustBeOdd,
                       "{WINDOW_UPDATE: flags=1, stream_id=4, length=4}")));
}

TEST(Frame, ParseRejectsWindowUpdateFrameZeroIncrement) {

  EXPECT_THAT(
      ValidateFrame( 0, 0, 4,
                     8,
                     0xff,
                     0, 0, 0, 0,
                     0, 0, 0, 0),
      Http2StatusIs(
          Http2Status::Http2ErrorType::kConnectionError,
          Http2ErrorCode::kProtocolError,
          absl::StrCat(RFC9113::kWindowSizeIncrement,
                       "{WINDOW_UPDATE: flags=255, stream_id=0, length=4}")));
  EXPECT_THAT(
      ValidateFrame( 0, 0, 4,
                     8,
                     0,
                     0x7f, 0xff, 0xff, 0xff,
                     0, 0, 0, 0),
      Http2StatusIs(
          Http2Status::Http2ErrorType::kStreamError,
          Http2ErrorCode::kProtocolError,
          absl::StrCat(
              RFC9113::kWindowSizeIncrement,
              "{WINDOW_UPDATE: flags=0, stream_id=2147483647, length=4}")));
}

TEST(Frame, GrpcHeaderTest) {
  constexpr uint8_t kFlags = 15;
  constexpr uint32_t kLength = 1111111;

  SliceBuffer payload;
  EXPECT_EQ(payload.Length(), 0);

  AppendGrpcHeaderToSliceBuffer(payload, kFlags, kLength);
  EXPECT_EQ(payload.Length(), kGrpcHeaderSizeInBytes);

  GrpcMessageHeader header = ExtractGrpcHeader(payload);
  EXPECT_EQ(payload.Length(), kGrpcHeaderSizeInBytes);
  EXPECT_EQ(header.flags, kFlags);
  EXPECT_EQ(header.length, kLength);
}

}
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
