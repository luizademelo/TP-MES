// Copyright 2023 gRPC authors.

#ifndef GRPC_SRC_CORE_EXT_TRANSPORT_CHAOTIC_GOOD_LEGACY_CHAOTIC_GOOD_TRANSPORT_H
#define GRPC_SRC_CORE_EXT_TRANSPORT_CHAOTIC_GOOD_LEGACY_CHAOTIC_GOOD_TRANSPORT_H

#include <grpc/support/port_platform.h>

#include <cstdint>
#include <limits>
#include <memory>
#include <utility>

#include "absl/strings/escaping.h"
#include "src/core/call/call_spine.h"
#include "src/core/ext/transport/chaotic_good_legacy/control_endpoint.h"
#include "src/core/ext/transport/chaotic_good_legacy/data_endpoints.h"
#include "src/core/ext/transport/chaotic_good_legacy/frame.h"
#include "src/core/ext/transport/chaotic_good_legacy/frame_header.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/event_engine/event_engine_context.h"
#include "src/core/lib/event_engine/tcp_socket_utils.h"
#include "src/core/lib/promise/lock_based_mpsc.h"
#include "src/core/lib/promise/loop.h"
#include "src/core/lib/promise/match_promise.h"
#include "src/core/lib/promise/seq.h"
#include "src/core/lib/promise/try_join.h"
#include "src/core/lib/promise/try_seq.h"
#include "src/core/lib/transport/promise_endpoint.h"

namespace grpc_core {
namespace chaotic_good_legacy {

inline std::vector<PromiseEndpoint> OneDataEndpoint(PromiseEndpoint endpoint) {
  std::vector<PromiseEndpoint> ep;
  ep.emplace_back(std::move(endpoint));
  return ep;
}

class IncomingFrame {
 public:
  template <typename T>
  IncomingFrame(FrameHeader header, T payload, size_t remove_padding)
      : header_(header),
        payload_(std::move(payload)),
        remove_padding_(remove_padding) {}

  const FrameHeader& header() { return header_; }

  auto Payload() {
    return Map(
        MatchPromise(
            std::move(payload_),
            [](absl::StatusOr<SliceBuffer> status) { return status; },
            [](DataEndpoints::ReadTicket ticket) { return ticket.Await(); }),
        [remove_padding =
             remove_padding_](absl::StatusOr<SliceBuffer> payload) {
          if (payload.ok()) payload->RemoveLastNBytesNoInline(remove_padding);
          return payload;
        });
  }

 private:
  FrameHeader header_;
  std::variant<absl::StatusOr<SliceBuffer>, DataEndpoints::ReadTicket> payload_;
  size_t remove_padding_;
};

class ChaoticGoodTransport : public RefCounted<ChaoticGoodTransport> {
 public:
  struct Options {
    uint32_t encode_alignment = 64;
    uint32_t decode_alignment = 64;
    uint32_t inlined_payload_size_threshold = 8 * 1024;
  };

  ChaoticGoodTransport(
      PromiseEndpoint control_endpoint,
      std::vector<PendingConnection> pending_data_endpoints,
      std::shared_ptr<grpc_event_engine::experimental::EventEngine>
          event_engine,
      std::shared_ptr<GlobalStatsPluginRegistry::StatsPluginGroup>
          stats_plugin_group,
      Options options, bool enable_tracing)
      : event_engine_(std::move(event_engine)),
        control_endpoint_(std::move(control_endpoint), event_engine_.get()),
        data_endpoints_(std::move(pending_data_endpoints), event_engine_.get(),
                        std::move(stats_plugin_group), enable_tracing),
        options_(options) {}

