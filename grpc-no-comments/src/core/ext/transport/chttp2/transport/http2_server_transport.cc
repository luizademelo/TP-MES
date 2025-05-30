
// Copyright 2024 gRPC authors.

#include "src/core/ext/transport/chttp2/transport/http2_server_transport.h"

#include <grpc/event_engine/event_engine.h>
#include <grpc/support/port_platform.h>

#include <memory>
#include <utility>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/status/status.h"
#include "src/core/call/call_destination.h"
#include "src/core/ext/transport/chttp2/transport/frame.h"
#include "src/core/ext/transport/chttp2/transport/hpack_encoder.h"
#include "src/core/ext/transport/chttp2/transport/hpack_parser.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/debug/trace_impl.h"
#include "src/core/lib/promise/loop.h"
#include "src/core/lib/promise/match_promise.h"
#include "src/core/lib/promise/party.h"
#include "src/core/lib/promise/poll.h"
#include "src/core/lib/promise/promise.h"
#include "src/core/lib/promise/try_seq.h"
#include "src/core/lib/resource_quota/arena.h"
#include "src/core/lib/slice/slice_buffer.h"
#include "src/core/lib/transport/promise_endpoint.h"
#include "src/core/lib/transport/transport.h"
#include "src/core/util/ref_counted.h"

