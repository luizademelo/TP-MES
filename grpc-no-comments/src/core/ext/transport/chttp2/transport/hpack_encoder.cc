
// Copyright 2015 gRPC authors.

#include "src/core/ext/transport/chttp2/transport/hpack_encoder.h"

#include <grpc/slice.h>
#include <grpc/slice_buffer.h>
#include <grpc/support/port_platform.h>

#include <algorithm>
#include <cstdint>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "src/core/ext/transport/chttp2/transport/bin_encoder.h"
#include "src/core/ext/transport/chttp2/transport/hpack_constants.h"
#include "src/core/ext/transport/chttp2/transport/hpack_encoder_table.h"
#include "src/core/ext/transport/chttp2/transport/legacy_frame.h"
#include "src/core/ext/transport/chttp2/transport/varint.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/surface/validate_metadata.h"
#include "src/core/lib/transport/timeout_encoding.h"
#include "src/core/util/crash.h"

namespace grpc_core {

namespace {

constexpr size_t kHeadersFrameHeaderSize = 9;

}

static void FillHeader(uint8_t* p, uint8_t type, uint32_t id, size_t len,
                       uint8_t flags) {

  DCHECK_LE(len, 16777216u);
  *p++ = static_cast<uint8_t>(len >> 16);
  *p++ = static_cast<uint8_t>(len >> 8);
  *p++ = static_cast<uint8_t>(len);
  *p++ = type;
  *p++ = flags;
  *p++ = static_cast<uint8_t>(id >> 24);
  *p++ = static_cast<uint8_t>(id >> 16);
  *p++ = static_cast<uint8_t>(id >> 8);
  *p++ = static_cast<uint8_t>(id);
}

void HPackCompressor::Frame(const EncodeHeaderOptions& options,
                            SliceBuffer& raw, grpc_slice_buffer* output) {
  uint8_t frame_type = GRPC_CHTTP2_FRAME_HEADER;
  uint8_t flags = 0;

  if (options.is_end_of_stream) {
    flags |= GRPC_CHTTP2_DATA_FLAG_END_STREAM;
  }
  options.call_tracer->RecordOutgoingBytes({0, 0, raw.Length()});
  while (frame_type == GRPC_CHTTP2_FRAME_HEADER || raw.Length() > 0) {

    size_t len = raw.Length();
    if (len <= options.max_frame_size) {
      flags |= GRPC_CHTTP2_DATA_FLAG_END_HEADERS;
    } else {
      len = options.max_frame_size;
    }
    FillHeader(grpc_slice_buffer_tiny_add(output, kHeadersFrameHeaderSize),
               frame_type, options.stream_id, len, flags);
    options.call_tracer->RecordOutgoingBytes({kHeadersFrameHeaderSize, 0, 0});
    options.ztrace_collector->Append([&]() {
      return H2HeaderTrace<false>{
          options.stream_id, (flags & GRPC_CHTTP2_DATA_FLAG_END_HEADERS) != 0,
          (flags & GRPC_CHTTP2_DATA_FLAG_END_STREAM) != 0,
          frame_type == GRPC_CHTTP2_FRAME_CONTINUATION,
          static_cast<uint32_t>(len)};
    });
    grpc_slice_buffer_move_first(raw.c_slice_buffer(), len, output);

    frame_type = GRPC_CHTTP2_FRAME_CONTINUATION;
    flags = 0;
  }
}

void HPackCompressor::SetMaxUsableSize(uint32_t max_table_size) {
  max_usable_size_ = max_table_size;
  SetMaxTableSize(std::min(table_.max_size(), max_table_size));
}

void HPackCompressor::SetMaxTableSize(uint32_t max_table_size) {
  if (table_.SetMaxSize(std::min(max_usable_size_, max_table_size))) {
    advertise_table_size_change_ = true;
    GRPC_TRACE_LOG(http, INFO)
        << "set max table size from encoder to " << max_table_size;
  }
}

namespace {
struct WireValue {
  WireValue(uint8_t huffman_prefix, bool insert_null_before_wire_value,
            Slice slice)
      : data(std::move(slice)),
        huffman_prefix(huffman_prefix),
        insert_null_before_wire_value(insert_null_before_wire_value),
        length(data.length() + (insert_null_before_wire_value ? 1 : 0)),
        hpack_length(length) {}
  WireValue(uint8_t huffman_prefix, bool insert_null_before_wire_value,
            Slice slice, size_t hpack_length)
      : data(std::move(slice)),
        huffman_prefix(huffman_prefix),
        insert_null_before_wire_value(insert_null_before_wire_value),
        length(data.length() + (insert_null_before_wire_value ? 1 : 0)),
        hpack_length(hpack_length + (insert_null_before_wire_value ? 1 : 0)) {}
  Slice data;
  const uint8_t huffman_prefix;
  const bool insert_null_before_wire_value;
  const size_t length;
  const size_t hpack_length;
};

WireValue GetWireValue(Slice value, bool true_binary_enabled, bool is_bin_hdr) {
  if (is_bin_hdr) {
    if (true_binary_enabled) {
      return WireValue(0x00, true, std::move(value));
    } else {
      uint32_t hpack_length;
      Slice output(grpc_chttp2_base64_encode_and_huffman_compress(
          value.c_slice(), &hpack_length));
      return WireValue(0x80, false, std::move(output), hpack_length);
    }
  } else {

    return WireValue(0x00, false, std::move(value));
  }
}

struct DefinitelyInterned {
  static bool IsBinary(grpc_slice key) {
    return grpc_is_refcounted_slice_binary_header(key);
  }
};
struct UnsureIfInterned {
  static bool IsBinary(grpc_slice key) {
    return grpc_is_binary_header_internal(key);
  }
};

class BinaryStringValue {
 public:
  explicit BinaryStringValue(Slice value, bool use_true_binary_metadata)
      : wire_value_(
            GetWireValue(std::move(value), use_true_binary_metadata, true)),
        len_val_(wire_value_.length) {}

