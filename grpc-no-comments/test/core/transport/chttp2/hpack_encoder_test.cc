
// Copyright 2015 gRPC authors.

#include "src/core/ext/transport/chttp2/transport/hpack_encoder.h"

#include <grpc/event_engine/memory_allocator.h>
#include <grpc/slice_buffer.h>
#include <stdlib.h>
#include <string.h>

#include <memory>
#include <string>

#include "absl/log/log.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "src/core/ext/transport/chttp2/transport/legacy_frame.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/resource_quota/arena.h"
#include "src/core/lib/resource_quota/memory_quota.h"
#include "src/core/lib/resource_quota/resource_quota.h"
#include "src/core/util/ref_counted_ptr.h"
#include "test/core/test_util/parse_hexstring.h"
#include "test/core/test_util/slice_splitter.h"
#include "test/core/test_util/test_config.h"

grpc_core::HPackCompressor* g_compressor;
grpc_core::Http2ZTraceCollector* g_ztrace_collector =
    new grpc_core::Http2ZTraceCollector();

typedef struct {
  bool eof;
  bool use_true_binary_metadata;
} verify_params;

static void verify_frames(grpc_slice_buffer& output, bool header_is_eof) {

  uint8_t type = 0xff, flags = 0xff;
  size_t i, merged_length, frame_size;
  bool first_frame = false;
  bool in_header = false;
  bool end_header = false;
  bool is_closed = false;
  for (i = 0; i < output.count;) {
    first_frame = i == 0;
    grpc_slice* slice = &output.slices[i++];

    uint8_t* p = GRPC_SLICE_START_PTR(*slice);
    frame_size = 0;
    frame_size |= static_cast<uint32_t>(p[0]) << 16;
    frame_size |= static_cast<uint32_t>(p[1]) << 8;
    frame_size |= static_cast<uint32_t>(p[2]);
    type = p[3];
    flags = p[4];

    merged_length = GRPC_SLICE_LENGTH(*slice);
    while (merged_length < frame_size + 9) {
      grpc_slice* slice = &output.slices[i++];
      merged_length += GRPC_SLICE_LENGTH(*slice);
    }

    if (first_frame && type != GRPC_CHTTP2_FRAME_HEADER) {
      LOG(ERROR) << "expected first frame to be of type header";
      LOG(ERROR) << "EXPECT: " << GRPC_CHTTP2_FRAME_HEADER;
      LOG(ERROR) << "GOT:    " << type;
      EXPECT_TRUE(false);
    } else if (first_frame && header_is_eof &&
               !(flags & GRPC_CHTTP2_DATA_FLAG_END_STREAM)) {
      LOG(ERROR) << "missing END_STREAM flag in HEADER frame";
      EXPECT_TRUE(false);
    }
    if (is_closed &&
        (type == GRPC_CHTTP2_FRAME_DATA || type == GRPC_CHTTP2_FRAME_HEADER)) {
      LOG(ERROR)
          << "stream is closed; new frame headers and data are not allowed";
      EXPECT_TRUE(false);
    }
    if (end_header && (type == GRPC_CHTTP2_FRAME_HEADER ||
                       type == GRPC_CHTTP2_FRAME_CONTINUATION)) {
      LOG(ERROR)
          << "frame header is ended; new headers and continuations are not "
             "allowed";
      EXPECT_TRUE(false);
    }
    if (in_header &&
        (type == GRPC_CHTTP2_FRAME_DATA || type == GRPC_CHTTP2_FRAME_HEADER)) {
      LOG(ERROR)
          << "parsing frame header; new headers and data are not allowed";
      EXPECT_TRUE(false);
    }
    if (flags & ~(GRPC_CHTTP2_DATA_FLAG_END_STREAM |
                  GRPC_CHTTP2_DATA_FLAG_END_HEADERS)) {
      LOG(ERROR) << "unexpected frame flags: " << flags;
      EXPECT_TRUE(false);
    }

    if (flags & GRPC_CHTTP2_DATA_FLAG_END_HEADERS) {
      in_header = false;
      end_header = true;
    } else if (type == GRPC_CHTTP2_DATA_FLAG_END_HEADERS) {
      in_header = true;
    }
    if (flags & GRPC_CHTTP2_DATA_FLAG_END_STREAM) {
      is_closed = true;
      if (type == GRPC_CHTTP2_FRAME_CONTINUATION) {
        LOG(ERROR) << "unexpected END_STREAM flag in CONTINUATION frame";
        EXPECT_TRUE(false);
      }
    }
  }
}

static void CrashOnAppendError(absl::string_view, const grpc_core::Slice&) {
  abort();
}

