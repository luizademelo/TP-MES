
// Copyright 2024 gRPC authors.

#include "src/core/ext/transport/chttp2/transport/http2_client_transport.h"

#include <grpc/event_engine/event_engine.h>
#include <grpc/support/port_platform.h>

#include <cstdint>
#include <memory>
#include <optional>
#include <utility>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/status/status.h"
#include "src/core/call/call_spine.h"
#include "src/core/ext/transport/chttp2/transport/frame.h"
#include "src/core/ext/transport/chttp2/transport/internal_channel_arg_names.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/promise/for_each.h"
#include "src/core/lib/promise/loop.h"
#include "src/core/lib/promise/map.h"
#include "src/core/lib/promise/match_promise.h"
#include "src/core/lib/promise/party.h"
#include "src/core/lib/promise/poll.h"
#include "src/core/lib/promise/promise.h"
#include "src/core/lib/promise/try_seq.h"
#include "src/core/lib/resource_quota/arena.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/lib/slice/slice_buffer.h"
#include "src/core/lib/transport/promise_endpoint.h"
#include "src/core/lib/transport/transport.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/sync.h"

namespace grpc_core {
namespace http2 {

using grpc_event_engine::experimental::EventEngine;

void Http2ClientTransport::PerformOp(GRPC_UNUSED grpc_transport_op* op) {
  HTTP2_CLIENT_DLOG << "Http2ClientTransport PerformOp Begin";

  HTTP2_CLIENT_DLOG << "Http2ClientTransport PerformOp End";
}

void Http2ClientTransport::Orphan() {
  HTTP2_CLIENT_DLOG << "Http2ClientTransport Orphan Begin";

  general_party_.reset();
  Unref();
  HTTP2_CLIENT_DLOG << "Http2ClientTransport Orphan End";
}

void Http2ClientTransport::AbortWithError() {
  HTTP2_CLIENT_DLOG << "Http2ClientTransport AbortWithError Begin";

  HTTP2_CLIENT_DLOG << "Http2ClientTransport AbortWithError End";
}

Http2Status Http2ClientTransport::ProcessHttp2DataFrame(Http2DataFrame frame) {

  HTTP2_TRANSPORT_DLOG << "Http2Transport ProcessHttp2DataFrame Factory";

  HTTP2_TRANSPORT_DLOG
      << "Http2Transport ProcessHttp2DataFrame Promise { stream_id="
      << frame.stream_id << ", end_stream=" << frame.end_stream
      << ", payload=" << frame.payload.JoinIntoString() << "}";
  ping_manager_.ReceivedDataFrame();
  return Http2Status::Ok();
}

Http2Status Http2ClientTransport::ProcessHttp2HeaderFrame(
    Http2HeaderFrame frame) {

  HTTP2_TRANSPORT_DLOG << "Http2Transport ProcessHttp2HeaderFrame Factory";

  HTTP2_TRANSPORT_DLOG
      << "Http2Transport ProcessHttp2HeaderFrame Promise { stream_id="
      << frame.stream_id << ", end_headers=" << frame.end_headers
      << ", end_stream=" << frame.end_stream
      << ", payload=" << frame.payload.JoinIntoString() << " }";
  ping_manager_.ReceivedDataFrame();
  return Http2Status::Ok();
}

Http2Status Http2ClientTransport::ProcessHttp2RstStreamFrame(
    Http2RstStreamFrame frame) {

  HTTP2_TRANSPORT_DLOG << "Http2Transport ProcessHttp2RstStreamFrame Factory";

  HTTP2_TRANSPORT_DLOG
      << "Http2Transport ProcessHttp2RstStreamFrame Promise{ stream_id="
      << frame.stream_id << ", error_code=" << frame.error_code << " }";
  return Http2Status::Ok();
}

Http2Status Http2ClientTransport::ProcessHttp2SettingsFrame(
    Http2SettingsFrame frame) {

  HTTP2_TRANSPORT_DLOG << "Http2Transport ProcessHttp2SettingsFrame Factory";

  HTTP2_TRANSPORT_DLOG
      << "Http2Transport ProcessHttp2SettingsFrame Promise { ack=" << frame.ack
      << ", settings length=" << frame.settings.size() << "}";
  return Http2Status::Ok();
}

auto Http2ClientTransport::ProcessHttp2PingFrame(Http2PingFrame frame) {

  HTTP2_TRANSPORT_DLOG << "Http2Transport ProcessHttp2PingFrame { ack="
                       << frame.ack << ", opaque=" << frame.opaque << " }";
  return AssertResultType<Http2Status>(If(
      frame.ack,
      [self = RefAsSubclass<Http2ClientTransport>(), opaque = frame.opaque]() {

        if (!self->ping_manager_.AckPing(opaque)) {
          HTTP2_TRANSPORT_DLOG << "Unknown ping resoponse received for ping id="
                               << opaque;
        }
        return Immediate(Http2Status::Ok());
      },
      [self = RefAsSubclass<Http2ClientTransport>(), opaque = frame.opaque]() {

        self->pending_ping_acks_.push_back(opaque);

        return Map(self->TriggerWriteCycle(), [](absl::Status status) {
          return (status.ok())
                     ? Http2Status::Ok()
                     : Http2Status::AbslConnectionError(
                           status.code(), std::string(status.message()));
        });
      }));
}

Http2Status Http2ClientTransport::ProcessHttp2GoawayFrame(
    Http2GoawayFrame frame) {

  HTTP2_TRANSPORT_DLOG << "Http2Transport ProcessHttp2GoawayFrame Factory";

  HTTP2_TRANSPORT_DLOG << "Http2Transport ProcessHttp2GoawayFrame Promise { "
                          "last_stream_id="
                       << frame.last_stream_id
                       << ", error_code=" << frame.error_code
                       << ", debug_data=" << frame.debug_data.as_string_view()
                       << "}";
  return Http2Status::Ok();
}

Http2Status Http2ClientTransport::ProcessHttp2WindowUpdateFrame(
    Http2WindowUpdateFrame frame) {

  HTTP2_TRANSPORT_DLOG
      << "Http2Transport ProcessHttp2WindowUpdateFrame Factory";

  HTTP2_TRANSPORT_DLOG
      << "Http2Transport ProcessHttp2WindowUpdateFrame Promise { "
         " stream_id="
      << frame.stream_id << ", increment=" << frame.increment << "}";
  return Http2Status::Ok();
}

Http2Status Http2ClientTransport::ProcessHttp2ContinuationFrame(
    Http2ContinuationFrame frame) {

  HTTP2_TRANSPORT_DLOG
      << "Http2Transport ProcessHttp2ContinuationFrame Factory";

  HTTP2_TRANSPORT_DLOG
      << "Http2Transport ProcessHttp2ContinuationFrame Promise { "
         "stream_id="
      << frame.stream_id << ", end_headers=" << frame.end_headers
      << ", payload=" << frame.payload.JoinIntoString() << " }";
  return Http2Status::Ok();
}

Http2Status Http2ClientTransport::ProcessHttp2SecurityFrame(
    Http2SecurityFrame frame) {
  HTTP2_TRANSPORT_DLOG << "Http2Transport ProcessHttp2SecurityFrame Factory";

  HTTP2_TRANSPORT_DLOG
      << "Http2Transport ProcessHttp2SecurityFrame Promise { payload="
      << frame.payload.JoinIntoString() << " }";
  return Http2Status::Ok();
}

auto Http2ClientTransport::ProcessOneFrame(Http2Frame frame) {
  HTTP2_CLIENT_DLOG << "Http2ClientTransport ProcessOneFrame Factory";
  return AssertResultType<Http2Status>(MatchPromise(
      std::move(frame),
      [this](Http2DataFrame frame) {
        return ProcessHttp2DataFrame(std::move(frame));
      },
      [this](Http2HeaderFrame frame) {
        return ProcessHttp2HeaderFrame(std::move(frame));
      },
      [this](Http2RstStreamFrame frame) {
        return ProcessHttp2RstStreamFrame(frame);
      },
      [this](Http2SettingsFrame frame) {
        return ProcessHttp2SettingsFrame(std::move(frame));
      },
      [this](Http2PingFrame frame) { return ProcessHttp2PingFrame(frame); },
      [this](Http2GoawayFrame frame) {
        return ProcessHttp2GoawayFrame(std::move(frame));
      },
      [this](Http2WindowUpdateFrame frame) {
        return ProcessHttp2WindowUpdateFrame(frame);
      },
      [this](Http2ContinuationFrame frame) {
        return ProcessHttp2ContinuationFrame(std::move(frame));
      },
      [this](Http2SecurityFrame frame) {
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

auto Http2ClientTransport::ReadAndProcessOneFrame() {
  HTTP2_CLIENT_DLOG << "Http2ClientTransport ReadAndProcessOneFrame Factory";
  return AssertResultType<absl::Status>(TrySeq(

      EndpointReadSlice(kFrameHeaderSize),

      [](Slice header_bytes) -> Http2FrameHeader {
        HTTP2_CLIENT_DLOG
            << "Http2ClientTransport ReadAndProcessOneFrame Parse "
            << header_bytes.as_string_view();
        return Http2FrameHeader::Parse(header_bytes.begin());
      },

      [this](Http2FrameHeader header) {
        HTTP2_CLIENT_DLOG << "Http2ClientTransport ReadAndProcessOneFrame Read";
        current_frame_header_ = header;
        return AssertResultType<absl::StatusOr<SliceBuffer>>(
            EndpointRead(header.length));
      },

      [this](SliceBuffer payload) -> absl::StatusOr<Http2Frame> {
        HTTP2_CLIENT_DLOG
            << "Http2ClientTransport ReadAndProcessOneFrame ParseFramePayload "
            << payload.JoinIntoString();
        ValueOrHttp2Status<Http2Frame> frame =
            ParseFramePayload(current_frame_header_, std::move(payload));
        if (!frame.IsOk()) {
          return HandleError(
              ValueOrHttp2Status<Http2Frame>::TakeStatus(std::move(frame)));
        }

        return TakeValue(std::move(frame));
      },
      [this](GRPC_UNUSED Http2Frame frame) {
        HTTP2_CLIENT_DLOG
            << "Http2ClientTransport ReadAndProcessOneFrame ProcessOneFrame";
        return AssertResultType<absl::Status>(Map(
            ProcessOneFrame(std::move(frame)),
            [self = RefAsSubclass<Http2ClientTransport>()](Http2Status status) {
              if (!status.IsOk()) {
                return self->HandleError(std::move(status));
              }

              return absl::OkStatus();
            }));
      }));
}

auto Http2ClientTransport::ReadLoop() {
  HTTP2_CLIENT_DLOG << "Http2ClientTransport ReadLoop Factory";
  return AssertResultType<absl::Status>(Loop([this]() {
    return TrySeq(ReadAndProcessOneFrame(), []() -> LoopCtl<absl::Status> {
      HTTP2_CLIENT_DLOG << "Http2ClientTransport ReadLoop Continue";
      return Continue();
    });
  }));
}

auto Http2ClientTransport::OnReadLoopEnded() {
  HTTP2_CLIENT_DLOG << "Http2ClientTransport OnReadLoopEnded Factory";
  return [self = RefAsSubclass<Http2ClientTransport>()](absl::Status status) {

    HTTP2_CLIENT_DLOG << "Http2ClientTransport OnReadLoopEnded Promise Status="
                      << status;
    GRPC_UNUSED absl::Status error =
        self->HandleError(Http2Status::AbslConnectionError(
            status.code(), std::string(status.message())));
  };
}

auto Http2ClientTransport::WriteFromQueue() {
  HTTP2_CLIENT_DLOG << "Http2ClientTransport WriteFromQueue Factory";
  return TrySeq(
      outgoing_frames_.NextBatch(),
      [self = RefAsSubclass<Http2ClientTransport>()](
          std::vector<Http2Frame> frames) {
        SliceBuffer output_buf;
        Serialize(absl::Span<Http2Frame>(frames), output_buf);
        uint64_t buffer_length = output_buf.Length();
        HTTP2_CLIENT_DLOG << "Http2ClientTransport WriteFromQueue Promise";
        return If(
            buffer_length > 0,
            [self, output_buffer = std::move(output_buf)]() mutable {
              self->bytes_sent_in_last_write_ = true;
              return self->endpoint_.Write(std::move(output_buffer),
                                           PromiseEndpoint::WriteArgs{});
            },
            [] { return absl::OkStatus(); });
      });
}

auto Http2ClientTransport::WriteLoop() {
  HTTP2_CLIENT_DLOG << "Http2ClientTransport WriteLoop Factory";
  return AssertResultType<absl::Status>(Loop([this]() {

    bytes_sent_in_last_write_ = false;
    return TrySeq(

        WriteFromQueue(),
        [self = RefAsSubclass<Http2ClientTransport>()] {
          return self->MaybeSendPing();
        },
        [self = RefAsSubclass<Http2ClientTransport>()] {
          return self->MaybeSendPingAcks();
        },
        [this]() -> LoopCtl<absl::Status> {

          if (bytes_sent_in_last_write_) {
            ping_manager_.ResetPingClock(true);
          }
          HTTP2_CLIENT_DLOG << "Http2ClientTransport WriteLoop Continue";
          return Continue();
        });
  }));
}

auto Http2ClientTransport::OnWriteLoopEnded() {
  HTTP2_CLIENT_DLOG << "Http2ClientTransport OnWriteLoopEnded Factory";
  return [self = RefAsSubclass<Http2ClientTransport>()](absl::Status status) {

    HTTP2_CLIENT_DLOG << "Http2ClientTransport OnWriteLoopEnded Promise Status="
                      << status;
    GRPC_UNUSED absl::Status error =
        self->HandleError(Http2Status::AbslConnectionError(
            status.code(), std::string(status.message())));
  };
}

Http2ClientTransport::Http2ClientTransport(
    PromiseEndpoint endpoint, GRPC_UNUSED const ChannelArgs& channel_args,
    std::shared_ptr<EventEngine> event_engine)
    : endpoint_(std::move(endpoint)),
      outgoing_frames_(kMpscSize),
      stream_id_mutex_( 1),
      bytes_sent_in_last_write_(false),
      keepalive_time_(std::max(
          Duration::Seconds(10),
          channel_args.GetDurationFromIntMillis(GRPC_ARG_KEEPALIVE_TIME_MS)
              .value_or(Duration::Infinity()))),

      keepalive_timeout_(std::max(
          Duration::Zero(),
          channel_args.GetDurationFromIntMillis(GRPC_ARG_KEEPALIVE_TIMEOUT_MS)
              .value_or(keepalive_time_ == Duration::Infinity()
                            ? Duration::Infinity()
                            : (Duration::Seconds(20))))),
      ping_timeout_(std::max(
          Duration::Zero(),
          channel_args.GetDurationFromIntMillis(GRPC_ARG_PING_TIMEOUT_MS)
              .value_or(keepalive_time_ == Duration::Infinity()
                            ? Duration::Infinity()
                            : Duration::Minutes(1)))),
      ping_manager_(channel_args, PingSystemInterfaceImpl::Make(this),
                    event_engine),
      keepalive_manager_(
          KeepAliveInterfaceImpl::Make(this),
          ((keepalive_timeout_ < ping_timeout_) ? keepalive_timeout_
                                                : Duration::Infinity()),
          keepalive_time_),
      keepalive_permit_without_calls_(false) {

  HTTP2_CLIENT_DLOG << "Http2ClientTransport Constructor Begin";

  auto general_party_arena = SimpleArenaAllocator(0)->MakeArena();
  general_party_arena->SetContext<EventEngine>(event_engine.get());
  general_party_ = Party::Make(std::move(general_party_arena));

  general_party_->Spawn("ReadLoop", ReadLoop(), OnReadLoopEnded());

  general_party_->Spawn("WriteLoop", WriteLoop(), OnWriteLoopEnded());

  keepalive_manager_.Spawn(general_party_.get());

  std::optional<Http2SettingsFrame> settings_frame =
      settings_.MaybeSendUpdate();
  if (settings_frame.has_value()) {
    general_party_->Spawn(
        "SendFirstSettingsFrame",
        [self = RefAsSubclass<Http2ClientTransport>(),
         frame = std::move(*settings_frame)]() mutable {
          return self->EnqueueOutgoingFrame(std::move(frame));
        },
        [](GRPC_UNUSED absl::Status status) {});
  }
  HTTP2_CLIENT_DLOG << "Http2ClientTransport Constructor End";
}

Http2ClientTransport::~Http2ClientTransport() {

  HTTP2_CLIENT_DLOG << "Http2ClientTransport Destructor Begin";
  HTTP2_CLIENT_DLOG << "Http2ClientTransport Destructor End";
}

RefCountedPtr<Http2ClientTransport::Stream> Http2ClientTransport::LookupStream(
    uint32_t stream_id) {
  MutexLock lock(&transport_mutex_);
  auto it = stream_list_.find(stream_id);
  if (it == stream_list_.end()) {
    HTTP2_CLIENT_DLOG
        << "Http2ClientTransport::LookupStream Stream not found stream_id="
        << stream_id;
    return nullptr;
  }
  return it->second;
}

bool Http2ClientTransport::MakeStream(CallHandler call_handler,
                                      const uint32_t stream_id) {

  MutexLock lock(&transport_mutex_);
  const bool on_done_added =
      call_handler.OnDone([self = RefAsSubclass<Http2ClientTransport>(),
                           stream_id](bool cancelled) {
        HTTP2_CLIENT_DLOG << "PH2: Client call " << self.get()
                          << " id=" << stream_id
                          << " done: cancelled=" << cancelled;
        if (cancelled) {

        }
        MutexLock lock(&self->transport_mutex_);
        self->stream_list_.erase(stream_id);
      });
  if (!on_done_added) return false;
  stream_list_.emplace(
      stream_id, MakeRefCounted<Stream>(std::move(call_handler), stream_id));
  return true;
}

auto Http2ClientTransport::CallOutboundLoop(
    CallHandler call_handler, const uint32_t stream_id,
    InterActivityMutex<uint32_t>::Lock lock ,
    ClientMetadataHandle metadata) {
  HTTP2_CLIENT_DLOG << "Http2ClientTransport CallOutboundLoop";

  auto send_message = [self = RefAsSubclass<Http2ClientTransport>(),
                       stream_id](MessageHandle message) mutable {

    SliceBuffer frame_payload;
    size_t payload_size = message->payload()->Length();
    AppendGrpcHeaderToSliceBuffer(frame_payload, message->flags(),
                                  payload_size);
    frame_payload.TakeAndAppend(*message->payload());
    Http2DataFrame frame{stream_id,  false,
                         std::move(frame_payload)};
    HTTP2_CLIENT_DLOG << "Http2ClientTransport CallOutboundLoop send_message";
    return self->EnqueueOutgoingFrame(std::move(frame));
  };

  SliceBuffer buf;
  encoder_.EncodeRawHeaders(*metadata.get(), buf);
  Http2Frame frame = Http2HeaderFrame{stream_id,  true,
                                       false, std::move(buf)};
  return GRPC_LATENT_SEE_PROMISE(
      "Ph2CallOutboundLoop",
      TrySeq(
          EnqueueOutgoingFrame(std::move(frame)),
          [call_handler, send_message, lock = std::move(lock)]() {

            return ForEach(MessagesFrom(call_handler), send_message);
          },

          [self = RefAsSubclass<Http2ClientTransport>(), stream_id]() mutable {

            Http2DataFrame frame{stream_id,  true, SliceBuffer()};
            return self->EnqueueOutgoingFrame(std::move(frame));
          },
          [call_handler]() mutable {
            return Map(call_handler.WasCancelled(), [](bool cancelled) {
              HTTP2_CLIENT_DLOG << "Http2ClientTransport PH2CallOutboundLoop"
                                   " End with cancelled="
                                << cancelled;
              return (cancelled) ? absl::CancelledError() : absl::OkStatus();
            });
          }));
}

void Http2ClientTransport::StartCall(CallHandler call_handler) {
  HTTP2_CLIENT_DLOG << "Http2ClientTransport StartCall Begin";
  call_handler.SpawnGuarded(
      "OutboundLoop",
      TrySeq(
          call_handler.PullClientInitialMetadata(),
          [self = RefAsSubclass<Http2ClientTransport>()](
              ClientMetadataHandle metadata) {

            return Staple(self->stream_id_mutex_.Acquire(),
                          std::move(metadata));
          },
          [self = RefAsSubclass<Http2ClientTransport>(),
           call_handler](auto args ) mutable {

            const uint32_t stream_id = self->NextStreamId(std::get<0>(args));
            return If(
                self->MakeStream(call_handler, stream_id),
                [self, call_handler, stream_id,
                 args = std::move(args)]() mutable {
                  return Map(
                      self->CallOutboundLoop(call_handler, stream_id,
                                             std::move(std::get<0>(args)),
                                             std::move(std::get<1>(args))),
                      [](absl::Status status) { return status; });
                },
                []() { return absl::InternalError("Failed to make stream"); });
          }));
  HTTP2_CLIENT_DLOG << "Http2ClientTransport StartCall End";
}

}
}
