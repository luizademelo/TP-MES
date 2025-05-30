
// Copyright 2024 gRPC authors.

#ifndef GRPC_SRC_CORE_EXT_TRANSPORT_CHTTP2_TRANSPORT_HTTP2_CLIENT_TRANSPORT_H
#define GRPC_SRC_CORE_EXT_TRANSPORT_CHTTP2_TRANSPORT_HTTP2_CLIENT_TRANSPORT_H

#include <cstdint>
#include <utility>

#include "src/core/call/call_spine.h"
#include "src/core/ext/transport/chttp2/transport/frame.h"
#include "src/core/ext/transport/chttp2/transport/header_assembler.h"
#include "src/core/ext/transport/chttp2/transport/hpack_encoder.h"
#include "src/core/ext/transport/chttp2/transport/hpack_parser.h"
#include "src/core/ext/transport/chttp2/transport/http2_settings.h"
#include "src/core/ext/transport/chttp2/transport/http2_status.h"
#include "src/core/ext/transport/chttp2/transport/http2_transport.h"
#include "src/core/ext/transport/chttp2/transport/keepalive.h"
#include "src/core/ext/transport/chttp2/transport/message_assembler.h"
#include "src/core/ext/transport/chttp2/transport/ping_promise.h"
#include "src/core/lib/promise/inter_activity_mutex.h"
#include "src/core/lib/promise/mpsc.h"
#include "src/core/lib/promise/party.h"
#include "src/core/lib/transport/promise_endpoint.h"
#include "src/core/lib/transport/transport.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/sync.h"

namespace grpc_core {
namespace http2 {

class Http2ClientTransport final : public ClientTransport {

 public:
  Http2ClientTransport(
      PromiseEndpoint endpoint, GRPC_UNUSED const ChannelArgs& channel_args,
      std::shared_ptr<grpc_event_engine::experimental::EventEngine>
          event_engine);

  Http2ClientTransport(const Http2ClientTransport&) = delete;
  Http2ClientTransport& operator=(const Http2ClientTransport&) = delete;
  Http2ClientTransport(Http2ClientTransport&&) = delete;
  Http2ClientTransport& operator=(Http2ClientTransport&&) = delete;
  ~Http2ClientTransport() override;

  FilterStackTransport* filter_stack_transport() override { return nullptr; }
  ClientTransport* client_transport() override { return this; }
  ServerTransport* server_transport() override { return nullptr; }
  absl::string_view GetTransportName() const override { return "http2"; }

  void SetPollset(grpc_stream*, grpc_pollset*) override {}
  void SetPollsetSet(grpc_stream*, grpc_pollset_set*) override {}

  void StartCall(CallHandler call_handler) override;

  void PerformOp(grpc_transport_op*) override;

  void Orphan() override;
  void AbortWithError();

  RefCountedPtr<channelz::SocketNode> GetSocketNode() const override {
    return nullptr;
  }

  auto TestOnlyEnqueueOutgoingFrame(Http2Frame frame) {

    return AssertResultType<absl::Status>(Map(
        outgoing_frames_.MakeSender().Send(std::move(frame)),
        [](StatusFlag status) {
          HTTP2_CLIENT_DLOG
              << "Http2ClientTransport::TestOnlyEnqueueOutgoingFrame status="
              << status;
          return (status.ok()) ? absl::OkStatus()
                               : absl::InternalError("Failed to enqueue frame");
        }));
  }
  auto TestOnlySendPing(absl::AnyInvocable<void()> on_initiate) {
    return ping_manager_.RequestPing(std::move(on_initiate));
  }
  template <typename Factory>
  auto TestOnlySpawnPromise(absl::string_view name, Factory factory) {
    return general_party_->Spawn(name, std::move(factory), [](auto) {});
  }

 private:

  Http2Status ProcessHttp2DataFrame(Http2DataFrame frame);
  Http2Status ProcessHttp2HeaderFrame(Http2HeaderFrame frame);
  Http2Status ProcessHttp2RstStreamFrame(Http2RstStreamFrame frame);
  Http2Status ProcessHttp2SettingsFrame(Http2SettingsFrame frame);
  auto ProcessHttp2PingFrame(Http2PingFrame frame);
  Http2Status ProcessHttp2GoawayFrame(Http2GoawayFrame frame);
  Http2Status ProcessHttp2WindowUpdateFrame(Http2WindowUpdateFrame frame);
  Http2Status ProcessHttp2ContinuationFrame(Http2ContinuationFrame frame);
  Http2Status ProcessHttp2SecurityFrame(Http2SecurityFrame frame);