namespace grpc_core {

class FakeCallTracer final : public CallTracerInterface {
 public:
  void RecordIncomingBytes(
      const TransportByteSize& transport_byte_size) override {}
  void RecordOutgoingBytes(
      const TransportByteSize& transport_byte_size) override {}
  void RecordSendInitialMetadata(
      grpc_metadata_batch* send_initial_metadata) override {}
  void RecordSendTrailingMetadata(
      grpc_metadata_batch* send_trailing_metadata) override {}
  void RecordSendMessage(const Message& send_message) override {}
  void RecordSendCompressedMessage(
      const Message& send_compressed_message) override {}
  void RecordReceivedInitialMetadata(
      grpc_metadata_batch* recv_initial_metadata) override {}
  void RecordReceivedMessage(const Message& recv_message) override {}
  void RecordReceivedDecompressedMessage(
      const Message& recv_decompressed_message) override {}
  void RecordCancel(grpc_error_handle cancel_error) override {}
  std::shared_ptr<TcpCallTracer> StartNewTcpTrace() override { return nullptr; }
  void RecordAnnotation(absl::string_view annotation) override {}
  void RecordAnnotation(const Annotation& annotation) override {}
  std::string TraceId() override { return ""; }
  std::string SpanId() override { return ""; }
  bool IsSampled() override { return false; }
};

}

grpc_slice EncodeHeaderIntoBytes(
    bool is_eof,
    const std::vector<std::pair<std::string, std::string>>& header_fields) {
  std::unique_ptr<grpc_core::HPackCompressor> compressor =
      std::make_unique<grpc_core::HPackCompressor>();
  grpc_metadata_batch b;

  for (const auto& field : header_fields) {
    b.Append(field.first,
             grpc_core::Slice::FromStaticString(field.second.c_str()),
             CrashOnAppendError);
  }

  grpc_core::FakeCallTracer call_tracer;
  grpc_core::HPackCompressor::EncodeHeaderOptions hopt{
      0xdeadbeef,
      is_eof,
      false,
      16384,
      &call_tracer, g_ztrace_collector};
  grpc_slice_buffer output;
  grpc_slice_buffer_init(&output);

  compressor->EncodeHeaders(hopt, b, &output);
  verify_frames(output, is_eof);

  grpc_slice ret = grpc_slice_merge(output.slices, output.count);
  grpc_slice_buffer_destroy(&output);

  return ret;
}

static void verify(
    bool is_eof, const char* expected,
    const std::vector<std::pair<std::string, std::string>>& header_fields) {
  const grpc_core::Slice merged(EncodeHeaderIntoBytes(is_eof, header_fields));
  const grpc_core::Slice expect(grpc_core::ParseHexstring(expected));

  EXPECT_EQ(merged, expect);
}

TEST(HpackEncoderTest, TestBasicHeaders) {
  grpc_core::ExecCtx exec_ctx;
  g_compressor = new grpc_core::HPackCompressor();

  verify(false, "000005 0104 deadbeef 00 0161 0161", {{"a", "a"}});
  verify(false, "00000a 0104 deadbeef 00 0161 0161 00 0162 0163",
         {{"a", "a"}, {"b", "c"}});

  delete g_compressor;
}

MATCHER(HasLiteralHeaderFieldNewNameFlagIncrementalIndexing, "") {
  constexpr size_t kHttp2FrameHeaderSize = 9u;

  constexpr uint8_t kLiteralHeaderFieldNewNameFlagIncrementalIndexing = 0x40;
  return (GRPC_SLICE_START_PTR(arg)[kHttp2FrameHeaderSize] ==
          kLiteralHeaderFieldNewNameFlagIncrementalIndexing);
}

MATCHER(HasLiteralHeaderFieldNewNameFlagNoIndexing, "") {
  constexpr size_t kHttp2FrameHeaderSize = 9u;

  constexpr uint8_t kLiteralHeaderFieldNewNameFlagNoIndexing = 0x00;
  return (GRPC_SLICE_START_PTR(arg)[kHttp2FrameHeaderSize] ==
          kLiteralHeaderFieldNewNameFlagNoIndexing);
}

TEST(HpackEncoderTest, GrpcTraceBinMetadataIndexing) {
  grpc_core::ExecCtx exec_ctx;

  const grpc_slice encoded_header = EncodeHeaderIntoBytes(
      false, {{grpc_core::GrpcTraceBinMetadata::key().data(), "value"}});
  EXPECT_THAT(encoded_header,
              HasLiteralHeaderFieldNewNameFlagIncrementalIndexing());

  grpc_slice_unref(encoded_header);
}

TEST(HpackEncoderTest, GrpcTraceBinMetadataNoIndexing) {
  grpc_core::ExecCtx exec_ctx;

  constexpr size_t long_value_size = 70000u;
  const grpc_slice encoded_header = EncodeHeaderIntoBytes(
      false, {{grpc_core::GrpcTraceBinMetadata::key().data(),
               std::string(long_value_size, 'a')}});
  EXPECT_THAT(encoded_header, HasLiteralHeaderFieldNewNameFlagNoIndexing());

  grpc_slice_unref(encoded_header);
}

TEST(HpackEncoderTest, TestGrpcTagsBinMetadataIndexing) {
  grpc_core::ExecCtx exec_ctx;

  const grpc_slice encoded_header = EncodeHeaderIntoBytes(
      false,
      {{grpc_core::GrpcTagsBinMetadata::key().data(), std::string("value")}});
  EXPECT_THAT(encoded_header,
              HasLiteralHeaderFieldNewNameFlagIncrementalIndexing());

  grpc_slice_unref(encoded_header);
}

