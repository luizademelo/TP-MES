
// Copyright 2015 gRPC authors.

#include "src/core/ext/transport/chttp2/transport/hpack_parser.h"

#include <grpc/slice.h>
#include <grpc/support/port_platform.h>
#include <stddef.h>
#include <stdlib.h>

#include <algorithm>
#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <variant>

#include "absl/base/attributes.h"
#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/status/status.h"
#include "absl/strings/match.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/string_view.h"
#include "absl/types/span.h"
#include "src/core/call/metadata_info.h"
#include "src/core/call/parsed_metadata.h"
#include "src/core/ext/transport/chttp2/transport/decode_huff.h"
#include "src/core/ext/transport/chttp2/transport/hpack_constants.h"
#include "src/core/ext/transport/chttp2/transport/hpack_parse_result.h"
#include "src/core/ext/transport/chttp2/transport/hpack_parser_table.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/lib/slice/slice_refcount.h"
#include "src/core/lib/surface/validate_metadata.h"
#include "src/core/telemetry/call_tracer.h"
#include "src/core/telemetry/stats.h"
#include "src/core/telemetry/stats_data.h"
#include "src/core/util/match.h"

namespace grpc_core {

namespace {

constexpr char kBase64Alphabet[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";

struct Base64InverseTable {
  uint8_t table[256]{};
  constexpr Base64InverseTable() {
    for (int i = 0; i < 256; i++) {
      table[i] = 255;
    }
    for (const char* p = kBase64Alphabet; *p; p++) {
      uint8_t idx = *p;
      uint8_t ofs = p - kBase64Alphabet;
      table[idx] = ofs;
    }
  }
};

constexpr Base64InverseTable kBase64InverseTable;

}

class HPackParser::Input {
 public:
  Input(grpc_slice_refcount* current_slice_refcount, const uint8_t* begin,
        const uint8_t* end, absl::BitGenRef bitsrc,
        HpackParseResult& frame_error, HpackParseResult& field_error)
      : current_slice_refcount_(current_slice_refcount),
        begin_(begin),
        end_(end),
        frontier_(begin),
        frame_error_(frame_error),
        field_error_(field_error),
        bitsrc_(bitsrc) {}

  grpc_slice_refcount* slice_refcount() { return current_slice_refcount_; }

  bool end_of_stream() const { return begin_ == end_; }

  size_t remaining() const { return end_ - begin_; }

  const uint8_t* cur_ptr() const { return begin_; }

  const uint8_t* end_ptr() const { return end_; }

  void Advance(size_t n) { begin_ += n; }

  std::optional<uint8_t> peek() const {
    if (end_of_stream()) {
      return {};
    }
    return *begin_;
  }

  std::optional<uint8_t> Next() {
    if (end_of_stream()) {
      UnexpectedEOF(1);
      return std::optional<uint8_t>();
    }
    return *begin_++;
  }

  std::optional<uint32_t> ParseVarint(uint32_t value) {

    auto cur = Next();
    if (!cur) return {};
    value += *cur & 0x7f;
    if ((*cur & 0x80) == 0) return value;

    cur = Next();
    if (!cur) return {};
    value += (*cur & 0x7f) << 7;
    if ((*cur & 0x80) == 0) return value;

    cur = Next();
    if (!cur) return {};
    value += (*cur & 0x7f) << 14;
    if ((*cur & 0x80) == 0) return value;

    cur = Next();
    if (!cur) return {};
    value += (*cur & 0x7f) << 21;
    if ((*cur & 0x80) == 0) return value;

    cur = Next();
    if (!cur) return {};
    uint32_t c = (*cur) & 0x7f;

    if (c > 0xf) return ParseVarintOutOfRange(value, *cur);
    const uint32_t add = c << 28;
    if (add > 0xffffffffu - value) {
      return ParseVarintOutOfRange(value, *cur);
    }
    value += add;
    if ((*cur & 0x80) == 0) return value;

    int num_redundant_0x80 = 0;
    do {
      cur = Next();
      if (!cur.has_value()) return {};
      ++num_redundant_0x80;
      if (num_redundant_0x80 == 16) {
        return ParseVarintMaliciousEncoding();
      }
    } while (*cur == 0x80);

    if (*cur == 0) return value;
    return ParseVarintOutOfRange(value, *cur);
  }