  size_t prefix_length() const {
    return len_val_.length() +
           (wire_value_.insert_null_before_wire_value ? 1 : 0);
  }

  void WritePrefix(uint8_t* prefix_data) {
    len_val_.Write(wire_value_.huffman_prefix, prefix_data);
    if (wire_value_.insert_null_before_wire_value) {
      prefix_data[len_val_.length()] = 0;
    }
  }

  Slice data() { return std::move(wire_value_.data); }

  uint32_t hpack_length() { return wire_value_.hpack_length; }

 private:
  WireValue wire_value_;
  VarintWriter<1> len_val_;
};

class NonBinaryStringValue {
 public:
  explicit NonBinaryStringValue(Slice value)
      : value_(std::move(value)), len_val_(value_.length()) {}

  size_t prefix_length() const { return len_val_.length(); }

  void WritePrefix(uint8_t* prefix_data) { len_val_.Write(0x00, prefix_data); }

  Slice data() { return std::move(value_); }

 private:
  Slice value_;
  VarintWriter<1> len_val_;
};

class StringKey {
 public:
  explicit StringKey(Slice key)
      : key_(std::move(key)), len_key_(key_.length()) {}

  size_t prefix_length() const { return 1 + len_key_.length(); }

  void WritePrefix(uint8_t type, uint8_t* data) {
    data[0] = type;
    len_key_.Write(0x00, data + 1);
  }

  Slice key() { return std::move(key_); }