TEST(HpackEncoderTest, TestGrpcTagsBinMetadataNoIndexing) {
  grpc_core::ExecCtx exec_ctx;

  constexpr size_t long_value_size = 70000u;
  const grpc_slice encoded_header = EncodeHeaderIntoBytes(
      false, {{grpc_core::GrpcTagsBinMetadata::key().data(),
               std::string(long_value_size, 'a')}});
  EXPECT_THAT(encoded_header, HasLiteralHeaderFieldNewNameFlagNoIndexing());

  grpc_slice_unref(encoded_header);
}

TEST(HpackEncoderTest, UserAgentMetadataIndexing) {
  grpc_core::ExecCtx exec_ctx;

  const grpc_slice encoded_header = EncodeHeaderIntoBytes(
      false, {{grpc_core::UserAgentMetadata::key().data(), "value"}});
  EXPECT_THAT(encoded_header,
              HasLiteralHeaderFieldNewNameFlagIncrementalIndexing());

  grpc_slice_unref(encoded_header);
}

TEST(HpackEncoderTest, UserAgentMetadataNoIndexing) {
  grpc_core::ExecCtx exec_ctx;

  constexpr size_t long_value_size = 70000u;
  const grpc_slice encoded_header =
      EncodeHeaderIntoBytes(false, {{grpc_core::UserAgentMetadata::key().data(),
                                     std::string(long_value_size, 'a')}});
  EXPECT_THAT(encoded_header, HasLiteralHeaderFieldNewNameFlagNoIndexing());

  grpc_slice_unref(encoded_header);
}

static void verify_continuation_headers(const char* key, const char* value,
                                        bool is_eof) {
  grpc_core::MemoryAllocator memory_allocator =
      grpc_core::MemoryAllocator(grpc_core::ResourceQuota::Default()
                                     ->memory_quota()
                                     ->CreateMemoryAllocator("test"));
  grpc_slice_buffer output;
  grpc_metadata_batch b;
  b.Append(key, grpc_core::Slice::FromStaticString(value), CrashOnAppendError);
  grpc_slice_buffer_init(&output);

  grpc_core::FakeCallTracer call_tracer;
  grpc_core::HPackCompressor::EncodeHeaderOptions hopt = {
      0xdeadbeef,
      is_eof,
      false,
      150,
      &call_tracer, g_ztrace_collector};
  g_compressor->EncodeHeaders(hopt, b, &output);
  verify_frames(output, is_eof);
  grpc_slice_buffer_destroy(&output);
}

TEST(HpackEncoderTest, TestContinuationHeaders) {
  grpc_core::ExecCtx exec_ctx;
  g_compressor = new grpc_core::HPackCompressor();

  char value[200];
  memset(value, 'a', 200);
  value[199] = 0;
  verify_continuation_headers("key", value, true);

  char value2[400];
  memset(value2, 'b', 400);
  value2[399] = 0;
  verify_continuation_headers("key2", value2, true);

  delete g_compressor;
}

TEST(HpackEncoderTest, EncodeBinaryAsBase64) {
  grpc_metadata_batch b;

  b.Append("grpc-trace-bin",
           grpc_core::Slice::FromStaticString(
               "Base64, a tool\nTo encode binary data into "
               "text\nSo it can be shared."),
           CrashOnAppendError);
  grpc_core::FakeCallTracer call_tracer;
  grpc_slice_buffer output;
  grpc_slice_buffer_init(&output);
  grpc_core::HPackCompressor::EncodeHeaderOptions hopt = {
      0xdeadbeef,
      true,
      false,
      150,
      &call_tracer, g_ztrace_collector};
  grpc_core::HPackCompressor compressor;
  compressor.EncodeHeaders(hopt, b, &output);
  grpc_slice_buffer_destroy(&output);

  EXPECT_EQ(compressor.test_only_table_size(), 136);
}

TEST(HpackEncoderTest, EncodeBinaryAsTrueBinary) {
  grpc_metadata_batch b;

  b.Append("grpc-trace-bin",
           grpc_core::Slice::FromStaticString(
               "Base64, a tool\nTo encode binary data into "
               "text\nSo it can be shared."),
           CrashOnAppendError);
  grpc_core::FakeCallTracer call_tracer;
  grpc_slice_buffer output;
  grpc_slice_buffer_init(&output);
  grpc_core::HPackCompressor::EncodeHeaderOptions hopt = {
      0xdeadbeef,
      true,
      true,
      150,
      &call_tracer, g_ztrace_collector};
  grpc_core::HPackCompressor compressor;
  compressor.EncodeHeaders(hopt, b, &output);
  grpc_slice_buffer_destroy(&output);

  EXPECT_EQ(compressor.test_only_table_size(), 114);
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  grpc::testing::TestGrpcScope grpc_scope;
  return RUN_ALL_TESTS();
}
