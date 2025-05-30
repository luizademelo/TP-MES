
// Copyright 2025 gRPC authors.

#ifndef GRPC_SRC_CORE_EXT_TRANSPORT_CHTTP2_TRANSPORT_HEADER_ASSEMBLER_H
#define GRPC_SRC_CORE_EXT_TRANSPORT_CHTTP2_TRANSPORT_HEADER_ASSEMBLER_H

#include <grpc/support/port_platform.h>

#include <cstddef>
#include <cstdint>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "src/core/call/metadata_batch.h"
#include "src/core/ext/transport/chttp2/transport/frame.h"
#include "src/core/ext/transport/chttp2/transport/hpack_encoder.h"
#include "src/core/ext/transport/chttp2/transport/hpack_parser.h"
#include "src/core/ext/transport/chttp2/transport/http2_status.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/lib/slice/slice_buffer.h"
#include "src/core/util/shared_bit_gen.h"

namespace grpc_core {
namespace http2 {

#define ASSEMBLER_LOG DVLOG(3)

constexpr absl::string_view kAssemblerContiguousSequenceError =
    "RFC9113 : Field blocks MUST be transmitted as a contiguous sequence "
    "of frames, with no interleaved frames of any other type or from any "
    "other stream.";

constexpr absl::string_view kAssemblerMismatchedStreamId =
    "CONTINUATION frame has a different Stream Identifier than the preceeding "
    "HEADERS frame.";

constexpr absl::string_view kAssemblerHpackError =
    "RFC9113 : A decoding error in a field block MUST be treated as a "
    "connection error of type COMPRESSION_ERROR.";

constexpr absl::string_view kGrpcErrorMaxTwoHeaderFrames =
    "Too many header frames sent by peer";

constexpr uint8_t kMaxHeaderFrames = 2;

class HeaderAssembler {
 public:

  Http2Status AppendHeaderFrame(Http2HeaderFrame&& frame) {

    if (GPR_UNLIKELY(header_in_progress_)) {
      Cleanup();
      LOG(ERROR) << "Connection Error: " << kAssemblerContiguousSequenceError;
      return Http2Status::Http2ConnectionError(
          Http2ErrorCode::kProtocolError,
          std::string(kAssemblerContiguousSequenceError));
    }

    DCHECK_GT(frame.stream_id, 0u)
        << "RFC9113 : HEADERS frames MUST be associated with a stream.";
    if (GPR_UNLIKELY(frame.stream_id != stream_id_)) {
      Cleanup();
      LOG(ERROR) << "Connection Error: " << kAssemblerContiguousSequenceError;
      return Http2Status::Http2ConnectionError(
          Http2ErrorCode::kProtocolError,
          std::string(kAssemblerContiguousSequenceError));
    }

    ++num_headers_received_;
    if (GPR_UNLIKELY(num_headers_received_ > max_headers_)) {
      Cleanup();
      LOG(ERROR) << "Connection Error: " << kGrpcErrorMaxTwoHeaderFrames;
      return Http2Status::Http2ConnectionError(
          Http2ErrorCode::kInternalError,
          std::string(kGrpcErrorMaxTwoHeaderFrames));
    }

    const size_t current_len = frame.payload.Length();
    if constexpr (sizeof(size_t) == 4) {
      if (GPR_UNLIKELY(buffer_.Length() >= UINT32_MAX - current_len)) {
        Cleanup();
        LOG(ERROR)
            << "Stream Error: SliceBuffer overflow for 32 bit platforms.";
        return Http2Status::Http2StreamError(
            Http2ErrorCode::kInternalError,
            "Stream Error: SliceBuffer overflow for 32 bit platforms.");
      }
    }

    header_in_progress_ = true;

    frame.payload.MoveFirstNBytesIntoSliceBuffer(current_len, buffer_);
    ASSEMBLER_LOG << "AppendHeaderFrame " << current_len << " Bytes.";

    if (frame.end_headers) {
      ASSEMBLER_LOG << "AppendHeaderFrame end_headers";
      is_ready_ = true;
    }

    return Http2Status::Ok();
  }

  Http2Status AppendContinuationFrame(Http2ContinuationFrame&& frame) {

    if (GPR_UNLIKELY(!header_in_progress_)) {
      Cleanup();
      LOG(ERROR) << "Connection Error: " << kAssemblerContiguousSequenceError;
      return Http2Status::Http2ConnectionError(
          Http2ErrorCode::kProtocolError,
          std::string(kAssemblerContiguousSequenceError));
    }

    if (GPR_UNLIKELY(is_ready_ == true)) {

      Cleanup();
      LOG(ERROR) << "Connection Error: " << kAssemblerContiguousSequenceError;
      return Http2Status::Http2ConnectionError(
          Http2ErrorCode::kProtocolError,
          std::string(kAssemblerContiguousSequenceError));
    }

    if (GPR_UNLIKELY(frame.stream_id != stream_id_)) {
      Cleanup();
      LOG(ERROR) << "Connection Error: " << kAssemblerMismatchedStreamId;
      return Http2Status::Http2ConnectionError(
          Http2ErrorCode::kProtocolError,
          std::string(kAssemblerMismatchedStreamId));
    }

    const size_t current_len = frame.payload.Length();
    frame.payload.MoveFirstNBytesIntoSliceBuffer(current_len, buffer_);
    ASSEMBLER_LOG << "AppendContinuationFrame " << current_len << " Bytes.";

    if (frame.end_headers) {
      ASSEMBLER_LOG << "AppendHeaderFrame end_headers";
      is_ready_ = true;
    }

    return Http2Status::Ok();
  }