  std::optional<StringPrefix> ParseStringPrefix() {
    auto cur = Next();
    if (!cur.has_value()) {
      DCHECK(eof_error());
      return {};
    }

    const bool huff = (*cur & 0x80) != 0;

    uint32_t strlen = (*cur & 0x7f);
    if (strlen == 0x7f) {

      auto v = ParseVarint(0x7f);
      if (!v.has_value()) {
        DCHECK(eof_error());
        return {};
      }
      strlen = *v;
    }
    return StringPrefix{strlen, huff};
  }

  bool eof_error() const {
    return min_progress_size_ != 0 || frame_error_.connection_error();
  }

  void ClearFieldError() {
    if (field_error_.ok()) return;
    field_error_ = HpackParseResult();
  }

  size_t min_progress_size() const { return min_progress_size_; }

  void SetErrorAndContinueParsing(HpackParseResult error) {
    DCHECK(error.stream_error());
    SetError(std::move(error));
  }

  void SetErrorAndStopParsing(HpackParseResult error) {
    DCHECK(error.connection_error());
    SetError(std::move(error));
    begin_ = end_;
  }

  void UnexpectedEOF(size_t min_progress_size) {
    CHECK_GT(min_progress_size, 0u);
    if (eof_error()) return;

    min_progress_size_ = min_progress_size + (begin_ - frontier_);
    DCHECK(eof_error());
  }

  void UpdateFrontier() {
    DCHECK_EQ(skip_bytes_, 0u);
    frontier_ = begin_;
  }

  void UpdateFrontierAndSkipBytes(size_t skip_bytes) {
    UpdateFrontier();
    size_t remaining = end_ - begin_;
    if (skip_bytes >= remaining) {

      skip_bytes_ = skip_bytes - remaining;
      frontier_ = end_;
    } else {

      frontier_ += skip_bytes_;
    }
  }

  const uint8_t* frontier() const { return frontier_; }

  absl::BitGenRef bitsrc() { return bitsrc_; }

 private:

  std::optional<uint32_t> ParseVarintOutOfRange(uint32_t value,
                                                uint8_t last_byte) {
    SetErrorAndStopParsing(
        HpackParseResult::VarintOutOfRangeError(value, last_byte));
    return std::optional<uint32_t>();
  }

  std::optional<uint32_t> ParseVarintMaliciousEncoding() {
    SetErrorAndStopParsing(HpackParseResult::MaliciousVarintEncodingError());
    return std::optional<uint32_t>();
  }

  void SetError(HpackParseResult error) {
    SetErrorFor(frame_error_, error);
    SetErrorFor(field_error_, std::move(error));
  }

  void SetErrorFor(HpackParseResult& error, HpackParseResult new_error) {
    if (!error.ok() || min_progress_size_ > 0) {
      if (new_error.connection_error() && !error.connection_error()) {
        error = std::move(new_error);
      }
      return;
    }
    error = std::move(new_error);
  }

  grpc_slice_refcount* current_slice_refcount_;

  const uint8_t* begin_;

  const uint8_t* const end_;

  const uint8_t* frontier_;

  HpackParseResult& frame_error_;
  HpackParseResult& field_error_;

  size_t min_progress_size_ = 0;

  size_t skip_bytes_ = 0;

