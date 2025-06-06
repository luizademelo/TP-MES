
// Copyright 2015 gRPC authors.

#include <benchmark/benchmark.h>
#include <grpc/slice.h>
#include <grpc/support/alloc.h>
#include <string.h>

#include <memory>
#include <sstream>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/random/random.h"
#include "src/core/call/metadata_batch.h"
#include "src/core/ext/transport/chttp2/transport/hpack_encoder.h"
#include "src/core/ext/transport/chttp2/transport/hpack_parser.h"
#include "src/core/lib/resource_quota/resource_quota.h"
#include "src/core/lib/slice/slice_internal.h"
#include "src/core/lib/slice/slice_string_helpers.h"
#include "src/core/lib/transport/timeout_encoding.h"
#include "src/core/util/crash.h"
#include "src/core/util/time.h"
#include "test/core/test_util/test_config.h"
#include "test/cpp/microbenchmarks/helpers.h"
#include "test/cpp/util/test_config.h"

static grpc_slice MakeSlice(const std::vector<uint8_t>& bytes) {
  grpc_slice s = grpc_slice_malloc(bytes.size());
  uint8_t* p = GRPC_SLICE_START_PTR(s);
  for (auto b : bytes) {
    *p++ = b;
  }
  return s;
}

namespace grpc_core {

static Http2ZTraceCollector* ztrace_collector = new Http2ZTraceCollector();

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

static void BM_HpackEncoderInitDestroy(benchmark::State& state) {
  grpc_core::ExecCtx exec_ctx;
  for (auto _ : state) {
    grpc_core::HPackCompressor c;
    grpc_core::ExecCtx::Get()->Flush();
  }
}
BENCHMARK(BM_HpackEncoderInitDestroy);

static void BM_HpackEncoderEncodeDeadline(benchmark::State& state) {
  grpc_core::ExecCtx exec_ctx;
  grpc_core::Timestamp saved_now = grpc_core::Timestamp::Now();

  grpc_core::MemoryAllocator memory_allocator =
      grpc_core::MemoryAllocator(grpc_core::ResourceQuota::Default()
                                     ->memory_quota()
                                     ->CreateMemoryAllocator("test"));
  grpc_metadata_batch b;
  b.Set(grpc_core::GrpcTimeoutMetadata(),
        saved_now + grpc_core::Duration::Seconds(30));

  grpc_core::HPackCompressor c;
  grpc_core::FakeCallTracer call_tracer;
  grpc_slice_buffer outbuf;
  grpc_slice_buffer_init(&outbuf);
  while (state.KeepRunning()) {
    c.EncodeHeaders(
        grpc_core::HPackCompressor::EncodeHeaderOptions{
            static_cast<uint32_t>(state.iterations()), true, false,
            size_t{1024}, &call_tracer, grpc_core::ztrace_collector},
        b, &outbuf);
    grpc_slice_buffer_reset_and_unref(&outbuf);
    grpc_core::ExecCtx::Get()->Flush();
  }
  grpc_slice_buffer_destroy(&outbuf);
}
BENCHMARK(BM_HpackEncoderEncodeDeadline);

template <class Fixture>
static void BM_HpackEncoderEncodeHeader(benchmark::State& state) {
  grpc_core::ExecCtx exec_ctx;
  static bool logged_representative_output = false;

  grpc_metadata_batch b;
  Fixture::Prepare(&b);

  grpc_core::HPackCompressor c;
  grpc_core::FakeCallTracer call_tracer;
  grpc_slice_buffer outbuf;
  grpc_slice_buffer_init(&outbuf);
  while (state.KeepRunning()) {
    static constexpr int kEnsureMaxFrameAtLeast = 2;
    c.EncodeHeaders(
        grpc_core::HPackCompressor::EncodeHeaderOptions{
            static_cast<uint32_t>(state.iterations()), state.range(0) != 0,
            Fixture::kEnableTrueBinary,
            static_cast<size_t>(state.range(1) + kEnsureMaxFrameAtLeast),
            &call_tracer, grpc_core::ztrace_collector},
        b, &outbuf);
    if (!logged_representative_output && state.iterations() > 3) {
      logged_representative_output = true;
      for (size_t i = 0; i < outbuf.count; i++) {
        char* s = grpc_dump_slice(outbuf.slices[i], GPR_DUMP_HEX);
        VLOG(2) << i << ": " << s;
        gpr_free(s);
      }
    }
    grpc_slice_buffer_reset_and_unref(&outbuf);
    grpc_core::ExecCtx::Get()->Flush();
  }
  grpc_slice_buffer_destroy(&outbuf);
}

namespace hpack_encoder_fixtures {

class EmptyBatch {
 public:
  static constexpr bool kEnableTrueBinary = false;
  static void Prepare(grpc_metadata_batch*) {}
};

class SingleStaticElem {
 public:
  static constexpr bool kEnableTrueBinary = false;
  static void Prepare(grpc_metadata_batch* b) {
    b->Set(grpc_core::GrpcAcceptEncodingMetadata(),
           grpc_core::CompressionAlgorithmSet(
               {GRPC_COMPRESS_NONE, GRPC_COMPRESS_DEFLATE}));
  }
};

static void CrashOnAppendError(absl::string_view, const grpc_core::Slice&) {
  abort();
}

class SingleNonBinaryElem {
 public:
  static constexpr bool kEnableTrueBinary = false;
  static void Prepare(grpc_metadata_batch* b) {
    b->Append("abc", grpc_core::Slice::FromStaticString("def"),
              CrashOnAppendError);
  }
};

template <int kLength, bool kTrueBinary>
class SingleBinaryElem {
 public:
  static constexpr bool kEnableTrueBinary = kTrueBinary;
  static void Prepare(grpc_metadata_batch* b) {
    b->Append("abc-bin", MakeBytes(), CrashOnAppendError);
  }