  auto WriteFrame(const FrameInterface& frame) {
    FrameHeader header = frame.MakeHeader();
    GRPC_TRACE_LOG(chaotic_good, INFO)
        << "CHAOTIC_GOOD: WriteFrame to:"
        << ResolvedAddressToString(control_endpoint_.GetPeerAddress())
               .value_or("<<unknown peer address>>")
        << " " << frame.ToString();
    return If(

        data_endpoints_.empty() ||
            header.payload_length <= options_.inlined_payload_size_threshold,

        [this, &header, &frame]() {
          SliceBuffer output;
          header.Serialize(output.AddTiny(FrameHeader::kFrameHeaderSize));
          frame.SerializePayload(output);
          return control_endpoint_.Write(std::move(output));
        },

        [this, header, &frame]() mutable {
          SliceBuffer payload;

          header.payload_connection_id = 1;
          const size_t padding = header.Padding(options_.encode_alignment);
          frame.SerializePayload(payload);
          GRPC_TRACE_LOG(chaotic_good, INFO)
              << "CHAOTIC_GOOD: Send " << payload.Length()
              << "b payload on data channel; add " << padding << " bytes for "
              << options_.encode_alignment << " alignment";
          if (padding != 0) {
            auto slice = MutableSlice::CreateUninitialized(padding);
            memset(slice.data(), 0, padding);
            payload.AppendIndexed(Slice(std::move(slice)));
          }
          return Seq(data_endpoints_.Write(std::move(payload)),
                     [this, header](uint32_t connection_id) mutable {
                       header.payload_connection_id = connection_id + 1;
                       SliceBuffer header_frame;
                       header.Serialize(
                           header_frame.AddTiny(FrameHeader::kFrameHeaderSize));
                       return control_endpoint_.Write(std::move(header_frame));
                     });
        });
  }

  template <typename Frame>
  auto TransportWriteLoop(LockBasedMpscReceiver<Frame>& outgoing_frames) {
    return Loop([self = Ref(), &outgoing_frames] {
      return TrySeq(

          outgoing_frames.Next(),

          [self = self.get()](Frame client_frame) {
            return self->WriteFrame(
                absl::ConvertVariantTo<FrameInterface&>(client_frame));
          },
          []() -> LoopCtl<absl::Status> {

            return Continue();
          });
    });
  }

  auto ReadFrameBytes() {
    return TrySeq(
        control_endpoint_.ReadSlice(FrameHeader::kFrameHeaderSize),
        [this](Slice read_buffer) {
          auto frame_header =
              FrameHeader::Parse(reinterpret_cast<const uint8_t*>(
                  GRPC_SLICE_START_PTR(read_buffer.c_slice())));
          GRPC_TRACE_LOG(chaotic_good, INFO)
              << "CHAOTIC_GOOD: ReadHeader from:"
              << ResolvedAddressToString(control_endpoint_.GetPeerAddress())
                     .value_or("<<unknown peer address>>")
              << " "
              << (frame_header.ok() ? frame_header->ToString()
                                    : frame_header.status().ToString());
          return frame_header;
        },
        [this](FrameHeader frame_header) {
          return If(

              frame_header.payload_connection_id == 0,

              [this, frame_header]() {
                return Map(control_endpoint_.Read(frame_header.payload_length),
                           [frame_header](absl::StatusOr<SliceBuffer> payload)
                               -> absl::StatusOr<IncomingFrame> {
                             if (!payload.ok()) return payload.status();
                             return IncomingFrame(frame_header,
                                                  std::move(payload), 0);
                           });
              },

              [this, frame_header]() -> absl::StatusOr<IncomingFrame> {
                const auto padding =
                    frame_header.Padding(options_.decode_alignment);
                return IncomingFrame(
                    frame_header,
                    data_endpoints_.Read(frame_header.payload_connection_id - 1,
                                         frame_header.payload_length + padding),
                    padding);
              });
        });
  }

  template <typename T>
  absl::StatusOr<T> DeserializeFrame(const FrameHeader& header,
                                     SliceBuffer payload) {
    T frame;
    GRPC_TRACE_LOG(chaotic_good, INFO)
        << "CHAOTIC_GOOD: Deserialize " << header << " with payload "
        << absl::CEscape(payload.JoinIntoString());
    CHECK_EQ(header.payload_length, payload.Length());
    auto s = frame.Deserialize(header, std::move(payload));
    GRPC_TRACE_LOG(chaotic_good, INFO)
        << "CHAOTIC_GOOD: DeserializeFrame "
        << (s.ok() ? frame.ToString() : s.ToString());
    if (s.ok()) return std::move(frame);
    return std::move(s);
  }

 private:
  std::shared_ptr<grpc_event_engine::experimental::EventEngine> event_engine_;
  ControlEndpoint control_endpoint_;
  DataEndpoints data_endpoints_;
  const Options options_;
};

}
}

#endif
