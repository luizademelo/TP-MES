Here's the commented version of the code:

```c++
// Copyright 2022 gRPC authors.

#include "src/core/ext/transport/chaotic_good/server_transport.h"

#include <grpc/event_engine/event_engine.h>
#include <grpc/grpc.h>
#include <grpc/slice.h>
#include <grpc/support/port_platform.h>

#include <memory>
#include <string>
#include <tuple>

#include "absl/cleanup/cleanup.h"
#include "absl/log/check.h"
#include "abs/log/log.h"
#include "absl/random/bit_gen_ref.h"
#include "absl/random/random.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "src/core/ext/transport/chaotic_good/frame.h"
#include "src/core/ext/transport/chaotic_good/frame_header.h"
#include "src/core/ext/transport/chaotic_good/frame_transport.h"
#include "src/core/ext/transport/chaotic_good/message_chunker.h"
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
#include "src/core/util/ref_counted_ptr.h"

namespace grpc_core {
namespace chaotic_good {

// Pushes a MessageFrame into the call's message reassembly buffer
auto ChaoticGoodServerTransport::StreamDispatch::PushFrameIntoCall(
    RefCountedPtr<Stream> stream, MessageFrame frame) {
  GRPC_TRACE_LOG(chaotic_good, INFO)
      << "CHAOTIC_GOOD: PushFrameIntoCall: frame=" << frame.ToString();
  return stream->message_reassembly.PushFrameInto(std::move(frame),
                                                  stream->call);
}

// Pushes a BeginMessageFrame into the call's message reassembly buffer
auto ChaoticGoodServerTransport::StreamDispatch::PushFrameIntoCall(
    RefCountedPtr<Stream> stream, BeginMessageFrame frame) {
  GRPC_TRACE_LOG(chaotic_good, INFO)
      << "CHAOTIC_GOOD: PushFrameIntoCall: frame=" << frame.ToString();
  return stream->message_reassembly.PushFrameInto(std::move(frame),
                                                  stream->call);
}

// Pushes a MessageChunkFrame into the call's message reassembly buffer
auto ChaoticGoodServerTransport::StreamDispatch::PushFrameIntoCall(
    RefCountedPtr<Stream> stream, MessageChunkFrame frame) {
  GRPC_TRACE_LOG(chaotic_good, INFO)
      << "CHAOTIC_GOOD: PushFrameIntoCall: frame=" << frame.ToString();
  return stream->message_reassembly.PushFrameInto(std::move(frame),
                                                  stream->call);
}

// Handles ClientEndOfStream frame - either finishes sends or fails the call
// if we're in the middle of a chunked message
auto ChaoticGoodServerTransport::StreamDispatch::PushFrameIntoCall(
    RefCountedPtr<Stream> stream, ClientEndOfStream) {
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
void ChaoticGoodServerTransport::StreamDispatch::DispatchFrame(
    IncomingFrame frame) {
  auto stream = LookupStream(frame.header().stream_id);
  if (stream == nullptr) return;
  stream->spawn_serializer->Spawn(
      [this, stream, frame = std::move(frame)]() mutable {
        DCHECK_NE(stream.get(), nullptr);
        auto& call = stream->call;
        return call.CancelIfFails(call.UntilCallCompletes(TrySeq(
            frame.Payload(),
            [stream = std::move(stream), this](Frame frame) mutable {
              return PushFrameIntoCall(std::move(stream),
                                       std::move(std::get<T>(frame)));
            },
            []() { return absl::OkStatus(); })));
      });
}

// Sends call body messages by chunking them into frames
auto ChaoticGoodServerTransport::StreamDispatch::SendCallBody(
    uint32_t stream_id, CallInitiator call_initiator,
    std::shared_ptr<TcpCallTracer> call_tracer) {
  return ForEach(MessagesFrom(call_initiator),
                 [this, stream_id, call_tracer = std::move(call_tracer)](
                     MessageHandle message) mutable {
                   return message_chunker_.Send(std::move(message), stream_id,
                                                call_tracer, outgoing_frames_);
                 });
}

// Sends both initial metadata and body for a call
auto ChaoticGoodServerTransport::StreamDispatch::SendCallInitialMetadataAndBody(
    uint32_t stream_id, CallInitiator call_initiator,
    std::shared_ptr<TcpCallTracer> call_tracer) {
  return TrySeq(
      call_initiator.PullServerInitialMetadata(),
      [stream_id, call_initiator, call_tracer = std::move(call_tracer),
       this](std::optional<ServerMetadataHandle> md) mutable {
        GRPC_TRACE_LOG(chaotic_good, INFO)
            << "CHAOTIC_GOOD: SendCallInitialMetadataAndBody: md="
            << (md.has_value() ? (*md)->DebugString() : "null");
        return If(
            md.has_value(),
            [&md, stream_id, &call_initiator, &call_tracer, this]() {
              ServerInitialMetadataFrame frame;
              frame.body = ServerMetadataProtoFromGrpc(**md);
              frame.stream_id = stream_id;
              return TrySeq(
                  outgoing_frames_.Send(
                      OutgoingFrame{std::move(frame), call_tracer}),
                  SendCallBody(stream_id, call_initiator, call_tracer));
            },
            []() { return StatusFlag(true); });
      });
}

// Main loop for handling outbound call operations
auto ChaoticGoodServerTransport::StreamDispatch::CallOutboundLoop(
    uint32_t stream_id, CallInitiator call_initiator) {
  std::shared_ptr<TcpCallTracer> call_tracer;
  auto tracer = call_initiator.arena()->GetContext<CallTracerInterface>();
  if (tracer != nullptr && tracer->IsSampled()) {
    call_tracer = tracer->StartNewTcpTrace();
  }
  return GRPC_LATENT_SEE_PROMISE(
      "CallOutboundLoop",
      Seq(Map(SendCallInitialMetadataAndBody(stream_id, call_initiator,
                                             call_tracer),
              [stream_id](StatusFlag main_body_result) {
                GRPC_TRACE_VLOG(chaotic_good, 2)
                    << "CHAOTIC_GOOD: CallOutboundLoop: stream_id=" << stream_id
                    << " main_body_result=" << main_body_result;
                return Empty{};
              }),
          call_initiator.PullServerTrailingMetadata(),
          [outgoing_frames = outgoing_frames_, stream_id,
           call_tracer](ServerMetadataHandle md) mutable {
            ServerTrailingMetadataFrame frame;
            frame.body = ServerMetadataProtoFromGrpc(*md);
            frame.stream_id = stream_id;
            return outgoing_frames.Send(
                OutgoingFrame{std::move(frame), call_tracer});
          }));
}

// Creates a new stream for incoming client initial metadata
absl::Status ChaoticGoodServerTransport::StreamDispatch::NewStream(
    uint32_t stream_id,
    ClientInitialMetadataFrame client_initial_metadata_frame) {
  auto md = ClientMetadataGrpcFromProto(client_initial_metadata_frame.body);
  if (!md.ok()) {
    return md.status();
  }
  RefCountedPtr<Arena> arena(call_arena_allocator_->MakeArena());
  arena->SetContext<grpc_event_engine::experimental::EventEngine>(
      ctx_->event_engine.get());
  std::optional<CallInitiator> call_initiator;
  auto call = MakeCallPair(std::move(*md), std::move(arena));
  call_initiator.emplace(std::move(call.initiator));
  auto add_result = AddStream(stream_id, *call_initiator);
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

// Processes the next incoming frame by type
auto ChaoticGoodServerTransport::StreamDispatch::ProcessNextFrame(
    IncomingFrame incoming_frame) {
  return Switch(
      incoming_frame.header().type,
      Case<FrameType::kClientInitialMetadata>([&, this]() {
        return Map(
            TrySeq(
                incoming_frame.Payload(),
                [this, header = incoming_frame.header()](Frame frame) mutable {
                  return NewStream(
                      header.stream_id,
                      std::move(std::get<ClientInitialMetadataFrame>(frame)));
                }),
            [](absl::Status status) {
              if (!status.ok()) {
                LOG(ERROR) << "Failed to process client initial metadata: "
                           << status;
              }
            });
      }),
      Case<FrameType::kMessage>([&, this]() mutable {
        DispatchFrame<MessageFrame>(std::move(incoming_frame));
      }),
      Case<FrameType::kBeginMessage>([&, this]() mutable {
        DispatchFrame<BeginMessageFrame>(std::move(incoming_frame));
      }),
      Case<FrameType::kMessageChunk>([&, this]() mutable {
        DispatchFrame<MessageChunkFrame>(std::move(incoming_frame));
      }),
      Case<FrameType::kClientEndOfStream>([&, this]() mutable {
        DispatchFrame<ClientEndOfStream>(std::move(incoming_frame));
      }),
      Case<FrameType::kCancel>([&, this]() {
        auto stream = ExtractStream(incoming_frame.header().stream_id);
        GRPC_TRACE_LOG(chaotic_good, INFO)
            << "Cancel stream " << incoming_frame.header().stream_id
            << (stream != nullptr ? " (active)" : " (not found)");
        if (stream == nullptr) return;
        auto& c = stream->call;
        c.SpawnInfallible("cancel", [c]() mutable { c.Cancel(); });
      }),
      Default([&]() {
        LOG_EVERY_N_SEC(INFO, 10)
            << "Bad frame type: " << incoming_frame.header().ToString();
      }));
}

// Handles an incoming frame by spawning a task to process it
void ChaoticGoodServerTransport::StreamDispatch::OnIncomingFrame(
    IncomingFrame incoming_frame) {
  incoming_frame_spawner_->Spawn(
      [self = RefAsSubclass<StreamDispatch>(),
       incoming_frame = std::move(incoming_frame)]() mutable {
        return self->ProcessNextFrame(std::move(incoming_frame));
      });
}

// Constructor for ChaoticGoodServerTransport
ChaoticGoodServerTransport::ChaoticGoodServerTransport(
    const ChannelArgs& args, OrphanablePtr<FrameTransport> frame_transport,
    MessageChunker message_chunker)
    : state_{std::make_unique<ConstructionParameters>(args, message_chunker)},
      frame_transport_(std::move(frame_transport)) {}

// Constructor for StreamDispatch
ChaoticGoodServerTransport::StreamDispatch::StreamDispatch(
    const ChannelArgs& args, FrameTransport* frame_transport,
    MessageChunker message_chunker,
    RefCountedPtr<UnstartedCallDestination> call_destination)
    : ctx_(frame_transport->ctx()),
      call_arena_allocator_(MakeRefCounted<CallArenaAllocator>(
          args.GetObject<ResourceQuota>()
              ->memory_quota()
              ->CreateMemoryAllocator("chaotic-good"),
          1024)),
      call_destination_(std::move(call_destination)),
      message_chunker_(message_chunker) {
  CHECK(ctx_ != nullptr);
  auto party_arena = SimpleArenaAllocator(0)->MakeArena();
  party_arena->SetContext<grpc_event_engine::experimental::EventEngine>(
      ctx_->event_engine.get());
  party_ = Party::Make(std::move(party_arena));
  incoming_frame_spawner_ = party_->MakeSpawnSerializer();
  MpscReceiver<OutgoingFrame> outgoing_pipe(8);
  outgoing_frames_ = outgoing_pipe.MakeSender();
  frame_transport->Start(party_.get(), std::move(outgoing_pipe), Ref());
}

// Sets the call destination for the transport
void ChaoticGoodServerTransport::SetCallDestination(
    RefCountedPtr<UnstartedCallDestination> call_destination) {
  auto construction_parameters =
      std::move(std::get<std::unique_ptr<ConstructionParameters>>(state_));
  state_ = MakeRefCounted<StreamDispatch>(
      construction_parameters->args, frame_transport_.get(),
      construction_parameters->message_chunker, std::move(call_destination));
}

// Handles transport orphanation
void ChaoticGoodServerTransport::Orphan() {
  if (auto* p = std::get_if<RefCountedPtr<StreamDispatch>>(&state_);
      p != nullptr) {
    (*p)->OnFrameTransportClosed(absl::UnavailableError("Transport closed"));
  }
  frame_transport_.reset();
  state_ = Orphaned{};
  Unref();
}

// Handles frame transport closure by cleaning up all streams
void ChaoticGoodServerTransport::StreamDispatch::OnFrameTransportClosed(
    absl::Status status) {
  GRPC_TRACE_LOG(chaotic_good, INFO)
      << "CHAOTIC_GOOD: OnFrameTransportClosed: " << status;

  ReleasableMutexLock lock(&mu_);
  last_seen_new_stream_id_ = std::numeric_limits<uint32_t>::max();
  StreamMap stream_map = std::move(stream_map_);
  stream_map_.clear();
  state_tracker_.SetState(GRPC_CHANNEL_SHUTDOWN,
                          absl::UnavailableError("transport closed"),
                          "transport closed");
  lock.Release();
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
ChaoticGoodServerTransport::StreamDispatch::LookupStream(uint32_t stream_id) {
  GRPC_TRACE_LOG(chaotic_good, INFO)
      << "CHAOTIC_GOOD " << this << " LookupStream " << stream_id;
  MutexLock lock(&mu_);
  auto it = stream_map_.find(stream_id);
  if (it == stream_map_.end()) return nullptr;
  return it->second;
}

// Extracts a stream by ID (removes it from the map)
RefCountedPtr<ChaoticGoodServerTransport::Stream>
ChaoticGoodServerTransport::StreamDispatch::ExtractStream(uint32_t stream_id) {
  GRPC_TRACE_LOG(chaotic_good, INFO)
      << "CHAOTIC_GOOD " << this << " ExtractStream " << stream_id;
  MutexLock lock(&mu_);
  auto it = stream_map_.find(stream_id);
  if (it == stream_map_.end()) return nullptr;
  auto r = std::move(it->second);
  stream_map_.erase(it);
  return r;
}

// Adds a new stream to the stream map
absl::Status ChaoticGoodServerTransport::StreamDispatch::AddStream(
    uint32_t stream_id, CallInitiator call_initiator) {
  MutexLock lock(&mu_);
  GRPC_TRACE_LOG(chaotic_good, INFO)
      << "CHAOTIC_GOOD " << this << " NewStream " << stream_id
      << " last_seen_new_stream_id_=" << last_seen_new_stream_id_;
  auto it = stream_map_.find(stream_id);
  if (stream_id <= last_seen_new_stream_id_) {
    return absl::InternalError("Stream id is not increasing");
  }
  if (it != stream_map_.end()) {
    return absl::InternalError("Stream already exists");
  }
  const bool on_done_added = call_initiator.OnDone(
      [self = RefAsSubclass<StreamDispatch>(), stream_id](bool) {
        GRPC_TRACE_LOG(chaotic_good, INFO)
            << "CHAOTIC_GOOD " << self.get() << " OnDone " << stream_id;
        auto stream = self->ExtractStream(stream_id);
        if (stream != nullptr) {
          auto& call = stream->call;
          call.SpawnInfallible("cancel",
                               [stream = std::move(stream)]() mutable {
                                 stream->call.Cancel();
                               });
        }
      });
  if (!on_done_added) {
    return absl::CancelledError();
  }
  stream_map_.emplace(stream_id,
                      MakeRefCounted<Stream>(std::move(call_initiator)));
  return absl::OkStatus();
}

// Starts watching for connectivity state changes
void ChaoticGoodServerTransport::StreamDispatch::StartConnectivityWatch(
    grpc_connectivity_state state,
    OrphanablePtr<ConnectivityStateWatcherInterface> watcher) {
  MutexLock lock(&mu_);
  state_tracker_.AddWat