  ValueOrHttp2Status<Arena::PoolPtr<grpc_metadata_batch>> ReadMetadata(
      HPackParser& parser, bool is_initial_metadata, bool is_client) {
    ASSEMBLER_LOG << "ReadMetadata " << buffer_.Length() << " Bytes.";

    DCHECK_EQ(is_ready_, true);

    Arena::PoolPtr<grpc_metadata_batch> metadata =
        Arena::MakePooledForOverwrite<grpc_metadata_batch>();
    parser.BeginFrame(
         metadata.get(),

         std::numeric_limits<uint32_t>::max(),
         std::numeric_limits<uint32_t>::max(),
        is_initial_metadata ? HPackParser::Boundary::EndOfHeaders
                            : HPackParser::Boundary::EndOfStream,
        HPackParser::Priority::None,
        HPackParser::LogInfo{stream_id_,
                             is_initial_metadata
                                 ? HPackParser::LogInfo::Type::kHeaders
                                 : HPackParser::LogInfo::Type::kTrailers,
                             is_client});
    for (size_t i = 0; i < buffer_.Count(); i++) {
      absl::Status result = parser.Parse(
          buffer_.c_slice_at(i), i == buffer_.Count() - 1, SharedBitGen(),
          nullptr);
      if (GPR_UNLIKELY(!result.ok())) {
        Cleanup();
        LOG(ERROR) << "Connection Error: " << kAssemblerHpackError;
        return Http2Status::Http2ConnectionError(
            Http2ErrorCode::kCompressionError,
            std::string(kAssemblerHpackError));
      }
    }
    parser.FinishFrame();

    Cleanup();

    return ValueOrHttp2Status<Arena::PoolPtr<grpc_metadata_batch>>(
        std::move(metadata));
  }

  size_t GetBufferedHeadersLength() const { return buffer_.Length(); }

  bool IsReady() const { return is_ready_; }

  explicit HeaderAssembler(const uint32_t stream_id)
      : header_in_progress_(false),
        is_ready_(false),
        num_headers_received_(0),
        max_headers_(kMaxHeaderFrames),
        stream_id_(stream_id) {}

  ~HeaderAssembler() = default;

  HeaderAssembler(HeaderAssembler&& rvalue) = delete;
  HeaderAssembler& operator=(HeaderAssembler&& rvalue) = delete;
  HeaderAssembler(const HeaderAssembler&) = delete;
  HeaderAssembler& operator=(const HeaderAssembler&) = delete;

 private:
  void Cleanup() {
    buffer_.Clear();
    header_in_progress_ = false;
    is_ready_ = false;
  }

  bool header_in_progress_;
  bool is_ready_;
  uint8_t num_headers_received_;
  const uint8_t max_headers_;
  const uint32_t stream_id_;
  SliceBuffer buffer_;
};

class HeaderDisassembler {
 public:

  bool PrepareForSending(Arena::PoolPtr<grpc_metadata_batch>&& metadata,
                         HPackCompressor& encoder) {

    DCHECK(!is_done_);

    return encoder.EncodeRawHeaders(*metadata.get(), buffer_);
  }

  Http2Frame GetNextFrame(const uint32_t max_frame_length,
                          bool& out_end_headers) {
    if (buffer_.Length() == 0 || is_done_) {
      DCHECK(false) << "Calling code must check size using HasMoreData() "
                       "before GetNextFrame()";
    }
    out_end_headers = buffer_.Length() <= max_frame_length;
    SliceBuffer temp;
    if (out_end_headers) {
      is_done_ = true;
      temp.Swap(&buffer_);
    } else {
      buffer_.MoveFirstNBytesIntoSliceBuffer(max_frame_length, temp);
    }
    if (!did_send_header_frame_) {
      did_send_header_frame_ = true;
      return Http2HeaderFrame{stream_id_, out_end_headers, end_stream_,
                              std::move(temp)};
    } else {
      return Http2ContinuationFrame{stream_id_, out_end_headers,
                                    std::move(temp)};
    }
  }

  bool HasMoreData() const { return !is_done_ && buffer_.Length() > 0; }

  size_t GetBufferedLength() const { return buffer_.Length(); }

  explicit HeaderDisassembler(const uint32_t stream_id,
                              const bool is_trailing_metadata)
      : stream_id_(stream_id),
        end_stream_(is_trailing_metadata),
        did_send_header_frame_(false),
        is_done_(false) {}

  ~HeaderDisassembler() = default;

  HeaderDisassembler(HeaderDisassembler&& rvalue) = delete;
  HeaderDisassembler& operator=(HeaderDisassembler&& rvalue) = delete;
  HeaderDisassembler(const HeaderDisassembler&) = delete;
  HeaderDisassembler& operator=(const HeaderDisassembler&) = delete;

  size_t TestOnlyGetMainBufferLength() const { return buffer_.Length(); }

 private:
  const uint32_t stream_id_;
  const bool end_stream_;
  bool did_send_header_frame_;
  bool is_done_;

  SliceBuffer buffer_;
};

}
}

#endif