namespace grpc_core {
namespace http2 {

#define HTTP2_SERVER_DLOG \
  DLOG_IF(INFO, GRPC_TRACE_FLAG_ENABLED(http2_ph2_transport))

using grpc_event_engine::experimental::EventEngine;

constexpr int kMpscSize = 10;

void Http2ServerTransport::SetCallDestination(
    RefCountedPtr<UnstartedCallDestination> call_destination) {

  CHECK(call_destination_ == nullptr);
  CHECK(call_destination != nullptr);
  call_destination_ = call_destination;

}

void Http2ServerTransport::PerformOp(GRPC_UNUSED grpc_transport_op*) {
  HTTP2_SERVER_DLOG << "Http2ServerTransport PerformOp Begin";

  HTTP2_SERVER_DLOG << "Http2ServerTransport PerformOp End";
}

void Http2ServerTransport::Orphan() {
  HTTP2_SERVER_DLOG << "Http2ServerTransport Orphan Begin";

  general_party_.reset();
  Unref();
  HTTP2_SERVER_DLOG << "Http2ServerTransport Orphan End";
}

void Http2ServerTransport::AbortWithError() {
  HTTP2_SERVER_DLOG << "Http2ServerTransport AbortWithError Begin";

  HTTP2_SERVER_DLOG << "Http2ServerTransport AbortWithError End";
}

Http2Status ProcessHttp2DataFrame(Http2DataFrame frame) {

  HTTP2_SERVER_DLOG << "Http2ServerTransport ProcessHttp2DataFrame Factory";

  HTTP2_SERVER_DLOG
      << "Http2ServerTransport ProcessHttp2DataFrame Promise { stream_id="
      << frame.stream_id << ", end_stream=" << frame.end_stream
      << ", payload=" << frame.payload.JoinIntoString() << "}";
  return Http2Status::Ok();
}

Http2Status ProcessHttp2HeaderFrame(Http2HeaderFrame frame) {

  HTTP2_SERVER_DLOG << "Http2ServerTransport ProcessHttp2HeaderFrame Factory";

  HTTP2_SERVER_DLOG
      << "Http2ServerTransport ProcessHttp2HeaderFrame Promise { stream_id="
      << frame.stream_id << ", end_headers=" << frame.end_headers
      << ", end_stream=" << frame.end_stream
      << ", payload=" << frame.payload.JoinIntoString() << " }";
  return Http2Status::Ok();
}

Http2Status ProcessHttp2RstStreamFrame(Http2RstStreamFrame frame) {

  HTTP2_SERVER_DLOG
      << "Http2ServerTransport ProcessHttp2RstStreamFrame Factory";

  HTTP2_SERVER_DLOG
      << "Http2ServerTransport ProcessHttp2RstStreamFrame Promise{ stream_id="
      << frame.stream_id << ", error_code=" << frame.error_code << " }";
  return Http2Status::Ok();
}

Http2Status ProcessHttp2SettingsFrame(Http2SettingsFrame frame) {

  HTTP2_SERVER_DLOG << "Http2ServerTransport ProcessHttp2SettingsFrame Factory";

  HTTP2_SERVER_DLOG
      << "Http2ServerTransport ProcessHttp2SettingsFrame Promise { ack="
      << frame.ack << ", settings length=" << frame.settings.size() << "}";
  return Http2Status::Ok();
}

Http2Status ProcessHttp2PingFrame(Http2PingFrame frame) {

  HTTP2_SERVER_DLOG << "Http2ServerTransport ProcessHttp2PingFrame Factory";

  HTTP2_SERVER_DLOG
      << "Http2ServerTransport ProcessHttp2PingFrame Promise { ack="
      << frame.ack << ", opaque=" << frame.opaque << " }";
  return Http2Status::Ok();
}

Http2Status ProcessHttp2GoawayFrame(Http2GoawayFrame frame) {

  HTTP2_SERVER_DLOG << "Http2ServerTransport ProcessHttp2GoawayFrame Factory";

  HTTP2_SERVER_DLOG << "Http2ServerTransport ProcessHttp2GoawayFrame Promise { "
                       "last_stream_id="
                    << frame.last_stream_id
                    << ", error_code=" << frame.error_code
                    << ", debug_data=" << frame.debug_data.as_string_view()
                    << "}";
  return Http2Status::Ok();
}

Http2Status ProcessHttp2WindowUpdateFrame(Http2WindowUpdateFrame frame) {

  HTTP2_SERVER_DLOG
      << "Http2ServerTransport ProcessHttp2WindowUpdateFrame Factory";

  HTTP2_SERVER_DLOG
      << "Http2ServerTransport ProcessHttp2WindowUpdateFrame Promise { "
         " stream_id="
      << frame.stream_id << ", increment=" << frame.increment << "}";
  return Http2Status::Ok();
}

Http2Status ProcessHttp2ContinuationFrame(Http2ContinuationFrame frame) {

  HTTP2_SERVER_DLOG
      << "Http2ServerTransport ProcessHttp2ContinuationFrame Factory";

  HTTP2_SERVER_DLOG
      << "Http2ServerTransport ProcessHttp2ContinuationFrame Promise { "
         "stream_id="
      << frame.stream_id << ", end_headers=" << frame.end_headers
      << ", payload=" << frame.payload.JoinIntoString() << " }";
  return Http2Status::Ok();
}

Http2Status ProcessHttp2SecurityFrame(Http2SecurityFrame frame) {
  HTTP2_SERVER_DLOG << "Http2ServerTransport ProcessHttp2SecurityFrame Factory";

  HTTP2_SERVER_DLOG
      << "Http2ServerTransport ProcessHttp2SecurityFrame Promise { payload="
      << frame.payload.JoinIntoString() << " }";
  return Http2Status::Ok();
}

auto Http2ServerTransport::ProcessOneFrame(Http2Frame frame) {
  HTTP2_SERVER_DLOG << "Http2ServerTransport ProcessOneFrame Factory";
  return AssertResultType<Http2Status>(MatchPromise(
      std::move(frame),
      [](Http2DataFrame frame) {
        return ProcessHttp2DataFrame(std::move(frame));
      },
      [](Http2HeaderFrame frame) {
        return ProcessHttp2HeaderFrame(std::move(frame));
      },
      [](Http2RstStreamFrame frame) {
        return ProcessHttp2RstStreamFrame(frame);
      },
      [](Http2SettingsFrame frame) {
        return ProcessHttp2SettingsFrame(std::move(frame));
      },
      [](Http2PingFrame frame) { return ProcessHttp2PingFrame(frame); },
      [](Http2GoawayFrame frame) {
        return ProcessHttp2GoawayFrame(std::move(frame));
      },
      [](Http2WindowUpdateFrame frame) {
        return ProcessHttp2WindowUpdateFrame(frame);
      },
      [](Http2ContinuationFrame frame) {
        return ProcessHttp2ContinuationFrame(std::move(frame));
      },
      [](Http2SecurityFrame frame) {
        return ProcessHttp2SecurityFrame(std::move(frame));
      },
      [](GRPC_UNUSED Http2UnknownFrame frame) {

        return Http2Status::Ok();
      },
      [](GRPC_UNUSED Http2EmptyFrame frame) {
        LOG(DFATAL)
            << "ParseFramePayload should never return a Http2EmptyFrame";
        return Http2Status::Ok();
      }));
}

auto Http2ServerTransport::ReadAndProcessOneFrame() {
  HTTP2_SERVER_DLOG << "Http2ServerTransport ReadAndProcessOneFrame Factory";
  return AssertResultType<absl::Status>(TrySeq(

      endpoint_.ReadSlice(kFrameHeaderSize),

      [](Slice header_bytes) -> Http2FrameHeader {
        HTTP2_SERVER_DLOG
            << "Http2ServerTransport ReadAndProcessOneFrame Parse "
            << header_bytes.as_string_view();
        return Http2FrameHeader::Parse(header_bytes.begin());
      },

      [this](Http2FrameHeader header) {
        HTTP2_SERVER_DLOG << "Http2ServerTransport ReadAndProcessOneFrame Read";
        current_frame_header_ = header;
        return AssertResultType<absl::StatusOr<SliceBuffer>>(
            endpoint_.Read(header.length));
      },

      [this](SliceBuffer payload) -> absl::StatusOr<Http2Frame> {
        HTTP2_SERVER_DLOG
            << "Http2ServerTransport ReadAndProcessOneFrame ParseFramePayload "
            << payload.JoinIntoString();
        ValueOrHttp2Status<Http2Frame> frame =
            ParseFramePayload(current_frame_header_, std::move(payload));
        if (frame.IsOk()) {
          return TakeValue(std::move(frame));
        }

        return HandleError(
            ValueOrHttp2Status<Http2Frame>::TakeStatus(std::move(frame)));
      },
      [this](GRPC_UNUSED Http2Frame frame) {
        HTTP2_SERVER_DLOG
            << "Http2ServerTransport ReadAndProcessOneFrame ProcessOneFrame";
        return Map(
            ProcessOneFrame(std::move(frame)),
            [self = RefAsSubclass<Http2ServerTransport>()](Http2Status status) {
              if (status.IsOk()) {
                return absl::OkStatus();
              }
              return self->HandleError(std::move(status));
            });
      }));
}

auto Http2ServerTransport::ReadLoop() {
  HTTP2_SERVER_DLOG << "Http2ServerTransport ReadLoop Factory";
  return AssertResultType<absl::Status>(Loop([this]() {
    return TrySeq(ReadAndProcessOneFrame(), []() -> LoopCtl<absl::Status> {
      HTTP2_SERVER_DLOG << "Http2ServerTransport ReadLoop Continue";
      return Continue();
    });
  }));
}

auto Http2ServerTransport::OnReadLoopEnded() {
  HTTP2_SERVER_DLOG << "Http2ServerTransport OnReadLoopEnded Factory";
  return [self = RefAsSubclass<Http2ServerTransport>()](absl::Status status) {

    HTTP2_SERVER_DLOG << "Http2ServerTransport OnReadLoopEnded Promise Status="
                      << status;
    GRPC_UNUSED absl::Status error_status =
        self->HandleError(Http2Status::AbslConnectionError(
            status.code(), std::string(status.message())));
  };
}

auto Http2ServerTransport::WriteFromQueue() {
  HTTP2_SERVER_DLOG << "Http2ServerTransport WriteFromQueue Factory";
  return []() -> Poll<absl::Status> {

    HTTP2_SERVER_DLOG << "Http2ServerTransport WriteFromQueue Promise";
    return Pending{};
  };
}

auto Http2ServerTransport::WriteLoop() {
  HTTP2_SERVER_DLOG << "Http2ServerTransport WriteLoop Factory";
  return AssertResultType<absl::Status>(Loop([this]() {
    return TrySeq(WriteFromQueue(), []() -> LoopCtl<absl::Status> {
      HTTP2_SERVER_DLOG << "Http2ServerTransport WriteLoop Continue";
      return Continue();
    });
  }));
}

auto Http2ServerTransport::OnWriteLoopEnded() {
  HTTP2_SERVER_DLOG << "Http2ServerTransport OnWriteLoopEnded Factory";
  return [self = RefAsSubclass<Http2ServerTransport>()](absl::Status status) {

    HTTP2_SERVER_DLOG << "Http2ServerTransport OnWriteLoopEnded Promise Status="
                      << status;
    GRPC_UNUSED absl::Status error_status =
        self->HandleError(Http2Status::AbslConnectionError(
            status.code(), std::string(status.message())));
  };
}

Http2ServerTransport::Http2ServerTransport(
    PromiseEndpoint endpoint, GRPC_UNUSED const ChannelArgs& channel_args,
    std::shared_ptr<EventEngine> event_engine)
    : endpoint_(std::move(endpoint)), outgoing_frames_(kMpscSize) {

  HTTP2_SERVER_DLOG << "Http2ServerTransport Constructor Begin";

  auto general_party_arena = SimpleArenaAllocator(0)->MakeArena();
  general_party_arena->SetContext<EventEngine>(event_engine.get());
  general_party_ = Party::Make(std::move(general_party_arena));

  general_party_->Spawn("ReadLoop", ReadLoop(), OnReadLoopEnded());
  general_party_->Spawn("WriteLoop", WriteLoop(), OnWriteLoopEnded());
  HTTP2_SERVER_DLOG << "Http2ServerTransport Constructor End";
}

Http2ServerTransport::~Http2ServerTransport() {

  HTTP2_SERVER_DLOG << "Http2ServerTransport Destructor Begin";
  general_party_.reset();
  HTTP2_SERVER_DLOG << "Http2ServerTransport Destructor End";
}

}
}