  absl::BitGenRef bitsrc_;
};

absl::string_view HPackParser::String::string_view() const {
  if (auto* p = std::get_if<Slice>(&value_)) {
    return p->as_string_view();
  } else if (auto* p = std::get_if<absl::Span<const uint8_t>>(&value_)) {
    return absl::string_view(reinterpret_cast<const char*>(p->data()),
                             p->size());
  } else if (auto* p = std::get_if<std::vector<uint8_t>>(&value_)) {
    return absl::string_view(reinterpret_cast<const char*>(p->data()),
                             p->size());
  }
  GPR_UNREACHABLE_CODE(return absl::string_view());
}

template <typename Out>
HpackParseStatus HPackParser::String::ParseHuff(Input* input, uint32_t length,
                                                Out output) {

  if (input->remaining() < length) {
    input->UnexpectedEOF(length);
    return HpackParseStatus::kEof;
  }

  const uint8_t* p = input->cur_ptr();
  input->Advance(length);
  return HuffDecoder<Out>(output, p, p + length).Run()
             ? HpackParseStatus::kOk
             : HpackParseStatus::kParseHuffFailed;
}

struct HPackParser::String::StringResult {
  StringResult() = delete;
  StringResult(HpackParseStatus status, size_t wire_size, String value)
      : status(status), wire_size(wire_size), value(std::move(value)) {}
  HpackParseStatus status;
  size_t wire_size;
  String value;
};

HPackParser::String::StringResult HPackParser::String::ParseUncompressed(
    Input* input, uint32_t length, uint32_t wire_size) {

  if (input->remaining() < length) {
    input->UnexpectedEOF(length);
    DCHECK(input->eof_error());
    return StringResult{HpackParseStatus::kEof, wire_size, String{}};
  }
  auto* refcount = input->slice_refcount();
  auto* p = input->cur_ptr();
  input->Advance(length);
  if (refcount != nullptr) {
    return StringResult{HpackParseStatus::kOk, wire_size,
                        String(refcount, p, p + length)};
  } else {
    return StringResult{HpackParseStatus::kOk, wire_size,
                        String(absl::Span<const uint8_t>(p, length))};
  }
}

std::optional<std::vector<uint8_t>> HPackParser::String::Unbase64Loop(
    const uint8_t* cur, const uint8_t* end) {
  while (cur != end && end[-1] == '=') {
    --end;
  }

  std::vector<uint8_t> out;
  out.reserve((3 * (end - cur) / 4) + 3);

  while (end - cur >= 4) {
    uint32_t bits = kBase64InverseTable.table[*cur];
    if (bits > 63) return {};
    uint32_t buffer = bits << 18;
    ++cur;

    bits = kBase64InverseTable.table[*cur];
    if (bits > 63) return {};
    buffer |= bits << 12;
    ++cur;

    bits = kBase64InverseTable.table[*cur];
    if (bits > 63) return {};
    buffer |= bits << 6;
    ++cur;

    bits = kBase64InverseTable.table[*cur];
    if (bits > 63) return {};
    buffer |= bits;
    ++cur;

    out.insert(out.end(), {static_cast<uint8_t>(buffer >> 16),
                           static_cast<uint8_t>(buffer >> 8),
                           static_cast<uint8_t>(buffer)});
  }

  switch (end - cur) {
    case 0:
      return out;
    case 1:
      return {};
    case 2: {
      uint32_t bits = kBase64InverseTable.table[*cur];
      if (bits > 63) return {};
      uint32_t buffer = bits << 18;

      ++cur;
      bits = kBase64InverseTable.table[*cur];
      if (bits > 63) return {};
      buffer |= bits << 12;

      if (buffer & 0xffff) return {};
      out.push_back(static_cast<uint8_t>(buffer >> 16));
      return out;
    }
    case 3: {
      uint32_t bits = kBase64InverseTable.table[*cur];
      if (bits > 63) return {};
      uint32_t buffer = bits << 18;

      ++cur;
      bits = kBase64InverseTable.table[*cur];
      if (bits > 63) return {};
      buffer |= bits << 12;

      ++cur;
      bits = kBase64InverseTable.table[*cur];
      if (bits > 63) return {};
      buffer |= bits << 6;

      ++cur;
      if (buffer & 0xff) return {};
      out.push_back(static_cast<uint8_t>(buffer >> 16));
      out.push_back(static_cast<uint8_t>(buffer >> 8));
      return out;
    }
  }

  GPR_UNREACHABLE_CODE(return out;);
}

HPackParser::String::StringResult HPackParser::String::Unbase64(String s) {
  std::optional<std::vector<uint8_t>> result;
  if (auto* p = std::get_if<Slice>(&s.value_)) {
    result = Unbase64Loop(p->begin(), p->end());
  }
  if (auto* p = std::get_if<absl::Span<const uint8_t>>(&s.value_)) {
    result = Unbase64Loop(p->begin(), p->end());
  }
  if (auto* p = std::get_if<std::vector<uint8_t>>(&s.value_)) {
    result = Unbase64Loop(p->data(), p->data() + p->size());
  }
  if (!result.has_value()) {
    return StringResult{HpackParseStatus::kUnbase64Failed,
                        s.string_view().length(), String{}};
  }
  return StringResult{HpackParseStatus::kOk, s.string_view().length(),
                      String(std::move(*result))};
}

HPackParser::String::StringResult HPackParser::String::Parse(Input* input,
                                                             bool is_huff,
                                                             size_t length) {
  if (is_huff) {

    std::vector<uint8_t> output;
    HpackParseStatus sts =
        ParseHuff(input, length, [&output](uint8_t c) { output.push_back(c); });
    size_t wire_len = output.size();
    return StringResult{sts, wire_len, String(std::move(output))};
  }
  return ParseUncompressed(input, length, length);
}

HPackParser::String::StringResult HPackParser::String::ParseBinary(
    Input* input, bool is_huff, size_t length) {
  if (!is_huff) {
    if (length > 0 && input->peek() == 0) {

      input->Advance(1);
      return ParseUncompressed(input, length - 1, length);
    }

    auto base64 = ParseUncompressed(input, length, length);
    if (base64.status != HpackParseStatus::kOk) return base64;
    return Unbase64(std::move(base64.value));
  } else {

    std::vector<uint8_t> decompressed;

    enum class State { kUnsure, kBinary, kBase64 };
    State state = State::kUnsure;
    auto sts = ParseHuff(input, length, [&state, &decompressed](uint8_t c) {
      if (state == State::kUnsure) {

        if (c == 0) {

          state = State::kBinary;
          return;
        } else {

          state = State::kBase64;
        }
      }

      decompressed.push_back(c);
    });
    if (sts != HpackParseStatus::kOk) {
      return StringResult{sts, 0, String{}};
    }
    switch (state) {
      case State::kUnsure:

        return StringResult{HpackParseStatus::kOk, 0,
                            String(absl::Span<const uint8_t>())};
      case State::kBinary:

        {
          size_t wire_len = decompressed.size();
          return StringResult{HpackParseStatus::kOk, wire_len,
                              String(std::move(decompressed))};
        }
      case State::kBase64:

        return Unbase64(String(std::move(decompressed)));
    }
    GPR_UNREACHABLE_CODE(abort(););
  }
}

class HPackParser::Parser {
 public:
  Parser(Input* input, grpc_metadata_batch*& metadata_buffer,
         InterSliceState& state, LogInfo log_info)
      : input_(input),
        metadata_buffer_(metadata_buffer),
        state_(state),
        log_info_(log_info) {}

