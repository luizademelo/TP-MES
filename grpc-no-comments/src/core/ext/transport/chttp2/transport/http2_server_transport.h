
// Copyright 2024 gRPC authors.

#ifndef GRPC_SRC_CORE_EXT_TRANSPORT_CHTTP2_TRANSPORT_HTTP2_SERVER_TRANSPORT_H
#define GRPC_SRC_CORE_EXT_TRANSPORT_CHTTP2_TRANSPORT_HTTP2_SERVER_TRANSPORT_H

#include <cstdint>
#include <type_traits>

#include "absl/container/flat_hash_map.h"
#include "src/core/call/call_destination.h"
#include "src/core/call/call_spine.h"
#include "src/core/ext/transport/chttp2/transport/frame.h"
#include "src/core/ext/transport/chttp2/transport/hpack_encoder.h"
#include "src/core/ext/transport/chttp2/transport/hpack_parser.h"
#include "src/core/ext/transport/chttp2/transport/http2_settings.h"
#include "src/core/lib/promise/mpsc.h"
#include "src/core/lib/promise/party.h"
#include "src/core/lib/transport/promise_endpoint.h"
#include "src/core/lib/transport/transport.h"
#include "src/core/util/ref_counted.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/sync.h"

namespace grpc_core {
namespace http2 {

class Http2ServerTransport final : public ServerTransport {

 public:
  Http2ServerTransport(
      PromiseEndpoint endpoint, GRPC_UNUSED const ChannelArgs& channel_args,
      std::shared_ptr<grpc_event_engine::experimental::EventEngine>
          event_engine);
  ~Http2ServerTransport() override;

  FilterStackTransport* filter_stack_transport() override { return nullptr; }
  ClientTransport* client_transport() override { return nullptr; }
  ServerTransport* server_transport() override { return this; }
  absl::string_view GetTransportName() const override { return "http2"; }

  void SetPollset(grpc_stream*, grpc_pollset*) override {}
  void SetPollsetSet(grpc_stream*, grpc_pollset_set*) override {}

  void SetCallDestination(
      RefCountedPtr<UnstartedCallDestination> call_destination) override;

  void PerformOp(grpc_transport_op*) override;

  void Orphan() override;
  void AbortWithError();

  RefCountedPtr<channelz::SocketNode> GetSocketNode() const override {
    return nullptr;
  }

 private:

  auto ReadLoop();

  auto ReadAndProcessOneFrame();

  auto ProcessOneFrame(Http2Frame frame);

  auto OnReadLoopEnded();

  auto WriteFromQueue();

  auto WriteLoop();

  auto OnWriteLoopEnded();

  RefCountedPtr<Party> general_party_;

  PromiseEndpoint endpoint_;
  Http2SettingsManager settings_;

  Http2FrameHeader current_frame_header_;

  struct Stream : public RefCounted<Stream> {
    explicit Stream(CallInitiator call) : call(std::move(call)) {}

    CallInitiator call;

  };
  RefCountedPtr<UnstartedCallDestination> call_destination_;

  MpscReceiver<Http2Frame> outgoing_frames_;

  Mutex transport_mutex_;

  absl::flat_hash_map<uint32_t, RefCountedPtr<Stream>> stream_list_
      ABSL_GUARDED_BY(transport_mutex_);

  void CloseStream(uint32_t stream_id, absl::Status status,
                   DebugLocation whence = {}) {
    LOG(INFO) << "Http2ServerTransport::CloseStream for stream id=" << stream_id
              << " status=" << status << " location=" << whence.file() << ":"
              << whence.line();

  }

  void CloseTransport(const Http2Status& status, DebugLocation whence = {}) {
    LOG(INFO) << "Http2ClientTransport::CloseTransport status=" << status
              << " location=" << whence.file() << ":" << whence.line();

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

};

GRPC_CHECK_CLASS_SIZE(Http2ServerTransport, 240);

}
}

#endif
