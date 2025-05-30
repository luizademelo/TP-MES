// Copyright 2023 gRPC authors.

#include "test/core/transport/test_suite/transport_test.h"

#include <initializer_list>

#include "absl/random/random.h"

namespace grpc_core {

ClientAndServerTransportPair (*g_create_transport_test_fixture)(
    std::shared_ptr<grpc_event_engine::experimental::FuzzingEventEngine>) =
    nullptr;

void TransportTest::SetServerCallDestination() {
  transport_pair_.server->server_transport()->SetCallDestination(
      server_call_destination_);
}

CallInitiator TransportTest::CreateCall(
    ClientMetadataHandle client_initial_metadata) {
  auto call = MakeCall(std::move(client_initial_metadata));
  call.handler.SpawnInfallible(
      "start-call", [this, handler = call.handler]() mutable {
        transport_pair_.client->client_transport()->StartCall(
            handler.StartCall());
      });
  return std::move(call.initiator);
}

CallHandler TransportTest::TickUntilServerCall() {
  auto poll = [this]() -> Poll<CallHandler> {
    auto handler = server_call_destination_->PopHandler();
    if (handler.has_value()) return std::move(*handler);
    return Pending();
  };
  return TickUntil(absl::FunctionRef<Poll<CallHandler>()>(poll));
}

void TransportTest::ServerCallDestination::StartCall(
    UnstartedCallHandler handler) {
  handlers_.push(handler.StartCall());
}

std::optional<CallHandler> TransportTest::ServerCallDestination::PopHandler() {
  if (handlers_.empty()) return std::nullopt;
  auto handler = std::move(handlers_.front());
  handlers_.pop();
  return handler;
}

}