  auto ReadLoop();

  auto ReadAndProcessOneFrame();

  auto ProcessOneFrame(Http2Frame frame);

  auto OnReadLoopEnded();

  auto WriteFromQueue();

  auto WriteLoop();

  auto OnWriteLoopEnded();

  auto CallOutboundLoop(CallHandler call_handler, uint32_t stream_id,
                        InterActivityMutex<uint32_t>::Lock lock,
                        ClientMetadataHandle metadata);

  auto EnqueueOutgoingFrame(Http2Frame frame) {

    return AssertResultType<absl::Status>(Map(
        outgoing_frames_.MakeSender().Send(std::move(frame)),
        [self = RefAsSubclass<Http2ClientTransport>()](StatusFlag status) {
          HTTP2_CLIENT_DLOG
              << "Http2ClientTransport::EnqueueOutgoingFrame status=" << status;
          return (status.ok())
                     ? absl::OkStatus()
                     : self->HandleError(Http2Status::AbslConnectionError(
                           absl::StatusCode::kInternal,
                           "Failed to enqueue frame"));
        }));
  }

  auto TriggerWriteCycle() { return EnqueueOutgoingFrame(Http2EmptyFrame{}); }

  RefCountedPtr<Party> general_party_;

  PromiseEndpoint endpoint_;
  Http2SettingsManager settings_;

  Http2FrameHeader current_frame_header_;

  struct Stream : public RefCounted<Stream> {
    explicit Stream(CallHandler call, const uint32_t stream_id1)
        : call(std::move(call)),
          stream_state(HttpStreamState::kIdle),
          stream_id(stream_id1),
          header_assembler(stream_id1) {}

    CallHandler call;
    HttpStreamState stream_state;
    const uint32_t stream_id;
    TransportSendQeueue send_queue;
    GrpcMessageAssembler assembler;
    HeaderAssembler header_assembler;
  };

  uint32_t NextStreamId(
      InterActivityMutex<uint32_t>::Lock& next_stream_id_lock) {
    const uint32_t stream_id = *next_stream_id_lock;
    if (stream_id > RFC9113::kMaxStreamId31Bit) {

    }

    (*next_stream_id_lock) += 2;
    return stream_id;
  }

  MpscReceiver<Http2Frame> outgoing_frames_;

  Mutex transport_mutex_;

  absl::flat_hash_map<uint32_t, RefCountedPtr<Stream>> stream_list_
      ABSL_GUARDED_BY(transport_mutex_);

  InterActivityMutex<uint32_t> stream_id_mutex_;
  HPackCompressor encoder_;
  HPackParser parser_;

  bool MakeStream(CallHandler call_handler, uint32_t stream_id);

  void CloseStream(uint32_t stream_id, absl::Status status,
                   DebugLocation whence = {}) {
    HTTP2_CLIENT_DLOG << "Http2ClientTransport::CloseStream for stream id: "
                      << stream_id << " status=" << status
                      << " location=" << whence.file() << ":" << whence.line();

  }
  RefCountedPtr<Http2ClientTransport::Stream> LookupStream(uint32_t stream_id);

  auto EndpointReadSlice(const size_t num_bytes) {
    return Map(endpoint_.ReadSlice(num_bytes),
               [self = RefAsSubclass<Http2ClientTransport>()](
                   absl::StatusOr<Slice> status) {

                 self->keepalive_manager_.GotData();
                 return status;
               });
  }

  auto EndpointRead(const size_t num_bytes) {
    return Map(endpoint_.Read(num_bytes),
               [self = RefAsSubclass<Http2ClientTransport>()](
                   absl::StatusOr<SliceBuffer> status) {

                 self->keepalive_manager_.GotData();
                 return status;
               });
  }

  void CloseTransport(const Http2Status& status, DebugLocation whence = {}) {
    HTTP2_CLIENT_DLOG << "Http2ClientTransport::CloseTransport status="
                      << status << " location=" << whence.file() << ":"
                      << whence.line();

  }

  absl::Status HandleError(Http2Status status, DebugLocation whence = {}) {
    auto error_type = status.GetType();
    DCHECK(error_type != Http2Status::Http2ErrorType::kOk);

    if (error_type == Http2Status::Http2ErrorType::kStreamError) {
      CloseStream(current_frame_header_.stream_id, status.GetAbslStreamError(),
                  whence);
      return absl::OkStatus();
    } else if (error_type == Http2Status::Http2ErrorType::kConnectionError) {
      CloseTransport(status, whence);
      return status.GetAbslConnectionError();
    }

    GPR_UNREACHABLE_CODE(return absl::InternalError("Invalid error type"));
  }
  bool bytes_sent_in_last_write_;

