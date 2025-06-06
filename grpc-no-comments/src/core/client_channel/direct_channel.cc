// Copyright 2024 gRPC authors.

#include "src/core/client_channel/direct_channel.h"

#include "src/core/call/client_call.h"
#include "src/core/call/interception_chain.h"
#include "src/core/config/core_configuration.h"
#include "src/core/lib/event_engine/event_engine_context.h"
#include "src/core/lib/surface/channel_stack_type.h"
#include "src/core/util/orphanable.h"

namespace grpc_core {

absl::StatusOr<RefCountedPtr<DirectChannel>> DirectChannel::Create(
    std::string target, const ChannelArgs& args) {
  auto* transport = args.GetObject<Transport>();
  if (transport == nullptr) {
    return absl::InvalidArgumentError("Transport not set in ChannelArgs");
  }
  if (transport->client_transport() == nullptr) {
    return absl::InvalidArgumentError("Transport is not a client transport");
  }
  auto transport_call_destination = MakeRefCounted<TransportCallDestination>(
      OrphanablePtr<ClientTransport>(transport->client_transport()));
  auto event_engine =
      args.GetObjectRef<grpc_event_engine::experimental::EventEngine>();
  if (event_engine == nullptr) {
    return absl::InvalidArgumentError("EventEngine not set in ChannelArgs");
  }
  InterceptionChainBuilder builder(args);
  CoreConfiguration::Get().channel_init().AddToInterceptionChainBuilder(
      GRPC_CLIENT_DIRECT_CHANNEL, builder);
  auto interception_chain = builder.Build(transport_call_destination);
  if (!interception_chain.ok()) return interception_chain.status();
  return MakeRefCounted<DirectChannel>(
      std::move(target), args, std::move(event_engine),
      std::move(transport_call_destination), std::move(*interception_chain));
}

void DirectChannel::Orphaned() {
  transport_call_destination_.reset();
  interception_chain_.reset();
}

void DirectChannel::StartCall(UnstartedCallHandler unstarted_handler) {
  unstarted_handler.SpawnInfallible(
      "start",
      [interception_chain = interception_chain_, unstarted_handler]() mutable {
        interception_chain->StartCall(std::move(unstarted_handler));
        return []() {};
      });
}

void DirectChannel::GetInfo(const grpc_channel_info*) {

}

grpc_call* DirectChannel::CreateCall(
    grpc_call* parent_call, uint32_t propagation_mask,
    grpc_completion_queue* cq, grpc_pollset_set* ,
    Slice path, std::optional<Slice> authority, Timestamp deadline,
    bool ) {
  auto arena = call_arena_allocator()->MakeArena();
  arena->SetContext<grpc_event_engine::experimental::EventEngine>(
      event_engine_.get());
  return MakeClientCall(parent_call, propagation_mask, cq, std::move(path),
                        std::move(authority), false, deadline,
                        compression_options(), std::move(arena), Ref());
}

}
