Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

// Header files for HPACK encoder implementation
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
// Size of HTTP/2 frame header (9 bytes)
constexpr size_t kHeadersFrameHeaderSize = 9;
}

// Helper function to fill HTTP/2 frame header
// p: pointer to buffer where header will be written
// type: frame type
// id: stream ID
// len: length of frame payload
// flags: frame flags
static void FillHeader(uint8_t* p, uint8_t type, uint32_t id, size_t len,
                       uint8_t flags) {
  // Validate length doesn't exceed 24-bit maximum (16MB)
  DCHECK_LE(len, 16777216u);
  // Write 24-bit length in big-endian
  *p++ = static_cast<uint8_t>(len >> 16);
  *p++ = static_cast<uint8_t>(len >> 8);
  *p++ = static_cast<uint8_t>(len);
  // Write frame type, flags, and 32-bit stream ID in big-endian
  *p++ = type;
  *p++ = flags;
  *p++ = static_cast<uint8_t>(id >> 24);
  *p++ = static_cast<uint8_t>(id >> 16);
  *p++ = static_cast<uint8_t>(id >> 8);
  *p++ = static_cast<uint8_t>(id);
}

// Frame raw headers into HTTP/2 HEADERS/CONTINUATION frames
// options: encoding options including stream ID, max frame size, etc.
// raw: input slice buffer containing raw headers
// output: output slice buffer where framed data will be written
void HPackCompressor::Frame(const EncodeHeaderOptions& options,
                            SliceBuffer& raw, grpc_slice_buffer* output) {
  uint8_t frame_type = GRPC_CHTTP2_FRAME_HEADER;
  uint8_t flags = 0;

  // Set END_STREAM flag if specified in options
  if (options.is_end_of_stream) {
    flags |= GRPC_CHTTP2_DATA_FLAG_END_STREAM;
  }
  
  // Record outgoing bytes for tracing
  options.call_tracer->RecordOutgoingBytes({0, 0, raw.Length()});
  
  // Process all data, potentially splitting across multiple frames
  while (frame_type == GRPC_CHTTP2_FRAME_HEADER || raw.Length() > 0) {
    // Determine length for this frame
    size_t len = raw.Length();
    if (len <= options.max_frame_size) {
      // If all data fits, set END_HEADERS flag
      flags |= GRPC_CHTTP2_DATA_FLAG_END_HEADERS;
    } else {
      // Otherwise split across multiple frames
      len = options.max_frame_size;
    }
    
    // Write frame header
    FillHeader(grpc_slice_buffer_tiny_add(output, kHeadersFrameHeaderSize),
               frame_type, options.stream_id, len, flags);
    options.call_tracer->RecordOutgoingBytes({kHeadersFrameHeaderSize, 0, 0});
    
    // Add trace event for this frame
    options.ztrace_collector->Append([&]() {
      return H2HeaderTrace<false>{
          options.stream_id, (flags & GRPC_CHTTP2_DATA_FLAG_END_HEADERS) != 0,
          (flags & GRPC_CHTTP2_DATA_FLAG_END_STREAM) != 0,
          frame_type == GRPC_CHTTP2_FRAME_CONTINUATION,
          static_cast<uint32_t>(len)};
    });
    
    // Move data from raw buffer to output buffer
    grpc_slice_buffer_move_first(raw.c_slice_buffer(), len, output);

    // Subsequent frames will be CONTINUATION frames
    frame_type = GRPC_CHTTP2_FRAME_CONTINUATION;
    flags = 0;
  }
}

// Set maximum usable size for HPACK table
void HPackCompressor::SetMaxUsableSize(uint32_t max_table_size) {
  max_usable_size_ = max_table_size;
  SetMaxTableSize(std::min(table_.max_size(), max_table_size));
}

// Set maximum size for HPACK table
void HPackCompressor::SetMaxTableSize(uint32_t max_table_size) {
  if (table_.SetMaxSize(std::min(max_usable_size_, max_table_size))) {
    // If table size changed, advertise the change
    advertise_table_size_change_ = true;
    GRPC_TRACE_LOG(http, INFO)
        << "set max table size from encoder to " << max_table_size;
  }
}

