// Copyright 2024 gRPC authors.

#include "src/core/ext/transport/chaotic_good_legacy/control_endpoint.h"

#include "src/core/lib/event_engine/event_engine_context.h"
#include "src/core/lib/event_engine/tcp_socket_utils.h"
#include "src/core/lib/promise/loop.h"
#include "src/core/lib/promise/try_seq.h"

namespace grpc_core {
namespace chaotic_good_legacy {

auto ControlEndpoint::Buffer::Pull() {
  return [this]() -> Poll<SliceBuffer> {
    Waker waker;
    auto cleanup = absl::MakeCleanup([&waker]() { waker.Wakeup(); });
    MutexLock lock(&mu_);
    if (queued_output_.Length() == 0) {
      flush_waker_ = GetContext<Activity>()->MakeNonOwningWaker();
      return Pending{};
    }
    waker = std::move(write_waker_);
    return std::move(queued_output_);
  };
}

ControlEndpoint::ControlEndpoint(
    PromiseEndpoint endpoint,
    grpc_event_engine::experimental::EventEngine* event_engine)
    : endpoint_(std::make_shared<PromiseEndpoint>(std::move(endpoint))) {
  auto arena = SimpleArenaAllocator(0)->MakeArena();
  arena->SetContext(event_engine);
  write_party_ = Party::Make(arena);
  CHECK(event_engine != nullptr);
  write_party_->arena()->SetContext(event_engine);
  write_party_->Spawn(
      "flush-control",
      GRPC_LATENT_SEE_PROMISE(
          "FlushLoop", Loop([endpoint = endpoint_, buffer = buffer_]() {
            return AddErrorPrefix(
                "CONTROL_CHANNEL: ",
                TrySeq(

                    buffer->Pull(),

                    [endpoint, buffer = buffer.get()](SliceBuffer flushing) {
                      GRPC_TRACE_LOG(chaotic_good, INFO)
                          << "CHAOTIC_GOOD: Flush " << flushing.Length()
                          << " bytes from " << buffer << " to "
                          << ResolvedAddressToString(endpoint->GetPeerAddress())
                                 .value_or("<<unknown peer address>>");
                      return endpoint->Write(std::move(flushing),
                                             PromiseEndpoint::WriteArgs{});
                    },

                    []() -> LoopCtl<absl::Status> { return Continue{}; }));
          })),
      [](absl::Status) {});
}

}
}