  bool Parse() {
    switch (state_.parse_state) {
      case ParseState::kTop:
        return ParseTop();
      case ParseState::kParsingKeyLength:
        return ParseKeyLength();
      case ParseState::kParsingKeyBody:
        return ParseKeyBody();
      case ParseState::kSkippingKeyBody:
        return SkipKeyBody();
      case ParseState::kParsingValueLength:
        return ParseValueLength();
      case ParseState::kParsingValueBody:
        return ParseValueBody();
      case ParseState::kSkippingValueLength:
        return SkipValueLength();
      case ParseState::kSkippingValueBody:
        return SkipValueBody();
    }
    GPR_UNREACHABLE_CODE(return false);
  }

 private:
  bool ParseTop() {
    DCHECK(state_.parse_state == ParseState::kTop);
    auto cur = *input_->Next();
    input_->ClearFieldError();
    switch (cur >> 4) {

      case 0:
      case 1:
        switch (cur & 0xf) {
          case 0:
            return StartParseLiteralKey(false);
          case 0xf:
            return StartVarIdxKey(0xf, false);
          default:
            return StartIdxKey(cur & 0xf, false);
        }

      case 2:

        return FinishMaxTableSize(cur & 0x1f);
      case 3:
        if (cur == 0x3f) {

          return FinishMaxTableSize(input_->ParseVarint(0x1f));
        } else {

          return FinishMaxTableSize(cur & 0x1f);
        }

      case 4:
        if (cur == 0x40) {

          return StartParseLiteralKey(true);
        }
        [[fallthrough]];
      case 5:
      case 6:

        return StartIdxKey(cur & 0x3f, true);
      case 7:
        if (cur == 0x7f) {

          return StartVarIdxKey(0x3f, true);
        } else {

          return StartIdxKey(cur & 0x3f, true);
        }

      case 8:
        if (cur == 0x80) {

          input_->SetErrorAndStopParsing(
              HpackParseResult::IllegalHpackOpCode());
          return false;
        }
        [[fallthrough]];
      case 9:
      case 10:
      case 11:
      case 12:
      case 13:
      case 14:

        return FinishIndexed(cur & 0x7f);
      case 15:
        if (cur == 0xff) {

          return FinishIndexed(input_->ParseVarint(0x7f));
        } else {

          return FinishIndexed(cur & 0x7f);
        }
    }
    GPR_UNREACHABLE_CODE(abort());
  }

