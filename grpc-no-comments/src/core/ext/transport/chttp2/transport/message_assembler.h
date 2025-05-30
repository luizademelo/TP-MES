
// Copyright 2025 gRPC authors.

#ifndef GRPC_SRC_CORE_EXT_TRANSPORT_CHTTP2_TRANSPORT_MESSAGE_ASSEMBLER_H
#define GRPC_SRC_CORE_EXT_TRANSPORT_CHTTP2_TRANSPORT_MESSAGE_ASSEMBLER_H

#include <cstdint>
#include <utility>

#include "absl/log/check.h"
#include "src/core/call/message.h"
#include "src/core/ext/transport/chttp2/transport/frame.h"
#include "src/core/ext/transport/chttp2/transport/http2_status.h"
#include "src/core/lib/resource_quota/arena.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/lib/slice/slice_buffer.h"
#include "src/core/util/ref_counted_ptr.h"

namespace grpc_core {
namespace http2 {

constexpr uint32_t kOneGb = (1024u * 1024u * 1024u);

class GrpcMessageAssembler {
 public:

  absl::Status AppendNewDataFrame(SliceBuffer& payload,
                                  const bool is_end_stream) {
    DCHECK(!is_end_stream_)
        << "Calling this function when a previous frame was marked as the last "
           "frame does not make sense.";
    is_end_stream_ = is_end_stream;
    if constexpr (sizeof(size_t) == 4) {
      if (GPR_UNLIKELY(message_buffer_.Length() >=
                       UINT32_MAX - payload.Length())) {

        return absl::Status(
            absl::StatusCode::kInternal,
            "Stream Error: SliceBuffer overflow for 32 bit platforms.");
      }
    }
    payload.MoveFirstNBytesIntoSliceBuffer(payload.Length(), message_buffer_);
    DCHECK_EQ(payload.Length(), 0u);
    return absl::OkStatus();
  }

  absl::StatusOr<MessageHandle> ExtractMessage() {
    const size_t current_len = message_buffer_.Length();
    if (current_len < kGrpcHeaderSizeInBytes) {
      return ReturnNullOrError();
    }
    GrpcMessageHeader header = ExtractGrpcHeader(message_buffer_);
    if constexpr (sizeof(size_t) == 4) {
      if (GPR_UNLIKELY(header.length > kOneGb)) {

        return absl::Status(
            absl::StatusCode::kInternal,
            "Stream Error: SliceBuffer overflow for 32 bit platforms.");
      }
    }
    if (GPR_LIKELY(current_len - kGrpcHeaderSizeInBytes >= header.length)) {
      SliceBuffer discard;
      message_buffer_.MoveFirstNBytesIntoSliceBuffer(kGrpcHeaderSizeInBytes,
                                                     discard);
      discard.Clear();

      MessageHandle grpc_message = Arena::MakePooled<Message>();
      message_buffer_.MoveFirstNBytesIntoSliceBuffer(
          header.length, *(grpc_message->payload()));
      uint32_t& flag = grpc_message->mutable_flags();
      flag = header.flags;
      return grpc_message;
    }
    return ReturnNullOrError();
  }

 private:
  absl::StatusOr<MessageHandle> ReturnNullOrError() {

    if (GPR_UNLIKELY(is_end_stream_ && message_buffer_.Length() > 0)) {
      return absl::InternalError("Incomplete gRPC frame received");
    }
    return nullptr;
  }
  bool is_end_stream_ = false;
  SliceBuffer message_buffer_;
};

constexpr uint32_t kMaxMessageBatchSize = (16 * 1024u);

class GrpcMessageDisassembler {
 public:

  GrpcMessageDisassembler() = default;

  void PrepareSingleMessageForSending(MessageHandle message) {
    DCHECK_EQ(GetBufferedLength(), 0u);
    PrepareMessageForSending(std::move(message));
  }

  void PrepareBatchedMessageForSending(MessageHandle message) {
    PrepareMessageForSending(std::move(message));
    DCHECK_LE(GetBufferedLength(), kMaxMessageBatchSize)
        << "Avoid batches larger than " << kMaxMessageBatchSize << "bytes";
  }

  size_t GetBufferedLength() const { return message_.Length(); }

  Http2DataFrame GenerateNextFrame(const uint32_t stream_id,
                                   const uint32_t max_length,
                                   const bool is_end_stream = false) {
    DCHECK_GT(max_length, 0u);
    DCHECK_GT(GetBufferedLength(), 0u);
    SliceBuffer temp;
    const uint32_t current_length =
        message_.Length() >= max_length ? max_length : message_.Length();
    message_.MoveFirstNBytesIntoSliceBuffer(current_length, temp);
    return Http2DataFrame{stream_id, is_end_stream, std::move(temp)};
  }

  Http2DataFrame GenerateEmptyEndFrame(const uint32_t stream_id) {

    SliceBuffer temp;
    return Http2DataFrame{stream_id, true, std::move(temp)};
  }

 private:
  void PrepareMessageForSending(MessageHandle message) {
    AppendGrpcHeaderToSliceBuffer(message_, message->flags(),
                                  message->payload()->Length());
    message_.Append(*(message->payload()));
  }

  SliceBuffer message_;
};

}
}

#endif