 private:
  Slice key_;
  VarintWriter<1> len_key_;
};
}

namespace hpack_encoder_detail {
void Encoder::EmitIndexed(uint32_t elem_index) {
  VarintWriter<1> w(elem_index);
  w.Write(0x80, output_.AddTiny(w.length()));
}

uint32_t Encoder::EmitLitHdrWithNonBinaryStringKeyIncIdx(Slice key_slice,
                                                         Slice value_slice) {
  auto key_len = key_slice.length();
  auto value_len = value_slice.length();
  StringKey key(std::move(key_slice));
  key.WritePrefix(0x40, output_.AddTiny(key.prefix_length()));
  output_.Append(key.key());
  NonBinaryStringValue emit(std::move(value_slice));
  emit.WritePrefix(output_.AddTiny(emit.prefix_length()));

  uint32_t index = compressor_->table_.AllocateIndex(
      key_len + value_len + hpack_constants::kEntryOverhead);
  output_.Append(emit.data());
  return index;
}

void Encoder::EmitLitHdrWithBinaryStringKeyNotIdx(Slice key_slice,
                                                  Slice value_slice) {
  StringKey key(std::move(key_slice));
  key.WritePrefix(0x00, output_.AddTiny(key.prefix_length()));
  output_.Append(key.key());
  BinaryStringValue emit(std::move(value_slice), use_true_binary_metadata_);
  emit.WritePrefix(output_.AddTiny(emit.prefix_length()));
  output_.Append(emit.data());
}

uint32_t Encoder::EmitLitHdrWithBinaryStringKeyIncIdx(Slice key_slice,
                                                      Slice value_slice) {
  auto key_len = key_slice.length();
  StringKey key(std::move(key_slice));
  key.WritePrefix(0x40, output_.AddTiny(key.prefix_length()));
  output_.Append(key.key());
  BinaryStringValue emit(std::move(value_slice), use_true_binary_metadata_);
  emit.WritePrefix(output_.AddTiny(emit.prefix_length()));

  uint32_t index = compressor_->table_.AllocateIndex(
      key_len + emit.hpack_length() + hpack_constants::kEntryOverhead);
  output_.Append(emit.data());
  return index;
}

void Encoder::EmitLitHdrWithBinaryStringKeyNotIdx(uint32_t key_index,
                                                  Slice value_slice) {
  BinaryStringValue emit(std::move(value_slice), use_true_binary_metadata_);
  VarintWriter<4> key(key_index);
  uint8_t* data = output_.AddTiny(key.length() + emit.prefix_length());
  key.Write(0x00, data);
  emit.WritePrefix(data + key.length());
  output_.Append(emit.data());
}

void Encoder::EmitLitHdrWithNonBinaryStringKeyNotIdx(Slice key_slice,
                                                     Slice value_slice) {
  StringKey key(std::move(key_slice));
  key.WritePrefix(0x00, output_.AddTiny(key.prefix_length()));
  output_.Append(key.key());
  NonBinaryStringValue emit(std::move(value_slice));
  emit.WritePrefix(output_.AddTiny(emit.prefix_length()));
  output_.Append(emit.data());
}

void Encoder::AdvertiseTableSizeChange() {
  VarintWriter<3> w(compressor_->table_.max_size());
  w.Write(0x20, output_.AddTiny(w.length()));
}

void SliceIndex::EmitTo(absl::string_view key, const Slice& value,
                        Encoder* encoder) {
  auto& table = encoder->hpack_table();
  using It = std::vector<ValueIndex>::iterator;
  It prev = values_.end();
  size_t transport_length =
      key.length() + value.length() + hpack_constants::kEntryOverhead;
  if (transport_length > HPackEncoderTable::MaxEntrySize()) {
    encoder->EmitLitHdrWithNonBinaryStringKeyNotIdx(
        Slice::FromStaticString(key), value.Ref());
    return;
  }

  for (It it = values_.begin(); it != values_.end(); ++it) {
    if (value == it->value) {

      if (table.ConvertibleToDynamicIndex(it->index)) {

        encoder->EmitIndexed(table.DynamicIndex(it->index));
      } else {

        it->index = encoder->EmitLitHdrWithNonBinaryStringKeyIncIdx(
            Slice::FromStaticString(key), value.Ref());
      }

      if (prev != values_.end()) std::swap(*prev, *it);

      while (!values_.empty() &&
             !table.ConvertibleToDynamicIndex(values_.back().index)) {
        values_.pop_back();
      }

      return;
    }
    prev = it;
  }

  uint32_t index = encoder->EmitLitHdrWithNonBinaryStringKeyIncIdx(
      Slice::FromStaticString(key), value.Ref());
  values_.emplace_back(value.Ref(), index);
}

void Encoder::Encode(const Slice& key, const Slice& value) {
  if (absl::EndsWith(key.as_string_view(), "-bin")) {
    EmitLitHdrWithBinaryStringKeyNotIdx(key.Ref(), value.Ref());
  } else {
    EmitLitHdrWithNonBinaryStringKeyNotIdx(key.Ref(), value.Ref());
  }
}

void Compressor<HttpSchemeMetadata, HttpSchemeCompressor>::EncodeWith(
    HttpSchemeMetadata, HttpSchemeMetadata::ValueType value, Encoder* encoder) {
  switch (value) {
    case HttpSchemeMetadata::ValueType::kHttp:
      encoder->EmitIndexed(6);
      break;
    case HttpSchemeMetadata::ValueType::kHttps:
      encoder->EmitIndexed(7);
      break;
    case HttpSchemeMetadata::ValueType::kInvalid:
      LOG(ERROR) << "Not encoding bad http scheme";
      encoder->NoteEncodingError();
      break;
  }
}

void Compressor<HttpStatusMetadata, HttpStatusCompressor>::EncodeWith(
    HttpStatusMetadata, uint32_t status, Encoder* encoder) {
  if (status == 200) {
    encoder->EmitIndexed(8);
    return;
  }
  uint8_t index = 0;
  switch (status) {
    case 204:
      index = 9;
      break;
    case 206:
      index = 10;
      break;
    case 304:
      index = 11;
      break;
    case 400:
      index = 12;
      break;
    case 404:
      index = 13;
      break;
    case 500:
      index = 14;
      break;
  }
  if (GPR_LIKELY(index != 0)) {
    encoder->EmitIndexed(index);
  } else {
    encoder->EmitLitHdrWithNonBinaryStringKeyNotIdx(
        Slice::FromStaticString(":status"), Slice::FromInt64(status));
  }
}

void Compressor<HttpMethodMetadata, HttpMethodCompressor>::EncodeWith(
    HttpMethodMetadata, HttpMethodMetadata::ValueType method,
    Encoder* encoder) {
  switch (method) {
    case HttpMethodMetadata::ValueType::kPost:
      encoder->EmitIndexed(3);
      break;
    case HttpMethodMetadata::ValueType::kGet:
      encoder->EmitIndexed(2);
      break;
    case HttpMethodMetadata::ValueType::kPut:

      encoder->EmitLitHdrWithNonBinaryStringKeyNotIdx(
          Slice::FromStaticString(":method"), Slice::FromStaticString("PUT"));
      break;
    case HttpMethodMetadata::ValueType::kInvalid:
      LOG(ERROR) << "Not encoding bad http method";
      encoder->NoteEncodingError();
      break;
  }
}

void Encoder::EncodeAlwaysIndexed(uint32_t* index, absl::string_view key,
                                  Slice value, size_t) {
  if (compressor_->table_.ConvertibleToDynamicIndex(*index)) {
    EmitIndexed(compressor_->table_.DynamicIndex(*index));
  } else {
    *index = EmitLitHdrWithNonBinaryStringKeyIncIdx(
        Slice::FromStaticString(key), std::move(value));
  }
}

void Encoder::EncodeIndexedKeyWithBinaryValue(uint32_t* index,
                                              absl::string_view key,
                                              Slice value) {
  if (compressor_->table_.ConvertibleToDynamicIndex(*index)) {
    EmitLitHdrWithBinaryStringKeyNotIdx(
        compressor_->table_.DynamicIndex(*index), std::move(value));
  } else {
    *index = EmitLitHdrWithBinaryStringKeyIncIdx(Slice::FromStaticString(key),
                                                 std::move(value));
  }
}

void Encoder::EncodeRepeatingSliceValue(const absl::string_view& key,
                                        const Slice& slice, uint32_t* index,
                                        size_t max_compression_size) {
  if (hpack_constants::SizeForEntry(key.size(), slice.size()) >
      max_compression_size) {
    EmitLitHdrWithBinaryStringKeyNotIdx(Slice::FromStaticString(key),
                                        slice.Ref());
  } else {
    EncodeIndexedKeyWithBinaryValue(index, key, slice.Ref());
  }
}

void TimeoutCompressorImpl::EncodeWith(absl::string_view key,
                                       Timestamp deadline, Encoder* encoder) {
  const Timeout timeout = Timeout::FromDuration(deadline - Timestamp::Now());
  auto& table = encoder->hpack_table();
  for (size_t i = 0; i < kNumPreviousValues; i++) {
    const auto& previous = previous_timeouts_[i];
    if (!table.ConvertibleToDynamicIndex(previous.index)) continue;
    const double ratio = timeout.RatioVersus(previous.timeout);

    if (ratio > -3 && ratio <= 0) {
      encoder->EmitIndexed(table.DynamicIndex(previous.index));
      return;
    }
  }
  Slice encoded = timeout.Encode();
  uint32_t index = encoder->EmitLitHdrWithNonBinaryStringKeyIncIdx(
      Slice::FromStaticString(key), std::move(encoded));
  uint32_t i = next_previous_value_;
  ++next_previous_value_;
  previous_timeouts_[i % kNumPreviousValues] = PreviousTimeout{timeout, index};
}

Encoder::Encoder(HPackCompressor* compressor, bool use_true_binary_metadata,
                 SliceBuffer& output)
    : use_true_binary_metadata_(use_true_binary_metadata),
      compressor_(compressor),
      output_(output) {
  if (std::exchange(compressor_->advertise_table_size_change_, false)) {
    AdvertiseTableSizeChange();
  }
}

}
}