  void GPR_ATTRIBUTE_NOINLINE LogHeader(const HPackTable::Memento& memento) {
    const char* type;
    switch (log_info_.type) {
      case LogInfo::kHeaders:
        type = "HDR";
        break;
      case LogInfo::kTrailers:
        type = "TRL";
        break;
      case LogInfo::kDontKnow:
        type = "???";
        break;
    }
    LOG(INFO) << "HTTP:" << log_info_.stream_id << ":" << type << ":"
              << (log_info_.is_client ? "CLI" : "SVR") << ": "
              << memento.md.DebugString()
              << (memento.parse_status.get() == nullptr
                      ? ""
                      : absl::StrCat(
                            " (parse error: ",
                            memento.parse_status->Materialize().ToString(),
                            ")"));
  }

  void EmitHeader(const HPackTable::Memento& md) {

    state_.frame_length += md.md.transport_size();
    if (md.parse_status.get() != nullptr) {

      input_->SetErrorAndContinueParsing(*md.parse_status);
    }
    if (GPR_LIKELY(metadata_buffer_ != nullptr)) {
      metadata_buffer_->Set(md.md);
    }
    if (state_.metadata_early_detection.MustReject(state_.frame_length)) {

      input_->SetErrorAndContinueParsing(
          HpackParseResult::HardMetadataLimitExceededError(
              std::exchange(metadata_buffer_, nullptr), state_.frame_length,
              state_.metadata_early_detection.hard_limit()));
    }
  }

  bool FinishHeaderAndAddToTable(HPackTable::Memento md) {

    if (GRPC_TRACE_FLAG_ENABLED(chttp2_hpack_parser)) {
      LogHeader(md);
    }

    EmitHeader(md);

    if (GPR_UNLIKELY(!state_.hpack_table.Add(std::move(md)))) {
      input_->SetErrorAndStopParsing(
          HpackParseResult::AddBeforeTableSizeUpdated(
              state_.hpack_table.current_table_bytes(),
              state_.hpack_table.max_bytes()));
      return false;
    };
    return true;
  }

  bool FinishHeaderOmitFromTable(std::optional<HPackTable::Memento> md) {

    if (!md.has_value()) return false;
    FinishHeaderOmitFromTable(*md);
    return true;
  }

  void FinishHeaderOmitFromTable(const HPackTable::Memento& md) {

    if (GRPC_TRACE_FLAG_ENABLED(chttp2_hpack_parser)) {
      LogHeader(md);
    }
    EmitHeader(md);
  }

  bool StartIdxKey(uint32_t index, bool add_to_table) {
    DCHECK(state_.parse_state == ParseState::kTop);
    input_->UpdateFrontier();
    const auto* elem = state_.hpack_table.Lookup(index);
    if (GPR_UNLIKELY(elem == nullptr)) {
      InvalidHPackIndexError(index);
      return false;
    }
    state_.parse_state = ParseState::kParsingValueLength;
    state_.is_binary_header = elem->md.is_binary_header();
    state_.key.emplace<const HPackTable::Memento*>(elem);
    state_.add_to_table = add_to_table;
    return ParseValueLength();
  };

  bool StartVarIdxKey(uint32_t offset, bool add_to_table) {
    DCHECK(state_.parse_state == ParseState::kTop);
    auto index = input_->ParseVarint(offset);
    if (GPR_UNLIKELY(!index.has_value())) return false;
    return StartIdxKey(*index, add_to_table);
  }

  bool StartParseLiteralKey(bool add_to_table) {
    DCHECK(state_.parse_state == ParseState::kTop);
    state_.add_to_table = add_to_table;
    state_.parse_state = ParseState::kParsingKeyLength;
    input_->UpdateFrontier();
    return ParseKeyLength();
  }

  bool ShouldSkipParsingString(uint64_t string_length) const {

    return string_length > state_.hpack_table.current_table_size() &&
           state_.metadata_early_detection.MustReject(
               string_length + hpack_constants::kEntryOverhead);
  }

