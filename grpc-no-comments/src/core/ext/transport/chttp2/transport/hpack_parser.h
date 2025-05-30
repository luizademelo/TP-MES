
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_EXT_TRANSPORT_CHTTP2_TRANSPORT_HPACK_PARSER_H
#define GRPC_SRC_CORE_EXT_TRANSPORT_CHTTP2_TRANSPORT_HPACK_PARSER_H

#include <grpc/slice.h>
#include <grpc/support/port_platform.h>
#include <stddef.h>
#include <stdint.h>

#include <optional>
#include <string>
#include <utility>
#include <variant>
#include <vector>

#include "absl/random/bit_gen_ref.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/string_view.h"
#include "absl/types/span.h"
#include "src/core/call/metadata_batch.h"
#include "src/core/ext/transport/chttp2/transport/hpack_parse_result.h"
#include "src/core/ext/transport/chttp2/transport/hpack_parser_table.h"
#include "src/core/ext/transport/chttp2/transport/legacy_frame.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/lib/slice/slice_refcount.h"
#include "src/core/telemetry/call_tracer.h"
#include "src/core/util/random_early_detection.h"

namespace grpc_core {

class HPackParser {
 public:

  enum class Boundary : uint8_t {

    None,

    EndOfHeaders,

    EndOfStream
  };

  enum class Priority : uint8_t {

    None,

    Included
  };

  struct LogInfo {

    uint32_t stream_id;

    enum Type : uint8_t {
      kHeaders,
      kTrailers,
      kDontKnow,
    };
    Type type;

    bool is_client;
  };

  HPackParser();
  ~HPackParser();

  HPackParser(const HPackParser&) = delete;
  HPackParser& operator=(const HPackParser&) = delete;
  HPackParser(HPackParser&&) = default;
  HPackParser& operator=(HPackParser&&) = default;

  void BeginFrame(grpc_metadata_batch* metadata_buffer,
                  uint32_t metadata_size_soft_limit,
                  uint32_t metadata_size_hard_limit, Boundary boundary,
                  Priority priority, LogInfo log_info);

  void StopBufferingFrame() { metadata_buffer_ = nullptr; }

  grpc_error_handle Parse(const grpc_slice& slice, bool is_last,
                          absl::BitGenRef bitsrc,
                          CallTracerAnnotationInterface* call_tracer);

  void FinishFrame();

  HPackTable* hpack_table() { return &state_.hpack_table; }

  bool is_boundary() const { return boundary_ != Boundary::None; }

  bool is_eof() const { return boundary_ == Boundary::EndOfStream; }

  size_t buffered_bytes() const { return unparsed_bytes_.size(); }

 private:

  class Parser;
  class Input;

  class String {
   public:

    struct StringResult;

    String() : value_(absl::Span<const uint8_t>()) {}
    String(const String&) = delete;
    String& operator=(const String&) = delete;
    String(String&& other) noexcept : value_(std::move(other.value_)) {
      other.value_ = absl::Span<const uint8_t>();
    }
    String& operator=(String&& other) noexcept {
      value_ = std::move(other.value_);
      other.value_ = absl::Span<const uint8_t>();
      return *this;
    }

    Slice Take();

    absl::string_view string_view() const;

    static StringResult Parse(Input* input, bool is_huff, size_t length);

    static StringResult ParseBinary(Input* input, bool is_huff, size_t length);

   private:
    void AppendBytes(const uint8_t* data, size_t length);
    explicit String(std::vector<uint8_t> v) : value_(std::move(v)) {}
    explicit String(absl::Span<const uint8_t> v) : value_(v) {}
    String(grpc_slice_refcount* r, const uint8_t* begin, const uint8_t* end)
        : value_(Slice::FromRefcountAndBytes(r, begin, end)) {}

    template <typename Out>
    static HpackParseStatus ParseHuff(Input* input, uint32_t length,
                                      Out output);

    static StringResult ParseUncompressed(Input* input, uint32_t length,
                                          uint32_t wire_size);

    static StringResult Unbase64(String s);

    static std::optional<std::vector<uint8_t>> Unbase64Loop(const uint8_t* cur,
                                                            const uint8_t* end);

    std::variant<Slice, absl::Span<const uint8_t>, std::vector<uint8_t>> value_;
  };

  struct StringPrefix {

    uint32_t length;

    bool huff;

    std::string ToString() const {
      return absl::StrCat(length, " bytes ",
                          huff ? "huffman compressed" : "uncompressed");
    }
  };

  enum class ParseState : uint8_t {

    kTop,

    kParsingKeyLength,

    kParsingKeyBody,

    kSkippingKeyBody,

    kParsingValueLength,

    kParsingValueBody,

    kSkippingValueLength,

    kSkippingValueBody,
  };

  struct InterSliceState {
    HPackTable hpack_table;

    HpackParseResult frame_error;

    HpackParseResult field_error;

    uint32_t frame_length = 0;

    uint32_t string_length;

    RandomEarlyDetection metadata_early_detection;

    bool add_to_table;

    bool is_string_huff_compressed;

    bool is_binary_header;

    uint8_t dynamic_table_updates_allowed;

    ParseState parse_state = ParseState::kTop;
    std::variant<const HPackTable::Memento*, Slice> key;
  };

  grpc_error_handle ParseInput(Input input, bool is_last,
                               CallTracerAnnotationInterface* call_tracer);
  void ParseInputInner(Input* input);
  GPR_ATTRIBUTE_NOINLINE
  void HandleMetadataSoftSizeLimitExceeded(Input* input);

  grpc_metadata_batch* metadata_buffer_ = nullptr;

  std::vector<uint8_t> unparsed_bytes_;

  size_t min_progress_size_ = 0;

  Boundary boundary_;

  Priority priority_;

  LogInfo log_info_;
  InterSliceState state_;
};

}

grpc_error_handle grpc_chttp2_header_parser_parse(void* hpack_parser,
                                                  grpc_chttp2_transport* t,
                                                  grpc_chttp2_stream* s,
                                                  const grpc_slice& slice,
                                                  int is_last);

#endif