 private:
  static grpc_core::Slice MakeBytes() {
    std::vector<char> v;
    v.reserve(kLength);
    for (int i = 0; i < kLength; i++) {
      v.push_back(static_cast<char>(rand()));
    }
    return grpc_core::Slice::FromCopiedBuffer(v);
  }
};

class RepresentativeClientInitialMetadata {
 public:
  static constexpr bool kEnableTrueBinary = true;
  static void Prepare(grpc_metadata_batch* b) {
    b->Set(grpc_core::HttpSchemeMetadata(),
           grpc_core::HttpSchemeMetadata::kHttp);
    b->Set(grpc_core::HttpMethodMetadata(),
           grpc_core::HttpMethodMetadata::kPost);
    b->Set(
        grpc_core::HttpPathMetadata(),
        grpc_core::Slice(grpc_core::StaticSlice::FromStaticString("/foo/bar")));
    b->Set(grpc_core::HttpAuthorityMetadata(),
           grpc_core::Slice(grpc_core::StaticSlice::FromStaticString(
               "foo.test.google.fr:1234")));
    b->Set(
        grpc_core::GrpcAcceptEncodingMetadata(),
        grpc_core::CompressionAlgorithmSet(
            {GRPC_COMPRESS_NONE, GRPC_COMPRESS_DEFLATE, GRPC_COMPRESS_GZIP}));
    b->Set(grpc_core::TeMetadata(), grpc_core::TeMetadata::kTrailers);
    b->Set(grpc_core::ContentTypeMetadata(),
           grpc_core::ContentTypeMetadata::kApplicationGrpc);
    b->Set(grpc_core::UserAgentMetadata(),
           grpc_core::Slice(grpc_core::StaticSlice::FromStaticString(
               "grpc-c/3.0.0-dev (linux; chttp2; green)")));
  }
};

class MoreRepresentativeClientInitialMetadata {
 public:
  static constexpr bool kEnableTrueBinary = true;
  static void Prepare(grpc_metadata_batch* b) {
    b->Set(grpc_core::HttpSchemeMetadata(),
           grpc_core::HttpSchemeMetadata::kHttp);
    b->Set(grpc_core::HttpMethodMetadata(),
           grpc_core::HttpMethodMetadata::kPost);
    b->Set(grpc_core::HttpPathMetadata(),
           grpc_core::Slice(grpc_core::StaticSlice::FromStaticString(
               "/grpc.test.FooService/BarMethod")));
    b->Set(grpc_core::HttpAuthorityMetadata(),
           grpc_core::Slice(grpc_core::StaticSlice::FromStaticString(
               "foo.test.google.fr:1234")));
    b->Set(grpc_core::GrpcTraceBinMetadata(),
           grpc_core::Slice(grpc_core::StaticSlice::FromStaticString(
               "\x00\x01\x02\x03\x04\x05\x06\x07\x08"
               "\x09\x0a\x0b\x0c\x0d\x0e\x0f"
               "\x10\x11\x12\x13\x14\x15\x16\x17\x18"
               "\x19\x1a\x1b\x1c\x1d\x1e\x1f"
               "\x20\x21\x22\x23\x24\x25\x26\x27\x28"
               "\x29\x2a\x2b\x2c\x2d\x2e\x2f"
               "\x30")));
    b->Set(grpc_core::GrpcTagsBinMetadata(),
           grpc_core::Slice(grpc_core::StaticSlice::FromStaticString(
               "\x00\x01\x02\x03\x04\x05\x06\x07\x08"
               "\x09\x0a\x0b\x0c\x0d\x0e\x0f"
               "\x10\x11\x12\x13")));
    b->Set(
        grpc_core::GrpcAcceptEncodingMetadata(),
        grpc_core::CompressionAlgorithmSet(
            {GRPC_COMPRESS_NONE, GRPC_COMPRESS_DEFLATE, GRPC_COMPRESS_GZIP}));
    b->Set(grpc_core::TeMetadata(), grpc_core::TeMetadata::kTrailers);
    b->Set(grpc_core::ContentTypeMetadata(),
           grpc_core::ContentTypeMetadata::kApplicationGrpc);
    b->Set(grpc_core::UserAgentMetadata(),
           grpc_core::Slice(grpc_core::StaticSlice::FromStaticString(
               "grpc-c/3.0.0-dev (linux; chttp2; green)")));
  }
};

class RepresentativeServerInitialMetadata {
 public:
  static constexpr bool kEnableTrueBinary = true;
  static void Prepare(grpc_metadata_batch* b) {
    b->Set(grpc_core::HttpStatusMetadata(), 200);
    b->Set(grpc_core::ContentTypeMetadata(),
           grpc_core::ContentTypeMetadata::kApplicationGrpc);
    b->Set(
        grpc_core::GrpcAcceptEncodingMetadata(),
        grpc_core::CompressionAlgorithmSet(
            {GRPC_COMPRESS_NONE, GRPC_COMPRESS_DEFLATE, GRPC_COMPRESS_GZIP}));
  }
};

class RepresentativeServerTrailingMetadata {
 public:
  static constexpr bool kEnableTrueBinary = true;
  static void Prepare(grpc_metadata_batch* b) {
    b->Set(grpc_core::GrpcStatusMetadata(), GRPC_STATUS_OK);
  }
};

BENCHMARK_TEMPLATE(BM_HpackEncoderEncodeHeader, EmptyBatch)->Args({0, 16384});

BENCHMARK_TEMPLATE(BM_HpackEncoderEncodeHeader, EmptyBatch)->Args({1, 16384});
BENCHMARK_TEMPLATE(BM_HpackEncoderEncodeHeader, SingleStaticElem)
    ->Args({0, 16384});
BENCHMARK_TEMPLATE(BM_HpackEncoderEncodeHeader, SingleNonBinaryElem)
    ->Args({0, 16384});
BENCHMARK_TEMPLATE(BM_HpackEncoderEncodeHeader, SingleBinaryElem<1, false>)
    ->Args({0, 16384});
BENCHMARK_TEMPLATE(BM_HpackEncoderEncodeHeader, SingleBinaryElem<3, false>)
    ->Args({0, 16384});
BENCHMARK_TEMPLATE(BM_HpackEncoderEncodeHeader, SingleBinaryElem<10, false>)
    ->Args({0, 16384});
BENCHMARK_TEMPLATE(BM_HpackEncoderEncodeHeader, SingleBinaryElem<31, false>)
    ->Args({0, 16384});
BENCHMARK_TEMPLATE(BM_HpackEncoderEncodeHeader, SingleBinaryElem<100, false>)
    ->Args({0, 16384});

BENCHMARK_TEMPLATE(BM_HpackEncoderEncodeHeader, SingleNonBinaryElem)
    ->Args({0, 1});

BENCHMARK_TEMPLATE(BM_HpackEncoderEncodeHeader,
                   RepresentativeClientInitialMetadata)
    ->Args({0, 16384});
BENCHMARK_TEMPLATE(BM_HpackEncoderEncodeHeader,
                   MoreRepresentativeClientInitialMetadata)
    ->Args({0, 16384});
BENCHMARK_TEMPLATE(BM_HpackEncoderEncodeHeader,
                   RepresentativeServerInitialMetadata)
    ->Args({0, 16384});
BENCHMARK_TEMPLATE(BM_HpackEncoderEncodeHeader,
                   RepresentativeServerTrailingMetadata)
    ->Args({1, 16384});

}

static void BM_HpackParserInitDestroy(benchmark::State& state) {
  grpc_core::ExecCtx exec_ctx;
  for (auto _ : state) {
    {
      grpc_core::HPackParser();
    }
    grpc_core::ExecCtx::Get()->Flush();
  }
}
BENCHMARK(BM_HpackParserInitDestroy);

template <class Fixture>
static void BM_HpackParserParseHeader(benchmark::State& state) {
  std::vector<grpc_slice> init_slices = Fixture::GetInitSlices();
  std::vector<grpc_slice> benchmark_slices = Fixture::GetBenchmarkSlices();
  grpc_core::ExecCtx exec_ctx;
  grpc_core::HPackParser p;
  grpc_core::ManualConstructor<grpc_metadata_batch> b;
  b.Init();
  p.BeginFrame(&*b, std::numeric_limits<uint32_t>::max(),
               std::numeric_limits<uint32_t>::max(),
               grpc_core::HPackParser::Boundary::None,
               grpc_core::HPackParser::Priority::None,
               grpc_core::HPackParser::LogInfo{
                   1, grpc_core::HPackParser::LogInfo::kHeaders, false});
  auto parse_vec = [&p, bitgen = absl::BitGen()](
                       const std::vector<grpc_slice>& slices) mutable {
    for (size_t i = 0; i < slices.size(); ++i) {
      auto error =
          p.Parse(slices[i], i == slices.size() - 1, absl::BitGenRef(bitgen),
                  nullptr);
      CHECK_OK(error);
    }
  };
  parse_vec(init_slices);
  while (state.KeepRunning()) {
    b->Clear();
    parse_vec(benchmark_slices);
    grpc_core::ExecCtx::Get()->Flush();
  }

  b.Destroy();
  for (auto slice : init_slices) grpc_slice_unref(slice);
  for (auto slice : benchmark_slices) grpc_slice_unref(slice);
}

namespace hpack_parser_fixtures {

template <class EncoderFixture>
class FromEncoderFixture {
 public:
  static std::vector<grpc_slice> GetInitSlices() { return Generate(0); }
  static std::vector<grpc_slice> GetBenchmarkSlices() { return Generate(1); }