namespace {
// Structure representing a wire value with encoding information
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

// Get wire representation of a value based on encoding requirements
WireValue GetWireValue(Slice value, bool true_binary_enabled, bool is_bin_hdr) {
  if (is_bin_hdr) {
    if (true_binary_enabled) {
      // For true binary: prefix with null byte, no huffman encoding
      return WireValue(0x00, true, std::move(value));
    } else {
      // For base64 encoded binary: huffman compress and base64 encode
      uint32_t hpack_length;
      Slice output(grpc_chttp2_base64_encode_and_huffman_compress(
          value.c_slice(), &hpack_length));
      return WireValue(0x80, false, std::move(output), hpack_length);
    }
  } else {
    // For non-binary: no special encoding
    return WireValue(0x00, false, std::move(value));
  }
}

// Traits for checking if a key is binary (with different levels of certainty)
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

// Class for handling binary string values in HPACK encoding
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

// Class for handling non-binary string values in HPACK encoding
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

// Class for handling string keys in HPACK encoding
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
// Emit an indexed header field (HPACK indexed representation)
void Encoder::EmitIndexed(uint32_t elem_index) {
  VarintWriter<1> w(elem_index);
  w.Write(0x80, output_.AddTiny(w.length()));
}

// Emit literal header field with incremental indexing (non-binary)
uint32_t Encoder::EmitLitHdrWithNonBinaryStringKeyIncIdx(Slice key_slice,
                                                         Slice value_slice) {
  auto key_len = key_slice.length();
  auto value_len = value_slice.length();
  StringKey key(std::move(key_slice));
  key.WritePrefix(0x40, output_.AddTiny(key.prefix_length()));
  output_.Append(key.key());
  NonBinaryStringValue emit(std::move(value_slice));
  emit.WritePrefix(output_.AddTiny(emit.prefix_length()));

  // Allocate index in HPACK table for this entry
  uint32_t index = compressor_->table_.AllocateIndex(
      key_len + value_len + hpack_constants::kEntryOverhead);
  output_.Append(emit.data());
  return index;
}

// Emit literal header field without indexing (binary)
void Encoder::EmitLitHdrWithBinaryStringKeyNotIdx(Slice key_slice,
                                                  Slice value_slice) {
  StringKey key(std::move(key_slice));
  key.WritePrefix(0x00, output_.AddTiny(key.prefix_length()));
  output_.Append(key.key());
  BinaryStringValue emit(std::move(value_slice), use_true_binary_metadata_);
  emit.WritePrefix(output_.AddTiny(emit.prefix_length()));
  output_.Append(emit.data());
}

// Emit literal header field with incremental indexing (binary)
uint32_t Encoder::EmitLitHdrWithBinaryStringKeyIncIdx(Slice key_slice,
                                                      Slice value_slice) {
  auto key_len = key_slice.length();
  StringKey key(std::move(key_slice));
  key.WritePrefix(0x40, output_.AddTiny(key.prefix_length()));
  output_.Append(key.key());
  BinaryStringValue emit(std::move(value_slice), use_true_binary_metadata_);
  emit.WritePrefix(output_.AddTiny(emit.prefix_length()));

  // Allocate index in HPACK table for this entry
  uint32_t index = compressor_->table_.AllocateIndex(
      key_len + emit.hpack_length() + hpack_constants::kEntryOverhead);
  output_.Append(emit.data());
  return index;
}

// Emit literal header field without indexing (binary, indexed key)
void Encoder::EmitLitHdrWithBinaryStringKeyNotIdx(uint32_t key_index,
                                                  Slice value_slice) {
  BinaryStringValue emit(std::move(value_slice), use_true_binary_metadata_);
  VarintWriter<4> key(key_index);
  uint8_t* data = output_.AddTiny(key.length() + emit.prefix_length());
  key.Write(0x00, data);
  emit.WritePrefix(data + key.length());
  output_.Append(emit.data());
}

// Emit literal header field without indexing (non-binary)
void Encoder::EmitLitHdrWithNonBinaryStringKeyNotIdx(Slice key_slice,
                                                     Slice value_slice) {
  StringKey key(std::move(key_slice));
  key.WritePrefix(0x00, output_.AddTiny(key.prefix_length()));
  output_.Append(key.key());
  NonBinaryStringValue emit(std::move(value_slice));
  emit.WritePrefix(output_.AddTiny(emit.prefix_length()));
  output_.Append(emit.data());
}

// Advertise HPACK table size change to peer
void Encoder::AdvertiseTableSizeChange() {
  VarintWriter<3> w(compressor_->table_.max_size());
  w.Write(0x20, output_.AddTiny(w.length()));
}

// Emit a header field from the slice index
void SliceIndex::EmitTo(absl::string_view key, const Slice& value,
                        Encoder* encoder) {
  auto& table = encoder->hpack_table();
  using It = std::vector<ValueIndex>::iterator;
  It prev = values_.end();
  size_t transport_length =
      key.length() + value.length() + hpack_constants::kEntryOverhead;
  
  // If entry is too large, emit without indexing
  if (transport_length > HPackEncoderTable::MaxEntrySize()) {
    encoder->EmitLitHdrWithNonBinaryStringKeyNotIdx(
        Slice::FromStaticString(key), value.Ref());
    return;
  }

  // Check if we've seen this value before
  for (It it = values_.begin(); it != values_.end(); ++it) {
    if (value == it->value) {
      // If we have a usable index, emit indexed representation
      if (table.ConvertibleToDynamicIndex(it->index)) {
        encoder->EmitIndexed(table.DynamicIndex(it->index));
      } else {
        // Otherwise emit literal with indexing
        it->index = encoder->EmitLitHdrWithNonBinaryStringKeyIncIdx(
            Slice::FromStaticString(key), value.Ref());
      }

      // Move this value to front of LRU
      if (prev != values_.end()) std::swap(*prev, *it);

      // Clean up any values that are no longer in the table
      while (!values_.empty() &&
             !table.ConvertibleToDynamicIndex(values_.back().index)) {
        values_.pop_back();
      }

      return;
    }
    prev = it;
  }

  // New value - emit literal with indexing and add to our index
  uint32_t index = encoder->EmitLitHdrWithNonBinaryStringKeyIncIdx(
      Slice::FromStaticString(key), value.Ref());
  values_.emplace_back(value.Ref(), index);
}

// Encode a header key-value pair
void Encoder::Encode(const Slice& key, const Slice& value) {
  // Handle binary headers differently
  if (absl::EndsWith(key.as_string_view(), "-bin")) {
    EmitLitHdrWithBinaryStringKeyNotIdx(key.Ref(), value.Ref());
  } else {
    EmitLitHdrWithNonBinaryStringKeyNotIdx(key.Ref(), value.Ref());
  }
}

// Specialized compressor for HTTP scheme metadata
void Compressor<HttpSchemeMetadata, HttpSchemeCompressor>::EncodeWith(
    HttpSchemeMetadata, HttpSchemeMetadata::ValueType value, Encoder* encoder) {
  switch (value) {
    case HttpSchemeMetadata::ValueType::kHttp:
      encoder->EmitIndexed(6);  // Index for ":scheme: http"
      break;
    case HttpSchemeMetadata::ValueType::kHttps:
      encoder->EmitIndexed(7);  // Index for ":scheme: https"
      break;
    case HttpSchemeMetadata::ValueType::kInvalid:
      LOG(ERROR) << "Not encoding bad http scheme";
      encoder->NoteEncodingError();
      break;
  }
}

// Specialized compressor for HTTP status metadata
void Compressor<HttpStatusMetadata, HttpStatusCompressor>::EncodeWith(
    HttpStatusMetadata, uint32_t status, Encoder* encoder) {
  // Check for common status codes that have indexed representations
  if (status == 200) {
    encoder->EmitIndexed(8);  // Index for ":status: 200"
    return;
  }
  uint8_t index = 0;
  switch (status) {
    case 204: index = 9; break;   // Index for ":status: 204"
    case 206: index = 10; break;  // Index for ":status: 206"
    case 304: index = 11; break;  // Index for ":status: 304"
    case 400: index = 12; break;  // Index for ":status: 400"
    case 404: index = 13; break;  // Index for ":status: 404"
    case 500: index = 14; break;  // Index for ":status: 500"
  }
  if (GPR_LIKELY(index != 0)) {
    encoder->EmitIndexed(index);
  } else {
    // For uncommon