  bool ParseKeyLength() {
    DCHECK(state_.parse_state == ParseState::kParsingKeyLength);
    auto pfx = input_->ParseStringPrefix();
    if (!pfx.has_value()) return false;
    state_.is_string_huff_compressed = pfx->huff;
    state_.string_length = pfx->length;
    input_->UpdateFrontier();
    if (ShouldSkipParsingString(state_.string_length)) {
      input_->SetErrorAndContinueParsing(
          HpackParseResult::HardMetadataLimitExceededByKeyError(
              state_.string_length,
              state_.metadata_early_detection.hard_limit()));
      metadata_buffer_ = nullptr;
      state_.parse_state = ParseState::kSkippingKeyBody;
      return SkipKeyBody();
    } else {
      state_.parse_state = ParseState::kParsingKeyBody;
      return ParseKeyBody();
    }
  }

  bool ParseKeyBody() {
    DCHECK(state_.parse_state == ParseState::kParsingKeyBody);
    auto key = String::Parse(input_, state_.is_string_huff_compressed,
                             state_.string_length);
    switch (key.status) {
      case HpackParseStatus::kOk:
        break;
      case HpackParseStatus::kEof:
        DCHECK(input_->eof_error());
        return false;
      default:
        input_->SetErrorAndStopParsing(
            HpackParseResult::FromStatus(key.status));
        return false;
    }
    input_->UpdateFrontier();
    state_.parse_state = ParseState::kParsingValueLength;
    state_.is_binary_header = absl::EndsWith(key.value.string_view(), "-bin");
    state_.key.emplace<Slice>(key.value.Take());
    return ParseValueLength();
  }

  bool SkipStringBody() {
    auto remaining = input_->remaining();
    if (remaining >= state_.string_length) {
      input_->Advance(state_.string_length);
      return true;
    } else {
      input_->Advance(remaining);
      input_->UpdateFrontier();
      state_.string_length -= remaining;

      input_->UnexpectedEOF(
          std::min(state_.string_length, 1024u));
      return false;
    }
  }

  bool SkipKeyBody() {
    DCHECK(state_.parse_state == ParseState::kSkippingKeyBody);
    if (!SkipStringBody()) return false;
    input_->UpdateFrontier();
    state_.parse_state = ParseState::kSkippingValueLength;
    return SkipValueLength();
  }

  bool SkipValueLength() {
    DCHECK(state_.parse_state == ParseState::kSkippingValueLength);
    auto pfx = input_->ParseStringPrefix();
    if (!pfx.has_value()) return false;
    state_.string_length = pfx->length;
    input_->UpdateFrontier();
    state_.parse_state = ParseState::kSkippingValueBody;
    return SkipValueBody();
  }

  bool SkipValueBody() {
    DCHECK(state_.parse_state == ParseState::kSkippingValueBody);
    if (!SkipStringBody()) return false;
    input_->UpdateFrontier();
    state_.parse_state = ParseState::kTop;
    if (state_.add_to_table) {
      state_.hpack_table.AddLargerThanCurrentTableSize();
    }
    return true;
  }

  bool ParseValueLength() {
    DCHECK(state_.parse_state == ParseState::kParsingValueLength);
    auto pfx = input_->ParseStringPrefix();
    if (!pfx.has_value()) return false;
    state_.is_string_huff_compressed = pfx->huff;
    state_.string_length = pfx->length;
    input_->UpdateFrontier();
    if (ShouldSkipParsingString(state_.string_length)) {
      input_->SetErrorAndContinueParsing(
          HpackParseResult::HardMetadataLimitExceededByValueError(
              Match(
                  state_.key, [](const Slice& s) { return s.as_string_view(); },
                  [](const HPackTable::Memento* m) { return m->md.key(); }),
              state_.string_length,
              state_.metadata_early_detection.hard_limit()));
      metadata_buffer_ = nullptr;
      state_.parse_state = ParseState::kSkippingValueBody;
      return SkipValueBody();
    } else {
      state_.parse_state = ParseState::kParsingValueBody;
      return ParseValueBody();
    }
  }

