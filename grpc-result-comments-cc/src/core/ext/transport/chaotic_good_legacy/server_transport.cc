Here's the commented version of the code:

```c++
// Copyright 2022 gRPC authors.

#include "src/core/ext/transport/chaotic_good_legacy/server_transport.h"

#include <grpc/event_engine/event_engine.h>
#include <grpc/grpc.h>
#include <grpc/slice.h>
#include <grpc/support/port_platform.h>

#include <memory>
#include <string>
#include <tuple>

#include "absl/cleanup/cleanup.h"
#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/random/bit_gen_ref.h"
#include "absl/random/random.h"
#include "abs/status/status.h"
#include "absl/status/statusor.h"
#include "src/core/ext/transport/chaotic_good_legacy/chaotic_good_transport.h"
#include "src/core/ext/transport/chaotic_good_legacy/frame.h"
#include "src/core/ext/transport/chaotic_good_legacy/frame_header.h"
#include "src/core/lib/event_engine/event_engine_context.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/promise/activity.h"
#include "src/core/lib/promise/event_engine_wakeup_scheduler.h"
#include "src/core/lib/promise/for_each.h"
#include "src/core/lib/promise/loop.h"
#include "src/core/lib/promise/switch.h"
#include "src/core/lib/promise/try_seq.h"
#include "src/core/lib/resource_quota/arena.h"
#include "src/core/lib/resource_quota/resource_quota.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/lib/slice/slice_buffer.h"
#include "src/core/lib/transport/promise_endpoint.h"
#include "src/core/telemetry/metrics.h"
#include "src/core/util/ref_counted_ptr.h"

namespace grpc_core {
namespace chaotic_good_legacy {

// Pushes a MessageFrame into the call's message reassembly buffer
auto ChaoticGoodServerTransport::PushFrameIntoCall(RefCountedPtr<Stream> stream,
                                                   MessageFrame frame) {
  GRPC_TRACE_LOG(chaotic_good, INFO)
      << "CHAOTIC_GOOD: PushFrameIntoCall: frame=" << frame.ToString();
  return stream->message_reassembly.PushFrameInto(std::move(frame),
                                                  stream->call);
}

// Pushes a BeginMessageFrame into the call's message reassembly buffer
auto ChaoticGoodServerTransport::PushFrameIntoCall(RefCountedPtr<Stream> stream,
                                                   BeginMessageFrame frame) {
  GRPC_TRACE_LOG(chaotic_good, INFO)
      << "CHAOTIC_GOOD: PushFrameIntoCall: frame=" << frame.ToString();
  return stream->message_reassembly.PushFrameInto(std::move(frame),
                                                  stream->call);
}

// Pushes a MessageChunkFrame into the call's message reassembly buffer
auto ChaoticGoodServerTransport::PushFrameIntoCall(RefCountedPtr<Stream> stream,
                                                   MessageChunkFrame frame) {
  GRPC_TRACE_LOG(chaotic_good, INFO)
      << "CHAOTIC_GOOD: PushFrameIntoCall: frame=" << frame.ToString();
  return stream->message_reassembly.PushFrameInto(std::move(frame),
                                                  stream->call);
}

// Handles ClientEndOfStream frame - either completes call sends or fails if
// we're in the middle of a chunked message
auto ChaoticGoodServerTransport::PushFrameIntoCall(RefCountedPtr<Stream> stream,
                                                   ClientEndOfStream) {
  if (stream->message_reassembly.in_message_boundary()) {
    stream->call.FinishSends();
    return Immediate(StatusFlag{Success{}});
  } else {
    stream->message_reassembly.FailCall(
        stream->call, "Received end of stream before end of chunked message");
    return Immediate(StatusFlag{Failure{}});
  }
}

// Dispatches an incoming frame to the appropriate stream handler
template <typename T>
auto ChaoticGoodServerTransport::DispatchFrame(
    RefCountedPtr<ChaoticGoodTransport> transport, IncomingFrame frame) {
  auto stream = LookupStream(frame.header().stream_id);
  return If(
      stream != nullptr,
      [this, &stream, &frame, &transport]() {
        return stream->call.SpawnWaitable(
            "push-frame", [this, stream, frame = std::move(frame),
                           transport = std::move(transport)]() mutable {
              auto& call = stream->call;
              return call.UntilCallCompletes(TrySeq(
                  frame.Payload(),
                  [transport = std::move(transport),
                   header = frame.header()](SliceBuffer payload) {
                    return transport->DeserializeFrame<T>(header,
                                                          std::move(payload));
                  },
                  [stream = std::move(stream), this](T frame) mutable {
                    auto& call = stream->call;
                    return Map(call.CancelIfFails(PushFrameIntoCall(
                                   std::move(stream), std::move(frame))),
                               [](auto) { return absl::OkStatus(); });
                  }));
            });
      },
      []() { return absl::OkStatus(); });
}

namespace {
// Helper function that converts a boolean success status to a transport error
// while capturing the call initiator
auto BooleanSuccessToTransportErrorCapturingInitiator(CallInitiator initiator) {
  return [initiator = std::move(initiator)](StatusFlag success) {
    return success.ok() ? absl::OkStatus()
                        : absl::UnavailableError("Transport closed.");
  };
}
}

// Sends a frame to the client without waiting for acknowledgement
auto ChaoticGoodServerTransport::SendFrame(
    ServerFrame frame, LockBasedMpscSender<ServerFrame> outgoing_frames,
    CallInitiator call_initiator) {
  return Map(outgoing_frames.Send(std::move(frame)),
             BooleanSuccessToTransportErrorCapturingInitiator(
                 std::move(call_initiator)));
}

// Sends a frame to the client and waits for acknowledgement
auto ChaoticGoodServerTransport::SendFrameAcked(
    ServerFrame frame, LockBasedMpscSender<ServerFrame> outgoing_frames,
    CallInitiator call_initiator) {
  return Map(outgoing_frames.SendAcked(std::move(frame)),
             BooleanSuccessToTransportErrorCapturingInitiator(
                 std::move(call_initiator)));
}

// Sends the body of a call to the client by chunking messages
auto ChaoticGoodServerTransport::SendCallBody(
    uint32_t stream_id, LockBasedMpscSender<ServerFrame> outgoing_frames,
    CallInitiator call_initiator) {
  return ForEach(MessagesFrom(call_initiator),
                 [this, stream_id, outgoing_frames = std::move(outgoing_frames),
                  call_initiator](MessageHandle message) mutable {
                   return Map(message_chunker_.Send(std::move(message),
                                                    stream_id, outgoing_frames),
                              BooleanSuccessToTransportErrorCapturingInitiator(
                                  std::move(call_initiator)));
                 });
}

// Sends both initial metadata and body of a call to the client
auto ChaoticGoodServerTransport::SendCallInitialMetadataAndBody(
    uint32_t stream_id, LockBasedMpscSender<ServerFrame> outgoing_frames,
    CallInitiator call_initiator) {
  return TrySeq(
      call_initiator.PullServerInitialMetadata(),
      [stream_id, outgoing_frames, call_initiator,
       this](std::optional<ServerMetadataHandle> md) mutable {
        GRPC_TRACE_LOG(chaotic_good, INFO)
            << "CHAOTIC_GOOD: SendCallInitialMetadataAndBody: md="
            << (md.has_value() ? (*md)->DebugString() : "null");
        return If(
            md.has_value(),
            [&md, stream_id, &outgoing_frames, &call_initiator, this]() {
              ServerInitialMetadataFrame frame;
              frame.body = ServerMetadataProtoFromGrpc(**md);
              frame.stream_id = stream_id;
              return TrySeq(
                  SendFrame(std::move(frame), outgoing_frames, call_initiator),
                  SendCallBody(stream_id, outgoing_frames, call_initiator));
            },
            []() { return absl::OkStatus(); });
      });
}

// Main loop for handling outbound call operations (metadata and body)
auto ChaoticGoodServerTransport::CallOutboundLoop(
    uint32_t stream_id, CallInitiator call_initiator) {
  auto outgoing_frames = outgoing_frames_.MakeSender();
  return GRPC_LATENT_SEE_PROMISE(
      "CallOutboundLoop",
      Seq(Map(SendCallInitialMetadataAndBody(stream_id, outgoing_frames,
                                             call_initiator),
              [stream_id](absl::Status main_body_result) {
                GRPC_TRACE_VLOG(chaotic_good, 2)
                    << "CHAOTIC_GOOD: CallOutboundLoop: stream_id=" << stream_id
                    << " main_body_result=" << main_body_result;
                return Empty{};
              }),
          call_initiator.PullServerTrailingMetadata(),
          [this, stream_id, outgoing_frames,
           call_initiator](ServerMetadataHandle md) mutable {
            ServerTrailingMetadataFrame frame;
            frame.body = ServerMetadataProtoFromGrpc(*md);
            frame.stream_id = stream_id;
            return SendFrame(std::move(frame), outgoing_frames, call_initiator);
          }));
}

// Creates a new stream for an incoming call
absl::Status ChaoticGoodServerTransport::NewStream(
    ChaoticGoodTransport& transport, const FrameHeader& header,
    SliceBuffer payload) {
  CHECK_EQ(header.payload_length, payload.Length());
  // Deserialize client initial metadata
  auto client_initial_metadata_frame =
      transport.DeserializeFrame<ClientInitialMetadataFrame>(
          header, std::move(payload));
  if (!client_initial_metadata_frame.ok()) {
    return client_initial_metadata_frame.status();
  }
  
  // Convert metadata to gRPC format
  auto md = ClientMetadataGrpcFromProto(client_initial_metadata_frame->body);
  if (!md.ok()) {
    return md.status();
  }
  
  // Create arena and call pair
  RefCountedPtr<Arena> arena(call_arena_allocator_->MakeArena());
  arena->SetContext<grpc_event_engine::experimental::EventEngine>(
      event_engine_.get());
  std::optional<CallInitiator> call_initiator;
  auto call = MakeCallPair(std::move(*md), std::move(arena));
  call_initiator.emplace(std::move(call.initiator));
  
  // Add new stream and start processing
  const auto stream_id = client_initial_metadata_frame->stream_id;
  auto add_result = NewStream(stream_id, *call_initiator);
  if (!add_result.ok()) {
    call_initiator.reset();
    return add_result;
  }
  
  call_initiator->SpawnGuarded(
      "server-write", [this, stream_id, call_initiator = *call_initiator,
                       call_handler = std::move(call.handler)]() mutable {
        call_destination_->StartCall(std::move(call_handler));
        return CallOutboundLoop(stream_id, call_initiator);
      });
  return absl::OkStatus();
}

// Reads and processes a single frame from the transport
auto ChaoticGoodServerTransport::ReadOneFrame(
    RefCountedPtr<ChaoticGoodTransport> transport) {
  return GRPC_LATENT_SEE_PROMISE(
      "ReadOneFrame",
      TrySeq(
          transport->ReadFrameBytes(),
          [this, transport](IncomingFrame incoming_frame) mutable {
            return Switch(
                incoming_frame.header().type,
                Case<FrameType::kClientInitialMetadata>([&, this]() {
                  return TrySeq(incoming_frame.Payload(),
                                [this, transport = std::move(transport),
                                 header = incoming_frame.header()](
                                    SliceBuffer payload) mutable {
                                  return NewStream(*transport, header,
                                                   std::move(payload));
                                });
                }),
                Case<FrameType::kMessage>([&, this]() mutable {
                  return DispatchFrame<MessageFrame>(std::move(transport),
                                                     std::move(incoming_frame));
                }),
                Case<FrameType::kBeginMessage>([&, this]() mutable {
                  return DispatchFrame<BeginMessageFrame>(
                      std::move(transport), std::move(incoming_frame));
                }),
                Case<FrameType::kMessageChunk>([&, this]() mutable {
                  return DispatchFrame<MessageChunkFrame>(
                      std::move(transport), std::move(incoming_frame));
                }),
                Case<FrameType::kClientEndOfStream>([&, this]() mutable {
                  return DispatchFrame<ClientEndOfStream>(
                      std::move(transport), std::move(incoming_frame));
                }),
                Case<FrameType::kCancel>([&, this]() {
                  auto stream =
                      ExtractStream(incoming_frame.header().stream_id);
                  GRPC_TRACE_LOG(chaotic_good, INFO)
                      << "Cancel stream " << incoming_frame.header().stream_id
                      << (stream != nullptr ? " (active)" : " (not found)");
                  return If(
                      stream != nullptr,
                      [&stream]() {
                        auto c = std::move(stream->call);
                        return c.SpawnWaitable("cancel", [c]() mutable {
                          c.Cancel();
                          return absl::OkStatus();
                        });
                      },
                      []() -> absl::Status { return absl::OkStatus(); });
                }),
                Default([&]() {
                  LOG_EVERY_N_SEC(INFO, 10)
                      << "Bad frame type: "
                      << incoming_frame.header().ToString();
                  return ImmediateOkStatus();
                }));
          },
          []() -> LoopCtl<absl::Status> { return Continue{}; }));
}

// Main loop for reading frames from the transport
auto ChaoticGoodServerTransport::TransportReadLoop(
    RefCountedPtr<ChaoticGoodTransport> transport) {
  return Seq(got_acceptor_.Wait(),
             Loop([this, transport = std::move(transport)]() mutable {
               return ReadOneFrame(transport);
             }));
}

// Callback for when transport activities complete
auto ChaoticGoodServerTransport::OnTransportActivityDone(
    absl::string_view activity) {
  return [self = RefAsSubclass<ChaoticGoodServerTransport>(),
          activity](absl::Status status) {
    GRPC_TRACE_LOG(chaotic_good, INFO)
        << "CHAOTIC_GOOD: OnTransportActivityDone: activity=" << activity
        << " status=" << status;
    self->AbortWithError();
  };
}

// Constructor for the server transport
ChaoticGoodServerTransport::ChaoticGoodServerTransport(
    const ChannelArgs& args, PromiseEndpoint control_endpoint, Config config,
    RefCountedPtr<ServerConnectionFactory>)
    : call_arena_allocator_(MakeRefCounted<CallArenaAllocator>(
          args.GetObject<ResourceQuota>()
              ->memory_quota()
              ->CreateMemoryAllocator("chaotic-good"),
          1024)),
      event_engine_(
          args.GetObjectRef<grpc_event_engine::experimental::EventEngine>()),
      outgoing_frames_(4),
      message_chunker_(config.MakeMessageChunker()) {
  // Create transport and start processing loops
  auto transport = MakeRefCounted<ChaoticGoodTransport>(
      std::move(control_endpoint), config.TakePendingDataEndpoints(),
      event_engine_,
      args.GetObjectRef<GlobalStatsPluginRegistry::StatsPluginGroup>(),
      config.MakeTransportOptions(), false);
  auto party_arena = SimpleArenaAllocator(0)->MakeArena();
  party_arena->SetContext<grpc_event_engine::experimental::EventEngine>(
      event_engine_.get());
  party_ = Party::Make(std::move(party_arena));
  party_->Spawn(
      "server-chaotic-writer",
      GRPC_LATENT_SEE_PROMISE("ServerTransportWriteLoop",
                              transport->TransportWriteLoop(outgoing_frames_)),
      OnTransportActivityDone("writer"));
  party_->Spawn("server-chaotic-reader",
                GRPC_LATENT_SEE_PROMISE("ServerTransportReadLoop",
                                        TransportReadLoop(transport)),
                OnTransportActivityDone("reader"));
}

// Sets the destination for incoming calls
void ChaoticGoodServerTransport::SetCallDestination(
    RefCountedPtr<UnstartedCallDestination> call_destination) {
  CHECK(call_destination_ == nullptr);
  CHECK(call_destination != nullptr);
  call_destination_ = call_destination;
  got_acceptor_.Set();
}

// Cleans up transport resources
void ChaoticGoodServerTransport::Orphan() {
  AbortWithError();
  RefCountedPtr<Party> party;
  {
    MutexLock lock(&mu_);
    party = std::move(party_);
  }
  party.reset();
  Unref();
}

// Aborts transport with error and cleans up all streams
void ChaoticGoodServerTransport::AbortWithError() {
  outgoing_frames_.MarkClosed();
  ReleasableMutexLock lock(&mu_);
  aborted_with_error_ = true;
  StreamMap stream_map = std::move(stream_map_);
  stream_map_.clear();
  state_tracker_.SetState(GRPC_CHANNEL_SHUTDOWN,
                          absl::UnavailableError("transport closed"),
                          "transport closed");
  lock.Release();
  // Cancel all active streams
  for (auto& pair : stream_map) {
    auto stream = std::move(pair.second);
    auto& call = stream->call;
    call.SpawnInfallible("cancel", [stream = std::move(stream)]() mutable {
      stream->call.Cancel();
    });
  }
}

// Looks up a stream by ID (returns nullptr if not found)
RefCountedPtr<ChaoticGoodServerTransport::Stream>
ChaoticGoodServerTransport::LookupStream(uint32_t stream_id) {
  GRPC_TRACE_LOG(chaotic_good, INFO)
      << "CHAOTIC_GOOD " << this << " LookupStream " << stream_id;
  MutexLock lock(&mu_);
  auto it = stream_map_.find(stream_id);
  if (it == stream_map_.end()) return nullptr;
  return it->second;
}

// Extracts a stream by ID (removes it from the map)
RefCountedPtr<Chaotic