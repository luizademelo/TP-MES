// Copyright 2025 The gRPC authors.

#include "test/core/transport/chaotic_good/test_frame.h"

#include "test/core/transport/chaotic_good/test_frame.pb.h"

namespace grpc_core {
namespace chaotic_good {

namespace {
SliceBuffer MessageFramePayload(const chaotic_good_frame::MessageFrame& frame) {
  switch (frame.type_case()) {
    case chaotic_good_frame::MessageFrame::kData:
      return SliceBuffer(Slice::FromCopiedBuffer(frame.data()));
    case chaotic_good_frame::MessageFrame::kAllZerosLength:
      return SliceBuffer(Slice::ZeroContentsWithLength(
          std::min<size_t>(32 * 1024 * 1024, frame.all_zeros_length())));
    case chaotic_good_frame::MessageFrame::TYPE_NOT_SET:
      return SliceBuffer();
  }
}
}

Frame FrameFromTestFrame(const chaotic_good_frame::TestFrame& test_frame) {
  switch (test_frame.type_case()) {
    case chaotic_good_frame::TestFrame::kSettings:
      return SettingsFrame{test_frame.settings()};
    case chaotic_good_frame::TestFrame::kClientInitialMetadata:
      return ClientInitialMetadataFrame{
          test_frame.client_initial_metadata().payload(),
          test_frame.client_initial_metadata().stream_id()};
    case chaotic_good_frame::TestFrame::kServerInitialMetadata:
      return ServerInitialMetadataFrame{
          test_frame.server_initial_metadata().payload(),
          test_frame.server_initial_metadata().stream_id()};
    case chaotic_good_frame::TestFrame::kServerTrailingMetadata:
      return ServerTrailingMetadataFrame{
          test_frame.server_trailing_metadata().payload(),
          test_frame.server_trailing_metadata().stream_id()};
    case chaotic_good_frame::TestFrame::kBeginMessage:
      return BeginMessageFrame{test_frame.begin_message().payload(),
                               test_frame.begin_message().stream_id()};
    case chaotic_good_frame::TestFrame::kMessage:
      return MessageFrame{test_frame.message().stream_id(),
                          Arena::MakePooled<Message>(
                              MessageFramePayload(test_frame.message()), 0)};
    case chaotic_good_frame::TestFrame::kMessageChunk:
      return MessageChunkFrame{test_frame.message_chunk().stream_id(),
                               MessageFramePayload(test_frame.message_chunk())};
    case chaotic_good_frame::TestFrame::kClientEndOfStream:
      return ClientEndOfStream{test_frame.client_end_of_stream().stream_id()};
    case chaotic_good_frame::TestFrame::kCancel:
      return CancelFrame{test_frame.cancel().stream_id()};
    case chaotic_good_frame::TestFrame::TYPE_NOT_SET:
      return CancelFrame{0};
  }
}

}
}