  bool ParseValueBody() {
    DCHECK(state_.parse_state == ParseState::kParsingValueBody);
    auto value =
        state_.is_binary_header
            ? String::ParseBinary(input_, state_.is_string_huff_compressed,
                                  state_.string_length)
            : String::Parse(input_, state_.is_string_huff_compressed,
                            state_.string_length);
    absl::string_view key_string;
    if (auto* s = std::get_if<Slice>(&state_.key)) {
      key_string = s->as_string_view();
      if (state_.field_error.ok()) {
        auto r = ValidateKey(key_string);
        if (r != ValidateMetadataResult::kOk) {
          input_->SetErrorAndContinueParsing(
              HpackParseResult::InvalidMetadataError(r, key_string));
        }
      }
    } else {
      const auto* memento = std::get<const HPackTable::Memento*>(state_.key);
      key_string = memento->md.key();
      if (state_.field_error.ok() && memento->parse_status.get() != nullptr) {
        input_->SetErrorAndContinueParsing(*memento->parse_status);
      }
    }
    switch (value.status) {
      case HpackParseStatus::kOk:
        break;
      case HpackParseStatus::kEof:
        DCHECK(input_->eof_error());
        return false;
      default: {
        auto result =
            HpackParseResult::FromStatusWithKey(value.status, key_string);
        if (result.stream_error()) {
          input_->SetErrorAndContinueParsing(std::move(result));
          break;
        } else {
          input_->SetErrorAndStopParsing(std::move(result));
          return false;
        }
      }
    }
    auto value_slice = value.value.Take();
    const auto transport_size =
        key_string.size() + value.wire_size + hpack_constants::kEntryOverhead;
    auto md = grpc_metadata_batch::Parse(
        key_string, std::move(value_slice), state_.add_to_table, transport_size,
        [key_string, this](absl::string_view message, const Slice&) {
          if (!state_.field_error.ok()) return;
          input_->SetErrorAndContinueParsing(
              HpackParseResult::MetadataParseError(key_string));
          LOG(ERROR) << "Error parsing '" << key_string
                     << "' metadata: " << message;
        });
    HPackTable::Memento memento{
        std::move(md), state_.field_error.PersistentStreamErrorOrNullptr()};
    input_->UpdateFrontier();
    state_.parse_state = ParseState::kTop;
    if (state_.add_to_table) {
      return FinishHeaderAndAddToTable(std::move(memento));
    } else {
      FinishHeaderOmitFromTable(memento);
      return true;
    }
  }

  ValidateMetadataResult ValidateKey(absl::string_view key) {
    if (key == HttpSchemeMetadata::key() || key == HttpMethodMetadata::key() ||
        key == HttpAuthorityMetadata::key() || key == HttpPathMetadata::key() ||
        key == HttpStatusMetadata::key()) {
      return ValidateMetadataResult::kOk;
    }
    return ValidateHeaderKeyIsLegal(key);
  }

  bool FinishIndexed(std::optional<uint32_t> index) {
    state_.dynamic_table_updates_allowed = 0;
    if (!index.has_value()) return false;
    const auto* elem = state_.hpack_table.Lookup(*index);
    if (GPR_UNLIKELY(elem == nullptr)) {
      InvalidHPackIndexError(*index);
      return false;
    }
    FinishHeaderOmitFromTable(*elem);
    return true;
  }

  bool FinishMaxTableSize(std::optional<uint32_t> size) {
    if (!size.has_value()) return false;
    if (state_.dynamic_table_updates_allowed == 0) {
      input_->SetErrorAndStopParsing(
          HpackParseResult::TooManyDynamicTableSizeChangesError());
      return false;
    }
    state_.dynamic_table_updates_allowed--;
    if (!state_.hpack_table.SetCurrentTableSize(*size)) {
      input_->SetErrorAndStopParsing(
          HpackParseResult::IllegalTableSizeChangeError(
              *size, state_.hpack_table.max_bytes()));
      return false;
    }
    return true;
  }

  void InvalidHPackIndexError(uint32_t index) {
    input_->SetErrorAndStopParsing(
        HpackParseResult::InvalidHpackIndexError(index));
  }

