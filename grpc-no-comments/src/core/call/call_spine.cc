// Copyright 2024 gRPC authors.

#include "src/core/call/call_spine.h"

#include <grpc/support/port_platform.h>

#include "absl/functional/any_invocable.h"
#include "src/core/lib/event_engine/event_engine_context.h"
#include "src/core/lib/promise/for_each.h"
#include "src/core/lib/promise/try_seq.h"

namespace grpc_core {

void ForwardCall(CallHandler call_handler, CallInitiator call_initiator,
                 absl::AnyInvocable<void(ServerMetadata&)>
                     on_server_trailing_metadata_from_initiator) {
  call_handler.AddChildCall(call_initiator);

  call_handler.SpawnInfallible(
      "read_messages", [call_handler, call_initiator]() mutable {
        return Seq(
            ForEach(MessagesFrom(call_handler),
                    [call_initiator](MessageHandle msg) mutable {

                      call_initiator.SpawnPushMessage(std::move(msg));
                      return Success{};
                    }),
            [call_initiator]() mutable { call_initiator.SpawnFinishSends(); });
      });
  call_initiator.SpawnInfallible(
      "read_the_things",
      [call_initiator, call_handler,
       on_server_trailing_metadata_from_initiator =
           std::move(on_server_trailing_metadata_from_initiator)]() mutable {
        return Seq(
            call_initiator.CancelIfFails(TrySeq(
                call_initiator.PullServerInitialMetadata(),
                [call_handler, call_initiator](
                    std::optional<ServerMetadataHandle> md) mutable {
                  const bool has_md = md.has_value();
                  return If(
                      has_md,
                      [&call_handler, &call_initiator,
                       md = std::move(md)]() mutable {
                        call_handler.SpawnPushServerInitialMetadata(
                            std::move(*md));
                        return ForEach(
                            MessagesFrom(call_initiator),
                            [call_handler](MessageHandle msg) mutable {
                              call_handler.SpawnPushMessage(std::move(msg));
                              return Success{};
                            });
                      },
                      []() -> StatusFlag { return Success{}; });
                })),
            call_initiator.PullServerTrailingMetadata(),
            [call_handler,
             on_server_trailing_metadata_from_initiator =
                 std::move(on_server_trailing_metadata_from_initiator)](
                ServerMetadataHandle md) mutable {
              on_server_trailing_metadata_from_initiator(*md);
              call_handler.SpawnPushServerTrailingMetadata(std::move(md));
            });
      });
}

CallInitiatorAndHandler MakeCallPair(
    ClientMetadataHandle client_initial_metadata, RefCountedPtr<Arena> arena) {
  DCHECK_NE(arena.get(), nullptr);
  DCHECK_NE(arena->GetContext<grpc_event_engine::experimental::EventEngine>(),
            nullptr);
  auto spine =
      CallSpine::Create(std::move(client_initial_metadata), std::move(arena));
  return {CallInitiator(spine), UnstartedCallHandler(spine)};
}

}