 private:
  static std::vector<grpc_slice> Generate(int iteration) {
    grpc_core::ExecCtx exec_ctx;
    grpc_metadata_batch b;
    EncoderFixture::Prepare(&b);

    grpc_core::HPackCompressor c;
    grpc_core::FakeCallTracer call_tracer;
    std::vector<grpc_slice> out;
    bool done = false;
    int i = 0;
    while (!done) {
      grpc_slice_buffer outbuf;
      grpc_slice_buffer_init(&outbuf);
      c.EncodeHeaders(
          grpc_core::HPackCompressor::EncodeHeaderOptions{
              static_cast<uint32_t>(i), false,
              EncoderFixture::kEnableTrueBinary, 1024 * 1024, &call_tracer,
              grpc_core::ztrace_collector},
          b, &outbuf);
      if (i == iteration) {
        for (size_t s = 0; s < outbuf.count; s++) {
          out.push_back(grpc_slice_ref(outbuf.slices[s]));
        }
        done = true;
      }
      grpc_slice_buffer_reset_and_unref(&outbuf);
      grpc_core::ExecCtx::Get()->Flush();
      grpc_slice_buffer_destroy(&outbuf);
      i++;
    }

    CHECK(!out.empty());
    CHECK_GT(GRPC_SLICE_LENGTH(out[0]), 9);
    out[0] = grpc_slice_sub_no_ref(out[0], 9, GRPC_SLICE_LENGTH(out[0]));
    return out;
  }
};

class EmptyBatch {
 public:
  static std::vector<grpc_slice> GetInitSlices() { return {}; }
  static std::vector<grpc_slice> GetBenchmarkSlices() {
    return {MakeSlice({})};
  }
};

class IndexedSingleStaticElem {
 public:
  static std::vector<grpc_slice> GetInitSlices() {
    return {MakeSlice(
        {0x40, 0x07, ':', 's', 't', 'a', 't', 'u', 's', 0x03, '2', '0', '0'})};
  }
  static std::vector<grpc_slice> GetBenchmarkSlices() {
    return {MakeSlice({0xbe})};
  }
};

class AddIndexedSingleStaticElem {
 public:
  static std::vector<grpc_slice> GetInitSlices() { return {}; }
  static std::vector<grpc_slice> GetBenchmarkSlices() {
    return {MakeSlice(
        {0x40, 0x07, ':', 's', 't', 'a', 't', 'u', 's', 0x03, '2', '0', '0'})};
  }
};

class KeyIndexedSingleStaticElem {
 public:
  static std::vector<grpc_slice> GetInitSlices() {
    return {MakeSlice(
        {0x40, 0x07, ':', 's', 't', 'a', 't', 'u', 's', 0x03, '2', '0', '0'})};
  }
  static std::vector<grpc_slice> GetBenchmarkSlices() {
    return {MakeSlice({0x7e, 0x03, '4', '0', '4'})};
  }
};

class IndexedSingleInternedElem {
 public:
  static std::vector<grpc_slice> GetInitSlices() {
    return {MakeSlice({0x40, 0x03, 'a', 'b', 'c', 0x03, 'd', 'e', 'f'})};
  }
  static std::vector<grpc_slice> GetBenchmarkSlices() {
    return {MakeSlice({0xbe})};
  }
};

class AddIndexedSingleInternedElem {
 public:
  static std::vector<grpc_slice> GetInitSlices() { return {}; }
  static std::vector<grpc_slice> GetBenchmarkSlices() {
    return {MakeSlice({0x40, 0x03, 'a', 'b', 'c', 0x03, 'd', 'e', 'f'})};
  }
};

class KeyIndexedSingleInternedElem {
 public:
  static std::vector<grpc_slice> GetInitSlices() {
    return {MakeSlice({0x40, 0x03, 'a', 'b', 'c', 0x03, 'd', 'e', 'f'})};
  }
  static std::vector<grpc_slice> GetBenchmarkSlices() {
    return {MakeSlice({0x7e, 0x03, 'g', 'h', 'i'})};
  }
};

class NonIndexedElem {
 public:
  static std::vector<grpc_slice> GetInitSlices() { return {}; }
  static std::vector<grpc_slice> GetBenchmarkSlices() {
    return {MakeSlice({0x00, 0x03, 'a', 'b', 'c', 0x03, 'd', 'e', 'f'})};
  }
};

template <int kLength, bool kTrueBinary>
class NonIndexedBinaryElem;

template <int kLength>
class NonIndexedBinaryElem<kLength, true> {
 public:
  static std::vector<grpc_slice> GetInitSlices() { return {}; }
  static std::vector<grpc_slice> GetBenchmarkSlices() {
    std::vector<uint8_t> v = {
        0x00, 0x07, 'a', 'b', 'c',
        '-',  'b',  'i', 'n', static_cast<uint8_t>(kLength + 1),
        0};
    for (int i = 0; i < kLength; i++) {
      v.push_back(static_cast<uint8_t>(i));
    }
    return {MakeSlice(v)};
  }
};

template <>
class NonIndexedBinaryElem<1, false> {
 public:
  static std::vector<grpc_slice> GetInitSlices() { return {}; }
  static std::vector<grpc_slice> GetBenchmarkSlices() {
    return {MakeSlice(
        {0x00, 0x07, 'a', 'b', 'c', '-', 'b', 'i', 'n', 0x82, 0xf7, 0xb3})};
  }
};

template <>
class NonIndexedBinaryElem<3, false> {
 public:
  static std::vector<grpc_slice> GetInitSlices() { return {}; }
  static std::vector<grpc_slice> GetBenchmarkSlices() {
    return {MakeSlice({0x00, 0x07, 'a', 'b', 'c', '-', 'b', 'i', 'n', 0x84,
                       0x7f, 0x4e, 0x29, 0x3f})};
  }
};

template <>
class NonIndexedBinaryElem<10, false> {
 public:
  static std::vector<grpc_slice> GetInitSlices() { return {}; }
  static std::vector<grpc_slice> GetBenchmarkSlices() {
    return {MakeSlice({0x00, 0x07, 'a',  'b',  'c',  '-',  'b',
                       'i',  'n',  0x8b, 0x71, 0x0c, 0xa5, 0x81,
                       0x73, 0x7b, 0x47, 0x13, 0xe9, 0xf7, 0xe3})};
  }
};

template <>
class NonIndexedBinaryElem<31, false> {
 public:
  static std::vector<grpc_slice> GetInitSlices() { return {}; }
  static std::vector<grpc_slice> GetBenchmarkSlices() {
    return {MakeSlice({0x00, 0x07, 'a',  'b',  'c',  '-',  'b',  'i',  'n',
                       0xa3, 0x92, 0x43, 0x7f, 0xbe, 0x7c, 0xea, 0x6f, 0xf3,
                       0x3d, 0xa7, 0xa7, 0x67, 0xfb, 0xe2, 0x82, 0xf7, 0xf2,
                       0x8f, 0x1f, 0x9d, 0xdf, 0xf1, 0x7e, 0xb3, 0xef, 0xb2,
                       0x8f, 0x53, 0x77, 0xce, 0x0c, 0x13, 0xe3, 0xfd, 0x87})};
  }
};

template <>
class NonIndexedBinaryElem<100, false> {
 public:
  static std::vector<grpc_slice> GetInitSlices() { return {}; }
  static std::vector<grpc_slice> GetBenchmarkSlices() {
    return {MakeSlice(
        {0x00, 0x07, 'a',  'b',  'c',  '-',  'b',  'i',  'n',  0xeb, 0x1d, 0x4d,
         0xe8, 0x96, 0x8c, 0x14, 0x20, 0x06, 0xc1, 0xc3, 0xdf, 0x6e, 0x1f, 0xef,
         0xde, 0x2f, 0xde, 0xb7, 0xf2, 0xfe, 0x6d, 0xd4, 0xe4, 0x7d, 0xf5, 0x55,
         0x46, 0x52, 0x3d, 0x91, 0xf2, 0xd4, 0x6f, 0xca, 0x34, 0xcd, 0xd9, 0x39,
         0xbd, 0x03, 0x27, 0xe3, 0x9c, 0x74, 0xcc, 0x17, 0x34, 0xed, 0xa6, 0x6a,
         0x77, 0x73, 0x10, 0xcd, 0x8e, 0x4e, 0x5c, 0x7c, 0x72, 0x39, 0xd8, 0xe6,
         0x78, 0x6b, 0xdb, 0xa5, 0xb7, 0xab, 0xe7, 0x46, 0xae, 0x21, 0xab, 0x7f,
         0x01, 0x89, 0x13, 0xd7, 0xca, 0x17, 0x6e, 0xcb, 0xd6, 0x79, 0x71, 0x68,
         0xbf, 0x8a, 0x3f, 0x32, 0xe8, 0xba, 0xf5, 0xbe, 0xb3, 0xbc, 0xde, 0x28,
         0xc7, 0xcf, 0x62, 0x7a, 0x58, 0x2c, 0xcf, 0x4d, 0xe3})};
  }
};

using RepresentativeClientInitialMetadata = FromEncoderFixture<
    hpack_encoder_fixtures::RepresentativeClientInitialMetadata>;
using RepresentativeServerInitialMetadata = FromEncoderFixture<
    hpack_encoder_fixtures::RepresentativeServerInitialMetadata>;
using RepresentativeServerTrailingMetadata = FromEncoderFixture<
    hpack_encoder_fixtures::RepresentativeServerTrailingMetadata>;
using MoreRepresentativeClientInitialMetadata = FromEncoderFixture<
    hpack_encoder_fixtures::MoreRepresentativeClientInitialMetadata>;

class SameDeadline {
 public:
  static std::vector<grpc_slice> GetInitSlices() {
    return {
        grpc_slice_from_static_string("@\x0cgrpc-timeout\x03"
                                      "30S")};
  }
  static std::vector<grpc_slice> GetBenchmarkSlices() {

    return {MakeSlice({0x0f, 0x2f, 0x03, '3', '0', 'S'})};
  }
};

BENCHMARK_TEMPLATE(BM_HpackParserParseHeader, EmptyBatch);
BENCHMARK_TEMPLATE(BM_HpackParserParseHeader, IndexedSingleStaticElem);
BENCHMARK_TEMPLATE(BM_HpackParserParseHeader, AddIndexedSingleStaticElem);
BENCHMARK_TEMPLATE(BM_HpackParserParseHeader, KeyIndexedSingleStaticElem);
BENCHMARK_TEMPLATE(BM_HpackParserParseHeader, IndexedSingleInternedElem);
BENCHMARK_TEMPLATE(BM_HpackParserParseHeader, AddIndexedSingleInternedElem);
BENCHMARK_TEMPLATE(BM_HpackParserParseHeader, KeyIndexedSingleInternedElem);
BENCHMARK_TEMPLATE(BM_HpackParserParseHeader, NonIndexedElem);
BENCHMARK_TEMPLATE(BM_HpackParserParseHeader, NonIndexedBinaryElem<1, false>);
BENCHMARK_TEMPLATE(BM_HpackParserParseHeader, NonIndexedBinaryElem<3, false>);
BENCHMARK_TEMPLATE(BM_HpackParserParseHeader, NonIndexedBinaryElem<10, false>);
BENCHMARK_TEMPLATE(BM_HpackParserParseHeader, NonIndexedBinaryElem<31, false>);
BENCHMARK_TEMPLATE(BM_HpackParserParseHeader, NonIndexedBinaryElem<100, false>);
BENCHMARK_TEMPLATE(BM_HpackParserParseHeader, NonIndexedBinaryElem<1, true>);
BENCHMARK_TEMPLATE(BM_HpackParserParseHeader, NonIndexedBinaryElem<3, true>);
BENCHMARK_TEMPLATE(BM_HpackParserParseHeader, NonIndexedBinaryElem<10, true>);
BENCHMARK_TEMPLATE(BM_HpackParserParseHeader, NonIndexedBinaryElem<31, true>);
BENCHMARK_TEMPLATE(BM_HpackParserParseHeader, NonIndexedBinaryElem<100, true>);
BENCHMARK_TEMPLATE(BM_HpackParserParseHeader,
                   RepresentativeClientInitialMetadata);
BENCHMARK_TEMPLATE(BM_HpackParserParseHeader,
                   MoreRepresentativeClientInitialMetadata);
BENCHMARK_TEMPLATE(BM_HpackParserParseHeader,
                   RepresentativeServerInitialMetadata);
BENCHMARK_TEMPLATE(BM_HpackParserParseHeader,
                   RepresentativeServerTrailingMetadata);
BENCHMARK_TEMPLATE(BM_HpackParserParseHeader,
                   RepresentativeClientInitialMetadata);
BENCHMARK_TEMPLATE(BM_HpackParserParseHeader,
                   MoreRepresentativeClientInitialMetadata);
BENCHMARK_TEMPLATE(BM_HpackParserParseHeader,
                   RepresentativeServerInitialMetadata);
BENCHMARK_TEMPLATE(BM_HpackParserParseHeader, SameDeadline);

}

namespace benchmark {
void RunTheBenchmarksNamespaced() { RunSpecifiedBenchmarks(); }
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  LibraryInitializer libInit;
  ::benchmark::Initialize(&argc, argv);
  grpc::testing::InitTest(&argc, &argv, false);
  benchmark::RunTheBenchmarksNamespaced();
  return 0;
}