  Input* const input_;
  grpc_metadata_batch*& metadata_buffer_;
  InterSliceState& state_;
  const LogInfo log_info_;
};

Slice HPackParser::String::Take() {
  if (auto* p = std::get_if<Slice>(&value_)) {
    return p->Copy();
  } else if (auto* p = std::get_if<absl::Span<const uint8_t>>(&value_)) {
    return Slice::FromCopiedBuffer(*p);
  } else if (auto* p = std::get_if<std::vector<uint8_t>>(&value_)) {
    return Slice::FromCopiedBuffer(*p);
  }
  GPR_UNREACHABLE_CODE(return Slice());
}

HPackParser::HPackParser() = default;

HPackParser::~HPackParser() = default;

void HPackParser::BeginFrame(grpc_metadata_batch* metadata_buffer,
                             uint32_t metadata_size_soft_limit,
                             uint32_t metadata_size_hard_limit,
                             Boundary boundary, Priority priority,
                             LogInfo log_info) {
  metadata_buffer_ = metadata_buffer;
  if (metadata_buffer != nullptr) {
    metadata_buffer->Set(GrpcStatusFromWire(), true);
  }
  boundary_ = boundary;
  priority_ = priority;
  state_.dynamic_table_updates_allowed = 2;
  state_.metadata_early_detection.SetLimits(
      metadata_size_soft_limit,
      metadata_size_hard_limit);
  log_info_ = log_info;
}

grpc_error_handle HPackParser::Parse(
    const grpc_slice& slice, bool is_last, absl::BitGenRef bitsrc,
    CallTracerAnnotationInterface* call_tracer) {
  if (GPR_UNLIKELY(!unparsed_bytes_.empty())) {
    unparsed_bytes_.insert(unparsed_bytes_.end(), GRPC_SLICE_START_PTR(slice),
                           GRPC_SLICE_END_PTR(slice));
    if (!(is_last && is_boundary()) &&
        unparsed_bytes_.size() < min_progress_size_) {

      return absl::OkStatus();
    }
    std::vector<uint8_t> buffer = std::move(unparsed_bytes_);
    return ParseInput(
        Input(nullptr, buffer.data(), buffer.data() + buffer.size(), bitsrc,
              state_.frame_error, state_.field_error),
        is_last, call_tracer);
  }
  return ParseInput(Input(slice.refcount, GRPC_SLICE_START_PTR(slice),
                          GRPC_SLICE_END_PTR(slice), bitsrc, state_.frame_error,
                          state_.field_error),
                    is_last, call_tracer);
}

grpc_error_handle HPackParser::ParseInput(
    Input input, bool is_last, CallTracerAnnotationInterface* call_tracer) {
  ParseInputInner(&input);
  if (is_last && is_boundary()) {
    if (state_.metadata_early_detection.Reject(state_.frame_length,
                                               input.bitsrc())) {
      HandleMetadataSoftSizeLimitExceeded(&input);
    }
    global_stats().IncrementHttp2MetadataSize(state_.frame_length);
    if (call_tracer != nullptr && call_tracer->IsSampled() &&
        metadata_buffer_ != nullptr) {
      MetadataSizesAnnotation metadata_sizes_annotation(
          metadata_buffer_, state_.metadata_early_detection.soft_limit(),
          state_.metadata_early_detection.hard_limit());
      call_tracer->RecordAnnotation(metadata_sizes_annotation);
    }
    if (!state_.frame_error.connection_error() &&
        (input.eof_error() || state_.parse_state != ParseState::kTop)) {
      state_.frame_error = HpackParseResult::IncompleteHeaderAtBoundaryError();
    }
    state_.frame_length = 0;
    return std::exchange(state_.frame_error, HpackParseResult()).Materialize();
  } else {
    if (input.eof_error() && !state_.frame_error.connection_error()) {
      unparsed_bytes_ = std::vector<uint8_t>(input.frontier(), input.end_ptr());
      min_progress_size_ = input.min_progress_size();
    }
    return state_.frame_error.Materialize();
  }
}

void HPackParser::ParseInputInner(Input* input) {
  switch (priority_) {
    case Priority::None:
      break;
    case Priority::Included: {
      if (input->remaining() < 5) {
        input->UnexpectedEOF(5);
        return;
      }
      input->Advance(5);
      input->UpdateFrontier();
      priority_ = Priority::None;
    }
  }
  while (!input->end_of_stream()) {
    if (GPR_UNLIKELY(
            !Parser(input, metadata_buffer_, state_, log_info_).Parse())) {
      return;
    }
    input->UpdateFrontier();
  }
}

void HPackParser::FinishFrame() { metadata_buffer_ = nullptr; }

void HPackParser::HandleMetadataSoftSizeLimitExceeded(Input* input) {
  input->SetErrorAndContinueParsing(
      HpackParseResult::SoftMetadataLimitExceededError(
          std::exchange(metadata_buffer_, nullptr), state_.frame_length,
          state_.metadata_early_detection.soft_limit()));
}

}