  const Duration keepalive_time_;

  const Duration keepalive_timeout_;

  const Duration ping_timeout_;
  PingManager ping_manager_;
  std::vector<uint64_t> pending_ping_acks_;
  KeepaliveManager keepalive_manager_;

  bool keepalive_permit_without_calls_;

  auto SendPing(absl::AnyInvocable<void()> on_initiate) {
    return ping_manager_.RequestPing(std::move(on_initiate));
  }
  auto WaitForPingAck() { return ping_manager_.WaitForPingAck(); }

  auto CreateAndWritePing(bool ack, uint64_t opaque_data) {
    Http2Frame frame = Http2PingFrame{ack, opaque_data};
    SliceBuffer output_buf;
    Serialize(absl::Span<Http2Frame>(&frame, 1), output_buf);
    return endpoint_.Write(std::move(output_buf), {});
  }

  Duration NextAllowedPingInterval() {
    MutexLock lock(&transport_mutex_);
    return (!keepalive_permit_without_calls_ && stream_list_.empty())
               ? Duration::Hours(2)
               : Duration::Seconds(1);
  }

  auto MaybeSendPing() {
    return ping_manager_.MaybeSendPing(NextAllowedPingInterval(),
                                       ping_timeout_);
  }

  auto MaybeSendPingAcks() {
    return AssertResultType<absl::Status>(If(
        pending_ping_acks_.empty(), [] { return absl::OkStatus(); },
        [this] {
          std::vector<Http2Frame> frames;
          frames.reserve(pending_ping_acks_.size());
          for (auto& opaque_data : pending_ping_acks_) {
            frames.emplace_back(Http2PingFrame{true, opaque_data});
          }
          pending_ping_acks_.clear();
          SliceBuffer output_buf;
          Serialize(absl::Span<Http2Frame>(frames), output_buf);
          return endpoint_.Write(std::move(output_buf), {});
        }));
  }

  class PingSystemInterfaceImpl : public PingInterface {
   public:
    static std::unique_ptr<PingInterface> Make(
        Http2ClientTransport* transport) {
      return std::make_unique<PingSystemInterfaceImpl>(
          PingSystemInterfaceImpl(transport));
    }

    Promise<absl::Status> SendPing(SendPingArgs args) override {
      return transport_->CreateAndWritePing(args.ack, args.opaque_data);
    }

    Promise<absl::Status> TriggerWrite() override {
      return transport_->TriggerWriteCycle();
    }

    Promise<absl::Status> PingTimeout() override {

      LOG(INFO) << "Ping timeout at time: " << Timestamp::Now();

      return Immediate(
          transport_->HandleError(Http2Status::Http2ConnectionError(
              Http2ErrorCode::kRefusedStream, "Ping timeout")));
    }

   private:

    Http2ClientTransport* transport_;
    explicit PingSystemInterfaceImpl(Http2ClientTransport* transport)
        : transport_(transport) {}
  };

  class KeepAliveInterfaceImpl : public KeepAliveInterface {
   public:
    static std::unique_ptr<KeepAliveInterface> Make(
        Http2ClientTransport* transport) {
      return std::make_unique<KeepAliveInterfaceImpl>(
          KeepAliveInterfaceImpl(transport));
    }

   private:
    explicit KeepAliveInterfaceImpl(Http2ClientTransport* transport)
        : transport_(transport) {}
    Promise<absl::Status> SendPingAndWaitForAck() override {
      return TrySeq(transport_->TriggerWriteCycle(), [transport = transport_] {
        return transport->WaitForPingAck();
      });
    }
    Promise<absl::Status> OnKeepAliveTimeout() override {

      LOG(INFO) << "Keepalive timeout triggered";

      return Immediate(
          transport_->HandleError(Http2Status::Http2ConnectionError(
              Http2ErrorCode::kRefusedStream, "Keepalive timeout")));
    }

    bool NeedToSendKeepAlivePing() override {
      bool need_to_send_ping = false;
      {
        MutexLock lock(&transport_->transport_mutex_);
        need_to_send_ping = (transport_->keepalive_permit_without_calls_ ||
                             !transport_->stream_list_.empty());
      }
      return need_to_send_ping;
    }

    Http2ClientTransport* transport_;
  };
};

GRPC_CHECK_CLASS_SIZE(Http2ClientTransport, 600);

}
}

#endif
