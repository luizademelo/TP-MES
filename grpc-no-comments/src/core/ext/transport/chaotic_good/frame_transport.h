// Copyright 2024 gRPC authors.

#ifndef GRPC_SRC_CORE_EXT_TRANSPORT_CHAOTIC_GOOD_FRAME_TRANSPORT_H
#define GRPC_SRC_CORE_EXT_TRANSPORT_CHAOTIC_GOOD_FRAME_TRANSPORT_H

#include "src/core/ext/transport/chaotic_good/frame.h"
#include "src/core/ext/transport/chaotic_good/transport_context.h"
#include "src/core/lib/promise/map.h"
#include "src/core/lib/promise/match_promise.h"
#include "src/core/lib/promise/mpsc.h"
#include "src/core/lib/promise/party.h"
#include "src/core/lib/promise/pipe.h"
#include "src/core/lib/promise/promise.h"
#include "src/core/telemetry/tcp_tracer.h"

namespace grpc_core {
namespace chaotic_good {

class IncomingFrame {
 public:
  IncomingFrame(FrameHeader header, absl::StatusOr<SliceBuffer> payload)
      : header_(header), payload_(std::move(payload)) {}
  IncomingFrame(FrameHeader header,
                Promise<absl::StatusOr<SliceBuffer>> payload)
      : header_(header), payload_(std::move(payload)) {}

  const FrameHeader& header() { return header_; }

  auto Payload() {
    return Map(MatchPromise(
                   std::move(payload_),
                   [](absl::StatusOr<SliceBuffer> status) { return status; },
                   [](Promise<absl::StatusOr<SliceBuffer>> promise) {
                     return promise;
                   }),
               [header = header_](absl::StatusOr<SliceBuffer> payload)
                   -> absl::StatusOr<Frame> {
                 if (!payload.ok()) return payload.status();
                 return ParseFrame(header, std::move(*payload));
               });
  }

 private:
  FrameHeader header_;
  std::variant<absl::StatusOr<SliceBuffer>,
               Promise<absl::StatusOr<SliceBuffer>>>
      payload_;
};

struct OutgoingFrame {
  Frame payload;

  std::shared_ptr<TcpCallTracer> call_tracer;
};

inline OutgoingFrame UntracedOutgoingFrame(Frame frame) {
  return OutgoingFrame{std::move(frame), nullptr};
}

class FrameTransportSink : public RefCounted<FrameTransportSink> {
 public:
  using RefCounted::RefCounted;

  virtual void OnIncomingFrame(IncomingFrame incoming_frame) = 0;
  virtual void OnFrameTransportClosed(absl::Status status) = 0;
};

class FrameTransport : public InternallyRefCounted<FrameTransport> {
 public:
  using InternallyRefCounted::InternallyRefCounted;

  virtual void Start(Party* party, MpscReceiver<OutgoingFrame> outgoing_frames,
                     RefCountedPtr<FrameTransportSink> sink) = 0;
  virtual TransportContextPtr ctx() = 0;
};

}
}

#endif
